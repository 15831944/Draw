#pragma once
//#if !defined(_AFXDLL)
#ifndef _AFXDLL
#error MFC Lib
#endif
#ifdef _DEBUG
#ifdef _x64
#pragma comment(lib,"../lib/Debug/x64/testd.lib")
#else
#pragma comment(lib,"../lib/Debug/x86/testd.lib")
#endif
#else
#ifdef _x64
#pragma comment(lib,"../lib/Release/x64/test.lib")
#else
#pragma comment(lib,"../lib/Release/x86/test.lib")
#endif

#endif