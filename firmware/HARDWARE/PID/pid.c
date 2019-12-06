#include "pid.h"
#include "package.h"
#include "adc.h"

PID VPID;



void pidset(pack_t p)//��pack��ת����pid��������pid����
{
   VPID.setpoint = p.m.data[0];
   VPID.Kp = p.m.data[1];
   VPID.Ki = p.m.data[2];
	 VPID.Kd = p.m.data[3];
}

 


float PID_realize(float result)//pid����
{
	VPID.nowerror = VPID.setpoint-result;
	VPID.integral += VPID.nowerror;
	VPID.voltage = VPID.Kp*VPID.nowerror+VPID.Ki*VPID.integral+VPID.Kd*(VPID.nowerror-VPID.lasterror);
	VPID.lasterror = VPID.nowerror;
	VPID.result =VPID.voltage*1.0;
	return VPID.result;
}
 


float checkpidset()//����ǰ����Ƿ������¶�
 {
	 if(VPID.setpoint == 0 || VPID.Kp == 0)
   {
		 return 0;
	 }
	 else
	 { 
		 return 1;
	 }
 }
 
 

void pid_init()//pid��ʼ��
{
	VPID.setpoint = 0;
	VPID.result = 0; 
	VPID.nowerror = 0;
	VPID.lasterror = 0;  
	VPID.Kp = 0.2;     
	VPID.Ki = 0.015;      
	VPID.Kd = 0.2;    
  VPID.integral = 0;
	VPID.voltage = 0;
}
 
