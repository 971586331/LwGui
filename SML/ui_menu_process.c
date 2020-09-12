
/**********************************************************************
* @brief	UI菜单项处理引擎
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/

#include "video_memory.h"
#include "LCDFont.h"
#include "multi_menu.h"

/*********************************************************************//**
 * @brief 		通用的菜单项处理引擎
 * @param[in] 	
 * @return 		
 **********************************************************************/
void general_menu_process_engine(struct Menu * this)
{
	int i = 0, j = 0;
	int page_num = 0;

	//画菜单标题栏的矩形
	Dis_Rectangle(32,4,180,32,PURECOLOR);

	//画菜单图标
	Dis_Image(48, 5, _list_1616, 16, 16, PURECOLOR);
	Dis_Image(180, 5, _list_1616, 16, 16, PURECOLOR);

	//显示菜单标题
	Dis_16_16_Str(100 , 5, this->menu_name, PURECOLOR);

	//计算分页显示的页数
	this->record_sub_num < 4 ? (page_num = 0):(page_num = this->record_sub_num/4);
	for(i=0; i<4; i++)
	{
		//计算当前显示的菜单项
		j = page_num*4 + i;
		if (j < this->menu_num)
		{

			//光标在当前项，则反色显示
			if(this->record_sub_num == j)
			{
				//显示序号
				Dis_Image(32, 8+i*2,  numero_1616[j+1], 16, 16, INVERTED);
				//显示菜单名称
				Dis_16_16_Str(48, 8+i*2 , this->sub_menu_name[j], INVERTED);
				if ((this->submenuPtr[j])->menu_num != 0)	
					Dis_Image(200, 8+i*2, _arrow_1616, 16, 16, INVERTED);
			}
			else
			{
				//显示序号
				Dis_Image(32, 8+i*2, numero_1616[j+1], 16, 16, PURECOLOR);
				//显示菜单名称
				Dis_16_16_Str(48, 8+i*2, this->sub_menu_name[j], PURECOLOR);
				if ((this->submenuPtr[j])->menu_num != 0)	
					Dis_Image(200, 8+i*2, _arrow_1616, 16, 16, PURECOLOR);
			}
		}
		else	//如果一页显示的项小于4项，剩下的填空白
		{
			Dis_Image(48, 8+i*2, _spac_1616, 16, 16, PURECOLOR);
		}
	}
}


