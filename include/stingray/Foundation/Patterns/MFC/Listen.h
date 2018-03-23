///////////////////////////////////////////////////////////////////////////////
// Listen.h : Declaration of SECWndListener
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
// Description:  Declaration of SECWndListener
//

//
// SECWndListener
// This class implements the ability to attach to an existing CWnd and link 
// to its internal message queue via the standard subclassing mechanism.

#ifndef __SFL_SECWndListener_H__
#define __SFL_SECWndListener_H__

// Header Includes
#include <Foundation\Patterns\MFC\Plugin.h>

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

namespace stingray {
namespace foundation {

//@doc SECWndListener
//@mfunc WNDPROC  | SECWndListener | GetOldWndProc | Gets a pointer to the WNDPROC associated with this window listener.
//@xref <c SECWndListener>

//@doc SECWndListener
//@mfunc DLGPROC  | SECWndListener | GetOldDlgProc | Gets a pointer to the DLGPROC associated with this window listener.
//@xref <c SECWndListener>

// Forward declarations
class SECWndListener;

// Type-safe pointer list of window listener objects (to be associated with each HWND)
typedef CTypedPtrList<CPtrList,SECWndListener*> SECWndListenerList;

// This struct contains info to be associated with each HWND in the ptr map below.
typedef struct SECWndListener_MsgProcInfo_tag {
	// Pointer to the original WNDPROC/DLGPROC for the associated HWND
	UINT size;				// sizeof this struct. For error detection.
	WNDPROC lpfnWndProc;	// 1 or the other, not both!
	DLGPROC lpfnDlgProc;
	SECWndListenerList* pListenerList;
}	SECWndListener_MsgProcInfo;

// Map each HWDN to its unique information struct containing WNDPROC/DLGPROC info
typedef CTypedPtrMap<CMapPtrToPtr,HWND,SECWndListener_MsgProcInfo*> SECHWndToWndListenerListMap;

// Bitflags for SetMessageHandle call
#define SEC_LISTENER_PROCESSNORMAL		0x0000 // continue normal chained processing
#define SEC_LISTENER_HANDLED_LISTENERS	0x0001 // do not forward msg to any more chained listeners
#define SEC_LISTENER_HANDLED_WINDOW		0x0002 // do not forward msg to original window
#define SEC_LISTENER_HANDLED_ALL		0x00ff // stop all processing for this msg (listenrs + orig window)

/////////////////////////////////////////////////////////////////////////////
// SECWndListener

//@doc SECWndListener 
//@class Window Listener base class
//@base public | SECWndPlugIn
class SECWndListener : public SECWndPlugIn
{
	FOUNDATION_DECLARE_DYNAMIC(SECWndListener)
/*protected: 
	FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); 
public: 
	static const CRuntimeClass classSECWndListener; 
	FOUNDATION_API static CRuntimeClass* PASCAL GetThisClass(); 
	FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; 
*/
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	FOUNDATION_API SECWndListener();
	FOUNDATION_API virtual ~SECWndListener();

	inline virtual BOOL AttachWnd(CWnd* pWnd,BOOL bDialogProc=TRUE)
	{ 
		bDialogProc; // unused (provided for back. compat.) 
		return PlugInTo(pWnd); 
	}

	// NOT IMPLEMENTED FOR THIS DERIVED CLASS! Use SetMessageHandleStatus instead!
	inline virtual void SetMessageHandled(BOOL) { ASSERT(FALSE); }

	FOUNDATION_API virtual void SetMessageHandleStatus(DWORD dwHandledType);
	inline DWORD GetMessageHandleStatus(){ return m_dwMsgHandledType; }
	inline void ClearMessageHandleStatus() { m_dwMsgHandledType=SEC_LISTENER_PROCESSNORMAL; }
	FOUNDATION_API void SetMessageLResult(LRESULT lResult);

	// Operations
	FOUNDATION_API virtual BOOL PlugInTo( CWnd* pWnd);
	FOUNDATION_API virtual void UnPlug();

protected:
	//@cmember
	/* Override this to "listen" for a particular message*/
	 FOUNDATION_API virtual BOOL OnSubclassMessage(UINT Message,WPARAM wParam,LPARAM lParam);

	//@cmember
	/* Override this to "listen" for a particular message*/
	FOUNDATION_API virtual BOOL OnSubclassMessage(UINT Message,WPARAM wParam,LPARAM lParam,LRESULT& lResult);

protected:

	// Implementation Member Variables
	DWORD m_dwMsgHandledType;
	HWND m_hWndCached;
	BOOL m_bUseProvidedLResult;
	LRESULT m_LResultProvided;

	// Implementation Member Functions
	FOUNDATION_API virtual BOOL SubclassAttached(CWnd* pWnd);
	FOUNDATION_API virtual BOOL AddListenerEntry(SECWndListener_MsgProcInfo* pProcInfo);
	FOUNDATION_API virtual BOOL SubclassNewListenerEntry(HWND hWndListen);
	FOUNDATION_API virtual BOOL IsWindowProc(HWND hWndListen);
	FOUNDATION_API virtual BOOL UnSubclassAttached();

	//Override needed to avoid multiple reflected notifications in child controls.
	FOUNDATION_API virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	// Static callback functions. These dish off to actual instances of SECWndListener,
	// as is mapped via m_mapHwndToListenerList 
	FOUNDATION_API static LRESULT FAR PASCAL SubclassWndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);
	FOUNDATION_API static LRESULT FAR PASCAL SubclassDlgProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);
	FOUNDATION_API static LRESULT FAR PASCAL SubclassProc(HWND hWnd,UINT Message,WPARAM wParam, LPARAM lParam, BOOL bWndProc);
	FOUNDATION_API static LRESULT FAR PASCAL UnplugAllListeners(HWND hWnd,UINT Message,WPARAM wParam, LPARAM lParam, BOOL bWndProc);

	// Map a C-Style message callback to an actual C++ window listener object.
	static SECHWndToWndListenerListMap m_mapHwndToListenerList;

	// Generated message map functions
	//{{AFX_MSG(SECWndListener)
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


#endif //__SFL_SECWndListener_H__

