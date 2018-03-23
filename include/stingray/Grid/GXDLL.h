///////////////////////////////////////////////////////////////////////////////
// GXDLL.h

#ifndef _GXDLL_H_
#define _GXDLL_H_

#ifdef _GXEXT
#undef _GXDLL
#define _GXDLL
#endif

#ifdef _GXDLL

#ifndef GX_DATAEXT
	#define GX_DATAEXT     AFX_DATA_IMPORT
	#define GX_DATADEF
#endif

#ifndef _GXCOLL_H_
#include "gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

	// return OG DLL Resource Handle
extern GRID_API HINSTANCE AFXAPI GXGetResourceHandle();

#if _MFC_VER >= 0x0400

// Support for OG language Dll's (MFC 4.x only)

class CGXLangDll
{
public:
	GRID_API CGXLangDll();
	GRID_API ~CGXLangDll();

	// [VC7] Return types corrected to BOOL to match implementations.
	GRID_API BOOL Load(LPCTSTR pszLang, LPCTSTR pszPath);
	GRID_API BOOL Free();

private:
	 HINSTANCE m_hLangDll;
	 HINSTANCE m_hOldLang;
	 HINSTANCE m_hOldRes;
};

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#else // _GXDLL

	// not using OG DLL, so I should return the Afx Resource Handle
#define GXGetResourceHandle AfxGetResourceHandle

#endif // _GXDLL

#endif // _GXDLL_H_

/////////////////////////////////////////////////////////////////////////////
