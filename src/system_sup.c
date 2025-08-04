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
#include <stdbool.h>

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

#if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || \
   defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || \
   defined(__ARM_ARCH_6ZK__) || defined( __ARM_ARCH_6M__ )


bool __atomic_compare_exchange_4 (volatile void *ptr, void *expected, unsigned int desired, \
                                 bool weak, int success_memorder, int failure_memorder) \
{
   (void) weak;
   (void) success_memorder;
   (void) failure_memorder;
   __disable_irq();
   int cur = *(volatile int *)ptr;
   if (cur != *(int *)expected)
   {
      *(int *)expected = cur;
      __enable_irq();
      return false;
   }
   *(volatile int *)ptr = desired;
   __enable_irq();
   return true;
}


#endif


/*--- Fin ------------------------------------------------------------------*/
