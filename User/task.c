
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

//�������
static TASK_COMPONENTS TaskComps[TASKS_MAX] = 
{
//	����	���б�־	��ʼʱ��	���ʱ��	������
    {0xAA,	0x55,		10,			200, 		Task_ADC},				// ADC��������ͱջ�����
    {0xAA,	0x55,		20,			10, 		Task_ButtonCheck},     	// �����������
    {0xAA,	0x55,		30,			500, 		Task_LcdRefresh},     	// LCDˢ������
};

/*********************************************************************//**
 * @brief		�����־�����ŵ������ж���
 * @param[in]	
 * @return		
 **********************************************************************/
void TaskRemarks(void)
{
    uint8_t i = 0;
    for (i=0; i<TASKS_MAX; i++)         		// �������ʱ�䴦��
    {
    	if( TaskComps[i].onoff == 0xAA )
    	{
	        if (TaskComps[i].TaskTimer > 0)         // ʱ�䲻Ϊ0
	        {
	            TaskComps[i].TaskTimer --;         	// ��ȥһ������
	            if (TaskComps[i].TaskTimer <= 0)    // ʱ�������
	            {
	                 TaskComps[i].TaskTimer = TaskComps[i].ItvTime;		// �ָ���ʱ��ֵ��������һ��
	                 TaskComps[i].TaskRun = 0xAA;           			// �����������
	            }
	        }
    	}
	}
}

/*******************************************************//**
 * @brief		��ѯ�����������������񣬷ŵ���ѭ����
 * @param[in]	
 * @return		
 *******************************************************/
void TaskProcess(void)
{
    uint8_t i;
    for (i=0; i<TASKS_MAX; i++)           	// �������ʱ�䴦��
    {
        if (TaskComps[i].TaskRun == 0xAA)  	// ʱ�䲻Ϊ0
        {
            TaskComps[i].TaskHook();       	// ��������
            TaskComps[i].TaskRun = 0x55; 	// ��־��0
        }
    }   
}

/*********************************************************************//**
 * @brief		ģ�����ɼ��ͱջ���������
 * @param[in]	
 * @return	
 * @timer 			
 **********************************************************************/
void Task_ADC(void)
{
    //PRINTF("run Task_ADC\n");
	//����ADת�����˲�

}

/*********************************************************************//**
 * @brief		������������
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
 * @brief		LCDˢ������
 * @param[in]	
 * @return	
 * @timer 			
 **********************************************************************/
void Task_LcdRefresh(void)
{
	//�����ǰҳ���ж�ʱˢ�����ݣ����������
	if(CurrPage->func_parameter_update != NULL)
		CurrPage->func_parameter_update(CurrPage);

	//�����Դ�ˢ��ҳ��
	GPIO_SetValue(0, (1<<9));
	Refresh_Screen();
	GPIO_ClearValue(0, (1<<9));
}


