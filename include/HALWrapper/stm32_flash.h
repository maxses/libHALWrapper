#ifndef HALWRAPPER_STM32_FLASH_H
#define HALWRAPPER_STM32_FLASH_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_flash.h
 * @brief      Wrapper to include MCU specific header file for FLASH memory
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#pragma GCC diagnostic push
#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wvolatile"
#endif


#if defined STM32F0

   #include <stm/stm32f0xx_hal_flash.h>

#elif defined STM32F1

   #include <stm/stm32f1xx_hal_flash.h>

#elif defined STM32F3

   #include <stm/stm32f3xx_hal_flash.h>
   #include <stm/stm32f3xx_hal_flash_ex.h>

#elif defined STM32F4

   #include <stm/stm32f4xx_hal_flash.h>

#elif defined STM32L1

   #include <stm/stm32l1xx_hal_flash.h>

   #ifdef __cplusplus
   extern "C" {
   #endif

      void    FLASH_PageErase(uint32_t PageAddress);

   #ifdef __cplusplus
   }
   #endif

#elif defined STM32L0

   #include <stm/stm32l0xx_hal_flash.h>
   #ifdef __cplusplus
   extern "C" {
   #endif

      void    FLASH_PageErase(uint32_t PageAddress);

   #ifdef __cplusplus
   }
   #endif

#elif defined STM32L4

   #include <stm/stm32l4xx_hal_flash.h>

#elif defined STM32G0

   #include <stm/stm32g0xx_hal_flash.h>

#elif defined STM32G4

   #include <stm/stm32g4xx_hal_flash.h>

#elif defined STM32G0

   #include <stm/stm32g0xx_hal_flash.h>

#else

   #error "Unknown MCU"

#endif


#pragma GCC diagnostic pop


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_FLASH_H
