/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include <ifxCpu_Irq.h>
#include "IfxScuWdt.h"
#include "SmartCar_GPIO.h"
#include "SmartCar_Uart.h"
#include "SmartCar_Upload.h"
#include "SmartCar_Oled.h"
#include "SmartCar_Pwm.h"
#include "SmartCar_MPU.h"
#include "SmartCar_MT9V034.h"
#include "SmartCar_Systick.h"
#include "common.h"

#include "team_ctr.h"
#include "Electric.hpp"
#include "image.h"
#include "my_math.h"
#include "menu.h"



#pragma section all "cpu0_dsram"
//IfxCpu_syncEvent g_cpuSyncEvent;



int32 Item_ID = 1;
Car_data CAR[Max_Item_Amount];

int *buff;

//cam_zf9v034_configPacket_t cameraCfg;
//dmadvp_config_t dmadvpCfg;
//dmadvp_handle_t dmadvpHandle;
//disp_ssd1306_frameBuffer_t *dispBuffer;
//inv::i2cInterface_t imu_i2c(nullptr, IMU_INV_I2cRxBlocking, IMU_INV_I2cTxBlocking);
//inv::mpu6050_t imu_6050(imu_i2c);
int mode_flag = 0;//状态切换标志位变量
int *p_mflag = NULL;//状态切换指针
int prem_flag = 0;//状态切换标志位变量2，previous标志位

//void run_car(dmadvp_handle_t *dmadvpHandle,disp_ssd1306_frameBuffer_t *dispBuffer);//摄像头跑车函数
void elec_runcar(void);//电磁跑车函数
void mode_switch(void);//模式切换中断回调函数


int core0_main(void)
{
    /** 初始化阶段，关闭总中断 */
    IfxCpu_disableInterrupts();
    /** 初始化时钟 */
    get_clk();
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    /** GPIO初始化 */
    GPIO_Init(P22,0, PUSHPULL,1);
    GPIO_Init(P22,1, PUSHPULL,1);
    GPIO_Init(P22,2, PUSHPULL,1);
    GPIO_Init(P22,3, PUSHPULL,1);
    /** 定时中断初始化 */
    Pit_Init(CCU6_0,PIT_CH0,1000*1000);  //电机
    Pit_Init(CCU6_0,PIT_CH1,3000*1000);  //舵机
    Pit_Init(CCU6_1,PIT_CH0,7000*1000);  //状态切换
    //Pit_Init(CCU6_1,PIT_CH1,1000*1000);  //待定
    /** 初始化OLED屏幕 */
    SmartCar_Oled_Init();
    extern const uint8 DISP_image_100thAnniversary[8][128];
    SmartCar_Buffer_Upload((uint8*) DISP_image_100thAnniversary);
    /** 初始化菜单 */
    MenuItem_t* MenuRoot = MenuCreate();
    MenuItem_t *currItem = MenuRoot->Child_list;
    /*初始化标志位*/
    delay_runcar = 0;//延迟发车标志位
    banmaxian_flag = 0;//斑马线识别标志位
    /** 初始化结束，开启总中断 */
    IfxCpu_enableInterrupts();
    //初始化外设

    buff = (uint8 *)malloc(4096);
    Date_Read(0,8,buff);
    memcpy(CAR, &buff[0], sizeof(Car_data) * Max_Item_Amount);
    CAR[0].dataint++; //启动次数计数器

    c_data[0].M_Kp=CAR[3].datafloat;
    c_data[0].M_Ki=CAR[4].datafloat;
    c_data[0].Motorspeed[0]=CAR[17].datafloat;
    mora_flag=CAR[5].datafloat;
    c_data[0].Kp=CAR[8].datafloat;
    c_data[0].Kd=CAR[9].datafloat;
    c_data[0].servo_mid=CAR[10].datafloat;
    threshold=CAR[13].dataint;

while(TRUE)
{
    switch(mode_flag)//菜单模式
        {
        case 0x00:
        {
            MenuPrint(MenuRoot, currItem);                  //构建菜单并打印
            //当标志位为0时:
            delay_runcar = 0;  //延迟发车标志位置为0
            while(TRUE)
            {
                currItem = ButtonProcess(GetRoot(currItem), currItem);
                //prem_flag = mode_flag;
                servo_init(&(c_data[0].servo_pwm));//舵机初始化
                Motorsp_Init();    //电机速度初始化
                //if(prem_flag != mode_flag) break;  //如果标志位发生改变则打断循环
                if(mode_flag != 0x00) break;
            }
        }
        break;
        case 0x01://百年校庆图标模式
        {
          //MENU_Suspend();          //菜单挂起
          DISP_SSD1306_BufferUpload((uint8*) DISP_image_100thAnniversary);   //百年校庆图像显示
          while(TRUE)
          {
              prem_flag = mode_flag;
              SDK_DelayAtLeastUs(2000000,180*1000*1000);
              //if(prem_flag != mode_flag) break;     //如果标志位发生改变则打断循环
              if(mode_flag != 0x01) break;
          }
        }
        break;
        case 0x02://摄像头跑车模式
        {

            SmartCar_OLED_Fill(0);
            SmartCar_MT9V034_Init();

             Motorsp_Init();//电机速度初始化
             servo_init(&(c_data[0].servo_pwm));//舵机初始化
             delay_runcar = 0;   //延时发车标志位置0
             //p = pitMgr_t::insert(5000U, 1U, Delay_car, pitMgr_t::enable);//延时发车，测试删除定时器中断
             while(TRUE)
               {
               //if(delay_runcar==1) pitMgr_t::remove(*p);//测试不再延迟发车，清除定时器中断
               prem_flag = mode_flag;
               while (!mt9v034_finish_flag){}
               mt9v034_finish_flag = 0;
               THRE();
               image_main();
               servo_pid();
               Speed_radio((c_data[0].servo_pwm-c_data[0].servo_mid));
               SmartCar_Show_IMG((uint8*) mt9v034_image, 120, 188);
               //if(prem_flag != mode_flag) break;
               if(mode_flag != 0x02) break;
               }
              //banmaxian_flag = 0;//斑马线识别标志位

        }break;
        case 0x03://电磁跑车模式
                {
                    MENU_Suspend();
                    DISP_SSD1306_Fill(0);
                    SDK_DelayAtLeastUs(5000000,180*1000*1000);
                    delay_runcar = 0;//延迟发车标志位
                while(TRUE)
                 {
                    prem_flag = mode_flag;
                    elec_runcar();
                    SmartCar_OLED_Printf6x8(30,5,"%c","elecmode");
                    //if(prem_flag != mode_flag) break;
                    if(mode_flag != 0x03) break;
                  }
                }
                    break;
        default: break;//其他模式，待定
        }
        //TODO: 在这里添加车模保护代码
}//while结束

}//main结束


//中断服务函数
//电机
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套

    Motor_ctr();

    PIT_CLEAR_FLAG(CCU6_0, PIT_CH0);

}

//舵机
IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套

    servo();

    PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);

}
//状态切换
IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套

    mode_switch();

    PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);

}
//待定
/*IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套
    PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);

}*/
/*void run_car(dmadvp_handle_t *dmadvpHandle,disp_ssd1306_frameBuffer_t *dispBuffer)
{

}*/
void elec_runcar(void)//电磁跑车函数
{
    servo_pid();
}
void mode_switch(void)//模式切换中断回调函数
{
    (GPIO_PinRead(P33, 12) == 0)? ((*p_mflag) |= 0x01):((*p_mflag) &= 0xfe);
    (GPIO_PinRead(P33, 13) == 0)? ((*p_mflag) |= 0x02):((*p_mflag) &= 0xfd);
    //(GPIO_PinRead(GPIOA,13) == 0)? ((*p_mflag) |= 0x04):((*p_mflag) &= 0xfb);
    //(GPIO_PinRead(GPIOA,15) == 0)? ((*p_mflag) |= 0x08):((*p_mflag) &= 0xf7);
}

#pragma section all restore
