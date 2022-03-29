#pragma once
#define KEYGET(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) //按键监控
enum class NextKW { STOP, NEXT, BACK };//全局
enum class Difficulty { EASY, NORMAL, HARD, HELL };
enum class Music { ON, OFF };
enum class Hitmusic { OFF, ON };
enum class Life { ONE, THREE, FIVE, SEVEN, NINE };
enum class PlayType { SINGLE, TWIN };					//全局
enum class PlaneType { TYPE_0, TYPE_1,TYPE_2 };			//全局

extern bool ifhit;										//是否敲击键盘
extern int instruct;
extern const int WIDTH;
extern const int HEIGHT;
extern NextKW ifnext;
extern PlayType playtype;								//全局变量
extern PlaneType planetype_0;							//全局变量
extern PlaneType planetype_1;							//全局变量
extern Music muc;
extern Life lif;
extern Difficulty diff;									//难度

