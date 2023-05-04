#ifndef __BOARD_H
#define __BOARD_H
#include "includes.h"


//变量定义




//结构体定义
#pragma pack(1)
typedef struct 
{	
	uint8_t  RX_flag:1;          	 	//IDLE receive flag
	uint16_t RX_Size;             		//receive length
	uint8_t  RX_pData[20]; 	 		    //DMA receive buffer
}Openmv1_dma_rec;
#pragma pack()

typedef struct 
{
	uint8_t  RX_flag:1;         	 				 	//IDLE receive flag
	uint16_t RX_Size;           					  //receive length
	uint8_t  RX_pData[256]; 	  				  //DMA receive buffer
}Openmv2_dma_rec;


//外部声明
extern Openmv1_dma_rec Openmv1_buf; 
extern Openmv2_dma_rec Openmv2_buf; 
extern QueueHandle_t Control_Message_Queue ;
extern QueueHandle_t Pressure_Message_Queue; 
extern QueueHandle_t Imu_Rec_Queue;
extern QueueHandle_t Imu_Msg_Queue;
extern QueueHandle_t TempHum_Message_Queue ;
extern u32 run_time[6];
// extern QueueHandle_t Command_Message_Queue ;  


// 
// extern QueueHandle_t Battery_Message_Queue ; 


//函数声明
void Task_Queue_Semaphore_Timers_Create(void);//消息队列创建
void delay_ms(int nms);	//ms级延迟函数
void delay_sys_us(uint32_t Delay);  //us延时函数

void USER_UART_IRQHandler(UART_HandleTypeDef *huart); //串口中断函数
void BSP_Init(void);
u32 getRunTime(u8 n);
void Task_Queue_Semaphore_Timers_Create(void);

#endif
