#pragma once
#ifndef _GOBANGJUDGE_H_
#define _GOBANGJUDGE_H_
#include<iostream>
#include"defin.h"
using namespace std;
class GobangJudge
{
	public:
		int bjudge(int a[][SIZE], int power);  //����Ƿ���һ����һ��ʤ��
		int claim(int power,int flag = 2);  // ��һ��ʤ�� ����1     break ��while     //�����������������������Text����
		void Text(string text);  //��text��ӡ��������
};
#endif // !_GOBANGJUDGE_H_



