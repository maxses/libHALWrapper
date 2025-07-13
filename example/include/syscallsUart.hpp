/**---------------------------------------------------------------------------
 *
 * @file   stdioUart.hpp
 * @brief  Sloppy implementation of syscall functions
 *
 * Just let examples for libHALWrapper work. "printf" should print on UART.
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_uart.h>     // UART_HandleTypeDef


/*--- Declarations -------------------------------------------------------*/


void setStdioUart( UART_HandleTypeDef* uartHandle );


/*--- Fin ------------------------------------------------------------------*/
