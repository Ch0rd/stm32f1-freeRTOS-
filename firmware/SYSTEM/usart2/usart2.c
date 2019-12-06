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

u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	 
u8 USART2_FLAG=0;


 
//��ʼ��Ӳ��
void usart2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//0.ʹ��USART2 GPIOA����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE);
	
	//1.GPIO:PA2 PA3
	//PA2:�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA3:��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//2.USART1��8N1
	USART_InitStruct.USART_BaudRate = 38400;                                     //������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //Ӳ������
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No;                              //У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;                           //ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                      //����λ����
	USART_Init(USART2, &USART_InitStruct);
	
  USART_Init(USART2, &USART_InitStruct); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART2, ENABLE);     //�򿪣�USART2
	

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

void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	BaseType_t xHigherPriorityTaskWoken;	 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
	{
	  Res = USART_ReceiveData(USART2);	//��ȡ���յ�������
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res;
			USART2_RX_STA++;
			if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	
			if(Res==0xFF)USART2_RX_STA|=0x8000;	//���������        						 
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
	