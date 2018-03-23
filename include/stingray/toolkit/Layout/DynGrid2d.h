///////////////////////////////////////////////////////////////////////////////
// DynGrid2d.h : Declaration of SECLNDynamicGrid2d
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
// Description:  Declaration of SECLNDynamicGrid2d class
//

// 2 dimensional implementation of SECLNDynamicGridLine

#ifndef __SECLNDYNAMIC_GRID_2D_H__
#define __SECLNDYNAMIC_GRID_2D_H__

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

/////////////////////////////////////////////////////////////////////////////
// ISECPreferredNodeRectSet

// Very simplistic interface for preferred rect reset toggle.

class ISECPreferredNodeRectSet 
{
public:
	virtual ~ISECPreferredNodeRectSet() {}
	TOOLKIT_API virtual void FlagPreferredRectResetOnNextRecalc()=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDynamicGrid2d

class SECLNDynamicGrid2d : 	public SECLNDynamicGridLine,
							public ISECPreferredNodeRectSet 
{

public:	
	TOOLKIT_API SECLNDynamicGrid2d();
	virtual ~SECLNDynamicGrid2d() {}

	// SECLNDynamicGridLine overrides
	TOOLKIT_API virtual void SetSplitterRealtimeDragMode(BOOL bEnable=TRUE);
	TOOLKIT_API virtual void InitializeLine(HWND hWndParent,BOOL bHorzOrientation=TRUE);
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNodeToAdd,
							SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNodeToRemove);
	TOOLKIT_API virtual int GetNodeCellChildCount();
	TOOLKIT_API virtual SECLayoutNode* GetHeadCellNode();
	TOOLKIT_API virtual SECLayoutNode* LocateCellNodeFromPoint(const CPoint& ptNodeHit,BOOL& bAfter,
													SECLNDynamicGridLine** ppLineParent);
	TOOLKIT_API virtual void AppendChildNodeList(SECLayoutNodePtrList& listNodes);													
	TOOLKIT_API virtual BOOL CalcChildConstraints(SECLayoutNode* pChild,SECDynGridInsertConstraints& cnstr);

	// ISECUndoableNode overrides
	virtual ISECUndoableNode* QueryOptimalUndoNode() { return this; }

	// ISECPreferredNodeRectSet implementation
	virtual void FlagPreferredRectResetOnNextRecalc() { m_bResetPreferredRectOnNextRecalc=TRUE; }

protected:
	// SECLayoutNode overrides
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);

	// Overridables
	virtual SECLNDynamicGridLine* CreateDynGridLine() { return new SECLNDynamicGridLine; }
	TOOLKIT_API virtual SECLNDynamicGridLine* CreateNewLineChildAndInsertNode(
								SECLayoutNode* pNodeToAdd,
								SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual void OnSetNewChildOrientation(SECLayoutNode* pNodeToAdd,
								SECDynGridInsertConstraints& InsertConstraint);

protected:
	
	// Implementation Member Functions
	TOOLKIT_API virtual SECLNDynamicGridLine* LocateChildLine(SECLayoutNode* pSearchNode);
	TOOLKIT_API virtual SECLNDynamicGridLine* GetHeadOrTailChildLine(BOOL bGetTail);

	// Implementation Member Variables
	BOOL m_bResetPreferredRectOnNextRecalc;
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

#endif //__SECLNDYNAMIC_GRID_2D_H__
