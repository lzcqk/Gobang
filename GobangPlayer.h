#pragma once
#ifndef _GOBANGPLAYER_H_
#define _GOBANGPLAYER_H_
#include"defin.h"
#include"GobangAI.h"
#include "GobangMAKE.h"
class GobangPlayer
{
	private:
		int playerpower;//��¼��ҵ�Ȩ��
		static int turn;//��¼��ҵ�ǰ�������µĲ���
		static int maxturn;//��¼���ȫ�����ӵĴ���
	public:
		GobangMAKE assist;
		GobangAI oumiga;
		GobangPlayer(int flag = 2 );//��ʼ������PVPʱ�����⴦��
		void on_Mouse(int event, int x, int y);//����¼�
		void withdraw();//�������
		void goforward();//�����������
		void one_more();//����һ�̲���
		void save();//������ֲ���
		int rewrite();//��������̲���
		static void onMouse(int event, int x, int y, int, void* userdata)
		{
			GobangPlayer* temp = reinterpret_cast<GobangPlayer*>(userdata);
			temp->on_Mouse(event, x, y);
		}
		void Initial();//����¼����
		int power();//�������Ȩ��
		void freshstatic();//��turn��Maxturnȫ����0

};

#endif // !_GOBANGPLAYER_H_

