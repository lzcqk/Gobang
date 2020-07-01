#include"defin.h"
#include"GobangAI.h"
#include"GobangJudge.h"
#include"GobangMAKE.h"
#include"GobangPlayer.h"

int Gametype = -1;
int Gofirst = -1;
int finish = 1;
int board[SIZE][SIZE] = { 0 }; //AI 为1， player 为2
//int playerhist[SIZE * 2] = { 0 };
//int AIhist[SIZE * 2] = { 0 };
int maxx = 0, maxy = 0; //记录格子 减少遍历次数
int minx = 14, miny = 14;   // 记录格子减少遍历次数
int playerpoint = 0;   // 玩家落子数  用于观察玩家是否落子 如果是 则AI落子
const char* imagename = "Gobang.jpg";
Mat picture = imread(imagename);
int zuo[48] = { 0 };
int  xia[36] = { 0 }; // 36 ---->>   2x + 4           __________    1 4 --->>  x 
void mmcompare(int x, int y)
{
	if (x >= maxx) maxx = x;
	if (x <= minx) minx = x;
	if (y >= maxy) maxy = y;
	if (y <= miny) miny = y;
}

int PvE()
{
	int mainpower = 0;
	GobangMAKE realboard;
	realboard.make_board();
	GobangPlayer  pla;
	GobangAI aape;
	GobangJudge xiaowang;
	while (1)
	{
		imshow("Gobang", picture);
		//imshow("五子棋", picture);
	     pla.Initial();
		if (playerpoint ==1)
		{
			imshow("Gobang", picture);
			mainpower = xiaowang.bjudge(board, pla.power());
			finish = xiaowang.claim(mainpower);
			imshow("Gobang", picture);
			playerpoint = 0;
			if (finish == 1)
			{
				aape.choose(1);
				imshow("Gobang", picture);
				mainpower = xiaowang.bjudge(board, aape.power());
				finish = xiaowang.claim(mainpower);
				imshow("Gobang", picture);
			}
		}
		if (waitKey(20) == 27 || getWindowProperty("Gobang", WND_PROP_AUTOSIZE) == -1) { break; } // getWindowProperty() 如果指定窗口被关闭 return -1
	}
	return 0;
}


int PvP()
{
	int mainpower = 0;
	GobangMAKE realboard;
	realboard.make_board();
	GobangPlayer  plaone;
	GobangPlayer platwo(1);  //player 2的权重为1
	GobangJudge xiaowang;
	while (1)
	{
		imshow("Gobang", picture);
		//imshow("五子棋", picture);
		if (playerpoint == 0 && finish == 1)
		{
			plaone.Initial();
			imshow("Gobang", picture);
			mainpower = xiaowang.bjudge(board, plaone.power());  //白棋
			finish = xiaowang.claim(mainpower, 1);
			imshow("Gobang", picture);
		}
		if (playerpoint==1 && finish == 1)
		{ 
			platwo.Initial();
			imshow("Gobang", picture);
			mainpower = xiaowang.bjudge(board, platwo.power());  //黑棋
			finish = xiaowang.claim(mainpower, 1);
			imshow("Gobang", picture);
		}
		if (waitKey(20) == 27 || getWindowProperty("Gobang", WND_PROP_AUTOSIZE) == -1) { break; } // getWindowProperty() 如果指定窗口被关闭 return -1
	}
	return 0;
}