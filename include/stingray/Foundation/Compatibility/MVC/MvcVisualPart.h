///////////////////////////////////////////////////////////////////////////////
// MvcVisualPart.h : Declaration of MvcVisualPart
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
// Author:       Dean Hallman
// Description:  Declaration of MvcVisualPart interface.
//

// @doc MvcVisualPart

#ifndef __COMPAT_MVCVISUALPART_H__
#define __COMPAT_MVCVISUALPART_H__

// Includes

//#include "..\Patterns\Collect.h"


#ifndef __COMPAT_MVCVISUALCOMPONENT_H__
#include "Foundation\Compatibility\MVC\MvcVisualComponent.h"
#endif

//#include <StingrayExportDefs.h>

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _MVCDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    MVC_DATAEXT
#endif //_MVCDLL

///////////////////////////////////////////////////////////////////////////
//
//  MvcVisualPart
//
//@doc MvcVisualPart
//@mdata MvcVisualPart* | MvcVisualPart | m_pContainer | Pointer to the visual part that contains this visual part
//@xref <c MvcVisualPart>

//@class
// An MvcVisualPart is a type of visual component that keeps track of
// its container. Knowledge of its parent allows a visual part to perform 
// invalidation and establish its own size based on the size of its container.
//
// Because of its extra member variables, a visual part 
// is a slightly heavier object than the MvcVisualComponent class.  
// If you require many instantiations of a display
// object, you should probably derive each from MvcVisualComponent and the
// container from MvcVisualPart, MvcLogicalPart or MvcViewport.
//
//@base public | MvcVisualComponent
//

class FOUNDATION_API MvcVisualPart : public MvcVisualComponent
{
// Constructor(s) & destructor
public:
	MvcVisualPart(MvcVisualPart* pContainer = NULL);
	virtual ~MvcVisualPart();

	//@cmember
	/* Create a visual part as a child of the specified container*/
	virtual BOOL Create(MvcVisualPart* pContainer = NULL);

// Attributes
protected:

	//@cmember
	/* Pointer to the visual part that contains this visual part*/
	MvcVisualPart* m_pContainer;

// Accessors
public:

	//@cmember
	/* Retrieve the container of this visual part*/
	MvcVisualPart* GetContainer();

	//@cmember
	/* Set the container of this visual part*/
	virtual void SetContainer(MvcVisualPart* pContainer);

// Operations
public:

	// Invalidation

	//@cmember
	/* Invalidate the entire visual part*/
	virtual void Invalidate(BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

	//@cmember
	/* Invalidate the specified component's entire rectangle*/
	virtual void InvalidateVisual(MvcVisualComponent* pVC, BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

	//@cmember
	/* Invalidate the specified rectangle within this visual part*/
	virtual void InvalidateRect(const CRect& rcLog, BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

// Overridables
public:

	//@cmember
	/* An overridable for adding additional creation or initialization logic.*/
	virtual BOOL OnCreate();
};

///////////////////////////////////////////////////////////////////////////

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // __COMPAT_MVCVISUALPART_H__

