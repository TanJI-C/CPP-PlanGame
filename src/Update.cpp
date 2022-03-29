#include"Update.h"

bool ifhit = false;//用于记录是否选中{判断是否进入下一界面的钥匙}
int instruct = 0;
const int WIDTH = 450;
const int HEIGHT = 650;
NextKW ifnext = NextKW::STOP;////能否进入下一显示界面
PlayType playtype = PlayType::SINGLE;//全局变量
PlaneType planetype_0 = PlaneType::TYPE_0;//全局变量
PlaneType planetype_1 = PlaneType::TYPE_0;//全局变量
Difficulty diff = Difficulty::EASY;//难度
Life lif = Life::FIVE;
Music muc = Music::ON;
