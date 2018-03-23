///////////////////////////////////////////////////////////////////////////////
// DynGrid.h : Declaration of SECLNDynamicGridLine
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
// Description:  Declaration of SECLNDynamicGridLine class
//

#ifndef __SECLNDYNAMIC_GRID_LINE_H__
#define __SECLNDYNAMIC_GRID_LINE_H__

// Header Includes
#include "toolkit\layout\NodeSplt.h"
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

//
// Class SECLNDynamicGridLine
//
// This layout node type is provided
// as a convenience for inserting several splitters side by side without
// the need to consider deep tree nesting. For example, scenarios like this
// are now easily possible:
//
// -----------------
// | A | B | C | D |
// -----------------
//
// Instead of having to manually track a complex tree like this:
// 
// -------------------------
// | ----------------- |   |
// | | --------- |   | |   |
// | | | A | B | | C | | D |
// | | --------- |   | |   |
// | ----------------- |   |
// -------------------------
//
// In addition, SECLNDynamicGridLine supports "virtual splitters",
// i.e. the capability for 1 splitter to be dragged beyond the contents
// of 1 of its panes. For example, the splitter between A,B above
// could conceivably be dragged to the right past node C (with the
// requisite change in layout administrated by the composite parent).
// 
// Static nodes (non-resizable via splitter) can also be inserted 
// anywhere in the line.
//

/////////////////////////////////////////////////////////////////////////////
// SECDynGridInsertConstraints

// Insertion constraints associated with a new node addition to 
// an SECLNDynamicGridLine derived class. Encapsulates
// several diverse insertion criteria in an easy to use object,
// rather than exposing via a long, convoluted API.

//@doc SECDynGridInsertConstraints 
//@class Insertion constraints associated with a new node addition to the grid.
//@xref <c SECDockInsertionConstraints>
class SECDynGridInsertConstraints 
{
public:
	TOOLKIT_API SECDynGridInsertConstraints();
	TOOLKIT_API virtual ~SECDynGridInsertConstraints();

	//@access Operations

	//@cmember
	/* Copy insertion constraints from a different insertion constraint object. */
	TOOLKIT_API virtual void CopyFrom(const SECDynGridInsertConstraints& Src);

	//@cmember
	/* Reset constraints to acceptable defaults. */
	TOOLKIT_API virtual void Reset();

	//@access Configuration

	//@cmember Insertion will occur relative to this node. If NULL, insertion will occur at head or tail.
	SECLayoutNode* m_pNodeRelative;

	//@cmember Used in conjunction with m_pNodeRelative, controls if insertion should be before or after. If m_pNodeRelative is NULL, TRUE denotes tail, FALSE head.
	BOOL m_bInsertAfter;

	//@cmember
	/* Alternate to m_pNodeRelative relative insertion specification */
	TOOLKIT_API void SetInsertPosition(UINT nPos,BOOL bAfter=TRUE,BOOL bPrimaryCnstr=TRUE);

	//@cmember
	/* Get the insertion position configured by SetInsertPosition */
	TOOLKIT_API BOOL GetInsertPosition(UINT& nPos) const;	
	
	//@cmember If TRUE, insertion will create a new line before or after the parent line of the set relative insertion node/position.
	BOOL m_bCreateNewLine;

	//@cmember If TRUE, node will be bounded by a sizing splitter if it has an adjacent neighbor. If FALSE, no sizing splitter will be provided.
	BOOL m_bDynamicNode;

	//@cmember Forced insertion size. If positive, node will be inserted with this size (width for horizontal, height for vertical). If negative (default) an average size will be used.
	int m_nForcedSize;			

	//@cmember Forced newline insertion size. Similar to m_nForcedSize, but applied only to new line creation (m_bCreateNewLine==TRUE, or first insertion)
	int m_nForcedNewLineSize;	

	TOOLKIT_API void SetInsertPoint(const CPoint& ptNodeInsert,BOOL bEnable=TRUE);
	TOOLKIT_API BOOL GetInsertPoint(CPoint& ptNodeInsert);

protected:
	BOOL m_bInsertPointActive;
	CPoint m_ptInsert;
	UINT m_nNodeRelativePos;
	BOOL m_bNumericPosPrimary;
	UINT m_nNodeRelativeLinePos;	// utility value for use with SetInsertPosition

	friend class SECLNDynamicGrid2d;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDynamicGridLineCell

class SECLNDynamicGridLineCell 
{
public:
	TOOLKIT_API SECLNDynamicGridLineCell();	

	BOOL m_bDynamicCell;
	SECLNVirtualSplitter* m_pSplitterPrev,*m_pSplitterNext;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDynamicGridLine

//
//						ISECParentOfNegotiableChildNode
//								  |
//						SECParentOfNegotiableChildNode
//								  |	 ISECVirtualSplitterObserver
// SECLayoutNode ISECUndoableNode |	  		|		ISECReparentableNode
//			|			  |		  |	       	|			|
//			------------- |	      | --------|	    -----
//						| |	      ||	------------|
//						| |	      ||	|
//					SECLNDynamicGridLine

class SECLNDynamicGridLine : 	public SECLayoutNode,
								public ISECUndoableNode,
								public ISECVirtualSplitterObserver,
								public ISECReparentableNode,
								public SECParentOfNegotiableChildNode,
								public SECDefHideableNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNDynamicGridLine();
	TOOLKIT_API virtual ~SECLNDynamicGridLine();

	// Accessors
	//	...Get and Set functions...
	enum SizingAlgorithm { 	SizeFirstToLast, 	// apply size changes to left/top cell first, then work outward
							SizeLastToFirst, 	// apply size changes to right/bottom cell first, then work inward
							SizeAllEqually };	// apply size changes equally to all elements in list

	inline void SetSizingAlgorithm(SizingAlgorithm Algorithm) { m_SizingAlgorithm=Algorithm; }
	inline SizingAlgorithm GetSizingAlgorithm() { return m_SizingAlgorithm; }

	TOOLKIT_API static void SetDefSizingAlgorithm(SizingAlgorithm Alg);
	TOOLKIT_API static SizingAlgorithm GetDefSizingAlgorithm();

	// "Stretch to contain" mode will grow/shrink this 
	// node to accomodate new additions, removals.
	TOOLKIT_API void SetStretchToContainChildrenMode(BOOL bEnable=TRUE);
	inline BOOL GetStretchToContainChildrenMode() { return m_bStretchToContain; }

	TOOLKIT_API virtual void SetSplitterRealtimeDragMode(BOOL bEnable=TRUE);
	inline BOOL GetSplitterRealtimeDragMode() { return m_bSplitterRealtimeDrag; }

	inline HWND GetParentWindow() {return m_hWndParent;};
	
	// Overrides
	// SECLayoutNode overrides

	// Operations
	TOOLKIT_API virtual void InitializeLine(HWND hWndParent,BOOL bHorzOrientation=TRUE);
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNodeToAdd);
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNodeToAdd,
							SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNodeToRemove);
	// ISECUndoableNode implementation	
	TOOLKIT_API virtual ISECUndoableNode* QueryOptimalUndoNode();
	TOOLKIT_API virtual int UndoableRemoveLayoutNode(SECLayoutNode* pNodeToRemove);
	TOOLKIT_API virtual int RestoreLastRemoveLayoutNode();
	TOOLKIT_API virtual int RestoreRemoveLayoutNode(SECLayoutNode* pNode);	
	
	// ISECReparentableNode implementation
	TOOLKIT_API virtual BOOL ReparentNode(ISECLNContainer* pNewOwner);	
	virtual ISECLNContainer* GetContainer() { return NULL; }	

	// Utility Functions
	TOOLKIT_API virtual SECLayoutNode* LocateCellNodeFromPoint(const CPoint& ptNodeHit,BOOL& bAfter,
													SECLNDynamicGridLine** ppLineParent);
	TOOLKIT_API virtual BOOL HasChildNode(SECLayoutNode* pChild);
	virtual int GetNodeCellChildCount() { return (int)m_listOrderedNodeCells.GetCount(); }
	virtual SECLayoutNode* GetHeadCellNode() { return m_listOrderedNodeCells.GetHead(); }
	TOOLKIT_API virtual SECLayoutNode* GetAdjacentCellNode(SECLayoutNode* pNodeRelative,BOOL bNextNode=TRUE);
	TOOLKIT_API virtual SECLNDynamicGridLineCell* GetCell(SECLayoutNode* pNode);
	TOOLKIT_API virtual UINT CalcAvgCellSize(BOOL bCalcForInsertion=FALSE);
	TOOLKIT_API virtual void AppendChildNodeList(SECLayoutNodePtrList& listNodes);
	TOOLKIT_API virtual BOOL CalcChildConstraints(SECLayoutNode* pChild,SECDynGridInsertConstraints& cnstr);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// SECLayoutNode overrides
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);

	// ISECVirtualSplitterObserver overrides
	TOOLKIT_API virtual void OnNotifySplitterMovement(SECLNVirtualSplitter* pSplitter,
										int nDeltaX,int nDeltaY);

	// New Overridables
	TOOLKIT_API virtual void OnSetNewChildOrientation(SECLayoutNode* pNodeToAdd,
								SECDynGridInsertConstraints& InsertConstraint);

	// Object Allocation
	TOOLKIT_API virtual SECLNVirtualSplitter* CreateVirtualSplitter();

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	SizingAlgorithm			m_SizingAlgorithm;
	SECLayoutNodePtrList	m_listOrderedNodeCells;
	CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,SECLNDynamicGridLineCell*> m_mapNodeToCell;
	HWND					m_hWndParent;
	BOOL					m_bStretchToContain, m_bSplitterRealtimeDrag;
	CSize					m_szDeltaPendingChildNegotiateRecalc;
	CSize					m_szMinCachedForStretch, m_szMaxCachedForStretch;
	DWORD					m_dwMinMaxFlagsForStretch;
	SECLNMemMgr				m_mgrVirtualSplitters;
	TOOLKIT_API static SizingAlgorithm	m_DefSizingAlgorithm;
	
	// Undoable Node Cached values
	SECDynGridInsertConstraints m_UndoNodeConstraints;
	SECLayoutNode*				m_pUndoableRemovedNode;

	// AddLayoutNode helper functions
	TOOLKIT_API virtual void PostProcessAddNode(SECLayoutNode* pNode,
							SECDynGridInsertConstraints& InsertConstraint);		
	TOOLKIT_API virtual SECLNDynamicGridLineCell* CreateNewCell(SECLayoutNode* pNode,
							const SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual BOOL RemoveExistingCell(SECLayoutNode* pNode);
	TOOLKIT_API virtual BOOL ResolveInsertionPosition(SECLayoutNode* pNodeToAdd,
							const SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual POSITION GetNodePosFromIndex(int nIndex,BOOL& bAfter);
	TOOLKIT_API virtual BOOL RemoveInsertionPosition(SECLayoutNode* pNodeToRemove);

	// RemoveLayoutNode helper functions
	TOOLKIT_API virtual void PostProcessRemoveNode(SECLayoutNode* pNodeToRemove);

	// Logic for resolving splitter parenting on new node addition
	TOOLKIT_API virtual BOOL SetVSplittersOnAdd(SECLayoutNode* pNewNode);
	TOOLKIT_API virtual BOOL SetVSplitterBetween2Nodes(SECLayoutNode* pNodePrev,
										SECLayoutNode* pNewNode,
										SECLayoutNode* pNextNode);
	TOOLKIT_API virtual BOOL SetVSplitterAdjacentNodes(SECLayoutNode* pNodeFirst,
										SECLayoutNode* pNodeSecond);

	// Logic for resolving splitter parenting on node removal
	TOOLKIT_API virtual BOOL SetVSplittersOnRemove(SECLayoutNode* pRemoveNode);
	TOOLKIT_API virtual BOOL RemoveVSplitterBetween2Nodes(SECLayoutNode* pNodePrev,
										SECLayoutNode* pRemoveNode,
										SECLayoutNode* pNextNode);
	TOOLKIT_API virtual BOOL RemoveVSplitterAdjacentNodes(SECLayoutNode* pNodeFirst,
										SECLayoutNode* pNodeSecond);

	// Layout Utility Functions
	TOOLKIT_API virtual UINT CalcTotalVSplitterSize(SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual BOOL SizeCellsToFit(SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual BOOL SizeCellsToFit(UINT nSizeToFit,SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual UINT CalcCurrentCellSize(UINT& nCurrentCellSize,SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual BOOL SizeCellsToFitAllEqually(int nNeededDelta,UINT nCells,SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual BOOL SizeCellsToFitOneDirection(int nNeededDelta,
										UINT nCells,
										BOOL bFirstToLast,
										SECLayoutNode* pExcludeNode=NULL);
	TOOLKIT_API virtual BOOL ClipCellSizesToFit(int nNeededDelta,BOOL bFirstToLast);
	virtual BOOL ApplyCellPositions() { return ApplyCellPositions(GetCurrentRect()); }										
	TOOLKIT_API virtual BOOL ApplyCellPositions(const CRect& rectDesired);
	TOOLKIT_API virtual BOOL SetVirtualSplitterBoundingRanges(SECLayoutNode* pNodeStart,
										SECLayoutNode* pNodeStop);
	TOOLKIT_API virtual int CalcMinSumTable(CUIntArray& arrMinSumTable,
										SECLayoutNode* pNodeStart,
										SECLayoutNode* pNodeStop);
	TOOLKIT_API virtual CRect CalcRangeBoundingRect(SECLayoutNode* pNodeStart,
										SECLayoutNode* pNodeStop);

	// OnNotifySplitterMovement helper functions
	TOOLKIT_API virtual BOOL LocateSplitterPanes(SECLNVirtualSplitter* pSplitter,
										SECLayoutNode** ppNodeBefore,
										SECLayoutNode** ppNodeAfter);
	TOOLKIT_API virtual int SlideDynamicCellSizes(SECLayoutNode* pNodeRelative,
										int nChange,						
										BOOL bIncreasing,					
										SECLayoutNode** ppInvalidateBound);
	TOOLKIT_API virtual BOOL RealizeNodeRange(SECLayoutNode* pInvalidateStart,
										SECLayoutNode* pInvalidateStop);

	// Utility Worker Functions
	TOOLKIT_API virtual BOOL GetNextAndPrevNodes(SECLayoutNode* pNodeReference,
										SECLayoutNode** ppPrevNode,
										SECLayoutNode** ppNextNode);
	TOOLKIT_API virtual void SetNodeRectWithinMinMax(SECLayoutNode* pNode,CRect& rcNode);
	TOOLKIT_API virtual void ClearCellList();
	TOOLKIT_API virtual BOOL TestHitBeforeOrAfter(const CRect& rectNode,const CPoint& ptHit);
	TOOLKIT_API virtual BOOL AdjustNewRectWithPendingDeltas(CRect& rectNew);
	TOOLKIT_API virtual BOOL GetNodeNumericPos(SECLayoutNode* pNode,UINT& nNodePos,UINT& nNodeCount);
	
	// Undo-Redo workers
	TOOLKIT_API virtual int UndoRestoreLayoutNode(SECLayoutNode* pNode,SECDynGridInsertConstraints& cnstr);

	stingray::foundation::SECObjectMemoryManager_T<SECDynGridInsertConstraints> m_mgrUndoCnstr;							
	CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,SECDynGridInsertConstraints*> m_mapNodeToUndoCnstr;

	// Friend Class Declarations
#ifdef SECLAYOUTNODE_EXTENDED_DIAGNOSTICS
	friend class SECLNDiagnostics;			// Debug Diagnostic Support
#endif
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

#endif //__SECLNDYNAMIC_GRID_LINE_H__
