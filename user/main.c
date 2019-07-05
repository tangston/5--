#include "stm32f10x.h"
#include "bsp_led.h"

/*���ڿ�ѧϰλ��������ѧ��C51��ͬѧӦ����ӡ��8λ��ʱ�������ǿ���ֱ�Ӷ���sbit�����������ļĴ�����ĳһλ��ƽ�ߵ�
* ��8λ��Ѱַ��ʽ�򵥣�������������STM32һѰ����16λ32λ�����ģ�����ôȥ��������ĳһλ�أ��ⷨ�뵼��ٷ�������
* λ�������Ŀռ䣬SRAM����Ƭ������������1MB�Ŀռ䣬��������Щ��������Ĵ�����ÿ 1bit���ͳ�8λ��һ���֣������ͳ�4���ֱ��32λ��
* ��͵���һλ�����λ��������ȫ��0��䣬������Ҳû���ã�Ӳ��������Щλ����ֻ��32λһ�ң��ҵÿ��������
* ������ܲο�  Ұ��F103�����ǽ̳̻�ٶ�һ�� λ������ �ؼ��֣����������Armд��Դ����ע�����λ�������Ĺٷ�ʹ�÷���
*/

/* Ԥ���벻ִ�еĲ��ֲ��Ǳ������ݣ�ֱ�ӵ������С�ļ���ͼ����Ի��Լ��ֶ�ɾ�����ɣ����ߺ�æ�������˰���ɾ��֮������֪ͨ��һ��*/
#if 0
/*�Ѱ˸���ˮ�Ƹ����������������*/
uint32_t LED_x[]={  LED_0_GPIO_Pin, LED_1_GPIO_Pin, LED_2_GPIO_Pin, LED_3_GPIO_Pin,
                      LED_4_GPIO_Pin, LED_5_GPIO_Pin, LED_6_GPIO_Pin, LED_7_GPIO_Pin  };
#endif
                      

                      
/*led�������pin�����ݴ��ѧ��ģ������ͼ��飬��ԭ��ͼ��֪��GPIOE��8��15�ܽ�
** 
**    �Ĵ��������������λ����������ȥ���أ������ĵط���ַ��ʽ�ǣ� ((addr & 0xF0000000)+0x02000000+((addr &0x00FFFFFF)<<5)+(n<<2))   
**                                           addr��Ҫ������λ���ڵ��������ַ+����Ĵ�����ƫ�Ƶ�ַ��n��������Ĵ����ĵڼ�λ����0��ʼ�㣬Ϊʲô��0��ʼ�����Ķ�STM32F10x�ٷ������ֲ�                                        
**/                    
#define   GPIOE_ODR_Addr    (GPIOE_BASE+0x0C)   //GPIOB�ǹٷ�GPIOͷ�ļ��ﶨ���˵ģ���Щ�������ֲ�8.2.4���㲻�Źٷ�����⣬���Լ�#defineһ��GPIO_Base,������ֲ�2.3��

/*���磬��Ҫλ����LED�Ƶ�L2��L2����ԭ��ͼ��֪��GPIOE_Pin_10,������Ҫ��GPIOE->ODR�ĵ�10λ��������������ȡ����ţ��ҳ������ٰ���д1��L3������*/                      
/*��ô�����addr�������Ǻ궨�����Addr�ˣ����ǰ����滻��GPIOE_ODR_Addr
*                      
*�������ż�ʱ�䣬�ٶ� �������ĺ궨�� �� ʵ���Ϲ����������������ã����˼��������ҪƵ��ʹ��ĳһЩ��������                   */
#define   PEout(n)  *(unsigned int *)((GPIOE_ODR_Addr & 0xF0000000)+0x02000000+((GPIOE_ODR_Addr &0x00FFFFFF)<<5)+(n<<2))
/*��һ���Ǻ���C����������ڴ����˼����ʽ���Ǻ�+һ��C���Ը�ʽ�ĵ�ַ
* �ڶ���(unsigned int *)�����߱�������������������������������������һ���ǿ��ܽ����Ϊ������������C���Ը�ʽ�ĵ�ַ���Ǹ��ڴ�ռ�����ƺ�
* ����������ÿ��ͨ��PEout��n�������൱��ֱ��ִ���˺����  �������ƺ�+���ţ��Ϳ����޸�����ڴ�����������
*/

/*�����������������������C51����ֱ�Ӳ���LED�ĸо��أ�������֮ǰ�Ĵ����Ч����Ӧ����������*/
#define L3  PEout(10) //LED�����ǿ�������ƽ��  ��  �ߵ͵�ƽ����out������
/*������LED������Ҳ�����Լ���������һ�£����¸㻵������̣��¾����ҵ�GitHub https://github.com/tangston?tab=repositories��you can delete the broken one and clone my good one*/

/*  ����������ģ��ǰһ�½ڵ���ѯ��ʽ���������Ƶư��𣬰ѿ������ϵ�K1��K2��K3�����������LEDһ��λ�������
*   ��ʾ����������ԭ��ͼ����GPIOC_Pin_0��1��2,�ֱ��Ӧ����K1 K2 K3�������������ڻ���ַ��GPIOC�Ļ���ַ��ƫ�������Ʋ�STM32�ٷ������ֲ�8.2.3���������ɲ��Ĺٷ��ĵ���ϰ��
*   �����ַ�Ļ���ַ��ƫ����������«��ư��д��KEY���� ���Ǽ�� ����Ĵ��� �ˣ�
*
*/

#if 0
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]);
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]);

void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]);
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]);
#endif

void delay(void);

/*����ӳٺ������ܲ���׼��*/
void  delay(void){
  int count =0x6f000;
  while(count--);
}  

int main(void){
   
    LED_SEG_CLK_Init( );
    // stm32��λ��JTAG��SWĬ��ͬʱ�����ģ������е�JTAG�˿ھ���ϵͳ�������������GPIOB�ǲ������õ�
   // AFIO->MAPR |= 0x02000000;//�ر�JTAG-DP������SW-DP����ǰ��Ҫ���� LED��SEGʱ�ӡ�SELʱ�ӡ�AFIOʱ�ӣ����رյĻ�����ռ��һЩ����������޷�������
    AFIO_Init();//��ע�͵����У����޷��������PB.3������Ĵ��������ǲ�ע�͵��Ļ�����PB.3����ߵ�ƽ��������������LED���֣���LED��ͨ�����Ʋ������������
    LED_SEG_GPIO_Config(  );
    SEL_GPIO_Config(  );
    LED_SEG_Select_CMD(Select_LED);
  //LED_SEG_Select_CMD(Select_SEG);
    //KEY_GPIO_Config();//����������ͬѧ��ȡ��ע�͸��У����������ֵ�λ������
  
    while(1){
      
      delay();
      L3  = !L3;
      
      /*�ο�����
      if(PCin(n)==true)
      {
          delay_ms(50);//�ӳ�����ǰһ���н��ܣ������Ͳ��ᰴ��ȥ������ж��㰴�˺ܶ�����
           Ln  = !Ln;//�ﵽ��һ�¾�   ��һ��/��һ��   ��Ч��
      }
      */
      
      
      
      #if 0
      
      
      
         if(KEY_SCAN(KEY_GPIO_Port, KEY1_GPIO_Pin)==1){ 
            count =0;
           while(count<=0x20){
             led_mode1_left(&count,LED_x);
           }
         }else if(KEY_SCAN(KEY_GPIO_Port,KEY2_GPIO_Pin)==1){
            count =0;
           while(count<=0x20){
             led_mode1_right(&count,LED_x);
            }
           }else if(KEY_SCAN(KEY_GPIO_Port,KEY3_GPIO_Pin)==1){
            count =0;
           while(count<=0x20){
             led_mode2_left(&count,LED_x);
           }
         }
           #endif
         
  }
}

#if 0
/**
* @brief ��һ�����������������
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //��ʼ��һ�������Ϊȫ�� 
    GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    
    int led_number=*the_first_light;//����һ�£���Ҫ��������
    (* the_first_light)++;

    led_number %=8;

    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
/**
* @brief ��һ��������right�ҷ��������
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //��ʼ��һ�������Ϊȫ��
      GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    int led_number=-(*the_first_light);//����һ�£���Ҫ��������
    (* the_first_light)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0�������ᱻ��λ��ȫ�������︴��ճ����ʱ��㷴�ˣ����øĴ��룬�ɴ�Ĳ���
    
    led_number  +=  8;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/**
* @brief ��һ���������������ƣ�����������Ĭ��ȫ��
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
   
    int led_number=*the_first_dark;//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
 
    led_number %=8;
  
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
   
     
}
/**
* @brief ��һ��������ҷ�������ƣ�����������Ĭ��ȫ��
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
    
    int led_number=-(*the_first_dark);//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;  
    if(led_number==0){led_number --;}//led_number=16�������ᱻ��λ��ȫ��
    
    led_number+=8;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��

}
#endif
