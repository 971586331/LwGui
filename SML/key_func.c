
/**********************************************************************
* @brief	UI按键处理引擎
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
 * @brief 		目录界面按up的通用操作
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_up(struct Menu * this)
{
	if ( this->record_sub_num>0)
	{
		this->record_sub_num--;
	}

	Clear_Lcd_Buff_Menu();		//清除显存
	//执行菜单项处理引擎
	if( this->func_menu_process != NULL )
	{
		this->func_menu_process(this);
	}
	//执行页面初始化
	if( this->func_init != NULL )
	{
		this->func_init(this);
	}
	
}

/*********************************************************************//**
 * @brief 		目录界面按down的通用操作
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_down(struct Menu * this)
{
	if (this->record_sub_num<(this->menu_num-1))
	{
		this->record_sub_num++;
	}

	Clear_Lcd_Buff_Menu();		//清除显存
	//执行菜单项处理引擎
	if( this->func_menu_process != NULL )
	{
		this->func_menu_process(this);
	}
	//执行页面初始化
	if( this->func_init != NULL )
	{
		this->func_init(this);
	}
}

/*********************************************************************//**
 * @brief 		目录界面按ent的通用操作
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_ent(struct Menu * this)
{
	CurrPage = this->submenuPtr[this->record_sub_num];
	CurrPage->record_sub_num=0;

	Clear_Lcd_Buff_Menu();		//清除显存
	//执行菜单项处理引擎
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//执行页面初始化
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(CurrPage);
	}

}

/*********************************************************************//**
 * @brief 		目录界面按esc的通用操作
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_menu_esc(struct Menu * this)
{
	if (this->parent != NULL)
	{
		CurrPage = this->parent;
	}

	Clear_Lcd_Buff_Menu();		//清除显存
	//执行菜单项处理引擎
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//执行页面初始化
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(CurrPage);
	}
}

/*********************************************************************//**
 * @brief 		监控页面按键操作
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_monitor_all(struct Menu * this)
{
	CurrPage = &menu_main;

	Clear_Lcd_Buff_Menu();		//清除显存
	//执行菜单项处理引擎
	if( CurrPage->func_menu_process != NULL )
	{
		CurrPage->func_menu_process(CurrPage);
	}
	//执行页面初始化
	if( CurrPage->func_init != NULL )
	{
		CurrPage->func_init(this);
	}
}

/*********************************************************************//**
 * @brief 		操作-启动页面按确定
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_start_ent(struct Menu * this)
{
	//返回上一层
	key_menu_esc(this);

	//发送启动信号
}

/*********************************************************************//**
 * @brief 		操作-停止页面按确定
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_stop_ent(struct Menu * this)
{
	//返回上一层
	key_menu_esc(this);

	//发送停止信号

}

/*********************************************************************//**
 * @brief 		操作-再生页面按确定
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_opera_regenerate_ent(struct Menu * this)
{
	//返回上一层
	key_menu_esc(this);

	//发送再生信号
	
}

/*********************************************************************//**
 * @brief 		设置-对比度按+
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_up(struct Menu * this)
{
	char str[5];

	gSystem_Manage.contrast_reset ++;
	if( gSystem_Manage.contrast_reset > 32 )
		gSystem_Manage.contrast_reset = 32;

	//显示重设值
	sprintf(str, "%d", gSystem_Manage.contrast_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);

	transfer_command_lcd(0x81);    //设置对比度，“0x81”不可改动，紧跟着的2个数据是可改的，但“先微调后粗调”这个顺序别乱了
	transfer_data_lcd(gSystem_Manage.contrast_reset);   		 //微调对比度,可调范围0x00～0x3f，共64级
	transfer_data_lcd(0x04);  		 //粗调对比度,可调范围0x00～0x07，共8级
}

/*********************************************************************//**
 * @brief 		设置-对比度按-
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_down(struct Menu * this)
{
	char str[5];

	gSystem_Manage.contrast_reset --;
	if( gSystem_Manage.contrast_reset < 8 )
		gSystem_Manage.contrast_reset = 8;

	//显示重设值
	sprintf(str, "%d", gSystem_Manage.contrast_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);

	transfer_command_lcd(0x81);    //设置对比度，“0x81”不可改动，紧跟着的2个数据是可改的，但“先微调后粗调”这个顺序别乱了
	transfer_data_lcd(gSystem_Manage.contrast_reset);   		 //微调对比度,可调范围0x00～0x3f，共64级
	transfer_data_lcd(0x04);  		 //粗调对比度,可调范围0x00～0x07，共8级
}

/*********************************************************************//**
 * @brief 		设置-对比度按确认
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_contrast_ent(struct Menu * this)
{
	//返回上一层
	key_menu_esc(this);

	gSystem_Parameter.contrast = gSystem_Manage.contrast_reset;
	//参数保存到EEPROM
	
}

/*********************************************************************//**
 * @brief 		设置-背光时间按+
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_up(struct Menu * this)
{
	char str[5];

	gSystem_Manage.backlight_reset ++;
	if( gSystem_Manage.backlight_reset > 99 )
		gSystem_Manage.backlight_reset = 99;

	//显示重设值
	sprintf(str, "%d", gSystem_Manage.backlight_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);
}

/*********************************************************************//**
 * @brief 		设置-背光时间按-
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_down(struct Menu * this)
{
	char str[5];

	gSystem_Manage.backlight_reset --;
	if( gSystem_Manage.backlight_reset < 5 )
		gSystem_Manage.backlight_reset = 5;

	//显示重设值
	sprintf(str, "%d", gSystem_Manage.backlight_reset);
	Clear_Will_Lcd_Buff(120, 10, 16, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);
}

/*********************************************************************//**
 * @brief 		设置-背光时间按确认
 * @param[in] 	
 * @return 		
 **********************************************************************/
void key_set_backlight_ent(struct Menu * this)
{
	//返回上一层
	key_menu_esc(this);

	gSystem_Parameter.backlight = gSystem_Manage.backlight_reset;
	//参数保存到EEPROM
}

