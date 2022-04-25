#include "stm32f10x.h"
#include "IERG3810_clock.h"
#include "IERG3810_NVIC_SetPriorityGroup.h"
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_colour.h"
#include "IERG3810_DrawObstacles.h"
#include "IERG3810_DrawBackground.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_delay.h"
#include "IERG3810_Exti_handler.h"
#include "Global.h"
#include "run.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#define LCD_BASE ((u32)(0x6C000000 | 0x000007FE))
#define LCD ((LCD_TypeDef *) LCD_BASE)
#define LCD_LIGHT_ON GPIOB->BSRR |= 0x00000001;

//Var ini
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

u8 task1HeartBeat ;
u32 arrow_pos = 214;
u32 ps2key;
u32 i;
u32 remain = 240;
u32 remainForCloud = 240;
u32 remainForBird = 150;
u16 j;
u32 sheep = 0;
u32 timeout = 10000;
u32 ps2key = 0;// Keyboard data
u32 ps2count = 0;// keyboard recieved input
u8 ps2dataReady = 0; //1 = correct
u32 ps2PreviousKey = 0;
u32 dataread=0;
u16 buzzer_toggle = 1;
u16 difficulty = 2;	//set speed
u16 random;
int highscore =0;
int score =0;
int page = 0; //chage game scene
typedef enum {
	FALSE = 0, TRUE = 1
} bool;
bool released = FALSE;
char score_display[3] = "";
char hscore_display[3] = "";
const u16 BG_COLOR = 0xFFFF;
const u16 FONT = 0x0000;
const u16 GREY = 0xC5D7;
const u16 ChangeColor = 0xFFE0;



//Functions 

void DS0ON(){
 GPIOB->BRR = 1 << 5;
} 
void DS0OFF(){
	GPIOB->BSRR = 1 << 5;
}
void DS1ON(){
GPIOE->BRR = 1 << 5;
} 
void DS1OFF(){
GPIOE->BSRR = 1 << 5;
}

void Dino(u32 pos_y, u16 bgcolor, u16 custome) {	//draw the dino, where the dino should start at x: 50, y: 50. If need to call without jumping, pass 50 as parameter
	u16 i, j;
	u16 dino_x = 50;
	
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if (run1[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(dino_x + j, pos_y - 25 + i + 50, bgcolor);
		}
	}
}				
void StartScreen(u16 bgcolor){	
		
	IERG3810_TFTLCD_FillRectangle(0,0, 240, 0, 320);
	
	IERG3810_TFTLCD_ShowCharInLine(65,  290, "IERG3810 Project",   20, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(30,  270, "Yeung Tang",         12, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(138, 270, "1155144676",         10, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(30,  250, "Doria Tang",			   12, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(138, 250, "1155126139",				 10, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(75,  230, "Group No: A4",   	   12, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(75,  210, "Chrome Dino",     	 12, BG_COLOR, FONT);
	IERG3810_TFTLCD_ShowCharInLine(50,  130, "Press any to start", 20, BG_COLOR, FONT);
	Dino(10, BG_COLOR, 0);

	while(1){
	//if PS2 keyboard received data correctly
		
		if(ps2count >= 11){			
			if(ps2key){ //press any to start
				break;
			}
			ps2key=0;
			ps2count=0;
			EXTI->PR=1<<11;	
		}
		Delay(100);

	}
	return;
}
void InstructionPage(u16 bgcolor){

	IERG3810_TFTLCD_FillRectangle(BG_COLOR,0, 240, 0, 320);
	
	IERG3810_TFTLCD_ShowCharInLine(50, 280,"Choose difficulty",    20, FONT, BG_COLOR);
	IERG3810_TFTLCD_ShowCharInLine(40, 204,"Press Enter to start", 20, FONT, BG_COLOR);
	IERG3810_TFTLCD_ShowCharInLine(40, 184,"Press Space to jump",  20, FONT, BG_COLOR);
	
	IERG3810_TFTLCD_FillRectangle(0xFBE0,20,200,80,25); //level 1
	IERG3810_TFTLCD_FillRectangle(0xF800,20,200,40,25); //level 2
	IERG3810_TFTLCD_ShowCharInLine(110, 85, "Easy",      5, FONT, 0xFBE0);
	IERG3810_TFTLCD_ShowCharInLine(90, 45, "Difficult", 10, FONT, 0xF800);

	page = 1;
	while(1){
	//if PS2 keyboard received data correctly
		if(ps2count >= 11){
		
					if(ps2key==0x69){								//Pressing number 1
						difficulty = 2;
						IERG3810_TFTLCD_FillRectangle(BG_COLOR,0,240,40,60);
						IERG3810_TFTLCD_FillRectangle(FONT,22,200,82,25);
						IERG3810_TFTLCD_FillRectangle(BG_COLOR,22,200,42,25);
						IERG3810_TFTLCD_FillRectangle(0xFFFF,20,200,80,25);
						IERG3810_TFTLCD_FillRectangle(0xF800,20,200,40,25);
						IERG3810_TFTLCD_ShowCharInLine(110, 85, "Easy",      5, FONT, 0xFFFF);
						IERG3810_TFTLCD_ShowCharInLine(90, 45, "Difficult", 10, FONT, 0xF800);
						released=FALSE;
					
					}
					if(ps2key==0x72){								//Pressing number 2
						difficulty = 3;	

						IERG3810_TFTLCD_FillRectangle(BG_COLOR,0,240,40,60);
						IERG3810_TFTLCD_FillRectangle(BG_COLOR,22,200,82,25);
						IERG3810_TFTLCD_FillRectangle(FONT,22,200,42,25);
						IERG3810_TFTLCD_FillRectangle(0xFBE0,20,200,80,25);
						IERG3810_TFTLCD_FillRectangle(0xFFFF,20,200,40,25);
						IERG3810_TFTLCD_ShowCharInLine(110, 85, "Easy",      5, FONT, 0xFBE0);
						IERG3810_TFTLCD_ShowCharInLine(90, 45, "Difficult", 10, FONT, 0xFFFF);
						released=FALSE;
				
					}
					if(ps2key==0x5A){ //Pressing num 6 0x74 == 6, 0x5A == enter
						break;
					}
			ps2key=0;
			ps2count=0;
			EXTI->PR=1<<11;
		}
		Delay(100);
	}
	return ;
}
void EXTI15_10_IRQHandler(void){
	//students write program here
	if(ps2count>0 && ps2count <9){
		dataread |= ((GPIOC->IDR & (1<<10)) >>10)<<(ps2count-1); //IDR read C port bit 10 data then shift to right most and shift to the currnet bit
	}

	if(page == 2){
		if(ps2key==0x66){								         //pressing space to jump
			j = 50;
			released=FALSE;
		}
	}
	ps2count++;
	ps2key |= dataread;
	dataread=0;
	Delay(10);
	EXTI->PR = 1<<11;
}


void IERG3810_SYSTICK_Init10ms(void){ //systick to smooth the interupt
	SysTick-> CTRL= 0;
	SysTick->LOAD = 800;
	SysTick->CTRL |= 0x3;
}



void drawbox(int x){
	if (x==1){
	
	}
		
	if (x==2){
	
	}
		
	if (x==3){
	
	}
		
	
	for(i=0; i<200; i++) 
		IERG3810_TFTLCD_DrawDot(+i, 10, FONT);
	
	for(i=0; i<200; i++) 
		IERG3810_TFTLCD_DrawDot(10+i, 10, FONT);
	
	for(i=0; i<25; i++) 
		IERG3810_TFTLCD_DrawDot(10+i, 10, FONT);
	
	for(i=0; i<25; i++) 
		IERG3810_TFTLCD_DrawDot(10+i, 10, FONT);
	
}
void Countdown(){
	u16 i;
	for(i = 3; i > 0; i--){
		if(i == 3){
		IERG3810_TFTLCD_SevenSegment(07E0, 80, 80, i);
		Delay(5000000);
		IERG3810_TFTLCD_SevenSegment(FONT, 80, 80, i);
		}
		if(i == 2){
		IERG3810_TFTLCD_SevenSegment(0xFFE0, 80, 80, i);
		Delay(5000000);
		IERG3810_TFTLCD_SevenSegment(FONT, 80, 80, i);
		}
		
		if(i == 1){
		IERG3810_TFTLCD_SevenSegment(0xF800, 80, 80, i);
		Delay(5000000);
		IERG3810_TFTLCD_SevenSegment(FONT, 80, 80, i);
		}
		
	}
}
int Collide(){ //check collide
	if((remain >= 50) && (remain <= 70)){
		if(j < 20) {
			return TRUE; 
		}
	}
	return FALSE;
}
void Gameplay(){

	u16 state = 0;
	void (*obstacle_ptr[])(u16, u16) = {DrawObstacle1, DrawObstacle2, DrawObstacle3};
	page = 2;
	while(1){

		random = 1;
		if(task1HeartBeat >100){
			task1HeartBeat = 0;
			Dino(j,BG_COLOR, 0);
			DrawGround();
			DrawCloud(remainForCloud, FONT);
			DrawBird(remainForBird, FONT);
			(*obstacle_ptr[state])(remain, FONT);
			Delay(1000);
			if(j>0){
				DS0ON();
				DS1OFF();
				Dino(j,FONT,0);
				Dino(0,FONT,0);
				j--;
			}
			else{
				DS0OFF();
				DS1ON();
			}
		
			if(remainForCloud>0){
				remainForCloud--;
				DrawCloud(remainForCloud, ChangeColor);
			}
			if(remainForBird>0){
				remainForBird--;
				DrawBird(remainForBird, ChangeColor);
			}
			if(remainForCloud == 0){
				remainForCloud = 240;
			}
			if(remainForBird == 0){
				remainForBird = 240;
			}
				
			if(remain>0){
				remain -= difficulty;
				(*obstacle_ptr[state])(remain, BG_COLOR);
			}
			else if(remain == 0){
				state = (state+1) % 3;
				remain = 240;
				score++;
			} 
			ps2key=0;
			ps2count=0;
			EXTI->PR=1<<11;	
		}
			Delay(100);
		if (Collide() == TRUE)
			break;
		
	}	
}
void Buzzer(){
	if (((GPIOA->IDR) & (1 << 0)) == (uint32_t)Bit_RESET) { 
		if(buzzer_toggle == 0){
				GPIOB->ODR ^= 1<<8; 
				buzzer_toggle=1; 
				Delay(10000);
		} else{
				GPIOB->ODR ^= 1<<8; 
					buzzer_toggle =0; 
					Delay(10000);
		}
	}
}

void Cal(void){
	int i =0;
	int temp_score = score;
	int htemp_score = score;
	if(htemp_score > highscore || highscore == 0){
		highscore = htemp_score;
		for(i = 0; i < 2; i++){ 
		hscore_display[3-i] = htemp_score%10 + '0';
		htemp_score /= 10;	
	 }
	}else{
		htemp_score = highscore;
		for(i = 0; i < 2; i++){ 
		hscore_display[3-i] = htemp_score%10 + '0';
		htemp_score /= 10;	
	 }
		
	}
	
	for(i = 0; i < 2; i++){
		score_display[3-i] = temp_score%10 + '0';
		temp_score /= 10;	
	 }
	if(score > 20)
		USART_print(2,"WoW, u WIN");
	else
		USART_print(2,"You LOSE HAHA");
}

void ScoreBoard(){
	Cal();
	//IERG3810_TFTLCD_FillRectangle(BG_COLOR,0, 240, 0, 320);
	
	IERG3810_TFTLCD_ShowCharInLine(60, 84,"Your score:", 10, FONT, BG_COLOR);
	IERG3810_TFTLCD_ShowCharInLine(60, 124,"High score:", 10, FONT, BG_COLOR);
	IERG3810_TFTLCD_ShowCharInLine(160, 84, score_display, 4, FONT, BG_COLOR);
	IERG3810_TFTLCD_ShowCharInLine(160, 124, hscore_display, 4, FONT, BG_COLOR);
	IERG3810_TFTLCD_FillRectangle(FONT,150, 20, 124, 20);
	//IERG3810_TFTLCD_FillRectangle(FONT,150, 20, 124, 15);

	Buzzer(); //a smol bippp when lose
	Delay(10000000);
	Buzzer();

}


int main(void){
	IERG3810_clock_tree_init();
	IERG3810_TIM3_PwmInit(9999,72);
	IERG3810_NVIC_SetPriorityGroup(5);
	IERG3810_SYSTICK_Init10ms();
	IERG3810_TFTLCD_Init();
	IERG3810_TFTLCD_SetParameter();
	IERG3810_keyUP_ExtiInit();
	IERG3810_PS2key_ExtiInit();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_USART2_init(36, 9600);
	DS1OFF(); 

	while(1){
		DS1OFF(); 
		DS0OFF();
		score = 0;
		j = 0;
		remain = 240;
		remainForCloud = 240;
		remainForBird = 110;
		IERG3810_TFTLCD_FillRectangle(0,0, 240, 0, 320);
		StartScreen(BG_COLOR);
		IERG3810_TFTLCD_FillRectangle(FONT,0, 240, 0, 320);
		InstructionPage(BG_COLOR);
		IERG3810_TFTLCD_FillRectangle(FONT,0, 240, 0, 320);
		Countdown();
		Gameplay();
		ScoreBoard();
		Delay(30000000);
		memset(score_display, 0, 3); //reset the score
	}
}
