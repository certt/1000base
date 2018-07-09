#include "Main.h"

PresentFn oPresent;
ResetFn oReset;
LockCursorFn oLockCursor;

void __stdcall Hooks::LockCursor()
{
	if (g_Vars->Menu.Opened) {
		I::Surface->UnLockCursor();
		return;
	}

	oLockCursor(I::Surface);
}

long __stdcall Hooks::Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) {
	if (!g_Globals->RenderInit)
		g_ImRender->SetupPresent(device);

	g_ImRender->PreRender(device);
	g_Visuals->ESP();
	g_ImRender->PostRender(device);
	g_Menu->Menu();
	g_ImRender->EndPresent(device);

	return oPresent(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) {
	if (!g_Globals->RenderInit)
		return oReset(pDevice, pPresentationParameters);

	g_ImRender->InvalidateObjects();
	long hr = oReset(pDevice, pPresentationParameters);
	g_ImRender->CreateObjects(pDevice);
	return hr;
}