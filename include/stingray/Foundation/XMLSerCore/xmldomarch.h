///////////////////////////////////////////////////////////////////////////////
// xmldomarch.h : SECXMLDOMArchive
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
// Description:  Archive class with XML DOM specific implementation
//

#ifndef __SFL_XMLDOMARCHIVE_H__
#define __SFL_XMLDOMARCHIVE_H__

#if _WIN32_IE < 0x0500
#pragma message("Warning: It appears that you are not linking to the latest Platform SDK. This is required for the latest XML DOM interfaces. Errors may result.")
#endif //_WIN32_IE < 0x0500

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

#include <foundation\XMLSerCore\xmldomdoc.h>
#include <foundation\XMLSerCore\xmlarch.h>
#include <foundation\XMLSerCore\xmlcteb64qp.h>
#include <StingrayExportDefs.h>

namespace stingray {
	namespace foundation {

#define MAX_TAGNAME_SIZE 128

#define MAX_NUM_STRING_SIZE 29

//@doc SECXMLDOMArchive
//@class SECXMLDOMArchive | The SECXMLDOMArchive uses the latest XML DOM interfaces (MS XML 2.5 SDK) to 
//	interact with XML documents. An SECXMLDOMArchive instance gets created and gets associated with 
// a .xml file by  the SECXMLDocAdapter_T class. You would however only 
// deal with the base SECXMLArchive interface in your application. You could also create and 
// initialize SECXMLDOMArchive yourself if you choose not to use the document adapter class in 
// your application.
//@base public | SECXMLArchive
//@xref <c SECXMLArchive>
//@xref <c SECXMLDocAdapter_T>

class SECXMLDOMArchive : public SECXMLArchive
{
public:
	
	inline SECXMLDOMArchive(LPCTSTR fileName, UINT nMode, LPCTSTR rootTagName, LPCTSTR headerInfo =NULL)
	: SECXMLArchive(fileName, nMode, rootTagName, headerInfo)
	{
		m_pOtlXMLDoc = new SECXMLDocument((LPTSTR)rootTagName, (LPTSTR)headerInfo);

		m_sipCurElemCacheList = NULL;

		if(nMode == load)
		{
			HRESULT hr;
			if(FAILED(hr = m_pOtlXMLDoc->LoadFromFile((LPTSTR)fileName)))
			{
				AfxThrowOleException(hr);
			}else if(hr == S_FALSE)
			{
				AfxThrowFileException(CFileException::invalidFile, -1, fileName);
			}

			m_pOtlXMLDoc->GetRoot(&m_sipCurParElem);

			// Initialize the map in SECXMLDocument
			m_pOtlXMLDoc->MapElements(m_sipCurParElem, FALSE);	// FALSE == Don't recurse
		}else if(nMode == store)
		{
			m_pOtlXMLDoc->GetRoot(&m_sipCurParElem);
		}
	}

	inline ~SECXMLDOMArchive()
	{
		CleanUp();
	}


	//Operations

	// Saves the current document content to the file (useful only while writing)
	// and disconnects from the file.
	inline virtual void Close()
	{
		ASSERT(m_sipCurElemCacheList == NULL);
			// Did you forget to call CloseElement after OpenElement?
		if(m_nMode == store)
			m_pOtlXMLDoc->SaveToFile(m_strFilePath);

		CleanUp();
	}

	// abort without saving the document (useful only while writing)
	// and disconnects from the file.
	inline void CleanUp()
	{
		if(m_pOtlXMLDoc)
		{
			delete m_pOtlXMLDoc;
			m_pOtlXMLDoc = NULL;
		}

		while(m_sipCurElemCacheList)
		{
			OpenElemCacheListItem* pCurr = m_sipCurElemCacheList;
			m_sipCurElemCacheList = m_sipCurElemCacheList->m_pPrev;
			delete pCurr;
			pCurr = NULL; // QA: 31948
		}

		if(m_sipCurElemCacheList) // QA: 31948
		{
			delete m_sipCurElemCacheList;
			m_sipCurElemCacheList = NULL;
		}
	}

	inline virtual BOOL OpenElement(LPCTSTR tagName, BOOL bAssertOnFailure = FALSE)
	{
		CComQIPtr<IXMLDOMNode> sipNewChildElem;

		if(m_nMode == load)
		{
			CComVariant vaVal;
			if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_DISPATCH))
			{
				sipNewChildElem = vaVal.pdispVal;

				SECXMLDocument::XMLTagMap *map = new SECXMLDocument::XMLTagMap(); // Deleted by OpenElemCacheListItem
				*map = m_pOtlXMLDoc->m_map;
				// Cache the current parent element
				TCHAR* strTagName = new TCHAR[_tcslen(tagName) + 1]; // Deleted by OpenElemCacheListItem
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(strTagName, tagName);
				m_sipCurElemCacheList = new OpenElemCacheListItem(strTagName, NULL, map, m_sipCurElemCacheList);
				m_pOtlXMLDoc->ClearMap(FALSE);

				// Reload the map for the new parent element
				m_pOtlXMLDoc->MapElements(sipNewChildElem, FALSE);	// FALSE == Don't recurse
			}
			else
			{
				if(bAssertOnFailure)
					ASSERT(FALSE);

				// QA: 32054
#if _MSC_VER >= 1400
				vaVal.ClearToZero();
#else
				vaVal.Clear();
#endif

				return FALSE;	// tagName not found
			}
			// QA: 32054
#if _MSC_VER >= 1400
			vaVal.ClearToZero();
#else
			vaVal.Clear();
#endif
		}
		else if (m_nMode == store)
		{
			if(FAILED(m_pOtlXMLDoc->AddTag(tagName, NODE_ELEMENT, &sipNewChildElem, m_sipCurParElem)))
			ASSERT(FALSE);

			// Cache the current parent element
			TCHAR* strTagName = new TCHAR[_tcslen(tagName) + 1]; // Deleted by OpenElemCacheListItem
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(strTagName, tagName);
			m_sipCurElemCacheList = new OpenElemCacheListItem(strTagName, m_sipCurParElem, NULL, m_sipCurElemCacheList);

			m_sipCurParElem = sipNewChildElem;
		}

		// QA: 32054
		sipNewChildElem.Release();

		return TRUE;
	}

	inline virtual void CloseElement(LPCTSTR tagName)
	{
		ASSERT(m_sipCurElemCacheList);	// OpenElement would have initialized m_sipCurElemCacheList
										// Did you call OpenElement first?

		if(_tcscmp(tagName, m_sipCurElemCacheList->m_tagName) == 0)
		{
			if(m_nMode == store)
				m_sipCurParElem = m_sipCurElemCacheList->m_elem;
			else if(m_nMode == load)
				m_pOtlXMLDoc->m_map = *(m_sipCurElemCacheList->m_map);

			OpenElemCacheListItem* pCurr = m_sipCurElemCacheList;
			m_sipCurElemCacheList = m_sipCurElemCacheList->m_pPrev;

			delete pCurr;
			pCurr = NULL;
		}
		else
			ASSERT(FALSE);	// Trying to close an element that is not the latest Opened element
	}


	// insertion operations

	// insertion operator
	// should handle recursion
	inline virtual SECXMLArchive& Write(LPCTSTR contextTagName, IXMLSerialize* pFormatter)
	{
		if(!pFormatter->IsDataAvailableToWrite())
			return *this;

		// Store the current parent element
		CComPtr<IXMLDOMNode> sipCurParElem = m_sipCurParElem;

		// Create a new element
		CComPtr<IXMLDOMNode> sipNewChildElem;

		// Get the tagname for the new element
		LPTSTR tagName = NULL;
		if(contextTagName == NULL)
		{
			tagName = new TCHAR[MAX_TAGNAME_SIZE];
			pFormatter->GetElementType(tagName);
		}else
		{
			tagName = (LPTSTR)contextTagName;
		}
		ASSERT(tagName != NULL);

		if(_tcslen(tagName) == 0)
		{
			pFormatter->XMLSerialize(*this);
			delete [] tagName;
			tagName = NULL;

			// QA: 32054
			sipCurParElem.Release();
			sipNewChildElem.Release();

			return *this;
		}

		// Create the new element with the given tag
		if(FAILED(m_pOtlXMLDoc->AddTag(tagName, NODE_ELEMENT, &sipNewChildElem, sipCurParElem)))
			ASSERT(FALSE);

		// Set the current parent element to the newly created child element
		m_sipCurParElem = sipNewChildElem;

		if(contextTagName == NULL)
		{
			// Peforming sanity check
			OpenElemCacheListItem* pBeforeXMLSer = m_sipCurElemCacheList; // Temporary pointer

			// Ask the Formatter to insert child elements for this element
			pFormatter->XMLSerialize(*this);

			ASSERT(pBeforeXMLSer == m_sipCurElemCacheList);
				// Within the above XMLSerialize function all Opened elements should have been closed.

			if(tagName)
			{
				delete [] tagName;
				tagName = NULL;
			}
		}else
		{
			// Recurse to write the pFormatter element as child of "contextTagName" element
			this->Write(NULL, pFormatter);
		}

		// Reset the current parent element
		m_sipCurParElem = sipCurParElem;

		// QA: 32054
		sipCurParElem.Release();
		sipNewChildElem.Release();

		return *this;
	}


	inline virtual SECXMLArchive& Write(LPCTSTR tagName, BYTE by)
	{
		USES_CONVERSION;

		//TODO
		CString str(_T("TODO"));

		str.Format(_T("%d"), (int)by);
		
		// Add it as a Text element under the current parent element
		m_pOtlXMLDoc->AddTextTag(tagName, str.GetBuffer(6), NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, WORD w)
	{
		return Write(tagName, (DWORD)w);
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, LONG l)
	{
		TCHAR buffer[MAX_NUM_STRING_SIZE];
		
		// Convert to string
		// QA: 31989 - #if Secure Code Cleanup.
		_ltot(l, buffer, 10);

		// Add it as a Text element under the current parent element
		m_pOtlXMLDoc->AddTextTag(tagName, buffer, NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, DWORD dw)
	{
		TCHAR buffer[MAX_NUM_STRING_SIZE];
		
		// Convert to string
		// QA: 31989 - #if Secure Code Cleanup.
		_ultot( dw, buffer, 10);
		// Add it as a Text element under the current parent element
		m_pOtlXMLDoc->AddTextTag(tagName, buffer, NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, float f)
	{
		TCHAR buffer[MAX_NUM_STRING_SIZE];
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buffer, _T("%g"), f);

		// Add it as a Text element under the current parent element
		m_pOtlXMLDoc->AddTextTag(tagName, buffer, NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, double d)
	{
		TCHAR buffer[MAX_NUM_STRING_SIZE];
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buffer, _T("%.13g"), d);

		// Add it as a Text element under the current parent element
		m_pOtlXMLDoc->AddTextTag(tagName, buffer, NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, int i)
	{
		return Write(tagName, (LONG)i);
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, short w)
	{
		return Write(tagName, (LONG)w);
	}

/*	inline virtual SECXMLArchive& Write(LPCTSTR tagName, TCHAR ch)
	{
		TCHAR buffer[2];

		buffer[0]=ch;
		buffer[1]=_T('\0');

		m_pOtlXMLDoc->AddTextTag(tagName, buffer, NODE_TEXT, NULL, m_sipCurParElem);

		return *this;
	}
*/
	inline virtual SECXMLArchive& Write(LPCTSTR tagName, unsigned u)
	{
		return Write(tagName, (DWORD)u);
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, LPCTSTR str, long nType = NODE_TEXT)
	{
		if(str == NULL)
			ASSERT(FALSE);
		m_pOtlXMLDoc->AddTextTag(tagName, str, nType, NULL, m_sipCurParElem);

		return *this;
	}

	inline virtual SECXMLArchive& Write(LPCTSTR tagName, const void* lpBuf, UINT nMax, int encodeType = SEC_BASE64)
	{
		USES_CONVERSION;
		
		SECCTEBase* pEncoder = NULL;
		CString strEncodedDataTagName;

		// Create a encoder based on the type specified
		if(encodeType == SEC_BASE64)
		{
			pEncoder = new SECBase64Encoder(1);
//			pEncoder->SetFinalNewline(TRUE);
			strEncodedDataTagName = _T("Base64_Encoded");
		}
		else if(encodeType == SEC_QUOTED_PRINTABLE)
		{
			pEncoder = new SECQPEncoder(1);
			strEncodedDataTagName = _T("QuotedPrintable_Encoded");
		}

		ASSERT(pEncoder);

		pEncoder->Encode((BYTE*)lpBuf, nMax);	// Figure out the encoded length
		int nLen = pEncoder->GetOutBufferSize();
		char* pOut = new char[nLen + 1];

		//int nRet = 
		pEncoder->EndEncode((BYTE*)pOut, nLen);

		pOut[nLen] = _T('\0');

		// Write to the document like this:
		// <tagName> <ENCODING_TYPE> CDATA_SECTION(encoded data) </ENCODING_TYPE> </tagName>

		OpenElement(tagName);
		Write(strEncodedDataTagName, (LPCTSTR)A2T(pOut), NODE_CDATA_SECTION);
		CloseElement(tagName);

		// Clean up
        delete [] pOut; // QA: 31948
		pOut = NULL;
		
		delete pEncoder; // QA: 31948
		pEncoder = NULL;

		return *this;
	}

	// extraction operations

	// extraction operator
	// should handle recursion
	inline virtual BOOL Read(LPCTSTR contextTagName, IXMLSerialize* pFormatter, BOOL bAssertOnFailure = FALSE)
	{
		// The COTLXMLDoc's map will be loaded with the appropriate elements at this point.

		if(pFormatter == NULL && contextTagName == NULL)
			return FALSE;

		// Get the tagname of the element to be found
		LPTSTR tagName = NULL;
		if(contextTagName == NULL)
		{
			tagName = new TCHAR[MAX_TAGNAME_SIZE];
			pFormatter->GetElementType(tagName);
		}else
		{
			tagName = (LPTSTR)contextTagName;
		}
		ASSERT(tagName != NULL);

		// If the formatter does not have a tagname, then use the current parent node
		if(_tcslen(tagName) == 0)	
		{
			pFormatter->PreReadXML();
			pFormatter->XMLSerialize(*this);
			delete [] tagName;
			tagName = NULL; // QA: 31948

			return TRUE;
		}

		// Get the corresponding element from the map
		CComVariant vaVal;
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_DISPATCH))
		{
			// THe corresponding child:
			CComQIPtr<IXMLDOMNode> sipChild;
			sipChild = vaVal.pdispVal;

			// Cache the current map in COTLXMLDoc.
			SECXMLDocument::XMLTagMap m_Curmap = m_pOtlXMLDoc->m_map;
			m_pOtlXMLDoc->ClearMap(FALSE);

			// Reset the map in the OTLXMLDoc to the new elements under sipChild
			m_pOtlXMLDoc->MapElements(sipChild, FALSE);	// FALSE == Don't recurse

			// Call the Formatter 
			if(contextTagName == NULL)
			{
				// Peforming sanity check
				OpenElemCacheListItem* pBeforeXMLSer = m_sipCurElemCacheList;

				pFormatter->PreReadXML();

				pFormatter->XMLSerialize(*this);

				ASSERT(pBeforeXMLSer == m_sipCurElemCacheList);
					// Within the above XMLSerialize function all Opened elements should have been closed.

				delete [] tagName;
				tagName = NULL; // QA: 31948
			}else
			{
				this->Read(NULL, pFormatter, bAssertOnFailure);
			}

			// Reset the map
			m_pOtlXMLDoc->m_map = m_Curmap;

			// QA: 32054
#if _MSC_VER >= 1400
			vaVal.ClearToZero();
#else
			vaVal.Clear();
#endif
			sipChild.Release();
		}else
		{
			if((contextTagName == NULL) && (NULL != tagName)) // QA: 29972
			{
				delete [] tagName;
				tagName = NULL; // QA: 31948
			}
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		if((contextTagName == NULL) && (NULL != tagName)) // QA: 29972
		{
			delete [] tagName;
			tagName = NULL; // QA: 31948
		}

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, BYTE& by, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_UI1))
		{
			by = vaVal.bVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, WORD& w, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_UI2))
		{
			w = vaVal.uiVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, DWORD& dw, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_UI4))
		{
			dw = vaVal.ulVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, LONG& l, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_I4))
			l = vaVal.lVal;
		else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, float& f, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_R4))
		{
			f = vaVal.fltVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, double& d, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_R8))
		{
			d = vaVal.dblVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, int& i, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_INT))
		{
			i = vaVal.intVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, short& w, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_I2))
		{
			w = vaVal.iVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, char& ch, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_I1))
		{
			ch = vaVal.cVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, unsigned& u, BOOL bAssertOnFailure = FALSE)
	{
		CComVariant vaVal;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, vaVal, VT_UINT))
		{
			u = vaVal.uintVal;
		}else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		// QA: 32054
#if _MSC_VER >= 1400
		vaVal.ClearToZero();
#else
		vaVal.Clear();
#endif

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, CString& string, BOOL bAssertOnFailure = FALSE)
	{
		UINT nSize = 0;
		LPTSTR strRes = NULL;	
		if(Read(tagName, strRes, nSize, FALSE, FALSE))	
		{	
			string = strRes;	
			delete [] strRes;
			strRes = NULL; // QA: 31948
		}
		else
		{
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

		return TRUE;
	}

	inline virtual BOOL Read(LPCTSTR tagName, void*& lpBuf, UINT& nMax, BOOL bAssertOnFailure = FALSE)
	{
		BOOL bSuccess = FALSE;
		
		// Look for the element from the children loaded in the map.
		if(OpenElement(tagName))
		{
			SECCTEBase* pDecoder = NULL;
			TCHAR* pBuffSrc = NULL;
			// Check if base64 encoded or Quoted_Printable encoded
			UINT nLenSrc = 0;
			if(Read(_T("Base64_Encoded"), pBuffSrc, nLenSrc))
			{
				pDecoder = new SECBase64Encoder(1);
			}else if(Read(_T("QuotedPrintable_Encoded"), pBuffSrc, nLenSrc))
			{
				pDecoder = new SECQPEncoder(1);
			}

			ASSERT(pDecoder);

			// Use the decoder to decode the data
			pDecoder->Decode((BYTE*)pBuffSrc, nLenSrc - 1);
			UINT nDecodedSize = pDecoder->GetOutBufferSize();

			bSuccess = TRUE;
			if(nDecodedSize > nMax)
			{
				nMax = nDecodedSize;	// Not enough space in buffer, try again with a bigger buffer
			}else
			{
				pDecoder->EndDecode((BYTE*)lpBuf, nMax);
			}
			// Clean up
            delete [] pBuffSrc; // QA: 31948
			pBuffSrc = NULL;

			delete pDecoder; // QA: 31948
			pDecoder = NULL;
			
			CloseElement(tagName);
		}

		if(!bSuccess)
			if(bAssertOnFailure)
				ASSERT(FALSE);
		
		return bSuccess;
	}

	inline virtual BOOL Read(LPCTSTR tagName, LPTSTR& lpBuff, UINT& nLen, BOOL bAssertOnFailure = FALSE, BOOL bTruncateOnOverflow =FALSE )
	{
		_bstr_t bstr;
		// Look for the element from the children loaded in the map.
		if(m_pOtlXMLDoc->FindTextTag(tagName, bstr))
		{
			UINT len = bstr.length();
			len++;	//length with the terminating null char.

			if(len > nLen && !bTruncateOnOverflow)
			{
				// Delete the exisiting buffer and create a new one.
				delete [] lpBuff;
				lpBuff = new TCHAR[len];
				nLen = len;
			}

			USES_CONVERSION;

			// Using _tcsncpy and manualy appending the terminating null char
			// to take care of cases where truncation is allowed to take place.
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(lpBuff, OLE2T(bstr), len-1);

			// While not truncating the following operation is valid but unnecessary.
			lpBuff[len-1] = _T('\0');
		}
		else
		{
#if _MSC_VER >= 1400
			::SysFreeStringHelper(bstr); // QA: 31948
#else
			::SysFreeString(bstr);
#endif
			if(bAssertOnFailure)
				ASSERT(FALSE);
			return FALSE;
		}

#if _MSC_VER >= 1400
		::SysFreeString(bstr); // QA: 31948
#else
		::SysFreeString(bstr);
#endif

		return TRUE;
	}


protected:
	SECXMLDocument* m_pOtlXMLDoc;
	CComPtr<IXMLDOMNode> m_sipCurParElem;

	struct OpenElemCacheListItem
	{
	public:
		inline OpenElemCacheListItem():m_tagName(NULL), m_elem(NULL), m_map(NULL), m_pPrev(NULL){};
		inline OpenElemCacheListItem(LPTSTR name, CComPtr<IXMLDOMNode> elem, SECXMLDocument::XMLTagMap* map, OpenElemCacheListItem* pPrev)
			:m_tagName(name), m_elem(elem), m_map(map), m_pPrev(pPrev){};

		inline ~OpenElemCacheListItem()
		{
			if(m_map) // QA: 31948
			{
				delete m_map;
				m_map = NULL;
			}
			if(m_tagName) // QA: 31948
			{
				delete [] m_tagName;
				m_tagName = NULL;
			}
		}

		LPTSTR						m_tagName;
		CComPtr<IXMLDOMNode>		m_elem;
		SECXMLDocument::XMLTagMap*	m_map;
		OpenElemCacheListItem*		m_pPrev;
	};

	OpenElemCacheListItem* m_sipCurElemCacheList;
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif	//__SFL_XMLDOMARCHIVE_H__
