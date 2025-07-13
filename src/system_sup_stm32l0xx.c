/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32l0xx.c
 * @brief      Default system clock config for STM32L0 devices
 *
 * Check stm32l0xx_hal_rcc.c from HAL for OSC values.
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
#include <HALWrapper/stm32_sup.h>         // Error_Handler()


/*--- Implementation -------------------------------------------------------*/


/**
 * @brief  System Clock Configuration
 *
 * * System Clock source = PLL (HSI)
 * * HSI                 = 16000000 Hz
 * * MSI                 =  2094000 Hz
 * * SYSCLK              = 32000000 Hz ( HSI * 6 / 3 )
 *
 * @retval None
 */
__attribute__ ((weak))
void SystemClock_Config_l0( void )
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  // After reset the device runs on MSI with 2,094Mhz
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState            = RCC_LSI_OFF;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLL_DIV3;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set Voltage scale1 as MCU will run at 32MHz */
  __PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}


/*--- Fin ------------------------------------------------------------------*/
