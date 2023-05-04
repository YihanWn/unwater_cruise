/*
 * @brief	��openmv1����Ѳ��ʹ�ã����ڽ��ջش��ĽǶ��Լ��ؾ�����
 * @author 	������ΰ
 * @Date	��2020.10.08
 */

/*
 *NOTE  : �������ݵ�Э�飬Э�����û��д
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
		__HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);												//��������4 openmv1 ���ڿ����ж�
		HAL_UART_Receive_DMA(&huart4, Openmv1_buf.RX_pData,sizeof(Openmv1_buf.RX_pData));  		//��������4   dma	��������
		__HAL_UART_CLEAR_IDLEFLAG(&huart4);														//��� ����4 �����жϱ�־λ
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
		
			//���յ�������   ��ŵ�OPENMV1_MSG�ṹ����			
			memcpy(&Openmv1_msg,&Openmv1_buf.RX_pData,10);	
					
//			memcpy(&Openmv1_msg.Head,&Openmv1_buf.RX_pData[0],1);
//			memcpy(&Openmv1_msg.Head_1,&Openmv1_buf.RX_pData[1],1);	
//			memcpy(&Openmv1_msg.ANGLE,&Openmv1_buf.RX_pData[2],4);	
//			memcpy(&Openmv1_msg.DISTANCE,&Openmv1_buf.RX_pData[6],4);				
			
		    memset(Openmv1_buf.RX_pData,'\0',sizeof(Openmv1_buf.RX_pData));
			HAL_UART_Receive_DMA(huart,Openmv1_buf.RX_pData,sizeof(Openmv1_buf.RX_pData));  
		}
}


//���ڽ������ݴ�����



