/*
 ******************************************************
 * @author   :zhao xinwei
 * @Date     :2020.10.06
 * @version  :1.0 
 * @brief	 :��������
 *
 ******************************************************
 */

#include "ControlTask.h"
#include "MessageTask.h"


/*********************���Ʒ�ʽ�л�****************/
/************************************************/
#define DEEP_CONTROL	0
#define FIND_LINE 		1
#define FIND_BLOB 		0
#define MOTOR_TEST 		0
#define HEADING_CONTROL 0
/************************************************/
/************************************************/


float angle = 0;
float inter = 0;
float Angle_PID_out = 0;
float Inter_PID_out = 0;
float Deep_PID_out = 0;
float Differential = 0;
float x_offest = 0.0f;
float y_offest = 0.0f;
float x_offest_out = 0.0f;
float y_offest_out = 0.0f;
float heading_pid_out = 0.0f;

float Deep_tar = 0.0f;
float heading_tar = 0.0f;



/*********************�����������****************/
/************************************************/
void ControlTask_Function(void const * argument)
{
    portTickType tick = xTaskGetTickCount();
    NLPID_Init();
	
    while(1)
    {
		run_time[1] = getRunTime(1);
		
		
		#if DEEP_CONTROL		//����ǰ��
			Deep_tar = 10.0;    //Ŀ�����
			Deep_PID_out = PID_Inner_Calculate(Deep_tar,control_data.depth,&Deep_PID);	
		
			__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_3,1450);		//��ǰ	
			__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_1,1550);		
			__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_1,1550);	
			__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_3,1450);
			Move_UpDown(Deep_PID_out);
		#endif
		
		
		#if MOTOR_TEST			//�������
			test_motor_fb();		
		#endif 

		
		#if FIND_LINE			//Ѳ��										 	 			
			angle = Openmv1_msg.ANGLE;											
			Angle_PID_out = PID_Inner_Calculate(MID,angle,&Angle_PID);  		
			
			inter = Openmv1_msg.DISTANCE;										
			Inter_PID_out = PID_Inner_Calculate(MID,inter,&Inter_PID);			
			
			Differential = Inter_PID_out + Angle_PID_out;						
			
			Move_Left_Ctrl(60-Differential);									
			Move_Right_Ctrl(60+Differential);												
		#endif
		
		
		#if FIND_BLOB			//��λ���ʶ�𱨾�			
		if(Openmv2_msg.Status == 1) 				
		{
			// ���Ʊ�������  ����ָʾ�Ʊ���
			HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_SET);
			//��ȡƫ����
			x_offest = Openmv2_msg.X_offest;
			y_offest = Openmv2_msg.Y_offest;
			
				if (x_offest > DeadBand || x_offest < -DeadBand)      				//һ��Ҫ���ú���������������豸�����Ƶ������  
				{
					x_offest_out = PID_Inner_Calculate(X_MID,x_offest,&X_offest_PID);
					y_offest_out = PID_Inner_Calculate(Y_MID,y_offest,&Y_offest_PID);					
					
					Move_Horizontal(y_offest_out, 0.0,x_offest_out);					
				}											
		}

			if (Openmv2_msg.Status == 2) 			
		{
			// ���Ʊ�������  Բ��ָʾ�Ʊ���
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_SET);
			//��ȡƫ����
			x_offest = Openmv2_msg.X_offest;
			y_offest = Openmv2_msg.Y_offest;
			
				if (x_offest > DeadBand || x_offest < -DeadBand)      				//һ��Ҫ���ú���������������豸�����Ƶ������ 
				{
					x_offest_out = PID_Inner_Calculate(X_MID,x_offest,&X_offest_PID);
					y_offest_out = PID_Inner_Calculate(Y_MID,y_offest,&Y_offest_PID);					
				
					Move_Horizontal(y_offest_out, 0.0,x_offest_out);					
				}			
		}				
		#endif
		
		#if HEADING_CONTROL
		heading_pid_out = YAWPID_Control(&YawNLPID,control_data.yawing,control_data.yaw_groy,heading_tar);
		heading_pid_out = CONSTRAIN(heading_pid_out, 50, -50); 

		Horizontal_Control(0.0,heading_pid_out);

		
		#endif 
		
		
		HAL_IWDG_Refresh(&hiwdg);												//ע��ι�����������᲻�ϸ�λ
        vTaskDelayUntil(&tick,50);
		
    }

}

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
