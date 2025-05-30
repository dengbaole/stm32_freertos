
#include "bsp_key.h"

static uint8_t key_execution_countdown;
static uint8_t key_pressed_cnt;
static uint8_t key_times;
uint8_t key_release_falg = 0;  //0释放



void key_gpio_config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK | KEY2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
}



uint8_t is_key_on(void) {
	return GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON;
}



static void key_execution(uint8_t key_time_cnt) {
	switch (key_time_cnt) {
		case 1:
			printf("Suspend_LEDG_handle\n");
			// vTaskSuspendAll必须和xTaskResumeAll成对出现
			// vTaskSuspendAll();/* 挂起调度器 */
			// xTaskResumeAll();/* 解挂调度器 */
			//不支持挂起嵌套，没有挂起计数，只需要调用一次就能解挂起
			vTaskSuspend(LEDG_Task_Handle);/* 挂起LED任务 */
			printf("Suspend_LEDG_handle!\n");
			break;
		case 2:
			printf("Resume_LEDG_handle\n");
			vTaskResume(LEDG_Task_Handle);/* 恢复LED任务！ */
			//中断中需要执行这个函数
			// xTaskResumeFromISR(LEDG_Task_Handle);
			printf("Resume_LEDG_handle\n");
			break;
		case 3:
			break;
		case 4:

			break;
		case 5:
			break;
		default:
			break;
	}
	key_times = 0;
}

void key_handle_10ms(void) {
	if(is_key_on()) {
		if(key_pressed_cnt < 250) {
			key_pressed_cnt++;
			if(key_pressed_cnt == 200) {
				// event_push(EVT_BUTTONLONG);
			}
		}
		if(key_pressed_cnt == KEY_IN_DEBOUNCE) {
			key_release_falg = 5;
			key_times++;
			if(key_times >= 5) {
				key_times = 5;
			}
			key_execution_countdown = 50;
		}
	} else {
		key_pressed_cnt = 0;
		if(key_release_falg > 0) {
			key_release_falg--;
		}
	}

	if(key_execution_countdown > 0) {
		key_execution_countdown--;
		if (key_execution_countdown == 0) {
			key_execution_countdown = 0;
			key_execution(key_times);
			key_times = 0;
		}
	}
}




