   #------------------------------------------------------------------------------
#
# \brief    CMakeLists.txt file for "libHALWrapper"
#
#           The source files are (mostly) obtained from stm via obtain.sh script.
#           To let the Depencies work we need to mention the sourcefiles with
#           absolute pathes via an ${B} variable.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


cmake_minimum_required( VERSION 3.11 )

# ASM neccessary or startup asembler file does not get included
project( libHALWrapper ASM C CXX )

option( BUILD_EXAMPLE "Build an simple 'Hello World' example; use the script instead" 0 )

string(SUBSTRING "${MCU_REV_LONG}" 0 2 MCU_REV )

set ( B "${CMAKE_CURRENT_BINARY_DIR}/HAL" )
file( MAKE_DIRECTORY "${B}" )

if ( "${MCU_REV_LONG}" STREQUAL "" )
        message ( SEND_ERROR "CMake variable MCU_REV_LONG is not set. It should be something like 'f042x6'.\n" )
	message ( SEND_ERROR
		"If you are using arena:")
	message ( SEND_ERROR
		"Check your arena board files. The used arena board is ${ARENA_BOARD}.")
	message ( FATAL_ERROR
                "The used board file is '${ARENA_BOARD_FILE}'."
		)
endif()

string( SUBSTRING "${MCU_REV_LONG}" 0 2 MCU_REV )
string( SUBSTRING "${MCU_REV_LONG}" 0 4 MCU_REV_MID )
set ( MCU_REV_MASK "${MCU_REV_MID}xx" )

# Uppercase variants of variables
string( TOUPPER "${MCU_REV_LONG}" MCU_REV_LONG_UC )
string( TOUPPER "${MCU_REV_MID}" MCU_REV_MID_UC )
string( TOUPPER "${MCU_REV}" MCU_REV_UC )
string( REPLACE "X" "x" MCU_REV_LONG_UC "${MCU_REV_LONG_UC}")
set ( MCU_REV_MASK_UC "${MCU_REV_MID_UC}xx" )

if ( "${MCU_REV}" STREQUAL "" )
        message ( FATAL_ERROR
                "Coud not extract MCU_REV from '${MCU_REV_LONG}'."
                )
endif()


set( LIST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/stm32${MCU_REV}_hal.list )

if ( NOT EXISTS "${LIST_FILE}" )
   message( FATAL_ERROR "List file does not exist for MCU '${MCU_REV}': ${LIST_FILE}" )
endif( )

# Get filenames for C-Files from list-file in data directory; make it a proper list
file( READ ${LIST_FILE} libHALWrapper_SOURCES )
string( STRIP "${libHALWrapper_SOURCES}" libHALWrapper_SOURCES )
string( REPLACE "\n" ";" libHALWrapper_SOURCES ${libHALWrapper_SOURCES} )
list( TRANSFORM libHALWrapper_SOURCES PREPEND ${B}/src/${MCU_REV}/ )

set(
   libHALWrapper_SOURCES
      ${libHALWrapper_SOURCES}
      ${B}/src/${MCU_REV}/startup_stm32${MCU_REV_LONG}.s
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
      ${B}/include/${MCU_REV}/stm/stm32${MCU_REV_LONG}.h
      ${B}/include/${MCU_REV}/stm/core_cm0.h
      ${B}/include/${MCU_REV}/stm/core_cm1.h
      ${B}/include/${MCU_REV}/stm/core_cm3.h
      ${B}/include/${MCU_REV}/stm/core_cm4.h
      ${B}/include/${MCU_REV}/stm/cmsis_version.h
      ${B}/include/${MCU_REV}/stm/cmsis_compiler.h
      ${B}/include/${MCU_REV}/stm/cmsis_gcc.h
      ${B}/include/${MCU_REV}/stm/mpu_armv7.h
      ${B}/include/${MCU_REV}/stm/system_stm32${MCU_REV}xx.h
		# ${B}include/${MCU_REV}/stm/Legacy/stm32_hal_legacy.h
)


set (
   libHALWrapper_DOCS
      ${B}/doc/LICENSE.md
)


#--- --------------------------------------------------------------------------

set( MCU_DEF_LONG STM32${MCU_REV_LONG} )
string( TOUPPER "${MCU_DEF_LONG}" MCU_DEF_LONG )
string( REPLACE "X" "x" MCU_DEF_LONG "${MCU_DEF_LONG}" )

set( MCU_DEF STM32${MCU_REV} )
string( TOUPPER "${MCU_DEF}" MCU_DEF )

# message( FATAL_ERROR "### MCU_DEF: ${MCU_DEF}" )

file(
   GLOB
   libHALWrapper_SOURCES_SUPPLEMENTARY
      src/stm32/*.c*
)

set( libHALWrapper_HEADERS_SUPPLEMENTARY
)

find_program(BASH bash HINTS /bin)

add_custom_command(OUTPUT ${libHALWrapper_SOURCES} ${libHALWrapper_HEADERS} ${libHALWrapper_DOCS}
                   COMMAND
                            ${CMAKE_COMMAND} -E env ${BASH} -c "${CMAKE_CURRENT_SOURCE_DIR}/scripts/obtain_github.sh ${MCU_REV} &> obtain_${MCU_REV}.log"
                   COMMENT "Obtaining HAL sources"
                   VERBATIM
                   WORKING_DIRECTORY ${B}
)

add_library( HALWrapper-${MCU_REV} STATIC
	${libHALWrapper_SOURCES}
	${libHALWrapper_SOURCES_SUPPLEMENTARY}
	${libHALWrapper_HEADERS}
	${libHALWrapper_HEADERS_SUPPLEMENTARY}
	${libHALWrapper_DOCS}
)

target_compile_definitions(
    HALWrapper-${MCU_REV}
        PUBLIC
            -DSTM32${MCU_REV_UC}=1
            -DSTM32${MCU_REV_MID_UC}=1
            -DSTM32${MCU_REV_LONG_UC}=1
            -DSTM32${MCU_REV_MASK_UC}=1
)

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

target_compile_definitions(
   HALWrapper-${MCU_REV}
   PUBLIC
      -D${MCU_DEF}=1
      -D${MCU_DEF_LONG}=1
)

#target_compile_options(
#   HALWrapper-${MCU_REV}
#   PRIVATE
#      $<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>
#)

install(TARGETS HALWrapper-${MCU_REV}
		  RUNTIME DESTINATION lib
		  ARCHIVE DESTINATION lib
)

install ( FILES ${libHALWrapper_HEADERS}
         DESTINATION include/stm
)

install ( DIRECTORY include/HALWrapper
         DESTINATION include
)

install ( FILES ${B}/doc/LICENSE.md
         DESTINATION share/doc/libHALWrapper
)

install ( FILES ${B}/doc/LICENSE_HAL.md
         DESTINATION share/doc/libHALWrapper
)

install ( DIRECTORY ${B}/doc/HAL
         DESTINATION share/doc/libHALWrapper
)

install ( DIRECTORY ${B}/doc/CMSIS
         DESTINATION share/doc/libHALWrapper
)


if( BUILD_EXAMPLE )

add_subdirectory( example )

endif( BUILD_EXAMPLE )


#------------------------------------------------------------------------------
