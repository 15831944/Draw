///////////////////////////////////////////////////////////////////////////////
// ScriptHostDoc.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SEC_SCRIPTHOSTDOC_H_
#define __SEC_SCRIPTHOSTDOC_H_

// Include this header file only to resolve the GetForm method
// in SECScriptHostDoc class changed by macro in this file
#include <winspool.h> 

//#include <afxrich.h>
#include "toolkit\ActvHost\ScriptHost.h" 
#include "toolkit\ActvHost\ContainerProps.h"
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

// Forward declarations
class  SECAFormObj;		//the 'form' that can fire events
class  CScriptHost;		//active engine host
class  SECACtrlItem;	//the control in design mode
class  SECAObjectDef;	//object definition sufficient to create a control
class  SECAEventBar;	//[objects] [events] VB like thing 

////////////////////////////////////////////////update hints//////////
static int UPDATE_CODE_SAVE			 = 1111;  //non-consts: can be modified 
static int UPDATE_CODE_LOAD			 = 1112;  //at run time if they clash with
static int UPDATE_GOTO_ERROR		 = 1113;  //subclassed hints.
static int UPDATE_FIND_EVENT_HANDLER = 1114;
static int UPDATE_ADD_EVENT_HANDLER  = 1115; 
static int UPDATE_CLEAR_CLIENT		 = 1116;
struct EvtHandlerHint { const CString *str1; const CString *str2; };
//////////////////////////////////////////////////////////////////////

enum	ScriptMode { SM_RUN, SM_DESIGN };

//////////////////////////////////////////////////////////////////////

// Dummy window for error notifications to allow proper stack unwind
// on script failure.
#define SEC_WM_SCRIPT_ERR	WM_USER+0x3f0

class SECScriptHostDocDummyWnd : public CWnd
{
public:
	inline SECScriptHostDocDummyWnd() 			
						{ m_pDoc=(SECScriptHostDoc *)NULL; }
	inline void SetScriptHostDoc(SECScriptHostDoc *pDoc) 
						{ m_pDoc=pDoc; }
protected:
	//{{AFX_MSG(SECCurrencyEdit)
	//}}AFX_MSG
	TOOLKIT_API afx_msg LRESULT OnErrorNotify(WPARAM u,LPARAM l);
	TOOLKIT_DECLARE_MESSAGE_MAP()

	SECScriptHostDoc* m_pDoc;
};	

//////////////////////////////////////////////////////////////////////
//@doc SECScriptHostDoc 
//@mfunc SECAFormObj*  | SECScriptHostDoc | GetFormObj | Returns the form associated with the script.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc ScriptMode | SECScriptHostDoc | GetMode | Returns the current mode: SM_RUN or SM_DESIGN
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc CString& | SECScriptHostDoc | GetScript | Returns the current script text.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc SECAScriptHost* | SECScriptHostDoc | GetScriptHost | Returns the embedded scripting host.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc BOOL | SECScriptHostDoc | OnEnterCodeMode | Edit mode/code view is about to be entered. Return FALSE to abort.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc BOOL | SECScriptHostDoc | OnEnterEditMode | Edit mode is about to be entered. Return FALSE to abort.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc BOOL | SECScriptHostDoc | OnEnterRunMode | Run mode is about to be entered. Return FALSE to abort.
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc  static void | SECScriptHostDoc | SetFormClass | Set the form object runtime class for link back from script.
//@parm CRuntimeClass* | pRuntimeClass | A pointer to the runtime class of the form object
//@xref <c SECScriptHostDoc>

//@doc SECScriptHostDoc 
//@mfunc  void | SECScriptHostDoc | SetScript | Set the current runtime scripting code.
//@parm const CString& | strCode | The text for the scripting code
//@xref <c SECScriptHostDoc>




//@doc SECScriptHostDoc 
//@class ActiveScript document class
//@BASE public | COleDocument
//@BASE public | IActiveScriptErrorHandler
//@comm This class is intended to be plugged directly into your frame window's document template. In general, you will not need to utilize any of these member functions unless deriving a class and customizing functionality.
//@xref <c IActiveScriptErrorHandler>
class SECScriptHostDoc : public COleDocument, 
					     public IActiveScriptErrorHandler
{
protected:
	TOOLKIT_API SECScriptHostDoc();
	TOOLKIT_DECLARE_DYNCREATE(SECScriptHostDoc)

	class SECDocTemplateAccess : public CDocTemplate 
	{
		public:
			TOOLKIT_API SECDocTemplateAccess();
			CRuntimeClass* GetDocClass() 	{ return m_pDocClass; }
			CRuntimeClass* GetViewClass()	{ return m_pViewClass; }
			CRuntimeClass* GetFrameClass()	{ return m_pFrameClass; }
	};


public:
	//public operations

	//@access Accessors

	//@cmember
	/* Access the embedded ScriptHost object*/
	inline SECAScriptHost* GetScriptHost() { return m_pScriptHost; }

	//@cmember
	/* Access the embedded script form object*/
	inline SECAFormObj* GetFormObj() { return InternalGetForm(); }

	//@access Operations

	//@cmember
	/* Enable runtime form edit mode*/
	TOOLKIT_API virtual void EnableEditMode();

	//@cmember
	/* Toggle between edit and run mode*/
	TOOLKIT_API virtual BOOL ToggleMode();

	//@cmember
	/* Set the current form mode*/
	TOOLKIT_API virtual BOOL SetMode( ScriptMode sm );

	//@cmember
	/* Get the current form mode*/
	TOOLKIT_API virtual ScriptMode GetMode() { return m_Mode; }

	//@cmember
	/* View scripting code in edit mode*/
	TOOLKIT_API virtual void ViewCode();	

	//@cmember
	/* View OLE objects in edit mode*/
	TOOLKIT_API virtual void ViewObjects();

	// initializes the document from the file (should be called from the SM_DESIGN state)
	TOOLKIT_API BOOL OpenDocument( LPCTSTR lpszPathName, BOOL fOpenInEditState ); 
	
	TOOLKIT_API void UpdateTitle();

	//these two should only be accessible to the view

	//@cmember
	/* Initialize the scripting model*/
	TOOLKIT_API virtual HRESULT CreateScriptingModel();

	//@cmember
	/* Destroy the existing scripting model*/
	TOOLKIT_API virtual HRESULT DestroyScriptingModel();

	//access to the script

	//@cmember
	/* Return the current runtime script code*/
	inline const CString&	GetScript()	{ return m_Script; }

	//@cmember
	/* Set the current runtime scripting code*/
	inline void SetScript(const CString& strCode)	{ m_Script = strCode; }

	//@cmember
	/* Set the form object runtime class for link back from script.*/
	TOOLKIT_API static void SetFormClass(CRuntimeClass* pRuntimeClass);

	TOOLKIT_API static CRuntimeClass* m_pFormRuntimeClass;

	//creation/destruction of individual items
	TOOLKIT_API virtual SECACtrlItem* CreateItem(const CString &strNameInScrpt, const CRect *initialRect);
	TOOLKIT_API void AddFront(SECACtrlItem* pItem);
	TOOLKIT_API void DeleteItem(SECACtrlItem* pItem);
	TOOLKIT_API virtual CView *GetScriptView(); // default gets the active view
	TOOLKIT_API virtual CFrameWnd *GetFrame();  // different for SDI/MDI -- important override !

	//error handling

	//@access Overridables

	//@cmember
	/* Callback for runtime scripting errors*/
    TOOLKIT_API virtual HRESULT HandleError( IActiveScriptError *perr );

	//event bar interaction
	//@cmember
	/* Adds items to the event bar*/
	TOOLKIT_API virtual HRESULT AddDesignedObjectInfos( SECAEventBar &EventBar );
	TOOLKIT_API BOOL IsEventHandled( const CString &strEventForItem, BOOL fSelectHandler );
	TOOLKIT_API void EventIsHandled( BOOL fHandled );
	TOOLKIT_API BOOL SetEventHandler(const CString &strEventForItem, const CString &strEmptyHandlerBody); //true if set

	//doc's attributes
	inline SECAContainerProps &GetContainerProperties() { return m_contProps; }
	inline const CSize &GetDocumentSize() { return m_contProps.GetFormSize(); }
	inline SECAFormObj *GetForm() { return InternalGetForm(); }
	inline BOOL CompoundFile() { return m_bCompoundFile; }
	inline BOOL	IsNewDoc() { return m_strPathName == _T(""); }
	
protected:
	// virtual overrides

	//@cmember
	/* Create the script host object. Override to hook in a derived class.*/
	TOOLKIT_API virtual SECAScriptHost* OnCreateScriptHost(IActiveScriptErrorHandler* pErrHandler);

	// Mode change - return FALSE to abort the mode change

	//@cmember
	/* Run mode is about to be entered. Return FALSE to abort.*/
	virtual BOOL OnEnterRunMode() { return TRUE; }

	//@cmember
	/* Edit mode is about to be entered. Return FALSE to abort.*/
	virtual BOOL OnEnterEditMode() { return TRUE; }

	//@cmember
	/* Edit mode/code view is about to be entered. Return FALSE to abort.*/
	virtual BOOL OnEnterCodeMode() { return TRUE; }

	//@cmember
	/* Create runtime form scripting object.*/
	TOOLKIT_API virtual SECAFormObj* OnCreateFormObject(CRuntimeClass* pRuntimeClass);

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECScriptHostDoc)

public:
	TOOLKIT_API virtual BOOL OnNewDocument();
	TOOLKIT_API virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	TOOLKIT_API virtual ~SECScriptHostDoc();
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(SECScriptHostDoc)
	TOOLKIT_API afx_msg void OnEditTest();
	TOOLKIT_API afx_msg void OnRun();
	TOOLKIT_API afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnFileSaveAs();
	TOOLKIT_API afx_msg void OnToggleView();
	TOOLKIT_API afx_msg void OnUpdateToggleView(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateRun(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(SECScriptHostDoc)
	TOOLKIT_API afx_msg void Caption(LPCTSTR strCaption);
	//}}AFX_DISPATCH
	TOOLKIT_DECLARE_DISPATCH_MAP()
	TOOLKIT_DECLARE_INTERFACE_MAP()

public:
	TOOLKIT_API virtual BOOL IsModified();
	TOOLKIT_API virtual void SetModifiedFlag(BOOL bModified = TRUE);
	TOOLKIT_API virtual void SetModified (BOOL bModified = TRUE);    // modifies the doc

protected:
	TOOLKIT_API virtual HRESULT Run();
	TOOLKIT_API virtual void    ClearAllItems();	//remove all doc's items and update the view
	TOOLKIT_API virtual BOOL    SaveItems();		//serializes items to a temporary file
	TOOLKIT_API virtual BOOL    LoadItems();		//""
	TOOLKIT_API virtual void    ReportSaveLoadException( LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault );
	TOOLKIT_API virtual BOOL    OnSaveDocument( LPCTSTR lpszPathName );
	TOOLKIT_API virtual BOOL    OnOpenDocument( LPCTSTR lpszPathName );
	TOOLKIT_API virtual void	OnCloseDocument();
	TOOLKIT_API virtual void    SaveFramePos();		//frame interaction
	TOOLKIT_API virtual void    RestoreFramePos();	//""
	TOOLKIT_API virtual void    ReplaceView(CRuntimeClass* pViewClass, CFrameWnd* pFrame); //this version has only one view. future versions might have several views separated by splitter
	TOOLKIT_API virtual SECAFormObj* InternalGetForm();

protected:
	TOOLKIT_API virtual HRESULT AddEmbeddedObjects(); //make things like 'form' and 'doc' visible to the script
	TOOLKIT_API virtual HRESULT GetDesignedObjects (/*in out*/CArray < SECAObjectDef, SECAObjectDef& > &objectDefs);
	TOOLKIT_API virtual HRESULT CreateActiveObjects( const	  CArray < SECAObjectDef, SECAObjectDef& > &objectDefs);
	TOOLKIT_API virtual HRESULT SavePersistantState( const SECACtrlItem *pItem,
										 COleStreamFile **pPersistFile );


	SECAContainerProps       m_contProps;	//attributes of a form (VBScript or JScript, form size, form name, etc.)
	SECAFormObj			    *m_pForm;	    //event firable item (ole control)
	SECAScriptHost	        *m_pScriptHost;//active engine host. can be used by itself.
	ScriptMode			     m_Mode;		//run or design
	CString				     m_Script;		//serializable
	CString				     m_strTempPathName; //temporarily created file
	BOOL				     m_fLoadingDocument;//are we in a loading state ?
	SECScriptHostDocDummyWnd m_wndError;	// error notification window
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SEC_SCRIPTHOSTDOC_H_

/////////////////////////////////////////////////////////////////////////////

