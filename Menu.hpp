#pragma once

#include "MenuElements.hpp"

class CMenu
{
private:

	std::vector<Element*> elements;
	Element* frame;

public:

	void Setup();

	void Paint()
	{
		if (IsDetached()) return;
		Input->GetClicked();

		for (Element* pElement : elements)
		{
			if (pElement->is_separate_frame)
				pElement->Tick();
		}

		POINT ptMouse = Input->GetMousePos();
		if (frame && frame->GetVisible())
		{
			for (Element* pElement : elements)
			{
				if (pElement)
				{
					if (!pElement->is_separate_frame)
						pElement->Tick();
				}
			}

			static int mouseSize = 25;
			static SourceSDK::Vertex_t mouseShape[3];
			mouseShape[0].Init(Vector2(ptMouse.x, ptMouse.y));
			mouseShape[1].Init(Vector2(ptMouse.x + mouseSize, ptMouse.y + mouseSize / 2));
			mouseShape[2].Init(Vector2(ptMouse.x + mouseSize / 2, ptMouse.y + mouseSize));

			D::DrawPolygon(3, mouseShape, SourceSDK::Color::White());
		}
	}

	void Add(Element* element)
	{
		elements.push_back(element);
	}

	Element* GetFrame()
	{
		return frame;
	}

};

extern CMenu* Menu;