/*bsp   �弶֧�ְ�����˼*/

#include "bsp_led.h"

/*  @brief:���￪�������/LED������ʱ��+����ѡ���GPIOB��ʱ��+AFIO���ö˿ڵ�ʱ��
*
*
*/
void LED_SEG_CLK_Init(void){
  /*��������ʱ�ӣ�Ϊʲô���������ʱ�ӣ����Բο�ST�����ֲᣬ2.1ϵͳ�ܹ���RCC��APB2���ӵ�����*/
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);//ʹ������ܺ�LED������ʱ��
  RCC_APB2PeriphClockCmd(SEL_GPIO_CLK, ENABLE);//ʹ��select�� GPIOB clock
  RCC_APB2PeriphClockCmd(LED_AFIO_CLK, ENABLE);//ʹ�ܸ��ö˿�ʱ��
}

/*  @brief  ����� LED/SEG+����ѡ�� ������Ĵ���ȫ������Ϊ�������
*
*
*/
void LED_SEG_GPIO_Config(void){
    uint32_t x=0;
    uint32_t LED_x_GPIO_Pin[]={
    LED_0_GPIO_Pin,LED_1_GPIO_Pin,LED_2_GPIO_Pin,LED_3_GPIO_Pin
  , LED_4_GPIO_Pin,LED_5_GPIO_Pin,LED_6_GPIO_Pin,LED_7_GPIO_Pin };
   
  /*  LED/SEG ͳһ���ó�ͨ�����������50MHZ������ٶ�*/
    GPIO_InitTypeDef  GPIO_InitStruct;//������Ҫ��ʼ����װ�õ� GPIO���ó�ʼ�� �ṹ��
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  
  for(;x<=7;++x){
       
    GPIO_InitStruct.GPIO_Pin=LED_x_GPIO_Pin[x];
    GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
     
  }
}
/*  @brief ���������� ���� ר��������ѡ���IO  �� LED or SEGMENT��SEL from SEGs��JTAG-DP or SW-DP
**  @param  void
**  
*/
void SEL_GPIO_Config(void){
    uint32_t x=0;
    uint32_t SEL_GPIO_Pin[]={SEL_GPIO_0_Pin,SEL_GPIO_1_Pin,SEL_GPIO_2_Pin,SEL_GPIO_3_Pin};
   
  /*  LED ͳһ���ó�ͨ�����������50MHZ������ٶ�*/
    GPIO_InitTypeDef  GPIO_InitStruct;//������Ҫ��ʼ����װ�õ� GPIO���ó�ʼ�� �ṹ��
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  
  for(;x<=3;++x){
       
    GPIO_InitStruct.GPIO_Pin=SEL_GPIO_Pin[x];
    GPIO_Init(SEL_GPIO_Port, &GPIO_InitStruct);     
  }
}
/*  @brief:  select LED or SEGMENT.   LED��ѡ���Ǹߵ�ƽ��Ч��SEG�ǵ͵�ƽ��Ч
*       @argument:  Select_LED    ,   Select_SEG 
*   
*/
void LED_SEG_Select_CMD(State NewState){
  
  if(NewState == Select_LED){    
    GPIO_SetBits(SEL_GPIO_Port,SEL_GPIO_3_Pin);
  }else{
    GPIO_ResetBits(SEL_GPIO_Port,SEL_GPIO_3_Pin);
  }
}

/*
*
* ������Ժ�ѧ����ӳ��͸���������д
* ���ԭ��ͼ��֪��
*/

    void AFIO_Init(void){
      AFIO->MAPR |= 0x02000000;//�ر�JTAG-DP������SW-DP
    }



