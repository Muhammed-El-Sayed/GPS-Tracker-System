 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 *******************************************************************************/

#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LCD_init(void) 
{
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE_COMMAND); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(CURSOR_OFF_COMMAND); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}


void LCD_sendCommand(uint8 command) 
{
	Dio_WriteChannel(DioConf_LCD_RS_PIN_ID_INDEX, 0);/* Instruction Mode RS=0 */
	Dio_WriteChannel(DioConf_LCD_RW_PIN_ID_INDEX, 0);/* write data to LCD so RW=0 */
	SysTick_Delay_ms(1);/* delay for processing Tas = 50ns */
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 1);/* Enable LCD E=1 */
	SysTick_Delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
	Dio_WritePort(DioConf_PORTB_PORT_ID_INDEX ,command);/* out the required command to the data bus D0 --> D7 */
	SysTick_Delay_ms(1);/* delay for processing Tdsw = 100ns */
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 0);/* disable LCD E=0 */
	SysTick_Delay_ms(1);/* delay for processing Th = 13ns */
}


void LCD_displayCharacter(uint8 character) 
{
	Dio_WriteChannel(DioConf_LCD_RS_PIN_ID_INDEX, 1);/* Data Mode RS=1 */	
	Dio_WriteChannel(DioConf_LCD_RW_PIN_ID_INDEX, 0);/* write data to LCD so RW=0 */
	SysTick_Delay_ms(1);/* delay for processing Tas = 50ns */
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 1);/* Enable LCD E=1 */
	SysTick_Delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
	Dio_WritePort(DioConf_PORTB_PORT_ID_INDEX ,character);/* out the required command to the data bus D0 --> D7 */
	SysTick_Delay_ms(1);/* delay for processing Tdsw = 100ns */
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 0);/* disable LCD E=0 */
	SysTick_Delay_ms(1);/* delay for processing Th = 13ns */
}


void LCD_displayString(uint8* string)
{
	uint8 index = 0;
	while(*(string + index) != '\0') 
        {
		LCD_displayCharacter(*(string + index++));
	}
}


void LCD_goToRowColoumn(uint8 rowOffset, uint8 coloumnOffset) {
	uint8 offset = 0x00;
	if(rowOffset > 0)
        {
          offset += 0x40;
        }
	offset += coloumnOffset;
	LCD_sendCommand(SET_CURSOR_LOCATION_COMMAND + offset);
}

void LCD_displayStringRowColoumn(uint8* string, uint8 row, uint8 coloumn) 
{
	LCD_goToRowColoumn(row, coloumn);
	LCD_displayString(string);
}


void LCD_clearScreen(void) 
{
	LCD_sendCommand(CLEAR_COMMAND);
}


void LCD_integerToString(int number)
{
   uint8 str[16];    /*create an empty string to store number*/
   sprintf((char*)str,"%i", number);   /*make the number into string using sprintf function*/
   LCD_displayString(str);

}

void LCD_doubleToString(float64 number) 
{
 
	sint16 x = (sint16)number;
	LCD_integerToString(x);
	LCD_displayCharacter('.');
	float64 fraction = number - x;
	x = (sint16) (fraction * 100);
        if(x < 10)
          LCD_displayCharacter('0');
	LCD_integerToString(x);
}

