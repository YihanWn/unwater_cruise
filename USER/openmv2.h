#ifndef __OPENMV2_H
#define __OPENMV2_H

#include "includes.h"


#pragma pack(1)
typedef struct
{		
	uint8_t Head;
	
	uint8_t Head_1;
	//angle 
	float  X_offest;
	//distance
	float  Y_offest;

	float  Length;
	
	float  Status;
}Openmv2_Rec_Msg;
#pragma pack()

extern Openmv2_Rec_Msg Openmv2_msg;
//º¯ÊýÉùÃ÷
void Openmv2_Rec_IDLE_Fun(UART_HandleTypeDef *huart);
void Openmv2_Init(void);

#endif


