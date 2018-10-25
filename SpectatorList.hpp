#pragma once

#include "MenuElements.hpp"
#include "CBaseEntity.h"

class SpectatorList : public Element
{
protected:

	std::vector<std::string> specs;

public:

	SpectatorList()
	{
		specs.clear();
	}

	void Think()
	{
		if (!V::PlayerList::SpectatorList) return;
		if (!I::EngineClient->IsInGame())
		{
			if (!specs.empty())
				specs.clear();
			return;
		}

		if (!IsControlOpen())
		{
			static int bWasntHolding = false;
			static int bGrabbing = false;
			static int iOffsetX = 0, iOffsetY = 0;

			POINT ptMouse = Input->GetMousePos();

			if (Input->Holding(x, y, width, 28) && !bGrabbing && bWasntHolding)
			{
				bGrabbing = true;
				iOffsetX = x - ptMouse.x;
				iOffsetY = y - ptMouse.y;
			}
			else if (bGrabbing && !GetAsyncKeyState(VK_LBUTTON))
			{
				bGrabbing = false;
				iOffsetX = 0;
				iOffsetY = 0;
			}

			if (bGrabbing)
			{
				x = ptMouse.x + iOffsetX;
				y = ptMouse.y + iOffsetY;
			}

			int iScrW, iScrH;
			I::EngineClient->GetScreenSize(iScrW, iScrH);

			x = U::Clamp(x, 0, iScrW - width);
			y = U::Clamp(y, 0, iScrH - height);

			bWasntHolding = Input->Hovering(x, y, width, 28) && !GetAsyncKeyState(VK_LBUTTON);
		}

		// THIS PART IS ACTUALLY LOGIC RELATED TO SPECTATOR LIST
		using namespace SourceSDK;

		for (int i = 1; i < MAX_CLIENTS; i++)
		{
			CBaseEntity* pEnt = (CBaseEntity*)I::ClientEntityList->GetClientEntity(i);
			if (!pEnt) continue;

			std::string strObserverName = pEnt->GetName();

			if ((pEnt->IsAlive() || pEnt->IsDormant()))
			{
				// Do not skip instantly, need to check if it was spectating before being alive or dormant
				auto it = std::find(specs.begin(), specs.end(), strObserverName);
				if (it != specs.end())
					specs.erase(it);
				continue;
			}

			CBaseEntity* pObserverTarget = pEnt->GetObserverTarget();
			if (!pObserverTarget)
			{
				// Could be that now the entity isn't spectating anymore so pOT is nullptr.
				// I need to delet it
				auto it = std::find(specs.begin(), specs.end(), strObserverName);
				if (it != specs.end())
					specs.erase(it);
				continue;
			}

			if (pObserverTarget == CBaseEntity::GetLocalPlayer())
			{
				// The observer target is ME! This entity is currently spectating me.
				// If this entity isn't present inside the list, push_back it
				if (std::find(specs.begin(), specs.end(), strObserverName) == specs.end())
					specs.push_back(strObserverName);
			}
			else
			{
				// The observer target isn't me, this entity is spectating someone else. 
				// Remove it from the list if it's present
				auto it = std::find(specs.begin(), specs.end(), strObserverName);
				if (it != specs.end())
					specs.erase(it);
			}
		}
	}

	void Paint()
	{
		if (!V::PlayerList::SpectatorList) return;
		if (!I::EngineClient->IsInGame()) return;

		height = 35 + specs.size() * 24;

		D::DrawFilledRect(x, y, width, height, SourceSDK::Color(60, 60, 60, 175));
		D::DrawFilledRect(x, y, width, 24, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x, y, 12, height, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x + width - 12, y, 12, height, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x, y + height - 12, width, 12, SourceSDK::Color::DarkestGray());
		D::DrawOutlinedRect(x, y, width, height, SourceSDK::Color::Black());
		D::DrawOutlinedRect(x + 12, y + 24, width - 24, height - 36, V::Colors::MenuColor_Second);
		D::DrawString(F::Tahoma12_Outline, x + width / 2, y + 12, SourceSDK::Color::White(), true, XorStr("Spectator List"));

		for (auto i = 0; i < specs.size(); i++)
			if (specs[i] != "")
				D::DrawString(F::Tahoma12_Outline, rx + 19, ry + 24 * (i + 1) + 12, SourceSDK::Color::White(), false, XorStr("%s"), specs[i].c_str());
	}

};