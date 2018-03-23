///////////////////////////////////////////////////////////////////////////////
// GXEXT.h : Common Extensions
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

#ifndef _GXEXT_H_
#define _GXEXT_H_

#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif

#ifndef _GXRESRC_H_
#include "gxresrc.h"
#endif

// // #include <StingrayExportDefs.h>

#pragma warning(disable: 4273)

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

// header file

/////////////////////////////////////////////////////////////////////////////
// Time and date formatting

#include <time.h>

#if !defined(_AFX_NO_DB_SUPPORT)

#include <sqlext.h> // TIMESTAMP_STRUCT

#else

// needed for GXFormatTimeStamp

typedef short int               SWORD;
typedef unsigned short int      UWORD;
typedef unsigned long int       UDWORD;

typedef SWORD                   SQLSMALLINT;
typedef UDWORD                  SQLUINTEGER;
typedef UWORD                   SQLUSMALLINT;

typedef struct tagTIMESTAMP_STRUCT
{
		SQLSMALLINT    year;
		SQLUSMALLINT   month;
		SQLUSMALLINT   day;
		SQLUSMALLINT   hour;
		SQLUSMALLINT   minute;
		SQLUSMALLINT   second;
		SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;

#endif

GRID_API size_t AFXAPI GXIntlStrFtime(
	HINSTANCE nResourceHandle,
	UINT nStrFTimeResourceID,
	LPTSTR s,
	size_t maxs,
	LPCTSTR f,
	const struct tm *t);

GRID_API void AFXAPI GXFormatTimeStamp(CString& strRet, const CTime* pTime);
GRID_API void AFXAPI GXFormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);

// Parsing date/time values

// NOTE: This methods are provided because parsing
// date/time values was not possible with VC 1.5x
// and VC 2.x projects.
//
// If you are using VC 4.x or greater, we recommend
// using the COleDateTime::ParseDateTime for this
// purpose.

GRID_API void AFXAPI GXImplementOleDateTime();
GRID_API void AFXAPI GXImplementNoOleDateTime();
GRID_API void AFXAPI GXUpdateDateTimeSettings();
GRID_API GXDateFormat AFXAPI GXGetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
GRID_API TCHAR AFXAPI GXGetTimeSeparatorFromWinIni(BOOL bReload = FALSE);

// CTime
GRID_API BOOL AFXAPI GXParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);

// TIMESTAMP_STRUCT
GRID_API BOOL AFXAPI GXParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);

/////////////////////////////////////////////////////////////////////////////
// global methods

GRID_API CView*      AFXAPI GXGetActiveView();
	// returns pointer to active view object

GRID_API CDocument*  AFXAPI GXGetActiveDocument();
	// returns pointer to active document

GRID_API CWnd* AFXAPI GXGetParentWnd(const CWnd* pWnd, struct GRID_API CRuntimeClass* pClass, BOOL bAnyState);
	// returns pointer to parent window
	// or NULL if parent window is not derived from pClass

GRID_API void AFXAPI GXFormatString1(CString& rString, LPCTSTR lpszFormat, LPCTSTR lpsz1);

GRID_API CString AFXAPI GXReplaceString(CString& strTarget, CString strFind, CString strReplace);

GRID_API void AFXAPI GXWriteProfileLong(LPCTSTR szSection, LPCTSTR szEntry, LONG val);
GRID_API LONG AFXAPI GXGetProfileLong(LPCTSTR szSection, LPCTSTR szEntry, LONG val);

/////////////////////////////////////////////////////////////////////////////
// Preprocessor directives

//---------------------------------------------------------------------------//
// Definintions for DECLARE_REGISTER AND IMPLEMENT_REGISTER have moved to    //
// StingrayExportDefs.h and are now renamed to:                              //
// GRID_DECLARE_REGISTER  and GRID_IMPLEMENT_REGISTER.                       //
//---------------------------------------------------------------------------//

/////////////////////////////////////////////////////////////////////////////
// Drawing routines

class CGXDrawingAndFormatting
{
public:
	GRID_API virtual ~CGXDrawingAndFormatting();

	// Patterns (used in brushes)
	GRID_API virtual const CBitmap* GXGetPatternBitmap(int n);

	// Text routines
	GRID_API virtual int  GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL, gxEllipseType gxFormatEx = gxNoEllipse);

	GRID_API virtual int  GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL);
	GRID_API virtual int  GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LONG lfOrientation, LPRECT lpRectClip = NULL);
	GRID_API virtual int  GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt);
	GRID_API virtual int  GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat);
	GRID_API virtual int  GXComputeLineBreaks(CDC* pDC, LPCTSTR sz, int nCount, LPRECT rc, UINT nFormat, int* LineBreaks, int* LineLengths, int nMaxBreaks);

	// Text formatting and parsing
	GRID_API virtual CString GXFormatText(const CGXStyle& style, LPCTSTR pszValue = NULL, unsigned nValueType = GX_VT_STRING, CGXGridCore* pGrid = NULL, CGXControl* pControl = NULL);
	GRID_API virtual BOOL GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat = NULL, unsigned* pImportPlaces = NULL);

	// 3d frame
	GRID_API virtual void GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);

	// sunken borders (for windows in dialogs)
	GRID_API virtual void _GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge);

	// focus text (push buttons call this when button has focus)
	GRID_API virtual void GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat);

	// CGXStatic::Draw
	GRID_API virtual void DrawStatic(CGXControl* pControl, CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	GRID_API static void AFXAPI ImplementDrawRotatedText();
	GRID_API static void AFXAPI ImplementNumberFormatting();
};

// Support for DDP/DIB Bitmaps

// supporting routines for device independent bitmaps
GRID_API HANDLE AFXAPI GXLoadResourceBitmap(HINSTANCE hInstance, LPCTSTR lpString);
GRID_API HANDLE AFXAPI GXLoadResourceBitmap(LPCTSTR lpString);
GRID_API DWORD AFXAPI GXGetNumDIBColorEntries(LPBITMAPINFO pBmpInfo);

// transparent bitmaps
GRID_API void AFXAPI GXDrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
	int yStart, COLORREF cTransparentColor);

// Button state

const UINT GX_BTNFOCUS      = 0x01;
const UINT GX_BTNSCOPE      = 0x02;
const UINT GX_BTNPRESSED    = 0x04;
const UINT GX_BTNCHECKED    = 0x04;
const UINT GX_BTNUNCHECKED  = 0x08;

// Pure VGA colors
GRID_API COLORREF AFXAPI GXGetVGAColor(int index);

// Find a color in the array
GRID_API int AFXAPI GXFindColor(COLORREF rgbColor);

// Patterns (used in brushes)
extern int _gxnPatternCount;
GRID_API const CBitmap* AFXAPI GXGetPatternBitmap(int n);

class CGXStyle;
//---------------------------//
// Drawing routines
//---------------------------//
//@cmember
// Draw inset.
GRID_API void AFXAPI GXDrawInset(CDC* pDC, int x, int y, int dx, int dy, COLORREF rgbFace = RGB(255,255,255));
//@cmember
// Draw button.
GRID_API void AFXAPI GXDrawButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed, COLORREF rgbFace = RGB(192,192,192));
//@cmember
// Invert rect.
GRID_API void AFXAPI GXInvertRect(CDC* pDC, const CRect& rect, const CRect& rectClip);
//@cmember
// PatB
GRID_API void AFXAPI GXPatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);
//@cmember
// PatB
GRID_API void AFXAPI GXPatB(CDC* pDC,const CRect& rc, COLORREF rgb);
//@cmember
// Draw blank button.
GRID_API void AFXAPI GXDrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed = FALSE);
//@cmember
// Draw radio buttons.
GRID_API int  AFXAPI GXDrawRadioButtons(CDC* pDC, CRect rect, LPCTSTR pszValue, LPCTSTR pszChoices, BOOL bDraw3D = FALSE);
//@cmember
// Hit test radio buttons.
GRID_API int  AFXAPI GXHitTestRadioButtons(CDC* pDC, CRect rect, LPCTSTR pszChoices, CPoint pt);
//@cmember
// Draw text like multiline edit.
GRID_API int  AFXAPI GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL);
//@cmember
// Draw text like multiline edit ex.
GRID_API int  AFXAPI GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL, gxEllipseType gxFormatEx = gxNoEllipse);
//@cmember
// Get multiline text position under point.
GRID_API int  AFXAPI GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt);
//@cmember
// Get multiline text break count.
GRID_API int  AFXAPI GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat);
//@cmember
// Compute line breaks.
GRID_API int  AFXAPI GXComputeLineBreaks(CDC* pDC, LPCTSTR sz, int nCount, LPRECT rc, UINT nFormat, int* LineBreaks, int* LineLengths, int nMaxBreaks);
//@cmember
// Draw 3D frame. 
GRID_API void AFXAPI GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);
//@cmember
// Draw 3D frame.
GRID_API void AFXAPI GXDraw3dFrame(CDC* pDC, const CRect &rc, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);
//@cmember
// Get next line.
GRID_API int  AFXAPI GXGetNextLine(CString& s, CString &sLine);
//@cmember
// Get column string.
GRID_API void AFXAPI GXGetColString(LPCTSTR pszLine, int nCol, LPTSTR szResult, int nMaxLen);
//@cmember
// Find choice list item.
GRID_API int AFXAPI GXFindChoiceListItem(const CString& strFind, int nCol, const CString& strChoiceList, BOOL bSkipFirstRow, CString& sItem, BOOL bExact = TRUE);
//@cmember
// Sort choice list.
GRID_API void AFXAPI GXSortChoiceList(CString& strChoiceList, int nCol = 0, BOOL bSkipFirstRow = FALSE);
//@cmember
// Load system color bitmap.
GRID_API BOOL AFXAPI GXLoadSysColorBitmap(CBitmap& bmp, LPCTSTR lpszName);
//@cmember
// Format text.
GRID_API CString AFXAPI GXFormatText(const CGXStyle& style, LPCTSTR pszValue = NULL, unsigned nValueType = GX_VT_STRING, CGXGridCore* pGrid = NULL, CGXControl* pControl = NULL);
//@cmember
// Draw rotated text.
GRID_API int  AFXAPI GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LONG lfOrientation, LPRECT lpRectClip = NULL);
//@cmember
// Draw sunken borders.
GRID_API void AFXAPI _GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge);
//@cmember
// Deval.
GRID_API BOOL AFXAPI GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat = NULL, unsigned* pImportPlaces = NULL);

// Useful drawing functions ... these exist in the MFC from version 3 onwards.
#ifdef WIN32

	//@cmember
	// Fill solid rect1.
	#define GXFillSolidRect1(dc, rect, color) \
			(dc)->FillSolidRect(rect, color)
			
	//@cmember
	// Fill solid rect2.
	#define GXFillSolidRect2(dc, x, y, cx, cy, color) \
			(dc)->FillSolidRect(x, y, cx, cy, color)
			
	//@cmember
	// Draw 3D rect1.
	#define GXDraw3dRect1(dc, rect, color1, color2) \
			(dc)->Draw3dRect(rect, color1, color2)
			
	//@cmember
	// Draw 3D rect2.
	#define GXDraw3dRect2(dc, x, y, cx, cy, color1, color2) \
			(dc)->Draw3dRect(x, y, cx, cy, color1, color2)

#else // WIN32

	//@cmember
	// Fill solid rect1.
	extern void AFXAPI GXFillSolidRect1(CDC* pDC, LPCRECT lpRect, COLORREF color);
	//@cmember
	// Fill solid rect2.
	extern void AFXAPI GXFillSolidRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color);
	//@cmember
	// Draw 3D rect1.
	extern void AFXAPI GXDraw3dRect1(CDC* pDC, LPCRECT lpRect, COLORREF color1, COLORREF color2);
	//@cmember
	// Draw 3D rect2.
	extern void AFXAPI GXDraw3dRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color1,
							COLORREF color2);  
						
#endif // WIN32

#if(WINVER < 0x0400)
/* 3D border styles */
#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER       0x0003
#define BDR_INNER       0x000c
#define BDR_RAISED      0x0005
#define BDR_SUNKEN      0x000a


#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)
#endif

//@cmember
// Draw edge.
GRID_API void AFXAPI GXDrawEdge(CDC* pDC, CRect rect, UINT nEdge, BOOL bAdjust = FALSE);
//@cmember
// Draw focus text.
GRID_API void AFXAPI GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat = DT_CENTER);


/////////////////////////////////////////////////////////////////////////////////
// CGXDIB  : Device independant bitmaps

class CGXDIB : public CObject
{
	GRID_DECLARE_DYNCREATE(CGXDIB)
public:

// Attributes
	HANDLE	m_hbm;
	DWORD	m_dwColors;
	int		m_nWidth;
	int		m_nHeight;
	BOOL	m_bGDIObject;

	//@cmember
	// Attach.
	GRID_API BOOL Attach(HANDLE hObject);
	//@cmember
	// Detach.
	GRID_API HANDLE Detach();
	//@cmember
	// Get safe handle.
	GRID_API HANDLE GetSafeHandle() const;
	//@cmember
	// Get color count.
	GRID_API DWORD GetColorCount();
	//@cmember
	// Get size.
	GRID_API CSize GetSize();

	//@cmember
	// Constructors
	GRID_API CGXDIB();
	//@cmember
	// Load dib.
	GRID_API BOOL LoadDIB(LPCTSTR lpszResourceName);
	//@cmember
	// Load dib.
	GRID_API BOOL LoadDIB(UINT nIDResource);

// Operations
	// clean up
	//@cmember
	// Destroy dib.
	GRID_API void DestroyDIB();

	enum StretchFlags
	{
		none = 0,
		asymmetric = 1,
		symmetric = 2
	};

	//@cmember
	// Drawing
	GRID_API void Draw(CDC* pDC, LPRECT lpRect, int nStretchFlags = none, UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL);
	GRID_API static void AFXAPI Draw(CDC* pDC, HANDLE hbm, LPRECT lpRect, int nStretchFlags = none, UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL);

// Implementation
public:
	GRID_API virtual ~CGXDIB();
};

/////////////////////////////////////////////////////////////////////////////////
// CGXDIBPool : Collection of DIBS

class CGXDIBPool : public CObject
{
	GRID_DECLARE_DYNAMIC(CGXDIBPool)
public:

// Attributes
	CMapStringToPtr  m_mapDIBHandles;

// Constructors
	GRID_API CGXDIBPool();

// Operations
	//@cmember
	// Lookup or create dib.
	GRID_API virtual HANDLE LookupOrCreateDIB(const CString& strValue);
	//@cmember
	// Empty pool.
	GRID_API void EmptyPool();

	//@cmember
	// Get resource string.
	GRID_API virtual LPCTSTR GetResourceString(const CString& strValue, CString& strResource);
	//@cmember
	// Load dib.
	GRID_API virtual HANDLE LoadDIB(const CString& strValue, LPCTSTR pszResourceString);
	//@cmember
	// Create value string.
	GRID_API virtual void CreateValueString(UINT nID, CString& strRet);
	GRID_API virtual void CreateValueString(const CString& strResourceName, CString& strRet);

// Implementation
public:
	GRID_API virtual ~CGXDIBPool();
};

//////////////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice: printer settings

class CGXPrintDeviceImp;

class CGXPrintDevice: public CObject
{
	GRID_DECLARE_SERIAL(CGXPrintDevice)

//  Data
protected:
	HGLOBAL         m_hDevMode;
	HGLOBAL         m_hDevNames;
	HDC             m_hPrintDC;
	CGXAbstractPrintDeviceImp* m_pPrintDeviceImp;

//  Constructor/destructor
public:
	//@cmember
	// Print device.
	GRID_API CGXPrintDevice();
	GRID_API CGXPrintDevice(const CGXPrintDevice&);
	GRID_API CGXPrintDevice& operator=(const CGXPrintDevice&);
	GRID_API virtual ~CGXPrintDevice();
	//@cmember
	// Serialize.
	GRID_API void Serialize(CArchive& ar);
	//@cmember
	// Implement print device.
	GRID_API static void AFXAPI ImplementPrintDevice();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// device handles
public:
	//@cmember
	// Create and destroy printer device objects.
	GRID_API void CreateDeviceHandles(LPDEVNAMES pDevnames, DWORD nSizeDevnames, LPDEVMODE pDevmode, DWORD nSizeDevmode);
	GRID_API void CreateDeviceHandles(HGLOBAL hDN, HGLOBAL hDM);
	GRID_API void DestroyDeviceHandles();
	//@cmember
	// Compare printer device objects.
	GRID_API BOOL CompareDeviceHandles(LPDEVNAMES pDevnames, DWORD nSizeDevnames, LPDEVMODE pDevmode, DWORD nSizeDevmode);
	GRID_API BOOL CompareDeviceHandles(HGLOBAL hDN, HGLOBAL hDM);
	//@cmember
	// Copy printer device objects.
	GRID_API void CopyDeviceHandles(HGLOBAL& hDN, HGLOBAL& hDM);
	//@cmember
	// If printer device objects do not yet exist, create and initialize them with defaults.
	GRID_API void NeedDeviceHandles();
	//@cmember
	// Get information about print device
	GRID_API virtual HDC GetPrintDC();
	//@cmember
	// Reset print device context.
	GRID_API virtual void ResetPrintDC();
	//@cmember
	// Get buffers with device info,
	// !!! You must delete these buffers after usage.
	GRID_API void GetDeviceInfo(LPDEVNAMES& pDevnames, DWORD &nSizeDevnames, LPDEVMODE& pDevmode, DWORD& nSizeDevmode);
	GRID_API void GetDeviceInfo(HGLOBAL hDN, HGLOBAL hDM, LPDEVNAMES& pDevnames, DWORD &nSizeDevnames, LPDEVMODE& pDevmode, DWORD& nSizeDevmode);
	//@cmember
	// Load default settings.
	GRID_API void GetDefaults();

	friend class CGXPrintDeviceImp;
};


/////////////////////////////////////////////////////////////////////////////
// CGXWaitCursor: hourglass wrapper

struct CGXWaitCursor
{
// Construction/Destruction
	GRID_API CGXWaitCursor();
	GRID_API ~CGXWaitCursor();

// Operations
	GRID_API void Restore();
};

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXLongOperation

const int MAXLEVEL = 64;

class CGXLongOperation
{
public:
// Construction/Destruction
	GRID_API CGXLongOperation();
	GRID_API ~CGXLongOperation();

	// static Data
	//@cmember
	// Abort string.
	GRID_API static void AFXAPI SetAbortString(LPCTSTR s);  // Text to be displayed in abort-dialog
	GRID_API static void AFXAPI SetAbortString(UINT nID);

	//@cmember
	// Set default cancel text.
	GRID_API static void AFXAPI SetDefaultCancelText(LPCTSTR s);
	//@cmember
	// Set default done text.
	GRID_API static void AFXAPI SetDefaulDoneText(LPCTSTR s);
	//@cmember
	// Set default status text.
	GRID_API static void AFXAPI SetDefaultStatusText(LPCTSTR s);
	//@cmember
	// Set ticks first time.
	GRID_API static void AFXAPI SetTicksFirstTime(DWORD dw);
	//@cmember
	// Set ticks continued.
	GRID_API static void AFXAPI SetTicksContinued(DWORD dw);
	//@cmember
	// Set frame wnd.
	GRID_API static void AFXAPI SetFrameWnd(CWnd* pWnd);
	//@cmember
	// Get current level.
	GRID_API static int  AFXAPI GetCurrentLevel();          // level of operation
	//@cmember
	// Get locked state.
	GRID_API static BOOL AFXAPI GetLockedState();           // locked state indicates not to update the status bar
	//@cmember
	// Get wait cursor state.
	GRID_API static BOOL AFXAPI GetWaitCursorState();       // Long operations will display a waitcursor
	//@cmember
	// Get abort state.
	GRID_API static BOOL AFXAPI GetAbortState();            // User pressed <ESC>-Key
	//@cmember
	// Get abort confirmed state.
	GRID_API static BOOL AFXAPI GetAbortConfirmedState();   // User confirmed aborting in abort-dialog
	//@cmember
	// Get rollback confirmed state.
	GRID_API static BOOL AFXAPI GetRollbackConfirmedState();// User confirmed rollback in abort-dialog
	//@cmember
	// Set percent done.
	GRID_API static void AFXAPI SetPercentDone(int nPercent);
	//@cmember
	// Implement long operation.
	GRID_API static void AFXAPI ImplementLongOperation();
	//@cmember
	// Status text for current operation.
	GRID_API LPCTSTR GetStatusText() const;
	//@cmember
	// Set status text.
	GRID_API void  SetStatusText(LPCTSTR s, BOOL bCopyBuffer = TRUE);
	//@cmember
	// Set status text.
	GRID_API void  SetStatusText(UINT nID);
	//@cmember
	// Free status text.
	GRID_API void  FreeStatusText();	// deletes the status text for the current level
	//@cmember
	// Set can rollback.
	GRID_API void  SetCanRollback(BOOL bCanRollback);// Can the user rollback the operation?
	//@cmember
	// Set can abort.
	GRID_API void  SetCanAbort(BOOL bCanAbort);      // Can the user abort the operation?
	//@cmember
	// Set locked state.
	// Locked state indicates not to update the status bar in higher operation levels.
	GRID_API static void  AFXAPI SetLockedState(BOOL bLocked = TRUE);
		
	// Operations
	//@cmember
	// Need messages.
	// Test, if messages should be processed.
	GRID_API BOOL NeedMessages();            
	//@cmember
	// Do messages.
	// Process messages and check if user aborted.
	GRID_API BOOL DoMessages(BOOL& bAbort);  
	//@cmember
	// Do messages.
	// Simply process messages.
	// Returns TRUE, if messages have been processed.
	GRID_API BOOL DoMessages();  
	//@cmember
	// Specifies if a WM_SETMESSAGESTRING should be
	// send to the status bar automatically.
	GRID_API void SetUpdateStatusBar(BOOL b);
	//@cmember
	// Specifies if the status bar should be
	// cleared when the operation is finished.
	GRID_API void SetResetStatusBar(BOOL b);

	// Ticks
	DWORD GetTickCount() const;
#if !defined(_AFXDLL) && !defined(_WINDLL)
	CString GetStrFTime(LPTSTR f) const;
#endif

private:
	// current operation-level
	DWORD m_nTickStart;             // start-time
	DWORD m_nLastTick;              // last time processing messages

	LPCTSTR m_pszStatusText;    // Text to be displayed in status line

	BOOL    m_bResetStatusBar;    // automaticaly reset status bar
	BOOL    m_bUpdateStatusBar;   // automaticaly update status bar

	// helper methods
private:
	void ProcessMessages();

	friend class CGXLongOperationImp;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxext.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXEXT_H_
