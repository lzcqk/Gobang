#include"defin.h"
#include"GobangAI.h"
#include"GobangJudge.h"
#include"GobangMAKE.h"
#include"GobangPlayer.h"

int Gametype = -1;
int Gofirst = -1;
int finish = 1;
int board[SIZE][SIZE] = { 0 }; //AI Ϊ1�� player Ϊ2
//int playerhist[SIZE * 2] = { 0 };
//int AIhist[SIZE * 2] = { 0 };
int maxx = 0, maxy = 0; //��¼���� ���ٱ�������
int minx = 14, miny = 14;   // ��¼���Ӽ��ٱ�������
int playerpoint = 0;   // ���������  ���ڹ۲�����Ƿ����� ����� ��AI����
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
		//imshow("������", picture);
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
		if (waitKey(20) == 27 || getWindowProperty("Gobang", WND_PROP_AUTOSIZE) == -1) { break; } // getWindowProperty() ���ָ�����ڱ��ر� return -1
	}
	return 0;
}


int PvP()
{
	int mainpower = 0;
	GobangMAKE realboard;
	realboard.make_board();
	GobangPlayer  plaone;
	GobangPlayer platwo(1);  //player 2��Ȩ��Ϊ1
	GobangJudge xiaowang;
	while (1)
	{
		imshow("Gobang", picture);
		//imshow("������", picture);
		if (playerpoint == 0 && finish == 1)
		{
			plaone.Initial();
			imshow("Gobang", picture);
			mainpower = xiaowang.bjudge(board, plaone.power());  //����
			finish = xiaowang.claim(mainpower, 1);
			imshow("Gobang", picture);
		}
		if (playerpoint==1 && finish == 1)
		{ 
			platwo.Initial();
			imshow("Gobang", picture);
			mainpower = xiaowang.bjudge(board, platwo.power());  //����
			finish = xiaowang.claim(mainpower, 1);
			imshow("Gobang", picture);
		}
		if (waitKey(20) == 27 || getWindowProperty("Gobang", WND_PROP_AUTOSIZE) == -1) { break; } // getWindowProperty() ���ָ�����ڱ��ر� return -1
	}
	return 0;
}