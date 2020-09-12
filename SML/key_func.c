
/**********************************************************************
* @brief	UI������������
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/


#include "stdint.h"
#include "key_func.h"
#include "multi_menu.h"
#include "lpc17xx_libcfg.h"
#include "video_memory.h"
#include "main.h"
#include "system_manage.h"
#include "stdio.h"
#include "LCDFont.h"
#include "JLX240160G.h"

/*********************************************************************//**
 * @brief 		Ŀ¼���水up��ͨ�ò���
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_up(struct Menu * this)
{
	if ( this->record_sub_num>0)
	{
		this->record_sub_num--;
	}

	Clear_Lcd_Buff_Menu();		//����Դ�
	//ִ�в˵��������
	if( this->func_menu_process != NULL )
	{
		this->func_menu_process(this);
	}
	//ִ��ҳ���ʼ��
	if( this->func_init != NULL )
	{
		this->func_init(this);
	}
	
}

/*********************************************************************//**
 * @brief 		Ŀ¼���水down��ͨ�ò���
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_down(struct Menu * this)
{
	if (this->record_sub_num<(this->menu_num-1))
	{
		this->record_sub_num++;
	}

	Clear_Lcd_Buff_Menu();		//����Դ�
	//ִ�в˵��������
	if( this->func_menu_process != NULL )
	{
		this->func_menu_process(this);
	}
	//ִ��ҳ���ʼ��
	if( this->func_init != NULL )
	{
		this->func_init(this);
	}
}

/*********************************************************************//**
 * @brief 		Ŀ¼���水ent��ͨ�ò���
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_ent(struct Menu * this)
{
	CurrPage = this->submenuPtr[this->record_sub_num];
	CurrPage->record_sub_num=0;

	Clear_Lcd_Buff_Menu();		//����Դ�
	//ִ�в˵��������
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//ִ��ҳ���ʼ��
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(CurrPage);
	}

}

/*********************************************************************//**
 * @brief 		Ŀ¼���水esc��ͨ�ò���
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_esc(struct Menu * this)
{
	if (this->parent != NULL)
	{
		CurrPage = this->parent;
	}

	Clear_Lcd_Buff_Menu();		//����Դ�
	//ִ�в˵��������
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//ִ��ҳ���ʼ��
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(CurrPage);
	}
}

/*********************************************************************//**
 * @brief 		���ҳ�水������
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_monitor_all(struct Menu * this)
{
	CurrPage = &menu_main;

	Clear_Lcd_Buff_Menu();		//����Դ�
	//ִ�в˵��������
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//ִ��ҳ���ʼ��
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(this);
	}
}

/*********************************************************************//**
 * @brief 		����-����ҳ�水ȷ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_start_ent(struct Menu * this)
{
	//������һ��
	key_menu_esc(this);

	//���������ź�
}

/*********************************************************************//**
 * @brief 		����-ֹͣҳ�水ȷ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_stop_ent(struct Menu * this)
{
	//������һ��
	key_menu_esc(this);

	//����ֹͣ�ź�

}

/*********************************************************************//**
 * @brief 		����-����ҳ�水ȷ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_regenerate_ent(struct Menu * this)
{
	//������һ��
	key_menu_esc(this);

	//���������ź�
	
}

/*********************************************************************//**
 * @brief 		����-�ԱȶȰ�+
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_up(struct Menu * this)
{
	char str[5];

	gSystem_Manage.contrast_reset ++;
	if( gSystem_Manage.contrast_reset > 32 )
		gSystem_Manage.contrast_reset = 32;

	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.contrast_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);

	transfer_command_lcd(0x81);    //���öԱȶȣ���0x81�����ɸĶ��������ŵ�2�������ǿɸĵģ�������΢����ֵ������˳�������
	transfer_data_lcd(gSystem_Manage.contrast_reset);   		 //΢���Աȶ�,�ɵ���Χ0x00��0x3f����64��
	transfer_data_lcd(0x04);  		 //�ֵ��Աȶ�,�ɵ���Χ0x00��0x07����8��
}

/*********************************************************************//**
 * @brief 		����-�ԱȶȰ�-
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_down(struct Menu * this)
{
	char str[5];

	gSystem_Manage.contrast_reset --;
	if( gSystem_Manage.contrast_reset < 8 )
		gSystem_Manage.contrast_reset = 8;

	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.contrast_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);

	transfer_command_lcd(0x81);    //���öԱȶȣ���0x81�����ɸĶ��������ŵ�2�������ǿɸĵģ�������΢����ֵ������˳�������
	transfer_data_lcd(gSystem_Manage.contrast_reset);   		 //΢���Աȶ�,�ɵ���Χ0x00��0x3f����64��
	transfer_data_lcd(0x04);  		 //�ֵ��Աȶ�,�ɵ���Χ0x00��0x07����8��
}

/*********************************************************************//**
 * @brief 		����-�ԱȶȰ�ȷ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_ent(struct Menu * this)
{
	//������һ��
	key_menu_esc(this);

	gSystem_Parameter.contrast = gSystem_Manage.contrast_reset;
	//�������浽EEPROM
	
}

/*********************************************************************//**
 * @brief 		����-����ʱ�䰴+
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_up(struct Menu * this)
{
	char str[5];

	gSystem_Manage.backlight_reset ++;
	if( gSystem_Manage.backlight_reset > 99 )
		gSystem_Manage.backlight_reset = 99;

	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.backlight_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);
}

/*********************************************************************//**
 * @brief 		����-����ʱ�䰴-
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_down(struct Menu * this)
{
	char str[5];

	gSystem_Manage.backlight_reset --;
	if( gSystem_Manage.backlight_reset < 5 )
		gSystem_Manage.backlight_reset = 5;

	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.backlight_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);
}

/*********************************************************************//**
 * @brief 		����-����ʱ�䰴ȷ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_ent(struct Menu * this)
{
	//������һ��
	key_menu_esc(this);

	gSystem_Parameter.backlight = gSystem_Manage.backlight_reset;
	//�������浽EEPROM
}

