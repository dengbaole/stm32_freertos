
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "bsp_usart.h"

/**************************** 任务句柄 ********************************/
/*
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
/* 创建任务句柄 */
static TaskHandle_t AppTaskCreate_Handle = NULL;
/* LED任务句柄 */
static TaskHandle_t LED_Task_Handle = NULL;

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


/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void AppTaskCreate(void);/* 用于创建任务 */

static void LED_Task(void* pvParameters);/* LED_Task任务实现 */

static void BSP_Init(void);/* 用于初始化板载相关资源 */

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：开发板硬件初始化
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/
int main(void) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

	/* 开发板硬件初始化 */
	BSP_Init();
	printf("动态创建任务!\r\n");
	/* 创建AppTaskCreate任务 */
	// xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
	// 					  (const char*    )"AppTaskCreate",/* 任务名字 */
	// 					  (uint16_t       )512,  /* 任务栈大小 */
	// 					  (void*          )NULL,/* 任务入口函数参数 */
	// 					  (UBaseType_t    )1, /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(AppTaskCreate, "AppTaskCreate", 512, NULL, 1, &AppTaskCreate_Handle);
	/* 启动任务调度 */
	if(pdPASS == xReturn)
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	else
		return -1;

	while(1);   /* 正常不会执行到这里 */
}


/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

	taskENTER_CRITICAL();           //进入临界区

	// /* 创建LED_Task任务 */
	// xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* 任务入口函数 */
	// 					  (const char*    )"LED_Task",/* 任务名字 */
	// 					  (uint16_t       )512,   /* 任务栈大小 */
	// 					  (void*          )NULL,	/* 任务入口函数参数 */
	// 					  (UBaseType_t    )2,	    /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&LED_Task_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(LED_Task, "LED_Task", 512, NULL, 2, &LED_Task_Handle);
	if(pdPASS == xReturn)
		printf("创建LED_Task任务成功!\r\n");

	vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务

	taskEXIT_CRITICAL();            //退出临界区
}



/**********************************************************************
  * @ 函数名  ： LED_Task
  * @ 功能说明： LED_Task任务主体
  * @ 参数    ：
  * @ 返回值  ： 无
  ********************************************************************/
static void LED_Task(void* parameter) {
	static uint8_t i = 0;
	while (1) {
		i++;
		if(i % 3 == 0) {
			LEDB_ON;
		} else if(i % 3 == 1) {
			LEDR_ON;
		} else {
			LEDG_ON;
		}

		vTaskDelay(500);   /* 延时500个tick */
		printf("LED_Task Running,LEDB_ON\r\n");

		LEDG_OFF;
		LEDR_OFF;
		LEDB_OFF;
		vTaskDelay(500);   /* 延时500个tick */
		printf("LED_Task Running,LEDB_OFF\r\n");
	}
}

/***********************************************************************
  * @ 函数名  ： BSP_Init
  * @ 功能说明： 板级外设初始化，所有板子上的初始化均可放在这个函数里面
  * @ 参数    ：
  * @ 返回值  ： 无
  *********************************************************************/
static void BSP_Init(void) {
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	LED_GPIO_Config();
	USART_Config();

}

/********************************END OF FILE****************************/
