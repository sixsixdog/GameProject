#ifndef   _UGP_MAIN_H_
#define _UGP_MAIN_H_

#include "../StrandedEngine/engine.h"
#pragma comment(lib,"../Debug/StrandedEngine.lib")

#define WINDOW_CLASS				"StrandedGame"
//��������
#define WINDOW_TITLE			"Stranded"
//������
#define WIN_WIDTH 800
//������
#define WIN_HIGHT 600
//����߶�
#define FULLSCREEN 0
//�Ƿ�ȫ��

bool InitializeEngine();
void ShutDownEngine();

bool InitializeMainMenu();
void MainMenuRender();
void MainMenuCallBack(int id, int state);


bool GameInitialize();
void GameLoop();
void GameShutdown();

#define GUI_MAIN_SCREEN 1
#define GUI_START_SCREEN 2
#define GUI_CREDITS_SCREEN 3

#define STATIC_TEXT_ID 1
#define BUTTON_START_ID 2
#define BUTTON_CREDITS_ID 3
#define  BUTTON_QUIT_ID 4
#define BUTTON_BACK_ID 5
#define BUTTONLEVEL_1_ID 6


#endif
