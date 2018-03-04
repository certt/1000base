#include "Main.h"

void Utils::InitHooks()
{
	std::unique_ptr<CVMTHookManager> ClientMode;
	ClientMode = std::make_unique<CVMTHookManager>(I::ClientMode);

	DWORD dwPresent = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB 74 1F") + 0x2;
	DWORD dwReset = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;

	oCreateMove = (CreateMoveFn)ClientMode->dwHookMethod((DWORD)Hooks::CreateMove, 24);
	oPresent = (PresentFn)((new CVMTHookManager((PDWORD*)dwPresent))->dwHookMethod((DWORD)&Hooks::Present, 0));
	oReset = (ResetFn)((new CVMTHookManager((PDWORD*)dwReset))->dwHookMethod((DWORD)&Hooks::Reset, 0));
}

bool Utils::WorldToScreen(const Vector &origin, Vector &screen)
{
	const auto screenTransform = [&origin, &screen]() -> bool
	{
		static std::uintptr_t pViewMatrix;
		if (!pViewMatrix)
		{
			pViewMatrix = static_cast<std::uintptr_t>(g_Utils->FindPatternIDA("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
			pViewMatrix += 3;
			pViewMatrix = *reinterpret_cast<std::uintptr_t*>(pViewMatrix);
			pViewMatrix += 176;
		}

		const VMatrix& w2sMatrix = *reinterpret_cast<VMatrix*>(pViewMatrix);
		screen.x = w2sMatrix.m[0][0] * origin.x + w2sMatrix.m[0][1] * origin.y + w2sMatrix.m[0][2] * origin.z + w2sMatrix.m[0][3];
		screen.y = w2sMatrix.m[1][0] * origin.x + w2sMatrix.m[1][1] * origin.y + w2sMatrix.m[1][2] * origin.z + w2sMatrix.m[1][3];
		screen.z = 0.0f;

		float w = w2sMatrix.m[3][0] * origin.x + w2sMatrix.m[3][1] * origin.y + w2sMatrix.m[3][2] * origin.z + w2sMatrix.m[3][3];

		if (w < 0.001f)
		{
			screen.x *= 100000;
			screen.y *= 100000;
			return true;
		}

		float invw = 1.f / w;
		screen.x *= invw;
		screen.y *= invw;

		return false;
	};

	if (!screenTransform())
	{
		int iScreenWidth, iScreenHeight;
		I::Engine->GetScreenSize(iScreenWidth, iScreenHeight);

		screen.x = (iScreenWidth * 0.5f) + (screen.x * iScreenWidth) * 0.5f;
		screen.y = (iScreenHeight * 0.5f) - (screen.y * iScreenHeight) * 0.5f;

		return true;
	}
	return false;
}

DWORD Utils::FindPatternIDA(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}

	return NULL;
}