#include "ImuTask.h"
#include "PressureTask.h"


static int IMU_Rec_Length = 0;

void ImuTask_Function(void const * argument)
{
  
	portTickType tick = xTaskGetTickCount();
	
	while(1)
	{

		if(xQueueReceive(Imu_Rec_Queue, &IMU_Rec_Length, portMAX_DELAY)) 
			{	
				IMU_ReadData(&SensorData.imu_data);
				xQueueOverwrite(Imu_Msg_Queue,&SensorData.imu_data);	
			}
			vTaskDelayUntil(&tick,50);
	}
 
}


