
/**********************************************************************
* @brief	LCD驱动
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/


#include "lpc17xx_libcfg.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#include "JLX240160G.h"
#include "systen_delay.h"
#include "video_memory.h"
#include "LCDFont.h"
#include "malloc.h"	 
#include "string.h"
	
//LCD写指令
void transfer_command_lcd(uint8_t cmdx)
{	
	I2C_M_SETUP_Type txsetup;
	uint8_t data[2];
	data[0] = 0x80;
	data[1] = cmdx;
	
	txsetup.sl_addr7bit = 0x3C;
	txsetup.tx_data = data;
	txsetup.tx_length = 2;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 1;

	if (I2C_MasterTransferData(LCDI2CDEV, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS)
	{
		return;
	} 
	else 
	{
		return;
	}

}

//LCD写数据
void transfer_data_lcd(uint8_t datax)
{	
	I2C_M_SETUP_Type txsetup;
	uint8_t data[2];
	data[0] = 0xC0;
	data[1] = datax;

	txsetup.sl_addr7bit = 0x3C;
	txsetup.tx_data = data;
	txsetup.tx_length = 2;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 1;

	if (I2C_MasterTransferData(LCDI2CDEV, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS)
	{
		return;
	} 
	else 
	{
		return;
	}  
}


void LcdI2cInit(void)
{
	PINSEL_CFG_Type PinCfg;

	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 1;
	PinCfg.Pinnum = 27;
	PinCfg.Portnum = 0; //P0.27 SDA0
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 28; //P0.28 SCL0
	PINSEL_ConfigPin(&PinCfg);	
	PINSEL_SetI2C0Pins(PINSEL_I2C_Fast_Mode, ENABLE);

	// Initialize I2C peripheral
	I2C_Init(LCDI2CDEV, 1000000);

	/* Enable I2C1 operation */
	I2C_Cmd(LCDI2CDEV, ENABLE);

}


void LcdInit(void)
{
	PINSEL_CFG_Type PinCfg;
	
	PinCfg.Funcnum = 0;
	PinCfg.Pinnum = 25;
	PinCfg.Portnum = 3;	
	PINSEL_ConfigPin(&PinCfg);	//P3.25 背光IO
	PinCfg.Pinnum = 26;
	PINSEL_ConfigPin(&PinCfg);	//P3.26 复位IO
	GPIO_SetDir(3, (1<<25), 1);  
	GPIO_SetDir(3, (1<<26), 1);  

	LcdI2cInit();		//初始化IIC总线

	my_delay_ms(10);	//复位LCD
	LCD_RST_L;
	my_delay_ms(10);
	LCD_RST_H;
	my_delay_ms(10);

	LCD_BL_L;	//打开背光
	//LCD_BL_H;

	transfer_command_lcd(0x30);   	//EXT=0
	transfer_command_lcd(0x94);   	//Sleep out
	transfer_command_lcd(0x31);   	//EXT=1
	transfer_command_lcd(0xD7);   	//Autoread disable
	transfer_data_lcd(0X9F);      	// 

	transfer_command_lcd(0x32);   	//Analog SET
	transfer_data_lcd(0x00);  		//OSC Frequency adjustment
	transfer_data_lcd(0x01);  		//Frequency on booster capacitors->6KHz
	transfer_data_lcd(0x01);  		//Bias=1/13

	transfer_command_lcd(0x20);   	//灰度设置
	transfer_data_lcd(0x01); 
	transfer_data_lcd(0x03);
	transfer_data_lcd(0x05);
	transfer_data_lcd(0x07); 
	transfer_data_lcd(0x09);
	transfer_data_lcd(0x0b);
	transfer_data_lcd(0x0d);
	transfer_data_lcd(0x10);
	transfer_data_lcd(0x11);
	transfer_data_lcd(0x13);
	transfer_data_lcd(0x15);
	transfer_data_lcd(0x17);
	transfer_data_lcd(0x19);
	transfer_data_lcd(0x1b);
	transfer_data_lcd(0x1d);
	transfer_data_lcd(0x1f);

	transfer_command_lcd(0x30);   	//EXT1=0，EXT0=0,表示选择了“扩展指令表1”
	transfer_command_lcd(0x75);   	//页地址设置
	transfer_data_lcd(0X00);      	//起始页地址：YS=0X00
	transfer_data_lcd(0X14);      	//结束页地址：YE=0x1F	每4行为一页，第0～3行为第0页，第124～127行为第31页（31=0x1f）
	transfer_command_lcd(0x15);   	//列地址设置
	transfer_data_lcd(0X00);      	//起始列地址：XS=0
	transfer_data_lcd(0XFF);      	//结束列地址：XE=256（0xff）
	
	transfer_command_lcd(0xBC);    	//行列扫描方向
	transfer_data_lcd(0x01);  		//MX.MY=Normal
	
	transfer_command_lcd(0x08);    	//数据格式选择,0x0C是低位在前D0-D7,0x08是高位在前D7-D0

	transfer_command_lcd(0xCA);    	//显示控制
	transfer_data_lcd(0X00);  		//设置CL驱动频率：CLD=0 
	transfer_data_lcd(0X9F);  		 //占空比：Duty=160
	transfer_data_lcd(0X20);  		 //N行反显：Nline=off

	transfer_command_lcd(0xF0);    //显示模式 
	transfer_data_lcd(0X10);  		 //如果设为0x11：表示选择4灰度级模式，如果设为0x10:表示选择黑白模式

	transfer_command_lcd(0x81);    //设置对比度，“0x81”不可改动，紧跟着的2个数据是可改的，但“先微调后粗调”这个顺序别乱了
	transfer_data_lcd(0x14);   		 //微调对比度,可调范围0x00～0x3f，共64级
	transfer_data_lcd(0x04);  		 //粗调对比度,可调范围0x00～0x07，共8级
	
	transfer_command_lcd(0x20);    //电源控制
	transfer_data_lcd(0x0B);   		 //D0=regulator ; D1=follower ; D3=booste,  on:1 off:0
	my_delay_ms(10);           
	transfer_command_lcd(0xAF);    //打开显示
}

//设置光标
void lcd_address(uint16_t x, uint16_t y, uint16_t x_total, uint16_t y_total)
{
	x=x;
	y=y+1;
	
	transfer_command_lcd(0x15);		//Set Column Address
	transfer_data_lcd(x);		
	transfer_data_lcd(x+x_total-1);		

	transfer_command_lcd(0x75);		//Set Page Address	
	transfer_data_lcd(y);		
	transfer_data_lcd(y+y_total);	
	transfer_command_lcd(0x30);	
	transfer_command_lcd(0x5c);	
}

//清屏
void clear_screen()
{
	int i,j;	
	lcd_address(0,0,241,21);
	for(i=0;i<21;i++)
	{
		for(j=0;j<241;j++)
		{
			transfer_data_lcd(0x00);
		}
	}
}

void test(void)
{
	const uint8_t *data[] = {_dian_1616, _ya_1616, _liou_1616, _zhuang_1616, NULL};

	Clear_Lcd_Buff();
	Dis_Asc_Char(0, 0, ASC_8_8, (uint8_t *)"s", 8, 8, PURECOLOR);
	Dis_Asc_Char(100, 10, ASC_8_16, (uint8_t *)"z", 8, 16, INVERTED);
	Dis_Asc_Str(200, 6, ASC_8_8, (uint8_t *)"usb", 8, 8, PURECOLOR);
	Dis_Asc_Char(230, 19, ASC_8_8, (uint8_t *)"y", 8, 8, PURECOLOR);

	Dis_16_16_Str(100, 14, data, PURECOLOR);

	Dis_line(0, 3, 240, PURECOLOR);
	Dis_line(0, 15, 240, PURECOLOR);
	
	Refresh_Screen();
}

/*********************************************************************//**
 * @brief 		将显存中的数据扔到屏幕上
 * @param[in] 	
 * @return 		
 **********************************************************************/
void Refresh_Screen(void)
{
	I2C_M_SETUP_Type txsetup;
	uint8_t cmd = 0xC0;
	uint8_t *cursor = NULL; 
	int i = 0, j = 0;

	//cursor = mymalloc(LCD_X_PIXEL+1);

	for(i=0; i<LCD_Y_PAGE; i++)
	{
		lcd_address(0, i, 240, 1);

		for(j=0; j<LCD_X_PIXEL; j++)
			transfer_data_lcd(Lcd_Buff[i][j]);

		/*
		//此处存疑
		//这里本来是想连续写LCD的显示RAM，提高写入效率的，但发现这个LCD好像不支持连续写入
		memset(cursor, 0x00, x+1);
		memcpy((char *)cursor, (char *)&cmd, 1);
		memcpy((char *)cursor + 1, (char *)Lcd_Buff[i], x);
		
		txsetup.sl_addr7bit = 0x3C;
		txsetup.tx_data = cursor;
		txsetup.tx_length = x + 1;
		txsetup.rx_data = NULL;
		txsetup.rx_length = 0;
		txsetup.retransmissions_max = 1;

		if (I2C_MasterTransferData(LCDI2CDEV, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS)
		{
			PRINTF("i2c OK!\n");
		} 
		else 
		{
			PRINTF("i2c error!\n");
		} 
		*/
		
	}
	//myfree(cursor);
}

