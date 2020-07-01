#pragma once
#ifndef _DEFIN_H_
#define _DEFIN_H_
#include<opencv2/opencv.hpp>
using namespace cv; 

#define BLUE  Scalar(255,140,0)
#define BLACK Scalar (0,0,0)//scalar 为BGR 
#define WHITE Scalar(255,255,255,100)
#define RED Scalar(38 ,38,205)
constexpr auto SIZE =15;

extern int Gametype;//记录游戏类型
extern int Gofirst;//记录先手状态
extern int finish ;//用于当有一方获胜时，终止循环
extern int board[SIZE][SIZE]; //AI 为1， player 为2
//extern int playerhist[SIZE * 2] ;
//extern int AIhist[SIZE * 2];
extern  int maxx , maxy; //记录格子 减少遍历次数
extern int minx , miny ;   // 记录格子减少遍历次数
extern int playerpoint ;   // 玩家落子数  用于观察玩家是否落子 如果是 则AI落子
extern const char* imagename ;//棋盘背景名称 xxx.jpg
extern Mat picture;
extern int zuo[48] ;//   将图片的xy像素均匀分布在数组中，便于操作棋盘
extern int  xia[36]; // 36 ---->>   2x + 4           __________    1 4 --->>  x 
void mmcompare(int x, int y);//将maxx，maxy，minx，miny根据落子的x，y大小进行改进，从而防止遗漏某一个位置
int PvE();//人机对战模式
int PvP();//双人博弈
#endif // !_DEFIN_H_
