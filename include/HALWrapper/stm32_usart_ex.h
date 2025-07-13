#if defined STM32F0
   #include <stm/stm32f0xx_hal_usart_ex.h>
#elif defined STM32F1
   // Does not exist. USART_WORDLENGTH is defined in stm32f4xx_hal_usart.h
#elif defined STM32F3
   #include <stm/stm32f3xx_hal_usart_ex.h>
#elif defined STM32F4
   // Does not exist. USART_WORDLENGTH is defined in stm32f4xx_hal_usart.h
#elif defined STM32L1
   // Does not exist. USART_WORDLENGTH is defined in stm32l1xx_hal_usart.h
#elif defined STM32G4
   #include <stm/stm32g4xx_hal_usart_ex.h>
#endif
