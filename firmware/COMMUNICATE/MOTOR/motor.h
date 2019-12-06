#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"

#include "package.h"


extern xTaskHandle SecondTaskHandle;
extern xSemaphoreHandle First_Semaphore;
extern xSemaphoreHandle Second_Semaphore;
  

void FirstTask(void *param);
void ThirdTask(void *param);
void SecondTask(void *param);

#endif
