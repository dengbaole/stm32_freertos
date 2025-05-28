#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
// R-��ɫ
#define LEDB_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LEDB_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LEDB_GPIO_PIN		GPIO_Pin_0			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// G-��ɫ
#define LEDR_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LEDR_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LEDR_GPIO_PIN		GPIO_Pin_1			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// B-��ɫ
#define LEDG_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define LEDG_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LEDG_GPIO_PIN		GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */


/** the macro definition to trigger the led on or off
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* ʹ�ñ�׼�Ĺ̼������IO*/
#define LEDB(a)	if (a)	\
		GPIO_SetBits(LEDB_GPIO_PORT,LEDB_GPIO_PIN);\
	else		\
		GPIO_ResetBits(LEDB_GPIO_PORT,LEDB_GPIO_PIN)

#define LEDR(a)	if (a)	\
		GPIO_SetBits(LEDR_GPIO_PORT,LEDR_GPIO_PIN);\
	else		\
		GPIO_ResetBits(LEDR_GPIO_PORT,LEDR_GPIO_PIN)

#define LEDG(a)	if (a)	\
		GPIO_SetBits(LEDG_GPIO_PORT,LEDG_GPIO_PIN);\
	else		\
		GPIO_ResetBits(LEDG_GPIO_PORT,LEDG_GPIO_PIN)


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
#define LEDB_TOGGLE		 digitalToggle(LEDB_GPIO_PORT,LEDB_GPIO_PIN)
#define LEDB_OFF		   digitalHi(LEDB_GPIO_PORT,LEDB_GPIO_PIN)
#define LEDB_ON			   digitalLo(LEDB_GPIO_PORT,LEDB_GPIO_PIN)

#define LEDR_TOGGLE		 digitalToggle(LEDR_GPIO_PORT,LEDR_GPIO_PIN)
#define LEDR_OFF		   digitalHi(LEDR_GPIO_PORT,LEDR_GPIO_PIN)
#define LEDR_ON			   digitalLo(LEDR_GPIO_PORT,LEDR_GPIO_PIN)

#define LEDG_TOGGLE		 digitalToggle(LEDG_GPIO_PORT,LEDG_GPIO_PIN)
#define LEDG_OFF		   digitalHi(LEDG_GPIO_PORT,LEDG_GPIO_PIN)
#define LEDG_ON			   digitalLo(LEDG_GPIO_PORT,LEDG_GPIO_PIN)

/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
	LEDB_ON;\
	LEDR_OFF\
	LEDG_OFF

//��
#define LED_GREEN		\
	LEDB_OFF;\
	LEDR_ON\
	LEDG_OFF

//��
#define LED_BLUE	\
	LEDB_OFF;\
	LEDR_OFF\
	LEDG_ON


//��(��+��)
#define LED_YELLOW	\
	LEDB_ON;\
	LEDR_ON\
	LEDG_OFF
//��(��+��)
#define LED_PURPLE	\
	LEDB_ON;\
	LEDR_OFF\
	LEDG_ON

//��(��+��)
#define LED_CYAN \
	LEDB_OFF;\
	LEDR_ON\
	LEDG_ON

//��(��+��+��)
#define LED_WHITE	\
	LEDB_ON;\
	LEDR_ON\
	LEDG_ON

//��(ȫ���ر�)
#define LED_RGBOFF	\
	LEDB_OFF;\
	LEDR_OFF\
	LEDG_OFF

void LED_GPIO_Config(void);

#endif /* __LED_H */
