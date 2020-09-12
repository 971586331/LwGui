
#ifndef _TASK_H
#define _TASK_H

#include "lpc_types.h"

#define TASKS_MAX (3)

//����ṹ
typedef struct TASK_COMPONENTS
{
	int32_t onoff;				// �����Ƿ�ִ��
	int32_t TaskRun;			// �������б�־
	int32_t TaskTimer;			// ����ʼʱ��
    int32_t ItvTime;        	// �������м��ʱ��
    void (*TaskHook)(void);		// Ҫ���е�������
} TASK_COMPONENTS;       		// ������

void TaskRemarks(void);
void TaskProcess(void);


void Task_ButtonCheck(void);
//ADC��������ͱջ�����
void Task_ADC(void);
//
void Task_LcdRefresh(void);


#endif


