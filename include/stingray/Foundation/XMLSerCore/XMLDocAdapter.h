///////////////////////////////////////////////////////////////////////////////
// XMLDocAdapter.h : The SECXMLDocAdapter_T document adapter class template
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
// Description:  Serves to hook the MFC document architecture into the SEC XML serialization framework
//

#ifndef __SFL_XMLDOCADAPTER_H__
#define __SFL_XMLDOCADAPTER_H__

#pragma once

//[VC7] changing path
#if (_MFC_VER < 0x0700)
#include <..\src\afximpl.h>
#else
#include <..\src\mfc\afximpl.h>
#endif

#include <foundation\sflres.h>
#include <foundation\XMLSerCore\xmlarch.h>
#include <foundation\XMLSerCore\xmldomarch.h>
#include <foundation\XMLSerCore\XMLFTRFactory.h>

namespace stingray {
namespace foundation {


///////////////////////////////////////////////////////////////////////////
//@doc SECXMLDocAdapter_T
//
//@mfunc void | SECXMLDocAdapter_T | OnSECFileOpenXML | Built-in handler for the XML - File Open menu command.
//@rdesc void
//@comm Invoke this function from your document's message map entry for the XML - File Open menu command.
//
//@mfunc void | SECXMLDocAdapter_T | OnSECFileSaveXML | Built-in handler for the XML - File Save menu command.
//@rdesc void
//@comm Invoke this function from your document's message map entry for the XML - File Save menu command.
//
//@mfunc void | SECXMLDocAdapter_T | OnSECFileSaveXMLAs | Built-in handler for the XML - File Save As menu command.
//@rdesc void
//@comm Invoke this function from your document's message map entry for the XML - File Save As menu command.
//
//@mfunc BOOL | SECXMLDocAdapter_T | XMLSaveDocument | This function can be called to save the current document to the 
// specified file. 
//@rdesc TRUE if the save operation is successful.
//@parm LPCTSTR | lpszPathName | The document path.
//@comm This function is usually called by the framework when an XML - Save command is invoked. Calling XMLSaveDocument 
// will create an SECXMLArchive object for the specified file and invoke the document's XMLSerialize routine with this 
// archive instance.
//
//@mfunc BOOL | SECXMLDocAdapter_T | XMLOpenDocument | This function can be called to initialize an existing document with the 
// specified file. 
//@rdesc TRUE if the open operation is successful.
//@parm LPCTSTR | lpszPathName | The document path.
//@comm This function is usually called by the framework when an XML - Open command is invoked. Calling XMLOpenDocument 
// will create an SECXMLArchive object for the specified file and invoke the document's XMLSerialize routine with this 
// archive instance.
//
//@class SECXMLDocAdapter_T | The SECXMLDocAdapter_T class template serves as a bridge between the MFC CDocument/CArchive 
// based serialization architecture and the Stingray SECXMLArchive based XML Serialization Framework. To add the XML 
// serialization capability to your document/view application, simply derive your document class from the SECXMLDocAdapter_T 
// template passing in your document's existing base class as the template argument. By virtue of the SECXMLDocAdapter_T 
// base, your document class inherits from the SFL IXMLSerialize interface and must provide an implementation for the 
// IXMLSerialize::XMLSerialize() and IXMLSerialize::GetElementType() functions.
//
//  <mf SECXMLDocAdapter_T::OnSECFileOpenXML>, 
//  <mf SECXMLDocAdapter_T::OnSECFileSaveXML>,
//  <mf SECXMLDocAdapter_T::OnSECFileSaveXMLAs>,
//  <mf SECXMLDocAdapter_T::XMLOpenDocument>, and 
//  <mf SECXMLDocAdapter_T::XMLSaveDocument>
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@tcarg class | base | Base class of the application's document. This is usually a CDocument or it's derivative. 
//
//@base public | base
//@base public | CXMLSerializeImp
//
template <class base>
class SECXMLDocAdapter_T : public base, public CXMLSerializeImp
{
typedef SECXMLDocAdapter_T<base> SECXMLDocument;
typedef base SECXMLDocumentBase;

public:
	SECXMLDocAdapter_T()
	{
	}

	virtual ~SECXMLDocAdapter_T()
	{
	}

protected:
	CString m_strXMLPathName;
	
protected:

	//@cmember
	/* Menu command handler for XML - File Open.*/
	afx_msg void OnSECFileOpenXML()
	{
		CString fileName;

		if( !PromptXMLFileName(fileName, AFX_IDS_OPENFILE, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, TRUE) )
			return; // open cancelled

		AfxGetApp()->OpenDocumentFile(fileName);
	}

	//@cmember
	/* Menu command handler for XML - File Save.*/
	afx_msg void OnSECFileSaveXML()
	{
		DWORD dwAttrib = GetFileAttributes(m_strXMLPathName);
		if (dwAttrib & FILE_ATTRIBUTE_READONLY)
		{
			// we do not have read-write access or the file does not (now) exist
			if (!DoXMLSave(NULL))
			{
				TRACE0("Warning: File save failed.\n");
				return;
			}
		}
		else
		{
			if (!DoXMLSave(m_strXMLPathName))
			{
				TRACE0("Warning: File save failed.\n");
				return;
			}
		}
	}

	//@cmember
	/* Menu command handler for XML - File Save As.*/
	afx_msg void OnSECFileSaveXMLAs()
	{
		DoXMLSave(NULL);
	}

// XML serialization implementation that exists in parallel to the CDocument persistence framework
public:
	// Based on MFC CDocument::DoSave(...)
	virtual BOOL DoXMLSave(LPCTSTR lpszPathName)
	{
		CString newName = lpszPathName;
		if (newName.IsEmpty())
		{
			CDocTemplate* pTemplate = GetDocTemplate();
			ASSERT(pTemplate != NULL);

			newName = m_strXMLPathName;
			if (newName.IsEmpty())
			{
				newName = m_strTitle;
				// check for dubious filename
				int iBad = newName.FindOneOf(_T(" #%;/\\"));
				if (iBad != -1)
					newName.ReleaseBuffer(iBad);

				// If the current document already has an extension type, then remove this suffix and append 
				// the .xml suffix to the proposed file name
				int nExt = newName.Find(_T("."));
				if(nExt != -1)
					newName.ReleaseBuffer(nExt);
				newName += _T(".xml");				
			}

			if( !PromptXMLFileName(newName, AFX_IDS_SAVEFILE, OFN_HIDEREADONLY|OFN_PATHMUSTEXIST, FALSE) )
				return FALSE;	// Cancelled
		}

		if( !IsXMLExtension(newName) )
		{
			int nExt = newName.Find(_T("."));
			if(nExt == -1)	// No extension, just add .xml and continue
				newName += _T(".xml");
			// Ok, an extension exists. But is this a blank? If so, then add xml and continue
			else if(newName.GetLength()-1 == nExt)
					newName += _T("xml");	
			else // Invalid format specified. ASSERT and return FALSE.
			{
				TRACE0("Warning: Incompatible file extension. Failed to Save as XML.\n");
				ASSERT(0);
				return FALSE;
			}			
		}

		CWaitCursor wait;
		if (!XMLSaveDocument(newName))
			return FALSE;		

		// cache the path name of the XML file for future save operations		
		CacheDocumentPath(newName);
		// reset the title and change the document name
		SetPathName(newName, TRUE);

		return TRUE;        // success
	}

	//@cmember
	/* Saves the current document to the specified file.*/
	virtual BOOL XMLSaveDocument(LPCTSTR lpszPathName)
	{
		ASSERT(AfxIsValidString(lpszPathName));

		// The SECXMLArchive class is a replacement for the MFC CArchive class, that supports persistance of
		// the document content in an XML format
		CString strTagName, strHeader;
		GetElementType(strTagName.GetBuffer(128)); 
		GetXMLHeader(strHeader.GetBuffer(128));
		strTagName.ReleaseBuffer();
		strHeader.ReleaseBuffer();
		TRY
		{
			SECXMLDOMArchive saveArchive(lpszPathName, SECXMLArchive::store, strTagName, strHeader);
			saveArchive.m_pDocument = this;
			
			CWaitCursor wait;
			XMLSerialize(saveArchive);     // save the document
			saveArchive.Close();		
		}
		CATCH_ALL(e)
		{
			TCHAR szError[512];
			e->GetErrorMessage(szError, sizeof(szError));
			TRACE(_T("\nFailed Saving XML Document: ")+CString(szError));
			TRACE(_T("\n"));
			THROW_LAST();
		}
		END_CATCH_ALL

		return TRUE;        // success
	}

	//@cmember
	/* Opens the specified file to initialize an existing document.*/
	virtual BOOL XMLOpenDocument(LPCTSTR lpszPathName)
	{
		ASSERT(AfxIsValidString(lpszPathName));
		
		// Use our custom XML archiving class to load the document 
		CString strTagName, strHeader;
		GetElementType(strTagName.GetBuffer(128));
		GetXMLHeader(strHeader.GetBuffer(128));
		strTagName.ReleaseBuffer();
		strHeader.ReleaseBuffer();
		TRY
		{
			SECXMLDOMArchive loadArchive(lpszPathName, SECXMLArchive::load, strTagName, strHeader);
			loadArchive.m_pDocument = this;
			
			CWaitCursor wait;
			XMLSerialize(loadArchive);     // load the document
			loadArchive.Close();
		}
		CATCH_ALL(e)
		{
			TCHAR szError[512];
			e->GetErrorMessage(szError, sizeof(szError));
			TRACE(_T("\nFailed Opening XML Document: ")+CString(szError));
			TRACE(_T("\n"));
			THROW_LAST();
		}
		END_CATCH_ALL
		
		CacheDocumentPath(lpszPathName);

		return TRUE;	
	}

	
	// Override this member in the document class to provide a different header. 
	virtual void GetXMLHeader(LPTSTR lpRoot)
	{
		ASSERT(AfxIsValidString(lpRoot, 50));	
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy( lpRoot, _T("<?xml version=\"1.0\" standalone=\"yes\"?>") );
	}


// Implementation
protected:
	BOOL IsXMLExtension(LPCTSTR lpszPathName)
	{
		ASSERT(lpszPathName);
		CString strPath = lpszPathName;

		// Is this an XML file?
		if( !strPath.IsEmpty() && ( strPath.Find(_T(".xml")) != -1) )
			return TRUE;
		else
			return FALSE;
	}

	void CacheDocumentPath(LPCTSTR lpszPathName)
	{
		ASSERT(lpszPathName);
		if(m_strXMLPathName.IsEmpty() || (m_strXMLPathName.Compare(lpszPathName)!=0) )
		{
			TCHAR szFullPath[_MAX_PATH];
			AfxFullPath(szFullPath, lpszPathName);
			m_strXMLPathName = lpszPathName;			
		}
	}

	// Similar to the CDocManager::DoPromptFileName() function but uses only the .xml filter. 
	BOOL PromptXMLFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog)
	{
		CString title;
		VERIFY(title.LoadString(nIDSTitle));

		CFileDialog dlgFile(bOpenFileDialog);
		dlgFile.m_ofn.Flags |= lFlags;

		CString strFilter;

		// Add the "*.xml" XML files filter
		CString xmlFilter;
		// If the following line triggers an ASSERT, then this is probably because the SFL resources have not 
		// been added to this project. Please include the "foundation\sfl.rc" file from the 'Compile-time directives' 
		// section of the Visual Studio Resource Includes dialog.  
		VERIFY(xmlFilter.LoadString(IDS_SFL_XMLFILTER));
		strFilter += xmlFilter;
		strFilter += (TCHAR)'\0';
		strFilter += _T("*.xml");
		strFilter += (TCHAR)'\0';
		dlgFile.m_ofn.nMaxCustFilter++;

		// append the "*.*" all files filter
		CString allFilter;
		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		strFilter += allFilter;
		strFilter += (TCHAR)'\0';   // next string please
		strFilter += _T("*.*");
		strFilter += (TCHAR)'\0';   // last string
		dlgFile.m_ofn.nMaxCustFilter++;

		dlgFile.m_ofn.lpstrFilter = strFilter;
		dlgFile.m_ofn.lpstrTitle = title;
		dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
#ifdef _WIN64
		INT_PTR nResult = dlgFile.DoModal();
#else
		int nResult = dlgFile.DoModal();
#endif //_WIN64
		fileName.ReleaseBuffer();
		return nResult == IDOK;
	}

// CDocument overrides
public:
	// Override CDocument::On(Open/Save)Document and if path refers to a .xml file, then kick-off the 
	// corresponding XML serialization mechanism
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName)
	{
		ASSERT(lpszPathName);

		// Is this a valid XML file?
		if( IsXMLExtension(lpszPathName) )
			return XMLOpenDocument(lpszPathName);
		
		// allow default CDocument processing
		return base::OnOpenDocument(lpszPathName);	
	}

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName)
	{
		ASSERT(lpszPathName);

		if( IsXMLExtension(lpszPathName) )
			return XMLSaveDocument(lpszPathName);

		return base::OnSaveDocument(lpszPathName);
	}	

};

}; // namespace stingray::foundation
}; // namespace stingray


#endif //__SFL_XMLDOCADAPTER_H__

