///////////////////////////////////////////////////////////////////////////////
// Border.h
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
// Description:  Declaration of SECLNBorder class
//
// SECLNBorder
// This simple layout algorithm allows construction of a border
// around 1 (and only 1) child layout node.
// 

#ifndef __SECLAYOUT_BORDER_H__
#define __SECLAYOUT_BORDER_H__

// Header Includes

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
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
// SECLNBorder_T

//
// Base class must be derived from SECLayoutNode!
//

template <class Base>
class SECLNBorder_T : public Base
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	inline SECLNBorder_T() 
	{ 
		m_nBorderLeft=m_nBorderRight=m_nBorderTop=m_nBorderBottom=0; 
		m_nPendingDeltaTop=m_nPendingDeltaBottom=m_nPendingDeltaLeft=m_nPendingDeltaRight=0;		
	}
	virtual ~SECLNBorder_T() {}

	// Operations
	TOOLKIT_API void ClearBorderMargins();
	TOOLKIT_API void SetBorderMargins(UINT nAll);
	TOOLKIT_API void SetBorderMargins(UINT nLeftRight,UINT nTopBottom);

	// These 2 functions must be inlined for proper template expansion
	inline void SetBorderMargins(UINT nLeft,UINT nTop,UINT nRight,UINT nBottom) 
	{
		m_nBorderLeft=nLeft; m_nBorderTop=nTop;
		m_nBorderRight=nRight; m_nBorderBottom=nBottom;
	}
	inline void GetBorderMargins(UINT& nLeft,UINT& nTop,UINT& nRight,UINT& nBottom) 
	{
		nLeft=m_nBorderLeft; nTop=m_nBorderTop;
		nRight=m_nBorderRight; nBottom=m_nBorderBottom;
	}
	
	// Fetch the contained node upon which this border surrounds.
	TOOLKIT_API virtual SECLayoutNode* GetContainedNode();

	// Query the current node child count
	TOOLKIT_API virtual int GetBorderNodeChildCount();

	// Overrides
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual void SetPreferredRect(const CRect& rectPreferred);
	TOOLKIT_API virtual void GetPreferredRect(CRect& rectPreferred);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,
								 BOOL bChildNegotiate,BOOL bStrictRecalc);
	TOOLKIT_API virtual void OnRecalcChild(SECLayoutNode* pChild,const CRect& rcChild);								 

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Functions
	TOOLKIT_API virtual void ResetBorderMinMaxSize();
	TOOLKIT_API virtual void AdjustNewRectWithPendingDeltas(CRect& rectNew);
	TOOLKIT_API virtual void NegotiateNewRectWithContainedNode(CRect& rectNew);

	// Implementation Member Variables
	UINT m_nBorderLeft,m_nBorderRight,m_nBorderTop,m_nBorderBottom;
	BOOL m_bHorizontal;
	CRect m_rectDrawLeft,m_rectDrawTop,m_rectDrawBottom,m_rectDrawRight;
	int m_nPendingDeltaTop,m_nPendingDeltaBottom,m_nPendingDeltaLeft,m_nPendingDeltaRight;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNBorder

typedef SECLNBorder_T<SECLayoutNode> SECLNBorder;

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SECLAYOUT_BORDER_H__
