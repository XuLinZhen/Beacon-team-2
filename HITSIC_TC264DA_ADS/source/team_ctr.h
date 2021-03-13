/*
 * team_ctr.h
 *
 *  Created on: 2021年2月25日
 *      Author: Administrator
 */

#ifndef SOURCE_TEAM_CTR_H_
#define SOURCE_TEAM_CTR_H_

#include "common.h"
//#include "sc_ftm.h"
#include "image.h"
#include "team_elec.h"
#include "math.h"
#include "IfxGtm_PinMap.h"
//#include"sc_host.h"

extern float error_n;//偏差值，定义为全局变量，为了在菜单显示
extern int delay_runcar;//延迟发车标志位
extern int mot_left;
extern int mot_right;
extern float M_right_drs;
extern int mora_flag;
extern float M_left_drs;    //左电机理想速度
extern float M_right_pwm;
extern float wifidata[20];
extern float da[8];

typedef struct _cardata{
    int32 Motorspeed[3] ;//= {22,0,150};
    float servo_mid;//=7.51;            //定义舵机中值
    float servo_pwm;//=7.51;            //定义舵机pwm值
    float Kp;// = 0.0091;                //定义舵机比例系数
    float Kd ;//= 0.0065;                //定义舵机微分系数
    float M_Kp;// = 1.0;              //定义电机比例系数
    float M_Ki; //= 0.4;              //定义电机积分系数
    float Sradio;// = 2.0;
}cardata;
extern cardata c_data[2];//车数据数组
/**********************************************************************************************************************
*  @brief      电机控制函数在定时器中断中运行
*  @return     void 匀速控制舵机
*  @since      v1.1
*  Sample usage:                 Motor_ctr;
**********************************************************************************************************************/
void Motor_ctr(void);//电机控制，暂时匀速
/**********************************************************************************************************************
*  @brief      舵机初始化
*  @return     void 电磁或摄像头控制舵机
*  @since      v1.1
*  Sample usage:                 servo_init;
**********************************************************************************************************************/
void servo_init(float *pwm);
/**********************************************************************************************************************
*  @brief      pid控制函数在跑车函数主函数中运行
*  @return     void 舵机偏差
*  @since      v1.1
*  Sample usage:                 servo_pid();
**********************************************************************************************************************/
void servo_pid(void);
/**********************************************************************************************************************
*  @brief      pid控制函数在舵机中断中运行
*  @return     void 舵机pwm值
*  @since      v1.1
*  Sample usage:                 servo;
**********************************************************************************************************************/
void servo(void);
/**********************************************************************************************************************
*  @brief      电机pid控制函数
*  @return     void 电机占空比
*  @since      v1.1
*  Sample usage:                 Motor_pid();
**********************************************************************************************************************/
void Motor_pid(void);
/**********************************************************************************************************************
*  @brief      电机理想速度初始化函数
*  @return     void 电机理想速度
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Motorsp_Init(void);
/**********************************************************************************************************************
*  @brief      电机理想速度设置函数
*  @prama       x 左电机理想速度
*  @prama       y 右电机理想速度
*  @return     void 电机理想速度
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Motorsp_Set(float x,float y);
/**********************************************************************************************************************
*  @brief      电机差速比计算函数
*  @prama       x 舵机打角
*  @prama       y 右电机理想速度
*  @return     float          差速比
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Speed_radio(float x);
/**********************************************************************************************************************
*  @brief      延迟发车标志位设置函数
*  @return     void          关闭中断，标志位设置为1
*  @since      v1.1
*  Sample usage:                 Delay_car();
**********************************************************************************************************************/
void Delay_car();

#endif /* SOURCE_TEAM_CTR_H_ */
