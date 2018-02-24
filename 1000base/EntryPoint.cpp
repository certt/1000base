#include "Main.h"

void Initialize()
{
	while (!(g_Globals->CSGOWindow = FindWindowA("Valve001", NULL)))
		Sleep(200);

	g_Utils->InitHooks();

    // Hooks::get().Init();

	//Hooks::oldWindowProc = (WNDPROC)SetWindowLongPtr(G::Window, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);
}

bool __stdcall DllMain(void* dll_instance, unsigned long reason_to_call, void* reserved) {
	switch (reason_to_call) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls((HMODULE)dll_instance);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, dll_instance, 0, 0);
		break;
	}

	return true;
}