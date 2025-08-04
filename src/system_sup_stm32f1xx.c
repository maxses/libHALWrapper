/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32f3xx.c
 * @brief      Default system clock config for STM32F3 devices
 *
 * Check stm32f1xx_hal_rcc.c from HAL for OSC values.
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


/*--- Implementation -------------------------------------------------------*/


/**
  * @brief  System Clock Configuration
  *
  * * System Clock source    = PLL ( HSI / 2 )
  * * HSI                    = 8000000 Hz
  * * PLL                    = 4000000 Hz ( PLL / 2 )
  * * SYSCLK(Hz)             = 64000000 Hz ( PLL * 16 )
  *
  * @param  None
  * @retval None
  */
__attribute__ ((weak))
void SystemClock_Config_f1( void )
{
   RCC_ClkInitTypeDef clkinitstruct = {0};
   RCC_OscInitTypeDef oscinitstruct = {0};
   HAL_StatusTypeDef  halStatus;

   /* After reset the device runs on HSI */
   oscinitstruct.OscillatorType  = ( RCC_OSCILLATORTYPE_HSI
   #if defined USE_LSE
               | RCC_OSCILLATORTYPE_LSE );
   oscinitstruct.LSEState        = RCC_LSE_ON;
   #else
               );
   #endif
   oscinitstruct.HSIState        = RCC_HSI_ON;
   oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
   oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
   oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
   if ( HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK )
   {
      Error_Handler();
   }

   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
   clocks dividers */
   clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 );
   clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
   clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
   if ( HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2 ) != HAL_OK )
   {
      Error_Handler();
   }
}


/*--- Fin ------------------------------------------------------------------*/
