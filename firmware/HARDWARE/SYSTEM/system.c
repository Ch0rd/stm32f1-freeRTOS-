#include "system.h"
 
xTaskHandle elecTaskHandle; 
 
 void systemInit(void)
 { 
  gpio_init();
	delay_init();	    	 //延时函数初始化	  
	uart_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// 设置中断优先级分组4		  	 
	usart2_init();
	usart4_init();
  com_init();
  pack_init();
	LED0=!LED0;
	USART2_Send_Data("初始化",sizeof("初始化"));
}	
void elecTask(void *param)
{
	int j;
	static portTickType xLastWakeTime; 
	xLastWakeTime = xTaskGetTickCount();
	
   /*电源管理*/
	
	vTaskDelete(elecTaskHandle);	  
}	



