///////////////////////////////////////////////////////////////////////////////
// Splitter.h : Declaration of SECSplitterBase
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
// Description:  Declaration of SECSplitterBase
//

#ifndef __SECSPLITTERBASE_H
#define __SECSPLITTERBASE_H

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

#define SEC_DEF_SPLITTER_ID 0xedef	// choose a unique, non-conflicting id

// Splitter flags
#define SEC_SPLITTER_REALTIME_DRAG	0x0001
#define SEC_SPLITTER_SPAN_ROWS		0x0002

//@doc SECSplitterBase
//@mfunc DWORD  | SECSplitterBase | GetSplitterFlags | Gets the splitter style flags.
//@xref <c SECSplitterBase>

//@doc SECSplitterBase
//@mfunc void  | SECSplitterBase | SetSplitterFlags | Sets the splitter style flags.
//@parm DWORD | dwFlags | New splitter style flags.
//@xref <c SECSplitterBase>

//@doc SECSplitterBase
//@mfunc void  | SECSplitterBase | SetSplitterWidth | Set the pixel width of the splitter bar itself.
//@parm int | nNewWidth | New splitter width in pixels.
//@xref <c SECSplitterBase>

//@doc SECSplitterBase
//@mfunc void  | SECSplitterBase | SetDrawingStyle | Set the splitter drawing style for this 
// specific instance, overriding default style.
//@xref <c SECSplitterBase> <mf SECSplitterBase::GetDrawingStyle>

//@doc SECSplitterBase
//@mfunc DWORD  | SECSplitterBase | GetDrawingStyle | Get the splitter drawing style for this instance.
//@xref <c SECSplitterBase> <mf SECSplitterBase::SetDrawingStyle>

/////////////////////////////////////////////////////////////////////////////
// SECSplitterPaneInfo

//@doc SECSplitterPaneInfo 
//@class Pane information for SECSplitterBase
class SECSplitterPaneInfo : public CObject 
{
	TOOLKIT_DECLARE_DYNAMIC(SECSplitterPaneInfo);

public:
	// Intialization/Destruction
	TOOLKIT_API SECSplitterPaneInfo();
	virtual ~SECSplitterPaneInfo() {}

	//@cmember
	/* Set the NorthWest pane rectangle*/
	TOOLKIT_API void SetPaneRectNW(LPCRECT pRectPane);

	//@cmember
	/* Get the NorthWest pane rectangle*/
	TOOLKIT_API BOOL GetPaneRectNW(CRect& rectPane);

	//@cmember
	/* Set the NorthEast pane rectangle*/
	TOOLKIT_API void SetPaneRectNE(LPCRECT pRectPane);

	//@cmember
	/* Get the NorthEast pane rectangle*/
	TOOLKIT_API BOOL GetPaneRectNE(CRect& rectPane);

	//@cmember
	/* Set the SouthWest pane rectangle*/
	TOOLKIT_API void SetPaneRectSW(LPCRECT pRectPane);

	//@cmember
	/* Get the SouthWest pane rectangle*/
	TOOLKIT_API BOOL GetPaneRectSW(CRect& rectPane);

	//@cmember
	/* Set the SouthEast pane rectangle*/
	TOOLKIT_API void SetPaneRectSE(LPCRECT pRectPane);

	//@cmember
	/* Get the SouthEast pane rectangle*/
	TOOLKIT_API BOOL GetPaneRectSE(CRect& rectPane);

protected:
	CRect m_rectPaneNW,m_rectPaneNE,m_rectPaneSW,m_rectPaneSE;
	BOOL m_bPaneNW,m_bPaneNE,m_bPaneSW,m_bPaneSE;

	TOOLKIT_API BOOL GetPaneRect(CRect& rectPane,const CRect& rectMember,BOOL bMember);
	TOOLKIT_API void SetPaneRect(LPCRECT pRectPane,CRect& rectMember,BOOL& bMember);
};


/////////////////////////////////////////////////////////////////////////////
// SECSplitterBase

// Splitter drawing styles
#define SEC_SPLITTERBASE_DRAW_GLOBAL_SETTING	0x0001
#define SEC_SPLITTERBASE_DRAW_TRADITIONAL		0x0002
#define SEC_SPLITTERBASE_DRAW_FLAT				0x0004
#define SEC_SPLITTERBASE_DRAW_BORDER			0x0008

//@doc SECSplitterBase 
//@class Base Stingray splitter functionality
//@BASE public | CWnd
class SECSplitterBase : public CWnd
{
	TOOLKIT_DECLARE_DYNAMIC(SECSplitterBase);

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECSplitterBase();
	TOOLKIT_API virtual ~SECSplitterBase();

	//@access Initialization
	//@cmember
	/* Create the splitter window*/
	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd,CRect rect=CRect(0,0,0,0),
				DWORD dwStyle=WS_CHILD|WS_VISIBLE,
				UINT nID=SEC_DEF_SPLITTER_ID,DWORD dwFlags=0);

	//@access Accessors
	//@cmember
	/* Set the width of the splitter control itself.*/
	TOOLKIT_API static void SetSplitterWidth(int nNewWidth);
	TOOLKIT_API static int GetSplitterWidth();

	// Splitter drawing style
	// Use the static's for easy access, or the member functions to override
	// the global setting (local style used if not SEC_SPLITTERBASE_DRAW_GLOBAL_SETTING)

	//@cmember
	/* Set the default splitter drawing style */
	TOOLKIT_API static void SetDrawingStyleAll(DWORD dwStyle=SEC_SPLITTERBASE_DRAW_TRADITIONAL);

	//@cmember
	/* Get the default splitter drawing style */
	TOOLKIT_API static DWORD GetDrawingStyleAll();

	//@cmember
	/* Set the splitter drawing style for this specific instance, overriding default style */
	inline void SetDrawingStyle(DWORD dwStyle=SEC_SPLITTERBASE_DRAW_TRADITIONAL) { m_dwDrawingStyle=dwStyle; }

	//@cmember
	/* Get the splitter drawing style for this instance */
	inline DWORD GetDrawingStyle() { return m_dwDrawingStyle; }

	//@cmember
	/* Get the current splitter flags*/
	inline DWORD GetSplitterFlags()			{ return m_dwFlags; }

	//@cmember
	/* Set the current splitter flags.*/
	TOOLKIT_API void SetSplitterFlags(DWORD dwFlags);

	//@cmember
	/* Fit splitter window inside specified bounding margins*/
	TOOLKIT_API void SetBoundingMargins(int nLeft=0,int nRight=0,int nTop=0,int nBottom=0);

	//@cmember
	/* Get the bounding margins for the splitter window*/
	TOOLKIT_API void GetBoundingMargins(int& nLeft,int& nRight,int& nTop,int& nBottom);

	//@cmember
	/* Set x,y position of the splitter*/
	TOOLKIT_API virtual void SetSplitterPositions(int xColPos=0,int yRowPos=0);

	//@cmember
	/* Get x,y position of the splitter*/
	TOOLKIT_API void GetSplitterPositions(int& xColPos,int& yRowPos);

	// Operations
	//@access Operations
	//@cmember
	/* Add a pane to the splitter window*/
	TOOLKIT_API virtual BOOL AddPane(USHORT nRow,USHORT nCol);
	//@cmember
	/* Remove a pane from the splitter window*/
	TOOLKIT_API virtual BOOL RemovePane(USHORT nRow,USHORT nCol);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// Override this with your own pane display logic
	//@access Overridables
	//@cmember
	/* Pane positions are changing*/
	TOOLKIT_API virtual void OnSetPanePositions(SECSplitterPaneInfo* pPaneInfo);

	//@cmember
	/* Render the splitters*/
	TOOLKIT_API virtual void OnDrawSplitters(CDC* pDC);

	//@cmember
	/* Render the row splitter*/
	TOOLKIT_API virtual void OnDrawSplitterRow(CDC* pDC,const CRect& rectRow,
								   const CRect& rectCol);

	//@cmember
	/* Render the column splitter*/
	TOOLKIT_API virtual void OnDrawSplitterCol(CDC* pDC,const CRect& rectRow,
								   const CRect& rectCol);

	//@cmember
	/* Render the row splitter with the "flat look" */
	TOOLKIT_API virtual void OnDrawSplitterRowFlat(CDC* pDC,const CRect& rectRow,
								   const CRect& rectCol);

	//@cmember
	/* Render the column splitter with the "flat look" */
	TOOLKIT_API virtual void OnDrawSplitterColFlat(CDC* pDC,const CRect& rectRow,
								   const CRect& rectCol);

	//@cmember
	/* Render the row splitter with the "border look" */
	TOOLKIT_API virtual void OnDrawSplitterBorderLook(CDC* pDC,const CRect& rectDraw);

	//@cmember
	/* Splitter drag operation is starting*/
	TOOLKIT_API virtual BOOL OnSplitterDragStart(CPoint point,BOOL bRowSplitter,
									 BOOL bColSplitter);

	//@cmember
	/* Splitter drag operation has completed*/
	TOOLKIT_API virtual void OnSplitterMoved(int deltaX,int deltaY);

	//@cmember
	/* Splitter has been invalidated*/
	TOOLKIT_API virtual void OnSplitterInvalidate(CRect rectInvalid,BOOL bErase);

	//@cmember
	/* Splitter is moving*/
	TOOLKIT_API virtual void OnTrackMouseMove(CDC* pDC,int pointX,int pointY,
								  CRect& rectRow,CRect& rectCol,
								  BOOL bRowSplitter,BOOL bColSplitter);

	// Overridables for custom splitter implementation
	virtual HDC GetTrackerDC() { return ::GetDC( GetSafeHwnd() ); }

	virtual void ConvertTrackerCoordinates(CRect&,CRect&) {} // No-Op for base class
	TOOLKIT_API virtual BOOL GetSplitterBoundaries(int& nBoundLeft,int& nBoundTop,
									int& nBoundRight,int& nBoundBottom);
	TOOLKIT_API virtual CSize OnAdjustFinalSplitterRect(CRect& rectSplitter,
									const CRect& rectClient,BOOL bRowSplitter);

	virtual BOOL OnPrepareDC(CDC*) { return TRUE; }

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	DWORD m_dwFlags;
	BOOL  m_bPaneNW,m_bPaneNE,m_bPaneSW,m_bPaneSE;
	int   m_nRowYOffset,m_nColXOffset;				// relative splitter offsets
	CRect m_rectRowSplitter,m_rectColSplitter;		// physical splitter positions
	CRect m_rectRowSplitterClient,m_rectColSplitterClient;	// relative splitter positions
	CRect m_rectClient;

	// Splitter orientations. 
	enum SplitterRowOrient { LEFT, RIGHT, WIDTH, NOROW };
	SplitterRowOrient m_orientRow;
	enum SplitterColOrient { TOP, BOTTOM, HEIGHT, NOCOL };
	SplitterColOrient m_orientCol;

	// For splitter track
	BOOL m_bInStartTracking;
	CRect m_rectLastRowTracker,m_rectLastColTracker;
	CSize m_sizeLastRowTracker,m_sizeLastColTracker;
	int m_nMarginLeft,m_nMarginRight,m_nMarginTop,m_nMarginBottom;
	TOOLKIT_API static int m_nSplitterWidth;

	// Splitter Drawing
	TOOLKIT_API static DWORD m_dwDrawingStyleAll;
	BOOL m_dwDrawingStyle;

	// Implementation Member Functions
	TOOLKIT_API virtual void CalcNeededSplitters();
	TOOLKIT_API virtual BOOL MoveSplitter(const CRect& rectOld,const CRect& rectNew,BOOL bRow);
	TOOLKIT_API virtual BOOL MoveAndSetSplitter(const CRect& rectNew,BOOL bRow);
	TOOLKIT_API virtual void SplitterHitTest(CPoint point,BOOL& bRowSplitter,
								 BOOL &bColSplitter);
	TOOLKIT_API virtual void RecalcSplitterRects(CRect& rectRowSplitter,
									 CRect& rectColSplitter,
									 int& xPosColSplitter,
									 int& yPosRowSplitter);
	TOOLKIT_API virtual void RecalcSplitterRects();
	TOOLKIT_API virtual void RefreshSplitterClientRects();
	TOOLKIT_API virtual void StartTracking(CPoint point,BOOL bRowSplitter,
							   BOOL bColSplitter);
	TOOLKIT_API virtual CSize Track(CPoint point,BOOL bRowSplitter,BOOL bColSplitter);
	TOOLKIT_API virtual void DrawTrackerRect(const CRect& RectTracker,CDC* pDC,BOOL bRow,
								 BOOL bErase=FALSE);
	TOOLKIT_API virtual void TrackMessageLoop(CDC* pDC,BOOL bRowSplitter,BOOL bColSplitter,
								  CRect& rectRow,CRect& rectCol);
	TOOLKIT_API virtual void ResetPanePositions();
	TOOLKIT_API virtual void ResetPanePositions(const CRect& rectRow,const CRect& rectCol);
	TOOLKIT_API virtual void PumpPaintMessages();
	TOOLKIT_API void InitCursorsIfNeeded();
	TOOLKIT_API virtual DWORD SECSplitterBase::ResolveAppropDrawingStyle();

	//---------------------------------------------------------------------//
	// 						Message Map Declarations					   //
	//---------------------------------------------------------------------//

	// Generated message map functions
	//{{AFX_MSG(SECSplitterBase)
    TOOLKIT_API afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnPaint();
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


#endif // __SECSPLITTERBASE_H__

