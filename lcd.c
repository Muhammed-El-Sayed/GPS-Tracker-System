#include"lcd.h"
void LCD_sendCommand(uint8 command) {
	Dio_WriteChannel(DioConf_LCD_RS_PIN_ID_INDEX, 0);	
	Dio_WriteChannel(DioConf_LCD_RW_PIN_ID_INDEX, 0);
	// MARK:- this function isn't implemented 
	delay(50);  // Unit is ns
	//
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 1);
	// MARK:- this function isn't implemented 
	delay(190);  // Unit is ns
	//
	Dio_WritePort(DioConf_PORTB_PORT_ID_INDEX ,command);
	// MARK:- this function isn't implemented 
	delay(100);  // Unit is ns
	//
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 0);
	// MARK:- this function isn't implemented 
	delay(13);  // Unit is ns
	//
}


void LCD_displayCharacter(uint8 character) {
	Dio_WriteChannel(DioConf_LCD_RS_PIN_ID_INDEX, 1);	
	Dio_WriteChannel(DioConf_LCD_RW_PIN_ID_INDEX, 0);
	// MARK:- this function isn't implemented 
	delay(50);  // Unit is ns
	//
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 1);
	// MARK:- this function isn't implemented 
	delay(190);  // Unit is ns
	//
	Dio_WritePort(DioConf_PORTB_PORT_ID_INDEX ,character);
	// MARK:- this function isn't implemented 
	delay(100);  // Unit is ns
	//
	Dio_WriteChannel(DioConf_LCD_E_PIN_ID_INDEX, 0);
	// MARK:- this function isn't implemented 
	delay(13);  // Unit is ns
	//
}


void LCD_displayString(uint8* string) {
	uint8 index = 0;
	while(*(string + index) != '\0') {
		LCD_displayCharacter(*(string + index++));
	}
}

// zero index
void LCD_goToRowColoumn(uint8 rowOffset, uint8 coloumnOffset) {
	uint8 offset = 0x00;
	if(rowOffset > 0)
		offset += 0x40;
	offset += coloumnOffset;
	LCD_sendCommand(CURSOR_OR_DISPLAY_SHIFT + offset);
}

void LCD_displayStringRowColoumn(uint8* string, uint8 row, uint8 coloumn) {
	LCD_goToRowColoumn(row, coloumn);
	LCD_displayString(string);
}


void LCD_clearScreen() {
	LCD_sendCommand(CLEAR_COMMAND);
}


void LCD_integerToString(sint16 data) {
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);
}


void LCD_init() {
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_doubleToString(float64 data) {
	sint16 x = (sint16)data;
	LCD_integerToString(x);
	LCD_displayCharacter('.');
	float64 fraction = data - x;
	x=fraction * 100;
	LCD_integerToString(x);
}