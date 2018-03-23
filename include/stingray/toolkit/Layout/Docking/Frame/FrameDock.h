///////////////////////////////////////////////////////////////////////////////
// FrameDock.h
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
// Description:  Declaration of SECFrameDockingFeature 
//

#ifndef __SEC_FRAME_DOCKING_FEATURE_H__
#define __SEC_FRAME_DOCKING_FEATURE_H__

#ifdef WIN32

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

// Constants

// Macros

// Types

//@doc SECSetBorderSizingParms
//@mdata BOOL | SECSetBorderSizingParms | m_bSplitter | Specifies whether a sizing
// splitter is provided on the inside edge of the border.  Set by default to TRUE.
//@xref <c SECSetBorderSizingParms>

//@doc SECSetBorderSizingParms
//@mdata BOOL | SECSetBorderSizingParms | m_bSizeOnDock | Specified whether the 
// border can increase or decrease in size during a dock/undock operation.  If FALSE, 
// the border size remains fixed. Set by default to TRUE.
//@xref <c SECSetBorderSizingParms>

//@doc SECSetBorderSizingParms
//@mdata BOOL | SECSetBorderSizingParms | m_bRealtimeDrag | Specifies whether 
// border splitter tracking will be performed in realtime.  If FALSE, a prediction 
// tracker is used. Set by default to TRUE.
//@xref <c SECSetBorderSizingParms>

//@doc SECSetBorderSizingParms
//@mfunc  | SECSetBorderSizingParms | SECSetBorderSizingParms | SECSetBorderSizingParms contstructor
//@syntax SECSetBorderSizingParms()
//@syntax SECSetBorderSizingParms(BOOL bSplitter,BOOL bSizeOnDock,BOOL bRealtimeDrag)
//@parm BOOL | bSplitter | If TRUE, provide a sizing splitter on inside edge of border. (Empty constructor defaults to TRUE).
//@parm BOOL | bSizeOnDock | If TRUE, border can increase or decrease size on dock/undock. If FALSE, border will stay fixed. (Empty constructor defaults to TRUE).
//@parm BOOL | bRealtimeDrag | If TRUE, border splitter tracking will be performed in realtime. If FALSE, prediction tracker is used. (Empty constructor defaults to TRUE).
//@xref <c SECSetBorderSizingParms> <mf SECFrameDockingFeature::SetBorderSizing>

//@doc SECSetBorderSizingParms
//@class Border sizing parameters for use by SECFrameDockingFeature::SetBorderSizing
//@comm
// This class is provided to simplify the parameter passing to SECFrameDockingFeature::SetBorderSizing
// as well as serve as a placeholder for future parameter additions.
//@xref <mf SECFrameDockingFeature::SetBorderSizing>
class SECSetBorderSizingParms 
{
public:
	//@access Construction

	//@cmember Constructor
	inline SECSetBorderSizingParms() { m_bSplitter=m_bSizeOnDock=m_bRealtimeDrag=TRUE; }

	//@cmember Constructor
	inline SECSetBorderSizingParms(BOOL bSplitter,BOOL bSizeOnDock,BOOL bRealtimeDrag) 
		{
			m_bSplitter=bSplitter;
			m_bSizeOnDock=bSizeOnDock;
			m_bRealtimeDrag=bRealtimeDrag; 
		}

	//@access Public Member Variables

	//@cmember If TRUE, provide a sizing splitter on inside edge of border. Defaults to TRUE
	BOOL m_bSplitter;

	//@cmember If TRUE, border can increase or decrease size on dock/undock. If FALSE, border will stay fixed. Defaults to TRUE
	BOOL m_bSizeOnDock;

	//@cmember If TRUE, border splitter tracking will be performed in realtime. If FALSE, prediction tracker is used. Defaults to TRUE
	BOOL m_bRealtimeDrag;
};

// Forward Declarations

/////////////////////////////////////////////////////////////////////////////
// SECFrameDockingFeature

//
// Derived from SECFrameDockingFeatureBase, the 
// SECFrameDockingFeature class adds support for 
// SECDynGridLineTarget border target nodes.
// 

//@doc SECFrameDockingFeature
//@class Advanced docking frame window feature 
//@comm Derived from SECFrameDockingFeatureBase, this class provides
// a concreate implementation of the frame window advanced docking
// feature that supports docking to border nodes preconfigured
// with a dynamic, 2 dimensional "grid" target. Typically an instance
// of this class is instantiated in top level frame or MDI child frame
// and EnableDocking is called in response to WM_CREATE.
//@BASE public | SECFrameDockingFeatureBase
//@xref <c SECFrameDockingFeatureBase>
//@xref <mf SECFrameDockingFeatureBase::EnableDocking>
class SECFrameDockingFeature : public SECFrameDockingFeatureBase 
{
public:
	TOOLKIT_API SECFrameDockingFeature();
	TOOLKIT_API virtual ~SECFrameDockingFeature();

	// Operations

	// Overrides
	TOOLKIT_API virtual BOOL DockNode(SECLayoutNode* pNode);

	// New Operations

	//@access Operations

	//@cmember
	/* Dock a dockable layout node to the associated frame window using the constraints passed in. */
	TOOLKIT_API virtual int DockNode(SECLayoutNode* pNode,SECDockInsertionConstraints& Cnstr);

	//@cmember
	/* Dock a dockable layout node to the associated frame window using the configuration passed in. */
	TOOLKIT_API virtual BOOL DockNode(SECLayoutNode* pNode,DWORD dwDockSite,int nSize=-1,BOOL bNewLine=FALSE);

	//@access Configuration

	//@cmember
	/* Set the border sizing configuration for all 4 borders */
	TOOLKIT_API virtual BOOL SetBorderSizing(const SECSetBorderSizingParms& SizingParms,
									BOOL bRecalcRealize=FALSE);

	//@cmember
	/* Set the border sizing configuration for a specific border */
	TOOLKIT_API virtual BOOL SetBorderSizing(DockSite site,const SECSetBorderSizingParms& SizingParms,
									BOOL bRecalcRealize=FALSE);

	//@cmember
	/* Set the border sizing configuration for a specific border */
	TOOLKIT_API virtual BOOL SetBorderSizing(DWORD dwDockSite,const SECSetBorderSizingParms& SizingParms,
									BOOL bRecalcRealize=FALSE);

	// Accessors
	TOOLKIT_API virtual void GetBorderClientEdges(SECLNBorderClientEdge** ppTop,
								SECLNBorderClientEdge** ppBottom,
								SECLNBorderClientEdge** ppLeft,
								SECLNBorderClientEdge** ppRight);

protected:
	// Overrides
	TOOLKIT_API virtual SECLayoutNode* CreateDockingTarget(SECLayoutNode* pParent,
							DockSite site,CWnd* pParentWnd);
	TOOLKIT_API virtual SECLNBorderClient* CreateBorderClientNode();
	TOOLKIT_API virtual LRESULT OnNotifyPostOnSizeParent();

	// Implementation Member Variables
	SECDockInsertionConstraints m_DefDockCnstr;
};

/////////////////////////////////////////////////////////////////////////////
// ISECBorderTargetParent

// Mixin interface for SECLNBorderClient derived class that supports
// querying a specific border child target

class ISECBorderTargetParent 
{
public:
	virtual ~ISECBorderTargetParent() {}
	TOOLKIT_API virtual ISECDockTarget* LocateBorderTarget(SECLNBorderClient::BorderPosition pos)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDockBorderClient

// Extension of SECLNBorderClient that makes specific assumptions about
// the environment established by SECFrameDockingFeature.
// This class is not designed to be used in any other environment.

class SECLNDockBorderClient : public SECLNBorderClient,
							  public ISECBorderTargetParent 
{
public:
	TOOLKIT_API SECLNDockBorderClient();
	inline void SetFrameDockBackPtr(SECFrameDockingFeature* pFrameDockFeat) 
									{ m_pFrameDockFeat=pFrameDockFeat; }

	// ISECBorderTargetParent implementation
	TOOLKIT_API virtual ISECDockTarget* LocateBorderTarget(BorderPosition pos);

protected:
	// Overrides
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);

	// Implementation Member Functions
	TOOLKIT_API virtual void UpdateVisibilityAllEdges();
	TOOLKIT_API virtual int GetContainedTargetDockNodeCount(SECLNBorderClientEdge* pBorderEdge);
	TOOLKIT_API virtual void QueryLeftRightBordersNeeded(BOOL& bLeftBorder,BOOL& bRightBorder);

	// Implementation Member Variables
	SECFrameDockingFeature* m_pFrameDockFeat;
	int m_nOffClientThreshold;
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

#endif	// WIN32

#endif  //__SEC_FRAME_DOCKING_FEATURE_H__
