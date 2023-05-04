#ifndef __PRESSURETASK_H
#define __PRESSURETASK_H

#include "includes.h"

typedef struct {
	PressureMsg_t   Pressure_Data; //
	IMU_Msg_t  		imu_data;
	TempHumiMsg_t   TempHum_Data; 
} SensorMsg_t;

extern SensorMsg_t SensorData;
void PressureTask_Function(void const * argument);
#endif

