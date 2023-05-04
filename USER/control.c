#include "control.h"

/*
 *控制说明                      		  俯视图     1 2 3 4 
 *                                                5 6              
 *
 * 											1 pb0				2 pd14
 *									
 *									    5	pc7			  6 pd13
 *
 *											4	pc6				3 pd12
 *
 *         定义设备运转情况    前进后退、左转右转、45°方向前进
 */
 
 

  
#define Hand_Ctrl(x)    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,Hand_MID + x)
  
 /*
  * @brief  :水平运动控制函数
  * @param	： l_r > 0 左移， < 0右移
  * @param	： f_b > 0 前移， < 0后移
  *	@NOTE	：此处函数需要做修改
  */
void Move_Horizontal(float f_b, float rotate,float l_r)      
{		
		__HAL_TIM_SET_COMPARE(&Left_Motor ,TIM_CHANNEL_1,MIDValue + f_b + l_r + rotate);    		//左后
		__HAL_TIM_SET_COMPARE(&Left_Motor ,TIM_CHANNEL_3,MIDValue - f_b + l_r + rotate);			//左前
		
		__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_1,MIDValue + f_b - l_r + rotate);			//右后
		__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_3,MIDValue - f_b - l_r + rotate);			//右前	
}


/**
  * @funNm    Move_UpDown
  * @brief    上浮下潜控制函数
  * @param	  Value < 0 下潜控制
  * @retval
**/
void Move_UpDown(float Value)
{
		__HAL_TIM_SET_COMPARE(&Left_Motor , TIM_CHANNEL_2,  MIDValue  + Value);  
		__HAL_TIM_SET_COMPARE(&Right_Motor, TIM_CHANNEL_2,  MIDValue  + Value);  
		
}


void LED_TOGGLE(void)
{
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);
}


/**
  * @funNm    Move_Left_Ctrl
  * @brief    左侧推进器控制函数
  * @param	
  * @retval
**/
void Move_Left_Ctrl(float value)
{	
	__HAL_TIM_SET_COMPARE(&Left_Motor,TIM_CHANNEL_1,MIDValue + value);
	__HAL_TIM_SET_COMPARE(&Left_Motor,TIM_CHANNEL_3,MIDValue - value);
}



/**
  * @funNm    Move_Right_Ctrl
  * @brief    右侧推进器控制函数
  * @param	
  * @retval
**/
void Move_Right_Ctrl(float value)
{	
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_1,MIDValue + value);
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_3,MIDValue - value);
}

/**
  * @funNm   test_motor	
  * @brief   电机测试
  * @param	
  * @retval
**/

void test_motor_fb(void)
{
	__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_1,1600);		//左后
	__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_2,1650);		//左中
	__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_3,1400);		//左前
	__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_4,1600);
	
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_1,1600);		//右后
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_2,1650);		//右中
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_3,1400);		//右前
	__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_4,1600);

}


void l_r_test(void)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1600);
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,1400);
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,1600);
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,1600);
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,1400);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,1400);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1400);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1600);
}


/**
  * @funNm   Wat_LED_Switch	
  * @brief   水泵、LED照明灯开关函数
  * @param	
  * @retval
**/
void Wat_LED_Switch(u8 ctrl_num,u8 switch_sign)
{
	if(ctrl_num == 0)
	{
		if (switch_sign)
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1600);
		}
		else
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1400);
		}
	}
	else 
	{
		if (switch_sign)
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1600);
		}
		else
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1400);
		}
	}	
	
}


/**
  * @funNm	Left_Conver	 
  * @brief	设置电机PWM 去死区 线性化速度	 
  * @param	in_speed (-100 : 100) 
  * @retval	对应速度的pwm  
*/ 
float Left_Conver(float in_speed)
{
	static float out_pwm = 1500;
	float speed = CONSTRAIN(in_speed, 50,-50);
	if(speed == 0){
		out_pwm = 1500;
	}else if(speed>0){
		if(speed < 2){speed = 2;}
		out_pwm = speed + 1525;//(4B)  //1560;//(3B)//1550;
	}else if(speed<0){
		if(speed > -2){speed = -2;}
		out_pwm = speed - 1485;//(4B)  //1450;//(3B)
	}
	return out_pwm;
}

/**
  * @funN	Right_Conver	 
  * @brief	设置电机PWM 去死区 线性化速度	 	 
  * @param	in_speed (-100 : 100) 
  * @retval	对应速度的pwm  
*/ 
float Right_Conver(float in_speed)
{
	static float out_pwm = 1500;
	float speed = CONSTRAIN(in_speed, 50,-50);
	if(speed == 0){
		out_pwm = 1500;
	}else if(speed>0){
		if(speed < 2){speed = 2;}
		out_pwm = speed + 1525;//(34B)//1530;
	}else if(speed<0){
		if(speed > -2){speed = -2;}
		out_pwm = speed + 1485;//(34B)//1470;
	}
	return out_pwm;
}


/**
  * @funN	Horizontal_Control	 
  * @brief	设置电机速度	 
  * @param	front_back 前后速度  left_right左右转速度
  * @retval	
*/ 
int left_pwm[1];
int right_pwm[1];
void Horizontal_Control(int16_t front_back,int16_t left_right)
{
		static int left_motor;
		static int right_motor;
	

		left_pwm [0] = Left_Conver (left_right);     //由输入的速度算出所需pwm值
		right_pwm[0] = Right_Conver(-left_right);

	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,right_pwm[0]);	//左后
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,left_pwm[0]);	//左前
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,left_pwm[0]);	//右后
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,right_pwm[0]);	//右前
	
}


void Waring_Light(int light)
{
	if (light == 0)      	 //红灯报警
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_SET);
		delay_sys_us(1000);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_RESET);
		delay_sys_us(1000);
	}
	else if (light == 1) 	 //蓝灯报警
	{
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin,GPIO_PIN_SET);
		delay_sys_us(1000);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin,GPIO_PIN_RESET);
		delay_sys_us(1000);
	}	
	else  					 //绿灯报警
	{	
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_SET);
		delay_sys_us(1000);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET);
		delay_sys_us(1000);
	}
}
