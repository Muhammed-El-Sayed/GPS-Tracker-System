/******************************************************************************
*
* Module: Gpt
*
* File Name: Gpt_Regs.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - Gpt Driver Registers
*
* Author: Salma Ali
******************************************************************************/
#ifndef GPT_REGS_H
#define GPT_REGS_H


#include "Platform_Types.h"


/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG (*((volatile unsigned long *)0xE000E010))
#define SYSTICK_RELOAD_REG (*((volatile unsigned long *)0xE000E014))
#define SYSTICK_CURRENT_REG (*((volatile unsigned long *)0xE000E018))


/*****************************************************************************
Functions prototypes
*****************************************************************************/
void SysTick_Init(void);
void SysTick_Delay(uint32 delay);
void SysTick_Delay_ms(uint32 delay);




#endif