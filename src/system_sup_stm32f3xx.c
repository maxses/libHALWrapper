/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32f3xx.c
 * @brief      Default system clock config for STM32F3 devices
 *
 * Check stm32f3xx_hal_rcc.c from HAL for OSC values.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_rcc.h>
#include <HALWrapper/stm32_flash.h>       // FLASH_LATENCY_1
#include <HALWrapper/stm32_sup.h>


#if defined USE_HSE
   #error USE_HSE not implemented for this MCU
#endif


/*--- Implementation -------------------------------------------------------*/


/**
 * @brief  System Clock Configuration
 *
 * * System Clock source = PLL
 * * HSI                 = 8000000 Hz
 * * SYSCLK              = 32000000 Hz ( HSI * 4 )
 *
 * @param  None
 * @retval None
 */
__attribute__ ((weak))
void SystemClock_Config_f3( void )
{
   RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
   RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };

   /* The HSI Oscillator already ON after system reset.*/
   #if ! defined USE_LSE
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   #else
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
   RCC_OscInitStruct.LSEState = RCC_LSE_ON;
   // No calibration for LSE
   #endif
   RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
   {
      Error_Handler();
   }

   /* Select PLL as system clock source and configure the HCLK, PCLK1
   clocks dividers */
   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
   {
      Error_Handler();
   }

   #if defined USE_RTC_ON_LSE
      enableRtcOnLse();
   #endif
}


/*--- Fin ------------------------------------------------------------------*/
