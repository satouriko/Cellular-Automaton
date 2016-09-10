#ifndef DRAWHELPER_TOYWAR
#define DRAWHELPER_TOYWAR

#include <cstdio>
#include <unistd.h>

// 清除屏幕 
#define CLEAR() printf("\033[2J") 

// 定位光标 
#define MOVETO(y,x) printf("\033[%d;%dH", (x), (y)) 

// 光标复位 
#define RESET_CURSOR() printf("\033[H") 

// 隐藏光标 
#define HIDE_CURSOR() printf("\033[?25l") 

// 显示光标 
#define SHOW_CURSOR() printf("\033[?25h") 

enum ForeGround { BLACK_F=30, RED_F, GREEN_F, YELLOW_F, BLUE_F, PURPUL_F, DARKGREEN_F, WHITE_F };

enum BackGround { BLACK_B=40, RED_B, GREEN_B, YELLOW_B, BLUE_B, PURPUL_B, DARKGREEN_B, WHITE_B };

// 设置颜色
#define SET_COLOR(c) printf("\033[%dm",(c))

#define RESET_ALL() printf("\033[0m")

#endif
