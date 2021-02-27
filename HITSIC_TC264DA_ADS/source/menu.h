/*
 * menu.h
 *
 *  Created on: 2021��2��23��
 *      Author: Administrator
 */

#ifndef SOURCE_MENU_H_
#define SOURCE_MENU_H_

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "SmartCar_Flash.h"
//#include "drv_disp_ssd1306.hpp"
//#include "drv_ftfx_flash.hpp"

#define name_size 16u
#define Max_Item_Amount 30      //�˵����������
#define delay_time 2000000

extern int32 Item_ID;
extern uint8 *buff;
extern uint8 Error;
typedef enum item_type          //�˵�������
{
    intType = 1,                //������
    floatType,                  //������
    listType,                   //�˵��ͣ���һ���Ӳ˵���ͷ�ڵ㣩
    nulType,                   //������
}itemType;

typedef enum button_order
{
    up = 1,
    down, //2
    left,//3
    right,//4
    OK,//5
}button_order;


/**
 * @brief : һЩ����ڵ��ID
 * @�еĽڵ�ĵ��Σ������������������ڵ㲻ͬ
 */
typedef enum special_id
{
    gear = 12,      //PID�����ĵ�λ��������ֻ�����޸Ķ�û��ʹ�ã���Ϊ��û��PID����
    Kp1  = 14,
    Ti1  = 15,
    Td1  = 16,
    save = 21,
}special_id;

typedef enum range
{
    min = 0,
    max,
}range;

typedef struct Car_data                 //���ݣ����λ򸡵���
{
    int     dataint;
    float   datafloat;
}Car_data;

//typedef union Car_data                //���պ�Ľ��������������ݴ洢
//{
//    int     dataint;
//    float   datafloat;
//}Car_data;

extern Car_data CAR[Max_Item_Amount];  //���ݽṹ�壬�������κ͸�����

typedef struct MenuItem_t
{
    itemType    Item_type;              //�˵�������
    int         list_ID;                //�˵�������ֱ���˵��е����
    int         ID;                     //�˵��������
    int         data_range[2];          //����������
    Car_data   *Item_data;              //����ָ�룬ָ��ṹ��
    struct MenuItem_t *Pre_item;               //ǰһ���ڵ�ָ��
    struct MenuItem_t *Next_item;              //��һ���ڵ�ָ��
    struct MenuItem_t *Child_list;             //�Ӳ˵���һ���ָ�루ֻ�в˵���������listTypeʱ�ŷǿգ�
    char        Item_name[name_size];   //�˵������ƣ���Ļ��ʾ
}MenuItem_t;

/**
 * @brief : ���˵���pItem����˵�Menu
 */
void MenuItem_Insert(MenuItem_t* Menu, MenuItem_t* pItem);

/**
 * @brief : ������Ҫ��ӡ�˵�Menu
 */
void MenuPrint(MenuItem_t *Menu, MenuItem_t *currItem);

/**
 * @brief : ������Ҫ��ӡ�˵���currItem���޸Ĳ���ʱ��
 * @pos:���λ�ã�
 * @data_array:�˵������ݰ�λ��ֳ�����
 */
void ItemPrint(MenuItem_t *currItem, int32 pos, int32 *data_array, int32 length);

/**
 * @brief : ���ݸ���֮�����Ƿ���������Χ��
 */
int32 DataCheck(MenuItem_t *currItem, int32 Item_dataint);

/**
 * @brief : �Ѱ�λ��ֳɵ����黹ԭ������
 */
int32 ArrayToDataint(int32 *data_array, int32 length);

/**
 * @brief : �����˵���
 */
MenuItem_t *MenuCreate(void);

/**
 * @brief :  �˵����
 * @Item_name:�˵�������
 * @Item_Type:�˵����������ͣ�ö��itemType��
 * @data_min: �˵������ݵ���Сֵ
 * @data_max: �˵������ݵ����ֵ
 */
MenuItem_t *ItemCreate(char* Item_name, itemType Item_Type, int32 data_min, int32 data_max);

/**
 * @brief : �����������������������ݴ�������������������ѭ���б�����
 */
MenuItem_t *ButtonProcess(MenuItem_t *Menu, MenuItem_t* currItem);

/**
 * @brief : ���˵�����ģ��������
 */
MenuItem_t *CursorMove_down(MenuItem_t* currItem);

/**
 * @brief : ���˵�����ģ��������
 */
MenuItem_t *CursorMove_up(MenuItem_t* currItem);

/**
 * @brief : ����˵����˵������ǰ������ݵĲ˵���Ҳ�����Ƿ�����һ���˵�
 */
MenuItem_t *IntoMenu(MenuItem_t *currItem);

/**
 * @brief : ��õ�ǰ�˵�����ֱ���Ĳ˵��ڵ�
 */
MenuItem_t *GetRoot(MenuItem_t *currItem);

/**
 * @brief : �����޸ĳ���
 */
MenuItem_t *DataModify(MenuItem_t *currItem);

/**
 * @brief : ���ݶ�ȡ����
 * @sector_num:����һ��������ȡ����
 */
void Date_Read(uint32 sector_num);

/**
 * @brief : ����д�뺯��
 * @sector_num:����һ��������ȡ����
 */
void Date_Write(uint32 sector_num);



#endif /* SOURCE_MENU_H_ */
