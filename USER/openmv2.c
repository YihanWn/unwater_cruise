
/*
 * @brief	��openmv1����Ѳ��ʹ�ã����ڽ��ջش��ĽǶ��Լ��ؾ�����
 * @author 	������ΰ
 * @Date	��2020.10.08
 */

/*
 *NOTE  : �������ݵ�Э�飬Э�����û��д
 */


#include "openmv2.h"

Openmv2_dma_rec Openmv2_buf;
Openmv2_Rec_Msg Openmv2_msg;


/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void Openmv2_Init(void)
{	
	Openmv2_buf.RX_flag = 0;
	__HAL_UART_ENABLE_IT(&huart5,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart5,Openmv2_buf.RX_pData,sizeof(Openmv2_buf.RX_pData));
	__HAL_UART_CLEAR_IDLEFLAG(&huart5);
	Openmv2_msg.Status = 0;
}

/**
  * @funNm  
  * @brief   
  * @param	
  * @retval
**/
void Openmv2_Rec_IDLE_Fun(UART_HandleTypeDef *huart)
{
	
	static uint32_t temp;
	if((__HAL_UART_GET_FLAG(&huart5,UART_FLAG_IDLE) != RESET))  
		{  
			
			__HAL_UART_CLEAR_IDLEFLAG(&huart5);  
			HAL_UART_DMAStop(&huart5);  
			temp = huart->hdmarx->Instance->NDTR; 
 
			Openmv2_buf.RX_flag=1;  
		
			//�����յ�������
		    memcpy(&Openmv2_msg,&Openmv2_buf.RX_pData,18);

		    memset(Openmv2_buf.RX_pData,'\0',sizeof(Openmv1_buf.RX_pData));
			HAL_UART_Receive_DMA(&huart5,Openmv2_buf.RX_pData,sizeof(Openmv2_buf.RX_pData));  
		}
}

