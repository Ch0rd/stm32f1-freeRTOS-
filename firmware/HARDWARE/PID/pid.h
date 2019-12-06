#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
#include "package.h"


/*pid�ṹ��*/ 
typedef struct
	{ 
   float setpoint;       //�趨ֵ
	 float result;     //���ֵ
	 float nowerror;  //��ƫ��
	 float lasterror;     //ǰһ��ƫ��
   float Kp;     //����ϵ��
   float Ki;      //����ϵ��
   float Kd;    //΢��ϵ��
   float integral;   //����ֵ
   float voltage;   //���Ƶı���    
 }PID;	


void pid_init(void);
float checkpidset(void);
void pidset(pack_t p);	
float PID_realize(float result);
 
#endif
