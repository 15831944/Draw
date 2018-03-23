///////////////////////////////////////////////////////////////////////////////
// secwsmgr.h
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
//  Authors:		Dean Hallman & Scot Wingo
//  Description:	SECWorkspaceManager declaration
//
// Change History:
//  2/24/97 Mark Isham - Restructured architecture for better extensibility
//                       and SECDockState tracking
// 06.19.06 CSD          exported classes with TOOLKIT_API macro

#ifdef WIN32

#ifndef __SECWSMGR_H__
#define __SECWSMGR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __LSTBXEDT_H__
#include "toolkit\lstbxedt.h"
#endif

#ifndef __SBARMGR_H__
#include "toolkit\sbarmgr.h"
#endif

#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
#endif

#ifndef __SWINMDI_H__
#include "toolkit\swinmdi.h"
#endif

#ifndef __SDOCKSTA_H__
#include "toolkit\sdocksta.h"
#endif

#ifndef __SECREG_H__
#include "toolkit\secreg.h"
#endif

#include <StingrayExportDefs.h>

class SECToolBarManager;

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

#define SEC_WORKSPACE_MGR_WORKSPACE_LIST	_T("Workspace List\\")
#define SEC_WORKSPACE_MGR_WORKSPACES   		_T("Workspaces\\")
#define SEC_WORKSPACE_MGR_WORKSPACES_COUNT  _T("workspace_count")
#define SEC_WORKSPACE_MGR_WORKSPACES_PREFIX _T("workspace_")


/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceState

class SECWorkspaceState : public CObject  
{
    TOOLKIT_DECLARE_DYNAMIC(SECWorkspaceState);

public:
    // Construction
    TOOLKIT_API SECWorkspaceState();

public:
	TOOLKIT_API void EmptyWindowInfoList();

	// Override these to implement your own storage medium/protocol.
	TOOLKIT_API virtual BOOL SaveState(CString strBaseRegKey,CString strWorkspaceName);
	TOOLKIT_API virtual BOOL LoadState(CString strBaseRegKey,CString strWorkspaceName);
	TOOLKIT_API virtual void Serialize(CArchive& ar,CString strWorkspaceName);

	TOOLKIT_API virtual BOOL RenameState(CString strBaseRegKey,CString strOldName,CString strNewName);
	TOOLKIT_API virtual BOOL DeleteState(CString strBaseRegKey,CString strWorkspaceName);

   // Implementation    
public:
	CObList					m_WindowInfoList;
	CDockState*				m_pDockState;
	CString					m_strStateName;
	SECControlBarManager*	m_pManager;

protected:
  
// Implementation
public:
	TOOLKIT_API virtual ~SECWorkspaceState();

protected:
};

/////////////////////////////////////////////////////////////////////////////
// SECWindowInfo

// Window type specifiers - use for bitwise comparisons
#define SEC_WININFO_TYPE_SEC				0x0001
#define SEC_WININFO_TYPE_TOP_LEVEL_FRAME	0x0002
#define SEC_WININFO_TYPE_MDI_FRAME			0x0004

// Registry keywords for use by SECWindowInfo
#define SEC_WININFO_REG_PATHNAME	_T("PathName")
#define SEC_WININFO_REG_DOCTYPE		_T("DocType")
#define SEC_WININFO_REG_WINTITLE	_T("WindowTitle")
#define SEC_WININFO_REG_TYPE		_T("Type")
#define SEC_WININFO_REG_WNDPLACE	_T("WindowPlacement")

class SECWindowInfo : public CObject 
{

    TOOLKIT_DECLARE_DYNAMIC(SECWindowInfo);
    
public:

    // Construction
    TOOLKIT_API SECWindowInfo();
	TOOLKIT_API virtual ~SECWindowInfo();
	TOOLKIT_API virtual void SetWindowType(CWnd* pWnd);

	// override these if you have any additional information to load/store		
	TOOLKIT_API virtual void SaveToRegistry(SECRegistry& rRegKey);
	TOOLKIT_API virtual void LoadFromRegistry(SECRegistry& rRegKey);
	TOOLKIT_API virtual void Serialize(CArchive& ar);

    // Attributes
public:
	CString			m_strPathName;
	CString			m_strDocType;
	CString			m_strWindowTitle;
	DWORD			m_dwType;
	WINDOWPLACEMENT m_wp;
};

/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceManager

//@doc SECWorkspaceManager 
//@class Mechanism for saving and restore application window state. 
//@devnote
// The SECWorkspaceManager class should be considered obsolete
// and is provided solely for backward compatibility. All new development should
// utilize the <c SECWorkspaceManagerEx> class.
//@BASE public | CCmdTarget
//@xref <c SECWorkspaceManagerEx>
class SECWorkspaceManager : public CCmdTarget 
{
    TOOLKIT_DECLARE_DYNAMIC(SECWorkspaceManager);

public:
    // Construction

	//@access Construction/Initialization
    
	//@cmember
	/* Constructor*/
    TOOLKIT_API SECWorkspaceManager();

	// It is recommended that strWorkspaceMgrKey be unique for different
	// applications using the SECWorkspaceMgr, otherwise invalid window
	// configurations may result.

	//@cmember
	/* Initialize the workspace manager*/
	TOOLKIT_API BOOL Create(CWinApp* pWinApp,CString strWorkspaceMgrKey);
	//@cmember
	/* Initialize the workspace manager*/
	TOOLKIT_API BOOL Create(CString strWorkspaceMgrKey);

    // Attributes
public:
    TOOLKIT_API CString  GetActiveWorkspace() const;
    TOOLKIT_API POSITION GetFirstWorkspacePosition() const;
    TOOLKIT_API CString  GetNextWorkspace(POSITION& pos) const;
    TOOLKIT_API int      GetWindowCount() const;
    TOOLKIT_API POSITION GetFirstWindowPosition() const;
    TOOLKIT_API CWnd*    GetNextWindow(POSITION& pos) const;
    TOOLKIT_API BOOL     DoesWorkspaceExist(CString strTestWorkspace);
    
	//@access Operations
public:
	//@cmember
	/* Add new window to workspace open window list*/
    TOOLKIT_API void AddWindow(CWnd* pWnd);

	//@cmember
	/* Remove window from workspace open window list*/
    TOOLKIT_API void RemoveWindow(CWnd* pWnd);

	//@cmember
	/* Close all windows configured via AddWindow*/
    TOOLKIT_API void CloseAllWindows();

	//@cmember
	/* Set a new active workspace*/
	TOOLKIT_API void SetActiveWorkspace(CString& strActiveWorkspace);
    
    // Overridables (operations too)
public:
	//@cmember
	/* Open a new workspace*/
	TOOLKIT_API virtual void OpenWorkspace(CString strWorkspaceName);

	//@cmember
	/* Save existing workspace*/
	TOOLKIT_API virtual void SaveWorkspace(CString strWorkspaceName);

	//@cmember
	/* Rename workspace*/
    TOOLKIT_API virtual BOOL RenameWorkspace(CString strOldName,CString strNewName);

	//@cmember
	/* Create a new workspace*/
    TOOLKIT_API virtual BOOL CreateNewWorkspace(CString strWorkspaceName);

	//@cmember
	/* Delete Workspace*/
    TOOLKIT_API virtual BOOL DeleteWorkspace(CString strWorkspaceName);

	//@cmember
	/* Close currently active workspace*/
    TOOLKIT_API virtual void CloseActiveWorkspace();

    TOOLKIT_API virtual void ReadWorkspaceList();
	TOOLKIT_API virtual void RefreshWorkspaceListInReg();

protected: 
	// Overridable implementation

	// Called by workspace manager on the onset of a workspace state
	// operation. These are the entry points to all major state operations.
	// Override these to implement your own workspace protocol 
	// and/or storage medium.
    TOOLKIT_API virtual BOOL OnWorkspaceStateLoad(SECWorkspaceState& rState,
									  CString strWorkspaceName);
    TOOLKIT_API virtual BOOL OnWorkspaceStateSave(SECWorkspaceState& rState,
									  CString strWorkspaceName);
	TOOLKIT_API virtual BOOL OnWorkspaceStateRename(SECWorkspaceState& rState,
									  CString strOldWorkspaceName,
									  CString strNewWorkspaceName);
	TOOLKIT_API virtual BOOL OnWorkspaceStateDelete(SECWorkspaceState& rState,
									  CString strWorkspaceName);


	// These are called when the workspace state is to be loaded/saved.
	// Override *both* to perform your own custom workspace state 
	// implementation.
	TOOLKIT_API virtual BOOL GetWorkspaceState(SECWorkspaceState& rState);
 	TOOLKIT_API virtual BOOL SetWorkspaceState(SECWorkspaceState& rState);

	// Open document with specified path name
	TOOLKIT_API virtual CDocument* OnOpenDocumentFile(CDocTemplate* pDocTempl,CString strPathName);
	TOOLKIT_API virtual BOOL OnPromptSaveAsIfNecessary(CString& strPathName,CFrameWnd* pWnd,CDocument* pDoc);
	TOOLKIT_API virtual BOOL OnAddToWindowList(CWnd* pWnd);

	// Called immediately before a window will be set to the
	// workspace or loaded from the workspace. Override and return
	// FALSE to veto 1 or more windows.
	TOOLKIT_API virtual BOOL OnSetWorkspaceStateWnd(SECWindowInfo* pWI);
	TOOLKIT_API virtual BOOL OnGetWorkspaceStateWnd(CWnd* pWnd);

	// These are called just before SECDockState load/save.
	// Override and return FALSE to perform custom SECDockState load/save.
	TOOLKIT_API virtual BOOL OnSetWorkspaceStateDockState();
	TOOLKIT_API virtual BOOL OnGetWorkspaceStateDockState();

	// Override this to supply your own workspace manager dialog
	TOOLKIT_API virtual CDialog* CreateWorkspaceManagerDialog(SECWorkspaceManager* pWSM);

   // Implementation    
public:
    CStringList	m_strListWorkspaces;
    CString		m_strActiveWorkspace;
    CObList		m_obListWindows;
    CWinApp*	m_pWinApp;
	CString		m_strWorkspaceRegBase;
	CString		m_strWorkspaceList;
	CString		m_strWorkspaceStorage;

protected:
	// return registry key of workspace list
	inline virtual CString GetWorkspaceListKey() { return m_strWorkspaceList; }
	inline virtual CString GetWorkspaceDataKey() { return m_strWorkspaceStorage; }
	inline virtual CString GetRegistryKey() { return GetWorkspaceListKey(); } // back compatible

protected:
	// Frame window for control bar state save/load
    SECFrameWnd*	m_pFrameWnd;
    SECMDIFrameWnd* m_pMDIFrameWnd;

// Implementation
public:
	TOOLKIT_API virtual ~SECWorkspaceManager();

protected:
	// Generated message map functions
	//{{AFX_MSG(SECWorkspaceManager)
	TOOLKIT_API afx_msg BOOL OnWorkspace(UINT nID);
	TOOLKIT_API afx_msg void OnUpdateWorkspaceMenu(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnWorkspaceNew();
	TOOLKIT_API afx_msg void OnWorkspaceOpen();
	TOOLKIT_API afx_msg void OnWorkspaceSaveAs();
	TOOLKIT_API afx_msg void OnWorkspaceDelete();
	TOOLKIT_API afx_msg void OnWorkspaceClose();
	TOOLKIT_API afx_msg void OnWorkspaceSave();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceListBoxEditor
class SECWorkspaceManagerDialog;

class SECWorkspaceListBoxEditor : public SECListBoxEditor
{
public:
	TOOLKIT_API SECWorkspaceListBoxEditor(SECWorkspaceManager* pWM,SECWorkspaceManagerDialog* pWMD);

protected:
	// virtual overrides
	TOOLKIT_API virtual void OnEditingJustStarted();
	TOOLKIT_API virtual void OnEditingStopped();
	TOOLKIT_API virtual void OnItemRenamed(int nIndexRenamed,CString strOldName,CString NewName);
	TOOLKIT_API virtual void OnItemAdded(int nIndexNewItem,CString strTextInserted);
	TOOLKIT_API virtual void OnItemMoved(int nOldIndex,int nNewIndex,CString strTextMoved,BOOL WasDragged);
	TOOLKIT_API virtual BOOL OnItemDelete(int nIndexToBeDeleted,CString strTextDeleted);

	// implementation
	TOOLKIT_API BOOL ReplaceListBoxItem(CListBox* pLB,int iIndex,CString strNewText,SEC_DWORD dwItemData=0);
	
	SECWorkspaceManager* m_pWM;
	SECWorkspaceManagerDialog* m_pWMD;
};


/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceManagerDialog

class SECWorkspaceManagerDialog : public CDialog
{
// Construction
public:
	TOOLKIT_API SECWorkspaceManagerDialog(SECWorkspaceManager* pWSM,CWnd* pParent = NULL);
	TOOLKIT_API ~SECWorkspaceManagerDialog();
    TOOLKIT_API BOOL UpdateWorkspaceRenameMap(CString strOldName,CString strNewName);
	TOOLKIT_API void AddWorkspaceToKillList(CString strWorkspaceName);

// Dialog Data
	//{{AFX_DATA(SECWorkspaceManagerDialog)
	enum { IDD = IDD_OPEN_WORKSPACE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{Afx_VIRTUAL(SECWorkspaceManagerDialog)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	SECWorkspaceListBoxEditor* m_pLBEditor;
    SECWorkspaceManager* m_pWSM;

	// workspace rename map
	TOOLKIT_API void InitializeWorkspaceRenameMap();
	TOOLKIT_API void ApplyWorkspaceRenameMap();
	
	CMapStringToString m_strWorkspaceRenameMap;
	CStringList m_strWorkspacesDeleted;

	BOOL m_bNT351;

	TOOLKIT_API void ApplySettings();

	// Generated message map functions
	//{{AFX_MSG(SECWorkspaceManagerDialog)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnOpenWorkspace();
	TOOLKIT_API afx_msg void OnSaveWorkspace();
	TOOLKIT_API afx_msg void OnDone();
	TOOLKIT_API afx_msg void OnCancel();
	TOOLKIT_API afx_msg void OnPaint();
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

#endif // __SECWSMGR_H__

#endif // WIN32

