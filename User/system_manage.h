
#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

struct System_Parameter
{
	int contrast;
	int backlight;
};


struct System_Manage
{
	int contrast_reset;
	int backlight_reset;
	
};


extern struct System_Parameter gSystem_Parameter;
extern struct System_Manage gSystem_Manage;



#endif

