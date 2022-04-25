#include "stm32f10x.h"
#include "IERG3810_KEY.h"

void IERG3810_KEY_Init() 
{
	//KEY2 PE2
	RCC->APB2ENR |= 1 << 6; 
	GPIOE->CRL &= 0xFFFFF0FF; 
	GPIOE->CRL |= 0x00000300; 
	GPIOE->BSRR |= 1 << 2; 
	
	//KEY1 PE3
	RCC ->APB2ENR |= 1 << 6;
	GPIOE->CRL &= 0xFFFF0FFF; 
	GPIOE->CRL |= 0x00003000; 
	GPIOE->BSRR = 1 << 3;
	
	//KEYUP PA0
	RCC->APB2ENR |= 1 << 2;    
	GPIOA->CRL &= 0xFFFFFFF0;  
	GPIOA->CRL |= 0x00000003;
}
// put your procedure and code here
