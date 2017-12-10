#pragma once

#include <stdio.h>
#include <windows.h>

#include "Menu.h"

#define CLASS_NAME L"Reflec Beat Touch Launcher"

#define ITEM_HEIGHT 75
#define ITEM_PADDING 25

class Display
{
	public:
		Display(HINSTANCE hInstance, Menu *mInst);
		~Display(void);

		void Tick();
		int GetSelectedItem(double x, double y);

	private:
		HINSTANCE inst;
		HWND hwnd;
};
