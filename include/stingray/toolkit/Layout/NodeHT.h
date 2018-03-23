///////////////////////////////////////////////////////////////////////////
// NodeHT.h : Declaration of SECLNHitTester
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
// Description:  Declaration of SECLNHitTester
//

//
// SECLNHitTester
// Utility class for layout node HitTesting operations
// 

#ifndef __SEC_LN_HITTEST_H__
#define __SEC_LN_HITTEST_H__

// Header Includes
#include <math.h>
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
// SECLNHitTester

class SECLNHitTester 
{
public:
	TOOLKIT_API SECLNHitTester();
	TOOLKIT_API virtual ~SECLNHitTester();

	TOOLKIT_API static SECLayoutNode* HitTestNodeChildren(SECLayoutNode* pParent,
						const CPoint& ptClientTest,BOOL bRecurse=FALSE);	

	TOOLKIT_API static SECLayoutNode* FindClosestChildNode(SECLayoutNode* pParent,
											const CPoint& ptClientTest,
											CPoint& ptClientChildNodeClosest,
											BOOL& bDirectHit);
	TOOLKIT_API static BOOL IsChildNode(SECLayoutNode* pParent,SECLayoutNode* pChild);
protected:
	TOOLKIT_API static double GetDistanceBetweenPoints(const CPoint& pt1,const CPoint& pt2);
	TOOLKIT_API static CPoint GetClosestRectPoint(const CRect& rect,const CPoint& ptTest);			
};	

/////////////////////////////////////////////////////////////////////////////
// ISECOffNodeHitTest

// Mixin interface to facilitate hit-testing of nodes when mouse point
// is within a certain threshold (but still outside) of a particular node.
// Client returns TRUE if it accepts the point as a hit.

class ISECOffNodeHitTest 
{
public:
	virtual ~ISECOffNodeHitTest() {}

	virtual BOOL AcceptOffNodeHit(const CPoint& ptNodeTest)=0;
};


/////////////////////////////////////////////////////////////////////////////
// SECLNOffNodeIFaceHitTest_T

// Worker class to recursively parse a tree of nodes (breadth first traversal),
// returning the first node that supports ISECOffNodeHitTest, accepts
// an off-node hit, and supports the templatized interface passed in.

template <class IFACETEST>
class SECLNOffNodeIFaceHitTest_T 
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Initialization/Destruction
	inline SECLNOffNodeIFaceHitTest_T() {}
	virtual ~SECLNOffNodeIFaceHitTest_T() {}

	virtual IFACETEST* GetOffNodeHit(SECLayoutNode* pNodeTest,const CPoint& ptNodeTest);

protected:
	virtual IFACETEST* GetOffNodeHitRecurse(SECLayoutNode* pNodeTest,const CPoint& ptNodeTest);
	virtual IFACETEST* TestOffNodeHit(SECLayoutNode* pNodeTest,const CPoint& ptNodeTest);
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


#endif //__SEC_LN_HITTEST_H__
