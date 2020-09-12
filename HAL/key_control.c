

#include "key_control.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

const struct Key_Manage gKey_Manage[KEY_NUM] = {
	{{2, 8},	0x01,},
	{{2, 12},	0x02,},
	{{2, 13}, 	0x04,},
	{{1, 21},	0x08,},
};

/************************************************//**
* @brief 		4个按键的IO初始化
* @param[in]	
* @return 		
*************************************************/
void KEY_Init(void)
{
	PINSEL_CFG_Type PinCfg;
	int i = 0;
	
	for(i=0; i<KEY_NUM; i++)
	{
		
		PinCfg.OpenDrain = 0;
		PinCfg.Pinmode = 0;
		PinCfg.Funcnum = 0;
		PinCfg.Pinnum = gKey_Manage[i].pin.Portnum;
		PinCfg.Portnum = gKey_Manage[i].pin.Pinnum;
		PINSEL_ConfigPin(&PinCfg);
		GPIO_SetDir(gKey_Manage[i].pin.Portnum, (1<<gKey_Manage[i].pin.Pinnum), 0);		//设置为输入
	}
}

/************************************************//**
* @brief 		扫描一次4个IO
* @param[in]	
* @return 		
*************************************************/
uint8_t KEY_Scan(void)
{
	int i = 0;
    int key = 0;

	for(i=0; i<KEY_NUM; i++)
	{
		if( ((GPIO_ReadValue(gKey_Manage[i].pin.Portnum) >> gKey_Manage[i].pin.Pinnum) & 0x01) == 0 )
				key |= gKey_Manage[i].Key_value;
	}

    return key; 
}

/************************************************//**
* @brief 		按键去抖动和长按检测，10ms调用一次
* @param[in]	
* @return 		
*************************************************/
uint8_t Key_Driver(void)
{
    static e_Key_State key_state = NULL_STATE;
    static uint8_t key_time = 0;						
	static uint8_t key_value = 0;			
	uint8_t key_return = 0;					
	
	switch(key_state)
	{
		case NULL_STATE:	//空闲状态
		{
			if( (KEY_Scan() & 0x000f) != 0x00)	
				key_state = ACK_STATE;
			break;
		}
		case ACK_STATE:		//确认状态
		{
			if((KEY_Scan() & 0x000f)  != 0x00)	
			{
				key_time = 0;
				key_value = KEY_Scan() & 0x000f;	
				key_state = TIMEING_STATE;
			}
			else			
				key_state = NULL_STATE;
			break;
		}
		case TIMEING_STATE:	//超时状态	
		{
			if((KEY_Scan() & 0x000f) != 0x00)	
			{
				key_time ++;
				if(key_time > 100)
				{
                    key_time = 0;
                    key_return = key_value | PRESS_VALUE;	
                    key_value = 0x00;
					key_state = LONG_PRESS_STATE;
					break;
				}
			}
			else
			{
				key_return = key_value;			
                key_value = 0x00;
				key_state = NULL_STATE;
			}
            break;
		}
        case LONG_PRESS_STATE:	//长按状态
        {
            if((KEY_Scan() & 0x000f) == 0x00)		
                key_state = NULL_STATE;			
            break;
        }
	}
	return key_return;
}




