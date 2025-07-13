/**---------------------------------------------------------------------------
 *
 * @file   example_config_stm32f303x8.h
 * @brief  Specify used periphery for example
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


#if ! defined STM32F303x8
   #error "Wrong file is included. Just include 'config.h' instead of this file."
#endif

#define GPIO_PERIPHERY     GPIOB
#define GPIO_PIN           GPIO_PIN_3
#define LED_LOOPS          (10000000/16)
#define UART_PIN_PERIPHERY GPIOA
#define UART_PINS          ( GPIO_PIN_2 | GPIO_PIN_15 )
#define UART_PINS_AF       GPIO_AF7_USART2


/*--- Fin ------------------------------------------------------------------*/
