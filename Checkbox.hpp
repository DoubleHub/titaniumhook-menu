#pragma once

#include "MenuElements.hpp"

class Checkbox : public Element
{
protected:

	int size;
	std::string title;
	bool* value;

public:

	Checkbox() 
	{
		size = 14;
		title = "";
		value = nullptr;
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (IsControlOpen()) return;

		if (!visible) return;

		if (Input->Clicked(rx, ry, size, size)) {
			BUTTON_SOUND;
			*value = !*value;
		}
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawRectGradientVertical(rx, ry, size, size, *value ? V::Colors::MenuColor_First : SourceSDK::Color::LightGray(), *value ? V::Colors::MenuColor_Second : SourceSDK::Color::Gray());
		//D::DrawFilledRect(rx, ry, size, size, *value ? V::Colors::MenuColor_First : SourceSDK::Color::LightGray());
		D::DrawOutlinedRect(rx, ry, size, size, SourceSDK::Color::Black());
		D::DrawString(F::Tahoma12_Outline, rx + size + 4, ry + size / 2, SourceSDK::Color::White(), false, title.c_str());
	}

	void SetTitle(std::string _title) { title = _title; }
	std::string GetTitle() { return title; }
	bool* GetValue() { return value; }
	void SetValue(bool* value_) { value = value_; }

};