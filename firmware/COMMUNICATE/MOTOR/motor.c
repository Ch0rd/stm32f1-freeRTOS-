#include "motor.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "gpio.h"
#include "delay.h"
#include "comlink.h"


xTaskHandle SecondTaskHandle;



void FirstTask(void *param)
{
	int i;
  BaseType_t err = pdFALSE;
	
	while(1)
	{
		if(First_Semaphore!=NULL)
		{
			err = xSemaphoreTake(First_Semaphore,portMAX_DELAY);	//获取信号量
			
			if(err == pdTRUE)
			{

        /*执行任务1内容*/
				
				vTaskResume(SecondTaskHandle);
				
			  for(i=0;i<10;i++)
				{
					vTaskDelay(500/portTICK_RATE_MS);//等待5s
					LED0=!LED0;
				}
				xSemaphoreGive(Second_Semaphore);
			}
		}
		vTaskDelay(10);
	}
}

void SecondTask(void *param)
{
	int i;
	BaseType_t err = pdFALSE;
	while(1)
	{
		if(Second_Semaphore!=NULL)
		{
			err = xSemaphoreTake(Second_Semaphore,portMAX_DELAY);
			if(err == pdTRUE)
			{
         
				/*执行任务2内容*/
			  for(i=0;i<10;i++)
				{
					vTaskDelay(500/portTICK_RATE_MS);//等待5s
					LED1=!LED1;
				}
				
				vTaskSuspend(NULL);
			}
		}
	}
}
void ThirdTask(void *param)
{
	while(1)
	{	
		
		/*任务3内容*/
		LED0=!LED0;
		vTaskDelay(500/portTICK_RATE_MS);
	}
}
