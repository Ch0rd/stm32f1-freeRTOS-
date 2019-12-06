#include "package.h"
#include "usart.h"
#include "usart2.h"
#include "gpio.h"
#include "string.h"
#include "malloc.h"
#include "motor.h"
#include "comlink.h"



		
xQueueHandle Pack_Queue;
xSemaphoreHandle First_Semaphore;
xSemaphoreHandle Second_Semaphore;

static const u8 ack[6]={0xAA,0x01,0x00,0x01,0x90,0xFF};

static pack_t datatopack(u8* USART_RX_BUF)//�����ݴ����pack
{ 
	pack_t tem;
	tem.header = USART_RX_BUF[0];
	tem.m.msgID = USART_RX_BUF[1];
	tem.m.dataLen = USART_RX_BUF[2];
	tem.crc_v = USART_RX_BUF[3]<<8 | USART_RX_BUF[4];
	tem.tailer = USART_RX_BUF[5];
  return tem;  
}


/*PACK����*/
static void packanalyze(pack_t *p)
{
	u16 crc;
	if(p->header==0xAF && p->tailer==0xFF)//��ͷ��β��֤
	{
		crc = CrcCal((u8*)&p->m,p->m.dataLen+2);
		if(p->crc_v==crc)
		{
	      if(p->m.msgID == DOWN_FIRST)
	      {
          xSemaphoreGive(First_Semaphore);
          xQueueSend(Tx_Queue,ack,0);
				}
	      else if(p->m.msgID == DOWN_SECOND)
	      {
          xSemaphoreGive(Second_Semaphore);
          xQueueSend(Tx_Queue,ack,0);						
	      }
				//else if (����3)			
		}
	}
}


/*USB�������ݴ�������*/
void usblinkDataProcessTask(void *param)
{
	u8* buffer;
	BaseType_t err;
	pack_t p;		
	while(1)
	{
		buffer = mymalloc(USART_REC_LEN);
		if(Pack_Queue!=NULL)
		{
	   	memset(buffer,0,USART_REC_LEN);	//���������
			err=xQueueReceive(Pack_Queue,buffer,portMAX_DELAY);//������ϢMessage_Queue
			if(err==pdTRUE)			//���յ���Ϣ
      {
				p = datatopack(buffer);
				packanalyze(&p);
      }
    }
		myfree(buffer);		//�ͷ��ڴ�
    vTaskDelay(10); 
	}
}

void pack_init(void)
{
	Pack_Queue = xQueueCreate(16,USART_REC_LEN);
	First_Semaphore = xSemaphoreCreateBinary();	
	Second_Semaphore = xSemaphoreCreateBinary();
}
