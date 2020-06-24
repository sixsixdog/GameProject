#ifndef _UGP_RENDERINTERFACE_H_
#define _UGP_RENDERINTERFACE_H_

#include "define.h"
#include "meterial.h"
#include "light.h"
#include "GUI.h"

class CRenderInterface
{
public:
	CRenderInterface() : m_screenWidth(0), m_screenHeight(0), m_near(0), m_far(0) {}

	virtual ~CRenderInterface() {}

	virtual bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen) = 0;
	virtual void OneTimeInit() = 0;
	virtual void Shutdown() = 0;
	virtual void SetClearCol(float r, float g, float b) = 0;

	virtual void StartRender(bool bColor, bool bDepth, bool bStencil) = 0;
	virtual int Render(int staticId) = 0;
	virtual void EndRendering() = 0;
	virtual void ClearBuffers(bool bColor, bool bDepth, bool bStencil) = 0;

	virtual int CreateStaticBuffer(VertexType vType, PrimType primType, int totalVerts, int totalIndices, int Stride,
		void** data, unsigned int* indices, int* staticId) = 0;

	virtual void SetMaterial(stMaterial* mat) = 0;

	virtual void SetLight(stLight* light, int index) = 0;
	virtual void DisableLight(int index) = 0;

	virtual void SetTranspency(RenderState state, TransState src, TransState dst) = 0;
	virtual int AddTexture2D(char* file, int* texId) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	virtual void SetMultiTextur() = 0;
	virtual void ApplyTextur(int index, int texId) = 0;
	virtual void SaveScreenShot(char* file) = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisablePointSprites() = 0;

	virtual bool CreateText(char* font, int weight, bool italic, int size, int& id) = 0;
	virtual bool DisplayText(int id, long x, long y, int r, int g, int b, char* text, ...) = 0;
	virtual bool DisplayText(int id, long x, long y, unsigned long color, char* text, ...) = 0;

	bool CreateGUI(int& id)
	{
		if (!m_guiList)
		{
			m_guiList = new CGUISystem[1];
			if (!m_guiList) return UGP_FAIL;
		}
		else
		{
			CGUISystem* temp;
			temp = new CGUISystem[m_totalGUIs + 1];
			memcpy(temp, m_guiList, sizeof(CGUISystem) * m_totalGUIs);
			delete[] m_guiList;
			m_guiList = temp;
		}
		id = m_totalGUIs;
		m_totalGUIs++;

		return true;
	}
	virtual bool AddGUIBackdrop(int guiId, char* fileName) = 0;
	virtual bool AddGUIStaticText(int guiId, int id, char* text, int x, int y, unsigned long color, int fontID) = 0;
	virtual bool AddGUIButton(int guidId, int id, int x, int y, char* up, char* over, char* down) = 0;
	virtual void ProcessGUI(int guiID, bool LMVDown, int mouseX, int mouseY, void(*funcPtr)(int id, int state)) = 0;

	virtual void CalculateProjMatrix(float fov, float n, float f) = 0;
	virtual void CalculateOrthoMatrix(float n, float f) = 0;

protected:
	int m_screenWidth;
	int m_screenHeight;
	bool m_fullscreen;

	int m_totalFonts;

	CGUISystem* m_guiList;
	int m_totalGUIs;

	WinHWND m_mainHandle;

	float m_near;
	float m_far;
};


#endif