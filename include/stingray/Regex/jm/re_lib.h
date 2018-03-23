/*
 *
 * Copyright (c) 1998-9
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   FILE     re_lib.h
  *   VERSION  2.24
  *   Automatic library file inclusion.
  */


#ifndef RE_LIB_H
#define RE_LIB_H


#if defined(_MSC_VER) && !defined(RE_BUILD_DLL)
#ifdef __SGI_STL_PORT
   #ifdef _DLL
      #ifdef _DEBUG
		#if(_MSC_VER >= 1500)
			#pragma comment(lib, "vc9-stlport-re200dl.lib")
		#elif(_MSC_VER >= 1400)
			#pragma comment(lib, "vc8-stlport-re200dl.lib")
		#elif(_MSC_VER >= 1310)
			#pragma comment(lib, "vc71-stlport-re200dl.lib")
		#else
			#pragma comment(lib, "vc6-stlport-re200dl.lib")
		#endif //_MSC_VER >= 1400
      #else // DEBUG
		#if(_MSC_VER >= 1500)
			#pragma comment(lib, "vc9-stlport-re200l.lib")
		#elif(_MSC_VER >= 1400)
			#pragma comment(lib, "vc8-stlport-re200l.lib")
		#elif(_MSC_VER >= 1310)
			#pragma comment(lib, "vc71-stlport-re200l.lib")
		#else
			#pragma comment(lib, "vc6-stlport-re200l.lib")
		#endif //_MSC_VER >= 1400
      #endif // _DEBUG
   #else // _DLL
      #ifdef _MT
         #ifdef _DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-stlport-re200dm.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-stlport-re200dm.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-stlport-re200dm.lib")
			#else
				#pragma comment(lib, "vc6-stlport-re200dm.lib")
			#endif //_MSC_VER >= 1400
         #else //_DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-stlport-re200m.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-stlport-re200m.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-stlport-re200m.lib")
			#else
				#pragma comment(lib, "vc6-stlport-re200m.lib")
			#endif //_MSC_VER >= 1400
         #endif //_DEBUG
      #else //_MT
         #ifdef _DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-stlport-re200d.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-stlport-re200d.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-stlport-re200d.lib")
			#else
				#pragma comment(lib, "vc6-stlport-re200d.lib")
			#endif //_MSC_VER >= 1400
         #else //_DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-stlport-re200.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-stlport-re200.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-stlport-re200.lib")
			#else
				#pragma comment(lib, "vc6-stlport-re200.lib")
			#endif //_MSC_VER >= 1400
         #endif //_DEBUG
      #endif //_MT
   #endif //_DLL
#else
   #ifdef _DLL
      #ifdef _DEBUG
		#if(_MSC_VER >= 1500)
			#pragma comment(lib, "vc9-re200dl.lib")
		#elif(_MSC_VER >= 1400)
			#pragma comment(lib, "vc8-re200dl.lib")
		#elif(_MSC_VER >= 1310)
			#pragma comment(lib, "vc71-re200dl.lib")
		#else
			#pragma comment(lib, "vc6-re200dl.lib")
		#endif //_MSC_VER >= 1400
      #else // DEBUG
		#if(_MSC_VER >= 1500)
			#pragma comment(lib, "vc9-re200l.lib")
		#elif(_MSC_VER >= 1400)
			#pragma comment(lib, "vc8-re200l.lib")
		#elif(_MSC_VER >= 1310)
			#pragma comment(lib, "vc71-re200l.lib")
		#else
			#pragma comment(lib, "vc6-re200l.lib")
		#endif //_MSC_VER >= 1400
      #endif // _DEBUG
   #else // _DLL
      #ifdef _MT
         #ifdef _DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-re200dm.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-re200dm.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-re200dm.lib")
			#else
				#pragma comment(lib, "vc6-re200dm.lib")
			#endif //_MSC_VER
         #else //_DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-re200m.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-re200m.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-re200m.lib")
			#else
				#pragma comment(lib, "vc6-re200m.lib")
			#endif //_MSC_VER >= 1400
         #endif //_DEBUG
      #else //_MT
         #ifdef _DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-re200d.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-re200d.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-re200d.lib")
			#else
				#pragma comment(lib, "vc6-re200d.lib")
			#endif //_MSC_VER >= 1400
         #else //_DEBUG
			#if(_MSC_VER >= 1500)
				#pragma comment(lib, "vc9-re200.lib")
			#elif(_MSC_VER >= 1400)
				#pragma comment(lib, "vc8-re200.lib")
			#elif(_MSC_VER >= 1310)
				#pragma comment(lib, "vc71-re200.lib")
			#else
				#pragma comment(lib, "vc6-re200.lib")
			#endif //_MSC_VER >= 1400
         #endif //_DEBUG
      #endif //_MT
   #endif //_DLL
#endif // __SGI_STL_PORT
#endif //BOOST_MSVC


#if defined(__BORLANDC__) && !defined(RE_BUILD_DLL)
   
   #if __BORLANDC__ < 0x550
   
   #ifdef RE_USE_VCL
   
      #ifdef _RTLDLL
         #pragma comment(lib, "bcb4re200lv.lib")
      #else
         #pragma comment(lib, "bcb4re200v.lib")
      #endif
   
   #else // VCL
   
   #ifdef _RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb4re200lm.lib")
      #else // __MT__
         #pragma comment(lib, "bcb4re200l.lib")
      #endif // __MT__
   #else //_RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb4re200m.lib")
      #else // __MT__
         #pragma comment(lib, "bcb4re200.lib")
      #endif // __MT__
   #endif // _RTLDLL
   
   #endif // VCL
   
   #else // C++ Builder 5:

   #ifdef RE_USE_VCL
   
      #ifdef _RTLDLL
         #pragma comment(lib, "bcb5re200lv.lib")
      #else
         #pragma comment(lib, "bcb5re200v.lib")
      #endif
   
   #else // VCL
   
   #ifdef _RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb5re200lm.lib")
      #else // __MT__
         #pragma comment(lib, "bcb5re200l.lib")
      #endif // __MT__
   #else //_RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb5re200m.lib")
      #else // __MT__
         #pragma comment(lib, "bcb5re200.lib")
      #endif // __MT__
   #endif // _RTLDLL
   
   #endif // VCL
   
   #endif   
   
#endif //__BORLANDC__

#endif // RE_LIB_H




