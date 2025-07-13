#ifndef HALWRAPPER_STM32_TSC_H
#define HALWRAPPER_STM32_TSC_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_tsc.h
 * @brief      Wrapper to include MCU specific header file for TSC
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#if defined STM32F0

   #include <stm/stm32f0xx_hal_tsc.h>

#elif defined STM32F1

   //#include <stm/stm32f1xx_hal_tsc.h>

#elif defined STM32F3

   #include <stm/stm32f3xx_hal_tsc.h>

#elif defined STM32F4

   //#include <stm/stm32f4xx_hal_tsc.h>

#elif defined STM32L1

   // stm32l1 has no tsc
   // #include <stm/stm32l1xx_hal_tsc.h>

#elif defined STM32L0

   #include <stm/stm32l0xx_hal_tsc.h>

#elif defined STM32L4

   #include <stm/stm32l4xx_hal_tsc.h>

#elif defined STM32G0

   // #include <stm/stm32g0xx_hal_tsc.h>
    #error "MCU does not support TSC"

#elif defined STM32G4

   // #include <stm/stm32g4xx_hal_tsc.h>
   #error "MCU does not support TSC"

#else

   #error "Unknown MCU"

#endif


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_TSC_H
