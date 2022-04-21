#include <font.h>
#include <lcdinit.h>
#include <st7789v.h>
#include <stdio.h>
#include <stdlib.h>

#include "fpioa.h"
#include "gpio.h"
#include "sleep.h"
#include "sysctl.h"

int solve() { printf("solve"); }
int main() {
  printf("Hello World\n");
  gpio_def_init();  // gpio初始化
  u8 i, j;
  float t = 0;
  LCD_Init();  // LCD初始化
  LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);
  while (1) {
    LCD_ShowChinese(32, 32, "元", RED, BLACK, 32, 0);
    LCD_ShowChinese(65, 65, "旦", RED, BLACK, 32, 0);
    LCD_ShowChinese(98, 98, "快", RED, BLACK, 32, 0);
    LCD_ShowChinese(131, 131, "乐", RED, BLACK, 32, 0);
    // LCD_ShowChinese(0, 0, "中", RED, WHITE, 16, 0);
    // LCD_ShowString(0, 40, "LCD_W:", RED, WHITE, 16, 0);
    // LCD_ShowIntNum(48, 40, LCD_W, 3, RED, WHITE, 16);
    // LCD_ShowString(80, 40, "LCD_H:", RED, WHITE, 16, 0);
    // LCD_ShowIntNum(128, 40, LCD_H, 3, RED, WHITE, 16);
    // LCD_ShowString(0, 70, "Increaseing Nun:", RED, WHITE, 16, 0);
    // LCD_ShowFloatNum1(128, 70, t, 4, RED, WHITE, 16);
    t += 0.11;
    /*for (j = 0; j < 3; j++) {
      for (i = 0; i < 6; i++) {
        LCD_ShowPicture(40 * i, 120 + j * 40, 40, 40, gImage_1);
      }
    }
  }*/
  }
  return 1;
}
