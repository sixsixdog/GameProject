#ifndef _UGP_GUI_H_
#define _UGP_GUI_H_

#include "define.h"

struct stGUIControl
{
	stGUIControl() :m_text(NULL) {};
	//GUI控制类型 ID 颜色
	int m_type;
	int m_id;
	unsigned long m_color;

	//如果是字体ID是正在使用的字体
	int m_listID;
	//开始的控制位置
	float m_xPos, m_yPos;
	//按钮大小
	float m_width, m_height;
	//静态文本
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