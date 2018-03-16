#pragma once
//#if !defined(_AFXDLL)
#ifndef _AFXDLL
#error MFC Lib
#endif
#ifdef _DEBUG
	#ifdef _x64
		#pragma comment(lib,"../lib/Debug/x64/DBd.lib")
	#else
		#pragma comment(lib,"./lib/Debug/x86/DBd.lib")
	#endif
#else
	#ifdef _x64
		#pragma comment(lib,"../lib/Release/x64/DB.lib")
	#else
		#pragma comment(lib,"../lib/Release/x86/DB.lib")
	#endif

#endif