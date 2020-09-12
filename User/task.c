
#include "task.h"
#include "debug_frmwrk.h"
#include "string.h"
#include "systen_delay.h"
#include <math.h>
#include "main.h"
#include "key_control.h"
#include "multi_menu.h"
#include "JLX240160G.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

//任务管理
static TASK_COMPONENTS TaskComps[TASKS_MAX] = 
{
//	开关	运行标志	开始时间	间隔时间	任务函数
    {0xAA,	0x55,		10,			200, 		Task_ADC},				// ADC采样任务和闭环控制
    {0xAA,	0x55,		20,			10, 		Task_ButtonCheck},     	// 按键检查任务
    {0xAA,	0x55,		30,			500, 		Task_LcdRefresh},     	// LCD刷新任务
};

/*********************************************************************//**
 * @brief		任务标志处理，放到节拍中断中
 * @param[in]	
 * @return		
 **********************************************************************/
void TaskRemarks(void)
{
    uint8_t i = 0;
    for (i=0; i<TASKS_MAX; i++)         		// 逐个任务时间处理
    {
    	if( TaskComps[i].onoff == 0xAA )
    	{
	        if (TaskComps[i].TaskTimer > 0)         // 时间不为0
	        {
	            TaskComps[i].TaskTimer --;         	// 减去一个节拍
	            if (TaskComps[i].TaskTimer <= 0)    // 时间减完了
	            {
	                 TaskComps[i].TaskTimer = TaskComps[i].ItvTime;		// 恢复计时器值，从新下一次
	                 TaskComps[i].TaskRun = 0xAA;           			// 任务可以运行
	            }
	        }
    	}
	}
}

/*******************************************************//**
 * @brief		轮询满足运行条件的任务，放到主循环中
 * @param[in]	
 * @return		
 *******************************************************/
void TaskProcess(void)
{
    uint8_t i;
    for (i=0; i<TASKS_MAX; i++)           	// 逐个任务时间处理
    {
        if (TaskComps[i].TaskRun == 0xAA)  	// 时间不为0
        {
            TaskComps[i].TaskHook();       	// 运行任务
            TaskComps[i].TaskRun = 0x55; 	// 标志清0
        }
    }   
}

/*********************************************************************//**
 * @brief		模拟量采集和闭环控制任务
 * @param[in]	
 * @return	
 * @timer 			
 **********************************************************************/
void Task_ADC(void)
{
    //PRINTF("run Task_ADC\n");
	//进行AD转换和滤波

}

/*********************************************************************//**
 * @brief		按键处理任务
 * @param[in]	
 * @return		
 **********************************************************************/
void Task_ButtonCheck(void)
{
	uint8_t key_value = 0;
	
	key_value = Key_Driver();
	if( key_value != 0x00 )
	{
//		PRINTF("key_value = %x\n", key_value);
		switch(key_value)
		{
			case 0x01:
			{
				if( CurrPage->funcKeyUP != NULL )
					CurrPage->funcKeyUP(CurrPage);
				break;
			}
			case 0x02:
			{
				if( CurrPage->funcKeyENT != NULL )
					CurrPage->funcKeyENT(CurrPage);
				break;
			}
			case 0x04:
			{
				if( CurrPage->funcKeyESC != NULL )
					CurrPage->funcKeyESC(CurrPage);
				break;
			}
			case 0x08:
			{
				if( CurrPage->funcKeyDOWN != NULL )
					CurrPage->funcKeyDOWN(CurrPage);
				break;
			}
			default:break;
		}

	}
}

/*********************************************************************//**
 * @brief		LCD刷新任务
 * @param[in]	
 * @return	
 * @timer 			
 **********************************************************************/
void Task_LcdRefresh(void)
{
	//如果当前页面有定时刷新内容，在这里调用
	if(CurrPage->func_parameter_update != NULL)
		CurrPage->func_parameter_update(CurrPage);

	//调用显存刷新页面
	GPIO_SetValue(0, (1<<9));
	Refresh_Screen();
	GPIO_ClearValue(0, (1<<9));
}


