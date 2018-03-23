///////////////////////////////////////////////////////////////////////////////
// GXSTYDLG.h
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

#ifndef _GXSTYDLG_H_
#define _GXSTYDLG_H_

#ifndef _GXRESRC_H_
#include "gxresrc.h"
#endif

#ifndef _GXSTYLES_H_
#include "gxstyles.h"
#endif

#ifndef _GXWND_H_
#include "gxwnd.h"
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

// classes defined in this header file

class CGXStylesDialog;
class CGXStyleSheet;
class CGXFontPage;
class CGXColorPage;
class CGXBorderPage;
class CGXAlignmentPage;
class CGXMergeCellPage;
class CGXFloatCellPage;
class CGXControlPage;
class CGXUserAttributPage;
class CGXBasedOnPage;
class CGXFormatPage;
class CGXGridParam;

/////////////////////////////////////////////////////////////////////////////
// CGXStylesDialog dialog

class CGXStylesDialog : public CDialog
{
	GRID_DECLARE_DYNAMIC(CGXStylesDialog)

// Construction
public:
	GRID_API CGXStylesDialog(CWnd* pParent = NULL);   // standard constructor

	GRID_API void SetStylesMap(CGXStylesMap& stylesmap);
	GRID_API const CGXStylesMap& GetStylesMap();
	GRID_API void SetParam(CGXGridParam* pParam);

protected:
// Dialog Data
	//{{AFX_DATA(CGXStylesDialog)
	enum { IDD = IDD_GXSTYLESDLG };
	CComboBox   m_cbStyles;
	CButton m_btnRemoveStyle;
	CButton m_btnChangeStyle;
	CButton m_btnAddStyle;
	BOOL    m_bSaveDefault;
	CString m_sStyle;
	//}}AFX_DATA

	CGXStylesMap m_StylesMap;
	CGXGridParam* m_pParam;

// Overrides
	GRID_API virtual CGXStyleSheet* CreateStyleSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXStylesDialog)
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	GRID_API virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGXStylesDialog)
	GRID_API afx_msg void OnBtnAddStyle();
	GRID_API afx_msg void OnBtnChangeStyle();
	GRID_API afx_msg void OnBtnLoadDefStyles();
	GRID_API afx_msg void OnBtnRemoveStyle();
	GRID_API afx_msg void OnSelchangeStyleNames();
	GRID_API afx_msg void OnEditchangeStyleName();
	GRID_API afx_msg void OnDblclkStyleNames();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXStyleSheet

class CGXStyleSheet : public CGXPropertySheet
{
	GRID_DECLARE_DYNAMIC(CGXStyleSheet)

// Construction
public:
	GRID_API CGXStyleSheet(UINT nIDCaption, CGXStylesMap& stylesMap, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	GRID_API CGXStyleSheet(LPCTSTR pszCaption, CGXStylesMap& stylesMap, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	GRID_API CGXStyleSheet(UINT nIDCaption, CGXGridParam* pParam, CGXStylesMap* pStylesMap = NULL, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	GRID_API CGXStyleSheet(LPCTSTR pszCaption, CGXGridParam* pParam, CGXStylesMap* pStylesMap = NULL, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	GRID_API virtual void CreatePages();

// Attributes
protected:
	GRID_API void Init();

	CGXStyle*       m_pStyle;
	CGXStyle*       m_pDefaultStyle;
	CGXStylesMap*   m_pStylesMap;
	CGXGridParam*   m_pParam;

	CGXFontPage*        m_pFontPage;
	CGXColorPage*       m_pColorPage;
	CGXBorderPage*      m_pBorderPage;
	CGXAlignmentPage*   m_pAlignmentPage;
	CGXMergeCellPage*  m_pMergeCellPage;
	CGXFloatCellPage*  m_pFloatCellPage;
	CGXControlPage*     m_pControlPage;
	CGXUserAttributPage* m_pUserAttributPage;
	CGXBasedOnPage*     m_pBasedOnPage;
	CGXFormatPage*		m_pFormatPage;

protected:
	// Overridable factory methods for creating the pages.
	GRID_API virtual CGXFontPage* CreateFontPage();
	GRID_API virtual CGXColorPage* CreateColorPage();
	GRID_API virtual CGXBorderPage* CreateBorderPage();
	GRID_API virtual CGXAlignmentPage* CreateAlignmentPage();
	GRID_API virtual CGXMergeCellPage* CreateMergeCellPage();
	GRID_API virtual CGXFloatCellPage* CreateFloatCellPage();
	GRID_API virtual CGXControlPage* CreateControlPage();
	GRID_API virtual CGXUserAttributPage* CreateUserAttributPage();
	GRID_API virtual CGXBasedOnPage* CreateBasedOnPage();
	GRID_API virtual CGXFormatPage* CreateFormatPage();

public:
	GRID_API virtual void UpdateData(BOOL bSaveAndValidate);

	GRID_API void SetStyle(const CGXStyle& style);
	GRID_API void SetDefaultStyle(const CGXStyle& style);
	GRID_API void SetStylesMap(const CGXStylesMap& stylesMap);
	GRID_API const CGXStyle& GetStyle() const;
	GRID_API const CGXStyle& GetDefaultStyle() const;
	GRID_API const CGXStylesMap& GetStylesMap() const;

// Operations
public:

	//{{AFX_VIRTUAL(CGXStyleSheet)
	GRID_API virtual SEC_INT DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXStyleSheet();

protected:
	//{{AFX_MSG(CGXStyleSheet)
	GRID_API afx_msg void OnOK();
	GRID_API afx_msg BOOL OnNcActivate(BOOL bActive);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGXFontPage dialog

// CGXTextColorComboBox control

class CGXTextColorComboBox : public CComboBox
{
// Construction
public:
	GRID_API CGXTextColorComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTextColorComboBox)
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXTextColorComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTextColorComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

// CGXFontSample control

class CGXFontSample : public CWnd
{
public:
	GRID_API CGXFontSample();

// attributes
	COLORREF	m_rgbTextColor;
	CFont*		m_pFont;
	int			m_nOrientation;

	GRID_API void SetTextColor(COLORREF rgbColor);
	GRID_API COLORREF GetTextColor() const;

	GRID_API void SetSampleFont(CFont* pFont, BOOL nOrientation = 0);
	GRID_API CFont* GetSampleFont();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXFontSample)
	//}}AFX_VIRTUAL

//#if _MFC_VER < 0x0300
	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXFontSample)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXFontFaceNameBox window

class CGXFontFaceNameBox : public CComboBox
{
// Construction
public:
	GRID_API CGXFontFaceNameBox();

	// Attributes
public:
	CBitmap  m_bmTTFont;
	COLORREF m_rgbWindowText;
	COLORREF m_rgbWindow;
	COLORREF m_rgbHilight;
	COLORREF m_rgbHilightText;

// Operations
public:
	GRID_API void InitSysColors();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXFontFaceNameBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXFontFaceNameBox();
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGXFontFaceNameBox)
	GRID_API afx_msg void OnSysColorChange();
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CGXFontPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXFontPage)

// Construction
public:
	GRID_API CGXFontPage(const CGXFont* pFont = NULL);
	GRID_API virtual ~CGXFontPage();

//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXFONTPAGE
//	#define IDD_GXFONTPAGE IDD_GXFONTTAB
//#endif
// Dialog Data
	//{{AFX_DATA(CGXFontPage)
	enum { IDD = IDD_GXFONTPAGE };
	CComboBox	m_cbOrientation;
	CButton		m_btnStrikeout;
	CButton		m_btnUnderline;
	CComboBox   m_cbSize;
	CComboBox   m_cbOutline;
	//}}AFX_DATA

	CGXTextColorComboBox	m_cbTextColor;
	CGXFontSample			m_wndSample;
	CGXFontFaceNameBox		m_cbFaceName;

	CGXFont     m_font;
	CGXFont     m_fontParent;
	CString     m_sParentName;
	CFont       fontSample;
	COLORREF    m_rgbText;
	BOOL        m_bIncludeText;

	GRID_API void SetParentFont(const CGXFont* pFontParent, LPCTSTR szParentName = NULL);
	GRID_API const CGXFont& GetFont() const;
	GRID_API void SetFont(const CGXFont* pFont);
	GRID_API void SetIncludeTextColor(BOOL b);
	GRID_API BOOL GetIncludeTextColor();
	GRID_API void SetTextColor(COLORREF rgbColor);
	GRID_API COLORREF GetTextColor();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXFontPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bUpdate;

	// Generated message map functions
	//{{AFX_MSG(CGXFontPage)
	GRID_API afx_msg void OnSelchangeFaceName();
	GRID_API afx_msg void OnSelchangeOutline();
	GRID_API afx_msg void OnSelchangeSize();
	GRID_API afx_msg void OnKillfocusSize();
	GRID_API afx_msg void OnSelchangeOrientation();
	GRID_API afx_msg void OnKillfocusOrientation();
	GRID_API afx_msg void OnKillfocusOutline();
	GRID_API afx_msg void OnKillfocusFacename();
	GRID_API afx_msg void OnUnderlineClicked();
	GRID_API afx_msg void OnStrikeoutClicked();
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnCloseupGxcbtextcolor();
	GRID_API afx_msg void OnEditchangeGxcbtextcolor();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXColorPage dialog

// CGXColorButtonBox control

class CGXColorButtonBox : public CWnd
{
	GRID_DECLARE_REGISTER()

// Construction
public:
	GRID_API CGXColorButtonBox();

// Attributes
public:
	GRID_API int GetCurSel() const;
	GRID_API void SetCurSel(int nIndex);

	int m_nCurSel;
	BOOL m_bDefaultButton;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorButtonBox)
	//}}AFX_VIRTUAL

//#if _MFC_VER < 0x0300
	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Implementation
public:
	GRID_API virtual ~CGXColorButtonBox();
	GRID_API CRect GetButtonRect(int nIndex) const;
	GRID_API BOOL HitTest(const CPoint& pt, int& retVal) const;
	GRID_API void DrawColorButton(CDC* pDC, int nIndex) const;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXColorButtonBox)
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

// CGXColorSample control

class CGXColorSample : public CWnd
{
	GRID_DECLARE_REGISTER()

public:
	GRID_API CGXColorSample();

// Attributes
	CGXBrush    m_brInterior;
	int         m_n3dFrame;

	GRID_API void SetBrush(CBrush* pBrush);
	GRID_API CBrush* GetBrush() const;

	GRID_API void SetInterior(const CGXBrush& logbrush);
	GRID_API const CGXBrush& GetInteriorRef() const;

	GRID_API int Get3dFrame() const;
	GRID_API void Set3dFrame(int n);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorSample)
	//}}AFX_VIRTUAL

//#if _MFC_VER < 0x0300
	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXColorSample)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

// CGXPatternComboBox control

class CGXPatternComboBox : public CComboBox
{
// Construction
public:
	GRID_API CGXPatternComboBox();

// Attributes
public:
	COLORREF m_rgbText,
			 m_rgbBack;

	GRID_API COLORREF GetTextColor() const;
	GRID_API void SetTextColor(COLORREF rgbColor);

	GRID_API COLORREF GetBackColor() const;
	GRID_API void SetBackColor(COLORREF rgbColor);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXPatternComboBox)
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXPatternComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXPatternComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};


// CGXColorPage dialog

class CGXColorPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXColorPage)

// Construction
public:
	GRID_API CGXColorPage();
	GRID_API virtual ~CGXColorPage();

	// Parent Style
//  void SetParentColor(CGXBrush brParent, COLORREF rgbBack, LPCTSTR szParentName = NULL);

	// Interior
	GRID_API BOOL GetIncludeInterior() const;
	GRID_API void SetIncludeInterior(BOOL b);
	GRID_API const CGXBrush& GetInterior() const;
	GRID_API void SetInterior(const CGXBrush& brush);

	// 3d Frame
	GRID_API int Get3dFrame() const;
	GRID_API void Set3dFrame(int n);

protected:
// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXCOLORPAGE
//	#define IDD_GXCOLORPAGE IDD_GXCOLORTAB
//#endif
	//{{AFX_DATA(CGXColorPage)
	enum { IDD = IDD_GXCOLORPAGE };
	CStatic m_textBaseStyle;
	int     m_n3dFrame;
	//}}AFX_DATA

	CGXColorButtonBox   m_wndBackColor;
	CGXColorButtonBox   m_wndTextColor;
	CGXColorSample      m_wndColorSample;

	GRID_API CGXColorButtonBox& BackColorWnd();
	GRID_API CGXColorButtonBox& TextColorWnd();
	GRID_API CGXColorSample& ColorSampleWnd();

	CGXPatternComboBox m_cbPatterns;

	CGXBrush    m_logbrushParent;
	BOOL        m_bIncludeInterior;
	CGXBrush    m_logbrushInterior;
	CBrush      m_brSample;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXColorPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CGXColorPage)
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg LRESULT OnChangedColor(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnGxbtn3dradioClicked();
	GRID_API afx_msg void OnSelchangeGxcombopattern();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXBorderPage Propertypage

// CGXBorderTypeButton control

class CGXBorderTypeButton : public CButton
{
// Construction
public:
	GRID_API CGXBorderTypeButton();
	GRID_API void SetLogPen(const LOGPEN& logpen);
	GRID_API const LOGPEN& GetLogPen();
	GRID_API void EnableCheckBox(BOOL b);
	GRID_API void SetColor(COLORREF rgbColor);
	GRID_API void SetActive(BOOL b);

	GRID_API void SetInclude(BOOL b);
	GRID_API BOOL GetInclude();

// Attributes
protected:
	LOGPEN m_logpen;
	BOOL m_bCheckBox;
	int m_bInclude;

	CPen m_pen;
	BOOL m_bActive;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBorderTypeButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXBorderTypeButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXBorderTypeButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

// CGXColorComboBox control

class CGXColorComboBox : public CComboBox
{
// Construction
public:
	GRID_API CGXColorComboBox();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorComboBox)
public:
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXColorComboBox();

	// Generated message map functions

	GRID_DECLARE_MESSAGE_MAP()
};

class CGXBorderPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXBorderPage)

// Public interface
public:
	GRID_API CGXBorderPage();
	GRID_API virtual ~CGXBorderPage();

	GRID_API BOOL GetIncludeBorders(int nBorder);
	GRID_API void SetIncludeBorders(int nBorder, BOOL b);

	GRID_API void SetBorders(int nBorder, const LOGPEN& pen);
	GRID_API const LOGPEN& GetBorders(int nBorder);

	GRID_API void EnableRangeButton(BOOL bVisible);

//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXBORDERSPAGE
//	#define IDD_GXBORDERSPAGE IDD_GXBORDERSTAB
//#endif
// Implementation
protected:
	//{{AFX_DATA(CGXBorderPage)
	enum { IDD = IDD_GXBORDERSPAGE };
	//}}AFX_DATA

	CGXBorderTypeButton m_btnType[8];
	CGXBorderTypeButton m_btnBorder[5];
	CGXColorComboBox m_lboxColors;

	UINT m_nCurType;
	BOOL m_bRange;
	UINT m_nCurBorder;

	//{{AFX_VIRTUAL(CGXBorderPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGXBorderPage)
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnSelendokCombocolor();
	GRID_API afx_msg void OnCloseupCombocolor();
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXAlignmentPage dialog

class CGXAlignmentPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXAlignmentPage)

// Construction
public:
	GRID_API CGXAlignmentPage();
	GRID_API virtual ~CGXAlignmentPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXALIGNPAGE
//	#define IDD_GXALIGNPAGE IDD_GXALIGNTAB
//#endif
	//{{AFX_DATA(CGXAlignmentPage)
	enum { IDD = IDD_GXALIGNPAGE };
	int     m_nAllowEnter;
	int     m_nWrapText;
	int     m_nHorzAlign;
	int     m_nVertAlign;
	int     m_nAutoSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXAlignmentPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXAlignmentPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXMergeCellPage dialog

class CGXMergeCellPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXMergeCellPage)

// Construction
public:
	GRID_API CGXMergeCellPage();
	GRID_API virtual ~CGXMergeCellPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXMERGEPAGE
//	#define IDD_GXMERGEPAGE IDD_GXMERGETAB
//#endif
	//{{AFX_DATA(CGXMergeCellPage)
	enum { IDD = IDD_GXMERGEPAGE };
	int     m_nMergeCell;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXMergeCellPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXMergeCellPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXFloatCellPage dialog

class CGXFloatCellPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXFloatCellPage)

// Construction
public:
	GRID_API CGXFloatCellPage();
	GRID_API virtual ~CGXFloatCellPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXFLOATPAGE
//	#define IDD_GXFLOATPAGE IDD_GXFLOATTAB
//#endif
	//{{AFX_DATA(CGXFloatCellPage)
	enum { IDD = IDD_GXFLOATPAGE };
	int     m_nFloatCell;
	int     m_nFloodCell;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXFloatCellPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXFloatCellPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXControlPage dialog

class CGXControlPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXControlPage)

// Construction
public:
	GRID_API CGXControlPage();
	GRID_API virtual ~CGXControlPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXCONTROLPAGE
//	#define IDD_GXCONTROLPAGE IDD_GXCONTROLTAB
//#endif
	//{{AFX_DATA(CGXControlPage)
	enum { IDD = IDD_GXCONTROLPAGE };
	CComboBox   m_cbControlName;
	CEdit   m_editValue;
	CButton m_checkValue;
	int     m_nReadOnly;
	CString m_sChoices;
	int     m_nValue;
	CString m_sValue;
	CString m_sMaxLength;
	int     m_nTriState;
	int     m_nEnabled;
	//}}AFX_DATA

	// int      m_nVertScrollbar;

	// Control
	WORD m_nControl;       // UINT_MAX indicates that no control is specified

	const CMapWordToPtr* m_pControlNameMap;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXControlPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXControlPage)
	GRID_API virtual BOOL OnInitDialog();
	GRID_API afx_msg void OnGxcheckValue();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXUserAttributPage dialog

class CGXUserAttributPageGrid : public CGXGridWnd
{
	GRID_DECLARE_REGISTER()

public:
	// Attributes
	CString m_sNameTitle, m_sValueTitle;

public:
	// Overridables
	GRID_API virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType);
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol);
};

class CGXUserAttributPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXUserAttributPage)

// Construction
public:
	GRID_API CGXUserAttributPage();
	GRID_API virtual ~CGXUserAttributPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXUSERATTRPAGE
//	#define IDD_GXUSERATTRPAGE IDD_GXUSERATTRTAB
//#endif
	//{{AFX_DATA(CGXUserAttributPage)
	enum { IDD = IDD_GXUSERATTRPAGE };
	//}}AFX_DATA

	CGXUserAttributPageGrid m_userGrid;
	CStringArray			m_arrayContent;
	CByteArray				m_arrayInclude;
	CWordArray				m_arrayID;
	const CMapWordToPtr*	m_pUserAttrInfoMap;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXUserAttributPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXUserAttributPage)
	GRID_API virtual BOOL OnInitDialog();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXBasedOnPage dialog

class CGXBasedOnPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXBasedOnPage)

// Construction
public:
	GRID_API CGXBasedOnPage();
	GRID_API virtual ~CGXBasedOnPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXSPECIALPAGE
//	#define IDD_GXSPECIALPAGE IDD_GXSPECIALTAB
//#endif
	//{{AFX_DATA(CGXBasedOnPage)
	enum { IDD = IDD_GXSPECIALPAGE };
	CComboBox   m_cbBasedOn;
	CString     m_sBasedOn;
	//}}AFX_DATA

	CStringList m_BasedOnStringList;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXBasedOnPage)
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXBasedOnPage)
	GRID_API virtual BOOL OnInitDialog();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXFormatPage dialog

class CGXFormatPage : public CGXPropertyPage
{
	GRID_DECLARE_DYNCREATE(CGXFormatPage)

// Construction
public:
	GRID_API CGXFormatPage();	// standard constructor
	GRID_API virtual ~CGXFormatPage();

// Dialog Data
//#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
//	#undef IDD_GXFORMATPAGE
//	#define IDD_GXFORMATPAGE IDD_GXFORMATTAB
//#endif
	int		m_nFormat;
	//{{AFX_DATA(CGXFormatPage)
	enum { IDD = IDD_GXFORMATPAGE };
	CComboBox	m_cbFormat;
	CString		m_strPlaces;
	//}}AFX_DATA

// Implementation
protected:
	GRID_API virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGXFormatPage)
	GRID_API virtual BOOL OnInitDialog();
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

#endif // _GXSTYDLG_H_
