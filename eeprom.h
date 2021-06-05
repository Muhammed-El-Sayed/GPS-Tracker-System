/******************************************************************************
 *
 * Module: eeprom
 *
 * File Name: eeprom.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller-internal EEPROM Driver
 *
 *
 *******************************************************************************/

#ifndef EEPEROM_H
#define EEPEROM_H


#include "Std_Types.h"
#include "Common_Macros.h"
#include <assert.h>

/*******************************************************************************
 *                      Preprocessor Macros                                    *
*******************************************************************************/
 
/* 
* EEPROM_SIZE_INFORMATION register contains size of EEPROM in two forms, form of # of blocks (16 words) 
* and # of words,
* we can use any form to calculate the EEPROM size in bytes.
* in the following Macro we use WORDCNT field in EEPROM_SIZE_INFORMATION to calcaulate the size in bytes 
*/
   
#define EEPROM_EESIZE_WORDCNT_MASK               0x0000FFFF         /*This mask is used to get the "WORDCNT" part from EESIZE.*/
#define EEPROM_EESIZE_WORDCNT_SHIFT              0                  /*This value is used to shift the "WORDCNT" part to LSBs to get size.*/

/* Size in bytes = size in words * 4*/
#define SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(x)   ((((x) & EEPROM_EESIZE_WORDCNT_MASK) >> EEPROM_EESIZE_WORDCNT_SHIFT) * 4)

/* EEPROM is word addressing */
#define EEPROM_BLOCK_FROM_ADDRESS( ui32Addr)     ((ui32Addr) >> 6)
#define EEPROM_OFFSET_FROM_ADDRESS(x)   (((x) >> 2) & 0x0F)
 /*******************************************************************************
  *                              Module Data Types                              *
 *******************************************************************************/
typedef union
{
    uint32 word_32_bit;
    struct S
    {
        char a;
        char b;
        char c;
        char d;

    }character_8_bit;
}REG;

/*******************************************************************************
 *                      Functions Prototypes                                   *
*******************************************************************************/

boolean EEPROM_Init(void);
uint32 EEPROM_getSize(void);
void EEPROM_read( uint32* saveLocation, uint32 startAddress, uint32 count);
void EEPROM_write( uint32* writeLocation, uint32 startAddress, uint32 count);
uint32 EEPROM_writeBytes(uint8* str,uint32 startAddress);

#endif
