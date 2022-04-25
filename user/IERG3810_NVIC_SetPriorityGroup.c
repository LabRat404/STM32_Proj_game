#include "stm32f10x.h"

void IERG3810_NVIC_SetPriorityGroup(u8 prigroup){
	u32 temp, temp1;
	temp1 = prigroup & 0x00000007;	//only concern 3 bits
	temp1 <<= 8;		//'Why'
	temp = SCB->AIRCR;	//ARM DDI0337E page 8-22
	temp &= 0x0000F8FF;	//ARM DDI0337E page 8-22
	temp |= 0x05FA0000;	//ARM DDI0337E page 8-22
	temp |= temp1;
	SCB->AIRCR = temp;
}
