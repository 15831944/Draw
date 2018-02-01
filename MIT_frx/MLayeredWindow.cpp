#include "stdafx.h"
#include "MLayeredWindow.h"

using namespace mit;
using namespace mit::frx;

/**************************************************************
 * MakeWindowTrasparent(window, factor)
 *
 * A function that will try to make a window transparent
 * (layered) under versions of Windows that support that kind
 * of thing. Gracefully fails on versions of Windows that
 * don't.
 *
 * Returns FALSE if the operation fails.
 */

typedef DWORD (WINAPI *PSLWA)(HWND, DWORD, BYTE, DWORD);

static PSLWA pSetLayeredWindowAttributes = NULL;
static BOOL initialized = FALSE;

bool MLayeredWindow::MakeTransparent(HWND hWnd, unsigned char factor)
{
	/* First, see if we can get the API call we need. If we've tried
	 * once, we don't need to try again. */
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary (_T("user32"));

		pSetLayeredWindowAttributes = 
			(PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

	/* Windows need to be layered to be made transparent. This is done
		* by modifying the extended style bits to contain WS_EX_LAYARED. */
	SetLastError(0);

	SetWindowLongPtr(hWnd, 
				GWL_EXSTYLE , 
				GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	if (GetLastError())
		return FALSE;

	/* Now, we need to set the 'layered window attributes'. This
	* is where the alpha values get set. */
	return pSetLayeredWindowAttributes (hWnd, 
                                        RGB(0,0,1), 
                                        factor,
										LWA_COLORKEY|LWA_ALPHA) > 0 ? true : false;
}

bool MLayeredWindow::MakeWindowTransparent(CWnd *w, unsigned char factor)
{
	HWND wnd = w->GetSafeHwnd();

	ASSERT(wnd);

	return MakeTransparent(wnd, factor);
}