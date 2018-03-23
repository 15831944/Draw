///////////////////////////////////////////////////////////////////////////////
// WBUtilFuncs.h : Utility Functions while working with the DHTML and WebBrowser control
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
// Description:  Declaration of Utility Functions
//

#ifndef __SEC_IEUTILFUNCS_H
#define __SEC_IEUTILFUNCS_H

#include <mshtml.h>
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

//@enum HTML retrieval type
typedef enum _SEC_SaveHTMLTypes {
	SEC_SAVEVIA_CACHEFILE	= 0x01,	//@emem Retrieve the correponding file in the cache
	SEC_SAVEVIA_IPERSISTFILE	= 0x02,	//@emem Retreive the rendered HTML (with scripts expanded).
	SEC_SAVEVIA_DOM	= 0x04,	//@emem Retrieve the HTML with the latest changes made via the DOM.
	SEC_SAVE_RECURSIVELY_WITH_SUBDIRINFO	= 0x80,	//@emem Retrieve recursively including the links (applied only when retrieving from cache)
	SEC_SAVE_RECURSIVELY_WITHOUT_SUBDIRINFO	=	0x40,//@emem No recursive retrieval
} SEC_SaveHTMLTypes;

#define BEGIN_HTML_DDX(bSave, pBrowser)	\
{	\
	BOOL save = bSave;	\
	IHTMLDocument2* pDoc;	\
	\
	HRESULT hr = pBrowser->get_Document(CDelayedDispAssignInDestructor_T<IHTMLDocument2*, &IID_IHTMLDocument2>(pDoc));	\
	\
	if(SUCCEEDED(hr))	\
	{	

#define END_HTML_DDX()	\
	}	\
}	


#define DDX_HTML_Text(htmlElem, fnInHtmlElem, string)	\
{	\
	IHTMLElement* pElem = FindElement(htmlElem, pDoc);		\
	if(pElem)	\
	{	\
		if(save)	\
		{	\
			BSTR bstr;	\
			if(SUCCEEDED(pElem->get_##fnInHtmlElem(&bstr)))	\
				string = CString(bstr);	\
		}	\
		else	\
			pElem->put_##fnInHtmlElem(string.AllocSysString());	\
		pElem->Release();	\
	}	\
}
	
#define DDX_HTML_Attrib(htmlElem, strAttrName, varValue, bCase)	\
{	\
	IHTMLElement* pElem = FindElement(htmlElem, pDoc);		\
	if(pElem)	\
	{	\
		if(save)	\
			pElem->getAttribute(CComBSTR(strAttrName), 0L, &varValue);	\
		else	\
			pElem->setAttribute(CComBSTR(strAttrName), varValue, bCase);	\
		pElem->Release();	\
	}\
}

template <class T, const IID* _IID>
class CDelayedDispAssignInDestructor_T
{
public:
	CDelayedDispAssignInDestructor_T(T& spDest)
		:m_spDest(spDest){m_pDispatch = NULL;};
	~CDelayedDispAssignInDestructor_T()
	{
		if(m_pDispatch)
		{
			m_pDispatch->QueryInterface(*_IID, (void**)&m_spDest); m_pDispatch->Release();
		}
	}

	operator IDispatch**(){return &m_pDispatch;}

	IDispatch* m_pDispatch;
	T& m_spDest;
};

//@doc ISearchLogic 
//@mfunc virtual BOOL | ISearchLogic | ExamineBrowser | WalkAndExamineIEBrowsers calls this virtual to check if the required
// browser was found.
//@parm IWebBrowser2* | pBrowser | A reference to the browser control which is to be examined.
//@rdesc Returns TRUE if found, FALSE otherwise
//
//@class ISearchLogic is an interface that the WalkAndExamineIEBrowsers function
// uses to determine if a HWND and a WebBrowser control are related. Take a look at
// CFindWBCtrlFromHWND which is an implementation of this interface.
//@xref <c CFindWBCtrlFromHWND>
class ISearchLogic
{
public:
	//@cmember
	/* Encloses the logic to check if the required browser was found.*/
	TOOLKIT_API virtual BOOL ExamineBrowser(IWebBrowser2* pBrowser) = 0;
};

//@doc CFindWBCtrlFromHWND
//@mdata IWebBrowser2* | CFindWBCtrlFromHWND | m_pBrowser | A reference to the resultant
// Web Browser control is stored in this member.
//@xref <c CFindWBCtrlFromHWND>
//
//@mfunc  | CFindWBCtrlFromHWND | CFindWBCtrlFromHWND | Constructor
//@parm HWND | hwnd | The hwnd whose corresponding browser control is to be found.
//
//@doc CFindWBCtrlFromHWND 
//@class CFindWBCtrlFromHWND encapsulates the logic that retrieves a web browser control that is
// a child (not necessarily immediate) of the specified HWND. It traverses the browser HWND's 
// parent-child relation hierarchy upwards and sees if any of its parent HWND matches the specified
// HWND.
// This class is used in conjunction with the WalkAndExamineIEBrowsers utility function to traverse
// the IShellWindows array and determine the Web Browser control related to the specified HWND.
// Take a look at the Toolkit\Pro\WBExtSample for an illustration of the usage of this class.
//@base public | ISearchLogic
class CFindWBCtrlFromHWND : public ISearchLogic
{
public:
	//@cmember
	/* Constructor. */
	TOOLKIT_API CFindWBCtrlFromHWND(HWND hwnd):m_hWnd(hwnd){m_pBrowser = NULL;};

	TOOLKIT_API virtual BOOL ExamineBrowser(IWebBrowser2* pBrowser);

	//@cmember
	/* A reference to the resultant browser control.*/
	IWebBrowser2* m_pBrowser;
	
protected:
	HWND m_hWnd;
};

//@doc SECHtmlElemDesc 
//
//@mfunc void | SECHtmlElemDesc | SetTagName | Sets the tag name in the element description.
//@parm LPCTSTR | lpszTagname | The tag neme to be set.
//
//@mfunc CString& | SECHtmlElemDesc | GetTagName | Gets the tag name in the element description.
//@rdesc The tag name if any, could be empty if not set.
//
//@mfunc void | SECHtmlElemDesc | AddAttributeDesc | Adds an attribute name / value pair to the element description.
//@parm LPCTSTR | lpszAttr | The attribute name
//@parm LPCTSTR | lpszProp | The attribute value
//
//@mfunc BOOL | SECHtmlElemDesc | LookupAttribute | Lookup an attribute name / value pair in the element description.
//@parm LPCTSTR | lpszAttr | The attribute name
//@parm LPCTSTR | lpszProp | The attribute value
//@rdesc Returns TRUE if found, FALSE otherwise
//
//@class SECHtmlElemDesc Allows you to describe a HTML element. You can use this in fucntions
// like FindElement to find a element with the provided description. The description could
// be in the form of a tag name or Attribute Name and Value pairs.
//@comm See the WBExtSample in the \SAMPLES\TOOLKIT\PRO\WBEXTSAMPLE directory for a 
// demonstration of this class.
class SECHtmlElemDesc
{
public:
	inline SECHtmlElemDesc(){};

	//@cmember
	/* Sets the tag name in the element description.*/
	inline void SetTagName(LPCTSTR lpszTagname){strTagName = lpszTagname; strTagName.MakeLower();}
	//@cmember
	/* Add an attribute to the description. */
	inline void AddAttributeDesc(LPCTSTR lpszAttr, LPCTSTR lpszProp)
	{
		CString strKey = lpszAttr;
		strKey.MakeLower();
		mapAttrVsProp.SetAt(strKey, lpszProp);
	}

	//@cmember
	/* Lookup an attribute. */
	inline BOOL LookupAttribute(LPCTSTR lpszAttr, CString& strProp)
	{
		CString strKey = lpszAttr;
		strKey.MakeLower();
		return mapAttrVsProp.Lookup(strKey, strProp);
	}

	//@cmember
	/* Get the tag name of the element. */
	inline CString& GetTagName() { return strTagName; }
	
protected:
	CMapStringToString mapAttrVsProp;	
	CString strTagName;
};


// These classes retrieve some most frequently used interfaces from the IWebBrowser2 interface.

//@func HRESULT | GetWBBody | Retruns the BODY element of the underlying document
//@parm IWebBrowser2* | pBrowser | The browser whose BODY element is to be retrieved.
//@parm IHTMLElement*& | pBody | Out parameter where the Element will be returned.
//@rdesc Returns S_OK if successful or an Error code.
TOOLKIT_API HRESULT GetWBBody(IWebBrowser2* pBrowser, IHTMLElement*& pBody);

//@func HRESULT | GetWBAllCollection | Retruns the All Collection of the underlying document
//@parm IWebBrowser2* | pBrowser | The browser whose BODY element is to be retrieved.
//@parm IHTMLElementCollection*& | pColl | Out parameter where the Collection will be returned.
//@rdesc Returns S_OK if successful or an Error code.
TOOLKIT_API HRESULT GetWBAllCollection(IWebBrowser2* pWebBrowser, IHTMLElementCollection *& pColl);

//@func IHTMLEventObj* | GetCurrentEvent | Retruns the Current event object of the specified browser
//@parm IWebBrowser2* | pBrowser | The browser whose current event object is to be retrieved.
//@rdesc Returns a reference to the Event Object if found or NULL
TOOLKIT_API IHTMLEventObj* GetCurrentEvent(IWebBrowser2* pBrowser);

//@func IHTMLElement* | FindElement | Finds an IHTMLElement with the description provided
//@parm SECHtmlElemDesc& | elem | The description of an element.
//@parm IHTMLDocument2* | pHtmlDoc | The document in which to search for the element
//@rdesc Returns the element if found or NULL
//@xref <c SECHtmlElemDesc>
TOOLKIT_API IHTMLElement* FindElement(SECHtmlElemDesc& elem, IHTMLDocument2* pHtmlDoc);

//@func void | WalkAndExamineIEBrowsers | This utility function walks the registered IWebBrowser2 controls 
// in the Running Object Table via the IShellWindows interface and uses the ISearchLogic instance provided to
// examine every browser encountered. The parsing is as suggested in the MSDN article ID Q176792.
//@parm ISearchLogic* | pSearchLogic | A reference to an instance of ISearchLogic with some logic built in to
// determine the relationship of the browser to a HWND
//@xref <c ISearchLogic>
TOOLKIT_API void WalkAndExamineIEBrowsers(ISearchLogic* pSearchLogic);

//@func void | LoadWBViaIPersist | Loads the browser with HTML composed in memory
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control
//@parm BSTR | bstrHTML | The HTML to load the browser control with.
TOOLKIT_API void LoadWBViaIPersist(IWebBrowser2* pWebBrowser, BSTR bstrHTML);

//@func HRESULT | LoadWBViaIPersist | Loads the browser with HTML in a IStream instance. Used by LoadWBViaIPersist.
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control
//@parm IStream* | pStream | A reference to the IStream instance.
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT LoadWBFromStream(IWebBrowser2* pWebBrowser, IStream* pStream);

//@func HRESULT | OpenInWB | Opens a new URL in the specified Web Browser with the PostData and Headers.
//@parm BSTR | bstrUrl | The URL to open
//@parm BSTR | bstrPostData | Post data to be sent along with the URL
//@parm BSTR | bstrHeaders | Header data to be sent along with the URL
//@parm VARIANT | dispBrowser | An IDispatch reference to the browser control where the URL is opened.
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT OpenInWB(BSTR bstrUrl, BSTR bstrPostData, BSTR bstrHeaders, VARIANT dispBrowser);

// The following functions let you store the contents of a Web Browser document into a file.

//@func HRESULT | SaveWebOCIntoStream | Stores the HTML in the Web Browser document into an IStream instance. Used by
// SaveWBViaIPersistFile
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control.
//@parm IStream*& | pStream | The IStream instance into which the retrieved HTML is stored.
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT SaveWebOCIntoStream(IWebBrowser2* pWebBrowser, IStream*& pStream);

//@func HRESULT | SaveWBViaCache | Will provide you a copy of the corresponding html file stored in the cache.
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control.
//@parm BSTR | bstrFile | The file into which the retrieved HTML is stored.
//@parm BSTR | bstrDir | The directory path into which the files corresponding to the embedded links are stored.
//@parm int | nType | Use any of the following enumerations
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT SaveWBViaCache(IWebBrowser2* pWebBrowser, BSTR bstrFile, BSTR bstrDir, int nType);

//@func HRESULT | SaveWBViaCache | Will retrieve the HTML (with scripts expanded) as rendered by the Web Browser control.
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control.
//@parm BSTR | bstrFile | The file into which the retrieved HTML is stored.
//@parm BSTR | bstrDir | The directory path into which the files corresponding to the embedded links are stored.
//@parm int | nType | @xref <t HTML retrieval type>
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT SaveWBViaIPersistFile(IWebBrowser2* pWebBrowser, BSTR bstrFile, BSTR bstrDir, int nType);

//@func HRESULT | SaveWBViaCache | Will retrieve the HTML from the document with the latest updates made to the document.
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control.
//@parm BSTR | bstrFile | The file into which the retrieved HTML is stored.
//@parm BSTR | bstrDir | The directory path into which the files corresponding to the embedded links are stored.
//@parm int | nType | @xref <t HTML retrieval type>
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT SaveWBViaDOM(IWebBrowser2* pWebBrowser, BSTR bstrFile, BSTR bstrDir, int nType);

//@func HRESULT | SaveWBViaCache | Retrieve HTML into memeory. Uses SaveWBViaIPersistFile.
//@parm IWebBrowser2* | pWebBrowser | A reference to the Web Browser control.
//@parm BSTR* | pbstrHTML | Out parameter with the resultant HTML.
//@rdesc Returns S_OK if successful or the Error Code.
TOOLKIT_API HRESULT SaveWBViaIPersist(IWebBrowser2* pWebBrowser, BSTR* pbstrHTML);

TOOLKIT_API HRESULT SaveFileFromCacheFile(LPCTSTR strLocURL, LPCTSTR lpszFile);

TOOLKIT_API HRESULT SaveLinksToSourceFiles(IWebBrowser2* pWebBrowser, BSTR bstrLocURL, BSTR bstrDir, int nType);

TOOLKIT_API HRESULT ComposePostData(LPVARIANT pvPostData, LPCTSTR strPostData);

TOOLKIT_API BOOL GetCacheEntryInfo(LPTSTR lpszUrl, LPTSTR& lpszFileName);

TOOLKIT_API void ValidatePath(LPCTSTR lpszFilePath);

TOOLKIT_API BOOL GetFileModifyTime(const CString& FileName, COleDateTime& time);

TOOLKIT_API BOOL CompareFileTimeStamps(LPCTSTR lpszFile1, LPCTSTR lpszFile2);

TOOLKIT_API BOOL IsWndRelated(HWND hwnd1, HWND hwnd2);

TOOLKIT_API HRESULT Connect(IWebBrowser2* pBrowser, IDispatch* pDisp, DWORD* pdwCookie);

TOOLKIT_API HRESULT Disconnect(IWebBrowser2* pBrowser, DWORD* pdwCookie);

#pragma comment(lib, "Wininet.lib")

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	//__SEC_IEUTILFUNCS_H
