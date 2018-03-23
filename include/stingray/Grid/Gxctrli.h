///////////////////////////////////////////////////////////////////////////////
// Gxctrli.h
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

#ifndef _GXCTRLI_H
#define _GXCTRLI_H

#ifndef _GXCTRL_H
#include "gxctrl.h"
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


class CGXButton: public CGXChild
{
public:
	// construction, destrcution
	GRID_API CGXButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);


	// Mouse hit
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL MouseMove(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt);

	// Keyboard
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT flags);

	GRID_API virtual void OnGridCancelMode();

protected:
	BOOL m_bPressed;
	BOOL m_bMouseDown;
	BOOL m_bCanPress;
    BOOL m_bEnabled;
};

class CGXComboBoxButton: public CGXButton
{
public:
	// construction, destrcution
	GRID_API CGXComboBoxButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
};

class CGXHotSpotButton: public CGXButton
{
public:
	// construction, destrcution
	GRID_API CGXHotSpotButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);
};

class CGXArrowButton: public CGXButton
{
public:
	// construction, destrcution
	GRID_API CGXArrowButton(CGXControl* pComposite);

	GRID_API virtual BOOL MouseMove(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt);

	// increase/decrease speed when mouse button is pressed
	DWORD dwLastTick, dwTicksNeeded;
};

class CGXUpArrowButton: public CGXArrowButton
{
public:
	// construction, destrcution
	GRID_API CGXUpArrowButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);
};

class CGXDownArrowButton: public CGXArrowButton
{
public:
	// construction, destrcution
	GRID_API CGXDownArrowButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);
};

// CGXBitmapButtonChild supports device independent bitmaps

//@doc
//@class
//The <c CGXBitmapButtonChild> class implements a bitmap button which can be used as a child in a control.<nl> 
//<nl>
//When the user clicks the button, the control's <mf OnClickedButton> method is called.
//The default behavior of this method is to call <mf CGXGridCore::OnClickedButtonRowCol>.
//
//To process this event, you can either override the control's <mf OnClickedButton>
//method or simply override <mf OnClickedButtonRowCol> in your <c CGXGridCore>-derived class.<nl>
//<nl>
//You should create and add the button child in the constructor of your <c CGXControl>-derived class
//(the CGXChild description illustrates an edit control with a bitmap button).<nl>
//<nl>
//The rectangle for the button should be passed to the child object when the control's <mf OnInitChildren>
//method is called.
//@base public | CGXButton |
//@xref <c CGXBitmapButtonChild>  <c CGXControl> <mf CGXControl::OnClickedButton> 
class CGXBitmapButtonChild : public CGXButton
{
public:
// Construction
	//@access Operations
	//@cmember 
	//Constructs a bitmap child object.
	GRID_API CGXBitmapButtonChild(CGXControl* pComposite);
	GRID_API virtual ~CGXBitmapButtonChild();
	//@cmember
	// Loads bitmap images identified by their resource names or ID numbers. 
	GRID_API BOOL LoadBitmaps(LPCTSTR lpszBitmapResource,
			LPCTSTR lpszBitmapResourceSel = NULL,
			LPCTSTR lpszBitmapResourceFocus = NULL);

	GRID_API BOOL LoadBitmaps(UINT nIDBitmapResource,
			UINT nIDBitmapResourceSel = 0,
			UINT nIDBitmapResourceFocus = 0);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);

	GRID_API virtual CSize GetSize();
	GRID_API CSize GetSize(HANDLE hbm);

// Implementation:
public:
	// all bitmaps must be the same size
	HANDLE m_hBitmap;           // normal image (REQUIRED)
	HANDLE m_hBitmapSel;        // selected image (OPTIONAL)
	HANDLE m_hBitmapFocus;      // focused but not selected (OPTIONAL)
};

// Compatibility with OG 1.01
// CGXDIBitmapButtonChild functionality has been
// integrated into the CGXBitmapButtonChild in OG 1.1.

#define CGXDIBitmapButtonChild CGXBitmapButtonChild

/////////////////////////////////////////////////////////////////////////////
// CGXPushbutton control

class CGXPushbutton: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXPushbutton)

public:
	// Constructor & Destructor
	GRID_API CGXPushbutton(CGXGridCore* pGrid);
	GRID_API CGXPushbutton(CGXGridCore* pGrid, CGXButton* pChild);

	// Operations
	GRID_API virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Prevents inverting the borders for the current cell

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Optimizing Size
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

protected:
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes
	CGXChild* m_pButton;
};

/////////////////////////////////////////////////////////////////////////////
// CGXBitmapButton control

// CGXBitmapButton supports device independent bitmaps

//@doc 
//@class
//The CGXBitmapButton class implements a bitmap button that can be used in grid cells.<nl>
//<nl>
//To display bitmaps in cells, you need to register a <c CGXBitmapButton>  
//object for each different bitmap button. When the object is created you should pass 
//the resource ids of the bitmap to the <c CGXBitmapButton> constructor.
//<c CGXBitmapButton> can be used as a pushbutton. 
//You can specify bitmaps for normal state, pressed state and focus-state.<nl>
//<nl>
//When the user clicks the bitmap, the control's <mf OnClickedButton> method is called. 
//The default behavior of <mf OnClickedButton> is to call <mf CGXGridCore::OnClickedButtonRowCol>.<nl>
//<nl>
//To process this event, you can either subclass <c CGXBitmapButton> and override the 
//control's <mf OnClickedButton> method, or simply override <mf OnClickedButtonRowCol> in your 
//CGXGridCore-derived class.<nl>
//<nl>
//The following steps are necessary to display bitmaps in cells:<nl>
//<nl>
//1. You need to add a string resource:<nl>
//<nl>
//Example:<nl>
//<nl>
//<pre><code>
// // Your .RC - file:
//STRINGTABLE DISCARDABLE
//BEGIN
//      IDS_CTRL_BITMAP        "Welcome bitmap"
//END
//<ecode><epre>
//<nl>
//2. In <mf OnInitialUpdate>, you should pass a new instance of the object together 
//with the string resource id to <bold>RegisterControl<ebold>.<nl>
//<nl>
//<pre><code>
//void CGridSampleView::OnInitialUpdate( )
//{
//   ...
//  RegisterControl(IDS_CTRL_BITMAP,
//      new CGXBitmapButton(this, IDB_WELCOME));
//}
//<ecode><epre>
//<nl>
//3. Now, you can apply the bitmap to any cell in the grid with <mf CGXStyle::SetControl>. 
//<pre><code>
// // Display the welcome bitmap
// SetStyleRange(CGXRange( 3, 2 ), CGXStyle( )
//   .SetControl( IDS_CTRL_BITMAP ));
//<ecode><epre>
//<nl>
//@base public | CGXControl|
//@xref  <c CGXBitmapButton> <mf CGXGridCore::RegisterControl> <mf CGXStyle::SetControl>
//<mf CGXControl::OnClickedButton> <mf CGXGridCore::OnClickedButtonRowCol> 
class CGXBitmapButton: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXBitmapButton)

// Construction
public:
	// Constructor & Destructor
	//@access 
	//@cmember 
	//Constructs a bitmap control object. 
	GRID_API CGXBitmapButton(CGXGridCore* pGrid, UINT nIDBitmapResource,
		UINT nIDBitmapResourceSel = 0, UINT nIDBitmapResourceFocus = 0);

	// Operations
	GRID_API virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Prevents inverting the borders for the current cell

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

protected:
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes
	CGXBitmapButtonChild*	m_pButton;
	BOOL					m_bInvertBorders;
	BOOL					m_bCanPress;
};

// Compatibility with OG 1.01

#define CGXDIBitmapButton CGXBitmapButton

/////////////////////////////////////////////////////////////////////////////
// CGXCheckBox control

class CGXCheckBox: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXCheckBox)

public:
	// Constructor & Destructor
	GRID_API CGXCheckBox(CGXGridCore* pGrid, BOOL bDraw3d = TRUE, UINT nBitmapResourceId = 0, UINT nPrintResourceId = 0);
	GRID_API virtual ~CGXCheckBox();
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Drawing, optimal size
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL MouseMove(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// User clicked checkbox
	GRID_API virtual void OnClickedButton(CGXChild* pChild);

	// System settings
	GRID_API virtual void OnGridSysColorChange();

	// Checkbox
	GRID_API virtual UINT GetState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
	GRID_API virtual void DrawCheckBox(CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString);
	GRID_API virtual CRect ComputeCheckBoxRect(CDC* pDC, CRect rect, LPCTSTR lpszString, DWORD dtAlign);
	GRID_API virtual COLORREF GetColorValue(COLORREF rgb, BOOL bPrint);

	GRID_API virtual void DrawXPCheckBox(HTHEME lhTheme, CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString);

	GRID_API virtual BOOL LoadBitmap();  // 0 will load default bitmap
		// If you want to use CGXCheckbox with your own bitmap, you should
		// call LoadBitmap after constructing the CGXCheckBox object

	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual void OnGridCancelMode();

	// allows changing the colors that are used in the CB Bitmap
	GRID_API static void SetCheckBackColor(COLORREF rgb);
	GRID_API static void SetCheckFrameColor(COLORREF rgb);
	GRID_API static void ResetCheckColorScheme();

protected:
	BOOL	m_bDraw3d;
	HANDLE	m_hbitmapCheck;
	HANDLE	m_hbitmapPrint;
	UINT	m_nBitmapResourceId;
	UINT	m_nPrintResourceId;
	CSize	m_sizeCheck;
	int		m_nCheckBoxSize;
	// internal state - only valid for current cell
	BOOL	m_bScope;
	CRect	m_rectBox;
	// for changing the checkbox colors
	GRID_API static BOOL		m_gbCheckClrInc;
	GRID_API static COLORREF m_grgbFrame;
	GRID_API static COLORREF m_grgbBack;
};


/////////////////////////////////////////////////////////////////////////////
// CGXCheckBoxEx control
//
// Has an active state unlike the regular check box. Will Call OnModify etc...
//
class CGXCheckBoxEx: public CGXCheckBox
{
	GRID_DECLARE_CONTROL(CGXCheckBoxEx)

public:
	// Constructor & Destructor
	GRID_API CGXCheckBoxEx(CGXGridCore* pGrid, BOOL bDraw3d = TRUE, UINT nBitmapResourceId = 0, UINT nPrintResourceId = 0);

	// Status
	GRID_API virtual BOOL GetModify();
	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL IsActive();
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL Store();

	// Operations...
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Drawing, optimal size
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	// Mouse hit
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// User clicked checkbox
	GRID_API virtual void OnClickedButton(CGXChild* pChild);

protected:
	BOOL m_bActive;
	BOOL m_bModified;

};


/////////////////////////////////////////////////////////////////////////////
// CGXRadioButton control

class CGXRadioButton: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXRadioButton)

public:
	GRID_API CGXRadioButton(CGXGridCore* pGrid, BOOL bDraw3d = FALSE);

	// Drawing, size
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// Attributes:
protected:
	int m_nRadioBtns;   // No. of alternatives
	BOOL m_bDraw3d;
};

/////////////////////////////////////////////////////////////////////

// Has an active state and gives you an option to align radio button horizontally
class CGXRadioButtonEx: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXRadioButtonEx)

public:
	GRID_API CGXRadioButtonEx(CGXGridCore* pGrid, BOOL bDraw3d = FALSE);
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Status
	GRID_API virtual BOOL GetModify();
	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL IsActive();
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL Store();
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Drawing, size
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	GRID_API virtual BOOL IsWindowlessControl();

	// Attributes:
protected:
	BOOL	m_bActive;
	BOOL	m_bModified;
	int		m_nRadioBtns;   // No. of alternatives
	BOOL	m_bDraw3d;
};

/////////////////////////////////////////////////////////////////////////////
// CGXStatic control

class CGXStatic : public CGXControl
{
	GRID_DECLARE_CONTROL(CGXStatic)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXStatic(CGXGridCore* pGrid);

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
		// compute the interior rectangle for the text
		// without buttons and borders
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	// cells tips enable
	GRID_API void ImplementCellTips();
};

/////////////////////////////////////////////////////////////////////////////
// CGXHeader control

class CGXHeader: public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXHeader)

public:
	GRID_API CGXHeader(CGXGridCore* pGrid);

	GRID_API virtual void OnGridSysColorChange();

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual void InvertBorders(CDC* pDC, const CRect& r);
	GRID_API virtual BOOL GetMarkHeaderState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);

	// QA: 32311
	inline virtual BOOL UsesCustomSelectionColor() { return m_bUsesCustomSelectionColor; }
	inline virtual void SetUsesCustomSelectionColor(BOOL bEnable) { m_bUsesCustomSelectionColor = bEnable; }
	inline virtual COLORREF GetCustomSelectionColor() { return m_clrCustomSelectionColor; }
	inline virtual void SetCustomSelecitonColor(COLORREF clr) { m_clrCustomSelectionColor = clr; }

	COLORREF m_clrCustomSelectionColor;
	BOOL m_bUsesCustomSelectionColor; 
};

// for compatibility with 1.0, 1.1
#define m_bAlwaysLeftJustified m_bAllwaysLeftJustified

/////////////////////////////////////////////////////////////////////////////
// CGXEditControl control

class CGXEditControl : public CEdit, public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXEditControl)
	GRID_DECLARE_DYNAMIC(CGXEditControl)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXEditControl(CGXGridCore* pGrid, UINT nID = 0);
	GRID_API virtual ~CGXEditControl();
	GRID_API virtual CWnd* GetWndPtr() const;

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
		// Hides the CEdit without changing the m_bIsActive flag

	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
	GRID_API virtual BOOL OnEndEditing();
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual void SetCurrentText(const CString& str);
	GRID_API BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);

	GRID_API virtual BOOL StripSeparatorFromValue(CString& sValue, const CGXStyle* pStyle, double& d);
		// called from Store & ConvertControlTextToValue (handles Paste)
		// to strip group separator from the value before it is stored

	GRID_API virtual BOOL PutDecInValue(CString& sValue, const CGXStyle* pStyle);
		//called from Init to put correct dec sep in windowtext

	GRID_API virtual BOOL AcceptCommasInNumbers(const CGXStyle* pStyle);
		//returns whether strings with thousands separator should be treated
		//as a number. Default behavior is to check for a number format
		//(eg. GX_FMT_FIXED)

	// Mouse hit
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	// Called when the user presses a key on the inactive current cell
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);

	// Called from OnChar (lets you change the nChar)
	GRID_API virtual BOOL OnProcessChar(UINT nChar, UINT nRepCnt, UINT flags);

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

	// for paste validation
	GRID_API virtual BOOL ValidatePaste(const CString& sPaste);

	// Edit control only
	GRID_API int  CalcTextPosUnderPt(CPoint point);
	GRID_API void SetWrapText(BOOL b);
	GRID_API void SetRTLReading(BOOL b);
	GRID_API void SetAllowEnter(BOOL b);
	GRID_API void SetVertScrollBar(BOOL b);
	GRID_API void SetCellColor(COLORREF rgb);
	GRID_API void SetTextAlign(UINT ntAlign);
	GRID_API void GetSel(int& nStartChar, int& nEndChar) const;
	GRID_API DWORD GetSel() const;

// Implementation
protected:
	GRID_API virtual BOOL CreateControl(DWORD dwStyle = 0, LPRECT lpRect = NULL);
	GRID_API virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	GRID_API BOOL  UpdateEditStyle();
	GRID_API int   GetLastVisibleLine(LPRECT lprect = NULL);

// Attributes
public:
	BOOL            m_bAutoSize;
	BOOL            m_bVertScrollBar;
	BOOL            m_bAlwaysLeftJustified;

protected:
	UINT            m_nID;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	CFont           m_font;

	COLORREF        m_rgbWndHilightText;

	DWORD   m_dwEditStyle;
	LONG    m_ntAlign;
	BOOL    m_bUpdateEditStyle;
	int     m_dyHeight;
	int     m_dxMaxCharWidth;
	COLORREF
			m_rgbCell;
	BOOL    m_bAllowEnter;
	BOOL    m_bWrapText;
	BOOL	m_bRTL;
	BOOL    m_bSizeChanged;
	CString m_sLastChar;
	BOOL    m_bDoNotEmptyLastChar;
	int     m_nLimitText;
	BOOL    m_bFloatDone;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXEditControl)
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnStyleChanged( int nStyleType, LPSTYLESTRUCT lpStyleStruct );
	//}}AFX_MSG
#if _MFC_VER >= 0x0400
	GRID_API afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	GRID_API afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnImeEndComposition(WPARAM wParam, LPARAM lParam);
#endif
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXVScrollEdit control

class CGXVScrollEdit: public CGXEditControl
{
	GRID_DECLARE_CONTROL(CGXVScrollEdit)
	GRID_DECLARE_DYNAMIC(CGXVScrollEdit)

public:
	// Constructor & Destructor
	GRID_API CGXVScrollEdit(CGXGridCore* pGrid, UINT nID = 0);
	GRID_API virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXVScrollEdit)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXHotSpotEdit control

class CGXHotSpotEdit: public CGXEditControl
{
	GRID_DECLARE_CONTROL(CGXHotSpotEdit)
	GRID_DECLARE_DYNAMIC(CGXHotSpotEdit)

public:
	// Constructor & Destructor
	GRID_API CGXHotSpotEdit(CGXGridCore* pGrid, UINT nID = 0);
	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

protected:
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes:
	CGXChild* m_pHotSpot;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXHotSpotEdit)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXSpinEdit control

class CGXSpinEdit: public CGXEditControl
{
	GRID_DECLARE_CONTROL(CGXSpinEdit)
	GRID_DECLARE_DYNAMIC(CGXSpinEdit)

public:
	// Constructor & Destructor
	GRID_API CGXSpinEdit(CGXGridCore* pGrid, UINT nID = 0);
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);

	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

protected:
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
	GRID_API virtual void OnClickedButton(CGXChild* pChild);

	// Attributes:
	CGXChild*	m_pUpArrow;
	CGXChild*	m_pDownArrow;
	BOOL		m_bWrap;
	LONG		m_nMinBound, m_nMaxBound;
	BOOL		m_bMinBound, m_bMaxBound;
	BOOL		m_bStartValue;
	LONG		m_nStartValue;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXSpinEdit)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBox control

// when the user presses the dropdown button,
// a CGXGridCombo window is displayed with WS_POPUP style
// and a CGXComboListBox window is embedded into the CGXGridCombo window.
//
// CGXComboListBox sends messages WM_GX_LBOXEND, WM_GX_LBOXCANCEL
// and WM_GX_LBOXCHANGED to the CGXComboBox control.
//
// When CGXComboBox receives a WM_GX_LBOXEND message, the current
// selection is stored and the listbox is destroyed.
//
// When CGXComboBox receives a WM_GX_LBOXCHANGE, the edit text is
// updated.
//
// When CGXComboBox receives a WM_GX_LBOXCANCEL, the listbox will
// be destroyed.
//

// flags
const UINT GXCOMBO_TEXTFIT   = 0x0001;
	// combobox adapts input text to an item in the dropdown list
const UINT GXCOMBO_NOTEXTFIT = 0x0002;
	// user can input any text
const UINT GXCOMBO_ZEROBASED = 0x0004;
	// cell value is a zero-based index
const UINT GXCOMBO_ONEBASED  = 0x0008;
	// cell value is a one-based index
const UINT GXCOMBO_DISPLAYCHOICE  = 0x0010;
	// must be combined either with GXCOMBO_ONEBASED or GXCOMBO_ZEROBASED
	// cell value is a index but the choice is displayed in the cell

 // CGXComboListBox will be embedded into the CGXGridCombo window.

class CGXComboListBox : public CListBox
{
	GRID_DECLARE_DYNAMIC(CGXComboListBox)

// Construction
public:
	GRID_API CGXComboListBox(CWnd* pMsgWnd);
	GRID_API virtual ~CGXComboListBox();

    // [VC7] CListBox Create Function returns BOOL.
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0);

// Operations
public:
	GRID_API void SetBackColor(COLORREF rgb);

// Implementation
protected:
	// Attributes
	BOOL    m_bKeyDown;
	BOOL    m_bLButtonDown;
	CWnd*   m_pMsgWnd;
	BOOL    m_bColor;
	COLORREF m_rgbBack;
	int     m_nOldSel;
	BOOL    m_bAlNum;
	int		m_nRepCnt;

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXComboListBox)
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

// CGXComboBox is the control which encapsulates
// the combobox behaviour.

class CGXComboBox: public CGXEditControl
{
	GRID_DECLARE_CONTROL(CGXComboBox)
	GRID_DECLARE_DYNAMIC(CGXComboBox)

public:
	// Constructor & Destructor
	GRID_API CGXComboBox(CGXGridCore* pGrid, UINT nEditID, UINT nListBoxID, UINT nFlags);
	GRID_API virtual ~CGXComboBox();

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Keyboard
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT flags);

	// WM_MOUSEACTIVATE message
	GRID_API virtual BOOL MouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);

	// override this method for ownerdrawn list-boxes.
	GRID_API virtual CGXGridCombo* CreateDropDown(CWnd* pWnd, const CRect& rect);
	GRID_API virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID = 0);
	GRID_API virtual void ShowDropDown(BOOL bShow);
	GRID_API virtual BOOL GetDroppedState();
	GRID_API virtual BOOL ValidateString(const CString& sEdit);
	GRID_API virtual void ReplaceSel(LPCTSTR pszReplaceText);

	GRID_API virtual CGXGridCombo* GetGridComboBox() { return m_pDropDownWnd; }

	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual BOOL GetValue(CString& strResult);

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Status
	GRID_API virtual BOOL Store();
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual void Reset();
	GRID_API virtual void OnNotifyMsg(MSG* pMsg);

protected:
	// Childs
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
	GRID_API virtual void OnClickedButton(CGXChild* pChild);

	// Override these methods if you don't want to fill the list from the coice-list
	GRID_API virtual void OnStoreDroppedList(CListBox* lbox);
	GRID_API virtual void OnFillDroppedList(CListBox* lbox);

	// Override this method for changing the defaulting listbox size
	GRID_API virtual CRect OnGetListboxRect(const CRect& rcCellRect);

	// Override this method if you don't want that
	// the listbox will be destroyed
	GRID_API virtual void DestroyDropDownWnd(CWnd* pDropDownWnd);

	// Attributes:
public:
	BOOL            m_bFillWithChoiceList;
	BOOL            m_bInactiveDrawAllCell; // draw text over pushbutton when inactive
	BOOL            m_bInactiveDrawButton;  // draw pushbutton when inactive
	UINT            m_nFlags;
	DWORD           m_dwListBoxStyle;       // default style for dropdown-list
	BOOL            m_bDropdownOnly;        // set this TRUE if text shall not be editable
	BOOL            m_bSizeToContent;       // set FALSE if button shall have the same height as cell


protected:
	CGXChild*       m_pButton;
	UINT            m_nListBoxID;
	CGXGridCombo*   m_pDropDownWnd;
	CFont           m_fontCombo;

	// Implementation
	int             m_nDefaultHeight;
	int             m_nExtraFrame;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboBox)
	GRID_API afx_msg LRESULT OnListBoxEnd(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxCancel(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxChanged(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxKillFocus(WPARAM, LPARAM);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXListBox control

class CGXListBox: public CListBox, public CGXControl
{
	GRID_DECLARE_CONTROL(CGXListBox)
	GRID_DECLARE_DYNAMIC(CGXListBox)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXListBox(CGXGridCore* pGrid, UINT nID = 0);
	GRID_API virtual ~CGXListBox();
	GRID_API virtual CWnd* GetWndPtr() const;

	// Status
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();

	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();

	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual void SetCurrentText(const CString& str);

	// Operations
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual BOOL Store();

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual void Hide();

	// Mouse hit
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// Notifications
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Listbox control only
	GRID_API virtual void FillListBox();

// Implementation
protected:
	GRID_API virtual BOOL CreateControl();
	GRID_API void SetCellColor(COLORREF rgb);

// Attributes
private:
	UINT            m_nID;
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bIsModify;
	CFont           m_font;
	COLORREF        m_rgbWndHilightText;
	int				m_dyHeight;
	COLORREF		m_rgbCell;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXListBox)
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboEditPart window

// this class defines the subclassed edit portion of the CGXComboBoxWnd

class CGXComboEditPart : public CEdit
{
// Construction
public:
	GRID_API CGXComboEditPart();

// Implementation
public:
	GRID_API virtual ~CGXComboEditPart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboEditPart)
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBoxWndButton child control

class CGXComboBoxWndButton: public CGXButton
{
public:
	// construction, destrcution
	GRID_API CGXComboBoxWndButton(CGXControl* pComposite);

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive);
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBoxWnd control

class CGXComboBoxWnd : public CComboBox, public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXComboBoxWnd)
	GRID_DECLARE_DYNAMIC(CGXComboBoxWnd)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXComboBoxWnd(CGXGridCore* pGrid);
	GRID_API virtual ~CGXComboBoxWnd();
	GRID_API virtual CWnd* GetWndPtr() const;

	GRID_API BOOL Create(DWORD dwStyle, UINT nID = 0);

	// Status
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();

	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();

	// Operations
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	GRID_API virtual BOOL Store();
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual void Hide();
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);
	GRID_API virtual void OnClickedButton(CGXChild* pChild);
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual void SetCurrentText(const CString& str);
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API void GetEditSel(int& nStart, int& nEnd);
	GRID_API BOOL SetEditSel(int nStart, int nEnd);

	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual BOOL ValidateString(const CString& sEdit);
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Override this method for changing the defaulting listbox size
	GRID_API virtual CRect OnGetListboxRect(const CRect& rcCellRect);

	// Find and Replace
	GRID_API virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	GRID_API virtual void ReplaceSel(LPCTSTR pszReplaceText);
	GRID_API virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual BOOL GetSelectedText(CString& strResult);

	// color
	GRID_API void SetCellColor(COLORREF rgb);

	GRID_API void GetWindowText(CString& rString) const;
	GRID_API int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const;

	//overridden to handle ignoring deletes for nonactive dropdownlists
	GRID_API virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);



// Implementation
protected:
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	GRID_API virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual void OnSetfocus();

	// Childs
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	GRID_API void SetActiveAndDropDown();

// Attributes
public:
	int             m_nExtraFrame;  // extra frame for combobox in cell
	BOOL            m_bFillWithChoiceList;
	BOOL            m_bWantArrowKeys;
	BOOL            m_bSizeToContent;
	int             m_nIndexValue;
	BOOL            m_bDispChoice;
	BOOL            m_bDropDownOnClick;
	BOOL            m_bInactiveDrawButton;
	BOOL            m_bInactiveDrawAllCell;
	BOOL            m_bForceInsideCell;
	BOOL			m_bFindTextSupported;
	CGXComboEditPart m_wndEdit;
	CGXChild*       m_pButton;

protected:
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bModified;
	CFont           m_font;
	COLORREF        m_rgbWndHilightText;
	COLORREF        m_rgbCell;
	int             m_nStartChar,
					m_nEndChar;
	BOOL            m_bDropDownOnNextSetFocus;
	int             m_nDefaultHeight;
	BOOL            m_bDraw3dFrame;
	CString			m_sOldText;
	int             m_nOldSel;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboBoxWnd)
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

	friend class CGXComboEditPart;
};

/////////////////////////////////////////////////////////////////////////////
// CGXWndWrapper control

class CGXWndWrapper: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXWndWrapper)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXWndWrapper(CGXGridCore* pGrid, CWnd* pWnd, BOOL bNeedDestroy = FALSE, BOOL bCanActivate = FALSE, BOOL bInvertBorders = TRUE);
		// bCanActivate should be FALSE for Bitmaps, TRUE for controls
		// Please note that if you want to use CWnds in your grid,
		// you should consider subclassing with multiple inheritance from
		// CGXControl and CWnd (see CGXListBox or CGXEditControl for example).
		// By subclassing you have a compatible interface to the grid,
		// but also access to the message-map inherited from CWnd.
	GRID_API virtual ~CGXWndWrapper();

	GRID_API virtual CWnd* GetWndPtr() const;

	// Status
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();

	// Operations
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Stores the cell coordinates, resets the style and sets the window text

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// Invalidates and updates the decorated windows
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     set focus
		// else {
		//     set window inactive
		// }


	GRID_API virtual void InvertBorders(CDC* pDC, const CRect& r);
	GRID_API virtual void Hide();
	GRID_API virtual BOOL OnEndEditing();


	// Mouse hit
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

protected:
	// default constructor for derived classes only
	GRID_API CGXWndWrapper(CGXGridCore* pGrid);

// Attributes
protected:
	CWnd*           m_pWnd;
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	CFont           m_font;
	BOOL            m_bCanActivate; // FALSE for Bitmaps, TRUE for controls
	BOOL            m_bNeedDestroy; // TRUE when m_pWnd must be deleted
	BOOL            m_bInvertBorders;
};

/////////////////////////////////////////////////////////////////////////////
// CGXMaskControl control

// CGXMaskData

class CGXMaskData: public CObject
{
	GRID_DECLARE_DYNCREATE(CGXMaskData);

public:
	// construction, destruction
	GRID_API CGXMaskData();
	GRID_API virtual ~CGXMaskData();

	GRID_API virtual void Empty();

	// Prepare mask
	GRID_API virtual void SetMask(LPCTSTR strMask);

	// Data
	GRID_API virtual void GetData(CString& strData, int nFirstChar = 0, int nLastChar = -1, BOOL bTrim = TRUE) const;    // filters out mask chars from m_astrDisplay and
				// replaces m_chPrompt chars with blanks
				// Return Value: TRUE if valid, FALSE if invalid chars

	GRID_API virtual int SetData(LPCTSTR strData, int nStartPos = -1, BOOL bInsert = FALSE);
				// Adds mask chars to m_astrDisplay and
				// replaces blanks with m_chPrompt chars
				// Return Value: TRUE if valid, FALSE if invalid chars

	GRID_API virtual void GetDisplayString(CString& strDisplay, int nFirstChar = 0, int nLastChar = -1) const;
				// Build strDisplay from m_astrDisplay

	GRID_API virtual int SetDisplayString(LPCTSTR strDisplay, int nStartPos = -1, BOOL bInsert = FALSE);
				// Initializes m_astrDisplay

	GRID_API BOOL SetPromptChar(const CString& sPrompt, BOOL bUpdateDisplayString = TRUE);

	GRID_API const CString& GetPromptChar() const;

	GRID_API virtual BOOL IsCharValid(int nPos, CString& sChar) const;

	GRID_API virtual int GetNextDataPos(int nOldPos) const;
	GRID_API virtual int GetPrevDataPos(int nOldPos) const;
	GRID_API virtual int FindLastFilledDataPos(int nStartPos) const;

	GRID_API virtual int PushChar(int nStartPos, const CString& sChar, int& nNextPos);
		// adds a character and returns the next data posiition
	GRID_API virtual void PullChar(int nFromPos, int nToPos);

	// Validation
	GRID_API virtual BOOL IsValidDisplayString() const;
				// Checks if m_astrDisplay is valid

	GRID_API virtual BOOL IsEmptyMask() const;
				// Checks if there is a mask

	GRID_API virtual int GetTextLength() const;

	GRID_API virtual int GetEditPos(int nCharPos) const;
	GRID_API virtual int GetCharPos(int nEditPos) const;

	GRID_API virtual void ClearData();

	GRID_API virtual void SetMaxLength(int nLength);
	GRID_API virtual int SetMaxLength() const;

	// Overridables
	GRID_API virtual BOOL IsMaskChar(TCHAR ch) const;

	// Helper functions
	GRID_API virtual BOOL IsLiteral(int nPos) const;

protected:
	// Data members (arrays make it easier to handle multi byte chars)
	CStringArray	m_astrMask;       // Holds the mask chars
	CByteArray64	m_abIsLiteral;    // Holds information which characters are literal
	CStringArray	m_astrDisplay;    // Holds the display string
	CString			m_sPrompt;             // The prompt character, space is default.
	BOOL			m_bIgnoreEmptyMask;       // Ignore Mask when it is empty
	int				m_nMaxLength;              // Use this as maximum length when mask is empty
#ifdef _MBCS
	GRID_API static BOOL		m_bDBCSEnabled;
#endif
};


// CGXMaskControl

class CGXMaskControl : public CEdit, public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXMaskControl)
	GRID_DECLARE_DYNAMIC(CGXMaskControl)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXMaskControl(CGXGridCore* pGrid, UINT nID = 0, CRuntimeClass* pDataClass = RUNTIME_CLASS(CGXMaskData));
	GRID_API virtual ~CGXMaskControl();
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	GRID_API void AttachData(CRuntimeClass* pDataClass = RUNTIME_CLASS(CGXMaskData));
	GRID_API virtual BOOL CreateControl(DWORD dwStyle = 0, LPRECT lpRect = NULL);
	GRID_API virtual CWnd* GetWndPtr() const;

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

	GRID_API virtual BOOL OnValidate();

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		// }

	GRID_API virtual void Hide();
		// Hides the CEdit without changing the m_bIsActive flag

	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual void SetCurrentText(const CString& str);
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual void InitMask(CGXMaskData* pMask, const CGXStyle& style);

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

	// Edit control only
	GRID_API int  CalcTextPosUnderPt(CPoint point);
	GRID_API void SetCellColor(COLORREF rgb);
	GRID_API void SetTextAlign(UINT ntAlign);
	GRID_API void GetSel(int& nStartChar, int& nEndChar) const;
	GRID_API DWORD GetSel() const;
	GRID_API void GetCharSel(int& nPosition, int& nEndPos) const;
	GRID_API void SetCharSel(int nPosition, int nEndPos, BOOL bNoScroll = FALSE);
	GRID_API void SendEvent(UINT nEvent);

	// Clipboard
	GRID_API virtual BOOL Copy();
	GRID_API virtual BOOL Paste();
	GRID_API virtual BOOL Cut();
	GRID_API virtual BOOL CanCopy();
	GRID_API virtual BOOL CanCut();
	GRID_API virtual BOOL CanPaste();

// Implementation
protected:
	GRID_API virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	GRID_API void UpdateDisplay(LPCTSTR lpszText = NULL);
	GRID_API BOOL  UpdateEditStyle();
	GRID_API int   GetLastVisibleLine(LPRECT lprect = NULL);

// Attributes
public:
	BOOL            m_bDisplayEmpty;    // Set this TRUE if mask should also be displayed for empty values
	BOOL            m_bAlwaysLeftJustified;
	CGXMaskData*    m_pMask;
	CGXMaskData*    m_pExtMask;

protected:
	UINT            m_nID;
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bInsertMode;
	CFont           m_font;
	COLORREF        m_rgbWndHilightText;
	DWORD			m_dwEditStyle;
	LONG			m_ntAlign;
	BOOL			m_bUpdateEditStyle;
	int				m_dyHeight;
	int				m_dxMaxCharWidth;
	COLORREF		m_rgbCell;
	BOOL			m_bForceReplaceData;
	// Generated message map functions
protected:
	//{{AFX_MSG(CGXMaskControl)
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
#if _MFC_VER >= 0x0300
	GRID_API afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
#endif
	GRID_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Password control

class CGXPasswordControl: public CGXEditControl
{
	GRID_DECLARE_CONTROL(CGXPasswordControl)
	GRID_DECLARE_DYNAMIC(CGXPasswordControl)

public:
	// Constructor & Destructor
	GRID_API CGXPasswordControl(CGXGridCore* pGrid, UINT nID = 0);

	// Overrides
	GRID_API virtual BOOL GetControlText(CString& sResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Disable Copy and Cut operations, so that user
	// cannot paste text into another application to
	// check out the cells contents
	GRID_API virtual BOOL Copy();
	GRID_API virtual BOOL Cut();

	// Attributes
	BOOL	m_bReplaceAsterisk;
	TCHAR	m_chPasswordChar;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXPasswordControl)
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXProgressCtrl control

class CGXProgressCtrl: public CGXControl
{
	GRID_DECLARE_CONTROL(CGXProgressCtrl)

public:
	// Construction/Destruction
	GRID_API CGXProgressCtrl(CGXGridCore* pGrid);
	GRID_API virtual ~CGXProgressCtrl();

public:
	// Initialization
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

	// optimized method for changing the value
	GRID_API static BOOL AFXAPI SetProgressValue(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, LONG newPos);

	// CGXControl overridables
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	// Overridables
protected:
	GRID_API virtual void OnGetCaption(CString& strCaption, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
	GRID_API virtual COLORREF OnGetCaptionColor(BOOL bForeOrBack, const CGXStyle& style);
	GRID_API virtual COLORREF OnGetCaptionTextColor(BOOL bForeOrBack, const CGXStyle& style);

	// Implementation
	GRID_API CRect GetUpdateRect(LONG newValue, CRect boundRect, const CGXStyle& style);
	GRID_API void UpdateUnitFactor(CRect boundRect, LONG normVal);

	// Attributes
protected:
	double m_unitFactor;
};

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBox control

class CGXTabbedComboLBox;
class CGXTabbedComboBox;
class CGXTabbedLBoxHeader;

class CGXTabbedComboBox : public CGXComboBox
{
	GRID_DECLARE_CONTROL(CGXTabbedComboBox)
	GRID_DECLARE_DYNAMIC(CGXTabbedComboBox)

// Construction
public:
	GRID_API CGXTabbedComboBox(CGXGridCore* pGrid, UINT nEditID = 0, UINT nListBoxID = 0);
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

// Attributes
public:
	int			m_nValueCol;		// Value to be stored in style
	int			m_nDisplayCol;      // Text to be displayed in cell
	BOOL		m_bDispAllCols;		// display table-like dropdown list
	BOOL		m_bDisplayTitleRow;	// Use first line in choice list
									// to display titles for each column
	int			m_nSortCol;			// Sort the choicelist
	CString		m_strColWidths;		// Column Widths
	COLORREF	m_rgbGridLine;
	COLORREF	m_rgbBackColor;
	COLORREF	m_rgbTextColor;
	BOOL		m_bCheckAndFillCBEdit; // MS Access like replacing of edit text
	int			m_nDefaultHeight;
	int			m_nCurFillChoicelistId;
	LONG		m_nSerial;
    int			m_nLeftMargin;
public:
	// Constructor & Destructor
	GRID_API virtual ~CGXTabbedComboBox();

// Operations
public:
	GRID_API void SetTabStops(int iTabStops);
	GRID_API void AddTabStop(int iIndex, int iTabStop);
	GRID_API virtual void CheckAndFillCBEdit();
	GRID_API CMapStringToString* GetValueToChoiceMap(const CGXStyle& style);
	GRID_API CMapStringToString* GetTextToChoiceMap(const CGXStyle& style);
	GRID_API static void AFXAPI ResetChoiceMap(CGXGridParam* pParam, int nChoiceListId = -1);

// Overrides
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);

	GRID_API virtual BOOL OnValidate();
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	GRID_API virtual CGXGridCombo* CreateDropDown(CWnd* pWnd, const CRect& rect);
	GRID_API virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID);
	GRID_API virtual CRect OnGetListboxRect(const CRect& rcCellRect);
	GRID_API virtual void OnStoreDroppedList(CListBox* lbox);
	GRID_API virtual void OnFillDroppedList(CListBox* lbox);
	GRID_API virtual void DestroyDropDownWnd(CWnd* pDropDownWnd);
	GRID_API virtual void ShowDropDown(BOOL bShow);
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual BOOL ValidateString(const CString& sEdit);

protected:
	// interior state for current cell only
	CRect m_rectComboLBox;
	int m_nWidthLBox;
	int m_nColCount;
	int m_iTabCount;
	LPINT m_piarTabStops;
	CGXTabbedLBoxHeader* m_pWndTitleRow;

	BOOL m_bListBoxFilled;
	CGXTabbedComboLBox* m_pComboLbox;
	CGXGridCombo*   m_pComboLboxPopup;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboBox)
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()

	friend class CGXTabbedComboLBox;
};

class CGXTabbedComboLBox : public CGXComboListBox
{
// Construction
public:
	GRID_API CGXTabbedComboLBox(CGXTabbedComboBox* pTabbedComboBox);

// Attributes
	CGXTabbedComboBox* m_pTabbedComboBox;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDropDownList)
	GRID_API virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	GRID_API virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboLBox)
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()

	friend class CGXTabbedComboBox;
};

class CGXTabbedComboBoxWnd;
class CGXTabbedLBoxHeader;

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBoxWnd window

class CGXTabbedComboBoxWnd : public CGXComboBoxWnd
{
	GRID_DECLARE_CONTROL(CGXTabbedComboBoxWnd);
	GRID_DECLARE_DYNAMIC(CGXTabbedComboBoxWnd);

// Construction
public:
	GRID_API CGXTabbedComboBoxWnd(CGXGridCore* pGrid);
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

// Attributes
public:
	// for all cells
	int			m_nValueCol;        // Value to be stored in style
	int			m_nDisplayCol;      // Text to be displayed in cell
	BOOL		m_bDispAllCols;		// display table-like dropdown list
	BOOL		m_bDisplayTitleRow; // Use first line in choice list
									// to display titles for each column
	int			m_nSortCol;			// Sort the choicelist
	CString		m_strColWidths;		// Column Widths
	COLORREF	m_rgbGridLine;
	COLORREF	m_rgbBackColor;
	COLORREF	m_rgbTextColor;
    int			m_nLeftMargin; 
	GRID_API void SetReadOnly(BOOL bReadOnly = TRUE);

// Operations
public:
	GRID_API void SetTabStops(int iTabStops);
	GRID_API void AddTabStop(int iIndex, int iTabStop);
	GRID_API void LoadLBoxEntries();

// Overrides
	GRID_API virtual HBRUSH OnGridCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API virtual BOOL CreateControl(DWORD dwStyle = CBS_DROPDOWN, UINT nID = 0);
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
	GRID_API virtual BOOL GetValue(CString& strResult);
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	GRID_API virtual BOOL OnValidate();
	GRID_API virtual void GetCurrentText(CString& strResult);
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual void Hide();
	GRID_API virtual void SetModify(BOOL bModified = TRUE);
	GRID_API virtual BOOL GetModify();
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual void OnClickedButton(CGXChild* pChild);
	GRID_API void SetActiveAndDropDown();
	GRID_API virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	GRID_API virtual BOOL ValidateString(const CString& sEdit);
	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTabbedComboBoxWnd)
public:
	GRID_API virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	GRID_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	GRID_API virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXTabbedComboBoxWnd();

	// this class defines the subclassed edit portion of the CGXComboBoxWnd
protected:
	// interior state for current cell only
	CRect	m_rectComboLBox;
	int		m_nWidthLBox;
	CEdit*	m_pWndCBEditPart;
	int		m_nColCount;
	int		m_iTabCount;
	LPINT	m_piarTabStops;
	CGXTabbedLBoxHeader* m_pWndTitleRow;
	BOOL	m_bReadOnly;
	BOOL	m_bIgnoreNextDraw;
	BOOL	m_bLockMeasure;
	CString m_sAddString;

public:
	HWND m_hComboLBox;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboBoxWnd)
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

	friend class CGXTabbedCBEditWnd;
};

// edit box

class CGXTabbedCBEditWnd : public CEdit
{
// Construction
public:
	GRID_API CGXTabbedCBEditWnd();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTabbedCBEditWnd)
protected:
	GRID_API virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXTabbedCBEditWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedCBEditWnd)
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXCheckListComboBox

#if _MFC_VER >= 0x0400

class CGXCheckListComboLBox : public CCheckListBox
{
	GRID_DECLARE_DYNAMIC(CGXCheckListComboLBox)

// Construction
public:
	GRID_API CGXCheckListComboLBox(CWnd* pMsgWnd);
	GRID_API virtual ~CGXCheckListComboLBox();

    // [VC7] Create Function returns BOOL type.
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Operations
public:
	GRID_API void SetBackColor(COLORREF rgb);

// Implementation
protected:
	// Attributes
	BOOL    m_bKeyDown;
	BOOL    m_bLButtonDown;
	CWnd*   m_pMsgWnd;
	BOOL    m_bColor;
	COLORREF m_rgbBack;
	int     m_nOldSel;
	BOOL    m_bAlNum;

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXCheckListComboLBox)
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

// CGXComboBox is the control which encapsulates
// the combobox behaviour.

class CGXCheckListComboBox: public CGXComboBox
{
	GRID_DECLARE_CONTROL(CGXCheckListComboBox)
	GRID_DECLARE_DYNAMIC(CGXCheckListComboBox)

public:
	// Constructor & Destructor
	GRID_API CGXCheckListComboBox(CGXGridCore* pGrid, UINT nEditID = 0, UINT nListBoxID = 0);
	GRID_API virtual ~CGXCheckListComboBox();
	GRID_API virtual BOOL OnProcessChar(UINT nChar, UINT nRepCnt, UINT flags);

	GRID_API virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID);
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
//  virtual BOOL GetValue(CString& strResult);

	// Override these methods if you don't want to fill the list from the coice-list
	GRID_API virtual void OnStoreDroppedList(CListBox* lbox);
	GRID_API virtual void OnFillDroppedList(CListBox* lbox);

	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	GRID_API virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRID_API virtual void SetActive(BOOL bActive);
	int m_nCount;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCheckListComboBox)
	GRID_API afx_msg LRESULT OnListBoxEnd(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxCancel(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxChanged(WPARAM, LPARAM);
	GRID_API afx_msg LRESULT OnListBoxKillFocus(WPARAM, LPARAM);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};


#endif  // _MFC_VER >= 0x0400

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxctrli.inl"
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

#endif // _GXCTRLI_H
