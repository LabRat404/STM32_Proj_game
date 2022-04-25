#include "stm32f10x.h"
#include "IERG3810_USART.h"

void IERG3810_USART2_init(u32 pclk1, u32 bound)
{
	//USART2
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk1*1000000)/(bound*16);
	mantissa = temp;
	fraction = (temp-mantissa)*16;
	mantissa <<= 4;
	mantissa += fraction;
	RCC->APB2ENR |= 1<<2;
	RCC->APB1ENR |= 1<<17;
	GPIOA->CRL &= 0xFFFF00FF; //PA2, PA3 alternate func
	GPIOA->CRL |= 0x00008B00; //PA2, PA3 alternate func
	RCC->APB1RSTR |= 1<<17;
	RCC->APB1RSTR &= ~(1<<17);
	USART2->BRR = mantissa;
	USART2->CR1 |= 0x2008;
}

void IERG3810_USART1_init(u32 pclk1, u32 bound)
{
	//USART1
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk1*1000000)/(bound*16);
	mantissa = temp;
	fraction = (temp-mantissa)*16;
	mantissa <<= 4;
	mantissa += fraction;
	RCC->APB2ENR |= 1<<2; //Port A
	RCC->APB2ENR |= 1<<14; //USART1
	GPIOA->CRH &= 0xFFFFFF00F; // shift to pin 9, pin 10
	GPIOA->CRH |= 0x0000008B0; // 
	RCC->APB2RSTR |= 1<<14; //USART1
	RCC->APB2RSTR &= ~(1<<14);
	USART2->BRR = mantissa;
	USART2->CR1 |= 0x2008;
}

void USART_print(u8 USARTport, char *st) 
{
	u8 i=0; 
	while (st[i] != 0x00) {
		//if(USARTport == 1) USART1->DR = st[i]; //parse to string array
		//if(USARTport == 2) USART2->DR = st[i];
		if(USARTport == 1) 
		{
				USART1->DR = st[i];
				while(!((USART1->SR)&(1<<7)));
		}
		if(USARTport == 2)
		{
				USART2->DR = st[i];
				while(!((USART2->SR)&(1<<7)));
		}
		//Delay(50000);
		if(i == 255) break;
		i++;
	}
}
