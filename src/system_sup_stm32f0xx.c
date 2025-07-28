/**---------------------------------------------------------------------------
 *
 * @file       system_sup_stm32f0xx.c
 * @brief      Default system clock config for STM32F0 devices
 *
 * Check stm32f0xx_hal_rcc.c from HAL for OSC values.
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


/*--- Implementation -------------------------------------------------------*/


// Use the 48Mhz internal oscilator per default for USB
#if defined STM32F072xB
   #define USE_HSI48          1
#endif

#ifdef USE_LSE
   #define OPTIONAL_LSE    RCC_OSCILLATORTYPE_LSE
#else
   #define OPTIONAL_LSE    0
#endif


/**
 * @brief  System Clock Configuration
 *
 * The STM32F0 has an special HSI48 with 48Mhz. It is more precise as
 * the regular HSI. The higher speed is needed for using USB. HSI48 will be
 * used when "USE_HSI48" is defined. It is automatically defined for STM32F072
 * for compatibility reasons.
 *
 * When USE_HSI48 is set:
 * * System Clock source      = PLL (HSI48)
 * * SYSCLK                   = 48000000 Hz ( PLL[HSI48] )
 *
 * When USE_HSI48 is not set:
 * * System Clock source      = PLL (HSI)
 * * HSI Frequency            = 8000000 Hz
 * * SYSCLK                   = 48000000 Hz ( HSI * 6 )
 */
__attribute__ ((weak))
void SystemClock_Config_f0( void )
{
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_OscInitTypeDef RCC_OscInitStruct;

   #ifdef USE_HSI48
      /* Select HSI48 Oscillator as PLL source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | OPTIONAL_LSE;
      RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
   #else
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | OPTIONAL_LSE;
      RCC_OscInitStruct.HSIState = RCC_HSI_ON;
      RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   #endif

   #ifdef USE_LSE
      RCC_OscInitStruct.LSEState = RCC_LSE_ON;
   #endif

   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

   #ifdef USE_HSI48
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
      RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
      RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
      RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   #else
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
      RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
      RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
   #endif
   if ( HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK )
   {
      Error_Handler();
   }

   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   if ( HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK )
   {
      Error_Handler();
   }

   #if defined USE_RTC_ON_LSE
      enableRtcOnLse();
   #endif
      
   return;
}


/*--- Fin ------------------------------------------------------------------*/
