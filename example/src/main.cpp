//-----------------------------------------------------------------------------
///
/// \file   main.cpp
/// \brief  Example for libHALWrapper usage on STM32 evaluation boards
///
///         Trivial LED blinking. The NucleoF303k8 also prints a string via UART
///         Verified Boards:
///            * STM32F072B-DISCO (STM32F072RB)
///            * NUCLEO-F303K8 (STM32F303K8T6)
///            * STM32F4DISCOVERY (STM32F407VG)
/// 
/// \date   20250719
/// \author Maximilian Seesslen <development@seesslen.net>
///
//-----------------------------------------------------------------------------


//---Includes------------------------------------------------------------------


#include <HALWrapper/stm32_dma.h>
#include <HALWrapper/stm32_uart.h>
#include <HALWrapper/stm32_rcc.h>
#include <HALWrapper/stm32_gpio.h>
#include <HALWrapper/stm32_cortex.h>


#if ! ( defined STM32F0 || defined STM32F3 || defined STM32F4 )
    #error Expected MCU defines are not set. This example will only compile via the provided build script.
#endif

#if defined STM32F303x8
   #define GPIO_PERIPHERY  GPIOB
   #define GPIO_PIN        GPIO_PIN_3
   #define LED_LOOPS (10000000/16)
#elif defined STM32F072xB
   #define GPIO_PERIPHERY  GPIOC
   #define GPIO_PIN        GPIO_PIN_7
   #define LED_LOOPS (10000000/16)
#elif defined STM32F407xG
   #define GPIO_PERIPHERY  GPIOD
   #define GPIO_PIN        GPIO_PIN_15
   #define LED_LOOPS (10000000/16)
#else
   #error Expected MCU defines are not set. This example will only compile via the provided build script.
#endif


//---Implementation------------------------------------------------------------


__attribute__((noreturn)) void exception()
{
    while(1)
    {
    }
}

extern "C"
{
   // GCC may use memset() even if no libc is used.
   void * memset ( void * ptr, int value, size_t num )
   {
      for(int i1=0; i1++; i1<num)
      {
         ((char*)ptr)[i1]=value;
      }
      return(ptr);
   }
    
    // HAL expects this function to exist but no libc is used in this example.
    void __libc_init_array()
    {
      return;
    }
    
    void SystemClock_Config();
    
    void SysTick_Handler()
    {
       HAL_SYSTICK_IRQHandler();
       return;
    }
    
   // Needed for TCB
    void _exit(int code)
    {
       exception();
    }
}


GPIO_InitTypeDef gpioInit
{
   .Pin{ GPIO_PIN },
   .Mode { GPIO_MODE_OUTPUT_PP },
   .Pull { GPIO_NOPULL },
   .Speed { GPIO_SPEED_LOW },
   .Alternate { 0 },
};

#if defined STM32F303x8

GPIO_InitTypeDef gpioUartInit
{
   .Pin{ GPIO_PIN_2 | GPIO_PIN_15 },
   .Mode { GPIO_MODE_AF_PP },
   .Pull { GPIO_PULLUP },
   .Speed { GPIO_SPEED_FREQ_HIGH },
   .Alternate { GPIO_AF7_USART2 },
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
      .OneBitSampling =  UART_ONE_BIT_SAMPLE_ENABLE,
   },
   .AdvancedInit
   {
      .AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
   }
};

#endif

int main(int argc, const char* argv[])
{
   // Provided by libHALWrapper; default clock configuration
   SystemClock_Config();
   SystemCoreClockUpdate();
   
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_USART2_CLK_ENABLE();
   
   HAL_GPIO_Init( GPIO_PERIPHERY, &gpioInit );
   
   #if defined STM32F303x8
   
      HAL_GPIO_Init( GPIOA, &gpioUartInit );
   
   #endif // ? STM32F303x8
   
   HAL_GPIO_WritePin(  GPIO_PERIPHERY, GPIO_PIN, GPIO_PIN_SET );
   
   #if defined STM32F303x8
      
      if ( HAL_UART_Init( &uartHandle ) != HAL_OK)
      {
         exception();
      }
   
      HAL_UART_Transmit( &uartHandle, (const uint8_t*)"Hello World!\n\r", 14, 100000 );

   #endif // ? STM32F303x8

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
   
   return(0);
};


//---Fin-----------------------------------------------------------------------

