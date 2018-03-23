///////////////////////////////////////////////////////////////////////////////
// GXIME.h
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
//
// Author: Stefan Hoenig
//

// Support for IME window. If you would like to enable your
// application for IME/Win95, following steps are necessary
// a) Insert
//      GX_IMPLEMENT_IME()
// in your application class .CPP file.
//
// b) Insert
//      GXEnableIme();
// into your InitInstance method.
//
// c) Change the Project Settings. Open Link and enter
//      imm32.lib
// in the object library/modules edit box.
//

#ifndef _GXIME_H_
#define _GXIME_H_

#if _MFC_VER >= 0x0400

#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif

#ifndef _IMM_
#include <imm.h>
#endif

// // #include <StingrayExportDefs.h>

class GRID_API CGXNoImeProxy
{
public:
	virtual HIMC ImmGetContext(HWND m_hWnd) = 0;
	virtual BOOL ImmSetOpenStatus(HIMC hImc, BOOL bOpen) = 0;
	virtual BOOL ImmGetOpenStatus(HIMC hIMC) = 0;
};

class CGXImeProxy: public CGXNoImeProxy
{
public:
	GRID_API virtual HIMC ImmGetContext(HWND m_hWnd);
	GRID_API virtual BOOL ImmSetOpenStatus(HIMC hImc, BOOL bOpen);
	GRID_API virtual BOOL ImmGetOpenStatus(HIMC hIMC);
};

#define GX_IMPLEMENT_IME() \
HIMC CGXImeProxy::ImmGetContext(HWND m_hWnd) { return ::ImmGetContext(m_hWnd); } \
BOOL CGXImeProxy::ImmSetOpenStatus(HIMC hImc, BOOL bOpen) { return ::ImmSetOpenStatus(hImc, bOpen); } \
BOOL CGXImeProxy::ImmGetOpenStatus(HIMC hIMC) { return ::ImmGetOpenStatus(hIMC); }
// END GX_IMPLEMENT_IME

inline void AFXAPI GXEnableIme()
{
	ASSERT(GXGetImeState()->m_pImeProxy == NULL);
	if (::GetSystemMetrics(SM_DBCSENABLED))
		GXGetImeState()->m_pImeProxy = new CGXImeProxy;
}

// NOTE: if CGXImeProxy is undeclared, you have to insert
// GX_IMPLEMENT_IME()
// in your application class .CPP file.

#endif // _MFC_VER >= 0x0400

#endif
