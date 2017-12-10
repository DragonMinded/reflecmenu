#pragma once

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// Resolution of the display's input
#define HORIZONTAL_RESOLUTION 48
#define VERTICAL_RESOLUTION 76

class Touch
{
	public:
		Touch();
		~Touch();

		void Tick();
		void GetTouchPosition(double &xp, double &yp) { xp = x; yp = y; };
		bool GetTouchHeld() { return click; }

	private:
		HANDLE OpenSerial( const _TCHAR *arg, int baud );
		bool ValidatePacket();
		void SeparateAxis(bool *horizontal, bool *vertical);
		void GetLikelyClickPosition(bool *horizontal, bool *vertical, double *x, double *y, bool *click);

		HANDLE serial;
		unsigned char packet[22];
		bool click;
		double x, y;
};