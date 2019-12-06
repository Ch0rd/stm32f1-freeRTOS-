#ifndef __SYSTEM_H
#define __SYSTEM_H

/* freertos �����ļ� */
#include "FreeRTOSConfig.h"

/*FreeRTOS���ͷ�ļ�*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"



/*�ײ�Ӳ������*/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "usart4.h"

#include "gpio.h"
#include "motor.h"


/*�������*/
#include "package.h"
#include "comlink.h"

extern xTaskHandle elecTaskHandle; 

void systemInit(void);
void elecTask(void *param);
#endif /* __SYSTEM_H */
