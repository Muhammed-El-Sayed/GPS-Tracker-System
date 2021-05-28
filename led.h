#ifndef LED_H
#define LED_H


#include "Common_Macros.h"
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"


#define PORTF_NUM (5U)
#define PF1       (1U)


/*Functions*/
void Led_Red_Init(void);

#endif
