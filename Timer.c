#include "Timer.h"

void SysTick_Init(void){
	SYSTICK_CTRL_REG = 0; // 1) disable SysTick during setup 
	SYSTICK_RELOAD_REG = 0x00FFFFFF; // 2) maximum reload value NVIC_ST_CURRENT_R = 0; // 3) any write to CURRENT clears it NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}

// The delay parameter is in units of the 80 MHz core clock(12.5 ns)
void SysTick_Delay(uint32 delay){
	SYSTICK_RELOAD_REG = delay-1; // number of counts
	SYSTICK_CURRENT_REG = 0; // any value written to CURRENT clears 
	while((SYSTICK_CTRL_REG & 0x00010000) == 0); // wait for flag
}

// Call this routine to wait for delay "delay" melliseconds
void SysTick_Delay_ms(uint32 delay){ 
	uint32 i;
	for(i=0; i < delay; i++){
		SysTick_Wait(80000); // wait 10ms 
}