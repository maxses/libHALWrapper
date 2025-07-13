#ifndef HALWRAPPER_STM32_CORTEX_H
#define HALWRAPPER_STM32_CORTEX_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_cortex.h
 * @brief      Wrapper to include MCU specific header file for cortex
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#ifdef __cplusplus

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile"

#endif // ? __cplusplus

#if defined STM32F0

   #include <stm/stm32f0xx_hal_cortex.h>

#elif defined STM32F1

   #include <stm/stm32f1xx_hal_cortex.h>

#elif defined STM32F3

   #include <stm/stm32f3xx_hal_cortex.h>

#elif defined STM32F4

   #include <stm/stm32f4xx_hal_cortex.h>

#elif defined STM32L1

   #include <stm/stm32l1xx_hal_cortex.h>

#elif defined STM32L0

   #include <stm/stm32l0xx_hal_cortex.h>

#elif defined STM32L4

   #include <stm/stm32l4xx_hal_cortex.h>

#elif defined STM32G0

   #include <stm/stm32g0xx_hal_cortex.h>

#elif defined STM32G4

   #include <stm/stm32g4xx_hal_cortex.h>

#elif defined STM32G0

   #include <stm/stm32g0xx_hal_cortex.h>

#else

   #error "Unknown MCU"

#endif


#ifdef __cplusplus

#pragma GCC diagnostic pop

#endif // ? __cplusplus


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_CORTEX_H
