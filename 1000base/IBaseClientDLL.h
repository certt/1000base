#pragma once

class ClientClass
{
public:
	BYTE _chPadding[8];
	char* szName;
	RecvTable* rtTable;
	ClientClass* pNextClass;
	int iClassID;
};

class IBaseClientDLL
{
public:
	ClientClass * GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return g_Utils->get_vfunc<GetAllClassesFn>(this, 8)(this);
	}
};