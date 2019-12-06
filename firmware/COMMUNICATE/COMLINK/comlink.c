#include "comlink.h"
#include "malloc.h"

xQueueHandle Message_Queue; 
xQueueHandle Tx_Queue; 

void com_init(void)
{
	Message_Queue = xQueueCreate(16,USART_REC_LEN);
  Tx_Queue = xQueueCreate(16,USART_REC_LEN); 
}


void rxTask(void *param)//�����ϴ������ʡ�ԣ��ж����ѽ����ݴ���message���У�������ֻ����message����ת��pack���У���Ϊ�˽ṹ������������������
{
	u8* buffer;
	BaseType_t err ;
	while(1)
	{
		buffer = mymalloc(USART_REC_LEN);
		
		if(Message_Queue!=NULL)
		{
	   	memset(buffer,0,USART_REC_LEN);	//���������
			err=xQueueReceive(Message_Queue,buffer,portMAX_DELAY);//������ϢMessage_Queue
			if(err==pdTRUE)			//���յ���Ϣ
      { 
			  xQueueSend(Pack_Queue,buffer,0);			//���յ�����Ϣ
      }
    }
		myfree(buffer);		//�ͷ��ڴ�
    vTaskDelay(10);
	}
}

void txTask(void *param)
{
	u8 *sendbuffer;
	BaseType_t err;

	while(1)
	{
		sendbuffer = mymalloc(USART_REC_LEN);
		if(Tx_Queue!=NULL)
		{		
			memset(sendbuffer,0,USART_REC_LEN);	//���������
			err=xQueueReceive(Tx_Queue,sendbuffer,portMAX_DELAY);//������ϢTx_Queue
			if(err==pdTRUE)
			{
				USART2_Send_Data(sendbuffer,7);
			}
		}
	 myfree(sendbuffer);		//�ͷ��ڴ�
	 vTaskDelay(10);
  }
}