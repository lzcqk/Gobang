#include "GobangMAKE.h"
#include"defin.h"

GobangMAKE::GobangMAKE() 
{
	n = 0;
}
void GobangMAKE::make_board()
{
	for (int i = 0; i < 48; i++) { zuo[i] = picture.cols / 48 * (i); }
	for (int i = 0; i < 36; i++) { xia[i] = picture.rows / 36 * (i); }
	for (int x = 1; x < 18; x++)
	{
		n = x * 2;
		if (x == 1 || x == 17)
		{
			line(picture, Point(zuo[n], xia[2]), Point(zuo[n], xia[34]), BLACK, 4);
			line(picture, Point(zuo[2], xia[n]), Point(zuo[34], xia[n]), BLACK, 4);
		}
		else
		{
			line(picture, Point(zuo[n], xia[2]), Point(zuo[n], xia[34]), BLACK);
			line(picture, Point(zuo[2], xia[n]), Point(zuo[34], xia[n]), BLACK);
		}
	}
	//Rect rect(zuo[40], xia[30], 100, 100);
	int FONT = FONT_HERSHEY_TRIPLEX;
	rectangle(picture, Point(zuo[36], xia[4]), Point(zuo[40], xia[7]), RED, 2, 8, 0);
	putText(picture, "PvP", Point(zuo[36]+5, xia[7]-12), FONT, 0.8, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[42], xia[4]), Point(zuo[46], xia[7]), RED, 2, 8, 0);
	putText(picture, "PvE", Point(zuo[42] + 5, xia[7] - 12), FONT, 0.8, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[36], xia[8]), Point(zuo[40], xia[12]), RED, 2, 8, 0);
	putText(picture, "with", Point(zuo[36] + 3, xia[12] -35), FONT, 0.7, Scalar(0, 0, 255), 2);
	putText(picture, "draw", Point(zuo[36] + 3, xia[12] - 10), FONT, 0.7, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[42], xia[8]), Point(zuo[46], xia[12]), RED, 2, 8, 0);
	putText(picture, "for", Point(zuo[42] + 10, xia[12] - 35), FONT, 0.7, Scalar(0, 0, 255), 2);
	putText(picture, "ward", Point(zuo[42] + 3, xia[12] - 10), FONT, 0.7, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[36], xia[14]), Point(zuo[46], xia[17]), RED, 2, 8, 0);
	putText(picture, "Save", Point(zuo[36] + 40, xia[17] - 15), FONT, 0.8, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[36], xia[19]), Point(zuo[46], xia[22]), RED, 2, 8, 0);
	putText(picture, "Load", Point(zuo[36] + 40, xia[22] - 15), FONT, 0.8, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[36], xia[24]), Point(zuo[46], xia[28]), RED, 2, 8, 0);
	putText(picture, "Replay", Point(zuo[36] + 30, xia[28] - 20), FONT, 0.8, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[36], xia[29]), Point(zuo[40], xia[32]), RED, 2, 8, 0);
	putText(picture, "P/W", Point(zuo[36] + 5, xia[32] - 12), FONT, 0.7, Scalar(0, 0, 255), 2);
	rectangle(picture, Point(zuo[42], xia[29]), Point(zuo[46], xia[32]), RED, 2, 8, 0);
	putText(picture, "E/B", Point(zuo[42] + 5, xia[32] - 12), FONT, 0.8, Scalar(0, 0, 255), 2);
}
void GobangMAKE::board_initial()
{
	int x = 0;
	int y = 0;
	maxx = 0; maxy = 0; minx = 14 ; miny = 14;
	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++)
		{
			board[x][y] = 0;
		}
	}
}
void GobangMAKE::refresh()
{
	int xa = maxx; int xi = minx; int ya = maxy; int yi = miny;
	for (; xi <= xa; xi++)
	{
		for (yi = miny; yi <= ya; yi++)
		{
			if (board[xi][yi] == 1) circle(picture, Point(zuo[2 * xi + 4], xia[2 * yi + 4]), 8, BLACK, -1);
			if (board[xi][yi] == 2) circle(picture, Point(zuo[2 * xi + 4], xia[2 * yi + 4]), 8, WHITE, -1);
		}
	}
}