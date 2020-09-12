
/**********************************************************************
* @file		video_memory.c
* @brief	显示中间层，为LCD驱动提供显存
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/

#include "lpc17xx_libcfg.h"
#include "stdio.h"
#include "video_memory.h"
#include "string.h"

uint8_t Lcd_Buff[LCD_Y_PAGE][LCD_X_PIXEL];


/*********************************************************************//**
 * @brief 		清除显存
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Lcd_Buff(void)
{
	memset(Lcd_Buff, 0x00, LCD_Y_PAGE*LCD_X_PIXEL);
}

/*********************************************************************//**
 * @brief 		清除任意区域的显存
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Will_Lcd_Buff(uint16_t x, uint16_t y, uint16_t width, uint16_t hight)
{
	int i = 0, j = 0;
	for(i = 0; i<hight/8; i++)
	{
		for(j=0; j<width; j++)
		{
			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//判断写入范围是否超过显存大小
			{
				Lcd_Buff[y+i][x+j] = 0x00;
			}
		}
	}
}

/*********************************************************************//**
 * @brief 		清除菜单项显示区
 				菜单项显示区是4~15行
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Lcd_Buff_Menu(void)
{
	int i = 0;
	for(i=4; i<16; i++)
		memset(Lcd_Buff[i], 0x00, LCD_X_PIXEL);
}

/*********************************************************************//**
 * @brief 		清除报警显示区
 				报警显示区是1~2行
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Lcd_Buff_Alarm(void)
{
	int i = 0;
	for(i=1; i<3; i++)
		memset(Lcd_Buff[i], 0x00, LCD_X_PIXEL);

}

/*********************************************************************//**
 * @brief 		清除状态显示区
 				状态显示区是17~18行
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Lcd_Buff_Status(void)
{
	int i = 0;
	for(i=17; i<19; i++)
		memset(Lcd_Buff[i], 0x00, LCD_X_PIXEL);

}

/*********************************************************************//**
 * @brief 		显示8*8或8*16的ASC字符
 * @param[in] 	x:列坐标
 				y:页坐标
 				lib:使用的字符集
 				str:要显示的字符
 				width：字符宽，单位像素
 				hight：字符高，单位像素
 				flag：显示模式，正色和反色
 * @return 		
 **********************************************************************/
void Dis_Asc_Char(uint16_t x, uint16_t y, const uint8_t *lib, uint8_t * str, uint8_t width, uint8_t hight, enum DISPLAY_MODE flag)
{
	uint16_t lib_start = 0;
	int i=0, j=0;

	//lib_start = *str;
	lib_start = (*str-0x20)*(width/8)*hight;	//计算字符在字符码表中的起始位置

	for(i=0; i<(hight/8); i++)		//Y方向有多少页数据
	{
		for(j=0; j<width; j++)		//X方向有多少像素
		{
			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//判断写入范围是否超过显存大小
			{
				if(flag == PURECOLOR)
					Lcd_Buff[y+i][x+j] = lib[lib_start + i*width + j];			//将字模块写入显存
				else
					Lcd_Buff[y+i][x+j] = ~lib[lib_start + i*width + j];
			}
			else
			{
				//超出的数据不写入显存
			}
		}
	}
}

/*********************************************************************//**
 * @brief 		显示ASC字符串
 * @param[in] 	x:列坐标
 				y:页坐标
 				lib:使用的字符集
 				str:要显示的字符串
 				width：字符宽，单位像素
 				hight：字符高，单位像素
 				flag：显示模式，正色和反色
 * @return 		
 **********************************************************************/
void Dis_Asc_Str(uint16_t x, uint16_t y, const uint8_t *lib, uint8_t * str, uint8_t width, uint8_t hight, enum DISPLAY_MODE flag)
{
	uint16_t str_len = 0;
	uint16_t i = 0;

	str_len = strlen((const char *)str);
	for(i=0; i<str_len; i++)
	{
		Dis_Asc_Char(x+(i*8), y, lib, str+i, width, hight, flag);
	}
}

/*********************************************************************//**
 * @brief 		显示一个图像，图像的高必需是8的整数倍
 * @param[in] 	x:列坐标
 				y:页坐标
 				ptr:要显示的图像
 				width：字符宽，单位像素
 				hight：字符高，单位像素
 				flag：显示模式，正色和反色
 * @return 		
 **********************************************************************/
void Dis_Image(uint16_t x, uint16_t y, const uint8_t *ptr, uint16_t width, uint16_t hight, enum DISPLAY_MODE flag)
{
	int i=0, j=0;

	for(i=0; i<(hight/8); i++)		//Y方向有多少页数据
	{
		for(j=0; j<width; j++)		//X方向有多少像素
		{

			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//判断写入范围是否超过显存大小
			{
				if(flag == PURECOLOR)
					Lcd_Buff[y+i][x+j] = ptr[i*width + j];			//将字模块写入显存
				else
					Lcd_Buff[y+i][x+j] = ~ptr[i*width + j];
			}
			else
			{
				//超出的数据不写入显存
			}
		}
	}
}

/*********************************************************************//**
 * @brief		显示一个16*16的图片串，可以用于显示汉字串
 * @param[in]	x:列坐标
				y:页坐标
				str:要显示的字符串
				flag：显示模式，正色和反色
 * @return		
 **********************************************************************/
void Dis_16_16_Str(uint16_t x, uint16_t y, const uint8_t **str, enum DISPLAY_MODE flag)
{
	uint16_t i = 0;

	while( *(str+i) != NULL)
	{
		Dis_Image(x+(i*16), y, str[i], 16, 16, flag);
		i ++;
	}
}

/*********************************************************************//**
 * @brief		画一条线
 * @param[in]	x:列坐标
				y:页坐标
				str:要显示的字符串
				flag：显示模式，正色和反色
 * @return		
 **********************************************************************/
void Dis_line(uint16_t x, uint16_t y, uint16_t width, enum DISPLAY_MODE flag)
{
	uint16_t i = 0;

	for(i=0; i<width; i++)
	{
		if(flag == PURECOLOR)
			Lcd_Buff[y][x+i] = (0x18);
		else
			Lcd_Buff[y][x+i] = ~(0x18);
	}
}

/*********************************************************************//**
 * @brief		画一个矩形
 * @param[in]	x:列坐标
				y:页坐标
				width：矩形的宽
				hight：矩形的高
				flag：显示模式，正色和反色
 * @return		
 **********************************************************************/
void Dis_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, enum DISPLAY_MODE flag)
{
	int i = 0, j = 0;
	int page = (hight/8);

	for (i=0; i<width; i++)
	{
		for(j=0; j<page; j++)
		{
			if( (i == 0) && (j == 0) )
				Lcd_Buff[y+j][x+i] = (0xF8);
			if( (i == width-1) && (j == 0) )
				Lcd_Buff[y+j][x+i] = (0xF8);
			if( (i == 0) && (j == page-1) )
				Lcd_Buff[y+j][x+i] = (0x1F);
			if( (i == width-1) && (j == page-1) )
				Lcd_Buff[y+j][x+i] = (0x1F);

			if( ((i == 0) || (i == width-1)) && (j != 0) && (j != page-1) )
				Lcd_Buff[y+j][x+i] = (0xFF);

			if( (i != 0) && (i != width-1) && (j == 0) )
				Lcd_Buff[y+j][x+i] = (0x08);

			if( (i != 0) && (i != width-1) && (j == page-1) )
				Lcd_Buff[y+j][x+i] = (0x10);
		}
	}
}



