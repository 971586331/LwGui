
/**********************************************************************
* @brief	UI�˵��������
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/

#include "video_memory.h"
#include "LCDFont.h"
#include "multi_menu.h"

/*********************************************************************//**
 * @brief 		ͨ�õĲ˵��������
 * @param[in] 	
 * @return 		
 **********************************************************************/
void general_menu_process_engine(struct Menu * this)
{
	int i = 0, j = 0;
	int page_num = 0;

	//���˵��������ľ���
	Dis_Rectangle(32,4,180,32,PURECOLOR);

	//���˵�ͼ��
	Dis_Image(48, 5, _list_1616, 16, 16, PURECOLOR);
	Dis_Image(180, 5, _list_1616, 16, 16, PURECOLOR);

	//��ʾ�˵�����
	Dis_16_16_Str(100 , 5, this->menu_name, PURECOLOR);

	//�����ҳ��ʾ��ҳ��
	this->record_sub_num < 4 ? (page_num = 0):(page_num = this->record_sub_num/4);
	for(i=0; i<4; i++)
	{
		//���㵱ǰ��ʾ�Ĳ˵���
		j = page_num*4 + i;
		if (j < this->menu_num)
		{

			//����ڵ�ǰ���ɫ��ʾ
			if(this->record_sub_num == j)
			{
				//��ʾ���
				Dis_Image(32, 8+i*2,  numero_1616[j+1], 16, 16, INVERTED);
				//��ʾ�˵�����
				Dis_16_16_Str(48, 8+i*2 , this->sub_menu_name[j], INVERTED);
				if ((this->submenuPtr[j])->menu_num != 0)	
					Dis_Image(200, 8+i*2, _arrow_1616, 16, 16, INVERTED);
			}
			else
			{
				//��ʾ���
				Dis_Image(32, 8+i*2, numero_1616[j+1], 16, 16, PURECOLOR);
				//��ʾ�˵�����
				Dis_16_16_Str(48, 8+i*2, this->sub_menu_name[j], PURECOLOR);
				if ((this->submenuPtr[j])->menu_num != 0)	
					Dis_Image(200, 8+i*2, _arrow_1616, 16, 16, PURECOLOR);
			}
		}
		else	//���һҳ��ʾ����С��4�ʣ�µ���հ�
		{
			Dis_Image(48, 8+i*2, _spac_1616, 16, 16, PURECOLOR);
		}
	}
}


