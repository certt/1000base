#pragma once

class CVMTHookManager
{
private:
	int vtable;
	int orig;
	int orig_protect;
	DWORD hk;
	int ent;
	int offs;
public:
	CVMTHookManager(void* instance)
	{
		vtable = *((int*)instance);
	}

	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex)
	{
		int entry = vtable + sizeof(int) * iIndex;
		int org = *((int*)entry);

		int org_protect = Unprotect((void*)entry);
		*((int*)entry) = (int)dwNewFunc;

		orig = org;
		hk = dwNewFunc;
		ent = entry;

		return orig;
	}

	void* GetOriginal()
	{
		return (void*)orig;
	}

	void* ReHook()
	{
		*((int*)ent) = (int)hk;
		return (void*)orig;
	}

	void UnHook()
	{
		*((int*)ent) = (int)orig;
	}

	int Unprotect(void* reg)
	{
		MEMORY_BASIC_INFORMATION memInf;

		VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
		VirtualProtect(memInf.BaseAddress, memInf.RegionSize, PAGE_READWRITE, &memInf.Protect);

		return memInf.Protect;
	}
};