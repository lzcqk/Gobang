#include "GobangPlayer.h"
#include"defin.h"
#include"GobangMAKE.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<fstream>

using namespace std;
using namespace cv;


GobangPlayer::GobangPlayer(int flag)
{
	ofstream cling("playerchessboard.txt", ios::trunc);
	cling.close();
	playerpower = flag;
}
int GobangPlayer::turn = 0;
int GobangPlayer::maxturn = 0;
void GobangPlayer::freshstatic() { turn = 0; maxturn = 0; }
void GobangPlayer::on_Mouse(int event, int x, int y)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (zuo[2] < x && x < zuo[34] && xia[2] < y && y < xia[34] && finish && Gofirst != -1 && Gametype != -1)
		{
			int xcount = 0;
			int ycount = 0;
			int fx = 0; //标记是否在线上
			int fy = 0;
			for (xcount = 0; xcount < SIZE; xcount++)
			{
				if (zuo[xcount * 2 + 3] < x && x < zuo[xcount * 2 + 5])
				{
					x = zuo[xcount * 2 + 4];
					fx = 1;
					break;
				}
			}
			for (ycount = 0; ycount < SIZE; ycount++)
			{
				if (xia[ycount * 2 + 3] < y && y < zuo[ycount * 2 + 5])
				{
					y = zuo[ycount * 2 + 4];
					fy = 1;
					break;
				}
			}
			if (fx && fy)
			{
				if (board[xcount][ycount] == 0)  //如果没人下过此处
				{
					if (playerpower == 2)circle(picture, Point(x, y), 8, WHITE, -1);
					if (playerpower == 1)circle(picture, Point(x, y), 8, BLACK, -1);
					board[xcount][ycount] = playerpower;
					ofstream writer("playerchessboard.txt", ios::in);
					if (writer.is_open())
					{
						writer.seekp(int(turn * 6), ios::beg);
						if (xcount >= 10) { writer << xcount; }
						else writer << "0" << xcount;
						writer << " ";
						if (ycount >= 10) { writer << ycount; }
						else writer << "0" << ycount;
						writer << " ";
						writer.close();
					}
					//playerhist[2 * turn] = xcount;
					//playerhist[2 * turn + 1] = ycount;
					if (turn == maxturn) maxturn++;
					turn++;
					if (turn+oumiga.Aiturn() == SIZE * SIZE) { finish = 0; cout<<"Board has been filled!!"<<endl;}
					mmcompare(xcount, ycount);
					if (playerpower == 2)playerpoint = 1;
					if (playerpower == 1)playerpoint = 0;
				}
			}
		}
		else if (zuo[36] < x && x < zuo[40] && xia[4] < y && y < xia[7]) { cout << "PvP" << endl; Gametype = 2; }  // 2 是pvp
		else if (zuo[42] < x && x < zuo[46] && xia[4] < y && y < xia[7]) { cout << "PvE" << endl; Gametype = 1; }  // 1是pve
		else if (zuo[36] < x && x < zuo[40] && xia[8] < y && y < xia[12]) { cout << "Withdraw" << endl; withdraw(); } // 悔棋
		else if (zuo[42] < x && x < zuo[46] && xia[8] < y && y < xia[12]) { cout << "Forward" << endl; goforward(); } 
		else if (zuo[36] < x && x < zuo[46] && xia[14] < y && y < xia[17]) { cout << "Save " << endl; save(); }
		else if (zuo[36] < x && x < zuo[46] && xia[19] < y && y < xia[22]) { cout << "Load" << endl; rewrite(); }
		else if (zuo[36] < x && x < zuo[46] && xia[24] < y && y < xia[28]) { cout << "Replay" << endl; one_more(); } //再来一局
		else if (zuo[36] < x && x < zuo[40] && xia[29] < y && y < xia[32]) { cout << "P/W" << endl; Gofirst = 0; } //0是白棋先手
		else if (zuo[42] < x && x < zuo[46] && xia[29] < y && y < xia[32]) { cout << "E/B" << endl; Gofirst = 1; } // 1是黑棋先手
		else { cout << "unavailable" << endl; } //测试 后期删去
		/*Mat dst;
		cvtColor(picture, dst, COLOR_BGR2HSV);
		uchar* data1 = dst.ptr<uchar>(y);
		int hval = data1[int(x) * 3];
		int sval = data1[int(x ) * 3 + 1];
		int vval = data1[int(x ) * 3 + 2];
		cout << x << " " << y << endl;
		printf("H:%d\tS:%d\tV:%d\n", hval, sval, vval);*/
	}
}
void GobangPlayer::withdraw()
{
	if (turn > 0)
	{
		turn--; int fake_turn = turn + 1; int x; int y;
		//board[playerhist[2 * turn]][playerhist[2 * turn + 1]] = 0;
		ifstream reader("playerchessboard.txt");
		if (reader.is_open())
		{
			while (fake_turn--)
			{
				reader >> x >> y;
			}
			//cout << x << "    " << y << endl;
			board[x][y] = 0;
			reader.close();
		}
		else cout << "error" << endl;
		oumiga.withdraw();
		picture = imread(imagename);
		assist.make_board();
		assist.refresh();
	}
}
void GobangPlayer::goforward() 
{
	if (turn < maxturn)
	{
		turn++;  int fake_turn = turn ; int x; int y;
		ifstream reader("playerchessboard.txt");
		if (reader.is_open())
		{
			while (fake_turn--)
			{
				reader >> x >> y;
			}
			board[x][y] = playerpower;
			reader.close();
		}
		else cout << "error" << endl;
		oumiga.goforward();
		picture = imread(imagename);
		assist.make_board();
		assist.refresh();
	}
}
void GobangPlayer::one_more()
{
	assist.board_initial();finish = 1; playerpoint = Gofirst; oumiga.freshstatic(); freshstatic();
	ofstream cling("playerchessboard.txt", ios::trunc);
	cling.close();
	ofstream AIcling("AIchessboard.txt", ios::trunc);
	AIcling.close();
	picture = imread(imagename);
	assist.make_board();
}
void GobangPlayer::save()
{
	imwrite("Save_chess.jpg", picture);
}

int  GobangPlayer::rewrite()
{
	one_more();
	Mat old_chess = imread("Save_chess.jpg");
	if (old_chess.empty())
	{
		cout << "You haven't saved the chess manual before" << endl;
		return -1;
	}
	//picture = old_chess;
	Mat dst; int Blackchess = 0; int Whitechess = 0;
	cvtColor(old_chess, dst, COLOR_BGR2HSV);
	for (int y = 0; y < 15; y++)
	{
		uchar* data1 = dst.ptr<uchar>(xia[2 * y + 4] + 1);
		for (int x = 0; x < 15; x++)
		{
			int hval = data1[int((zuo[2 * x + 4] + 1) * 3)];
			int sval = data1[int((zuo[2 * x + 4] + 1) * 3) + 1];
			int vval = data1[int((zuo[2 * x + 4] + 1) * 3) + 2];
			/*if (x == 6 && y == 7) { cout << hval << "====" << sval << "=====" << vval << endl; //circle(picture, Point(zuo[2 * x + 4], xia[2 * y + 4]), 8,RED, -1);
			}*/
			//if (x == 6 && y == 6) cout << hval << "====" << sval << "=====" << vval << endl;
			if (180 >= hval && hval >= 0 && 255 >= sval && sval >= 0 && 46 >= vval && vval >= 0) { board[x][y] = 1; Blackchess++; mmcompare(x, y); }  //黑色棋子
			if (160 >= hval && hval >= 0 && 10 >= sval && sval >= 0 && vval <= 255 && vval >= 240) { board[x][y] = 2; Whitechess++; mmcompare(x, y); } //白色棋子
		}
	}
	/*
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			cout << board[x][y];
		}
		cout << endl;
	}
	*/
	if (Blackchess == Whitechess) playerpoint = Gofirst;
	else if ((Gametype == 1) && (Blackchess == Whitechess - 1 )) playerpoint = 0;
	else if ((Gametype == 2) && (Blackchess == Whitechess - 1)) playerpoint = 1;
	else if ((Gametype == 1) && (Blackchess == Whitechess + 1)) playerpoint = 1;
	else if ((Gametype == 2) && (Blackchess == Whitechess + 1)) playerpoint = 0;
	else { finish = 0; playerpoint = 2; cout << "Cheating chess" << endl; }  //偷棋 
	picture = imread(imagename);
	assist.make_board();
	assist.refresh();
	return 0;
}
void GobangPlayer::Initial()
{
	setMouseCallback("Gobang", onMouse, this);
}
int GobangPlayer::power() { return playerpower; }
