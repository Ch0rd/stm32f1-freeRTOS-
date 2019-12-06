#include "comlink.h"
#include "malloc.h"

xQueueHandle Message_Queue; 
xQueueHandle Tx_Queue; 

void com_init(void)
{
	Message_Queue = xQueueCreate(16,USART_REC_LEN);
  Tx_Queue = xQueueCreate(16,USART_REC_LEN); 
}


void rxTask(void *param)//理论上此任务可省略，中断中已将数据传入message队列，此任务只用作message队列转到pack队列，但为了结构更清晰，保留此任务
{
	u8* buffer;
	BaseType_t err ;
	while(1)
	{
		buffer = mymalloc(USART_REC_LEN);
		
		if(Message_Queue!=NULL)
		{
	   	memset(buffer,0,USART_REC_LEN);	//清除缓冲区
			err=xQueueReceive(Message_Queue,buffer,portMAX_DELAY);//请求消息Message_Queue
			if(err==pdTRUE)			//接收到消息
      { 
			  xQueueSend(Pack_Queue,buffer,0);			//接收到的消息
      }
    }
		myfree(buffer);		//释放内存
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
			memset(sendbuffer,0,USART_REC_LEN);	//清除缓冲区
			err=xQueueReceive(Tx_Queue,sendbuffer,portMAX_DELAY);//请求消息Tx_Queue
			if(err==pdTRUE)
			{
				USART2_Send_Data(sendbuffer,7);
			}
		}
	 myfree(sendbuffer);		//释放内存
	 vTaskDelay(10);
  }
}