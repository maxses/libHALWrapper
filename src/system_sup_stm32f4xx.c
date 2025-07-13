/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32f4xx.c
 * @brief      Default system clock config for STM32F4 devices
 *
 * Check stm32f4xx_hal_rcc.c from HAL for OSC values.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_rcc.h>
#include <HALWrapper/stm32_flash.h>       // FLASH_LATENCY_1
#include <HALWrapper/stm32_pwr.h>         // PWR_REGULATOR_VOLTAGE_SCALE1
#include <HALWrapper/stm32_sup.h>
#include <HALWrapper/stm32_hal.h>         // HAL_GetREVID


/*--- Implementation -------------------------------------------------------*/


/**
 * @brief  System Clock Configuration
 *
 * Either HSI or HSE can be used. When HSE should be used, "USE_HSE" has to be
 * defined.
 *
 * * System Clock source = PLL
 * * HSI                 = 8000000 Hz
 * * HSE                 = 8000000 Hz
 * * SYSCLK              = 168000000 Hz ( HSE / 8_M * 336_N / 2_P )
 * * HCLK                = 168000000 Hz ( SYSCLK )
 * * APB1                = 42000000 Hz ( HCLK / 4 )
 *
 * @param  None
 * @retval None
 */
__attribute__ ((weak))
void SystemClock_Config_f4(void)
{
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_OscInitTypeDef RCC_OscInitStruct;

   /* Enable Power Control clock */
   __HAL_RCC_PWR_CLK_ENABLE();

   /* The voltage scaling allows optimizing the power consumption when the device is
      clocked below the maximum system frequency, to update the voltage scaling value
      regarding system frequency refer to product datasheet.  */
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

   #ifdef USE_HSE
   /* Enable HSE Oscillator and activate PLL with HSE as source */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   #else
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSEState = RCC_HSI_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   #endif
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLM = 8;
   RCC_OscInitStruct.PLL.PLLN = 336;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ = 7;
   if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      Error_Handler();
   }

   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
   if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
   {
      Error_Handler();
   }

   /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
   if (HAL_GetREVID() == 0x1001)
   {
      /* Enable the Flash prefetch */
      __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
   }
}


/*--- Fin ------------------------------------------------------------------*/
