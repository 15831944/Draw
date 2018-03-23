///////////////////////////////////////////////////////////////////////////////
// sbardock.h
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
//  Description:	Declarations for SECDockBar / SECMiniDockFrameWnd
//  Created:		May 1996
//
//  LW, Mar 15, 1999
//  Added DECLARE_SECWRAPVIEW micro
//

#ifdef WIN32

#ifndef __SBARDOCK_H__
#define __SBARDOCK_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXPRIV_H__
#include "afxpriv.h"  // CDockBar is a private, undocumented MFC class that
                      // we subclass.  Hence, the necessity to include afxpriv.h
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
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

class SECControlBar;
class SECControlBarInfo;

// Operation types for SECDockBar::SetControlBarWidthsInRow
#define SEC_DOCKBAR_MAX_CONTROL_BAR				1
#define SEC_DOCKBAR_EVEN_SPACE_CONTROL_BARS		2


// DockBar extended styles
#define SEC_DOCKBAR_NOWEIGHT		(0x0001)

// Command ID range set and used by SECDockBar for the SEC-based control bars
#define SEC_IDW_CTRLBAR_FIRST			(0xE001)
#define SEC_IDW_CTRLBAR_LAST			(0xE0FF)

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Define DECLARE_SECWRAPVIEW Micro
//
// The DECLARE_SECWRAPVIEW micro generates a CView class which wrapped the specified view. The
// view generated will be the parent of the view being wrapped. The purpose of the wrap view is
// to solve the control view ( CEditView, CListView ... ) docking issue.
//
// You can use the micro as following,
//
// Suppose you have a CView derived class called CMyView. To wrap the CMyView class, you can
// declare a wrap class in your CWinApp derived class as this
//
//		DECLARE_SECWRAPVIEW(CMyView)
//
// and then, change the RUNTIME_CLASS parameter in the document template constructor from
// RUNTIME_CLASS(CMyView) to SECWRAPVIEW_RUNTIME_CLASS(CMyView) as this
//
//		SECMultiDocTemplate* pDocTemplate;
//		pDocTemplate = new SECMultiDocTemplate(
//			IDR_CTRLVITYPE,
//			RUNTIME_CLASS(CMyDoc),
//			RUNTIME_CLASS(CMyChildFrame), 
//			SECWRAPVIEW_RUNTIME_CLASS(CMyView)); 
//		AddDocTemplate(pDocTemplate);
//
// Note: Your view must handle the WM_MOUSEACTIVATE as following. Don't call CView's
// OnMouseActivate method. Otherwise, your view might receive extra OnActivateView calls.
//
//		int CMyView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
//		{
//			return 0;
//		}
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#define SECWRAPVIEW_RUNTIME_CLASS(class_name)	\
	(CRuntimeClass*) &(SEC_##class_name::class##SEC_##class_name)

#define DECLARE_SECWRAPVIEW(class_name)	\
	class SEC_##class_name : public CView			\
	{												\
	protected:										\
		SEC_##class_name() { m_pView = NULL; }		\
		DECLARE_DYNCREATE(SEC_##class_name)			\
													\
	/* Attributes */								\
		CView *m_pView;								\
	public:											\
		virtual void OnInitialUpdate()				\
		{											\
			CView::OnInitialUpdate();				\
													\
			CDocument* pDoc = (CDocument*) GetDocument();	\
			ASSERT(pDoc);									\
															\
			pDoc->AddView(m_pView);							\
			m_pView->OnInitialUpdate();						\
															\
			CMDIChildWnd *pWnd = (CMDIChildWnd*) GetParent();	\
			ASSERT(pWnd);										\
																\
			pWnd->SetActiveView(m_pView);						\
		}														\
	protected:													\
		virtual void OnDraw(CDC* /*pDC*/) {}					\
		virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)		\
		{																							\
			if (bActivate)																			\
			{																						\
				ASSERT(pActivateView == this || pActivateView == m_pView);							\
																									\
				CWnd *pWnd = CWnd::GetFocus();														\
																									\
				/* set the focus to the wrapped view if this frame/view/pane is now active */		\
				if (IsTopParentActive() && pWnd != m_pView && !m_pView->IsChild(pWnd))				\
					((CViewWithFriendship*) m_pView)->OnActivateView(bActivate, m_pView, pDeactiveView);	\
			} else {																						\
				ASSERT(pDeactiveView == this || pDeactiveView == m_pView);									\
				((CViewWithFriendship*) m_pView)->OnActivateView(false, pActivateView, m_pView);			\
			}																								\
		}																									\
	/* Implementation */							\
		virtual ~SEC_##class_name() {}				\
													\
		class CViewWithFriendship : public CView	\
	 		{ friend class SEC_##class_name; };		\
													\
	/* Generated message map functions */			\
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct)	\
		{													\
			if (CView::OnCreate(lpCreateStruct) == -1)		\
				return -1;									\
															\
			/* Create the wrapped view */					\
			CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(class_name);		\
																			\
			/* If this assert fires, it is because you did not override the GetViewClass method	  */ \
			/* or the RuntimeClass pointer returned from the GetViewClass is not the RuntimeClass */ \
			/* of a CView derived class.														  */ \
																									\
			ASSERT( pRuntimeClass && pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CView)) );			\
																									\
			m_pView = (CView*) pRuntimeClass->CreateObject();										\
			CRect r(0, 0, 0, 0);																	\
			m_pView->Create(NULL, NULL, lpCreateStruct->style, r, this, AFX_IDW_PANE_FIRST);						\
																									\
			return 0;																				\
		}																							\
																									\
		afx_msg void OnSize(UINT nType, int cx, int cy)												\
		{																							\
			CView::OnSize(nType, cx, cy);															\
																									\
			if (m_pView && ::IsWindow(m_pView->m_hWnd))												\
				m_pView->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);							\
		}																							\
																									\
		afx_msg int OnMouseActivate(CWnd* /*pDesktopWnd*/, UINT /*nHitTest*/, UINT /*message*/)	{ return 0; }		\
																									\
		TOOLKIT_DECLARE_MESSAGE_MAP()																		\
	};																								\
																									\
	IMPLEMENT_DYNCREATE(SEC_##class_name, CView)													\
	BEGIN_MESSAGE_MAP(SEC_##class_name, CView)														\
		ON_WM_CREATE()																				\
		ON_WM_SIZE()																				\
		ON_WM_MOUSEACTIVATE()																		\
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// End DECLARE_SECWRAPVIEW Micro
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// SECDockBar 

// class SECDockPos
// ----------------
//   defines a position (of a control bar) within an SECDockBar
//
// class SECDockSize
// -----------------
//   defines the size (of a control bar) within an SECDockBar
//
struct SECDockPos {
     int  m_iRow;
     int  m_iColumn;    
     unsigned long m_ulFlags;
     enum Flags { LAST_ROW_DELTA=0x1ul, LAST_COL_DELTA=0x2ul, INSERT_ROW=0x4ul };
     inline SECDockPos ( int c = 0, int r = 0, unsigned long x = 0 ) : m_iRow(r), m_iColumn(c), m_ulFlags(x) { }
};
struct SECDockSize {
     float m_fPctWidth;
     int   m_iHeight;
     unsigned long m_ulFlags; // currently unused
     inline SECDockSize ( float w = 1.0f, int h = 150, unsigned long x = 0 ) : m_fPctWidth(w), m_iHeight(h), m_ulFlags(x) { }
};

/////////////////////////////
// AutoDuck tag block block for SECDockBar 
// adinsert AutoDuck insertion point for SECDockBar 
//@doc SECDockBar 
//@class The SECDockBar class is derived from CDockBar. This class manages the 
// positioning and docking for all bars. Additional information specific to Objective
// Toolkit docking classes is stored in this class.
//@xref <c SECControlBar>
//@xref <c SECCustomToolBar>
class SECDockBar : public CDockBar
{
// Construction
public:
	TOOLKIT_DECLARE_DYNCREATE(SECDockBar) // QA: 31877
	//@cmember
	// Constructor
	TOOLKIT_API SECDockBar(BOOL bFloating = FALSE, BOOL bMDIChild = FALSE);
	//@cmember
	// Virtual Destructor
	TOOLKIT_API virtual ~SECDockBar();
	// bFloating is true if attached to SECMiniDockFrameWnd
	// bMDIChild is true if attached to SECControlBarMDIChildWnd

// Attributes
public:
	// Helper Class for Splitters
	class Splitter : public CObject	
	{
		public:
			enum Orientation	{ Horizontal, Vertical };
			enum Type			{ RowSplitter, BarSplitter };

			// Construction
			TOOLKIT_API Splitter(Type type, Orientation orientation, const RECT & rect);

			// Attributes
			TOOLKIT_API static const int	cx;
			TOOLKIT_API static const int	cy;
			int					m_nMin;
			int					m_nMax;
			int					m_nPos;
			// Enumerations

			enum Orientation	m_orientation;
			enum Type			m_type;
			
			CRect				m_rect;
			BOOL				m_bInUse;

		protected:
			CRect				m_rectLast;
			CSize				m_sizeLast;
			BOOL				m_bErase;          // TRUE if DrawTrackerRect is called for erasing
			BOOL				m_bFinalErase;     // TRUE if DragTrackerRect called for final erase

		// Operations
		public:
			TOOLKIT_API virtual void Draw(CDC *pDC);
			TOOLKIT_API int Track(CWnd* pWnd, CPoint point, CWnd* pWndClipTo);

 		// Implementation
		protected:
			TOOLKIT_API void DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd);
	};

	// Helper Class for Edges
	class ClientEdge : public CObject	
	{

		public:
			enum Orientation	{ Horizontal, Vertical };
			enum Orientation	m_orientation;
			// Construction
			ClientEdge(Orientation orientation, const RECT & rect);

			// Attributes
			TOOLKIT_API static const int	cx;
			TOOLKIT_API static const int	cy;
			
			CRect				m_rect;
			BOOL				m_bInUse;

		// Operations
		public:
			TOOLKIT_API virtual void Draw(CDC *pDC);
	};

	// Attributes
public:
 	static TOOLKIT_API BOOL m_bBorderClientEdge; // QA: 31877
	static TOOLKIT_API BOOL m_bEnableCntxtList;  // QA: 31877
	CPtrArray	m_arrInvalidBars;		// Array of control bars needing a repaint
	CObArray	m_arrEdges;				// Array of client edges
    CObArray    m_arrSplitters;			// Array of splitters
	BOOL		m_bMDIChild;
	DWORD		m_dwExDockStyle;

protected:
	AFX_SIZEPARENTPARAMS*	m_pLayout;     
	CControlBar*			m_pBarDocked;
	BOOL					m_bProcessingDelayedInvalidates;
	BOOL					m_bOptimizeNextRedraw;
	float					m_fAdjustedMinPctWidth;
	HTHEME					m_hReBarTheme;
	static TOOLKIT_API BOOL	m_bIsTracking;	// QA: 32241 - Are we tracking?

	// Maps command ID's to Control bars
	CMap<UINT, UINT, SECControlBar*, SECControlBar*> m_mapCmdIDtoBars;

public:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECDockBar)
	//@cmember
	TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );
    //}}AFX_VIRTUAL

// Implementation
public:
   
#ifdef _DEBUG
	//@cmember
	TOOLKIT_API virtual void	AssertValid() const;
	//@cmember
	TOOLKIT_API virtual void	Dump(CDumpContext& dc) const;
#endif
	//@cmember
	// Sizing
	TOOLKIT_API virtual BOOL	IsControlBarAtMaxWidthInRow(SECControlBar* pBar);
	//@cmember
	// Is the only controlbar in the row?
	TOOLKIT_API virtual BOOL	IsOnlyControlBarInRow(SECControlBar* pBar);
	//@cmember
	// Get controlbar size.
	TOOLKIT_API BOOL			GetBarSizePos(CControlBar* pBar,int& nRow,int& nCol,int& nHeight);
	//@cmember
	// Creation
	TOOLKIT_API BOOL			Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID) {return CDockBar::Create(pParentWnd, dwStyle, nID);}
	//@cmember
	// Creation
	TOOLKIT_API BOOL			Create(CWnd* pParentWnd, DWORD dwStyle, DWORD dwExStyle, UINT nID);
	//@cmember
	// Operations
	TOOLKIT_API void			DockControlBar(CControlBar* pBar, LPCRECT lpRect = NULL);
	//@cmember
	// Get controlbar row.
	TOOLKIT_API virtual BOOL	GetControlBarRow(CPtrList& rowList,SECControlBar* pBar);
	//@cmember
	// Set controlbar widths in row.
	TOOLKIT_API virtual void	SetControlBarWidthsInRow(SECControlBar* pBar,USHORT uOperationType);

	//@cmember
	// Drawing
	TOOLKIT_API virtual void	DoPaint(CDC* pDC);
	//@cmember
	// Redraw controlbar.
	TOOLKIT_API void			InvalidateBar(CControlBar* pBar);
	//@cmember
	// Redraw controlbar at position nPos.
	TOOLKIT_API void			InvalidateBar(int nPos);
	//@cmember
	// Redraw controlbars in row nPosRow.
	TOOLKIT_API void			InvalidateToRow(int nPosRow);
	//@cmember
	// Show/Hide controlbar.
	TOOLKIT_API virtual void	OnBarHideShow(CControlBar* pBar);
	//@cmember
	// Delay redraw messages.
	TOOLKIT_API virtual void	ProcessDelayedInvalidates();

	// Splitter/Client Edge Related function
	//@cmember
	// Splitter hittest.
    TOOLKIT_API Splitter*		HitTest(CPoint pt);
	//@cmember
	// Splitter tracking rect.
    TOOLKIT_API virtual void	StartTracking(Splitter* pSplit, CPoint pt);
	//@cmember
	// Get splitter.
    inline Splitter*			GetSplitter(int i) { return ((Splitter *)(m_arrSplitters[i])); };
	//@cmember
	// Add splitter.
    TOOLKIT_API virtual void	AddSplitter(Splitter::Type type, Splitter::Orientation orientation, int x1, int y1, int x2, int y2, int nPos);
	//@cmember
	// Calculate the tracking limits.
	TOOLKIT_API virtual void	CalcTrackingLimits(Splitter* pSplitter);
	//@cmember
	// Delete all splitters.
    TOOLKIT_API void			DeleteAllSplitters();
	//@cmember
	// Begin recycle splitters.
	TOOLKIT_API void			BeginRecycleSplitters();
	//@cmember
	// End recycle splitters.
	TOOLKIT_API void			EndRecycleSplitters();
	//@cmember
	// Add client edge.
    TOOLKIT_API virtual void	AddClientEdge(ClientEdge::Orientation orientation, int x1, int y1, int x2, int y2);
	//@cmember
	// Delete all edges.
    TOOLKIT_API void			DeleteAllEdges();
	//@cmember
	// Begin recycle edges.
	TOOLKIT_API void			BeginRecycleEdges();
	//@cmember
	// End recycle edges.
	TOOLKIT_API void			EndRecycleEdges();
	//@cmember
	// Invalidate custom toolbars in the row.
	TOOLKIT_API virtual void	InvalidateCustomToolBarsInRow(SECControlBar* pBar);

    // Queries / Attributes
	//@cmember
	// Is the controlbar new?
	TOOLKIT_API BOOL			IsNewBar(CControlBar* pBarToTest) const;
	//@cmember
	// Get the next controlbar in the row.
	TOOLKIT_API CControlBar*	NextBarThisRow(int nPos);
	//@cmember
	// Get the next visible controlbar in the row.
	TOOLKIT_API CControlBar*	NextVisibleBarThisRow(int nPos);
	//@cmember
	// Get the previous controlbar in the row.
	TOOLKIT_API CControlBar*	PrevBarThisRow(int nPos);
	//@cmember
	// Get the previous visible controlbar in the row.
	TOOLKIT_API CControlBar*	PrevVisibleBarThisRow(int nPos);
	//@cmember
	// Get the first controlbar.
    TOOLKIT_API SECControlBar*	GetFirstControlBar ();
	//@cmember
	// Is the controlbar new to the row?
	TOOLKIT_API BOOL			BarIsNewToThisRow(CControlBar* pBarToTest, int nCurrentRow) const;
	//@cmember
	// Get the row height.
	TOOLKIT_API int				GetRowHeight(int nPos) const;
	//@cmember
	// Get SECControlBarInfo
	TOOLKIT_API void			GetBarInfo(SECControlBarInfo* pInfo);
	//@cmember
	// Set SECControlBarInfo
	TOOLKIT_API void			SetBarInfo(SECControlBarInfo* pInfo, CFrameWnd* pFrameWnd);
	//@cmember
	// Get the row start position.
	TOOLKIT_API int				RowStartPosition(int nRow) const;

	// Layout
	//@cmember
	// Calculate the fixed layout.
	TOOLKIT_API virtual CSize	CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	//@cmember
	// Calculate the docking layout.
	TOOLKIT_API virtual CRect	CalcDockingLayout(CControlBar* pBarToDock, CRect& rectBar, CPoint pt, int& nPosDockingRow, CRect& prevFocusRect, CPoint& prevPt);
	//@cmember
	// Set the row height.
	TOOLKIT_API void			SetRowHeight(int nPos, int nRowHeight);
	//@cmember
	// Adjust the row height.
	TOOLKIT_API void			AdjustRowHeight(int nPos, int nWidth);

	// Docking
	//@cmember
	// Dock the controlbar based on column and row.
	TOOLKIT_API virtual void	DockControlBar(CControlBar* pBar, int nCol, int nRow);
	//@cmember
	// Dock the controlbar based on SECDockPos. 
	TOOLKIT_API virtual void	DockControlBar(CControlBar* pBar, const SECDockPos & rPos); 
	//@cmember
	// Redock the controlbar. 
	TOOLKIT_API virtual void	ReDockControlBar(CControlBar* pBar, LPCRECT lpRect = NULL);
	//@cmember
	// Remove controlbar.
	TOOLKIT_API virtual BOOL    RemoveControlBar(CControlBar*, int nPosExclude = -1, int bAddPlaceHolder = FALSE);
	//@cmember
	// OnSplitterMoved handler.
	TOOLKIT_API virtual void	OnSplitterMoved(Splitter* pSplitter, int nDelta);
	//@cmember
	// CDockBar override:  to repair a defect
	TOOLKIT_API virtual int		GetDockedVisibleCount() const;

    // Layout
protected:
	//@cmember
	// Normalize the row.
	TOOLKIT_API virtual void	NormalizeRow(int nPos, CControlBar* pBarDocked, int& nBarsBidirectional, int& nBarsUnidirectional);
	//@cmember
	// Calculate latest min/max percentage width.
	TOOLKIT_API virtual void	CalcLatestMinMaxPctWidth();
	//@cmember
	// Apply percentage witdh overlap.
	TOOLKIT_API virtual float	ApplyPctWidthOverlap(float fOverlap,SECControlBar* pBar);
	//@cmember
	// Predict insert position.
	TOOLKIT_API int				PredictInsertPosition(CControlBar* pBarIns, CRect rect, CPoint ptMid);

	// Implementation helpers
	//@cmember
	// Insert controlbar.
	TOOLKIT_API virtual int		Insert(CControlBar* pBarIns, int nInsCol, int nInsRow);
	//@cmember
	// Insert controlbar.
	TOOLKIT_API virtual int		Insert(CControlBar* pBarIns, const SECDockPos & rPosIns);
	//@cmember
	// Insert controlbar.
	TOOLKIT_API virtual int		Insert(CControlBar* pBar, CRect rect, CPoint ptMid);
	//@cmember
	// Insert controlbar as first row.
	TOOLKIT_API virtual int		InsertAsFirstRow(CControlBar* pBarIns);
	//@cmember
	// Insert controlbar. 
	TOOLKIT_API virtual int		InsertRowBar(int nPos,CControlBar* pBarIns);
	//@cmember
	// Adjust controlbar width by delta.
	TOOLKIT_API int				AdjustBarWidthByDelta(SECControlBar* pBar,int nDelta,const CSize& sizeMax);
public:
    // AutoHide Helper
	//@cmember
	// Find the autohide top row dock position.
    TOOLKIT_API int             FindAutoHideTopRowDockPos();
	//@cmember
	// QA: 32241 - Are we tracking? 
	inline BOOL IsTracking() { return m_bIsTracking; }

    // Generated message map functions
protected:
    //{{AFX_MSG(SECDockBar)
	//@cmember
	// OnCreate handler.
	TOOLKIT_API afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	//@cmember
	// OnSetCursor handler.
	TOOLKIT_API afx_msg BOOL	OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//@cmember
	// OnMouseMove handler.
	TOOLKIT_API afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	// OnLButtonDown handler.
	TOOLKIT_API afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	//@cmember
	// OnContextMenu handler.
	TOOLKIT_API afx_msg void	OnContextMenu(CWnd* pWnd, CPoint pos );
	//@cmember
	// OnCtrlBarCmdRange handler.
	TOOLKIT_API afx_msg void	OnCtrlBarCmdRange(UINT nID);
	//@cmember
	// OnDestroy handler.
	TOOLKIT_API afx_msg void	OnDestroy();
	//@cmember
	// OnSizeParent handler.
	TOOLKIT_API afx_msg LRESULT OnSizeParent(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnEraseBkgnd handler.
	TOOLKIT_API afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	//@cmember
	// OnThemeChagned handler.
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API afx_msg LRESULT OnThemeChanged();
	#endif
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP()

	friend class SECMiniDockFrameWnd;
	friend class SECDockContext;
};


class SECMiniDockFrameWnd : public CMiniDockFrameWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECMiniDockFrameWnd)

public:
// Construction
	TOOLKIT_API SECMiniDockFrameWnd();
	TOOLKIT_API virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);

// Implementation
public:
	SECDockBar m_wndSECDockBar;

// Operations
	//@cmember
	// Recalculate layout.
	TOOLKIT_API virtual void RecalcLayout(CPoint point, BOOL bNotify = TRUE);
	//@cmember
	// Recalculate layout.
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify = TRUE);

	//{{AFX_MSG(CMiniFrameWnd)
	//@cmember
	// OnClose handler.
	TOOLKIT_API afx_msg void OnClose();
	//@cmember
	// OnNcLButtonDown handler.
	TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//@cmember
	// OnNcLButtonDbClk handler.
	TOOLKIT_API afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	//@cmember
	// OnParentNotify handler.
	TOOLKIT_API afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG
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

#endif // __SBARDOCK_H__

#endif // WIN32
