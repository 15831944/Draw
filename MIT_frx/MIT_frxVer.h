#ifndef __MIT_FRXVER_H__
#define __MIT_FRXVER_H__

#if !defined(_AFXDLL)
	#error MFC Lib를 Shared Lib로 지정해야 합니다 !
#endif

#if defined(_AFXEXT)
  #define MITFRX_LIBPATH "../../lib/Build"
#else
  #define MITFRX_LIBPATH "../lib/Build"
#endif 

#if _MSC_VER >= 1700  // vc++ 11.0
  #define MITFRX_DEVENVVER_PATH ""
#else
  #define MITFRX_DEVENVVER_PATH "/vc90"
#endif 

#if defined(_DEBUG)
	#if defined(_IGEN)
		#define MITFRX_DEBUGORRELEASE "/iGenDebug"
	#elif defined(_MGEN)	
		#define MITFRX_DEBUGORRELEASE "/Debug"
	#else
		#define MITFRX_DEBUGORRELEASE "/CivilDebug"
	#endif
#else
	#if defined(_IGEN)
		#define MITFRX_DEBUGORRELEASE "/iGenRelease"
	#elif defined(_MGEN)
		#define MITFRX_DEBUGORRELEASE "/Release"
	#else
		#define MITFRX_DEBUGORRELEASE "/CivilRelease"
	#endif
#endif

#define MITFRX_SUBMDL ""
#if defined(_EDU)
  #define MITFRX_SUBMDL "_EDU"
#endif

#if defined(_CH)
  #define MITFRX_COUNTRY "_CH"
#elif defined(_US)
	#define MITFRX_COUNTRY "_US"
#elif defined(_JP)
	#define MITFRX_COUNTRY "_JP"
#elif defined(_RUS)
	#define MITFRX_COUNTRY "_RUS"
#else
  #define MITFRX_COUNTRY ""
#endif

#if !defined(_X64)
  #define MITFRX_PLATFORM "/x86"
#else
  #define MITFRX_PLATFORM "/x64"
#endif

#define MITFRX_LIBNAME "/MIT_frx.lib"

// MITFRX_LIBPATH MITFRX_DEVENVVER_PATH MITFRX_DEBUGORRELEASE MITFRX_PLATFORM MITFRX_LIBNAME
// ex) "../../lib/debug/x86/MIT_frx.lib"
// ex) "../lib/release/x64/MIT_frx.lib"
// ex) "../../lib/vc90/release/x64/MIT_frx.lib"
//#pragma message( "automatically link with (" MITFRX_LIBPATH MITFRX_DEVENVVER_PATH MITFRX_DEBUGORRELEASE MITFRX_COUNTRY MITFRX_PLATFORM MITFRX_LIBNAME ")")
#define AUTOLIBNAME   MITFRX_LIBPATH MITFRX_DEVENVVER_PATH MITFRX_DEBUGORRELEASE MITFRX_SUBMDL MITFRX_COUNTRY MITFRX_PLATFORM MITFRX_LIBNAME

// Perform autolink here:
#pragma message( "automatically link with (" AUTOLIBNAME ")")
#pragma comment(lib, AUTOLIBNAME)
#undef AUTOLIBNAME
#endif // End of __MIT_FRXVER_H__
