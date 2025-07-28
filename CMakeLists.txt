#------------------------------------------------------------------------------
#
# \brief    CMakeLists.txt file for "libHALWrapper"
#
#           The source files are (mostly) obtained from stm via obtain.sh script.
#           To let the Depencies work the sourcefiles need to be specified with
#           absolute pathes via an ${B} variable.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


cmake_minimum_required( VERSION 3.11 )

# ASM neccessary or startup asembler file does not get included
project( libHALWrapper ASM C CXX )

option( MCU_AUTO_FLAGS "When this option is set, adding libHALWrapper as \
   subdirectory will set compiler flags for given MCU." OFF )
option( BUILD_EXAMPLE  "Build an simple 'Hello World'. This can only be done \
   when libHALWrapper is the top level CMake project." OFF )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )

if( BUILD_EXAMPLE )

   if( NOT PROJECT_IS_TOP_LEVEL )
      message( FATAL_ERROR "The libHALWrapper example can only be build when it is build in top level, not in a cmake sub directory." )
   endif( NOT PROJECT_IS_TOP_LEVEL )
   
   if( NOT DEFINED MCU )
      set( MCU stm32f303x8 )
   endif( NOT DEFINED MCU )
   
   find_package( MCUShrink )
   
endif( BUILD_EXAMPLE )

if( NOT DEFINED MCU )
   message( FATAL_ERROR
      "Variable MCU is not set. This is required."
      " Example: -DMCU=stm32f303x8"
   )
endif( NOT DEFINED MCU )

# The example will automatically set cmake variables. As long as libHALWrapper
# should be able to work standalone without 'arena', the variables have to be
# set here to compile.
find_package( MCURev )

# The example will automatically set compiler flags for e.g. stm32f303
if( MCU_AUTO_FLAGS )
   find_package( MCUFlags )
endif( MCU_AUTO_FLAGS )

set ( B "${CMAKE_CURRENT_BINARY_DIR}/HAL" )
file( MAKE_DIRECTORY "${B}" )

if ( "${MCU}" STREQUAL "" )
        message ( FATAL_ERROR 
           "CMake variable 'MCU' is not set. "
           "It should be something like 'stm32f042x6'."
           "If you are using arena: Check your arena board files. \n"
           "The currently used arena board is ${ARENA_BOARD}.\n"
           "The currently used board file is '${ARENA_BOARD_FILE}'."
        )
endif( )

set( LIST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/stm32${MCU_REV}_hal.list )

if ( NOT EXISTS "${LIST_FILE}" )
   message( FATAL_ERROR "List file does not exist for MCU '${MCU}': ${LIST_FILE}" )
endif( )

# Get filenames for C-Files from list-file in data directory; make it a proper list
file( READ ${LIST_FILE} libHALWrapper_SOURCES )
string( STRIP "${libHALWrapper_SOURCES}" libHALWrapper_SOURCES )
string( REPLACE "\n" ";" libHALWrapper_SOURCES ${libHALWrapper_SOURCES} )
list( TRANSFORM libHALWrapper_SOURCES PREPEND ${B}/src/${MCU_REV}/ )

# Some startup scripts are flash size dependant, some are not; this is
# reflected in the filename.
if(      ( MCU_REV_MASK STREQUAL "f407xx" )
      OR ( MCU_REV_MASK STREQUAL "g031xx" )
      OR ( MCU_REV_MASK STREQUAL "g030xx" )
      OR ( MCU_REV_MASK STREQUAL "g431xx" )
      OR ( MCU_REV_MASK STREQUAL "g441xx" )
      OR ( MCU_REV_MASK STREQUAL "l011xx" )
      OR ( MCU_REV_MASK STREQUAL "l031xx" )
      # OR ( MCU_REV_MASK STREQUAL "l152xx" )   # Nope!
      OR ( MCU_REV_MASK STREQUAL "l431xx" )
      OR ( MCU_REV_MASK STREQUAL "l443xx" )
)
   set( MCU_STARTUP_CODE "stm32${MCU_REV_MASK}" )
else( )
   set( MCU_STARTUP_CODE "stm32${MCU_REV_LONG}" )
endif()

if( MCU_ALIAS )
   set( MCU_STARTUP_CODE "${MCU_ALIAS}" )
endif()

set(
   libHALWrapper_SOURCES
      ${libHALWrapper_SOURCES}
      ${B}/src/${MCU_REV}/startup_${MCU_STARTUP_CODE}.s
      ${B}/src/${MCU_REV}/system_stm32${MCU_REV}xx.c
)

# Get filenames for Header-Files from list-file in data directory; make it a proper list
set( LIST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/stm32${MCU_REV}_hal_header.list )
file( READ ${LIST_FILE} libHALWrapper_HEADERS )
string( STRIP "${libHALWrapper_HEADERS}" libHALWrapper_HEADERS )
string( REPLACE "\n" ";" libHALWrapper_HEADERS ${libHALWrapper_HEADERS} )
list( TRANSFORM libHALWrapper_HEADERS PREPEND ${B}/include/${MCU_REV}/stm/ )

set(
   libHALWrapper_HEADERS
      ${libHALWrapper_HEADERS}
      ${B}/include/${MCU_REV}/stm/stm32${MCU_REV}xx.h
      ${B}/include/${MCU_REV}/stm/${MCU_STARTUP_CODE}.h
      ${B}/include/${MCU_REV}/stm/core_cm0.h
      ${B}/include/${MCU_REV}/stm/core_cm1.h
      ${B}/include/${MCU_REV}/stm/core_cm3.h
      ${B}/include/${MCU_REV}/stm/core_cm4.h
      ${B}/include/${MCU_REV}/stm/cmsis_version.h
      ${B}/include/${MCU_REV}/stm/cmsis_compiler.h
      ${B}/include/${MCU_REV}/stm/cmsis_gcc.h
      ${B}/include/${MCU_REV}/stm/mpu_armv7.h
      ${B}/include/${MCU_REV}/stm/system_stm32${MCU_REV}xx.h
)


set (
   libHALWrapper_DOCS
      ${B}/doc/LICENSE.md
)


#-----------------------------------------------------------------------------


set(
   libHALWrapper_SOURCES_SUPPLEMENTARY
      src/system_sup.c
      src/system_sup_stm32${MCU_REV}xx.c
)

set( libHALWrapper_HEADERS_SUPPLEMENTARY
)

find_program(BASH bash HINTS /bin)

# How to obtain HAL sources
add_custom_command(
   OUTPUT
      ${libHALWrapper_SOURCES} ${libHALWrapper_HEADERS} ${libHALWrapper_DOCS}
   COMMAND
      ${CMAKE_COMMAND} -E env ${BASH} -c "${CMAKE_CURRENT_SOURCE_DIR}/scripts/obtain_github.sh ${MCU_REV} &> obtain_${MCU_REV}.log"
   COMMENT "Obtaining HAL sources"
   VERBATIM
   WORKING_DIRECTORY ${B}
)

add_library(
   HALWrapper-${MCU_REV} STATIC
   ${libHALWrapper_SOURCES}
   ${libHALWrapper_SOURCES_SUPPLEMENTARY}
   ${libHALWrapper_HEADERS}
   ${libHALWrapper_HEADERS_SUPPLEMENTARY}
   ${libHALWrapper_DOCS}
)

add_library(
   HALWrapper::HALWrapper ALIAS HALWrapper-${MCU_REV}
)

target_compile_definitions(
   HALWrapper-${MCU_REV}
      PUBLIC
         -D${MCU_UC}=1
         -DSTM32${MCU_REV_UC}=1
         -DSTM32${MCU_REV_MID_UC}=1
         -DSTM32${MCU_REV_LONG_UC}=1
         -DSTM32${MCU_REV_MASK_UC}=1
         -DMCU_REV=${MCU_REV}
         -DMCU=${MCU}
)

# An STM32L152x8 needs the macro STM32L152xB to be set for HAL library.
if( MCU_ALIAS_UC )
   target_compile_definitions(
      HALWrapper-${MCU_REV}
         PUBLIC
            -D${MCU_ALIAS_UC}=1
   )
endif( MCU_ALIAS_UC )

target_include_directories(
   HALWrapper-${MCU_REV}
   INTERFACE
      "${B}/include/${MCU_REV}"
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
   PRIVATE
      # Some stm headers include files without subdirectory
      "${B}/include/${MCU_REV}/stm"
      "${libHALWrapper_SOURCE_DIR}/include"
      "${B}/include/${MCU_REV}"
)

install(
   TARGETS
      HALWrapper-${MCU_REV}
   RUNTIME DESTINATION lib
   ARCHIVE DESTINATION lib
)

install (
   FILES ${libHALWrapper_HEADERS}
   DESTINATION include/stm
)

install (
   DIRECTORY include/HALWrapper
   DESTINATION include
)

install (
   FILES ${B}/doc/LICENSE.md
   DESTINATION share/doc/libHALWrapper
)

install (
   FILES ${B}/doc/LICENSE_HAL.md
   DESTINATION share/doc/libHALWrapper
)

install (
   DIRECTORY ${B}/doc/HAL
   DESTINATION share/doc/libHALWrapper
)

install (
   DIRECTORY ${B}/doc/CMSIS
   DESTINATION share/doc/libHALWrapper
)


if( BUILD_EXAMPLE )
   add_subdirectory( example )
endif( BUILD_EXAMPLE )


if( NOT PROJECT_IS_TOP_LEVEL )
   # Set some variables for the parent scope to make things easier.
   # Otherwise they would need to also include package "MCURev"
   set( MCU_REV "${MCU_REV}" PARENT_SCOPE )
   set( MCU_REV_LONG "${MCU_REV_LONG}" PARENT_SCOPE )

   # Change parents CMAKE_MODULE_PATH?
   # set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE )
endif( NOT PROJECT_IS_TOP_LEVEL )


#------------------------------------------------------------------------------
