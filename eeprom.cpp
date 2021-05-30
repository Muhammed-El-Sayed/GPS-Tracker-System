/******************************************************************************
 *
 * Module: TivaC internal EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: Source file for the internal EEPROM Memory
 *
 *
 *******************************************************************************/
#include "eeprom.h"
#include "eeprom_Regs.h"

boolean EEPROMInit(void)
{

	SET_BIT(EEPROM_RUN_MODE_GATING_CONTROL_REGISTER, RO);
	SysTick_Delay_ms(1);
	while (BIT_IS_SET(EEPROM_DONE_STATUS_REGISTER, WORKING_BIT));
	if (BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, PRETRY) | BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, ERETRY))
		return FALSE;
	SET_BIT(EEPROM_SOFTWARE_RESET_REGISTER, RO);
	SysTick_Delay_ms(1);
	while (BIT_IS_SET(EEPROM_DONE_STATUS_REGISTER, WORKING_BIT));
	if (BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, PRETRY) | BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, ERETRY))
		return FALSE;
	return TRUE;

}

void
EEPROMRead(uint32_t* pui32Data, uint32_t ui32Address, uint32_t ui32Count)
{
  
}
