/////////////////////////////////////////////////////////////////////////////
// SOleDock.h : Declaration of SECOleServerItem, 
//				SECOleServerDoc, SECOleCntrFrameWnd
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
// Description:  Declaration of SECOleServerItem, SECDocObjectServerItem,
//				 SECOleServerDoc, SECOleCntrFrameWnd, SECFriendOleIPFrameWnd
//
// These classes provide the necessary support to allow the Objective
// Toolkit extended docking window architecture to be used in conjunction
// with an OLE inplace activation. Much of this code is pasted
// as-is from the MFC 4.21 base classes to provide the needed 
// functional overrides of nonvirtual members. This grants the ability
// to override MFC nonvirtual members, but vigilance must be maintained
// to insure the latest functional compatibility with the latest MFC
// releases.
// - MTI 11/29/97

#ifndef __SECOLEDOCK_H__
#define __SECOLEDOCK_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

// SECOleIPFrame support only on VC 4.2 and above
#if _MFC_VER >=0x420

// Header Includes

// For SECFrameWnd
#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
#endif

// For CDocObjectServerItem
#ifndef __AFXDOCOB_H__
#include <afxdocob.h>
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

// Constants

// Macros

// Types

// Forward Declarations

// SEC equiv. of Afx functions to properly resolve compile linkage (MFC 4.21)
#define SEC_QUERYINTERFACE(lpUnknown, iface) \
	(iface*)_SecAfxQueryInterface(lpUnknown, IID_##iface)
LPUNKNOWN AFXAPI _SecAfxQueryInterface(LPUNKNOWN lpUnknown, REFIID iid);

TOOLKIT_API DWORD AFXAPI _SecAfxRelease(LPUNKNOWN* lplpUnknown);

#ifndef _DEBUG
#define SEC_RELEASE(lpUnk) _SecAfxRelease((LPUNKNOWN*)&lpUnk)
#else	
#define SEC_RELEASE(lpUnk) RELEASE(lpUnk)
#endif

/////////////////////////////////////////////////////////////////////////////
// SECOleServerItem

//@doc SECOleServerItem 
//@class COleServerItem derived class to provide support for OT docking windows inside an OLE IP Server
//@BASE public | COleServerItem 
//@comm
// Use this class in place of an existing COleServerItem base class to 
// provide native support for OT docking windows with an OLE IP Server.
// In addition to a base class change, make sure all base member invocations
// of your derived class now invoke SECOleServerItem in place of COleServerItem
// Note: If your IP Server is an ActiveX document server, use 
// SECDocObjectServerItem instead of this class.
//@xref <c SECDocObjectServerItem>
//@xref <c SECOleServerDoc>
class SECOleServerItem : public COleServerItem
{
	TOOLKIT_DECLARE_DYNAMIC(SECOleServerItem);

public:
	TOOLKIT_API SECOleServerItem(COleServerDoc* pServerDoc, BOOL bAutoDelete);

protected:
	TOOLKIT_API virtual void OnShow();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECOleServerItem)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(SECOleServerItem)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SECDocObjectServerItem

//@doc SECDocObjectServerItem 
//@class CDocObjectServerItem derived class to provide support for OT docking windows inside an OLE IP Server
//@BASE public | CDocObjectServerItem 
//@comm
// Use this class in place of an existing CDocObjectServerItem base class to 
// provide native support for OT docking windows with an OLE IP Server.
// In addition to a base class change, make sure all base member invocations
// of your derived class now invoke SECDocObjectServerItem in place of CDocObjectServerItem
// Note: If your IP Server is NOT an ActiveX document server, use 
// SECOleServerItem instead of this class.
//@xref <c SECOleServerItem>
//@xref <c SECOleServerDoc>
class SECDocObjectServerItem : public CDocObjectServerItem
{
	TOOLKIT_DECLARE_DYNAMIC(SECDocObjectServerItem);

public:
	TOOLKIT_API SECDocObjectServerItem(COleServerDoc* pServerDoc, BOOL bAutoDelete);

protected:
	TOOLKIT_API virtual void OnShow();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECDocObjectServerItem)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(SECDocObjectServerItem)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SECOleServerDoc

//@doc SECOleServerDoc 
//@class COleServerDoc derived class to provide support for OT docking windows inside an OLE IP Server
//@BASE public | COleServerDoc 
//@comm
// Use this class in place of an existing COleServerDoc base class to 
// provide native support for OT docking windows with an OLE IP Server.
// In addition to a base class change, make sure all base member invocations
// of your derived class now invoke SECOleServerDoc in place of COleServerDoc.
//@xref <c SECOleServerItem> <c SECDocObjectServerItem>
class SECOleServerDoc : public COleServerDoc
{
	TOOLKIT_DECLARE_DYNAMIC(SECOleServerDoc);

public:
	// Non-virtual override of COleServerDoc::ActivateInPlace(),
	// accomplished through direct cast from calling code in 
	// SECOleServerItem::OnShow
	TOOLKIT_API BOOL ActivateInPlace();

protected:

	TOOLKIT_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SECOleServerDoc

// ************** IMPORTANT VERSIONING NOTE *********************
// This class is derived from SECFrameWnd to provide the necessary
// OT docking windows capability inside an inplace frame window.
// MFC expects a COleCntrFrameWnd (derived from CFrameWnd) objects 
// to be used in this capacity, as instantiated in 
// COleServerDoc::ActivateInPlace. Clearly we need to replace the
// COleCntrFrameWnd objects with SECOleCntrFrameWnd objects to
// provide the necessary docking window support, but since
// C++ is a statically typed language and MFC does not easily
// support multiple inheritance with 2 CWnd derived base classes,
// we need to resort to stronger measures. Since SECOleCntrFrameWnd
// is a code-copied version of COleCntrFrameWnd, but with a SECFrameWnd
// base class in place of CFrameWnd, we can fool C++ by issuing a
// reinterpret_cast to alter the C++ type of this object from 
// SECOleCntrFrameWnd to COleCntrFrameWnd (see 
// SECOleServerDoc::ActivateInPlace). This works because
// the layout of this class (member var/function offsets, vtable,etc.)
// is identical to that of COleCntrFrameWnd. Therefore, this class
// must ALWAYS maintain an exact duplicate of the class declaration
// defined for COleCntrFrameWnd. NO MODIFICATIONS ALLOWED!
// Use a derived class to make any necessary modifications.
// A pragma warning has been placed in the source file to insure
// this class is always updated with the latest version of MFC.
// ************** IMPORTANT VERSIONING NOTE *********************

class SECOleCntrFrameWnd : public SECFrameWnd
{
	TOOLKIT_DECLARE_DYNAMIC(SECOleCntrFrameWnd);

// Constructor
public:
	TOOLKIT_API SECOleCntrFrameWnd(COleIPFrameWnd* pInPlaceFrame);

// Implementation
protected:
	COleIPFrameWnd* m_pInPlaceFrame;
	TOOLKIT_API virtual void PostNcDestroy();

public:
	TOOLKIT_API virtual ~SECOleCntrFrameWnd();
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify = TRUE);
	TOOLKIT_API void OnIdleUpdateCmdUI();
	TOOLKIT_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);
#ifdef _DEBUG
	TOOLKIT_API void AssertValid() const;
#endif
};


/////////////////////////////////////////////////////////////////////////////
// SECFriendOleIPFrameWnd

// Utility class to provide proper friendship access to protected "SEC"
// counterparts of COleIPFrameWnd function.

class SECFriendOleIPFrameWnd : public COleIPFrameWnd 
{
	// grant proper friendship access to the corresponding
	// SEC helper classes.
	friend class SECOleServerItem;
	friend class SECOleServerDoc;
	friend class SECOleCntrFrameWnd;
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

#endif // WIN32

#endif // MFC version

#endif //	__SECOLEDOCK_H__
