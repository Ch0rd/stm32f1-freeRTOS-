#include "usart.h"
#include "delay.h"
#include "malloc.h"
#include "comlink.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "gpio.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 

int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

 
 u8 USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	 


 
//初始化硬件
void uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//0.使能USART2 GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	//1.GPIO:PA9 PA10
	//PA9:复用推挽输
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA10:浮空输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//2.USART1：8N1
	USART_InitStruct.USART_BaudRate = 38400;                                     //波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //硬件流控
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //模式
	USART_InitStruct.USART_Parity = USART_Parity_No;                              //校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;                           //停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                      //数据位长度
	USART_Init(USART1, &USART_InitStruct);
	
  USART_Init(USART1, &USART_InitStruct); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);     //打开：USART2
	

}

void USART2_Send_Data(u8 *buf,u16 len)
{
  u16 t;
  GPIO_SetBits(GPIOA,GPIO_Pin_9);           
  for(t=0;t<len-1;t++)        
  {           
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);  
    USART_SendData(USART1,buf[t]); 
  }     
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);        
  GPIO_ResetBits(GPIOA,GPIO_Pin_9);                    
}

void USART1_Send_Data(u8 *buf,u16 len)
{
  u16 t;
  GPIO_SetBits(GPIOA,GPIO_Pin_9);           
  for(t=0;t<len-1;t++)        
   {           
      while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);  
      USART_SendData(USART1,buf[t]); 
   }     
   while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);        
   GPIO_ResetBits(GPIOA,GPIO_Pin_9);                    
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
	BaseType_t xHigherPriorityTaskWoken;	 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
		{
	    Res =USART_ReceiveData(USART1);	//读取接收到的数据
		  if((USART1_RX_STA&0x8000)==0)//接收未完成
			{	
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收										
				  if(Res==0xFF)USART1_RX_STA|=0x8000;	//接收完成了        						  			 
			}	   		 
    } 
	if((USART1_RX_STA&0x8000)&&(Message_Queue!=NULL))
	{
			USART1_Send_Data(USART1_RX_BUF,7);
		xQueueSendFromISR(Message_Queue,USART1_RX_BUF,&xHigherPriorityTaskWoken);
		USART1_RX_STA=0;
		memset(USART1_RX_BUF,0,USART_REC_LEN);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
} 