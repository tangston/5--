#include  "bsp_key.h"
void delay1(){
  int count=0x5f000;
  while(count--);
}

/**
* @brief ��ʼ�������˿ڼ���ʱ��
* @param void
* @retval void
* 
*/
void KEY_GPIO_Config(void){
  
  GPIO_InitTypeDef  GPIO_InitStruct;
  uint32_t  KEY_GPIO_Pin[]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2};
  uint32_t  x=0;
  
  RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);//����Key��������ʱ��
 
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
  
  for( ;x<=2;++x){
    
    GPIO_InitStruct.GPIO_Pin=KEY_GPIO_Pin[x];
    GPIO_Init(KEY_GPIO_Port,&GPIO_InitStruct);
    
  }
  
}

/**
* @brief ����Ƿ��а�������
* @param GPIOx:����Ķ˿�, x �����ǣ�C��
* @param GPIO_Pin:����Ķ˿�λ�� ������ GPIO_PIN_x��x ������ 0...2��
* @retval ������״̬
* @arg KEY_UP:����û����
* @arg KEY_DOWN:��������
*/
uint32_t  KEY_SCAN(GPIO_TypeDef*   GPIOx   , uint16_t  GPIO_Pin){
  
 if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==0){
      delay1();
      return 1;
 }
 return 0;
  
}

