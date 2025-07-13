/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32l4xx.c
 * @brief      Default system clock config for STM32L4 devices
 *
 * Check stm32l4xx_hal_rcc.c from HAL for OSC values.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_rcc.h>
#include <HALWrapper/stm32_pwr.h>
#include <HALWrapper/stm32_flash.h>
#include <HALWrapper/stm32_sup.h>         // Error_Handler()


/*--- Implementation -------------------------------------------------------*/


/**
 * @brief  System Clock Configuration
 *
 * * System Clock source = MSI
 * * SYSCLK(Hz)          = 24000000 Hz
 *
 * @param  None
 * @retval None
 */
__attribute__ ((weak))
void SystemClock_Config_l4( void )
{
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};

   __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_3);
   HAL_RCC_DeInit();

   /* After reset the device runs on MSI with 4Mhz.
      Update MSI to 24Mhz (RCC_MSIRANGE_9)
   */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
   RCC_OscInitStruct.MSIState = RCC_MSI_ON;
   RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_9;
   RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;
   if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      Error_Handler();
   }

   /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
      clocks dividers */
   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
   if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, __HAL_FLASH_GET_LATENCY()) != HAL_OK)
   {
      Error_Handler();
   }
}


/*--- Fin ------------------------------------------------------------------*/
