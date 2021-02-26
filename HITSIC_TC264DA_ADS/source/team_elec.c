/*
 * team_elec.c
 *
 *  Created on: 2021��2��26��
 *      Author: Administrator
 */


/*
 * Electric.cpp
 *
 *  Created on: 2021��2��23��
 *      Author: Administrator
 */


#include "team_elec.h"

int ADC[8];//����ADͨ����ȡ���ֵ
int LV_Temp[2][SampleTimes];//��д�����
float LV[2]={0,0};//����
float AD[2]={0,0};//�����˲�����������

void LV_Sample(void)                             // ad�ɼ�����
{
    ADC[1]=SCADC_Sample(ADC0,0,12);
    ADC[7]=SCADC_Sample(ADC0,0,18);

  for(int i=0 ; i < SampleTimes; i++)
  {
    /*��ȡ������ֵ*/
    LV_Temp[0][i]=(int)SCADC_Sample(ADC0,0,12);//����
    LV_Temp[1][i]=(int)SCADC_Sample(ADC0,0,18);//�ҵ��

  }
}

void LV_Get_Val(void)//Լ0.3mS                  //�Բɼ���ֵ�˲�
{
 // ��ʱ����0-65535(255)������
  for(int i=0;i<2;i++)
  {
    for(int j=0; j < SampleTimes;j++)
    {
         if(LV_Temp[i][j]>240)//�޳�ë���ź�
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
               Swap(&LV_Temp[k][i],&LV_Temp[k][j]);//������swap�����Լ�д
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
void Normalized(void)//��һ���������복�޷�����
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
