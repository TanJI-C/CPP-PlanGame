#include<Windows.h>
#include<conio.h>
#include<graphics.h>
#include"SS.h"
#include"Update.h"
#include<mmsystem.h>
#pragma comment (lib,"winmm.lib")


//Show函数表示界面
//P表示图像界面打印
/*笔记
1. 一般结构的改进，先打印，在输入指令
*/


//第一界面
void SS_WelcomeShow() {
	mciSendString("open SS_bgm.mp3 alias SS_bgm", 0, 0, 0);
	mciSendString("play SS_bgm repeat", 0, 0, 0);
	ifnext = NextKW::STOP;												//进入下一界面的钥匙归零
	SS_WelcomeShow_PCover0();											//游戏初始界面打印
	while (1) {															//使用循环语句，仅输入正确的字符时进入下一步
		SS_WelcomeShow_PCover1();
		if (_kbhit() && (instruct = _getch()) == ' ') {
			ifnext = NextKW::NEXT;										//有钥匙时进入下一界面
			mciSendString("open SS_bgm_hit.mp3 alias SS_bgm_hit", 0, 0, 0);
			mciSendString("play SS_bgm_hit repeat", 0, 0, 0);
			putimage(0, 134, 400, 60, &SS_WS_PG_text, 0, 0);
			Sleep(1180);
			putimage(0, 134, 400, 60, &SS_WS_PG_text, 0, 60);
			Sleep(1180);
			mciSendString("close SS_bgm", 0, 0, 0);
			putimage(0, 134, 400, 60, &SS_WS_PG_text, 0, 120);
			if (_kbhit() && (instruct = _getch()) == ' ') goto endPG;
			Sleep(1180);
			break;
		}
		Sleep((rand() % 3) * 1000);										//随机停留一段时间
	}
	SS_WelcomeShow_PGif();
endPG:;
}
//第二界面
void SS_ToolShow() {
	ifnext = NextKW::STOP;												//进入下一界面的钥匙归零
	mciSendString("close GG_bgm", 0, 0, 0);
	if(muc==Music::ON)
		mciSendString("play SS_bgm_hit repeat", 0, 0, 0);
	int SS_TS_index = 0;												//存储光标的指向→笔记：打印函数与底层数据的关系（底层数据经底层数据处理函数处理之后输送给打印函数），实现了互通
	putimage(0, 0, 450, 650, &SS_TS_background, 0, 0);					//第一次打印选择界面，后续方便进行更改
	while (1) {
		//读取指令//为啥要放在后面//读取指令上遇到了些困难
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		switch (instruct) {
		case 72:if (--SS_TS_index < 0)++SS_TS_index; break;				//上或下的指令，是光标指向相应的移动
		case 80:if (++SS_TS_index > 2)--SS_TS_index; break;
		case ' ':ifhit = true; break;
		}
																		//数据执行（选中&未选中）
		if (ifhit) {													//进入下一子界面
			ifhit = false;												//归零，便于下次使用
			switch (SS_TS_index) {										//根据光标坐标，判断进入哪一个界面
			case 0:SS_ToolShow_PlayShow(); break;
			case 1:SS_ToolShow_OptionShow(); break;
			case 2:SS_ToolShow_CreaterShow(); break;
			}
		}
		putimage(0, 0, 450, 650, &SS_TS_background, 450 * SS_TS_index, 0);//光标转换,打印界面
		if (ifnext == NextKW::NEXT)break;								//退出该界面{钥匙从PlayShow得到}
	}
}

void SS_ToolShow_PlayShow() {
	ifnext = NextKW::STOP;//进入下一界面的钥匙归零
	bool SS_TS_PS_index = false;
	putimage(0, 0, 450, 650, &SS_TS_PS_background, 0, 0);
	while (1) {
		//读取指令
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		switch (instruct) {//发现:实际上输入数字之后并不会读取数据，而是经过一个循环之后再进行数据读取
		case 72:
		case 80:SS_TS_PS_index = !SS_TS_PS_index; break;
		case ' ':ifhit = true; break;//选中了，数据执行时会进入第一个if中
		case 27:ifnext = NextKW::BACK; break;
		}
		//数据执行（选中&未选中）
		if (ifhit) {//选中模式了
			ifhit = false;//归零，便于下次使用
			switch (SS_TS_PS_index) {//选中后播放动画，得到钥匙{直达ChooseShow}
			case false:/*SS_ToolShow_PlayShow_PGif_0()*/; ifnext = NextKW::NEXT; playtype = PlayType::SINGLE; break;//播放动画，得到钥匙，选择模式，breakShow
			case true:/*SS_ToolShow_PlayShow_PGif_1()*/; ifnext = NextKW::NEXT; playtype = PlayType::TWIN; break;//
			}
		}
		else {//没有选中模式
			putimage(0, 0, 450, 650, &SS_TS_PS_background, 450 * SS_TS_PS_index, 0);
		}
		//退出该界面
		if (ifnext == NextKW::NEXT || ifnext == NextKW::BACK)break;
	}
}
void SS_ToolShow_OptionShow() {
	ifnext = NextKW::STOP;//进入下一界面的钥匙归零
	int SS_TS_OS_index = 0;
	int SS_TS_OS_opt[4] = { (int)muc,(int)lif,(int)diff,0};

	//进来先初始化
	putimage(0, 0, &SS_TS_OS_background);
	putimage(0, 300, 450, 70, &SS_TS_OS_life, 0, 70 * SS_TS_OS_opt[1]);
	putimage(0, 400, 450, 70, &SS_TS_OS_diff, 0, 70 * SS_TS_OS_opt[2]);
	putimage(0, 510, 450, 100, &SS_TS_OS_text, 0, 0);
	putimage(150, 200, &SS_TS_OS_black);
	putimage(350, 200, &SS_TS_OS_black);
	putimage(0, 200, 450, 70, &SS_TS_OS_music, 0, 70 * SS_TS_OS_opt[0]);//因为是指向显示的，所以直接放最后
	while (1) {
		//接收指令
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		switch (instruct) {
		case 72:if (--SS_TS_OS_index < 0)SS_TS_OS_index++; break;
		case 80:if (++SS_TS_OS_index > 3)SS_TS_OS_index--; break;
		case 75:
			switch (SS_TS_OS_index) {
			case 0:if (--SS_TS_OS_opt[0] < 0)SS_TS_OS_opt[0]++; break;
			case 1:if (--SS_TS_OS_opt[1] < 0)SS_TS_OS_opt[1]++; break;
			case 2:if (--SS_TS_OS_opt[2] < 0)SS_TS_OS_opt[2]++; break;
			}break;
		case 77:
			switch (SS_TS_OS_index) {
			case 0:if (++SS_TS_OS_opt[0] > 1)SS_TS_OS_opt[0]--; break;
			case 1:if (++SS_TS_OS_opt[1] > 4)SS_TS_OS_opt[1]--; break;
			case 2:if (++SS_TS_OS_opt[2] > 3)SS_TS_OS_opt[2]--; break;
			}break;
		case ' ':ifhit = true; break;
		}
		//数据修改
		//可否仅针对值发生变换时操作
		//命令执行
		if (ifhit) { 
			ifhit = false; 
			if (SS_TS_OS_index == 3) {
				ifnext = NextKW::BACK; 
			} 
		}//拿到回去的指令
		else { SS_ToolShow_OptionShow_PToolCard(SS_TS_OS_index, SS_TS_OS_opt); }
		//判断是否离开此界面
		if (ifnext == NextKW::BACK) {
			break;
		}
	}
	//离开前，数据初始化
	muc = (Music)SS_TS_OS_opt[0];
	if (muc == Music::ON) {
		mciSendString("play SS_bgm_hit repeat", 0, 0, 0);
	}
	else {
		mciSendString("pause SS_bgm_hit", 0, 0, 0);
	}
	lif = (Life)SS_TS_OS_opt[1];
	diff = (Difficulty)SS_TS_OS_opt[2];
}
void SS_ToolShow_CreaterShow() {
	ifnext = NextKW::STOP;
	putimage(0, 0, &SS_TS_CS_background);
	while (1) {
		//读入指令+指令执行
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		if (instruct == ' ')ifnext = NextKW::BACK;
		//判断是否返回界面
		if (ifnext == NextKW::BACK) {
			SS_ToolShow_CreaterShow_PGif();
			break;
		}
	}
}
//第三界面
void SS_ChoseShow() {
	//为防止全局变量ifnext//笔记：可以使用全局变量的覆盖性暂时覆盖掉ifnext的值吗
	ifnext = NextKW::STOP;//进入下一界面的钥匙归零
	int SS_CS_index = false;
	//system("cls");
	putimage(0, 0, 450, 650, &SS_CS_background, 0, 0);
	while (1) {//补充：还是不行，这里选择的是战机的类型，不是游戏模式，因此要定义全局变量TYPE{也恰好可以利用这个数据进行下一步的选择}
		//再补充：经过思考后，发现ifnext的功能应该与游戏模式分开为两个变量来记录，提高可读性
		//接收指令
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		switch (instruct) {
		case 72:if (--SS_CS_index < 0)SS_CS_index++; break;
		case 80:if (++SS_CS_index > 2)SS_CS_index--; break;
		case ' ':ifhit = true; break;
		}
		//执行数据
		if (ifhit) {
			ifhit = false;
			putimage(0, 0, 450, 650, &SS_CS_background, 450 * SS_CS_index, 650);
			Sleep(200);
			ifnext = NextKW::NEXT;
			break;
		}
		else {
			putimage(0, 0, 450, 650, &SS_CS_background, 450 * SS_CS_index, 0);
		}
		//退出该界面
		if (ifnext == NextKW::NEXT) {
			break;
		}
	}
	//离开前，数据改变
	switch (SS_CS_index) {
	case 0:planetype_0 = PlaneType::TYPE_0; break;
	case 1:planetype_0 = PlaneType::TYPE_1; break;
	case 2:planetype_0 = PlaneType::TYPE_2; break;
	}
}
//GG界面
//GG界面
void EndShow()
{
	ifnext = NextKW::STOP;
	mciSendString("open GG_bgm.mp3 alias GG_bgm", 0, 0, 0);
	mciSendString("pause SS_bgm_hit ", 0, 0, 0);
	mciSendString("play GG_bgm ", 0, 0, 0);
	int y_ima = rand() % 2 * 400;
	putimage(0, 100, 450, 400, &ES_GameOverY, 0, y_ima, SRCAND);
	putimage(0, 100, 450, 400, &ES_GameOver, 0, y_ima, SRCPAINT);
	while (1)
	{
		if ((instruct = _getch()) == 224)
			instruct = _getch();
		if (instruct == 'r' || instruct == 'R')
		{
			ifnext = NextKW::BACK;
			break;
		}
	}
}
