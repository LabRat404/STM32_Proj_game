#include "stm32f10x.h"
#include "IERG3810_delay.h"

void EXTI2_IRQHandler(void){
	u8 i;
	for(i = 0; i < 10; i++){
		GPIOE->BRR = 1 << 5;  //DS1_ON;
		Delay(1000000);
		GPIOE->BSRR = 1 << 5; //DS1_OFF;
		Delay(1000000);
	}
	EXTI->PR = 1 << 0;	//Clear this exception pending bit*/
}

void EXTI0_IRQHandler(void){
	u8 j;
	for(j=0;j<10;j++){
		GPIOB->BRR = 1 << 5;  //DS0_ON;
		Delay(1000000);
		GPIOB->BSRR = 1 << 5; //DS0_OFF;
		Delay(1000000);
	}
	EXTI->PR = 1<<2;							//Clear this exception pending bit
}
void IERG3810_keyUP_ExtiInit(void){ //GPIOA->CRL   		|= 0x00000003
	RCC->APB2ENR 		|= 1<<2; 			//refer to lab1 setup
	GPIOA->CRL   		&= 0xFFFFFFF0;
	GPIOA->CRL   		|= 0x00000003;
	GPIOA->ODR   		|= 0<<0;  //keep PA0 as the same to set high
	RCC->APB2ENR 		|= 0x01;
	AFIO->EXTICR[0] &= 0xFFFFFFF0; //CRL clear bit at PA0
	AFIO->EXTICR[0] |= 0x00000000; //PA0 pin 
	EXTI->IMR				|= 1<<0;			//mask at line 0 interrupt
	EXTI->FTSR			|= 1<<0; 			//falling edge
	//EXTI->RTSR		|= 1<<0; 		 	//rising edge
	
	NVIC->IP[6]			=  0x35; //position 6
	NVIC->ISER[0]		&= ~(1<<6); 
	NVIC->ISER[0]		|= (1<<6); //IRQ6
}
void IERG3810_PS2key_ExtiInit(void){
	//EXTi-11,PC11 clock ,PC10 data poistion 40 
	RCC->APB2ENR 		|= 1<<4; 			//refer to lab1 setup
	GPIOC->CRH   		&= 0xFFFF00FF; //pc 10&11
	GPIOC->CRH   		|= 0x00008800; //pc 10&11
	GPIOC->ODR   		|= 1<<10;  //output port10 data
	GPIOC->ODR   		|= 1<<11;  //output port11 data
	
	RCC->APB2ENR 		|= 0x01;
	AFIO->EXTICR[2] &= 0xFFFF0FFF; //CRH clear bit at PC10,11
	AFIO->EXTICR[2] |= 0x00002000; //PC11 pin 0010
	EXTI->IMR				|= 1<<11;			//mask at line 11 interrupt
	EXTI->FTSR			|= 1<<11; 			//falling edge
	//EXTI->RTSR		|= 1<<11; 		 	//rising edge
	
	NVIC->IP[40]			=  0x35; //IRQ40
	NVIC->ISER[1]		&= ~(1<<8); 
	NVIC->ISER[1]		|= (1<<8); //40 exceed range[0], range+1+8bit
}

void IERG3810_TIM3_PwmInit(u16 arr,u16 psc){
	RCC->APB2ENR |= 1<<3;			//lab1
	GPIOB->CRL &= 0xFF0FFFFF;		//lab1
	GPIOB->CRL |= 0x00B00000;		//lab1
	
	RCC->APB2ENR|=1<<0;					//lab4
	
	AFIO->MAPR&=0xFFFFF3FF;			
	AFIO->MAPR|=3<<10;					
	RCC->APB1ENR|=1<<1;					
	TIM3->ARR =arr;							
	TIM3->PSC=psc;							
	TIM3->CCMR1|=7<<12;				
	TIM3->CCMR1|=1<<11;				
	TIM3->CCMR1|=7<<4;
	TIM3->CCMR1|=1<<3;
	TIM3->CCMR2|=7<<4;
	TIM3->CCMR2|=1<<3;
	TIM3->CCER|=1<<4;						
	TIM3->CCER|=1<<0;
	TIM3->CCER|=1<<8;
	TIM3->CR1=0x0080;						
	TIM3->CR1|=0x01;	
}
