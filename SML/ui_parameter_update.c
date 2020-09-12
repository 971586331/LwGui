
/**********************************************************************
* @file		ui_parameter_update.c
* @brief	UI数据更新
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/

#include "multi_menu.h"
#include "string.h"
#include "video_memory.h"
#include "LCDFont.h"
#include "stdio.h"
/*********************************************************************//**
 * @brief 		监控页面初始化
 * @param[in] 	
 * @return 		
 **********************************************************************/
void monitor_page_parameter_update(struct Menu * this)
{
	static float sss = 0.00;
	char str[10];
	
	sss += 0.001;
	sprintf(str, "%0.3f", sss);
	Clear_Will_Lcd_Buff(120, 10, 8*10, 16);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);
}


