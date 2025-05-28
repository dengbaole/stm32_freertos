/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include "bsp_led.h"

/**
 * @brief  ��ʼ������LED��IO
 * @param  ��
 * @retval ��
 */
void LED_GPIO_Config(void) {
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_APB2PeriphClockCmd( LEDB_GPIO_CLK | LEDR_GPIO_CLK | LEDG_GPIO_CLK, ENABLE);
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LEDB_GPIO_PIN;

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*������������Ϊ50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LEDB_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LEDR_GPIO_PIN;

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LEDR_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LEDG_GPIO_PIN;

	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(LEDG_GPIO_PORT, &GPIO_InitStructure);

	/* �ر�����led��	*/
	GPIO_SetBits(LEDB_GPIO_PORT, LEDB_GPIO_PIN);

	/* �ر�����led��	*/
	GPIO_SetBits(LEDR_GPIO_PORT, LEDR_GPIO_PIN);

	/* �ر�����led��	*/
	GPIO_SetBits(LEDG_GPIO_PORT, LEDG_GPIO_PIN);
}


/*********************************************END OF FILE**********************/
