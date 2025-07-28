#------------------------------------------------------------------------------
#
# \brief    CMake package MCURev
#
#           This package will set variables by input variable MCU:
#              MCU (input, e.g. stm32f303x8)
#              MCU_UC (e.g. STM32F303x8)
#              MCU_REV (e.g. f3)
#              MCU_REV_UC (e.g. F3)
#              MCU_REV_LONG (e.g. f303x8)
#              MCU_REV_MID (e.g. f303)
#              MCU_REV_MASK (e.g. f303xx)
#              MCU_REV_MASK_UC (e.g. F303xx)
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


cmake_minimum_required( VERSION 3.11 )


if( NOT DEFINED MCU )
   message( FATAL_ERROR 
      "Variable MCU is not set. This is required."
      " Example: -DMCU=stm32f303x8" 
   )
endif( NOT DEFINED MCU )

# Filter out the MCU package. E.g. convert stm32f303k8 to stm32f303x8
string( SUBSTRING "${MCU}" 0 9 MCU1 )
string( SUBSTRING "${MCU}" 10 1 MCU2 )
set ( MCU "${MCU1}x${MCU2}" )

string( SUBSTRING "${MCU}" 5 -1 MCU_REV_LONG )
string( SUBSTRING "${MCU}" 5 2 MCU_REV )
string( SUBSTRING "${MCU}" 5 4 MCU_REV_MID )
set ( MCU_REV_MASK "${MCU_REV_MID}xx" )

# Uppercase variants of variables
string( TOUPPER "${MCU}" MCU_UC )
string( TOUPPER "${MCU_REV_LONG}" MCU_REV_LONG_UC )
string( TOUPPER "${MCU_REV_MID}" MCU_REV_MID_UC )
string( TOUPPER "${MCU_REV}" MCU_REV_UC )
string( REPLACE "X" "x" MCU_UC "${MCU_UC}")
set ( MCU_REV_MASK_UC "${MCU_REV_MID_UC}xx" )

# An bug? There is no "stm32l152x8.h" but a "stm32l152xb.h". Define for this
# as to be set
if ( MCU_UC STREQUAL "STM32L152x8" )
   set( MCU_ALIAS_UC "STM32L152xB" )
endif()

if ( MCU_UC STREQUAL "STM32F042x4" )
   set( MCU_ALIAS_UC "STM32F042x6" )
endif()

if( MCU_ALIAS_UC )
   string( TOLOWER "${MCU_ALIAS_UC}" MCU_ALIAS )
endif( MCU_ALIAS_UC )

if ( "${MCU_REV}" STREQUAL "" )
        message ( FATAL_ERROR
                "Coud not extract MCU_REV from MCU '${MCU}'."
                )
endif()


#------------------------------------------------------------------------------
