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
   __disable_irq();
   while(1)
   {

   }
}


// Have a plausible backtrace instead of default handler qhich could be any
// reason.
void HardFault_Handler()
{
   Error_Handler();
}


void SysTick_Handler()
{
   HAL_SYSTICK_IRQHandler();
   return;
}


uint32_t HAL_RCC_GetSysClockFreq_48Mhz()
{
   return( 48000000 );
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


bool __atomic_compare_exchange_1 (volatile void *ptr, void *expected, uint8_t desired, \
                                 bool weak, int success_memorder, int failure_memorder) \
{
   (void) weak;
   (void) success_memorder;
   (void) failure_memorder;
   __disable_irq();
   uint8_t cur = *(volatile uint8_t *)ptr;
   if (cur != *(int *)expected)
   {
      *(uint8_t *)expected = cur;
      __enable_irq();
      return false;
   }
   *(volatile uint8_t *)ptr = desired;
   __enable_irq();
   return true;
}


bool __atomic_compare_exchange_2 (volatile void *ptr, void *expected, uint16_t desired, \
                                 bool weak, int success_memorder, int failure_memorder) \
{
   (void) weak;
   (void) success_memorder;
   (void) failure_memorder;
   __disable_irq();
   uint16_t cur = *(volatile uint16_t *)ptr;
   if (cur != *(int *)expected)
   {
      *(uint16_t *)expected = cur;
      __enable_irq();
      return false;
   }
   *(volatile uint16_t *)ptr = desired;
   __enable_irq();
   return true;
}


#endif


/*--- Fin ------------------------------------------------------------------*/
