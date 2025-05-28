/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-霸道 STM32 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include "bsp_led.h"

/**
 * @brief  初始化控制LED的IO
 * @param  无
 * @retval 无
 */
void LED_GPIO_Config(void) {
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启LED相关的GPIO外设时钟*/
	RCC_APB2PeriphClockCmd( LEDB_GPIO_CLK | LEDR_GPIO_CLK | LEDG_GPIO_CLK, ENABLE);
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LEDB_GPIO_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LEDB_GPIO_PORT, &GPIO_InitStructure);

	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LEDR_GPIO_PIN;

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LEDR_GPIO_PORT, &GPIO_InitStructure);

	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LEDG_GPIO_PIN;

	/*调用库函数，初始化GPIOF*/
	GPIO_Init(LEDG_GPIO_PORT, &GPIO_InitStructure);

	/* 关闭所有led灯	*/
	GPIO_SetBits(LEDB_GPIO_PORT, LEDB_GPIO_PIN);

	/* 关闭所有led灯	*/
	GPIO_SetBits(LEDR_GPIO_PORT, LEDR_GPIO_PIN);

	/* 关闭所有led灯	*/
	GPIO_SetBits(LEDG_GPIO_PORT, LEDG_GPIO_PIN);
}


/*********************************************END OF FILE**********************/
