#include "Main.h"

PresentFn oPresent;
long __stdcall Hooks::Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	if (!g_Globals->RenderInit)
	{
		ImGui_ImplDX9_Init(g_Globals->CSGOWindow, device);
		g_ImRender->CreateObjects(device);
		g_Globals->RenderInit = true;
	}

	DWORD dwOld_D3DRS_COLORWRITEENABLE;
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);

	g_ImRender->PreRender(device);

	ImGui::Begin("1000base", &g_Globals->RenderInit, ImVec2(400, 300), 1.0f);
	{
		if (I::Engine->IsInGame() && I::Engine->IsConnected())
			ImGui::Text("Local player is spawned!");
	}
	ImGui::End();

	if (I::Engine->IsInGame() && I::Engine->IsConnected()) {
		for (int i = 1; i <= I::Engine->GetMaxClients(); ++i)
		{
			C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
			if (!Entity
				|| !Entity->GetLifeState() == 0
				|| !Entity->GetHealth() > 0)
				continue;

			Vector vecBottom, vecScreenBottom, vecScreenOrigin;
			Vector vecOrigin = vecBottom = Entity->GetOrigin();
			vecBottom.z += (Entity->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
			if (!g_Utils->WorldToScreen(vecBottom, vecScreenBottom) || !g_Utils->WorldToScreen(vecOrigin, vecScreenOrigin))
				continue;
			float lineHeight = (vecScreenOrigin.y - vecScreenBottom.y);
			float edgeWidth = lineHeight / 4;
			float lineWidth = edgeWidth;
			edgeWidth /= 1.5f;
			Vector leftUpCorn = Vector(vecScreenOrigin.x - lineWidth - LINE_WIDTH, vecScreenBottom.y, 0.f);
			Vector rightUpCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenBottom.y, 0.f);
			Vector leftDownCorn = Vector(vecScreenOrigin.x - lineWidth, vecScreenOrigin.y, 0.f);
			Vector rightDownCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenOrigin.y, 0.f);

			g_ImRender->DrawEspBox(leftUpCorn, rightDownCorn, Color::Red(), 3);
		}
	}

	g_ImRender->PostRender(device);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);

	return oPresent(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

ResetFn oReset;
long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (!g_Globals->RenderInit)
		return oReset(pDevice, pPresentationParameters);

	
	ImGui_ImplDX9_InvalidateDeviceObjects();
	g_ImRender->InvalidateObjects();
	long hr = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	g_ImRender->CreateObjects(pDevice);

	return hr;
}