
#ifndef __BSP_SEG_H
#define __BSP_SEG_H

#include "stm32f10x.h"
#define   true 1
#define   false 0
#define KEY_GPIO_Port   GPIOC
#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOC

#define KEY1_GPIO_Pin       GPIO_Pin_0
#define KEY2_GPIO_Pin       GPIO_Pin_1
#define KEY3_GPIO_Pin       GPIO_Pin_2

/** �������±��ú�
* ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
* ����������Ϊ�͵�ƽ���Ѻ����ó� KEY_ON=0 ��KEY_OFF=1 ����
*/
#define KEY_UP             1
#define KEY_DOWN           0


void KEY_GPIO_Config(void);
uint32_t  KEY_SCAN(GPIO_TypeDef*   GPIOx   , uint16_t  GPIO_Pin);
#endif /*__BSP_LED_H*/

