//----------------------------------------------------------------------------
///
/// \brief  Some info about the STM32 chip thats used
///
///         STM32_SPEED_FAKTOR: frequency divided by 16Mhz
///
/// \date   20150111
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile"

#if defined STM32L100xC
#include <stm/stm32l100xc.h>
#elif defined STM32F103x6
#include <stm/stm32f103x6.h>
#elif defined STM32F103xB
#include <stm/stm32f103xb.h>
#elif defined STM32F303x8
#include <stm/stm32f303x8.h>
#elif defined STM32F334x8
#include <stm/stm32f334x8.h>
#elif defined STM32F407xx
#include <stm/stm32f407xx.h>
#elif defined STM32F072xB
#include <stm/stm32f072xb.h>
#elif defined STM32F042x6
#include <stm/stm32f042x6.h>
#include <stm/stm32f0xx_hal.h>
#elif defined STM32L011xx
#include <stm/stm32l011xx.h>
#elif defined STM32L031xx
#include <stm/stm32l031xx.h>
#elif defined STM32L151xB
#include <stm/stm32l151xb.h>
#elif defined STM32L152xB
#include <stm/stm32l152xb.h>
#elif defined STM32L431xx
#include <stm/stm32l431xx.h>
#elif defined STM32L443xx
#include <stm/stm32l443xx.h>
#elif defined STM32G030xx
#include <stm/stm32g030xx.h>
#elif defined STM32G441xx
#include <stm/stm32g441xx.h>
#elif defined STM32G030xx
#include <stm/stm32g030xx.h>
#else
#error "Unknown MCU"
#endif

#pragma GCC diagnostic pop


//---fin.---------------------------------------------------------------------
