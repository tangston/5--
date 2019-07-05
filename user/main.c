#include "stm32f10x.h"
#include "bsp_led.h"

/*本节课学习位带操作，学过C51的同学应该有印象，8位机时代，我们可以直接定义sbit来操作单独的寄存器的某一位电平高低
* 但8位机寻址方式简单，可以这样做，STM32一寻就是16位32位是最快的，那怎么去单独操作某一位呢？意法半导体官方给出了
* 位带操作的空间，SRAM区和片上外设区各有1MB的空间，他们让这些输入输出寄存器的每 1bit膨胀成8位成一个字，再膨胀成4个字变成32位，
* 最低的那一位代表该位，其他的全用0填充，设置了也没有用，硬件不理这些位，它只管32位一找，找得快就完事了
* 具体介绍参考  野火F103零死角教程或百度一下 位带操作 关键字，里面介绍了Arm写的源代码注释里的位带操作的官方使用方法
*/

/* 预编译不执行的部分不是本课内容，直接点击左方缩小文件树图标忽略或自己手动删除即可，编者很忙，后世人帮我删完之后邮箱通知我一声*/
#if 0
/*把八个流水灯给捆起来，方便操作*/
uint32_t LED_x[]={  LED_0_GPIO_Pin, LED_1_GPIO_Pin, LED_2_GPIO_Pin, LED_3_GPIO_Pin,
                      LED_4_GPIO_Pin, LED_5_GPIO_Pin, LED_6_GPIO_Pin, LED_7_GPIO_Pin  };
#endif
                      

                      
/*led的输出的pin，根据大二学的模电数电和计组，看原理图得知是GPIOE的8到15管脚
** 
**    寄存器输入输出单独位膨胀它到哪去了呢？它到的地方地址公式是： ((addr & 0xF0000000)+0x02000000+((addr &0x00FFFFFF)<<5)+(n<<2))   
**                                           addr是要操作的位所在的外设基地址+这个寄存器的偏移地址，n是你这个寄存器的第几位，从0开始算，为什么从0开始，请阅读STM32F10x官方中文手册                                        
**/                    
#define   GPIOE_ODR_Addr    (GPIOE_BASE+0x0C)   //GPIOB是官方GPIO头文件里定义了的，这些都出自手册8.2.4，你不信官方代码库，就自己#define一个GPIO_Base,这节在手册2.3里

/*例如，我要位定义LED灯的L2，L2查阅原理图可知是GPIOE_Pin_10,我们需要把GPIOE->ODR的第10位在膨胀区（本人取的外号）找出来，再把它写1，L3就亮了*/                      
/*那么上面的addr就是我们宏定义里的Addr了，我们把它替换成GPIOE_ODR_Addr
*                      
*下面是炫技时间，百度 带参数的宏定义 。 实际上工程里这样并不常用，除了极少数情况要频繁使用某一些单独引脚                   */
#define   PEout(n)  *(unsigned int *)((GPIOE_ODR_Addr & 0xF0000000)+0x02000000+((GPIOE_ODR_Addr &0x00FFFFFF)<<5)+(n<<2))
/*第一个星号是C语言里访问内存的意思，格式是星号+一个C语言格式的地址
* 第二个(unsigned int *)，告诉编译器，我这里后面的数不是立即数（软件里大一你们可能叫这个为常数），而是C语言格式的地址，是该内存空间的门牌号
* 这样，我们每次通过PEout（n），就相当于直接执行了后面的  访问门牌号+进门，就可以修改这个内存里面存的数了
*/

/*如何最后操作起来，看起来像C51那样直接操作LED的感觉呢？宁晓兰之前的代码等效起来应该是这样的*/
#define L3  PEout(10) //LED是我们控制它电平输  出  高低电平让他out亮或灭
/*其他的LED灯你们也可以自己定义着玩一下，别怕搞坏这个工程，怕就来我的GitHub https://github.com/tangston?tab=repositories，you can delete the broken one and clone my good one*/

/*  进阶修炼，模仿前一章节的轮询方式，按键控制灯暗灭，把开发板上的K1、K2、K3都给像上面的LED一样位定义出来
*   提示：按键翻阅原理图，在GPIOC_Pin_0、1、2,分别对应的是K1 K2 K3，所以他的所在基地址是GPIOC的基地址，偏移量请移步STM32官方中文手册8.2.3，自行养成查阅官方文档的习惯
*   输出地址的基地址和偏移量请依葫芦画瓢来写。KEY就是 我们检测 输入寄存器 了，
*
*/

#if 0
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]);
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]);

void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]);
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]);
#endif

void delay(void);

/*软件延迟函数，很不精准的*/
void  delay(void){
  int count =0x6f000;
  while(count--);
}  

int main(void){
   
    LED_SEG_CLK_Init( );
    // stm32复位后，JTAG与SW默认同时开启的，即所有的JTAG端口均被系统保留，软件设置GPIOB是不起作用的
   // AFIO->MAPR |= 0x02000000;//关闭JTAG-DP，启用SW-DP。在前面要启动 LED与SEG时钟、SEL时钟、AFIO时钟，不关闭的话它会占用一些引脚让软件无法设置它
    AFIO_Init();//若注释掉该行，则无法软件配置PB.3的输出寄存器，我们不注释掉的话，对PB.3输出高电平，经过反相器到LED部分，则LED导通（电势差比数码管那里大）
    LED_SEG_GPIO_Config(  );
    SEL_GPIO_Config(  );
    LED_SEG_Select_CMD(Select_LED);
  //LED_SEG_Select_CMD(Select_SEG);
    //KEY_GPIO_Config();//进阶修炼的同学请取消注释该行，做按键部分的位带操作
  
    while(1){
      
      delay();
      L3  = !L3;
      
      /*参考代码
      if(PCin(n)==true)
      {
          delay_ms(50);//延迟消抖前一课有介绍，这样就不会按下去它疯狂判定你按了很多下了
           Ln  = !Ln;//达到按一下就   亮一下/灭一下   的效果
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
* @brief 仅一个灯亮的左方向跑马灯
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //初始化一下跑马灯为全灭 
    GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    
    int led_number=*the_first_light;//备份一下，主要操作备份
    (* the_first_light)++;

    led_number %=8;

    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
/**
* @brief 仅一个灯亮的right右方向跑马灯
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //初始化一下跑马灯为全灭
      GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    int led_number=-(*the_first_light);//备份一下，主要操作备份
    (* the_first_light)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0呃话，会被置位成全亮，这里复制粘贴的时候搞反了，懒得改代码，干脆改参数
    
    led_number  +=  8;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/**
* @brief 仅一个灯灭的左方向跑马灯，函数结束后默认全亮
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
   
    int led_number=*the_first_dark;//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
 
    led_number %=8;
  
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
   
     
}
/**
* @brief 仅一个灯灭的右方向跑马灯，函数结束后默认全亮
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
    
    int led_number=-(*the_first_dark);//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;  
    if(led_number==0){led_number --;}//led_number=16呃话，会被置位成全灭
    
    led_number+=8;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮

}
#endif
