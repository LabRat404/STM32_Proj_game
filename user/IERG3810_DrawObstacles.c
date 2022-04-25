#include "stm32f10x.h"
#include "IERG3810_DrawObstacles.h"

void DrawObstacle1(u16 pos_x, u16 color) {
	u16 i, j;
	
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (obstacle1[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(pos_x - j, i + 25, color);
		}
	}
}

void DrawObstacle2(u16 pos_x, u16 color) {
	u16 i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (obstacle2[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(pos_x - j, i + 25, color);
		}
	}
}

void DrawObstacle3(u16 pos_x, u16 color) {
	u16 i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (obstacle3[i][j] == 0)
				IERG3810_TFTLCD_DrawDot(pos_x - j, i + 25, color);
		}
	}
}