///////////////////////////////////////////////////////////////////////////////
// OtlXmlDoc.h
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

#ifndef __OTLXMLDOC_H__
#define __OTLXMLDOC_H__

#ifndef __OTLBASE_H__
	#error otlxmldoc.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otlfilestream.h>
#include <comdef.h>

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		#include <msxml6.h>
	#else
		#include <msxml.h>
	#endif
#else
	#include <msxml.h>
#endif

#include <stdio.h>
#include <foundation\stwarn.h>
#include <map>
#include <foundation\stwarnp.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlXmlDocument

class COtlXMLDocument
{
public:
	typedef std::map<_bstr_t, _bstr_t, std::less<_bstr_t> > XMLTagMap;
	CComPtr<IXMLDocument> m_sipDoc;
	XMLTagMap m_map;

public:
	// construct and create a document
	inline COtlXMLDocument(){}
	inline COtlXMLDocument(LPTSTR strRootTag, LPTSTR strHeader=NULL)
	{
		Create(strRootTag, strHeader);
	}

	// create an empty document with a root tag
	inline BOOL Create(LPTSTR strRootTag, LPTSTR strHeader=NULL)
	{
		USES_CONVERSION;
		//HRESULT hr = E_FAIL;
		if(!strHeader)
			strHeader = _T("");

		if(FAILED(CoCreateInstance(CLSID_XMLDocument, 
									NULL,
									CLSCTX_ALL,
									IID_IXMLDocument,
									reinterpret_cast<void**>(&m_sipDoc))))
				return FALSE;


		char* pszHeader = T2A(strHeader);
		char* pszRootTag = T2A(strRootTag);

		char szXml[2048];

#ifdef _WIN64
		// QA: 31989 - #if Secure Code Cleanup.
		sprintf(szXml, "%s\n<%s>\n</%s>\n", pszHeader, pszRootTag, pszRootTag);
#else
		sprintf(szXml, "%s\n<%s>\n</%s>\n", pszHeader, pszRootTag, pszRootTag);
#endif //_WIN64

		// create the stream from which to initialize the document
		//    first, write the given xml content 
		//    then, seek to the beginning of the stream
		CComPtr<IStream> sipStream;
		if (FAILED(CreateStreamOnHGlobal(0, 1, &sipStream)))
			return FALSE;

		unsigned long ulUnused;
		if(FAILED(sipStream->Write(szXml, (int)strlen(szXml), &ulUnused)))
			return FALSE;

		LARGE_INTEGER pos = { (__int64)0 };
		if(FAILED(sipStream->Seek(pos, STREAM_SEEK_SET, 0)))
			return FALSE;

		// initialize the new document from the given given stream
		CComQIPtr<IPersistStreamInit> sipPersist(m_sipDoc);

		if(FAILED(sipPersist->Load(sipStream)))
			return FALSE;

		return m_sipDoc != 0;
	}

	// find a tag and return a bstr value for the first text child
	// call LoadMap before using
	inline BOOL FindTextTag(const _bstr_t& strTag, _bstr_t& strValue)
	{
		XMLTagMap::iterator it;
		if((it = m_map.find(strTag)) != m_map.end())
		{
            strValue = (*it).second;
			return TRUE;		
		}
		return FALSE;
	}

	// find a tag and return a variant representation of the first text child
	// call LoadMap before using
	inline BOOL FindTextTag(const _bstr_t& strTag, CComVariant& vVal, VARTYPE vt)
	{
		_bstr_t strVal;
		if(FindTextTag(strTag, strVal))
		{
			vVal = (BSTR)strVal;
			if(FAILED(vVal.ChangeType(vt)))
				return FALSE;
			return TRUE;
		}
		return FALSE;
	}


	inline void ClearMap()
	{
		m_map.erase(m_map.begin(), m_map.end());
	}

	// populate the text tag map with tagname,textchild values
	inline BOOL LoadMap()
	{
		ClearMap();
		OTLASSERT(m_sipDoc);
		CComPtr<IXMLElement> sipRoot;
		HRESULT hr = GetDocument()->get_root(&sipRoot);
		if(FAILED(hr))
			return FALSE;
		// enumerate all element tags and add to the list
		if(MapElements(sipRoot))
			return TRUE;
		return FALSE;
	}

	// recursive map builder
	inline BOOL MapElements(IXMLElement* pRoot, BOOL bRecurse = TRUE)
	{
		CComPtr<IXMLElementCollection> sipChildren;
		HRESULT hr = pRoot->get_children(&sipChildren);
		if (FAILED(hr) || !sipChildren)
			return FALSE;

		long nChildren;
		if(FAILED(sipChildren->get_length(&nChildren)))
			return FALSE;
		
		for ( long i = 0;  i < nChildren;  ++i ) 
		{
			CComVariant vIndex = (long)i;
			CComVariant vEmpty;
			IDispatch* pDisp = 0;
			if(FAILED(sipChildren->item(vIndex, vEmpty, &pDisp)))
				return FALSE;
			CComQIPtr<IXMLElement> sipChild(pDisp);
			long lType;
			if(FAILED(sipChild->get_type(&lType)))
				return FALSE;
			if(lType == XMLELEMTYPE_ELEMENT)
			{
				BSTR strText;
				if(GetTextTag(sipChild, strText))
				{	
					BSTR strTagName;
					if(SUCCEEDED(sipChild->get_tagName(&strTagName)))
					{
						ATLTRACE("MapEntry: %S\t%S\n", strTagName, strText);
						m_map.insert(XMLTagMap::value_type( strTagName, strText));
						::SysFreeString(strTagName);
					}
					::SysFreeString(strText);
				}
				if( bRecurse )
					MapElements(sipChild);
			}
		}
		return TRUE;
	}

	// release the msmxml parser
	inline void Destroy()
	{
		if(m_sipDoc)
			m_sipDoc = NULL;
	}

	// attach to an existing document
	inline void Attach(IXMLDocument* pDoc)
	{
		OTLASSERT(pDoc);
		if(m_sipDoc)
			Destroy();
		m_sipDoc = pDoc;
	}

	inline void Detach()
	{
		Destroy();
	}

	// returns the root element
	inline HRESULT GetRoot(IXMLElement** ppRoot) 
	{
		OTLASSERT(m_sipDoc && ppRoot);
		*ppRoot = 0;
		return m_sipDoc->get_root(ppRoot);
	}
	
	// populate from an existing XML file
	inline HRESULT LoadFromFile(LPTSTR strFileName)
	{
		OTLASSERT(m_sipDoc && strFileName);
		CComBSTR strFile(strFileName);
		return m_sipDoc->put_URL(strFile);
	}

	// save to an XML file
	inline HRESULT SaveToFile(LPTSTR strFileName)
	{
		USES_CONVERSION;
		OTLASSERT(m_sipDoc && strFileName);
		HRESULT hr;
		CComObject<COtlFileStream> *pfstream;
		hr = CComObject<COtlFileStream>::CreateInstance( &pfstream );
		if(FAILED(hr))
			return hr;

		hr = pfstream->Open(T2OLE(strFileName), TRUE);
		if(FAILED(hr))
			return hr;
		// save the XML text to a chunk of memory
		CComQIPtr<IPersistStreamInit> sipPersist(m_sipDoc);
		if(sipPersist)
			hr = sipPersist->Save(pfstream, FALSE /* don't clear dirty bit */);
		else
			hr = E_NOINTERFACE;

		return hr;
	}

	// add a generic element
	// <strTagName> </strTagName>
	inline HRESULT AddTag(LPCTSTR strTagName, long nType, IXMLElement** ppRetVal=NULL, IXMLElement* pParent=NULL)
	{
		CComPtr<IXMLElement> sipElem;
		CComVariant vType = nType;
		CComVariant vName;
		// second parameter can not be used for text elements, must call put_text instead
		if(nType != (long)XMLELEMTYPE_TEXT)
			vName = strTagName;

		// create an element
		HRESULT hr;
		if(FAILED(hr = m_sipDoc->createElement(vType, vName, &sipElem)))
			return hr;

		// create as child of parent, or root if NULL parent
		CComPtr<IXMLElement> sipParent;
		if( pParent )
			sipParent = pParent;
		else
			if(FAILED(hr = m_sipDoc->get_root(&sipParent)))
				return hr;

		if(FAILED(hr = sipParent->addChild(sipElem, -1 /* -1=append */, -1 /* reserved, must be -1 */ )))
			return hr;

		// initialize the return value	
		if(ppRetVal)
		{
			*ppRetVal = sipElem;
			((IXMLElement*)*ppRetVal)->AddRef();
		}
		return hr;
	}
	
	// add an element with a text child element
	// <strTagName> strText </strTagName>
	inline HRESULT AddTextTag(LPCTSTR strTagName, LPCTSTR strText, IXMLElement** ppRetVal=NULL, IXMLElement* pParent=NULL)
	{
		OTLASSERT(m_sipDoc);
		// create an element
		HRESULT hr;
		CComPtr<IXMLElement> sipElem;
		if(FAILED(hr = AddTag(strTagName, (long)XMLELEMTYPE_ELEMENT, &sipElem, pParent)))
			return hr;

		// create a text element under the element
		CComPtr<IXMLElement> sipText;
		if(FAILED(hr = AddTag(NULL, (long)XMLELEMTYPE_TEXT, &sipText, sipElem)))
			return hr;

		CComBSTR s(strText);
		if(FAILED(hr = sipText->put_text(s)))
			return hr;

		// initialize the return value	
		if(ppRetVal)
		{
			*ppRetVal = sipElem;
			((IXMLElement*)*ppRetVal)->AddRef();
		}
		return hr;
	}

	// add an attribute to an element
	inline HRESULT SetAttribute(IXMLElement* pElem, LPTSTR strName, LPTSTR strValue)
	{
		OTLASSERT(strName && strValue && pElem);
		CComBSTR bstrName = strName;
		CComVariant vValue = strValue;
		return pElem->setAttribute(bstrName, vValue);
	}

	// get the document interface pointer
	IXMLDocument* GetDocument(){ return m_sipDoc;}
	
	inline BOOL HasErrorInfo(IUnknown* pDoc) 
	{
		long nLineNumber;
		_bstr_t bstrFound, bstrExpected, bstrBuffer;
		return GetErrorInfo(pDoc, nLineNumber, bstrFound, bstrExpected, bstrBuffer);
	}


	inline BOOL GetErrorInfo ( IUnknown* pDoc,
		                       long & rnLineNumber, 
		                       _bstr_t & rbstrFound,
		                       _bstr_t & rbstrExpected,
		                       _bstr_t & rbstrBuffer )
	{
		CComQIPtr<IXMLError> sipError = pDoc;
		if (!sipError) return FALSE; // no error info supported
		_xml_error xmle;
		HRESULT hr = sipError->GetErrorInfo(&xmle);
		if(SUCCEEDED(hr))
		{
			rnLineNumber  = xmle._nLine;
			rbstrFound    = _bstr_t(xmle._pszFound,    FALSE /* just attach */);
			rbstrExpected = _bstr_t(xmle._pszExpected, FALSE /* just attach */);
			rbstrBuffer   = _bstr_t(xmle._pchBuf,      FALSE /* just attach */);
			return TRUE;
		}
		else
		{ // no error info available 
			rnLineNumber  = 0;
			rbstrFound    = rbstrExpected = rbstrBuffer = _bstr_t();
			return FALSE; // no error info found
		}
		return TRUE;
	}
	
	inline BOOL GetTextTag(IXMLElement* pElement, BSTR& strTag)
	{
		OTLASSERT(pElement);
		CComPtr<IXMLElementCollection> sipChildren;
		HRESULT hr = pElement->get_children(&sipChildren);
		if (FAILED(hr) || !sipChildren)
			return FALSE;

		long nChildren = 0;
		if(FAILED(sipChildren->get_length(&nChildren)) || nChildren < 1)
			return FALSE;
				
		CComVariant vIndex = (long)0;
		CComVariant vEmpty;
		CComPtr<IDispatch> sipDisp;
		if(FAILED(sipChildren->item(vIndex, vEmpty, &sipDisp)))
			return FALSE;
		CComQIPtr<IXMLElement> sipChild(sipDisp);
		long lType;
		if(FAILED(sipChild->get_type(&lType)))
			return FALSE;
		if(lType != XMLELEMTYPE_TEXT)
			return FALSE;

		if(FAILED(sipChild->get_text(&strTag)))
			return FALSE;
		return TRUE;
	}

// diagnostics
#ifdef _DEBUG
	inline void TRACE_ELEMENT(IXMLElement* pElem=NULL, LPTSTR strLabel=NULL)
	{
		USES_CONVERSION;
		if(strLabel)
			ATLTRACE("%s\n", T2A(strLabel));
		_TraceElement(pElem, 1 /* indent */);
	}

	inline void TRACE_ROOT()
	{
		CComPtr<IXMLElement> sipRoot;
		HRESULT hr = GetDocument()->get_root(&sipRoot);
		if(FAILED(hr))
			return;
		ATLTRACE("root\n");
		CComBSTR s;
		hr = sipRoot->get_tagName(&s);
		long type;
		hr = sipRoot->get_type(&type);
		ATLTRACE("   tag='%S'  type=%ld\n", s, type);
	}

	inline void _TraceElement ( IXMLElement* pRoot, int nIndent )
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

		CComPtr<IXMLElementCollection> sipChildren;
		HRESULT hr = pRoot->get_children(&sipChildren);
		if (FAILED(hr) || !sipChildren)
		{
			ATLTRACE("%snum children = %ld\n", szIndent, 0);
			return;
		}

		long nChildren;
		if(FAILED(sipChildren->get_length(&nChildren)))
			return;
		
		ATLTRACE("%snum children = %ld\n", szIndent, nChildren);
		for ( long i = 0;  i < nChildren;  ++i ) 
		{
			CComVariant vIndex = (long)i;
			CComVariant vEmpty;
			CComPtr<IDispatch> sipDisp;
			if(FAILED(sipChildren->item(vIndex, vEmpty, &sipDisp)))
				break;
			CComQIPtr<IXMLElement> sipChild(sipDisp);
			long lType;
			if(FAILED(sipChild->get_type(&lType)))
				break;
			switch (lType) {
				case XMLELEMTYPE_ELEMENT:
					{
					ATLTRACE("%schild #%ld, type=ELEMENT", szIndent, i+1);
					CComBSTR s;
					sipChild->get_tagName(&s);
					ATLTRACE(", tag='%S'", s);
					break;
					}
				case XMLELEMTYPE_COMMENT:
					{
					ATLTRACE("%schild #%ld, type=COMMENT", szIndent, i+1);
					CComBSTR s;
					sipChild->get_text(&s);
					ATLTRACE(", text='%S'", s);
					break;
					}
				case XMLELEMTYPE_TEXT:
					{
					ATLTRACE("%schild #%ld, type=TEXT", szIndent, i+1);
					CComBSTR s;
					sipChild->get_text(&s);
					ATLTRACE(", text='%S'", s);
					break;
					}
			}
			ATLTRACE("\n");
			_TraceElement(sipChild, 1+nIndent);
		}
	}
#else
	static void TRACE_ELEMENT(IXMLElement* sipElem=NULL, LPCTSTR strLabel=NULL){}
	static void TRACE_ROOT(){}
	static void _TraceElement ( IXMLElement* sipRoot, int nIndent ){}
#endif // debug


};


};	// namespace StingrayOTL

#endif // __OTLXMLDOC_H__



