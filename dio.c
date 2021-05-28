/******************************************************************************
*
* Module: Dio
*
* File Name: Dio.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Dio Driver
*
* Author: Salma Ali
******************************************************************************/

#include "dio.h"
#include "Dio_Regs.h"
/* PB structure used with Dio_Init */
const Dio_ConfigType Dio_Configuration = {
		                                                           DioConf_LCD_RS_PORT_NUM,DioConf_LCD_RS_PIN_NUM,
							                   DioConf_LCD_RW_PORT_NUM,DioConf_LCD_RW_PIN_NUM,
                                                                           DioConf_LCD_E_PORT_NUM,DioConf_LCD_E_PIN_NUM,
                                                                           DioConf_LCD_D0_PORT_NUM,DioConf_LCD_D0_PIN_NUM,
                                                                           DioConf_LCD_D1_PORT_NUM,DioConf_LCD_D1_PIN_NUM,
                                                                           DioConf_LCD_D2_PORT_NUM,DioConf_LCD_D2_PIN_NUM,
                                                                           DioConf_LCD_D3_PORT_NUM,DioConf_LCD_D3_PIN_NUM,
                                                                           DioConf_LCD_D4_PORT_NUM,DioConf_LCD_D4_PIN_NUM,
                                                                           DioConf_LCD_D5_PORT_NUM,DioConf_LCD_D5_PIN_NUM,
                                                                           DioConf_LCD_D6_PORT_NUM,DioConf_LCD_D6_PIN_NUM,
                                                                           DioConf_LCD_D7_PORT_NUM,DioConf_LCD_D7_PIN_NUM,
};
static const Dio_ConfigChannel* Dio_PortChannels = NULL_PTR;
/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType* ConfigPtr)
{

		/* point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
	
}
/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(uint8 ChannelId,uint8 Level)
{
	volatile uint32* Port_Ptr = NULL_PTR;
	
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch (Dio_PortChannels[ChannelId].Port_Num)
		{
		case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
			break;
		case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
			break;
		case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
			break;
		case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
			break;
		case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
			break;
		case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
			break;
		}
		if (Level == STD_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
		}
		else if (Level == STD_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
		}
	
}
/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
uint8 Dio_ReadChannel(uint8 ChannelId)
{
	volatile uint32* Port_Ptr = NULL_PTR;
	uint8 output = STD_LOW;
	
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch (Dio_PortChannels[ChannelId].Port_Num)
		{
		case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
			break;
		case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
			break;
		case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
			break;
		case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
			break;
		case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
			break;
		case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
			break;
		}
		/* Read the required channel */
		if (BIT_IS_SET(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num))
		{
			output = STD_HIGH;
		}
		else
		{
			output = STD_LOW;
		}

	return output;
}

