
#ifndef __BSP_LED_H
#define __BSP_LED_H
#define State  uint32_t
#include "stm32f10x.h"

/*�ܽ������LEDƬ����������Ĺܽ�,���ﶨ��ľ���LED�Ĺܽź�GPIO�����Ĺܽŵ���ϵ*/
#define LED_0_GPIO_Pin   GPIO_Pin_8     //������L0������GPIO�ĵڰ˸��ܽ�
#define LED_1_GPIO_Pin   GPIO_Pin_9 
#define LED_2_GPIO_Pin   GPIO_Pin_10  
#define LED_3_GPIO_Pin   GPIO_Pin_11  
#define LED_4_GPIO_Pin   GPIO_Pin_12  
#define LED_5_GPIO_Pin   GPIO_Pin_13  
#define LED_6_GPIO_Pin   GPIO_Pin_14  
#define LED_7_GPIO_Pin   GPIO_Pin_15  

#define LED_GPIO_Port  GPIOE          // LED/SEG �õ���GPIOE
#define LED_GPIO_CLK  RCC_APB2Periph_GPIOE  //����㿪stm32f10x_rcc.c������һ�¹ؼ��֣������������ƶ�����
#define LED_AFIO_CLK  RCC_APB2Periph_AFIO //���ö˿ڵ�ʱ��

/*  seg:segment,�������һ��һ����ʾ�ģ���ȡ��SEG
**  SEL��ȡselectǰ������ĸ
**  ��ΪSEG��LED�����ˣ�����д����һ��
*/
#define SEL_GPIO_0_Pin      GPIO_Pin_0//0��2������λ����Ϊ8�������ֻ��˭����״̬
#define SEL_GPIO_1_Pin      GPIO_Pin_1
#define SEL_GPIO_2_Pin     GPIO_Pin_2
#define SEL_GPIO_3_Pin     GPIO_Pin_3//�������������֮�󣬶�Ӧ����λ���1��LED��Ч������λ���0���������Ч
#define SEL_GPIO_Port   GPIOB     //SELECT �õ���GPIOB
#define SEL_GPIO_CLK    RCC_APB2Periph_GPIOB//��ѡ��LED/SEGѡ���GPIOBʱ��

#define Select_LED        0
#define Select_SEG        1


void LED_SEG_CLK_Init(void);
void LED_SEG_GPIO_Config(void);
void SEL_GPIO_Config(void);
void LED_SEG_Select_CMD(State NewState);

 
void AFIO_Init(void);
#endif /*__BSP_LED_H*/

