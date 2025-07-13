/**---------------------------------------------------------------------------
 *
 * @file   main.cpp
 * @brief  Example for libHALWrapper usage on STM32 evaluation boards
 *
 * Trivial LED blinking. The NucleoF303k8 also prints a string via UART
 *
 * Verified Boards:
 *    * STM32F072B-DISCO (STM32F072RB)
 *    * NUCLEO-F303K8 (STM32F303K8T6)
 *    * STM32F4DISCOVERY (STM32F407VG)
 *    * STM32G031 Nucleo-32 (STM32G031K8)
 *    * Miniminutnik (STM32L031F6)
 *    * CANDis (STM32G443KB)
 *    * Fridgetemp (STM32L152C8)
 *    * CANIO (STM32F042F6)
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <HALWrapper/stm32_uart.h>
#include <HALWrapper/stm32_rcc.h>      // __HAL_RCC_XXX_CLK_ENABLE
#include <HALWrapper/stm32_gpio.h>
#include <HALWrapper/stm32_sup.h>      // SystemClock_Config
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  // strlen

#include <syscallsUart.hpp>            // setStdioUart();

#if ! ( defined STM32F0 || defined STM32F3 || defined STM32F4 || \
        defined STM32G0 || defined STM32G4 || defined STM32L0 || \
        defined STM32L1 )
    #error Expected MCU defines are not set. This example will only compile via the provided build script.
#endif

#include <config.h>
#include <info.hpp>


/*--- Implementation -------------------------------------------------------*/


GPIO_InitTypeDef gpioInit
{
   .Pin{ GPIO_PIN },
   .Mode { GPIO_MODE_OUTPUT_PP },
   .Pull { GPIO_NOPULL },
   .Speed { GPIO_SPEED_LOW },
   .Alternate { 0 },
};

// Is example using UART at all? Not available for all boards.
#if defined UART_PINS

GPIO_InitTypeDef gpioUartInit
{
   .Pin{ UART_PINS },
   .Mode { GPIO_MODE_AF_PP },
   .Pull { GPIO_PULLUP },
   .Speed { GPIO_SPEED_FREQ_HIGH },
   .Alternate { UART_PINS_AF },
};

UART_HandleTypeDef uartHandle
{
   .Instance { USART2 },
   .Init
   {
      .BaudRate { 115200 },
      .WordLength { UART_WORDLENGTH_8B },
      .StopBits = UART_STOPBITS_1,
      .Parity = UART_PARITY_NONE,
      .Mode = UART_MODE_TX_RX,
      .HwFlowCtl = UART_HWCONTROL_NONE,
      .OverSampling = UART_OVERSAMPLING_16,

      #if defined UART_ONE_BIT_SAMPLE_ENABLE
      .OneBitSampling =  UART_ONE_BIT_SAMPLE_ENABLE,
      #endif
   },
   #if defined UART_ADVFEATURE_NO_INIT
   .AdvancedInit
   {
      .AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
   }
   #endif // ? UART_ADVFEATURE_NO_INIT
};

int uartWrite(int __fd, const void *__buf, size_t __nbyte)
{
   HAL_UART_Transmit( &uartHandle, (const uint8_t*)__buf, __nbyte, 100000 );
   HAL_UART_Transmit( &uartHandle, (const uint8_t*)"\r", 1, 100000 );
   return(0);
}

int uartPutc( char ch, FILE* f )
{
   HAL_UART_Transmit( &uartHandle, (const uint8_t*)&ch, 1, 100000 );
   if( ch == '\n' )
   {
      ch='\r';
      HAL_UART_Transmit( &uartHandle, (const uint8_t*)&ch, 1, 100000 );
   }
   return(0);
}


#endif // ? UART_PINS


[[noreturn]]
int main(int argc, const char* argv[])
{
   // Provided by libHALWrapper; default clock configuration
   SystemClock_Config();
   SystemCoreClockUpdate();
   
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   #if defined(__HAL_RCC_GPIOD_CLK_ENABLE)
   __HAL_RCC_GPIOD_CLK_ENABLE();
   #endif
   __HAL_RCC_USART2_CLK_ENABLE();
   
   HAL_GPIO_Init( GPIO_PERIPHERY, &gpioInit );
   
   #if defined UART_PINS
   
      HAL_GPIO_Init( UART_PIN_PERIPHERY, &gpioUartInit );
   
   #endif // ? UART_PINS
   
   HAL_GPIO_WritePin(  GPIO_PERIPHERY, GPIO_PIN, GPIO_PIN_SET );
   
   #if defined UART_PINS
      
      if ( HAL_UART_Init( &uartHandle ) != HAL_OK)
      {
         Error_Handler();
      }
   
      HAL_UART_Transmit( &uartHandle, (const uint8_t*)"Hello World!\n\r", 14, 100000 );
      setStdioUart( &uartHandle );
      
   #endif // ? UART_PINS
      
   info();

   // Let the LED blink
   while(1)
   {
      HAL_GPIO_WritePin(  GPIO_PERIPHERY, GPIO_PIN, GPIO_PIN_SET );
      for(int i1=0; i1<LED_LOOPS; i1++)
      {
         asm( "nop; \n" );
      }
      
      HAL_GPIO_WritePin(  GPIO_PERIPHERY, GPIO_PIN, GPIO_PIN_RESET );
      for(int i1=0; i1<LED_LOOPS; i1++)
      {
         asm( "nop; \n" );
      }
   }
   
   // Its a noreturn, so return statement must be missing
};


/*--- Fin ------------------------------------------------------------------*/
