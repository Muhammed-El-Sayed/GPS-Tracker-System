#ifndef LCD_H_
#define LCD_H_
#include"dio.h"
#include"Platform_Types.h"
#include"Timer.h"
#define CLEAR_COMMAND                  0x01
#define EIGHT_BIT_MODE_TWO_LINES       0x38
#define CURSOR_OR_DISPLAY_SHIFT        0x80
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(uint8* string);
void LCD_goToRowColoumn(uint8 rowOffset, uint8 coloumnOffset);
void LCD_displayStringRowColoumn(uint8* string, uint8 row, uint8 coloumn);
void LCD_clearScreen();
void LCD_integerToString(sint16 data);
void LCD_init();
void LCD_doubleToString(float64 data);
#endif