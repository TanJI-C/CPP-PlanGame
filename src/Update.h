#pragma once
#define KEYGET(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) //�������
enum class NextKW { STOP, NEXT, BACK };//ȫ��
enum class Difficulty { EASY, NORMAL, HARD, HELL };
enum class Music { ON, OFF };
enum class Hitmusic { OFF, ON };
enum class Life { ONE, THREE, FIVE, SEVEN, NINE };
enum class PlayType { SINGLE, TWIN };					//ȫ��
enum class PlaneType { TYPE_0, TYPE_1,TYPE_2 };			//ȫ��

extern bool ifhit;										//�Ƿ��û�����
extern int instruct;
extern const int WIDTH;
extern const int HEIGHT;
extern NextKW ifnext;
extern PlayType playtype;								//ȫ�ֱ���
extern PlaneType planetype_0;							//ȫ�ֱ���
extern PlaneType planetype_1;							//ȫ�ֱ���
extern Music muc;
extern Life lif;
extern Difficulty diff;									//�Ѷ�

