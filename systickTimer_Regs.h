
 /******************************************************************************
 *
 * Module: SysctickTimer
 *
 * File Name: SysctickTimer_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - SysctickTimer Driver Registers
 *
 * Author: Salma Ali
 ******************************************************************************/
#ifndef  SYSTICK_TIMER_REGS_H
#define  SYSTICK_TIMER_REGS_H


/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile unsigned long *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile unsigned long *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile unsigned long *)0xE000E018))
/*****************************************************************************
NVIC Registers
*****************************************************************************/
#define NVIC_PRI3_REG             (*((volatile unsigned long *)0xE000E40C))

#endif