#------------------------------------------------------------------------------
#
# \brief    CMake package MCUFlags
#
#           This package will set compiler flags for controller defined by MCU_REV.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


cmake_minimum_required( VERSION 3.11 )

if( NOT DEFINED MCU_UC )
   find_package( MCURev )
endif()

if ( NOT DEFINED MCU_REV )
   message( FATAL_ERROR "Variable MCU_REV is not set. This is required. "
      "Example: -DMCU_REV=f3. CMake package 'MCURev' can be used to set this variable." )
endif ( NOT DEFINED MCU_REV )

# Possible generic options, but it not to this package to decide:
#   -fno-exceptions -ffunction-sections -fdata-sections

if( MCU_REV STREQUAL "f0" )
   set( MCU_FLAGS "-march=armv6-m -mcpu=cortex-m0 -mfloat-abi=soft -mthumb" )
elseif( MCU_REV STREQUAL "f3" )
   set( MCU_FLAGS "-march=armv7e-m -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb" )
elseif( MCU_REV STREQUAL "f4" )
   set( MCU_FLAGS "-march=armv7e-m -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb" )
elseif( MCU_REV STREQUAL "g0" )
   set( MCU_FLAGS "-mcpu=cortex-m0plus -mfloat-abi=soft -mthumb" )
elseif( MCU_REV STREQUAL "g4" )
   set( MCU_FLAGS "-march=armv7e-m -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb" )
elseif( MCU_REV STREQUAL "l0" )
   set( MCU_FLAGS "-march=armv6-m -mcpu=cortex-m0 -mfloat-abi=soft -mthumb" )
elseif( MCU_REV STREQUAL "l1" )
   set( MCU_FLAGS "-march=armv7-m -mcpu=cortex-m3 -mfloat-abi=soft -mthumb" )
else()
   message( FATAL_ERROR "MCU_REV '${MCU_REV}' not known." )
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS}" )
# set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections" )

add_compile_definitions(
   # Have an define like STM32F303x6
   ${MCU_UC}
)


#------------------------------------------------------------------------------
