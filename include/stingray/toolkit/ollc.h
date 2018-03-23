///////////////////////////////////////////////////////////////////////////////
// ollc.h
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
//  Author:             Justin Rudd
//  Description:        Declarations for SECShortcutListCtrl
//  Created:            September 1997
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifdef WIN32

#ifndef __OLLC_H__
#define __OLLC_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXOLE_H__
#include <afxole.h>
#endif

#ifndef __SLSTCTL_H__
#include "toolkit\slstctl.h"
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

#define LVIS_EX_ICONUP			(0x0400)
#define LVIS_EX_ICONDOWN		(0x0800)

#define MOUSE_TIMER				(0xf0f0)

const UINT NM_LB_REORDERED 		= 1100;     // notification sent when items are 
                                       		// reordered
const UINT SEC_NM_ITEMCLICKED	= 1101;		// Notification of item clicked

// Structure utilized for extended information of SEC_NM_ITEMCLICKED notification
typedef struct SEC_SCNMHDR_tag {
	NMHDR nmhdr;
	int iSelItem;
} SEC_SCNMHDR;

/////////////////////////////////////////////////////////////////////////////
// SECShortcutListCtrl window

// Exported through base class. 
class SECShortcutListCtrl : public SECListCtrl
{
	TOOLKIT_DECLARE_DYNCREATE( SECShortcutListCtrl )

//Nested classes...
protected:
	enum
	{
		ScrollUp   = -10,
		ScrollDown = -11
	};

public:
	class ListDropTarget : public COleDropTarget
	{
	public:
		TOOLKIT_API ListDropTarget();

		TOOLKIT_API virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pData, DWORD dwKeyState, CPoint point );
		TOOLKIT_API virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pData, DWORD dwKeyState, CPoint point );
		TOOLKIT_API virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pData, DROPEFFECT de, CPoint point );
		TOOLKIT_API virtual void OnDragLeave( CWnd* pWnd );

		SECShortcutListCtrl* m_pList;

		enum
		{
			AboveTopItem    = -1,
			BelowBottomItem = -2
		};

	protected:
		TOOLKIT_API int GetItemAbovePoint( const CPoint& pt );
		TOOLKIT_API int GetItemBelowPoint( const CPoint& pt );

		CRect m_rcLastFilled;
		GUID  m_guidTemp;
	};

	friend class ListDropTarget;

protected:
	class ScrollButton
	{
	public:
		ScrollButton( BOOL bScrollUp );

		enum
		{
			Up,
			Down
		};

		TOOLKIT_API void  SetRect( const CRect& rcBtn );
		TOOLKIT_API CRect GetRect() const;

		TOOLKIT_API void ModifyState( long lRemove, long lAdd );

		TOOLKIT_API virtual void Draw( CDC* pDC );

	protected:
		CRect m_rcBtn;
		long  m_lState;
		BOOL  m_bScrollUp;

		friend class SECShortcutListCtrl;
	};

// Construction
public:
	TOOLKIT_API SECShortcutListCtrl();

// Attributes
protected:
	int m_iLastHitItem;
	SEC_UINT m_iTimerID;
    int m_iDeltaIni;

protected:
	TOOLKIT_API void StartTimer();
	TOOLKIT_API void StopTimer();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECShortcutListCtrl)
	//}}AFX_VIRTUAL
	TOOLKIT_API virtual int HitTest( CPoint pt, UINT* pFlags, int& iHitCol ) const;
	TOOLKIT_API virtual BOOL Update( int nItem, BOOL bLabelOnly = FALSE, BOOL bEraseBkgnd = TRUE, BOOL bUpdateBelow = FALSE );
	TOOLKIT_API virtual void DrawSeparator( CDC* pdc, const CRect& rcBounds, int iLoc );
	TOOLKIT_API virtual int  GetMargin() const;
	TOOLKIT_API virtual BOOL SetTextColor(COLORREF rgbText);
	TOOLKIT_API virtual BOOL DeleteItem( int nItem, int cCount = 1 );
	TOOLKIT_API virtual BOOL DeleteItem( Item* pItem );
	TOOLKIT_API virtual BOOL DeleteAllItems();

	TOOLKIT_API void	SetFlatStyleMode( BOOL bEnabled = TRUE );

protected:
	TOOLKIT_API virtual void RecalcLayout();
	TOOLKIT_API virtual void ClearMeasurements();

	TOOLKIT_API virtual void DrawInvalidItems( LvPaintContext* pPC );
	TOOLKIT_API virtual void DrawSubItemIcon( LvPaintContext* pPC );
	TOOLKIT_API virtual void DrawSubItemText( LvPaintContext* pPC );
	TOOLKIT_API virtual void DrawScrollButtons( LvPaintContext* pPC, LPSCROLLINFO pScrollInfo );

	TOOLKIT_API virtual BOOL PrepareDataForTransfer( COleDataSource* pData, LV_ITEM* pLVI );
	TOOLKIT_API virtual void ExtendContextMenu( CMenu& menu );

	TOOLKIT_API virtual ListDropTarget* CreateDropTarget() const;
	TOOLKIT_API virtual ScrollButton* CreateScrollUpButton() const;
	TOOLKIT_API virtual ScrollButton* CreateScrollDownButton() const;

	TOOLKIT_API virtual void DoScrollDown();
	TOOLKIT_API virtual void DoScrollUp();

	TOOLKIT_API virtual CPoint* GetLeftArrow( const CRect& rc, int iLoc );
	TOOLKIT_API virtual CPoint* GetRightArrow( const CRect& rc, int iLoc );

	TOOLKIT_API virtual void _Icon( int iItem, UINT nState );
	TOOLKIT_API virtual UINT _Icon( int iItem );

	TOOLKIT_API virtual void NotifySecSCNMHDR( UINT wNotify, LV_ITEM* pItem );

// Implementation
public:
	TOOLKIT_API virtual ~SECShortcutListCtrl();

	// Generated message map functions
protected:
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	TOOLKIT_API afx_msg void OnKillFocus( CWnd* pNewWnd );
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );
	TOOLKIT_API afx_msg void OnListMenu_LargeIcon();
	TOOLKIT_API afx_msg void OnListMenu_SmallIcon();
    TOOLKIT_API afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	TOOLKIT_API afx_msg void OnMButtonDown(UINT nFlags, CPoint pt);
	TOOLKIT_API afx_msg void OnSysColorChange();

	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
	ListDropTarget* m_pDropTarget;
	ScrollButton* m_pUpBtn;
	ScrollButton* m_pDownBtn;
	CPoint m_ptLastButtonDown;

	BOOL	m_bFlatStyleMode;

private:
	//Since static members don't come across process boundaries to well...we'll make it private...
	static GUID s_dragGuid;
	static BOOL s_bGuidCreated;
	static UINT s_clipformat;
};

typedef struct tagLISTDATA
{
	tagLISTDATA();

	GUID    guid;
	LV_ITEM item;
} LISTDATA, *PLISTDATA;

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __OLLC_H__
#endif // WIN32
