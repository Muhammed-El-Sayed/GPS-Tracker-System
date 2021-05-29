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
#include "Common_Macros.h"

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES             (4U)
#define DIO_CONFIGURED_PORTS                (1U)
/* Channel Index in the array of structures in dio.c */
#define DioConf_LCD_RS_PIN_ID_INDEX        (uint8)0x00
#define DioConf_LCD_RW_PIN_ID_INDEX        (uint8)0x01
#define DioConf_LCD_E_PIN_ID_INDEX         (uint8)0x02
#define DioConf_LED_PIN_ID_INDEX           (uint8)0x03
/* Channel Index in the array of structures in dio.c */
#define DioConf_PORTB_PORT_ID_INDEX        (uint8)0x00
/* DIO Configured Port ID's  */
#define DioConf_LCD_RS_PORT_NUM                0 /* PORTA */
#define DioConf_LCD_RW_PORT_NUM                0 /* PORTA */
#define DioConf_LCD_E_PORT_NUM                 0 /* PORTA */
#define DioConf_LED_PORT_NUM                   5 /* PORTF*/
/* DIO Configured Channel ID's */
#define DioConf_LCD_RS_PIN_NUM                 0/* Pin 0 in PORTA */
#define DioConf_LCD_RW_PIN_NUM                 1/* Pin 1 in PORTA */
#define DioConf_LCD_E_PIN_NUM                  2/* Pin 2 in PORTA */
#define DioConf_LED_PIN_NUM                    1/* Pin 1 in PORTF */

/*DIO configured Port Port ID*/
#define DioConf_PORTB_PORT_NUM                1/* PORTB */

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
typedef struct
{
	/* Member contains the ID of the Port*/
	 uint8  Port_Num;
	
}Dio_ConfigPort;

/* Data Structure required for initializing the Dio Driver */
typedef struct Dio_ConfigType
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
        Dio_ConfigPort Ports[DIO_CONFIGURED_PORTS];
} Dio_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to read Port*/
uint8 Dio_ReadPort(uint8 PortId);

/* Function to write Port */
void Dio_WritePort(uint8 PortId, uint8 Level);


/* Function to read channel  */
uint8 Dio_ReadChannel(uint8 ChannelId);

/* Function to write channel */
void Dio_WriteChannel(uint8 ChannelId, uint8 Level);

/* Function for DIO module Initialization */
void Dio_Init(const Dio_ConfigType* ConfigPtr);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */
