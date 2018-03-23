///////////////////////////////////////////////////////////////////////////////
// SizeNode.h : Declaration of SECLNSizable
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
// Description:  Declaration of SECLNSizable class
//

#ifndef __SEC_LAYOUT_NODE_SIZABLE_H__
#define __SEC_LAYOUT_NODE_SIZABLE_H__

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

#if ( _MFC_VER < 0x0421 )
// disable warning 4097 for VC4.x:
// SECLNBorder intentially used as a synonym of SECLNBorder_T<SECLayoutNode>
#pragma warning(disable:4097)
#endif 

// Size Border flags for ShowSizeBorders function
#define SEC_LAYOUT_NODE_SIZE_NONE	0x0000
#define SEC_LAYOUT_NODE_SIZE_TOP	0x0001
#define SEC_LAYOUT_NODE_SIZE_BOTTOM	0x0002
#define SEC_LAYOUT_NODE_SIZE_LEFT	0x0004
#define SEC_LAYOUT_NODE_SIZE_RIGHT	0x0008
#define SEC_LAYOUT_NODE_SIZE_HORZ	SEC_LAYOUT_NODE_SIZE_LEFT | SEC_LAYOUT_NODE_SIZE_RIGHT
#define SEC_LAYOUT_NODE_SIZE_VERT	SEC_LAYOUT_NODE_SIZE_TOP | SEC_LAYOUT_NODE_SIZE_BOTTOM
#define SEC_LAYOUT_NODE_SIZE_ALL	SEC_LAYOUT_NODE_SIZE_HORZ | SEC_LAYOUT_NODE_SIZE_VERT

/////////////////////////////////////////////////////////////////////////////
// SECLNSizable
//
//
//	SECLayoutNode	ISECParentOfNegotiableChildNode
//		|					|
//		SECLNBorder	SECParentOfNegotiableChildNode I	SECVirtualSplitterObserver
//			|		|	---------------------------------|	
//			SECLNSizable
//

// Decorator node to add dynamic sizing capability to a child layout.
//
//  Example:
// 	Undecorated node:	   Decorated Node:
//	-------------------   -------------------
//  |                 |   |               | |
//  |                 |   |               | |
//  |                 |   |	         <----| |---->
//  |                 |   |               | |
//  |                 |   |               | |
//  -------------------   -------------------
//
// 	Where the decorated node has a bounding splitter on its right
//  side, allowing dynamic adjustment of its width.


class SECLNSizable : 	public SECLNBorder,
						public SECParentOfNegotiableChildNode,
						public ISECVirtualSplitterObserver
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNSizable();
	TOOLKIT_API virtual ~SECLNSizable();

	// Operations
	TOOLKIT_API virtual BOOL InitSizeBorders(CWnd* pParent,BOOL bRealtimeDrag,DWORD dwSizeBorderFlags=0);
	TOOLKIT_API void SetVirtualSizingBounds(const CRect& rectBounds,BOOL bDoRecalc=TRUE);
	inline CRect GetVirtualSizingBounds() { return m_rcVirtBounds; }
	TOOLKIT_API virtual void ShowSizingSplitters(BOOL bShow,BOOL bRealtimeDrag,BOOL bRecalcRealize);

	// SECLayoutNode overrides
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);

	// SECLNBorder overrides
	TOOLKIT_API virtual SECLayoutNode* GetContainedNode();
	TOOLKIT_API virtual int GetBorderNodeChildCount();

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

	// Object Allocation
	virtual SECLNVirtualSplitter* CreateVirtualSplitter() { return new SECLNVirtualSplitter; }

	// SECLNBorder override
	TOOLKIT_API virtual void NegotiateNewRectWithContainedNode(CRect& rectNew);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	SECLNVirtualSplitter*	m_pVSplitTop,*m_pVSplitBottom,*m_pVSplitLeft,*m_pVSplitRight;
	SECLayoutNode*			m_pContainedNode;
	DWORD					m_dwSizeBorderFlags, m_dwCachedBorderFlagsForHideRestore;
	CWnd*					m_pParentWnd;
	CRect					m_rcVirtBounds;
	BOOL					m_bSelfInitiatedNegotiateRecalc;

	// Implementation Member Functions
	TOOLKIT_API virtual SECLNVirtualSplitter* CreateSplitterIfNeeded(CWnd* pParent,
												SECLNVirtualSplitter* pSplitter,
												BOOL bRealtimeDrag,
												BOOL bHorzOrientation);
	TOOLKIT_API virtual SECLNVirtualSplitter* DestroySplitterIfPresent(SECLNVirtualSplitter* pSplitter);
	TOOLKIT_API virtual void RecalcSplitterPositions(const CRect& rectDesired);
	TOOLKIT_API int GetSplitterCount();
};

/////////////////////////////////////////////////////////////////////////////

#if ( _MFC_VER < 0x0421 )
// reenable warning 4097 for VC4.x:
#pragma warning(default:4097)
#endif 


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SEC_LAYOUT_NODE_SIZABLE_H__
