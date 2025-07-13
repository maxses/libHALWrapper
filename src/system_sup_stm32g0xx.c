/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32g0xx.c
 * @brief      Default system clock config for STM32G0 devices
 *
 * Check stm32g0xx_hal_rcc.c from HAL for OSC values.
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
#include <HALWrapper/stm32_hal.h>         // uwTickPrio


/*--- Implementation -------------------------------------------------------*/


/**
 * @brief  System Clock Configuration
 *
 * * System Clock source = PLL (HSI)
 * * HSI                 = 8000000 Hz
 * * SYSCLK              = 32000000 Hz (HSI / 1_M * 8_N / 2_P)
 *
 * @param  None
 * @retval None
 */
__attribute__ ((weak))
void SystemClock_Config_g0()
{
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

   /** Configure the main internal regulator output voltage
    */
   HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

   /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
   RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
   RCC_OscInitStruct.PLL.PLLN = 8;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
   #if defined RCC_PLLQ_SUPPORT
   RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV5;
   #endif
   RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

   // HAL_InitTick() is called, requiering an valid uwTickPrio
   uwTickPrio=0;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      Error_Handler();
   }

   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
   {
      Error_Handler();
   }
}


/*--- Fin ------------------------------------------------------------------*/
