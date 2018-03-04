#include "Main.h"

IBaseClientDLL* I::Client = nullptr;
IVEngineClient* I::Engine = nullptr;
IClientEntityList* I::EntityList = nullptr;
IGlobalVars* I::Globals = nullptr;
IClientMode* I::ClientMode = nullptr;

void Interfaces::InitInterfaces()
{
	I::Client = g_Interfaces->get_interface<IBaseClientDLL*>("client.dll", "VClient018");
	I::Engine = g_Interfaces->get_interface<IVEngineClient*>("engine.dll", "VEngineClient014");
	I::EntityList = g_Interfaces->get_interface<IClientEntityList*>("client.dll", "VClientEntityList003");
	// fuck this shit, some users get crash
	//I::ClientMode = **(IClientMode***)((*(DWORD**)I::Client)[10] + 0x5);
	//I::Globals = **(IGlobalVars***)((*(DWORD**)I::Client)[0] + 0x1B);
	// this one better
	I::ClientMode = **reinterpret_cast<IClientMode***> ((*reinterpret_cast<uintptr_t**>(I::Client))[10] + 0x5u);
	I::Globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(I::Client))[0] + 0x1Bu);
}