
/**********************************************************************
* @brief	UI��ʼ������
* @version	1.0
* @date		2019 03 23
* @author	shiyu
*
* All rights reserved.
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "LCDFont.h"
#include "video_memory.h"
#include "multi_menu.h"
#include "system_manage.h"

/*********************************************************************//**
 * @brief 		����ҳ���ʼ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void page_start_init(struct Menu * this)
{
	//ϵͳ���ڳ�ʼ��
	const uint8_t * row_1[] = {_xi1_1616, _tong_1616, _chu2_1616, _shi2_1616, _hua_1616, NULL};

	Dis_16_16_Str(50, 10, row_1, PURECOLOR);
}

/*********************************************************************//**
 * @brief 		���ҳ���ʼ��
 * @param[in] 	
 * @return 		
 **********************************************************************/
void page_monitor_init(struct Menu * this)
{
	//����״̬
	const uint8_t * row_1[] = {_xi1_1616, _tong_1616, _chu2_1616, _shi2_1616, _hua_1616, _fenhao_1616, NULL};
	//�¶�
	const uint8_t * row_2[] = {_wen_1616, _du_1616, _fenhao_1616, NULL};
	//��ն�
	const uint8_t * row_3[] = {_zhen_1616, _kong_1616, _du_1616, _fenhao_1616, NULL};

	Dis_16_16_Str(50, 4, row_1, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);
}

/*********************************************************************//**
 * @brief		����-����ҳ���ʼ��
 * @param[in]	
 * @return		
 **********************************************************************/
void page_opera_start_init(struct Menu * this)
{
	//�Ƿ��������±ã�
	const uint8_t * row_1[] = {_shi5_1616, _fou_1616, _qi_1616, _dong_1616, _di_1616, _wen_1616, _be_1616, _wenhao_1616, NULL};
	//��ȷ�ϼ�����
	const uint8_t * row_2[] = {_an_1616, _du_1616, _fenhao_1616, NULL};
	//�����ؼ��˳�
	const uint8_t * row_3[] = {_zhen_1616, _kong_1616, _du_1616, _fenhao_1616, NULL};

	//���ؼ�
	const uint8_t * row_4_1[] = {_fan_1616, _huei_1616, NULL};
	//ȷ�ϼ�
	const uint8_t * row_4_2[] = {_que_1616, _ren_1616, NULL};

	Dis_16_16_Str(50, 4, row_1, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);

	//��ʾ���ؼ�
	Dis_16_16_Str(10, 14, row_4_1, INVERTED);
	//��ʾȷ�ϼ�
	Dis_16_16_Str(200, 14, row_4_2, INVERTED);
}

/*********************************************************************//**
 * @brief		����-ֹͣҳ���ʼ��
 * @param[in]	
 * @return		
 **********************************************************************/
void page_opera_stop_init(struct Menu * this)
{
	//�Ƿ�ֹͣ���±ã�
	const uint8_t * row_1[] = {_shi5_1616, _fou_1616, _ting_1616, _zhi6_1616, _di_1616, _wen_1616, _be_1616, _wenhao_1616, NULL};
	//��ȷ��������
	const uint8_t * row_2[] = {_an_1616, _du_1616, _fenhao_1616, NULL};
	//�����ؼ��˳�
	const uint8_t * row_3[] = {_zhen_1616, _kong_1616, _du_1616, _fenhao_1616, NULL};

	//���ؼ�
	const uint8_t * row_4_1[] = {_fan_1616, _huei_1616, NULL};
	//ȷ�ϼ�
	const uint8_t * row_4_2[] = {_que_1616, _ren_1616, NULL};

	Dis_16_16_Str(50, 4, row_1, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);

	//��ʾ���ؼ�
	Dis_16_16_Str(10, 14, row_4_1, INVERTED);
	//��ʾȷ�ϼ�
	Dis_16_16_Str(200, 14, row_4_2, INVERTED);
}

/*********************************************************************//**
 * @brief		����-����ҳ���ʼ��
 * @param[in]	
 * @return		
 **********************************************************************/
void page_opera_regenerate_init(struct Menu * this)
{
	//�Ƿ��������±ã�
	const uint8_t * row_1[] = {_shi5_1616, _fou_1616, _zai_1616, _sheng1_1616, _di_1616, _wen_1616, _be_1616, _wenhao_1616, NULL};
	//��ȷ��������
	const uint8_t * row_2[] = {_an_1616, _du_1616, _fenhao_1616, NULL};
	//�����ؼ��˳�
	const uint8_t * row_3[] = {_zhen_1616, _kong_1616, _du_1616, _fenhao_1616, NULL};

	//���ؼ�
	const uint8_t * row_4_1[] = {_fan_1616, _huei_1616, NULL};
	//ȷ�ϼ�
	const uint8_t * row_4_2[] = {_que_1616, _ren_1616, NULL};


	Dis_16_16_Str(50, 4, row_1, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);

	//��ʾ���ؼ�
	Dis_16_16_Str(10, 14, row_4_1, INVERTED);
	//��ʾȷ�ϼ�
	Dis_16_16_Str(200, 14, row_4_2, INVERTED);
}

/*********************************************************************//**
 * @brief		����-�Աȶ�ҳ���ʼ��
 * @param[in]	
 * @return		
 **********************************************************************/
void page_set_contrast_init(struct Menu * this)
{
	char str[5];

	//��ǰֵ��
	const uint8_t * row_2[] = {_dang_1616, _qian1_1616, _zhi3_1616, _fenhao_1616, NULL};
	//����ֵ��
	const uint8_t * row_3[] = {_chong_1616, _she_1616, _zhi3_1616, _fenhao_1616,  NULL};

	//���ؼ�
	const uint8_t * row_4_1[] = {_fan_1616, _huei_1616, NULL};
	//ȷ�ϼ�
	const uint8_t * row_4_2[] = {_que_1616, _ren_1616, NULL};

	Dis_16_16_Str(50, 4, this->menu_name, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);

	//��ʾ��ǰֵ
	sprintf(str, "%d", gSystem_Parameter.contrast);
	Dis_Asc_Str(120, 7, ASC_8_16, (uint8_t *)str, 8, 16, PURECOLOR);
	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.contrast_reset);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);


	//��ʾ���ؼ�
	Dis_16_16_Str(10, 14, row_4_1, INVERTED);
	//��ʾȷ�ϼ�
	Dis_16_16_Str(200, 14, row_4_2, INVERTED);
}


/*********************************************************************//**
 * @brief		����-�Աȶ�ҳ���ʼ��
 * @param[in]	
 * @return		
 **********************************************************************/
void page_set_backlight_init(struct Menu * this)
{
	char str[5];

	//��ǰֵ��
	const uint8_t * row_2[] = {_dang_1616, _qian1_1616, _zhi3_1616, _fenhao_1616, NULL};
	//����ֵ��
	const uint8_t * row_3[] = {_chong_1616, _she_1616, _zhi3_1616, _fenhao_1616,  NULL};

	//���ؼ�
	const uint8_t * row_4_1[] = {_fan_1616, _huei_1616, NULL};
	//ȷ�ϼ�
	const uint8_t * row_4_2[] = {_que_1616, _ren_1616, NULL};

	Dis_16_16_Str(50, 4, this->menu_name, PURECOLOR);
	Dis_16_16_Str(50, 7, row_2, PURECOLOR);
	Dis_16_16_Str(50, 10, row_3, PURECOLOR);

	//��ʾ��ǰֵ
	sprintf(str, "%d", gSystem_Parameter.backlight);
	Dis_Asc_Str(120, 7, ASC_8_16, (uint8_t *)str, 8, 16, PURECOLOR);
	//��ʾ����ֵ
	sprintf(str, "%d", gSystem_Manage.backlight_reset);
	Dis_Asc_Str(120, 10, ASC_8_16, (uint8_t *)str, 8, 16, INVERTED);


	//��ʾ���ؼ�
	Dis_16_16_Str(10, 14, row_4_1, INVERTED);
	//��ʾȷ�ϼ�
	Dis_16_16_Str(200, 14, row_4_2, INVERTED);

}


