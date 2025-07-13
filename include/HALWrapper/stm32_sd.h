#if defined STM32F0
//#include <stm/stm32f0xx_hal_sd.h>
#elif defined STM32F1
#include <stm/stm32f1xx_hal_sd.h>
#elif defined STM32F3
    // No SD for F3
#elif defined STM32F4
#include <stm/stm32f4xx_hal_sd.h>
#elif defined STM32L1
#include <stm/stm32l1xx_hal_sd.h>
#elif defined STM32L0
   // No SD for L0
#elif defined STM32L4
#include <stm/stm32l4xx_hal_sd.h>
#elif defined STM32G4
   // No SD for G4
#elif defined STM32G0
   // No SD for G0
#else
#error "Unknown MCU"
#endif
