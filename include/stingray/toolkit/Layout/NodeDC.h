///////////////////////////////////////////////////////////////////////////////
// NodeDC.h : Declaration of SECLayoutNodeDC
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
// Description:  Declaration of SECLayoutNodeDC
//
// SECLayoutNodeDC class (see also SECLayoutNode base class)
// This derivation of SECLayoutNode provides the implementation
// for DC drawing in the layout node tree.
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SECLAYOUTNODEDC_H__
#define __SECLAYOUTNODEDC_H__

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
// SECLayoutNodeDCBase

//@doc SECLayoutNodeDCBase
//@class Layout node that supports layout of Device-Context based rendered images.
//@comm
// This class is provided as a mechanism to layout nodes based on DC drawing
// (for example MVC ViewPorts), rather than tied to a specific HWND
//@BASE public | SECLayoutNode
class SECLayoutNodeDCBase : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	inline SECLayoutNodeDCBase() {
		m_hWndOwner=NULL;
	}
	virtual ~SECLayoutNodeDCBase() {}

	// Attributes
	virtual int GetDeferWindowCount() { return 1; }	// insure a realize call
	virtual BOOL IsNodeAttached() { return (BOOL)(SEC_INT)(m_hWndOwner); }

	//@access Accessors

	//@cmember
	/* Set the HWND owner of this DC-based node */
	virtual void SetNodeOwnerHWND(HWND hWndOwner) { m_hWndOwner=hWndOwner; }

	//@cmember
	/* Get the HWND owner of this DC-based node */
	inline HWND GetNodeOwnerHWND() 		 	  { return m_hWndOwner; }

	// Operations
	TOOLKIT_API virtual BOOL RealizeNodeHelper(HDWP* phDWP,HDC hDC);	
	TOOLKIT_API virtual void EraseNodeBkgnd(BOOL bRecurse=TRUE,HDC hDC=NULL);
	TOOLKIT_API virtual void PaintNode(BOOL bRecurse=TRUE,HDC hDC=NULL);

	TOOLKIT_API static BOOL CalcInvalidateRects(const CRect& rcOld,const CRect& rcNew,
						                        CRect& rcEraseTop,CRect& rcEraseBottom,
						                        CRect& rcEraseLeft,CRect& rcEraseRight);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	//@access Overridables

	//@cmember
	/* Override to provide the appropriate rendered image in the provided rectangle */
	TOOLKIT_API virtual void OnDrawNode(HDC hDC,const CRect& rcNodeDraw);

	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rectInvalid,BOOL bDoErase);	

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	HWND m_hWndOwner;
};

/////////////////////////////////////////////////////////////////////////////
// SECLayoutNodeDC

// Logical extension of SECLayoutNodeDCBase to provide hideable node support.
// This functionality is not automatically built into the SECLayoutNodeDCBase
// base due to an architectural necessity in the advanced docking extensions
// to break out the ISECHideableNode interface support (necessary to avoid
// interface duplicity in some of the templatized base class implementations).
// The base implementation is an internal implementation detail, though,
// and use of the SECLayoutNodeDC derived class should be safe for 
// external usage.

class SECLayoutNodeDC : public SECLayoutNodeDCBase,
					  	public SECDefHideableNode 
{
protected:						  
	// SECLayoutNodeDCBase override
	TOOLKIT_API virtual void PaintNode(BOOL bRecurse=TRUE,HDC hDC=NULL);

	// SECDefHideableNode override
	TOOLKIT_API virtual BOOL OnShowNode(BOOL bShow);							  
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


#endif //__SECLAYOUTNODEDC_H__
