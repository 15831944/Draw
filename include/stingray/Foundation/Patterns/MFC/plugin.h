///////////////////////////////////////////////////////////////////////////////
// plugin.h : Declaration of SECWndPlugIn
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
// Authors:      Stefan Hoenig, Dean Hallman, Justin Rudd
// Description:  Declaration of SECWndPlugIn
//

#ifdef WIN32

#ifndef __SFL_PLUGIN_H__
#define __SFL_PLUGIN_H__

//
// CMN Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#include <StingrayExportDefs.h>

// Constants

// Macros

// Plugin specific message map macro that returns NULL for CWnd::messageMap queries

#if (_MFC_VER <= 0x0421)
#ifndef AFX_COMDAT
#define AFX_COMDAT
#endif
#endif

//CWangVC7 and Marius solution for SECPlugin
// The message map is no longer exported in VC7 so the  
// _GetBaseMessageMap from VC6 was replaced with GetThisMessageMap in VC7  
// and the semantic of the function was changed to return the current class  
// message map instead of the base class message map 
// Also I have added versioning based on MFC version 
#if (_MFC_VER < 0x0700) 
#ifdef _AFXDLL
#define BEGIN_NOCWND_MESSAGE_MAP(theClass, baseClass) \
	const AFX_MSGMAP* PASCAL theClass::_GetBaseMessageMap() \
		{ return NULL; } \
	const AFX_MSGMAP* theClass::GetMessageMap() const \
		{ return &theClass::messageMap; } \
	AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = \
	{ &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
	AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
	{ \

#else
#define BEGIN_NOCWND_MESSAGE_MAP(theClass, baseClass) \
	const AFX_MSGMAP* theClass::GetMessageMap() const \
		{ return &theClass::messageMap; } \
	AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = \
	{ NULL, &theClass::_messageEntries[0] }; \
	AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
	{ \

#endif//_AFXDLL
#else //_MFC_VER

#ifdef _AFXDLL 
#define BEGIN_NOCWND_MESSAGE_MAP(theClass, baseClass) \
    const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap() \
	{ return &theClass::messageMap; } \
    const AFX_MSGMAP* theClass::GetMessageMap() const \
	{ return &theClass::messageMap; } \
    AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = \
    { NULL, &theClass::_messageEntries[0] }; \
    AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
    { \

#else //_AFXDLL

#define BEGIN_NOCWND_MESSAGE_MAP(theClass, baseClass) \
    const AFX_MSGMAP* theClass::GetMessageMap() const \
	{ return &theClass::messageMap; } \
    AFX_COMDAT const AFX_MSGMAP theClass::messageMap = \
    { NULL, &theClass::_messageEntries[0] }; \
    AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
    { \
 
#endif //_AFXDLL 
#endif //_MFC_VER

#define END_NOCWND_MESSAGE_MAP() \
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } \
	}; \
		static const AFX_MSGMAP messageMap = \
		{ NULL, &_messageEntries[0] }; \
		return &messageMap; \
	}								  \

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
// SECWndPlugIn


//@doc SECWndPlugIn 
//@mdata BOOL | SECWndPlugIn  | m_bNeedDefaultProcessing | Normally, SECWndPlugIn will not forward default processing of a message to CWnd::DefWindowProc.
// This is because you could have multiple plug-ins doing default processing for the same message. However, it is necessary in some cases to allow default
// processing. In this case, set m_bNeedDefaultProcessing to TRUE in the message handler before calling the base class handler. For example, if your
// plug-in has a handler for WM_SETCURSOR ( OnSetCursor ) you will want default processing or the cursor will not behave properly. Simply set m_bNeedDefaultProcessing = TRUE
// before calling SECWndPlugIn::OnSetCursor(...) and the SECWndPlugIn::DefWindowProc will delegate to CWnd::DefWindowProc. m_bNeedDefaultProcessing is
// reset to FALSE in every OnWndMsg.
//@xref <c SECWndPlugIn>


//@doc SECWndPlugIn 
//@class Window "plugin" for tapping into a particular hWnd's message map.
//@base public | CWnd
//@comm An object of this class will attach to a particular hWnd to hook into the message map.
class SECWndPlugIn : public CWnd
{
	FOUNDATION_DECLARE_DYNAMIC(SECWndPlugIn);

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction

	//@cmember
	/* Constructor*/
	 FOUNDATION_API SECWndPlugIn();
	 FOUNDATION_API virtual ~SECWndPlugIn();

	//@access Attributes

	//@cmember
	/* Set to TRUE inside your message handler if you don't want any other plug ins or default message handling done*/
	BOOL m_bExitMessage;

	//@cmember
	/* Set to TRUE inside your message handler to enable CWnd::DefWindowProc processing.*/
	BOOL m_bNeedDefaultProcessing;
	
	//@access Operations

	//@cmember
	/* Specify intercepted message was handled, and set return code for this message. */
	FOUNDATION_API virtual void SetMessageHandled(BOOL bRC=TRUE);
	
	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
public:
	//@cmember
	/* Plug in to the specific window passed in.*/
	FOUNDATION_API virtual BOOL PlugInTo( CWnd* pWnd );
	inline BOOL PlugIn(CWnd* pWnd) { return PlugInTo(pWnd); }
	FOUNDATION_API virtual void UnPlug();
	inline virtual BOOL IsPlugged() { return m_bPluggedIn; }

protected:

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	BOOL m_bMsgHandled, m_bMsgRC, m_bPluggedIn;

	// Implementation Member Functions

	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECWndPlugIn)
	public:
	 FOUNDATION_API virtual BOOL OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	 FOUNDATION_API virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	protected:
	 FOUNDATION_API virtual LRESULT DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	//}}AFX_VIRTUAL
#ifdef _DEBUG
	 FOUNDATION_API virtual void AssertValid() const;
#endif

	//---------------------------------------------------------------------//
	// 						Message Map Declarations					   //
	//---------------------------------------------------------------------//

	// Generated message map functions
	//{{AFX_MSG(SECWndPlugIn)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	FOUNDATION_DECLARE_MESSAGE_MAP()

};

};  // namespace stingray::foundation
};  // namespace stingray

/////////////////////////////////////////////////////////////////////////////

//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SFL_PLUGIN_H__

#endif // WIN32
