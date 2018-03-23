///////////////////////////////////////////////////////////////////////////////
// gxdtctrl.h : Declarations for the Calendar Control
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

#ifndef _GXDTCTRL_H_
#define _GXDTCTRL_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

#ifndef _GXDTCAL_H_
#include "gxdtcal.h"
#endif

#ifndef _GXCTRLI_H_
#include "gxctrli.h"
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

// header file

// Control format type as used by GX_IDS_UA_DATEFORMATTYPE

#define GX_DTFORMAT_TIME		_T("0")	// Locale time format
#define GX_DTFORMAT_SHORTDATE	_T("1")	// Locale short date format 
#define GX_DTFORMAT_LONGDATE	_T("2")	// Locale long date format
#define GX_DTFORMAT_CUSTOM		_T("3")	// A user supplied date/time format string 
#define GX_DTFORMAT_DATETIME	_T("4")	// Locale short date+Locale time format string 

// The validation types as used by GX_IDS_UA_DATEVALIDMODE
#define GX_DTVALIDMODE_NONE		_T("0")	// No validation is required
#define GX_DTVALIDMODE_TIME		_T("1")	// Validation of time fields only
#define GX_DTVALIDMODE_DATE		_T("2")	// Validation of date fields only
#define GX_DTVALIDMODE_DATETIME	_T("3")	// Validation of date & time fields

/////////////////////////////////////////////////////////////////////////////
// CGXDateTimeCtrl window
class CGXCaptiveDateTimeCtrl: public CGXBDateTimeCtrl
{
	
protected:
	GRID_API void SetValue(LPCTSTR pszRawValue);
	GRID_API void LayoutGadgets(CDC* pDC, CRect rect);
	GRID_API void LayoutGadgets();

	// value of UA that specifies whether string input is viewed as number
	BOOL m_bForceStrValueAsNumber;

	friend class CGXDateTimeCtrl;
};


class CGXDTGadget: public CGXBDTGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTNumericGadget: public CGXBDTNumericGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTListGadget: public CGXBDTListGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTStaticGadget: public CGXBDTStaticGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTSpinGadget: public CGXBDTSpinGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTButtonGadget: public CGXBDTButtonGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDateTimeCtrl : public CGXBDateTimeCtrl, public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXDateTimeCtrl)
	GRID_DECLARE_DYNAMIC(CGXDateTimeCtrl)

// Construction
public:
	GRID_API CGXDateTimeCtrl(CGXGridCore* pGrid, UINT nId);

protected:
	BOOL m_bDateValueAsNumber;

	// value of UA that specifies whether string input is viewed as number
	BOOL m_bForceStrValueAsNumber;

	// Precision for time
	int m_nPrecision;

public:
	//Attributes
	GRID_API virtual CWnd* GetWndPtr() const;
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

	//specifies if the spin button should be drawn in the
	//inactive state
	BOOL m_bInactiveDrawSpin;

	//specifies if the button should be drawn in the inactive state
	BOOL m_bInactiveDrawButton;

	//specifies if an empty cell should be initialized with current date
	//and time for Custom format. If FALSE, cell will be initialized with
	//PSEUDO_NULL (31.12.1899)
	BOOL m_bInitCustomCurrent;

	//specifies if tab should be processed by the control
	BOOL m_bProcessTab;
	//functions
	GRID_API BOOL CreateControl(DWORD dwStyle, LPRECT lpRect);


	// CGXControl overrides that provide the grid adapter

	// CGXControl overrides - for Current Cell only
	// state
	GRID_API virtual void Init(ROWCOL nRow,ROWCOL nCol);
	GRID_API virtual void Hide();
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();
	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();
	GRID_API virtual void SetDateValueAsNumber(BOOL bDateValueAsNumber);
	GRID_API virtual BOOL IsDateValueAsNumber();

	// value
	GRID_API virtual BOOL OnValidate();
	GRID_API virtual BOOL ValidateString(const CString& sEdit);
	GRID_API virtual void SetCurrentText(const CString& str);
	GRID_API virtual void GetCurrentText(CString& sMaskedResult);
	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual BOOL Store();

	// events
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL OnStartEditing();
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual void ReplaceSel(LPCTSTR pszReplaceText);
	GRID_API virtual BOOL GetSelectedText(CString& sWindowText);

	// copy paste
	GRID_API virtual BOOL CanCopy();
	GRID_API virtual BOOL Copy();
	GRID_API virtual BOOL CanCut();
	GRID_API virtual BOOL Cut();
	GRID_API virtual BOOL CanPaste();
	GRID_API virtual BOOL Paste();

	// CGXControl overrides - for any cell
	// drawing
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// value
	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
	GRID_API virtual BOOL GetControlText(CString& strDisplay, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
	GRID_API virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	// sorting
	GRID_API virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// CGXBDateTimeCtrl overrides
	GRID_API virtual void PositionGadget(UINT nFlags, CPoint point,  BOOL bIgnoreNullValue = FALSE);
	GRID_API virtual BOOL OnChanging(const COleDateTime& /* newDateTime */);
	GRID_API virtual void OnChanged();

	// Helpers for static rendering of the gadgets
	GRID_API virtual void DrawSpinGadget(CDC* pDC, CGXDTSpinGadget* pGadget, CRect rectClip);
	GRID_API virtual void DrawNumericGadget(CDC* pDC, CGXDTNumericGadget* pGadget, CRect rectClip);
	GRID_API virtual void DrawListGadget(CDC* pDC, CGXDTListGadget* pGadget, CRect rectClip);
	GRID_API virtual void DrawStaticGadget(CDC* pDC, CGXDTStaticGadget* pGadget, CRect rectClip);
	GRID_API virtual void DrawButtonGadget(CDC* pDC, CGXDTButtonGadget* pGadget, CRect rectClip);
	GRID_API virtual BOOL SetFormat(CGXBDateTimeCtrl& control, const CGXStyle& style);

	// other helpers
	GRID_API virtual BOOL ParseTextWithCurrentFormat(const CString& psz, const CGXStyle* pOldStyle, CStringArray& strArray );
	
protected:
	//attributes
	BOOL m_bActive;

	//the control id
	UINT m_nID;

	//for validation
	COleDateTime m_valdt;

	//for the modified flag
	BOOL m_bModify;

	//for Find/Replace support
	ROWCOL m_LastFRow, m_LastFCol;

	CString m_strlfText;

	int m_nLastGadget;

	BOOL m_bFound;

	//String containing delimiters
	CString m_strDelim;

	//used for formatting in control text
	CGXCaptiveDateTimeCtrl m_TextCtrlWnd;
	CGXCaptiveDateTimeCtrl m_DrawCtrlWnd;

	//for the drawing
	CFont m_font;

	friend class CGXBDTSpinGadget;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDateTimeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXDateTimeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXDateTimeCtrl)
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

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
#endif // _MFC_VER >= 0x0400

#endif // _GXDTCTRL_H_

