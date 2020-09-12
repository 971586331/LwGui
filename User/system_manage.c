
#include "lpc17xx_libcfg.h"
#include "system_manage.h"

struct System_Parameter gSystem_Parameter = {
	.contrast = 0x14,	//0~63
	.backlight = 10,	//5~99
};


struct System_Manage gSystem_Manage = {
	.contrast_reset = 0x14,
	.backlight_reset = 10,
};



