/*
 * @brief	：openmv1用于巡线使用，串口接收回传的角度以及截距数据
 * @author 	：赵新伟
 * @Date	：2020.10.08
 */

/*
 *NOTE  : 接收数据的协议，协议解析没有写
 */


#include "openmv1.h"

Openmv1_dma_rec Openmv1_buf;
Openmv1_Rec_Msg Openmv1_msg;
Openmv1_Dis_t Openmv1_Dispose;

/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void Openmv1_Init (void)
{
		Openmv1_buf.RX_flag = 0;
		__HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);												//开启串口4 openmv1 串口空闲中断
		HAL_UART_Receive_DMA(&huart4, Openmv1_buf.RX_pData,sizeof(Openmv1_buf.RX_pData));  		//开启串口4   dma	接收数据
		__HAL_UART_CLEAR_IDLEFLAG(&huart4);														//清除 串口4 空闲中断标志位
}

/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void Openmv1_Rec_IDLE_Fun(UART_HandleTypeDef *huart)
{
	
	static uint32_t temp;

 
	if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))  
		{   
			__HAL_UART_CLEAR_IDLEFLAG(huart);  
			HAL_UART_DMAStop(huart);  
			
			temp = huart->hdmarx->Instance->NDTR; 			
			Openmv1_buf.RX_flag=1;  
		
			//接收到的数据   存放到OPENMV1_MSG结构体中			
			memcpy(&Openmv1_msg,&Openmv1_buf.RX_pData,10);	
					
//			memcpy(&Openmv1_msg.Head,&Openmv1_buf.RX_pData[0],1);
//			memcpy(&Openmv1_msg.Head_1,&Openmv1_buf.RX_pData[1],1);	
//			memcpy(&Openmv1_msg.ANGLE,&Openmv1_buf.RX_pData[2],4);	
//			memcpy(&Openmv1_msg.DISTANCE,&Openmv1_buf.RX_pData[6],4);				
			
		    memset(Openmv1_buf.RX_pData,'\0',sizeof(Openmv1_buf.RX_pData));
			HAL_UART_Receive_DMA(huart,Openmv1_buf.RX_pData,sizeof(Openmv1_buf.RX_pData));  
		}
}


//串口接收数据处理函数



