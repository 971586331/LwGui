
/**********************************************************************
* @brief	多层菜单实现
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/


#include "multi_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "LCDFont.h"
#include "malloc.h"
#include "ui_init.h"
#include "key_func.h"
#include "ui_parameter_update.h"
#include "ui_menu_process.h"

struct Menu page_start;
struct Menu page_monitor;
struct Menu menu_main;
struct Menu menu_main_opera;
struct Menu menu_main_set;
struct Menu menu_main_record;
struct Menu menu_main_manage;
struct Menu page_opera_start;
struct Menu page_opera_stop;
struct Menu page_opera_regenerate;
struct Menu page_set_contrast;
struct Menu page_set_backlight;


struct Menu * CurrPage;	//指向当前页面

//启动页面
struct Menu page_start = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {NULL},
	.sub_menu_name = {NULL},
	.submenuPtr = {NULL},
	.parent = NULL,
	.func_menu_process = NULL,
	.func_init = page_start_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = NULL,
	.funcKeyDOWN = NULL,
	.funcKeyENT = NULL,
	.funcKeyESC = NULL,
};

//监控页面
struct Menu page_monitor = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {NULL},
	.sub_menu_name = {NULL},
	.submenuPtr = {NULL},
	.parent = NULL,
	.func_menu_process = NULL,
	.func_init = page_monitor_init,
	.func_parameter_update = monitor_page_parameter_update,
	.func_refresh = NULL,
	.funcKeyUP = key_monitor_all,
	.funcKeyDOWN = key_monitor_all,
	.funcKeyENT = key_monitor_all,
	.funcKeyESC = key_monitor_all,
};

//主菜单
struct Menu menu_main = {
	.menu_num = 4,		
	.record_sub_num = 0,
	.menu_name = {_zhu1_1616, _cai_1616, _dan_1616, NULL},
	.sub_menu_name = { 	{_cao_1616, _zuo_1616, NULL},
						{_she_1616, _zhi1_1616, NULL},
						{_ji1_1616, _lu2_1616, NULL},
						{_guan1_1616, _li1_1616, NULL}, 
						{NULL}, },
	.submenuPtr = {	&menu_main_opera,
					&menu_main_set,
					&menu_main_record,
					&menu_main_manage,
					NULL},
	.parent = &page_monitor,
	.func_menu_process = general_menu_process_engine,
	.func_init = NULL,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_menu_up,
	.funcKeyDOWN = key_menu_down,
	.funcKeyENT = key_menu_ent,
	.funcKeyESC = key_menu_esc,
};

//操作菜单
struct Menu menu_main_opera = {
	.menu_num = 3,		
	.record_sub_num = 0,
	.menu_name = {_cao_1616, _zuo_1616, NULL},
	.sub_menu_name = { 	{_qi_1616, _dong_1616, NULL},
						{_ting_1616, _zhi6_1616, NULL},
						{_zai1_1616, _sheng1_1616, NULL},
						{NULL},	},
	.submenuPtr = {	&page_opera_start,
					&page_opera_stop,
					&page_opera_regenerate,
					NULL},
	.parent = &menu_main,
	.func_menu_process = general_menu_process_engine,
	.func_init = NULL,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_menu_up,
	.funcKeyDOWN = key_menu_down,
	.funcKeyENT = key_menu_ent,
	.funcKeyESC = key_menu_esc,
};

//设置菜单
struct Menu menu_main_set = {
	.menu_num = 2,		
	.record_sub_num = 0,
	.menu_name = {_she_1616, _zhi1_1616, NULL},
	.sub_menu_name = { 	{_she_1616, _zhi1_1616, _dui_1616, _bi2_1616, _du_1616, NULL},
						{_she_1616, _zhi1_1616, _bei1_1616, _guang_1616, _shi3_1616, _jian2_1616, NULL},
						{NULL},	},
	.submenuPtr = {&page_set_contrast,
					&page_set_backlight,
					NULL},
	.parent = &menu_main,
	.func_menu_process = general_menu_process_engine,
	.func_init = NULL,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_menu_up,
	.funcKeyDOWN = key_menu_down,
	.funcKeyENT = key_menu_ent,
	.funcKeyESC = key_menu_esc,
};

//记录菜单
struct Menu menu_main_record = {
	.menu_num = 3,		
	.record_sub_num = 0,
	.menu_name = {_ji1_1616, _lu2_1616, NULL},
	.sub_menu_name = { 	{_cha_1616, _kan_1616, _fa_1616, _men_1616, _lei1_1616, _ji2_1616, _kai_1616, _guan_1616, _ci_1616, _shu_1616,  NULL},
						{_cha_1616, _kan_1616, _she_1616, _bei_1616, _cao_1616, _zuo_1616, _r_1616, _zhi7_1616, NULL},
						{_cha_1616, _kan_1616, _she_1616, _bei_1616, _bao1_1616, _jing_1616, _ji1_1616, _lu2_1616, NULL},
						{NULL},	},
	.submenuPtr = {NULL},
	.parent = &menu_main,
	.func_menu_process = general_menu_process_engine,
	.func_init = NULL,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_menu_up,
	.funcKeyDOWN = key_menu_down,
	.funcKeyENT = key_menu_ent,
	.funcKeyESC = key_menu_esc,
};

//管理菜单
struct Menu menu_main_manage = {
	.menu_num = 2,		
	.record_sub_num = 0,
	.menu_name = {_guan1_1616, _li1_1616, NULL},
	.sub_menu_name ={ 	{_she_1616, _zhi1_1616, _bao1_1616, _jing_1616, _yu1_1616, _zhi3_1616, NULL},
						{_she_1616, _zhi1_1616, _she_1616, _bei_1616, _di_1616, _zhi8_1616, NULL},
						{NULL},	},
	.submenuPtr = {NULL},
	.parent = &menu_main,
	.func_menu_process = general_menu_process_engine,
	.func_init = NULL,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_menu_up,
	.funcKeyDOWN = key_menu_down,
	.funcKeyENT = key_menu_ent,
	.funcKeyESC = key_menu_esc,
};

//操作-启动低温泵页面
struct Menu page_opera_start = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {NULL},
	.sub_menu_name ={NULL},
	.submenuPtr = {NULL},
	.parent = &menu_main_opera,
	.func_menu_process = NULL,
	.func_init = page_opera_start_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = NULL,
	.funcKeyDOWN = NULL,
	.funcKeyENT = key_opera_start_ent,
	.funcKeyESC = key_menu_esc,
};

//操作-停止低温泵页面
struct Menu page_opera_stop = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {NULL},
	.sub_menu_name ={NULL},
	.submenuPtr = {NULL},
	.parent = &menu_main_opera,
	.func_menu_process = NULL,
	.func_init = page_opera_stop_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = NULL,
	.funcKeyDOWN = NULL,
	.funcKeyENT = key_opera_stop_ent,
	.funcKeyESC = key_menu_esc,
};

//操作-再生低温泵页面
struct Menu page_opera_regenerate = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {NULL},
	.sub_menu_name ={NULL},
	.submenuPtr = {NULL},
	.parent = &menu_main_opera,
	.func_menu_process = NULL,
	.func_init = page_opera_regenerate_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = NULL,
	.funcKeyDOWN = NULL,
	.funcKeyENT = key_opera_regenerate_ent,
	.funcKeyESC = key_menu_esc,
};

//设置-对比度页面
struct Menu page_set_contrast = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {_she_1616, _zhi1_1616, _dui_1616, _bi2_1616, _du_1616, NULL},
	.sub_menu_name ={NULL},
	.submenuPtr = {NULL},
	.parent = &menu_main_set,
	.func_menu_process = NULL,
	.func_init = page_set_contrast_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_set_contrast_up,
	.funcKeyDOWN = key_set_contrast_down,
	.funcKeyENT = key_set_contrast_ent,
	.funcKeyESC = key_menu_esc,
};

//设置-背光时间页面
struct Menu page_set_backlight = {
	.menu_num = 0,		
	.record_sub_num = 0,
	.menu_name = {_she_1616, _zhi1_1616, _bei1_1616, _guang_1616, _shi3_1616, _jian2_1616, NULL},
	.sub_menu_name ={NULL},
	.submenuPtr = {NULL},
	.parent = &menu_main_set,
	.func_menu_process = NULL,
	.func_init = page_set_backlight_init,
	.func_parameter_update = NULL,
	.func_refresh = NULL,
	.funcKeyUP = key_set_backlight_up,
	.funcKeyDOWN = key_set_backlight_down,
	.funcKeyENT = key_set_backlight_ent,
	.funcKeyESC = key_menu_esc,
};


