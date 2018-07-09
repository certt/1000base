#pragma once

class ISurface
{
public:
	void UnLockCursor()
	{
		typedef void(__thiscall* original_fn)(void*);
		g_Utils->get_vfunc< original_fn >(this, 66)(this);
	}
};