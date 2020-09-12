
#ifndef _KEY_H
#define _KEY_H

#include "lpc17xx_libcfg.h"


#define KEY_NUM (4)
#define PRESS_VALUE (0x100)

//GPIO½á¹¹
struct Gpio_Fun
{
	uint8_t Portnum;
	uint8_t Pinnum;
};

struct Key_Manage
{
	const struct Gpio_Fun pin;
	const int Key_value;
};

//°´¼ü×´Ì¬
typedef enum
{
    NULL_STATE,
    ACK_STATE,	
    TIMEING_STATE,	
    LONG_PRESS_STATE,
}e_Key_State; 	

void KEY_Init(void);
uint8_t KEY_Scan(void);
uint8_t Key_Driver(void);

extern const struct Key_Manage gKey_Manage[KEY_NUM];


#endif


