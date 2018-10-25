#pragma once

#include "MenuElements.hpp"

typedef void(*ButtonCallbackFn)();
extern void SaveConfigLegit();
extern void SaveConfigRage();
extern void LoadConfigLegit();
extern void LoadConfigRage();
extern void Panic();
extern void SaveSkins();
extern void LoadSkins();
extern void ForceFullUpdate();

class Button : public Element
{
protected:

	std::string title;
	ButtonCallbackFn fn;
	bool centered;

public:

	Button()
	{
		title = "";
		fn = nullptr;
		centered = false;
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (!visible) return;
		if (IsControlOpen()) return;

		if (Input->Clicked(rx, ry, width, height))
			if (fn != nullptr) {
				BUTTON_SOUND;
				fn();
			}
	}

	void Paint()
	{
		if (!visible) return;
		static int off = 3;

		if (Input->Holding(rx, ry, width, height))
		{
			D::DrawRectGradientVertical(rx + off, ry + off, width, height, V::Colors::MenuColor_Second, V::Colors::MenuColor_First);
			D::DrawOutlinedRect(rx + off, ry + off, width, height, SourceSDK::Color::Black());
			D::DrawString(F::Tahoma12_Outline, rx + 3 + off, ry + height / 2 + off, SourceSDK::Color::White(), centered, "%s", title.c_str());
		}
		else
		{
			D::DrawRectGradientVertical(rx, ry, width, height, V::Colors::MenuColor_First, V::Colors::MenuColor_Second);
			D::DrawOutlinedRect(rx, ry, width, height, SourceSDK::Color::Black());
			D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), centered, "%s", title.c_str());
		}
	}

	std::string GetTitle() { return title; }
	void SetTitle(std::string _title) { title = _title; }
	void SetCallback(ButtonCallbackFn _fn) { fn = _fn; }
	void SetCentered(bool _center) { centered = _center;  }

};