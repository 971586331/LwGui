

#ifndef VIDEO_MEMORY_H
#define VIDEO_MEMORY_H

#include "lpc17xx_libcfg.h"
#include "stdint.h"

#define LCD_X_PIXEL (240)
#define LCD_Y_PIXEL	(160)
#define LCD_Y_PAGE	(20)

//显示模式
enum DISPLAY_MODE
{
	PURECOLOR,	//正色显示
	INVERTED,	//反色显示
};

void Clear_Lcd_Buff(void);
void Clear_Will_Lcd_Buff(uint16_t x, uint16_t y, uint16_t width, uint16_t hight);
void Clear_Lcd_Buff_Menu(void);
void Clear_Lcd_Buff_Alarm(void);
void Clear_Lcd_Buff_Status(void);


void Dis_Asc_Char(uint16_t x, uint16_t y, const uint8_t *lib, uint8_t * str, uint8_t width, uint8_t hight, enum DISPLAY_MODE flag);
void Dis_Asc_Str(uint16_t x, uint16_t y, const uint8_t *lib, uint8_t * str, uint8_t width, uint8_t hight, enum DISPLAY_MODE flag);
void Dis_Image(uint16_t x, uint16_t y, const uint8_t *ptr, uint16_t width, uint16_t hight, enum DISPLAY_MODE flag);
void Dis_16_16_Str(uint16_t x, uint16_t y, const uint8_t **str, enum DISPLAY_MODE flag);
void Dis_line(uint16_t x, uint16_t y, uint16_t width, enum DISPLAY_MODE flag);
void Dis_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, enum DISPLAY_MODE flag);

extern uint8_t Lcd_Buff[LCD_Y_PAGE][LCD_X_PIXEL];


#endif


