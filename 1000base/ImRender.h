#pragma once

#include "ABytes.h"

class ImGuiRendering {
public:
	void __stdcall CreateObjects(IDirect3DDevice9* pDevice);
	void __stdcall InvalidateObjects();
	void __stdcall PreRender(IDirect3DDevice9* device);
	void __stdcall PostRender(IDirect3DDevice9* deivce);
	void __stdcall EndPresent(IDirect3DDevice9* device);
	void __stdcall SetupPresent(IDirect3DDevice9* device);

	void DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width);
	void DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness);
	void DrawWave(Vector loc, float radius, Color clr, float thickness);
	void DrawString(ImFont* font, float x, float y, Color color, const char* message, ...);

private:
	ImDrawData _drawData;
	ImDrawList* _drawList;
	IDirect3DTexture9* _texture;
	ImFontAtlas _fonts;
	DWORD dwOld_D3DRS_COLORWRITEENABLE;
}; extern ImGuiRendering* g_ImRender;