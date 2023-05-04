/*
 * @author   :zhao xinwei
 * @Date     :2020.10.06
 * @version  :1.0 
 */


#ifndef __CONTROL_H
#define __CONTROL_H

#include "includes.h"

#define	Left_Motor 		htim3
#define Right_Motor 	htim4	
	
#define MAX_SPEED 	  			   150 
#define ConstSpeedq    			   100
#define X_MID           				   80
#define Y_MID		   				 	   60
#define Expect_Distance 			68
#define Hand_MID						1500		

#define Water_motor					1
#define LED_light                   0
#define linedead					3
#define angledead		 			3

#define LED_RED      0
#define LED_BLUE     1
#define LED_GREEN    2

typedef enum 
{
    MANUAL = 0,
    AUTO
}ControlState_t;


typedef struct{
//	int16_t channel[4];
	float temperture;
	float depth;
	float yawing;       //航向
	float pitching;   	//前后偏角
	float rolling;    	//左右偏角
	
	//添加如下内容
	float pitch_groy;		
	float roll_groy;
	float yaw_groy;
	
	float humi;
	
	
	ControlState_t depth_state;
	ControlState_t heading_state;
	bool  Control_Disable;
	float navi_angle;
	float navi_distance;
}ControlMsg_t;

//函数声明
void Move_Horizontal(float f_b, float rotate,float l_r);
void Move_UpDown(float Value);
void Move_Left_Ctrl(float value);
void Move_Right_Ctrl(float value);
void test_motor_fb(void);
void l_r_test(void);
void LED_TOGGLE(void);
float Right_Conver(float in_speed);
float Left_Conver(float in_speed);
void Waring_Light(int light);
void Wat_LED_Switch(u8 ctrl_num,u8 switch_sign);
void Horizontal_Control(int16_t front_back,int16_t left_right);


extern ControlMsg_t control_data;




//#define pi 3.1415926

//typedef unsigned short int uint16_t;
//typedef unsigned int       uint32_t;
//typedef unsigned char      uint8_t;
//typedef enum
//{
//    MANUAL = 0,
//    AUTO
//} ControlState_t;

//#pragma pack(1)
//typedef struct
//{
//    short          channel[4];
//    float          depth;
//    float          heading;  //航向
//    float          pitching; //前后偏角
//    float          rolling;  //左右偏角
//    ControlState_t depth_state;
//    ControlState_t heading_state;
//    //	float voltage;
//} ControlMsg_t;

//typedef struct
//{
//    u8    depth_state;   //定深状态
//    u8    heading_state; //定航状态
//    float gyroX;         //角速度
//    float gyroY;
//    float gyroZ;
//    float pid_head;   //定航
//    float pid_updown; //定深
//    float headP;      //定航PID系数
//    float headI;
//    float headD;
//    float depP; //定深PID系数
//    float depI;
//    float depD;
//    short fb_rocker;
//    short lr_rocker;
//    short ud_rocker;
//    short turn_rocker;
//    u16   FR_val; //右前pwm
//    u16   FL_val;
//    u16   BR_val;
//    u16   BL_val;
//    u16   UR_val;
//    u16   UL_val;
//} CtrlPara_t;
//#pragma pack()
///**
// * @brief	推进器推力最大最小宏定义
// */
//#define PROPFMax 62.07
//#define PROPFMin -40.6

///**
//  * @funNm	ROV_FValuetypedef
//  * @brief  初始化使用，保存推力限制的阈值
//  */
//typedef struct
//{
//    float Fxmax;     //x轴最大值
//    float Fxmin;     //x轴最小值
//    float Fymax;     //y轴最大值
//    float Fymin;     //y轴最小值
//    float Fzmax;     //z轴最大值
//    float Fzmin;     //z轴最小值
//    float Fyawmax;   //yaw轴最大值
//    float Fyawmin;   //yaw轴最小值
//    float Fpitchmax; //pitch轴最大值
//    float Fpitchmin; //pitch轴最小值
//    float Frollmax;  //roll轴最大值
//    float Frollmin;  //roll轴最小值
//} ROV_FValuetypedef;
//#define MAX_SPEED 500 //490
//#define MotorPWMMidVal       1490 
////#define DELTA_PWM     10
//#define MAX_PWM     (MotorPWMMidVal + MAX_SPEED)
//#define MIN_PWM     (MotorPWMMidVal - MAX_SPEED)
//#define SPEED_COEFF 4.0 //4.9
////#define CONSTRAIN(x,max,min) (x>max?max:(x<min?min:x))
//#define MAX(a, b) (a > b ? a : b)
//#define MIN(a, b) (a < b ? a : b)

//// extern int  DogBeatCount;
//// extern u8   DogHeardBeat(void);
//// extern void FeedDogHeardBeat(void);
//// void        CtrlMidPwmInit(void);
//void        Cal6FreedomForceValue(float Tang, float Tmin, float Tmax);
//void        ThrottleToForceControl(bool Closestate, float Tx, float Ty, float Tz, float Tyaw, float Tpitch, float Troll, float yaw, float pitch, float roll);
//float       SetValf32(float x, float Lval, float Hval);
//float       sign(float x);
#endif
