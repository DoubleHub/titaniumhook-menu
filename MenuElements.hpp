#pragma once

#include "Drawings.h"
#include "SkinParser.hpp"
#include "Input.hpp"

class Element
{
protected:

	int x, y, rx, ry, ox, oy, width, height, tab, tick;
	bool visible;
	Element* parent;
	std::vector<Element*> children;

public:

	bool is_separate_frame;

	Element()
	{
		x = y = rx = ry = ox = oy = tab = tick = 0;
		width = height = 100;
		parent = nullptr;
		visible = false;
	}

	void Tick()
	{
		if (IsDetached()) return;
		if (tick > 0) --tick;

		if (parent)
		{
			rx = x + parent->ox + parent->rx;
			ry = y + parent->oy + parent->ry;
		}
		else
		{
			rx = x + ox;
			ry = y + oy;
		}

		Think();
		Paint();

		if (!children.empty())
			for (Element* pChild : children)
				if (pChild) pChild->Tick();
	}

	virtual void Think() {}
	virtual void Paint() {}

	void SetPosition(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	void GetPosition(int& x_, int& y_)
	{
		x_ = x;
		y_ = y;
	}

	void SetSize(int width_, int height_)
	{
		width = width_;
		height = height_;
	}

	void GetSize(int& width_, int& height_)
	{
		width = width_;
		height = height_;
	}

	void SetVisible(bool visible_) { visible = visible_; }
	bool GetVisible() { return visible; }
	void SetTab(int tab_) { tab = tab_; }
	int GetTab() { return tab; }
	int GetRealX() { return rx; }
	int GetRealY() { return ry; }
	int GetOffsetX() { return ox; }
	int GetOffsetY() { return oy; }

	void Add(Element* pElement)
	{
		pElement->parent = this;
		children.push_back(pElement);
	}

};

#include "Frame.hpp"
#include "Tab.hpp"
#include "Checkbox.hpp"
#include "Groupbox.hpp"
#include "Combobox.hpp"
#include "KeyReader.hpp"
#include "Slider.hpp"
#include "Textbox.hpp"
#include "ColorPicker.hpp"
#include "PlayerList.hpp"
#include "Button.hpp"
#include "SpectatorList.hpp"
#include "Radar.hpp"

extern void FillComboBox_Hitbox(Combobox* pCombobox);