#include "main.h"
HWND g_hwnd;
CRenderInterface* g_Render = NULL;

int g_mainGui = -1;
int g_startGui = -1;
int g_creditsGui = -1;
int g_currentGui = GUI_MAIN_SCREEN;

int g_arialID = -1;

bool LMBDown = false;
//��갴��
int mouseX = 0, mouseY = 0;
//���λ��

LRESULT WINAPI MsgPro(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		//���յ��ݻ���Ϣ
		PostQuitMessage(0);
		//�����˳���Ϣ
		return 0;
		break;
	case WM_KEYDOWN:
		//���̰���
		if (wParam == VK_ESCAPE)
			//����Ϊesc
			PostQuitMessage(0);
		//�����˳���Ϣ
		break;
	case WM_LBUTTONDOWN:
		//�������
		LMBDown = true;
		break;
	case WM_LBUTTONUP:
		//�������
		LMBDown = false;
		break;
	case WM_MOUSEMOVE:
		//����ƶ�
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	}
	//ʣ����Ϣ����ϵͳ����
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE P, LPSTR cmd, int show)
{
	//������
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgPro,NULL,NULL,h,NULL,NULL,(HBRUSH)GetStockObject(WHITE_BRUSH)
	,NULL,WINDOW_CLASS };
	//ע�ᴰ��
	RegisterClassEx(&wc);

	//���ݴ�����̬����
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
	//��������ɹ������ô���Ϊ�ɼ���������ˢ��
	if (g_hwnd)
	{
		ShowWindow(g_hwnd, SW_SHOWDEFAULT);
		UpdateWindow(g_hwnd);
	}
	//��ʼ��D3D����
	if (InitializeEngine())
	{
		//��ʼ����Ϸ
		if (GameInitialize())
		{
			//������Ϣ�岢��ʼ��
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			//�������λ��
/*			SetCursorPos(0, 0);*/

			//ѭ�������յ��˳���Ϣ
			while (msg.message != WM_QUIT)
			{
				//������ʽ��ȡ����Ϣ
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					//������Ϣ
					TranslateMessage(&msg);
					//�ַ���Ϣ
					DispatchMessage(&msg);
				}
				else
				{
					//��Ϸѭ��
					GameLoop();
				}
			}
		}
	}
	//������Ϸ����
	GameShutdown();
	//�����������
	ShutDownEngine();
	//��ע�ᴰ����
	UnregisterClass(WINDOW_CLASS, h);
}
//��ʼ������
bool InitializeEngine()
{
	//����D3D��Ⱦ��
	if (FAILED(CreateD3DRenderer(&g_Render))) return false;
	//��ʼ��
	if (FAILED(g_Render->Initialize(WIN_WIDTH, WIN_HIGHT, g_hwnd, FULLSCREEN))) return false;

	//���ò�����ɫ
	g_Render->SetClearCol(0, 0, 0);
	//��������
	if (!g_Render->CreateText((char*)"Arial", 0, true, 18, g_arialID))
		return false;

	return true;
}
//����ֹͣ����
void ShutDownEngine()
{
	//�����Ⱦ������
	if (g_Render)
	{
		//ֹͣ��Ⱦ��
		g_Render->Shutdown();
		//ɾ����Ⱦ��
		delete g_Render;
		//����ָ��
		g_Render = NULL;
	}
}

//��Ϸ��ʼ��
bool GameInitialize()
{
	//��ʼ���˵�
	if (!InitializeMainMenu()) return false;
	return true;
}

//��Ϸѭ������
void GameLoop()
{
	//��Ⱦ�˵�
	MainMenuRender();
}

//��Ϸ��������
void GameShutdown()
{
}

//��ʼ���˵�����
bool InitializeMainMenu()
{
	//�������˵�UI
	if (!g_Render->CreateGUI(g_mainGui)) return false;
	//������ʼ����UI
	if (!g_Render->CreateGUI(g_startGui)) return false;

	//���UI����
	if (!g_Render->AddGUIBackdrop(g_mainGui, (char*)"menu/mainMenu.jpg"))
		return false;
	if (!g_Render->AddGUIBackdrop(g_startGui, (char*)"menu/startMenu.jpg"))
		return false;

	//��Ӿ�̬�ı�
	if (!g_Render->AddGUIStaticText(g_mainGui, STATIC_TEXT_ID, (char*)"Version:1.0",
		PERCENT_OF(WIN_WIDTH, 0.85),
		PERCENT_OF(WIN_HIGHT, 0.05),
		UGPCOLOR_ARGB(255, 255, 255, 255),
		g_arialID))
		return false;
	//��Ӱ�ť
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_START_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.4),
		(char*)"menu/startUp.png", (char*)"menu/startDown.png",
		(char*)"menu/startOver.png")) return false;
	//��Ӱ�ť
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_CREDITS_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.5),
		(char*)"menu/creditsUp.png", (char*)"menu/creditsDown.png",
		(char*)"menu/creditsOver.png")) return false;
	//��Ӱ�ť
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_QUIT_ID, PERCENT_OF(WIN_WIDTH, 0.05),
		PERCENT_OF(WIN_HIGHT, 0.6),
		(char*)"menu/quitUp.png", (char*)"menu/quitDown.png",
		(char*)"menu/quitOver.png")) return false;

	return true;
}

//���˵��ص�����
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

//��������Ⱦ
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