
#ifndef MULTI_MENU_H
#define MULTI_MENU_H

#include "stdint.h"

#define SUBMENU_MAXNUM    12  //�Ӳ˵����Ӳ˵����Ƶ���������
//typedef void(*FUNC_POINT)(struct Menu * this);

//����һ���˵��ṹ
struct Menu
{
	uint8_t menu_num;   						//�Ӳ˵�������
	uint8_t record_sub_num;						//��ǰָ����Ӳ˵�
	const uint8_t *menu_name[SUBMENU_MAXNUM];			//���˵�����
	const uint8_t *sub_menu_name[SUBMENU_MAXNUM][SUBMENU_MAXNUM];		//�ֲ˵�����
	struct Menu *submenuPtr[SUBMENU_MAXNUM];	//�Ӳ˵�����
	struct Menu *parent;						//ָ���ϼ��˵�
	void (*func_menu_process)(struct Menu *);				//�˵��������
	void (*func_init)(struct Menu *);						//ҳ���ʼ��
	void (*func_parameter_update)(struct Menu *);			//ҳ���������
	void (*func_refresh)(struct Menu *);					//ҳ��ˢ������
	void (*funcKeyUP)(struct Menu *);						//UP��������
	void (*funcKeyDOWN)(struct Menu *);						//DOWN��������
	void (*funcKeyENT)(struct Menu *);						//ENT��������
	void (*funcKeyESC)(struct Menu *);						//ESC��������
};


extern struct Menu * CurrPage;	//ָ��ǰҳ��

extern struct Menu page_start;
extern struct Menu page_monitor;
extern struct Menu menu_main;
extern struct Menu menu_main_opera;
extern struct Menu menu_main_set;
extern struct Menu menu_main_record;
extern struct Menu menu_main_manage;


#endif



