///////////////////////////////////////////////////////////////////////////////
// xmlarch.h : SECXMLArchive
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
// Description:  The XML Archive class
//

#ifndef __SFL_XMLARCHIVE_H__
#define __SFL_XMLARCHIVE_H__

#pragma warning (disable : 4430)

#include <foundation\XMLSerCore\XMLCommon.h>
//#include <foundation\String\sflstring.h>
#include <StingrayExportDefs.h>

namespace stingray {
	namespace foundation {

#define MAX_TAGNAME_SIZE 128

// forward declaration [hack] for non-MFC build configurations
#ifndef _MFC_VER
class CDocument;
#endif;

///////////////////////////////////////////////////////////////////////////
//@doc SECXMLArchive
//@class SECXMLArchive | SECXMLArchive is the CArchive equivalent of MFC's binary serialization architecture. 
// However unlike CArchive, SECXMLArchive is just an interface and the actual implementation is 
// provided in the SECXMLDOMArchive derived class.
//
//@mfunc | SECXMLArchive | SECXMLArchive | Constructor.
//@parm LPCTSTR | fileName | Reference to a file.
//@parm UINT | nMode | Specifies the mode in which the archive is to be created.
//@parm LPCTSTR | rootTagName | The root tag name of the resultant document. Useful only while saving.
//@parmopt LPCTSTR | headerInfo | NULL | The header info to be put in the document. Useful only while saving.
//
//@mfunc BOOL | SECXMLArchive | IsLoading | Lets you check if the archive is loading an XML file.
//@rdesc TRUE if the archive is loading; FALSE otherwise
//
//@mfunc BOOL | SECXMLArchive | IsStoring | Lets you check if the archive is storing an XML file.
//@rdesc TRUE if the archive is storing; FALSE otherwise
//
//@mfunc LPCTSTR | SECXMLArchive | GetFile | Returns the name associated with the archive.
//@rdesc A string with the name of the file associated with the archive.
//
//@mfunc virtual void | SECXMLArchive | Close | Saves the current document content to the file 
// immediately (useful only while writing) and disconnects from the file.
//
//@mfunc virtual void | SECXMLArchive | CleanUp | Abort without saving the document 
// (useful only while writing) and disconnects from the file.
//
//@mfunc virtual BOOL | SECXMLArchive | OpenElement | Creates a new element with the specified
// tagName while saving and creates all new elements a children of this element until a 
// corresponding CloseElement call has been made. Looks for the specified element while loading and
// if available makes it the current parent element from which all future searches for elements
// will be made.
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be created.
//@parmopt BOOL | bAssertOnFailure | FALSE | Specifies if function should ASSERT if tag was not found.
//@xref <c SECXMLArchive>
//
//@mfunc virtual BOOL | SECXMLArchive | CloseElement | Closes a currently open element (made 
// with a call to OpenElement. Make sure to always close an Opened element when you are done with it.
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be created.
//@xref <c SECXMLArchive>
//
//@mfunc SECXMLArchive& | SECXMLArchive | Write | Creates a new element with the specified tagname and stores the value as a child 
// Text Element of the new element. The new element is made the child of the current parent Element.
//@syntax Write(LPCTSTR tagName, BYTE by)
//@syntax Write(LPCTSTR tagName, WORD w)
//@syntax Write(LPCTSTR tagName, LONG l)
//@syntax Write(LPCTSTR tagName, DWORD dw)
//@syntax Write(LPCTSTR tagName, float f)
//@syntax Write(LPCTSTR tagName, double d)
//@syntax Write(LPCTSTR tagName, int i)
//@syntax Write(LPCTSTR tagName, short w)
//@syntax Write(LPCTSTR tagName, unsigned u)
//@syntax Write(LPCTSTR tagName, LPCTSTR str, long type = 3/*NODE_TEXT*/)
//@syntax Write(LPCTSTR tagName, const void* lpBuf, UINT nMax, int encodeType = SEC_BASE64)
//@syntax Write(LPCTSTR contextTagName, IXMLSerialize* pFormatter)
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be created.
//@parm BYTE | by | The byte value to be stored.
//@parm WORD | w | The WORD value to be stored.
//@parm LONG | l | The LONG value to be stored.
//@parm DWORD | dw | The DWORD value to be stored.
//@parm float | f | The float value to be stored.
//@parm double | db | The double value to be stored.
//@parm int | n | The int value to be stored.
//@parm short | sh | The short value to be stored.
//@parm unsigned | ui | The unsigned value to be stored.
//@parm LPCTSTR | str | The string value to be stored.
//@parmopt int | type | 3 | Type specifies whether to store it as string value (NODE_TEXT) the default
// or NODE_CDATA_SECTION
//@parm const void* | lpBuf | The buffer containing the binary stream to be stored.
//@parm UINT | nMax | Specifies the size of the buffer.
//@parmopt int | encodeType | SEC_BASE64 | The encode type to be used - base64 or quoted printable
//@parm IXMLSerialize* | pFormatter | A reference to a formatter which has XMLSerialize overriden
// and whose elements are stored as children of the newly created element.
//@rdesc A reference to itself.
//@xref <c SECXMLArchive>
//
//@mfunc BOOL | SECXMLArchive | Read | Looks for an element with the specified tag name under the current Parent Element 
// in the XML DOM and reads the data into the out parameter.
//@syntax Read(LPCTSTR tagName, BYTE& by, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, WORD& w, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, DWORD& dw, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, LONG& l, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, float& f, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, double& d, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, int& i, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, short& w, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, char& ch, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, unsigned& u, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, LPTSTR& lpBuff, UINT& nLen, BOOL bAssertOnFailure = FALSE, BOOL bTruncateOnOverflow = FALSE)
//@syntax Read(LPCTSTR tagName, void*& lpBuf, UINT& nBuffLen, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR contextTagName, IXMLSerialize* pFormatter, BOOL bAssertOnFailure = FALSE)
//@syntax Read(LPCTSTR tagName, CString& string, BOOL bAssertOnFailure = FALSE)
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be retrieved.
//@parm BYTE& | by | A reference where the result is stored.
//@parm WORD& | w | A reference where the result is stored.
//@parm DWORD& | dw | A reference where the result is stored.
//@parm LONG& | l | A reference where the result is stored.
//@parm float& | f | A reference where the result is stored.
//@parm double& | d | A reference where the result is stored.
//@parm int& | n | A reference where the result is stored.
//@parm short& | sh | A reference where the result is stored.
//@parm char& | ch | A reference where the result is stored.
//@parm unsigned& | u | A reference where the result is stored.
//@parm LPTSTR& | str | A reference where the result is stored.
//@parm UINT& | nLen | Specifies the size of the buffer.
//@parmopt BOOL | bTruncateOnOverflow | FALSE | Specifies whether the retrieved string should be limited
// to the size specified. If FALSE and if the supplied buffer is not big enough, it is deleted and
// a new buffer created with the necessary size and str is bound to that buffer.
//@parm void*& | lpBuff | A reference where the result is stored.
//@parm UINT& | nBuffLen | Specifies the size of the buffer. If the size is not big enough, nLef is
// updated with the necessary size and the function returns TRUE with no update to lpBuff.
//@parm CString& | str | A reference where the result is stored.
//@parmopt int | type | 3 | Type specifies whether to store it as string value (NODE_TEXT) the default
// or NODE_CDATA_SECTION
//@parm IXMLSerialize* | pFormatter | A reference to a formatter which has XMLSerialize overriden
// and whose Read calls are executed in the context of the newly loaded element.
//@parmopt BOOL | bAssertOnFailure | FALSE | Flag indicated whether function should ASSERT if tag not found.
//@rdesc TRUE if tag found, FALSE otherwise.
//@xref <c SECXMLArchive>
//
//@mfunc BOOL | SECXMLArchive | Serialize | Stores or Loads an element with the specified
// tag name under the current Parent Element in the XML DOM. Calls the corresponding Read or 
// Write based on the context in which the archive was created.
//@syntax BOOL Serialize(LPCTSTR tagName, BYTE& by, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, WORD& w, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, DWORD& dw, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, LONG& l, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, float& f, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, double& d, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, int& i, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, short& w, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, char& ch, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, unsigned& u, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, LPTSTR& lpBuff, UINT& nLen, long type = 3/*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE, BOOL bTruncateOnOverflow = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, void*& lpBuf, UINT nLen, int encodeType = SEC_BASE64, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR contextTagName, IXMLSerialize* pFormatter, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, CString& string, long type = 3 /*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE)
//@syntax BOOL Serialize(LPCTSTR tagName, CString*& string, long type = 3 /*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE)
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be stored or retrieved.
//@parm BYTE& | by | An in parameter while storing and out parameter while loading.
//@parm WORD& | w | An in parameter while storing and out parameter while loading.
//@parm DWORD& | dw | An in parameter while storing and out parameter while loading.
//@parm LONG& | l | An in parameter while storing and out parameter while loading.
//@parm float& | f | An in parameter while storing and out parameter while loading.
//@parm double& | d | An in parameter while storing and out parameter while loading.
//@parm int& | i | An in parameter while storing and out parameter while loading.
//@parm short& | sh | An in parameter while storing and out parameter while loading.
//@parm char& | ch | An in parameter while storing and out parameter while loading.
//@parm unsigned& | ui | An in parameter while storing and out parameter while loading.
//@parm LPTSTR& | lpBuff | An in parameter while storing and out parameter while loading.
//@parm UINT& | nLen | Specifies the size of the buffer.
//@parmopt int | type | 3 | Type specifies whether to store it as string value (NODE_TEXT) the default
// or NODE_CDATA_SECTION
//@parm void*& | lpBuf | An in parameter while storing and out parameter while loading.
//@parm int | encodeType | Type specifies the encoding type to use - base64 or printed quotable.
//@parm CString& | str | An in parameter while storing and out parameter while loading.
//@parmopt int | type | 3 | Type specifies whether to store it as string value (NODE_TEXT) the default
// or NODE_CDATA_SECTION
//@parm CString* | pStr | An in parameter while storing and out parameter while loading.
//@parm IXMLSerialize* | pFormatter | A reference to a formatter which has XMLSerialize overriden
// and whose serialization calls are executed in the context of the newly loaded element.
//@parmopt BOOL | bAssertOnFailure | FALSE | Flag indicated whether function should ASSERT if tag not found.
//@parmopt BOOL | bTruncateOnOverflow | FALSE | Specifies whether the retrieved string should be limited
// to the size specified. If FALSE and if the supplied buffer is not big enough, it is deleted and
// a new buffer created with the necessary size and str is bound to that buffer.
//@rdesc TRUE if tag found, FALSE otherwise. Useful only while loading.
//@xref <c SECXMLArchive>
//
//
//@mfunc BOOL | SECXMLArchive | IsElementAvailable | Lets you find out if an element is available within
// the current parent element.
//@parm LPCTSTR | tagName | Specifies the tag name of the element to be searched for.
//@rdesc TRUE if tag found, FALSE otherwise.
//@xref <c SECXMLArchive>
class SECXMLArchive
{
public:
//@doc SECXMLArchive
//@enum Mode |
// The mode in which the archive is to be created. To be specified in the constructor.
	enum Mode { 
		store = 0,	//@emem Specifies archive is created to Save XML into a file
		load = 1	//@emem Specifies archive is created to Load XML from a file
	};
//@doc SECXMLArchive
//@enum EncodeType |
// The encoding type to be used while storing binary data.
	enum EncodeType 
	{
		SEC_BASE64 = 0,	//@emem Use base64 encoding method
		SEC_QUOTED_PRINTABLE = 1 //@emem Use quoted printable encoding method
	};

	//@cmember
	/* Constructor */
	FOUNDATION_API SECXMLArchive(LPCTSTR fileName, UINT nMode, LPCTSTR rootTagName, LPCTSTR headerInfo = NULL);
//#ifndef _SFL_MFC_SUPPORT
//	virtual ~SECXMLArchive(){}
//#else
	FOUNDATION_API virtual ~SECXMLArchive();
//#endif


	// Attributes
	//@cmember
	/* Check if archiver was created to load a file. */
	inline BOOL IsLoading() const{return (m_nMode == load)?TRUE:FALSE;}
	//@cmember
	/* Check if archiver was created to save a file. */
	inline BOOL IsStoring() const{return (m_nMode == store)?TRUE:FALSE;}

	//@cmember
	/* Get the underlying file bound to the archive. */
	inline LPCTSTR GetFile() const{return m_strFilePath;}

	//Operations
	//@cmember
	/* Saves the current document content to the file (useful only while writing) and disconnects from the file.*/
//#ifndef _SFL_MFC_SUPPORT
//	virtual void Close(){}
//#else
	FOUNDATION_API virtual void Close();
//#endif

	//@cmember
	/* Abort without saving the document (useful only while writing) and disconnects from the file.*/
//#ifndef _SFL_MFC_SUPPORT
//	virtual void CleanUp(){}
//#else
	FOUNDATION_API virtual void CleanUp();
//#endif

	//@cmember
	/* Open an element into which data is to be read or written. */
	virtual BOOL OpenElement(LPCTSTR tagName, BOOL bAssertOnFailure = FALSE) = 0;
	//@cmember
	/* Close the previously openend element. */
	virtual void CloseElement(LPCTSTR tagName) = 0;

	// insertion operations
	//@cmember
	/* Write the fundamental data types into the archive */
	virtual SECXMLArchive& Write(LPCTSTR tagName, BYTE by) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, WORD w) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, LONG l) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, DWORD dw) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, float f) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, double d) = 0;

	virtual SECXMLArchive& Write(LPCTSTR tagName, int i) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, short w) = 0;
//	virtual SECXMLArchive& Write(LPCTSTR tagName, TCHAR ch) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, unsigned u) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, LPCTSTR str, long type = 3/*NODE_TEXT*/) = 0;
	virtual SECXMLArchive& Write(LPCTSTR tagName, const void* lpBuf, UINT nMax, int encodeType = SEC_BASE64) = 0;

	virtual SECXMLArchive& Write(LPCTSTR contextTagName, IXMLSerialize* pFormatter) = 0;

	// extraction operation
	//@cmember
	/* Read the fundamental data types into the archive */
	virtual BOOL Read(LPCTSTR tagName, BYTE& by, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, WORD& w, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, DWORD& dw, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, LONG& l, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, float& f, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, double& d, BOOL bAssertOnFailure = FALSE) = 0;

	virtual BOOL Read(LPCTSTR tagName, int& i, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, short& w, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, char& ch, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, unsigned& u, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, LPTSTR& lpBuff, UINT& nLen, BOOL bAssertOnFailure = FALSE, BOOL bTruncateOnOverflow = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, void*& lpBuf, UINT& nLen, BOOL bAssertOnFailure = FALSE) = 0;

	virtual BOOL Read(LPCTSTR contextTagName, IXMLSerialize* pFormatter, BOOL bAssertOnFailure = FALSE) = 0;
	virtual BOOL Read(LPCTSTR tagName, CString& string, BOOL bAssertOnFailure = FALSE) = 0;


	// Single interface for both Read and Write
	//@cmember
	/* Read or Write the fundamental data types into the archive */
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, BYTE& by, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, WORD& w, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, DWORD& dw, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, LONG& l, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, float& f, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, double& d, BOOL bAssertOnFailure = FALSE);

	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, int& i, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, short& w, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, char& ch, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, unsigned& u, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, LPTSTR& lpBuff, UINT& nLen, long type = 3/*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE, BOOL bTruncateOnOverflow = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, void*& lpBuf, UINT nLen, int encodeType = SEC_BASE64, BOOL bAssertOnFailure = FALSE);

	FOUNDATION_API BOOL Serialize(LPCTSTR contextTagName, IXMLSerialize* pFormatter, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, CString& string, long type = 3 /*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE);
	FOUNDATION_API BOOL Serialize(LPCTSTR tagName, CString*& string, long type = 3 /*NODE_TEXT*/, BOOL bAssertOnFailure = FALSE);

	//@cmember
	/* Check if an element with the specified tag is available.*/
	FOUNDATION_API BOOL IsElementAvailable(LPCTSTR tagName);

//#ifndef _WIN64
	CDocument* m_pDocument;
//#endif //_WIN64

protected:
	UINT m_nMode;
	LPTSTR m_strFilePath;
};

}; // namespace stingray::foundation
}; // namespace stingray


#endif	//__SFL_XMLARCHIVE_H__
