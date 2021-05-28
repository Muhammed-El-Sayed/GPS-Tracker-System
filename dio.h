/******************************************************************************
*
* Module: Dio
*
* File Name: Dio.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver
*
* Author: Salma ALi
******************************************************************************/

#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"
#include "Platform_Types.h"
#include "Common_Macros.h"

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES             (11U)

/* Channel Index in the array of structures in dio.c */
#define DioConf_LCD_RS_PIN_ID_INDEX        (uint8)0x00
#define DioConf_LCD_RW_PIN_ID_INDEX        (uint8)0x01
#define DioConf_LCD_E_PIN_ID_INDEX         (uint8)0x02
#define DioConf_LCD_D0_PIN_ID_INDEX        (uint8)0x03
#define DioConf_LCD_D1_PIN_ID_INDEX        (uint8)0x04
#define DioConf_LCD_D2_PIN_ID_INDEX        (uint8)0x05
#define DioConf_LCD_D3_PIN_ID_INDEX        (uint8)0x06
#define DioConf_LCD_D4_PIN_ID_INDEX        (uint8)0x07
#define DioConf_LCD_D5_PIN_ID_INDEX        (uint8)0x08
#define DioConf_LCD_D6_PIN_ID_INDEX        (uint8)0x09
#define DioConf_LCD_D7_PIN_ID_INDEX        (uint8)0x0A

/* DIO Configured Port ID's  */
#define DioConf_LCD_RS_PORT_NUM                0 /* PORTA */
#define DioConf_LCD_RW_PORT_NUM                0 /* PORTA */
#define DioConf_LCD_E_PORT_NUM                 0 /* PORTA */
#define DioConf_LCD_D0_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D1_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D2_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D3_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D4_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D5_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D6_PORT_NUM                1 /* PORTB */
#define DioConf_LCD_D7_PORT_NUM                1 /* PORTB */

/* DIO Configured Channel ID's */
#define DioConf_LCD_RS_PIN_NUM                 0/* Pin 0 in PORTA */
#define DioConf_LCD_RW_PIN_NUM                 1/* Pin 1 in PORTA */
#define DioConf_LCD_E_PIN_NUM                  2/* Pin 2 in PORTA */
#define DioConf_LCD_D0_PIN_NUM                 0/* Pin 0 in PORTB */
#define DioConf_LCD_D1_PIN_NUM                 1/* Pin 1 in PORTB */
#define DioConf_LCD_D2_PIN_NUM                 2/* Pin 2 in PORTB */
#define DioConf_LCD_D3_PIN_NUM                 3/* Pin 3 in PORTB */
#define DioConf_LCD_D4_PIN_NUM                 4/* Pin 4 in PORTB */
#define DioConf_LCD_D5_PIN_NUM                 5/* Pin 5 in PORTB */
#define DioConf_LCD_D6_PIN_NUM                 6/* Pin 6 in PORTB */
#define DioConf_LCD_D7_PIN_NUM                 7/* Pin 7 in PORTB */
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	 uint8  Port_Num;
	/* Member contains the ID of the Channel*/
	 uint8  Ch_Num;
}Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */
typedef struct Dio_ConfigType
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for DIO read Channel*/
uint8  Dio_ReadChannel(uint8 ChannelId);

/* Function for DIO write Channel */
void Dio_WriteChannel(uint8 ChannelId, uint8 Level);

/* Function for DIO Initialization API */
void Dio_Init(const Dio_ConfigType* ConfigPtr);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */
