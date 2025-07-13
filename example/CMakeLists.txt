#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for the example in libHALWrapper
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( hello_world ASM C CXX )

# Reduce size; add_compile_options() does not apply to parent directories
set( ADD_MCU_FLAGS "-fno-exceptions -ffunction-sections -fdata-sections" )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ADD_MCU_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADD_MCU_FLAGS}" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" PARENT_SCOPE )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE )

include_directories( include )

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(
   ${PROJECT_NAME}
   HALWrapper-${MCU_REV}
   ${LIBS}
)

if( NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/scripts/${MCU}.ld" )
   message( FATAL_ERROR "There is no linker script for MCU '${MCU}'."
      "The MCU is just not supported by the libHALWrapper example." )
endif()

# Use the linkerscripts needed for the board for the example
target_link_options(
   ${PROJECT_NAME}
   PRIVATE
      -Wl,--nostdlib
      -Wl,-L${CMAKE_CURRENT_SOURCE_DIR}/scripts
      -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/scripts/${MCU}.ld
      -Wl,--build-id=none -Wl,--gc-sections
)


#------------------------------------------------------------------------------
