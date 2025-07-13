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


#if defined STM32L100xC

#elif defined STM32F103xB

#elif defined STM32F303x8

#elif defined STM32F334x8

#elif defined STM32F407xx
#include <stm/core_cm4.h>
#elif defined STM32F072xB
#include <stm/core_cm0.h>
#endif


//---fin.---------------------------------------------------------------------
