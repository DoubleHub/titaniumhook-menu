#pragma once

#include "MenuElements.hpp"

class ColorSlider : public Element
{
protected:
	
	int min, max;
	std::string title;
	SourceSDK::Color* value; // Must be a COLOR value

public:

	ColorSlider()
	{
		min = 0;
		max = 255;
		title = "";
		value = nullptr;
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (!visible) return;
		if (IsControlOpen()) return;

		if (value)
		{
			if (title == XorStr("R"))
				value->SetRed(U::Clamp(value->r(), min, max));
			if (title == XorStr("G"))
				value->SetGreen(U::Clamp(value->g(), min, max));
			if (title == XorStr("B"))
				value->SetBlue(U::Clamp(value->b(), min, max));
		}
	}

	void Paint()
	{
		if (!visible)
			return;

		D::DrawFilledRect(rx, ry, width, height, SourceSDK::Color::DarkestGray());

		if (title == XorStr("R"))
		{
			//D::DrawRectGradientVertical(rx, ry, value->r() * ((float(width) - 2.f) / max), height, V::Colors::MenuColor_Second, *value);
			D::DrawFilledRect(rx, ry, value->r() * ((float(width) - 2.f) / max), height, *value);
		}
		if (title == XorStr("G"))
		{
			//D::DrawRectGradientVertical(rx, ry, value->g() * ((float(width) - 2.f) / max), height, V::Colors::MenuColor_Second, *value);
			D::DrawFilledRect(rx, ry, value->g() * ((float(width) - 2.f) / max), height, *value);
		}
		if (title == XorStr("B"))
		{
			//D::DrawRectGradientVertical(rx, ry, value->b() * ((float(width) - 2.f) / max), height, V::Colors::MenuColor_Second, *value);
			D::DrawFilledRect(rx, ry, value->b() * ((float(width) - 2.f) / max), height, *value);
		}

		D::DrawOutlinedRect(rx, ry, width, height, SourceSDK::Color::Black());

		if (title == "R")
		{
			//D::DrawFilledRect(rx + value->r() * ((float(width) - 2.f) / max), ry - 2, 5, 11, *value);
			//D::DrawOutlinedRect(rx + value->r() * ((float(width) - 2.f) / max), ry - 2, 5, 11, SourceSDK::Color::Black());
		}
		if (title == "G")
		{
			//D::DrawFilledRect(rx + value->g() * ((float(width) - 2.f) / max), ry - 2, 5, 11, *value);
			//D::DrawOutlinedRect(rx + value->g() * ((float(width) - 2.f) / max), ry - 2, 5, 11, SourceSDK::Color::Black());
		}
		if (title == "B")
		{
			//D::DrawFilledRect(rx + value->b() * ((float(width) - 2.f) / max), ry - 2, 5, 11, *value);
			//D::DrawOutlinedRect(rx + value->b() * ((float(width) - 2.f) / max), ry - 2, 5, 11, SourceSDK::Color::Black());
		}

		POINT ptMouse = Input->GetMousePos();
		if (Input->Holding(rx, ry - 6, width, height + 6))
		{
			if (title == XorStr("R"))
				value->SetRed(U::Clamp((ptMouse.x - rx) * max / ((float)width - 2.f), min, max));
			if (title == XorStr("G"))
				value->SetGreen(U::Clamp((ptMouse.x - rx) * max / ((float)width - 2.f), min, max));
			if (title == XorStr("B"))
				value->SetBlue(U::Clamp((ptMouse.x - rx) * max / ((float)width - 2.f), min, max));
		}

		D::DrawString(F::Tahoma12_Outline, rx + width + 7, ry + height/2 + 1, SourceSDK::Color::White(), true, XorStr("%s"), title.c_str());
	}

	void SetValue(SourceSDK::Color* _value) { value = _value; }
	void SetTitle(std::string _title) { title = _title; }

};

class ColorPicker : public Element
{
protected:

	SourceSDK::Color* value; // MUST BE A COLOR VALUE
	Element* tab;

public:

	ColorPicker(Element* _tab)
	{
		tab = _tab;
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (!visible) return;
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(rx, ry + 45, width, height, *value);
		D::DrawOutlinedRect(rx, ry + 45, width, height, SourceSDK::Color::Black());
	}

	void CreateSliders()
	{
		static int off = 9;
		auto red_slider = new ColorSlider;
		red_slider->SetPosition(x,y);
		red_slider->SetSize(width - off, 7);
		red_slider->SetValue(value);
		red_slider->SetTitle(XorStr("R"));
		tab->Add(red_slider);
		auto green_slider = new ColorSlider;
		green_slider->SetPosition(x,y + 15);
		green_slider->SetSize(width - off, 7);
		green_slider->SetValue(value);
		green_slider->SetTitle(XorStr("G"));
		tab->Add(green_slider);
		auto blue_slider = new ColorSlider;
		blue_slider->SetPosition(x,y + 30);
		blue_slider->SetSize(width - off, 7);
		blue_slider->SetValue(value);
		blue_slider->SetTitle(XorStr("B"));
		tab->Add(blue_slider);
	}

	void SetValue(SourceSDK::Color* _value) { value = _value; }
};