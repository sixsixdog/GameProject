#ifndef _UGP_GUI_H_
#define _UGP_GUI_H_

#include "define.h"

struct stGUIControl
{
	//GUI�������� ID ��ɫ
	stGUIControl() :m_text(NULL), m_type(0), m_id(0), m_listID(0), m_upTex(0), m_downTex(0), m_overTex(0), m_xPos(0), m_yPos(0), m_width(0), m_height(0), m_color(0) {};

	//��̬�ı�
	char* m_text;
	int m_type;
	int m_id;
	//���������ID������ʹ�õ�����
	int m_listID;
	int m_upTex, m_downTex, m_overTex;
	//��ʼ�Ŀ���λ��
	float m_xPos, m_yPos;
	//��ť��С
	float m_width, m_height;
	unsigned long m_color;
};

class CGUISystem
{
public:
	CGUISystem() :m_controls(0), m_totalControls(0), m_backDropID(-1) {}
	~CGUISystem() { Shutdown(); }

	void Shutdown();
	bool AddBackdrop(int texID, int staticID);
	bool AddStaticText(int id, char* text, int x, int y, unsigned long color, int fontID);
	bool AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
	int IncreaseControls();

	stGUIControl* GetGUICotrol(int id)
	{
		if (id < 0 || id >= m_totalControls)
			return NULL;

		return &m_controls[id];
	}

	int GetTotalControls()
	{
		return m_totalControls;
	}

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