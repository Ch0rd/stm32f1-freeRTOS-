#ifndef __GPIO_H
#define __GPIO_H	 
#include "sys.h"

void gpio_init(void);
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2
#define LED2 PAout(12)	// PA12


#endif
