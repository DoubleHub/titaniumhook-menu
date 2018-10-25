#pragma once

#include "MenuElements.hpp"

extern char* szKeyNames[112];

class KeyReader : public Element
{
protected:

	bool waiting;
	std::string title;
	int* value;

public:

	KeyReader()
	{
		waiting = false;
		title = "";
		value = nullptr;
	}

	void Think()
	{
		visible = parent->GetVisible();

		if (!visible) return;

		if (IsControlOpen()) return;

		if (waiting)
		{
			for (int i = 1; i < 112; i++)
			{
				if (i == 3 || i == 13)
					continue;
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					BUTTON_SOUND;
					tick = 30;
					*value = VK_LBUTTON;
					waiting = false;
				}
				if (GetAsyncKeyState(i) == -32767 && tick == 0)
				{
					BUTTON_SOUND;
					*value = i;
					waiting = false;
				}
			}
		}
		else if (Input->Clicked(rx, ry, width, height) && tick == 0)
		{
			BUTTON_SOUND;
			waiting = true;
		}
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(rx, ry, width, height, SourceSDK::Color::DarkestGray3());
		D::DrawString(F::Tahoma12_Outline, rx + 3, ry - 7, SourceSDK::Color::White(), false, XorStr("%s"), title.c_str());
		D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), false, XorStr("%s"), waiting ? XorStr("Press Key...") : szKeyNames[*value]);
	}

	std::string GetTitle() { return title; }
	void SetTitle(std::string _title) { title = _title; }
	void SetValue(int* _value) { value = _value; }

};