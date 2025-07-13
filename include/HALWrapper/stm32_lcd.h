#ifndef HALWRAPPER_STM32_LCD_H
#define HALWRAPPER_STM32_LCD_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_lcd.h
 * @brief      Wrapper to include MCU specific header file for LCD
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#if defined STM32F0


#elif defined STM32F1

#elif defined STM32F3

#elif defined STM32F4

#elif defined STM32L1

   #include <stm/stm32l1xx_hal_lcd.h>

#elif defined STM32L0

#elif defined STM32L4

#elif defined STM32G4

#else

   #error "unknown MCU"

#endif


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_LCD_H
