/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32g4xx.c
 * @brief      Default system clock config for STM32G4 devices
 *
 * Check stm32g4xx_hal_rcc.c from HAL for OSC values.
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
//#include <HALWrapper/stm32_hal.h>         // HAL_GetREVID


/*--- Implementation -------------------------------------------------------*/

#if defined STM32G441xB
   #define USE_HSE      1
#endif

/**
 * @brief  System Clock Configuration
 * @retval None
 *
 * USB needs either QPLL 48Mhz or HSI48 48Mhz.
 *
 * * HSI = 16000000 Hz
 */
__attribute__ ((weak))
void SystemClock_Config_g4( void )
{
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
   RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

   HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

   #ifdef USE_HSE
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSI;
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
   #else
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_LSI;
   RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
   #endif
   RCC_OscInitStruct.LSIState = RCC_LSI_ON;
   RCC_OscInitStruct.HSI48State = RCC_HSI48_OFF;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
   RCC_OscInitStruct.PLL.PLLN = 12;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
   RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      Error_Handler();
   }

   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
   {
      Error_Handler();
   }

   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USB|RCC_PERIPHCLK_FDCAN|RCC_PERIPHCLK_RTC;
   PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
   PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
   PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
   PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
   {
      Error_Handler();
   }

   HAL_RCC_EnableCSS();
}


/*--- Fin ------------------------------------------------------------------*/
