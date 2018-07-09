#pragma once

class Globals
{
public:
	HWND CSGOWindow;
	bool isPanorama;
	bool RenderInit;
	ImFont* Font1;
	ImFont* Font2;
	C_BaseEntity* LocalPlayer;
private:
}; extern Globals* g_Globals;