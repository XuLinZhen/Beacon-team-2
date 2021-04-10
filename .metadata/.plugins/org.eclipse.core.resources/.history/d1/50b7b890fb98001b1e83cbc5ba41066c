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
//#include "cv.h"
//#include "highgui.h"
#include <math.h>
#include "common.h"
#include "SmartCar_GPIO.h"
#include "SmartCar_Systick.h"

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

extern uint8 IMG[CAMERA_H][CAMERA_W];//二值化后图像数组
extern uint8 image_Buffer_0[CAMERA_H][CAMERA_W];
extern uint8* camera_buffer_addr;//指向灰度图的首地址
extern int threshold;
extern int foresight;
extern uint8 banmaxian_flag;
extern uint8 out_flag;
extern int zebra;
extern uint8 centre_h;
extern uint8 centre_l;

void head_clear(void);
void THRE(void);
int find_f(int a);
void search_white_range();
void find_all_connect();
void find_road();
uint8 find_continue(uint8 i_start, uint8 j_start);
void ordinary_two_line(void);
void image_main();
void get_mid_line(void);
float get_error(void);

void my_memset(uint8* ptr, uint8 num, uint8 size);


void banmaxian(int zebra);
void ckeck_out_road();
//信标
void find_light();
extern int flag;



#endif /* SOURCE_IMAGE_H_ */
