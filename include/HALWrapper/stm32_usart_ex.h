#ifndef HALWRAPPER_STM32_USART_EX_H
#define HALWRAPPER_STM32_USART_EX_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_usart_ex.h
 * @brief      Wrapper to include MCU specific header file for USART extended
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#if defined STM32F0

   #include <stm/stm32f0xx_hal_usart_ex.h>

#elif defined STM32F1

   // Does not exist. USART_WORDLENGTH is defined in stm32f4xx_hal_usart.h

#elif defined STM32F3

   #include <stm/stm32f3xx_hal_usart_ex.h>

#elif defined STM32F4

   // Does not exist. USART_WORDLENGTH is defined in stm32f4xx_hal_usart.h

#elif defined STM32L1

   // Does not exist. USART_WORDLENGTH is defined in stm32l1xx_hal_usart.h

#elif defined STM32G4

   #include <stm/stm32g4xx_hal_usart_ex.h>

#endif


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_USART_H
