#include "stdafx.h"

static AFX_EXTENSION_MODULE testddll = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("WG_TEST.DLL Initializing!\n");

		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(testddll, hInstance))
			return 0;
		new CDynLinkLibrary(testddll);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("WG_DGN.DLL Terminating!\n");
		AfxTermExtensionModule(testddll);
	}
	return 1;   // ok
}