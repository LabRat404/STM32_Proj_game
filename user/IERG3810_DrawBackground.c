#include "stm32f10x.h"
#include "IERG3810_DrawBackground.h"
#include "IERG3810_TFTLCD.h"
#include "decoration.h"

void DrawCloud(u16 pos_x, u16 color){
	u16 i, j;
	
	for(i = 0; i < 12; i++){
		for(j = 0; j < 20; j++){
			if(cloud[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(pos_x - j, i + 180, color);
		}
	}
}

void DrawCloud2(u16 pos_x, u16 color){
	u16 i, j;
	
	for(i = 0; i < 12; i++){
		for(j = 0; j < 20; j++){
			if(cloud[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(pos_x - j, i + 200, color);
		}
	}
}

void DrawGround(){
	 u16 i;
	 static u16 counter_x;
	 static u16 counter_y;
	 const u16 BLACK = 0x0000;
	 const u16 WHITE = 0xFFFF;
	 const u16 GREY = 0xC5D7;
	 u16 color[5] = {WHITE, GREY, WHITE, BLACK, WHITE};
	 
	 IERG3810_TFTLCD_FillRectangle(GREY, 0, 240, 20, 5);
	 for(i = 0; i < 240; i++){
		IERG3810_TFTLCD_DrawDot(counter_x, counter_y, color[i%5]);
		 counter_x = (counter_x + 1) % 240;
		 if(counter_y == 43) counter_y = 38;
	 }
}