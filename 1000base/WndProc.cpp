#include "Main.h"
WNDPROC Hooks::oldWindowProc;

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool PressedButtons = false;

	if (!PressedButtons && GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = true;
	}
	else if (PressedButtons && !GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = false;

		g_Vars->Menu.Opened = !g_Vars->Menu.Opened;
		if (g_Vars->Menu.Opened)
			I::Engine->ExecuteClientCmd("cl_mouseenable 0");
		else
			I::Engine->ExecuteClientCmd("cl_mouseenable 1");
	}

	if (g_Vars->Menu.Opened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(oldWindowProc, hWnd, uMsg, wParam, lParam);
}