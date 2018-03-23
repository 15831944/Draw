///////////////////////////////////////////////////////////////////////////////
// gxcurctl.h : Currency Control
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
// Authors: Daniel Jebaraj, Praveen Ramesh
//
// Portions of this code were copied from Objective Toolkit.


#ifndef _GXCURCTL_H_
#define _GXCURCTL_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

// header file

#ifndef _GXCURBAS_H_
#include "gxcurbas.h"
#endif

#ifndef _GXCTRLI_H_
#include "gxctrli.h"
#endif

// // #include <StingrayExportDefs.h>

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXCaptiveCurEdit: public CGXBCurrencyEdit
{
	friend class CGXCurrencyEdit;
};

/////////////////////////////////////////////////////////////////////////////
// CGXCurrencyEdit control

class CGXCurrencyEdit : public CGXBCurrencyEdit, public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXCurrencyEdit)
	GRID_DECLARE_DYNAMIC(CGXCurrencyEdit)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXCurrencyEdit(CGXGridCore* pGrid, UINT nID);
	GRID_API virtual ~CGXCurrencyEdit();

	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

	// Status
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();

	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();

	// Operations
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Stores the cell coordinates, resets the style and sets the window text

	GRID_API virtual BOOL Store();
		// Call SetStyleRange() and assign FALSE to m_bIsActive
		// Cell will be automatically redrawn inactive

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		// }

	GRID_API virtual void Hide();
		// Hides the CGXBCurrencyEdit without changing the m_bIsActive flag

	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual void SetCurrentText(const CString& str);

	// Mouse hit
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	// Called when the user presses a key on the inactive current cell
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);

	// Find and Replace
	GRID_API virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	GRID_API virtual void ReplaceSel(LPCTSTR pszReplaceText);
	GRID_API virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL GetSelectedText(CString& strResult);

	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// clipboard
	GRID_API virtual BOOL Paste();
	GRID_API virtual BOOL Cut();
	GRID_API virtual BOOL Copy();

	// Edit control only
	GRID_API int  CalcTextPosUnderPt(CPoint point);
	GRID_API void GetSel(int& nStartChar, int& nEndChar) const;
	GRID_API DWORD GetSel() const;

	GRID_API virtual BOOL CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL);
	GRID_API virtual CWnd* GetWndPtr() const;
	GRID_API virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual void InitFromUserAttributes(CGXBCurrencyEdit* pEdit, const CGXStyle* pStyle);
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;
	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
	

// Implementation
public:
	GRID_API virtual BOOL CreateControl(DWORD dwStyle = 0);

// Attributes
protected:
	UINT    m_nID;
	BOOL    m_bIsActive;    // indicates, if the CWnd is active
	CFont   m_font;
	int     m_dyHeight;
	int     m_dxMaxCharWidth;
	CString m_sLastChar;
	BOOL    m_bDoNotEmptyLastChar;
	BOOL	m_bSetText;
	BOOL	m_bFirst;
	BOOL	m_bIgnoreFractions;
	ROWCOL	m_LFRow;
	BOOL	m_bFromInit;
	BOOL	m_bModified;	
	CGXCaptiveCurEdit m_CapCtrlWnd;	
	//Added these 4/1/97
	BOOL	m_bForceHitTrue;
	GRID_API static TCHAR m_cBlankThouSep;
	GRID_API static TCHAR m_cBlankMonetarySym;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCurrencyEdit)
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	GRID_API afx_msg LRESULT OnCalcSetText(WPARAM wParam, LPARAM lParam);
#if _MFC_VER >= 0x0400
	GRID_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
#endif
	GRID_DECLARE_MESSAGE_MAP()
};

#ifdef _GX_ENABLE_INLINES
inline void CGXCurrencyEdit::GetSel(int& nStartChar, int& nEndChar) const
	{ ASSERT(::IsWindow(m_hWnd)); DWORD dw = (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); nStartChar = LOWORD(dw); nEndChar = HIWORD(dw); }

inline DWORD CGXCurrencyEdit::GetSel() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); }
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
#endif // _MFC_VER >= 0x0400

#endif //_GXCURCTL_H_
