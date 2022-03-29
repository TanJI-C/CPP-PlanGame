#include"Update.h"
#include"SS.h"
#include"PG.h"
#include<stdlib.h>
#include<time.h>
/*
显示界面的函数的功能
	显示初始界面{含点击触发界面和选择界面}【选择功能】
	游戏模式界面{弹出多个窗口}
	设置界面{设置界面函数}【选择功能和返回功能】
	初始化参数传递给Update
初始化函数：
	使用一访多的设定进行选择
与用户相关的函数：
	输入类型及相应的处理【处理包含函数
与用户无关的函数：
	速度控制变量
	位移函数
	击中判定函数
	药包判定函数
*/
/*
显示界面：
1.三大界面→三个阶段→三个函数进行循环
	·初始显示界面（StartShow0）
	·选择界面（接受指令和打印界面{不含返回功能}）
		·游戏模式的打印【函数SS1_PlayType】（接受指令打印界面{含返回功能}）
		·设置界面
			·设置界面函数【SS1_Option】（接受指令{双向指令{二维数组进行模拟？}}打印界面）
			·含返回功能上一界面的功能
	·功能选择界面{选择+动态放映？}
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
			SS_WelcomeShow();								//第一界面
			SkipSS_W:
			SS_ToolShow();									//第二界面
			SS_ChoseShow();									//第三界面
			if (ifnext == NextKW::NEXT) {
				ifnext = NextKW::STOP;						//最后一个Show直接使之STOP
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
	P1.Init((int)planetype_0);						//P1初始化
	enemy_num = (int)diff * 2 + 3;							//敌机初始化
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
	for (int i = 0; i < enemy_num; i++)						//敌机的图片
	{
		enemy[i].PlaneP();

		enemy[i].PlaneMove();
		enemy[i].BulletP_Move();
		enemy[i].BulletCreate();
		for (int j = 0; j < P1.bullet_num; j++)						//碰撞检测
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

