
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "platform.h"


/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 *
 */


/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */







static void BSP_Init(void) {
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

	BSP_Init();
	printf("动态创建任务!\n");
	/* 创建AppTaskCreate任务 */
	// xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
	// 					  (const char*    )"AppTaskCreate",/* 任务名字 */
	// 					  (uint16_t       )512,  /* 任务栈大小 */
	// 					  (void*          )NULL,/* 任务入口函数参数 */
	// 					  (UBaseType_t    )1, /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(AppTaskCreate, "AppTaskCreate", 512, NULL, 1, &AppTaskCreate_Handle);
	/* 启动任务调度 */
	if(pdPASS == xReturn) {
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	} else {
		return -1;
	}

	while(1);   /* 正常不会执行到这里 */
}




