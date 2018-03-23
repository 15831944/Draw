///////////////////////////////////////////////////////////////////////////////
// DockInfo.h
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
// Description:  Declaration of docking utility information classes
//

#ifndef __SEC_DOCKING_INFO_H__
#define __SEC_DOCKING_INFO_H__

// Header Includes
#include "Toolkit\Layout\DynGrid.h"
#include "Toolkit\Layout\Docking\Frame\FrameDockBase.h"
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

class ISECBorderTargetParent;

/////////////////////////////////////////////////////////////////////////////
// SECDockInProgressInfo

// An object of this type is used to encapsulate common data used during
// the lifetime of 1 specific docking event.

class SECDockInProgressInfo 
{
public:
	TOOLKIT_API SECDockInProgressInfo();
	TOOLKIT_API virtual ~SECDockInProgressInfo();
	TOOLKIT_API virtual void Reset();
	
	// Suggested docking rect, optionally configured
	TOOLKIT_API void SetDockingRect(const CRect& rcScreenDock);
	TOOLKIT_API void ClearDockingRect();
	TOOLKIT_API BOOL GetDockingRect(CRect& rcScreenDock) const;

	// Offset from the docking initiator origin for prediction insertion drawing
	CSize m_szOriginPredictOffset;
	// Original node rectangle (in screen coordinates) at the start of the drag
	CRect m_rcScreenNodeBeforeDrag;
	// Are we dragging a node horizontally?
	BOOL m_bNodeHorzBeforeDrag;	

protected:	
	BOOL m_bUseDockingRect;
	CRect m_rcScreenDocking;	
};

/////////////////////////////////////////////////////////////////////////////
// SECDockInsertionContraints

// An object of this type is used to facilitate easy insertion of a new
// dockable node into a 2d dynamic gridline docking target option.

//@doc SECCurrencyEdit
//@mfunc SECFrameDockingFeatureBase::DockSite  | SECCurrencyEdit | HasSel | Returns nonzero if the control
// currently has selected text.
//@xref <c SECCurrencyEdit>

//@doc SECDockInsertionConstraints
//@mfunc SECFrameDockingFeatureBase::DockSite | SECDockInsertionConstraints | GetDockSite | 
// Gets the docksite used for next insertion.
//@xref <c SECDockInsertionConstraints> 
//@xref <mf SECFrameDockingFeatureBase::SetDockSite> <mf SECFrameDockingFeature::DockNode>

//@doc SECDockInsertionConstraints 
//@class Advanced docking insertion constraint parameters
//@comm An object of this type can be used to facilitate advanced
// docking insertions with relative ease. In addition, this object
// can be reused for subsequent DockNode operations for multiple
// dock operations with like configurations.
//@BASE public | SECDynGridInsertConstraints
//@xref <c SECFrameDockingFeature>
//@xref <c SECFrameDockingFeatureBase>
//@xref <mf SECFrameDockingFeature::DockNode>
//@xref <mf SECFrameDockingFeatureBase::DockNode>
//@xref <c SECDynGridInsertConstraints>
class SECDockInsertionConstraints : public SECDynGridInsertConstraints 
{
public:
	TOOLKIT_API SECDockInsertionConstraints();

	//@access Operations

	//@cmember
	/* Copy insertion constraints from a different insertion constraint object. */
	TOOLKIT_API virtual void CopyFromEx(const SECDockInsertionConstraints& Src);

	//@cmember
	/* Reset constraints to acceptable defaults. */
	TOOLKIT_API virtual void Reset();

	//@access Accessors
	//@cmember
	/* Preset the dock site id used for next insertion. */
	TOOLKIT_API void SetDockSite(DWORD dwDockSite);

	//@cmember
	/* Preset the dock site used for next insertion */
	inline void SetDockSite(SECFrameDockingFeatureBase::DockSite site) { m_DockSite=site; }

	//@cmember
	/* Get the dock site configured for next insertion */
	inline SECFrameDockingFeatureBase::DockSite GetDockSite() const { return m_DockSite; }
	
protected:
	SECFrameDockingFeatureBase::DockSite m_DockSite;
};

/////////////////////////////////////////////////////////////////////////////
// SECDockingNodeConstraints

// Administrated by the docking manager, a SECDockingNodeConstraints object 
// contains information unique to 1 specific dockable node and will survive 
// throughout the lifetime of that dockable node. 1 docking node constraint
// object is mapped to each dockable node that participates in the
// docking framework.

class SECDockingNodeConstraints 
{
public:
	TOOLKIT_API SECDockingNodeConstraints();
	TOOLKIT_API virtual ~SECDockingNodeConstraints();
	TOOLKIT_API virtual void LoadFromInsertCnstr(const SECDockInsertionConstraints& InsertConstraints);

	// Floating MRU rectangle	
	TOOLKIT_API void SetMRUFloatRect(const CRect& rcScreenMRU);
	TOOLKIT_API void ClearMRUFloatRect();
	TOOLKIT_API BOOL GetMRUFloatRect(CRect& rcScreenMRU);

	// Docked MRU constraints
	TOOLKIT_API void SetMRUDockCnstr(const SECDockInsertionConstraints& DockCnstr);
	TOOLKIT_API void SetMRUDockCnstr(SECLayoutNode* pNode);
	TOOLKIT_API void ClearMRUDockCnstr();
	TOOLKIT_API BOOL GetMRUDockCnstr(SECDockInsertionConstraints& DockCnstr);

	// Border Client awareness (optional)
	inline ISECBorderTargetParent* GetBorderTargetParent() { return m_pBorderTargetParent; }
	inline void SetBorderTargetParent(ISECBorderTargetParent* pBTP) { m_pBorderTargetParent=pBTP; }

	BOOL m_bSizableWhenDocked;	
	// Floating Caption Behavior
	BOOL m_bHideOnClose;	// defaults to TRUE
	BOOL m_bCloseEnabled;	// defaults to TRUE

protected:	
	BOOL						m_bFloatMRUEnabled,m_bDockMRUEnabled;
	CRect						m_rcScreenFloatMRU;
	SECDockInsertionConstraints	m_DockCnstrMRU;
	ISECBorderTargetParent*		m_pBorderTargetParent;
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


#endif //__SEC_DOCKING_INFO_H__
