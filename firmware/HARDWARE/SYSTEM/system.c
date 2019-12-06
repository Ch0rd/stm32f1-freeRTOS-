#include "system.h"
 
xTaskHandle elecTaskHandle; 
 
 void systemInit(void)
 { 
  gpio_init();
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// �����ж����ȼ�����4		  	 
	usart2_init();
	usart4_init();
  com_init();
  pack_init();
	LED0=!LED0;
	USART2_Send_Data("��ʼ��",sizeof("��ʼ��"));
}	
void elecTask(void *param)
{
	int j;
	static portTickType xLastWakeTime; 
	xLastWakeTime = xTaskGetTickCount();
	
   /*��Դ����*/
	
	vTaskDelete(elecTaskHandle);	  
}	



