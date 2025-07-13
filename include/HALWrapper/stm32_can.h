#if defined STM32F0
    #include <stm/stm32f0xx_hal_can.h>
    #include <stm/stm32f0xx_hal_can.h>
#elif defined STM32F1
    #include <stm/stm32f1xx_hal_can.h>
#elif defined STM32F3
    #include <stm/stm32f3xx_hal_can.h>
#elif defined STM32F4
    #include <stm/stm32f4xx_hal_can.h>
#elif defined STM32L1
    // No can on STM32L100
    #error "No CAN on this MCU"
#elif defined STM32L0
    // No can on STM32L011
    #error "No CAN on this MCU"
#elif defined STM32L4
    #include <stm/stm32l4xx_hal_can.h>
#elif defined STM32G0
    #include <stm/stm32g0xx_hal_fdcan.h>
#elif defined STM32G4
   // mpu_armv7.h uses "compound assignment with 'volatile'-qualified left operand
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wvolatile"
      #include <stm/stm32g4xx_hal_fdcan.h>
   #pragma GCC diagnostic pop
#else
    #error "Unknown MCU"
#endif
