///////////////////////////////////////////////////////////////////////////////
// sdocksta.h
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
//  Description:	Declarations for SECControlBarInfo and SECDockState
//  Created:		August 1996
//
#ifndef UNDER_CE
#if defined(WIN32)

#ifndef __SDOCKSTA_H__
#define __SDOCKSTA_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECPERSTREE_H__
#include "toolkit\perstree.h"
#endif

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
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
class SECControlBarManager;

/////////////////////////////////////////////////////////////////////////////
// SECDockState
//
class SECDockState : public CDockState
{
	TOOLKIT_DECLARE_SERIAL(SECDockState)

// Construction
public:
	TOOLKIT_API SECDockState();
	TOOLKIT_API SECDockState(SECControlBarManager* pControlBarManager);

// Attributes
protected:
	SECControlBarManager* m_pControlBarManager;

// Operations
public:
	TOOLKIT_API virtual void Serialize(CArchive& ar);
	TOOLKIT_API virtual void SaveState(LPCTSTR lpszProfileName);
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory,SECPersistentTreeNode* pRoot);
	TOOLKIT_API virtual void LoadState(LPCTSTR lpszProfileName);
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pRoot);
	TOOLKIT_API virtual BOOL GetDockState(const CFrameWnd* pFrameWnd);
	TOOLKIT_API virtual BOOL SetDockState(CFrameWnd* pFrameWnd);
	TOOLKIT_API void Clear(); //deletes all the barinfo's

	// For memory management
	TOOLKIT_API void SetAllocList(CPtrList* pList) { m_pAllocList=pList; }

	// Override to create your own controlbar info object
	TOOLKIT_API virtual SECControlBarInfo* CreateCBInfoObject(SECControlBarManager* pMgr);

	// Utility functions used by SetDockState
	TOOLKIT_API virtual void SetControlBarInfoObjects(CFrameWnd* pFrameWnd,BOOL bMDI);
	TOOLKIT_API virtual void ApplyControlBarExtendedStyles();
	TOOLKIT_API virtual void ApplyControlBarInfoMDIChildren(CFrameWnd* pFrameWnd);


// Implementation
public:
	TOOLKIT_API virtual ~SECDockState();

protected:

	// Utility functions used by SetDockState
	TOOLKIT_API virtual SECControlBar* DynCreateControlBar(const CString& strClassName,
							CFrameWnd* pParentWnd,SECControlBarInfo* pInfo);
	TOOLKIT_API virtual CRuntimeClass* LocateRuntimeClass(const CString& strClassName);

	CPtrList* m_pAllocList;
};

/////////////////////////////////////////////////////////////////////////////
// SECControlBarInfoEx

class SECControlBarInfoEx : public CObject
{
	TOOLKIT_DECLARE_DYNCREATE(SECControlBarInfoEx)

// Constructors
public:
	TOOLKIT_API SECControlBarInfoEx();

// Operations
public:
	TOOLKIT_API virtual void Serialize(CArchive& ar, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(LPCTSTR lpszSection, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pBarNode);
	TOOLKIT_API virtual BOOL SaveState(LPCTSTR lpszSection);
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory,
						   SECPersistentTreeNode* pBarNode);
};

/////////////////////////////////////////////////////////////////////////////
// SECControlBarInfo

class SECControlBarInfo : public CControlBarInfo
{
public:
// Implementation
	TOOLKIT_API SECControlBarInfo();
	TOOLKIT_API SECControlBarInfo(SECControlBarManager* pControlBarManager);

// Attributes
  	CSize m_szDockHorz; // Dimensions when docked horizontally
	CPoint m_ptDockHorz;
	CSize m_szDockVert; // Dimensions when docked vertically
	CSize m_szFloat;    // Dimensions when floating
	DWORD m_dwMRUDockingState; // Remember docking state when "Allow Docking" unchecked
	DWORD m_dwDockStyle;
	float m_fPctWidth;
	DWORD m_dwStyle;    // creation style (used for layout)
	DWORD m_dwExStyle;  // Extended Style Bits
	BOOL m_bPreviouslyFloating;  // After unfloat as MDI child,
									// should we dock or float it
	BOOL m_bMDIChild;				// Floating as an MDI child
	WINDOWPLACEMENT m_wpMDIChild;	// WINDOWPLACEMENT info for MDI child.

	// New parms for dynamic controlbar creation
	CString m_strClassName;		// Class name 
	CString m_strWindowName;	// Window name
	int m_nResourceID;			// Dialogbar resource id

    // autohide stuff
    BOOL m_bAutoHide;
    BOOL m_bAutoHidePinned;
    UINT m_nLastAlignedDocking;

	SECControlBarInfoEx* m_pBarInfoEx;
	DWORD m_dwBarTypeID;
	SECControlBarManager* m_pControlBarManager;

	TOOLKIT_API void Serialize(CArchive& ar, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(LPCTSTR lpszProfileName, int nIndex, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pBarNode,SECDockState* pDockState);
	TOOLKIT_API virtual BOOL SaveState(LPCTSTR lpszProfileName, int nIndex);
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory,SECPersistentTreeNode* pParent,
						   int nIndex);


// Implementation
public:
	TOOLKIT_API virtual ~SECControlBarInfo();

protected:
	TOOLKIT_API virtual BOOL LoadCControlBarInfoState(SECPersistentTreeNode* pBarNode,
										  SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadSECControlBarInfoState(SECPersistentTreeNode* pBarNode);
	TOOLKIT_API virtual BOOL SaveCControlBarInfoState(SECPTNFactory& nodeFactory,
										  SECPersistentTreeNode* pBarNode);
	TOOLKIT_API virtual BOOL SaveSECControlBarInfoState(SECPTNFactory& nodeFactory,
										  SECPersistentTreeNode* pBarNode);
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SDOCKSTA_H__

#endif // WIN32
#endif  //UNDER_CE (WindowsCE)
