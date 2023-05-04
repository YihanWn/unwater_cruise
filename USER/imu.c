
/**
  ******************************************************************************
  * @file    imu.c
  * @author  赵新伟
  * @date    2020.10.22 
  ******************************************************************************
  * @attention
  *	 
  ******************************************************************************
  */


#include "imu.h"


Usart_Rec_MSG Imu_Rec_Msg = {0};
static IMU_Raw_Msg Imu_Raw = {0};


/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void imu_init(void)
{
	__HAL_UART_ENABLE_IT(&IMU_USART, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&IMU_USART,Imu_Rec_Msg.RX_Date,sizeof(Imu_Rec_Msg.RX_Date));
	__HAL_UART_CLEAR_IDLEFLAG(&IMU_USART);
}


/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void Imu_Rec_IDLE_Fun(UART_HandleTypeDef *huart)
{
	static u32 temp;

 
	if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))  
		{   
			__HAL_UART_CLEAR_IDLEFLAG(huart);  
			HAL_UART_DMAStop(huart);  
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			
			temp = huart->hdmarx->Instance->NDTR; 						  
			Imu_Rec_Msg.RX_Size = RX_LEN - temp;
			Imu_Rec_Msg.RX_Flag=1;
			//向消息队列发送IMU数据			
			if (Imu_Rec_Queue != NULL)
			{
					xQueueSendFromISR(Imu_Rec_Queue, &Imu_Rec_Msg.RX_Size, &xHigherPriorityTaskWoken);
			}			
			HAL_UART_Receive_DMA(&IMU_USART,Imu_Rec_Msg.RX_Date,sizeof(Imu_Rec_Msg.RX_Date));  
		}

}

/**
  * @funNm   IMU数据解析	
  * @brief   
  * @param	
  * @retval
**/
void Imu_Data_unpack(uint8_t* buf, uint16_t len)
{
    static uint8_t  Buf1[11], Buf2[11], Buf3[11];

    memcpy(Buf1, buf, 11);
    memcpy(Buf2, buf + 11, 11);
    memcpy(Buf3, buf + 22, 11);
    if(Buf1[0] == 0x55 &&  Buf2[0] == 0x55 &&   Buf3[0] == 0x55)
    {
        uint8_t Sum1 = 0, Sum2 = 0, Sum3 = 0;
        for(uint8_t i = 0; i < 10 ; i++)
        {
            Sum1 += Buf1[i];
            Sum2 += Buf2[i];
            Sum3 += Buf3[i];
        }
        if(Sum1 == Buf1[10]  && Sum2 == Buf2[10] && Sum3 == Buf3[10])
        {
						//加速度
            Imu_Raw.acceleration[0] = (short)(Buf1[3] << 8 | Buf1[2]) / 32768.0 * 16;
            Imu_Raw.acceleration[1] = (short)(Buf1[5] << 8 | Buf1[4]) / 32768.0 * 16;
            Imu_Raw.acceleration[2] = (short)(Buf1[7] << 8 | Buf1[6]) / 32768.0 * 16;
						//角速度
            Imu_Raw.angular_velocity[0] = (short)(Buf2[3] << 8 | Buf2[2]) / 32768.0 * 2000;
            Imu_Raw.angular_velocity[1] = (short)(Buf2[5] << 8 | Buf2[4]) / 32768.0 * 2000;
            Imu_Raw.angular_velocity[2] = (short)(Buf2[7] << 8 | Buf2[6]) / 32768.0 * 2000;
						//角度
            Imu_Raw.Angle[0] = (short)(Buf3[3] << 8 | Buf3[2]) / 32768.0 * 180;
            Imu_Raw.Angle[1] = (short)(Buf3[5] << 8 | Buf3[4]) / 32768.0 * 180;
            Imu_Raw.Angle[2] = (short)(Buf3[7] << 8 | Buf3[6]) / 32768.0 * 180;
        }
    }
}




/**
  * @funNm		IMU_ReadData
  * @brief		imu欧拉角数据读取
  * @param		imu_data	：传入数据指针
  * @retval		void
*/
void IMU_ReadData(IMU_Msg_t *imu_data)
{
	 if(Imu_Rec_Msg.RX_Flag == 1)
	 {
			//imu姿态角解析
			Imu_Data_unpack(Imu_Rec_Msg.RX_Date, Imu_Rec_Msg.RX_Size);
		
			//清空DMA缓存
			memset(Imu_Rec_Msg.RX_Date, '\0', RX_LEN);
		
			//姿态解析	
			imu_data->yaw = Imu_Raw.Angle[2];
			imu_data->roll = Imu_Raw.Angle[1];
			imu_data->pitch = Imu_Raw.Angle[0];

			imu_data->pitch_groy = Imu_Raw.angular_velocity[0];
			imu_data->roll_groy = Imu_Raw.angular_velocity[1];
			imu_data->yaw_groy = Imu_Raw.angular_velocity[2];

			imu_data->acc_pitch = Imu_Raw.acceleration[0];
			imu_data->acc_roll = Imu_Raw.acceleration[1];
			imu_data->acc_yaw = Imu_Raw.acceleration[2];
		
			//开启DMA接收
			HAL_UART_Receive_DMA(&IMU_USART, Imu_Rec_Msg.RX_Date, RX_LEN);
			Imu_Rec_Msg.RX_Flag = 0;
		}
}



