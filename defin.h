#pragma once
#ifndef _DEFIN_H_
#define _DEFIN_H_
#include<opencv2/opencv.hpp>
using namespace cv; 

#define BLUE  Scalar(255,140,0)
#define BLACK Scalar (0,0,0)//scalar ΪBGR 
#define WHITE Scalar(255,255,255,100)
#define RED Scalar(38 ,38,205)
constexpr auto SIZE =15;

extern int Gametype;//��¼��Ϸ����
extern int Gofirst;//��¼����״̬
extern int finish ;//���ڵ���һ����ʤʱ����ֹѭ��
extern int board[SIZE][SIZE]; //AI Ϊ1�� player Ϊ2
//extern int playerhist[SIZE * 2] ;
//extern int AIhist[SIZE * 2];
extern  int maxx , maxy; //��¼���� ���ٱ�������
extern int minx , miny ;   // ��¼���Ӽ��ٱ�������
extern int playerpoint ;   // ���������  ���ڹ۲�����Ƿ����� ����� ��AI����
extern const char* imagename ;//���̱������� xxx.jpg
extern Mat picture;
extern int zuo[48] ;//   ��ͼƬ��xy���ؾ��ȷֲ��������У����ڲ�������
extern int  xia[36]; // 36 ---->>   2x + 4           __________    1 4 --->>  x 
void mmcompare(int x, int y);//��maxx��maxy��minx��miny�������ӵ�x��y��С���иĽ����Ӷ���ֹ��©ĳһ��λ��
int PvE();//�˻���սģʽ
int PvP();//˫�˲���
#endif // !_DEFIN_H_
