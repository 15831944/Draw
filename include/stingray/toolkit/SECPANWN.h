///////////////////////////////////////////////////////////////////////////////
// SECPANWN.h
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
//  Author:		Scot Wingo
//  Description:	Declaration of the panning overview window
//  Created:		Tue Jun 27 15:13:35 1995
//
//   CHANGELOG
//
//      MSW    9/30/95   Code Review
//

#ifndef __SECPANWN_H__
#define __SECPANWN_H__

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

// Forward declarations
class SECPanView;

/////////////////////////////////////////////////////////////////////////////
// SECPanWnd window

/////////////////////////////
// AutoDuck tag block block for SECPanWnd 

// adinsert AutoDuck insertion point for SECPanWnd 
//@doc SECPanWnd 
//@class SECPanWnd is an overview window that shows the user a miniaturization of the entire view provided 
// by <c SECPanView>.
//@comm
// The user can use the overview window to pan the visible portion of the view and also to see where the 
// visible area lies in relation to other portions of the view.  The overview window is especially 
// helpful at large zoom levels when it is possible to lose track of the current location in a complex 
// view.
//
// The currently visible region of the view is outlined by a dotted rectangle.  The user can move the 
// dotted rectangle to change the currently visible area.  If the user updates the view or scrolls, 
// SECPanWnd is automatically updated to  reflect the changes.
//
// The CLOUD sample in the \SAMPLES\TOOLKIT\STANDARD\VIEWS\CLOUD directory demonstrates SECPanWnd.
//@xref<c SECPanView>
//@BASE public | CWnd
class SECPanWnd : public CWnd
{
    // We're friends with the pan view. 
    friend class SECPanView;
    
// Construction
public:
	//@Access Public Members
	//Constructors
	//@cmember
	/* Constructs an SECPanWnd overview window object.*/
    TOOLKIT_API SECPanWnd(SECPanView *);

// Attributes
public:
	//@Access Attributes
	//@cmember
	/* Creates the overview window and specifies its initial position and size.*/
    TOOLKIT_API virtual BOOL Create(CRect rectCreate, LPCTSTR lpszTitle = NULL);

	//@cmember
	/* Implements the overview window’s style settings at creation.*/
    TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
// Operations
public:
	//@Access Operations
	//@cmember
	/* Sets the rectangle representing the overview window.*/
    TOOLKIT_API void SetPanRect(CRect rectNewPan);

	//@cmember
	/* Draws the rectangle representing the overview window.*/
    TOOLKIT_API void DrawPanRect(CDC * pDC);

	TOOLKIT_API void InvalidateOverviewWnd(CRect * rectUpdate  = NULL );

	//@cmember
	/* Updates the overview window when the user scrolls or updates the panning view.*/
    TOOLKIT_API void OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint);

// Implementation
public:
    TOOLKIT_API virtual ~SECPanWnd();
#ifdef _DEBUG
	TOOLKIT_API void Dump(CDumpContext  &dc);
	TOOLKIT_API void AssertValid();
#endif //_DEBUG
    SECPanView * m_pPanView;        //Back pointer to view
    CRect        m_rectLogPan;      //The current viewport
    CSize        m_szLogDrag;       //The size of the rect being dragged
    BOOL         m_bCaptured;       //Is the mosue captured
    HCURSOR      m_hOverviewCursor; //Cursor for dragging the overview rect
	BOOL		 m_bClipVerified;	//Has the success of ClipOverviewCursor() been verified
	
    //Impementation specific helper functions for overview wnd.
    TOOLKIT_API void ClipOverviewCursor();
    TOOLKIT_API void OverviewDPtoLP(CPoint *);
    
    // Generated message map functions
protected:
    //{{AFX_MSG(SECPanWnd)
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnClose();
	//}}AFX_MSG
    TOOLKIT_API afx_msg void OnPaint();
    
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __SECPANWN_H__




