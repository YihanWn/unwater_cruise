/*
 *@auther   :zhao xinwei
 *@Date     :2020.10.06
 */

#include "pwm.h"


/* 
 * @brief   :pwm初始化      
 */
void pwm_init(void){
    int i;

		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
		

		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);

		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,MIDValue);      		//水平推进器——左后 pc6 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,MIDValue); 			//水平推进器——左中 pc7 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,MIDValue); 			//水平推进器——左前 pb0 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,MIDValue);       //pb1

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,MIDValue); 			//水平推进器——右后  pd12
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,MIDValue); 			//水平推进器——右中  pd13 
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MIDValue);		 	//水平推进器——右前  pd14
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MIDValue);		  //pd15
	
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1400);			//水泵	pa1
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1400);			//LED照明灯  pa2
	  HAL_Delay(2000);
	  for(i=1450;i<1570;i++){
	  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);      		//水平推进器——左后 pc6 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,i); 			//水平推进器——左中 pc7 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,i);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,i); 			//水平推进器——右后  pd12
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,i); 			//水平推进器——右中  pd13 
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,i);	  
		delay_ms(50);
		}
    for(i=1570;i>1500;i--){
	  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);      		//水平推进器——左后 pc6 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,i); 			//水平推进器——左中 pc7 
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,i);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,i); 			//水平推进器——右后  pd12
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,i); 			//水平推进器——右中  pd13 
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,i);	
			
		delay_ms(50);
		}
		__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_3,1350);		//左前	
		__HAL_TIM_SET_COMPARE(&Left_Motor, TIM_CHANNEL_1,1650);		
		__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_1,1650);	
		__HAL_TIM_SET_COMPARE(&Right_Motor,TIM_CHANNEL_3,1350);
		
		
}
