#ifndef __INCLUDES_H
#define __INCLUDES_H
//Cube生成
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"

#include "tim.h"
#include "usart.h"
#include "spi.h"
#include "gpio.h"
#include "iwdg.h"
//C标准库
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
//自定义 
#define	u8  unsigned char
#define u16 unsigned short int
#define	u32 unsigned int
#define MIDValue 1500
//Drivers
#include "board.h"
#include "imu.h"
#include "pwm.h"
#include "openmv1.h"
#include "openmv2.h"
#include "control.h"
#include "dht11.h"
#include "ms5803.h"
#include "PID.h"


#endif
