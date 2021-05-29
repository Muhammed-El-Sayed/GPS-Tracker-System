 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_


#include "Std_Types.h"
#include "SystickTimer.h"
#include "dio.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Commands */
#define CLEAR_COMMAND                  0x01
#define TWO_LINE_LCD_Eight_BIT_MODE_COMMAND   0x38
#define SET_CURSOR_LOCATION_COMMAND            0x80
#define CURSOR_OFF_COMMAND                    0x0C
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(uint8* string);
void LCD_goToRowColoumn(uint8 rowOffset, uint8 coloumnOffset);
void LCD_displayStringRowColoumn(uint8* string, uint8 row, uint8 coloumn);
void LCD_clearScreen(void);
void LCD_integerToString(sint16 data);
void LCD_init(void);
void LCD_doubleToString(float64 data);
#endif