#ifndef __IERG3810_EXTI_HANDLER_H
#define __IERG3810_EXTI_HANDLER_H
#include "stm32f10x.h"

void EXTI2_IRQHandler(void);
void EXTI0_IRQHandler(void);
void IERG3810_keyUP_ExtiInit(void);
void IERG3810_PS2key_ExtiInit(void);
void IERG3810_TIM3_PwmInit(u16 arr,u16 psc);

#endif
