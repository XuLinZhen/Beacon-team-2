/*
 * image.h
 *
 *  Created on: 2021��2��23��
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
#define CAMERA_H  120                            //ͼƬ�߶�
#define CAMERA_W  188                            //ͼƬ���
#define FAR_LINE 1//ͼ�����ϱ߽�
#define NEAR_LINE 113//ͼ�����±߽�
#define LEFT_SIDE 0//ͼ������߽�
#define RIGHT_SIDE 187//ͼ�����ұ߽�
#define MISS 94
#define white_num_MAX 10//ÿ��������������

/////////////////////////////
#define black 0x00
#define white 0x01
#define blue  0x02
#define green 0x03
#define red   0x04
#define gray  0x05
#define purple 0x06
///////////////////////////

extern uint8 IMG[CAMERA_H][CAMERA_W];//��ֵ����ͼ������
extern uint8 image_Buffer_0[CAMERA_H][CAMERA_W];
extern uint8* camera_buffer_addr;//ָ��Ҷ�ͼ���׵�ַ
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
//�ű�
void find_light();
extern int flag;



#endif /* SOURCE_IMAGE_H_ */
