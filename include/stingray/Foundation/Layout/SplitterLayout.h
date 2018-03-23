///////////////////////////////////////////////////////////////////////////////
// SplitterLayout.h : SFL Layout Manager
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
// Author:       Gilberto Araya
// Description:  Splitter layout
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4876)
	#pragma warning(disable:4284) // STL, not a UDT or reference to a UDT. Errors if infix notation used.
#endif


#include <foundation\SflCommon.h>
#include <foundation\Layout\DCNode.h>
#include <deque>
#include <foundation\Layout\LayoutNode.h>
#include <foundation\Layout\SplitterLayout.h>
#include <foundation\Graphics\GraphicContext.h>
#include <Foundation\sflres.h>
#include <foundation\stwarn.h>
#include <stdexcept>
#include <foundation\stwarnp.h>


#pragma warning(disable: 4275)

/////////////////////////////////////////////////////////////////////
// Resource identifiers for the special splitter cursors

namespace stingray {
namespace foundation {


//@doc


//@enum SplitterFlags |
// Configuration flags that can be applied to splitter nodes
// to control diverse aspects of their appearance.
FOUNDATION_API enum SplitterFlags {
	SplitterRealtimeDrag = 0x0001,	//@emem Enable real time dragging: windows are moved as the splitter is dragged, 
									//providing immediate feedback to the user.
	SplitterBottomBorder = 0x0002,	//@emem Draw the bottom border of the splitter node.
	SplitterRightBorder = 0x0004,	//@emem Draw the right border of the splitter node.
	SplitterBorders = 0x0006,		//@emem Combination of SplitterBottomBorder and SplitterRightBorder.
	SplitterNoSplitters = 0x0008	//@emem Do not provide draggable splitters. Simulates a grid layout.
};


//@enum SplitterDrawingStyle |
// Style used by the splitter node to draw the splitter bars.
FOUNDATION_API enum SplitterDrawingStyle {
	DrawGlobalSetting = 0x0000,	
	DrawTraditional = 0x0001,		//@emem Traditional splitters, with pronounced 3-D effect. Similar to the MFC splitters.
	DrawFlat = 0x0002,				//@emem Splitter bars with a flatter 3-D effect, similar to the VB or VJ environments.
	DrawBorder = 0x0004				//@emem Splitter bars with no 3-D effect at all, drawn just as spaces separating the splitter cells.
};



//@interface ISplitter |
//  Provides all the accessors and methods to control the operation
//  of a splitter layout node.
//@base  | ILayoutNode
interface __declspec(uuid("8B1647C2-45E5-11d3-9D92-00C04F91E286")) ISplitter
: public ILayoutNode
{
	//@prop,property int | Get/SetSplitterWidth |
	// Sets or retrieves the thickness in pixels of the splitter bars.
	//@@syntax nWidth = pSplitter->GetSplitterWidth();
	//@@syntax pSplitter->SetSplitterWidth(nWidth);
	//@@parm int | nWidth | Thickness in pixels of the splitter bars.
	virtual void SetSplitterWidth(int nNewWidth) = 0;
	virtual int GetSplitterWidth() const = 0;

	//@prop,property DrawingStyle | Get/SetDrawingStyle |
	// Sets or retrieves the drawing style of the splitter. The drawing style
	// determines the appearance with which the splitter bars will be drawn.
	//@@syntax DWORD dwStyle = pSplitter->GetDrawingStyle();
	//@@syntax pSplitter->SetDrawingStyle(dwStyle);
	//@@parm DWORD | dwStyle | Style for drawing the splitter bars.
	//@@comm 
	// Acceptable values for this property are those from the <t SplitterDrawingStyle>
	// enumeration. 
	virtual void SetDrawingStyle(DWORD dwStyle = DrawGlobalSetting) = 0;
	virtual DWORD GetDrawingStyle() const = 0;

	//@prop,property DWORD | Get/SetSplitterFlags | 
	// Sets or retrieves the flags that control certain aspects of how 
	// the splitter behaves.
	//@@syntax DWORD dwFlags = pSplitter->GetSplitterFlags();
	//@@syntax pSplitter->SetSplitterFlags(dwFlags);
	//@@parm DWORD | dwFlags | Set of flags applied to the splitter node.
	//@@comm
	// Acceptable values are any OR-combination of values from the <t SplitterFlags>
	// enumeration.
	virtual DWORD GetSplitterFlags() const = 0;
	virtual void SetSplitterFlags(DWORD dwFlags) = 0;

	//@meth,method CPoint | GetSplitterPosition |
	// Retrieves the position of the splitter bar on the bottom-right
	// of the cell determined by the (iRow, iCol) coordinates.
	//@@syntax CPoint pt = pSplitter->GetSplitterPosition(iRow, iCol);
	//@@parm short | iRow | Row position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in position of vertical bar.
	//@@parm short | iCol | Column position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in position of horizontal bar.
	//@@rdesc Position of the splitter bar intersection, in coordinates relative to the master
	// window.
	//@@comm
	// Set iRow to -1 if you are only interested in the x coordinate of the vertical splitter bar.
	// Set iCol to -1 if you are only interested in the y coordinate of the horizontal splitter bar.
	// If either iRow or iCol is -1, the corresponding entry in the returned CPoint should be ignored.
	virtual CPoint GetSplitterPosition(short iRow, short iCol) const = 0;

	//@meth,method void | SetSplitterPosition |
	// Programatically sets the position of the splitter bar on the bottom-right
	// of the cell determined by the (iRow, iCol) coordinates.
	//@@syntax CPoint pt = pSplitter->GetSplitterPosition(iRow, iCol);
	//@@syntax pSplitter->SetSplitterPosition(iRow, iCol, pt);
	//@@parm short | iRow | Row position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in position of vertical bar.
	//@@parm short | iCol | Column position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in position of horizontal bar.
	//@@parm CPoint | pt | Position where you want to move the splitter, in coordinates relative
	// to the master window.
	//@@comm 
	// Set iRow to -1 if you are only interested in moving the vertical splitter bar.
	// Set iCol to -1 if you are only interested in moving the horizontal splitter bar.
	// If either iRow or iCol is -1, the corresponding entry in the returned CPoint will be ignored. <nl>
	// The effect of moving the splitter can be achieved with either the SetSplitterPosition method or
	// the <mf ISplitter::MoveSplitter> method. The main difference is that SetSplitterPosition receives
	// the exact position where you want to set the splitter bars, whereas MoveSplitter rather concentrates in
	// the number of units you want to move the splitter from its current position.
	virtual void SetSplitterPosition(short iRow, short iCol, CPoint ptSplitter) = 0;

	//@meth,method CSize | MoveSplitter |
	// Moves a specified splitter bar by a given displacement.
	//@@syntax CSize szActualDisplacement = pSplitter->MoveSplitter(iRow, iCol, szDelta);
	//@@parm short | iRow | Row position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in moving the vertical bar.
	//@@parm short | iCol | Column position of the cell, based on 0. Set this parameter to 
	//  -1 if only interested in moving the horizontal bar.
	//@@parm CSize | szDelta | Movement desired for the splitter bars specified with the
	// coordinates (iRow, iCol). If either of those parameters is -1, only the value 
	// in szDelta corresponding to the given coordinate is considered.
	//@@rdesc Returns the actual displacement of the splitter. It may be different than the 
	// szDelta parameter if the splitter could not be moved for some reason like out of bounds
	// problems or if the column or row has reached a width of 0.
	//@@comm
	// The effect of moving the splitter can be achieved with either the MoveSplitter method or
	// the <mf ISplitter::SetSplitterPosition> method. The main difference is that SetSplitterPosition receives
	// the exact position where you want to set the splitter bars, whereas MoveSplitter rather concentrates in
	// the number of units you want to move the splitter from its current position.
	virtual CSize MoveSplitter(short iRow, short iCol, CSize szDelta) = 0;

	//@meth,method void | SetGridDimensions |
	// Defines the dimensions of the splitter grid, so sucessive calls to
	// <mf ILayoutNode::AddLayoutNode> can distribute the new nodes in rows
	// and columns.
	//@@syntax pSplitter->SetGridDimensions(nRows, nCols);
	//@@parm short | nRows | Number of rows the grid should have.
	//@@parm short | nCols | Number of columns the grid should have.
	//@@comm
	// SetGridDimensions does not actually expands or contracts the splitter grid.
	// It rather sets the maximum number of columns and rows the splitter will accept.
	virtual void SetGridDimensions(short nRows, short nCols = 1) = 0;

	//@meth,method bool | AddPane |
	// Adds a new pane in the splitter in the position indicated by the coordinates
	// (nRow, nCol) and spanning nRowSpan rows and nColSpan columns. 
	//@@syntax bResult = pSplitter->AddPane
	//@@parm ILayoutNode* | pNode | Layout node that will occupy the area reserved
	// for the pane being created.
	//@@parm short | nRow | Row position of the topmost cell of the pane.
	//@@parm short | nCol | Column position of the leftmost cell of the pane.
	//@@parm short | nRowSpan | Number of rows occupied by the pane. Default is 1.
	//@@parm short | nColSpan | Number of columns occupied by the pane. Default is 1.
	//@@comm
	// A pane is a set of contiguous cells that are all occupied by the same layout node. 
	// No splitter bars go across a pane; it is resized as though it were a single cell.<nl>
	// Use AddPane() instead of <mf ILayoutNode::AddLayoutNode> to take advantage of the 
	// special characteristics of the splitter, like cell spanning and positioning. 
	virtual bool AddPane(ILayoutNode* pNode, short nRow, short nCol, short nRowSpan = 1, short nColSpan = 1) = 0;

	//@meth,method bool | RemovePane | 
	// Removes from the splitter grid the cell indicated by (nRow, nCol) coordinates.
	//@@parm short | nRow | Row position of the cell being removed.
	//@@parm short | nCol | Column position of the cell being removed.
	//@@rdesc true if the cell was removed successfully, false otherwise.
	//@@comm
	// The cells occupied by this pane are left empty, unless one or more rows
	// or columns are left empty, in which case those rows or columns are eliminated.
	virtual bool RemovePane(short nRow, short nCol) = 0;
};



//@class CSplitterLayout |
// Implements splitters and integrates this feature into the layout
// manager architecture.
//@supint ILayoutNode | Basic layout node functionality
//@supint ISplitter | Splitter-specific functionality
//@base | CDCLayoutBase<CSplitterLayout, ISplitter>
//@comm
// The splitter layout, unlike the rest of the layout algorithms, is a dynamic interactive layout
// arrangement. An application user can rearrange windows interactively, using the
// mouse. In the other layout algorithms, the layout recalculation is triggered indirectly
// by operations such as resizing the container window.<nl>
// The splitter layout node offers multiple configuration choices, from choosing the
// style used or drawing the splitter bars, to getting rid of the bars altogether,
// producing non-interactive grid layout.
class __declspec(uuid("8B1647C3-45E5-11d3-9D92-00C04F91E286")) CSplitterLayout: 
	public CDCLayoutBase<CSplitterLayout, ISplitter>
{
public:
	typedef CDCLayoutBase<CSplitterLayout, ISplitter> _LayoutBase;

	// Initialization/Destruction
	CSplitterLayout();
	virtual ~CSplitterLayout() {}

public:

	// ISplitter interface
	virtual void SetSplitterWidth(int nNewWidth) {m_nSplitterWidth = nNewWidth;}
	virtual int GetSplitterWidth() const {return m_nSplitterWidth;}

	virtual void SetDrawingStyle(DWORD dwStyle = DrawGlobalSetting) {m_dwDrawingStyle = dwStyle;}
	virtual DWORD GetDrawingStyle() const {return m_dwDrawingStyle;}

	virtual DWORD GetSplitterFlags() const {return m_dwFlags;}
	virtual void SetSplitterFlags(DWORD dwFlags) {m_dwFlags = dwFlags;}

	inline virtual void SetSplitterPosition(short iRow, short iCol, CPoint ptSplitter);
	inline virtual CPoint GetSplitterPosition(short iRow, short iCol) const;
	inline virtual CSize MoveSplitter(short iRow, short iCol, CSize szDelta);

	inline virtual void SetGridDimensions(short nRows, short nCols = 1);

	inline virtual bool AddPane(ILayoutNode* pNode, short nRow, short nCol, short nRowSpan = 1, short nColSpan = 1);
	inline virtual bool RemovePane(short nRow, short nCol);


public:
	// ILayoutNode interface overrides
	inline virtual CRect OnRecalcLayout(const CRect& rectDesired, bool bChildNegotiate, bool bStrictRecalc);
	inline virtual bool OnRealizeNode(CLayoutTransaction& aTransaction);

	inline virtual int AddLayoutNode (ILayoutNode* pNode);
	inline virtual int RemoveLayoutNode(ILayoutNode* pNode);


protected:
	// CDCLayoutBase overrides
	inline virtual void OnPaint(HDC hDC = NULL);
	inline virtual bool EraseNodeBkgnd(HDC hDC = NULL, bool bApplyToChildren = true);

protected:

	// Event map
	BEGIN_WINDOW_EVENT_MAP(CSplitterLayout)
		HANDLE_WINDOW_EVENT(WM_SETCURSOR, OnSetCursor)
		HANDLE_WINDOW_EVENT(WM_LBUTTONDOWN, OnLButtonDown)
		HANDLE_WINDOW_EVENT(WM_MOUSEMOVE, OnMouseMove)
	END_WINDOW_EVENT_MAP()

	inline LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	inline LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	inline LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


protected:

	// Implementation Member Variables
	int m_nSplitterWidth;
	DWORD m_dwDrawingStyle;
	DWORD m_dwFlags;

	short m_nMaxRow, m_nMaxCol;
	short m_nNextCol, m_nNextRow;


	// For splitter track
	bool m_bTracking;
	CRect m_rcLastRowTracker, m_rcLastColTracker;
	CSize m_szLastRowTracker, m_szLastColTracker;



protected:
	// Pane information

	struct CPaneInfo
	{
		CPaneInfo(ILayoutNode* aNode = 0, short aRow = 0, short aCol = 0, short aRowSpan = 1, short aColSpan = 1):
		m_pPaneNode(aNode),
		nRowOrigin(aRow), nColOrigin(aCol), nRowSpan(aRowSpan), nColSpan(aColSpan)
		{}
		CPaneInfo(const CPaneInfo& aInfo): 
		m_pPaneNode(aInfo.m_pPaneNode),
		nRowOrigin(aInfo.nRowOrigin), nColOrigin(aInfo.nColOrigin), nRowSpan(aInfo.nRowSpan), nColSpan(aInfo.nColSpan)
		{}

		// Data
		ILayoutNode* m_pPaneNode;
		short nRowOrigin;
		short nColOrigin;
		short nRowSpan;
		short nColSpan;

		// Operations
		bool IsEmpty() const {return m_pPaneNode == 0;}
		void Empty() {m_pPaneNode = 0;}
	};

	struct CPanes
	{
		CPanes(): m_nGapSize(0), m_bEndingRowGap(false), m_bEndingColGap(false) {}

		inline ILayoutNode* GetPaneNode(short nRow, short nCol);

		inline void Insert(ILayoutNode* pNode, short nRow, short nCol, short nRowSpan = 1, short nColSpan = 1);
		inline void Remove(short iRow, short iCol);
		inline bool FindPane(ILayoutNode* pNode, short& nRow, short& nCol);
		inline CPaneInfo& GetCell(short iRow, short iCol);
		inline const CPaneInfo& GetCell(short iRow, short iCol) const;
		inline CRect GetCellRect(short nRow, short nCol) const;
		inline CRect GetPaneRect(short nRow, short nCol) const;

		short GetRowCount() const {return static_cast<short>(m_RowPoints.size());}
		short GetColCount() const {return static_cast<short>(m_ColPoints.size());}

		inline void DistributeNewRect(const CRect& rcNewRect, int iGapSize = 0);
		inline void SetRowHeight(short nRow, int nHeight);
		inline void SetColWidth(short nCol, int nWidth);
		inline int GetRowHeight(short nRow) const;
		inline int GetColWidth(short nCol) const;

		inline void ApplyRects(bool bNegotiate = true, bool bStrict = true);

		inline bool GapTest(CPoint ptPos, short& nRow, short& nCol) const;

		inline CRect GetCurrentRect() const;
	protected:

		inline CRect GetPaneRect(const CPaneInfo& pane) const;
		inline void AddColumns(short nPos = -1, short nCount = 1);
		inline void RemoveColumns(short nPos, short nCount = 1);

		inline void AddRows(short nPos = -1, short nCount = 1);
		inline void RemoveRows(short nPos, short nCount = 1);

		inline bool IsColEmpty(short iColumn) const;
		inline bool IsRowEmpty(short iRow) const;

		inline bool InBounds(short iRow, short iCol) const;

		inline int GetMaxRowHeight(short iRow) const;
		inline int GetMaxColWidth(short iCol) const;

	private:
		typedef std::deque<float> CoordList; 
		typedef std::deque<CPaneInfo> CellsList; 
		typedef std::deque<CellsList> ColsList; 

		ColsList m_grid;
		CoordList m_RowPoints;
		CoordList m_ColPoints;
		CPoint m_ptOrigin;
		int m_nGapSize; 
		bool m_bEndingRowGap;
		bool m_bEndingColGap;
	};

	friend struct CPanes;
	CPanes m_panes;


	// Drawing information
	struct CSplitterDrawInfo 
	{
		HDC   hdc;
		CRect rcCell;
		DWORD dwDrawingStyle;
		bool  bDrawHSplitter;
		bool  bDrawVSplitter;
		bool  bDrawHConnector;
		bool  bDrawVConnector;

		CSplitterDrawInfo(HDC aDC, CRect aRect, DWORD aStyle, bool bHS = true, bool bVS = true, bool bHC = true, bool bVC = true)
			: hdc(aDC), rcCell(aRect), dwDrawingStyle(aStyle), 
			bDrawHSplitter(bHS), bDrawVSplitter(bVS), bDrawHConnector(bHC), bDrawVConnector(bVC)
		{}
	};

protected:
	// Implementation

	inline virtual bool SplitterHitTest(CPoint point, short& iRowSplitter, short& iColSplitter);
	inline CRect GetRowSplitterRect(short iRow) const;
	inline CRect GetColSplitterRect(short iCol) const;

	inline virtual void DrawSplitters(HDC hdc);
	inline virtual void DrawCellSplitter(const CSplitterDrawInfo& sdInfo);
	DWORD ResolveAppropDrawingStyle()
	{
		if (m_dwDrawingStyle == DrawGlobalSetting) {
			return m_dwDrawingStyleAll; 
		}
		else {
			return m_dwDrawingStyle;
		}
	}
	inline void SetSplitterCursor(CPoint ptPos);

	// Splitter mouse tracking
	inline virtual void StartTracking(CPoint point, short iRowSplitter, short iColSplitter);
	inline virtual CSize Track(CPoint point, short iRowSplitter, short iColSplitter);
	inline virtual bool TrackMessageLoop(HDC hdcTracker, short iRowSplitter, short iColSplitter, CRect& rcRowSplitter, CRect& rcColSplitter);
	inline virtual void OnTrackMouseMove(HDC hdcTracker, CPoint ptOldPos, CPoint ptNewPos, short iRowSplitter, short iColSplitter, CRect& rcRowSplitter, CRect& rcColSplitter);
	inline virtual void DrawTrackerRect(HDC hdcTracker, CRect rcTracker, bool bRow, bool bErase = false);
	inline virtual HDC GetTrackerDC();

	// Called when the drag operation starts
	inline virtual bool OnSplitterDragStart(CPoint /*point*/, short /*iRowSplitter*/, short /*iColSplitter*/) {return true;}
	// Called when the drag operation finishes
	inline virtual CSize OnAdjustFinalSplitterRect(CRect& rcSplitter, bool bRow);
	// Called after a moving of the splitter
	inline virtual void OnSplitterMoved(CSize szDelta);
	inline void PumpPaintMessages();

public:
	// Default splitter behavior
	inline void InitSplitters();
	static int m_nSplitterWidthAll;
	static DWORD m_dwDrawingStyleAll;
	static HCURSOR m_hcurVSplitter;
	static HCURSOR m_hcurHSplitter;
	static HCURSOR m_hcurCrossSplitter;

};

/////////////////////////////////////////////////
// CPanes internal class


ILayoutNode* CSplitterLayout::CPanes::GetPaneNode (
	short nRow, 
	short nCol
	)
{
	CPaneInfo pane = GetCell(nRow, nCol);
	return pane.m_pPaneNode;
}


void CSplitterLayout::CPanes::Insert (
									  ILayoutNode* pNode,
									  short nRow,
									  short nCol,
									  short nRowSpan,
									  short nColSpan
									  )
{
	// At most, it is allowed to specify one more row or column than currently existing, 
	// meaning to add one entry in that dimension.
	// Check in-bounds-ness.

	// Insert new column if necessary
	if ((nCol == GetColCount()) || (nCol + nColSpan >= GetColCount())) {
		const short colCount = static_cast<short>(nCol + nColSpan - GetColCount());
		AddColumns(GetColCount(), colCount);
	}
	// Insert new row if necessary
	if ((nRow == GetRowCount()) || (nRow + nRowSpan >= GetRowCount())) {
		const short rowCount = static_cast<short>(nRow + nRowSpan - GetRowCount());
		AddRows(GetRowCount(), rowCount);
	}

	// If entry already exists, but empty, just add the new element
	for (short iCol = nCol; iCol < nCol + nColSpan; ++iCol) {
		for (short iRow = nRow; iRow < nRow + nRowSpan; ++iRow) {
			if (InBounds(iRow, iCol)) {
				CPaneInfo& pane = GetCell(iRow, iCol);
				if (!pane.IsEmpty()) {
					std::exception error;
					throw error;
				}
				pane.m_pPaneNode = pNode;
				pane.nColOrigin = nCol;
				pane.nColSpan = nColSpan;
				pane.nRowOrigin = nRow;
				pane.nRowSpan = nRowSpan;
			}
			else {
				std::range_error error("Out of range");
				throw error;
			}
		}
	}
}


void CSplitterLayout::CPanes::Remove(short iRow, short iCol)
{
	// Check for validity of indexes
	CPaneInfo& pane = GetCell(iRow, iCol);

	// Empty all cells that span this pane, and remove if necessary
	for (short posCol = pane.nColOrigin; posCol < pane.nColOrigin + pane.nColSpan; ++posCol) {
		CellsList& col = m_grid[posCol];
		for (short posRow = pane.nRowOrigin; posRow < pane.nRowOrigin + pane.nRowSpan; ++posRow) {
			CPaneInfo& paneSpan = col[posRow];
			paneSpan.Empty();
		}

		if (IsColEmpty(posCol)) {
			RemoveColumns(posCol, 0);
		}
	}


	// If last cell in row, remove row
	short posRow = static_cast<short>(pane.nRowOrigin + pane.nRowSpan - 1);
	for (; posRow <= pane.nRowOrigin; --posRow) {
		if (IsRowEmpty(posRow)) {
			RemoveRows(posRow, 0);
		}
	}
}


bool CSplitterLayout::CPanes::FindPane (
										ILayoutNode* pNode, 
										short& iRow, 
										short& iCol
										)
{
	iCol = 0;
	bool bFound = false;
	for (ColsList::iterator posCol = m_grid.begin(); !bFound && posCol != m_grid.end(); ++posCol, ++iCol) {
		iRow = 0;
		for (CellsList::iterator posCell = (*posCol).begin(); !bFound && posCell != (*posCol).end(); ++posCell, ++iRow) {
			CPaneInfo& pane = (*posCell);
			bFound = (pane.m_pPaneNode == pNode);
		}
	}

	if (!bFound) {
		iRow = -1;
		iCol = -1;
	}

	return bFound;
}


CSplitterLayout::CPaneInfo& CSplitterLayout::CPanes::GetCell (
	short iRow, 
	short iCol
	)
{
	// Check in-bounds-ness.
	if (!InBounds(iRow, iCol)) {
		std::range_error error("Out of bounds");
		throw error;
	}

	ColsList::reference col = m_grid[iCol];
	CPaneInfo& pane = col[iRow];

	return pane;
}


const CSplitterLayout::CPaneInfo& CSplitterLayout::CPanes::GetCell (
	short iRow, 
	short iCol
	) const
{
	// Check in-bounds-ness.
	if (!InBounds(iRow, iCol)) {
		std::range_error error("Out of bounds");
		throw error;
	}

	ColsList::const_reference col = m_grid[iCol];
	const CPaneInfo& pane = col[iRow];

	return pane;
}


CRect CSplitterLayout::CPanes::GetCellRect (
	short nRow, 
	short nCol
	) const
{
	CRect rcCellRect;

	rcCellRect.top = (nRow == 0)? m_ptOrigin.y : static_cast<int>(m_RowPoints[nRow - 1]) + m_nGapSize;
	rcCellRect.bottom = static_cast<int>(m_RowPoints[nRow]);

	rcCellRect.left = (nCol == 0)? m_ptOrigin.x : static_cast<int>(m_ColPoints[nCol - 1]) + m_nGapSize;
	rcCellRect.right = static_cast<int>(m_ColPoints[nCol]);

	return rcCellRect;
}


CRect CSplitterLayout::CPanes::GetPaneRect (
	short nRow, 
	short nCol
	) const
{
	const CPaneInfo& pane = GetCell(nRow, nCol);
	return GetPaneRect(pane);
}


CRect CSplitterLayout::CPanes::GetPaneRect (
	const CPaneInfo& pane
	) const
{
	CRect rcOrigin = GetCellRect(pane.nRowOrigin, pane.nColOrigin);

	const short endRow = static_cast<short>(pane.nRowOrigin + pane.nRowSpan - 1);
	const short endCol = static_cast<short>(pane.nColOrigin + pane.nColSpan - 1);
	CRect rcEnd = GetCellRect(endRow, endCol);

	CRect rcPane;
	rcPane.UnionRect(rcOrigin, rcEnd);

	return rcPane;
}



void CSplitterLayout::CPanes::SetRowHeight (
	short nRow, 
	int nHeight
	)
{
	if ((nHeight < 0) || (nHeight > GetMaxRowHeight(nRow))) {
		return;
	}

	int delta;
	// Adjust width of all cells in this column
	delta = nHeight - GetRowHeight(nRow);
	m_RowPoints[nRow] += delta;
}


void CSplitterLayout::CPanes::SetColWidth (
	short nCol, 
	int nWidth
	)
{
	if ((nWidth < 0) || (nWidth > GetMaxColWidth(nCol))) {
		return;
	}

	int delta;
	// Adjust width of all cells in this column
	delta = nWidth - GetColWidth(nCol);
	m_ColPoints[nCol] += delta;
}


int CSplitterLayout::CPanes::GetRowHeight (
	short nRow
	) const
{
	return GetCellRect(nRow, 0).Height();
}


int CSplitterLayout::CPanes::GetColWidth (
	short nCol
	) const
{
	return GetCellRect(0, nCol).Width();
}


int CSplitterLayout::CPanes::GetMaxRowHeight (
	short nRow
	) const
{
	int nMaxRow = GetRowCount() - 1;
	if (nRow < 0 || nRow > nMaxRow)  {
		std::out_of_range error("Out of range");
		throw error;
	}

	int nMaxHeight = GetRowHeight(nRow);

	if (nRow < nMaxRow) {
		nMaxHeight += GetRowHeight(static_cast<short>(nRow + 1));
	}

	return nMaxHeight;
}


int CSplitterLayout::CPanes::GetMaxColWidth (
	short nCol 
	) const
{
	int nMaxCol = GetColCount() - 1;
	if (nCol < 0 || nCol > nMaxCol)  {
		std::out_of_range error("Out of range");
		throw error;
	}

	int nMaxWidth = GetColWidth(nCol);

	if (nCol < nMaxCol) {
		nMaxWidth += GetColWidth(static_cast<short>(nCol + 1));
	}

	return nMaxWidth;
}


void CSplitterLayout::CPanes::DistributeNewRect (
	const CRect& rcNewRect, 
	int iGapSize
	)
{
	CRect rcOld = GetCurrentRect();
	int nColCount = GetColCount();
	int nRowCount = GetRowCount();

	// Traslate the grid to the new position
	// Scale the cells proportionally to the new size
	// Reset the splitter origin
	float fOldOriginX = static_cast<float>(m_ptOrigin.x);
	float fOldOriginY = static_cast<float>(m_ptOrigin.y);

	m_ptOrigin = rcNewRect.TopLeft();

	float fCellOriginX = static_cast<float>(m_ptOrigin.x);
	float fCellOriginY = static_cast<float>(m_ptOrigin.y);

	CSize szOldDistribution = rcOld.Size();
	CSize szNewDistribution = rcNewRect.Size();

	// Eliminate the gaps from the distributable space
	szOldDistribution -= CSize(m_nGapSize * (nColCount - 1), m_nGapSize * (nRowCount - 1));
	szNewDistribution -= CSize(iGapSize * (nColCount - 1), iGapSize * (nRowCount - 1));

	float fNewCellX = 0.0f; 
	float fNewCellY = 0.0f;

	// In case the rectangle has not been distributed before, divide the new area among equal parts
	if (szOldDistribution.cx <= 0) {
		fNewCellX = static_cast<float>(szNewDistribution.cx) / nColCount;
	}
	if (szOldDistribution.cy <= 0) {
		fNewCellY = static_cast<float>(szNewDistribution.cy) / nRowCount;
	}

	for (int posCol = 0; posCol < nColCount; ++posCol) {
		if (szOldDistribution.cx > 0) {
			float fRatio = (m_ColPoints[posCol] - fOldOriginX) / szOldDistribution.cx;
			fNewCellX = fRatio * szNewDistribution.cx;
		} 

		fOldOriginX = m_ColPoints[posCol] + m_nGapSize;
		m_ColPoints[posCol] = fCellOriginX += fNewCellX;

		fCellOriginX += iGapSize;
	}

	for (int posRow = 0; posRow < nRowCount; ++posRow) {
		if (szOldDistribution.cy > 0) {
			float fRatio = (m_RowPoints[posRow] - fOldOriginY) / szOldDistribution.cy;
			fNewCellY = fRatio * szNewDistribution.cy;
		} 

		fOldOriginY = m_RowPoints[posRow] + m_nGapSize;
		m_RowPoints[posRow] = fCellOriginY += fNewCellY;

		fCellOriginY += iGapSize;
	}

	m_nGapSize = iGapSize;
}


void CSplitterLayout::CPanes::ApplyRects (
	bool bNegotiate, 
	bool bStrict
	)
{
	short nCol;
	ColsList::iterator posCol ;
	for (posCol = m_grid.begin(), nCol = 0; posCol != m_grid.end(); ++posCol, ++nCol) {
		short nRow;
		CellsList::iterator posCell;
		for (posCell = (*posCol).begin(), nRow = 0; posCell != (*posCol).end(); ++posCell, ++nRow) {
			CPaneInfo& pane = (*posCell);

			if (!pane.IsEmpty() && (pane.nRowOrigin == nRow) && (pane.nColOrigin == nCol)) {
				pane.m_pPaneNode->RecalcLayout(GetPaneRect(pane), bNegotiate, bStrict);
			}
		}
	}
}


CRect CSplitterLayout::CPanes::GetCurrentRect (
	) const
{
	CRect rcCurrent;

	rcCurrent.TopLeft() = m_ptOrigin;
	rcCurrent.bottom = static_cast<int>(m_RowPoints[GetRowCount() - 1]) + (m_bEndingRowGap? m_nGapSize : 0);
	rcCurrent.right = static_cast<int>(m_ColPoints[GetColCount() - 1]) + (m_bEndingColGap? m_nGapSize : 0);

	return rcCurrent;
}


bool CSplitterLayout::CPanes::GapTest (
									   CPoint ptPos, 
									   short& nRow, 
									   short& nCol
									   ) const
{
	nRow = -1;
	nCol = -1;

	CRect rcCurrent = GetCurrentRect();
	if (!rcCurrent.PtInRect(ptPos)) {
		return false;
	}

	bool bFound = false;
	bool bPassed = false;
	short iCol, iRow;
	// Check if point corresponds to a column
	for (iCol = 0; !bPassed && !bFound && (iCol < GetColCount()); ++iCol) {
		int iColRight = static_cast<int>(m_ColPoints[iCol]);
		if (ptPos.x < iColRight) {
			bPassed = true;
		}
		else if ((ptPos.x >= iColRight) && (ptPos.x < iColRight + m_nGapSize)) {
			bFound = true;
			nCol = iCol;
		}
	}

	bFound = false;
	bPassed = false;
	// Check if point corresponds to a row
	for (iRow = 0; !bFound && (iRow < GetRowCount()); ++iRow) {
		int iRowBottom = static_cast<int>(m_RowPoints[iRow]);
		if (ptPos.y < iRowBottom) {
			bPassed = true;
		}
		else if ((ptPos.y >= iRowBottom) && (ptPos.y < iRowBottom + m_nGapSize)) {
			bFound = true;
			nRow = iRow;
		}
	}

	// Check for column or row spanning
	const CPaneInfo& pane = GetCell(--iRow, --iCol);
	if ((nRow != -1) && (nCol == -1) && (nRow != pane.nRowOrigin + pane.nRowSpan - 1)) {
		nRow = -1;
	}

	if ((nCol != -1) && (nRow == -1) && (nCol != pane.nColOrigin + pane.nColSpan - 1)) {
		nCol = -1;
	}

	return (nRow != -1) || (nCol != -1);
}


void CSplitterLayout::CPanes::AddColumns (
	short nPos, 
	short nCount
	)
{
	if (nPos == -1) {
		nPos = GetColCount();
	}

	for (short i = 0; i < nCount; ++i) {
		CellsList newCol(GetRowCount());

		ColsList::iterator posCol;


		if (nPos == GetColCount()) {
			m_grid.push_back(newCol);
			int iColPoint = GetColCount() == 0 ? m_ptOrigin.x : static_cast<int>(m_ColPoints[nPos - 1]);
			m_ColPoints.push_back(static_cast<float>(iColPoint + m_nGapSize));
			posCol = m_grid.end() - 1;
		}
		else {
			posCol = m_grid.begin() + nPos + i;
			posCol = m_grid.insert(posCol, newCol);
			m_ColPoints.insert(m_ColPoints.begin() + nPos + i, 1, m_ColPoints[nPos] + m_nGapSize);
		}

		// Initialize panes in the column
		short nRow;
		CellsList::iterator posRow;
		for (posRow = (*posCol).begin(), nRow = 0; posRow != (*posCol).end(); ++posRow, ++nRow) {
			(*posRow).nRowOrigin = nRow;
			(*posRow).nColOrigin = static_cast<short>(nPos + i);
		}

	}
}


void CSplitterLayout::CPanes::RemoveColumns (
	short nPos, 
	short nCount
	)
{
	m_grid.erase(m_grid.begin() + nPos, m_grid.begin() + nPos + nCount);
	m_ColPoints.erase(m_ColPoints.begin() + nPos, m_ColPoints.begin() + nPos + nCount);
}


void CSplitterLayout::CPanes::AddRows (
									   short nPos, 
									   short nCount
									   )
{
	if (nPos == -1) {
		nPos = GetRowCount();
	}

	short nCol;
	ColsList::iterator posCol;
	for (posCol = m_grid.begin(), nCol = 0; posCol != m_grid.end(); ++posCol, ++nCol) {
		for (short i = 0; i < nCount; ++i) {
			CPaneInfo newPane(0, static_cast<short>(nPos + i), nCol, 1, 1);

			if (nPos == GetRowCount()) {
				(*posCol).push_back(newPane);
			}
			else {
				(*posCol).insert((*posCol).begin() + nPos + i, 1, newPane);
			}
		}
	}

	for (short i = 0; i < nCount; ++i) {
		if (nPos == GetRowCount()) {
			int iRowPoint = GetRowCount() == 0? m_ptOrigin.y : static_cast<int>(m_RowPoints[nPos - 1]);
			m_RowPoints.push_back(static_cast<float>(iRowPoint + m_nGapSize));
		}
		else {
			m_RowPoints.insert(m_RowPoints.begin() + nPos, 1, m_RowPoints[nPos] + m_nGapSize);
		}
	}
}


void CSplitterLayout::CPanes::RemoveRows (
	short nPos, 
	short nCount
	)
{
	for (ColsList::iterator i = m_grid.begin(); i != m_grid.end(); ++i) {
		CellsList::iterator posRemove = (*i).begin() + nPos;
		(*i).erase(posRemove, posRemove + nCount);
	}
	m_RowPoints.erase(m_RowPoints.begin() + nPos, m_RowPoints.begin() + nPos + nCount);
}


bool CSplitterLayout::CPanes::IsColEmpty(short iColumn) const
{
	const CellsList& col = m_grid[iColumn];

	bool bEmpty = true;
	for (CellsList::const_iterator i = col.begin(); bEmpty && i != col.end(); ++i) {
		bEmpty = (*i).IsEmpty();
	}

	return bEmpty;
}

bool CSplitterLayout::CPanes::IsRowEmpty(short iRow) const
{
	bool bEmpty = true;
	for (ColsList::const_iterator i = m_grid.begin(); bEmpty && i != m_grid.end(); ++i) {
		const CPaneInfo& pane = (*i)[iRow];
		bEmpty = pane.IsEmpty();
	}

	return bEmpty;
}


bool CSplitterLayout::CPanes::InBounds(short iRow, short iCol) const
{
	if ((iRow < 0) || (iRow >= GetRowCount()) || (iCol < 0) || (iCol >= GetColCount())) {
		return false;
	}
	return true;
}



/////////////////////////////////////////////////
// Static members: global settings



void CSplitterLayout::InitSplitters()
{
	if (m_hcurHSplitter == NULL) { 
		m_hcurHSplitter = ::LoadCursor(GetResourceHandle(), MAKEINTRESOURCE(IDC_HSPLITBAR));
	}			

	if (m_hcurVSplitter == NULL) {
		m_hcurVSplitter = ::LoadCursor(GetResourceHandle(), MAKEINTRESOURCE(IDC_VSPLITBAR));
	}

	if (m_hcurCrossSplitter == NULL) {
		m_hcurCrossSplitter = ::LoadCursor(GetResourceHandle(), MAKEINTRESOURCE(IDC_CROSSSPLITBAR));
	}
}



/////////////////////////////////////////////////
// CSplitterLayout class


CSplitterLayout::CSplitterLayout (
								  ): 
m_nSplitterWidth(m_nSplitterWidthAll), m_dwDrawingStyle(m_dwDrawingStyleAll), m_dwFlags(0),
m_nMaxRow(1), m_nMaxCol(1),
m_nNextCol(0), m_nNextRow(0),
m_bTracking(false)
{
	InitSplitters();
}



/////////////////////////////////////////////////
// ILayoutNode interface implementation


CRect CSplitterLayout::OnRecalcLayout (
									   const CRect& rectDesired, 
									   bool bChildNegotiate, 
									   bool bStrictRecalc
									   )
{
	// some prelim calculations for proper row/column cell placement
	m_panes.DistributeNewRect(rectDesired, m_nSplitterWidth);
	m_panes.ApplyRects(bChildNegotiate, bStrictRecalc);
	if (bChildNegotiate) {
		// TODO: rect massaging here...

		m_panes.ApplyRects(false, bStrictRecalc);
	}

	SetCurrentRect(rectDesired);
	return rectDesired;
}


bool CSplitterLayout::OnRealizeNode (
									 CLayoutTransaction& aTransaction
									 )
{
	return _LayoutBase::OnRealizeNode(aTransaction);
}


void CSplitterLayout::OnPaint (
							   HDC hDC
							   )
{
	DrawSplitters(hDC);
}


bool CSplitterLayout::EraseNodeBkgnd (
									  HDC hDC, 
									  bool bApplyToChildren
									  )
{
	hDC;
	bApplyToChildren;
	return true;
}


int CSplitterLayout::AddLayoutNode (ILayoutNode* pNode) 
{
	int res = _LayoutBase::AddLayoutNode(pNode);
	AddPane(pNode, m_nNextRow, m_nNextCol++);
	if (m_nNextCol > m_nMaxCol) {
		m_nNextCol = 0;
		++m_nNextRow;
	}

	if (m_nNextRow > m_nMaxRow) {
		m_nNextRow = ++m_nMaxRow;
	}

	return res;
}


int CSplitterLayout::RemoveLayoutNode(ILayoutNode* pNode)
{
	int res = _LayoutBase::RemoveLayoutNode(pNode);
	short iRow, iCol;
	if (m_panes.FindPane(pNode, iRow, iCol)) {
		m_panes.Remove(iRow, iCol);
	}
	return res;
}



/////////////////////////////////////////////////
// ISplitter interface implementation


CPoint CSplitterLayout::GetSplitterPosition (
	short iRow, 
	short iCol
	) const
{
	CRect rcCell = m_panes.GetCellRect(static_cast<short>((iRow != -1)? iRow : 0), static_cast<short>((iCol != -1)? iCol : 0));
	CPoint ptSplitter(iCol != -1? rcCell.right : 0, iRow != -1? rcCell.bottom : 0);

	return ptSplitter;
}


void CSplitterLayout::SetSplitterPosition (
	short iRow, 
	short iCol, 
	CPoint ptSplitter
	)
{
	int nOldWidth = iCol != -1? m_panes.GetColWidth(iCol) : 0;
	int nOldHeight = iRow != -1? m_panes.GetRowHeight(iRow) : 0;
	CPoint ptOldPos = GetSplitterPosition(iRow, iCol);

	CSize szDelta = ptSplitter - ptOldPos;

	if (iCol != -1) {
		m_panes.SetColWidth(iCol, nOldWidth + szDelta.cx);
	}
	if (iRow != -1) {
		m_panes.SetRowHeight(iRow, nOldHeight + szDelta.cy);
	}
}


CSize CSplitterLayout::MoveSplitter (
									 short iRow, 
									 short iCol, 
									 CSize szDelta
									 )
{
	CPoint ptOldPos = GetSplitterPosition(iRow, iCol);
	SetSplitterPosition(iRow, iCol, ptOldPos + szDelta);
	CPoint ptNewPos = GetSplitterPosition(iRow, iCol);

	CSize szActualMovement = ptNewPos - ptOldPos;
	if (szActualMovement != CSize(0, 0)) {
		m_panes.ApplyRects();
		CLayoutTransaction aTransaction;
		RealizeNode(aTransaction);

	}

	return szActualMovement;
}


void CSplitterLayout::SetGridDimensions (
	short nRows,
	short nCols
	)
{
	m_nMaxCol = static_cast<short>(nCols - 1);
	m_nMaxRow = static_cast<short>(nRows - 1);
}


bool CSplitterLayout::AddPane (
							   ILayoutNode* pNode,
							   short nRow,
							   short nCol,
							   short nRowSpan,
							   short nColSpan
							   )
{
	m_panes.Insert(pNode, nRow, nCol, nRowSpan, nColSpan);
	_LayoutBase::AddLayoutNode(pNode);
	return true;
}


bool CSplitterLayout::RemovePane (
								  short nRow,
								  short nCol
								  )
{
	ILayoutNode* pNode = m_panes.GetPaneNode(nRow, nCol);
	m_panes.Remove(nRow, nCol);
	_LayoutBase::RemoveLayoutNode(pNode);
	return true;
}



/////////////////////////////////////////////////
// Message handlers


LRESULT CSplitterLayout::OnSetCursor (
									  UINT uMsg, 
									  WPARAM wParam, 
									  LPARAM lParam, 
									  BOOL& bHandled
									  )
{
	uMsg;
	int nHitTest = LOWORD(lParam);
	HWND hwndMouse = reinterpret_cast<HWND>(wParam);
	if (nHitTest == HTCLIENT && hwndMouse == m_hWnd) {
		return TRUE;    // we will handle it in the mouse move
	}

	bHandled = FALSE;
	return 0;
}


LRESULT CSplitterLayout::OnLButtonDown (
										UINT uMsg, 
										WPARAM wParam, 
										LPARAM lParam, 
										BOOL& bHandled
										)
{
	uMsg; wParam;

	CPoint ptCursor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	// Mouse hit on 1 (or both) of the splitters?
	short iRowSplitter, iColSplitter;
	if (!(m_dwFlags & SplitterNoSplitters) && SplitterHitTest(ptCursor, iRowSplitter, iColSplitter)) {
		StartTracking(ptCursor, iRowSplitter, iColSplitter);
	}
	else {
		bHandled = FALSE;
	}

	return 0;
}


LRESULT CSplitterLayout::OnMouseMove (
									  UINT uMsg, 
									  WPARAM wParam, 
									  LPARAM lParam, 
									  BOOL& bHandled
									  )
{
	uMsg; wParam;

	// Hittest for the splitter
	CPoint ptCursor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	SetSplitterCursor(ptCursor);
	bHandled = FALSE;
	return 0;
}



/////////////////////////////////////////////////
// Splitter Implementation 


void CSplitterLayout::SetSplitterCursor (
	CPoint ptPos
	)
{
	short iRowSplitter = -1;
	short iColSplitter = -1;
	if (!(m_dwFlags & SplitterNoSplitters) && SplitterHitTest(ptPos, iRowSplitter, iColSplitter)) {
		// Set the new cursor based on hittest result
		if ((iRowSplitter != -1) && (iColSplitter != -1)) {
			::SetCursor(m_hcurCrossSplitter);
		}
		else if (iRowSplitter != -1) {
			::SetCursor(m_hcurHSplitter);
		}
		else if (iColSplitter != -1) {
			::SetCursor(m_hcurVSplitter);
		}
	}
	else {
#ifdef _WIN64
		HCURSOR hcurDefault = reinterpret_cast<HCURSOR>(::GetClassLongPtr(m_hWnd, GCLP_HCURSOR));
#else	//_WIN32
		HCURSOR hcurDefault = reinterpret_cast<HCURSOR>(::GetClassLong(m_hWnd, GCL_HCURSOR));
#endif	//_WIN64
		::SetCursor(hcurDefault);
	}
}


bool CSplitterLayout::SplitterHitTest (
									   CPoint point, 
									   short& iRowSplitter, 
									   short& iColSplitter
									   )
{
	bool bResult = m_panes.GapTest(point, iRowSplitter, iColSplitter);

	if (bResult) {
		if (!(m_dwFlags & SplitterBottomBorder) && (iRowSplitter == m_panes.GetRowCount() - 1)) {
			iRowSplitter = -1;
		}

		if (!(m_dwFlags & SplitterRightBorder) && (iColSplitter == m_panes.GetColCount() - 1)) {
			iColSplitter = -1;
		}

		bResult = (iRowSplitter != -1) || (iColSplitter != -1);
	}

	return bResult;
}


CRect CSplitterLayout::GetRowSplitterRect (
	short iRow
	) const
{
	CRect rcSplitter = m_panes.GetCurrentRect();
	rcSplitter.TopLeft() = GetSplitterPosition(iRow, -1);
	rcSplitter.bottom = rcSplitter.top + m_nSplitterWidth;
	return rcSplitter;
}


CRect CSplitterLayout::GetColSplitterRect (
	short iCol
	) const
{
	CRect rcSplitter = m_panes.GetCurrentRect();
	rcSplitter.TopLeft() = GetSplitterPosition(-1, iCol);
	rcSplitter.right = rcSplitter.left + m_nSplitterWidth;
	return rcSplitter;
}




/////////////////////////////////////////////////
// Splitter Drawing Logic


void CSplitterLayout::DrawSplitters (
									 HDC hdc
									 )
{
	// Resolve the appropriate drawing style (global or local)
	DWORD dwStyle = ResolveAppropDrawingStyle();

	int nMaxCols = m_panes.GetColCount();
	int nMaxRows = m_panes.GetRowCount();

	for (short iCol = 0; iCol < nMaxCols; ++iCol) {
		for (short iRow = 0; iRow < nMaxRows; ++iRow) {
			CRect rcCell = m_panes.GetCellRect(iRow, iCol);
			CSplitterDrawInfo drawInfo(hdc, rcCell, dwStyle);

			CPaneInfo& aPane = m_panes.GetCell(iRow, iCol);

			CPaneInfo* pContPane;

			drawInfo.bDrawHSplitter = (iRow == (aPane.nRowOrigin + aPane.nRowSpan - 1)) && 
				((iRow < nMaxRows - 1) || (m_dwFlags & SplitterBottomBorder));
			drawInfo.bDrawVSplitter = (iCol == (aPane.nColOrigin + aPane.nColSpan - 1)) &&
				((iCol < nMaxCols - 1) || (m_dwFlags & SplitterRightBorder));

			pContPane = (iCol < m_panes.GetColCount() - 1)? &m_panes.GetCell(iRow, static_cast<short>(iCol + 1)) : NULL;
			drawInfo.bDrawHConnector = pContPane && (iRow == (pContPane->nRowOrigin + pContPane->nRowSpan - 1));
			pContPane = (iRow < m_panes.GetRowCount() - 1)? &m_panes.GetCell(static_cast<short>(iRow + 1), iCol) : NULL;
			drawInfo.bDrawVConnector = pContPane && (iCol == (pContPane->nColOrigin + pContPane->nColSpan - 1));

			// This DC expects painting via the relative client coordinates
			DrawCellSplitter(drawInfo);
		}
	}
}


void CSplitterLayout::DrawCellSplitter (
										const CSplitterDrawInfo& sdInfo
										)
{
	HDC hdc = sdInfo.hdc;

	CRect rcSplitterRow(sdInfo.rcCell.left, sdInfo.rcCell.bottom, sdInfo.rcCell.right + m_nSplitterWidth, sdInfo.rcCell.bottom + m_nSplitterWidth);
	CRect rcSplitterCol(sdInfo.rcCell.right, sdInfo.rcCell.top, sdInfo.rcCell.right + m_nSplitterWidth, sdInfo.rcCell.bottom + m_nSplitterWidth);

	// Paint the splitter interior
	if (sdInfo.bDrawHSplitter) {
		::FillRect(sdInfo.hdc, rcSplitterRow, reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1));
	}
	if (sdInfo.bDrawVSplitter) {
		::FillRect(sdInfo.hdc, rcSplitterCol, reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1));
	}

	if (sdInfo.dwDrawingStyle == DrawBorder) {
		return;
	}

	short nShadowPos = static_cast<short>((sdInfo.dwDrawingStyle == DrawTraditional)? 1 : 0);

	// Paint the hilite:
	CRect rcHilite;
	rcHilite.SetRect(rcSplitterRow.TopLeft(), CPoint(rcSplitterCol.left + 1, rcSplitterRow.top + 1));
	if (sdInfo.bDrawHSplitter) {
		if (!sdInfo.bDrawVSplitter) {
			rcHilite.right = rcSplitterRow.right;
		}
		::FillRect(hdc, rcHilite, reinterpret_cast<HBRUSH>(COLOR_BTNHIGHLIGHT + 1));
	}
	if (sdInfo.bDrawHConnector) {
		rcHilite.left = rcSplitterCol.right - nShadowPos - 1; rcHilite.right = rcSplitterRow.right;
		::FillRect(hdc, rcHilite, reinterpret_cast<HBRUSH>(COLOR_BTNHIGHLIGHT + 1));
	}

	rcHilite.SetRect(rcSplitterCol.TopLeft(), CPoint(rcSplitterCol.left + 1, rcSplitterRow.top + 1));
	if (sdInfo.bDrawVSplitter) {
		if (!sdInfo.bDrawHSplitter) {
			rcHilite.bottom = rcSplitterCol.bottom;
		}
		::FillRect(hdc, rcHilite, reinterpret_cast<HBRUSH>(COLOR_BTNHIGHLIGHT + 1));
	}
	if (sdInfo.bDrawVConnector) {
		rcHilite.top = rcSplitterRow.bottom - nShadowPos - 1; rcHilite.bottom = rcSplitterCol.bottom;
		::FillRect(hdc, rcHilite, reinterpret_cast<HBRUSH>(COLOR_BTNHIGHLIGHT + 1));
	}


	// Paint the shadow
	CRect rcShadow;
	rcShadow.SetRect(rcSplitterRow.left, rcSplitterRow.bottom - nShadowPos - 1, rcSplitterCol.left, rcSplitterRow.bottom - nShadowPos);
	if (sdInfo.bDrawHSplitter) {
		if (!sdInfo.bDrawVConnector) {
			rcShadow.right = rcSplitterRow.right;
		}
		::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_BTNSHADOW + 1));
	}
	if (sdInfo.bDrawHConnector) {
		rcShadow.left = rcSplitterCol.right - nShadowPos - 1; rcShadow.right = rcSplitterRow.right;
		::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_BTNSHADOW + 1));
	}

	rcShadow.SetRect(rcSplitterCol.right - nShadowPos - 1, rcSplitterCol.top, rcSplitterCol.right - nShadowPos, rcSplitterRow.top);
	if (sdInfo.bDrawVSplitter) {
		if (!sdInfo.bDrawHConnector) {
			rcShadow.bottom = rcSplitterCol.bottom;
		}
		::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_BTNSHADOW + 1));
	}
	if (sdInfo.bDrawVConnector) {
		rcShadow.top = rcSplitterRow.bottom - nShadowPos - 1; rcShadow.bottom = rcSplitterCol.bottom;
		::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_BTNSHADOW + 1));
	}


	if (sdInfo.dwDrawingStyle == DrawTraditional) {
		// Paint the frame
		rcShadow.SetRect(rcSplitterRow.left, rcSplitterRow.bottom - 1, rcSplitterCol.left, rcSplitterRow.bottom);
		if (sdInfo.bDrawHSplitter) {
			if (!sdInfo.bDrawVConnector) {
				rcShadow.right = rcSplitterRow.right;
			}
			::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME + 1));
		}
		if (sdInfo.bDrawHConnector) {
			rcShadow.left = rcSplitterCol.right - 1; rcShadow.right = rcSplitterRow.right;
			::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME + 1));
		}
		rcShadow.SetRect(rcSplitterCol.right - 1, rcSplitterCol.top, rcSplitterCol.right, rcSplitterRow.top);
		if (sdInfo.bDrawVSplitter) {
			if (!sdInfo.bDrawHConnector) {
				rcShadow.bottom = rcSplitterCol.bottom;
			}
			::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME + 1));
		}
		if (sdInfo.bDrawVConnector) {
			rcShadow.top = rcSplitterRow.bottom - 1; rcShadow.bottom = rcSplitterCol.bottom;
			::FillRect(hdc, rcShadow, reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME + 1));
		}
	}
}


void CSplitterLayout::DrawTrackerRect (
									   HDC hdcTracker, 
									   CRect rcTracker, 
									   bool bRow, 
									   bool bErase
									   )
{
	CSize szTracker(0, 0);
	CGraphicsContext dc(hdcTracker);

	CRect rcLastTracker = bRow? m_rcLastRowTracker : m_rcLastColTracker;
	CSize szLastTracker = bRow? m_szLastRowTracker : m_szLastColTracker;
	if (bRow) {
		rcTracker.InflateRect(0, -1);
		if (!bErase) {
			szTracker.cx = 0;
			szTracker.cy = m_nSplitterWidth - 1;
		}
	}
	else {
		rcTracker.InflateRect(-1, 0);
		if (!bErase) {
			szTracker.cx = m_nSplitterWidth - 1;
			szTracker.cy = 0;
		}
	}

	dc.DrawDragRect(rcTracker, szTracker, rcLastTracker, szTracker);
	//dc.Rectangle(&rcTracker);

	if (bRow) {
		m_rcLastRowTracker = rcTracker;
		m_szLastRowTracker = szTracker;
	}
	else {
		m_rcLastColTracker = rcTracker;
		m_szLastColTracker = szTracker;
	}
}


/////////////////////////////////////////////////
// Splitter Mouse Tracking 


void CSplitterLayout::StartTracking (
									 CPoint point, 
									 short iRowSplitter, 
									 short iColSplitter
									 )
{
	// Avoid reentrancy
	if (m_bTracking) {
		return;
	}

	m_bTracking = true;

	// Allow subclass to abort track operation
	if (!OnSplitterDragStart(point, iRowSplitter, iColSplitter)) {
		m_bTracking = false;
		return;
	}

	// Some misc init per each new track
	m_rcLastRowTracker.SetRectEmpty();
	m_rcLastColTracker.SetRectEmpty();
	m_szLastRowTracker.cx = m_szLastRowTracker.cy = 0;
	m_szLastColTracker.cx = m_szLastColTracker.cy = 0;

	try {
		// Drag the splitter(s) here
		CSize szDelta;
		szDelta = Track(point, iRowSplitter, iColSplitter);
	}
	catch (...) {
	}

	// Signal end for critical section
	m_bTracking = false;
}


CSize CSplitterLayout::Track (
							  CPoint point, 
							  short iRowSplitter, 
							  short iColSplitter
							  )
{
	point;

	CSize szDelta(0, 0);

	// don't handle if capture already set
	if (GetCapture() != NULL) {
		return szDelta;
	}

	// Set capture to monopolize mouse messages, even outside this window
	::SetCapture(m_hWnd);
	_ASSERTE(m_hWnd == ::GetCapture());

	::UpdateWindow(m_hWnd);

	// get DC for drawing
	HDC hdcDraw = GetTrackerDC();
	//_ASSERTE(hdcDraw);

	// Save the current splitter positions in case the drag is aborted
	CRect rcRowSplitter = GetRowSplitterRect(iRowSplitter);
	CRect rcColSplitter = GetColSplitterRect(iColSplitter);
	CRect rcOriginalRow = rcRowSplitter;
	CRect rcOriginalCol = rcColSplitter;

	// Draw initial tracking rect(s) over the current positions
	if (!(m_dwFlags & SplitterRealtimeDrag)) {
		if (iRowSplitter != -1) {
			DrawTrackerRect(hdcDraw, rcRowSplitter, true);
		}
		if (iColSplitter != -1) {
			DrawTrackerRect(hdcDraw, rcColSplitter, false);
		}
	}

	// Handle the capture events, including drag movement
	if (TrackMessageLoop(hdcDraw, iRowSplitter, iColSplitter, rcRowSplitter, rcColSplitter)) {
		// Drag operation successfully finished, new position

		// Calculate the change in splitter position to be returned to caller.
		szDelta.cx = rcColSplitter.left - rcOriginalCol.left;
		szDelta.cy = rcRowSplitter.top - rcOriginalRow.top;

		// Pump virtual override to tweak resultant splitter rects, if desired
		if (rcOriginalRow != rcRowSplitter) {
			szDelta -= OnAdjustFinalSplitterRect(rcRowSplitter, true);
		}
		if (rcOriginalCol != rcColSplitter) {
			szDelta -= OnAdjustFinalSplitterRect(rcColSplitter, false);
		}

		if (!(m_dwFlags & SplitterRealtimeDrag)) {
			// Erase any visible trackers
			if (iRowSplitter != -1) {
				DrawTrackerRect(hdcDraw, CRect(), true);
			}
			if (iColSplitter != -1) {
				DrawTrackerRect(hdcDraw, CRect(), false);
			}
			m_rcLastRowTracker.SetRectEmpty();
			m_rcLastColTracker.SetRectEmpty();

			// Trigger a recalc of both splitters
			if ((szDelta.cx != 0) || (szDelta.cy != 0)) {
				// Apply the new positions 
				MoveSplitter(iRowSplitter, iColSplitter, szDelta);
				OnSplitterMoved(szDelta);
			}
		}

	}
	else {
		// Drag operation cancelled
		if (m_dwFlags & SplitterRealtimeDrag) {
			CSize szResetDelta(rcOriginalCol.left - rcColSplitter.left, rcOriginalRow.top - rcRowSplitter.top);
			MoveSplitter(iRowSplitter, iColSplitter, szResetDelta);
			OnSplitterMoved(szDelta);
		}
	}

	// Cleanup
	try { 
		::ReleaseDC(NULL, hdcDraw); 
	}
	catch(...) {
	}

	::ReleaseCapture();

	return szDelta;
}


bool CSplitterLayout::TrackMessageLoop (
										HDC hdcTracker, 
										short iRowSplitter, 
										short iColSplitter, 
										CRect& rcRowSplitter,
										CRect& rcColSplitter
										)
{
	bool bCanceled = false;
	bool bKeepTracking = true;

	CPoint ptOldPos;
	::GetCursorPos(&ptOldPos);
	::MapWindowPoints(HWND_DESKTOP, m_hWnd, &ptOldPos, 1);

	// Spin our own message loop until capture lost or cancelled/accepted
	while (bKeepTracking) {
		MSG msg;
		::GetMessage(&msg, NULL, 0, 0);


		// Capture lost?
		if (::GetCapture() != m_hWnd) {
			break;
		}

		switch (msg.message) {
			// handle movement/accept messages
			case WM_MOUSEMOVE: {
				CPoint ptNewPos(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
				OnTrackMouseMove(hdcTracker, ptOldPos, ptNewPos, iRowSplitter, iColSplitter, rcRowSplitter, rcColSplitter);
				ptOldPos = ptNewPos;

				// Allow paint messages to keep up with rapid
				// mousemoves, else screen gets out of whack.
				PumpPaintMessages();
				break;
							   }
			case WM_LBUTTONUP: { // Drag operation has completed successfully - invoke NULL
				bKeepTracking = false;
				break;
							   }

							   // Escape or right mouse click will cancel the drag:
			case WM_KEYDOWN: 
				if (msg.wParam != VK_ESCAPE) {
					break;
				}
			case WM_RBUTTONDOWN: {
				// Cancel the drag operation. If row or column splitter has
				// moved, then restore old position.
				bCanceled = true;
				bKeepTracking = false;
				break;
								 }
								 // just dispatch rest of the messages
			default: {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
				break;
					 }
		}
	}

	return !bCanceled;
}


void CSplitterLayout::OnTrackMouseMove (
										HDC hdcTracker,
										CPoint ptOldPos,
										CPoint ptNewPos,
										short iRowSplitter,
										short iColSplitter,
										CRect& rcRowSplitter,
										CRect& rcColSplitter
										)
{
	ptOldPos;

	// handle resize cases (and part of move)
	CRect rcOldRow = rcRowSplitter;
	CRect rcOldCol = rcColSplitter;

	// Establish new splitter and/or drag rect positioning
	CPoint ptSplitterPos;
	CSize szDelta;

	if (iRowSplitter != -1) {
		ptSplitterPos.y = ptNewPos.y - (m_nSplitterWidth / 2);
		if (ptSplitterPos.y < m_rcCurrent.top || ptSplitterPos.y >= m_rcCurrent.bottom - m_nSplitterWidth) {
			ptSplitterPos.y = (ptSplitterPos.y < m_rcCurrent.top)? (m_rcCurrent.top) : (m_rcCurrent.bottom - m_nSplitterWidth);
		}
		rcRowSplitter.top = ptSplitterPos.y;
		rcRowSplitter.bottom = rcRowSplitter.top + m_nSplitterWidth;
	}

	if (iColSplitter != -1) {
		ptSplitterPos.x = ptNewPos.x - (m_nSplitterWidth / 2);
		if (ptSplitterPos.x < m_rcCurrent.left || ptSplitterPos.x >= m_rcCurrent.right - m_nSplitterWidth) {
			ptSplitterPos.x = (ptSplitterPos.x < m_rcCurrent.left)? (m_rcCurrent.left) : (m_rcCurrent.right - m_nSplitterWidth);
		}
		rcColSplitter.left = ptSplitterPos.x;
		rcColSplitter.right = rcColSplitter.left + m_nSplitterWidth;
	}

	// only redraw and callback if the rect actually changed!
	szDelta.cx = rcColSplitter.left - rcOldCol.left;
	szDelta.cy = rcRowSplitter.top - rcOldRow.top;

	if (m_dwFlags & SplitterRealtimeDrag) {
		// Real-time drag. Update immediately
		MoveSplitter(iRowSplitter, iColSplitter, szDelta);
	}
	else {
		if (iRowSplitter != -1 && !rcRowSplitter.EqualRect(&rcOldRow)) {
			// Draw row tracking rect only if moving row splitter
			DrawTrackerRect(hdcTracker, rcRowSplitter, true);
		}

		if (iColSplitter != -1 && !rcColSplitter.EqualRect(&rcOldCol)) {
			// Draw col tracking rect only if moving row splitter
			DrawTrackerRect(hdcTracker, rcColSplitter, false);
		}
	}

	// If splitter actually moved
	if ((m_dwFlags & SplitterRealtimeDrag) && (szDelta != CSize(0, 0))) {
		OnSplitterMoved(szDelta);
	}
}


void CSplitterLayout::PumpPaintMessages() { 
	MSG msg;
	while(::PeekMessage(&msg, NULL, WM_PAINT, WM_PAINT, PM_REMOVE)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}  
}


HDC CSplitterLayout::GetTrackerDC (
								   ) 
{
	// Get a DC for the entire screen.
	// The reason this DC is gotten for the screen and not for the associated window
	// is because the window may have the WS_CLIPCHILDREN style set,
	// preventing the tracker rectangle to be correctly drawn
	HDC hdcTracker = ::GetDC(NULL);

	// Map the logical origin to the client area of this window
	CPoint ptOrg(0, 0);
	::MapWindowPoints(m_hWnd, HWND_DESKTOP, &ptOrg, 1);
	::SetViewportOrgEx(hdcTracker, ptOrg.x, ptOrg.y, NULL);

	return hdcTracker;
}


CSize CSplitterLayout::OnAdjustFinalSplitterRect (
	CRect& rcSplitter, 
	bool bRow
	)
{
	rcSplitter; bRow;

	CSize szAdjustment(0, 0);
	return szAdjustment;
}


void CSplitterLayout::OnSplitterMoved (
									   CSize szDelta
									   )
{
	szDelta;
	CLayoutTransaction aTransaction;
	RealizeNode(aTransaction);
}

};
};

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
	#pragma warning (pop)
	#endif
#endif
