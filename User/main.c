
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "platform.h"
#include "bsp_key.h"




/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */







static void platform_init(void) {
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	LED_GPIO_Config();
	USART_Config();
	key_gpio_config();
}




int main(void) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	platform_init();
	//printf("动态创建任务!\n");
	/* 创建AppTaskCreate任务 */
	// xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
	// 					  (const char*    )"AppTaskCreate",/* 任务名字 */
	// 					  (uint16_t       )512,  /* 任务栈大小 */
	// 					  (void*          )NULL,/* 任务入口函数参数 */
	// 					  (UBaseType_t    )1, /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(AppTaskCreate, "AppTaskCreate", 128, NULL, 1, &AppTaskCreate_Handle);
	/* 启动任务调度 */
	if(pdPASS == xReturn) {
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	} else {
		return -1;
	}

	while(1);   /* 正常不会执行到这里 */
}




