///////////////////////////////////////////////////////////////////////////////
// SECHtmlVw.h : Utility Functions while working with the DHTML and WebBrowser control
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
// Authors:      Praveen Ramesh
// Description:  Declaration of WebBrowser Extension Utility Classes

#ifndef _SEC_HTML_VIEW
#define _SEC_HTML_VIEW

#include <afxhtml.h>
#include <mshtmhst.h>
#include <mshtml.h>
#include <StingrayExportDefs.h>

// Make sure to compile this file with platform SDK.
#if _WIN32_IE < 0x0500
#pragma message("Warning: It appears that you are not linking to the latest Platform SDK. This is required for the latest XML DOM interfaces. Errors may result.")
#endif //_WIN32_IE < 0x0500

// The following 2 defines are missing in some versions of the Platform SDK and are declared here to help compile.

// NOTE: If multiple definitions of DBFILETIME are present, then you are using an older version of the SDK.
// Please upgrade to the April 2000 or a later version of the MS Platform SDK.
#pragma message("###########\r\nInformation: If you receive Error(s) C2065: DBFILETIME : undeclared identifier,\r\nremove the comments surrounding the code found in sechtmlvw.h!\r\n###########")
/*
typedef struct  tagDBFILETIME
    {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
    }	DBFILETIME;

#define	DBTYPE_DBFILETIME	137 
*/

#ifndef DISPID_DATASOURCE
#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT

#if (_MFC_VER < 0x0700)
	#include <transact.h>
	#include <..\src\occimpl.h>
#else
	#include <ocdb.h>
	#include <..\src\mfc\occimpl.h>	
	#include <afxocc.h>
#endif

#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT
#endif

#pragma warning(disable: 4100)

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


class CDocHostUIHandler : public IDocHostUIHandler
{
public:
	inline CDocHostUIHandler(CDocHostUIHandler* pRedirect = NULL):m_pRedirect(pRedirect){};

	TOOLKIT_API virtual STDMETHODIMP ShowContextMenu(DWORD,POINT*,IUnknown*,IDispatch*);
    TOOLKIT_API virtual STDMETHODIMP GetHostInfo(DOCHOSTUIINFO*);
    TOOLKIT_API virtual STDMETHODIMP ShowUI(DWORD,
                            IOleInPlaceActiveObject*,
                            IOleCommandTarget*,
                            IOleInPlaceFrame*,
                            IOleInPlaceUIWindow*);
    TOOLKIT_API virtual STDMETHODIMP HideUI();
    TOOLKIT_API virtual STDMETHODIMP UpdateUI();
    TOOLKIT_API virtual STDMETHODIMP EnableModeless(INT);
    TOOLKIT_API virtual STDMETHODIMP OnDocWindowActivate(INT);
    TOOLKIT_API virtual STDMETHODIMP OnFrameWindowActivate(INT);
    TOOLKIT_API virtual STDMETHODIMP ResizeBorder(LPCRECT,IOleInPlaceUIWindow*,INT);
    TOOLKIT_API virtual STDMETHODIMP TranslateAccelerator(LPMSG,const GUID*,DWORD);
    TOOLKIT_API virtual STDMETHODIMP GetOptionKeyPath(LPOLESTR*,DWORD);
    TOOLKIT_API virtual STDMETHODIMP GetDropTarget(IDropTarget*,IDropTarget**);
    TOOLKIT_API virtual STDMETHODIMP GetExternal(IDispatch**);
    TOOLKIT_API virtual STDMETHODIMP TranslateUrl(DWORD,OLECHAR*,OLECHAR**);
    TOOLKIT_API virtual STDMETHODIMP FilterDataObject(IDataObject*,IDataObject**);

	CDocHostUIHandler *m_pRedirect;
};

class SECOleControlSite : public COleControlSite
{
public:
	inline SECOleControlSite(COleControlContainer *pCnt = NULL, CDocHostUIHandler *pDestImp = NULL):COleControlSite(pCnt) 
		{ m_xDocHostUIHandler.m_pRedirect = pDestImp; }

protected:

// QA: 32167 - Toolkit Interface Map/Part
TOOLKIT_DECLARE_INTERFACE_MAP()
TOOLKIT_BEGIN_INTERFACE_PART(DocHostUIHandler, CDocHostUIHandler)

// IDocHostUIHandler implementation in CDocHostUIHandler

END_INTERFACE_PART(DocHostUIHandler)

};


class SECOccManager : public COccManager
{
public:
	SECOleControlSite *m_pOleControlSite;
	CDocHostUIHandler *m_pDestImp;

	inline SECOccManager(CDocHostUIHandler *pDestImp = NULL) { m_pOleControlSite = NULL; m_pDestImp = pDestImp;}

	inline COleControlSite* CreateSite(COleControlContainer* pCtrlCont)
	{
		m_pOleControlSite = new SECOleControlSite(pCtrlCont, m_pDestImp);
		return m_pOleControlSite;
	};
};

//@doc SECHTMLView 
//@class SECHTMLView derives from the MFC CHtmlView and provides you default virtual handlers 
// for IDocHostUIHandler which you just have to override in your derived class if necessary.
// Use this class in conjunction with the Utility functions provided in WBUtilFuncs.h for a 
// powerful and easy way to automate the Web Browser control in your MFC applications.
// See the WBExtSample in the \SAMPLES\TOOLKIT\PRO\WBEXTSAMPLE directory for code samples
// on the usage of this class and how to set up event handlers for specific HTML elements using the
// EventSink available in the default IOleControlSite implementation.
//@base public | CHtmlView
//@base public | CDocHostUIHandler
class SECHTMLView : public CHtmlView, public CDocHostUIHandler
{
protected:
	inline SECHTMLView(){m_pROccManager = new SECOccManager(this);};
	virtual ~SECHTMLView(){if(m_pROccManager)delete m_pROccManager;};
	TOOLKIT_DECLARE_DYNCREATE(SECHTMLView);

public:

	// Dummy implementation for IUnknown inherited via CDocHostUIHandler
	// This should never be called
	inline STDMETHOD_(ULONG, AddRef)(){return 0;}; 
	inline STDMETHOD_(ULONG, Release)(){return 0;}; 
	inline STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj){return NULL;}; 

	TOOLKIT_API virtual void OnDocumentComplete(LPCTSTR lpszURL);

	TOOLKIT_API virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext);

#if( _MFC_VER >= 0x0700 )
	TOOLKIT_API virtual BOOL CreateControlSite( COleControlContainer* pContainer, COleControlSite** ppSite, UINT nID, 
									REFCLSID clsid);
#endif

	SECOccManager* m_pROccManager;

};


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	//__SEC_IEUTILFUNCS_H


