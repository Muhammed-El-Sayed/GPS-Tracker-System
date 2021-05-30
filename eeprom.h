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

// EESIZE register contains size of EEPROM in two forms, form of # of blocks (16 words) and # of words, we can use any
// form to calculate the EEPROM size in bytes.
#define EEPROM_EESIZE_WORDCNT_MASK               0x07FF0000           // This mask is used to get the "BLKCNT" part from EESIZE.
#define EEPROM_EESIZE_WORDCNT_SHIFT 16                   // This value is used to shift the "BLKCNT" part to LSBs to get size.
// Size in bytes = size in words * 4
#define SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(x)   ((((x) & EEPROM_EESIZE_WORDCNT_MASK) >> EEPROM_EESIZE_WORDCNT_SHIFT) * 4)

// EEPROM is word addressing
#define EEPROM_BLOCK_FROM_ADDRESS(x)             (x &= 0xFFFFFFF0)
#define EEPROM_OFFSET_FROM_ADDRESS(x)            (x &= ~(0xFFFFFFF0))

boolean EEPROMInit(void);
uint32 EEPROM_getSize(void);
void EEPROM_read(uint32_t* saveLocation, uint32_t startAddress, uint32_t count);
void EEPROM_write(uint32_t* writeLocation, uint32_t startAddress, uint32_t count);

#endif