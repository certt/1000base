#include "Main.h"

void Utils::InitHooks()
{
	DWORD dwPresent = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB 74 1F") + 0x2;
	DWORD dwReset = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;
	oPresent = (PresentFn)((new CVMTHookManager((PDWORD*)dwPresent))->dwHookMethod((DWORD)&Hooks::Present, 0));
	oReset = (ResetFn)((new CVMTHookManager((PDWORD*)dwReset))->dwHookMethod((DWORD)&Hooks::Reset, 0));
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