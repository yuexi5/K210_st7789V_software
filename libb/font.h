/*********************************************************************************************************************
 *取模字符库：阴极、逐行式、顺向、点阵16
 *汉字字符注意取模长宽大小
 ********************************************************************************************************************/

#ifndef _FONT_H
#define _FONT_H
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//#define uint8 uint8_t
//#define int8 int8_t
//#define uint16 uint16_t
//#define int16 int16_t
//#define uint32 uint32_t
//#define int32 int32_t

extern const unsigned char ascii_1206[][12];

extern const unsigned char ascii_1608[][16];

extern const unsigned char ascii_2412[][48];

extern const unsigned char ascii_3216[][64];

typedef struct {
  unsigned char Index[2];
  unsigned char Msk[24];
} typFNT_GB12;

extern const typFNT_GB12 tfont12[96];

typedef struct {
  unsigned char Index[2];
  unsigned char Msk[32];
} typFNT_GB16;

extern const typFNT_GB16 tfont16[128];
typedef struct {
  unsigned char Index[2];
  unsigned char Msk[72];
} typFNT_GB24;

extern const typFNT_GB24 tfont24[192];

typedef struct {
  unsigned char Index[2];
  unsigned char Msk[128];
} typFNT_GB32;

extern const typFNT_GB32 tfont32[512];

#endif
