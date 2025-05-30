#ifndef __PLATFORM_H
#define	__PLATFORM_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define  QUEUE_LEN    4   /* 队列的长度，最大可包含多少个消息 */
#define  QUEUE_SIZE   1   /* 队列中每个消息大小（字节） */

extern TaskHandle_t AppTaskCreate_Handle;
/* LED任务句柄 */
extern TaskHandle_t LEDB_Task_Handle;
extern TaskHandle_t LEDG_Task_Handle;
extern TaskHandle_t KEY_Task_Handle;


extern TaskHandle_t AppTaskCreate_Handle;
/* LED任务句柄 */
extern TaskHandle_t LEDB_Task_Handle;
extern TaskHandle_t LEDG_Task_Handle;

void queue_send(uint8_t key_num);
void AppTaskCreate(void* parameter);
static void ledr_task(void* parameter);
static void ledg_task(void* parameter);
static void key_task(void* parameter);
static void Receive_Task(void* parameter);

#endif

