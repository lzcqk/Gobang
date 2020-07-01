#pragma once
#ifndef _GOBANGAI_H_
#define _GOBANGAI_H_
#include"defin.h"
class GobangAI
{
	private:
		int AIpower ;//ai在棋盘中所拥有的权重，即代表它的数字
		int scoreboard[SIZE][SIZE] ;//记录各位点分数，让ai可选出一个最优的位置
		int staticpower ;  // 看看是什么棋子
		int nextx;//用于第二次虚拟落子
		int nexty ;
		int fourself_dying;//当有两个死四时为必胜棋，所以需要特殊处理
		int fourplayer_dying ;
		int maxscorex;//用于第二次虚拟落子时比较最大得分时，存储x
		int maxscorey;//用于第二次虚拟落子时比较最大得分时，存储y
		static int AIturn;//用于记录AI的当前棋盘中的落子数，用于悔棋等额外操作
		static int maxAIturn;//用于记录AI一共落子的次数
	public:
		GobangAI();//初始化
		void initial();//用于初始化scoreboard，将其全部重新置为0，便于下次利用
		void aidraw(int x, int  y);//将AI所选的位点绘画在棋盘上
		int LE(int x, int y, int flag, int role);//用于模拟棋子落在棋子连线首末的情况     eg：模拟落子：X  原有棋子为O         OOOOX
		int VOV(int x, int y, int flag, int role);//用于模拟棋子落在棋子连线之间的情况  eg：模拟落子：X  原有棋子为O          OXOOOO
		int AIjudge(int x, int y, int role); // role 控制加减        //模拟各种情况去处理棋盘
		void checkscore();//遍历有可能落子的scoreboard位置，寻找最大的得分位点，后输出
		int choose(int );//AI选择落子的入口，用于排除棋盘中已经落子的位置，后将未落子的位置交由AIjudge处理
		void next(int x, int y);//二次模拟落子
		void withdraw();//悔棋操作
		void goforward();//撤销悔棋操作
		int power();//返回AI的AIpower（返回AI的权重）
		void freshstatic();//将AIturn和AImaxturn清0，用于重新开始游戏等操作
		int Aiturn();//返回AIturn的值，用于悔棋等操作
};


#endif // !_GOBANGAI_H_

