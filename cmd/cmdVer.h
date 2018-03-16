#pragma once
//#if !defined(_AFXDLL)
#ifndef _AFXDLL
#error MFC Lib
#endif
#ifdef _DEBUG
#ifdef _x64
#pragma comment(lib,"../lib/Debug/x64/cmdd.lib")
#else
#pragma comment(lib,"../lib/Debug/x86/cmdd.lib")
#endif
#else
#ifdef _x64
#pragma comment(lib,"../lib/Release/x64/cmd.lib")
#else
#pragma comment(lib,"../lib/Release/x86/cmd.lib")
#endif

#endif