/**---------------------------------------------------------------------------
 *
 * @file   example_config_stm32f072xb.h
 * @brief  Specify used periphery for example
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


#if ! defined STM32F072xB
   #error "Wrong file is included. Just include 'config.h' instead of this file."
#endif

#define GPIO_PERIPHERY     GPIOC
#define GPIO_PIN           GPIO_PIN_7
#define LED_LOOPS          (10000000/16)


/*--- Fin ------------------------------------------------------------------*/
