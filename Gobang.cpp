#include<iostream>
#include<opencv2/opencv.hpp>
#include"defin.h"
#include "GobangPlayer.h"

using namespace std;
using namespace cv;

int main()
{
	namedWindow("Gobang");
	//namedWindow("五子棋");
	if (picture.empty())
	{
		cout << "lose the picture" << endl;
		return -1;
	}
	cout << "Please choose PVE or PVP , then choose P/W or E/B." << endl;
	GobangPlayer  pla;
	GobangMAKE realboard;
	realboard.make_board();
	imshow("Gobang", picture);
	while (Gametype == -1 || Gofirst == -1) { pla.Initial();if (waitKey(20) == 27 || getWindowProperty("Gobang", WND_PROP_AUTOSIZE) == -1) { break; } }
	playerpoint = Gofirst;
	if (Gametype == 1) { PvE(); }
	if (Gametype == 2) { PvP(); }
	return 0;
}