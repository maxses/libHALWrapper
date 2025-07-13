/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"

void PWR_DeInit(void)
{
    return;
}

void PWR_BackupAccessCmd(FunctionalState NewState)
{
    return;
}

void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
    return;
}

void PWR_PVDCmd(FunctionalState NewState)
{
    return;
}

void PWR_WakeUpPinCmd(FunctionalState NewState)
{
    return;
}

void PWR_BackupRegulatorCmd(FunctionalState NewState)
{
    return;
}

void PWR_MainRegulatorModeConfig(uint32_t PWR_Regulator_Voltage)
{
    return;
}

void PWR_FlashPowerDownCmd(FunctionalState NewState)
{
    return;
}

void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    return;
}

void PWR_EnterSTANDBYMode(void)
{
    return;
}

FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;

  return bitstatus;
}

void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    return;
}

