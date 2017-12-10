#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "Menu.h"
#include "Display.h"
#include "Touch.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	/* Get arguments */
	LPWSTR *argv;
    int argc;
    argv = CommandLineToArgvW(GetCommandLine(), &argc);

	/* Ensure command is good */
    if( argc < 2 )
    {
		MessageBox(
			NULL,
			(LPCWSTR)L"Missing ini file argument!",
			(LPCWSTR)L"Invalid Invocation",
			MB_ICONERROR | MB_OK | MB_DEFBUTTON1
		);
		return 1;
    }

	if( argc > 2 )
	{
		MessageBox(
			NULL,
			(LPCWSTR)L"Too many arguments specified!",
			(LPCWSTR)L"Invalid Invocation",
			MB_ICONERROR | MB_OK | MB_DEFBUTTON1
		);
		return 1;
    }

	/* Initialize menu */
	Menu *menu = new Menu(argv[1]);

	if( menu->NumberOfEntries() < 1 )
	{
		MessageBox(
			NULL,
			(LPCWSTR)L"No games configured to launch!",
			(LPCWSTR)L"Invalid Invocation",
			MB_ICONERROR | MB_OK | MB_DEFBUTTON1
		);
		return 1;
	}

	/* Initialize touch display */
	Touch *touch = new Touch();

	/* Create menu screen */
	Display *display = new Display(hInstance, menu);
	
	/* Actual game to load */
	char *path = NULL;
		
	/* It may have taken a long time to init */
	menu->ResetTimeout();

	/* Loop until time's up, then boot */
    while( true )
    {
		/* Tick all of the pieces, because nobody wants threads */
		display->Tick();
		menu->Tick();
		touch->Tick();

		/* See if somebody killed the display window */
		if (display->WasClosed())
		{
			break;
		}

		/* Check to see if we ran out of time waiting for input */
		if (menu->ShouldBootDefault())
		{
			path = menu->GetEntryPath(0);
			break;
		}

		/* Check to see if the user made a selection */
		if (touch->GetTouchHeld()) {
			double x, y;
			touch->GetTouchPosition(x, y);
			
			int entry = display->GetSelectedItem(x, y);
			if (entry >= 0) {
				path = menu->GetEntryPath(entry);
				break;
			}
		}
	}
	
	/* Kill menu and serial connection */
	delete display;
	delete touch;
	delete menu;

	if (path != NULL)
	{
		/* Launch actual game */
		system(path);
	}

    return 0;
}

