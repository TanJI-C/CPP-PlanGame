#pragma once
#include"Update.h"
#include<graphics.h>

extern IMAGE SS_WS_PG_text;

extern IMAGE SS_TS_background;

extern IMAGE SS_TS_PS_background;

extern IMAGE SS_TS_OS_background;
extern IMAGE SS_TS_OS_music;
extern IMAGE SS_TS_OS_life;
extern IMAGE SS_TS_OS_diff;
extern IMAGE SS_TS_OS_text;
extern IMAGE SS_TS_OS_black;

extern IMAGE SS_TS_CS_background;

extern IMAGE SS_CS_background;

extern IMAGE ES_GameOverY;
extern IMAGE ES_GameOver;
void InitImage();
//第一界面
void SS_WelcomeShow();
void SS_WelcomeShow_PCover0();
void SS_WelcomeShow_PCover1();
void SS_WelcomeShow_PGif();
//第二界面
void SS_ToolShow();
void SS_ToolShow_PlayShow();
void SS_ToolShow_OptionShow();
void SS_ToolShow_OptionShow_PToolCard(const int index, const int* a);
void SS_ToolShow_CreaterShow();
void SS_ToolShow_CreaterShow_PGif();
//第三界面
void SS_ChoseShow();
//ES
void EndShow();

