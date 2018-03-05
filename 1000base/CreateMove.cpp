#include "Main.h"

CreateMoveFn oCreateMove;
bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	auto bCreateMoveReturn = oCreateMove(flInputSampleTime, pCmd); // Cause that`s fix a lot of bugs w/ this hook

	if (!pCmd || !pCmd->command_number)
		return bCreateMoveReturn;

	g_Globals->LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	return false;
}
