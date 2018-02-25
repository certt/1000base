#include "Main.h"

void Visuals::ESP()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected()) {
		for (int i = 1; i <= I::Engine->GetMaxClients(); ++i)
		{
			C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
			if (!Entity
				|| !Entity->GetLifeState() == 0
				|| !Entity->GetHealth() > 0)
				continue;

			Vector vecBottom, vecScreenBottom, vecScreenOrigin;
			Vector vecOrigin = vecBottom = Entity->GetOrigin();
			vecBottom.z += (Entity->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
			if (!g_Utils->WorldToScreen(vecBottom, vecScreenBottom) || !g_Utils->WorldToScreen(vecOrigin, vecScreenOrigin))
				continue;
			float lineHeight = (vecScreenOrigin.y - vecScreenBottom.y);
			float edgeWidth = lineHeight / 4;
			float lineWidth = edgeWidth;
			edgeWidth /= 1.5f;
			Vector leftUpCorn = Vector(vecScreenOrigin.x - lineWidth - LINE_WIDTH, vecScreenBottom.y, 0.f);
			Vector rightUpCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenBottom.y, 0.f);
			Vector leftDownCorn = Vector(vecScreenOrigin.x - lineWidth, vecScreenOrigin.y, 0.f);
			Vector rightDownCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenOrigin.y, 0.f);

			int screenWidth, screenHeight;
			I::Engine->GetScreenSize(screenWidth, screenHeight);
			g_ImRender->DrawString(g_Globals->Font1, screenWidth / 2, screenHeight / 2, Color::White(), "really gay");
			g_ImRender->DrawString(g_Globals->Font2, screenWidth / 2, screenHeight / 2, Color::White(), "gay");
			g_ImRender->DrawEspBox(leftUpCorn, rightDownCorn, Color::Red(), 3);
			g_ImRender->DrawWave(vecOrigin, 50, Color::Green(), 3);
		}
	}
}