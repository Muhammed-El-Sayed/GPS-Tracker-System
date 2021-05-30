/******************************************************************************
 *
 * Module: TivaC internal EEPROM
 *
 * File Name: eeprom.h
 *
 * Description: Header file for the internal EEPROM Memory
 *
 *
 *******************************************************************************/

#ifndef EEPEROM_H
#define EEPEROM_H

#include "SystickTimer.h"
#include "Std_Types.h"

boolean EEPROMInit(void);
void EEPROMRead(uint32* pui32Data, uint32 ui32Address, uint32 ui32Count);
#endif