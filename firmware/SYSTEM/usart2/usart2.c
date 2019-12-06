#include "usart2.h"
#include "delay.h"
#include "malloc.h"
#include "package.h"
#include "comlink.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "gpio.h"

u8 USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	 
u8 USART2_FLAG=0;


 
//初始化硬件
void usart2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//0.使能USART2 GPIOA外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE);
	
	//1.GPIO:PA2 PA3
	//PA2:复用推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA3:浮空输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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
	USART_Init(USART2, &USART_InitStruct);
	
  USART_Init(USART2, &USART_InitStruct); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART2, ENABLE);     //打开：USART2
	

}



void USART2_Send_Data(u8 *buf,u16 len)
{
  u16 t;
  GPIO_SetBits(GPIOA,GPIO_Pin_2);           
  for(t=0;t<len-1;t++)        
  {           
    while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);  
    USART_SendData(USART2,buf[t]); 
  }     
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);        
  GPIO_ResetBits(GPIOA,GPIO_Pin_2);                    
}

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	BaseType_t xHigherPriorityTaskWoken;	 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
	  Res = USART_ReceiveData(USART2);	//读取接收到的数据
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{
			USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res;
			USART2_RX_STA++;
			if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	
			if(Res==0xFF)USART2_RX_STA|=0x8000;	//接收完成了        						 
		}	   		 
  } 
	if((USART2_RX_STA&0x8000)&&(Message_Queue!=NULL))
	{
		xQueueSendFromISR(Message_Queue,USART2_RX_BUF,&xHigherPriorityTaskWoken);
		USART2_RX_STA=0;
		memset(USART2_RX_BUF,0,USART_REC_LEN);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
} 
	