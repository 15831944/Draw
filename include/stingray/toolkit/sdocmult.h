///////////////////////////////////////////////////////////////////////////////
// sdocmult.h
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
//  Author:			Dean Hallman
//  Description:	Declarations for SECMultiDocTemplate
//  Created:		Sept 1996
//

#ifdef WIN32

#ifndef __SDOCMULT_H__
#define __SDOCMULT_H__

#ifndef __SDOCKFRM_H__
#include "toolkit\sdockfrm.h"
#endif

#ifndef __SBARDOCK_H__
#include "toolkit\sbardock.h"
#endif

#ifndef __SYSCMDEX_H__
#include "toolkit\syscmdex.h"
#endif

#ifndef __S_DC_VW_FBK_H__
#include "toolkit\sdcvwfbk.h"
#endif //__S_DC_VW_FBK_H__

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


// Inline AutoDuck functions/data

//@doc SECMultiDocTemplate
//@mdata DWORD  | SECMultiDocTemplate | m_dwDockableScxFlags | SCX flags passed to OnEnableSysCommandEx() for a new dockable frame; default is SCXOPT_ENABLED \| SCXOPT_NO_CAPTION_BUTTON
//@xref <c SECMultiDocTemplate>

//@doc SECMultiDocTemplate
//@mdata DWORD  | SECMultiDocTemplate | m_dwScxFlags | SCX flags passed to OnEnableSysCommandEx() for a new mdi child; default is SCXOPT_ENABLED \| SCXOPT_NO_CAPTION_BUTTON
//@xref <c SECMultiDocTemplate>

//@doc SECMultiDocTemplate
//@mfunc BOOL  | SECMultiDocTemplate | IsCaptionButtonEnabled | Returns TRUE if the SCXOPT_NO_CAPTION_BUTTON flag is NOT present
//@xref <c SECMultiDocTemplate>

//@doc SECMultiDocTemplate
//@mfunc BOOL | SECMultiDocTemplate | IsContextMenuEnabled | Returns TRUE if the SCXOPT_NO_CONTEXTMENU flag is NOT present
//@xref <c SECMultiDocTemplate>

//@doc SECMultiDocTemplate
//@mfunc BOOL  | SECMultiDocTemplate | IsRDblClickEnabled | Returns TRUE if the SCXOPT_NO_HANDLE_RDBLCLK flag is NOT present
//@xref <c SECMultiDocTemplate>

//@doc SECMultiDocTemplate
//@mfunc ISECVwDockFeedBack*  | SECMultiDocTemplate | GetFeedbackInterface | Returns pointer to an implementation of ISECVwDockFeedBack.
//Default does a dynamic_cast on the view class assuming that the interface is mixed in with the derived view class.
//Derive from SECMultiDocTemplate if this is not appropriate
//@xref <c SECMultiDocTemplate>


/////////////////////////////////////////////////////////////////////////////
// SECMultiDocTemplate
//


// SECDockableState
//   enum of state values for a dockable window.  A dockable window is either docked left, docked top, docked bottom,
//   docked right, or "dockable-floating."  "Dockable-floating" means the window is floating but can be docked.
//   For brevity of notation, this enum is not nested within the namespace of SECMultiDocTemplate.
// Note: due to an autoduck parsing error, this enum is commented in the remarks
// of GetDockableState
//@enum Dockable states
enum SECDockableState {
	SEC_DOCKABLE_NULL_STATE=-1,			//@emem NULL initialization
	SEC_DOCKED_TOP, 					//@emem docked to top dockbar
	SEC_DOCKED_LEFT, 					//@emem docked to left dockbar
	SEC_DOCKED_BOTTOM, 					//@emem docked to bottom dockbar
	SEC_DOCKED_RIGHT, 					//@emem docked to right dockbar
	SEC_DOCKABLE_FLOAT 					//@emem floating state
};

// Forward Declarations
class SECDockableFrame;

//@doc SECMultiDocTemplate 
//@class MDI Document Template with Docking Views enablement
//@BASE public | CMultiDocTemplate
//@comm This document template class must be used to utilized Stingray Docking Views 
class SECMultiDocTemplate : public CMultiDocTemplate
{
	TOOLKIT_DECLARE_DYNAMIC(SECMultiDocTemplate)

	typedef std::list<HWND>  CParentList;

// Constructors
public:
	//@access Construction/Initialization

	//@cmember
	/* Constructor*/
	TOOLKIT_API SECMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pViewClass, DWORD dwScxFlags = -1);

	//@cmember
	/* Constructor*/
	TOOLKIT_API SECMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,CRuntimeClass* pFrameClass,
		CRuntimeClass* pViewClass,UINT nIDDockableResource = 0, CRuntimeClass* pDockableFrameClass = 0,
		CRuntimeClass* pControlBarClass = 0, DWORD dwScxFlags = -1);

public:

	//@access Operations

	// See base class...
	TOOLKIT_API virtual void LoadTemplate();

	inline CRuntimeClass* GetDockFrameClass() { return m_pDockableFrameClass; }
	inline CRuntimeClass* GetControlBarClass() { return m_pControlBarClass; }

// Attributes
protected:
	CRuntimeClass*	m_pDockableFrameClass;	// Class for creating new dockable frames
	CRuntimeClass*	m_pControlBarClass;
	BOOL			m_bCreateDocked;
	UINT			m_nIDDockableResource;  // IDR_ for dockable frame/menu/accel as well
	COleClientItem*	m_pActiveClientItem;	// This member added to record the current in-place active ole item

// Overridables
public:
	// base override
	TOOLKIT_API virtual CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther);

	//@cmember
	/* Create a new frame window, with the option of initially docked*/
	TOOLKIT_API virtual CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther,
								BOOL bInitiallyDocked,
								int nDockedViewBarID = 0);

	//@cmember
	/* Open a new document, with the option to create initially docked.*/
	TOOLKIT_API virtual CDocument* OpenDocumentFile(
		LPCTSTR lpszPathName,
		BOOL bMakeVisible = TRUE,
		BOOL bInitiallyDocked = FALSE,
		int nDockedViewBarID = 0);

	//@cmember
	/* Toggle the docking state of the frame window parameter*/
	TOOLKIT_API virtual CFrameWnd* ToggleDocking(CFrameWnd* pFrame);

	//@cmember
	/* Create a dockable frame to wrap the docking view*/
	TOOLKIT_API virtual SECDockableFrame* CreateNewDockableFrame(CDocument* pDoc, CFrameWnd* pOther,UINT nDockBarID = 0,const SECDockPos * pPos = 0, const SECDockSize * pSize = 0);

	//@cmember
	/* Check if frame is currently docked*/
	TOOLKIT_API virtual BOOL IsDocked(const CFrameWnd* pFrame) const;

	//@cmember
	/* Query current frame's docking state*/
    TOOLKIT_API virtual SECDockableState GetDockableState (const CFrameWnd* pFrame) const;

	//@cmember
	/* Dock a frame*/
	TOOLKIT_API virtual CFrameWnd* Dock(CFrameWnd* pFrameOld);

	//@cmember
	/* Dock a frame at a specific spot*/
	TOOLKIT_API virtual CFrameWnd* Dock(CFrameWnd* pFrameOld, UINT nDockBarID, const SECDockPos * pDockPos, const SECDockSize * pDockSize);

	//@cmember
	/* Undock a frame*/
	TOOLKIT_API virtual CFrameWnd* Undock(CFrameWnd* pFrameOld);

	//@cmember
	/* Reparent all children of the old frame to the new frame*/
	TOOLKIT_API virtual void ReparentAllChildren(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew);

	//@cmember
	/* Activate the dockable frame passed in*/
	TOOLKIT_API virtual BOOL ActivateDockableFrame(CFrameWnd* pFrameNew);

// WM_SYSCOMMANDEX enablement
//   WM_SYSCOMMANDEX handling allows the frame type to be dynamic (e.g., as in docking views)
//   and optionally has a new button in the caption to automatically send WM_SYSCOMMANDEX
//   messages for the user.  The virtual OnEnableSysCommandEx() is called when a new frame 
//   is created.  The default implementation  OnEnableSysCommandEx() calls the EnableSysCommandEx()
//   member of the frame and passes the DWORD flags parameter as is.  To enable WM_SYSCOMMANDEX 
//   handling but disable the caption button, use m_dwScxFlags |= SCXOPT_NO_CAPTION_BUTTON or
//   m_dwDockableScxFlags |= SCXOPT_NO_CAPTION_BUTTON.  
//   Similarly, use the flag SCXOPT_NO_HANDLE_RDBLCLK to disable right double
//   click firing of WM_SYSCOMMANDEX.
// The SCXOPT_ constants are in the namespace nsSysCommandEx.
public:
	//@cmember
	/* Tailor WM_SYSCOMMANDEX commands of interest.*/
	TOOLKIT_API virtual void OnEnableSysCommandEx(CFrameWnd* pFrame, DWORD dwScxFlags);

	//@cmember
	/* Adds/Removes the SCXOPT_NO_CAPTION_BUTTON flag*/
	TOOLKIT_API virtual void EnableCaptionButton(BOOL bEnable=TRUE, BOOL bUpdate=TRUE);

	//@cmember
	/* Adds/Removes the SCXOPT_NO_HANDLE_RDBLCLK flag*/
	TOOLKIT_API virtual void EnableRDblClick(BOOL bEnable=TRUE, BOOL bUpdate=TRUE);

	//@cmember
	/* Adds/Removes the SCXOPT_NO_CONTEXTMENU flag. 
	The context menu is displayed by right clicking in the caption.*/
	TOOLKIT_API virtual void EnableContextMenu(BOOL bEnable, BOOL bUpdate=TRUE);
	
	//@cmember
	/* Returns TRUE if the SCXOPT_NO_CAPTION_BUTTON flag is NOT present*/
	TOOLKIT_API virtual BOOL IsCaptionButtonEnabled(){return !(m_dwScxFlags & nsSysCommandEx::SCXOPT_NO_CAPTION_BUTTON);}

	//@cmember
	/*  Returns TRUE if the SCXOPT_NO_HANDLE_RDBLCLK flag is NOT present*/
	TOOLKIT_API virtual BOOL IsRDblClickEnabled(){ return !(m_dwScxFlags & nsSysCommandEx::SCXOPT_NO_HANDLE_RDBLCLK);}

	//@cmember
	/*  Returns TRUE if the SCXOPT_NO_CONTEXTMENU flag is NOT present*/
	TOOLKIT_API virtual BOOL IsContextMenuEnabled(){ return !(m_dwScxFlags & nsSysCommandEx::SCXOPT_NO_CONTEXTMENU);}

	//@cmember
	/*  Adds and/or removes SCXOPT flags from the template*/
	TOOLKIT_API virtual void ModifyOptions(DWORD dwRemove, DWORD dwAdd, BOOL bUpdate=TRUE);

	//@cmember
	/*  Updates the SCXOPT flags for every frame window created using this doc template*/
	TOOLKIT_API virtual void UpdateAllFrames();

	//@cmember
	/*  Return the docking feedback reciever interface. This can be NULL. Default does a dynamic_cast on CView* to get interface.*/
	TOOLKIT_API virtual ISECVwDockFeedBack* GetFeedbackInterface(CView* pView) {ASSERT(pView != NULL); return dynamic_cast<ISECVwDockFeedBack*>(pView);};

// reflection support
	//@cmember
	/*  When CCtrlView derived classes are used call this method to enable notification messages to work.*/
	TOOLKIT_API void EnableReflection();

	/*  When CCtrlView derived classes are used call this method to add parent windows of these views*/
	TOOLKIT_API void AddToParentList(HWND hWndParent);
	/*  When CCtrlView derived classes are used call this method to add parent windows of these views*/
	TOOLKIT_API void AddToParentList(const CWnd* pWndParent);
	
	/*  When CCtrlView derived classes are used, call this method to remove previously added parents of these views*/
	TOOLKIT_API void RemoveFromParentList(HWND hWndParent);
	/*  When CCtrlView derived classes are used, call this method to remove previously added parents of these views*/
	TOOLKIT_API void RemoveFromParentList(const CWnd* pWndParent);
// end reflection support

	//@cmember
	/* SCX flags passed to OnEnableSysCommandEx() for a new mdi child; default is SCXOPT_ENABLED \| SCXOPT_NO_CAPTION_BUTTON*/
	DWORD m_dwScxFlags;         

	//@cmember
	/* SCX flags passed to OnEnableSysCommandEx() for a new dockable frame; default is SCXOPT_ENABLED \| SCXOPT_NO_CAPTION_BUTTON*/
	DWORD m_dwDockableScxFlags; 

// Implementation
protected:
	TOOLKIT_API BOOL ActivateDocumentDockableFrame(CDocument* pDocument);

	int m_nSpecificBarID;
	// reflection support members
	bool m_bReflectionEnabled;
	CParentList	m_listParents;

	TOOLKIT_API const CParentList& GetParentList() const;
	TOOLKIT_API CParentList& GetParentListRef();

	TOOLKIT_API bool IsWindowInParentList(const CWnd* pWnd) const;
	TOOLKIT_API bool IsWindowInParentList(HWND hWnd) const;

	TOOLKIT_API void DestroyParentList();
	TOOLKIT_API virtual void ActOnWindow(CWnd* pWnd);

public:
	TOOLKIT_API virtual ~SECMultiDocTemplate();

#ifdef _DEBUG
	TOOLKIT_API virtual void Dump(CDumpContext&) const;
	TOOLKIT_API virtual void AssertValid() const;
#endif //_DEBUG

	// menu & accelerator resource for dockable frame
	HMENU m_hMenuDockable;
	HACCEL m_hAccelDockable;

	// Generated message map functions
	//{{AFX_MSG(SECMultiDocTemplate)
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SDOCMULT_H__

#endif // WIN32

