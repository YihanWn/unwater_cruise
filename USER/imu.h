#ifndef __IMU_H
#define __IMU_H


#include "includes.h"

#define		IMU_USART		huart2
#define 	RX_LEN 			256	


typedef struct
{
	u8 	RX_Flag:1;
	u16 RX_Size;
	u8 	RX_Date[RX_LEN];
}Usart_Rec_MSG;




typedef struct
{
	float acceleration[3];		//���ٶ�
	float angular_velocity[3];//���ٶ�
	float Angle[3];						//�Ƕ�
	uint8_t	state;
	int	freq;	
}IMU_Raw_Msg;




typedef struct
{
	float	pitch;	//������
	float	roll;		//�����
	float	yaw;		//�����
	  
	float pitch_groy;
	float roll_groy;
	float yaw_groy;
		
	float acc_pitch;
	float acc_yaw;
	float acc_roll;
}IMU_Msg_t;



extern	IMU_Msg_t imu_data;
extern Usart_Rec_MSG Imu_Rec_Msg;


void Imu_Rec_IDLE_Fun(UART_HandleTypeDef *huart);
void imu_init(void);
void Imu_Data_unpack(uint8_t* buf, uint16_t len);
void IMU_ReadData(IMU_Msg_t *mpu6050_data);

#endif





