///////////////////////////////////////////////////////////////////////////////
// ScriptHost.h
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
// UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef _SCRIPTHOST_H
#define _SCRIPTHOST_H

#include <afxtempl.h>
#include <ActivScp.h>
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

///////////////////////////////////////////////////////////////////////
extern const CLSID CLSID_VBScript_local;

class SECAObjectDef
{	
public: 
		inline SECAObjectDef() { m_pPersist = NULL; m_dwStyle = WS_CHILD; }

		enum { psStream, psStorage };

		//control attributes needed for creation
		CString m_clsid;		//{...}
		CString m_name;			//name to appear in the script
		CRect   m_cont_rect;	//position in the conatiner window

		//persistant state ----------------------------------------+
		int				m_ptType;		
		COleStreamFile *m_pPersist;

		//style
		DWORD m_dwStyle;
};

///////////////////////////////////////////////////////////////////////
//@doc IActiveScriptErrorHandler 
//@mfunc HRESULT  | IActiveScriptErrorHandler | HandleError | Scripting error pure virtual callback
//@parm  IActiveScriptError | *perr | a pointer to the error
//@xref <c IActiveScriptError>
//@comm This function has no default implementation and must be overridden

//@doc IActiveScriptErrorHandler 
//@class Scripting Error handler interface
//@comm Base interface to receive Active Scripting runtime error notifications.
class IActiveScriptErrorHandler
{
public:
	//@cmember
	/* Scripting error pure virtual callback*/
	virtual HRESULT HandleError( IActiveScriptError *perr ) = 0;
};
//---------------------------------------------------------------------

//@doc SECScriptHostDoc 
//@class ActiveScript document class
//@BASE public | IActiveScriptSite
//@BASE public | IActiveScriptSiteWindow
//@comm MFC encapsulation of the IActiveScriptSite and IActiveScriptSiteWindow COM interfaces to hook scripting capability to your MFC application.

class SECAScriptHost : public IActiveScriptSite, 
					   public IActiveScriptSiteWindow
{ 
public:

  //@access Construction/Initialization

  //@cmember
  /* Construction*/
  TOOLKIT_API SECAScriptHost( IActiveScriptErrorHandler *phandler=NULL );
  TOOLKIT_API virtual ~SECAScriptHost();

  // This overload is provided for convenience when using SECAScriptHost
  // directly in your app and you want to use VBScript or JScript

  //@access Operation

  //@cmember,menum
  /* ScriptLang - available scripting languages*/
  enum ScriptLang { 
	                VBScript,		//@@emem VBScript scripting language
	                 JScript		//@@emem JavaScript scripting language
	};

  //@cmember
  /* Create the scripting engine of choice.*/
  TOOLKIT_API virtual HRESULT CreateScriptEngine( CLSID clsidEngine );

  //@cmember
  /* Create the scripting engine of choice*/
  TOOLKIT_API virtual HRESULT CreateScriptEngine(ScriptLang lang);

  //@cmember
  /* Destroy the current scripting engine*/
  TOOLKIT_API virtual HRESULT DestroyScriptEngine();

  //@cmember
  /* Add a top-level OLE automation object to this script*/
  TOOLKIT_API virtual HRESULT AddTopLevelItem(LPCOLESTR pstrItemName, LPDISPATCH lpDisp, 
                                              CWnd *pItemWnd = NULL, 
                                              DWORD dwItemFlags = SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE );

  //@cmember
  /* Parse script in specified file*/
  TOOLKIT_API virtual HRESULT ParseFile(TCHAR *pszFileName, LPCOLESTR pstrItemName = NULL);

  //@cmember
  /* Parse script in specified buffer*/
  TOOLKIT_API virtual HRESULT ParseBuffer( const TCHAR *pszBuffer, UINT sizeBuffer, LPCOLESTR pstrItemName = NULL);

  //@cmember
  /* Set the current script state*/
  TOOLKIT_API virtual HRESULT SetScriptState( SCRIPTSTATE  ss = SCRIPTSTATE_CONNECTED );

  //@cmember
  /* Get the current script state*/
  TOOLKIT_API virtual HRESULT GetScriptState( SCRIPTSTATE *ss );

  //@cmember
  /* Set the host window for script execution*/
  inline virtual HRESULT SetHostWindow( HWND hWnd ) { m_hWnd = hWnd; return S_OK; }

  //@cmember
  /* Set the host window for script execution*/
  TOOLKIT_API virtual HRESULT SetHostWindow( CWnd* pWnd);

  CTypedPtrMap<CMapStringToPtr, CString, IDispatch *> m_TopObjects;
  CTypedPtrMap<CMapStringToPtr, CString, CWnd	   *> m_ItemWnds;
  LPDISPATCH GetItemDispatch( LPCOLESTR pstrName ); //does not addref

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);

protected:

  // *** IActiveScriptSite methods ***
  STDMETHOD(GetLCID)(LCID *plcid);
  STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown **ppiunkItem, ITypeInfo **ppti);
  STDMETHOD(GetDocVersionString)(BSTR *pszVersion);
  STDMETHOD(RequestItems)(void);
  STDMETHOD(RequestTypeLibs)(void);
  STDMETHOD(OnScriptTerminate)(const VARIANT *pvarResult, const EXCEPINFO *pexcepinfo);
  STDMETHOD(OnStateChange)(SCRIPTSTATE ssScriptState);
  STDMETHOD(OnScriptError)(IActiveScriptError *pscripterror);
  STDMETHOD(OnEnterScript)(void);
  STDMETHOD(OnLeaveScript)(void);

  // *** IActiveScriptSiteWindow methods ***
  STDMETHOD(GetWindow)(HWND *phwnd);
  STDMETHOD(EnableModeless)(BOOL fEnable);

  IActiveScript				*m_ps;
  IActiveScriptParse		*m_psp;
  IActiveScriptErrorHandler *m_pErrHandler;

  CLSID         m_clsidEngine;
  HWND			m_hWnd;
  ULONG			m_cref;

  //parsing helpers
  TOOLKIT_API static ULONG	s_srcOffset;
  TOOLKIT_API static char  *s_pszError;
  friend TOOLKIT_API void   SkipWhite( char **ppsz,  BOOL fSkipNewLines );
  friend TOOLKIT_API int    FindToken( char *pszCur, char **ppszBeginArg, char **ppszNextLine, HRESULT *phr, char   **ppszError);
};

/////////////////////////////////////////////////////////////////////////////

TOOLKIT_API HRESULT GetEventTypeInfo(IUnknown *pObject, ITypeInfo **pTypeInfo);

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

TOOLKIT_API HRESULT CheckTypeInfo(LPOLEOBJECT lpObject);

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////
#endif

