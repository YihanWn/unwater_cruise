
#include "board.h"

//定义消息队列
QueueHandle_t Imu_Rec_Queue = NULL;
QueueHandle_t Control_Message_Queue = NULL;  
QueueHandle_t Pressure_Message_Queue = NULL; 
QueueHandle_t Imu_Msg_Queue = NULL;
QueueHandle_t TempHum_Message_Queue = NULL;
//QueueHandle_t Battery_Message_Queue = NULL; 
//QueueHandle_t Command_Message_Queue = NULL; 


/**
 * @funNm : delay_ms
 * @brief : 延时函数
 * @param : nms
 * @retval: void
 */
void delay_ms(int nms)   
{
		if(xTaskGetSchedulerState()==taskSCHEDULER_NOT_STARTED)
		{
			HAL_Delay(nms);
		}else
		{
			osDelay(nms);
		}
}

/**
 * @funNm : delay_sys_us
 * @brief : 延时nus
 * @param : nus:要延时的us数.	0~204522252(最大值即2^32/fac_us@fac_us=168)	 
 * @retval: void
 */
void delay_sys_us(uint32_t Delay)//1个delay，大概1.5us
{
	uint32_t cnt = Delay * 32;  
    uint32_t i = 0;
    for(i = 0; i < cnt; i++)__NOP();
}

/**
 * @funNm : Task_Queue_Semaphore_Timers_Create
 * @brief : 任务消息队列、信号量、定时器创建
 * @param : void
 * @retval: 1.在各个任务执行前创建  2.注意防止中断打断创建
 */
void Task_Queue_Semaphore_Timers_Create(void)
{
		 do{
			 Pressure_Message_Queue = xQueueCreate(1, sizeof(PressureMsg_t));
		 }while(Pressure_Message_Queue==NULL);
		
		 do{
		 	Imu_Rec_Queue = xQueueCreate(1, sizeof(uint32_t));
		 }while(Imu_Rec_Queue==NULL);
				
		 do{
			Imu_Msg_Queue = xQueueCreate(1,sizeof(IMU_Msg_t));
		}while(Imu_Msg_Queue == NULL);
		 
		 do{
		 	Control_Message_Queue = xQueueCreate(3, sizeof(ControlMsg_t));
		 }while(Control_Message_Queue==NULL);
		
		 do{
		 	TempHum_Message_Queue = xQueueCreate(1, sizeof(TempHumiMsg_t));
		 }while(TempHum_Message_Queue==NULL);
		
		// do{
		// 		Battery_Message_Queue = xQueueCreate(1, sizeof(uint32_t));	
		// }while(Battery_Message_Queue==NULL);
	
}

/**
 * @funNm : USER_UART_IRQHandler
 * @brief : 串口中断函数
 * @param : huart 某串口
 * @retval: void
 */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{

		 if(huart->Instance == UART4)           //openmv1   巡线摄像头反馈信号
		 {
			Openmv1_Rec_IDLE_Fun(&huart4);
		 }
		 
		 if(huart->Instance == UART5)           //openmv1   定位摄像头反馈信号
		 {
			Openmv2_Rec_IDLE_Fun(&huart5);
		 }
		
		 if(huart->Instance == USART2)           //openmv1   定位摄像头反馈信号
		 {
			Imu_Rec_IDLE_Fun(&huart2);
		 }
}

/**
  * @funNm   BSP_Init
  * @brief   所有外设初始化
  * @param	 void
  * @retval  void
*/
void BSP_Init(void)
{	
	DHT11_init();
	imu_init();
    PID_Init() ;
	Openmv1_Init ();
	Openmv2_Init ();
	HAL_GPIO_WritePin(LED_light_GPIO_Port,LED_light_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor_GPIO_Port,Motor_Pin,GPIO_PIN_RESET);
}

u32 last_time[6] = {0};
u32 run_time[6]  = {0};

u32 getRunTime(u8 n)
{
    u32 run_time_vaule = 0;
    u32 cur_time       = HAL_GetTick();

    run_time_vaule = cur_time - last_time[n];

    last_time[n] = cur_time;

    return run_time_vaule;
}
