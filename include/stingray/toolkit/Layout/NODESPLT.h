///////////////////////////////////////////////////////////////////////////////
// NodeSplt.h : Declaration of SECLayoutNodeSplitter
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
// Description:  Declaration of SECLayoutNodeSplitter
//

#ifndef __SECSPLITTERNODE_H
#define __SECSPLITTERNODE_H

// Header Includes
#ifndef __SECSPLITTERBASE_H
#include "toolkit\layout\splitter.h"
#endif

#ifndef __SECLAYOUTNOD_H__
#include "toolkit\layout\layoutnd.h"
#endif

#ifndef __SECLAYOUTNODEWND_H__
#include "toolkit\layout\NodeWnd.h"
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
// SECLayoutNodeSplitter

//
//	CWnd					SECLayoutNode
//	  |						|
//	  SECSplitterBase	SECLayoutNodeWnd
//				|		|
//			SECLayoutNodeSplitter
//

//@doc SECLayoutNodeSplitter 
//@class Splitter node for layout framework
//@BASE public | SECSplitterBase
//@BASE public | SECLayoutNode
//@comm This class is a marriage of the base splitter functionality to the layout node hierarchy.

class SECLayoutNodeSplitter : public SECSplitterBase, public SECLayoutNodeWnd
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLayoutNodeSplitter();
	TOOLKIT_API virtual ~SECLayoutNodeSplitter();

	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd,CRect rect=CRect(0,0,0,0),
				DWORD dwStyle=WS_CHILD|WS_VISIBLE,
				UINT nID=SEC_DEF_SPLITTER_ID,DWORD dwFlags=0);

	TOOLKIT_API virtual void SetNodeExStyle(DWORD dwExStyle=0,BOOL bRecurseChildren=FALSE);
	TOOLKIT_API virtual void SetSplitterPositions(int xColPos=0,int yRowPos=0);

	// Operations
	//@cmember
	/* Add a layout node as a splitter pane*/
	TOOLKIT_API virtual BOOL AddPane(USHORT nRow,USHORT nCol,SECLayoutNode* pNode);
	TOOLKIT_API virtual BOOL RemovePane(USHORT nRow,USHORT nCol);

	// Splitter needs special hand-holding for Z-Order, hence the override
	TOOLKIT_API virtual void RecalcZOrder(BOOL bRecurseChildren);
	TOOLKIT_API virtual BOOL RealizeNodeHelper(HDWP* phDWP,HDC hDC);	

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// SECSplitterBase overrides:
	TOOLKIT_API virtual void OnSetPanePositions(SECSplitterPaneInfo* pPaneInfo);
	TOOLKIT_API virtual void OnSplitterMoved(int deltaX,int deltaY);
	TOOLKIT_API virtual void OnSplitterInvalidate(CRect rectInvalid,BOOL bErase);
	TOOLKIT_API virtual BOOL MoveAndSetSplitter(const CRect& rectNew,BOOL bRow);

	// SECLayoutNode overrides:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rectInvalid,BOOL bDoErase);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	CTypedPtrArray<CPtrArray,SECLayoutNode*> m_nodePanes;
	CRect m_rectNewRow,m_rectNewCol;
	BOOL m_bRowAddCastToggle;
	BOOL m_bColAddCastToggle;

	// Implementation member Functions
	TOOLKIT_API virtual CRect AdjustMinMaxPreferred(const CRect& rectOld,
									const CRect& rectNew,
									int& nColXOffset,int& nRowYOffset,
									BOOL bChildNegotiate);

	TOOLKIT_API virtual BOOL SizeOutsideLimit(int nSize,int nLimit,BOOL bTopBounding);
	TOOLKIT_API virtual BOOL SizeInsideLimit(int nSize,int nLimit,BOOL bTopBounding);
	TOOLKIT_API virtual void DistributeSplitterPixels(int& nSizeSide1,int& nSizeSide2,
											 int nLimitSide1,int nLimitSide2,
											 int& nPixelsToMove);
	TOOLKIT_API virtual void CalcMinMaxPrefHorz(int& nWidthMinWest,int& nWidthMinEast,
							int& nWidthMaxWest,int& nWidthMaxEast,
							int& nWidthPrefWest,int& nWidthPrefEast,
							const CRect& rectNew);
	TOOLKIT_API virtual void CalcMinMaxPrefVert(int& nHeightMinNorth,int& nHeightMinSouth,
							int& nHeightMaxNorth,int& nHeightMaxSouth,
							int& nHeightPrefNorth,int& nHeightPrefSouth,
							const CRect& rectNew);

	// Generated message map functions
	//{{AFX_MSG(SECLayoutNodeSplitter)
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

typedef CTypedPtrList<CPtrList,SECLayoutNodeSplitter*> SECLayoutNodeSplitterList;

/////////////////////////////////////////////////////////////////////////////
// ISECVirtualSplitterObserver

class ISECVirtualSplitterObserver 
{
public:
	virtual ~ISECVirtualSplitterObserver() {}		
	friend class SECLNVirtualSplitter;

protected:
	// Notification that a registered virtual splitter has been moved
	TOOLKIT_API virtual void OnNotifySplitterMovement(SECLNVirtualSplitter* pSplitter, int nDeltaX,int nDeltaY)=0; 
};

/////////////////////////////////////////////////////////////////////////////
// SECLNVirtualSplitter

//
//	CWnd					SECLayoutNode
//	  |						|
//	  SECSplitterBase	SECLayoutNodeWnd
//				|		|
//			SECLayoutNodeSplitter
//					|
//				SECLNVirtualSplitter
//

class SECLNVirtualSplitter : public SECLayoutNodeSplitter 
{
public:
	TOOLKIT_API SECLNVirtualSplitter();
	TOOLKIT_API virtual ~SECLNVirtualSplitter();

	inline void SetVirtualBoundingRect(const CRect& rcVirtual) { m_rcVirtual=rcVirtual; }
	inline CRect GetVirtualBoundingRect() { return m_rcVirtual; }

	inline void SetObserver(ISECVirtualSplitterObserver* pObserver) { m_pObserver=pObserver; }
	inline ISECVirtualSplitterObserver* GetObserver() { return m_pObserver; }

	// SECLayoutNode overrides	
	TOOLKIT_API virtual void SetNodeHorizontal(BOOL bHorz=TRUE,BOOL bRecurse=FALSE);	

protected:

	// SECLayoutNode overrides
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);

	// SECSplitterBase Overrides
	TOOLKIT_API virtual void RefreshSplitterClientRects();
	virtual void ResetPanePositions(const CRect&,const CRect&) {} // No-Op
	virtual void OnSetPanePositions(SECSplitterPaneInfo*) {} // No-Op 
	TOOLKIT_API virtual void OnSplitterMoved(int deltaX,int deltaY);
	TOOLKIT_API virtual CSize OnAdjustFinalSplitterRect(CRect& rectSplitter,
									const CRect& rectClient,BOOL bRowSplitter);
	TOOLKIT_API virtual BOOL MoveAndSetSplitter(const CRect& rectNew,BOOL bRow);
	TOOLKIT_API virtual HDC GetTrackerDC();
	TOOLKIT_API virtual void ConvertTrackerCoordinates(CRect& rcConverted,
										   CRect& rcLastConverted);
	TOOLKIT_API virtual BOOL GetSplitterBoundaries(int& nBoundLeft,int& nBoundTop,
									int& nBoundRight,int& nBoundBottom);
	TOOLKIT_API virtual BOOL OnPrepareDC(CDC* pDC);
	TOOLKIT_API virtual void OnDrawSplitters(CDC* pDC);

	// Implementation
	CRect m_rcVirtual, m_rcLastInvalidate;
	ISECVirtualSplitterObserver* m_pObserver;
};

typedef CTypedPtrList<CPtrList,SECLNVirtualSplitter*> SECVirtualSplitterList;

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __SECSPLITTERNODE_H

