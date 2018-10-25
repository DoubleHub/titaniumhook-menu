#pragma once

#include "MenuElements.hpp"

extern char* szKeyboard[112];

class Textbox : public Element
{
protected:

	bool waiting;
	std::string title;
	std::string value;
	char* value_ptr;
	int iMaxLength;

	void MakeSpecial(int i)
	{
		if (i == 0x31) // 1 -> !
		{
			value += XorStr("!");
		}
		else if (i == 0x34) // 4 -> $
		{
			value += XorStr("$");
		}
		else if (i == 0x35) // 5 -> %
		{
			value += XorStr("%");
		}
		else if (i == 0x36) // 6 -> &
		{
			value += XorStr("&");
		}
		else if (i == 0x38) // 8 -> (
		{
			value += XorStr("(");
		}
		else if (i == 0x39) // 9 -> )
		{
			value += XorStr(")");
		}
		else if (i == 0x30) // 0 -> =
		{
			value += XorStr("=");
		}
		else
		{
			std::string key = std::string(szKeyboard[i]);
			std::transform(key.begin(), key.end(), key.begin(), ::toupper);
			value += key;
		}
		BUTTON_SOUND;
	}

public:

	bool bIsSkinName;
	Combobox* par_WeapList;

	Textbox()
		: value("")
	{
		waiting = false;
		title = "";
		bIsSkinName = false;
		iMaxLength = 1024;
		par_WeapList = nullptr;
	}

	void Think()
	{
		visible = parent->GetVisible();

		if (!visible) return;
		if (IsControlOpen()) return;

		if (GetAsyncKeyState(VK_BACK) == -32767)
		{
			if (!bIsSkinName)
			{
				if (value.length() > 0 && value.length() < iMaxLength)
					value.erase(value.end() - 1);
			}
			else
			{
				for (auto& e : GetSkinConfigList())
				{
					if (par_WeapList->FancyWeaponNameToRaw(par_WeapList->GetCurrentItem()) == e.WeaponName)
					{
						if (e.CustomName.length() > 0 && e.CustomName.length() < iMaxLength)
							e.CustomName.erase(e.CustomName.end() - 1);
					}
				}
			}
		}

		if (waiting && D::GetStringWidth(F::Tahoma12_Outline, value.c_str()) < width)
		{
			for (int i = 1; i < 112; i++)
			{
				if (i == 3 || i == 13)
					continue;
				if (GetAsyncKeyState(VK_LBUTTON))
					continue;
				if (GetAsyncKeyState(VK_BACK))
				{
					if (value.length() > 0)
						value.erase(value.end());
				}
				if (GetAsyncKeyState(i) == -32767 && tick == 0)
				{
					if (value.length() < iMaxLength)
					{
						if (GetAsyncKeyState(VK_SHIFT) && tick == 0)
							MakeSpecial(i);
						else 
						{
							value += *szKeyboard[i];
							BUTTON_SOUND;
						}
					}
					
					if (bIsSkinName && par_WeapList)
					{
						for (auto& e : GetSkinConfigList())
						{
							if (par_WeapList->FancyWeaponNameToRaw(par_WeapList->GetCurrentItem()) == e.WeaponName)
							{
								e.CustomName += szKeyboard[i];
								BUTTON_SOUND;
							}
						}
					}
				}
				if (GetAsyncKeyState(VK_TAB) == -32767 && tick == 0)
				{
					waiting = false;
				}
			}

			if (Input->GetClick())
			{
				POINT mouse = Input->GetMousePos();
				if (mouse.x < rx || mouse.x > rx + width
					|| mouse.y < ry || mouse.y > ry + height)
				{
					waiting = false;
				}
			}
		}
		else if (Input->Clicked(rx, ry, width, height))
		{
			waiting = true;
		}

		value_ptr = const_cast<char*>(value.c_str());
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(rx, ry, width, height, SourceSDK::Color::DarkestGray3());
		D::DrawString(F::Tahoma12_Outline, rx + 3, ry - 7, SourceSDK::Color::White(), false, XorStr("%s"), title.c_str());
		if (!bIsSkinName)
		{
			D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), false, XorStr("%s"), value.c_str());
			if (waiting)
				D::DrawString(F::Tahoma12_Outline, rx + D::GetStringWidth(F::Tahoma12_Outline, XorStr("%s"), value.c_str()), ry + height / 2, SourceSDK::Color::White(), false, XorStr("|"));
		}
		else
		{
			for (auto& e : GetSkinConfigList())
			{
				if (par_WeapList->FancyWeaponNameToRaw(par_WeapList->GetCurrentItem()) == e.WeaponName)
				{
					D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), false, XorStr("%s"), e.CustomName.c_str());
					if (waiting)
						D::DrawString(F::Tahoma12_Outline, rx + D::GetStringWidth(F::Tahoma12_Outline, XorStr("%s"), e.CustomName.c_str()), ry + height / 2, SourceSDK::Color::White(), false, XorStr("|"));
				}
			}
		}
	}

	std::string GetTitle() { return title; }
	std::string GetValue() { return value; }
	void SetTitle(std::string _title) { title = _title; }
	void SetValue(char* _value) { value_ptr = _value; }
	void SetMaxLen(int iLen) { iMaxLength = iLen; }
};

class Textbox_NumbersOnly : public Textbox
{
public:

	void Think()
	{
		visible = parent->GetVisible();

		if (!visible) return;

		if (GetAsyncKeyState(VK_BACK) == -32767)
		{
			if (value.length() > 0 && value.length() < iMaxLength)
				value.erase(value.end() - 1);
		}

		if (waiting && D::GetStringWidth(F::Tahoma12_Outline, value.c_str()) < width)
		{
			for (int i = 0x30; i <= 0x39; i++)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
					continue;
				if (GetAsyncKeyState(i) == -32767 && tick == 0)
				{
					if (value.length() < iMaxLength)
						value += *szKeyboard[i];
				}
				if (GetAsyncKeyState(VK_TAB) == -32767 && tick == 0)
					waiting = false;
			}

			if (Input->GetClick())
			{
				POINT mouse = Input->GetMousePos();
				if (mouse.x < rx || mouse.x > rx + width
					|| mouse.y < ry || mouse.y > ry + height)
				{
					waiting = false;
				}
			}
		}
		else if (Input->Clicked(rx, ry, width, height))
		{
			waiting = true;
		}
	}

};