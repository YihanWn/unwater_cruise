#ifndef __OPENMV1_H
#define __OPENMV1_H

#include "includes.h"

//变量定义


#pragma pack(1)
//结构体定义
typedef struct 
{
	uint8_t Head;
	
	uint8_t Head_1;
	//angle 
	float  ANGLE;
	//distance
	float  DISTANCE;
	
}Openmv1_Rec_Msg;
#pragma pack()

typedef struct 
{
	uint8_t Head;
	
	uint8_t Head_1;
	//angle 
	int  ANGLE;
	//distance
	int  DISTANCE;
	
}Openmv1_Dis_t;

//外部声明
extern Openmv1_Rec_Msg Openmv1_msg;
extern Openmv1_Dis_t Openmv1_Dispose;
//函数声明
void Openmv1_Init (void);
void Openmv1_Rec_IDLE_Fun(UART_HandleTypeDef *huart);


#endif


