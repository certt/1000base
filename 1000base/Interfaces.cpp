#include "Main.h"

IBaseClientDLL* I::Client = nullptr;
IVEngineClient* I::Engine = nullptr;
IClientEntityList* I::EntityList = nullptr;
IGlobalVars* I::Globals = nullptr;
IClientMode* I::ClientMode = nullptr;
ISurface* I::Surface = nullptr;

void Interfaces::InitInterfaces()
{
	I::Client = g_Interfaces->get_interface<IBaseClientDLL*>(g_Globals->isPanorama ? "client_panorama.dll" : "client.dll", "VClient018");
	I::Engine = g_Interfaces->get_interface<IVEngineClient*>("engine.dll", "VEngineClient014");
	I::EntityList = g_Interfaces->get_interface<IClientEntityList*>(g_Globals->isPanorama ? "client_panorama.dll" : "client.dll", "VClientEntityList003");
	I::Surface = g_Interfaces->get_interface<ISurface*>("vguimatsurface.dll", "VGUI_Surface031");

	I::ClientMode = **reinterpret_cast<IClientMode***> ((*reinterpret_cast<uintptr_t**>(I::Client))[10] + 0x5u);
	I::Globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(I::Client))[0] + 0x1Bu);
}