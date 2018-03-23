///////////////////////////////////////////////////////////////////////////////
// XMLCommon.h : IXMLSerialize and CXMLSerializeImp
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
// Description:  Definition of the IXMLSerialize interface
//

#ifndef __SFL_XMLCOMMON_H__
#define __SFL_XMLCOMMON_H__

#include <atlbase.h>

//#ifdef _WIN64

#include "tchar.h"
#if(_MSC_VER >= 1310) // MSVC71 and higher
#include <atlstr.h>
#endif // _MSC_VER >= 1301
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG

//#endif // _WIN64


#include <StingrayExportDefs.h>

#include "foundation\string\sflstring.h"

#pragma warning(disable: 4996)

namespace stingray {
	namespace foundation {

class SECXMLArchive;

///////////////////////////////////////////////////////////////////////////
//@doc IXMLSerialize
//
//
//@mfunc void | IXMLSerialize | GetElementType | Returns the XML tag name for this type.
//@rdesc void
//@parm LPTSTR | str | The tag name identifying this type in the XML document.
//
//@mfunc BOOL | IXMLSerialize | IsDataAvailableToWrite | Confirms the availability of persistable data.
//@rdesc TRUE if data is available.
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.
//
//@mfunc void | IXMLSerialize | PreReadXML | Called by the archive object before a read operation.
//@rdesc void
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.
//
//@mfunc void | IXMLSerialize | XMLSerialize | Override XMLSerialize in your formatter and provide the XML format 
// read/write implementation.
//@rdesc void
//@parm SECXMLArchive& | ar | The archive object for serializing the XML formatted data.
//@comm The XMLSerialize routine is analogous to the CObject::Serialize() function. While Serialize() provides a native 
// read/write format, the implementation provided in XMLSerialize will be in an XML format.
//
//@mfunc IXMLSerialize* | IXMLSerialize | operator IXMLSerialize* | Overloaded operator used by the archive object.
//@rdesc An instance of the formatter.
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.
//
//
//@class IXMLSerialize | IXMLSerialize is the core interface for the Stingray XML Serialization Framework. This interface 
// defines various methods that are called, by the XML framework, during various stages of a typical serialization operation. 
// Any class expecting to take part in the serialization should have an XML formatter class that implements the 
// IXMLSerialize interface. To avoid the tedium of implementing the full IXMLSerialize interface each time, user's can 
// simply base their formatters on the CXMLSerializeImp class that provides a partial implementation of IXMLSerialize.
//
//  <mf CXMLSerializeImp::GetElementType>,
//  <mf CXMLSerializeImp::IsDataAvailableToWrite>,
//  <mf CXMLSerializeImp::PreReadXML>,
//  <mf CXMLSerializeImp::XMLSerialize>,
//  <mf CXMLSerializeImp::IXMLSerialize*>
//
// See Also <c CXMLSerializeImp>
//
class IXMLSerialize
{
public:
	//@cmember
	/* Returns the XML tag name.*/
	virtual void GetElementType(LPTSTR str) = 0;
	
	//@cmember
	/* Confirms the availability of persistable data.*/
	virtual BOOL IsDataAvailableToWrite() = 0;

	//@cmember
	/* Called before a read operation.*/
	virtual void PreReadXML()=0;
	
	//@cmember
	/* Serialization function*/
	virtual void XMLSerialize(SECXMLArchive& ar) = 0;
	
	//@cmember
	/* Overloaded operator*/
	virtual operator IXMLSerialize*()=0;
};


///////////////////////////////////////////////////////////////////////////
//@doc CXMLSerializeImp
//
//
//@mfunc | CXMLSerializeImp | CXMLSerializeImp | Constructor. 
//@parm LPCTSTR | strElementType = NULL | The XML tag name identifying this type.
//@comm The tag name can be passed in as the constructor parameter or can be provided in an override of the GetElementType()
// function.
//
//@mfunc | CXMLSerializeImp | ~CXMLSerializeImp | Destructor. 
//
//@mfunc void | CXMLSerializeImp | GetElementType | Override this function to provide the XML tag name.
//@rdesc void
//@parm LPTSTR | str | The tag name identifying this type in the XML document.
//
//@mfunc BOOL | CXMLSerializeImp | IsDataAvailableToWrite | Called by the archive object to verify the presence of persistable 
// data. 
//@rdesc TRUE if data is available.
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.
//
//@mfunc void | CXMLSerializeImp | PreReadXML | Called by the archive object before a read operation.
//@rdesc void
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.
//
//@mfunc void | CXMLSerializeImp | XMLSerialize | Override this function and provide your read/write implementation for 
// the XML serialization.
//@rdesc void
//@parm SECXMLArchive& | ar | The archive object for serializing the XML formatted data.
//@comm The XMLSerialize routine is analogous to the CObject::Serialize() function. While Serialize() provides a native 
// read/write format, the implementation provided in XMLSerialize will be in an XML format.
//
//@mfunc IXMLSerialize* | CXMLSerializeImp | operator IXMLSerialize* | Overloaded operator used by the archive object.
//@rdesc An instance of the formatter.
//@comm CXMLSerializeImp provides a default implementation of this function. It is not necessary to override this method 
// in your formatter class.//
//
//
//@class CXMLSerializeImp | The CXMLSerializeImp class provides a basic implementation of the IXMLSerialize interface. To  
// take part in the serialization process, a formatter class should derive from CXMLSerializeImp and provide an 
// implementation for the IXMLSerialize::XMLSerialize() virtual. During an XML File Open/Save operation, the serialization 
// framework calls the formatter's XMLSerialize() override through the application's document.
//
//  <mf CXMLSerializeImp::GetElementType>,
//  <mf CXMLSerializeImp::IsDataAvailableToWrite>,
//  <mf CXMLSerializeImp::PreReadXML>,
//  <mf CXMLSerializeImp::XMLSerialize>, and
//  <mf CXMLSerializeImp::IXMLSerialize*>
//
// See Also <c IXMLSerialize>
//
//@base public | IXMLSerialize
//

class CXMLSerializeImp : public IXMLSerialize
{
public:
	// Pass in the element type of the underlying object optionally.
	//@cmember
	/* Constructor.*/
	CXMLSerializeImp(LPCTSTR strElementType = NULL)	
	{
		if(strElementType)
		{
			m_strElementType = new TCHAR[_tcslen(strElementType) + 1];
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(m_strElementType, strElementType);
		}else
		{
			m_strElementType = NULL;
		}
	}

	//@cmember
	/* Destructor.*/
	virtual ~CXMLSerializeImp()
	{
		if(m_strElementType) 
		{
			delete [] m_strElementType;
			m_strElementType = NULL;
		}
	}

	//@cmember
	/* Gets the tag name.*/
	virtual void GetElementType(LPTSTR str)
	{
#ifndef _MFC_VER
		if(m_strElementType != NULL) {
#else
		ASSERT(m_strElementType != NULL);
#endif		

		// If you did not supply an element type in the constructor, override this 
		// function in your derived class and provide the element type name
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(str, m_strElementType);
#ifndef _MFC_VER
		}
#endif
	}

	//@cmember
	/* Called to confirm the availability of persistable data.*/
	virtual BOOL IsDataAvailableToWrite(){return TRUE;}

	//@cmember
	/* Called before a read operation.*/
	virtual void PreReadXML(){}

	//@cmember
	/* Serialization function*/
	virtual void XMLSerialize(SECXMLArchive& ar) = 0;

	//@cmember
	/* Overloaded operator*/
	virtual operator IXMLSerialize*(){return this;}

protected:
	LPTSTR m_strElementType;
};

#define SEC_XML_DYNCREATE_OBJECT(classX)	\
protected: \
	classX*& m_ptrObj; \
public: \
	virtual void PreReadXML()	\
{	\
	if(m_ptrObj == NULL)	\
		m_ptrObj = new classX();	\
}	\
	virtual BOOL IsDataAvailableToWrite()	\
{	\
	if(m_ptrObj == NULL)	\
		return FALSE;	\
	else	\
		return TRUE;	\
}

inline CString SECXMLLoadString(UINT nResID)
{
	CString str;
#ifndef _MFC_VER
	str.LoadString(nResID);
#else
	VERIFY(str.LoadString(nResID));
#endif
	return str;
}

}; // namespace stingray::foundation
}; // namespace stingray


#endif //__SFL_XMLCOMMON_H__