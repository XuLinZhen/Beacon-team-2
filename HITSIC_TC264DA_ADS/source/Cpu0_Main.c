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
#include "SmartCar_PIT.h"
#include "common.h"

#include "team_ctr.h"
#include "team_elec.h"
#include "image.h"
#include "my_math.h"
#include "menu.h"
#include "SmartCar_ADC.h"

#pragma section all "cpu0_dsram"

//IfxCpu_syncEvent g_cpuSyncEvent;
int32 Item_ID = 1;
Car_data CAR[Max_Item_Amount];
uint8 *buff;
uint8 Error;
float ssss[2]={0};
float time=0;
int mode_flag = 0;//状态切换标志位变量
int *p_mflag = NULL;//状态切换指针
int prem_flag = 0;//状态切换标志位变量2，previous标志位

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
    /** 编码器初始化 */
    SmartCar_Encoder_Init(GPT12_T2, IfxGpt120_T2INB_P33_7_IN, IfxGpt120_T2EUDB_P33_6_IN);
    SmartCar_Encoder_Init(GPT12_T6, IfxGpt120_T6INA_P20_3_IN, IfxGpt120_T6EUDA_P20_0_IN);
    /** PWM初始化 */
    //电机
    SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_0_TOUT53_P21_2_OUT, 20000, 0);
    SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_1_TOUT54_P21_3_OUT, 20000, 0);
    SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_2_TOUT55_P21_4_OUT, 20000, 0);
    SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_3_TOUT56_P21_5_OUT, 20000, 0);
    //舵机
    SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM1_1_TOUT31_P33_9_OUT, 50, 0);
    //SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_1_TOUT31_P33_9_OUT, 50, 0);
    /** 定时中断初始化 */
    Pit_Init(CCU6_0,PIT_CH0,5*1000);  //电机
    //Pit_Init(CCU6_0,PIT_CH1,30*1000);  //待定
    Pit_Init(CCU6_1,PIT_CH0,20*1000);  //状态切换
    Pit_Init(CCU6_1,PIT_CH1,20*1000);  //舵机
    /** 初始化OLED屏幕  */
    SmartCar_Oled_Init();
    extern const uint8 DISP_image_100thAnniversary[8][128];
    SmartCar_Buffer_Upload((uint8*) DISP_image_100thAnniversary);
    /** ADC */
    ADC_Init(ADC_2, ADC2_CH11_A45);
    ADC_Init(ADC_2, ADC2_CH12_A46);
    /** 初始化摄像头 */
    // SmartCar_MT9V034_Init();
    /** 初始化串口 */
    SmartCar_Uart_Init(IfxAsclin0_TX_P14_0_OUT,IfxAsclin0_RXA_P14_1_IN,921600,0);
    /** 初始化菜单 */
    MenuItem_t* MenuRoot = MenuCreate();
    MenuItem_t *currItem = MenuRoot->Child_list;
    /*初始化标志位*/
    delay_runcar = 0;//延迟发车标志位
    banmaxian_flag = 0;//斑马线识别标志位
    /** 初始化结束，开启总中断 */
    IfxCpu_enableInterrupts();
    //初始化外设
    Date_Read(0);
    CAR[0].dataint++; //启动次数计数器
    ctrl_pwm.kp=CAR[3].datafloat;
    ctrl_pwm.ki=CAR[4].datafloat;
    c_data[0].Motorspeed[0]=CAR[17].datafloat;
    mora_flag=CAR[5].datafloat;
    c_data[0].Kp=CAR[8].datafloat;
    c_data[0].Kd=CAR[9].datafloat;
    c_data[0].servo_mid=CAR[10].datafloat;
    threshold=CAR[13].dataint;
    c_data[1].Motorspeed[0]=CAR[18].datafloat;
while(1)
{
    switch(mode_flag)//菜单模式
        {
        case 0x00:
        {

            MenuPrint(MenuRoot, currItem);                  //构建菜单并打印
            //当标志位为0时:
            delay_runcar = 0;  //延迟发车标志位置为0
            while(1)
            {
                //SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_0_TOUT53_P21_2_OUT, 4000);
                //SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_1_TOUT54_P21_3_OUT, 3000);
                //SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_2_TOUT55_P21_4_OUT, 2000);
                //SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_3_TOUT56_P21_5_OUT, 3000);
                //SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM1_1_TOUT31_P33_9_OUT, 751);//680right 820left
                /*ssss[0]+=0.1;
                ssss[1]=ADC_Get(ADC_2, ADC2_CH11_A45, ADC_12BIT);
                ssss[2]=ADC_Get(ADC_2, ADC2_CH12_A46, ADC_12BIT);
                ssss[3]=SmartCar_Encoder_Get(GPT12_T2);
                ssss[4]=SmartCar_Encoder_Get(GPT12_T6);
                SmartCar_VarUpload(ssss,5);*/
                currItem = ButtonProcess(GetRoot(currItem), currItem);
                //servo_init(&(c_data[0].servo_pwm));//舵机初始化
                //Motorsp_Init();    //电机速度初始化
                ssss[0]+=0.001;
                if((1+sin(ssss[0]))/2>0.5)
                {
                    c_data[1].Motorspeed[0]=70;
                }
                else
                    c_data[1].Motorspeed[0]=20;
                SmartCar_VarUpload(&wifidata[0],12);//WiFi上传数据
                //如果标志位发生改变则打断循环
                if(mode_flag != 0x00) break;

            }
        }
        break;
        case 0x01://模式待定
        {
          while(1)
          {
              SmartCar_Show_IMG((uint8*) mt9v034_image, 120, 188);
              SmartCar_OLED_Printf6x8(95, 0, "%3.3f",time);
              //如果标志位发生改变则打断循环
              if(mode_flag != 0x01) break;
          }
        }
        break;
        case 0x02://摄像头跑车模式
        {
            //pitMgr_t *p;//测试删除定时器中断
            SmartCar_OLED_Fill(0);
            SmartCar_MT9V034_Init();
            Motorsp_Init();//电机速度初始化
            float ser=6.8;
            servo_init(&(ser));//舵机初始化
            //servo_init(&(c_data[0].servo_pwm));//舵机初始化
            delay_runcar = 0;   //延时发车标志位置0
            //p = pitMgr_t::insert(5000U, 1U, Delay_car, pitMgr_t::enable);//延时发车，测试删除定时器中断
            while(1)
               {
                Systick_Start(STM0);
               //if(delay_runcar==1) pitMgr_t::remove(*p);//测试不再延迟发车，清除定时器中断
               prem_flag = mode_flag;
               //摄像头跑车程序内容
               while (!mt9v034_finish_flag){}
               mt9v034_finish_flag = 0;
               THRE();
               image_main();
               servo_pid();
               Speed_radio((c_data[0].servo_pwm-c_data[0].servo_mid));
               //SmartCar_Show_IMG((uint8*) mt9v034_image, 120, 188);
               /* 传图 */
               //SmartCar_ImgUpload((uint8*) mt9v034_image, 120, 188);
               /********/
               time=GetTime_ms(STM0);
               SmartCar_VarUpload(&wifidata[0],12);//WiFi上传数据
               if(mode_flag != 0x02) break;
               }
            banmaxian_flag = 0;//斑马线识别标志位

        }break;
        case 0x03://电磁跑车模式
        {
            delay_runcar = 0;//延迟发车标志位
        while(1)
          {
            prem_flag = mode_flag;
            elec_runcar();
            SmartCar_OLED_Printf6x8(30,5,"%c","elecmode");
            if(mode_flag != 0x03) break;
          }
        }break;
        default:
         break;//其他模式，待定
        }//Switch结束
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
/*IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套
    servo();
    PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);
}*/
//状态切换
IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套
    mode_switch();
    PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);
}
//待定
IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
    enableInterrupts();//开启中断嵌套
    servo();
    PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);

}
void elec_runcar(void)//电磁跑车函数
{
    servo_pid();
}
void mode_switch(void)//模式切换中断回调函数
{
    if(GPIO_Read(P33, 11) == 1 && GPIO_Read(P33, 10) == 1)
    {
        //(*p_mflag) |= 0x01;
        mode_flag=0;
    }
    else if(GPIO_Read(P33, 11) != 1 && GPIO_Read(P33, 10) == 1)
    {
        //(*p_mflag) &= 0xfe;
        mode_flag=1;
    }
    else if(GPIO_Read(P33, 11) == 1 && GPIO_Read(P33, 10) != 1)
    {
        //(*p_mflag) |= 0x02;
        mode_flag=2;
    }
    else if(GPIO_Read(P33, 11) != 1 && GPIO_Read(P33, 10) != 1)
    {
        //(*p_mflag) &= 0xfd;
        mode_flag=3;
    }
    //(GPIO_Read(P33, 12) == 0)? ((*p_mflag) |= 0x01):((*p_mflag) &= 0xfe);
    //(GPIO_Read(P33, 13) == 0)? ((*p_mflag) |= 0x02):((*p_mflag) &= 0xfd);
    //(GPIO_PinRead(GPIOA,13) == 0)? ((*p_mflag) |= 0x04):((*p_mflag) &= 0xfb);
    //(GPIO_PinRead(GPIOA,15) == 0)? ((*p_mflag) |= 0x08):((*p_mflag) &= 0xf7);
}
MenuItem_t *ItemCreate(char* Item_name, itemType Item_Type, int32 data_min, int32 data_max)
{
    MenuItem_t* pItem = (MenuItem_t*)malloc(sizeof(MenuItem_t));  //开内存，创建一个新的菜单项结构体 pItem
    pItem->Item_type = Item_Type;            //为新建立的菜单结构体 类型赋值
    strncpy(pItem->Item_name, Item_name, name_size);  //名称赋值
    pItem->Item_name[name_size - 1] = '\0';    //在数组末尾加0

    if (Item_ID < Max_Item_Amount)
    {
        pItem->ID = Item_ID;            //从1开始，0是启动次数计数器
        Item_ID++;
    }
    pItem->data_range[min] = data_min;
    pItem->data_range[max] = data_max;
    pItem->Item_data = &CAR[Item_ID-1];

    pItem->list_ID = 0;         //主菜单头节点是0
    pItem->Pre_item = NULL;
    pItem->Next_item = NULL;
    pItem->Child_list = NULL;
    return pItem;
}
void MenuItem_Insert(MenuItem_t* Menu, MenuItem_t* pItem)
{
    if (Menu->Child_list == NULL)  //当当前menu的子菜单为空时，创立新的子菜单
    {
        Menu->Child_list = pItem;
        pItem->list_ID = 1;
        pItem->Pre_item = Menu;
        Menu->Item_data->dataint = 1;
    }
    else     //当当前menu的子菜单不为空时，向下找到最后一项
    {
        MenuItem_t* pctrl = Menu->Child_list;
        while(pctrl->Next_item != NULL)
        {
            pctrl = pctrl->Next_item;
        }
        pctrl->Next_item = pItem;
        pItem->Pre_item = pctrl;
        pItem->list_ID = pctrl->list_ID + 1;
        Menu->Item_data->dataint++;
    }
}
MenuItem_t *MenuCreate(void)
{

    MenuItem_t* MenuRoot = ItemCreate("Beacon team 2", listType, 1, 20);   //menu为菜单项类型

    //MenuItem_t* MenuRoot = ItemCreate("Main Menu", listType, 1, 20);   //menu为菜单项类型
    MenuItem_t* Motor = ItemCreate("Motor", listType, 0, 10);
    {
        MenuItem_t* Motor_Kp = ItemCreate("Motor_Kp", floatType, 0, 100);
        Motor_Kp->Item_data->datafloat=c_data[0].M_Kp;
        MenuItem_t* Motor_Ki = ItemCreate("Motor_Ki", floatType, 0, 100);
        Motor_Ki->Item_data->datafloat=c_data[0].M_Ki;
        MenuItem_t* Mora_flag = ItemCreate("Mora_flag", floatType, 0, 100);
        Mora_flag->Item_data->datafloat=mora_flag;

        MenuItem_Insert(Motor, ItemCreate("Back", listType, 1, 20));
        MenuItem_Insert(Motor, Motor_Kp);
        MenuItem_Insert(Motor, Motor_Ki);
        MenuItem_Insert(Motor, Mora_flag);
    }
    MenuItem_t* Servo = ItemCreate("Servo", listType, 0, 10);
    {

        MenuItem_t* Servo_Kp = ItemCreate("Servo_Kp", floatType, 0, 100);
        Servo_Kp->Item_data->datafloat=c_data[0].Kp;
        MenuItem_t* Servo_Kd = ItemCreate("Servo_Kd", floatType, 0, 100);
        Servo_Kd->Item_data->datafloat=c_data[0].Kd;
        MenuItem_t* Servo_Mid = ItemCreate("Servo_Mid", floatType, 0, 20);
        Servo_Mid->Item_data->datafloat=c_data[0].servo_mid;

        MenuItem_Insert(Servo, ItemCreate("Back", listType, 1, 20));
        MenuItem_Insert(Servo, Servo_Kp);
        MenuItem_Insert(Servo, Servo_Kd);
        MenuItem_Insert(Servo, Servo_Mid);
    }
    MenuItem_t* Camera = ItemCreate("Camera", listType, 0, 10);
    {
        MenuItem_t* Threshold = ItemCreate("Threshold", intType, 0, 255);
        Threshold->Item_data->dataint=threshold;

        MenuItem_Insert(Camera, ItemCreate("Back", listType, 1, 20));
        MenuItem_Insert(Camera, Threshold);
    }
    MenuItem_t* SAVE = ItemCreate("SAVE", listType, 0, 20);
    {
        MenuItem_Insert(SAVE, ItemCreate("Back", listType, 1, 20));
    }
    MenuItem_t* Motor_Speed_zx = ItemCreate("M_Speed_zx", floatType, 0, 100);
    MenuItem_t* Motor_Speed_qd = ItemCreate("M_Speed_qd", floatType, 0, 100);
    Motor_Speed_zx->Item_data->datafloat=c_data[0].Motorspeed[0];
    Motor_Speed_qd->Item_data->datafloat=c_data[1].Motorspeed[0];
    MenuItem_Insert(MenuRoot, ItemCreate("*******", listType, 0, 20));
    MenuItem_Insert(MenuRoot, Motor);
    MenuItem_Insert(MenuRoot, Servo);
    MenuItem_Insert(MenuRoot, Camera);
    MenuItem_Insert(MenuRoot, Motor_Speed_zx);
    MenuItem_Insert(MenuRoot, Motor_Speed_qd);
    MenuItem_Insert(MenuRoot, SAVE);
    return MenuRoot;
}
/**
 * @ 显示效果:
 * @
 * @ 菜单项名称   启动次数   当前项编号/菜单总项数
 * @ -----------------------------
 * @ （除主菜单以外）[Back]
 * @  [菜单类型项]
 * @  普通数据项            数据
 * @  ......
 */
void MenuPrint(MenuItem_t *Menu, MenuItem_t *currItem)  //再加一项当前指针
{
    SmartCar_OLED_Fill(0);
    int x = 0, y = 2;   //菜单项在y = 2开始
    SmartCar_OLED_Printf6x8(0, 1,"---------------------");
    SmartCar_OLED_P6x8Str(0, 0, Menu->Item_name);//"%s",
    SmartCar_OLED_Printf6x8(100, 0, "%d",currItem->list_ID);//"%d" ,
    SmartCar_OLED_P6x8Str(110, 0, "/");
    SmartCar_OLED_Printf6x8(120, 0, "%d" , Menu->Item_data->dataint);
    int start_print_ID;
    MenuItem_t *pctrl = Menu->Child_list;
    if(currItem->list_ID <= 6)
    {
        start_print_ID=1;
    }
    else
    {
        start_print_ID=currItem->list_ID - 5;
    }
    //start_print_ID = currItem->list_ID <= 6? 1:currItem->list_ID - 5;   //滚动式菜单，
    while (pctrl->list_ID != start_print_ID)        //从哪一项开始打印，需要改，光标移到最后再往上移有问题。
    {
        pctrl = pctrl->Next_item;
    }
    while (pctrl != NULL && y <= 7)
    {
        if (pctrl->Item_type == listType)
            SmartCar_OLED_P6x8Str(6, y, pctrl->Item_name);
        else if (pctrl->Item_type == intType)
        {
            SmartCar_OLED_P6x8Str(6, y, pctrl->Item_name);
            SmartCar_OLED_Printf6x8(66, y,"%d", pctrl->Item_data->dataint);
        }
        else if (pctrl->Item_type == floatType)
        {
            SmartCar_OLED_P6x8Str(6, y, pctrl->Item_name);
            SmartCar_OLED_Printf6x8(66, y,"%3.4f", pctrl->Item_data->datafloat);
        }
        y++;
        pctrl = pctrl->Next_item;
    }
    if(currItem->list_ID + 1 >= 7)
    {
        SmartCar_OLED_Printf6x8(0, 7,">");
    }
    else
    {
        SmartCar_OLED_Printf6x8(0, currItem->list_ID + 1,">");
    }
}
int ButtonRead(void)
{
    int button_operation = 0;
    if (!GPIO_Read(P23,1))
    {
        button_operation = up;
        Delay_ms(STM0, 250);
    }
    if (!GPIO_Read(P22,1))
    {
        button_operation = down;
        Delay_ms(STM0, 250);
    }
    if (!GPIO_Read(P22,2))
    {
        button_operation = left;
        Delay_ms(STM0, 250);
    }
    if (!GPIO_Read(P22,3))
    {
        button_operation = right;
        Delay_ms(STM0, 250);
    }
    if (!GPIO_Read(P22,0))
    {
        button_operation = OK;
        Delay_ms(STM0, 250);
    }
    return button_operation;
}
MenuItem_t *ButtonProcess(MenuItem_t *Menu, MenuItem_t* currItem)
{
    int button_order = ButtonRead();
    switch (button_order)
    {
        case up:
            currItem = CursorMove_up(currItem);
            MenuPrint(Menu, currItem);
            break;
        case down:
            currItem = CursorMove_down(currItem);
            MenuPrint(Menu, currItem);
            break;
        case OK:

            if  (currItem->list_ID==7)
            {
                /*da[0]=c_data[0].M_Kp;
                da[1]=c_data[0].M_Ki;
                da[2]=c_data[0].Motorspeed[0];
                da[3]=mora_flag;
                da[4]=c_data[0].Kp;
                da[5]=c_data[0].Kd;
                da[6]=c_data[0].servo_mid;
                da[7]=threshold;*/
                //memcpy(&buff[0], CAR, sizeof(Car_data) * Max_Item_Amount);
                Date_Write(0);
                MenuPrint(Menu, currItem);
                ctrl_pwm.kp=CAR[3].datafloat;
                ctrl_pwm.ki=CAR[4].datafloat;
                c_data[0].Motorspeed[0]=CAR[17].datafloat;
                mora_flag=CAR[5].datafloat;
                c_data[0].Kp=CAR[8].datafloat;
                c_data[0].Kd=CAR[9].datafloat;
                c_data[0].servo_mid=CAR[10].datafloat;
                threshold=CAR[13].dataint;
                c_data[1].Motorspeed[0]=CAR[18].datafloat;

            }
            else if (currItem->Item_type == listType)
                currItem = IntoMenu(currItem);
            else
            {
                currItem = DataModify(currItem);
                MenuPrint(Menu, currItem);
            }
            break;
        default:
            break;
    }
    return currItem;
}
MenuItem_t *CursorMove_down(MenuItem_t* currItem)
{
    if (currItem->Next_item != NULL)
    {
        currItem = currItem->Next_item;
    }
    return currItem;
}
MenuItem_t *CursorMove_up(MenuItem_t* currItem)
{
    if (currItem->list_ID > 1)
    {
        currItem = currItem->Pre_item;
    }
    return currItem;
}
MenuItem_t *IntoMenu(MenuItem_t *currItem)
{
    if (currItem->list_ID == 1)     //[Back]
    {
        currItem = currItem->Pre_item;
        MenuPrint(GetRoot(currItem), currItem);
    }
    else
    {
        MenuPrint(currItem, currItem->Child_list);
        currItem = currItem->Child_list;
    }
    return currItem;
}
MenuItem_t *GetRoot(MenuItem_t *currItem)       //获取当前操作的菜单项所属的菜单
{
    MenuItem_t *pctrl = currItem;
    if (pctrl->list_ID == 0)
        return pctrl;
    while(pctrl->list_ID > 1)
    {
        pctrl = pctrl->Pre_item;
    }
    return pctrl->Pre_item;
}
/**
 * @ 显示效果:
 * @
 * @ 菜单项名称       菜单项数据的范围
 * @ -----------------------------
 * @
 * @        1 2 3 4 （e-2）
 * @        ^
 * @ （特殊项）相关参数实时显示
 * @ （特殊项）相关参数实时显示
 * @  [ O K ]     >[C a n c e l]
 */
void ItemPrint(MenuItem_t *currItem, int32 pos, int32 *data_array, int32 length)
{
    int flag=0;
    SmartCar_OLED_Fill(0);
    int max_digit = length;//sizeof(data_array) / sizeof(int32_t);

    SmartCar_OLED_P6x8Str(10, 0, currItem->Item_name);//"%s",
    SmartCar_OLED_Printf6x8(70, 0, "[");
    SmartCar_OLED_Printf6x8(80, 0, "%d" ,currItem->data_range[min]);
    SmartCar_OLED_Printf6x8(90, 0, ",");
    SmartCar_OLED_Printf6x8(100, 0, "%d" , currItem->data_range[max]);
    SmartCar_OLED_Printf6x8(120, 0, "]");
    //SmartCar_OLED_Printf6x8(0, 0,"  %s   [%d,%d]", currItem->Item_name, currItem->data_range[min], currItem->data_range[max]);

    SmartCar_OLED_Printf6x8(0, 1,"---------------------");

    int i;
    for(i = 0; i < max_digit; i++)
    {
        //显示各个数位
        if (currItem->Item_type == floatType)
        {
            if(i==(max_digit-4))
            {
                SmartCar_OLED_Printf6x8(42 + i*6, 3, ".");
                SmartCar_OLED_Printf6x8(42 + (i+1)*6, 3, "%d", data_array[i]);
                flag=1;
            }
            else
            {
                if(flag==1)
                {
                    SmartCar_OLED_Printf6x8(42 + (i+1)*6, 3, "%d", data_array[i]);
                }
                else
                {
                    SmartCar_OLED_Printf6x8(42 + i*6, 3, "%d", data_array[i]);
                }
            }
        }
        else if(currItem->Item_type == intType)
        {
            SmartCar_OLED_Printf6x8(42 + i*6, 3, "%d", data_array[i]);     //显示各个数位
        }
    }
    SmartCar_OLED_Printf6x8(80, 7, "[OK]");
    SmartCar_OLED_Printf6x8(12, 7, "[Cancel]");
    if  (pos == max_digit + 1)
    {
        SmartCar_OLED_Printf6x8(6, 7, ">");
    }
    else if (pos == max_digit + 2)
    {
        SmartCar_OLED_Printf6x8(74, 7, ">");
    }
    else
    {
        if (pos <= (max_digit-4))
           {
               SmartCar_OLED_Printf6x8(42 + (pos-1)*6, 4, "^");
           }
           else if (pos > (max_digit-4))
           {
               SmartCar_OLED_Printf6x8(42 + (pos)*6, 4, "^");
           }
        //SmartCar_OLED_Printf6x8(42 + (pos-1)*6, 4, "^");
    }
    int Item_dataint = ArrayToDataint(data_array, max_digit);
    /*switch (currItem->ID)
    {
        case Kp1:
        {
            float Item_datafloat = ((float)Item_dataint) / 100.0;
            DISP_SSD1306_Printf_F6x8(6, 5,"Ki1=%6.4f", Item_datafloat / (float)CAR[Ti1].dataint);
            DISP_SSD1306_Printf_F6x8(6, 6,"Kd1=%6.1f", Item_datafloat * (float)CAR[Td1].dataint);
            break;
        }
        case Ti1:
        {
            DISP_SSD1306_Printf_F6x8(6, 5,"Ki1=%6.4f", CAR[Kp1].datafloat / (float)Item_dataint);
            break;
        }
        case Td1:
        {
            DISP_SSD1306_Printf_F6x8(6, 6,"Kd1=%6.1f", CAR[Kp1].datafloat * (float)Item_dataint);
            break;
        }
        default:
            break;
    }*/
}
MenuItem_t *DataModify(MenuItem_t *currItem)
{
    int max_digit, i;
    if(currItem->Item_type == intType)
    {
        max_digit=0;
    }
    else
    {
        max_digit=4;
    }
    //max_digit = (currItem->Item_type == intType) ? 0 : 4;   //所有浮点型均为四位小数
    int data_max = currItem->data_range[max];
    while(data_max != 0)
    {
        data_max /= 10;
        max_digit++;
    }                       //获得最大数位

    int data_array[max_digit];
    int Item_dataint=0;
    if(currItem->Item_type == intType)
    {
        Item_dataint = currItem->Item_data->dataint;
    }
    else
    {
        Item_dataint = floor(currItem->Item_data->datafloat * 10000);
    }
    //int Item_dataint = (currItem->Item_type == intType) ? currItem->Item_data->dataint : floor(currItem->Item_data->datafloat * 10000);
    for(i = 0; i < max_digit; i++)
    {
        data_array[max_digit - 1 - i] = Item_dataint % 10;//((i+1)*10);
        Item_dataint /= 10;
    }
    ItemPrint(currItem, 1, data_array, max_digit);
    int pos = 1;        //pos:光标位置
    while(1)
    {
        int flag_return = 0;
        int button_order = ButtonRead();
        switch(button_order)
        {
            case left:          //光标左移
                if(pos > 1)
                {
                    pos--;
                    ItemPrint(currItem, pos, data_array, max_digit);
                }
                break;
            case right:
                if(pos < max_digit + 2)
                {
                    pos++;
                    ItemPrint(currItem, pos, data_array, max_digit);
                }
                break;
            case up:            //光标指向的数位+1
                if(pos <= max_digit && data_array[pos-1] < 9)
                {
                    data_array[pos-1]++;
                    ItemPrint(currItem, pos, data_array, max_digit);
                }
                break;
            case down:
                if(pos >= 1 && data_array[pos-1] > 0)
                {
                    data_array[pos-1]--;
                    ItemPrint(currItem, pos, data_array, max_digit);
                }
                break;
            case OK:
                if (pos == max_digit + 2)       //[OK]
                {
                    Item_dataint = ArrayToDataint(data_array, max_digit);
                    if (DataCheck(currItem, Item_dataint))
                    {
                        if (currItem->Item_type == intType)
                            currItem->Item_data->dataint = Item_dataint;
                        else  currItem->Item_data->datafloat = (float)Item_dataint / 10000.0;
                    }
                    flag_return = 1;
                    break;
                }
                if (pos == max_digit + 1)           //[cancel]，返回上一级菜单
                {
                    flag_return = 1;
                }
                break;
            default:
                break;
        }
        if (flag_return) break;
    }
    return currItem;
}
int32 DataCheck(MenuItem_t *currItem, int32 Item_dataint)
{
    if (currItem->Item_type == intType)
    {
        return ((Item_dataint <= currItem->data_range[max]) && (Item_dataint >= currItem->data_range[min]));
    }
    else if (currItem->Item_type == floatType)
    {
        float Item_datafloat = ((float)Item_dataint) / 10000.0;
        return ((Item_datafloat <= currItem->data_range[max]) && (Item_datafloat >= currItem->data_range[min]));
        //return ( (currItem->data_range[max] - Item_datafloat) > 1e-6 && (Item_datafloat - currItem->data_range[min]) > 1e-6 );
    }
}
int32 ArrayToDataint(int32 *data_array, int32 length)
{
    int Item_dataint = 0;
    int max_digit = length;
    for (int i = 0; i < max_digit; i++)
    {
        Item_dataint *= 10;
        Item_dataint += data_array[i];
    }
    return Item_dataint;
}
void Date_Read(uint32 sector_num)
{
    CAR[3].datafloat=Page_Read(sector_num,0,float);
    CAR[4].datafloat=Page_Read(sector_num,1,float);
    CAR[17].datafloat=Page_Read(sector_num,2,float);
    CAR[5].datafloat=Page_Read(sector_num,3,float);
    CAR[8].datafloat=Page_Read(sector_num,4,float);
    CAR[9].datafloat=Page_Read(sector_num,5,float);
    CAR[10].datafloat=Page_Read(sector_num,6,float);
    CAR[13].dataint=Page_Read(sector_num,7,int);
    CAR[18].datafloat=Page_Read(sector_num,8,float);
}
void Date_Write(uint32 sector_num)
{
    Sector_Erase(sector_num);
    uint32 fla[9];
    fla[0]=float_conversion_uint32(CAR[3].datafloat);
    fla[1]=float_conversion_uint32(CAR[4].datafloat);
    fla[2]=float_conversion_uint32(CAR[17].datafloat);
    fla[3]=float_conversion_uint32(CAR[5].datafloat);
    fla[4]=float_conversion_uint32(CAR[8].datafloat);
    fla[5]=float_conversion_uint32(CAR[9].datafloat);
    fla[6]=float_conversion_uint32(CAR[10].datafloat);
    fla[7]=float_conversion_uint32(CAR[13].dataint);
    fla[8]=float_conversion_uint32(CAR[18].datafloat);
    Sector_Program(sector_num,fla);
}


#pragma section all restore
