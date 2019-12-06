#include "usart4.h"
#include "delay.h"
#include "malloc.h"
#include "package.h"
#include "comlink.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "gpio.h"

u8 USART4_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART4_RX_STA=0;       //接收状态标记	 
u8 USART4_FLAG=0;


 
//初始化硬件
void usart4_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//0.使能USART4 GPIOC外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	//1.GPIO:PC10 PC11
	//PC10:复用推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//PC11:浮空输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=8 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//2.USART4：8N1
	USART_InitStruct.USART_BaudRate = 38400;                                     //波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //硬件流控
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //模式
	USART_InitStruct.USART_Parity = USART_Parity_No;                              //校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;                           //停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                      //数据位长度
	USART_Init(UART4, &USART_InitStruct);
	
  USART_Init(UART4, &USART_InitStruct); //初始化串口4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(UART4, ENABLE);     //打开：USART4
	

}



void USART4_Send_Data(u8 *buf,u16 len)
{
  u16 t;
  GPIO_SetBits(GPIOC,GPIO_Pin_10);           
  for(t=0;t<len-1;t++)	
  {
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);  
    USART_SendData(UART4,buf[t]); 
  }     
  while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);        
  GPIO_ResetBits(GPIOC,GPIO_Pin_10);                    
}

void UART4_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	BaseType_t xHigherPriorityTaskWoken;	 
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_9);  
	  Res = USART_ReceiveData(UART4);	//读取接收到的数据
		if((USART4_RX_STA&0x8000)==0)//接收未完成
		{
			USART4_RX_BUF[USART4_RX_STA&0X3FFF]=Res;
			USART4_RX_STA++;
			if(USART4_RX_STA>(USART_REC_LEN-1))USART4_RX_STA=0;//接收数据错误,重新开始接收
			if(Res==0xFF)USART4_RX_STA|=0x8000;	//接收完成了        					 
		}	   		 
   } 
	if((USART4_RX_STA&0x8000)&&(Message_Queue!=NULL))
	{
		USART4_Send_Data(USART4_RX_BUF,8);
		xQueueSendFromISR(Message_Queue,USART4_RX_BUF,&xHigherPriorityTaskWoken);
		USART4_RX_STA=0;
		memset(USART4_RX_BUF,0,USART_REC_LEN);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
} 
	