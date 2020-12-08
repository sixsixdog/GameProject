#ifndef _UGP_GUI_H_
#define _UGP_GUI_H_

#include "define.h"

struct stGUIControl
{
	stGUIControl() :m_text(NULL) {};
	//GUI�������� ID ��ɫ
	int m_type;
	int m_id;
	unsigned long m_color;

	//���������ID������ʹ�õ�����
	int m_listID;
	//��ʼ�Ŀ���λ��
	float m_xPos, m_yPos;
	//��ť��С
	float m_width, m_height;
	//��̬�ı�
	char* m_text;

	int m_upTex, m_downTex, m_overTex;
};

class CGUISystem
{
public:
	CGUISystem() :m_controls(0), m_totalControls(0), m_backDropID(-1) {}
	~CGUISystem() { Shutdown(); }

	int IncreaseControls();

	bool AddBackdrop(int texID, int staticID);
	bool AddStaticText(int id, char* text, int x, int y, unsigned long color, int fontID);
	bool AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
	void Shutdown();

	stGUIControl* GetGUICotrol(int id)
	{
		if (id < 0 || id >= m_totalControls) return NULL;
		return &m_controls[id];
	}

	int GetTotalControls() { return m_totalControls; }
	stGUIControl* GetbackDrop()
	{
		if (m_backDropID >= 0 && m_totalControls)
			return &m_controls[m_backDropID];

		return NULL;
	}

private:
	stGUIControl* m_controls;
	int m_totalControls;
	int m_backDropID;
};

#endif