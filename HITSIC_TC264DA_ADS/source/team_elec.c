/*
 * team_elec.c
 *
 *  Created on: 2021年2月26日
 *      Author: Administrator
 */


/*
 * Electric.cpp
 *
 *  Created on: 2021年2月23日
 *      Author: Administrator
 */


#include "team_elec.h"

int ADC[8];//两个AD通道读取电感值
int LV_Temp[2][SampleTimes];//电感处理函数
float LV[2]={0,0};//数组
float AD[2]={0,0};//保存滤波后数据数组

void LV_Sample(void)                             // ad采集函数
{
    ADC[1]=SCADC_Sample(ADC0,0,12);
    ADC[7]=SCADC_Sample(ADC0,0,18);

  for(int i=0 ; i < SampleTimes; i++)
  {
    /*获取采样初值*/
    LV_Temp[0][i]=(int)SCADC_Sample(ADC0,0,12);//左电感
    LV_Temp[1][i]=(int)SCADC_Sample(ADC0,0,18);//右电感

  }
}

void LV_Get_Val(void)//约0.3mS                  //对采集的值滤波
{
 // 有时会在0-65535(255)间跳动
  for(int i=0;i<2;i++)
  {
    for(int j=0; j < SampleTimes;j++)
    {
         if(LV_Temp[i][j]>240)//剔除毛刺信号
         {
             LV_Temp[i][j] = 240;
         }
    }
  }
}

void LV_Sort(void)
{
    for(int k=0;k<2;k++)
     {
       for(int i=0;i < SampleTimes-1;i++)
       {
         for(int j=i+1;j < SampleTimes;j++)
         {
             if(LV_Temp[k][i]>LV_Temp[k][j])
               Swap(&LV_Temp[k][i],&LV_Temp[k][j]);//交换，swap函数自己写
         }
       }
     }
}

void Swap(int*a,int*b)
{
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;

}
void Normalized(void)//归一化函数加入车无法运行
{
    for(int i=0;i<2;i++)
    {
        int max = LV_Temp[i][SampleTimes-1];
        int min = LV_Temp[i][0];
        for(int j=0; j < SampleTimes;j++)
        {
            int thisdata = LV_Temp[i][j];
            LV_Temp[i][j] = (((thisdata-min)/(max - min))*100U);
        }
    }

}
float *LV_average(void)
{
    for(int k=0;k<2;k++)
     {
       LV[k]=0;
       for(int i=3;i<SampleTimes-3;i++)
       {
            LV[k]+=(float)LV_Temp[k][i];
       }
       LV[k]=LV[k]/(SampleTimes-6);
       if( LV[k] < MinLVGot )
       {
          LV[k] = MinLVGot;
       }
     }
    for(int j = 0; j<2 ;j++)
    {
        AD[j] = LV[j];
    }
    return AD;

}
float Get_erro(void)
{
    LV_Sample();
    LV_Get_Val();
    LV_Sort();
    //Normalized();
    float *p;
    p = LV_average();
    return (p[0]-p[1])/(p[1]*p[0]);
}
