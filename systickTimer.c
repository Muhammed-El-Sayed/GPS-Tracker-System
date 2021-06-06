/******************************************************************************
 *
 * Module:  SysTick Timer
 *
 * File Name:  SysTick Timer.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - SysTick Timer Driver.
 *
 ******************************************************************************/
#include "SystickTimer.h"
#include "SystickTimer_Regs.h"


#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29

/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */

/************************************************************************************
* Service Name: Return_Latitude_Direction
* Parameters (in): buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick Timer configuration to count n miliseconds:
*              - Set the Reload value
*              - Enable SysTick Timer with System clock 16Mhz
*              - Enable SysTick Timer Interrupt and set its priority
static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Description: SysTick Timer ISR
************************************************************************************/
void SysTick_Handler(void)
{
    /* Check if the Timer0_setCallBack is already called */
    if(g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}

/* Call this function to start the systick timer*/
void SysTick_Start(uint16 time)
{
    SYSTICK_CTRL_REG    = 0;                         /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999 * time;              /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;                         /* Clear the Current Register value */
    /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
   
}

/* Call this function to stop the systick timer*/
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
}

/* Description: Function to Setup the SysTick Timer call back*/
void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}


/*call this function to wait for "delay" in milliseconds */
void SysTick_Delay_ms(uint16 delay)
{
    SYSTICK_CTRL_REG    = 0;                         /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999 * delay;         /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;                         /* Clear the Current Register value */
    /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x05;
    while((SYSTICK_CTRL_REG & 0x00010000) == 0); /* wait for the systictimer to finish count and raise the count flag*/
}

//fucntion to make delay in seconds 
void SysTick_Delay_sec(uint16 delay)
{
    for(uint8 i = 0 ; i < delay ; i++)
    {
        SysTick_Delay_ms(1048);   
    }
}



