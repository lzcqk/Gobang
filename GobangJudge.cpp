#include "GobangJudge.h"
#include"defin.h"

int GobangJudge::bjudge(int a[][SIZE], int power)
{
	if (maxx - minx >= 4 || maxy - miny >= 4)
	{
		for (int x = minx; x <= maxx; x++) //    ||||||||||||  ����������   ���Ϊmin   min
		{
			for (int y = miny; y + 4 <= maxy; y++)
			{
				if (a[x][y] == a[x][y + 1] && a[x][y + 1] == a[x][y + 2] && a[x][y + 2] == a[x][y + 3] && a[x][y + 3] == a[x][y + 4] && a[x][y] != 0) return power;
			}
		}
		for (int y = miny; y <= maxy; y++) //    -------- ����������       ���Ϊ  min      min
		{
			for (int x = minx; x + 4 <= maxx; x++)
			{
				if (a[x][y] == a[x + 1][y] && a[x + 1][y] == a[x + 2][y] && a[x + 2][y] == a[x + 3][y] && a[x + 3][y] == a[x + 4][y] && a[x][y] != 0) return power;
			}
		}
		int x = minx;
		int y = maxy;
		int count = 1;
		int xtemp = 0;
		int ytemp = 0;
		for (; x + 5 > 15; x--);//  û�г�������
		xtemp = x;
		for (; y + 5 > 15; y--);
		for (; y + 4 > miny; y--, count++) //    �Խ������� \\\\\\\\\\\\\  ����   /
		{
			ytemp = y;
			int i = 0;
			while (count - i)
			{
				if (i != 0) { x++;   y++; }
				if (a[x][y] == a[x + 1][y + 1] && a[x + 1][y + 1] == a[x + 2][y + 2] && a[x + 2][y + 2] == a[x + 3][y + 3] && a[x + 3][y + 3] == a[x + 4][y + 4] && a[x][y] != 0) return power;
				i++;
			}
			y = ytemp; x = xtemp;
		}
		ytemp = y;
		for (; x + 4 <= maxx; x++, count--) //    �Խ������� \\\\\\\\\\\\\  ���ұ�   /
		{
			xtemp = x;
			int i = 0;
			while (count - i)
			{
				if (i != 0) { x++;   y++; }
				if (a[x][y] == a[x + 1][y + 1] && a[x + 1][y + 1] == a[x + 2][y + 2] && a[x + 2][y + 2] == a[x + 3][y + 3] && a[x + 3][y + 3] == a[x + 4][y + 4] && a[x][y] != 0) return power;
				i++;
			}
			x = xtemp; y = ytemp;
		}
		count = 1;
		x = maxx;
		y = maxy;
		xtemp = x;
		for (; y + 5 > 15; y--);
		for (; y + 4 > miny; y--, count++) //    �Խ�������//////////// ����   
		{
			ytemp = y;
			int i = 0;
			while (count - i)
			{
				if (i != 0) { x--;   y++; }
				if (a[x][y] == a[x - 1][y + 1] && a[x - 1][y + 1] == a[x - 2][y + 2] && a[x - 2][y + 2] == a[x - 3][y + 3] && a[x - 3][y + 3] == a[x - 4][y + 4] && a[x][y] != 0) return power;
				i++;
			}
			y = ytemp; x = xtemp;
		}
		ytemp = y;
		for (; x > minx + 3; x--, count--) //    �Խ������� ///////////  ����////
		{
			xtemp = x;
			int i = 0;
			while (count - i)
			{
				if (i != 0) { x--;   y++; }
				if (a[x][y] == a[x - 1][y + 1] && a[x - 1][y + 1] == a[x - 2][y + 2] && a[x - 2][y + 2] == a[x - 3][y + 3] && a[x - 3][y + 3] == a[x - 4][y + 4] && a[x][y] != 0) return power;
				i++;
			}
			x = xtemp; y = ytemp;
		}
	}
	return 0;
}
int GobangJudge::claim(int power,int flag)  // ��һ��ʤ�� ����1     break ��while
{
	if (power == 1 && flag == 2 )
	{
		string text = "AI win";
		Text(text);
		return 0;
	}
	if (power == 2 && flag == 2)
	{
		string text = "You win";
		Text(text);
		return 0;
	}
	if (power == 1 && flag == 1)
	{
		string text = "W_Player win";
		Text(text);
		return 0;
	}
	if (power == 2 && flag == 1)
	{
		string text = "B_Player win";
		Text(text);
		return 0;
	}
	return 1;
}
void GobangJudge::Text(string text)
{
	int font_face = FONT_HERSHEY_COMPLEX;
	double font_scale = 2;
	int thickness = 2;
	int baseline;

	Size text_size = getTextSize(text, font_face, font_scale, thickness, &baseline);     //��ȡ�ı���ĳ���
	Point origin;
	origin.x = picture.cols / 2 - text_size.width / 2;
	origin.y = picture.rows / 2 + text_size.height / 2;            //���ı�����л���
	putText(picture, text, origin, font_face, font_scale, BLUE, thickness, 8, 0);
}