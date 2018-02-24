#include "Main.h"

PresentFn oPresent;
long __stdcall Hooks::Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	if (!g_Globals->RenderInit)
	{
		ImGui_ImplDX9_Init(g_Globals->CSGOWindow, device);
		g_Globals->RenderInit = true;
	}

	ImGui_ImplDX9_NewFrame();

	ImGui::Begin("1000base", &g_Globals->RenderInit, ImVec2(400, 300), 1.0f);
	{
		if (I::Engine->IsInGame() && I::Engine->IsConnected())
			ImGui::Text("Local player is spawned!");
	}
	ImGui::End();

	ImGui::Render();

	return oPresent(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

ResetFn oReset;
long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (!g_Globals->RenderInit)
		return oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	long hr = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	return hr;
}