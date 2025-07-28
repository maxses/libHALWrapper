/**---------------------------------------------------------------------------
 *
 * @file       system_sup.c
 * @brief      Generic supplementary functions
 *
 * Just some default handlers.
 *
 * @date      20240821
 * @author    Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_sup.h>
#include <HALWrapper/stm32_cortex.h>   // HAL_SYSTICK_IRQHandler
#include <HALWrapper/stm32_rcc.h>


/*--- Implementation -------------------------------------------------------*/


void Error_Handler()
{
   while(1)
   {

   }
}


void SysTick_Handler()
{
   HAL_SYSTICK_IRQHandler();
   return;
}


void enableRtcOnLse()
{
   RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
   PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
   {
      Error_Handler();
   }
}


/*--- Fin ------------------------------------------------------------------*/
