///////////////////////////////////////////////////////////////////////////////
// tbtnwnd.h
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
//  Authors:		Don
//  Description:	Declarations for SECWndBtn
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBTNWND_H__
#define __TBTNWND_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TBTNSTD_H__
#include "toolkit\tbtnstd.h"
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

// Define the hotspot width which a SECWndBtn will use for resizing
#define SEC_WNDBTN_RESIZE_WIDTH		3

///////////////////////////////////////////////////////////////////////////////
// SECWndBtn class
//
class SECWndBtn : public SECStdBtn
{
// Construction
public:
	TOOLKIT_API SECWndBtn();

// Attributes
public:
	enum NotifyCodes		// Notification codes sent with
	{						// wmSECToolBarWndNotify
		NBase   = 0x0100,
		WndInit = NBase + 1	// CWnd has been created and needs initialisation.
	};

	enum InformCode			// Codes informing us to take some kind of action
	{
		IBase   = 0x0100,
		WndMsg  = IBase + 1	// Dispatch message to CWnd
	};

// Operations
public:
	// SetMode informs the button when the button either enters/leaves a
	// vertically docked state
	TOOLKIT_API virtual void SetMode(BOOL bVertical);

   // Sets the style for this button
	TOOLKIT_API virtual void SetStyle(UINT nStyle);

	// Modifies our window position
	TOOLKIT_API virtual void SetPos(int x, int y);

	// Invalidates the button
	TOOLKIT_API virtual void Invalidate(BOOL bErase = FALSE) const;

	// CWnd passes messages here first.
	TOOLKIT_API virtual BOOL LButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL LButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL LButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL RButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL RButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL RButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API BOOL SetCursor();

// Overrideables
public:
	// Called when the button is hidden or unhidden.
	TOOLKIT_API virtual void OnHide();

protected:
	TOOLKIT_API void PrePaint();
	TOOLKIT_API void PostPaint();
	TOOLKIT_API void ForwardMessage(UINT nMessage, WPARAM wParam = 0, LPARAM lParam = 0);

	// Pass on a notification to the toolbar owner
	TOOLKIT_API void SendNotify(UINT nCode);

// Overrideables
public:
	// Initialises button after creation.
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);

	// Draw the button
	TOOLKIT_API virtual void DrawButton(CDC& dc, SECBtnDrawData& data);

	// Tool-tip/flyby help hit-testing
	TOOLKIT_API virtual int  OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	// Informs button of some event
	TOOLKIT_API virtual void InformBtn(UINT nCode, void* pData);

	// Functions called when saving/loading a toolbar state, allowing the
	// button to save state info.
	TOOLKIT_API virtual void GetBtnInfo(BYTE* nSize, LPBYTE* ppInfo) const;
	TOOLKIT_API virtual void SetBtnInfo(BYTE nSize, const LPBYTE pInfo);

	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	TOOLKIT_API virtual void AdjustSize();

protected:
	virtual CWnd* GetWnd() = 0;			// Returns pointer to our CWnd

	// Creates our CWnd
	virtual BOOL CreateWnd(CWnd* pParentWnd, DWORD dwStyle, CRect& rect, 
						   int nID) = 0;

// Implementation
public:
	inline virtual ~SECWndBtn() {}

protected:
	// Implementation, data members.
	static HCURSOR hCurHorzDrag;// Shared cursor - used when resizing
	BOOL  m_bWndVisible;		// CWnd is currently visible (not vert. docked)
	int   m_nSize;				// Width of CWnd.
	int   m_nMinSize;			// Minimum width of CWnd.
	int   m_nHeight;			// Wanted Height of CWnd.
	int   m_nRealHeight;		// Actual Height of CWnd.
};

// CWndBtn helper macro
#define WND_BUTTON(class, id, wndId, style, wndStyle, wndDefWidth, \
				   wndMinWidth, wndHeight) \
	{class, id, style|TBBS_BUTTON|SEC_TBBS_NODISABLE, wndId, wndStyle, MAKELONG(wndDefWidth, \
     wndMinWidth), wndHeight, 0},

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBTNWND_H__

#endif // WIN32
