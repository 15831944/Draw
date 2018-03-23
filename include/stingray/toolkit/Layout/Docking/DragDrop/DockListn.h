///////////////////////////////////////////////////////////////////////////////
// DockListn.h
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
// Description:  Declaration of SECDockingListener_T 
//

#ifndef __SEC_DOCKING_LISTENER_H__
#define __SEC_DOCKING_LISTENER_H__

#ifdef WIN32

// Header Includes
#include "toolkit\Layout\LayListn.h"
#include "toolkit\DragDrop\LocalMsgDragTask.h"
#include "toolkit\DragDrop\OleDragTask.h"
#include "toolkit\Layout\Docking\DragDrop\DragDropDockFeat.h"
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

typedef SECLocalDragDropTask_T<SECLayoutWndListener> SECLocalDockingDragDropTask;
typedef SECOleDragDropTask_T<SECLayoutWndListener> SECOleDockingDragDropTask;

// Forward Declarations
class SECLNDockingMgr;
class ISECLNContainer;

/////////////////////////////////////////////////////////////////////////////
// ISECDockingListenerConfig

// Common interface for configuration reset.

class ISECDockingListenerConfig 
{
public:
	TOOLKIT_API virtual ~ISECDockingListenerConfig() {}
	virtual void SetAutoRegister(BOOL bAutoRegister)=0;
	virtual BOOL GetAutoRegister()=0;
	virtual void ClearListener()=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECDockingListener_T

// ListenerClass must be derived from SECWndListener!

template <class ListenerBaseClass>
class SECDockingListener_T : public ListenerBaseClass,
							 public ISECDockingListenerConfig
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Initialization/Destruction
	inline SECDockingListener_T() 
	{
		m_pMgr=NULL;
		m_bAutoRegister=TRUE;
		m_pDockFeature=NULL;
	}
	
	inline virtual ~SECDockingListener_T() 
	{
		if(m_pMgr)
			m_pMgr->RemoveRootRegisteredLayoutNode(m_pLayoutNode);
		if(m_pDockFeature)
			delete m_pDockFeature;
	}

	// Implementation of ISECDockingListenerConfig
	inline virtual void SetAutoRegister(BOOL bAutoRegister) { m_bAutoRegister=bAutoRegister; }
	inline virtual BOOL GetAutoRegister() { return m_bAutoRegister; }
	TOOLKIT_API virtual void ClearListener();

	// These overrides will automate much of the docking manager registration
	TOOLKIT_API virtual BOOL AutoInit(SECLayoutNode* pRootNode,CWnd* pParent,
							BOOL bDialogProc=TRUE,
							BOOL bDoRecalc=TRUE,
							BOOL bInitUsingWindowRect=FALSE);
	TOOLKIT_API virtual BOOL AutoInit(SECLayoutNode* pRootNode,CWnd* pParent,
							SECLNDockingMgr* pMgr,BOOL bDialogProc=TRUE,
							BOOL bDoRecalc=TRUE,
							BOOL bInitUsingWindowRect=FALSE);

protected:
	// overridable for custom AutoInit initialization step.
	inline virtual void PerformCustomInit(CWnd*) {}
	inline virtual SECDragDropDockingFeature* CreateDockingFeature() { return new SECDragDropDockingFeature; }

	SECDragDropDockingFeature* m_pDockFeature;
	SECLNDockingMgr* m_pMgr;
	BOOL m_bAutoRegister;
};

/////////////////////////////////////////////////////////////////////////////
// SECDockingListener

// Docking Listener for use with local message loop based drag/drop

class SECDockingListener : public SECDockingListener_T<SECLocalDockingDragDropTask>
{
public:
	// Set threshold to initiate drag on initial lbutton down
	inline virtual void PerformCustomInit(CWnd*) { m_fDragThresholdDistance=0.0f; }
};

/////////////////////////////////////////////////////////////////////////////
// SECOleDockingListener

// Docking Listener for use with OLE based drag/drop

class SECOleDockingListener : public SECDockingListener_T<SECOleDockingDragDropTask>
{
protected:
	TOOLKIT_API virtual void PerformCustomInit(CWnd* pParentWnd);
	SECOleDropTarget m_DockOleDropTarget;
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

#endif  //__SEC_DOCKING_LISTENER_H__
