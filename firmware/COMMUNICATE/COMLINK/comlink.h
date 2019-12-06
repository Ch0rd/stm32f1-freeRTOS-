#ifndef __COMLINK_H__
#define __COMLINK_H__



#include "stm32f10x.h"
#include "stdio.h"
#include "usart2.h"
#include "usart4.h"
#include "package.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

extern xQueueHandle Message_Queue;
extern xQueueHandle Tx_Queue; 

void com_init(void);


void rxTask(void *param);
void txTask(void *param);

#endif
