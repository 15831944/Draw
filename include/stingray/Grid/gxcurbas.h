///////////////////////////////////////////////////////////////////////////////
// gxcurbas.h : Declarations for the Currency Control
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
//

#ifndef _GXCURBAS_H_
#define _GXCURBAS_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

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

/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit window
//
// Adds a combo like drop down button to an edit control
//

class CGXBDropEdit : public CEdit
{
	GRID_DECLARE_DYNAMIC(CGXBDropEdit)

	
// Construction
public:
	GRID_API CGXBDropEdit();

	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// Attach to an existing edit control
	GRID_API BOOL AttachEdit(int nCtlID, CWnd* pParentWnd);

// Attributes
public:
	// Methods for manipulating the alignment mode (within the edit control)
	GRID_API void SetRightAlign(BOOL bRightAlign = TRUE);
	GRID_API BOOL IsRightAligned() const;

	// Methods for manipulating the border settings
	GRID_API void SetBorder(WORD wLeftBorder, WORD wRightBorder);
	GRID_API DWORD GetBorders() const;

// Operations
public:
	// Methods to set/get the bitmap on the button
	GRID_API BOOL SetBitmap(UINT nBmpID);
	GRID_API BOOL SetBitmap(LPCTSTR lpszBmpName);
	GRID_API BOOL SetBitmap();						// Removes button
	GRID_API HBITMAP GetBitmap() const;

	// Determintes whether the given point (in screen or client
	// coordinates) is a hit on the button.
	// OG specific made this virtual 4/2/97
	GRID_API virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;

	// Forces a redraw of the button
	GRID_API void InvalidateBtn();

// Overrideables
protected:
	// Method called when the button has been clicked
	GRID_API virtual void OnClicked();

	// Method called to draw the button
	GRID_API virtual void DrawBtn(CDC& dc, CRect r);

	// Method to handle Mouse Leave messages.
	GRID_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	GRID_API virtual ~CGXBDropEdit();

#ifdef _DEBUG
	GRID_API virtual void Dump(CDumpContext& dc) const;
	GRID_API virtual void AssertValid() const;
#endif

protected:
	// Implementation, data members.
	CRect   m_btnRect;				// The window rect of the button (in our
									// parents client coordinates)
	CBitmap m_bmp;					// Bitmap drawn on face of button
	LPCTSTR m_lpszBmpName;			// Resource ID of above bitmap
	WORD    m_wState;				// Current state (see States below)
	WORD    m_wLeftBorder;			// Left hand Gap between bitmap and border
	WORD    m_wRightBorder;			// Right hand Gap between bitmap and border

	// Bit settings in m_wState
	enum States
	{
		Pressed    = 0x0001,		// Button is currently down	
		Capture    = 0x0002,		// We are tracking a left click on the button		
		RightAlign = 0x0004,		// The button is right aligned within the edit
		Hover      = 0x0008
	};

	// Implementation - message map and entries
	GRID_DECLARE_MESSAGE_MAP()

	GRID_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	GRID_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnNcMouseMove(UINT nFlags, CPoint point);
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	GRID_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	GRID_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
	GRID_API afx_msg void OnNcPaint();
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnEnable(BOOL bEnable);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

/////////////////////////////////////////////////////////////////////////////

// Function to take the given rectange in the given dc and draw it disabled.
void AFXAPI CGXBDrawDisabled(CDC& dc, int x, int y, int nWidth, int nHeight);




class CGXBCurrencyEdit : public CGXBDropEdit //public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXBCurrencyEdit)
public:

	// The following nested helper class provides the core currency
	// formatting and parsing methods.

	class GRID_API Format
	{
	public:
		// Construction/destruction.  Note: if the default initialization
		// does not occur, the object will in a valid but decidedly 
		// American state.

		Format(BOOL bInitializeFromSystemDefaults = TRUE);
		inline virtual ~Format() {}

		// Property retrieval and setting methods for all the currency
		// display options.  Some important notes: 
		//
		// 1) Setting the thousand separator to the null character ('\0') 
		//    will prevent its use.
		// 2) Setting the decimal digits to negative one (-1) will use 
		//    as many digits are necessary to display the number.  If
		//    the number of digits is larger than required, the output
		//    will be padded with the padding character.
		//
		// Negative Format  Positive Format
		//
		// 0	($1)		0	$1 
		// 1	-$1			1	1$ 
		// 2	$-1			2	$ 1
		// 3	$1-			3	1 $
		// 4	(1$)
		// 5	-1$			These formats are taken directly from
		// 6	1-$			Microsoft's documentation regarding
		// 7	1$-			the international section of WIN.INI.
		// 8	-1 $		The CGXBCurrencyEdit uses them for the
		// 9	-$ 1		positive and negative formats given via
		// 10	$ 1-		the formatting object.

		inline BOOL IsLeadingZeroEnabled() const
			{ return m_bLeadingZero; }
		inline void EnableLeadingZero(BOOL b)
			{ m_bLeadingZero = b; }
		inline BOOL IsDecimalSeparatorLineEnabled() const
			{ return m_bDecimalSeparatorLine; }
		inline void EnableDecimalSeparatorLine(BOOL b)
			{ m_bDecimalSeparatorLine = b; }
		inline BOOL IsRotateWhileAtEndEnabled() const
			{ return m_bRotateWhileAtEnd;	}
		inline void EnableRotateWhileAtEnd(BOOL b)
			{ m_bRotateWhileAtEnd = b;	}
		inline BOOL IsSeparatorsInLeadingSpaceEnabled() const
			{ return m_bSeparatorsInLeadingSpaces;	}
		inline void EnableSeparatorsInLeadingSpace(BOOL b)
			{ m_bSeparatorsInLeadingSpaces = b;	}
		inline LPCTSTR GetMonetarySymbol() const
			{ return m_strMonetarySymbol; }
		inline void SetMonetarySymbol(LPCTSTR p)
			{ m_strMonetarySymbol = p; }
		inline LPCTSTR GetGrouping() const
			{ return m_strGrouping; }
		BOOL SetGrouping(LPCTSTR x);
		inline TCHAR GetThousandSeparator() const
			{ return m_cThousandSeparator; }
		inline void SetThousandSeparator(TCHAR c)
			{ m_cThousandSeparator = c; }
		inline TCHAR GetDecimalSeparator() const
			{ return m_cDecimalSeparator; }
		inline void SetDecimalSeparator(TCHAR c)
			{ m_cDecimalSeparator = c; }
		inline TCHAR GetPaddingCharacter() const
			{ return m_cPaddingCharacter; }
		BOOL SetPaddingCharacter(TCHAR c);
		BOOL GetBackgroundColor(COLORREF& cr) const;
		void SetBackgroundColor(COLORREF cr);
		BOOL GetNegativeColor(COLORREF& cr) const;
		void SetNegativeColor(COLORREF cr);
		BOOL GetPositiveColor(COLORREF& cr) const;
		void SetPositiveColor(COLORREF cr);
		inline COLORREF GetDecimalSeparatorLineColor() const
			{ return m_crSeparator; }
		inline void SetDecimalSeparatorLineColor(COLORREF cr)
			{ m_crSeparator = cr; }
		inline int GetPositiveFormat() const
			{ return m_iPositiveFormat; }
		void SetPositiveFormat(int i);
		inline int GetNegativeFormat() const
			{ return m_iNegativeFormat; }	
		void SetNegativeFormat(int i);
		inline int GetDecimalDigits() const
			{ return m_iDecimalDigits; }
		inline void SetDecimalDigits(int i)
			{ m_iDecimalDigits = i; }
		inline int GetFractionalDigits() const
			{ return m_iFractionalDigits; }
		inline void SetFractionalDigits(int i)
			{ m_iFractionalDigits = i; }

		// Reads values as necessary from registry, INI file, etc. to
		// match settings specified by user in Control Panel.

		void InitializeFromSystemDefaults();

		// The following method clears any previously specified custom 
		// color use.

		inline void ClearCustomColors()
			{ m_iColorUseFlags = 0; }

		// The following methods convert between a numeric value and a
		// string representation.  If customization beyond that required
		// by the basic Format object is requied, derive your own class
		// and override the following methods; then pass your format
		// object to the SECCurrencyEdit in its constructor.

		virtual BOOL ParseValue(LPCTSTR pcsz, double& d, BOOL& bNegative) const;
		virtual void FormatValue(double dAbs, CString& str, BOOL bIsNegative) const;

		// If, for some pathological reason, the user needs to set the thousands
		// separator equivalent to the decimal separator, then he needs to derive
		// his own class and override these methods. Otherwise, it is not at all
		// likely that parsing will ever work consistently and accurately.

		virtual int FindDecimalSeparator(LPCTSTR pcszString, TCHAR cDecimal = '\0') const;
		virtual int FindFirstAndLastDigits(LPCTSTR pcszString, int& iFirst, int& iLast) const;
		
		// Operators - virtual to allow descendant handling.

		virtual Format& operator=(const Format& rhs);
		virtual BOOL operator==(const Format& rhs) const;
		inline virtual BOOL operator!=(const Format& rhs) const
			{ return !operator==(rhs); }

	private:
		BOOL m_bLeadingZero;			// leading 0 for numbers -1 < n < 1 ?
		BOOL m_bDecimalSeparatorLine;	// vertical line for decimal point?
		BOOL m_bRotateWhileAtEnd;		// Rotates the decimal part/fraction part while the 
										// the cursor is at the end...FALSE by default
		BOOL m_bSeparatorsInLeadingSpaces;	// will display seperators even on the leading spaces
										// FALSE by default
		CString m_strMonetarySymbol;		// currency symbol (default: $)
		CString m_strGrouping;			// decimal digit grouping sizes
		TCHAR m_cThousandSeparator;		// groups decimal digits (default: ,)
		TCHAR m_cDecimalSeparator;		// decimal point (default: .)
		TCHAR m_cPaddingCharacter;		// used to pad to left of decimal
		COLORREF m_crBackground;		// background color of control window
		COLORREF m_crNegative;			// color of text when value is negative
		COLORREF m_crPositive;			// color of text when value is negative
		COLORREF m_crSeparator;			// color of decimal separator line
		int m_iColorUseFlags;			// internal color flags variable
		int m_iPositiveFormat;			// WIN.INI format for positive values
		int m_iNegativeFormat;			// WIN.INI format for negative values
		int m_iDecimalDigits;			// number of characters left of decimal
		int m_iFractionalDigits;		// number of digits to right of decimal
	};

	// Construction/destruction.

	GRID_API CGXBCurrencyEdit();
	GRID_API CGXBCurrencyEdit(Format* pFmt);
	GRID_API virtual ~CGXBCurrencyEdit();

	// Replaces an existing edit control.

	GRID_API BOOL Initialize(CWnd* pwndParent, UINT uiControlID);

	// Gets or sets the actual numeric value directly.

	GRID_API void GetValue(double& d) const;	
	GRID_API void SetValue(double d, BOOL bRedraw = TRUE);

	// Gets of sets the display formatting data.

	GRID_API void GetFormat(Format& f);
	GRID_API void SetFormat(const Format& f);

	// The alignment is actually maintained via edit ES_* style values;
	// these methods are provided largely for convenience.

	enum Align { left = 0, center = 1, right = 2 };
	GRID_API Align GetAlignment() const;
	GRID_API void SetAlignment(Align a);

	// The read-only feature is actually mantained via the normal edit
	// control ES_READONLY style; these methods are provided largely
	// for convenience.  The EM_SETREADONLY message will also work.

	GRID_API BOOL IsReadOnly() const;
	GRID_API void SetReadOnly(BOOL b);
	
	GRID_API void SetMargins(UINT nLeft, UINT nRight);
	inline DWORD GetMargins() const
		{ return MAKELONG(m_uiLeftMargin, m_uiRightMargin); }
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBCurrencyEdit)
	//}}AFX_VIRTUAL

	BOOL m_bRotateWhileAtEnd;			// Rotates the decimal part/fraction part while the 
										// the cursor is at the end...FALSE by default
	BOOL m_bSeparatorsInLeadingSpaces;	// will display seperators even on the leading spaces
										// FALSE by default

protected:
	GRID_API virtual BOOL ShowCalculator();
	GRID_API void NotifyParent(UINT uiCode);

	// Override of the CGXBDropEdit for handling the button click.

	inline virtual void OnClicked()
		{ ShowCalculator(); }

	// Data structure used for maintaining selection details.
	// Two special settings should be noted: 0, -1 means select 
	// all and -1, 0 means no selection.

	typedef struct tagSelData
	{
		int iStart, iStop;
		inline tagSelData() : iStart(-1), iStop(0) {}
		inline tagSelData(const tagSelData& s) :
			iStart(s.iStart), iStop(s.iStop) {}
		inline void Set(int i, int j) { iStart = i; iStop = j; }
		inline void Clear() { iStart = -1; iStop = 0; }
		inline void Normalize()
		{
			int iTmp;
			if (iStart > iStop)
			{
				iTmp = iStop;
				iStop = iStart;
				iStart = iTmp;
			}
		}
		inline tagSelData& operator=(const tagSelData& rhs)
		{
			if (this != &rhs)
			{
				iStart = rhs.iStart;
				iStop = rhs.iStop;
			}
			return *this;
		}

	} SELDATA;

	// Data structure used for maintaining undo data.

	typedef struct tagUndoData
	{
		CString strText;
		int iCaretPos;
		SELDATA sel;

		tagUndoData() : iCaretPos(-1) {}
		tagUndoData(const tagUndoData& u) : 
			strText(u.strText), iCaretPos(u.iCaretPos), sel(u.sel) {}
		inline tagUndoData& operator=(const tagUndoData& rhs)
		{
			if (this != &rhs)
			{
				strText = rhs.strText;
				iCaretPos = rhs.iCaretPos;
				sel = rhs.sel;
			}
			return *this;
		}

	} UNDODATA;
	
	BOOL m_bNegative;		// Is the data value negative?
	BOOL m_bCanUndo;		// undo buffer has something?
	BOOL m_bParseOnSetText;	// parse value on WM_SETTEXT?
	BOOL m_bRedraw;			// is redraw allowed?
	BOOL m_bMouseSelect;	// are we mouse selecting?
	BOOL m_bOverstrike;		// is overstrike mode enabled?
	UNDODATA m_Undo;		// undo buffer
	double m_dValue;		// numeric value
	Format* m_pFormat;		// current format settings
	HFONT m_hFont;			// font set via WM_SETFONT
	int m_iCaretPos;		// caret character position
	SELDATA m_Sel;			// selection information
	UINT m_uiRightMargin;	// The right margin in pixels.
	UINT m_uiLeftMargin;	// The left margin in pixels.


	// Descendant classes may override the following members to provide
	// a right-button popup menu, background drawing, save their own 
	// data for an undo operation, etc.

	GRID_API virtual BOOL PrepareTextForPaste(CString& strText);	
	GRID_API virtual CMenu* CreatePopupMenu() const;
	GRID_API virtual void DeletePopupMenu(CMenu* p) const;
	GRID_API virtual void DoBackspace();
	GRID_API virtual void DoDelete();
	GRID_API virtual void DoInsert(LPCTSTR pcsz);
	GRID_API virtual void EraseBackground(CDC* pDC);
	GRID_API virtual void SaveDataForUndo(LPCTSTR p = NULL, int iCaret = -1);
	GRID_API virtual void StartEdit(int iCaretPos);
	GRID_API virtual void StopEdit();
	GRID_API virtual void DrawDecimalSeparatorLine(CDC& DC, int x);
	GRID_API virtual void HandleNegativeSignKey();
	GRID_API virtual void ToggleOverstrikeMode();


	// Non-virtual members; descendant classes may utilize these, but should 
	// not override them.

	inline BOOL IsNegative() const
		{ return m_bNegative; }
	inline BOOL HasSel() const
		{ return m_Sel.iStart != -1 && m_Sel.iStop != m_Sel.iStart; }
	GRID_API BOOL SetSel(int iStart, int iStop);
	inline BOOL SetSelNone()
		{ return SetSel(-1, 0); }
	inline BOOL SetSelAll()
		{ return SetSel(0, -1); }
	inline BOOL IsMouseSelecting() const
		{ return m_bMouseSelect; }
	GRID_API BOOL IsEntireNumberSelected(BOOL* pbMore = NULL) const;
	inline BOOL IsOverstrikeEnabled() const
		{ return m_bOverstrike; }	
	GRID_API COLORREF GetBackgroundColor() const;
	GRID_API COLORREF GetTextColor() const;
	GRID_API int PointToCaretPos(const CPoint& pt);
	GRID_API void CalculateTextRect(CRect& rc);
	inline void DoInsert(TCHAR c)
		{ DoInsert(CString(c)); }
	GRID_API void GetSelectedText(CString& s) const;
	GRID_API void MoveCaret(int iChar, BOOL bUpdateSel = FALSE);
	GRID_API void PaintingCore(CDC& DC);
	inline void QueueRedraw(BOOL bEraseBackground = TRUE)
		{ if (m_bRedraw) InvalidateRect(NULL, bEraseBackground); }
	GRID_API void ReplaceSelString(LPCTSTR pcszNew, CString& str) const;
	GRID_API void SetWindowTextNoParse(LPCTSTR p);
	GRID_API void MoveCaretToNumber();
	GRID_API void SetValue(double d, BOOL bNegative, BOOL bRedraw);

	// Handlers provided by ClassWizard.

	//{{AFX_MSG(CGXBCurrencyEdit)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	// Edit control message handlers not provided by ClassWizard.

	GRID_API afx_msg LRESULT OnCanUndo(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnEmptyUndoBuffer(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetReadOnly(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetMargins(WPARAM wParam, LPARAM lParam);

	// Standard message handlers not provided by ClassWizard.

	GRID_API afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetRedraw(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnUndo(WPARAM wParam, LPARAM lParam);

	// Command handlers for right mouse button popup menu.

	GRID_API afx_msg void OnEditUndo();
	GRID_API afx_msg void OnEditCopy();
	GRID_API afx_msg void OnEditCut();
	GRID_API afx_msg void OnEditPaste();
	GRID_API afx_msg void OnEditClear();
	GRID_API afx_msg void OnEditSelectAll();

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

#endif //_GXCURBAS_H_
