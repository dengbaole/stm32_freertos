#include "platform.h"
#include "bsp_led.h"
#include "bsp_key.h"


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
QueueHandle_t Test_Queue = NULL;	/* 用于测试的消息队列 */

SemaphoreHandle_t BinarySem_Handle = NULL; /* 二值信号量句柄 */

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
TaskHandle_t RECEIVE_Task_Handle = NULL;
TaskHandle_t binarysam_task_Handle = NULL;

/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */



void queue_send(uint8_t key_num) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	uint32_t send_data1 = key_num;
	xReturn = xQueueSend( Test_Queue, /* 消息队列的句柄 */
						  &send_data1,/* 发送的消息内容 */
						  0 );        /* 等待时间 0 */
}

void binarysem_send(void) {
	BaseType_t xReturn = xSemaphoreGive( BinarySem_Handle );//给出二值信号量
	if( xReturn == pdTRUE ){
		printf("BinarySem_Handle二值信号量释放成功!\r\n");
	} else{
		printf("BinarySem_Handle二值信号量释放失败!\r\n");
	}
}




void AppTaskCreate(void* parameter) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

	taskENTER_CRITICAL();           //进入临界区

	Test_Queue = xQueueCreate((UBaseType_t ) QUEUE_LEN,/* 消息队列的长度 */
							  (UBaseType_t ) QUEUE_SIZE);/* 消息的大小 */
	if(NULL != Test_Queue) {
		printf("创建Test_Queue消息队列成功!\r\n");
	}
	/* 创建 BinarySem */
	BinarySem_Handle = xSemaphoreCreateBinary();
	if(NULL != BinarySem_Handle) {
		printf("BinarySem_Handle二值信号量创建成功!\r\n");
	}
	// /* 创建LED_Task任务 */
	// xReturn = xTaskCreate((TaskFunction_t )ledr_task, /* 任务入口函数 */
	// 					  (const char*    )"ledr_task",/* 任务名字 */
	// 					  (uint16_t       )512,   /* 任务栈大小 */
	// 					  (void*          )NULL,	/* 任务入口函数参数 */
	// 					  (UBaseType_t    )2,	    /* 任务的优先级 */
	// 					  (TaskHandle_t*  )&LEDB_Task_Handle);/* 任务控制块指针 */
	xReturn = xTaskCreate(ledr_task, "ledr_task", 128, NULL, 2, &LEDB_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建LEDR_Task任务成功!\r\n");
	}

	xReturn = xTaskCreate(ledg_task, "ledg_task", 128, NULL, 2, &LEDG_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建LEDG_Task任务成功!\r\n");
	}

	xReturn = xTaskCreate(key_task, "key_task", 128, NULL, 2, &KEY_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建KEY_Task任务成功!\r\n");
	}
	xReturn = xTaskCreate(queue_receive_task, "queue_receive_task", 128, NULL, 2, &RECEIVE_Task_Handle);
	if(pdPASS == xReturn) {
		printf("创建queue_receive_task任务成功!\r\n");
	}
	xReturn = xTaskCreate(binarysam_receive_task, "binarysam_receive_task", 128, NULL, 2, &binarysam_task_Handle);
	if(pdPASS == xReturn) {
		printf("创建binarysam_receive_task任务成功!\r\n");
	}

	vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务

	taskEXIT_CRITICAL();            //退出临界区
}



static void ledr_task(void* parameter) {
	static uint8_t i = 0;
	while (1) {
		i++;
		LEDR_ON;
		vTaskDelay(800);   /* 延时500个tick */
		printf("ledr_task Running,LEDB_ON\r\n");
		LEDR_OFF;
		vTaskDelay(800);   /* 延时500个tick */
		printf("ledr_task Running,LEDB_OFF\r\n");
	}
}


static void ledg_task(void* parameter) {
	static uint8_t i = 0;
	while (1) {
		i++;
		LEDG_ON;
		vTaskDelay(1000);   /* 延时500个tick */
		printf("ledr_task Running,LEDG_ON\r\n");
		LEDG_OFF;
		vTaskDelay(1000);   /* 延时500个tick */
		printf("ledr_task Running,LEDG_OFF\r\n");
	}
}



static void key_task(void* parameter) {
	static portTickType PreviousWakeTime;
	const portTickType TimeIncrement = pdMS_TO_TICKS(10);
	PreviousWakeTime = xTaskGetTickCount();
	while (1) {
		key_handle_10ms();
		// vTaskDelay(10);/* 延时20个tick */
		vTaskDelayUntil( &PreviousWakeTime, TimeIncrement ); //绝对延时
	}
}

/// @brief 消息队列接收任务
/// @param parameter
static void queue_receive_task(void* parameter) {
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint32_t r_queue;	/* 定义一个接收消息的变量 */
	while (1) {
		xReturn = xQueueReceive(Test_Queue,    /* 消息队列的句柄 */
								&r_queue,      /* 发送的消息内容 */
								portMAX_DELAY); /* 等待时间 一直等 */
		if(pdTRUE == xReturn) {
			printf("本次接收到的数据是%d\n\n", r_queue);
		} else {
			printf("数据接收出错,错误代码0x%lx\n", xReturn);
		}
	}
}

/// @brief 信号量接收任务
/// @param parameter
static void binarysam_receive_task(void* parameter) {
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	while (1) {
		//获取二值信号量 xSemaphore,没获取到则一直等待(阻塞不参与任务调度)
		xReturn = xSemaphoreTake(BinarySem_Handle,/* 二值信号量句柄 */
								 portMAX_DELAY); /* 等待时间 */
		if(pdTRUE == xReturn) {
			printf("BinarySem_Handle二值信号量获取成功!\n\n");
		}
	}
}