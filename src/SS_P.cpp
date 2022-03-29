#include"SS.h"
#include"Update.h"
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
IMAGE SS_WS_PC_background;
IMAGE SS_WS_PC_text;

IMAGE SS_MPlane;
IMAGE SS_WS_PG_text;
IMAGE SS_WS_PG;
IMAGE SS_WS_PG_MPlane;

IMAGE SS_TS_background;
IMAGE SS_TS_PS_background;
IMAGE SS_TS_OS_background;
IMAGE SS_TS_OS_music;
IMAGE SS_TS_OS_life;
IMAGE SS_TS_OS_diff;
IMAGE SS_TS_OS_text;
IMAGE SS_TS_OS_black;

IMAGE SS_TS_CS_background;
IMAGE SS_TS_CS_background_Mplane;

IMAGE SS_CS_background;

IMAGE ES_GameOverY; 
IMAGE ES_GameOver;

void InitImage() {
	//SS_WS_PC
	loadimage(&SS_WS_PC_background, "SS_WS_PC_background.jpg");
	loadimage(&SS_WS_PC_text, "SS_WS_PC_text.jpg");
	loadimage(&SS_MPlane, "SS_MPlane.jpg");								//changing
	//SS_WS_PG
	//文字
	loadimage(&SS_WS_PG_text, "SS_WS_PG_text.jpg");
	//逐帧打印
	loadimage(&SS_WS_PG, "SS_WS_PG.jpg");
	//穿过
	loadimage(&SS_WS_PG_MPlane, "SS_MPlaneSuper.jpg", 120, 188);
	//SS_TS
	loadimage(&SS_TS_background, "SS_TS_background.jpg");
	//SS_TS_PS
	loadimage(&SS_TS_PS_background, "SS_TS_PS_background.jpg");
	//TS_TS_OS
	loadimage(&SS_TS_OS_background, "SS_TS_OS_background.jpg");
	loadimage(&SS_TS_OS_music, "SS_TS_OS_music.jpg");
	loadimage(&SS_TS_OS_life, "SS_TS_OS_life.jpg");
	loadimage(&SS_TS_OS_diff, "SS_TS_OS_diff.jpg");
	loadimage(&SS_TS_OS_text, "SS_TS_OS_text.jpg");
	loadimage(&SS_TS_OS_black, "SS_TS_OS_black.jpg");
	//SS_TS_CS
	loadimage(&SS_TS_CS_background, "SS_TS_CS_background.jpg");
	loadimage(&SS_TS_CS_background_Mplane, "SS_MPlaneSuper.jpg", 160, 250);
	//SS_CS
	loadimage(&SS_CS_background, "SS_CS_background.jpg");
	//ES
	loadimage(&ES_GameOverY, "ES_GameOverY.jpg");
	loadimage(&ES_GameOver, "ES_GameOver.jpg");

}

void SS_WelcomeShow_PCover0() {
	putimage(0, 0, &SS_WS_PC_background);
	//文字上浮
	for (int i = 0; i < 50; i++) {
		cleardevice();
		putimage(0, 0, &SS_WS_PC_background);
		putimage(0, 620 - 4 * i, &SS_WS_PC_text);
		if (_kbhit() && (instruct = _getch()) == ' ') break;
		Sleep(100 - i);
	}
	putimage(0, 0, 450, 600, &SS_WS_PC_background, 450, 0);
}
void SS_WelcomeShow_PCover1(){
	//临时变量,随机飞机效果
	int SS_MP;
	SS_MP = rand() % 5;
	//飞机从左飞至右
	for (int i = -10; i < 90; i++) {
		cleardevice();
		putimage(0, 0, 450, 600, &SS_WS_PC_background, 450, 0);
		putimage(5 * i, 134, 400, 60, &SS_MPlane, 0, SS_MP * 60);
		Sleep(30 - i / 5);//飞机逐渐加速
	}
}
void SS_WelcomeShow_PGif() {
	//射出子弹动画
	for (int i = 0; i < 9; i++) {
		putimage(252, 134, 35, 268, &SS_WS_PG, 35 * i, 0);
		if (_kbhit() && (instruct = _getch()) == ' ') goto endPG;
		Sleep(200);
	}
	//飞机飞行动画0
	for (int i = 0; i < 68; i++) {
		putimage(254, 362 - 3 * i, 31, 35, &SS_WS_PG, 283, 228);
		if (_kbhit() && (instruct = _getch()) == ' ') goto endPG;
		Sleep(20);
	}
	//补充道路动画
	putimage(252, 134, 35, 268, &SS_WS_PG, 315, 0);
	Sleep(50);
	//飞机飞行动画1
	for (int i = 69; i < 72; i++) {
		putimage(254, 362 - 3 * i, 31, 35, &SS_WS_PG, 283, 228);
		if (_kbhit() && (instruct = _getch()) == ' ') goto endPG;
		Sleep(20);
	}
	//飞机飞行动画——转向
	for (int i = 84; i < 180; i++) {
		putimage(3 * i, 134, 400, 60, &SS_MPlane, 0, 0);
		Sleep(20 - i / 10);
	}
	//飞机从下飞过动画
	Sleep(1800);
	for (int i = 0; i < 180; i++) {
		putimage(3 * i, 422, 60, 94, &SS_WS_PG_MPlane, 0, (i % 40 < 20 ? 0 : 92));
		Sleep(18 - i / 10);//飞机逐渐加速
	}
endPG:;
}

void SS_ToolShow_OptionShow_PToolCard(const int SS_TS_OS_index, const int* SS_TS_OS_opt) {
	//相当于cleardevice()
	putimage(150, 200, &SS_TS_OS_black);
	putimage(350, 200, &SS_TS_OS_black);
	putimage(0, 510, 450, 100, &SS_TS_OS_text, 0, 0);
	if (SS_TS_OS_index == 3) {//如果是第四个
		putimage(0, 510, 450, 100, &SS_TS_OS_text, 0, 100);
	}
	else {//如果不是第四个
		switch (SS_TS_OS_index) {
		case 0:	putimage(0, 200, 450, 70, &SS_TS_OS_music, 0, 70 * SS_TS_OS_opt[0]); break;
		case 1:	putimage(0, 300, 450, 70, &SS_TS_OS_life, 0, 70 * SS_TS_OS_opt[1]); break;
		case 2:	putimage(0, 400, 450, 70, &SS_TS_OS_diff, 0, 70 * SS_TS_OS_opt[2]); break;
		}
	}
}

void SS_ToolShow_CreaterShow_PGif() {
	for (int i = -8; i < 40; i++) {
		putimage(15 * i, 120, 80, 125, &SS_TS_CS_background_Mplane, 0, (i % 40 < 20 ? 0 : 122));
		putimage(450 - 15 * i, 280, 80, 125, &SS_TS_CS_background_Mplane, 80, (i % 40 < 20 ? 0 : 122));
		Sleep(30);
	}
}


