#include "led.h"

/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
     volatile uint32 delay = 0;
     SYSCTL_REGCGC2_REG |= (1<<PORTF_NUM);
     delay = SYSCTL_REGCGC2_REG;
     GPIO_PORTF_AMSEL_REG &= ~(1<<PF1);      /* Disable Analog on PF1 */
     GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
     GPIO_PORTF_DIR_REG   |= (1<<PF1);       /* Configure PF1 as output pin */
     GPIO_PORTF_AFSEL_REG &= ~(1<<PF1);      /* Disable alternative function on PF1 */
     GPIO_PORTF_DEN_REG   |= (1<<PF1);       /* Enable Digital I/O on PF1 */
     GPIO_PORTF_DATA_REG  &= ~(1<<PF1);      /* Clear bit 1 in Data regsiter to turn off the led */
  
}
