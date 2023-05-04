#include "MessageTask.h"
#include "PressureTask.h"


SensorMsg_t SensorData;

  
 u8 sta = 0;
 u8 send_state[10] = {0};

void PressureTask_Function(void const * argument)
{	

	portTickType tick = xTaskGetTickCount();
  /* Infinite loop */
  while(1)
  {
	  
	  
		#ifdef  DEBUG
		
		#else

		Get_Pressure(&SensorData.Pressure_Data);
 
		// ��Ϣ��������Ϣ����  
		if(Pressure_Message_Queue)	  
	    send_state[0]  = xQueueOverwrite(Pressure_Message_Queue, &SensorData.Pressure_Data);

		#endif
 		vTaskDelayUntil(&tick,100);
	}
}


