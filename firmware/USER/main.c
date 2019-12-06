#include "system.h"	/*头文件集合*/


static TaskHandle_t startTaskHandle;
static void startTask(void *arg);

int main() 
{
	
	systemInit();			/*底层硬件初始化*/	

	xTaskCreate(startTask, "START_TASK", 300, NULL, 2, &startTaskHandle);	/*创建起始任务*/
	
	vTaskStartScheduler();	/*开启任务调度*/

	while(1){};
}	

void startTask(void *param)
{
	taskENTER_CRITICAL();	/*进入临界区*/
	
	//xTaskCreate(elecTask,"ELECLINK",100,NULL,8,&elecTaskHandle);//启动任务or电源管理任务，无需要可去除
	
	xTaskCreate(rxTask, "RXLINK", 100, NULL, 10, NULL);//创建串口接收任务
	
	xTaskCreate(txTask,"TXLINK",100,NULL,10,NULL);//创建串口发送任务
	
	xTaskCreate(usblinkDataProcessTask, "DATA_PROCESS", 100, NULL, 10, NULL);	//创建USB数据处理任务
	
	xTaskCreate(FirstTask,"FIRSTTASK",100,NULL,8,NULL);

	xTaskCreate(SecondTask,"SECONDTASK",100,NULL,8,&SecondTaskHandle);
	
	vTaskSuspend(SecondTaskHandle);//任务2只在任务1执行后恢复，通常挂起，无需要可去除
	
  //xTaskCreate(ThirdTask,"THIRDTASK",100,NULL,8,NULL);
	
	vTaskDelete(startTaskHandle);									/*删除开始任务*/
	
	taskEXIT_CRITICAL();	/*退出临界区*/
}
