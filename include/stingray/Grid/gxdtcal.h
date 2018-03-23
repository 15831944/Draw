///////////////////////////////////////////////////////////////////////////////
// gxdtcal.h : Declarations for the Calendar Control
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

#ifndef _GXDTCAL_H_
#define _GXDTCAL_H_

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

class CGXBCalendar;

#define GXDT_PANEL_SCHEMA					0x0100
#define GXDT_DAY_SCHEMA						0x0100
#define GXDT_CAL_SCHEMA						0x0100
#define GXDT_PANEL_DEBUG						FALSE

//	Drawing mode components.
#define GXDT_PDM_FILLIN						0x0001L
#define GXDT_PDM_BEVELPRESSED				0x0002L
#define GXDT_PDM_BEVELRELEASED				0x0004L
#define GXDT_PDM_OUTLINEPRESSED				0x0008L
#define GXDT_PDM_OUTLINERELEASED			0x0010L
#define GXDT_PDM_HIGHLIGHTPRESSED			0x0020L
#define GXDT_PDM_HIGHLIGHTRELEASED			0x0040L
#define GXDT_PDM_TEXTCENTERED				0x0080L
#define GXDT_PDM_PREPOSTGRAYED				0x0100L

// Behavior mode components
#define GXDT_PBM_TEXTSCALEABLEHEIGHT		0x1000L
#define GXDT_PBM_TEXTSCALEABLEWIDTH			0x2000L
#define GXDT_PBM_SELECTABLE					0x4000L
#define GXDT_PBM_HIGHLIGHTABLE				0x8000L
#define GXDT_PBM_AUTOCLOSEABLE				0x0100L
#define GXDT_PBM_PPSELECTABLE				0x0200L


#define GXDT_PDM_DRAW1 \
			GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_BEVELRELEASED | GXDT_PDM_OUTLINEPRESSED | \
			GXDT_PDM_OUTLINERELEASED | GXDT_PDM_HIGHLIGHTPRESSED | \
			GXDT_PDM_HIGHLIGHTRELEASED | \
			GXDT_PDM_PREPOSTGRAYED

#define GXDT_PDM_DRAW2 GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_HIGHLIGHTPRESSED | GXDT_PDM_HIGHLIGHTRELEASED | \
			GXDT_PDM_PREPOSTGRAYED

#define GXDT_PDM_DRAW3 GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_TEXTCENTERED 

#define GXDT_PDM_GXDT_DEFAULT_VIEW_DRAW GXDT_PDM_DRAW1
#define GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW GXDT_PDM_DRAW1
#define GXDT_PDM_GXDT_DEFAULT_POPUP_DRAW GXDT_PDM_DRAW3

#define GXDT_PDM_GXDT_DEFAULT_VIEW_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED
#define GXDT_PDM_GXDT_DEFAULT_DIALOG_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED
#define GXDT_PDM_GXDT_DEFAULT_POPUP_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED | \
			GXDT_PDM_TEXTCENTERED

#define GXDT_PBM_GXDT_DEFAULT_VIEW_BEHAVIOR \
			GXDT_PBM_SELECTABLE|GXDT_PBM_HIGHLIGHTABLE
#define GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR \
			GXDT_PBM_SELECTABLE | GXDT_PBM_HIGHLIGHTABLE
#define GXDT_PBM_GXDT_DEFAULT_POPUP_BEHAVIOR \
			GXDT_PBM_SELECTABLE

#define GXDT_DP_DEFAULTBEVELLINES		  		2



class CGXBPanel	: public CObject
{
	GRID_DECLARE_SERIAL( CGXBPanel ) 
// Construction
public:
	GRID_API BOOL HitTest( const CPoint &pt );
	GRID_API CGXBPanel( );
	GRID_API BOOL	Create( CRect r, 
					CWnd *pParent,
					DWORD dwStyle,
					UINT nID,
					BOOL bSelected = FALSE, 
					BOOL bHighlighted = FALSE, 
					long nDrawMode = GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW,
					long nBehaviorMode = GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR,
					UINT nBevelLines = GXDT_DP_DEFAULTBEVELLINES);

// Attributes
public:
	GRID_API COLORREF GetGrayTextColor( void );
	GRID_API void SetGrayTextColor( COLORREF &clr );
	GRID_API COLORREF SetTextColor( COLORREF &clr );
	GRID_API CRect SetContainerRect( CRect &rect );
	GRID_API CRect GetContainerRect( void );
	GRID_API CRect GetFaceRect( void );
	GRID_API CString SetTextLabel( CString &theLabel );
	GRID_API CString SetTextLabel( TCHAR *pszText );
	GRID_API CString GetTextLabel( void );
	GRID_API long SetDrawMode( long nMode );
	GRID_API long GetDrawMode( void );
	GRID_API UINT SetBevelLines( UINT nLines );
	GRID_API UINT GetBevelLines( void );
	GRID_API UINT SetHighlightLines( UINT nLines );
	GRID_API UINT GetHighlightLines( void );
	GRID_API BOOL SetSelected( BOOL bSelected, BOOL bRedraw = TRUE );
	GRID_API BOOL GetSelected( void );
	GRID_API BOOL SetHighlight( BOOL bHighlight, BOOL bRedraw = TRUE );
	GRID_API BOOL GetHighlight( void );
	GRID_API long SetBehaviorMode(long iBehaviorMode);

// Operations
public:
protected:
	GRID_API void GetMetrics( void );

// Overrides
public:
	GRID_API virtual BOOL OnDrawHighlight( CDC *pDC );
	GRID_API virtual BOOL OnDraw( CDC *pDC );
	GRID_API virtual BOOL OnDrawBevel( CDC *pDC );
	GRID_API virtual BOOL OnDrawOutline( CDC *pDC );
	GRID_API virtual BOOL OnDrawFace( CDC *pDC );
	GRID_API virtual BOOL OnDrawLabel( CDC *pDC );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBPanel)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXBPanel( );

	GRID_API void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point); 
	GRID_API void OnRButtonDown(UINT nFlags, CPoint point); 
	GRID_API void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	COLORREF m_clrGrayText;
	GRID_API void	TextCenteredInRect( CDC *pDC, CRect &theRect, CString& strText);
	GRID_API void	DrawBevelLines(	CDC *pDC, 
							COLORREF &topLeft, 
							COLORREF &bottomRight,
							UINT nStartOfOffset,
							UINT nEndOfOffset );
	GRID_API void	DrawRect(CDC *pDC, 
					 CRect theRect,
					 COLORREF theLineColor);
	
	CWnd*		m_pParent;
 	long		m_iBehaviorMode;
	long		m_iDrawMode;
	CString		m_sLabel;
	CRect		m_rOuterRect;
	UINT		m_nBevelLines;
	UINT		m_nHighlightLines;
	BOOL		m_bSelected;
	BOOL		m_bHighlighted;
	COLORREF	m_clrOutline;
	COLORREF	m_clrHighlight;
	COLORREF	m_clrText;

protected:
	BOOL m_bNeedMetrics;
	BOOL m_bCreated;
	UINT m_iStartOutline;
	UINT m_iStartBevel;
	UINT m_iStartHighlight;
	UINT m_iStartFace;
};



/////////////////////////////////////////////////////////////////////////////
// CGXBDayBox:
// See CGXBDayBox.cpp for the implementation of this class
//

class CGXBDayBox : public CGXBPanel
{
	GRID_DECLARE_SERIAL( CGXBDayBox ) 
// Construction
public:
	GRID_API CGXBDayBox( );
	GRID_API BOOL Create( CRect rect,
				 CGXBCalendar *pParent,
				 UINT nID,
 				 DWORD dwStyle = WS_CHILD|WS_VISIBLE,
				 BOOL bSelected = FALSE,
				 BOOL bHighlighted = FALSE,
				 long iDrawMode = GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW,
				 long iBehaviorMode = GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR,
				 UINT nBevelLines = GXDT_DP_DEFAULTBEVELLINES );
		
// Attributes
public:
#ifdef WIN32
	GRID_API COleDateTime SetDate( COleDateTime newDate );
	GRID_API const COleDateTime &GetDate( void );
#else
	GRID_API CTime SetDate( CTime newDate );
	GRID_API const CTime &GetDate( void );
#endif
	
	GRID_API BOOL SetPrePostState( BOOL bToWhat );
	GRID_API BOOL GetPrePostState( void );

// Operations
public:

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBox)
	//}}AFX_VIRTUAL
 	GRID_API virtual BOOL OnDrawLabel( CDC *pDC  );

// Implementation
public:
	GRID_API virtual ~CGXBDayBox( );
	GRID_API CSize GetBorderSize();
	GRID_API CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	GRID_API LOGFONT	FontSizeFromRect( CDC *pDC, 
							 LOGFONT *pLf = NULL, 
							 CRect *pR = NULL );
	GRID_API void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API void OnLButtonDblClk(UINT nFlags, CPoint point);


protected:
	UINT m_ordinal;
#ifdef WIN32
	COleDateTime m_today;
#else
	CTime        m_today;
#endif
	BOOL m_bPrePost;
	BOOL m_bDateInitted;

};


/////////////////////////////////////////////////////////////////////////////
// CGXBDayBar window

class CGXBDayBar : public CGXBPanel
{
// Construction
public:
	GRID_API CGXBDayBar();

// Attributes
public:

// Operations
public:
	GRID_API CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	GRID_API LOGFONT	FontSizeFromRect( CDC *pDC, 
							  LOGFONT *pLf = NULL, 
							  CRect *pR = NULL );

	GRID_API virtual BOOL OnDrawLabel( CDC *pDC );
	GRID_API void SetFirstDayOfWeek(int nFirstDay);
	GRID_API int GetFirstDayOfWeek() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXBDayBar();

	int m_nFirstDayOfWeek;
};


#define GXDT_CALTITLE_SCHEMA 0x0100


class CGXBCalTitle : public CGXBPanel
{
	GRID_DECLARE_SERIAL( CGXBCalTitle ) 
// Construction
public:
	GRID_API CGXBCalTitle();
	GRID_API BOOL Create( CRect r,
		     CWnd *pParent,
		     DWORD dwStyle,
		     UINT nID,
		     BOOL bPressed, 
		     BOOL bHighlighted, 
		     long iDrawMode,
		     long iBehaviorMode,
		     UINT nBevelLines );
 
// Attributes
public:
	GRID_API virtual CRect SetContainerRect( CRect &rect );

// Operations
public:
#ifdef WIN32
	GRID_API virtual BOOL SetPage( const COleDateTime &date );
#else
	GRID_API virtual BOOL SetPage( const CTime        &date );
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBCalTitle)
	//}}AFX_VIRTUAL
	GRID_API virtual BOOL OnDraw( CDC *pDC );

// Implementation
public:
	GRID_API virtual ~CGXBCalTitle();
	GRID_API CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	GRID_API LOGFONT FontSizeFromRect( CDC *pDC, 
							  LOGFONT *pLf = NULL,
							  CRect *pR = NULL );

protected:
	GRID_API void SizeButtons( void );
	CGXBCalendar *m_pParent;

	CButton	m_btnPrevYear;
	CButton	m_btnPrevMonth;
	CButton	m_btnNextMonth;
	CButton	m_btnNextYear;

	BOOL m_bYearButtons;
	BOOL m_bMonthButtons;

	GRID_API void OnNextYear();
	GRID_API void OnPrevYear();
	GRID_API void OnNextMonth();
	GRID_API void OnPrevMonth();
};


/////////////////////////////////////////////////////////////////////////////
// CGXBLocale 
//
//   This class aids in internationalization.
//


class CGXBLocale
{
// Construction
public:
	GRID_API CGXBLocale();

// Attributes
public:

	GRID_API static const int DaysPerWeek;
	GRID_API static const int MonthsPerYear;

protected:

#ifdef WIN32	//or WIN64
	GRID_API static LCID m_lcid;
	GRID_API static const LCTYPE DayNameIds[7][2];
	GRID_API static const LCTYPE MonthNameIds[12][2];
#else // WIN32
	GRID_API static TCHAR *dayAbbr[];
	GRID_API static TCHAR *dayFull[];
	GRID_API static TCHAR *monthAbbr[];
	GRID_API static TCHAR *monthFull[];
#endif


// Operations
public:

	GRID_API static BOOL AFXAPI GetDayName(CString& strDay, int nDay, BOOL bFullName = TRUE);
	GRID_API static BOOL AFXAPI GetMonthName(CString& strMonth, int nMonth, BOOL bFullName = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXBLocale(){}

};

class CGXBCalendar;

// Behavior options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define GXDT_BBM_AUTOSIZE_FONT				0x00010000L
#define GXDT_BBM_AUTOSIZE_RECT				0x00020000L 
#define GXDT_BBM_SINGLE_DATE				0x00040000L
#define GXDT_BBM_MONTH_BUTTONS				0x00080000L
#define GXDT_BBM_YEAR_BUTTONS				0x00100000L
#define GXDT_BBM_KEYBOARD_CONTROL			0x00200000L
#define GXDT_BBM_MONTH_FROZEN				0x00400000L
#define GXDT_BBM_AUTO_HIDE					GXDT_PBM_AUTOCLOSEABLE
#define GXDT_BBM_LBUTTONTRACK				0x01000000L

// Not yet implemented.
#define GXDT_BBM_RESIZEABLE				0x00800000L

// Draw options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define GXDT_BDM_FULL_MONTH_NAMES			0x10000000L
#define GXDT_BDM_FULL_DAY_NAMES			0x20000000L
  
// Styles for CGXBPopupCalendar
#define GXDT_PCS_ALIGNBOTTOMLEFT			0x0001		// Align calendar at bottom
													// left of supplied rect.

/*
// Calendar-control-to-parent messages.
#define GXDT_DATESELECTED				(WM_USER+1)
#define GXDT_HIGHLIGHTLISTCHANGED		(WM_USER+2)
#define GXDT_OK							(WM_USER+3)
#define GXDT_CANCEL						(WM_USER+4)
// moved to gxmsg.h
*/

// Defaults
#define GXDT_DEFAULT_DAY_BKGD_COLOR			COLOR_WINDOW	
#define GXDT_DEFAULT_DAY_PRE_POST_BKGD_COLOR	COLOR_BTNSHADOW			
#define GXDT_DEFAULT_DAYBAR_BKGD_COLOR		COLOR_BTNFACE
#define GXDT_DEFAULT_DAYBAR_FGD_COLOR		COLOR_BTNTEXT
#define GXDT_DEFAULT_TITLE_BKGD_COLOR		COLOR_ACTIVECAPTION
#define GXDT_DEFAULT_TITLE_FGD_COLOR			COLOR_CAPTIONTEXT
#define GXDT_DEFAULT_LINES_COLOR				COLOR_BTNTEXT
#define GXDT_DEFAULT_SELECTED_COLOR			COLOR_BKGD
#define GXDT_DEFAULT_HIGHLIGHTED_COLOR		COLOR_HIGHLIGHT
#define GXDT_DEFAULT_TEXT_COLOR				COLOR_WINDOWTEXT
#define GXDT_DEFAULT_GRAYTEXT_COLOR			COLOR_GRAYTEXT

#define GXDT_BBM_GXDT_DEFAULT_VIEW_BEHAVIOR \
			GXDT_PBM_GXDT_DEFAULT_VIEW_BEHAVIOR | GXDT_BBM_AUTOSIZE_FONT | \
			GXDT_BBM_YEAR_BUTTONS |GXDT_BBM_MONTH_BUTTONS | GXDT_BBM_KEYBOARD_CONTROL 

#define GXDT_BBM_GXDT_DEFAULT_DIALOG_BEHAVIOR GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR | \
		GXDT_BBM_AUTOSIZE_FONT | GXDT_BBM_YEAR_BUTTONS | GXDT_BBM_MONTH_BUTTONS | \
		GXDT_BBM_KEYBOARD_CONTROL 
									  
#define GXDT_BBM_GXDT_DEFAULT_POPUP_BEHAVIOR GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR | \
			GXDT_BBM_AUTOSIZE_FONT | GXDT_BBM_YEAR_BUTTONS | GXDT_BBM_MONTH_BUTTONS | \
			GXDT_BBM_KEYBOARD_CONTROL | GXDT_BBM_AUTO_HIDE

#define GXDT_BDM_GXDT_DEFAULT_VIEW_DRAW GXDT_PDM_GXDT_DEFAULT_VIEW_DRAW | \
			GXDT_BDM_FULL_MONTH_NAMES | GXDT_BDM_FULL_DAY_NAMES
#define GXDT_BDM_GXDT_DEFAULT_DIALOG_DRAW GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW | \
			GXDT_BDM_FULL_MONTH_NAMES
#define GXDT_BDM_GXDT_DEFAULT_POPUP_DRAW GXDT_PDM_GXDT_DEFAULT_POPUP_DRAW

#define GXDT_BDM_GXDT_DEFAULT_VIEW_PPDRAW GXDT_PDM_GXDT_DEFAULT_VIEW_PPDRAW
#define GXDT_BDM_GXDT_DEFAULT_DIALOG_PPDRAW GXDT_PDM_GXDT_DEFAULT_DIALOG_PPDRAW
#define GXDT_BDM_GXDT_DEFAULT_POPUP_PPDRAW GXDT_PDM_GXDT_DEFAULT_POPUP_PPDRAW



#define CGXBC_NUMDAYS					42				 //7 days x 6 wks. 
#define CGXBC_GXDT_DEFAULT_FONT				_T("Arial")

// Geometry of the Calendar
#define GXDT_VD_TOP							0.000
#define GXDT_VD_TITLE						0.175
#define	GXDT_VD_WK_0							0.250
#define GXDT_VD_WK_ARRAY						{ 0.250,0.375,0.500,0.625,\
												0.750,0.875,1.000}

#define GXDT_HD_LEFT							0.000
#define GXDT_HD_TITLE						1.000
#define GXDT_HD_DAYBAR						1.000
#define GXDT_HD_DAY_ARRAY					{0.000, 0.143, 0.286, 0.429,\
										 0.572, 0.715, 0.858, 1.000}


/////////////////////////////////////////////////////////////////////////////
// CGXBCalendar:
// See Calendar.cpp for the implementation of this class
//
class CGXBDayBox;
class CGXBDayBar;
class CGXBCalTitle;

class CGXBCalendar : public CWnd
{
	GRID_DECLARE_SERIAL( CGXBCalendar ) 
// Implementation

	//{{AFX_MSG(CGXBCalendar)
	GRID_API afx_msg void OnPaint();
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	GRID_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	GRID_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnNextYear(); 
	GRID_API afx_msg void OnPrevYear(); 
	GRID_API afx_msg void OnNextMonth();
	GRID_API afx_msg void OnPrevMonth();
	GRID_API afx_msg void OnSysColorChange();
	//}}AFX_MSG
	GRID_API afx_msg LRESULT OnOK(WPARAM u, LPARAM l);
	GRID_API afx_msg LRESULT OnCancel(WPARAM u, LPARAM l);
	DECLARE_MESSAGE_MAP()

// Construction
public:
	GRID_API CGXBCalendar( );
	GRID_API virtual BOOL Create(	DWORD dwStyle, 
							CRect &Rect, 
							CWnd *pWndParent, 
							UINT nID,
							CCreateContext* pContext = NULL );


// Attributes
public:
	GRID_API long GetPrePostDrawMode( void );
	GRID_API BOOL SetPrePostDrawMode( long l );
	GRID_API long GetBehaviorMode( void );
	GRID_API BOOL SetBehaviorMode( long m );
	GRID_API BOOL FAR SetDrawMode( long m );
	GRID_API long GetDrawMode( void );
#ifdef WIN32	//or WIN64
	GRID_API BOOL SetPage( const COleDateTime &calendarPage, BOOL bRedraw = FALSE );
	GRID_API const COleDateTime& GetSelectedDateValue( void );
	GRID_API UINT GetAllHighlightedDates( COleDateTime *pDates, UINT nDates );
#else
	GRID_API const CTime& GetSelectedDateValue( void );
#endif
	GRID_API UINT GetAllHighlightedDates( CTime *pDates, UINT nDates );
	GRID_API BOOL SetPage( const CTime &calendarPage, BOOL bRedraw = FALSE );
	GRID_API BOOL MarkDate( const CTime &date, BOOL bSelectIt );
	GRID_API CGXBDayBox *GetSelectedDate( void );
	GRID_API UINT GetNumHighlightedDates( void );
	GRID_API BOOL GetAutosizeFont( void );
	GRID_API BOOL GetAutosizeRect( void );
	GRID_API void SetAutosizeRect( BOOL bSet );
	GRID_API void SetAutosizeFont( BOOL bSet );
	GRID_API const CRect	&GetControlRect( void );
	GRID_API CRect SetControlRect( CRect &newRect );
	GRID_API BOOL GetSingleDate( void );
	GRID_API BOOL SetSingleDate( BOOL bTurnOn );
	GRID_API BOOL GetMonthButtons( void );
	GRID_API BOOL SetMonthButtons( BOOL bTurnOn );
	GRID_API BOOL GetYearButtons( void );
	GRID_API BOOL SetYearButtons( BOOL bTurnOn );
	GRID_API BOOL GetKeyboardControl( void );
	GRID_API BOOL SetKeyboardControl( BOOL bTurnOn );
	GRID_API BOOL GetMonthFrozen( void );
	GRID_API BOOL SetMonthFrozen( BOOL bMakeFrozen );
	GRID_API BOOL GetAutoHide( void );
	GRID_API BOOL SetAutoHide( BOOL bHideAutomatically );
	GRID_API UINT GetAlignmentFlag( void );
	GRID_API UINT SetAlignmentFlag( UINT lNewFlag );
	GRID_API CWnd *GetNotifyWnd( void );
	GRID_API void SetNotifyWnd( CWnd *pWnd );
	GRID_API COLORREF SetTextColor( COLORREF newColor );
	GRID_API COLORREF GetTextColor( void );
	GRID_API void SetFirstDayOfWeek(int nNewFirstDay, BOOL bRedraw = FALSE);
	GRID_API int GetFirstDayOfWeek() const;


// Operations
public:
	GRID_API virtual BOOL AdvanceDay( BOOL bSelectionFollows = TRUE );
	GRID_API virtual BOOL RetreatDay(  BOOL bSelectionFollows = TRUE );
	GRID_API virtual BOOL AdvanceWeek( BOOL bSelectionFollows = TRUE );
	GRID_API virtual BOOL RetreatWeek(  BOOL bSelectionFollows = TRUE );
	GRID_API virtual BOOL AdvanceMonth( BOOL bSelectionFollows = FALSE );
	GRID_API virtual BOOL RetreatMonth(  BOOL bSelectionFollows = FALSE );
	GRID_API virtual BOOL AdvanceYear(  BOOL bSelectionFollows = FALSE );
	GRID_API virtual BOOL RetreatYear(  BOOL bSelectionFollows = FALSE );
#ifdef WIN32	//or WIN64
	GRID_API virtual BOOL DeltaSelection( COleDateTimeSpan &ts );
	GRID_API virtual BOOL DeltaPage( COleDateTimeSpan &ts );
	GRID_API virtual	BOOL HighlightDate( COleDateTime &date, BOOL bSet );
	GRID_API virtual	BOOL SelectDate( COleDateTime date, BOOL bSet );
	GRID_API virtual	BOOL ToggleSelectDate( COleDateTime &date );
	GRID_API virtual	BOOL ToggleHighlightDate( COleDateTime &date );
#endif
	GRID_API virtual BOOL DeltaSelection( CTimeSpan &ts );
	GRID_API virtual BOOL DeltaPage( CTimeSpan &ts );
	GRID_API virtual	BOOL HighlightDate( CTime &date, BOOL bSet );
	GRID_API virtual	BOOL SelectDate( CTime date, BOOL bSet );
	GRID_API virtual	BOOL ToggleSelectDate( CTime &date );
	GRID_API virtual	BOOL ToggleHighlightDate( CTime &date );
	GRID_API void Serialize( CArchive &ar );

protected:
	GRID_API void PurgeDateList( void );
	GRID_API virtual BOOL IsDisplayableDate( int year, int month, int day );


// Overrideables
public:
	GRID_API virtual void InitColors();

// Implementation
public:
	GRID_API virtual	~CGXBCalendar( );
	GRID_API void TextCenteredInRect( CDC *pDC, 
							 CRect theRect, 
							 COLORREF clrFgnd, 
							 COLORREF clrBkgd,
							 CString& strText);

	CGXBDayBar m_pnlDayBar;
	CGXBCalTitle m_pnlTitle;

protected:
#ifdef WIN32	//or WIN64
	GRID_API void NormalizeDate( COleDateTime &date );
	GRID_API BOOL DateFoundInList( COleDateTime date );
	GRID_API BOOL RemoveDateFromList( COleDateTime date );
	GRID_API BOOL AddDateToList( COleDateTime date );
#else
	GRID_API void NormalizeDate( CTime &date );
	GRID_API BOOL DateFoundInList( CTime date );
	GRID_API BOOL RemoveDateFromList( CTime date );
	GRID_API BOOL AddDateToList( CTime date );
#endif
	GRID_API virtual void OnDatePegged( void );
	GRID_API virtual UINT GetClassStyle( void );
	GRID_API void AdjustFontSizes( CDC *pDC = NULL );
	GRID_API void AdjustRectSizes( CRect &r, CDC *pDC = NULL );
	GRID_API void SizeTitle( void );
	GRID_API void SizeDayBar( void );
	GRID_API void SizeDates( void );
	GRID_API void InitFonts( void );
	GRID_API void SetUpDateBoxes( void );
	GRID_API void PaintDates( CDC *pDC );

	enum deltaDate { negYear, negMonth, negDay, Day, Month, Year };
	
	CWnd *m_pParent;
	CWnd *m_pNotifyWnd;
	UINT m_nBevelLines;

protected:
	BOOL m_bCreated;
#ifdef _DEBUG
	GRID_API void DumpDateList( void );
#endif

#ifdef WIN32	//or WIN64
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

	CGXBDayBox m_day[CGXBC_NUMDAYS];
	CGXBDayBox *m_pSelectedDay;

	UINT	m_nOpMode;
	UINT	m_nAlignment;

	BOOL	m_bFullMonthNames;
	BOOL	m_bFullDayNames;

	BOOL	m_bCapture;
	BOOL    m_bDaySaved;
#ifdef WIN32	//WIN64
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
};


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalendar window

class CGXBPopupCalendar : public CGXBCalendar
{

	GRID_DECLARE_SERIAL(CGXBPopupCalendar);
	
	//{{AFX_MSG(CGXBPopupCalendar)
	GRID_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

// Construction
public:
	GRID_API CGXBPopupCalendar( );
	GRID_API virtual BOOL Create(DWORD dwStyle, 
						CRect &buttonRect, 
						CWnd *pParentWnd, 
						CCreateContext *pContext = NULL);

// Attributes
public:
	GRID_API long SetHideMode( long okOrCancel ); // IDOK or IDCANCEL
	GRID_API virtual UINT GetClassStyle( void );

// Operations
public:
	GRID_API void Serialize( CArchive &ar );

// Implementation
public:
	GRID_API virtual ~CGXBPopupCalendar( );

protected:
	BOOL m_bHideDoesOK;
};

// CGXBDateTimeCtrl styles
#define GXDT_DTS_CALENDAR		0x0001L
#define GXDT_DTS_UPDOWN			0x0002L
#define GXDT_DTS_Y2K_NOFIX		0x0010L		// overrides Y2K fix (backward compatibility)
#define GXDT_DTS_Y2K_CONTEXT	0x0020L     // base Y2K reference year on current date in control


// CGXBDateTimeCtrl notifications
#define GXDT_DTN_CHANGED		0x0100

// CGXBDateTimeCtrl Gadget IDs (bit settings)
#define GXDT_DTID_12HOUR		0x0001
#define GXDT_DTID_24HOUR		0x0002
#define GXDT_DTID_MINUTE		0x0004
#define GXDT_DTID_SECOND		0x0008
#define GXDT_DTID_AMPM		0x0010
#define GXDT_DTID_DAYNO		0x0020
#define GXDT_DTID_DAYNAME		0x0040
#define GXDT_DTID_MONTHNO		0x0080
#define GXDT_DTID_MONTHNAME	0x0100
#define GXDT_DTID_YEAR2		0x0200
#define GXDT_DTID_YEAR4		0x0400
#define GXDT_DTID_CALDROPDOWN	0x4000
#define GXDT_DTID_SPINNER		0x8000
#define GXDT_DTID_ALL			0xffff


// Forward references
class CGXBPopupCalendar;


// Gadget notifications
#define GXDT_GN_INCREMENT		0x0001
#define GXDT_GN_DECREMENT		0x0002
#define GXDT_GN_SPINUP		0x0003
#define GXDT_GN_SPINDOWN		0x0004
#define GXDT_GN_DROPDOWN		0x0005
#define GXDT_GN_VALIDATE		0x0006
#define GXDT_GN_MODIFY		0x0007
#define GXDT_GN_MINIMUM		0x0008
#define GXDT_GN_MAXIMUM		0x0009
#define GXDT_GN_EDIT			0x000a
#define GXDT_GN_NUMERIC_DONE	0x000b

// Forward references
class CGXBDateTimeCtrl;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTGadget 
//  
//  Abstract base class for the gadget components used by CGXBDateTimeCtrl
//
class CGXBDTGadget : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXBDTGadget)
// Construction
public:
	GRID_API CGXBDTGadget();

	// Initialises the gadget.
	GRID_API BOOL Initialise(CGXBDateTimeCtrl* pCtrl, int nID = -1);

// Attributes
public:
	enum	// Style flags (for m_style and GetStyle/SetStyle)
	{
		WantFocus = 0x0001,		// Gadget accepts focus (i.e. can be enabled)
		WantMouse = 0x0002,		// Gadget wants mouse clicks
		IsFixed   = 0x0004		// Gadget is not moveable (fixed to right edge
	};							// of control)

// Operations
public:
	// Set/Get the style flags for this gadget.
	GRID_API int  GetStyle() const;
	GRID_API void SetStyle(int style);

	// Set/Get the current value of the gadget
	GRID_API void SetValue(int nNewValue);
	GRID_API int  GetValue() const;

	// Returns the gadget's ID;
	GRID_API int GetID() const;

	// Set/Get the gadget's rectangle (relative to CGXBDateTimeCtrl's client)
	GRID_API const CRect& GetRect() const;
	GRID_API void SetRect(const RECT& rect);

// Overrideables
public:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc) = 0;

	// Function to draw the gadget
	virtual void Draw(CDC& dc) = 0;

	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	GRID_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN/WM_CHAR messages while gadget is enabled
	inline virtual void OnKeyDown(UINT /* nChar */) {}
	inline virtual void OnChar(UINT /* nChar */) {}

	// Handler for mouse messages while gadget is enabled (only if
	// style has WantMouse flag).
	inline virtual void OnLButtonDown(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnLButtonUp(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnMouseMove(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnCancelMode() {}

	// Handles timer events requested by this gadget
	inline virtual void OnTimer() {}

	// Handler for the WM_SYSCOLORCHANGE message (each gadget receives it)
	inline virtual void OnSysColorChange() {}

// Implementation
public:
	GRID_API virtual ~CGXBDTGadget();

protected:
	// Passes notify events to parent
	GRID_API BOOL Notify(UINT uNotifyCode, int nID, LPARAM lParam = 0L);

	// Invalidates this gadget.
	GRID_API void Invalidate(BOOL bImmediateRedraw = FALSE);

	// Returns the background color to use
	GRID_API COLORREF GetBkColor() const;
		
	// Set capture to this gadget
	GRID_API void CaptureMouse(BOOL bSet);

	// Functions for manipulating timer events
	GRID_API void StartTimer(UINT uElapse /* ms */);
	GRID_API void StopTimer();

	// Callback function used for timer events.
	GRID_API static void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, 
										  DWORD dwTime);

// Implementation - data members
protected:
	CRect               m_rect;			// Gadget window rect (relative to
										// CGXBDateTimeCtrl's client)
	BOOL                m_bEnabled;		// TRUE if we are enabled (have focus)
	int                 m_style;		// Holds style flags
	int                 m_nID;			// This gadgets ID
	int                 m_nValue;		// This gadgets current value
	CGXBDateTimeCtrl*    m_pCtrl;		// Parent CGXBDateTimeCtrl
	GRID_API static CMapWordToOb m_timers;		// Maps current timers onto gadgets
};


/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTStaticGadget
//  
//  Class implementing a non-editable text gadget for CGXBDateTimeCtrl
//
class CGXBDTStaticGadget : public CGXBDTGadget
{
	GRID_DECLARE_DYNAMIC(CGXBDTStaticGadget)
// Construction
public:
	GRID_API CGXBDTStaticGadget();

	// Initialises the static gadget (and define the caption)
	GRID_API BOOL Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszCaption, 
					int nID = -1);

// Attributes
public:

// Operations
public:
	// Function to return the caption
	GRID_API CString GetCaption() const;

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	GRID_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	GRID_API virtual void Draw(CDC& dc);

// Implementation
public:
	GRID_API virtual ~CGXBDTStaticGadget();

// Implementation - data members
protected:
	CString m_strCaption;				// Text of caption
};


/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTNumericGadget
//  
//  Class implementing an editable numeric gadte for CGXBDateTimeCtrl
//
class CGXBDTNumericGadget : public CGXBDTGadget
{
	GRID_DECLARE_DYNAMIC(CGXBDTNumericGadget)
// Construction
public:
	GRID_API CGXBDTNumericGadget();

	// Initialise the numeric gadget.
	GRID_API BOOL Initialise(CGXBDateTimeCtrl* pCtrl, int nMin, int nMax, int nValue, 
					BOOL bLeadZero, int nID = -1);

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	GRID_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	GRID_API virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	GRID_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	GRID_API virtual void OnKeyDown(UINT nChar);
	GRID_API virtual void OnChar(UINT nChar);

	// Handler for WM_CANCELMODE
	GRID_API virtual void OnCancelMode();

// Implementation
public:
	GRID_API virtual ~CGXBDTNumericGadget();

protected:
	// Validate's keyboard entry of new date
	GRID_API BOOL Validate();

// Implementation - data members
protected:
	int  m_nMin;				// Minimum value
	int  m_nMax;				// Maximum value
	int  m_nWidth;				// Maximum no. of chars. allowed
	int  m_nNewValue;			// New value (used during keyboard entry)
	int  m_nCurDigit;			// Current digit being editted
	BOOL m_bLeadZero;			// TRUE if value is to be displayed with
								// leading zero
};


/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTListGadget
//  
//  Class implementing a text gadget with a defined list of possible strings
//
class CGXBDTListGadget : public CGXBDTGadget
{
	GRID_DECLARE_DYNAMIC(CGXBDTListGadget)
// Construction
public:
	GRID_API CGXBDTListGadget();

	// Initialise the list gadget
	GRID_API BOOL Initialise(CGXBDateTimeCtrl* pCtrl, const CStringArray& list, int nValue, int nID = -1);

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	GRID_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	GRID_API virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	GRID_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	GRID_API virtual void OnKeyDown(UINT nChar);
	GRID_API virtual void OnChar(UINT nChar);

	// Handler for timer events
	GRID_API virtual void OnTimer();

// Implementation
public:
	GRID_API virtual ~CGXBDTListGadget();

protected:
	GRID_API int FindMatch(LPCTSTR lpszPat, int nCurPos);

// Implementation - data members
protected:
	CStringArray m_list;				// List of possible string
	TCHAR        m_cBuf[3];				// Used during entry of Multi-Byte
										// character
	CString      m_strPat;				// Holds string entered so far 
										// (during partial match)
	BOOL         m_bTimerRunning;		// TRUE when we have a timer enabled
};


/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTButtonGadget
//  
//  Class implementing a simple push button gadget for CGXBDateTimeCtrl
//
class CGXBDTButtonGadget : public CGXBDTGadget
{
	GRID_DECLARE_DYNAMIC(CGXBDTButtonGadget)
// Construction
public:
	GRID_API CGXBDTButtonGadget();

	GRID_API BOOL Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszBmpName, int nID = -1);

// Attributes
public:
	enum				// State flags (see m_nState)
	{
		Capture = 0x0001,			// We currently have capture (tracking
									// button press)
		Down    = 0x0002			// The button is currently pressed
	};

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	GRID_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	GRID_API virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	GRID_API virtual void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API virtual void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API virtual void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API virtual void OnCancelMode();

	// Handler for WM_SYSCOLORCHANGE
	GRID_API virtual void OnSysColorChange();

// Implementation
public:
	GRID_API virtual ~CGXBDTButtonGadget();

// Implementation - data members
protected:
	int     m_nState;				// State information
	CBitmap m_bmp;					// Bitmap displayed on button
	LPCTSTR m_lpszBmpName;			// Resource ID of bitmap
};


/////////////////////////////////////////////////////////////////////////////
//  class GRID_API CGXBDTSpinGadget
//  
//  Class implementing a spin button gadget for use with CGXBDateTimeCtrl
//
class CGXBDTSpinGadget : public CGXBDTGadget
{
	GRID_DECLARE_DYNAMIC(CGXBDTSpinGadget)
// Construction
public:
	GRID_API CGXBDTSpinGadget();

// Attributes
public:
	enum							// State flags (see m_nState)
	{	
		SpinUp       = 0x0001,		// The spin up button is currently pressed
		SpinDown     = 0x0002,		// The spin down button is currently pressed
		CaptureUp    = 0x0004,		// We are tracking press of spin up btn
		CaptureDown  = 0x0008,		// We are tracking press of spin down btn
		TimerRunning = 0x0010,		// We have a timer running
		InitialTimer = 0x0020		// The timer has been initialised (first
	};								// tick = 500ms, subsequent ticks = 100ms).

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	GRID_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	GRID_API virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	GRID_API virtual void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API virtual void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API virtual void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API virtual void OnCancelMode();

	// Handler for timer events
	GRID_API virtual void OnTimer();

// Implementation
public:
	GRID_API virtual ~CGXBDTSpinGadget();

protected:
	// Draws either up or down spin button
	GRID_API void DrawPart(CDC& dc, CRect& r, BOOL bInvert, BOOL bDown);

	// Returns 0 if point is on spin up button, 1 if on spin down, else -1
	GRID_API int  CheckHit(CPoint point) const;

// Implementation - data members
protected:
	int      m_nState;					// Holds state information
	SEC_UINT m_nTimer;					// Timer tick count

//used to specify timing for spinner
protected:
	GRID_API virtual int GetInitialTimerValue();
	GRID_API virtual int GetNormalTimerValue();

};


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl window
//    
class CGXBDateTimeCtrl : public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXBDateTimeCtrl)

// Construction
public:
	GRID_API CGXBDateTimeCtrl();

	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, 
				CCreateContext* pContext = NULL);
	GRID_API BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, 
				  CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

// Attributes
public:
	// Control format type as used by Get/SetFormat.
	enum FormatType
	{
		Time,							// Locale time format
		ShortDate,						// Locale short date format 
		LongDate,						// Locale long date format
		Custom,							// A user supplied date/time format 
		DateTime						// Locale short date + locale time
	};									

	// The validation types as used by Get/SetMinMax
	enum ValidationMode
	{
		NoValidation,					// No validation is required
		TimeValidation,					// Validation of time fields only
		DateValidation,					// Validation of date fields only
		DateTimeValidation				// Validation of date & time fields
	};

	// Definitions of non-editable fields as used by Get/SetNoEdit
	enum NoEdit
	{
		FixedYear   = 0x0001,			// The year is non-editable
		FixedMonth  = 0x0002,			// The month is non-editable
		FixedDay    = 0x0004,			// The day is non-editable
		FixedHour   = 0x0008,			// The hour is non-editable
		FixedMinute = 0x0010,			// The minute is non-editable
		FixedSecond = 0x0020			// The second is non-editable
	};

// Operations
public:
	// Forcing a given gadget to be redrawn
	GRID_API void InvalidateGadget(CGXBDTGadget* pGadget, BOOL bImmediateRedraw = FALSE);
	GRID_API void InvalidateGadget(int nIndex, BOOL bImmediateRedraw = FALSE);

	// Return the index of the gadget at the given point
	GRID_API int  GadgetFromPoint(CPoint point);

	// Bring a given gadget into the displayable portion of the window
	GRID_API void BringIntoView(CGXBDTGadget* pGadget);
	GRID_API void BringIntoView(int nIndex);

	// Set/Get the current date/time format
	GRID_API void SetFormat(FormatType format);
	GRID_API void SetFormat(LPCTSTR lpszFormat);
	GRID_API void GetFormat(FormatType& format) const;
	GRID_API void GetFormat(CString& format) const;

	// Functions for enabling fast input. With fast input enabled, when a 
	// numeric field has received a valid input (it's maximum number of
	// digits), it advances input focus to the next field.
	// virtual so that CGXDateTimeCtrl can supply the UA value instead
	GRID_API void EnableFastEntry(BOOL bEnable = TRUE);
	GRID_API virtual BOOL IsFastEntryEnabled() const;

	// Tells if the current gadget the right most or left most gadget that 
	// wants the focus

	GRID_API BOOL IsFocusOnRightMostGadget() const;
	GRID_API BOOL IsFocusOnLeftMostGadget() const;


	// Force the control to re-size to fit it's contents exactly
	GRID_API void SizeToContent();

	// Set/Determine the current modified state.
	GRID_API void SetModified(BOOL bModified);
	GRID_API void SetModified(BOOL bDate, BOOL bTime);
	GRID_API BOOL IsModified() const;
	GRID_API void IsModified(BOOL& bDate, BOOL& bTime) const;

	// Returns TRUE if the user is currently in the middle of editting one
	// of the numeric fields
	GRID_API BOOL IsEditing() const;

	// Set/Get the current date and time
	GRID_API BOOL SetDateTime(const COleDateTime& datetime);
	GRID_API BOOL SetDate(const COleDateTime& date);
	GRID_API BOOL SetTime(const COleDateTime& time);
	GRID_API const COleDateTime& GetDateTime() const;

	// Set/Get the current validation mode and the ranges being validated
	// to.
	GRID_API BOOL SetMinMax(const COleDateTime& minDateTime, 
				   const COleDateTime& maxDateTime, 
				   ValidationMode mode = DateTimeValidation);
	GRID_API ValidationMode GetMinMax(COleDateTime& minDateTime, 
							 COleDateTime& maxDateTime) const;

	// Validates the given date/time to the current ranges
	GRID_API BOOL Validate(const COleDateTime& datetime) const;

	// Set/Get the edittable fields.
	GRID_API int  GetNoEdit() const;
	GRID_API void SetNoEdit(int nNoEdit);

	// AM/PM indicator
	GRID_API BOOL IsHourPM();
// Overrides
	// Function called just before a commit of a new date/time is applied.
	// Return FALSE to abandon the commit.
	GRID_API virtual BOOL OnChanging(const COleDateTime& newDateTime);

	// Function called after the date/time has been modified. The default
	// implementation passes a GXDT_DTN_CHANGED notification to the parent.
	GRID_API virtual void OnChanged();

// Implementation
public:
	GRID_API virtual ~CGXBDateTimeCtrl();

protected:
	// Function responsible for parsing the date/time format string and 
	// building the m_gadgets component list.
	GRID_API void ParseDateTimeFormat();

	// Functions used by ParseDateTimeFormat for parsing individual components
	// of the date/time string
	GRID_API void ParseHours(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseMinutes(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseSeconds(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseAmPm(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseDay(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseMonth(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseYear(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseEra(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API void ParseQuotedText(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	GRID_API BOOL CheckLeadZero(LPCTSTR& lpsz, TCHAR c) const;
	GRID_API void FlushStatic(LPCTSTR lpszStart, LPCTSTR lpszEnd);

	// Functions used for changing the value of a speicific field 
	GRID_API BOOL ChangeHour(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeMinute(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeSecond(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeAmPm(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeDay(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeMonth(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API BOOL ChangeYear(UINT uNotifyCode, int nID, LPARAM lParam);
	GRID_API virtual int GetCentury(int n2DigitYear);	// Modified sig. in OG7.02

	// Functions for moving forward/backwards a gadget
	GRID_API void AdvanceGadget();
	GRID_API void RetreatGadget();

	// Function used to layout the gadgets within the controls client
	GRID_API virtual void LayoutGadgets();

	// Function used for controlling the drawing of the gadgets.
	GRID_API virtual void Draw(CDC& dc);

	// Handler for spinner events
	GRID_API BOOL SpinnerEvent(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handler for creating the popup calendar
	GRID_API virtual BOOL PopupCalendar(UINT uNotifyCode, int nID, LPARAM lParam);

	// Override this to hook in a SECPopupCalendar derived object.
	GRID_API virtual void OnCreatePopupCalendar();

	// Functions for updating the specified gadgets with new values and
	// for forcing them to be redisplayed
	GRID_API void UpdateGadgets(const COleDateTime& datetime);
	GRID_API void UpdateGadgets(UINT nFlags = GXDT_DTID_ALL);

	// Performs validation of a new date (and can correct certain
	// fields to make it valid)
	GRID_API virtual BOOL Validate(COleDateTime& datetime, int nPos) const;

	// Handles notify events from gadgets
	GRID_API virtual BOOL OnNotify(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handles requests from gadgets to capture the mouse.
	GRID_API void CaptureMouse(CGXBDTGadget* pGadget, BOOL bSet);

	// Functions for causing the gadget display to be re-built.
	GRID_API void ResetGadgets();
	GRID_API void Tidy();

protected:
// Implementation - data members
	enum								// Internal state flags
	{
		DateModified = 0x0001,			// The date has been modified
		TimeModified = 0x0002,			// The time has been modified
		Editing      = 0x0004			// A numeric field is currently being
	};									// editted.

	int               m_nState;			// Holds state information (see flags)
	int               m_nNoEdit;		// Holds non-editable fields (see NoEdit)
	BOOL			  m_bFastInput;		// TRUE if fast input enabled
	COleDateTime      m_datetime;		// Current date/time
	COleDateTime      m_datetimeMin;	// Minimum date/time
	COleDateTime      m_datetimeMax;	// Maximum date/time
	ValidationMode    m_validMode;		// Validation mode (see ValidationMode)
	FormatType        m_formatType;		// Date/Time format type (see FormatType)
	CString           m_strCustomFormat;// Holds custom date/time format string
	HFONT             m_hFont;			// Font used by control
	int               m_nCurGadget;		// Current gadget (gadget with focus)
	int               m_nXOrigin;		// Current offset (scrolled percentage)
										// of window.
	int               m_nRightOffset;	// Amount of space on right reserved for
										// fixed gadgets
	int               m_nFixed;			// No. of fixed gadgets.
	CGXBDTGadget*      m_pCapture;		// Ptr to gadget which has mouse capture
	CGXBPopupCalendar* m_pPopupCalendar;	// Handle of popup calendar 
										// (normally NULL)

	BOOL			  m_bHourPM;		// AM/PM toggle
	COLORREF          m_cBkColor;		// Current background color

public:
	int               m_nBkDisabled;	// System background color when disabled
	UINT              m_nCalBmp;		// ID of bmp to display on cal. drop down
										// button.

	BOOL              m_bDateTokens;	// OG: ParseDateTime will set this TRUE if it finds date tokens

protected:

	// CGXBDTGadgetArray would normally be implemented as a template 
	// (CTypedPtrArray). Since templates are not implemented by some Unix
	// compilers, we copy what the template would have done.
	class GRID_API CGXBDTGadgetArray : public CObArray
	{
	public:
		// Accessing elements
		CGXBDTGadget* GetAt(int nIndex) const;
		CGXBDTGadget*& ElementAt(int nIndex);
		void SetAt(int nIndex, CGXBDTGadget* ptr);

		// Potentially growing the array
		void SetAtGrow(int nIndex, CGXBDTGadget* newElement);
		int Add(CGXBDTGadget* newElement);
		int Append(const CGXBDTGadgetArray& src);
		void Copy(const CGXBDTGadgetArray& src);

		// Operations that move elements around
		void InsertAt(int nIndex, CGXBDTGadget* newElement, int nCount = 1);
		void InsertAt(int nStartIndex, CGXBDTGadgetArray* pNewArray);

		// overloaded operator helpers
		CGXBDTGadget* operator[](int nIndex) const;
		CGXBDTGadget*& operator[](int nIndex);
	};

	// m_gadgets is an array of all the gadget components.
	CGXBDTGadgetArray m_gadgets;

	// Implementation - message map and entries
	GRID_DECLARE_MESSAGE_MAP()

	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnEnable(BOOL bEnable);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	GRID_API afx_msg void OnNcPaint();
	GRID_API afx_msg LRESULT OnCalendarOK(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCalendarCancel(WPARAM wParam, LPARAM lParam);

	// A very dear friend of mine ...
	friend class CGXBDTGadget;

public:
	// Added for OG
	COLORREF m_clrText;
	COLORREF m_clrWindow;

	// Handles the spinner timing, initially set to 500 & 100 msecs.
	// To slow spinner, after call to OnInitialUpdate, try 
	//  ((CGXDateTimeCtrl*)GetRegisteredControl(GX_IDS_CTRL_DATETIME))->m_nNormalTimer = 200;
	int m_nInitialTimer;
	int m_nNormalTimer;	
};


/////////////////////////////////////////////////////////////////////////////
// Function for converting a DATE (base type of COleDateTime) to a tm structure
extern GRID_API BOOL AFXAPI GXBGetTmFromOleDate(DATE dtSrc, struct tm& tmDest);


/////////////////////////////////////////////////////////////////////////////

#define ON_GXDT_DTN_CHANGED(id, memberFxn) \
		ON_CONTROL(GXDT_DTN_CHANGED, id, memberFxn)


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxdtcal.inl"
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
#endif // #if _MFC_VER >= 0x0400   

#endif // _GXDTCAL_H_

