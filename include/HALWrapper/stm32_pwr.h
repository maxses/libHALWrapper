#if defined STM32F0
#include <stm/stm32f0xx_hal_pwr.h>
#include <stm/stm32f0xx_hal_pwr_ex.h>
#elif defined STM32F1
#include <stm/stm32f1xx_hal_pwr.h>
#elif defined STM32F3
#include <stm/stm32f3xx_hal_pwr.h>
#elif defined STM32F4
#include <stm/stm32f4xx_hal_pwr.h>
#elif defined STM32L1
#include <stm/stm32l1xx_hal_pwr.h>
#elif defined STM32L0
#include <stm/stm32l0xx_hal_pwr.h>
#elif defined STM32L4
#include <stm/stm32l4xx_hal_pwr.h>
#elif defined STM32G0
#include <stm/stm32g0xx_hal_pwr.h>
#elif defined STM32G4
#include <stm/stm32g4xx_hal_pwr.h>
#elif defined STM32G0
#include <stm/stm32g0xx_hal_pwr.h>
#else
#error "unknown MCU"
#endif
