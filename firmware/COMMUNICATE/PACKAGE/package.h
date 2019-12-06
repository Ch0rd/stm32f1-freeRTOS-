#ifndef __PACKAGE_H
#define __PACKAGE_H 			   
#include "sys.h" 
#include "crc.h"
#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

//���ݲ�ֺ궨��
#define  BYTE0(dwTemp)       ( *( (u8 *)(&dwTemp)	)  )
#define  BYTE1(dwTemp)       ( *( (u8 *)(&dwTemp) + 1) )
#define  BYTE2(dwTemp)       ( *( (u8 *)(&dwTemp) + 2) )
#define  BYTE3(dwTemp)       ( *( (u8 *)(&dwTemp) + 3) )


/*����֡ͷ*/
#define UP_BYTE 0xAA

/*����֡ͷ*/
#define DOWN_BYTE 0xAF

/*֡β*/
#define TAIL_BYTE 0xFF


extern xQueueHandle Pack_Queue;
extern xSemaphoreHandle First_Semaphore;
extern xSemaphoreHandle Second_Semaphore;

/*ͨѶ���ݽṹ*/
 typedef struct 
{
  uint8_t msgID;
	uint8_t dataLen;
	//uint8_t data[PACK_MAX_DATA_SIZE];
}maindata;

typedef struct 
{ 
	uint8_t header;
  maindata m;
	uint16_t crc_v;
	uint8_t tailer;
}pack_t;





/*�ϴ�����ID*/
typedef enum 
{
	UP_VERSION		= 0x00,
  UP_ACK		= 0x01,
}upmsgID_e;




/*����ָ��ID*/
typedef enum 
{
	DOWN_START	= 0x01,
	DOWN_FIRST	= 0x1A,
	DOWN_SECOND	= 0x1B,
  DOWN_THIRD = 0x1C,
}downmsgID_e;



/*����ָ��ID*//*
typedef enum
{
  ERROR_CHECKSELF = 0x01,
	ERROR_CHECKCRC = 0x02,
  ERROR_MISSTEMPSET = 0x10,
  ERROR_MESSAGE = 0x40,
	ERROR_KPKIKDTEMPSET = 0x41,
  ERROR_LIFTMESSAGE = 0x42,
}errorID_e;
*/

void pack_init(void);
void usblinkDataProcessTask(void *param);

#endif

