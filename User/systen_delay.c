
#include "systen_delay.h"
#include "task.h"

/************************** PRIVATE VARIABLES *************************/
/* SysTick Counter */
volatile unsigned long SysTickCnt;

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		SysTick handler sub-routine (1ms)
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SysTick_Handler (void) 
{
	  SysTickCnt++;

	  TaskRemarks();	//任务时间片轮询

	  
}

void delay_init(void)
{
		SysTick_Config(SystemCoreClock/1000 - 1); /* Generate interrupt each 1 ms   */
}

/*******************************************************//**
 * @brief		delay ms,???????
 * @param[in]	n:n ms
 * @return		
 *******************************************************/
void my_delay_ms(int n)
{
	int x, y;
	for(x=0; x<n; x++)
	{
		for(y=0; y<18500; y++)
		{
//			__NOP();
		}
	}
}

/*******************************************************//**
 * @brief		delay us,???????
 * @param[in]	n:n us
 * @return		
 *******************************************************/
void my_delay_us(int n)
{
	int x, y;
	for(x=0; x<n; x++)
	{
		for(y=0; y<20; y++)
		{
//			__NOP();
		}
	/*
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		*/
	}
}
