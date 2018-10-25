#pragma once

#include "MenuElements.hpp"

class Slider : public Element
{
protected:

	float min, max;
	std::string title;
	float* value;

public:

	Slider()
	{
		min = 0.f;
		max = 100.f;
		title = "";
		value = nullptr;
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (!visible) return;
		if (IsControlOpen()) return;

		if (value)
			*value = U::Clamp(*value, min, max);

		POINT ptMouse = Input->GetMousePos();
		if (Input->Holding(rx, ry - 6, width, height + 6)) {
			*value = U::Clamp((ptMouse.x - rx) * max / ((float)width - 2.f), min, max);
		}
		
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(rx, ry, width, height, SourceSDK::Color::DarkestGray());
		D::DrawRectGradientVertical(rx, ry, *value * ((float(width) - 2.f) / max), height, V::Colors::MenuColor_First, V::Colors::MenuColor_Second);
		D::DrawOutlinedRect(rx, ry, width, height, SourceSDK::Color::Black());
		//D::DrawFilledRect(rx + *value * ((float(width) - 2.f) / max), ry - 2, 5, 11, V::Colors::MenuColor_Second);
		//D::DrawOutlinedRect(rx + *value * ((float(width) - 2.f) / max), ry - 2, 5, 11, SourceSDK::Color::Black());

		D::DrawString(F::Tahoma12_Outline, rx + width / 2, ry - 10, SourceSDK::Color::White(), true, XorStr("%s"), title.c_str());
		D::DrawString(F::Tahoma12_Outline, rx + width / 2, ry + 20, SourceSDK::Color::White(), true, XorStr("%.1f"), *value);
	}

	float GetMin() { return min; }
	float GetMax() { return max; }
	std::string GetTitle() { return title; }
	float* GetValue() { return value; }
	void SetMin(float _min) { min = _min; }
	void SetMax(float _max) { max = _max; }
	void SetTitle(std::string _title) { title = _title; }
	void SetValue(float* _value) { value = _value; }
};