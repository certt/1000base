#pragma once

#include "ABytes.h"

class ImGuiRendering {
public:
	void __stdcall CreateObjects(IDirect3DDevice9* pDevice);
	void __stdcall InvalidateObjects();
	void __stdcall PreRender(IDirect3DDevice9* device);
	void __stdcall PostRender(IDirect3DDevice9* deivce);
	void DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width);

	ImDrawData _drawData;
	ImDrawList* _drawList;
	IDirect3DTexture9* _texture;
	ImFontAtlas _fonts;
}; extern ImGuiRendering* g_ImRender;