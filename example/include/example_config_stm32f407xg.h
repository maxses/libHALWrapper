/**---------------------------------------------------------------------------
 *
 * @file   example_config_stm32f407xG.h
 * @brief  Specify used periphery for example
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


#if ! defined STM32F407xG
   #error "Wrong file is included. Just include 'config.h' instead of this file."
#endif

#define GPIO_PERIPHERY     GPIOD
#define GPIO_PIN           GPIO_PIN_15
#define LED_LOOPS          (10000000/16)


/*--- Fin ------------------------------------------------------------------*/
