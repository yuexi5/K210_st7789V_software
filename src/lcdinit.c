#include <lcdinit.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fpioa.h"
#include "gpio.h"
#include "sleep.h"
#include "sysctl.h"

void gpio_def_init(void) {
  gpio_init();
  fpioa_set_function(17, FUNC_GPIO2);
  gpio_set_drive_mode(2, GPIO_DM_OUTPUT);
  gpio_set_pin(2, GPIO_PV_LOW);
  fpioa_set_function(21, FUNC_GPIO3);
  gpio_set_drive_mode(3, GPIO_DM_OUTPUT);
  gpio_set_pin(3, GPIO_PV_LOW);
  fpioa_set_function(22, FUNC_GPIO4);
  gpio_set_drive_mode(4, GPIO_DM_OUTPUT);
  gpio_set_pin(4, GPIO_PV_LOW);
  fpioa_set_function(25, FUNC_GPIO5);
  gpio_set_drive_mode(5, GPIO_DM_OUTPUT);
  gpio_set_pin(5, GPIO_PV_LOW);
  fpioa_set_function(30, FUNC_GPIO6);
  gpio_set_drive_mode(6, GPIO_DM_OUTPUT);
  gpio_set_pin(6, GPIO_PV_LOW);
  fpioa_set_function(31, FUNC_GPIO7);
  gpio_set_drive_mode(7, GPIO_DM_OUTPUT);
  gpio_set_pin(7, GPIO_PV_HIGH);
}

//不准确延时函数
void delay_ms(unsigned int ms) {
  unsigned int a;
  while (ms) {
    a = 1800;
    while (a--)
      ;
    ms--;
  }
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) {
  u8 i;
  gpio_set_pin(3, GPIO_PV_LOW);
  for (i = 0; i < 8; i++) {
    gpio_set_pin(4, GPIO_PV_LOW);
    if (dat & 0x80) {
      gpio_set_pin(6, GPIO_PV_HIGH);
    } else {
      gpio_set_pin(6, GPIO_PV_LOW);
    }
    gpio_set_pin(4, GPIO_PV_HIGH);
    dat <<= 1;
  }
  gpio_set_pin(3, GPIO_PV_HIGH);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat) { LCD_Writ_Bus(dat); }

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat) {
  LCD_Writ_Bus(dat >> 8);
  LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat) {
  gpio_set_pin(5, GPIO_PV_LOW);  //写命令
  LCD_Writ_Bus(dat);
  gpio_set_pin(5, GPIO_PV_HIGH);  //写数据
}

/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2) {
  if (USE_HORIZONTAL == 0) {
    LCD_WR_REG(0x2a);  //列地址设置
    LCD_WR_DATA(x1);
    LCD_WR_DATA(x2);
    LCD_WR_REG(0x2b);  //行地址设置
    LCD_WR_DATA(y1);
    LCD_WR_DATA(y2);
    LCD_WR_REG(0x2c);  //储存器写
  } else if (USE_HORIZONTAL == 1) {
    LCD_WR_REG(0x2a);  //列地址设置
    LCD_WR_DATA(x1);
    LCD_WR_DATA(x2);
    LCD_WR_REG(0x2b);  //行地址设置
    LCD_WR_DATA(y1 + 80);
    LCD_WR_DATA(y2 + 80);
    LCD_WR_REG(0x2c);  //储存器写
  } else if (USE_HORIZONTAL == 2) {
    LCD_WR_REG(0x2a);  //列地址设置
    LCD_WR_DATA(x1);
    LCD_WR_DATA(x2);
    LCD_WR_REG(0x2b);  //行地址设置
    LCD_WR_DATA(y1);
    LCD_WR_DATA(y2);
    LCD_WR_REG(0x2c);  //储存器写
  } else {
    LCD_WR_REG(0x2a);  //列地址设置
    LCD_WR_DATA(x1 + 80);
    LCD_WR_DATA(x2 + 80);
    LCD_WR_REG(0x2b);  //行地址设置
    LCD_WR_DATA(y1);
    LCD_WR_DATA(y2);
    LCD_WR_REG(0x2c);  //储存器写
  }
}

/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Init(void) {
  gpio_set_pin(2, GPIO_PV_LOW);
  delay_ms(100);
  gpio_set_pin(2, GPIO_PV_HIGH);
  delay_ms(100);
  gpio_set_pin(7, GPIO_PV_HIGH);
  delay_ms(100);
  //************* Start Initial Sequence **********//
  LCD_WR_REG(0x11);  // Sleep out
  delay_ms(120);     // Delay 120ms
  //************* Start Initial Sequence **********//
  LCD_WR_REG(0x11);  // Sleep out
  delay_ms(120);     // Delay 120ms
  //************* Start Initial Sequence **********//
  LCD_WR_REG(0x36);
  if (USE_HORIZONTAL == 0)
    LCD_WR_DATA8(0x00);
  else if (USE_HORIZONTAL == 1)
    LCD_WR_DATA8(0xC0);
  else if (USE_HORIZONTAL == 2)
    LCD_WR_DATA8(0x70);
  else
    LCD_WR_DATA8(0xA0);

  LCD_WR_REG(0x3A);
  LCD_WR_DATA8(0x05);

  LCD_WR_REG(0xB2);
  LCD_WR_DATA8(0x0C);
  LCD_WR_DATA8(0x0C);
  LCD_WR_DATA8(0x00);
  LCD_WR_DATA8(0x33);
  LCD_WR_DATA8(0x33);

  LCD_WR_REG(0xB7);
  LCD_WR_DATA8(0x35);

  LCD_WR_REG(0xBB);
  LCD_WR_DATA8(0x32);  // Vcom=1.35V

  LCD_WR_REG(0xC2);
  LCD_WR_DATA8(0x01);

  LCD_WR_REG(0xC3);
  LCD_WR_DATA8(0x15);  // GVDD=4.8V  颜色深度

  LCD_WR_REG(0xC4);
  LCD_WR_DATA8(0x20);  // VDV, 0x20:0v

  LCD_WR_REG(0xC6);
  LCD_WR_DATA8(0x0F);  // 0x0F:60Hz

  LCD_WR_REG(0xD0);
  LCD_WR_DATA8(0xA4);
  LCD_WR_DATA8(0xA1);

  LCD_WR_REG(0xE0);
  LCD_WR_DATA8(0xD0);
  LCD_WR_DATA8(0x08);
  LCD_WR_DATA8(0x0E);
  LCD_WR_DATA8(0x09);
  LCD_WR_DATA8(0x09);
  LCD_WR_DATA8(0x05);
  LCD_WR_DATA8(0x31);
  LCD_WR_DATA8(0x33);
  LCD_WR_DATA8(0x48);
  LCD_WR_DATA8(0x17);
  LCD_WR_DATA8(0x14);
  LCD_WR_DATA8(0x15);
  LCD_WR_DATA8(0x31);
  LCD_WR_DATA8(0x34);

  LCD_WR_REG(0xE1);
  LCD_WR_DATA8(0xD0);
  LCD_WR_DATA8(0x08);
  LCD_WR_DATA8(0x0E);
  LCD_WR_DATA8(0x09);
  LCD_WR_DATA8(0x09);
  LCD_WR_DATA8(0x15);
  LCD_WR_DATA8(0x31);
  LCD_WR_DATA8(0x33);
  LCD_WR_DATA8(0x48);
  LCD_WR_DATA8(0x17);
  LCD_WR_DATA8(0x14);
  LCD_WR_DATA8(0x15);
  LCD_WR_DATA8(0x31);
  LCD_WR_DATA8(0x34);
  LCD_WR_REG(0x21);

  LCD_WR_REG(0x29);
}
