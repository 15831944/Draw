///////////////////////////////////////////////////////////////////////////////
// curredit.h header file for SECDropEdit - subclassed edit with little
//			    drop down button.
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
//	Author:		John
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __CURREDIT_H__
#define __CURREDIT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

// The SECCurrencyEdit provides an extensible class for entering
// and displaying custom-formatted currency data.  Input data parsing
// and output display formatting can be customized by descending new
// classes from SECCurrencyEdit::Format and SECCurrencyEdit.
//
// The SECCurrencyEdit supports some of the EM_* edit control message
// interface, and can thus be manipulated to some degree using a CEdit
// object (not recommended, but possible if required for compatibility
// with existing code).  The following lists the messages supported.
//
// Windows Messages		Edit Control Messages
// ----------------		---------------------
// WM_COPY				EM_CANUNDO
// WM_CUT				EM_EMPTYUNDOBUFFER
// WM_GETFONT			EM_GETSEL
// WM_PASTE				EM_SETREADONLY
// WM_SETFONT			EM_SETSEL
// WM_SETREDRAW			EM_UNDO
// WM_SETTEXT
// WM_UNDO


#ifndef __DROPEDIT_H__
#include "toolkit\dropedit.h"
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Forward declarations
class SECCurrencyEdit;

//SECCurrencyEdit DDX routines

//@func SECCurrencyEdit DDX routine.
//@rdesc void
//@parm CDataExchange* | pDX | Pointer to a CDataExchange object.
//@parm SECCurrencyEdit& | medit | Reference to a SECCurrencyEdit control.
//@parm double& | dValue | The value to set or retrieve.
TOOLKIT_API void AFXAPI DDX_Currency(CDataExchange* pDX, SECCurrencyEdit& cedit, double& dValue);


/////////////////////////////
// AutoDuck tag block block for SECCurrencyEdit 

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bNegative | True if the data value is negative.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bCanUndo | True if the Undo buffer is not empty.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bParseOnSetText | True if control parses value 
// when WM_SETTEXT messages are received.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bRedraw | True if redraw is allowed.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bMouseSelect | True while mouse selecting.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata BOOL  | SECCurrencyEdit | m_bOverstrike | True if overstrike mode is enabled.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata UNDODATA  | SECCurrencyEdit | m_Undo | Undo buffer.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata double  | SECCurrencyEdit | m_dValue | Numeric value in the control.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata Format*  | SECCurrencyEdit | m_pFormat | Current format settings object.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata HFONT  | SECCurrencyEdit | m_hFont | Current font.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata int  | SECCurrencyEdit | m_iCaretPos | Caret character position.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata SELDATA  | SECCurrencyEdit | m_Sel | Selection information.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata UINT  | SECCurrencyEdit | m_uiRightMargin | The right margin in pixels.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mdata UINT  | SECCurrencyEdit | m_uiLeftMargin | The left margin in pixels.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc virtual void  | SECCurrencyEdit | OnClicked | Called when the button
// is pressed (to create the popup calculator).
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc DWORD  | SECCurrencyEdit | GetMargins | Retrieves the current margins.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | IsNegative | Returns nonzero if the current
// value is negative.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | HasSel | Returns nonzero if the control
// currently has selected text.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | SetSelNone | Deselects text in the control.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | SetSelAll | Selects all text in the control.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | IsMouseSelecting | Returns nonzero if the 
// mouse is currently selecting text.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc BOOL  | SECCurrencyEdit | IsOverstrikeEnabled | Returns nonzero if 
// overstrike mode is currently enabled.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc void  | SECCurrencyEdit | DoInsert | Handles inserting of a character.
//@parm TCHAR  | c | Character to insert.
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc void  | SECCurrencyEdit | QueueRedraw | Redraws queued data. 
//@xref <c SECCurrencyEdit>

//@doc SECCurrencyEdit
//@mfunc DWORD  | SECCurrencyEdit | GetMargins | Returns the current margins.
//@xref <c SECCurrencyEdit>


// adinsert AutoDuck insertion point for SECCurrencyEdit 
//@doc SECCurrencyEdit 
//@class The SECCurrencyEdit provides an extensible class for entering and 
// displaying custom-formatted currency data.  Input data parsing and output 
// display formatting can be customized by descending new classes from 
// SECCurrencyEdit::Format and SECCurrencyEdit.
//
// The SECCurrencyEdit class supports some of the EM_* edit control message 
// interface, and it can thus be manipulated to some degree using a Cedit 
// object (not recommended, but possible if required for compatibility with 
// existing code).  Messages supported are listed below.
//
// See the CURRENCY sample in the \SAMPLES\TOOLKIT\STANDARD\CONTROLS\CURRENCY 
// directory for a demonstration of this class.
//
//@flag Windows Messages |
// WM_COPY, WM_CUT, WM_GETFONT, WM_PASTE, WM_SETFONT,
// WM_SETREDRAW, WM_SETTEXT, WM_UNDO, 
//@flag Edit Control Messages |
// EM_CANUNDO, EM_EMPTYUNDOBUFFER, EM_GETSEL, EM_SETREADONLY
// EM_SETSEL, EM_UNDO, EM_SETMARGINS
//
//@base public | SECDropEdit
class SECCurrencyEdit : public SECDropEdit //public CWnd
{
public:
	TOOLKIT_DECLARE_DYNAMIC(SECCurrencyEdit)

	// The following nested helper class provides the core currency
	// formatting and parsing methods.

	class Format
	{
	public:
		// Construction/destruction.  Note: if the default initialization
		// does not occur, the object will in a valid but decidedly 
		// American state.

		TOOLKIT_API Format(BOOL bInitializeFromSystemDefaults = TRUE);
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
		// 8	-1 $		The SECCurrencyEdit uses them for the
		// 9	-$ 1		positive and negative formats given via
		// 10	1 $-		the formatting object.
		// 11	$ 1-
		// 12   $ -1		Rob (20 Aug 98):  Negative formats 10
		// 13   1- $        through 15 were updated to match those
		// 14   ($ 1)		of Windows NT 4.0.  Format indices 11 
		// 15   (1 $)       through 15 were added.  What was previously 
		//                  format index 10 "$ 1-" is now format index 11.

		inline BOOL IsLeadingZeroEnabled() const { return m_bLeadingZero; }
		inline void EnableLeadingZero(BOOL b) { m_bLeadingZero = b; }
		inline BOOL IsLeadingThousEnabled() const { return m_bLeadingThousSeparator; }
		inline void EnableLeadingThousSeparator (BOOL b) { m_bLeadingThousSeparator = b;}
		inline BOOL IsDecimalSeparatorLineEnabled() const { return m_bDecimalSeparatorLine; }
		inline void EnableDecimalSeparatorLine(BOOL b) { m_bDecimalSeparatorLine = b; }
		inline LPCTSTR GetMonetarySymbol() const { return m_strMonetarySymbol; }
		inline void SetMonetarySymbol(LPCTSTR p) { m_strMonetarySymbol = p; }
		inline LPCTSTR GetGrouping() const { return m_strGrouping; }
		TOOLKIT_API BOOL SetGrouping(LPCTSTR x);
		inline TCHAR GetThousandSeparator() const { return m_cThousandSeparator; }
		inline void SetThousandSeparator(TCHAR c) { m_cThousandSeparator = c; }
		inline TCHAR GetDecimalSeparator() const { return m_cDecimalSeparator; }
		inline void SetDecimalSeparator(TCHAR c) { m_cDecimalSeparator = c; }
		inline TCHAR GetPaddingCharacter() const { return m_cPaddingCharacter; }
		TOOLKIT_API BOOL SetPaddingCharacter(TCHAR c);
		TOOLKIT_API BOOL GetBackgroundColor(COLORREF& cr) const;
		TOOLKIT_API void SetBackgroundColor(COLORREF cr);
		TOOLKIT_API BOOL GetNegativeColor(COLORREF& cr) const;
		TOOLKIT_API void SetNegativeColor(COLORREF cr);
		TOOLKIT_API BOOL GetPositiveColor(COLORREF& cr) const;
		TOOLKIT_API void SetPositiveColor(COLORREF cr);
		inline COLORREF GetDecimalSeparatorLineColor() const { return m_crSeparator; }
		inline void SetDecimalSeparatorLineColor(COLORREF cr) { m_crSeparator = cr; }
		inline int GetPositiveFormat() const { return m_iPositiveFormat; }
		TOOLKIT_API void SetPositiveFormat(int i);
		inline int GetNegativeFormat() const { return m_iNegativeFormat; }
		TOOLKIT_API void SetNegativeFormat(int i);
		inline int GetDecimalDigits() const { return m_iDecimalDigits; }
		inline void SetDecimalDigits(int i) { m_iDecimalDigits = i; }
		inline int GetFractionalDigits() const { return m_iFractionalDigits; }
		inline void SetFractionalDigits(int i) { m_iFractionalDigits = i; }

		// Reads values as necessary from registry, INI file, etc. to
		// match settings specified by user in Control Panel.

		TOOLKIT_API void InitializeFromSystemDefaults();

		// The following method clears any previously specified custom 
		// color use.

		inline void ClearCustomColors() { m_iColorUseFlags = 0; }

		// The following methods convert between a numeric value and a
		// string representation.  If customization beyond that required
		// by the basic Format object is requied, derive your own class
		// and override the following methods; then pass your format
		// object to the SECCurrencyEdit in its constructor.

		TOOLKIT_API virtual BOOL ParseValue(LPCTSTR pcsz, double& d, BOOL& bNegative) const;
		TOOLKIT_API virtual void FormatValue(double dAbs, CString& str, BOOL bIsNegative) const;

		// If, for some pathological reason, the user needs to set the thousands
		// separator equivalent to the decimal separator, then he needs to derive
		// his own class and override these methods. Otherwise, it is not at all
		// likely that parsing will ever work consistently and accurately.

		TOOLKIT_API virtual int FindDecimalSeparator(LPCTSTR pcszString, TCHAR cDecimal = '\0') const;
		TOOLKIT_API virtual int FindFirstAndLastDigits(LPCTSTR pcszString, int& iFirst, int& iLast) const;

		// Operators - virtual to allow descendant handling.

		TOOLKIT_API virtual Format& operator=(const Format& rhs);
		TOOLKIT_API virtual BOOL operator==(const Format& rhs) const;
		inline virtual BOOL operator!=(const Format& rhs) const { return !operator==(rhs); }

	private:
		BOOL m_bLeadingZero;			// leading 0 for numbers -1 < n < 1 ?
		BOOL m_bLeadingThousSeparator;	// leading separator ($ ,   , 12,345.00)
		BOOL m_bDecimalSeparatorLine;	// vertical line for decimal point?
		CString m_strMonetarySymbol;	// currency symbol (default: $)
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

	//@access Construction/destruction

	//@cmember
	/* Constructs a SECCurrencyEdit object.*/
	TOOLKIT_API SECCurrencyEdit();

	//@cmember
	/* Constructs a  SECCurrencyEdit object.*/
	TOOLKIT_API SECCurrencyEdit(Format* pFmt);
	
	TOOLKIT_API virtual ~SECCurrencyEdit();

	//@cmember
	/* Replaces an existing edit control.*/
	TOOLKIT_API BOOL Initialize(CWnd* pwndParent, UINT uiControlID);

public:

	//@access Attributes	

	//@cmember
	/* Gets the actual numeric value directly.*/
	TOOLKIT_API void GetValue(double& d) const;

	//@cmember
	/* Sets the actual numeric value directly.*/
	TOOLKIT_API void SetValue(double d, BOOL bRedraw = TRUE);

	//@cmember
	/* Gets the display formatting data.*/
	TOOLKIT_API void GetFormat(Format& f);

	//@cmember
	/* Sets the display formatting data.*/
	TOOLKIT_API void SetFormat(const Format& f);

	//@cmember,menum
	/* Alignments*/
	enum Align 
	{	
		left = 0,		//@@emem Left alignment
		center = 1,		//@@emem Center alignment
		right = 2		//@@emem Right alignment
	};

	//@cmember
	/* The alignment is actually maintained via edit control */
	// ES_* style values; this function is provided for convenience.
	TOOLKIT_API Align GetAlignment() const;

	//@cmember
	/* The alignment is actually maintained via edit control */
	// ES_* style values; this function is provided for convenience.
	TOOLKIT_API void SetAlignment(Align a);

	//@cmember
	/* The read-only feature is actually maintained via the normal */
	// edit control ES_READONLY style; this function is provided for convenience.
	TOOLKIT_API BOOL IsReadOnly() const;

	//@cmember
	/* The read-only feature is actually maintained via the normal */
	// edit control ES_READONLY style; this function is provided for convenience.
	TOOLKIT_API void SetReadOnly(BOOL b);

	//@cmember
	/* Sets the margins for the control.*/
	TOOLKIT_API void SetMargins(UINT nLeft, UINT nRight);

	//@cmember
	/* Retrieves the margins for the control.*/
	inline DWORD GetMargins() const	 { return MAKELONG(m_uiLeftMargin, m_uiRightMargin); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECCurrencyEdit)
	//}}AFX_VIRTUAL

	//@access Overridable

public:
	
	// Determintes whether the given point (in screen or client
	// coordinates) is a hit on the button.
	//@cmember
	/* Performs hit testing for the button.*/
	TOOLKIT_API virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;

	//@cmember
	/* Pre-paste processing.*/
	TOOLKIT_API virtual BOOL PrepareTextForPaste(CString& strText);
	
	//@cmember
	/* Creates the popup menu.*/
	TOOLKIT_API virtual CMenu* CreatePopupMenu() const;
	
	//@cmember
	/* Deletes the popup menu.*/
	TOOLKIT_API virtual void DeletePopupMenu(CMenu* p) const;
	
	//@cmember
	/* Processes backspace key press.*/
	TOOLKIT_API virtual void DoBackspace();
	
	//@cmember
	/* Processes delete key press.*/
	TOOLKIT_API virtual void DoDelete();
	
	//@cmember
	/* Processes insert key press.*/
	TOOLKIT_API virtual void DoInsert(LPCTSTR pcsz);
	
	//@cmember
	/* Erases the control background.*/
	TOOLKIT_API virtual void EraseBackground(CDC* pDC);
	
	//@cmember
	/* Stores data for undo operation.*/
	TOOLKIT_API virtual void SaveDataForUndo(LPCTSTR p = NULL, int iCaret = -1);
	
	//@cmember
	/* Begins edit mode.*/
	TOOLKIT_API virtual void StartEdit(int iCaretPos);
	
	//@cmember
	/* Ends edit mode.*/
	TOOLKIT_API virtual void StopEdit();
	
	//@cmember
	/* Draws a vertical decimal separator on the control.*/
	TOOLKIT_API virtual void DrawDecimalSeparatorLine(CDC& DC, int x);
	
	//@cmember
	/* Handles a minus sign key press.*/
	TOOLKIT_API virtual void HandleNegativeSignKey();
	
	//@cmember
	/* Toggles overstrike mode state.*/
	TOOLKIT_API virtual void ToggleOverstrikeMode();

protected:

	//@cmember
	/* Displays calculator.*/
	TOOLKIT_API virtual BOOL ShowCalculator();
	
	// Override of the SECDropEdit for handling the button click.
	//@cmember
	/* Method called when the button has been clicked.*/
	inline virtual void OnClicked() { ShowCalculator(); }

public:

	// Handlers provided by ClassWizard.

	//{{AFX_MSG(SECCurrencyEdit)
	
	// access Overrides

	// Called when Windows or an application makes a request to repaint.
	TOOLKIT_API afx_msg void OnPaint();
	
	// Called when the user releases the right mouse button.
	TOOLKIT_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	// Called after gaining the input focus.
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	
	// Called when the user presses the left mouse button.
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	// Called immediately before losing the input focus. 
	TOOLKIT_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	
	// Called when a nonsystem key is pressed.
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// Override to control the particular types of input to process.
	TOOLKIT_API afx_msg UINT OnGetDlgCode();
	
	// Called when a keystroke translates to a nonsystem character. 
	TOOLKIT_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// Called when a system key is depressed.
	TOOLKIT_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// Called when the user double-clicks the left mouse button. 
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	// Called when the user releases teh left mouse button.
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	// Called when the mouse cursor moves. 
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	//}}AFX_MSG

	// Edit control message handlers not provided by ClassWizard.

	// Called to process the EM_CANUNDO message.
	TOOLKIT_API afx_msg LRESULT OnCanUndo(WPARAM wParam, LPARAM lParam);
	
	// Called to process the EM_EMPTYUNDOBUFFER message.
	TOOLKIT_API afx_msg LRESULT OnEmptyUndoBuffer(WPARAM wParam, LPARAM lParam);

	/* Called when an application changes the enabled state of */
	// the CWnd object. 
	TOOLKIT_API afx_msg void OnEnable(BOOL bEnable);

	// Called to process the EM_GETSEL message.
	TOOLKIT_API afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	
	// Called to process the EM_SETREADONLY message.
	TOOLKIT_API afx_msg LRESULT OnSetReadOnly(WPARAM wParam, LPARAM lParam);
	
	// Called to process the EM_SETSEL message.
	TOOLKIT_API afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	
	// Called to process the EM_SETMARGINS
	TOOLKIT_API afx_msg LRESULT OnSetMargins(WPARAM wParam, LPARAM lParam);

	// Standard message handlers not provided by ClassWizard.

	// Called to process the WM_GETFONT message.
	TOOLKIT_API afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_COPY message.
	TOOLKIT_API afx_msg LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_CUT message.
	TOOLKIT_API afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_PASTE message.
	TOOLKIT_API afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_SETFONT message.
	TOOLKIT_API afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_SETREDRAW message.
	TOOLKIT_API afx_msg LRESULT OnSetRedraw(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_SETTEXT message.
	TOOLKIT_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	
	// Called to process the WM_UNDO message.
	TOOLKIT_API afx_msg LRESULT OnUndo(WPARAM wParam, LPARAM lParam);

	// Command handlers for right mouse button popup menu.

	// Called to process the ID_EDIT_UNDO message.
	TOOLKIT_API afx_msg void OnEditUndo();
	
	// Called to process the ID_EDIT_COPY message.
	TOOLKIT_API afx_msg void OnEditCopy();
	
	// Called to process the ID_EDIT_CUT message.
	TOOLKIT_API afx_msg void OnEditCut();
	
	// Called to process the ID_EDIT_PASTE message.
	TOOLKIT_API afx_msg void OnEditPaste();
	
	// Called to process the ID_EDIT_CLEAR message.
	TOOLKIT_API afx_msg void OnEditClear();
	
	// Called to process the ID_EDIT_SELECT_ALL message.
	TOOLKIT_API afx_msg void OnEditSelectAll();

	// Called to paint non client area
	TOOLKIT_API afx_msg void OnNcPaint();
	

protected:
	// Non-virtual members; descendant classes may utilize these, but should 
	// not override them.

	//@access Implementation

	//@cmember
	/* Notify parent of control state change.*/
	TOOLKIT_API void NotifyParent(UINT uiCode);

	//@cmember
	/* Determines if current value is negative.*/
	inline BOOL IsNegative() const { return m_bNegative; }
	
	//@cmember
	/* Detemines if edit control has highlighted (selected) text.*/
	inline BOOL HasSel() const { return m_Sel.iStart != -1 && m_Sel.iStop != m_Sel.iStart; }
	
	//@cmember
	/* Sets the selected text.*/
	TOOLKIT_API BOOL SetSel(int iStart, int iStop);
	
	//@cmember
	/* Deselects all text in the control.*/
	inline BOOL SetSelNone() { return SetSel(-1, 0); }
	
	//@cmember
	/* Selects all text in the control*/
	inline BOOL SetSelAll() { return SetSel(0, -1); }
	
	//@cmember
	/* Returns whether text is currently being selected with the mouse.*/
	inline BOOL IsMouseSelecting() const { return m_bMouseSelect; }
	
	//@cmember
	/* Returns whether the entire number is selected.*/
	TOOLKIT_API BOOL IsEntireNumberSelected(BOOL* pbMore = NULL) const;
	
	//@cmember
	/* Returns whether overstrike mode is enabled.*/
	inline BOOL IsOverstrikeEnabled() const { return m_bOverstrike; }	
	
	//@cmember
	/* Returns the background color of the edit control. */
	TOOLKIT_API COLORREF GetBackgroundColor() const;
	
	//@cmember
	/* Returns the text color for the edit control.*/
	TOOLKIT_API COLORREF GetTextColor() const;
	
	//@cmember
	/* Points to the caret’s position. */
	TOOLKIT_API int PointToCaretPos(const CPoint& pt);
	
	//@cmember
	/* Calculates the rectangle for text in the edit control.*/
	TOOLKIT_API void CalculateTextRect(CRect& rc);
	
	//@cmember
	/* Makes an insertion in the edit control.*/
	inline void DoInsert(TCHAR c) { DoInsert(CString(c)); }
	
	//@cmember
	/* Gets text selected in the edit control.*/
	TOOLKIT_API void GetSelectedText(CString& s) const;
	
	//@cmember
	/* Relocates the caret in the edit control.*/
	TOOLKIT_API void MoveCaret(int iChar, BOOL bUpdateSel = FALSE);
	
	//@cmember
	/* Redraws the core currency formatting on the specified display device context.*/
	TOOLKIT_API void PaintingCore(CDC& DC);
	
	//@cmember
	/* Redraws queued data.*/
	inline void QueueRedraw(BOOL bEraseBackground = TRUE) { if (m_bRedraw) InvalidateRect(NULL, bEraseBackground); }
	
	//@cmember
	/* Replaces the currently selected string with the specified text. */
	TOOLKIT_API void ReplaceSelString(LPCTSTR pcszNew, CString& str);
	
	//@cmember
	/* Sets text that does not require parsing.*/
	TOOLKIT_API void SetWindowTextNoParse(LPCTSTR p);
	
	//@cmember
	/* Positions the caret near the number.*/
	TOOLKIT_API void MoveCaretToNumber();
	
	//@cmember
	/* Sets the value of the number in the control.*/
	TOOLKIT_API void SetValue(double d, BOOL bNegative, BOOL bRedraw);

	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API LRESULT OnThemeChanged();
	#endif

	// Data structure used for maintaining selection details.
	// Two special settings should be noted: 0, -1 means select 
	// all and -1, 0 means no selection.

	typedef struct tagSelData
	{
		int iStart, iStop;
		tagSelData() : iStart(-1), iStop(0) {}
		tagSelData(const tagSelData& s) :
			iStart(s.iStart), iStop(s.iStop) {}
		void Set(int i, int j) { iStart = i; iStop = j; }
		void Clear() { iStart = -1; iStop = 0; }
		void Normalize()
		{
			int iTmp;
			if (iStart > iStop)
			{
				iTmp = iStop;
				iStop = iStart;
				iStart = iTmp;
			}
		}
		tagSelData& operator=(const tagSelData& rhs)
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
		tagUndoData& operator=(const tagUndoData& rhs)
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

	//@access Protected data members

	//@cmember
	/* Is the data value negative?*/
	BOOL m_bNegative;
	
	//@cmember
	/* Undo buffer has something?*/
	BOOL m_bCanUndo;		
	
	//@cmember
	/* Parse value on WM_SETTEXT?*/
	BOOL m_bParseOnSetText;
	
	//@cmember
	/* Is redraw allowed?*/
	BOOL m_bRedraw;
	
	//@cmember
	/* Are we mouse selecting?*/
	BOOL m_bMouseSelect;
	
	//@cmember
	/* Is overstrike mode enabled?*/
	BOOL m_bOverstrike;
	
	//@cmember
	/* Undo buffer*/
	UNDODATA m_Undo;
	
	//@cmember
	/* Numeric value*/
	double m_dValue;
	
	//@cmember
	/* Current format settings*/
	Format* m_pFormat;
	
	//@cmember
	/* Font set via WM_SETFONT*/
	HFONT m_hFont;
	
	//@cmember
	/* Caret character position*/
	int m_iCaretPos;
	
	//@cmember
	/* 	Selection information*/
	SELDATA m_Sel;
	
	//@cmember
	/* 	The right margin in pixels.*/
	UINT m_uiRightMargin;
	
	//@cmember
	/* 	The left margin in pixels.*/
	UINT m_uiLeftMargin;

protected:
	HTHEME m_hEditTheme;

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// WIN32

#endif	// __CURREDIT_H__

