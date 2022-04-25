#include "stm32f10x.h"
#include "IERG3810_colour.h"

void ColorRed(void)
{
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 10000;
	TIM3->CCR3  = 10000;
}

void ColorYellow(void)
{
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3  = 10000;
}
void ColorGreen(void)
{
	TIM3->CCR1 = 10000;
	TIM3->CCR2 = 0;
	TIM3->CCR3  = 10000;
}
void ColorCyan(void)
{
	TIM3->CCR1 = 10000;
	TIM3->CCR2 = 0;
	TIM3->CCR3  = 0;
}
void ColorBlue(void)
{
	TIM3->CCR1 = 10000;
	TIM3->CCR2 = 10000;
	TIM3->CCR3  = 0;
}

void ColorMagenta(void)
{
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 10000;
	TIM3->CCR3  = 0;
}
void Dark(void)
{
	TIM3->CCR1 = 10000;
	TIM3->CCR2 = 10000;
	TIM3->CCR3  = 10000;
}