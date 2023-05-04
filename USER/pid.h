#ifndef __PID_H
#define __PID_H
#include "includes.h"


#define  CONSTRAIN(x,max,min) (x>max?max:(x<min?min:x))


//
typedef struct
{
	float yk;
	float yk_1;
	float yk_2;
	float uk;
	float uk_1;
	float uk_2;
	float num[3];
	float den[3];
}SOTF_typeDef;



//�ṹ�嶨��
typedef struct 
{
	float Bias;
	float Last_Bias;			/*ǰһ��ƫ��*/
	float Last_Last_Bias;		/*ǰ����ƫ��*/
		
	/* �ڻ�PID���� Kp Ki Kd	*/
	float Kp;
	float Ki;
	float Kd;
	
	float Pout;
	float Iout;
	float Dout;
	float Out;
	
	float PoutMAX; 		//����޷�
	float IoutMAX;
	float DoutMAX;
	float OutMAX;
	
	float PoutMIN;		//����޷�
	float IoutMIN;
	float DoutMIN;
	float OutMIN;
	/* �ڻ�PID���� */
	
}PID_t;


typedef struct
{
	bool OuterLoopEN;//true:�����⻷ 
	SOTF_typeDef OIntf;//�⻷����
	SOTF_typeDef Ofbtf;//�⻷����
	float Oe;
	float Oe1;
	float OeI;
	float OeImax;
	float OP;
	float OI;
	float OD;
	float Ooutput;
	float OoutMax;
	float OoutMin;
	SOTF_typeDef Oouttf;//�⻷���
	SOTF_typeDef Ifbtf;//�ڻ�����
	//fal��������
	float INVal;//��������
	float falnum;//0.5-1֮��
	float Ie;
	float Ie1;
	float IeI;
	float IeImax;
	float IP;
	float II;
	float ID;
	float ZVal;
	float Ioutput;
	float T;
	
}NLPID_Typedef;
extern NLPID_Typedef YawNLPID;

extern PID_t Inner_PID;		//�⻷PID�ṹ��
extern PID_t Outer_PID;		//�ڻ�PID�ṹ��
extern PID_t Angle_PID;		//�Ƕ�PID
extern PID_t Inter_PID;		//�ؾ�PID
extern PID_t X_offest_PID;
extern PID_t Y_offest_PID;
extern PID_t Deep_PID;

void PID_Param_Init(PID_t *pid, float *pid_param);
void PID_Init(void);
float PID_Inner_Calculate(float tar,float input,PID_t *pid);

float NLPID_Init(void);
float NLfal(float x,float a,float val);
float SOTFOutput(SOTF_typeDef* gs,float data);
float YawErrorDispose(float now,float obj);
float SetValf32(float x,float Lval,float Hval);
float YAWPID_Control(NLPID_Typedef *nl,float Onow,float Inow,float obj);
float sign(float x);
#endif // !__PID_H
