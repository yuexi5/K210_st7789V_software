#ifndef _LCDINIT_H
#define _LCDINIT_H

#include <fpioa.h>
#include <gpio.h>
#include <sleep.h>
#include <st7789v.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysctl.h>

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define LCD_W 240
#define LCD_H 240

#define u8 unsigned char
#define u16 unsigned int

// 17  REST 2
// 21  CS   3
// 22  SCLK 4
// 25  DC   5
// 30  MOSI 6
// 31  BLK  7

//-----------------LCD端口定义----------------
/*
#define LCD_SCLK_Clr() gpio_set_pin(4, GPIO_PV_LOW)  // SCL=SCLK
#define LCD_SCLK_Set() gpio_set_pin(4, GPIO_PV_HIGH)

#define LCD_MOSI_Clr() gpio_set_pin(6, GPIO_PV_LOW)  // SDA=MOSI
#define LCD_MOSI_Set() gpio_set_pin(6, GPIO_PV_HIGH)

#define LCD_RES_Clr() gpio_set_pin(2, GPIO_PV_LOW)  // RES
#define LCD_RES_Set() gpio_set_pin(2, GPIO_PV_HIGH)

#define LCD_DC_Clr() gpio_set_pin(5, GPIO_PV_LOW)  // DC
#define LCD_DC_Set() gpio_set_pin(5, GPIO_PV_HIGH)

#define LCD_BLK_Clr() gpio_set_pin(7, GPIO_PV_LOW)  // BLK
#define LCD_BLK_Set() gpio_set_pin(7, GPIO_PV_HIGH)
*/
void gpio_def_init(void);
void delay_ms(unsigned int ms);                        //不准确延时函数
void LCD_GPIO_Init(void);                              //初始化GPIO
void LCD_Writ_Bus(u8 dat);                             //模拟SPI时序
void LCD_WR_DATA8(u8 dat);                             //写入一个字节
void LCD_WR_DATA(u16 dat);                             //写入两个字节
void LCD_WR_REG(u8 dat);                               //写入一个指令
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);  //设置坐标函数
void LCD_Init(void);                                   // LCD初始化
#endif
