#include "main.h"
HWND g_hwnd;
CRenderInterface* g_Render = NULL;

int g_mainGui = -1;
int g_startGui = -1;
int g_creditsGui = -1;
int g_currentGui = GUI_MAIN_SCREEN;

int g_arialID = -1;

bool LMBDown = false;
//鼠标按下
int mouseX = 0, mouseY = 0;
//鼠标位置

LRESULT WINAPI MsgPro(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		//接收到摧毁消息
		PostQuitMessage(0);
		//发送退出消息
		return 0;
		break;
	case WM_KEYDOWN:
		//键盘按下
		if (wParam == VK_ESCAPE)
			//键码为esc
			PostQuitMessage(0);
		//发送退出消息
		break;
	case WM_LBUTTONDOWN:
		//左键按下
		LMBDown = true;
		break;
	case WM_LBUTTONUP:
		//左键弹起
		LMBDown = false;
		break;
	case WM_MOUSEMOVE:
		//鼠标移动
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	}
	//剩余消息交于系统处理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE P, LPSTR cmd, int show)
{
	//窗体类
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgPro,NULL,NULL,h,NULL,NULL,(HBRUSH)GetStockObject(WHITE_BRUSH)
	,NULL,WINDOW_CLASS };
	//注册窗体
	RegisterClassEx(&wc);

	//根据窗体形态创建
	if (FULLSCREEN)
	{
		g_hwnd = CreateWindowEx(NULL, WINDOW_CLASS, WINDOW_TITLE,
			WS_POPUP | WS_SYSMENU | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HIGHT, NULL, NULL, h, NULL);
	}
	else
	{
		g_hwnd = CreateWindowEx(NULL, WINDOW_CLASS, WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HIGHT, NULL, NULL, h, NULL);
	}
	//如果创建成功，设置窗体为可见，并立即刷新
	if (g_hwnd)
	{
		ShowWindow(g_hwnd, SW_SHOWDEFAULT);
		UpdateWindow(g_hwnd);
	}
	//初始化D3D引擎
	if (InitializeEngine())
	{
		//初始化游戏
		if (GameInitialize())
		{
			//创建消息体并初始化
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			//设置鼠标位置
/*			SetCursorPos(0, 0);*/

			//循环至接收到退出消息
			while (msg.message != WM_QUIT)
			{
				//非阻塞式获取消消息
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					//翻译消息
					TranslateMessage(&msg);
					//分发消息
					DispatchMessage(&msg);
				}
				else
				{
					//游戏循环
					GameLoop();
				}
			}
		}
	}
	//结束游戏进程
	GameShutdown();
	//结束引擎进程
	ShutDownEngine();
	//反注册窗体类
	UnregisterClass(WINDOW_CLASS, h);
}
//初始化引擎
bool InitializeEngine()
{
	//创建D3D渲染器
	if (FAILED(CreateD3DRenderer(&g_Render))) return false;
	//初始化
	if (FAILED(g_Render->Initialize(WIN_WIDTH, WIN_HIGHT, g_hwnd, FULLSCREEN))) return false;

	//设置擦除颜色
	g_Render->SetClearCol(0, 0, 0);
	//创建字体
	if (!g_Render->CreateText((char*)"Arial", 0, true, 18, g_arialID))
		return false;

	return true;
}
//用于停止引擎
void ShutDownEngine()
{
	//如果渲染器存在
	if (g_Render)
	{
		//停止渲染器
		g_Render->Shutdown();
		//删除渲染器
		delete g_Render;
		//回收指针
		g_Render = NULL;
	}
}

//游戏初始化
bool GameInitialize()
{
	//初始化菜单
	if (!InitializeMainMenu()) return false;
	return true;
}

//游戏循环函数
void GameLoop()
{
	//渲染菜单
	MainMenuRender();
}

//游戏结束函数
void GameShutdown()
{
}

//初始化菜单数据
bool InitializeMainMenu()
{
	//创建主菜单UI
	if (!g_Render->CreateGUI(g_mainGui)) return false;
	//创建开始界面UI
	if (!g_Render->CreateGUI(g_startGui)) return false;

	//添加UI背景
	if (!g_Render->AddGUIBackdrop(g_mainGui, (char*)"menu/mainMenu.jpg"))
		return false;
	if (!g_Render->AddGUIBackdrop(g_startGui, (char*)"menu/startMenu.jpg"))
		return false;

	//添加静态文本
	if (!g_Render->AddGUIStaticText(g_mainGui, STATIC_TEXT_ID, (char*)"Version:1.0",
		PERCENT_OF(WIN_WIDTH, 0.85),
		PERCENT_OF(WIN_HIGHT, 0.05),
		UGPCOLOR_ARGB(255, 255, 255, 255),
		g_arialID))
		return false;
	//添加按钮
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_START_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.4),
		(char*)"menu/startUp.png", (char*)"menu/startDown.png",
		(char*)"menu/startOver.png")) return false;
	//添加按钮
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_CREDITS_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.5),
		(char*)"menu/creditsUp.png", (char*)"menu/creditsDown.png",
		(char*)"menu/creditsOver.png")) return false;
	//添加按钮
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_QUIT_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.6),
		(char*)"menu/quitUp.png", (char*)"menu/quitDown.png",
		(char*)"menu/quitOver.png")) return false;

	return true;
}

//主菜单回调函数
void MainMenuCallBack(int id, int state)
{
	switch (id)
	{
	case BUTTON_START_ID:
		if (state == UGP_BUTTON_DOWN)
		{
			g_currentGui = GUI_START_SCREEN;
		}
	}
}

//主场单渲染
void MainMenuRender()
{
	if (!g_Render) return;

	g_Render->StartRender(1, 1, 0);

	if (g_currentGui == GUI_MAIN_SCREEN)
		g_Render->ProcessGUI(g_mainGui, LMBDown, mouseX, mouseY, MainMenuCallBack);
	if (g_currentGui == GUI_START_SCREEN)
		g_Render->ProcessGUI(g_startGui, LMBDown, mouseX, mouseY, MainMenuCallBack);

	g_Render->EndRendering();
}