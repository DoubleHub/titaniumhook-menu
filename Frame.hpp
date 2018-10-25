#pragma once

#include "MenuElements.hpp"

class Frame : public Element
{
public:

	Frame()
	{
		visible = false;
		I::InputSystem->EnableInput(true);
	}

	void Think()
	{
		static SourceSDK::ConVar* MouseLock = I::CVars->FindVar(XorStr("cl_mouseenable"));

		if (tick == 0 && GetAsyncKeyState(V::Menu::Key))
		{
			//printf("bullshit boi\n");
			tick = 30;
			visible = !visible;
			MouseLock->SetValue(!visible);
			I::InputSystem->EnableInput(!visible);
			if (visible) I::InputSystem->ResetInputState();
		}

		if (!visible) return;
		if (IsControlOpen()) return;

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

		x = U::Clamp(x, 1, iScrW - width - 1);
		y = U::Clamp(y, 1, iScrH - height - 1);

		bWasntHolding = Input->Hovering(x, y, width, 28) && !GetAsyncKeyState(VK_LBUTTON);
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(x, y, width, height, SourceSDK::Color(60, 60, 60, 175));
		D::DrawFilledRect(x, y, width, 24, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x, y, 12, height, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x + width - 12, y, 12, height, SourceSDK::Color::DarkestGray());
		D::DrawFilledRect(x, y + height - 12, width, 12, SourceSDK::Color::DarkestGray());
		D::DrawOutlinedRect(x, y, width, height, SourceSDK::Color::Black());
		D::DrawOutlinedRect(x + 12, y + 24, width - 24, height - 36, V::Colors::MenuColor_Second);
		D::DrawString(F::Tahoma12_Outline, x + width / 2, y + 12, SourceSDK::Color::White(), true, XorStr("%s for Counter-Strike: Global Offensive [BETA %s] - %s"), CHEAT_NAME, BUILD_VERSION, BUILD_MONTH);
	}

};