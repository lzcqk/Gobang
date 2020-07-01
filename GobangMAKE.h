#pragma once
#ifndef _GOBANGMAKE_H_
#define _GOBANGMAKE_H_
class GobangMAKE
{
private:
	int n;
public:
	GobangMAKE();
	void make_board();//将棋盘和各个控件画出
	void board_initial();//将board全部归0，用于重新开始一盘游戏
	void refresh();//将board上面的棋子全部画上棋盘中，用于读入旧棋盘时
};
#endif // !_GOBANGMAKE_H_



