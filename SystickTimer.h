/******************************************************************************
*
* Module: systickTimer
*
* File Name: systickTimer.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - systickTimer Driver
*
* Author: Salma Ali
******************************************************************************/
#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include "Std_Types.h"

/*****************************************************************************
Functions prototypes
*****************************************************************************/
void SysTick_Start(uint16 delay);
void SysTick_Stop(void);
void SysTick_SetCallBack(void (*Ptr2Func)(void));
void SysTick_Delay_ms(uint16 delay);
#endif