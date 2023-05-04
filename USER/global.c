#include "global.h"


#define M_PI 3.1415926

///**
//  * @funNm  IIR_2OrderLpf_Init
//  * @brief  二阶低通滤波器初值计算IIR滤波器形式
//  * @param SOTF_typeDef:二阶变换结构体
//  * @param fs:采样频率
//  * @param fc:截止频率 注意：fc必须满足 fs >= 3.3*fc 
//  * @retval void:void
//  */
//void IIR_2OrderLpf_Init(SOTF_typeDef *n, float fs, float fc)
//{
//    float Ohm = tan(M_PI * fc / fs);
//    float c   = 1 + 2 * cos(M_PI / 4) * Ohm + Ohm * Ohm;
//    n->num[0] = Ohm * Ohm / c;
//    n->num[1] = Ohm * Ohm * 2 / c;
//    n->num[2] = Ohm * Ohm / c;
//    n->den[0] = 1;
//    n->den[1] = 2 * (Ohm * Ohm - 1) / c;
//    n->den[2] = (1 - 2 * cos(M_PI / 4) * Ohm + Ohm * Ohm) / c;
//}

//float SOTFOutput(SOTF_typeDef *gs, float data)
//{
//    gs->uk   = data;
//    gs->yk   = -(gs->den[1]) * (gs->yk_1) - (gs->den[2]) * (gs->yk_2) + (gs->num[0]) * (gs->uk) + (gs->num[1]) * (gs->uk_1) + (gs->num[2]) * (gs->uk_2);
//    gs->yk_2 = gs->yk_1;
//    gs->yk_1 = gs->yk;
//    gs->uk_2 = gs->uk_1;
//    gs->uk_1 = gs->uk;
//    return (gs->yk);

//}


