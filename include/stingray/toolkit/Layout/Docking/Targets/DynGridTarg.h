///////////////////////////////////////////////////////////////////////////////
// DynGridTarg.h
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
// Description:  Declaration of dynamic grid docking target classes
//

#ifndef __SECLAYOUT_DOCK_DYNGRID_TARG_H__
#define __SECLAYOUT_DOCK_DYNGRID_TARG_H__

// Header Includes
#include "toolkit\Layout\DynGrid2d.h"
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

// Forward Declarations
class SECDefDockTargetBase;

/////////////////////////////////////////////////////////////////////////////
// SECDynGridLineTarget

//
// SECLayoutNode		ISECOffNodeHitTest	
//		|					|	
//	SECLNDynamicGridLine	|		ISECDockTarget
//			|				|		|
//		SECLNDynamicGrid2d	|	SECDefDockTargetBast
//				|			|	|
//				SECDynGridLineTarget
//

class SECDynGridLineTarget : public SECLNDynamicGrid2d, 
				             public SECDefDockTargetBase,
				             public ISECOffNodeHitTest
{
public:	
	TOOLKIT_API SECDynGridLineTarget();
	virtual ~SECDynGridLineTarget() {}
	
	// Get/Set the new line threshold values
	TOOLKIT_API void SetNewLineThreshold(float fPctLineWithin,UINT nThresholdOutside);
	TOOLKIT_API void GetNewLineThreshold(float &fPctLineWithin,UINT &nThresholdOutside);

	// Implementation of ISECOffNodeHitTest
	TOOLKIT_API virtual BOOL AcceptOffNodeHit(const CPoint& ptNodeTest);

	// SECLayoutNode overrides	
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNodeToAdd,
							              SECDynGridInsertConstraints& InsertConstraint);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNodeToRemove);	

	inline void SetFrameDockSite(SECFrameDockingFeatureBase::DockSite site) { m_dockSite=site; }
	TOOLKIT_API virtual BOOL CalcChildDockConstraints(SECLayoutNode* pChild,
				                                      SECDockInsertionConstraints& cnstr);

	// static members
	TOOLKIT_API static void SetUsePreferredValues(BOOL bUse);
	TOOLKIT_API static void SetPreferredDockHeight(DWORD dwHeight);
	TOOLKIT_API static void SetPreferredDockWidth(DWORD dwWidth);

    TOOLKIT_API static BOOL GetUsePreferredValues();
	TOOLKIT_API static DWORD GetPreferredDockHeight();
	TOOLKIT_API static DWORD GetPreferredDockWidth();


protected:
	// SECDefDockTargetBase overrides
	TOOLKIT_API virtual BOOL InsertDockingNode(SECLayoutNode* pNodeInsert,
		                                       const CPoint& ptNodeInsert,
											   const CPoint& ptScreenInsert,
											   BOOL bTrueDock,SECLNDockingMgr* pDockMgr,
											   const SECDockInProgressInfo& DockingInfo);

	TOOLKIT_API virtual BOOL RestoreStateFromBeforePrediction(SECLayoutNode* pNode);

	// Implementation Functions	
	TOOLKIT_API virtual BOOL QueryInsertNewLine(const CPoint& ptNodeInsert,
									SECDynGridInsertConstraints& Constraints);
	TOOLKIT_API virtual BOOL TestPointWithinThreshold(SECLayoutNode* pNodeTest,
									const CPoint& ptNodeTest,
									SECDynGridInsertConstraints& Constraints,
									BOOL bPointWithinNode);
	
	// Implementation Variables
	UINT			      m_nNewLineThresholdOutside;
	float			      m_fPctNewLineThresholdWithin;
	SECLayoutNode*	m_pLastInsertionChild;
	BOOL			      m_bRestoreNonStretchModeOnFirstAdd;
	int				      m_nRestoreNonStretchSize;
	stingray::foundation::SECRect		     m_rcBeforePrediction;
	SECFrameDockingFeatureBase::DockSite m_dockSite;

	TOOLKIT_API static BOOL		m_bUsePrefValues;
	TOOLKIT_API static DWORD	m_dwPrefHeight;
	TOOLKIT_API static DWORD	m_dwPrefWidth;
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


#endif //__SECLAYOUT_DOCK_DYNGRID_TARG_H__
