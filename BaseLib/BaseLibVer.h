#ifndef __BASELIB_VER_H__
#define __BASELIB_VER_H__

#if !defined(_AFXDLL)
	#error MFC Lib dynamic!
#endif

#ifdef _DEBUG
 #ifdef _x64
   #pragma comment(lib, "../Lib/Debug/x64/BaseLibd.lib")
 #else
   #pragma comment(lib, "..\\Lib\\Debug\\x86\\BaseLibd.lib")
  #endif
#else
  #ifdef _x64
   #pragma comment(lib, "..\\Lib\\Release\\x64\\BaseLib.lib")
  #else
   #pragma comment(lib, "..\\Lib\\Release\\x86\\BaseLib.lib")
  #endif
#endif

#endif // End of __WG_ALUVER_H__
