/*
 * my_math.c
 *
 *  Created on: 2021��2��23��
 *      Author: Administrator
 */


#include "my_math.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#define PI 3.1415926

int my_int_abs(int input)
{
    if (input < 0)
        return (-input);
    else
        return input;
}

float my_float_abs(float input)
{
    if (input < 0)
        return (-input);
    else
        return input;
}

int my_max(int x1, int x2)
{
    if (x1 > x2)
        return x1;
    else
        return x2;
}

int my_min(int x1, int x2)
{
    if (x1 > x2)
        return x2;
    else
        return x1;
}

float my_pow(int  base, int power)
{
    float result = 1;
    if (power >= 2)
    {
        for (int i = 0; i < power; i++)
        {
            result = result * base;

        }
        return result;
    }
    else if(power == 1)
    {
        return base;
    }
    else if(power == 0)
    {
        return result;
    }
}

float my_arctan(float slope)
{
    float angel;
    if ((slope > -1) && (slope < 1))
    {
        angel = slope - my_pow(slope, 3) / 3 + my_pow(slope, 5) / 5 - my_pow(slope, 7) / 7 + my_pow(slope, 9) / 9;
    }

    else
    {
        slope = 1 / slope;
        angel = slope - my_pow(slope, 3) / 3 + my_pow(slope, 5) / 5 - my_pow(slope, 7) / 7 + my_pow(slope, 9) / 9;
        angel = PI / 2 - angel;
    }
    angel = 180*angel/ PI;
    return angel;
}

int two_point_distance2(int x1, int y1, int x2, int y2)
{
    int distance2 = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    return distance2;
}
int distance_LIGHT_true(int x,int y)
{
    int distance_true=sqrt((x-94)*(x-94)+y*y);
    return distance_true;
}
int distance_LIGHT_ideal_left(int x,int y)
{
    int distance_ideal_left=-1.2931*x+4.0588;
    return distance_ideal_left;
}
int distance_LIGHT_ideal_right(int x,int y)
{
    int distance_ideal_rihgt=1.2743*x+12.743;
}
int sum_array(int a[],int num)
{
    int s=0;
    for(int i=0;i<num;i++)
    {
        s+=a[i];
    }
    return s;
}


