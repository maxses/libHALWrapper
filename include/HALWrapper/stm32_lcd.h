#if defined STM32F0
#elif defined STM32F1
#elif defined STM32F3
#elif defined STM32F4
#elif defined STM32L1
#include <stm/stm32l1xx_hal_lcd.h>
#elif defined STM32L0
#elif defined STM32L4
#elif defined STM32G4
#else
#error "unknown MCU"
#endif
