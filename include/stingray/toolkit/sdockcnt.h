///////////////////////////////////////////////////////////////////////////////
// sdockcnt.h
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
//  Author:			Dean Hallman
//  Description:	Declarations for SECDockContext
//  Created:		May 1996
//
#ifndef UNDER_CE
#if defined(WIN32) 

#ifndef __SDOCKCNT_H__
#define __SDOCKCNT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

// CDockBar is an private, undocumented MFC class that we subclass.
// Hence, the necessity to include afxpriv.h
#ifndef __AFXPRIV_H__
#include <afxpriv.h>
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

/////////////////////////////////////////////////////////////////////////////
// SECDockContext

// Forward Declarations
class SECDockBar;
class SECControlBar;

class SECDockContext : public CDockContext
{
// Construction
public:
    TOOLKIT_API SECDockContext(CControlBar* pBar);

// Attributes
protected:
	CRect m_rectFocus;
	CPoint m_ptStartDrag;
	CPoint m_ptPrev;
	int m_nPosDockingRow;
	BOOL m_bPreviouslyFloating;  // After unfloat as MDI child,
									// should we dock or float it

	CSize m_sizeMinTrack;      // Minimum tracking size
	CSize m_sizeMaxTrack;      // Maximum tracking size

// Operations
public:

// Double Click Operations
	TOOLKIT_API virtual void ToggleDocking();
	TOOLKIT_API virtual void ToggleMDIFloat();

// Drag Operations
	TOOLKIT_API virtual void StartDrag(CPoint pt);
	TOOLKIT_API void Move(CPoint pt);       // called when mouse has moved
	TOOLKIT_API void EndDrag();             // drop

	// Resize Operations
	TOOLKIT_API virtual void StartResize(int nHitTest, CPoint pt);
	TOOLKIT_API void Stretch(CPoint pt);
	TOOLKIT_API void EndResize();

	// Minimum and maximum tracking size
	TOOLKIT_API CSize GetMinTrackingSize();
	TOOLKIT_API void SetMinTrackingSize(int cx, int cy);
	TOOLKIT_API void SetMinTrackingSize(CSize szMin);

	TOOLKIT_API CSize GetMaxTrackingSize();
	TOOLKIT_API void SetMaxTrackingSize(int cx, int cy);
	TOOLKIT_API void SetMaxTrackingSize(CSize szMax);

// Operations
	TOOLKIT_API void CancelLoop();

// Implementation
public:
    TOOLKIT_API virtual ~SECDockContext();
    TOOLKIT_API BOOL Track();
    TOOLKIT_API virtual void DrawFocusRect(BOOL bRemoveRect = FALSE);
	TOOLKIT_API DWORD CanDock();

	friend class SECControlBar;
};

inline
CSize SECDockContext::GetMinTrackingSize()
{
	return m_sizeMinTrack;
}

inline
void SECDockContext::SetMinTrackingSize(int cx, int cy)
{
	m_sizeMinTrack = CSize(cx,cy);
}

inline
void SECDockContext::SetMinTrackingSize(CSize szMin)
{
	m_sizeMinTrack = szMin;
}

inline
CSize SECDockContext::GetMaxTrackingSize()
{
	return m_sizeMaxTrack;
}

inline
void SECDockContext::SetMaxTrackingSize(int cx, int cy)
{
	m_sizeMaxTrack = CSize(cx,cy);
}

inline
void SECDockContext::SetMaxTrackingSize(CSize szMax)
{
	m_sizeMaxTrack = szMax;
}

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SDOCKCNT_H__

#endif // WIN32
#endif  //UNDER_CE (WindowsCE)
