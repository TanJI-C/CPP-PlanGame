#include"Update.h"
#include"SS.h"
#include"PG.h"
#include<stdlib.h>
#include<time.h>
/*
��ʾ����ĺ����Ĺ���
	��ʾ��ʼ����{��������������ѡ�����}��ѡ���ܡ�
	��Ϸģʽ����{�����������}
	���ý���{���ý��溯��}��ѡ���ܺͷ��ع��ܡ�
	��ʼ���������ݸ�Update
��ʼ��������
	ʹ��һ�ö���趨����ѡ��
���û���صĺ�����
	�������ͼ���Ӧ�Ĵ��������������
���û��޹صĺ�����
	�ٶȿ��Ʊ���
	λ�ƺ���
	�����ж�����
	ҩ���ж�����
*/
/*
��ʾ���棺
1.�������������׶Ρ�������������ѭ��
	����ʼ��ʾ���棨StartShow0��
	��ѡ����棨����ָ��ʹ�ӡ����{�������ع���}��
		����Ϸģʽ�Ĵ�ӡ������SS1_PlayType��������ָ���ӡ����{�����ع���}��
		�����ý���
			�����ý��溯����SS1_Option��������ָ��{˫��ָ��{��ά�������ģ�⣿}}��ӡ���棩
			�������ع�����һ����Ĺ���
	������ѡ�����{ѡ��+��̬��ӳ��}
*/
int enemy_num;
MPlane P1;
Enemy* enemy;
BackGround PG_back;
void Initialize();
void InitPG();
void Show_UpdateWithoutUser();
void UpdateWithUser();
int main() {
	while (1)
	{
		Initialize();
		while (1) {
			SS_WelcomeShow();								//��һ����
			SkipSS_W:
			SS_ToolShow();									//�ڶ�����
			SS_ChoseShow();									//��������
			if (ifnext == NextKW::NEXT) {
				ifnext = NextKW::STOP;						//���һ��Showֱ��ʹ֮STOP
				break; 
			}
		}
		InitPG();
		while (1) {
			Sleep(20);
			Show_UpdateWithoutUser();
			UpdateWithUser();
			if (ifnext == NextKW::NEXT)
				break;
		}
		EndShow();
		goto SkipSS_W;
	}
	return 0;
}			
void Initialize() {
	InitImage();
	initgraph(WIDTH, HEIGHT);
	srand(time(NULL));
}
void InitPG() {
	P1.Init((int)planetype_0);						//P1��ʼ��
	enemy_num = (int)diff * 2 + 3;							//�л���ʼ��
	enemy = new Enemy[enemy_num];
	for (int i = 0; i < enemy_num; i++)
	{
		enemy[i].Init(i % 3);
	}
}
void Show_UpdateWithoutUser() {
	PG_back.BackGroundP_Move();
	P1.PlaneP();
	P1.L_BulletP_Move();
	P1.StatusP();
	for (int i = 0; i < enemy_num; i++)						//�л���ͼƬ
	{
		enemy[i].PlaneP();

		enemy[i].PlaneMove();
		enemy[i].BulletP_Move();
		enemy[i].BulletCreate();
		for (int j = 0; j < P1.bullet_num; j++)						//��ײ���
		{
			if (enemy[i].IfBehitted(P1.bullet[j]))
				P1.killenemy_num++;
		}
		for (int j = 0; j < P1.lbullet_num; j++)
		{
			if(enemy[i].IfBehitted(P1.lbullet[j]))
				P1.killenemy_num++;
		}
		for (int j = 0; j < enemy[i].bullet_num; j++)
		{
			P1.IfBehitted(enemy[i].bullet[j]);
		}
	}
	P1.LBulletCreate();
}
void UpdateWithUser() {
	P1.Operator();
}

