/*
 * menu.h
 *
 *  Created on: 2021年2月23日
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
#define Max_Item_Amount 30      //菜单项的最大个数
#define delay_time 2000000

extern int32 Item_ID;
extern uint8 *buff;
extern uint8 Error;
typedef enum item_type          //菜单项类型
{
    intType = 1,                //整数型
    floatType,                  //浮点型
    listType,                   //菜单型（是一个子菜单的头节点）
    nulType,                   //无类型
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
 * @brief : 一些特殊节点的ID
 * @有的节点的调参（调整）界面与其他节点不同
 */
typedef enum special_id
{
    gear = 12,      //PID参数的档位，程序中只能作修改而没有使用，因为还没有PID程序
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

typedef struct Car_data                 //数据，整形或浮点型
{
    int     dataint;
    float   datafloat;
}Car_data;

//typedef union Car_data                //验收后改进：共用体型数据存储
//{
//    int     dataint;
//    float   datafloat;
//}Car_data;

extern Car_data CAR[Max_Item_Amount];  //数据结构体，包含整形和浮点型

typedef struct MenuItem_t
{
    itemType    Item_type;              //菜单项类型
    int         list_ID;                //菜单项在其直属菜单中的序号
    int         ID;                     //菜单项总序号
    int         data_range[2];          //数据上下限
    Car_data   *Item_data;              //数据指针，指向结构体
    struct MenuItem_t *Pre_item;               //前一个节点指针
    struct MenuItem_t *Next_item;              //后一个节点指针
    struct MenuItem_t *Child_list;             //子菜单第一项的指针（只有菜单项类型是listType时才非空）
    char        Item_name[name_size];   //菜单项名称，屏幕显示
}MenuItem_t;

/**
 * @brief : 将菜单项pItem插入菜单Menu
 */
void MenuItem_Insert(MenuItem_t* Menu, MenuItem_t* pItem);

/**
 * @brief : 根据需要打印菜单Menu
 */
void MenuPrint(MenuItem_t *Menu, MenuItem_t *currItem);

/**
 * @brief : 根据需要打印菜单项currItem，修改参数时用
 * @pos:光标位置；
 * @data_array:菜单项数据按位拆分成数组
 */
void ItemPrint(MenuItem_t *currItem, int32 pos, int32 *data_array, int32 length);

/**
 * @brief : 数据改完之后检查是否在正常范围内
 */
int32 DataCheck(MenuItem_t *currItem, int32 Item_dataint);

/**
 * @brief : 把按位拆分成的数组还原成数据
 */
int32 ArrayToDataint(int32 *data_array, int32 length);

/**
 * @brief : 建立菜单树
 */
MenuItem_t *MenuCreate(void);

/**
 * @brief :  菜单项创建
 * @Item_name:菜单项名称
 * @Item_Type:菜单项数据类型（枚举itemType）
 * @data_min: 菜单项数据的最小值
 * @data_max: 菜单项数据的最大值
 */
MenuItem_t *ItemCreate(char* Item_name, itemType Item_Type, int32 data_min, int32 data_max);

/**
 * @brief : 按键动作处理，调用其它数据处理函数，在主函数无限循环中被调用
 */
MenuItem_t *ButtonProcess(MenuItem_t *Menu, MenuItem_t* currItem);

/**
 * @brief : （菜单界面的）光标下移
 */
MenuItem_t *CursorMove_down(MenuItem_t* currItem);

/**
 * @brief : （菜单界面的）光标上移
 */
MenuItem_t *CursorMove_up(MenuItem_t* currItem);

/**
 * @brief : 进入菜单，菜单可以是包含数据的菜单，也可以是返回上一级菜单
 */
MenuItem_t *IntoMenu(MenuItem_t *currItem);

/**
 * @brief : 获得当前菜单项所直属的菜单节点
 */
MenuItem_t *GetRoot(MenuItem_t *currItem);

/**
 * @brief : 数据修改程序
 */
MenuItem_t *DataModify(MenuItem_t *currItem);

/**
 * @brief : 数据读取函数
 * @sector_num:从哪一个扇区读取数据
 */
void Date_Read(uint32 sector_num);

/**
 * @brief : 数据写入函数
 * @sector_num:从哪一个扇区读取数据
 */
void Date_Write(uint32 sector_num);



#endif /* SOURCE_MENU_H_ */
