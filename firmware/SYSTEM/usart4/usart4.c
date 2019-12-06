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

u8 USART4_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART4_RX_STA=0;       //����״̬���	 
u8 USART4_FLAG=0;


 
//��ʼ��Ӳ��
void usart4_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//0.ʹ��USART4 GPIOC����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	//1.GPIO:PC10 PC11
	//PC10:�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//PC11:��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=8 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//2.USART4��8N1
	USART_InitStruct.USART_BaudRate = 38400;                                     //������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //Ӳ������
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No;                              //У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;                           //ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                      //����λ����
	USART_Init(UART4, &USART_InitStruct);
	
  USART_Init(UART4, &USART_InitStruct); //��ʼ������4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(UART4, ENABLE);     //�򿪣�USART4
	

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

void UART4_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	BaseType_t xHigherPriorityTaskWoken;	 
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_9);  
	  Res = USART_ReceiveData(UART4);	//��ȡ���յ�������
		if((USART4_RX_STA&0x8000)==0)//����δ���
		{
			USART4_RX_BUF[USART4_RX_STA&0X3FFF]=Res;
			USART4_RX_STA++;
			if(USART4_RX_STA>(USART_REC_LEN-1))USART4_RX_STA=0;//�������ݴ���,���¿�ʼ����
			if(Res==0xFF)USART4_RX_STA|=0x8000;	//���������        					 
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
	