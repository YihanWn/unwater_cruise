#include "MessageTask.h"
#include "SensorTask.h"
#include "PressureTask.h"


void SensorTask_Function(void const * argument)
{	

	portTickType tick = xTaskGetTickCount();
  /* Infinite loop */
  while(1)
  {
	  
		#ifdef  DEBUG
		
		#else
	    DHT11_Read_Data(&SensorData.TempHum_Data); 	    
		xQueueOverwrite(TempHum_Message_Queue,&SensorData.TempHum_Data);
		#endif
 		vTaskDelayUntil(&tick,100);
	}
}


