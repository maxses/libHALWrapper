#ifndef HALWRAPPER_STM32_SD_H
#define HALWRAPPER_STM32_SD_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_sd.h
 * @brief      Wrapper to include MCU specific header file for SD
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#if defined STM32F0

   //#include <stm/stm32f0xx_hal_sd.h>

#elif defined STM32F1

   #include <stm/stm32f1xx_hal_sd.h>

#elif defined STM32F3

   // No SD for F3

#elif defined STM32F4

   #include <stm/stm32f4xx_hal_sd.h>

#elif defined STM32L1

   #include <stm/stm32l1xx_hal_sd.h>

#elif defined STM32L0

   // No SD for L0

#elif defined STM32L4

   #include <stm/stm32l4xx_hal_sd.h>

#elif defined STM32G4

   // No SD for G4

#elif defined STM32G0

   // No SD for G0

#else

   #error "Unknown MCU"

#endif


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_SD_H
