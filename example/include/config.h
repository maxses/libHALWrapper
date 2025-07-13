/**---------------------------------------------------------------------------
 *
 * @file   config.h
 * @brief  Wrapper to include MCU specifig config file
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#if defined STM32F303x8
   #include <example_config_stm32f303x8.h>
#elif defined STM32F072xB
   #include <example_config_stm32f072xb.h>
#elif defined STM32F407xG
   #include <example_config_stm32f407xg.h>
#elif defined STM32G031x8
   #include <example_config_stm32g031x8.h>
#elif defined STM32L031x6
   #include <example_config_stm32l031x6.h>
#elif defined STM32G441xB
   #include <example_config_stm32g441xb.h>
#elif defined STM32L152x8
   #include <example_config_stm32l152x8.h>
#elif defined STM32F042x6
   #include <example_config_stm32f042x6.h>
#else
   #error Expected MCU defines are not set. This example will only compile \
          via the provided build script.
#endif


/*--- Fin ------------------------------------------------------------------*/
