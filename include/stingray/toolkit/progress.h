///////////////////////////////////////////////////////////////////////////////
// progress.h : Declaration of SECProgressCtrl
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
// Author:       Mark Isham
// Description:  Declaration of SECProgressCtrl
//

#ifndef __SECPROGRESSCTRL_H__
#define __SECPROGRESSCTRL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

#ifdef WIN32

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

// Preprocessor

// Header Includes

// Constants/Macros
// Defaults
#define SEC_PROGRESS_DEF_FGND_COLOR	RGB(0,0,128)		// dark blue
#define SEC_PROGRESS_DEF_BGND_COLOR	RGB(255,255,255)	// white

// Extended styles
#define SEC_EX_PROGRESS_VERT				0x00000001	// vertical progress ctrl		
#define SEC_EX_PROGRESS_RIGHT_TO_LEFT		0x00000010	// horizontal displays right to left
#define SEC_EX_PROGRESS_TOP_TO_BOTTOM		0x00000020	// vertical displays top to bottom
#define SEC_EX_PROGRESS_SHOWPERCENT			0x00000100	// show percent number inside bar
#define SEC_EX_PROGRESS_SHOWTEXT			0x00000200	// show text inside bar
#define SEC_EX_PROGRESS_TEXT_ALIGN_LEFT		0x00001000	// left justify shown text
#define SEC_EX_PROGRESS_TEXT_ALIGN_RIGHT	0x00002000	// right justify shown text
#define SEC_EX_PROGRESS_TEXT_ALIGN_CENTER	0x00004000	// center shown text
#define SEC_EX_PROGRESS_COMMCTRL32			0x00010000	// let CProgressCtrl paint the control
// Vista Only------------------------------------
#define SEC_EX_PROGRESS_INDETERMINATE       0x00020000  // An Indeterminate Style Progress Control
#define SEC_EX_PROGRESS_ERROR               0x00030000  // A progress control that is stopped (red)
#define SEC_EX_PROGRESS_PAUSED              0x00040000  // A progress control that is paused (blue)
#define SEC_EX_PROGRESS_PARTIAL             0x00500000  // A progress control that is partial (gold)
//-----------------------------------------------

// Default config: horizontal, left-to-right, with centered percent number
#define SEC_EX_PROGRESS_DEFAULTS	SEC_EX_PROGRESS_SHOWPERCENT | SEC_EX_PROGRESS_TEXT_ALIGN_CENTER

// Types

// Forward declarations

/////////////////////////////////////////////////////////////////////////////
// SECProgressCtrl

//@doc SECProgressCtrl
//@mfunc DWORD | SECProgressCtrl | GetExStyle | Get the current progress extended styles.
//@rdesc The curent progress extended styles
//@comm See <mf SECProgressCtrl::Create> for the flags that determine the style 
// options for the control.
//@xref <c SECProgressCtrl> <mf SECProgressCtrl::Create> <mf SECProgressCtrl::SetExStyle>

//@doc SECProgressCtrl
//@mfunc void | SECProgressCtrl | OnDisplayStr | Override this to alter a progress string 
// before display.
//@xref <c SECProgressCtrl> 

//@doc SECProgressCtrl
//@mfunc void | SECProgressCtrl | GetWindowText | Gets the current progress text.
//@xref <c SECProgressCtrl> <mf SECProgressCtrl::SetWindowText>

//@doc SECProgressCtrl
//@class The SECProgressCtrl offers several enhancements to the existing progress
// control, including "smooth fill" with percentages, multidirectional progressions
// (left to right, right to left, bottom to top, or top to bottom), fully configurable
// foreground/background coloring, and custom status text with configurable fonts.  
// The progress control also offers virtual hooks for you to easily provide your own
// customizations (for example, a textured progress bar).
//
// The SECProgressCtrl can be used anywhere a CProgressCtrl can be used.  You can 
// attach to an existing CProgressCtrl control via the <mf SECProgressCtrl::AttachProgress>
//  method, or dynamically create one via the <mf SECProgressCtrl::Create> method.
//
// See the <mf SECProgressCtrl::Create> method for the flags that determine the style 
// options for the control.
//
//@base public | CProgressCtrl
class SECProgressCtrl : public CProgressCtrl
{
	TOOLKIT_DECLARE_DYNAMIC(SECProgressCtrl);

	//---------------------------------------------------------------------//
	// 						Public Interface							   //
	//---------------------------------------------------------------------//
public:

	//@access Creation/Initialization 

	//@cmember
	/* Constructs a SECProgress control object.*/
	TOOLKIT_API SECProgressCtrl();

	TOOLKIT_API virtual ~SECProgressCtrl();

	//@cmember
	/* Dynamically create a progress control.*/
	TOOLKIT_API virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
						UINT nID,DWORD dwExStyle=SEC_EX_PROGRESS_DEFAULTS);

	//@cmember
	/* Attach to an existing progress control.*/
	TOOLKIT_API virtual BOOL AttachProgress(int nCtlID,CWnd* pParentWnd);

	//@access Attributes

	//@cmember
	/* Set progress value range for appropriate completion percentage.*/
	TOOLKIT_API virtual void SetRange(ULONG ulLower,ULONG ulUpper);

	//@cmember
	/* Set current progress position.*/
	TOOLKIT_API virtual ULONG SetPos(ULONG ulPos,BOOL bYield=TRUE);

	//@cmember
	/* Increment current progress position.*/
	TOOLKIT_API virtual ULONG OffsetPos(ULONG ulPos,BOOL bYield=TRUE);

	//@cmember
	/* Set step size for "StepIt" function call.*/
	TOOLKIT_API virtual ULONG SetStep(ULONG ulStep);

	//@cmember
	/* Set progress control foreground (bar) and background colors.*/
	TOOLKIT_API virtual void SetColors(COLORREF fgnd=SEC_PROGRESS_DEF_FGND_COLOR,
						   COLORREF bgnd=SEC_PROGRESS_DEF_BGND_COLOR);

	//@cmember
	/* Set the font for progress text.*/
	TOOLKIT_API virtual void SetFont(CFont* pFont=(CFont *)NULL,BOOL bRedraw=TRUE);

	//@cmember
	/* Set the current progress text.*/
	TOOLKIT_API virtual void SetWindowText(LPCTSTR lpszNewText=(const TCHAR *)NULL);

	//@cmember
	/* Get the current progress text.*/
	inline virtual void GetWindowText(CString& strText) { strText=m_strProgressText; }

	//@cmember
	/* Set the progress extended styles from the SEC_EX_PROGRESS_* flags.*/
	TOOLKIT_API void SetExStyle(DWORD dwExNewStyle);

	//@cmember
	/* Get the current progress extended styles.*/
	inline DWORD GetExStyle() { return m_dwExStyle; }

	//@access Operations

	//@cmember
	/* Step the progress up one increment of the step size (set by SetStep).*/
	TOOLKIT_API virtual ULONG StepIt(BOOL bYield=TRUE);

	//@cmember
	/* Reset the progress indicator to origin.*/
	TOOLKIT_API virtual void ResetProgress();

	//@cmember
	/* AutoStep the timer at a regular interval.*/
	TOOLKIT_API virtual BOOL StepOnTimer(UINT nInterval);	

	//@cmember
	/* AutoStep the timer at the max interval. */
	TOOLKIT_API virtual BOOL StartTimer();

	//@cmember
	/* Start and Stop the Timer for Indeterminate modes. */
	TOOLKIT_API virtual void SetTimerFlag(BOOL bEnable){m_bStartTimer = bEnable;}
	

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECProgressCtrl)
	//}}AFX_VIRTUAL

	// Public member variables

	//---------------------------------------------------------------------//
	// 						Protected Overridables						   //
	//---------------------------------------------------------------------//
protected:

	//@access Overridable

	//@cmember
	/* Progress control is initializing.*/
	TOOLKIT_API virtual BOOL OnInitProgress();

	// override these to perform your own bar painting (perhaps a texture?)

	//@cmember
	/* Paint the filled progress bar image.*/
	TOOLKIT_API virtual void OnPaintBarFill(CDC* pDC,CRect rectFill);

	//@cmember
	/* Paint the empty "unused" portion of the progress bar.*/
	TOOLKIT_API virtual void OnPaintBarEmpty(CDC* pDC,CRect rectEmpty);

	//@cmember
	/* Paint the progress text, if any.*/
	TOOLKIT_API virtual void OnPaintBarText(CDC* pDC,float fPctComplete,CRect rectEmpty,CRect rectFilled);

	//@cmember
	/* Override this to alter a progress string before display.*/
	inline virtual void OnDisplayStr(CString& strToDisplay) { strToDisplay; }

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//

protected:
	// Implementation member functions

	//@cmember
	/* Paints the progress control.*/
	TOOLKIT_API virtual void DoPaint(CPaintDC* pdc);

	//@cmember
	/* Calculates the filled/empty rectangles for the progress control.*/
	TOOLKIT_API virtual BOOL CalcProgressRects(float fPct,CRect& rectFilled,CRect& rectEmpty);

	//@cmember
	/* Paints the progress bar and text.*/
	TOOLKIT_API virtual BOOL PaintProgressBarAndText(float fPctComplete,CRect rectFilled,
										 CRect rectEmpty,CDC* pdc);
	
	//@cmember
	/* Calculates the percent complete.*/
	TOOLKIT_API virtual float CalcPercentComplete();

	TOOLKIT_API void YieldPaintMessages();

	// Implementation member variables
	ULONG		m_ulCurrentPos;
	ULONG		m_ulStep;
	ULONG		m_ulRangeLower,m_ulRangeUpper;
	COLORREF	m_FgndColor,m_BgndColor;
	CFont*		m_pFont;
	BOOL		m_bShowWindow;
	BOOL		m_bWndExists;
	CString		m_strProgressText;
	DWORD		m_dwExStyle;
	CRect		m_rectClient;
	SEC_UINT	m_nTimerID;
	HTHEME		m_hProgressTheme;
	BOOL        m_bStartTimer;

	// Generated message map functions
	//{{AFX_MSG(SECProgressCtrl)
	TOOLKIT_API afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnSize(UINT nType,int cx,int cy);
	TOOLKIT_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API LRESULT OnThemeChanged();
	#endif
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // WIN32

#endif //__SECPROGRESSCTRL_H__

