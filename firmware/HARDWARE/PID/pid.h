#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
#include "package.h"


/*pid结构体*/ 
typedef struct
	{ 
   float setpoint;       //设定值
	 float result;     //输出值
	 float nowerror;  //现偏差
	 float lasterror;     //前一拍偏差
   float Kp;     //比例系数
   float Ki;      //积分系数
   float Kd;    //微分系数
   float integral;   //积分值
   float voltage;   //控制的变量    
 }PID;	


void pid_init(void);
float checkpidset(void);
void pidset(pack_t p);	
float PID_realize(float result);
 
#endif
