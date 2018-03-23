///////////////////////////////////////////////////////////////////////////////
// GXPRDLG.h
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

#ifndef _GXPRPDLG_H_
#define _GXPRPDLG_H_

#ifndef _GXWND_H_
#include "gxwnd.h"
#endif

#ifndef _GXRESRC_H_
#include "gxresrc.h"
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

class CGXStyle;
class CGXStylesMap;
class CGXGridParam;


/////////////////////////////////////////////////////////////////////////////
// CGXDisplayPropertiesDialog dialog

class CGXGridLineColorBox : public CWnd
{
// Construction
public:
	GRID_API CGXGridLineColorBox();

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Attributes
public:
	GRID_API int GetCurSel() const;
	GRID_API void SetCurSel(int nIndex);

	int m_nCurSel;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXGridLineColorBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXGridLineColorBox();
	GRID_API CRect GetButtonRect(int nIndex) const;
	GRID_API BOOL HitTest(const CPoint& pt, int& retVal) const;
	GRID_API void DrawColorButton(CDC* pDC, int nIndex) const;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridLineColorBox)
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

class CGXUserPropertyGrid : public CGXGridWnd
{

public:
	// Attributes
	CString m_sNameTitle,
			m_sValueTitle;

public:
	// Overridables
	GRID_API virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType);
	GRID_API virtual void OnInitialUpdate();
};

class CGXDisplayPropertiesDialog : public CDialog
{
// Construction
public:
	GRID_API CGXDisplayPropertiesDialog(CGXProperties* pSettings, CGXStylesMap* pStylesMap, BOOL* pbSaveDefault, BOOL bIsChild, UINT nIDTemplate = GX_IDD_SETTINGS_DLG, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGXDisplayPropertiesDialog)
	enum { IDD = GX_IDD_SETTINGS_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	BOOL*   m_pbSaveDefault;
	BOOL    m_bCurrentDialog;
	BOOL    m_bChild;

	CGXProperties*	m_pSettings;
	CGXStylesMap*	m_pStylesMap;
	CWordArray		m_arrayID;
	CGXGridLineColorBox m_wndColorBox;
	CGXUserPropertyGrid m_wndUserGrid;
	CGXGridWnd			m_wndPreviewGrid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDisplayPropertiesDialog)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GRID_API void UpdateSettings(BOOL bSave);

	// Generated message map functions
	//{{AFX_MSG(CGXDisplayPropertiesDialog)
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnClickedBtnPrinter();
	GRID_API afx_msg void OnCheckedCtl();
	GRID_API virtual void OnOK();
	GRID_API virtual void OnCancel();
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg LRESULT OnChangedColor(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnSelchangeIdcListcolors();
	GRID_API afx_msg BOOL OnNcActivate(BOOL bActive);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXPrintPropertiesDialog dialog

class CGXPrintPropertiesWnd : public CGXGridWnd
{
// Construction
public:
	GRID_API CGXPrintPropertiesWnd();

// Attributes
public:

// Operations
public:

// Implementation
public:
	GRID_API virtual ~CGXPrintPropertiesWnd();

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXPrintPropertiesWnd)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

class CGXPrintPropertiesDialog : public CDialog
{
// Construction
public:
	GRID_API CGXPrintPropertiesDialog(CGXProperties* pSettings, CGXStylesMap* pStylesMap, BOOL* bSaveDefault, CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CGXPrintPropertiesDialog)
	enum { IDD = GX_IDD_SETTINGS_PRINT };
	CString m_sMarginBottom;
	CString m_sMarginLeft;
	CString m_sMarginRight;
	CString m_sMarginTop;
	BOOL    m_bCenterHorizontal;
	BOOL    m_bCenterVertikal;
	BOOL    m_bColHeaders;
	BOOL    m_bHorzLines;
	BOOL    m_bRowHeaders;
	BOOL    m_bVertLines;
	BOOL    m_bBlackWhite;
	BOOL    m_bPrintFrame;
	int     m_nPageOrder;
	//}}AFX_DATA
	BOOL*   m_pbSaveDefault;
	BOOL    m_bCurrentDialog;
	BOOL    m_bUseInch;

	CGXProperties* m_pSettings;
	CGXStylesMap* m_pStylesMap;

	CGXPrintPropertiesWnd m_wndPreview;

// Implementation
protected:
	GRID_API void UpdateSettings(BOOL bSave);
	GRID_API void UpdatePreview();
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGXPrintPropertiesDialog)
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnBtnPrinter();
	GRID_API afx_msg void OnCheckedCtl();
	GRID_API virtual void OnOK();
	GRID_API afx_msg void OnDestroy();
	GRID_API virtual void OnCancel();
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXHeaderFooterDialog dialog

class CGXHeaderFooterGrid : public CGXGridWnd
{
public:
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual BOOL OnActivateGrid(BOOL bActivate);
	GRID_API virtual void OnInitCurrentCell(ROWCOL nRow, ROWCOL nCol);

	// Generated message map functions
	//{{AFX_MSG(CGXHeaderFooterGrid)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

class CGXHeaderFooterDialog : public CDialog
{
// Construction
public:
	GRID_API CGXHeaderFooterDialog(
		CGXProperties* pSettings,
		BOOL* pbSaveDefault,
		CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CGXHeaderFooterDialog)
	enum { IDD = GX_IDD_SETTINGS_HEADERFOOTER };
	CString m_sDistFootNote;
	CString m_sDistHeader;
	CString m_sPageFirst;
	//}}AFX_DATA
	BOOL*           m_pbSaveDefault;
	BOOL            m_bCurrentDialog;
	CWnd*           m_wndActive;
	BOOL            m_bUseInch;

	CGXProperties* m_pSettings;

	GRID_API CGXTabWnd& GetTabWnd();

protected:
	CGXHeaderFooterGrid m_gridHeader;
	CGXHeaderFooterGrid m_gridFooter;

	CGXGridParam parHeader,
				 parFooter;

	CGXProperties properties;
	CGXStylesMap  stylesmap;

// Implementation
protected:
	GRID_API void DoFontDialog(CGXGridWnd* pGrid);

	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	GRID_API virtual void UpdateSettings(BOOL bSave);

	// Generated message map functions
	//{{AFX_MSG(CGXHeaderFooterDialog)
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnClickedBtnFont();
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API virtual void OnCancel();
	GRID_API virtual void OnOK();
	GRID_API afx_msg void OnClickedBtnPrinter();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXPRPDLG_H_
