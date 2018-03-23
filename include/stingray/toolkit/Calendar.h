///////////////////////////////////////////////////////////////////////////////
// Calendar.h : header file for the SECCalendar custom control
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
// CHANGELOG:
//
//    PCB	01/19/96	Started
//
//

// Don's changes:
//  (1) Added SEC_PCS_ALIGNBOTTOMLEFT
//  (2) Added GetSelectedDateValue
//  (3) Removed & from date/time passed into SelectDate

#ifndef __SEC_CALENDAR_H__
#define __SEC_CALENDAR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SEC_CALTITLE_H__
#include "toolkit\CalTitle.h"
#endif //__SEC_CALTITLE_H__

#ifndef __SEC_DAYBAR_H__
#include "toolkit\DayBar.h"
#endif //__SEC_DAYBAR_H__

#ifndef __SEC_DAYBOX_H__
#include "toolkit\DayBox.h"
#endif //__SEC_DAYBOX_H__

#include <StingrayExportDefs.h>

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

#define SEC_CAL_SCHEMA					0x0100

// Forward Declarations
class SECCalendar;


// Behavior options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define SECBM_AUTOSIZE_FONT				0x00010000L
#define SECBM_AUTOSIZE_RECT				0x00020000L 
#define SECBM_SINGLE_DATE				0x00040000L
#define SECBM_MONTH_BUTTONS				0x00080000L
#define SECBM_YEAR_BUTTONS				0x00100000L
#define SECBM_KEYBOARD_CONTROL			0x00200000L
#define SECBM_MONTH_FROZEN				0x00400000L
#define SECBM_AUTO_HIDE					SECPBM_AUTOCLOSEABLE
#define SECBM_LBUTTONTRACK				0x01000000L

// Not yet implemented.
#define SECBM_RESIZEABLE				0x00800000L

// Draw options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define SECDM_FULL_MONTH_NAMES			0x10000000L
#define SECDM_FULL_DAY_NAMES			0x20000000L
  
// Styles for SECPopupCalendar
#define SEC_PCS_ALIGNBOTTOMLEFT			0x0001		// Align calendar at bottom
													// left of supplied rect.

// Calendar-control-to-parent messages.
#define SEC_DATESELECTED				(WM_USER+0x0200)
#define SEC_HIGHLIGHTLISTCHANGED		(WM_USER+0x0201)
#define SEC_OK							(WM_USER+0x0202)
#define SEC_CANCEL						(WM_USER+0x0203)

// Defaults
#define DEFAULT_DAY_BKGD_COLOR			COLOR_WINDOW	
#define DEFAULT_DAY_PRE_POST_BKGD_COLOR	COLOR_BTNSHADOW			
#define DEFAULT_DAYBAR_BKGD_COLOR		COLOR_BTNFACE
#define DEFAULT_DAYBAR_FGD_COLOR		COLOR_BTNTEXT
#define DEFAULT_TITLE_BKGD_COLOR		COLOR_ACTIVECAPTION
// Change the title color. Otherwise the title may disappear at high contrast color modes.
//#define DEFAULT_TITLE_FGD_COLOR			COLOR_CAPTIONTEXT
#define DEFAULT_TITLE_FGD_COLOR			COLOR_WINDOWTEXT
//
#define DEFAULT_LINES_COLOR				COLOR_BTNTEXT
#define DEFAULT_SELECTED_COLOR			COLOR_BKGD
#define DEFAULT_HIGHLIGHTED_COLOR		COLOR_HIGHLIGHT
#define DEFAULT_TEXT_COLOR				COLOR_WINDOWTEXT
#define DEFAULT_GRAYTEXT_COLOR			COLOR_GRAYTEXT

#define SECBM_DEFAULT_VIEW_BEHAVIOR \
			SECPBM_DEFAULT_VIEW_BEHAVIOR | SECBM_AUTOSIZE_FONT | \
			SECBM_YEAR_BUTTONS |SECBM_MONTH_BUTTONS | SECBM_KEYBOARD_CONTROL 

#define SECBM_DEFAULT_DIALOG_BEHAVIOR SECPBM_DEFAULT_DIALOG_BEHAVIOR | \
		SECBM_AUTOSIZE_FONT | SECBM_YEAR_BUTTONS | SECBM_MONTH_BUTTONS | \
		SECBM_KEYBOARD_CONTROL 
									  
#define SECBM_DEFAULT_POPUP_BEHAVIOR SECPBM_DEFAULT_DIALOG_BEHAVIOR | \
			SECBM_AUTOSIZE_FONT | SECBM_YEAR_BUTTONS | SECBM_MONTH_BUTTONS | \
			SECBM_KEYBOARD_CONTROL | SECBM_AUTO_HIDE

#define SECDM_DEFAULT_VIEW_DRAW SECPDM_DEFAULT_VIEW_DRAW | \
			SECDM_FULL_MONTH_NAMES | SECDM_FULL_DAY_NAMES
#define SECDM_DEFAULT_DIALOG_DRAW SECPDM_DEFAULT_DIALOG_DRAW | \
			SECDM_FULL_MONTH_NAMES
#define SECDM_DEFAULT_POPUP_DRAW SECPDM_DEFAULT_POPUP_DRAW

#define SECDM_DEFAULT_VIEW_PPDRAW SECPDM_DEFAULT_VIEW_PPDRAW
#define SECDM_DEFAULT_DIALOG_PPDRAW SECPDM_DEFAULT_DIALOG_PPDRAW
#define SECDM_DEFAULT_POPUP_PPDRAW SECPDM_DEFAULT_POPUP_PPDRAW



#define SECC_NUMDAYS					42				/* 7 days x 6 wks. */
#define SECC_DEFAULT_FONT				_T("Arial")

// Geometry of the Calendar
#define VD_TOP							0.000
#define VD_TITLE						0.175
#define	VD_WK_0							0.250
#define VD_WK_ARRAY						{ 0.250,0.375,0.500,0.625,\
												0.750,0.875,1.000}

#define HD_LEFT							0.000
#define HD_TITLE						1.000
#define HD_DAYBAR						1.000
#define HD_DAY_ARRAY					{0.000, 0.143, 0.286, 0.429,\
										 0.572, 0.715, 0.858, 1.000}

/////////////////////////////////////////////////////////////////////////////
// SECCalendar:
// See Calendar.cpp for the implementation of this class
//

/////////////////////////////
// AutoDuck tag block for SECCalendar 


// adinsert AutoDuck insertion point for SECCalendar 
//@doc SECCalendar 
//@class SECCalendar implements a standard calendar control which can be 
// used for date entry, as well as date representation.  Through the use of 
// member functions, days on the calendar can be highlighted and selected.  
// An SECCalendar instance can be embedded into a dialog, or can be implemented 
// as a popup control through the derived class <c SECPopupCalendar>.  SECCalendar 
// can be embedded into a CView as well as a CDialog.  Since it is derived from 
// CWnd, it can usually be used anywhere a Cwnd can.
// 
//@comm SECCalendar maintains an internal page date as well as a selected date.  The 
// page date corresponds to the day currently being viewed.  So, if the page date 
// was specified as May 13th 1993, the month of May would be shown with the current 
// date.  If the user advanced the calendar by a month, the current page date would 
// also be advanced internally by one month to June 13th 1993.  The only feedback 
// the end user receives is that the month of the current page date is shown in the 
// calendar window.
//
// SECCalendar also maintains a single selected date internally which can be manipulated 
// even if it is not currently being displayed in the current page.  In other words, 
// the current page might be June 1993, while the selected date might be all the way 
// back on May 13th 1975.  The selected date can be advanced through member functions 
// behind the scenes while the current page remains at June 1993.
//
// The overall behavior of an SECCalendar instance is controlled through a number of 
// behavior and drawing options.  The calendar month being drawn consists of carryover 
// days from the previous month as well as days from the next month.  For example, 
// if the first day of the displayed month fell on a Tuesday, that would mean that two 
// carryover days from the previous month would be displayed for Sunday and Monday.  
// Similarly, days for the next month are displayed if space permits.  Behavior for 
// all displayed days is modified at creation time, or dynamically using the following 
// member functions: <mf SECCalendar::SetPrePostDrawMode> <mf SECCalendar::GetPrePostDrawMode>
//  <mf SECCalendar::SetDrawMode>  <mf SECCalendar::GetDrawMode>  <mf SECCalendar::SetBehaviorMode>
//  <mf SECCalendar::GetBehaviorMode>
//
// The CALTEST sample in the \SAMPLES\TOOLKIT\STANDARD\CONTROLS\CALENDAR directory demonstrates how 
// SECCalendar and <c SECPopupCalendar> are used.
//@base public | CWnd
class SECCalendar : public CWnd
{
	TOOLKIT_DECLARE_SERIAL( SECCalendar ) 

	//@access Creation/Initialization
public:
	
	//@cmember
	/* Creates a SECCalendar object.*/
	TOOLKIT_API SECCalendar();
	
	//@cmember
	/* Creates a child window and attaches it to the parent window passed in.*/
	TOOLKIT_API virtual BOOL Create(	DWORD dwStyle,
							CRect &Rect, 
							CWnd *pWndParent, 
							UINT nID,
							CCreateContext* pContext = NULL );

	//@access Attributes

public:

	//@cmember
	/* Retrieves the current drawing mode of overlapping days.*/
	TOOLKIT_API long GetPrePostDrawMode( void );
	
	//@cmember
	/* Sets the drawing mode of overlapping days.*/
	TOOLKIT_API BOOL SetPrePostDrawMode( long l );
	
	//@cmember
	/* Retrieves the behavior mode of the calendar.*/
	TOOLKIT_API long GetBehaviorMode( void );
	
	//@cmember
	/* Sets the behavior mode of the calendar.*/
	TOOLKIT_API BOOL SetBehaviorMode( long m );
	
	//@cmember
	/* Gets the drawing mode of the calendar.*/
	TOOLKIT_API long GetDrawMode( void );

	//@cmember
	/* Sets the drawing mode of the calendar.*/
	TOOLKIT_API BOOL FAR SetDrawMode( long m );
	
#ifdef WIN32

	//@cmember
	/* Sets the calendar page to be displayed (32-bit only).*/
	TOOLKIT_API BOOL SetPage( const COleDateTime &calendarPage, BOOL bRedraw = FALSE );

#endif

#ifdef WIN32	

	//@cmember
	/* Retrieves the currently selected date (32-bit only)*/
	TOOLKIT_API const COleDateTime& GetSelectedDateValue( void );
	
#else

	//@cmember
	/* Retrieves the currently selected date (16-bit only)*/
	TOOLKIT_API const CTime& GetSelectedDateValue( void );

#endif

#ifdef WIN32

	//@cmember
	/* Retrieves an array of pointers to all highlighted dates. (32-bit only)*/
	TOOLKIT_API UINT GetAllHighlightedDates( COleDateTime *pDates, UINT nDates );

#endif 

	//@cmember
	/* Retrieves an array of pointers to all highlighted dates.*/
	TOOLKIT_API UINT GetAllHighlightedDates( CTime *pDates, UINT nDates );
	
	//@cmember
	/* Sets the calendar page to be displayed.*/
	TOOLKIT_API BOOL SetPage( const CTime &calendarPage, BOOL bRedraw = FALSE );
		
	//@cmember
	/* Retrieves the currently selected date.*/
	TOOLKIT_API SECDayBox* GetSelectedDate( void );
	
	//@cmember
	/* Retrieves the number of highlighted dates.*/
	TOOLKIT_API UINT GetNumHighlightedDates( void );
	
	//@cmember
	/* Retrieves the status of the automatic size font mode.*/
	TOOLKIT_API BOOL GetAutosizeFont( void );
	
	//@cmember
	/* Sets the status of the automatic size font mode.*/
	TOOLKIT_API void SetAutosizeFont( BOOL bSet );
	
	//@cmember
	/* Retrieves the status of the automatic sizing CRect mode.*/
	TOOLKIT_API BOOL GetAutosizeRect( void );
	
	//@cmember
	/* Sets the status of the automatic sizing CRect mode.*/
	TOOLKIT_API void SetAutosizeRect( BOOL bSet );
	
	//@cmember
	/* Retrieves the CRect associated with the control.*/
	TOOLKIT_API const CRect& GetControlRect( void );
	
	//@cmember
	/* Sets a new CRect for the control.*/
	TOOLKIT_API CRect SetControlRect( CRect &newRect );
	
	//@cmember
	/* Returns the status of single date selection mode.*/
	TOOLKIT_API BOOL GetSingleDate( void );
	
	//@cmember
	/* Sets the status of single date selection mode.*/
	TOOLKIT_API BOOL SetSingleDate( BOOL bTurnOn );
	
	//@cmember
	/* Retrieves the active status of the month buttons.*/
	TOOLKIT_API BOOL GetMonthButtons( void );
	
	//@cmember
	/* Sets the active status of the month buttons.*/
	TOOLKIT_API BOOL SetMonthButtons( BOOL bTurnOn );
	
	//@cmember
	/* Retrieves the active status of the year buttons.*/
	TOOLKIT_API BOOL GetYearButtons( void );
	
	//@cmember
	/* Sets the active status of the year buttons.*/
	TOOLKIT_API BOOL SetYearButtons( BOOL bTurnOn );
	
	//@cmember
	/* Retrieves the active status of keyboard control.*/
	TOOLKIT_API BOOL GetKeyboardControl( void );
	
	//@cmember
	/* Sets the active status of keyboard control.*/
	TOOLKIT_API BOOL SetKeyboardControl( BOOL bTurnOn );
	
	//@cmember
	/* Returns nonzero (true) if the month currently displayed is frozen (can’t be changed).*/
	TOOLKIT_API BOOL GetMonthFrozen( void );
	
	//@cmember
	/* Freezes the month currently being displayed by the calendar control (the month can’t be changed).*/
	TOOLKIT_API BOOL SetMonthFrozen( BOOL bMakeFrozen );
	
	//@cmember
	/* Retrieves the active status of whether the calendar control is automatically hidden.*/
	TOOLKIT_API BOOL GetAutoHide( void );
	
	//@cmember
	/* Sets the active status indicating that the calendar control is automatically hidden.*/
	TOOLKIT_API BOOL SetAutoHide( BOOL bHideAutomatically );
	

	// Retrieves the alignment flag.
	TOOLKIT_API UINT GetAlignmentFlag( void );
	
	// Sets the alignment flag.
	TOOLKIT_API UINT SetAlignmentFlag( UINT lNewFlag );
	
	//
	TOOLKIT_API CWnd *GetNotifyWnd( void );
	
	//
	TOOLKIT_API void SetNotifyWnd( CWnd *pWnd );
	
	//@cmember
	/* Retrieves the color of the calendar text.*/
	TOOLKIT_API COLORREF GetTextColor( void );
	
	//@cmember
	/* Sets the color of the calendar text.*/
	TOOLKIT_API COLORREF SetTextColor( COLORREF newColor );
	
	//@cmember
	/* Retrieves the first day of the week.*/
	TOOLKIT_API int GetFirstDayOfWeek() const;
	
	//@cmember
	/* Sets the first day of the week.*/
	TOOLKIT_API void SetFirstDayOfWeek(int nNewFirstDay, BOOL bRedraw = FALSE);

	// Provide custom color settings.
	//@cmember
	/* Sets the color of the calendar text.*/
	TOOLKIT_API void SetCalendarColor(COLORREF newTextClr,
							COLORREF newDayBarTextClr,
							COLORREF newTitleTextClr,
							COLORREF newGrayTextClr);

	//@cmember
	/* Resets the color of the calendar text to default values.*/
	TOOLKIT_API void ResetCalendarColor();

public:
	//@access Operations

	TOOLKIT_API void Serialize( CArchive &ar );

	//@cmember
	/* Advances the calendar page date by one day.*/
	TOOLKIT_API virtual BOOL AdvanceDay( BOOL bSelectionFollows = TRUE );

	//@cmember
	/* Decrements the day being viewed by one.*/
	TOOLKIT_API virtual BOOL RetreatDay(  BOOL bSelectionFollows = TRUE );

	//@cmember
	/* Advances the page being viewed by one week.*/
	TOOLKIT_API virtual BOOL AdvanceWeek( BOOL bSelectionFollows = TRUE );

	//@cmember
	/* Decrements the day being viewed by one week.*/
	TOOLKIT_API virtual BOOL RetreatWeek(  BOOL bSelectionFollows = TRUE );

	//@cmember
	/* Advances the page being viewed by one month.*/
	TOOLKIT_API virtual BOOL AdvanceMonth( BOOL bSelectionFollows = FALSE );

	//@cmember
	/* Decrements the day being viewed by one month.*/
	TOOLKIT_API virtual BOOL RetreatMonth(  BOOL bSelectionFollows = FALSE );

	//@cmember
	/* Advances the page being viewed by one year.*/
	TOOLKIT_API virtual BOOL AdvanceYear(  BOOL bSelectionFollows = FALSE );

	//@cmember
	/* Decrements the day being viewed by one year.*/
	TOOLKIT_API virtual BOOL RetreatYear(  BOOL bSelectionFollows = FALSE );

#ifdef WIN32

	// 
	TOOLKIT_API virtual BOOL DeltaSelection( COleDateTimeSpan &ts );

	//
	TOOLKIT_API virtual BOOL DeltaPage( COleDateTimeSpan &ts );

	//@cmember
	/* Sets the highlighted state for the date passed in.*/
	TOOLKIT_API virtual	BOOL HighlightDate( COleDateTime &date, BOOL bSet );

	//@cmember
	/* Sets the selection state of the date passed in.*/
	TOOLKIT_API virtual	BOOL SelectDate( COleDateTime date, BOOL bSet );

	//@cmember
	/* Toggles the selection status of the date passed in.*/
	TOOLKIT_API virtual	BOOL ToggleSelectDate( COleDateTime &date );

	//@cmember
	/* Toggles the highlighted status of the date passed in. */
	TOOLKIT_API virtual	BOOL ToggleHighlightDate( COleDateTime &date );

	//@cmember
	/* Sets the highlight color for the date passed in.*/
	TOOLKIT_API virtual COLORREF SetHighlightColor( COleDateTime &date, COLORREF newColor );
#endif

	//
	TOOLKIT_API virtual BOOL DeltaSelection( CTimeSpan &ts );

	//
	TOOLKIT_API virtual BOOL DeltaPage( CTimeSpan &ts );

	//@cmember
	/* Sets the highlighted state for the date passed in.*/
	TOOLKIT_API virtual	BOOL HighlightDate( CTime &date, BOOL bSet );

	//@cmember
	/* Sets the selection state of the date passed in.*/
	TOOLKIT_API virtual	BOOL SelectDate( CTime date, BOOL bSet );

	//@cmember
	/* Toggles the selection status of the date passed in.*/
	TOOLKIT_API virtual	BOOL ToggleSelectDate( CTime &date );

	//@cmember
	/* Toggles the highlighted status of the date passed in. */
	TOOLKIT_API virtual	BOOL ToggleHighlightDate( CTime &date );

	//@cmember
	/* Sets the highlight color for the date passed in.*/
	TOOLKIT_API virtual COLORREF SetHighlightColor( CTime &date, COLORREF newColor );
	
protected:

	TOOLKIT_API void PurgeDateList( void );

	//@access Overridable
		
	TOOLKIT_API virtual BOOL IsDisplayableDate( int year, int month, int day );

public:

	//@cmember
	/* Initializes the colors for the calendar.*/
	TOOLKIT_API virtual void InitColors();

	// access Overrides

	//{{AFX_MSG(SECCalendar)
	// Called when the calendar windows makes a request to repaint.
	TOOLKIT_API afx_msg void OnPaint();
	
	// Called when the user clicks the OK button (the button with an ID of IDOK).
	TOOLKIT_API afx_msg LRESULT OnOK(WPARAM u, LPARAM l);

#ifndef UNDER_CE	
	// Called every time the mouse is moved.
#if _MFC_VER >= 0x0800 // Visual Studio 2005 (as of CTP August 2005)
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);	
#else
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
#endif //UNDER_CE (WindowsCE)

	// Calls when the user clicks the Cancel button the ESC key dialog box. 
	TOOLKIT_API afx_msg LRESULT OnCancel(WPARAM u, LPARAM l);	
	
	// Called when a nonsystem key is pressed.
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// Called when the user double-clicks the left mouse button. 
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	// Called when the user presses the left mouse button.
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	// Called when the user releases teh left mouse button.
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	// Called when the mouse cursor moves. 
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	// Called to inform CWnd to cancel any internal mode. 
	TOOLKIT_API afx_msg void OnCancelMode();
#ifndef UNDER_CE
	
	// Called when the user presses the right mouse button.
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
#endif //UNDER_CE (WindowsCE)	
	TOOLKIT_API afx_msg void OnNextYear(); 
	
	TOOLKIT_API afx_msg void OnPrevYear(); 
	
	TOOLKIT_API afx_msg void OnNextMonth();
	
	TOOLKIT_API afx_msg void OnPrevMonth();
	
	// Called when a change is made in the system color setting. 
	TOOLKIT_API afx_msg void OnSysColorChange();	
	//}}AFX_MSG

// Implementation
public:

	TOOLKIT_API virtual	~SECCalendar( );

protected:

	TOOLKIT_API void TextCenteredInRect( CDC *pDC, 
							 CRect theRect, 
							 COLORREF clrFgnd, 
							 COLORREF clrBkgd,
							 CString& strText);

#ifdef WIN32
	TOOLKIT_API virtual void NormalizeDate( COleDateTime &date );
	TOOLKIT_API BOOL DateFoundInList( COleDateTime date );
	TOOLKIT_API BOOL RemoveDateFromList( COleDateTime date );
	TOOLKIT_API BOOL AddDateToList( COleDateTime date );
#else
	TOOLKIT_API virtual void NormalizeDate( CTime &date );
	TOOLKIT_API BOOL DateFoundInList( CTime date );
	TOOLKIT_API BOOL RemoveDateFromList( CTime date );
	TOOLKIT_API BOOL AddDateToList( CTime date );
#endif
	TOOLKIT_API virtual void OnDatePegged( void );
	TOOLKIT_API virtual UINT GetClassStyle( void );
	TOOLKIT_API void AdjustFontSizes( CDC *pDC = NULL );
	TOOLKIT_API void AdjustRectSizes( CRect &r, CDC *pDC = NULL );
	TOOLKIT_API void SizeTitle( void );
	TOOLKIT_API void SizeDayBar( void );
	TOOLKIT_API void SizeDates( void );
	TOOLKIT_API virtual void InitFonts( void );
	TOOLKIT_API virtual void SetUpDateBoxes( void );
	TOOLKIT_API void PaintDates( CDC *pDC );
	
	enum deltaDate { negYear, negMonth, negDay, Day, Month, Year };
	CWnd *m_pNotifyWnd;
	CWnd *m_pParent;
	UINT m_nBevelLines;
	SECDayBar m_pnlDayBar;
	SECCalTitle m_pnlTitle;

protected:
	BOOL m_bCreated;
#ifdef _DEBUG
	TOOLKIT_API void DumpDateList( void );
#endif

#ifdef WIN32
	COleDateTime m_page;
	COleDateTime m_selection;
	COleDateTime *m_pSelection;
	COleDateTime m_phantomSelection;
#else
	CTime        m_page;
	CTime        m_selection;
	CTime        *m_pSelection;
	CTime        m_phantomSelection;
#endif

	SECDayBox m_day[SECC_NUMDAYS];
	SECDayBox *m_pSelectedDay;

	UINT	m_nOpMode;
	UINT	m_nAlignment;

	BOOL	m_bFullMonthNames;
	BOOL	m_bFullDayNames;

	BOOL	m_bCapture;
	BOOL    m_bDaySaved;
#ifdef WIN32
	COleDateTime m_SaveSelectedDay;
#else
	CTime        m_SaveSelectedDay;
#endif

	CObList m_HltDateList;

	LOGFONT	m_lfTitleFont;
	LOGFONT	m_lfDayFont;
	LOGFONT	m_lfDateFont;
	CFont   m_TitleFont;
	CFont	m_DayFont;
	CFont   m_DateFont;

public:
	inline CFont* GetTitleFont() { return &m_TitleFont; }
	inline CFont* GetDayBarFont() { return &m_DayFont; }
	inline CFont* GetDateFont() { return &m_DateFont; }

protected:
	BOOL m_bDefaultColor;		// Used for custom color settings.
	COLORREF m_clrText;
	COLORREF m_clrLines;
	COLORREF m_clrDayBarText;
	COLORREF m_clrDayBarFace;
	COLORREF m_clrTitleText;
	COLORREF m_clrTitleFace;
	COLORREF m_clrGrayText;

	long m_iPrePostDrawMode;
	long m_iDrawMode;
	long m_iPrePostBehaMode;
	long m_iBehaMode;

	TOOLKIT_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SECPopupCalendar window

/////////////////////////////
// AutoDuck tag block block for SECPopupCalendar 

//@doc SECPopupCalendar
//@mdata BOOL  | SECPopupCalendar | m_bHideDoesOK | Determines if calculator 
// send IDOK or IDCANCEL when hidden.
//@xref <c SECPopupCalendar> <mf SECPopupCalendar::SetHideMode>

// adinsert AutoDuck insertion point for SECPopupCalendar 
//@doc SECPopupCalendar 
//@class The SECPopupCalendar provides the function of the <c SECCalendar> class
// in a popup window by extending this <c SECCalendar> class.
//@base public | SECCalendar.
//@xref <c SECCalendar>

// Exported through base class. 
class SECPopupCalendar : public SECCalendar
{

	TOOLKIT_DECLARE_SERIAL(SECPopupCalendar);
	
	//@access Creation/Initialization

public:

	//@cmember
	/* Creates a SECPopupCalendar object*/
	TOOLKIT_API SECPopupCalendar( );

	//@cmember
	/* Creates a popup calendar window.*/
	TOOLKIT_API virtual BOOL Create(DWORD dwStyle, 
						CRect &buttonRect, 
						CWnd *pParentWnd, 
						CCreateContext *pContext = NULL);

	//@access Attributes
public:
	// IDOK or IDCANCEL
	//@cmember
	/* Selects the hiding behavior of the popup window.*/
	TOOLKIT_API long SetHideMode( long okOrCancel );

	// Retrieves the class style for the popup window.
	TOOLKIT_API virtual UINT GetClassStyle( void );

	//@access Operations

public:
	// Serializes this calendar through a CArchive object
	TOOLKIT_API void Serialize( CArchive &ar );


	//@access Overrides
public:

	//{{AFX_MSG(SECPopupCalendar)
	//@cmember
	/* Called when a CWnd object is being activated or deactivated. */
	TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG

// Implementation
public:
	TOOLKIT_API ~SECPopupCalendar( );

protected:
	//@cmember
	/* Determines if calculator send IDOK or IDCANCEL when hidden.*/
	BOOL m_bHideDoesOK;

	TOOLKIT_DECLARE_MESSAGE_MAP()
};


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////
#endif // __SEC_CALENDAR_H__   

