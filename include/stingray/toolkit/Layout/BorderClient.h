///////////////////////////////////////////////////////////////////////////////
// BorderClient.h : Declaration of SECLNBorderClient
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
// Description:  Declaration of SECLNBorderClient class
//
// Unlike SECLNBorder, SECLNBorderClient is designed to contain 
// up to 5 layout node children, configured in one of the following
// configurations:
//
// Top-Bottom, Left-Right:		Left-Right, Top-Bottom:
// -------------				-------------
// |     T     |				|   | T |   |
// |-----------|				|   |---|   |
// | L | C | R |				| L | C | R |
// |-----------|				|   |---|   |
// |     B     |				|   | B |   |
// -------------				-------------
//
// Upon resize, this algorithm will attempt to preserve the existing
// sizes (although not positions) of L,R,T,B, at the expense of
// the client area. If a min/max size is reached on the client, though,
// the the L,T,R,B nodes are shrinked/grown as needed, while accounting
// for their min/max sizes as well. If no accomodation can be made,
// then clipping will result.

#ifndef __SECLAYOUT_BORDER_CLIENT_H__
#define __SECLAYOUT_BORDER_CLIENT_H__

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
// ISECLNBorderClientEventRcvr

// Mixin interface to receive event notifications from the border client layout

class TOOLKIT_API ISECLNBorderClientEventRcvr 
{
public:
	virtual ~ISECLNBorderClientEventRcvr() {}

protected:
	virtual void OnClientRectChanged(const CRect& rcNewClient)=0;

	friend class SECLNBorderClient;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNBorderClient

class SECLNBorderClient : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNBorderClient();
	TOOLKIT_API virtual ~SECLNBorderClient();

	// Attributes
	//	...Publicly accessible member variables...
	enum BorderAlgorithm {
		TopBottomLeftRight,			// top/bottom get priority, then left/right
		LeftRightTopBottom			// left/right get priority, then top/bottom
		};
	enum BorderPosition { Top, Bottom, Left, Right, Client };

	// Accessors
	//	...Get and Set functions...
	inline void SetBorderAlgorithm(BorderAlgorithm alg)	{ m_BorderAlg=alg; }
	inline BorderAlgorithm GetBorderAlgorithm()	{ return m_BorderAlg; }
	inline void SetEventRecvr(ISECLNBorderClientEventRcvr* pEventRcvr) { m_pEventRcvr=pEventRcvr; }
	inline ISECLNBorderClientEventRcvr* GetEventRcvr() { return m_pEventRcvr; }
	TOOLKIT_API virtual BOOL LocatePositionFromNode(SECLayoutNode* pNode,BorderPosition& position);
	TOOLKIT_API virtual SECLayoutNode* LocateNodeFromPosition(BorderPosition position);

	// Operations
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode,BorderPosition position);

	// Overrides
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// SECLayoutNode override
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,
								 BOOL bChildNegotiate,BOOL bStrictRecalc);

	// Border calculation
	TOOLKIT_API virtual CRect RecalcBorderRects(const CRect& rectParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	SECLayoutNode* m_pNodeTop,*m_pNodeBottom,*m_pNodeLeft,*m_pNodeRight;
	SECLayoutNode* m_pNodeClient;
	BorderAlgorithm	m_BorderAlg;
	ISECLNBorderClientEventRcvr* m_pEventRcvr;

	// Implementation Member Functions

	// Insertion/Removal Logic
	TOOLKIT_API virtual BOOL GetAutoInsertPosition(BorderPosition& position);
	TOOLKIT_API virtual BOOL AddBorderNode(SECLayoutNode* pNode,BorderPosition position);
	TOOLKIT_API virtual BOOL RemoveBorderNode(SECLayoutNode* pNode);

	// Layout Calculation Logic
	TOOLKIT_API virtual CRect RecalcBorderRectsTBLR(const CRect& rectParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual CRect RecalcBorderRectsLRTB(const CRect& rectParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);

	TOOLKIT_API virtual BOOL SetClientRectWithinMinMax(
								const CRect& rectParent,CRect& rcClient,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual void AdjustClientRectOneDimension(
								SECLayoutNode* pBorderBefore,
								SECLayoutNode* pBorderAfter,
								const CRect& rectParent,
								CRect& rcClient,int nDelta,
								BOOL bHorzAdjust);
	TOOLKIT_API virtual void BoundClientInsideParent(CRect& rcClient,
								const CRect& rectParent);
	TOOLKIT_API virtual void ResetNodeRectsAroundClient(const CRect& rcClient,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual BOOL NegotiatePreferredChildNodeRects(const CRect& rcParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual BOOL NegotiatePreferredChildNodeRectsTBLR(const CRect& rcParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual BOOL NegotiatePreferredChildNodeRectsLRTB(const CRect& rcParent,
								CRect& rcTop,CRect& rcBottom,
								CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual void ApplyChildNodeRects(const CRect& rcClient,
								const CRect& rcTop,
								const CRect& rcBottom,
								const CRect& rcLeft,
								const CRect& rcRight);

	// Utility Functions
	TOOLKIT_API virtual float NormalizeBorderSizeIfTooLarge(int nFitSize,int nSize1,int nSize2);
	TOOLKIT_API virtual CRect CalcClientRect(CRect rcTop,CRect rcBottom,CRect rcLeft,CRect rcRight);
	TOOLKIT_API virtual void GetBorderRects(CRect& rcTop,CRect& rcBottom,CRect& rcLeft,CRect& rcRight);
	TOOLKIT_API virtual void GetAdjustedBorderRect(SECLayoutNode* pNode,CRect& rcNode);

	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//


	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:

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

#endif //__SECLAYOUT_BORDER_CLIENT_H__
