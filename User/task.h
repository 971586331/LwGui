
#ifndef _TASK_H
#define _TASK_H

#include "lpc_types.h"

#define TASKS_MAX (3)

//任务结构
typedef struct TASK_COMPONENTS
{
	int32_t onoff;				// 任务是否执行
	int32_t TaskRun;			// 任务运行标志
	int32_t TaskTimer;			// 任务开始时间
    int32_t ItvTime;        	// 任务运行间隔时间
    void (*TaskHook)(void);		// 要运行的任务函数
} TASK_COMPONENTS;       		// 任务定义

void TaskRemarks(void);
void TaskProcess(void);


void Task_ButtonCheck(void);
//ADC采样任务和闭环控制
void Task_ADC(void);
//
void Task_LcdRefresh(void);


#endif


