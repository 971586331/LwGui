
/**********************************************************************
* @file		video_memory.c
* @brief	��ʾ�м�㣬ΪLCD�����ṩ�Դ�
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
 * @brief 		����Դ�
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Clear_Lcd_Buff(void)
{
	memset(Lcd_Buff, 0x00, LCD_Y_PAGE*LCD_X_PIXEL);
}

/*********************************************************************//**
 * @brief 		�������������Դ�
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
			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//�ж�д�뷶Χ�Ƿ񳬹��Դ��С
			{
				Lcd_Buff[y+i][x+j] = 0x00;
			}
		}
	}
}

/*********************************************************************//**
 * @brief 		����˵�����ʾ��
 				�˵�����ʾ����4~15��
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
 * @brief 		���������ʾ��
 				������ʾ����1~2��
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
 * @brief 		���״̬��ʾ��
 				״̬��ʾ����17~18��
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
 * @brief 		��ʾ8*8��8*16��ASC�ַ�
 * @param[in] 	x:������
 				y:ҳ����
 				lib:ʹ�õ��ַ���
 				str:Ҫ��ʾ���ַ�
 				width���ַ�����λ����
 				hight���ַ��ߣ���λ����
 				flag����ʾģʽ����ɫ�ͷ�ɫ
 * @return 		
 **********************************************************************/
void Dis_Asc_Char(uint16_t x, uint16_t y, const uint8_t *lib, uint8_t * str, uint8_t width, uint8_t hight, enum DISPLAY_MODE flag)
{
	uint16_t lib_start = 0;
	int i=0, j=0;

	//lib_start = *str;
	lib_start = (*str-0x20)*(width/8)*hight;	//�����ַ����ַ�����е���ʼλ��

	for(i=0; i<(hight/8); i++)		//Y�����ж���ҳ����
	{
		for(j=0; j<width; j++)		//X�����ж�������
		{
			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//�ж�д�뷶Χ�Ƿ񳬹��Դ��С
			{
				if(flag == PURECOLOR)
					Lcd_Buff[y+i][x+j] = lib[lib_start + i*width + j];			//����ģ��д���Դ�
				else
					Lcd_Buff[y+i][x+j] = ~lib[lib_start + i*width + j];
			}
			else
			{
				//���������ݲ�д���Դ�
			}
		}
	}
}

/*********************************************************************//**
 * @brief 		��ʾASC�ַ���
 * @param[in] 	x:������
 				y:ҳ����
 				lib:ʹ�õ��ַ���
 				str:Ҫ��ʾ���ַ���
 				width���ַ�����λ����
 				hight���ַ��ߣ���λ����
 				flag����ʾģʽ����ɫ�ͷ�ɫ
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
 * @brief 		��ʾһ��ͼ��ͼ��ĸ߱�����8��������
 * @param[in] 	x:������
 				y:ҳ����
 				ptr:Ҫ��ʾ��ͼ��
 				width���ַ�����λ����
 				hight���ַ��ߣ���λ����
 				flag����ʾģʽ����ɫ�ͷ�ɫ
 * @return 		
 **********************************************************************/
void Dis_Image(uint16_t x, uint16_t y, const uint8_t *ptr, uint16_t width, uint16_t hight, enum DISPLAY_MODE flag)
{
	int i=0, j=0;

	for(i=0; i<(hight/8); i++)		//Y�����ж���ҳ����
	{
		for(j=0; j<width; j++)		//X�����ж�������
		{

			if( ((y+i) < LCD_Y_PAGE) && ((x+j) < LCD_X_PIXEL) )		//�ж�д�뷶Χ�Ƿ񳬹��Դ��С
			{
				if(flag == PURECOLOR)
					Lcd_Buff[y+i][x+j] = ptr[i*width + j];			//����ģ��д���Դ�
				else
					Lcd_Buff[y+i][x+j] = ~ptr[i*width + j];
			}
			else
			{
				//���������ݲ�д���Դ�
			}
		}
	}
}

/*********************************************************************//**
 * @brief		��ʾһ��16*16��ͼƬ��������������ʾ���ִ�
 * @param[in]	x:������
				y:ҳ����
				str:Ҫ��ʾ���ַ���
				flag����ʾģʽ����ɫ�ͷ�ɫ
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
 * @brief		��һ����
 * @param[in]	x:������
				y:ҳ����
				str:Ҫ��ʾ���ַ���
				flag����ʾģʽ����ɫ�ͷ�ɫ
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
 * @brief		��һ������
 * @param[in]	x:������
				y:ҳ����
				width�����εĿ�
				hight�����εĸ�
				flag����ʾģʽ����ɫ�ͷ�ɫ
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



