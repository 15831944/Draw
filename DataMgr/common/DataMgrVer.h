#pragma once
//#if !defined(_AFXDLL)
#ifndef _AFXDLL
#error MFC Lib
#endif
#ifdef _DEBUG
	#ifdef _x64
		#pragma comment(lib,"../../lib/Debug/x64/DataMgrd.lib")
	#else
		#pragma comment(lib,"../../lib/Debug/x86/DataMgrd.lib")
	#endif
#else
	#ifdef _x64
		#pragma comment(lib,"../../lib/Release/x64/DataMgr.lib")
	#else
		#pragma comment(lib,"../../lib/Release/x86/DataMgr.lib")
	#endif

#endif