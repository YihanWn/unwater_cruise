/*
 * @author   :zhao xinwei
 * @Date     :2020.10.06
 * @version  :1.0 
 */

#include "pid.h"


PID_t Angle_PID;		//角度PID
PID_t Inter_PID;		//截距PID
PID_t Deep_PID;
PID_t X_offest_PID;
PID_t Y_offest_PID;
NLPID_Typedef YawNLPID; 

//  pid 参数需要修改
								//  kp,    ki,     kd,    p_max,     p_min,    i_max,     i_min,    d_max,     d_min,  out_max,  out_min   
float 	 Angle_pid_param[11]   ={   1.0,  0.00001,  0.0001, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED };
float    Inter_pid_param[11]   ={   1.0,  0.00001,  0.0001, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED };
float    Deep_pid_param [11]   ={   7.0,  0.0001,   0.001, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED };
float    X_offset_pid_param[11]={   1.0,  0.000,   0.0, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED };
float    Y_offset_pid_param[11]={   1.0,    0.0,   0.0, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED, MAX_SPEED, -MAX_SPEED };


void PID_Init(void)                                                
{
	PID_Param_Init(&Angle_PID,Angle_pid_param);       
	PID_Param_Init(&Inter_PID,Inter_pid_param); 
	PID_Param_Init(&Deep_PID,Deep_pid_param);
	PID_Param_Init(&X_offest_PID,X_offset_pid_param); 
	PID_Param_Init(&Y_offest_PID,Y_offset_pid_param);
	
}
 
void PID_Param_Init(PID_t *pid, float *pid_param) //PID 参数设置函数
{
	pid->Kp = pid_param[0];
	pid->Ki = pid_param[1];;
	pid->Kd = pid_param[2];;
	pid->PoutMAX = pid_param[3];
	pid->PoutMIN = pid_param[4];
	pid->IoutMAX = pid_param[5];
	pid->IoutMIN = pid_param[6];
	pid->DoutMAX = pid_param[7];
	pid->DoutMIN = pid_param[8];
	pid->OutMAX = pid_param[9];
	pid->OutMIN = pid_param[10];
}



/*
 * @brief 	:内环PID计算
 * @tar 	:目标位置
 * @input	:反馈值
 */
float PID_Inner_Calculate(float tar,float input,PID_t *pid)
{
	pid->Bias = tar - input;
	/* Pout 计算  限幅 */
	pid->Pout = pid->Kp * pid->Bias;
	pid->Pout = CONSTRAIN (pid->Pout,pid->PoutMAX,pid->PoutMIN);
	/* Iout 计算  限幅 */
	pid->Iout += pid->Ki * pid->Bias;
	pid->Iout = CONSTRAIN (pid->Iout,pid->IoutMAX,pid->IoutMIN);
	/* Dout 计算  限幅 */
	pid->Dout = pid->Kd*(pid->Bias  - pid->Last_Bias);
	pid->Dout = CONSTRAIN (pid->Dout,pid->DoutMAX,pid->DoutMIN);
	/* OutPut 计算 限幅 */
	pid->Out = pid->Pout + pid->Iout + pid->Dout;
	pid->Out = CONSTRAIN (pid->Out,pid->OutMAX,pid->OutMIN);
	
	pid->Last_Bias = pid->Bias;
	return pid->Out;	
} 




/*
 * @brief 	:二阶滤波
 */
float SOTFOutput(SOTF_typeDef* gs,float data)//二阶滤波
{
	gs->uk=data;
	gs->yk=-(gs->den[1])*(gs->yk_1)-(gs->den[2])*(gs->yk_2) 
					+(gs->num[0])*(gs->uk)+(gs->num[1])*(gs->uk_1)+(gs->num[2])*(gs->uk_2);
	gs->yk_2=gs->yk_1;
	gs->yk_1=gs->yk;
	gs->uk_2=gs->uk_1;
	gs->uk_1=gs->uk;
	return  (gs->yk);
}

float YawErrorDispose(float now,float obj)
{
	float err=obj-now;
	if(err > 180){
		return (180 - fabs(now)+(180-obj)+obj);
	}
	else if(err < -180){
		return (-1*((180 - fabs(now))+(180+obj))+obj);
	}
	return now;
}

/**
  * @funNm  SetValf32
  * @brief  输入参数限幅输出
  * @param	x:输入参数
  * @param	Lval:最小阈值
  * @param	Hval:最大阈值
  * @retval float:返回限幅后的数
  */
float SetValf32(float x,float Lval,float Hval)//输入参数限幅输出
{
	if(x > Hval){
		return Hval;
	}
	else if(x < Lval){
		return Lval;
	}
	return x;
}




float NLPID_Init(void)
{
	YawNLPID.OuterLoopEN=true;
	YawNLPID.T=0.02;
	YawNLPID.ZVal=0;
	/***外环输入*5Hz***/
	YawNLPID.OIntf.num[0]=0.0571;
	YawNLPID.OIntf.num[1]=0.1143;
	YawNLPID.OIntf.num[2]=0.0571;
	YawNLPID.OIntf.den[0]=1.0000;
	YawNLPID.OIntf.den[1]=-1.0438;
	YawNLPID.OIntf.den[2]=0.2724;
	/*********/
	/***外环反馈*15Hz***/
	YawNLPID.Ofbtf.num[0]=0.2354;
	YawNLPID.Ofbtf.num[1]=0.4708;
	YawNLPID.Ofbtf.num[2]=0.2354;
	YawNLPID.Ofbtf.den[0]=1.0000;
	YawNLPID.Ofbtf.den[1]=-0.0592;
	YawNLPID.Ofbtf.den[2]=0.0009;
	/****航向外环PID*****/
	YawNLPID.OP=0.5;//7.4
	YawNLPID.OI=0.000;//0.02;//
	YawNLPID.OD=0.08;
	YawNLPID.OeImax=100;
	YawNLPID.OoutMax=2000;
	YawNLPID.OoutMin=-2000;
	/****航向内环PID******/
	YawNLPID.falnum=1.5;
	YawNLPID.INVal=25;
	YawNLPID.IP=1.0;
	YawNLPID.II=0.00;
	YawNLPID.ID=0.01;
	
	YawNLPID.IeImax=100;//300
	/***内环输入****/
	YawNLPID.Oouttf.num[0]=1;
	YawNLPID.Oouttf.num[1]=0;
	YawNLPID.Oouttf.num[2]=0;
	YawNLPID.Oouttf.den[0]=1;
	YawNLPID.Oouttf.den[1]=0;
	YawNLPID.Oouttf.den[2]=0;
	/***内环反馈15Hz****/
	YawNLPID.Ifbtf.num[0]=0.2354;
	YawNLPID.Ifbtf.num[1]=0.4708;
	YawNLPID.Ifbtf.num[2]=0.2354;
	YawNLPID.Ifbtf.den[0]=1.0000;
	YawNLPID.Ifbtf.den[1]=-0.0592;
	YawNLPID.Ifbtf.den[2]=0.0009;

}





/*
 *定航
 */
float YAWPID_Control(NLPID_Typedef *nl,float Onow,float Inow,float obj)
{
	SOTFOutput(&nl->OIntf,obj);
	SOTFOutput(&nl->Ofbtf,Onow);
	SOTFOutput(&nl->Ifbtf,Inow);
	float CLHeading=YawErrorDispose(nl->Ofbtf.yk,nl->OIntf.yk);//判断转向后对数据进行收敛方向判断
	if(nl->OuterLoopEN == true)//外环使能
	{
		//外环
		nl->Oe=nl->OIntf.yk - CLHeading;    												//外环误差 
		if(fabs(nl->Oe)< nl->ZVal) return 0;												//死区控制
		
		nl->Oe1= ((nl->OIntf.yk - nl->OIntf.yk_2)-(nl->Ofbtf.yk-nl->Ofbtf.yk_2))/nl->T;//微分
		nl->OeI= nl->OeI+nl->Oe*nl->T;															//积分
		nl->OeI= SetValf32(nl->OeI,-1*nl->OeImax,nl->OeImax);				//限幅	
		nl->Ooutput=nl->OP * nl->Oe + nl->OI*nl->OeI+nl->OD*nl->Oe1;//输出
		nl->Ooutput=SetValf32(nl->Ooutput,nl->OoutMin,nl->OoutMax);	//限幅

		//内环
		SOTFOutput(&nl->Oouttf,nl->Ooutput);												//二阶滤波
		nl->Ie= nl->Oouttf.yk - nl->Ifbtf.yk;    										//内环误差计算
		nl->Ie1=((nl->Oouttf.yk - nl->Oouttf.yk_2) - (nl->Ifbtf.yk - nl->Ifbtf.yk_2))/nl->T; 	//微分
		nl->IeI=nl->IeI+nl->Ie*nl->T;																//积分
		nl->IeI= SetValf32(nl->IeI,-1*nl->IeImax,nl->IeImax);				//限幅
//		nl->Ioutput=nl->IP*nl->Ie+nl->II*nl->IeI+nl->ID*nl->Ie1;
		nl->Ioutput= nl->IP*NLfal(nl->Ie,nl->falnum,nl->INVal)			
		+nl->II*nl->IeI
		+nl->ID*NLfal(nl->Ie1,nl->falnum/2,nl->INVal);
	}
	else{
		SOTFOutput(&nl->Oouttf,obj);																//二阶滤波
		//内环
		nl->Ie= nl->Oouttf.yk - nl->Ifbtf.yk;												//内环误差计算
		nl->Ie1=((nl->Oouttf.yk - nl->Oouttf.yk_2) - (nl->Ifbtf.yk - nl->Ifbtf.yk_2))/nl->T;	//微分
		nl->IeI=nl->IeI+nl->Ie*nl->T;																//积分
		nl->IeI= SetValf32(nl->IeI,-1*nl->IeImax,nl->IeImax);				//限幅
//		nl->Ioutput=nl->IP*nl->Ie+nl->II*nl->IeI+nl->ID*nl->Ie1;
		nl->Ioutput= nl->IP*NLfal(nl->Ie,nl->falnum,nl->INVal)
		+nl->II*nl->IeI
		+nl->ID*NLfal(nl->Ie1,nl->falnum/2,nl->INVal);
	}
	return nl->Ioutput;
}


/**
  * @funNm	sign
  * @brief  输入值取符号 返回±1
  * @param	x:输入float型数据
  * @retval x > 0 return 1 x < 0 return -1 x = 0 return 0 
  */
float sign(float x)// 输入值取符号 返回±1
{
	float output=0;
	if(x > 0){
		output=1;
	}
	else if(x < 0){
		output=-1;
	}
	return output;
}

float NLfal(float x,float a,float val)
{
	float out;
	float Absx=fabs(x);
	float signx=sign(x);
	if(Absx > 10000){
		out=x;
	}
	else{
		out=signx*val*pow(Absx/val,1.0/a);
	}
	return out;
}
