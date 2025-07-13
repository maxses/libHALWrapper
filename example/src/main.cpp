#include <HALWrapper/stm32_dma.h>
#include <HALWrapper/stm32_uart.h>
#include <HALWrapper/stm32_rcc.h>
#include <HALWrapper/stm32_gpio.h>
#include <HALWrapper/stm32_cortex.h>


#if ! defined STM32F3
    #error Expected MCU defines are not set. This example will only compile via the provided build script.
#endif


void exception()
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
}


GPIO_InitTypeDef gpioInit
{
   .Pin{ GPIO_PIN_3 },
   .Mode { GPIO_MODE_OUTPUT_PP },
   .Pull { GPIO_NOPULL },
   .Speed { GPIO_SPEED_LOW },
   .Alternate { 0 },
};


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


int main(int argc, const char* argv[])
{
   // Provided by libHALWrapper; default clock configuration
   SystemClock_Config();
   SystemCoreClockUpdate();
   
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_USART2_CLK_ENABLE();
   
   HAL_GPIO_Init( GPIOB, &gpioInit );
   HAL_GPIO_Init( GPIOA, &gpioUartInit );
   
   HAL_GPIO_WritePin(  GPIOB, GPIO_PIN_3, GPIO_PIN_SET );

   if ( HAL_UART_Init( &uartHandle ) != HAL_OK)
   {
      exception();
   }

   HAL_UART_Transmit( &uartHandle, (const uint8_t*)"Hello World!\n\r", 14, 100000 );

   while(1)
   {
      HAL_GPIO_WritePin(  GPIOB, GPIO_PIN_3, GPIO_PIN_SET );
      for(int i1=0; i1<100000; i1++)
      {
         asm( "nop; \n" );
      }
      
      HAL_GPIO_WritePin(  GPIOB, GPIO_PIN_3, GPIO_PIN_RESET );
      for(int i1=0; i1<100000/2; i1++)
      {
         asm( "nop; \n" );
      }
   }
   
   return(0);
};

