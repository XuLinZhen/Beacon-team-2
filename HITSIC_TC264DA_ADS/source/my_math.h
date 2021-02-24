/*
 * my_math.h
 *
 *  Created on: 2021年2月23日
 *      Author: Administrator
 */

#ifndef SOURCE_MY_MATH_H_
#define SOURCE_MY_MATH_H_

int my_int_abs(int);
float my_float_abs(float);
int my_max(int, int);
int my_min(int, int);
float my_pow(int, int);
float my_arctan(float);
int two_point_distance2(int, int, int, int);
int distance_LIGHT_true(int x,int y);  //实际距离计算函数
int distance_LIGHT_ideal_right(int x,int y);
int distance_LIGHT_ideal_left(int x,int y);//理想距离计算函数
int sum_array(int a[],int num);



#endif /* SOURCE_MY_MATH_H_ */
