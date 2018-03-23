///////////////////////////////////////////////////////////////////////////////
// NodeIFace.h : Declaration of basic layout manager utility interfaces
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
// Authors:      Mark Isham
// Description:  Declaration of basic basic layout manager utility interfaces
//

#ifndef __SEC_NODE_IFACES_H__
#define __SEC_NODE_IFACES_H__

#ifdef WIN32

// Header Includes
#include "toolkit\layout\Container.h"
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
// ISECParentOfNegotiableChildNode

class ISECParentOfNegotiableChildNode 
{
public:
	inline ISECParentOfNegotiableChildNode() {}

	// A child node will call this function on a parent when that child 
	// has just adjusted to a new size, and is requesting the parent
	// recalc it's layout to accomodate this changed size.
	// If container parm is defined, window will be properly recalc'd to
	// accomodate the change in child size (if applicable). Can be NULL.
	virtual BOOL RecalcOnChildSize(BOOL bWalkParentChain,ISECLNContainer* pContainer=NULL)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECParentOfNegotiableChildNode

// Default implementation of ISECParentOfNegotiableChildNode

class SECParentOfNegotiableChildNode : public ISECParentOfNegotiableChildNode 
{
public:
	TOOLKIT_API virtual BOOL RecalcOnChildSize(BOOL bWalkParentChain,ISECLNContainer* pContainer=NULL);
};

/////////////////////////////////////////////////////////////////////////////
// ISECHideableNode

class ISECHideableNode 
{
public:
	virtual ~ISECHideableNode() {}
	
	// Show/hide with optional ref-counting
	// Ref counting allows original caller to override internal show/hide commands.
	// Set TRUE to override the ref-count and show/hide regardless.
	virtual BOOL ShowNode(BOOL bShow,BOOL bResetRefCount=FALSE,BOOL bRecurse=TRUE)=0;
	virtual BOOL GetNodeVisible()=0;
	
protected:
	// This overridable is called when ref-count has been resolved,
	// and its time for a node to actually change its state
	virtual BOOL OnShowNode(BOOL bShow)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECDefHideableNode

// Default implementation of ISECHideableNode

class SECDefHideableNode : public ISECHideableNode 
{
public:
	TOOLKIT_API SECDefHideableNode();
	TOOLKIT_API virtual BOOL ShowNode(BOOL bShow,BOOL bResetRefCount=FALSE,BOOL bRecurse=TRUE);
	virtual BOOL GetNodeVisible() { return m_bVisible; }
	
protected:
	TOOLKIT_API virtual BOOL OnShowNode(BOOL bShow);
	
protected:
	int m_nShowRefCount;
	BOOL m_bVisible;
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

#endif	//__SEC_NODE_IFACES_H__
