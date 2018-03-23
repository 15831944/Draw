///////////////////////////////////////////////////////////////////////////////
// Helpers.h
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


#ifndef __SECHELPERS_H_
#define __SECHELPERS_H_

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL


//little MFC helper function
TOOLKIT_API BOOL ExtractBetween( const CString &strSource,
					                       const CString &strLeft, 
					                       const CString &strRight,
					                       CString &strMiddle );

//Parsing Support
TOOLKIT_API int FindToken( char    *pszCur,
                           char   **ppszBeginArg,
                           char   **ppszNextLine,
                           HRESULT *phr,
                           char   **ppszError );

//---------------------------------------------------------------------------
// To make the OLE-related code easier to read
//---------------------------------------------------------------------------
#if _SEC_VER > 0x0602 
#define CHECK(x)       { hr = (x);  if (hr) { SEC_FAIL(_T("Bad hr")); goto CleanUp; } }
#define CHECKSZ(x,sz)  { hr = (x);  if (hr) { SEC_FAIL(sz);       goto CleanUp; } }
#define CHECKCL(x)     { hr = (x);  if (hr) { SEC_FAIL(_T("Bad hr")); goto CheckLoop; } }
#define ARGSZ(f,sz)    {            if (f)  { SEC_FAIL(sz);       return E_INVALIDARG; } }
#define CHECKOS(x) { if (ERROR_SUCCESS!=(x)) { SEC_FAIL(_T("Bad")); hr=E_FAIL; goto CleanUp; } }
#else
#define CHECK(x)       { hr = (x);  if (hr) { FAIL(_T("Bad hr")); goto CleanUp; } }
#define CHECKSZ(x,sz)  { hr = (x);  if (hr) { FAIL(sz);       goto CleanUp; } }
#define CHECKCL(x)     { hr = (x);  if (hr) { FAIL(_T("Bad hr")); goto CheckLoop; } }
#define ARGSZ(f,sz)    {            if (f)  { FAIL(sz);       return E_INVALIDARG; } }
#define CHECKOS(x) { if (ERROR_SUCCESS!=(x)) { FAIL(_T("Bad")); hr=E_FAIL; goto CleanUp; } }
#endif

#define RELEASEPTRTYPE(p,typ) \
  {                           \
    if (p)                    \
      {                       \
      typ *__punk = (p);      \
      (p) = NULL;             \
      __punk->Release();      \
      }                       \
  }

#define RELEASEPTR(p)     RELEASEPTRTYPE(p,IUnknown)


//---------------------------------------------------------------------------
// Allocates a temporary buffer that will disappear when it goes out of scope
// NOTE: Be careful of that-- make sure you use the string in the same or
// nested scope in which you created this buffer.  People should not use this
// class directly; use the macro(s) below.
//---------------------------------------------------------------------------
class SECATempBuffer
  {
  public:
    inline SECATempBuffer(ULONG cb)
    {
      m_fAlloc = (cb > 120);
      if (m_fAlloc)
        m_pbBuf = new char[cb];
      else
        m_pbBuf = &m_szBufT;
    }
    inline ~SECATempBuffer() { if (m_pbBuf && m_fAlloc) delete m_pbBuf; }
    inline void *GetBuffer(void) { return m_pbBuf; }

  private:
    void *m_pbBuf;
    char  m_szBufT[120];  // We'll use this temp buffer for small cases.
    int   m_fAlloc;
  };


//---------------------------------------------------------------------------
// String helpers.
//---------------------------------------------------------------------------
// Given and ANSI String, copy it into a wide buffer.
// NOTE: Be careful about scoping when using this macro!
//
// How to use the below two macros:
//
//  ...
//  LPSTR pszA;
//  pszA = MyGetpszAnsiingRoutine();
//  SECA_MAKE_WIDEPTR_FROMANSI(pwsz, pszA);
//  MyUseWideStringRoutine(pwsz);
//  ...
//
// Similarily for SECA_MAKE_ANSIPTR_FROMWIDE().  Note that the first param does
// not have to be declared, and no clean up must be done.
//---------------------------------------------------------------------------
#define SECA_UNICODE_FROM_ANSI(pwszUnicode, pszAnsi, cb) \
    MultiByteToWideChar(CP_ACP, 0, pszAnsi, -1, pwszUnicode, cb);

// QA 32334
// Compiles and executes correctly 
// on WinXP SP2 and SP3 and Vista with and without Windows SDK
// QA test with ScriptMDI TAC sample and ScriptDlg class in sample
#define SECA_MAKE_WIDEPTR_FROMANSI(ptrname, pszAnsi) \
    long __l##ptrname; \
    LPWSTR ptrname; \
    __l##ptrname = MultiByteToWideChar(CP_ACP, 0, pszAnsi, -1, 0, 0); \
    ptrname = (LPWSTR) alloca(__l##ptrname*sizeof(WCHAR)); \
    MultiByteToWideChar(CP_ACP, 0, pszAnsi, -1, ptrname, __l##ptrname);

#define SECA_MAKE_ANSIPTR_FROMWIDE(ptrname, pwszUnicode) \
    WCHAR *__pwsz##ptrname = pwszUnicode?pwszUnicode:L""; \
    long __l##ptrname = (lstrlenW(__pwsz##ptrname) + 1) * sizeof(char); \
    SECATempBuffer __TempBuffer##ptrname(__l##ptrname); \
    WideCharToMultiByte(CP_ACP, 0, __pwsz##ptrname, -1, (LPSTR)__TempBuffer##ptrname.GetBuffer(), __l##ptrname, NULL, NULL); \
    LPSTR ptrname = (LPSTR)__TempBuffer##ptrname.GetBuffer()

//---------------------------------------------------------------------------

TOOLKIT_API HRESULT CreateObject( LPOLESTR pszProgID, IDispatch FAR* FAR* ppdisp );
/* Note: TOOLKIT_API not used on variable arg list <input type="button" >*/
HRESULT Invoke( LPDISPATCH pdisp, 
                WORD wFlags,
                LPVARIANT pvRet,
                EXCEPINFO FAR* pexcepinfo,
                UINT FAR* pnArgErr, 
                LPOLESTR pszName,
                LPCTSTR pszFmt, 
                ... );

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif			// __SECHELPERS_H_
