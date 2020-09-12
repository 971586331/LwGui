
#ifndef JLX240160G_H
#define JLX240160G_H

#include "stdint.h"

#define LCDI2CDEV (LPC_I2C0)

#define LCD_RST_H ( GPIO_SetValue(3, (1<<26)) )
#define LCD_RST_L ( GPIO_ClearValue(3, (1<<26)) )

#define LCD_BL_H ( GPIO_SetValue(3, (1<<25)) )
#define LCD_BL_L ( GPIO_ClearValue(3, (1<<25)) )

void transfer_command_lcd(uint8_t cmdx);
void transfer_data_lcd(uint8_t datax);

void LcdInit(void);
void clear_screen(void);
void Refresh_Screen(void);
void test(void);


#endif

