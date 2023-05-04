#include "MessageTask.h"
#include "PressureTask.h"

ControlMsg_t control_data;


float test_arr[10] = {0};

void MessageTask_Function(void const * argument)
{	

	portTickType tick = xTaskGetTickCount();
  /* Infinite loop */
  while(1)
  {
		
	  //在这里   获取个消息队列信息
	  if(Pressure_Message_Queue)
		xQueuePeek(Pressure_Message_Queue, &SensorData.Pressure_Data,1); //压传
	  if(Imu_Msg_Queue)
		xQueuePeek(Imu_Msg_Queue, &SensorData.imu_data,1);
	  if(TempHum_Message_Queue)
	    xQueuePeek(TempHum_Message_Queue, &SensorData.TempHum_Data,1);
	  //在这里   进行Control结构体赋值
	    control_data.depth = SensorData.Pressure_Data.depth;
	    control_data.pitch_groy = SensorData.imu_data.pitch_groy;
		control_data.yawing = SensorData.imu_data.yaw;
		control_data.humi = SensorData.TempHum_Data.humi;
	  
		test_arr[0] = SensorData.Pressure_Data.depth;
		test_arr[1] = SensorData.Pressure_Data.Temperature;
		test_arr[4] = SensorData.imu_data.pitch_groy;

 		vTaskDelayUntil(&tick,30);
	}
}



