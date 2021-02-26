/*
 * image.h
 *
 *  Created on: 2021年2月23日
 *      Author: Administrator
 */

#ifndef SOURCE_IMAGE_H_
#define SOURCE_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//#include "highgui.h"
#include <math.h>
//#include "image.h"

//#define MISS 94
#define CAMERA_H  120                            //图片高度
#define CAMERA_W  188                            //图片宽度
#define FAR_LINE 1//图像处理上边界
#define NEAR_LINE 113//图像处理下边界
#define LEFT_SIDE 0//图像处理左边界
#define RIGHT_SIDE 187//图像处理右边界
#define MISS 94
#define white_num_MAX 10//每行最多允许白条数

/////////////////////////////
#define black 0x00
#define white 0x01
#define blue  0x02
#define green 0x03
#define red   0x04
#define gray  0x05
#define purple 0x06
///////////////////////////

extern int8 IMG[CAMERA_H][CAMERA_W];//二值化后图像数组
extern int8 image_Buffer_0[CAMERA_H][CAMERA_W];
extern uint8* camera_buffer_addr;//指向灰度图的首地址
extern int threshold;
extern int foresight;
extern int8 banmaxian_flag;
extern int8 out_flag;
extern int zebra;

void head_clear(void);
void THRE(void);
int find_f(int a);
void search_white_range();
void find_all_connect();
void find_road();
uint8 find_continue(int8 i_start, int8 j_start);
void ordinary_two_line(void);
void image_main();
void get_mid_line(void);
float get_error(void);

void my_memset(int8* ptr, int8 num, int8 size);

void search_rightup_point();
void  search_leftup_point();
void search_rightdown_point();
void search_leftdown_point();
void connect_line_plan();
void find_cross();
void banmaxian(int zebra);
void ckeck_out_road();
//信标
void find_light();
extern int flag;



#endif /* SOURCE_IMAGE_H_ */
