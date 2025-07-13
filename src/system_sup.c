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


/*--- Fin ------------------------------------------------------------------*/
