///////////////////////////////////////////////////////////////////////////////
// XMLDomDoc.h : SECXMLDocument
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
// Authors:      Praveen Ramesh and Prakash Surendra
// Description:  Wrapper class for the IE XML DOM
//

#ifndef __SFL_XMLDOMDOC_H__
#define __SFL_XMLDOMDOC_H__

#include <comdef.h>

#ifdef NTDDI_VERSION
	//---------------------------------------------------------------
	// NOTE: msxml.h is no longer used on the Windows Vista platform. 
	// Use msxml6.h instead. 
	// 
	// To use MSXML6, make sure that NTDDI_VERSION is defined as 
	// NTDDI_VISTA on Windows Vista platforms and that the MSXML6 SDK 
	// is installed and pathed correctly. 
	//---------------------------------------------------------------
	#if NTDDI_VERSION >= NTDDI_VISTA
		// MSXML 6.0 SDK
		#include <msxml6.h>
	#else
		#include <msxml.h>
	#endif
#else
	#include <msxml.h>
#endif

#include <stdio.h>
#include <map>
#include <foundation\persistence\FileStream.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace stingray {
	namespace foundation {

/////////////////////////////////////////////////////////////////////////////
// COtlXmlDocument

// Macro for calling IUnknown::Release on map contents
#define RELEASE_MAPREFERENCES(x) \
	for(XMLTagMap::iterator itPos = x.begin(); itPos != x.end(); itPos++) \
			(*itPos).second->Release(); \


///////////////////////////////////////////////////////////////////////////
//@doc SECXMLDocument
//
//@mfunc | SECXMLDocument  | SECXMLDocument | Constructor
//@parm LPTSTR  | strRootTag | The name of the root tag (useful only while writing to an XML file)
//@parm LPTSTR  | strHeader | Any header info to be written into the XML file to be created.
//
//@mfunc | SECXMLDocument  | SECXMLDocument | Default Constructor
//@comm If you use this constructor to create the class, make sure to call Create or Attach to initialize the class properly.
//
//@mfunc HRESULT | SECXMLDocument  | Create | Call this function directly if you created the class using the default constructor.
//@rdesc Returns S_OK if successful, or else the error code.
//@parm LPTSTR  | strRootTag | The name of the root tag (useful only while writing to an XML file)
//@parm LPTSTR  | strHeader | Any header info to be written into the XML file to be created.
//
//@mfunc void | SECXMLDocument | Attach | Attach to an exisiting document. Use this instead of Create.
//@parm IXMLDOMDocument*  | pDoc | The document to which this class is to be attached to.
//
//@mfunc BOOL | SECXMLDocument | FindTextTag | Find the specified tag and return a bstr value for the first text child.
// Make sure to call LoadMap or MapElements before using.
//@rdesc Returns TRUE if successful, FALSE if no such tag was found in the currently loaded map.
//@syntax FindTextTag(const _bstr_t& strTag, _bstr_t& strValue)
//@syntax FindTextTag(const _bstr_t& strTag, CComVariant& vVal, VARTYPE vt)
//@parm const _bstr_t&  | strTag | The tag name of the element to be found.
//@parm _bstr_t&  | strValue | The out parameter with the search result.
//@parm CComVariant&  | vVal | The out parameter with the search result.
//@parm VARTYPE  | vt | The desired type of variant in the out parameter.
//
//@mfunc BOOL | SECXMLDocument | FindElementTag | Find the IXMLDOMNode pointer that matches the specified tag.
// Make sure to call LoadMap or MapElements before using.
//@rdesc Returns TRUE if successful, FALSE if no such tag was found in the currently loaded map.
//@parm const _bstr_t&  | strTag | The tag name of the element to be found.
//@parm IXMLDOMNode**  | ppElement | The out parameter with the search result.
//
//@mfunc void | SECXMLDocument | ClearMap | Calls IUnknown::Release (optionally) on all the map elements and 
// then erases the contents of the map
//@parm BOOL  | bRelease | Indicates whether Release should be called on the map elements before the map gets erased.
//
//@mfunc BOOL | SECXMLDocument | LoadMap | Populate the map with tagname, IXMLDOMElement values under the root tag.
// This function just calls MapElements with the root element.
//@rdesc Returns TRUE if successful, FALSE if mapping unsuccessful.
//
//@mfunc BOOL | SECXMLDocument | MapElements | Builds the tagname/element map for the elements under the specified element.
//@rdesc Returns TRUE if successful, FALSE if mapping unsuccessful.
//@parm IXMLDOMNode*  | pNode | The element whose children are to be mapped.
//@parm BOOL  | bRecurse | Indicates whether only the immediate children are to be mapped on recurse deeper.
//
//@mfunc void | SECXMLDocument | Destroy | Releases the msmxml parser.
//@rdesc void
//
//@mfunc HRESULT | SECXMLDocument | LoadFromFile | Populate from an existing XML file. Use this method to initialize
// this class when reading an XML file.
//@rdesc Returns S_OK if successful, the error code otherwise.
//@parm LPTSTR  | strFileName | The XML file name.
//
//@mfunc HRESULT | SECXMLDocument | SaveToFile | Save to an XML file. Call this when you are done writing into this class.
//@rdesc Returns S_OK if successful, the error code otherwise.
//@parm LPTSTR  | strFileName | The XML file name.
//
//@mfunc HRESULT | SECXMLDocument | AddTag | Adds a node of the specified type to the specified parent element.
//@rdesc Returns S_OK if successful, the error code otherwise
//@parm LPTSTR  | strTagName | The tag name of the child element to be created.
//@parm long  | nType | The type of element to be created. Either one of NODE_ELEMENT, NODE_TEXT, NODE_CDATA_SECTION.
//@parm IXMLDOMNode**  | ppRetVal | The out parameter where a reference to the newly created element is returned. Can be NULL.
//@parm IXMLDOMNode*  | pParent | The parent element under which to create the new child element. 
// If null, uses the root element of the document.
//
//@mfunc HRESULT | SECXMLDocument | AddTextTag | Adds an element with a text child element to the specified parent.
//@rdesc Returns S_OK if successful, the error code otherwise
//@parm LPTSTR  | strTagName | The tag name of the child element to be created.
//@parm LPTSTR  | strText | The text value of the child.
//@parm long  | nType | The type of element to be created. Either one of NODE_ELEMENT, NODE_TEXT, NODE_CDATA_SECTION.
//@parm IXMLDOMNode**  | ppRetVal | The out parameter where a reference to the newly created element is returned. Can be NULL.
//@parm IXMLDOMNode*  | pParent | The parent element under which to create the new child element. 
// If null, uses the root element of the document.
//@comm The resultant XML would look like this:
// <lt>pParentTag<gt>
//	<lt>strTagName<gt>
//		strText
//	<lt>/strTagName<gt>
// <lt>/pParentTag<gt>
//
//@mfunc HRESULT | SECXMLDocument | SetAttribute | Sets the attribute for the specified element.
//@rdesc Returns S_OK if successful, the error code otherwise
//@parm IXMLDOMNode*  | pNode | The element whose attribute is to be set.
//@parm LPTSTR  | strName | The attribute name.
//@parm LPTSTR  | strValue | The attribute value.
//
//@mfunc BOOL | SECXMLDocument | GetTextTag | Get the text value of the first child of the specified element.
//@rdesc Returns TRUE if successful, FALSE otherwise.
//@parm IXMLDOMNode*  | pNode | The element whose text child is to be found.
//@parm BSTR&  | strTag | The out parameter with the value of the child.
//
//@class SECXMLDocument | The SECXMLDocument class provides a simplified method for creating and reading XML files and 
// editing their content. 
//
//@comm The class requires the latest XML DOM runtime (provided with IE 5 and above)
// and the latest Platform SDK for the latest XML DOM interface defenitions.<nl>
// We use this class in our implementation of the SECXMLDOMArchive class, take a look at the source code 
// of this class for usage pattern.<nl>
// At any time this class maintains a map of child element tagnames of any node in the document hierarchy and
// a reference to their corresponding XML DOM interfaces. This way when you query for a child element 
// within that node, the retrieval is very fast.
//
class SECXMLDocument
{
public:
	typedef std::map<_bstr_t, IXMLDOMNode*, std::less<_bstr_t> > XMLTagMap;
	CComPtr<IXMLDOMDocument> m_sipDoc;
	XMLTagMap m_map;

public:
	// construct and create a document

	//@cmember
	/* Default constructor. */
	inline SECXMLDocument(){}

	//@cmember
	/* Initialization constructor. */
	inline SECXMLDocument(LPTSTR strRootTag, LPTSTR strHeader=NULL)
	{
		HRESULT hr = Create(strRootTag, strHeader);
		if(hr != S_OK)
			AfxThrowOleException(hr);
	}

	
	inline virtual ~SECXMLDocument()
	{
		// Call ClearMap() so that the cached interface pointers can be released
		if(!m_map.empty())
			ClearMap();

		// QA: 32054
		m_sipDoc.Release();
	}

	//@cmember
	/* Creates an empty document with a root tag. */
	inline HRESULT Create(LPTSTR strRootTag, LPTSTR strHeader=NULL)
	{
		USES_CONVERSION;
		HRESULT hr = E_FAIL;
		if(!strHeader)
			strHeader = _T("");

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		// Load MSXML 6.0 Interface. Requires the MSXML 6.0 SDK.
		if(FAILED(hr = CoCreateInstance( __uuidof(DOMDocument60), // Refers to CLSID_DOMDocument60
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(IXMLDOMDocument3), // Refers to IID_IXMLDOMDocument3
			reinterpret_cast<void**>(&m_sipDoc))))
			return hr;
	#else
		if(FAILED(hr = CoCreateInstance(CLSID_DOMDocument, 
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IXMLDOMDocument,
			reinterpret_cast<void**>(&m_sipDoc))))
			return hr;

	#endif
#else
		if(FAILED(hr = CoCreateInstance(CLSID_DOMDocument, 
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IXMLDOMDocument,
			reinterpret_cast<void**>(&m_sipDoc))))
			return hr;


#endif

		// Create Document with supplied headers...

		// Append a dummy body to the headers for the below call to work
		_bstr_t header = T2OLE(strHeader);
		header += T2OLE(_T("<body></body>"));

		VARIANT_BOOL bSuccess;
		if(FAILED(m_sipDoc->loadXML(header, &bSuccess)))
		{
			// QA: 32054
#if _MSC_VER >= 1400
			::SysFreeStringHelper(header);
#else
			::SysFreeString(header);
#endif
			return hr;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		::SysFreeStringHelper(header);
#else
		::SysFreeString(header);
#endif

		// Create the root element
		CComPtr<IXMLDOMElement> siRootElem;

		hr = m_sipDoc->createElement(T2OLE(strRootTag), (IXMLDOMElement**)&siRootElem);
		
		if(FAILED(hr))
		{
			// QA: 32054
			siRootElem.Release();

			return hr;
		}

		m_sipDoc->putref_documentElement(siRootElem);

		m_sipDoc->put_async((VARIANT_BOOL)FALSE);	// Our default mode of using the IXMLDOMDocument

		// QA: 32054
		siRootElem.Release();

		return S_OK;
	}

	//@cmember
	/* Finds a tag and return a bstr value for the first text child. */
	inline BOOL FindTextTag(const _bstr_t& strTag, _bstr_t& strValue)
	{
/*		TCHAR* strUpper = strTag;
		for( ; strUpper<(TCHAR*)strTag+strTag.length(); strUpper++ )
		{
			if(_istlower(*strUpper)!=0)
				*strUpper = _totupper(*strUpper);
		}
		_bstr_t bstrUpper = strUpper-strTag.length();
*/
		XMLTagMap::iterator it;
		if( ( it = m_map.find(strTag)) != m_map.end() )
		{
			BSTR bstr;
           	if( GetTextTag((*it).second, bstr) )
			{
				strValue = bstr;
#if _MSC_VER >= 1400
				::SysFreeStringHelper(bstr); // QA: 31948 
#else
				::SysFreeString(bstr);
#endif
				return TRUE;		
			}
		}
		return FALSE;
	}

	//@cmember
	/* Finds the IXMLDOMNode pointer that matches the tag. */
	inline BOOL FindElementTag(const _bstr_t& strTag, IXMLDOMNode** ppElement)
	{
/*		TCHAR* strUpper = strTag;
		for( ; strUpper<(TCHAR*)strTag+strTag.length(); strUpper++ )
		{
			if(_istlower(*strUpper)!=0)
				*strUpper = _totupper(*strUpper);
		}
		_bstr_t bstrUpper = strUpper-strTag.length();
*/

		XMLTagMap::iterator it;
		if( ( it = m_map.find(strTag)) != m_map.end() )
		{
			*ppElement = (*it).second;
			return TRUE;
		}
		return FALSE;
	}

	//@cmember
	/* Finds a tag and returns a variant representation of the first child. */
	inline BOOL FindTextTag(const _bstr_t& strTag, CComVariant& vVal, VARTYPE vt)
	{
		switch(vt)
		{
		case VT_DISPATCH:
			{
				IXMLDOMNode* pElement = NULL;
				if( FindElementTag(strTag, &pElement) )
				{
					vVal = (IDispatch*)pElement;
					if(FAILED(vVal.ChangeType(vt)))
						return FALSE;
					return TRUE;
				}
				break;
			}
		default:
			{
				
				_bstr_t strVal;
				if(FindTextTag(strTag, strVal))
				{
					vVal = (BSTR)strVal;
#if _MSC_VER >= 1400
					::SysFreeStringHelper(strVal); // QA: 31948
#else
					::SysFreeString(strVal);
#endif
					if(FAILED(vVal.ChangeType(vt)))
						return FALSE;
					return TRUE;
				}
				break;
			}
		}
		return FALSE;
	}


	//@cmember
	/* Clears all elements of the map. */
	inline void ClearMap(BOOL bRelease = TRUE)
	{
		// Call IUnknown::Release on all the map elements and then erase the contents of the map
		// IUnknown::Release decrements the reference count for the calling interface on a object. 
		// If the reference count on the object falls to 0, the object is freed from memory
		if(bRelease)
			RELEASE_MAPREFERENCES(m_map)
		m_map.erase(m_map.begin(), m_map.end());
	}

	//@cmember
	/* Populates the text tag map with tagname,textchild values. */
	inline BOOL LoadMap()
	{
		ClearMap();
		ASSERT(m_sipDoc);
		CComPtr<IXMLDOMNode> sipRoot;
		HRESULT hr = GetDocument()->get_documentElement((IXMLDOMElement**)&sipRoot);
		if(FAILED(hr))
		{
			// QA: 32054
			sipRoot.Release();
			return FALSE;
		}
		// enumerate all element tags and add to the list
		if(MapElements(sipRoot))
		{
			// QA: 32054
			sipRoot.Release();
			return TRUE;
		}
		// QA: 32054
		sipRoot.Release();

		return FALSE;
	}

	
	//@cmember
	/* Builds the element map starting with the 'pRoot' parameter as the root element. */
	inline BOOL MapElements(IXMLDOMNode* pRoot, BOOL bRecurse = TRUE)
	{
		// If the map is not empty, then first clear the contents
		if(!m_map.empty())
			ClearMap();

		return BuildMap(pRoot, bRecurse);		
	}

	// Recursive helper used by the MapElements()
	inline BOOL BuildMap(IXMLDOMNode* pRoot, BOOL bRecurse = TRUE)
	{
		CComPtr<IXMLDOMNodeList> sipChildren;
		HRESULT hr = pRoot->get_childNodes(&sipChildren);
		if (FAILED(hr) || !sipChildren)
		{
			// QA: 32054
			sipChildren.Release();
			return FALSE;
		}

		long nChildren;
		if(FAILED(sipChildren->get_length(&nChildren)))
		{
			// QA: 32054
			sipChildren.Release();
			return FALSE;
		}
		
		for ( long i = 0;  i < nChildren;  ++i ) 
		{
			CComPtr<IXMLDOMNode> sipChild;
			HRESULT hr;
			if(FAILED(hr = sipChildren->get_item(i, &sipChild)))
			{
				// QA: 32054
				sipChildren.Release();
				sipChild.Release();

				return FALSE;
			}
			long lType;
			if(FAILED(sipChild->get_nodeType((tagDOMNodeType *)&lType)))
			{
				// QA: 32054
				sipChildren.Release();
				sipChild.Release();

				return FALSE;
			}
			if(lType == NODE_ELEMENT)
			{
				BSTR strTagName;
				if(SUCCEEDED(sipChild->get_nodeName(&strTagName)))
				{
					ATLTRACE("ElementMapEntry: %S\t%p\n", strTagName, (IXMLDOMNode*)sipChild.p);
					m_map.insert(XMLTagMap::value_type( strTagName, (IXMLDOMNode*)sipChild.p));
					
				}
#if _MSC_VER >= 1400
				::SysFreeStringHelper(strTagName);// QA: 32054
#else
				::SysFreeString(strTagName);
#endif

				if( bRecurse )
					BuildMap(sipChild);
				
				// Detach the interface pointer from sipChild so that Release() is not called on IXMLDOMNode*
				sipChild.Detach();
			}
			// QA: 32054
			sipChild.Release();
		}

		// QA: 32054
		sipChildren.Release();

		return TRUE;
	}

	//@cmember
	/* Releases the msmxml parser. */
	inline void Destroy()
	{
		if(m_sipDoc)
		{
			// QA: 32054
			m_sipDoc.Release();
			m_sipDoc = NULL;
		}
	}

	//@cmember
	/* Attach to an existing document. */
	inline void Attach(IXMLDOMDocument* pDoc)
	{
		ASSERT(pDoc);
		if(m_sipDoc)
			Destroy();
		m_sipDoc = pDoc;
	}

	inline void Detach()
	{
		Destroy();
	}

	// returns the root element
	inline HRESULT GetRoot(IXMLDOMNode** ppRoot) 
	{
		ASSERT(m_sipDoc && ppRoot);
		*ppRoot = 0;
		return m_sipDoc->get_documentElement((IXMLDOMElement**)ppRoot);
	}
	
	//@cmember
	/* Populates from an existing XML file. */
	inline HRESULT LoadFromFile(LPTSTR strFileName)
	{
		CComVariant vaFile(strFileName);
		VARIANT_BOOL bSuccess; 
		HRESULT hr = m_sipDoc->load(vaFile, &bSuccess);
		// QA: 32054
#if _MSC_VER >= 1400
		vaFile.ClearToZero();
#else
		vaFile.Clear();
#endif

		if(hr == S_OK)
			ASSERT(bSuccess);	// Check the file path.
		
		return hr;
	}

	//@cmember
	/* Saves to an XML file. */
	inline HRESULT SaveToFile(LPTSTR strFileName)
	{
		CComVariant vaFileName(strFileName);

		HRESULT hr = m_sipDoc->save(vaFileName);
		// QA: 32054
#if _MSC_VER >= 1400
		vaFileName.ClearToZero();
#else
		vaFileName.Clear();
#endif

		return hr;
	}

	//@cmember
	/* Adds a generic node. */
	inline HRESULT AddTag(LPCTSTR strTagName, long nType, IXMLDOMNode** ppRetVal=NULL, IXMLDOMNode* pParent=NULL)
	{
		USES_CONVERSION;
		CComPtr<IXMLDOMNode> sipNode;
		CComVariant vType = nType;		
		CComBSTR bstrName;
		
		// second parameter can not be used for text elements, must call put_text instead
		if(nType == (long)NODE_ELEMENT)
			bstrName = T2COLE(strTagName);

		// create an element
		HRESULT hr;
		switch(nType)
		{
			case NODE_ELEMENT:
				{
				CComPtr<IXMLDOMElement> sipElem;
				if(FAILED(hr = m_sipDoc->createElement(bstrName, (IXMLDOMElement**)&sipElem)))
				{
					// QA: 32054
					sipNode.Release();
					sipElem.Release();

					return hr;
				}
				sipNode = sipElem;
				}
				break;

			case NODE_TEXT:
				{
				CComPtr<IXMLDOMText> sipText;
				if(FAILED(hr = m_sipDoc->createTextNode(bstrName, (IXMLDOMText**)&sipText)))
				{
					// QA: 32054
					sipNode.Release();
					sipText.Release();

					return hr;
				}
				sipNode = sipText;
				}
				break;

			case NODE_CDATA_SECTION:
				{
				CComPtr<IXMLDOMCDATASection> sipCDS;
				if(FAILED(hr = m_sipDoc->createCDATASection(bstrName, (IXMLDOMCDATASection**)&sipCDS)))
				{
					// QA: 32054
					sipNode.Release();
					sipCDS.Release();

					return hr;
				}
				sipNode = sipCDS;
				}
				break;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		::SysFreeStringHelper(bstrName);
		vType.ClearToZero();
#else
		::SysFreeString(bstrName);
		vType.Clear();
#endif

		// create as child of parent, or root if NULL parent
		CComPtr<IXMLDOMNode> sipParent;
		if( pParent )
			sipParent = pParent;
		else
			if(FAILED(hr = m_sipDoc->get_documentElement((IXMLDOMElement**)&sipParent)))
			{
				// QA: 32054
				sipNode.Release();
				sipParent.Release();

				return hr;
			}

		if(FAILED(hr = sipParent->appendChild(sipNode, NULL)))
		{
			// QA: 32054
			sipNode.Release();
			sipParent.Release();

			return hr;
		}

		// initialize the return value	
		if(ppRetVal)
		{
			*ppRetVal = sipNode;
			((IXMLDOMNode*)*ppRetVal)->AddRef();
		}

		// QA: 32054
		sipNode.Release();
		sipParent.Release();

		return hr;
	}
	
	//@cmember
	/* Adds an element with a text child element. */
	inline HRESULT AddTextTag(LPCTSTR strTagName, LPCTSTR strText, long nType, IXMLDOMNode** ppRetVal=NULL, IXMLDOMNode* pParent=NULL)
	{
		ASSERT(m_sipDoc);
		// create an element
		HRESULT hr;
		CComPtr<IXMLDOMNode> sipElem;
		if(FAILED(hr = AddTag(strTagName, (long)NODE_ELEMENT, &sipElem, pParent)))
		{
			// QA: 32054
			sipElem.Release();
			return hr;
		}

		// create a text element under the element
		CComPtr<IXMLDOMNode> sipText;
		if(FAILED(hr = AddTag(NULL, nType, &sipText, sipElem)))
		{
			// QA: 32054
			sipElem.Release();
			sipText.Release();

			return hr;
		}

		CComBSTR s(strText);

		if(FAILED(hr = sipText->put_text(s)))
		{
			// QA: 32054
#if _MSC_VER >= 1400
			::SysFreeStringHelper(s);
#else
			::SysFreeString(s);
#endif
			sipElem.Release();
			sipText.Release();

			return hr;
		}

		// initialize the return value	
		if(ppRetVal)
		{
			*ppRetVal = sipElem;
			((IXMLDOMNode*)*ppRetVal)->AddRef();
		}
		// QA: 32054
#if _MSC_VER >= 1400
		::SysFreeStringHelper(s);
#else
		::SysFreeString(s);
#endif
		sipElem.Release();
		sipText.Release();

		return hr;
	}

	//@cmember
	/* Adds an attribute to an element. */
	inline HRESULT SetAttribute(IXMLDOMNode* pNode, LPTSTR strName, LPTSTR strValue)
	{
		IXMLDOMElement* pElem = NULL;
	
		pNode->QueryInterface(IID_IXMLDOMElement, (void**)&pElem);

		ASSERT(pElem);
			// Call this only on an element type

		ASSERT(strName && strValue);

		CComBSTR bstrName = strName;
		CComVariant vValue = strValue;
		HRESULT hr = pElem->setAttribute(bstrName, vValue);

		// QA: 32054
#if _MSC_VER >= 1400
		::SysFreeStringHelper(bstrName);
#else
		::SysFreeString(bstrName);
#endif
		return hr;
	}

	// get the document interface pointer
	inline IXMLDOMDocument* GetDocument(){ return m_sipDoc;}
	
	//@cmember
	/* Gets the text value of the first child. */
	inline BOOL GetTextTag(IXMLDOMNode* pElement, BSTR& strTag)
	{
		ASSERT(pElement);
		CComPtr<IXMLDOMNodeList > sipChildren;
		HRESULT hr = pElement->get_childNodes(&sipChildren);
		if (FAILED(hr) || !sipChildren)
		{
			// QA: 32054
			sipChildren.Release();

			return FALSE;
		}

		long nChildren = 0;
		if(FAILED(sipChildren->get_length(&nChildren)) || nChildren < 1)
		{
			// QA: 32054
			sipChildren.Release();

			return FALSE;
		}
				
		CComQIPtr<IXMLDOMNode> sipChild;
		if(FAILED(sipChildren->get_item((long)0, &sipChild)))
		{
			// QA: 32054
			sipChildren.Release();
			sipChild.Release();

			return FALSE;
		}
		long lType;
		if(FAILED(sipChild->get_nodeType((tagDOMNodeType *)&lType)))
		{
			// QA: 32054
			sipChildren.Release();
			sipChild.Release();

			return FALSE;
		}
		if(lType != NODE_TEXT && lType != NODE_CDATA_SECTION)
		{
			// QA: 32054
			sipChildren.Release();
			sipChild.Release();

			return FALSE;		
		}

		if(FAILED(sipChild->get_text(&strTag)))
		{
			// QA: 32054
			sipChildren.Release();
			sipChild.Release();

			return FALSE;
		}
		// QA: 32054
		sipChildren.Release();
		sipChild.Release();

		return TRUE;
	}

// diagnostics
#ifdef _DEBUG
	inline void TRACE_ELEMENT(IXMLDOMNode* pElem=NULL, LPTSTR strLabel=NULL)
	{
		USES_CONVERSION;
		if(strLabel)
			ATLTRACE("%s\n", T2A(strLabel));
		_TraceElement(pElem, 1 /* indent */);
	}

	inline void TRACE_ROOT()
	{
		CComPtr<IXMLDOMNode> sipRoot;
		HRESULT hr = GetDocument()->get_documentElement((IXMLDOMElement**)&sipRoot);
		if(FAILED(hr))
		{
			// QA: 32054
			sipRoot.Release();

			return;
		}
		ATLTRACE("root\n");
		CComBSTR s;
		hr = sipRoot->get_nodeName(&s);
		long type;
		hr = sipRoot->get_nodeType((tagDOMNodeType *)&type);
		ATLTRACE("   tag='%S'  type=%ld\n", s, type);
		// QA: 32054
#if _MSC_VER >= 1400
		::SysFreeStringHelper(s);
#else
		::SysFreeString(s);
#endif
		sipRoot.Release();
	}

	inline void _TraceElement ( IXMLDOMNode* pRoot, int nIndent )
	{
		if(!pRoot)
		{
			TRACE_ROOT();
			return;
		}

		char szIndent[128];
		memset(szIndent, ' ', sizeof szIndent);
		if (nIndent * 3 < sizeof szIndent)
			szIndent[nIndent * 3] = '\0';
		else
			szIndent[sizeof szIndent] = '\0';

		CComPtr<IXMLDOMNodeList > sipChildren;
		HRESULT hr = pRoot->get_childNodes(&sipChildren);
		if (FAILED(hr) || !sipChildren)
		{
			ATLTRACE("%snum children = %ld\n", szIndent, 0);
			// QA: 32054
			sipChildren.Release();
			return;
		}

		long nChildren;
		if(FAILED(sipChildren->get_length(&nChildren)))
		{
			// QA: 32054
			sipChildren.Release();

			return;
		}
		
		ATLTRACE("%snum children = %ld\n", szIndent, nChildren);
		for ( long i = 0;  i < nChildren;  ++i ) 
		{
			CComQIPtr<IXMLDOMNode> sipChild;
			if(FAILED(sipChildren->get_item(i, &sipChild)))
				break;

			long lType;
			if(FAILED(sipChild->get_nodeType((tagDOMNodeType *)&lType)))
				break;

			BOOL bflag = FALSE;
			switch (lType) {
				case NODE_ELEMENT:
					{
					ATLTRACE("%schild #%ld, type=ELEMENT", szIndent, i+1);
					CComBSTR s;
					sipChild->get_nodeName(&s);
					ATLTRACE(", tag='%S'", s);
					// QA: 32054
#if _MSC_VER >= 1400
					::SysFreeStringHelper(s);
#else
					::SysFreeString(s);
#endif
					break;
					}
				case NODE_COMMENT:
					if(!bflag)
						ATLTRACE("%schild #%ld, type=COMMENT", szIndent, i+1);
					bflag = TRUE;
				case NODE_TEXT:
					if(!bflag)
						ATLTRACE("%schild #%ld, type=TEXT", szIndent, i+1);
					bflag = TRUE;
				case NODE_CDATA_SECTION:
					if(!bflag)
						ATLTRACE("%schild #%ld, type=CDATA_SECTION", szIndent, i+1);
					bflag = TRUE;

					CComBSTR s;
					sipChild->get_text(&s);
					ATLTRACE(", text='%S'", s);
					// QA: 32054
#if _MSC_VER >= 1400
					::SysFreeStringHelper(s);
#else
					::SysFreeString(s);
#endif
					break;

			}
			ATLTRACE("\n");
			_TraceElement(sipChild, 1+nIndent);

			// QA: 32054
			sipChild.Release();
		}
		// QA: 32054
		sipChildren.Release();
	}
	
#else
	inline static void TRACE_ELEMENT(IXMLDOMNode* sipElem=NULL, LPCTSTR strLabel=NULL){}
	inline static void TRACE_ROOT(){}
	inline static void _TraceElement ( IXMLDOMNode* sipRoot, int nIndent ){}
#endif // debug
};

};  // namespace stingray::foundation
};	// namespace stingray

#endif // __SFL_XMLDOMDOC_H__



