/******************************************************************************
 *
 * Module: eeprom
 *
 * File Name: eeprom.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller- internal EEPROM Driver
 *
 *
 *******************************************************************************/
#include "eeprom.h"
#include "eeprom_Regs.h"
#include "SystickTimer.h"

boolean EEPROM_Init(void)
{
     //  EEPROM_DONE_STATUS_REGISTER = 0x0;
	SET_BIT(EEPROM_RUN_MODE_GATING_CONTROL_REGISTER, R0_BIT);
	SysTick_Delay_ms(1);
	while (BIT_IS_SET(EEPROM_DONE_STATUS_REGISTER, WORKING_BIT));
        	//SysTick_Delay_ms(1);

	if (BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, PRETRY_BIT) | BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, ERETRY_BIT))
		return FALSE;
	CLEAR_BIT(EEPROM_SOFTWARE_RESET_REGISTER, R0_BIT);
	SysTick_Delay_ms(1);
	while (BIT_IS_SET(EEPROM_DONE_STATUS_REGISTER, WORKING_BIT));
        	//SysTick_Delay_ms(1);

	if (BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, PRETRY_BIT) | BIT_IS_SET(EEPROM_SUPPORT_CONTROL_STATUS_REGISTER, ERETRY_BIT))
		return FALSE;
	return TRUE;
}

/*Returns the size of EEPROM in bytes.*/
uint32 EEPROM_getSize(void) 
{
	return (SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
}

/* 
* Reads "Count" bytes from  "startAddress" word offset and saves the data starting from location "saveLocation" 
* Note: Memory is word addressing, but the user should send the address of byte, so it should be multible of 4 (word alligned)
* startAddress: not an actual address, it's an "offset" multiple of 4
* count: no.of bytes
*/
void EEPROM_read( uint32* saveLocation, uint32 startAddress, uint32 count)
{
	// Ensures that the address is > 0  --> Not sure why
  	assert(saveLocation);
  	// Ensures that the start reading addresss is in available EEPROM address space
  	assert(startAddress < SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
  	// Ensures that the last address is in available EEPROM address space
  	assert((startAddress + count) <= SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
       // Ensures that the assress is word alligned 
	assert((startAddress & 3) == 0);
	// Ensures that the count is word alligned 
   	assert((count & 3) == 0);

   	// Get count in words
   	count /= 4;

   	// Set start reading address, each address containes one word
   	// Read address consists of block address + word offset 
   	EEPROM_CURRENT_BLOCK_REGISTER = EEPROM_BLOCK_FROM_ADDRESS(startAddress);
   	EEPROM_CURRENT_OFFSET_REGISTER = EEPROM_OFFSET_FROM_ADDRESS(startAddress);

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


void EEPROM_write( uint32* writeLocation, uint32 startAddress, uint32 count) 
{
	// Ensures that the address is > 0  --> Not sure why
  	assert(writeLocation);
  	// Ensures that the start reading addresss is in available EEPROM address space
  	assert(startAddress < SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
  	// Ensures that the last address is in available EEPROM address space
  	assert((startAddress + count) <= SIZE_OF_EEPROM_IN_BYTES_FROM_EESIZE(EEPROM_SIZE_INFORMATION));
        //Ensures that the assress is word alligned 
	assert((startAddress & 3) == 0);
	// Ensures that the count is word alligned 
   	assert((count & 3) == 0);

   	// Busy waiting till EEPROM finishes it's current operation.
        uint32 writeStatus;
   	do 
   	{
   		writeStatus = EEPROM_DONE_STATUS_REGISTER;
   	}
   	while (writeStatus & WORKING_BIT);


   	// Get count in words
   	count /= 4;

   	// Set start writing address, each address containes one word
   	// Write address consists of block address + word offset 
   	EEPROM_CURRENT_BLOCK_REGISTER = EEPROM_BLOCK_FROM_ADDRESS(startAddress);
   	EEPROM_CURRENT_OFFSET_REGISTER = EEPROM_OFFSET_FROM_ADDRESS(startAddress);

   	while (count) 
   	{
   		// Here we should check for silicon problem, but we didn't found any info. about it in datasheet
		
		// Save the data at the current address in EEPROM and increment the address to the next operation
   		EPRROM_READ_WRITE_WITH_INCREMENT_REGISTER = *writeLocation;
   		SysTick_Delay_ms(1);
   		// Busy waiting till writing ends
   		do 
   		{
   		    writeStatus = EEPROM_DONE_STATUS_REGISTER;
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
uint32 EEPROM_writeBytes(uint8* str,uint32 startAddress)
{
    REG num;
    char* ptr = &num.character_8_bit.d;
    int character_count = 0;
    int word_count = startAddress;
    boolean flag = FALSE;
  
    
   while (str[character_count]!='\0')
    {
           *ptr = str[character_count];
           ptr--;
           if (flag == TRUE)
           {
               flag = FALSE;
              EEPROM_write(&num.word_32_bit,word_count*4,4);
               ptr = &num.character_8_bit.d;
               word_count++;
           }
           if (ptr == &num.character_8_bit.a)
           {
               flag = TRUE;
           }
           character_count++;
        
    }

   while (ptr != &num.character_8_bit.a)
   {
       *ptr = '#';
       ptr--;
       if (ptr == &num.character_8_bit.a)
       {
           *ptr = '#';
            EEPROM_write(&num.word_32_bit,word_count*4,4);
             word_count++;
            
       }

   }
   /* last word that remarks the end of the string ########*/
  uint32 endOfString= 0x23232323;
   EEPROM_write(&endOfString,word_count*4,4);
   word_count++;
   return word_count;
}

