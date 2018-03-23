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

#pragma once

//---------------------------------------------------------------------------
// All the things required to handle our ASSERT mechanism
//---------------------------------------------------------------------------
#ifdef DEBUG

TOOLKIT_API VOID DisplayAssert(LPTSTR pszMsg, LPTSTR pszAssert, LPTSTR pszFile, UINT line);

// *** Include this macro at the top of any source file using *ASSERT*() macros ***
#define SZTHISFILE	static TCHAR _szThisFile[] = _T( __FILE__ );


#if _SEC_VER > 0x0602 
#define SEC_FAIL(szMsg)				\
        { static TCHAR szMsgCode[] = szMsg;                    \
        DisplayAssert(szMsgCode, _T("SEC_FAIL"), _szThisFile, __LINE__); }
#else
#define FAIL(szMsg)                                         \
        { static TCHAR szMsgCode[] = szMsg;                    \
        DisplayAssert(szMsgCode, _T("FAIL"), _szThisFile, __LINE__); }
#endif

#else  // DEBUG

#define SZTHISFILE

#if _SEC_VER > 0x0602 
#define SEC_FAIL(err)
#else
#define FAIL(err)
#endif

#endif	// DEBUG


//---------------------------------------------------------------------------
// Macro that checks a pointer for validity on input
//---------------------------------------------------------------------------
#ifdef DEBUG
#define CHECK_POINTER(val) if (!(val) || IsBadWritePtr((void *)(val), sizeof(void *))) return E_POINTER
#else  // DEBUG
#define CHECK_POINTER(val)
#endif // DEBUG


//---------------------------------------------------------------------------
// Track signatures on objects for debugging
//---------------------------------------------------------------------------
#ifdef DEBUG

#define SIG_destroyed 'XxXx'
#define DECLARE_SIGNATURE(x)    DWORD __sig
#define CHECK_SIGNATURE(x)      ASSERT(this->__sig == (x), _T("Bad signature"))
#define INIT_SIGNATURE(x)       this->__sig = (x)
#define DESTROY_SIGNATURE(x)    this->__sig = SIG_destroyed

#else // DEBUG

#define DECLARE_SIGNATURE(x)
#define CHECK_SIGNATURE(x)
#define INIT_SIGNATURE(x)
#define DESTROY_SIGNATURE(x)

#endif // DEBUG

//--- EOF -------------------------------------------------------------------
