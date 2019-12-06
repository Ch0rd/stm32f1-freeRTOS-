#ifndef __USART2_H__
#define __USART2_H__

#include "stdio.h"	
#include "sys.h" 
#include "usart.h"




void usart2_init(void);
void USART2_Send_Data(u8 *buf,u16 len);

extern u8  USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记	

#endif
