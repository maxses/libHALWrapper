#ifndef HALWRAPPER_STM32_RCC_H
#define HALWRAPPER_STM32_RCC_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_rcc.h
 * @brief      Wrapper to include MCU specific header file for RCC
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

   #include <stm/stm32f0xx_hal_rcc.h>
   #include <stm/stm32f0xx_ll_rcc.h>
   // #include <stm/stm32f0xx_hal_rcc_ex.h>

#elif defined STM32F1

   #include <stm/stm32f1xx_hal_rcc.h>
   #include <stm/stm32f1xx_hal_rcc_ex.h>

#elif defined STM32F3

   #include <stm/stm32f3xx_hal_rcc.h>
   #include <stm/stm32f3xx_ll_rcc.h>

#elif defined STM32F4

   #include <stm/stm32f4xx_hal_rcc.h>

#elif defined STM32L1

   #include <stm/stm32l1xx_hal_rcc.h>

#elif defined STM32L0

   #include <stm/stm32l0xx_hal_rcc.h>

#elif defined STM32L4

   #include <stm/stm32l4xx_hal_rcc.h>
   #include <stm/stm32l4xx_ll_rcc.h>

#elif defined STM32G0

   #include <stm/stm32g0xx_hal_rcc.h>
   #include <stm/stm32g0xx_ll_rcc.h>
   #if ! defined(__HAL_RCC_ADC1_CLK_ENABLE)
      #define __HAL_RCC_ADC1_CLK_ENABLE              __HAL_RCC_ADC_CLK_ENABLE
   #else
      #error "RCC Quirk for ADC1 RCC macro not necessary any longer"
   #endif

#elif defined STM32G4

   #include <stm/stm32g4xx_hal_rcc.h>
   // Arena will struggle to get the right macro; no instance number in stm32g4
   // but in non-fdcan.
   #define __HAL_RCC_CAN1_CLK_ENABLE              __HAL_RCC_FDCAN_CLK_ENABLE

#else

   #error "unknown MCU"

#endif


#pragma GCC diagnostic pop


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_RCC_H
