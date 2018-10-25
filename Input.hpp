#pragma once

#include "Common.h"
#include "Interfaces.h"
#include "Utils.h"

class CInput;

class CInput
{
public:
	CInput() {};

	HWND hwCSGO;

	POINT GetMousePos()
	{
		static POINT ptMouse;
		hwCSGO = FindWindowA(XorStr("Valve001"), NULL);

		GetCursorPos(&ptMouse);
		ScreenToClient(hwCSGO, &ptMouse);

		int iScreenWidth, iScreenHeight;
		I::EngineClient->GetScreenSize(iScreenWidth, iScreenHeight);

		ptMouse.x = U::Clamp(ptMouse.x, 1, iScreenWidth);
		ptMouse.y = U::Clamp(ptMouse.y, 1, iScreenHeight);

		return ptMouse;
	}

	void GetClicked()
	{
		if (!this) return;

		if (GetAsyncKeyState(VK_LBUTTON) && this->hwCSGO == GetActiveWindow())
		{
			bClicked = false;
			bMouseD = true;
		}
		else if (bMouseD)
		{
			bClicked = true;
			bMouseD = false;
		}
		else if (bClicked)
		{
			bClicked = false;
		}
	}

	bool Holding(int iXStart, int iYStart, int iWidth, int iHeight)
	{
		if (!this) return false;

		if (GetAsyncKeyState(VK_LBUTTON) && this->hwCSGO == GetActiveWindow())
			if (Hovering(iXStart, iYStart, iWidth, iHeight))
				return true;

		return false;
	}

	bool Hovering(int iXStart, int iYStart, int iWidth, int iHeight)
	{
		if (!this) return false;

		POINT ptMouse = this->GetMousePos();

		if (ptMouse.x >= iXStart && iXStart + iWidth >= ptMouse.x)
			if (ptMouse.y >= iYStart && iYStart + iHeight >= ptMouse.y)
				return true;

		return false;
	}

	bool Clicked(int iXStart, int iYStart, int iWidth, int iHeight)
	{
		if (!this) return false;

		if (bClicked)
			if (Hovering(iXStart, iYStart, iWidth, iHeight))
				return true;

		return false;
	}

	bool GetClick()
	{
		if (!this) return false;
		return bClicked;
	}

private:
	bool bClicked, bMouseD;
};

extern CInput* Input;