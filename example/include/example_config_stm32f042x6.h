/**---------------------------------------------------------------------------
 *
 * @file   example_config_stm32f042x6.h
 * @brief  Specify used periphery for example
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


#if ! defined STM32F042x6
   #error "Wrong file is included. Just include 'config.h' instead of this file."
#endif

#define GPIO_PERIPHERY     GPIOA
#define GPIO_PIN           GPIO_PIN_0
#define LED_LOOPS          (10000000/16)
#define UART_PIN_PERIPHERY GPIOA
#define UART_PINS          ( GPIO_PIN_2 | GPIO_PIN_3 )
#define UART_PINS_AF       GPIO_AF1_USART2


/*--- Fin ------------------------------------------------------------------*/
