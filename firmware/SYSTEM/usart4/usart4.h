#ifndef __UART4_H__
#define __UART4_H__

#include "stdio.h"	
#include "sys.h" 
#include "usart.h"




void usart4_init(void);
void USART4_Send_Data(u8 *buf,u16 len);

extern u8  USART4_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART4_RX_STA;         		//����״̬���	

#endif