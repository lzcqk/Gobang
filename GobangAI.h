#pragma once
#ifndef _GOBANGAI_H_
#define _GOBANGAI_H_
#include"defin.h"
class GobangAI
{
	private:
		int AIpower ;//ai����������ӵ�е�Ȩ�أ���������������
		int scoreboard[SIZE][SIZE] ;//��¼��λ���������ai��ѡ��һ�����ŵ�λ��
		int staticpower ;  // ������ʲô����
		int nextx;//���ڵڶ�����������
		int nexty ;
		int fourself_dying;//������������ʱΪ��ʤ�壬������Ҫ���⴦��
		int fourplayer_dying ;
		int maxscorex;//���ڵڶ�����������ʱ�Ƚ����÷�ʱ���洢x
		int maxscorey;//���ڵڶ�����������ʱ�Ƚ����÷�ʱ���洢y
		static int AIturn;//���ڼ�¼AI�ĵ�ǰ�����е������������ڻ���ȶ������
		static int maxAIturn;//���ڼ�¼AIһ�����ӵĴ���
	public:
		GobangAI();//��ʼ��
		void initial();//���ڳ�ʼ��scoreboard������ȫ��������Ϊ0�������´�����
		void aidraw(int x, int  y);//��AI��ѡ��λ��滭��������
		int LE(int x, int y, int flag, int role);//����ģ��������������������ĩ�����     eg��ģ�����ӣ�X  ԭ������ΪO         OOOOX
		int VOV(int x, int y, int flag, int role);//����ģ������������������֮������  eg��ģ�����ӣ�X  ԭ������ΪO          OXOOOO
		int AIjudge(int x, int y, int role); // role ���ƼӼ�        //ģ��������ȥ��������
		void checkscore();//�����п������ӵ�scoreboardλ�ã�Ѱ�����ĵ÷�λ�㣬�����
		int choose(int );//AIѡ�����ӵ���ڣ������ų��������Ѿ����ӵ�λ�ã���δ���ӵ�λ�ý���AIjudge����
		void next(int x, int y);//����ģ������
		void withdraw();//�������
		void goforward();//�����������
		int power();//����AI��AIpower������AI��Ȩ�أ�
		void freshstatic();//��AIturn��AImaxturn��0���������¿�ʼ��Ϸ�Ȳ���
		int Aiturn();//����AIturn��ֵ�����ڻ���Ȳ���
};


#endif // !_GOBANGAI_H_

