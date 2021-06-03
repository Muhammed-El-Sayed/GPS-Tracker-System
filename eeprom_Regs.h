 /******************************************************************************
 *
 * Module: eeprom
 *
 * File Name: eeprom_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - eeprom driver Registers
 *
 ******************************************************************************/

#ifndef EEPEROM_REGS_H
#define EEPEROM_REGS_H


#define EEPROM_RUN_MODE_GATING_CONTROL_REGISTER      (*((volatile unsigned long *)0x400FE658))
#define R0_BIT 0

/*Two block types: 16 word/block or 1 word/block */
/*this register indicates the number of 16-word blocks and 32-bit words in the EEPROM.*/
#define EEPROM_SIZE_INFORMATION                      (*((volatile unsigned long *)0x400AF000))

/*The EEBLOCK register is used to select the EEPROM block for subsequent reads, writes and protection control*/
#define EEPROM_CURRENT_BLOCK_REGISTER                (*((volatile unsigned long *)0x400AF004))

/*register is used to select the EEPROM word to read or write within the block selected by the EEBLOCK register*/
/*to calculate the address of the word that will be written or read we add current block adderss to the curennt offset*/
#define EEPROM_CURRENT_OFFSET_REGISTER               (*((volatile unsigned long *)0x400AF008))

#define EPRROM_READ_WRITE_REGISTER                   (*((volatile unsigned long *)0x400AF010))

#define EPRROM_READ_WRITE_WITH_INCREMENT_REGISTER    (*((volatile unsigned long *)0x400AF014))

#define EEPROM_DONE_STATUS_REGISTER                  (*((volatile unsigned long *)0x400AF018))
#define WORKING_BIT   0

#define EEPROM_SUPPORT_CONTROL_STATUS_REGISTER       (*((volatile unsigned long *)0x400AF01C))
#define PRETRY_BIT 3
#define ERETRY_BIT 2

#define EEPROM_INTERRUPT_REGISTER                    (*((volatile unsigned long *)0x400AF040))

#define EEPROM_DEBUG_MASS_ERASE_REGISTER             (*((volatile unsigned long *)0x400AF040))

#define EEPROM_SOFTWARE_RESET_REGISTER               (*((volatile unsigned long *)0x400FE558))


#endif