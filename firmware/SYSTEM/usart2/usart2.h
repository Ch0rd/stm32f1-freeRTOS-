#ifndef __USART2_H__
#define __USART2_H__

#include "stdio.h"	
#include "sys.h" 
#include "usart.h"




void usart2_init(void);
void USART2_Send_Data(u8 *buf,u16 len);

extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���	

#endif
