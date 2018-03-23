///////////////////////////////////////////////////////////////////////////////
// Panel.h : header file for the SECPanel component of the SECCalendar 
//            custom control.
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


#ifndef __SEC_PANEL_H__
#define __SEC_PANEL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

#define SEC_PANEL_SCHEMA					0x0100

#define SEC_PANEL_DEBUG						FALSE
//	Drawing mode components.
#define SECPDM_FILLIN						0x0001L
#define SECPDM_BEVELPRESSED					0x0002L
#define SECPDM_BEVELRELEASED				0x0004L
#define SECPDM_OUTLINEPRESSED				0x0008L
#define SECPDM_OUTLINERELEASED				0x0010L
#define SECPDM_HIGHLIGHTPRESSED				0x0020L
#define SECPDM_HIGHLIGHTRELEASED			0x0040L
#define SECPDM_TEXTCENTERED					0x0080L
#define SECPDM_PREPOSTGRAYED				0x0100L

// Behavior mode components
#define SECPBM_TEXTSCALEABLEHEIGHT			0x1000L
#define SECPBM_TEXTSCALEABLEWIDTH			0x2000L
#define SECPBM_SELECTABLE					0x4000L
#define SECPBM_HIGHLIGHTABLE				0x8000L
#define SECPBM_AUTOCLOSEABLE				0x0100L
#define SECPBM_PPSELECTABLE					0x0200L


#define SECPDM_DRAW1 \
			SECPDM_FILLIN | SECPDM_BEVELPRESSED | \
			SECPDM_BEVELRELEASED | SECPDM_OUTLINEPRESSED | \
			SECPDM_OUTLINERELEASED | SECPDM_HIGHLIGHTPRESSED | \
			SECPDM_HIGHLIGHTRELEASED | \
			SECPDM_PREPOSTGRAYED

#define SECPDM_DRAW2 SECPDM_FILLIN | SECPDM_BEVELPRESSED | \
			SECPDM_HIGHLIGHTPRESSED | SECPDM_HIGHLIGHTRELEASED | \
			SECPDM_PREPOSTGRAYED

#define SECPDM_DRAW3 SECPDM_FILLIN | SECPDM_BEVELPRESSED | \
			SECPDM_TEXTCENTERED 

#define SECPDM_DEFAULT_VIEW_DRAW SECPDM_DRAW1
#define SECPDM_DEFAULT_DIALOG_DRAW SECPDM_DRAW1
#define SECPDM_DEFAULT_POPUP_DRAW SECPDM_DRAW3

#define SECPDM_DEFAULT_VIEW_PPDRAW SECPDM_FILLIN | SECPDM_PREPOSTGRAYED
#define SECPDM_DEFAULT_DIALOG_PPDRAW SECPDM_FILLIN | SECPDM_PREPOSTGRAYED
#define SECPDM_DEFAULT_POPUP_PPDRAW SECPDM_FILLIN | SECPDM_PREPOSTGRAYED | \
			SECPDM_TEXTCENTERED

#define SECPBM_DEFAULT_VIEW_BEHAVIOR \
			SECPBM_SELECTABLE|SECPBM_HIGHLIGHTABLE
#define SECPBM_DEFAULT_DIALOG_BEHAVIOR \
			SECPBM_SELECTABLE | SECPBM_HIGHLIGHTABLE
#define SECPBM_DEFAULT_POPUP_BEHAVIOR \
			SECPBM_SELECTABLE

#define SECP_DEFAULTBEVELLINES		  		2

/////////////////////////////////////////////////////////////////////////////
// SECPanel:
// See SECPanel.cpp for the implementation of this class
//
class SECCalendar;

class SECPanel	: public CObject
{
	TOOLKIT_DECLARE_SERIAL( SECPanel ) 
	
// Construction
public:
	TOOLKIT_API BOOL HitTest( const CPoint &pt );
	TOOLKIT_API SECPanel();
	TOOLKIT_API BOOL	Create( CRect r, 
					CWnd *pParent,
					DWORD dwStyle,
					UINT nID,
					BOOL bSelected = FALSE, 
					BOOL bHighlighted = FALSE, 
					long nDrawMode = SECPDM_DEFAULT_DIALOG_DRAW,
					long nBehaviorMode = SECPBM_DEFAULT_DIALOG_BEHAVIOR,
					UINT nBevelLines = SECP_DEFAULTBEVELLINES);

// Attributes
public:
	TOOLKIT_API COLORREF GetGrayTextColor( void );
	TOOLKIT_API void SetGrayTextColor( COLORREF &clr );
	TOOLKIT_API COLORREF SetTextColor( COLORREF &clr );
	TOOLKIT_API COLORREF GetHighlightColor( void );
	TOOLKIT_API void SetHighlightColor( COLORREF &clr );
	TOOLKIT_API CRect SetContainerRect( CRect &rect );
	TOOLKIT_API CRect GetContainerRect( void );
	TOOLKIT_API CRect GetFaceRect( void );
	TOOLKIT_API CString SetTextLabel( CString &theLabel );
	TOOLKIT_API CString SetTextLabel( TCHAR *pszText );
	TOOLKIT_API CString GetTextLabel( void );
	TOOLKIT_API long SetDrawMode( long nMode );
	TOOLKIT_API long GetDrawMode( void );
	TOOLKIT_API UINT SetBevelLines( UINT nLines );
	TOOLKIT_API UINT GetBevelLines( void );
	TOOLKIT_API UINT SetHighlightLines( UINT nLines );
	TOOLKIT_API UINT GetHighlightLines( void );
	TOOLKIT_API BOOL SetSelected( BOOL bSelected, BOOL bRedraw = TRUE );
	TOOLKIT_API BOOL GetSelected( void );
	TOOLKIT_API BOOL SetHighlight( BOOL bHighlight, BOOL bRedraw = TRUE );
	TOOLKIT_API BOOL GetHighlight( void );
	TOOLKIT_API long SetBehaviorMode(long iBehaviorMode);

// Operations
public:
protected:
	TOOLKIT_API void GetMetrics( void );
#ifndef WIN32
	TOOLKIT_API int  GetLogFont(CFont &theFont, LOGFONT* pLogFont);
#endif // WIN32	

// Overrides
public:
	TOOLKIT_API virtual BOOL OnDrawHighlight( CDC *pDC );
	TOOLKIT_API virtual BOOL OnDraw( CDC *pDC );
	TOOLKIT_API virtual BOOL OnDrawBevel( CDC *pDC );
	TOOLKIT_API virtual BOOL OnDrawOutline( CDC *pDC );
	TOOLKIT_API virtual BOOL OnDrawFace( CDC *pDC );
	TOOLKIT_API virtual BOOL OnDrawLabel( CDC *pDC );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECPanel)
	//}}AFX_VIRTUAL

// Implementation
public:
	TOOLKIT_API virtual ~SECPanel( );

	TOOLKIT_API void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API void OnLButtonDown(UINT nFlags, CPoint point); 
	TOOLKIT_API void OnRButtonDown(UINT nFlags, CPoint point); 
	TOOLKIT_API void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	COLORREF m_clrGrayText;
	TOOLKIT_API void	TextCenteredInRect( CDC *pDC, CRect &theRect, CString& strText);
	TOOLKIT_API void	DrawBevelLines(	CDC *pDC, 
							COLORREF &topLeft, 
							COLORREF &bottomRight,
							UINT nStartOfOffset,
							UINT nEndOfOffset );
	TOOLKIT_API void	DrawRect(CDC *pDC, 
					 CRect theRect,
					 COLORREF theLineColor);
	
	CWnd *m_pParent;
 	long m_iBehaviorMode;
	long m_iDrawMode;
	CString	m_sLabel;
	CRect m_rOuterRect;
	UINT m_nBevelLines;
	UINT m_nHighlightLines;
	BOOL m_bSelected;
	BOOL m_bHighlighted;
	COLORREF m_clrOutline;
	COLORREF m_clrHighlight;
	COLORREF m_clrText;

protected:
	BOOL m_bNeedMetrics;
	BOOL m_bCreated;
	UINT m_iStartOutline;
	UINT m_iStartBevel;
	UINT m_iStartHighlight;
	UINT m_iStartFace;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SEC_PANEL_H__

