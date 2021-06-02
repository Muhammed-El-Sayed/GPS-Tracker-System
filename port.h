/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Salma Ali
 ******************************************************************************/
#ifndef PORT_H
#define PORT_H

#include "Std_Types.h"
#include "Common_Macros.h"

/* Number of configured Port Pins */
#define PORT_CONFIGURED_PINS                    (12U)

/* Pin Index in the array of structures in Port_PBcfg.c */
#define PortConf_LCD_RS_PIN_ID_INDEX        (uint8)0x00
#define PortConf_LCD_RW_PIN_ID_INDEX        (uint8)0x01
#define PortConf_LCD_E_PIN_ID_INDEX         (uint8)0x02
#define PortConf_LCD_D0_PIN_ID_INDEX        (uint8)0x03
#define PortConf_LCD_D1_PIN_ID_INDEX        (uint8)0x04
#define PortConf_LCD_D2_PIN_ID_INDEX        (uint8)0x05
#define PortConf_LCD_D3_PIN_ID_INDEX        (uint8)0x06
#define PortConf_LCD_D4_PIN_ID_INDEX        (uint8)0x07
#define PortConf_LCD_D5_PIN_ID_INDEX        (uint8)0x08
#define PortConf_LCD_D6_PIN_ID_INDEX        (uint8)0x09
#define PortConf_LCD_D7_PIN_ID_INDEX        (uint8)0x0A
#define PortConf_LED_PIN_ID_INDEX           (uint8)0x0B
 
/* PORT Configured Port IDs  */
#define PortConf_LCD_RS_PORT_NUM                0 /* PORTA */
#define PortConf_LCD_RW_PORT_NUM                0 /* PORTA */
#define PortConf_LCD_E_PORT_NUM                 0 /* PORTA */
#define PortConf_LCD_D0_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D1_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D2_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D3_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D4_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D5_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D6_PORT_NUM                1 /* PORTB */
#define PortConf_LCD_D7_PORT_NUM                1 /* PORTB */
#define PortConf_LED_PORT_NUM                   5 /* PORTF */
   
/*PORT Configured Pin IDs */
#define PortConf_LCD_RS_PIN_NUM                 2/* Pin 0 in PORTA */
#define PortConf_LCD_RW_PIN_NUM                 3/* Pin 1 in PORTA */
#define PortConf_LCD_E_PIN_NUM                  4/* Pin 2 in PORTA */
#define PortConf_LCD_D0_PIN_NUM                 0/* Pin 0 in PORTB */
#define PortConf_LCD_D1_PIN_NUM                 1/* Pin 1 in PORTB */
#define PortConf_LCD_D2_PIN_NUM                 2/* Pin 2 in PORTB */
#define PortConf_LCD_D3_PIN_NUM                 3/* Pin 3 in PORTB */
#define PortConf_LCD_D4_PIN_NUM                 4/* Pin 4 in PORTB */
#define PortConf_LCD_D5_PIN_NUM                 5/* Pin 5 in PORTB */
#define PortConf_LCD_D6_PIN_NUM                 6/* Pin 6 in PORTB */
#define PortConf_LCD_D7_PIN_NUM                 7/* Pin 7 in PORTB */
#define PortConf_LED_PIN_NUM                    1/* Pin 1 in PORTF */
   
/* PORT configured Pin Direction */
#define PortConf_LCD_RS_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 0 in PORTA as an output pin */
#define PortConf_LCD_RW_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 1 in PORTA as an output pin */
#define PortConf_LCD_E_PIN_DIRECTION           (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 2 in PORTA as an output pin */
#define PortConf_LCD_D0_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 0 in PORTB as an output pin */
#define PortConf_LCD_D1_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 1 in PORTB as an output pin */
#define PortConf_LCD_D2_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 2 in PORTB as an output pin */
#define PortConf_LCD_D3_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 3 in PORTB as an output pin */
#define PortConf_LCD_D4_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 4 in PORTB as an output pin */
#define PortConf_LCD_D5_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 5 in PORTB as an output pin */
#define PortConf_LCD_D6_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 6 in PORTB as an output pin */
#define PortConf_LCD_D7_PIN_DIRECTION          (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 7 in PORTB as an output pin */
#define PortConf_LED_PIN_DIRECTION             (Port_PinDirectionType)PORT_PIN_OUT/*configure Pin 1 in PORTF as an output pin */
   
/*PORT configured Pin Mode */
#define PortConf_LCD_RS_PIN_MODE                0 /*configure Pin 0 in PORTA as GPIO Pin */
#define PortConf_LCD_RW_PIN_MODE                0 /*configure Pin 1 in PORTA as GPIO Pin */
#define PortConf_LCD_E_PIN_MODE                 0 /*configure Pin 2 in PORTA as GPIO Pin */
#define PortConf_LCD_D0_PIN_MODE                0 /*configure Pin 0 in PORTB as GPIO Pin */
#define PortConf_LCD_D1_PIN_MODE                0 /*configure Pin 1 in PORTB as GPIO Pin */
#define PortConf_LCD_D2_PIN_MODE                0 /*configure Pin 2 in PORTB as GPIO Pin */
#define PortConf_LCD_D3_PIN_MODE                0 /*configure Pin 3 in PORTB as GPIO Pin */
#define PortConf_LCD_D4_PIN_MODE                0 /*configure Pin 4 in PORTB as GPIO Pin */
#define PortConf_LCD_D5_PIN_MODE                0 /*configure Pin 5 in PORTB as GPIO Pin */
#define PortConf_LCD_D6_PIN_MODE                0 /*configure Pin 6 in PORTB as GPIO Pin */
#define PortConf_LCD_D7_PIN_MODE                0 /*configure Pin 7 in PORTB as GPIO Pin */
#define PortConf_LED_PIN_MODE                   0 /*configure Pin 1 in PORTF as GPIO Pin */

/*PORT configured Pin internal resisitor*/
#define PortConf_LCD_RS_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_RW_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_E_PIN_INTERNAL_RESISTOR  ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D0_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D1_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D2_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D3_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D4_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D5_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D6_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LCD_D7_PIN_INTERNAL_RESISTOR ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF
#define PortConf_LED_PIN_INTERNAL_RESISTOR    ( Port_InternalResistorType) PORT_INTERNAL_RESISTOR_OFF

/*PORT configured Pin initial value*/
#define PortConf_LCD_RS_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_RW_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_E_PIN_INITIAL_VALUE           STD_LOW
#define PortConf_LCD_D0_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D1_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D2_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D3_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D4_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D5_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D6_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LCD_D7_PIN_INITIAL_VALUE          STD_LOW
#define PortConf_LED_PIN_INITIAL_VALUE             STD_LOW

/*PORT configured pin analog functionality*/
#define PortConf_LCD_RS_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_RW_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_E_PIN_DIGITAL_MODE          (boolean)TRUE
#define PortConf_LCD_D0_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D1_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D2_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D3_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D4_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D5_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D6_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LCD_D7_PIN_DIGITAL_MODE         (boolean)TRUE
#define PortConf_LED_PIN_DIGITAL_MODE            (boolean)TRUE


 /*******************************************************************************
  *                              Module Data Types                              *
  *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for a PIN */
typedef enum
{
    PORT_INTERNAL_RESISTOR_OFF, PORT_INTERNAL_RESISTOR_PULL_UP, PORT_INTERNAL_RESISTOR_PULL_DOWN
}Port_InternalResistorType;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct
{
    uint8 port_num;
    uint8 pin_num;
    Port_PinDirectionType pin_direction;
    uint8 pin_mode;
    Port_InternalResistorType pin_internal_resistor;
    uint8 pin_initial_value;
    boolean pin_mode_digital;
}Port_ConfigPin;

/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
    Port_ConfigPin Pins[PORT_CONFIGURED_PINS];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
 /* Function for PORT Initialization */
void Port_Init(const Port_ConfigType* ConfigPtr);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif 

