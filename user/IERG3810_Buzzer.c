#include "stm32f10x.h"
#include "IERG3810_Buzzer.h"

void IERG3810_Buzzer_Init()
{
	//BUZZER PB8
	RCC->APB2ENR |= 1 << 3;    
	GPIOB->CRH &= 0xFFFFFFF0; 
	GPIOB->CRH |= 0x00000003; 
	GPIOB -> BSRR = 1 << 8;
}

// put your procedure and code here
