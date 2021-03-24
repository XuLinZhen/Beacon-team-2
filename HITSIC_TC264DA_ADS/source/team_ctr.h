/*
 * team_ctr.h
 *
 *  Created on: 2021��2��25��
 *      Author: Administrator
 */

#ifndef SOURCE_TEAM_CTR_H_
#define SOURCE_TEAM_CTR_H_

#include "common.h"
//#include "sc_ftm.h"
#include "image.h"
#include "team_elec.h"
#include "math.h"
#include "SmartCar_Encoder.h"
#include "SmartCar_Pwm.h"
#include "my_math.h"
//#include"sc_host.h"

extern float error_n;//ƫ��ֵ������Ϊȫ�ֱ�����Ϊ���ڲ˵���ʾ
extern int delay_runcar;//�ӳٷ�����־λ
extern int mot_left;
extern int mot_right;
extern float M_right_drs;
extern int mora_flag;
extern float M_left_drs;    //���������ٶ�
extern float M_right_pwm;
extern float wifidata[20];
extern float da[8];

typedef struct pidCtrl_t
{
    float kp, ki, kd;
    float errCurr, errIntg, errDiff, errPrev;
}pidCtrl_t;

extern pidCtrl_t ctrl_pwm;


typedef struct _cardata{
    int32 Motorspeed[3] ;//= {22,0,150};
    float servo_mid;//=7.51;            //��������ֵ
    float servo_pwm;//=7.51;            //������pwmֵ
    float Kp;// = 0.0091;                //����������ϵ��
    float Kd ;//= 0.0065;                //������΢��ϵ��
    float M_Kp;// = 1.0;              //����������ϵ��
    float M_Ki; //= 0.4;              //����������ϵ��
    float Sradio;// = 2.0;
}cardata;
extern cardata c_data[2];//����������
/**********************************************************************************************************************
*  @brief      ������ƺ����ڶ�ʱ���ж�������
*  @return     void ���ٿ��ƶ��
*  @since      v1.1
*  Sample usage:                 Motor_ctr;
**********************************************************************************************************************/
void Motor_ctr(void);//������ƣ���ʱ����
/**********************************************************************************************************************
*  @brief      �����ʼ��
*  @return     void ��Ż�����ͷ���ƶ��
*  @since      v1.1
*  Sample usage:                 servo_init;
**********************************************************************************************************************/
void servo_init(float *pwm);
/**********************************************************************************************************************
*  @brief      pid���ƺ������ܳ�����������������
*  @return     void ���ƫ��
*  @since      v1.1
*  Sample usage:                 servo_pid();
**********************************************************************************************************************/
void servo_pid(void);
/**********************************************************************************************************************
*  @brief      pid���ƺ����ڶ���ж�������
*  @return     void ���pwmֵ
*  @since      v1.1
*  Sample usage:                 servo;
**********************************************************************************************************************/
void servo(void);
/**********************************************************************************************************************
*  @brief      ���pid���ƺ���
*  @return     void ���ռ�ձ�
*  @since      v1.1
*  Sample usage:                 Motor_pid();
**********************************************************************************************************************/
void Motor_pid(void);
/**********************************************************************************************************************
*  @brief      ��������ٶȳ�ʼ������
*  @return     void ��������ٶ�
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Motorsp_Init(void);
/**********************************************************************************************************************
*  @brief      ��������ٶ����ú���
*  @prama       x ���������ٶ�
*  @prama       y �ҵ�������ٶ�
*  @return     void ��������ٶ�
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Motorsp_Set(float x,float y);
/**********************************************************************************************************************
*  @brief      ������ٱȼ��㺯��
*  @prama       x ������
*  @prama       y �ҵ�������ٶ�
*  @return     float          ���ٱ�
*  @since      v1.1
*  Sample usage:                 Motorsp_Init();
**********************************************************************************************************************/
void Speed_radio(float x);
/**********************************************************************************************************************
*  @brief      �ӳٷ�����־λ���ú���
*  @return     void          �ر��жϣ���־λ����Ϊ1
*  @since      v1.1
*  Sample usage:                 Delay_car();
**********************************************************************************************************************/
void Delay_car();
/**
 * @brief ����PID�����
 *
 * @param _pid  PID�����ṹ��ָ��
 * @return float PID������
 */
float PIDCTRL_CalcPIDGain(pidCtrl_t *_pid);
/**
 * @brief ����PIDƫ���֪ƫ����
 *
 * @param _pid  PID�����ṹ��ָ��
 * @param _err  ƫ��
 */
void PIDCTRL_ErrUpdate(pidCtrl_t *_pid, float _err);
/**
 * @brief ����������
 *
 * @param _pid  PID�����ṹ��ָ��
 * @return float ����������
 */
float PIDCTRL_CalcPGain(pidCtrl_t *_pid);

/**
 * @brief ����������
 *
 * @param _pid  PID�����ṹ��ָ��
 * @return float ���ֽ�����
 */
float PIDCTRL_CalcIGain(pidCtrl_t *_pid);

/**
 * @brief ����΢�����
 *
 * @param _pid  PID�����ṹ��ָ��
 * @return float ΢�ֽ�����
 */
float PIDCTRL_CalcDGain(pidCtrl_t *_pid);


#endif /* SOURCE_TEAM_CTR_H_ */
