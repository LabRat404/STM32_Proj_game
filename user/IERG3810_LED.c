#include "stm32f10x.h"
#include "IERG3810_LED.h"

void IERG3810_LED_Init() 
{
	//DS0 PB5
	RCC->APB2ENR |= 1 << 3;    //A-E Value
	GPIOB->CRL &= 0xFF0FFFFF;  //0-F Value, Clearing the position value
	GPIOB->CRL |= 0x00300000;  //Add value to that position
	
	//DS1 PE5
	RCC ->APB2ENR |= 1 << 6;
	GPIOE->CRL &= 0xFF0FFFFF; 
	GPIOE->CRL |= 0x00300000; 
	GPIOE -> BSRR = 1 << 5;
}
// put your procedure and code here
