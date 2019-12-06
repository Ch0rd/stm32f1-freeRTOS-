#include "gpio.h"

void gpio_init()
{
GPIO_InitTypeDef GPIO_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);	 //使能端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //OUT1 PE13
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //OUT2 PE14
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //OUT3 PE15
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);				 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //OUT4 PB12
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //OUT5 PB13
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);		
	 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //OUT6 PB14
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //OUT7 PB15
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					
 			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //OUT8 PD8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //OUT9 PD9
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
				 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //OUT10 PD10
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
		 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //OUT11 PD11
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
		 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //OUT12 PD12
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
		 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //OUT13 PD13
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //OUT14 PD14
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //OUT15 PD15
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);		
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //OUT16 PC6
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);
		 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //OUT17 PC7
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //OUT18 PC8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //OUT19 PC9
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
			 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //OUT20 PA8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED R   PB10
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED G   PB11
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	
 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //LED B   PA12
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //OUT13 PD2
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//IN1 PE5
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//IN2 PE6
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//IN3 PC13
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//IN4 PC14
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//IN5 PC15
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//IN6 PC0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//IN7 PC1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//IN8 PC2
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//IN9 PC3
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//IN10 PA0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//IN11 PA1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//IN12 PB0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//IN13 PB1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//IN14 PB2
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);  
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//IN15 PE7
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//IN16 PE8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//IN17 PE9
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//IN18 PE10
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//IN19 PE11
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//IN20 PE12
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	
 GPIO_ResetBits(GPIOE,GPIO_Pin_13);		//out1
 GPIO_ResetBits(GPIOE,GPIO_Pin_14);		//out2	
 GPIO_ResetBits(GPIOE,GPIO_Pin_15);	  //3
 GPIO_ResetBits(GPIOB,GPIO_Pin_12);		//4		 
 GPIO_ResetBits(GPIOB,GPIO_Pin_13);	  //5
 GPIO_ResetBits(GPIOB,GPIO_Pin_14);		//6	 
 GPIO_ResetBits(GPIOB,GPIO_Pin_15);	  //7
 GPIO_ResetBits(GPIOD,GPIO_Pin_8);	  //8	 
 GPIO_ResetBits(GPIOD,GPIO_Pin_9);    //9
 GPIO_ResetBits(GPIOD,GPIO_Pin_10);	  //10
 GPIO_ResetBits(GPIOD,GPIO_Pin_11);	  //11
 GPIO_ResetBits(GPIOD,GPIO_Pin_12);	  //12
 GPIO_ResetBits(GPIOD,GPIO_Pin_13);	  //13
 GPIO_ResetBits(GPIOD,GPIO_Pin_14);	  //14
 GPIO_ResetBits(GPIOD,GPIO_Pin_15);   //15
 GPIO_ResetBits(GPIOC,GPIO_Pin_6);		//16
 GPIO_ResetBits(GPIOC,GPIO_Pin_7);	  //17
 GPIO_ResetBits(GPIOC,GPIO_Pin_8);	  //18
 GPIO_ResetBits(GPIOC,GPIO_Pin_9);	  //19
 GPIO_SetBits(GPIOA,GPIO_Pin_8);	  //20 
 GPIO_SetBits(GPIOD,GPIO_Pin_2);	  //20 
	



}
