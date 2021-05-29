/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 ******************************************************************************/
#include "led.h"

/*********************************************************************************************/
void LED_setOn(void)
{
    Dio_WriteChannel(DioConf_LED_PIN_ID_INDEX,LED_ON);  /* LED ON */
}

/*********************************************************************************************/
void LED_setOff(void)
{
    Dio_WriteChannel(DioConf_LED_PIN_ID_INDEX,LED_OFF); /* LED OFF */
}
