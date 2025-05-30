#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"
#include "platform.h"

#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY1_GPIO_PORT    GPIOC
#define    KEY1_GPIO_PIN	 GPIO_Pin_6

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY2_GPIO_PORT    GPIOC
#define    KEY2_GPIO_PIN     GPIO_Pin_13


#define KEY_ON	0
#define KEY_OFF	1

#define KEY_IN_DEBOUNCE                 (2)
void key_gpio_config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif /* __KEY_H */

