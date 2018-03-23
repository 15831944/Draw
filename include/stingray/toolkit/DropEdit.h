///////////////////////////////////////////////////////////////////////////////
// DropEdit.h : header file for SECDropEdit - subclassed edit with little
//		drop down button.
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
//		Author:		Don			20/01/97
//


#ifndef __DROPEDIT_H__
#define __DROPEDIT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// SECDropEdit window
//
// Adds a combo like drop down button to an edit control
//

/////////////////////////////
// AutoDuck tag block block for SECDropEdit 

//@doc SECDropEdit
//@mdata CRect    | SECDropEdit | m_btnRect | The window rect of the button 
// (in our parents client coordinates)
//@xref <c SECDropEdit>

//@doc SECDropEdit
//@mdata CBitmap  | SECDropEdit | m_bmp | Bitmap drawn on face of button
//@xref <c SECDropEdit>

//@doc SECDropEdit
//@mdata LPCTSTR  | SECDropEdit | m_lpszBmpName | filename of the bitmap
//@xref <c SECDropEdit>

//@doc SECDropEdit
//@mdata WORD     | SECDropEdit | m_wState | Current state
//@xref <c SECDropEdit>

//@doc SECDropEdit
//@mdata WORD     | SECDropEdit | m_wLeftBorder | Left hand Gap between bitmap and border
//@xref <c SECDropEdit>

//@doc SECDropEdit
//@mdata WORD     | SECDropEdit | m_wRightBorder | Right hand Gap between bitmap and border
//@xref <c SECDropEdit>

// adinsert AutoDuck insertion point for SECDropEdit 
//@doc SECDropEdit 
//@class The SECDropEdit class adds a combo-like drop-down button to an 
// edit control.
//@comm This class is used with SECCurrencyEdit and Format to implement an edit 
// control for entering and displaying custom-formatted currency data.
//
// See the CURRENCY sample in the \SAMPLES\TOOLKIT\STANDARD\CONTROLS\CURRENCY 
// directory for a demonstration of this class.
//
//@base public | CEdit
class SECDropEdit : public CEdit
{
	TOOLKIT_DECLARE_DYNAMIC(SECDropEdit)

	//@access Creation/Initialization
public:
	//@cmember
	/* Constructs a SECDropEdit object.*/
	TOOLKIT_API SECDropEdit();

	//@cmember
	/* Creates a window and attaches it to the drop edit object.*/
	TOOLKIT_API virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	
	//@cmember
	/* Creates a child window with extended attributes and */
	// attaches it to the drop edit object.
	TOOLKIT_API virtual BOOL CreateEx(DWORD dwExStyle,DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	//@cmember
	/* Attaches an existing edit control to the drop edit object.*/
	TOOLKIT_API BOOL AttachEdit(int nCtlID, CWnd* pParentWnd);

	//@access Attributes
public:
	
	//@cmember
	/* Manipulates the alignment mode (within the edit control).*/
	TOOLKIT_API void SetRightAlign(BOOL bRightAlign = TRUE);
	
	//@cmember
	/* Indicates whether drop-down button is right-aligned within the edit control.*/
	TOOLKIT_API BOOL IsRightAligned() const;

	//@cmember
	/* Manipulates the border settings.*/
	TOOLKIT_API void SetBorder(WORD wLeftBorder, WORD wRightBorder);
	
	//@cmember
	/* Retrieves the border settings.*/
	TOOLKIT_API DWORD GetBorders() const;

public:
	
	//@access Operations

	// Methods to set/get the bitmap on the button
	//@cmember
	/* Sets bitmap on the button.*/
	TOOLKIT_API BOOL SetBitmap(UINT nBmpID);
	
	//@cmember
	/* Sets bitmap on the button.*/
	TOOLKIT_API BOOL SetBitmap(LPCTSTR lpszBmpName);
	
	//@cmember
	/* Removes the button.*/
	TOOLKIT_API BOOL SetBitmap();						// Removes button
	
	//@cmember
	/* Sets bitmap on the button.*/
	TOOLKIT_API HBITMAP GetBitmap() const;

	//@cmember
	/* Forces a redraw of the button.*/
	TOOLKIT_API void InvalidateBtn();

protected:

	//@access Overridable
 
	//@cmember
	/* Called when the button has been clicked.*/
	TOOLKIT_API virtual void OnClicked();

	//@cmember
	/* Draws the button.*/
	TOOLKIT_API virtual void DrawBtn(CDC& dc, CRect r);

	//@access Overrides
#ifndef UNDER_CE
	//@cmember
	/* Called when the size and position of the client area needs */
    // to be calculated.
	TOOLKIT_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
#endif //UNDER_CE	
	//@cmember
	/* Called when the user presses the left mouse button while the */
	// cursor is within a nonclient area of the CWnd object. 
	TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	
	//@cmember
	/* Called when the user releases teh left mouse button.*/
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	//@cmember
	/* Called after the CWnd object has been moved.*/
	TOOLKIT_API afx_msg void OnMove(int x, int y);

	//@cmember
	/* Called when the mouse cursor moves. */
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	//@cmember
	/* Called every time the mouse is moved.*/
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif	
	//@cmember
	/* Called when the nonclient area needs to be painted.*/
	TOOLKIT_API afx_msg void OnNcPaint();
	
	//@cmember
	/* Called to inform CWnd to cancel any internal mode. */
	TOOLKIT_API afx_msg void OnCancelMode();
	
	//@cmember
	/* Called when a change is made in the system color setting. */
	TOOLKIT_API afx_msg void OnSysColorChange();
	
	//@cmember
	/* Called when an application changes the enabled state of */
	// the CWnd object. 
	TOOLKIT_API afx_msg void OnEnable(BOOL bEnable);
	
	//@cmember
	/* Called when a nonsystem key is pressed.*/
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	//@cmember
	/* Called when a system key is depressed.*/
	TOOLKIT_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	//@cmember
	/* Called to process messages.*/
	TOOLKIT_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//@cmember
	TOOLKIT_API afx_msg void OnNcMouseMove( UINT nHitTest, CPoint point );

	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API LRESULT OnThemeChanged();
	#endif

public:

	//@cmember
	/* Determines whether the given point (in screen or client */
	// coordinates) is a hit on the button.
	TOOLKIT_API virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;

// Implementation
public:
	TOOLKIT_API virtual ~SECDropEdit();

#ifdef _DEBUG
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
	TOOLKIT_API virtual void AssertValid() const;
#endif

protected:
	// Implementation, data members.
	//@cmember
	/* The window rect of the button (in our*/
	// parents client coordinates)
	CRect   m_btnRect;

	//@cmember
	/* Bitmap drawn on face of button*/
	CBitmap m_bmp;

	//@cmember
	/* Resource ID of above bitmap*/
	LPCTSTR m_lpszBmpName;

	//@cmember
	/* Current state*/
	WORD    m_wState;

	//@cmember
	/* Left hand Gap between bitmap and border*/
	WORD    m_wLeftBorder;

	//@cmember
	/* Right hand Gap between bitmap and border*/
	WORD    m_wRightBorder;

	// Bit settings in m_wState
	enum States
	{
		Pressed    = 0x0001,		// Button is currently down	
		Capture    = 0x0002,		// We are tracking a left click on the button
		RightAlign = 0x0004,		// The button is right aligned within the edit
		Hot        = 0x0008			// The button is hot (under mouse cursor)
	};

	//@cmember
	/* Theme Handle for Button */
	HTHEME m_hButtonTheme;

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

// Function to take the given rectangle in the given dc and draw it disabled.
TOOLKIT_API void SECDrawDisabled(CDC& dc, int x, int y, int nWidth, int nHeight);

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __DROPEDIT_H__


