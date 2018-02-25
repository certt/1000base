#include "Main.h"

void CMenu::Menu()
{
	ImGui::Begin("1000base", &g_Globals->RenderInit, ImVec2(400, 300), 1.0f);
	{
		if (I::Engine->IsInGame() && I::Engine->IsConnected())
			ImGui::Text("Local player is spawned!");

		ImGui::PushFont(g_Globals->Font1);
		ImGui::Text("Test1");
		ImGui::PopFont();
		ImGui::PushFont(g_Globals->Font2);
		ImGui::Text("Test2");
		ImGui::PopFont();
	}
	ImGui::End();
}