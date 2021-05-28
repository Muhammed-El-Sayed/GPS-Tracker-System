/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Salma Ali
 ******************************************************************************/
#include "port.h"
#include "Port_Regs.h"
/* PB structure used with Port_Init */
 const Port_ConfigType Port_Configuration = {
                                            PortConf_LCD_RS_PORT_NUM,PortConf_LCD_RS_PIN_NUM,PortConf_LCD_RS_PIN_DIRECTION,PortConf_LCD_RS_PIN_MODE,
                                            PortConf_LCD_RS_PIN_INTERNAL_RESISTOR,PortConf_LCD_RS_PIN_INITIAL_VALUE,PortConf_LCD_RS_PIN_DIGITAL_MODE,

                                            PortConf_LCD_RW_PORT_NUM,PortConf_LCD_RW_PIN_NUM,PortConf_LCD_RW_PIN_DIRECTION,PortConf_LCD_RW_PIN_MODE,
                                            PortConf_LCD_RW_PIN_INTERNAL_RESISTOR,PortConf_LCD_RW_PIN_INITIAL_VALUE, PortConf_LCD_RW_PIN_DIGITAL_MODE,

                                            PortConf_LCD_E_PORT_NUM,PortConf_LCD_E_PIN_NUM,PortConf_LCD_E_PIN_DIRECTION,PortConf_LCD_E_PIN_MODE,
                                            PortConf_LCD_E_PIN_INTERNAL_RESISTOR,PortConf_LCD_E_PIN_INITIAL_VALUE,PortConf_LCD_E_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D0_PORT_NUM,PortConf_LCD_D0_PIN_NUM,PortConf_LCD_D0_PIN_DIRECTION,PortConf_LCD_D0_PIN_MODE,
                                            PortConf_LCD_D0_PIN_INTERNAL_RESISTOR,PortConf_LCD_D0_PIN_INITIAL_VALUE,PortConf_LCD_D0_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D1_PORT_NUM,PortConf_LCD_D1_PIN_NUM,PortConf_LCD_D1_PIN_DIRECTION,PortConf_LCD_D1_PIN_MODE,
                                            PortConf_LCD_D1_PIN_INTERNAL_RESISTOR,PortConf_LCD_D1_PIN_INITIAL_VALUE,PortConf_LCD_D1_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D2_PORT_NUM,PortConf_LCD_D2_PIN_NUM,PortConf_LCD_D2_PIN_DIRECTION,PortConf_LCD_D2_PIN_MODE,
                                            PortConf_LCD_D2_PIN_INTERNAL_RESISTOR,PortConf_LCD_D2_PIN_INITIAL_VALUE,PortConf_LCD_D2_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D3_PORT_NUM,PortConf_LCD_D3_PIN_NUM,PortConf_LCD_D3_PIN_DIRECTION,PortConf_LCD_D3_PIN_MODE,
                                            PortConf_LCD_D3_PIN_INTERNAL_RESISTOR,PortConf_LCD_D3_PIN_INITIAL_VALUE,PortConf_LCD_D3_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D4_PORT_NUM,PortConf_LCD_D4_PIN_NUM,PortConf_LCD_D4_PIN_DIRECTION,PortConf_LCD_D4_PIN_MODE,
                                            PortConf_LCD_D4_PIN_INTERNAL_RESISTOR,PortConf_LCD_D4_PIN_INITIAL_VALUE,PortConf_LCD_D4_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D5_PORT_NUM,PortConf_LCD_D5_PIN_NUM,PortConf_LCD_D5_PIN_DIRECTION,PortConf_LCD_D5_PIN_MODE,
                                            PortConf_LCD_D5_PIN_INTERNAL_RESISTOR,PortConf_LCD_D5_PIN_INITIAL_VALUE,PortConf_LCD_D5_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D6_PORT_NUM,PortConf_LCD_D6_PIN_NUM,PortConf_LCD_D6_PIN_DIRECTION,PortConf_LCD_D6_PIN_MODE,
                                            PortConf_LCD_D6_PIN_INTERNAL_RESISTOR,PortConf_LCD_D6_PIN_INITIAL_VALUE,PortConf_LCD_D6_PIN_DIGITAL_MODE,

                                            PortConf_LCD_D7_PORT_NUM,PortConf_LCD_D7_PIN_NUM,PortConf_LCD_D7_PIN_DIRECTION,PortConf_LCD_D7_PIN_MODE,
                                            PortConf_LCD_D7_PIN_INTERNAL_RESISTOR,PortConf_LCD_D7_PIN_INITIAL_VALUE,PortConf_LCD_D7_PIN_DIGITAL_MODE


};
static const Port_ConfigPin* Port_PortPins=NULL_PTR;
void Port_Init(const Port_ConfigType* ConfigPtr)
{

        /*
         * point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Port_PortPins = ConfigPtr->Pins; /* address of the first pins structure --> pins[0] */

        volatile uint32* Port_Ptr=NULL_PTR; /* point to the required Port Registers base address */
        volatile uint32 delay = 0;
        for (uint8 PinId = 0; PinId < PORT_CONFIGURED_PINS; PinId++)
        {
            switch (Port_PortPins[PinId].port_num)
            {
            case  0: Port_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  1: Port_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  2: Port_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  3: Port_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  4: Port_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  5: Port_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            }
            /* Enable clock for PORT and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= (1 << Port_PortPins[PinId].port_num);
            delay = SYSCTL_REGCGC2_REG;

            /*unlock the GPIOCR register, Set the corresponding bit in GPIOCR register to allow changes on this pin */
            if (((Port_PortPins[PinId].port_num == 3) && (Port_PortPins[PinId].pin_num == 7)) || ((Port_PortPins[PinId].port_num == 5) && (Port_PortPins[PinId].pin_num == 0))) /* PD7 or PF0 */
            {
                /* Unlock the GPIOCR register */
                *(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
                /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_COMMIT_REG_OFFSET), Port_PortPins[PinId].pin_num);
            }
            else if ((Port_PortPins[PinId].port_num == 2) && (Port_PortPins[PinId].pin_num <= 3)) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            /*Disable or Enable Alternative Function based on Pin Mode*/
            if (Port_PortPins[PinId].pin_mode == 0)  /*if pin is used as GPIO */
            {
                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortPins[PinId].pin_num);
            }
            else /*if pin is used for any other functionality*/
            {
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortPins[PinId].pin_num);
            }

            /*set the pin mode by inserting the PMCx bits inside GPIOPCTL register */
            *(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Port_PortPins[PinId].pin_mode << (Port_PortPins[PinId].pin_num * 4));

            /*set the pin direction and set internal pullup/internal pulldown/disable in case of input pin or intial value in case of output pin*/
            if (Port_PortPins[PinId].pin_direction == PORT_PIN_OUT)
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DIR_REG_OFFSET), Port_PortPins[PinId].pin_num);
                if (Port_PortPins[PinId].pin_initial_value == STD_HIGH)
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DATA_REG_OFFSET), Port_PortPins[PinId].pin_num);
                }
                else
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DATA_REG_OFFSET), Port_PortPins[PinId].pin_num);
                }
            }
            else if (Port_PortPins[PinId].pin_direction == PORT_PIN_IN)
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DIR_REG_OFFSET), Port_PortPins[PinId].pin_num);

                if (Port_PortPins[PinId].pin_internal_resistor == PORT_INTERNAL_RESISTOR_PULL_UP)
                {  /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PortPins[PinId].pin_num);
                }
                else if (Port_PortPins[PinId].pin_internal_resistor == PORT_INTERNAL_RESISTOR_PULL_DOWN)
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PortPins[PinId].pin_num);
                }
                else
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PortPins[PinId].pin_num);
                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PortPins[PinId].pin_num);
                }
            }
            else
            {
                /* Do Nothing */
            }
            if (Port_PortPins[PinId].pin_mode_digital == FALSE)
            {
                /* Ser the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortPins[PinId].pin_num);
                /* Set the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortPins[PinId].pin_num);
            }
            else
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortPins[PinId].pin_num);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortPins[PinId].pin_num);
            }



        }
    
}
