#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for the example in libHALWrapper
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( hello_world ASM C CXX )

include_directories( include )

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/syscallsUart.cpp
    src/info.cpp
)

target_link_libraries(
   ${PROJECT_NAME}
   HALWrapper::HALWrapper
)

if( NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/scripts/${MCU}.ld" )
   message( FATAL_ERROR "There is no linker script for MCU '${MCU}'."
      "The MCU is just not supported by the libHALWrapper example." )
endif()

# Use the linkerscripts needed for the board for the example
target_link_options(
   ${PROJECT_NAME}
   PRIVATE
      -Wl,-L${CMAKE_CURRENT_SOURCE_DIR}/scripts
      -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/scripts/${MCU}.ld
)


#------------------------------------------------------------------------------
