#ifndef __SYSTEM_H
#define __SYSTEM_H

/* freertos 配置文件 */
#include "FreeRTOSConfig.h"

/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"



/*底层硬件驱动*/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "usart4.h"

#include "gpio.h"
#include "motor.h"


/*任务相关*/
#include "package.h"
#include "comlink.h"

extern xTaskHandle elecTaskHandle; 

void systemInit(void);
void elecTask(void *param);
#endif /* __SYSTEM_H */
