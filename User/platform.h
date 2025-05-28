#ifndef __PLATFORM_H
#define	__PLATFORM_H

#include "FreeRTOS.h"
#include "task.h"


extern TaskHandle_t AppTaskCreate_Handle;
/* LED任务句柄 */
extern TaskHandle_t LEDB_Task_Handle;
extern TaskHandle_t LEDG_Task_Handle;

void AppTaskCreate(void* parameter);
static void ledr_task(void* parameter);
static void ledg_task(void* parameter);

#endif

