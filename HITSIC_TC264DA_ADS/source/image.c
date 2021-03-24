/*
 * image.c
 *
 *  Created on: 2021年2月23日
 *      Author: Administrator
 */



#include "image.h"
#include "my_math.h"
#include "team_ctr.h"
int f[10 * CAMERA_H];//考察连通域联通性
int flag=-1;
int light_flag[10]={0};
int number=0;
int sum=0;
//每个白条子属性
typedef struct {
    uint8   left;//左边界
    uint8   right;//右边界
    uint8   width;
    int   connect_num;//连通标记（号）
}range;

//每行的所有白条子
typedef struct {
    uint8   num;//每行白条数量
    range   area[white_num_MAX];//该行各白条区域
}all_range;

//属于赛道的每个白条子属性
typedef struct {
    uint8   left;//左边界
    uint8   right;//右边界
    uint8   width;//宽度
}road_range;

typedef struct {
    uint8   left;//左边界
    uint8   right;//右边界
    uint8   width;//宽度
}light_range;
//每行属于信标灯的白条子
typedef struct {
    uint8      white_num;
    light_range  connected[white_num_MAX];
}light;

typedef struct {
    int x;
    int y;
}point;

point determined_leftdown_point;
point determined_leftup_point;
point determined_rightdown_point;
point determined_rightup_point;

uint8 banmaxian_flag = 0;
uint8 cross_flag = 0;
uint8 out_flag= 0;
int zebra = 5;

//每行属于赛道的每个白条子
typedef struct {
    uint8   white_num;
    road_range   connected[white_num_MAX];
}road;

all_range white_range[CAMERA_H];//所有白条子
road my_road[CAMERA_H];//赛道
uint8 IMG[CAMERA_H][CAMERA_W];//二值化后图像数组
uint8 left_line[CAMERA_H], right_line[CAMERA_H];//赛道的左右边界
uint8 mid_line[CAMERA_H];
int all_connect_num = 0;//所有白条子数
uint8 top_road;//赛道最高处所在行数
int threshold = 215;//阈值
uint8* fullBuffer;
int foresight = 40;
light my_light[CAMERA_H];//信标灯
uint8 centre_h = 0;
uint8 centre_l = 0;
uint8 centre_h_pre = 0;
uint8 centre_l_pre = 0;
////////////////////////////////////////////
//功能：二值化
//输入：灰度图片
//输出：二值化图片
//备注：
///////////////////////////////////////////
void THRE()
{
    uint8* map;
    uint8* my_map;
    map = camera_buffer_addr;
    for (int i = 0; i < 120; i++)
    {
        my_map = &IMG[i][0];
        for (int j = 0; j < 188; j++)
        {
            if ((*map) > threshold)
                (*my_map) = 255;
            else (*my_map) = 0;
            map++;
            my_map++;
        }
    }
}

////////////////////////////////////////////
//功能：粗犷的清车头
//输入：
//输出：
//备注：要根据自己车头的大小进行修改
///////////////////////////////////////////
void head_clear(void)
{
    uint8* my_map;
    for (int i = 119; i >= 84; i--)
    {
        my_map = &IMG[i][0];
        for (int j = 40; j <= 135; j++)
        {
            *(my_map+j) = 255;
        }
    }
}

////////////////////////////////////////////
//功能：查找父节点
//输入：节点编号
//输出：最老祖先
//备注：含路径压缩
///////////////////////////////////////////
int find_f(int node)//返回的是父节点
{
    if (f[node] == node)return node;//找到最古老祖先，return
    f[node] = find_f(f[node]);//向上寻找自己的父节点
    return f[node];
}

////////////////////////////////////////////
//功能：提取跳变沿 并对全部白条子标号
//输入：IMG[120][188]
//输出：white_range[120]
//备注：指针提速
///////////////////////////////////////////
void search_white_range()
{
    uint8 i, j;
    int istart = NEAR_LINE;//处理起始行
    int iend = FAR_LINE;//处理终止行
    int tnum = 0;//当前行白条数
    all_connect_num = 0;//白条编号初始化
    uint8* map = NULL;
    for (i = istart; i >= iend; i--)
    {
        map = &IMG[i][LEFT_SIDE];//指针行走加快访问速度
        tnum = 0;
        for (j = LEFT_SIDE; j <= RIGHT_SIDE; j++, map++)
        {
            if ((*map))//遇白条左边界
            {
                tnum++;
                if (tnum >= white_num_MAX)break;
                range* now_white = &white_range[i].area[tnum];
                now_white->left = j;

                //开始向后一个一个像素点找这个白条右边界
                map++;
                j++;

                while ((*map) && j <= RIGHT_SIDE)
                {
                    map++;
                    j++;
                }
                now_white->right = j - 1;
                now_white->connect_num = ++all_connect_num;//白条数加一，给这个白条编号
                //计算白条的宽度
                now_white->width = now_white->right - now_white->left;
            }
        }
        white_range[i].num = tnum;
    }
}

////////////////////////////////////////////
//功能：寻找白条子连通性，将全部联通白条子的节点编号刷成最古老祖先的节点编号
//输入：
//输出：
//备注：
///////////////////////////////////////////
void find_all_connect()
{
    //f数组初始化
    for (int i = 1; i <= all_connect_num; i++)
        f[i] = i;

    //u为up d为down 即为当前处理的这两行中的上面那行和下面那行
    //u_num：上面行白条数
    //u_left：上面行当前白条左边界
    //u_right：上面行当前白条右边界
    //i_u：当前处理的这个白条是当前这行（上面行）白条中的第i_u个
    int u_num, i_u, u_left, u_right;
    int d_num, i_d, d_left, d_right;
    all_range* u_white = NULL;
    all_range* d_white = NULL;
    for (int i = NEAR_LINE; i > FAR_LINE; i--)//因为每两行每两行比较 所以循环到FAR_LINE+1
    {
        u_num = white_range[i - 1].num;
        d_num = white_range[i].num;
        u_white = &white_range[i - 1];
        d_white = &white_range[i];
        i_u = 1; i_d = 1;

        //循环到当前行或上面行白条子数耗尽为止
        while (i_u <= u_num && i_d <= d_num)
        {
            //变量先保存，避免下面访问写的冗杂且访问效率低
            u_left = u_white->area[i_u].left;
            u_right = u_white->area[i_u].right;
            d_left = d_white->area[i_d].left;
            d_right = d_white->area[i_d].right;

            if (u_left <= d_right && u_right >= d_left)//如果两个白条联通
                f[find_f(u_white->area[i_u].connect_num)] = find_f(d_white->area[i_d].connect_num);//父节点连起来

            //当前算法规则，手推一下你就知道为啥这样了
            if (d_right > u_right)i_u++;
            if (d_right < u_right)i_d++;
            if (d_right == u_right) { i_u++; i_d++; }
        }
    }
}

////////////////////////////////////////////
//功能：寻找赛道
//输入：
//输出：
//备注：
///////////////////////////////////////////
void find_road()
{
    uint8 istart = NEAR_LINE;
    uint8 iend = FAR_LINE;
    top_road = NEAR_LINE;//赛道最高处所在行数，先初始化话为最低处
    int road_f = -1;//赛道所在连通域父节点编号，先初始化为-1，以判断是否找到赛道
    int while_range_num = 0, roud_while_range_num = 0;
    all_range* twhite_range = NULL;
    road* tmy_road = NULL;
    //寻找赛道所在连通域
    // 寻找最中心的白条子
    for (int i = 1; i <= white_range[istart].num; i++)
        if (white_range[istart].area[i].left <= CAMERA_W / 2
            && white_range[istart].area[i].right >= CAMERA_W / 2 && (white_range[istart].area[i].right - white_range[istart].area[i].left) >= 90)
            road_f = find_f(white_range[istart].area[i].connect_num);

    if (road_f == -1)//若赛道没在中间，在113行选一行最长的认为这就是赛道
    {
        int widthmax = 0, jselect = 1;
        for (int i = 1; i <= white_range[istart].num; i++)
            if (white_range[istart].area[i].right - white_range[istart].area[i].left > widthmax)
            {
                widthmax = white_range[istart].area[i].right - white_range[istart].area[i].left;
                jselect = i;
            }
        road_f = find_f(white_range[istart].area[jselect].connect_num);
    }

    //现在我们已经得到了赛道所在连通域父节点编号，接下来把所有父节点编号是road_f的所有白条子扔进赛道数组就行了
    for (int i = istart; i >= iend; i--)
    {
        //变量保存，避免之后写的冗杂且低效
        twhite_range = &white_range[i];
        tmy_road = &my_road[i];
        while_range_num = twhite_range->num;
        tmy_road->white_num = 0;
        roud_while_range_num = 0;
        for (int j = 1; j <= while_range_num; j++)
        {
            if (find_f(twhite_range->area[j].connect_num) == road_f)
            {
                top_road = i;
                tmy_road->white_num++; roud_while_range_num++;
                tmy_road->connected[roud_while_range_num].left = twhite_range->area[j].left;
                tmy_road->connected[roud_while_range_num].right = twhite_range->area[j].right;
                tmy_road->connected[roud_while_range_num].width = twhite_range->area[j].right - twhite_range->area[j].left;

            }
        }
    }
}

////////////////////////////////////////////
//功能：返回相连下一行白条子编号
//输入：i_start起始行  j_start白条标号
//输出：白条标号
//备注：认为下一行与本行赛道重叠部分对多的白条为选定赛道
///////////////////////////////////////////
uint8 find_continue(uint8 i_start, uint8 j_start)
{
    uint8 j_return;
    uint8 j;
    uint8 width_max = 0;
    uint8 width_new = 0;
    uint8 left = 0;
    uint8 right = 0;
    uint8 dright, dleft, uright, uleft;
    j_return = MISS;//如果没找到，输出255
    if (j_start > my_road[i_start].white_num)
        return MISS;
    //选一个重叠最大的
    for (j = 1; j <= my_road[i_start - 1].white_num; j++)
    {
        dleft = my_road[i_start].connected[j_start].left;
        dright = my_road[i_start].connected[j_start].right;
        uleft = my_road[i_start - 1].connected[j].left;
        uright = my_road[i_start - 1].connected[j].right;
        if (//相连
            dleft < uright
            &&
            dright > uleft
            )
        {
            //计算重叠大小
            if (dleft < uleft) left = uleft;
            else left = dleft;

            if (dright > uright) right = uright;
            else right = dright;

            width_new = right - left + 1;

            if (width_new > width_max)
            {
                width_max = width_new;
                j_return = j;
            }
        }

    }
    return j_return;
}

////////////////////////////////////////////
//功能：通用决定双边
//输入：
//输出：
//备注：
///////////////////////////////////////////
void ordinary_two_line(void)
{
    uint8 i;
    uint8 j;
    uint8 j_continue[CAMERA_H];//第一条连通路径
    uint8 i_start;
    uint8 i_end;
    uint8 j_start = MISS;
    int width_max;

    //寻找起始行最宽的白条子
    i_start = NEAR_LINE;
    i_end = FAR_LINE;
    width_max = 0;
    for (j = 1; j <= my_road[i_start].white_num; j++)
    {
        if (my_road[i_start].connected[j].width > width_max)
        {
            width_max = my_road[i_start].connected[j].width;
            j_start = j;
        }
    }
    j_continue[i_start] = j_start;

    //记录连贯区域编号
    for (i = i_start; i > i_end; i--)
    {
        //如果相连编号大于该行白条数，非正常，从此之后都MISS
        if (j_continue[i] > my_road[i].white_num)
        {
            j_continue[i - 1] = MISS;
        }
        else
        {
            j_continue[i - 1] = find_continue(i, j_continue[i]);
        }

    }

    //全部初始化为MISS
    my_memset(left_line, MISS, CAMERA_H);
    my_memset(right_line, MISS, CAMERA_H);


    for (i = i_start; i > i_end; i--)
    {
        if (j_continue[i] <= my_road[i].white_num)
        {
            left_line[i] = my_road[i].connected[j_continue[i]].left;
            right_line[i] = my_road[i].connected[j_continue[i]].right;
            IMG[i][left_line[i]] = blue;
            IMG[i][right_line[i]] = red;
        }
        else
        {
            left_line[i] = MISS;
            right_line[i] = MISS;
        }
    }
}

////////////////////////////////////////////
//功能：数组初始化
//输入：uint8_t* ptr 数组首地址, uint8_t num初始化的值, uint8_t size数组大小
//输出：
//备注：因为k66库中认为memset函数不安全，所以无法使用；因此需要自己写一个my_memset
///////////////////////////////////////////
void my_memset(uint8* ptr, uint8 num, uint8 size)
{
    uint8* p = ptr;
    uint8 my_num = num;
    uint8 Size = size;
    for (int i = 0; i < Size; i++, p++)
    {
        *p = my_num;
    }
}
////////////////////////////////////////////
//功能：中线合成
//输入：左右边界
//输出：中线
//备注：
///////////////////////////////////////////
void get_mid_line(void)
{
    my_memset(mid_line, MISS, CAMERA_H);
    for(int i = NEAR_LINE;i >= FAR_LINE;i--)
        if (left_line[i] != MISS)
        {
            mid_line[i] = (left_line[i] + right_line[i]) / 2;
        }
        else
        {
            mid_line[i] = MISS;
        }

}
////////////////////////////////////////////
//功能：图像处理主程序
//输入：
//输出：
//备注：
///////////////////////////////////////////
void image_main()
{
    //head_clear();//清车头
   // banmaxian(zebra);//斑马线识别
    search_white_range();
     find_all_connect();

    find_light();
    if(number<10)
    {
        light_flag[number]=flag;
        number++;
    }
    else if (number==10)
    {
        for (int j=0;j<9;j++)
        {
            light_flag[j]=light_flag[j+1];
        }
        light_flag[9]=flag;
    }
    sum=sum_array(light_flag,10);
    if(sum<=2 && sum>=-2 && flag==-1)
    {
        centre_h=centre_h_pre;
        centre_l=centre_l_pre;
    }
    else if(sum<-5 )  //已切灯，寻找下一个
    {
        if(centre_l<94) //左切,舵机左打满
        {
            centre_h=0;
            centre_l=0;
        }
        else if (centre_l>=94)  //右切，舵机右打满
        {
            centre_h=0;
            centre_l=188;
        }
    }
    else if (sum<-5 &&light_flag[9]==1)
    {
        sum=0;
        light_flag[0]=1;
        for (int j=1;j<10;j++)
        {
            light_flag[j]=0;
        }
    }

}
float get_error(void)
{
    int id=0;
    int a=0;
    int tr=distance_LIGHT_true(centre_l,centre_h);
    if(tr>=30)
    {
        if(centre_l>94) a=centre_l-94;
        else a=94-centre_l;
    }
    else
    {
        if(centre_l>94)
            {
                id=distance_LIGHT_ideal_right(centre_l-94,centre_h);
                a=tr-id;
            }
            else
            {
                id=distance_LIGHT_ideal_left(centre_l-94,centre_h);
                a=id-tr;
            }
    }

    wifidata[7]=id;
    wifidata[8]=tr;

    wifidata[9]=a;
    wifidata[10]=centre_l;
    wifidata[11]=centre_h;
    return a;

}


void banmaxian(int zebra)
{
    int count_flag = 0;

    if ((my_road[foresight].white_num > zebra)
       || (my_road[foresight - 2].white_num) > zebra
       || (my_road[foresight - 4].white_num) > zebra
       || (my_road[foresight + 2].white_num) > zebra
       || (my_road[foresight + 4].white_num) > zebra
       )
           {
                banmaxian_flag = 1;
            }
}
    /*{
        if((my_road[foresight - 1].white_num = 1))
        count_flag ++;
    }

    if((my_road[foresight].white_num > 6)
       || (my_road[foresight - 2].white_num) > 6
       || (my_road[foresight - 4].white_num) > 6)
    {
        if(count_flag == 1)
        {
            banmaxian_flag = 1;
        }

    }
}*/

void ckeck_out_road()//检测跑出赛道函数
{
    int* my_map;
      int count = 0;//检测该范围黑点个数
      for (int i = 115; i >= 80; i--)
      {
          my_map = &IMG[i][0];
          for (int j = 60; j <= 110; j++)
            { if (*(my_map + j) ==0)
                 { count++; }
            }
      }


      if (count >= 1500)
          {out_flag= 1;}

      else out_flag= 0;
}
////////////////////////////////////////////
//功能：标记信标灯
//输入：
//输出：
//备注：
///////////////////////////////////////////
void find_light()
{
    centre_h_pre=centre_h;
    centre_l_pre=centre_l;
    uint8 istart = NEAR_LINE;
    uint8 iend = FAR_LINE;
    uint8 start_light_line = NEAR_LINE;
    uint8 end_light_line = FAR_LINE;
    int while_range_num = 0, light_while_range_num = 0;
    all_range* twhite_range = NULL;
    light* tmy_light = NULL;
    int width=0;

    int widthmax=0;
    int light_row=0;
    int light_f = -1;//信标灯所在连通域父节点编号，先初始化为-1，以判断是否找到信标灯
    int flag_j = 0;
    //寻找信标灯所在的第一个行数
    for (int i = istart; i >= iend; i--)
    {
        for (int j = 1; j <= white_range[i].num; j++)
        {
            width = white_range[i].area[j].right - white_range[i].area[j].left;
            if (width >= widthmax)
            {
                widthmax = width;
                light_row = j;
            }

        }
            if (white_range[i].num!=0&&white_range[i].area[light_row].width>=3&& white_range[i-1].num != 0 && white_range[i-1].area[light_row].width >= 3 && white_range[i - 2].num != 0 && white_range[i - 2].area[light_row].width >= 3)
            {
                start_light_line = i;
                flag = 1;
                break;
            }
            else
            {
                start_light_line = NEAR_LINE;
                flag = -1;
            }
    }


        for (int i = start_light_line; i >= iend; i--)
        {
             if (white_range[i].num == 0&&flag==1)
             {
                 end_light_line = i;
                 break;
             }
        }
        int mid_line = 0.5 * (start_light_line + end_light_line);
        light_f = find_f(white_range[start_light_line].area[light_row].connect_num);
        int mid_j = 0;
        int wid = 0;
        int widmax = 0;
        int j_flag = 0;
        int m, n;
        for (int i = start_light_line; i > end_light_line; i--)
        {
            //变量保存，避免之后写的冗杂且低效
            twhite_range = &white_range[i];
            tmy_light = &my_light[i];
            while_range_num = twhite_range->num;
            tmy_light->white_num = 0;
            for (int j = 1; j <= while_range_num; j++)
            {
                if (find_f(twhite_range->area[j].connect_num) == light_f)
                {
                    wid= twhite_range->area[j].right - twhite_range->area[j].left;
                    if (wid > widmax)
                    {
                        widmax = wid;
                        j_flag = j;
                    }

                    tmy_light->connected[j_flag].left = twhite_range->area[j_flag].left;
                    tmy_light->connected[j_flag].right = twhite_range->area[j_flag].right;
                    tmy_light->connected[j_flag].width = twhite_range->area[j_flag].right - twhite_range->area[j_flag].left;
                }
            }
            if (i == 0.5 * (start_light_line + end_light_line))
            {
                mid_j = j_flag;
            }
            m = my_light[i].connected[j_flag].left;
            n = my_light[i].connected[j_flag].right;
            //绘制信标灯轮廓
            for (int j = m; j <= n; j++)
            {
                if (flag == 1)
                {
                    IMG[i][j] = purple;
                }
            }
        }
        //将信标灯的标记出来
        if (flag == 1)
        {
            centre_h = 0.5 * (start_light_line + end_light_line);
            centre_l = ceil(0.5 * (m + n));
            IMG[centre_h][centre_l] =blue;
        }
}

