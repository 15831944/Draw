///////////////////////////////////////////////////////////////////////////////
// sbarmgr.h
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
//  Authors:		Dean Hallman
//  Description:	Declarations for SECControlBarManager
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __SBARMGR_H__
#define __SBARMGR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECPERSTREE_H__
#include "toolkit\perstree.h"
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

// Forward Declarations
class SECControlBarInfo;
class SECControlBarInfoEx;

/////////////////////////////////////////////////////////////////////////////
// SECControlBarManager
//

/////////////////////////////
// AutoDuck tag block block for SECControlBarManager 

// adinsert AutoDuck insertion point for SECControlBarManager 
//@doc SECControlBarManager 
//@class The SECControlBarManager class manages control bars as well as the
// state of an application's main frame.  It supports dynamic save and restore
// of control bars.
//@comm
// Included in Objective Toolkit is <c SECControlBar>, which replaces CControlBar as
// the base class for all your control bars.  SECControlBar adds support for sizing
// while docked, automatic stretching when resized and a default context menu with
// facilities for adding and removing menu items.
//
// See the VIZ sample in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ directory for a demonstration 
// of this class.
//@base public | CObject
class SECControlBarManager : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECControlBarManager)

// Construction
public:
	//@cmember
	/* Default constructor.*/
	TOOLKIT_API SECControlBarManager();
	//@cmember
	/* Constructor taking a pointer to the parent frame window.*/
	TOOLKIT_API SECControlBarManager(CFrameWnd* pFrameWnd);

// Operations
public:
	// Returns the a pointer to the main frame.
	//@cmember
	/* Returns the a pointer to the main frame.*/
	TOOLKIT_API virtual CFrameWnd* GetFrameWnd() const;

	// Save/Restore manager state
	// virtual overload provided for over-ride only. No functionality implemented.
	TOOLKIT_API virtual void LoadState(LPCTSTR lpszProfileName);

	// Locates and loads the PTN object
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pRoot);

	// virtual overload provided for over-ride only. No functionality implemented.
	TOOLKIT_API virtual void SaveState(LPCTSTR lpszProfileName) const;

	// Support for dynamic control bar save/restore. Use when
	// a variable number of control bars of a particular type
	// must be saved and restored.  (i.e. User-defined toolbars)
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory, SECPersistentTreeNode* pParent);	
	//@cmember
	/* Virtual overload provided for override only. No functionality implemented in this base class. It will differentiate between a tool bar and a menu bar in the custom classes.*/
	TOOLKIT_API virtual DWORD GetBarTypeID(CControlBar* pBar) const;
	//@cmember
	/* Virtual overload provided for override only. No functionality implemented in this base class. It will create an appropriate extended information pointer (pInfoEx) for the bar info provided so that the bar may be persistant.*/
	TOOLKIT_API virtual SECControlBarInfoEx* CreateControlBarInfoEx(SECControlBarInfo*) const;
	// Undock member Virtual overload provided for override only. No functionality implemented in this base class. It will dynamicly create a bar from a SECCONTROLBARINFO pointer.
	TOOLKIT_API virtual CControlBar* DynCreateControlBar(SECControlBarInfo* pBarInfo);

// Implementation
public:
	// Destructor
	TOOLKIT_API virtual ~SECControlBarManager();

// Attributes
protected:
	// Protected pointer to the main frame
	CFrameWnd* m_pFrameWnd;	
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SBARMGR_H__

#endif // WIN32

