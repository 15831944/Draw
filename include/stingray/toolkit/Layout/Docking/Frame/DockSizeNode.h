///////////////////////////////////////////////////////////////////////////////
// DockSizeNode.h
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
// Description:  Declaration of SECLNSizableDockBorder class
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SEC_LAYOUT_NODE_DOCK_SIZABLE_BORDER_H__
#define __SEC_LAYOUT_NODE_DOCK_SIZABLE_BORDER_H__

// Header Includes
#include "toolkit\layout\SizeNode.h"
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
// SECLNSizableDockBorder
//
//
// SECLayoutNode + others (see SizeNode.h header)
//		|
// SECLNSizable	ISECDockEventReceiver
//		|			|
//	  SECLNSizableDockBorder
//	

class SECLNSizableDockBorder : 	public SECLNSizable,
								public ISECDockEventReceiver {
								
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNSizableDockBorder();
	TOOLKIT_API virtual ~SECLNSizableDockBorder();

	// Attributes
	//	...Publicly accessible member variables...
	enum DockSide { top, bottom, left, right };

	// Accessors
	//	...Get and Set functions...
	inline void SetDockingSide(DockSide side) { m_DockSide=side; }
	inline DockSide GetDockingSide() { return m_DockSide; }

	// Operations

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// ISECDockEventReceiver implementation
	TOOLKIT_API virtual BOOL OnNotifyDockingEventComplete(SECLayoutNode* pNodeDocked,
							                              SECLayoutNode* pParentBeforeDock,
							                              SECLayoutNode* pParentAfterDock,
							                              SECLayoutNode* pTargetLN,
							                              SECLNMemMgr* pGarbageCollector);

	// SECLNSizable overrides
	TOOLKIT_API virtual void OnNotifySplitterMovement(SECLNVirtualSplitter* pSplitter,
										              int nDeltaX,int nDeltaY);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	DockSide m_DockSide;
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


#endif //__SEC_LAYOUT_NODE_DOCK_SIZABLE_BORDER_H__
