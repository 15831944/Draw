///////////////////////////////////////////////////////////////////////////////
// GXCTRL.h
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

#ifndef _GXCTRL_H
#define _GXCTRL_H

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


#undef GX_DATA
#undef GX_DATADEF

//#if _MFC_VER < 0x0300
//#define GX_DATA
//#define GX_DATADEF
//#else
#define GX_DATA AFX_DATA
#define GX_DATADEF AFX_DATADEF
//#endif


// header file

class CGXGridCore;
class CGXStyle;
struct GX_FR_STATE;
class CGXChild;
class CGXControl;
class CGXGridCombo;
class CGXCellTipWnd;

enum GXModifyType;


// The following functions have been renamed from earlier version
// #define GetFormattedText    GetControlText
#define OnInitChilds        OnInitChildren

/////////////////////////////////////////////////////////////////////////////
// Runtime Type Information for the CGXControl class

struct CGXControlClass
{
// Attributes
	LPCSTR m_lpszClassName;
#ifdef _GXDLL
	CGXControlClass* (PASCAL* m_pfnGetBaseClass)();
#else
	CGXControlClass* m_pBaseClass;
#endif
};

// Helper macros

#define CONTROL_CLASS(class_name) (&class_name::ctrl##class_name)

//-----------------------------------------------------------------------//
// The definition for DECLARE_CONTROL() and IMPLEMENT_CONTROL() have     // 
// been moved to StingrayExportDefs.h.                                   //
// Refer to GRID_DECLARE_CONTROL() and GRID_IMPLEMENT_CONTROL().         //
//-----------------------------------------------------------------------//

/////////////////////////////////////////////////////////////////////////////
// Global methods

GRID_API BOOL AFXAPI GXGetDoubleByteChar(TCHAR nChar, CString& sChar, BOOL& bDoubleByteChar, TCHAR& nDoubleByteLeadChar);

////////////////////////////////////////////////////////////////////////////
// CellTips implementation
class CGXCellTipWnd;

struct CGXCellTipBase
{
	GRID_API CGXCellTipBase();
	
	GRID_API virtual ~CGXCellTipBase();
	
	virtual BOOL NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle) = 0;

	virtual DWORD GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle) = 0;

	virtual void InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip) = 0;
};



/////////////////////////////////////////////////////////////////////////////
// Control base classes

class CGXControl
{
public:
	// a control allows you to have several childs (e.g. button, spin-arrows, ...)
	// LButtonDown, MouseMove, LButtonUp and Keypressed are automatically
	// redirected to the focused child.
	//
	// You should initialize the rectangles of the child by
	// overriding OnInitChildren

	// Constructor & Destructor
	GRID_API CGXControl(CGXGridCore* pGrid);
	GRID_API virtual ~CGXControl();
	GRID_API static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Run-Time Type Information
	// Object model (types, destruction, allocation)
	GRID_API virtual CGXControlClass* GetControlClass() const;
	GRID_API BOOL IsKindOf(const CGXControlClass* pClass) const;
	GRID_API virtual CRuntimeClass* GetRuntimeClass() const;
	GRID_API BOOL IsKindOf(const CRuntimeClass* pClass) const;

	GRID_API operator CWnd*();
	GRID_API virtual CWnd* GetWndPtr() const;

	// Status (need to be overriden)
	GRID_API virtual void SetActive(BOOL bActive);
	GRID_API virtual BOOL IsActive();    // default: FALSE
	GRID_API virtual BOOL IsActiveAlways();	// default: FALSE

	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();   // default: FALSE

	// Operations
	GRID_API virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Retrieves the style and initializes the CWnd
		// Called, when current cell is moved to cell (nRow, nCol)

	GRID_API virtual void Reset();
		// Hides the window, sets inactive and sets m_nRow, m_nCol to zero
		// Called, when current cell is moved to another cell, or
		// if control needs to be reinitialized

	GRID_API BOOL IsInit() const;
	GRID_API BOOL IsInit(ROWCOL nRow, ROWCOL nCol) const;
		// TRUE, if control is used as current cell
		//       (CGXControl::Init has been called and intrinsic state is initialized);
		// FALSE, if control is not used as current cell

	GRID_API virtual BOOL Store();
		// Calls SetStyleRange() and resets the modify flag
		// Cell will be automatically redrawn

	GRID_API virtual BOOL OnValidate();
		// Validates the active cell, default: FALSE

	GRID_API virtual BOOL OnStartEditing();
		// called when the user starts editing (pressed key or mouse into text)

	GRID_API virtual void OnModifyCell();
		// called when the user started modifying the text

	GRID_API virtual BOOL OnCancelEditing();
		// called when the user pressed ESCAPE

	GRID_API virtual void OnCanceledEditing();
		// called when the user pressed ESCAPE and the control has been reset

	GRID_API virtual BOOL OnEndEditing();
		// called when the user accepted the contents

	GRID_API virtual BOOL OnLeftCell(ROWCOL nNewRow, ROWCOL nNewCol);
		// called from SetCurrentCell when the cell has been
		// marked invalid and Grid()->IsCurrentCell(nRow, nCol)
		// returns FALSE. Return TRUE if the cell needs to
		// be redrawn.

	GRID_API virtual BOOL OnDeleteCell();
		// called when the user pressed DELETE on an inactive current cell

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
		// Returns the rectangle, e.g. the rect for the text to be drawn without buttons
		// default: rect = Grid()->CalcRectFromRowColEx(nRow, nCol)
		//          Grid()->SubsctractBorders();

	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);
		// Will be called from CalcSize to add borders and grid lines to col width / row height

	GRID_API virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
		// Computes the size needed to fit the cell's content in a cell.

	GRID_API virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
		// Return TRUE if cell can float other cells or can be flooded by other floatable cells

	GRID_API virtual BOOL CanMergeCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType);
		// Return TRUE if cell can be merged with other cells

	GRID_API virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Inverts the borders for the current cell;
		// Override this methode if you don't want to have inverted borders,
		// or if you want to have thicker borders

	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		//     - check box with GXDrawCheckBox
		//     - list box: DrawText for each item
		// }

	// current cell specific->
	GRID_API virtual void GetCurrentText(CString& strResult);
		// override this method to return the text which
		// is displayed in the current cell

	GRID_API virtual void SetCurrentText(const CString& str);
		// override this method to set the text as it should
		// be displayed in the current cell

	GRID_API virtual BOOL GetValue(CString& strResult);
		// Reads out the window text and converts it into
		// the plain value which should be stored in the style object.

	GRID_API virtual void SetValue(LPCTSTR pszRawValue);
		// Convert the value which should be stored in the
		// style object to the text which should be displayed
		// in the cell and display it in the active
		// current cell (e.g. with SetWindowText()).

		// This function is protected so that you are
		// forced to call SetValueRange instead of SetValue
		// directly from outside the control.
	// ->end

public:
	GRID_API virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
		// get the text which is displayed in the cell.
		// RTF specific-> Convert RTF string to unformated text ->END
		// ME specific-> Insert literals ->END
		// Combobox specific-> Convert index to display string ->END

	GRID_API virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);
		// set the text as it should be displayed in the cell.
		// RTF specific-> Convert unformated text to RTF string ->END
		// ME specific-> Adjust text to given mask and remove literals->END
		// Combobox specific-> Convert display string to index ->END
		// The default implementation checks for readonly and
		// maximum text length.


	GRID_API virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
		// called from SetControlText to get the value before it is stored in
		// the cell.

	GRID_API virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
		// CGXControl::StoreStyle will call CGXGridCore::StoreStyleRowCol
		// and check if cell is read-only.
		//
		// In OG 1.1, CGXGridCore::StoreStyleRowCol was directly called. This has
		// changed in version 1.2, in order to make the behavior more cell-oriented
		// and allow specific controls to modify the style object before it is stored
		// in the datastructure. The new RTF control will use the passed style object
		// and change the value depending on the new formattings. If the style object
		// is for example "Bold" and StoreStyle is called for an active RTF
		// control, the RTF control will make the paragraph bold (by changing
		// the cell's value which contains rich text formattings).
		//
		// NOTE: The check whether a cell is read-only has been moved from
		// CGXGridCore::StoreStyleRowCol to CGXControl::StoreStyle
		//

	GRID_API virtual BOOL LoadStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
		// Determines the cell-specifc style information for the
		// specified cell. RTF handles font, textcolor and text
		// alignment in the RTF value. Therefore, LoadStyle will
		// extract this information from the RTF value and set
		// this attributes in the style object.

	GRID_API virtual BOOL GetChoiceListItem(CString& strResult, LPCTSTR pszChoiceList, int nIndex);
		// determines choice list entry for a given index

	GRID_API virtual int FindStringInChoiceList(CString& sMatch, LPCTSTR pszEdit, LPCTSTR pszChoiceList, BOOL bExact);
		// searches the choice list for a given string and returns the index

	GRID_API virtual void Hide();
		// Hides the CWnd without changing the m_bIsActive flag

	GRID_API virtual void Refresh();
		// Hides the CWnd and Redraws the cell

	// Mouse hit
	GRID_API virtual BOOL MouseMove(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus

	GRID_API virtual BOOL MouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Left Button
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// Middle Button
	GRID_API virtual BOOL MButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	GRID_API virtual BOOL MButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	GRID_API virtual BOOL MButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// Right Button
	GRID_API virtual BOOL RButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	GRID_API virtual BOOL RButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	GRID_API virtual BOOL RButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// WM_MOUSEACTIVATE message
	GRID_API virtual BOOL MouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);

	// PreTranslateMessage
	GRID_API virtual BOOL OnGridPreTranslateMessage(MSG* pMsg);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
		// default: Calls child with focus

	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// Clipboard
	GRID_API virtual BOOL Copy();
	GRID_API virtual BOOL Paste();
	GRID_API virtual BOOL Cut();
	GRID_API virtual BOOL CanCopy();
	GRID_API virtual BOOL CanCut();
	GRID_API virtual BOOL CanPaste();

	// Sort Key
	GRID_API virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// Find and Replace
	GRID_API virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
		// default: returns FALSE
		// override this method to support find

	GRID_API virtual void ReplaceSel(LPCTSTR pszReplaceText);
		// override this method to support replace

	GRID_API virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
		// override this method to support replace

	GRID_API virtual BOOL GetSelectedText(CString& strResult);
		// override this method to return the selected text

	// Support for several child buttons (HotSpot, Combobox, Spinnbuttons)
	GRID_API virtual void OnClickedButton(CGXChild* pChild);
		// pChild points to the callee (see CGXSpinEdit for an example)

	GRID_API CGXGridCore* Grid();
		// Pointer to Grid

	GRID_API CWnd* GridWnd();
		// Pointer to GridWnd

	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		// Called from CGXGridCore::OnCommand for
		// ON_COMMAND messages (e.g. ON_CBN_SELCHANGE)

	GRID_API virtual void OnNotifyMsg(MSG* pMsg);
		// Called from CGXGridCore::OnVScroll, OnHScroll

	GRID_API virtual HBRUSH OnGridCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		// Called from CGXGridCore::DoCtlColor

	GRID_API virtual void OnGridWinIniChange(LPCTSTR lpszSection);
		// Called from CGXGridCore::OnGridWinIniChange

	GRID_API virtual void OnGridSysColorChange();

	GRID_API virtual BOOL IsReadOnly();

	GRID_API virtual void OnGridCancelMode();

	// for the celltips
	GRID_API virtual BOOL NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	
	// return the ID that identifies the CGXCellTipWnd derivative that will be used
	GRID_API virtual DWORD GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	
	// Lets the control initialize the celltip
	GRID_API virtual void InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip);

	// Windowless means just that, the control does not have a windows window associated with it
	GRID_API virtual BOOL IsWindowlessControl();

protected:
	GRID_API CFont* LoadFont(CDC* pDC, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// compares the font with the standard font
		// if different, the method selects the font into the device context

	GRID_API void FreeStyle(BOOL bGrid = TRUE);
		// deletes the style

	GRID_API CGXStyle* NeedStyle();
		// loads the style

	GRID_API virtual void AddChild(CGXChild*);
		// adds a child

	GRID_API virtual void RemoveChild(CGXChild*);
		// removes a child

	GRID_API virtual CGXChild* GetChild(int);
		// returns a child

	GRID_API virtual int GetCount();
		// No. of childs

	GRID_API virtual CGXChild* ChildWithFocus();
		// returns pointer to active child

	GRID_API virtual void FocusOnChild(CGXChild* child);
		// sets active child to retrieve mouse and keys messages

	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
		// override this methode to initialize the rectangle of the children

	GRID_API void OnKillFocus(CWnd* pNewWnd);
		// call this method from your OnKillFocus message handler.
		// it will deactivate the grid, if necessary

	GRID_API void ExcludeClipRect(const CRect& rect);
		// call this method to protect your controls to be overdrawn

	GRID_API virtual void DrawBackground(CDC* pDC, const CRect& rect, const CGXStyle& style, BOOL bErase = FALSE);
	GRID_API virtual void DrawFrame(CDC* pDC, const CRect& rect, const CGXStyle& style);

	GRID_API virtual BOOL ValidateString(const CString& sEdit);
		// Called after the user pressed a key and before it is accepted.
		// Will also be called from SetCurrentText before the text is
		// displayed in the cell.

	GRID_API virtual BOOL ValidatePaste(const CString& sPaste);
		// called when the user pastes text (when the cell is active)
		// Default implementation returns TRUE. If you implement this
		// build the complete string and call ValidateString (or) validate
		// the pasted text in this override itself. Refer to CGXEditControl
		// for a sample impl. This will be called from CGXControl::Paste which
		// will call ReplaceSel based on the return value from this call.

	GRID_API virtual void OnInvalidKeyPressed(LPCTSTR pszChar);
		// called when the user pressed an invalid key which
		// could not be accepted.

	GRID_API virtual BOOL GetMarkHeaderState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);

	// Attributes:
public:
	BOOL            m_bRefreshOnSetCurrentCell;
					// If you have a control which appearence is
					// depending on whether it is a current cell
					// or not, you should set m_bRefreshOnSetCurrentCell
					// = TRUE.

private:
	CGXGridCore*    m_pGrid;        // Pointer to grid

protected:
	ROWCOL          m_nRow,         // Row for current cell
					m_nCol;         // Column for current cell
	CGXStyle*       m_pStyle;       // Style for current cell
	BOOL            m_bInit;

	// childs
	CPtrList*   m_pChildList;
	CGXChild*   m_pChildFocus;

	// support for IME/DBCS
	BOOL    m_bDoubleByteChar;
	TCHAR   m_nDoubleByteLeadChar;

	// celltips
	CGXCellTipBase* m_pCellTipImpl;

// Implementation
public:
#ifndef _GXDLL
	static CGXControlClass GXNEAR ctrlCGXControl;
#else
	static GX_DATA CGXControlClass ctrlCGXControl;
	GRID_API static CGXControlClass* PASCAL _GetControlBaseClass();
#endif

	friend class CGXChild;
	friend class CGXCalcSizeImp;
	friend class CGXDrawingAndFormatting;
};

/////////////////////////////////////////////////////////////////////////////
// Child classes which can be used by the composite class

class CGXChild
{
public:
	// construction, destrcution
	GRID_API CGXChild(CGXControl* pComposite);
	GRID_API virtual ~CGXChild();

	// Member functions
	GRID_API virtual void SetRect(const CRect& r);
	GRID_API virtual CRect GetRect();
	GRID_API virtual BOOL Intersects(CPoint pt);

	// Focus
	GRID_API virtual BOOL HasFocus();

	// Text
	GRID_API virtual void SetText(LPCTSTR s);
	GRID_API virtual CString GetText();

	// Drawing
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive) = 0;
	GRID_API virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
	GRID_API virtual void Refresh();

	// Mouse hit
	GRID_API virtual BOOL MouseMove(UINT nFlags, CPoint pt);

	// Left Button
	GRID_API virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL LButtonUp(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint point);

	// Middle Button
	GRID_API virtual BOOL MButtonDown(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL MButtonUp(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL MButtonDblClk(UINT nFlags, CPoint point);

	// Right Button
	GRID_API virtual BOOL RButtonDown(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL RButtonUp(UINT nFlags, CPoint pt);
	GRID_API virtual BOOL RButtonDblClk(UINT nFlags, CPoint point);

	GRID_API virtual BOOL MouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Keyboard
	GRID_API virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// system settings
	GRID_API virtual void OnGridWinIniChange(LPCTSTR lpszSection);
		// Called from CGXGridCore::OnGridWinIniChange

	GRID_API virtual void OnGridSysColorChange();

	GRID_API virtual void OnGridCancelMode();

	inline CGXGridCore* Grid() { return m_pComposite->Grid(); }
		// Pointer to Grid

	inline CWnd* GridWnd() { return m_pComposite->GridWnd(); }
		// Pointer to GridWnd

protected:
	CGXControl*		m_pComposite;
	CRect           m_rect;
	CString         m_sText;

	// support for IME/DBCS
	BOOL			m_bDoubleByteChar;
	TCHAR			m_nDoubleByteLeadChar;
};


// CGXGridCombo window (will be created with WS_POPUP style)
//

class CGXGridCombo : public CWnd
{
// Construction
public:

	GRID_DECLARE_DYNAMIC(CGXGridCombo)

	GRID_API CGXGridCombo(CWnd* pGridWnd, CWnd* pWnd, const CRect& rect);

// Operations
	GRID_API void SetColor(COLORREF rgbText, COLORREF rgbBack);
	GRID_API CListBox& GetLBox();

	GRID_API static void AFXAPI RegisterClass();
	GRID_API static void AFXAPI UnregisterClass();
	GRID_API static BOOL AFXAPI GetComboBoxDropDown();
	GRID_API static void AFXAPI SetComboBoxDropDown(BOOL b = TRUE);
	GRID_API static CString AFXAPI GetClassName();

// Implementation
	GRID_API virtual ~CGXGridCombo();
	GRID_API void AttachListBox(CWnd* pListBox);

// Attributes
protected:
	CWnd*       m_pListBox;
	CWnd*       m_pGridWnd;

	BOOL        m_bColor;

	CBrush      br;
	COLORREF    m_rgbText,
				m_rgbBack;

protected:
	// overridables
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CGXGridCombo)
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	GRID_API afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
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

#endif // _GXCTRL_H
