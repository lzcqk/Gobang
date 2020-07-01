#pragma once
#ifndef _GOBANGJUDGE_H_
#define _GOBANGJUDGE_H_
#include<iostream>
#include"defin.h"
using namespace std;
class GobangJudge
{
	public:
		int bjudge(int a[][SIZE], int power);  //检查是否有一方玩家获得胜利
		int claim(int power,int flag = 2);  // 有一方胜利 返回1     break 出while     //宣布比赛结果，将结果分配给Text变量
		void Text(string text);  //将text打印在棋盘上
};
#endif // !_GOBANGJUDGE_H_



