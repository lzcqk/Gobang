#pragma once
#ifndef _GOBANGPLAYER_H_
#define _GOBANGPLAYER_H_
#include"defin.h"
#include"GobangAI.h"
#include "GobangMAKE.h"
class GobangPlayer
{
	private:
		int playerpower;//记录玩家的权重
		static int turn;//记录玩家当前棋盘所下的步数
		static int maxturn;//记录玩家全部落子的次数
	public:
		GobangMAKE assist;
		GobangAI oumiga;
		GobangPlayer(int flag = 2 );//初始化，当PVP时有特殊处理
		void on_Mouse(int event, int x, int y);//鼠标事件
		void withdraw();//悔棋操作
		void goforward();//撤销悔棋操作
		void one_more();//再来一盘操作
		void save();//保存棋局操作
		int rewrite();//读入旧棋盘操作
		static void onMouse(int event, int x, int y, int, void* userdata)
		{
			GobangPlayer* temp = reinterpret_cast<GobangPlayer*>(userdata);
			temp->on_Mouse(event, x, y);
		}
		void Initial();//鼠标事件入口
		int power();//返回玩家权重
		void freshstatic();//将turn，Maxturn全部清0

};

#endif // !_GOBANGPLAYER_H_

