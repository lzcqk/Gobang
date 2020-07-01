#include "GobangAI.h"
#include"defin.h"
#include<fstream>
#include<iostream>
using namespace std;

GobangAI::GobangAI()
{
	AIpower = 1;
	staticpower = 0;  // 看看是什么棋子
	nextx = -1;
	nexty = -1;
	fourself_dying = 0;
	fourplayer_dying = 0;
	maxscorex = 0;
	maxscorey = 0;
	ofstream AIcling("AIchessboard.txt", ios::trunc);
	AIcling.close();
	initial();
}
int GobangAI::AIturn = 0;
int GobangAI::maxAIturn = 0;

void GobangAI::initial()
{
	int xi = minx; int xa = maxx; int yi = miny; int ya = maxy;  int temp;
	if (xi > 0) xi--; if (xa < 14) xa++; if (yi > 0) yi--; if (ya < 14) ya++;  // 扩大一格
	temp = yi;
	for (; xi <= xa; xi++)
	{
		for (yi = temp; yi <= ya; yi++) { scoreboard[xi][yi] = 0; }
	}
}

void GobangAI::aidraw(int x, int  y)
{
	board[x][y] = AIpower;
	circle(picture, Point(zuo[2 * x + 4], xia[2 * y + 4]), 8, BLACK, -1);
	//AIhist[2 * AIturn] = x;
	//AIhist[2 * AIturn + 1] = y;
	ofstream AIwriter("AIchessboard.txt", ios::in);
	if (AIwriter.is_open())
	{
		AIwriter.seekp(int(AIturn * 6), ios::beg);
		if (x >= 10) { AIwriter << x; }
		else AIwriter << "0" << x;
		AIwriter << " ";
		if (y >= 10) { AIwriter << y; }
		else AIwriter << "0" << y;
		AIwriter << " ";
		AIwriter.close();
	}
	if (AIturn == maxAIturn) maxAIturn++;
	AIturn++;
	mmcompare(x, y);
}

int GobangAI::LE(int x, int y, int flag, int role)
{
	for (int i = -1; i <= 1; i += 1)
	{
		for (int j = -1; j <= 1; j += 1)  // 八个方向 还可能是 3 ----  1 这样子
		{
			if (flag == 4)
			{
				if (0 <= x + 4 * i && x + 4 * i <= 14 && 0 <= y + 4 * j && y + 4 * j <= 14 && (i != 0 || j != 0))  // 八个方向检查    未过界限
				{
					if (board[x][y] == board[x + 1 * i][y + 1 * j] && board[x + 1 * i][y + 1 * j] == board[x + 2 * i][y + 2 * j] &&
						board[x + 2 * i][y + 2 * j] == board[x + 3 * i][y + 3 * j]
						&& board[x + 3 * i][y + 3 * j] == board[x + 4 * i][y + 4 * j] && board[x + 4 * i][y + 4 * j] != 0)
					{
						if (role == 1)
						{
							board[x][y] = 0;
							aidraw(x, y);
							return 1;
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 3000;
						}
					}
				}
			}
			if (flag == 3)
			{
				if (0 <= x + 3 * i && x + 3 * i <= 14 && 0 <= y + 3 * j && y + 3 * j <= 14 && (i != 0 || j != 0))
				{
					//if (board[x][y] == 2) { board[x][y] = 1; staticpower = 1; }
					//if (board[x][y] == 1) { board[x][y] = 2; staticpower = 2; }
					if (board[x][y] == board[x + 1 * i][y + 1 * j] && board[x + 1 * i][y + 1 * j] == board[x + 2 * i][y + 2 * j] &&
						board[x + 2 * i][y + 2 * j] == board[x + 3 * i][y + 3 * j]
						&& board[x + 3 * i][y + 3 * j] != 0)
					{
						if (0 <= x + 4 * i && x + 4 * i <= 14 && 0 <= y + 4 * j && y + 4 * j <= 14 && 0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x + 4 * i][y + 4 * j] == 0 && board[x - i][y - i] == 0)   //             活  4         // 下一个只可以是 非staticpower  或者 0
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 2000; }  // 玩家活四后来处理
								if (staticpower == 1) { scoreboard[x][y] += 3000; } // 自己活四优先处理
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 1000;
							}
						}
						else if ((0 <= x + 4 * i && x + 4 * i <= 14 && 0 <= y + 4 * j && y + 4 * j <= 14 && board[x + 4 * i][y + 4 * j] == 0) || (0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x - i][y - i] == 0)) // 死4
						{
							if (role == 1)
							{
								if (staticpower == 2)
								{
									fourplayer_dying++;
									if (fourplayer_dying == 1) { scoreboard[x][y] += 666; }
									else scoreboard[x][y] += 1334;
								}  // 玩家死四后来处理
								if (staticpower == 1)
								{
									fourself_dying++;
									if (fourself_dying == 1) { scoreboard[x][y] += 1000; }
									else scoreboard[x][y] += 2000;
								} // 自己死四优先处理
							}
							//else // 被夹在中间   //没意义
							if (role == -1)
							{
								fourself_dying++;
								if (fourself_dying == 1) { scoreboard[nextx][nexty] -= 200; }
								else scoreboard[nextx][nexty] -= 1000;
							}
						}
					}
				}
			}
			if (flag == 2)
			{
				if (board[x][y] == board[x + 1 * i][y + 1 * j] && board[x + 1 * i][y + 1 * j] == board[x + 2 * i][y + 2 * j] &&
					board[x + 2 * i][y + 2 * j] != 0)
				{
					if (0 <= x + 3 * i && x + 3 * i <= 14 && 0 <= y + 3 * j && y + 3 * j <= 14 && 0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x + 3 * i][y + 3 * j] == 0 && board[x - i][y - i] == 0)  // 活3
					{
						if (role == 1)
						{
							if (staticpower == 2) { scoreboard[x][y] += 500; }  // 玩家活三后来处理
							if (staticpower == 1) { scoreboard[x][y] += 750; } // 自己活三优先处理
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 500;
						}
					}
					if ((0 <= x + 3 * i && x + 3 * i <= 14 && 0 <= y + 3 * j && y + 3 * j <= 14 && board[x + 3 * i][y + 3 * j] == 0) || (0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x - i][y - i] == 0))
					{
						if (role == 1)
						{
							if (staticpower == 2) { scoreboard[x][y] += 84; }  // 玩家死三
							if (staticpower == 1) { scoreboard[x][y] += 125; } // 自己死三
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 50;
						}
					}
				}
			}
			if (flag == 1)
			{
				if (board[x][y] == board[x + 1 * i][y + 1 * j] && board[x + 1 * i][y + 1 * j] != 0)
				{
					if (0 <= x + 2 * i && x + 2 * i <= 14 && 0 <= y + 2 * j && y + 2 * j <= 14 && 0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x + 2 * i][y + 2 * j] == 0 && board[x - i][y - i] == 0)  // 活3
					{
						if (role == 1)
						{
							if (staticpower == 2) { scoreboard[x][y] += 167; }  // 玩家活二后来处理
							if (staticpower == 1) { scoreboard[x][y] += 250; } // 自己活二优先处理
							//living ++;
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 200;
						}
					}
					if ((0 <= x + 2 * i && x + 2 * i <= 14 && 0 <= y + 2 * j && y + 2 * j <= 14 && board[x + 2 * i][y + 2 * j] == 0) || (0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x - i][y - i] == 0))
					{
						if (role == 1)
						{
							if (staticpower == 2) { scoreboard[x][y] += 40; }  // 玩家死二
							if (staticpower == 1) { scoreboard[x][y] += 60; } // 自己死二
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 5;
						}
					}
				}
			}
			if (flag == 0)
			{
				if (board[7][7] == 0) { scoreboard[7][7] = 100; }
				/*if (board[x][y] == board[x + 1 * i][y + 1 * j]  )
				{
					if (0 <= x + 3 * i && x + 3 * i <= 14 && 0 <= y + 3 * j && y + 3 * j <= 14 && 0 <= x - i && x - i <= 14 && 0 <= y - i && y - i <= 14 && board[x + 3 * i][y + 3 * j] == 0 && board[x - i][y - i] == 0)  // 活3
					{
						scoreboard[x][y] += 500;
						//living ++;
					}*/
			}
		}
	}
	return 0;
}
int GobangAI::VOV(int x, int y, int flag, int role)  //夹着它
{
	for (int j = -1; j <= 1; j += 1)
	{
		if (x != 14 && x != 0)
		{
			if (board[x - 1][y - 1 * j] == board[x][y] && board[x][y] == board[x + 1][y + 1 * j])
			{
				int point_xmin = x - 1;
				int point_xmax = x + 1;
				int basic = 2;
				while (--point_xmin >= 0 && 0 <= y - basic * j && y - basic * j <= 14 && basic++)
				{
					if (board[point_xmin][y - basic * j] == board[x][y]);
					else  break;
				}
				point_xmin++;
				basic = 2;
				while (++point_xmax <= 14 && 0 <= y + basic * j && y + basic * j <= 14 && basic++)
				{
					if (board[point_xmax][y + basic * j] == board[x][y]);
					else  break;
				}
				point_xmax--;
				if (point_xmax - point_xmin >= flag)
				{
					if (flag == 4)
					{
						if (role == 1)
						{
							board[x][y] = 0; aidraw(x, y);  return 1;
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 3000;
						}
					}
					if (flag == 3)
					{
						if (0 <= point_xmin - 1 && point_xmax + 1 <= 14 && 0 <= y - (basic + 1) * j && y - (basic + 1) * j <= 14 && 0 <= y + (basic + 1) * j && y + (basic + 1) * j <= 14 && board[point_xmin - 1][y - (basic + 1) * j] == 0 && board[point_xmax + 1][y + (basic + 1) * j] == 0)
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 2000; }  // 玩家活四后来处理
								if (staticpower == 1) { scoreboard[x][y] += 3000; } // 自己活四优先处理
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 1000;
							}
						}
						else if ((0 <= point_xmin - 1 && 0 <= y - (basic + 1) * j && y - (basic + 1) * j <= 14 && board[point_xmin - 1][y - (basic + 1) * j] == 0) || (point_xmax + 1 <= 14 && 0 <= y + (basic + 1) * j && y + (basic + 1) * j <= 14 && board[point_xmax + 1][y + (basic + 1) * j] == 0))
						{
							if (role == 1)
							{
								if (staticpower == 2)
								{
									fourplayer_dying++;
									if (fourplayer_dying == 1) { scoreboard[x][y] += 666; }
									else scoreboard[x][y] += 1334;
								}  // 玩家死四后来处理
								if (staticpower == 1)
								{
									fourself_dying++;
									if (fourself_dying == 1) { scoreboard[x][y] += 1000; }
									else scoreboard[x][y] += 2000;
								} // 自己死四优先处理 
							}
							if (role == -1)
							{
								fourself_dying++;
								if (fourself_dying == 1) { scoreboard[nextx][nexty] -= 200; }
								else scoreboard[nextx][nexty] -= 1000;
							}
						}
					}
					if (flag == 2)
					{
						if (0 <= point_xmin - 1 && point_xmax + 1 <= 14 && 0 <= y - (basic + 1) * j && y - (basic + 1) * j <= 14 && 0 <= y + (basic + 1) * j && y + (basic + 1) * j <= 14 && board[point_xmin - 1][y - (basic + 1) * j] == 0 && board[point_xmax + 1][y + (basic + 1) * j] == 0)
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 500; }  // 玩家活三后来处理
								if (staticpower == 1) { scoreboard[x][y] += 750; } // 自己活三优先处理
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 500;
							}
						}
						else if ((0 <= point_xmin - 1 && 0 <= y - (basic + 1) * j && y - (basic + 1) * j <= 14 && board[point_xmin - 1][y - (basic + 1) * j] == 0) || (point_xmax + 1 <= 14 && 0 <= y + (basic + 1) * j && y + (basic + 1) * j <= 14 && board[point_xmax + 1][y + (basic + 1) * j] == 0))
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 84; }  // 玩家死三
								if (staticpower == 1) { scoreboard[x][y] += 125; } // 自己死三
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 50;
							}
						}
					}
				}
			}
		}
		if (y != 0 && y != 14)
		{
			if (board[x][y - 1] == board[x][y] && board[x][y] == board[x][y + 1])
			{
				int point_ymin = y - 1;
				int point_ymax = y + 1;
				while (--point_ymin >= 0)
				{
					if (board[x][point_ymin] == board[x][y]);
					else  break;
				}
				point_ymin++;
				while (++point_ymax <= 14)
				{
					if (board[x][point_ymax] == board[x][y]);
					else  break;
				}
				point_ymax--;
				if (point_ymax - point_ymin >= flag)
				{
					if (flag == 4)
					{
						if (role == 1)
						{
							board[x][y] = 0; aidraw(x, y);  return 1;
						}
						if (role == -1)
						{
							scoreboard[nextx][nexty] -= 3000;
						}
					}
					if (flag == 3)
					{
						if (point_ymin - 1 >= 0 && board[x][point_ymin - 1] == 0 && point_ymax + 1 <= 14 && board[x][point_ymax + 1] == 0)   // 未出界 // 且为空  // 活4
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 2000; }
								if (staticpower == 1) { scoreboard[x][y] += 3000; }
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 1000;
							}
						}
						else if ((point_ymin - 1 >= 0 && board[x][point_ymin - 1] == 0) || (point_ymax + 1 <= 14 && board[x][point_ymax + 1] == 0))
						{
							if (role == 1)
							{
								if (staticpower == 2)
								{
									fourself_dying++;
									if (fourself_dying == 1) { scoreboard[x][y] += 666; }
									else scoreboard[x][y] += 1334;
								}
								if (staticpower == 1)
								{
									fourself_dying++;
									if (fourself_dying == 1) { scoreboard[x][y] += 1000; }
									else scoreboard[x][y] += 2000;
								}
							}
							if (role == -1)
							{
								fourself_dying++;
								if (fourself_dying == 1) { scoreboard[nextx][nexty] -= 200; }
								else scoreboard[nextx][nexty] -= 1000;
							}
						}
					}
					if (flag == 2)
					{
						if (point_ymin - 1 >= 0 && board[x][point_ymin - 1] == 0 && point_ymax + 1 <= 14 && board[x][point_ymax + 1] == 0)   // 未出界 // 且为空  // 活4
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 500; }  // 玩家活三后来处理
								if (staticpower == 1) { scoreboard[x][y] += 750; } // 自己活三优先处理
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 500;
							}
							/*								if (role == -1)
															{
																fourself_dying++;
																if (fourself_dying == 1) { scoreboard[nextx][nexty] -= 200; }
																else scoreboard[nextx][nexty] -= 1000;
															}
															*/
						}
						else if ((point_ymin - 1 >= 0 && board[x][point_ymin - 1] == 0) || (point_ymax + 1 <= 14 && board[x][point_ymax + 1] == 0))
						{
							if (role == 1)
							{
								if (staticpower == 2) { scoreboard[x][y] += 84; }  // 玩家死三
								if (staticpower == 1) { scoreboard[x][y] += 125; } // 自己死三
							}
							if (role == -1)
							{
								scoreboard[nextx][nexty] -= 50;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
int GobangAI::AIjudge(int x, int y, int role) // role 控制加减 
{
	int num = 2; // 八个方向检查
	if (role == -1) num = 1;
	if (maxx - minx >= 3 || maxy - miny >= 3)   //五连 则不做后续步骤
	{
		for (; num > 0; num--)
		{
			if (num % 2 == 0) staticpower = 1;
			else staticpower = 2;
			board[x][y] = staticpower;
			if (LE(x, y, 4, role)) { return 1; }
			if (VOV(x, y, 4, role)) { return 1; }
		}
	}
	for (num = 2; num > 0; num--)
	{
		fourself_dying = 0;
		fourplayer_dying = 0;
		if (num % 2 == 0) staticpower = 1;
		else staticpower = 2;
		board[x][y] = staticpower;
		if (maxx - minx >= 2 || maxy - miny >= 2)
		{
			LE(x, y, 3, role);
			VOV(x, y, 3, role);
		}
		if (maxx - minx >= 1 || maxy - miny >= 1)
		{
			LE(x, y, 2, role);
			VOV(x, y, 2, role);
		}
		for (int flag = 1; flag >= 0; flag--)
		{
			LE(x, y, flag, role);
		}
	}
	return 0;
}
void GobangAI::checkscore() //  找出最大值和  全部化0 同时进行
{
	int xi = minx; int xa = maxx; int yi = miny; int ya = maxy;  int temp; int bigx[SIZE]; int bigy[SIZE]; int i = 0; int tem = i;
	if (xi > 0) xi--; if (xa < 14) xa++; if (yi > 0) yi--; if (ya < 14) ya++;  // 扩大一格
	maxscorex = xi; maxscorey = yi;
	temp = yi;
	for (int num = 0; num < 15; num++) { bigx[num] = -1; bigy[num] = -1; }   // 初始化为   -1  
	for (; xi <= xa; xi++)
	{
		for (yi = temp; yi <= ya; yi++)
		{
			if (scoreboard[maxscorex][maxscorey] < scoreboard[xi][yi])
			{
				i = 0;
				maxscorex = xi;
				maxscorey = yi;
				for (int num = 0; num < SIZE; num++) { bigx[num] = -1; bigy[num] = -1; }
			}
			if ((scoreboard[maxscorex][maxscorey] == scoreboard[xi][yi]) && i < SIZE)
			{
				bigx[i] = xi;
				bigy[i] = yi;
				i++;
			}
		}
	}
	if (i > 0)
	{
		int cou = 0;
		nextx = maxscorex;
		nexty = maxscorey;
		for (; i >= 0; )
		{
			next(nextx, nexty);
			if (cou >= 1 && cou < SIZE)
			{
				if (scoreboard[maxscorex][maxscorey] < scoreboard[nextx][nexty]) { maxscorex = nextx; maxscorey = nexty; }
			}
			i--;
			if (i >= 0 && cou < SIZE)
			{
				nextx = bigx[i];
				nexty = bigy[i];
				cou++;
			}
		}
	}
	aidraw(maxscorex, maxscorey);
	initial();
}
int GobangAI::choose(int role)  //用极大极小值法
{
	if (Gofirst == 1 && AIturn == 0) { aidraw(7, 7); }
	else
	{
		int xi = minx; int xa = maxx; int yi = miny; int ya = maxy;  int temp;
		if (xi > 0) xi--; if (xa < 14) xa++; if (yi > 0) yi--; if (ya < 14) ya++;  // 扩大一格
		temp = yi;
		for (; xi <= xa; xi++)                               //发射棋子
		{
			for (yi = temp; yi <= ya; yi++)   //遍历数组
			{
				if (board[xi][yi] == 0)
				{
					if (AIjudge(xi, yi, role))
					{
						initial();
						return 0;
					}   //  五连 直接退出
					else board[xi][yi] = 0;
				}
			}
		}
		if (role == 1)checkscore();
	}
	return 0;
}
void GobangAI::next(int x, int y)
{
	int tempmaxx = maxx; int tempmaxy = maxy;
	mmcompare(x, y);
	board[x][y] = 1;
	choose(-1);
	board[x][y] = 0;
	maxx = tempmaxx; maxy = tempmaxy;
}
void GobangAI::withdraw()
{
	if (AIturn > 0)
	{
		AIturn--; int fake_AIturn = AIturn + 1; int x; int y;
		//board[AIhist[2 * AIturn]][AIhist[2 * AIturn + 1]] = 0;
		ifstream AIreader("AIchessboard.txt");
		if (AIreader.is_open())
		{
			while (fake_AIturn--)
			{
				AIreader >> x >> y;
			}
			cout << x << "    " << y << endl;
			board[x][y] = 0;
			AIreader.close();
		}
		else cout << "error" << endl;
	}
}

void GobangAI::goforward()
{
	if (AIturn < maxAIturn)
	{
		AIturn++; int fake_AIturn = AIturn; int x; int y;
		//board[AIhist[2 * AIturn]][AIhist[2 * AIturn + 1]] = 0;
		ifstream AIreader("AIchessboard.txt");
		if (AIreader.is_open())
		{
			while (fake_AIturn--)
			{
				AIreader >> x >> y;
			}
			//	cout << x << "    " << y << endl;
			board[x][y] = AIpower;
			AIreader.close();
		}
		else cout << "error" << endl;
	}
}
int GobangAI::power()
{
	return AIpower;
}
void GobangAI::freshstatic() { AIturn = 0; maxAIturn = 0; }
int GobangAI::Aiturn() { return AIturn; }