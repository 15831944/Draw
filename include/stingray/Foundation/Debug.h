///////////////////////////////////////////////////////////////////////////////
// Debug.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// Debug.h is a replacement for the debugging macros which 
// have become so well known in MFC. They will replace the
// ASSERT, VERIFY and TRACE macros in name but not neccesarily 
// in function. Particularly an ASSERT is very difficult to use
// to find the code that caused the error so a less drastic 
// error system will be provided here.
//
// Debug.h was written by Bob Powell (bobpowell@roguewave.com)
//

// Exclude if __AFX_H__ is defined
#ifndef __AFX_H__

#ifndef __DEBUGMACROS__
#define __DEBUGMACROS__

#pragma warning (disable : 4505)

#ifndef NONSTANDARD_GDI
	#include <crtdbg.h>
#endif //NONSTANDARD_GDI

#include <stdlib.h>
#include <windows.h>
#include <winuser.h>

#ifdef _DEBUG

#ifndef _INC_TCHAR
	#include "tchar.h"
#endif

static void DoAssert(char *pFile, int nLine)
{
	static TCHAR buffer[256];
	wsprintf(buffer,_T("Debug ASSERT failed in file %s at line %d"),pFile,nLine);
	switch(::MessageBox(NULL,(LPCTSTR)buffer,_T("DEBUG"),MB_ABORTRETRYIGNORE | MB_ICONSTOP))
	{
	case IDABORT:
#ifndef UNDER_CE
		_exit(1);
#else
		ExitThread(-1);
#endif
		break;
	case IDRETRY:
		DebugBreak(); // Step out of this routine to go back to the file that produced the error.
		break;
	case IDIGNORE:
		break;
	}
}


// /W4 warning C4505: 'DoTrace' : unreferenced local function has been removed
// The given function is local and not referenced in the body of the module; therefore, the function is dead code.
// The compiler does not generate code for this unused function.
static void DoTrace(TCHAR *pFormat,...)
{
	va_list args;
	va_start(args, pFormat);
	TCHAR buffer[512];
	int charcount = wsprintf(buffer, pFormat, args);
	if(charcount>0)
#ifndef NONSTANDARD_GDI
		_RPT1(_CRT_WARN,"%s\n",buffer);
#else // if NONSTANDARD_GDI
#endif //NONSTANDARD_GDI
	va_end(args);
}

#define ASSERT(x)\
	if(!(x))\
		DoAssert(__FILE__,__LINE__);\


#define TRACE(x) \
	DoTrace(_T("%s"),x);\

#define TRACE0(x) TRACE(x)

#define TRACE1(x,a)\
	DoTrace(x,a);\

#define TRACE2(x,a,b)\
	DoTrace(x,a,b);\

#define TRACE3(x,a,b,c)\
	DoTrace(x,a,b,c);\

#define TRACE4(x,a,b,c,d)\
	DoTrace(x,a,b,c,d);\

#define VERIFY(x) ASSERT(x)

#else // _DEBUG

#define ASSERT(x) ((void)(0))
#define VERIFY(x) ((void)(x))

#endif // _DEBUG

#endif // defined __DEBUGMACROS__

#endif // !defined __AFX_H__
