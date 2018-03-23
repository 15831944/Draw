///////////////////////////////////////////////////////////////////////////////
// StartDragCore.h
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
// Description:  Declaration of SECStartDragCore_T 
//

#ifndef __SEC_START_DRAG_CORE_H__
#define __SEC_START_DRAG_CORE_H__

#ifdef WIN32

// Header Includes
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

// Warning 4211 (redefined extern to static) is an intentional byproduct
// of the SECBEGIN_MESSAGE_MAP macro usage in StartDragCore.cpp that
// allows usage of the message map in a templatized CWnd decorator.
// Disable this warning only during reference to this 1 header 
// (restored below)
#pragma warning(disable : 4211)

// Constants
#define SEC_STARTDRAGCORE_DEFAULT_DRAG_THRESHOLD_DIST	1.0f

extern TOOLKIT_API CPoint SecGetScreenMousePoint(HWND hWnd,LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// SECStartDragCore_T

// Templatized base class passed in should be SECWndListener derived!

template <class ListenerBaseClass>
class SECStartDragCore_T : public ListenerBaseClass
{
public:

	// Initialization/Destruction
	inline SECStartDragCore_T() {
		m_bPossibleDrag=FALSE;
		m_ptScreenLastLButtonDown=CPoint(0,0);
		m_fDragThresholdDistance=SEC_STARTDRAGCORE_DEFAULT_DRAG_THRESHOLD_DIST;
	}
	inline virtual ~SECStartDragCore_T() {}
	
	// Distance to drag the mouse before initiating drag/drop sequence
	double m_fDragThresholdDistance;

	// Operations
	TOOLKIT_API virtual BOOL RelayEvent(MSG* pMsg);

protected:

	// override to test the initiation of a drag
	inline virtual BOOL TestDragStartPoint(UINT  /* nKeyFlags */, const CPoint& /* ptScreenTest */) 
	{ return TRUE; }

	// Override this function to handle a drag initiation
	TOOLKIT_API virtual BOOL OnStartDragDrop(UINT nKeyFlags,
								const CPoint& ptScreenLButtonDown,
								const CPoint& ptScreenMouseMove);

	// Override this function for custom behavior on a toggle event
	// that occurs in response to a double click operation
	TOOLKIT_API virtual BOOL OnDragDropToggleEvent(UINT nKeyFlags,
								const CPoint& ptScreenEvent);

protected:

	// Implementation Member Variables
	BOOL m_bPossibleDrag;
	CPoint m_ptScreenLastLButtonDown;

	// Implementation Member Functions
	TOOLKIT_API virtual BOOL HandleLButtonDown(UINT nFlags,const CPoint& ptScreen);
	TOOLKIT_API virtual BOOL HandleLButtonUp(UINT nFlags,const CPoint& ptScreen);
	TOOLKIT_API virtual BOOL HandleLButonDblClk(UINT nFlags,const CPoint& ptScreen);	
	TOOLKIT_API virtual BOOL HandleMouseMove(UINT nFlags,const CPoint& ptScreen);
	TOOLKIT_API virtual CPoint ScreenPtFromMSG(MSG* pMsg);

	// Generated message map functions
	//{{AFX_MSG(SECStartDragCore_T)
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnNcMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:

	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:

};

// Restore compilation warning 4211 (see comments at top of file)
// Note: compiler pop will only occur correctly on VC version 6.0 and above
#if _MFC_VER >= 0x0600
#pragma warning(default : 4211)
#endif

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// WIN32

#endif  //__SEC_START_DRAG_CORE_H__
