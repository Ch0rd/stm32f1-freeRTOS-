#include "system.h"	/*ͷ�ļ�����*/


static TaskHandle_t startTaskHandle;
static void startTask(void *arg);

int main() 
{
	
	systemInit();			/*�ײ�Ӳ����ʼ��*/	

	xTaskCreate(startTask, "START_TASK", 300, NULL, 2, &startTaskHandle);	/*������ʼ����*/
	
	vTaskStartScheduler();	/*�����������*/

	while(1){};
}	

void startTask(void *param)
{
	taskENTER_CRITICAL();	/*�����ٽ���*/
	
	//xTaskCreate(elecTask,"ELECLINK",100,NULL,8,&elecTaskHandle);//��������or��Դ������������Ҫ��ȥ��
	
	xTaskCreate(rxTask, "RXLINK", 100, NULL, 10, NULL);//�������ڽ�������
	
	xTaskCreate(txTask,"TXLINK",100,NULL,10,NULL);//�������ڷ�������
	
	xTaskCreate(usblinkDataProcessTask, "DATA_PROCESS", 100, NULL, 10, NULL);	//����USB���ݴ�������
	
	xTaskCreate(FirstTask,"FIRSTTASK",100,NULL,8,NULL);

	xTaskCreate(SecondTask,"SECONDTASK",100,NULL,8,&SecondTaskHandle);
	
	vTaskSuspend(SecondTaskHandle);//����2ֻ������1ִ�к�ָ���ͨ����������Ҫ��ȥ��
	
  //xTaskCreate(ThirdTask,"THIRDTASK",100,NULL,8,NULL);
	
	vTaskDelete(startTaskHandle);									/*ɾ����ʼ����*/
	
	taskEXIT_CRITICAL();	/*�˳��ٽ���*/
}
