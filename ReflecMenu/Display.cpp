#include <stdio.h>
#include <windows.h>

#include "Display.h"
#include "Menu.h"

Menu *globalMenu;
int resX, resY;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			/* Paint the window background */
			HBRUSH background = CreateSolidBrush(RGB(0,0,0));
            FillRect(hdc, &ps.rcPaint, background);
			DeleteObject(background);

			/* Set up text display */
			SetTextColor(hdc, RGB(240, 240, 240));
			SetBkMode(hdc, TRANSPARENT);
			SetBkColor(hdc, RGB(24, 24, 24));
			HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, L"Verdana");
			SelectObject(hdc, hFont);

			/* Set up brush colors */
			SelectObject(hdc, GetStockObject(DC_PEN));
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(24,24,24));
            SetDCPenColor(hdc, RGB(255,255,255));
        
			/* Draw each menu item */
			for( unsigned int i = 0; i < globalMenu->NumberOfEntries(); i++ ) {
				unsigned int top = ((ITEM_HEIGHT + ITEM_PADDING) * i) + ITEM_PADDING;
				unsigned int bottom = top + ITEM_HEIGHT;
				unsigned int left = ITEM_PADDING;
				unsigned int right = resX - ITEM_PADDING;
				
				/* Draw bounding rectangle */
				Rectangle(hdc, left, top, right, bottom);

				/* Draw text */
				RECT rect;
				rect.top = top;
				rect.bottom = bottom;
				rect.left = left;
				rect.right = right;
				
				wchar_t* wString = new wchar_t[4096];
				MultiByteToWideChar(CP_ACP, 0, globalMenu->GetEntryName(i), -1, wString, 4096);
				DrawText(hdc, wString, -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);
				delete wString;
        	}

			DeleteObject(hFont);
			
            EndPaint(hwnd, &ps);
			break;
	}

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

Display::Display(HINSTANCE hInstance, Menu *mInst)
{
	inst = hInstance;
	globalMenu = mInst;

	// Register the callback
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = inst;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

	// Get window sizes
	GetDesktopResolution(resX, resY);

	// Create an empty window
	hwnd = CreateWindow(CLASS_NAME, 0, WS_BORDER, 0, 0, resX, resY, NULL, NULL, inst, NULL);
	SetWindowLong(hwnd, GWL_STYLE, 0);
	ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
	ShowCursor(false);
}

Display::~Display(void)
{
	ShowCursor(true);
	DestroyWindow(hwnd);
	UnregisterClass(CLASS_NAME, inst);
}

void Display::Tick(void)
{
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
}

int Display::GetSelectedItem(double x, double y)
{
	int realX = (int)(x * (double)resX);
	int realY = (int)(y * (double)resY);

	for( unsigned int i = 0; i < globalMenu->NumberOfEntries(); i++ ) {
		int top = ((ITEM_HEIGHT + ITEM_PADDING) * i) + ITEM_PADDING;
		int bottom = top + ITEM_HEIGHT;
		int left = ITEM_PADDING;
		int right = resX - ITEM_PADDING;

		if (realX >= left && realX <= right && realY >= top && realY <= bottom) {
			return i;
		}
	}
	return -1;
}