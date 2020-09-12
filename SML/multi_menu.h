
#ifndef MULTI_MENU_H
#define MULTI_MENU_H

#include "stdint.h"

#define SUBMENU_MAXNUM    12  //子菜单和子菜单名称的最有数量
//typedef void(*FUNC_POINT)(struct Menu * this);

//定义一个菜单结构
struct Menu
{
	uint8_t menu_num;   						//子菜单的数量
	uint8_t record_sub_num;						//当前指向的子菜单
	const uint8_t *menu_name[SUBMENU_MAXNUM];			//主菜单名称
	const uint8_t *sub_menu_name[SUBMENU_MAXNUM][SUBMENU_MAXNUM];		//字菜单名称
	struct Menu *submenuPtr[SUBMENU_MAXNUM];	//子菜单对象
	struct Menu *parent;						//指向上级菜单
	void (*func_menu_process)(struct Menu *);				//菜单项处理引擎
	void (*func_init)(struct Menu *);						//页面初始化
	void (*func_parameter_update)(struct Menu *);			//页面参数更新
	void (*func_refresh)(struct Menu *);					//页面刷新引擎
	void (*funcKeyUP)(struct Menu *);						//UP按键处理
	void (*funcKeyDOWN)(struct Menu *);						//DOWN按键处理
	void (*funcKeyENT)(struct Menu *);						//ENT按键处理
	void (*funcKeyESC)(struct Menu *);						//ESC按键处理
};


extern struct Menu * CurrPage;	//指向当前页面

extern struct Menu page_start;
extern struct Menu page_monitor;
extern struct Menu menu_main;
extern struct Menu menu_main_opera;
extern struct Menu menu_main_set;
extern struct Menu menu_main_record;
extern struct Menu menu_main_manage;


#endif



