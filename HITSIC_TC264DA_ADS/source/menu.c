/*
 * menu.c
 *
 *  Created on: 2021年2月23日
 *      Author: Administrator
 */


#include"menu.h"
#include"Control.hpp"
#include"image.h"

int Error;

MenuItem_t *ItemCreate(char* Item_name, itemType Item_Type, int data_min, int data_max)
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

//    if (Item_Type == intType)             //验收后改进：共用体型数据存储
//    {
//        pItem->Item_data = &CAR[Item_ID-1].dataint;
//    }else if (Item_Type == floatType)
//    {
//        pItem->Item_data = &CAR[Item_ID-1].dataint;
//    }

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
    MenuItem_t* Motor_Speed = ItemCreate("M_Speed", floatType, 0, 100);
    Motor_Speed->Item_data->datafloat=c_data[0].Motorspeed[0];
    MenuItem_Insert(MenuRoot, ItemCreate("*******", listType, 0, 20));
    MenuItem_Insert(MenuRoot, Motor);
    MenuItem_Insert(MenuRoot, Servo);
    MenuItem_Insert(MenuRoot, Camera);
    MenuItem_Insert(MenuRoot, Motor_Speed);
    MenuItem_Insert(MenuRoot, SAVE);


/*
    MenuItem_t* PID = ItemCreate("PID", listType, 1, 20);
    MenuItem_Insert(MenuRoot, PID);
    MenuItem_Insert(PID, ItemCreate("Back", listType, 1, 20));
    MenuItem_t* PID1 = ItemCreate("PID1", listType, 1, 20);
    MenuItem_t* PID2 = ItemCreate("PID2", listType, 1, 20);
    MenuItem_Insert(PID, PID1);
    MenuItem_Insert(PID, PID2);
    MenuItem_Insert(PID, ItemCreate("Gear", intType, 1, 2));   //特殊项，PID档位设置，因暂无PID程序，故未体现特殊性  ID = 12

    MenuItem_Insert(PID1, ItemCreate("Back", listType, 1, 20));
    MenuItem_Insert(PID1, ItemCreate("Kp1", floatType, 0, 10));     //特殊项  ID = 14，特殊项的ID有枚举
    MenuItem_Insert(PID1, ItemCreate("Ti1", intType, 0, 2000));     //特殊项  ID = 15
    MenuItem_Insert(PID1, ItemCreate("Td1", intType, 0, 2000));     //特殊项  ID = 16

    MenuItem_Insert(PID2, ItemCreate("Back", listType, 1, 20));
    MenuItem_Insert(PID2, ItemCreate("Kp2", floatType, 1, 20));
    MenuItem_Insert(PID2, ItemCreate("Ti2", intType, 0, 2000));
    MenuItem_Insert(PID2, ItemCreate("Td2", intType, 0, 2000));
    MenuItem_Insert(MenuRoot, ItemCreate("SAVE", listType, 0, 20)); //特殊项  ID = 21*/
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
    DISP_SSD1306_Fill(0);
    int x = 0, y = 2;   //菜单项在y = 2开始
    DISP_SSD1306_Printf_F6x8(0, 0,"%s     %d/%d", Menu->Item_name,currItem->list_ID, Menu->Item_data->dataint);
    DISP_SSD1306_Printf_F6x8(0, 1,"---------------------");
    int start_print_ID;
    MenuItem_t *pctrl = Menu->Child_list;
    start_print_ID = currItem->list_ID <= 6? 1:currItem->list_ID - 5;   //滚动式菜单，
    while (pctrl->list_ID != start_print_ID)        //从哪一项开始打印，需要改，光标移到最后再往上移有问题。
    {
        pctrl = pctrl->Next_item;
    }
    while (pctrl != NULL && y <= 7)
    {
        if (pctrl->Item_type == listType)
            DISP_SSD1306_Printf_F6x8(6, y,"[%s]", pctrl->Item_name);
        else if (pctrl->Item_type == intType)
        {
            DISP_SSD1306_Printf_F6x8(6, y,"%s", pctrl->Item_name);
            DISP_SSD1306_Printf_F6x8(66, y,"%3d", pctrl->Item_data->dataint);
        }
        else if (pctrl->Item_type == floatType)
        {
            DISP_SSD1306_Printf_F6x8(6, y,"%s", pctrl->Item_name);
            DISP_SSD1306_Printf_F6x8(66, y,"%3.4f", pctrl->Item_data->datafloat);
        }
        y++;
        pctrl = pctrl->Next_item;
    }
    DISP_SSD1306_Printf_F6x8(0, currItem->list_ID + 1 >= 7? 7: currItem->list_ID + 1,">");
}


int ButtonRead(void)
{
    int button_operation = 0;
    delay(2*1800000);
    if (!GPIO_PinRead(GPIOE, 11))
    {
        button_operation = up;
    }
    if (!GPIO_PinRead(GPIOE, 7))
    {
        button_operation = down;
    }
    if (!GPIO_PinRead(GPIOE, 9))
    {
        button_operation = left;
    }
    if (!GPIO_PinRead(GPIOE, 8))
    {
        button_operation = right;
    }
    if (!GPIO_PinRead(GPIOE, 10))
    {
        button_operation = OK;
    }
    return button_operation;
}


void delay(int i)
{
    while(i--);
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

            if  (currItem->list_ID==6)
            {
                /*da[0]=c_data[0].M_Kp;
                da[1]=c_data[0].M_Ki;
                da[2]=c_data[0].Motorspeed[0];
                da[3]=mora_flag;
                da[4]=c_data[0].Kp;
                da[5]=c_data[0].Kd;
                da[6]=c_data[0].servo_mid;
                da[7]=threshold;*/
                memcpy(&buff[0], CAR, sizeof(Car_data) * Max_Item_Amount);
                FLASH_SectorWrite(0, buff);
                //Date_Write();
                //currItem = IntoMenu(currItem);
                MenuPrint(Menu, currItem);
                c_data[0].M_Kp=CAR[3].datafloat;
                c_data[0].M_Ki=CAR[4].datafloat;
                c_data[0].Motorspeed[0]=CAR[17].datafloat;
                mora_flag=CAR[5].datafloat;
                c_data[0].Kp=CAR[8].datafloat;
                c_data[0].Kd=CAR[9].datafloat;
                c_data[0].servo_mid=CAR[10].datafloat;
                threshold=CAR[13].dataint;

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
void ItemPrint(MenuItem_t *currItem, int pos, int *data_array, int length)
{
    bool flag=0;
    DISP_SSD1306_Fill(0);
    int max_digit = length;//sizeof(data_array) / sizeof(int32_t);

    DISP_SSD1306_Printf_F6x8(0, 0,"  %s   [%d,%d]", currItem->Item_name, currItem->data_range[min], currItem->data_range[max]);
    DISP_SSD1306_Printf_F6x8(0, 1,"---------------------");

    int i;
    for(i = 0; i < max_digit; i++)
    {
        //DISP_SSD1306_Printf_F6x8(42 + i*6, 3, "%d", data_array[i]);     //显示各个数位
        if (currItem->Item_type == floatType)
        {
            if(i==(max_digit-4))
            {
                DISP_SSD1306_Printf_F6x8(42 + i*6, 3, ".");
                DISP_SSD1306_Printf_F6x8(42 + (i+1)*6, 3, "%d", data_array[i]);
                flag=1;
            }
            else
            {
                if(flag==1)
                {
                    DISP_SSD1306_Printf_F6x8(42 + (i+1)*6, 3, "%d", data_array[i]);
                }
                else
                {
                    DISP_SSD1306_Printf_F6x8(42 + i*6, 3, "%d", data_array[i]);
                }
            }
        }
        else if(currItem->Item_type == intType)
        {
            DISP_SSD1306_Printf_F6x8(42 + i*6, 3, "%d", data_array[i]);     //显示各个数位
        }
    }
    DISP_SSD1306_Printf_F6x8(12, 7, "[OK]");
    DISP_SSD1306_Printf_F6x8(60, 7, "[Cancel]");
    if  (pos == max_digit + 1)
    {
        DISP_SSD1306_Printf_F6x8(6, 7, ">");
    }
    else if (pos == max_digit + 2)
    {
        DISP_SSD1306_Printf_F6x8(54, 7, ">");
    }
    else
    {
        DISP_SSD1306_Printf_F6x8(42 + (pos-1)*6, 4, "^");
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
    max_digit = (currItem->Item_type == intType) ? 0 : 4;   //所有浮点型均为四位小数
    int data_max = currItem->data_range[max];
    while(data_max != 0)
    {
        data_max /= 10;
        max_digit++;
    }                       //获得最大数位

    int data_array[max_digit];
    int Item_dataint = (currItem->Item_type == intType) ? currItem->Item_data->dataint : floor(currItem->Item_data->datafloat * 10000);
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
                if (pos == max_digit + 1)       //[OK]
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
                if (pos == max_digit + 2)           //[cancel]，返回上一级菜单
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


int DataCheck(MenuItem_t *currItem, int Item_dataint)
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

int ArrayToDataint(int *data_array, int length)
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

void Date_Read()
{
    Error=FLASH_SectorRead(0,buff);
    //int length=sizeof(read)/sizeof(float);
    //float* date=(float*)malloc(sizeof(float)*4096);
    //FLASH_SectorRead(sector,date);
    memcpy(da,&buff[0],8*sizeof(float));
    c_data[0].M_Kp=da[0];
    c_data[0].M_Ki=da[1];
    c_data[0].Motorspeed[0]=da[2];
    mora_flag=da[3];
    c_data[0].Kp=da[4];
    c_data[0].Kd=da[5];
    c_data[0].servo_mid=da[6];
    threshold=da[7];
    //free(date);
}
void Date_Write()
{
    /*da[0]=Motor_Kp->Item_data->datafloat;
    da[1]=Motor_Ki->Item_data->datafloat;
    da[2]=Motor_Speed->Item_data->datafloat;
    da[3]=Mora_flag->Item_data->datafloat;
    da[4]=Servo_Kp->Item_data->datafloat;
    da[5]=Servo_Kd->Item_data->datafloat;
    da[6]=Servo_Mid->Item_data->datafloat;
    da[7]=Threshold->Item_data->dataint;*/
    //int length=sizeof(write)/sizeof(float);
    //float* date=(float*)malloc(sizeof(float)*4096);
    //FLASH_SectorRead(sector,date);
    memcpy(&buff[0],da,8*sizeof(float));
    Error=FLASH_SectorWrite(0,buff);
    //free(date);
}
//PID参数调节的单独程序，实现较复杂，因为发现了更简单的方案，所以没有完成
//
//MenuItem_t* PIDAdjust(MenuItem_t* currItem)
//{
//    currItem = IntoMenu(currItem);
//    while (true)
//    {
//        int32_t button_order = ButtonRead();
//        switch (button_order)
//        {
//            case up:
//                currItem = CursorMove_up(currItem);
//                MenuPrint(Menu, currItem);
//                break;
//            case down:
//                currItem = CursorMove_down(currItem);
//                MenuPrint(Menu, currItem);
//                break;
//            case OK:
//                if (currItem->list_ID == 1)
//                {
//                    currItem = IntoMenu(currItem);
//                    return currItem;
//                }
//                else if (currItem->Item_type == listType)
//                    currItem = IntoMenu(currItem);
//                else  currItem = DataModify(currItem);
//                break;
//            case left:
//                if (currItem->list_ID == 4 && currItem->Item_data->dataint > 1) //Gear
//                {
//                    currItem->Item_data->dataint--;
//                    //修改档位相关操作
//                    MenuPrint(Menu, currItem);
//                }
//                break;
//            case right:
//                if (currItem->list_ID == 4 && currItem->Item_data->dataint < 2) //加新的PID档位改这里的2
//                {
//                    currItem->Item_data->dataint++;
//                    //修改档位相关操作
//                    MenuPrint(Menu, currItem);
//                }
//                break;
//            default:
//                break;
//        }
//    }
//
//}





