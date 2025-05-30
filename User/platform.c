#include "platform.h"
#include "bsp_led.h"
#include "bsp_key.h"



/**************************** 任务句柄 ********************************/
/*
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
/* 创建任务句柄 */
TaskHandle_t AppTaskCreate_Handle = NULL;
/* LED任务句柄 */
TaskHandle_t LEDB_Task_Handle = NULL;
TaskHandle_t LEDG_Task_Handle = NULL;
TaskHandle_t KEY_Task_Handle = NULL;



void AppTaskCreate(void* parameter) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

	taskENTER_CRITICAL();           //进入临界区

	// /* 创建LED_Task任务 */
	// xReturn = xTaskCreate((TaskFunction_t )ledr_task, /* 任务入口函数 */
	// 					  (const char*    )"ledr_task",/* 任务名字 */
	// 					  (uint16_t       )512,   /* 任务栈大小 */
	// 					  (void*          )NULL,	/* 任务入口函数参数 */
	// 					  (UBaseType_t    )2,	    /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&LEDB_Task_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(ledr_task, "ledr_task", 512, NULL, 2, &LEDB_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建LEDR_Task任务成功!\r\n");
	}

	xReturn = xTaskCreate(ledg_task, "ledg_task", 512, NULL, 2, &LEDG_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建LEDG_Task任务成功!\r\n");
	}

	xReturn = xTaskCreate(key_task, "key_task", 512, NULL, 2, &KEY_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建KEY_Task任务成功!\r\n");
	}

	vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务

	taskEXIT_CRITICAL();            //退出临界区
}



static void ledr_task(void* parameter) {
	static uint8_t i = 0;
	while (1) {
		i++;
		LEDR_ON;
		vTaskDelay(500);   /* 延时500个tick */
		printf("ledr_task Running,LEDB_ON\r\n");
		LEDR_OFF;
		vTaskDelay(500);   /* 延时500个tick */
		printf("ledr_task Running,LEDB_OFF\r\n");
	}
}


static void ledg_task(void* parameter) {
	static uint8_t i = 0;
	while (1) {
		i++;
		LEDG_ON;
		vTaskDelay(250);   /* 延时500个tick */
		printf("ledr_task Running,LEDG_ON\r\n");
		LEDG_OFF;
		vTaskDelay(250);   /* 延时500个tick */
		printf("ledr_task Running,LEDG_OFF\r\n");
	}
}



static void key_task(void* parameter) {
	static portTickType PreviousWakeTime; 
	const portTickType TimeIncrement = pdMS_TO_TICKS(1000); 
	PreviousWakeTime = xTaskGetTickCount();
	while (1) {
		key_handle_10ms();
		// vTaskDelay(10);/* 延时20个tick */
		vTaskDelayUntil( &PreviousWakeTime,TimeIncrement );//绝对延时
	}
}

