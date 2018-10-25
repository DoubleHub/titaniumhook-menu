#pragma once

#include "MenuElements.hpp"

class Tab : public Element
{
protected:

	std::string title;
	std::vector<Element*> items;

public:

	Tab() {}

	void Think()
	{
		visible = parent->GetVisible() && (parent->GetTab() == GetTab());

		if (!parent->GetVisible()) return;
		if (IsControlOpen()) return;

		if (Input->Clicked(rx + (GetTab() * 111) + 13, ry + 25, 111, 32)) {
			BUTTON_SOUND;
			parent->SetTab(GetTab());
		}
	}

	void Paint()
	{
		if (!parent->GetVisible()) return;

		bool bHovering = Input->Hovering(rx + (GetTab() * 111) + 13, ry + 25, 111, 32);
		//D::DrawFilledRect(rx + (GetTab() * 111) + 13, ry + 25, 111, 32, SourceSDK::Color::DarkestGray2());

		if (parent->GetTab() != GetTab())
		{
			// Not selected tab
			D::DrawRectGradientVertical(rx + (GetTab() * 111) + 13, ry + 25, 111, 32, SourceSDK::Color::DarkestGray4(), SourceSDK::Color::DarkestGray2());
			D::DrawString(F::Tahoma12_Outline, rx + (GetTab() * 111) + 13 + 55, ry + 25 + 16, bHovering ? V::Colors::MenuColor_First : SourceSDK::Color::White(), true, XorStr("%s"), title.c_str());
		}
		else
		{
			// Selected tab
			D::DrawRectGradientVertical(rx + (GetTab() * 111) + 13, ry + 25, 111, 32, SourceSDK::Color::DarkestGray2(), SourceSDK::Color::DarkestGray2());
			D::DrawString(F::Tahoma12_Outline, rx + (GetTab() * 111) + 13 + 55, ry + 25 + 16, V::Colors::MenuColor_First, true, XorStr("%s"), title.c_str());
			//D::DrawFilledRect(rx + (GetTab() * 111) + 12, ry + 25 + 32, 111, 3, V::Colors::MenuColor_Second);
			//D::DrawOutlinedRect(rx + (GetTab() * 111) + 12, ry + 25 + 32, 111, 3, SourceSDK::Color::Black());
		}

		//if (title == XorStr("Players")) // Ghetto gui fix
		//	D::DrawLine(rx + (GetTab() * 111) + 13 + 110, ry + 25, rx + (GetTab() * 111) + 13 + 110, ry + 25 + 32, V::Colors::MenuColor_Second);

		D::DrawOutlinedRect(rx + (GetTab() * 111) + 13, ry + 25, 111, 32, SourceSDK::Color::Black());
	}

	void SetTitle(std::string _title) { title = _title; }
	std::string GetTitle() { return title; }
	void AddItem(Element* item) { Add(item); }

};