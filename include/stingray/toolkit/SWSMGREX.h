///////////////////////////////////////////////////////////////////////////////
// SWSMGREX.h
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
// Description:  Declaration of SECWorkspaceManagerEx
//

#ifndef __SECWSMGREX_H__
#define __SECWSMGREX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32
									  
// Header Includes
#ifndef __PLUGIN_H__
#include "Foundation\patterns\MFC\plugin.h"
#endif

#ifndef __SECPERSTREE_H__
#include "toolkit\perstree.h"
#endif

#ifndef __WKSEXDLG_H__
#include "toolkit\WkSExDlg.h"
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

// Use these macros in the frame window classes to insure default message
// handlers are properly provided by the base.
#define DECLARE_WSMGREX_DEFAULT_HANDLERS()					\
	TOOLKIT_API afx_msg BOOL OnWorkspace(UINT nID);						\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceMenu(CCmdUI* pCmdUI);		\
	TOOLKIT_API afx_msg void OnWorkspaceNew();							\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceNew(CCmdUI* pCmdUI);		\
	TOOLKIT_API afx_msg void OnWorkspaceOpen();							\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceOpen(CCmdUI* pCmdUI);		\
	TOOLKIT_API afx_msg void OnWorkspaceSaveAs();						\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceSaveAs(CCmdUI* pCmdUI);	\
	TOOLKIT_API afx_msg void OnWorkspaceDelete();						\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceDelete(CCmdUI* pCmdUI);	\
	TOOLKIT_API afx_msg void OnWorkspaceClose();						\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceClose(CCmdUI* pCmdUI);	\
	TOOLKIT_API afx_msg void OnWorkspaceSave();							\
	TOOLKIT_API afx_msg void OnUpdateWorkspaceSave(CCmdUI* pCmdUI);

#define IMPLEMENT_WSMGREX_DEFAULT_HANDLERS(base)						\
	BOOL base::OnWorkspace(UINT nID) { nID; return TRUE; }				\
	void base::OnUpdateWorkspaceMenu(CCmdUI* pCmdUI) { pCmdUI; }		\
	void base::OnWorkspaceNew() {}										\
	void base::OnUpdateWorkspaceNew(CCmdUI* pCmdUI) { pCmdUI; }			\
	void base::OnWorkspaceOpen() {}										\
	void base::OnUpdateWorkspaceOpen(CCmdUI* pCmdUI) { pCmdUI; }		\
	void base::OnWorkspaceSaveAs() {}									\
	void base::OnUpdateWorkspaceSaveAs(CCmdUI* pCmdUI) { pCmdUI; }		\
	void base::OnWorkspaceDelete() {}									\
	void base::OnUpdateWorkspaceDelete(CCmdUI* pCmdUI) { pCmdUI; }		\
	void base::OnWorkspaceClose() {}									\
	void base::OnUpdateWorkspaceClose(CCmdUI* pCmdUI) { pCmdUI; }		\
	void base::OnWorkspaceSave() {}										\
	void base::OnUpdateWorkspaceSave(CCmdUI* pCmdUI) { pCmdUI; }
																		
#define MAP_WSMGREX_DEFAULT_HANDLERS()									\
	ON_COMMAND_EX_RANGE(ID_WORKSPACE_1, ID_WORKSPACE_SPACES, OnWorkspace) \
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_1, OnUpdateWorkspaceMenu)			\
	ON_COMMAND(ID_WORKSPACE_NEW, OnWorkspaceNew)						\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_NEW, OnUpdateWorkspaceNew)		\
	ON_COMMAND(ID_WORKSPACE_OPEN, OnWorkspaceOpen)						\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_OPEN, OnUpdateWorkspaceOpen)		\
	ON_COMMAND(ID_WORKSPACE_SAVEAS, OnWorkspaceSaveAs)					\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_SAVEAS, OnUpdateWorkspaceSaveAs)	\
	ON_COMMAND(ID_WORKSPACE_DELETE, OnWorkspaceDelete)					\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_DELETE, OnUpdateWorkspaceDelete)	\
	ON_COMMAND(ID_WORKSPACE_CLOSE, OnWorkspaceClose)					\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_CLOSE, OnUpdateWorkspaceClose)	\
	ON_COMMAND(ID_WORKSPACE_SAVE, OnWorkspaceSave)						\
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE_SAVE, OnUpdateWorkspaceSave)

// Types

// Forward Declarations

// AutoDuck inline comments

//@doc SECWorkspaceManagerEx
//@mfunc int  | SECWorkspaceManagerEx | GetMaxWorkspaceMRUSize | Gets the size of the Most Recently Used workspace list
//@xref <c SECWorkspaceManagerEx>

//@doc SECWorkspaceManagerEx
//@mfunc void  | SECWorkspaceManagerEx | SetMaxWorkspaceMRUSize | Set the size of the Most Recently Used workspace list
//@parm UINT | nMaxSize | Max number of entries in the MRU list.
//@xref <c SECWorkspaceManagerEx>

//@doc SECWorkspaceManagerEx
//@mfunc void  | SECWorkspaceManagerEx | GetWorkspaceFileExtension | Get the default file extension used for file based workspaces.
//@parm CString& | strExt | Reference to string to receive the file extension
//@xref <c SECWorkspaceManagerEx>

//@doc SECWorkspaceManagerEx
//@mfunc void  | SECWorkspaceManagerEx | SetWorkspaceFileExtension | Set the default file extension used for file based workspaces.
//@parm CString& | strExt | Reference to string with the file extension
//@xref <c SECWorkspaceManagerEx>

/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceManagerEx

//@doc SECWorkspaceManagerEx 
//@class Extended workspace manager class for persisting frame and controlbar 
// window state. NOTE: New development should exploit this class, rather
// than SECWorkspaceManager, as SECWorkspaceManager is considered obsolete
// and available only for backward compatibility.
//@BASE public | SecWndPlugIn
//@xref <c SECWorkspaceManager>
//@xref <c SECWndPlugIn>
class SECWorkspaceManagerEx : public stingray::foundation::SECWndPlugIn
{
	TOOLKIT_DECLARE_DYNCREATE(SECWorkspaceManagerEx);

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction

	//@cmember
	/* Construction/Initialization*/
	TOOLKIT_API SECWorkspaceManagerEx();
	TOOLKIT_API virtual ~SECWorkspaceManagerEx();

	// Attributes
	// ...Publicly accessible member variables...

	// Accessors
	// ...Get and Set functions...
	
	//@cmember
	/* Set the workspace manager to registry mode*/
	TOOLKIT_API virtual void SetRegistryMode(const CString& strAppSubKey,BOOL bEnable=TRUE,
								 HKEY hKeyApp=HKEY_CURRENT_USER, BOOL bSectionKey=FALSE);
								 
	//@cmember
	/* Set the workspace manager to registry mode*/
	TOOLKIT_API virtual void SetRegistryMode(BOOL bEnable, BOOL bSectionKey = FALSE); 

	// Operations

	//@access Operations

	//@cmember
	/* Close the currently active workspace.*/
	TOOLKIT_API virtual BOOL CloseWorkspace();

	//@cmember
	/* Save the currently active workspace state.*/
	TOOLKIT_API virtual BOOL SaveWorkspace();

	//@cmember
	/* Save the currently active workspace state under a new name.*/
	TOOLKIT_API virtual BOOL SaveWorkspace(CString strWorkspaceName);

	//@cmember
	/* Load a workspace state.*/
	TOOLKIT_API virtual BOOL OpenWorkspace(BOOL bLastActiveWorkspace=FALSE,BOOL bSuppressErrorDlg=FALSE);

	//@cmember
	/* Load the workspace state of the workspace name passed in.*/
	TOOLKIT_API virtual BOOL OpenWorkspace(CString strWorkspaceName,BOOL bSuppressErrorDlg=FALSE);

	//@cmember
	/* Get the name of the currently active workspace. */
	TOOLKIT_API BOOL GetActiveWorkspace(CString& strWorkspaceName); 
	
	// Workspace MRU List manipulation
	
	//@cmember
	/* Set the maximum number of workspaces in the MRU list*/
	inline void SetMaxWorkspaceMRUSize(UINT nMaxSize) { m_nMaxWorkspaceMRUSize=nMaxSize; }
	
	//@cmember
	/* Get the maximum number of workspaces in the MRU list*/
	inline int GetMaxWorkspaceMRUSize() { return m_nMaxWorkspaceMRUSize; }

	//@cmember
	/* Set the workspace default extension*/
	inline void SetWorkspaceFileExtension(const CString& strExt) { m_strWorkspaceFileExt=strExt; }

	//@cmember
	/* Get the workspace default extension*/
	inline void GetWorkspaceFileExtension(CString& strExt) { strExt=m_strWorkspaceFileExt; }
	
	// Overrides
	TOOLKIT_API virtual BOOL PlugInTo( CWnd* pWnd );

protected:
	//@access Overridable

	//@cmember
	/* Get the persistance strategy (file, registry, etc.)*/
	TOOLKIT_API virtual	SECPTNStrategy* GetPersistanceStrategy(const CString& strWorkspace);
	
	//@cmember
	/* Load the controlbar dockstate for current OpenWorkspace operation.*/
	TOOLKIT_API virtual BOOL OpenWorkspaceDockState(SECPersistentTreeNode* pRoot);

	//@cmember
	/* Load the frame window state for current OpenWorkspace operation.*/
	TOOLKIT_API virtual BOOL OpenWorkspaceFrameWnds(SECPersistentTreeNode* pRoot,
										CFrameWnd** ppActiveChildFrame);

	//@cmember
	/* Save the controlbar dockstate for current SaveWorkspace operation.*/
	TOOLKIT_API virtual BOOL SaveWorkspaceDockState(SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pRoot);
	//@cmember
	/* Save the frame window state for current SaveWorkspace operation.										*/
	TOOLKIT_API virtual BOOL SaveWorkspaceFrameWnds(SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pRoot);						
										
	//@cmember
	/* Display prompt dialog for workspace Open or SaveAs*/
	TOOLKIT_API virtual BOOL PromptWorkspaceName(CString& strWorkspaceName,BOOL bSaveAs);	

	//@cmember
	/* Overridable to load your own custom workspace data.*/
	TOOLKIT_API virtual void OpenWorkspaceCustomData(SECPersistentTreeNode* pRoot,
										const CString& strWorkspaceName);

	//@cmember
	/* Overridable to load your own custom workspace data.*/
	TOOLKIT_API virtual void SaveWorkspaceCustomData(SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pRoot,
										const CString& strWorkspaceName);
	
	//@cmember
	/* Close all the child frame windows.*/
	TOOLKIT_API virtual BOOL CloseAllChildFrames();

	//@cmember
	/* Close all the controlbars.*/
	TOOLKIT_API virtual BOOL CloseControlBars(CPtrList* pListBars,CFrameWnd* pFrame);

	//@cmember
	/* Override to load multiple views per single frame window.*/
	TOOLKIT_API virtual BOOL OpenAdditionalViewPerFrame(const CDocument* pDoc,
									const CFrameWnd* pFrame,
									const SECPersistentTreeNode* pAddViewNode);

	//@cmember
	/* Override to save multiple views per single frame window.*/
	TOOLKIT_API virtual SECPersistentTreeNode* SaveAdditionalViewPerFrame(
									CDocument* pDoc,
									CView* pView,
									CFrameWnd* pFrame,
									SECPTNFactory& nodeFactory,
									SECPersistentTreeNode* pParent,
									int nMultViewFrameUniqueID);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables

	// Can only use SECWorkspaceManagerEx with SECFrameWnd or SECMDIFrameWnd,
	// but CFrameWnd is the only common base. Constructors will enforce
	// proper type
	CFrameWnd* m_pFrameWnd;					// frame window mgr is attached to
	CString m_strCurrentWorkspace;			// name of currently open workspace
	BOOL m_bOpenWorkspace;					// true if there is a currently open workspace
	CString m_strWorkspaceFileExt;			// default workspace file extension
	
	// For registry persistence toggle
	CString m_strRegAppSubKey;				// Registry subkey for this app
	HKEY m_hRegAppKey;						// Registry root key for this app
	BOOL m_bRegEnabled;						// Registry support enabled toggle.
    BOOL m_bSectionKey;                     // CString is a section key rather
                                            // than an HKCU subkey

	UINT m_nShowCmd;						// The show command of child frame

	// Workspace MRU list	
	UINT m_nMaxWorkspaceMRUSize;			// max number of workspaces in the MRU list

	// Implementation Member Functions

	// Workspace open/save helper functions
	TOOLKIT_API virtual BOOL OpenWorkspaceMainFrame(SECPersistentTreeNode* pParent);	
	TOOLKIT_API virtual BOOL SaveWorkspaceMainFrame(SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pParent);
	TOOLKIT_API virtual BOOL OpenWorkspaceChildFrames(SECPersistentTreeNode* pParent,
										CFrameWnd** ppActiveChildFrame);
	TOOLKIT_API virtual BOOL SaveWorkspaceChildFrames(SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pParent,
										CFrameWnd* pActiveChildFrame);
	TOOLKIT_API virtual BOOL OpenSpecificChildFrame(SECPersistentTreeNode* pNode,
										CDocument** ppDoc,
										CFrameWnd** ppFrame,
										CFrameWnd** ppActiveChildFrame);
	TOOLKIT_API virtual SECPersistentTreeNode* SaveSpecificChildFrame(CDocument* pDoc,
										CView* pView,
										CFrameWnd* pFrame,
										CFrameWnd* pActiveFrame,
										SECPTNFactory& nodeFactory,
										SECPersistentTreeNode* pParent,
										int nChildNum);	
	TOOLKIT_API virtual BOOL SaveSpecificDockedView(CFrameWnd* pFrame,
										SECPersistentTreeNode* pFrameNode);
	TOOLKIT_API virtual BOOL SaveChildFrameDockedViewPositionFloater(CWnd* pParentWnd,
										SECPersistentTreeNode* pFrameNode);

	// Frame window helper functions
	TOOLKIT_API virtual BOOL OnSaveDoc(CFrameWnd* pFrameWnd,CDocument* pDoc);
	TOOLKIT_API virtual CFrameWnd* OpenChildFrame(CDocTemplate* pDocTemplate,
										const CString& strDocPath,
										CDocument** ppDoc);
	TOOLKIT_API virtual CDocument* OpenChildFrameDockedView(SECPersistentTreeNode* pFrameNode,
										CDocTemplate* pDocTemplate,
										const CString& strDocPath);
	TOOLKIT_API virtual BOOL OpenChildFrameDockedViewPositionFloater(
											SECPersistentTreeNode* pFrameNode,
											CDocument* pDocument);
	TOOLKIT_API virtual BOOL OpenChildFrameDockedViewPositionFloater(
											CFrameWnd* pFrame,
											SECPersistentTreeNode* pFrameNode,
											CDocument* pDocument);
	TOOLKIT_API virtual CFrameWnd* OpenExistingDocNewView(CDocTemplate* pDocTemplate,
										CDocument* pDoc,
										CFrameWnd* pFrame);
	TOOLKIT_API virtual CFrameWnd* OpenExistingDocNewDockedView(
										SECPersistentTreeNode* pFrameNode,
										CDocTemplate* pDocTemplate,
										CDocument* pDoc,
										CFrameWnd* pOther);
	TOOLKIT_API virtual void SetWorkspaceActiveChildFrame(CFrameWnd* pActiveChildFrame);
	
	// Workspace MRU list
public:
	TOOLKIT_API virtual BOOL GetWorkspaceMRUList(CStringList& listWorkspaces);
	TOOLKIT_API virtual LPCTSTR GetWorkspaceMRURegSuffix();								 
	
protected:
	TOOLKIT_API virtual BOOL SetWorkspaceMRUList(const CStringList& listWorkspaces);
	TOOLKIT_API virtual void SetMRUWorkspace(const CString& strWorkspaceName,
								 CStringList& listWorkspaces);
	TOOLKIT_API virtual BOOL RemoveFromMRUList(const CString& strWorkspaceName);

	// User input dialogs. Override for custom dialogs, or to prevent display.
	TOOLKIT_API virtual BOOL PromptWorkspaceNameReg(CString& strWorkspaceName,
										BOOL bAllowOpen,BOOL bAllowSave);
	TOOLKIT_API virtual void UpdateWorkspaceRegSettings(CStringList& listOrigWorkspaces,
												CStringList& listNewWorkspaces,
												CStringList& listDeletedWorkspaces);										
	TOOLKIT_API virtual BOOL PromptWorkspaceNameFile(CString& strWorkspaceName,BOOL bSaveAs);


	// Generated message map functions
	//{{AFX_MSG(SECWorkspaceManagerEx)
	//}}AFX_MSG
	DECLARE_WSMGREX_DEFAULT_HANDLERS()		// Handlers as defined above
	TOOLKIT_DECLARE_MESSAGE_MAP()
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

#endif //__SECWSMGREX_H__

