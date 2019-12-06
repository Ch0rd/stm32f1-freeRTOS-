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
			err = xSemaphoreTake(First_Semaphore,portMAX_DELAY);	//��ȡ�ź���
			
			if(err == pdTRUE)
			{

        /*ִ������1����*/
				
				vTaskResume(SecondTaskHandle);
				
			  for(i=0;i<10;i++)
				{
					vTaskDelay(500/portTICK_RATE_MS);//�ȴ�5s
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
         
				/*ִ������2����*/
			  for(i=0;i<10;i++)
				{
					vTaskDelay(500/portTICK_RATE_MS);//�ȴ�5s
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
		
		/*����3����*/
		LED0=!LED0;
		vTaskDelay(500/portTICK_RATE_MS);
	}
}
