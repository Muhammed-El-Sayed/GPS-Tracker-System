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

boolean EEPROM_init(void)
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

// Returns size of EEPROM in bytes.
uint32 EEPROM_getSize(void) {
	return (SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
}

// Reads "ui32Count" bytes from address "ui32Address" and save it at location "pui32Data"
// Note: Memory is word addressing, but the user should send the address of byte, so it should be multible of 4 (word alligned)
void EEPROM_read(uint32_t* saveLocation, uint32_t startAddress, uint32_t count)
{
	// Ensures that the address is > 0  --> Not sure why
  	assert(saveLocation);
  	// Ensures that the start reading addresss is in available EEPROM address space
  	assert(startAddress < SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
  	// Ensures that the last address is in available EEPROM address space
  	assert((startAddress + count) <= SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
    // Ensures that the assress is word alligned 
	assert((address & 3) == 0);
	// Ensures that the count is word alligned 
   	assert((count & 3) == 0);

   	// Get count in words
   	count /= 4;

   	// Set start reading address, each address containes one word
   	// Read address consists of block address + word offset 
   	EEPROM_CURRENT_BLOCK_REGISTER = EEPROM_BLOCK_FROM_ADDRESS(address);
   	EEPROM_CURRENT_OFFSET_REGISTER = EEPROM_OFFSET_FROM_ADDRESS(address);

   	// Read one word per itiration 
   	while (count) 
   	{
   		// Get the data of the current address in EEPROM and increment the address to the next read
   		*saveLocation = EPRROM_READ_WRITE_WITH_INCREMENT_REGISTER;
   		// Increase the save location to the next place.
   		saveLocation++;
   		count--;
   		// Increase block if the offset reaches maximum (word number 15 in the 16 word block)
   		// Note: the EEPROM_CURRENT_OFFSET_REGISTER is automatically reset to zero after reaching 15
   		if(count && (EEPROM_CURRENT_OFFSET_REGISTER == 0)) 
   		{
   			EEPROM_CURRENT_BLOCK_REGISTER++;
   		}
   	}
}


void EEPROM_write(uint32_t* writeLocation, uint32_t startAddress, uint32_t count) 
{
	// Ensures that the address is > 0  --> Not sure why
  	assert(writeLocation);
  	// Ensures that the start reading addresss is in available EEPROM address space
  	assert(startAddress < SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
  	// Ensures that the last address is in available EEPROM address space
  	assert((startAddress + count) <= SIZE_OF_EEPROM_IN_WORDS_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
    // Ensures that the assress is word alligned 
	assert((address & 3) == 0);
	// Ensures that the count is word alligned 
   	assert((count & 3) == 0);

   	// Busy waiting till EEPROM finishes it's current operation.
   	do 
   	{
   		uint32 writeStatus = EEPROM_DONE_STATUS_REGISTER;
   	}
   	while (writeStatus & WORKING_BIT);


   	// Get count in words
   	count /= 4;

   	// Set start writing address, each address containes one word
   	// Write address consists of block address + word offset 
   	EEPROM_CURRENT_BLOCK_REGISTER = EEPROM_BLOCK_FROM_ADDRESS(address);
   	EEPROM_CURRENT_OFFSET_REGISTER = EEPROM_OFFSET_FROM_ADDRESS(address);

   	while (count) 
   	{
   		// Here we should check for silicon problem, but we didn't found any info. about it in datasheet
		
		// Save the data at the current address in EEPROM and increment the address to the next operation
   		EPRROM_READ_WRITE_WITH_INCREMENT_REGISTER = *writeLocation;
   		SysTick_Delay_ms(1);
   		// Busy waiting till writing ends
   		do 
   		{
   			uint32 writeStatus = EEPROM_DONE_STATUS_REGISTER;
   		}
   		while (writeStatus & WORKING_BIT);
   		// Increase the write location to the next place.
   		writeLocation++;
   		count--;
   		// Increase block if the offset reaches maximum (word number 15 in the 16 word block)
   		// Note: the EEPROM_CURRENT_OFFSET_REGISTER is automatically reset to zero after reaching 15
   		if(count && (EEPROM_CURRENT_OFFSET_REGISTER == 0)) 
   		{
   			EEPROM_CURRENT_BLOCK_REGISTER++;
   		}
   	}
}
