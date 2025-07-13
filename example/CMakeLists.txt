#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for the example in libHALWrapper
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( hello_world ASM C CXX )


add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(
   ${PROJECT_NAME}
   HALWrapper-${MCU_REV}
)

# Use the linkerscripts needed for the board for the example
target_link_options(
   ${PROJECT_NAME}
   PRIVATE
      -Wl,--nostdlib -Wl,-L${CMAKE_CURRENT_SOURCE_DIR}/scripts
      -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/scripts/stm32f303x8.ld
      -Wl,--build-id=none -Wl,--gc-sections
)


#------------------------------------------------------------------------------
