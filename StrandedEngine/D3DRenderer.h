#ifndef _D3D_RENDERER_H_
#define _D3D_RENDERER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "RenderInterface.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

struct stD3DStaticBuffer
{
	stD3DStaticBuffer() : vbPtr(0), ibPtr(0), numVerts(0), numIndices(0), stride(0), fvf(0), primType(NULL_TYPE) {}

	LPDIRECT3DVERTEXBUFFER9 vbPtr;
	LPDIRECT3DINDEXBUFFER9 ibPtr;
	int numVerts;
	int numIndices;
	int stride;
	unsigned long fvf;
	PrimType primType;
};

struct stD3DTexture
{
	char* fileName;
	int width, height;
	LPDIRECT3DTEXTURE9 image;
};

class CD3DRenderer : public CRenderInterface
{
public:
	CD3DRenderer();
	~CD3DRenderer();

	bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen);

	void SetClearCol(float r, float g, float b);
	void Shutdown();
	void StartRender(bool bColor, bool bDepth, bool bStencil);
	int Render(int staticId);
	void EndRendering();
	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
	void EnableFog(float start, float end, UGP_FOG_TYPE type, unsigned long color, bool rangeFog);
	void DisableFog();

	int CreateStaticBuffer(VertexType vType, PrimType primType, int totalVerts, int totalIndices, int stride,
		void** data, unsigned int* indices, int* staticId);

	void SetMaterial(stMaterial* mat);
	void SetLight(stLight* light, int index);
	void DisableLight(int index);

	void SetTranspency(RenderState state, TransState src, TransState dst);
	int AddTexture2D(char* file, int* texId);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTextur();
	void ApplyTextur(int index, int texId);
	void SaveScreenShot(char* file);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisablePointSprites();

	bool CreateText(char* font, int weight, bool italic, int size, int& id);
	bool DisplayText(int id, long x, long y, int r, int g, int b, char* text, ...);
	bool DisplayText(int id, long x, long y, unsigned long color, char* text, ...);

	bool AddGUIBackdrop(int guiId, char* fileName);
	bool AddGUIStaticText(int guiId, int id, char* text, int x, int y, unsigned long color, int fontID);
	bool AddGUIButton(int guidId, int id, int x, int y, char* up, char* over, char* down);
	void ProcessGUI(int guiID, bool LMVDown, int mouseX, int mouseY, void(*funcPtr)(int id, int state));

	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrthoMatrix(float n, float f);

private:
	void OneTimeInit();
private:
	D3DCOLOR m_Color;
	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Device;
	bool m_renderingScene;

	LPD3DXFONT* m_fonts;

	stD3DStaticBuffer* m_staticBufferList;
	int m_numStaticBuffers;
	int m_activeStaticBuffer;

	stD3DTexture* m_textureList;
	unsigned int m_numTextures;
};

bool CreateD3DRenderer(CRenderInterface** pObj);

#endif