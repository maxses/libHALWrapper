#ifndef HALWRAPPER_STM32_CORE_H
#define HALWRAPPER_STM32_CORE_H
/**---------------------------------------------------------------------------
 *
 * @file       core.h
 * @brief      Wrapper to include MCU specific CMSIS core file
 *
 * @date       20150111
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#if defined STM32L100xC

#elif defined STM32F103xB

#elif defined STM32F303x8

#elif defined STM32F334x8

#elif defined STM32F407xx
   #include <stm/core_cm4.h>
#elif defined STM32F072xB
   #include <stm/core_cm0.h>
#endif


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_CORE_H
