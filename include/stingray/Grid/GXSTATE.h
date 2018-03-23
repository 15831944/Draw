///////////////////////////////////////////////////////////////////////////////
// GXSTATE.h
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

#ifndef _GXSTATE_H_
#define _GXSTATE_H_

// This file contains per application global data structures.
//
// If Objective/Grid MFC is used as Extension DLL,
// these global data structures are embedded in the
// CGXDynLinkLibrary object.
//
// If Objective/Grid MFC is used as Static Library,
// they are declared global in the implementation files.
//
// The application global data structures listed below are  
// CLocalThread-safe or CProcessThread-safe for both  
// DLL and statically linked libraries. 
// 
// struct GX_DRAW_STATE 
// struct GX_FR_STATE 
// struct GX_DIB_STATE 
// struct GX_WAIT_STATE 
// struct GX_CURSOR_STATE 
// struct GX_FONT_STATE 
// struct GX_IME_STATE 
// struct GX_SYS_DATA 
// 
// NOTE: As of RWSS 10.0, i.e. CD 50, this thread-safety is limited  
//       to the global data structures defined in this file only and  
//       as listed above for static configurations only. More 
//		 comprehensive work is still needed to further enhance 
//       thread-safety throughout all Stingray products. 
//

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


#include "gxabstr.h"

/////////////////////////////////////////////////////////////////////////////
// Initialize/reset state

class CGXAbstractControlFactory;
class CGXAbstractTabWndInterface;
class CGXAbstractRecordInfoWndInterface;
class CGXDrawingAndFormatting;
class CGXLangDll;
class CGXGridCore;
class CGXAppData;

GRID_API void AFXAPI GXInit(UINT uiMfcVersion, CGXAbstractControlFactory* pFactory, LPCTSTR pszLang = NULL, LPCTSTR pszPath = NULL);
GRID_API void AFXAPI GXInit(UINT uiMfcVersion, LPCTSTR pszLang = NULL, LPCTSTR pszPath = NULL);
	// initializes library and registers all window classes used by the grid control

inline void AFXAPI GXInit(LPCTSTR pszLang = NULL, LPCTSTR pszPath = NULL)
	{ GXInit(_MFC_VER, pszLang, pszPath); }

inline void AFXAPI GXInit(CGXAbstractControlFactory* pFactory, LPCTSTR pszLang = NULL, LPCTSTR pszPath = NULL)
	{ GXInit(_MFC_VER, pFactory, pszLang, pszPath); }

GRID_API void __cdecl GXTerminate(CGXAppData* pData = NULL);
	// unregisters all window classes used by the grid control

// use with ActiveX dlls
//extern "C" extern void WINAPI GXForceTerminate();
extern "C" GRID_API void __cdecl GXForceTerminate();

extern "C" GRID_API BOOL __cdecl GXDiscardNcActivate();

extern "C" GRID_API void __cdecl GXSetNewGridLineMode(BOOL bEnable = TRUE, UINT nStyle = PS_DOT, BOOL bNoHeaderBorders = TRUE);

#if defined(_GXDLL)
extern "C" GRID_API void WINAPI GXInitDll();
	// initialize DLL
#endif

// Register and unregister window classes
extern "C" GRID_API void __cdecl GXRegisterClasses(HINSTANCE hResource);
extern "C" GRID_API void __cdecl GXUnregisterClasses(HINSTANCE hResource);

// Following structures are declared in this header file:

// class GRID_API CGXAppData;

struct GX_DRAW_STATE;   // Drawing state
struct GX_FR_STATE;     // last find/replace state
struct GX_WAIT_STATE;   // CGXLongOperation state
struct GX_APP_STATE;    // only _GXDLL: container for all states

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXAppData

// QA: 32120 - CGXAppData should NOT be derived from CNoTrackObject.
class CGXAppData
{
public:
	GRID_API CGXAppData();
	GRID_API virtual ~CGXAppData();

	BOOL m_bInitDone;	// will be set TRUE from GXInit

// Data GXGetApp
	UINT m_uiStylesClipboardFormat;
		// Private clipboard format

	GRID_API void LoadResources();
	GRID_API void Init(CGXAbstractControlFactory* pFactory);

	// Resource Strings
	CString strmRedo;       // GX_IDM_REDO               
	CString strmUndo;       // GX_IDM_UNDO               
	CString strmUndoInfo;   // GX_IDM_UNDOINFO           
	CString strmStoreCells; // GX_IDM_STORECELLS         
	CString strmRestoreCells;   // GX_IDM_RESTORECELLS   
	CString strmCellFormatting; // GX_IDM_CELLFORMATTING 
	CString strmRemoveRows; // GX_IDM_REMOVEROWS         
	CString strmRemoveCols; // GX_IDM_REMOVECOLS         
	CString strmMoveRows; // GX_IDM_MOVEROWS             
	CString strmMoveCols; // GX_IDM_MOVECOLS             
	CString strmInsertRows; // GX_IDM_INSERTROWS         
	CString strmInsertCols; // GX_IDM_INSERTCOLS         
	CString strmCopyText;   // GX_IDM_COPYTEXT           
	CString strmCopyInternal;   // GX_IDM_COPYINTERNAL   
	CString strmCutData;    // GX_IDM_CUTDATA            
	CString strmClearData;    // GX_IDM_CLEARDATA
	CString strmCuttingData;    // GX_IDM_CUTTINGDATA    
	CString strmPastingData;    // GX_IDM_PASTINGDATA    
	CString strmPasteData;  // GX_IDM_PASTEDATA          
	CString strmReplacingAll;   // GX_IDM_REPLACINGALL   
	CString strmReplaceAll; // GX_IDM_REPLACEALL         
	CString strmSearching;  // GX_IDM_SEARCHING          
	CString strmResizeRows; // GX_IDM_RESIZEROWS
	CString strmResizeCols; // GX_IDM_RESIZECOLS
	CString strmSetFrozenRows;  // GX_IDM_SETFROZENROWS
	CString strmSetFrozenCols;  // GX_IDM_SETFROZENCOLS
	CString strmUndoCurrentCell;  // GX_IDM_SETFROZENCOLS
	CString strmPasteDiffRange;   // GX_IDM_PASTEDIFFRANGE
	CString strmDragDropCopy;
	CString strmDragDropMove;

	// CGXGridCombo class name
	CString sComboClassName;

	// other system information
	UINT    nWinVer;        // Major.Minor version numbers
	BOOL    bWin32s;        // TRUE if Win32s (or Windows 95)
	BOOL    bWin4;          // TRUE if Windows 4.0
	BOOL    bNotWin4;       // TRUE if not Windows 4.0
	BOOL    bWin31;         // TRUE if actually Win32s on Windows 3.1

	// Avoid flickering of titlebar
	BOOL    m_bDiscardNcActivate;

	// New grid line mode
	BOOL    m_bEnableNewGridLineMode;
	UINT    m_nDefaultGridLineStyle;
	BOOL    m_bNoHeaderBorders;

	// Support for ExpressionType and compatibility with OG 5.0
	int     m_nExpressionValueType;	// default is GX_VALUE_EXPRESSION
									// if you have a lot of GetStyleRowCol overrides
									// where you have a check for nType == 0 setting
									// m_nExpressionValueType = 0 will fix incompatibilities
									// and you don't have to change your GetStyleRowCol overrides.
									

	// Support for different charsets in font dialog
	BOOL	m_bDisplayFontCharset;

	// Control Factory
	CGXAbstractControlFactory* m_pControlFactory;

	// TabWnd and RecordInfoWnd support
	CGXAbstractTabWndInterface* m_pTabWndInt;
	CGXAbstractRecordInfoWndInterface* m_pRecordInfoWndInt;
	CGXAbstractRecordInfoWndInterface* m_pRecordInfoSplitterWndInt;
	CPtrList m_pSharedScrollBarRuntimeClassList;
 
	GRID_API void RegisterSharedScrollBar(CRuntimeClass* pRuntimeClass);
	GRID_API CWnd* GetSharedScrollbarParentWnd(const CWnd* pChildWnd) const;

	// Object Mapping (Parent Param for StylesMap, data object etc).
	CMapPtrToPtr m_mapObjectToGridList;

	GRID_API void AttachGridToObject(void* pObj, CGXGridCore* pGrid);
	GRID_API CGXGridCore* GetFirstGrid(void* pObj) const;
	GRID_API void DetachGrid(CGXGridCore* pGrid);

	// General drawing and formatting tools
	CGXDrawingAndFormatting* m_pDaFTools;

	// Formula Engine
	CObject* m_pEngineState;
	CObject* m_pParseState;
	CObject* m_pEvalState;
	CObject* m_pRegexState;
	CNoTrackObject* m_pMemObjState;

	// Intelli Mouse
	CObject* m_pIntelliState;		// only used for 16-bit _GXDLL builds

	// Enabled components 
	void* begin_component_ptr;
	CGXAbstractCoveredCellPoolImp*		m_pCoveredCellPoolImp;
	CGXAbstractSpanCellPoolImp*			m_pSpanCellPoolImp;
	CGXAbstractDelayedRangePoolImp*		m_pDelayedRangePoolImp;
	CGXAbstractPrintDeviceImp*			m_pPrintDeviceImp;
	CGXAbstractStyleCompareSubsetImp*	m_pStyleCompareSubsetImp;
	CGXAbstractStyleSerializeImp*		m_pStyleSerializeImp;
	CGXAbstractGridDocSerializeImp*		m_pDocSerializeImp;
	CGXAbstractGridProfileImp*			m_pGridProfileImp;
	CGXAbstractGridParamCopyOperatorImp* m_pParamCopyOperatorImp;
	CGXAbstractGridSortMoveDataImp*		m_pSortMoveDataImp;
	CGXAbstractDrawRotatedTextImp*		m_pDrawRotatedTextImp;
	CGXAbstractDateTimeImp*				m_pDateTimeImp;
	CGXAbstractDataCopyMoveCellsImp*	m_pDataCopyMoveCellsImp;
	CGXAbstractLongOperationImp*		m_pLongOperationImp;
	CGXAbstractSerializeOG5CompatibleImp* m_pSerializeOG5CompatibleImp;
	CGXAbstractNumberFormattingImp*		m_pNumberFormattingImp;
	void*								end_component_ptr;

	//used in NumberFormatting to sync with regional settings
	TCHAR charDecSep[2];
	TCHAR charGrpSep[2];
	BOOL m_bLocaleNumbersEnabled;
	BOOL m_bFormulaEnabled;
	GRID_API void UpdateLocaleNumberSettings();
	GRID_API void PutPointInString(CString& sValue);


#ifdef _DEBUG
	// Warnings about unimplemented function calls
	CMapStringToPtr m_mapNoImpWarnings;
	CMapStringToPtr m_mapAssertNoImp;
	CMapStringToPtr m_mapTraceOnce;
	CMapStringToPtr m_mapAssertOnTrace;
#endif

	GRID_API void AutoDeletePtr(void* p);
	CPtrList m_autodeleteptrlist;
};

	// returns pointer to CGXAppData object
#if defined(_GXDLL)
	struct GX_APP_STATE;
	GRID_API GX_APP_STATE* AFXAPI GXGetAppState();
	#define GXGetAppData() (GXGetAppState()->m_pAppData)
#else
	// QA: 32120 - Specifically, _gxAppData is NOT wrapped
	// in CThreadLocal. Doing so will cause asserts to fire
	// because it is also referenced as a member pointer
	// in another class. 
	extern CGXAppData GXNEAR _gxAppData;
	#define GXGetAppData() (&_gxAppData)
#endif

GRID_API CGXDrawingAndFormatting* AFXAPI GXDaFTools();
GRID_API void AFXAPI GXSetDaFTools(CGXDrawingAndFormatting* pTools);

/////////////////////////////////////////////////////////////////////////////
// GX_DRAW_STATE: Drawing state

#define GXNPATTERNS 41
#define GXNPENPATTERN1 33

// QA: 32120 - Deriving from CNoTracking Object
#ifdef _GXDLL
	struct GRID_API GX_DRAW_STATE
#else
	struct GRID_API GX_DRAW_STATE : public CNoTrackObject
#endif
{
	CBitmap m_bm3dCtrl;
	CBitmap m_abmPatternArray[GXNPATTERNS];
};

#if defined(_GXDLL)
	#define GXGetDrawState() (&GXGetAppState()->m_drawState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing &
	// reference from GXGetDrawState().
	extern CThreadLocal<GX_DRAW_STATE> GXNEAR _gxDrawState;
	#define GXGetDrawState() (_gxDrawState)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_FR_STATE : last find/replace state

class CFindReplaceDialog;
class CGXGridCore;
class CGXStyle;

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_FR_STATE
#else
	struct GX_FR_STATE : public CNoTrackObject
#endif
{
	CFindReplaceDialog* pFindReplaceDlg; // find or replace dialog
	BOOL	bFindOnly;		// Is pFindReplace the find or replace?
	CString strFind;		// last find string
	CString strFindUpper;   // last find string converted to upper
	CString strReplace;		// last replace string
	BOOL	bCase;			// TRUE==case sensitive, FALSE==not
	int		bNext;			// TRUE==search down, FALSE== search up
	BOOL	bTransaction;	// TRUE==call BeginTrans() / CommitTrans() in OnReplaceAll()
#ifdef _UNICODE
	LPSTR lpszMultiByteFindString;
#endif
	CGXGridCore* m_pActiveGrid;
	CWnd* pFindReplaceDlgOwner;
	CGXStyle* m_pStyle; // Cached style object (can be NULL)

	GRID_API void PrepareFindReplace();

	GRID_API GX_FR_STATE();
	GRID_API ~GX_FR_STATE();
};

#if defined(_GXDLL)
	#define GXGetLastFRState() (&GXGetAppState()->m_lastFRState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing &
	// reference from GXGetLastFRState().
	extern CThreadLocal<GX_FR_STATE> GXNEAR _gxLastFRState;
	#define GXGetLastFRState() (_gxLastFRState)
#endif


/////////////////////////////////////////////////////////////////////////////
// GX_DIB_STATE: DIB pool

class CGXDIBPool;

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_DIB_STATE
#else
	struct GX_DIB_STATE : public CNoTrackObject
#endif
{
	GRID_API GX_DIB_STATE();
	GRID_API ~GX_DIB_STATE();

	GRID_API CGXDIBPool* GetPool();

	CGXDIBPool* m_pDIBPool;
};

#if defined(_GXDLL)
	#define GXGetDIBState() (&GXGetAppState()->m_DIBState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing &
	// reference in GXGetDIBState().
	extern CThreadLocal<GX_DIB_STATE> GXNEAR _gxDIBState;
	#define GXGetDIBState() (_gxDIBState)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_WAIT_STATE : CGXLongOperation global state

const int gxnMaxWaitLevel = 64;     // maximum number of nested operations

//----------------------------------------------
// QA: 32120 - Deriving from CNoTrackObject
//----------------------------------------------
#ifdef _GXDLL
	struct GX_WAIT_STATE
#else
	struct GX_WAIT_STATE : public CNoTrackObject
#endif
{
	DWORD m_dwTicksFirstTime;       // ticks to show wait cursor (default: 1500)
	DWORD m_dwTicksContinued;       // ticks between processing messages (default: 750)

	BOOL  m_bAbortDialog;           // If m_bAbortDialog is FALSE, GetAbortConfirmedState()
									// will return TRUE, when the user presses ESC
									// without displaying the abort-dialog

	CString m_sDefaultStatusText;   // normally contains "Processing..."
	CString m_sDefaultDoneText;     // normally contains "Done..."
	CString m_sDefaultCancelText;   // normally contains "   Press ESC to cancel"

	int   m_nPercentDone;           // percentage (-1 if no percentage display)

	int   m_nRefCount;              // operation level
	int   m_nLevelLocked;           // higher levels will be locked updating the status bar
									// if it is -1, no levels are locked

	BOOL  m_bWaitCursor;            // WaitCursor visible?
	BOOL  m_bCanceled;              // <ESC>-Key pressed?
	BOOL  m_bUserConfirmed;         // Did the user confirm aborting the operation?
	BOOL  m_bRollbackConfirmed;     // Did the user confirm rollback the operation?

	BOOL  m_bCanAbort;              // Can the user abort the operation?
	BOOL  m_bCanRollback;           // Can the user rollback the operation?

	CString  m_sAbortText;          // Text to be displayed in abort-dialog

	LPCTSTR m_apszStatusText[gxnMaxWaitLevel];
									// this array logs the status text for each level
									// the statustext of the higher level is automatically
									// assigned to m_sStatusText when a new operation-object
									// is constructed
	BYTE m_abOwnStatusText[gxnMaxWaitLevel];
									// this array specifies if the status text should be deleted
									// when the level is left.

	TCHAR m_szStatusBuf[128];        // buffer for displaying status text
	int m_nIndicatorState;          // \ | / - indicator

	HWND m_hFrameWnd;              // pointer to mainframe window to receive WM_SETMESSAGESTRING

	GX_WAIT_STATE();
};

#if defined(_GXDLL)
	#define GXGetWaitState() (&GXGetAppState()->m_waitState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing
	// & reference in GXGetWaitState()
	extern CThreadLocal<GX_WAIT_STATE> GXNEAR _gxWaitState;
	#define GXGetWaitState() (_gxWaitState)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_CURSOR_STATE : Controls created by Dialog Template

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_CURSOR_STATE
#else
	struct GX_CURSOR_STATE : public CNoTrackObject
#endif
{
	HCURSOR m_hcurLast;
	HCURSOR m_hcurDestroy;
	UINT m_idcPrimaryLast;
	BOOL m_bNotFound;

	GRID_API GX_CURSOR_STATE();
};

#if defined(_GXDLL)
	#define GXGetCursorState() (&GXGetAppState()->m_cursorState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing &
	// reference in GXGetCursorState().
	extern CThreadLocal<GX_CURSOR_STATE> GXNEAR _gxCursorState;
	#define GXGetCursorState() (_gxCursorState)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_FONT_STATE : Controls created by Dialog Template

// each font has an integer index (< 255 -> lfFaceName)

struct CGXFontInfo;

#ifdef _GXDLL
	struct GX_FONT_STATE
#else
	struct GX_FONT_STATE : public CNoTrackObject
#endif
{
// costruction/destruction
	GRID_API GX_FONT_STATE();
	GRID_API ~GX_FONT_STATE();

// Access members for font info
	GRID_API BYTE GetFontCharset(unsigned nFont) const;
	GRID_API int GetFontType(unsigned nFont) const;
	GRID_API CGXFontInfo* GetFontInfo(unsigned nFont) const;
	GRID_API unsigned LookupFontInfo(LPCTSTR szFacename, BYTE lfdefPitchAndFamily = FF_DONTCARE, BYTE ndefCharSet = ANSI_CHARSET);

// Attributes
	int m_nLogPixelsY;
	int m_nLogPixelsX;

	// Map with LOGFONT structures (needed by GetLogFontRef() in CGXFont)
	CGXMapFontData m_mapFontData;

	// All fonts installed on system
	int m_nFontInfoCount;
	CGXFontInfo* m_aFontInfo;

	// Fonts used in OG but not installed on system
	CPtrArray m_apNotInstalledFontInfo;

	// max. 1023 used fonts either installed or not installed (see index in CGXFontInfo)
	CPtrArray m_apUsedFonts;  
};

#if defined(_GXDLL)
	#define GXGetFontState() (&GXGetAppState()->m_fontState)
#else
	// QA: 32120 - Wrapping with CThreadLocal and removing the &
	// reference in GXGetFontState.
	extern CThreadLocal<GX_FONT_STATE> GXNEAR _gxFontState;
	#define GXGetFontState() (_gxFontState)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_CTLUSR_STATE : Controls created by Dialog Template

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_CTLUSR_STATE
#else
	struct GX_CTLUSR_STATE : public CNoTrackObject
#endif
{
	CMapPtrToWord   m_ctrlmap;
};

/////////////////////////////////////////////////////////////////////////////
// GX_IME_STATE : Controls created by Dialog Template

#if _MFC_VER >= 0x0400

class CGXNoImeProxy;

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_IME_STATE
#else
	struct GX_IME_STATE : CNoTrackObject
#endif
{
	CGXNoImeProxy* m_pImeProxy;

	GRID_API GX_IME_STATE();
	GRID_API ~GX_IME_STATE();
};

#if defined(_GXDLL)
	#define GXGetImeState() (&GXGetAppState()->m_imeState)
#else
	// QA: 32120 - Wrapping in CThreadLocal and removing &
	// reference in GXGetImeState().
	extern CThreadLocal<GX_IME_STATE> GXNEAR _gxImeState;
	#define GXGetImeState() (_gxImeState)
#endif

#endif

/////////////////////////////////////////////////////////////////////////////
// System settings and colors

// QA: 32120 - Deriving from CNoTrackObject
#ifdef _GXDLL
	struct GX_SYS_DATA
#else
	struct GX_SYS_DATA : public CNoTrackObject
#endif
{
	CDWordArray     m_argbSysColors;
	int             m_nSysColors;

	// system metrics
	int cxBorder2, cyBorder2;

	// color values of system colors used for CToolBar
	COLORREF clrBtnFace, clrBtnShadow, clrBtnHilite;
	COLORREF clrWindowFrame, clr3DLight, clr3DDkShadow;
	COLORREF clrText, clrWindow, clrHighlight, clrHighlightText;

	// standard cursors
	HCURSOR hcurArrow;
	HCURSOR hcurHSplit, hcurVSplit;

	// other system information
	BOOL    bWin4;          // TRUE if Windows 4.0

	// Bitmaps with system colors
	CBitmap m_bmpDownArrow;
	CBitmap m_bmpDownArrowDisabled;

	GRID_API GX_SYS_DATA();
	GRID_API ~GX_SYS_DATA();

	GRID_API void UpdateSysColors();
	GRID_API void UpdateSysSettings();
	GRID_API COLORREF GetSysColor(int nIndex);
};

#if defined(_GXDLL)
	#define GXGetSysData() (&GXGetAppState()->m_sysData)
#else
	// QA: 32120 - Wrapping in CThreadLocal and removing &
	// reference in GXGetSysData().
	extern CThreadLocal<GX_SYS_DATA> GXNEAR _gxSysData;
	#define GXGetSysData() (_gxSysData)
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_APP_STATE : Containter for all States

#if defined(_GXDLL)

class CGXAppData;
struct CGXClassRegState;

#if _MFC_VER >= 0x0400
struct GX_APP_STATE: public CNoTrackObject
#else
struct GX_APP_STATE
#endif
{
	GX_WAIT_STATE   m_waitState;
	GX_FR_STATE     m_lastFRState;
	GX_DRAW_STATE   m_drawState;
	GX_CURSOR_STATE m_cursorState;
	GX_CTLUSR_STATE m_ctlusrState;
	GX_FONT_STATE   m_fontState;
	GX_DIB_STATE    m_DIBState;
	GX_SYS_DATA     m_sysData;
#if _MFC_VER >= 0x0400
	GX_IME_STATE    m_imeState;
#endif

	CGXAppData      *m_pAppData;

	// Language Dlls
	CGXLangDll*     m_pLangDll;

#if _MFC_VER < 0x0400
	// map with more process local objects (emulateu PROCESS_LOCAL macro under 16-Bit)
	CMapPtrToPtr    m_mapProcessLocalData;
#endif
 
	CGXClassRegState* m_pClassRegState;

	GX_APP_STATE();
	~GX_APP_STATE();
};

GRID_API GX_APP_STATE* AFXAPI GXGetAppState();
#endif

struct _gxClassRegStateNode
{
	GRID_API _gxClassRegStateNode();
	GRID_API _gxClassRegStateNode(AFX_MODULE_STATE* pState);
	GRID_API ~_gxClassRegStateNode();
	
	AFX_MODULE_STATE* m_pState;
	_gxClassRegStateNode* m_pNext;
};

struct _gxClassRegStateList
{
	GRID_API _gxClassRegStateList();
	GRID_API ~_gxClassRegStateList();
	
	GRID_API void Add(AFX_MODULE_STATE* pState);
	GRID_API void Remove(AFX_MODULE_STATE* pState);
	GRID_API AFX_MODULE_STATE* GetNextState();
	GRID_API BOOL IsEmpty();

	_gxClassRegStateNode* m_pHead;
};

#ifdef _GXDLL
struct CGXClassRegState
{
	AFX_MODULE_STATE* m_pRegisterState;
	_gxClassRegStateList* m_pList;
	BOOL m_bIgnoreAdd;

	GRID_API CGXClassRegState();
	GRID_API ~CGXClassRegState();
	GRID_API void RegisterDone(AFX_MODULE_STATE* pState);
	GRID_API void RegisterRevoke(AFX_MODULE_STATE* pState);
};

#else
// static builds only a stub is needed
// QA: Deriving from CNoTrackObject
struct CGXClassRegState : public CNoTrackObject
{
	GRID_API CGXClassRegState();
	GRID_API ~CGXClassRegState();
	GRID_API void RegisterDone(AFX_MODULE_STATE* pState);
	GRID_API void RegisterRevoke(AFX_MODULE_STATE* pState);
};
#endif // _GXDLL

#ifdef _GXDLL
	GRID_API CGXClassRegState* GXGetRegState();
	
	struct GX_CLASSREG_STATE: public CNoTrackObject
	{
		CGXClassRegState* m_pClassRegState;

		GRID_API GX_CLASSREG_STATE();
		GRID_API ~GX_CLASSREG_STATE();
	};
#else

	// QA: 32120 - Wrapping in CThreadLocal and removing &
	// reference in GXGetRegState().
	extern CThreadLocal<CGXClassRegState> _gxRegState;
	#define GXGetRegState() (_gxRegState)
#endif //_GXDLL

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif //_GXSTATE_H_

/////////////////////////////////////////////////////////////////////////////
