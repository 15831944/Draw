///////////////////////////////////////////////////////////////////////////////
// XMLCollFormatters.h : MFC Collection formatters
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
//
// Authors:      Praveen Ramesh and Prakash Surendra
// Description:  XML Formatter classes for the MFC collection types that support Serialization
//

#ifndef __SFL_XMLCOLLFTRS_H__
#define __SFL_XMLCOLLFTRS_H__

#include <foundation\XMLSerCore\XMLArch.h>
#include <foundation\XMLSerCore\XMLFTRFactory.h>
#include <StingrayExportDefs.h>

#pragma warning(disable : 4097)

namespace stingray {
	namespace foundation {

extern SECXMLFormatterFactory _FTRFactory;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SerializeData function used by the CObject* serialization routines implemented by the formatter classes

template<class _type>
void SerializeObjData_T(SECXMLArchive& ar, _type& val)
{
	SECXMLFormatterFactory* pFactory = SECXMLGetFTRFactory();
	ASSERT(pFactory != NULL);
	CXMLSerializeImp* pFTR = NULL;
	if(ar.IsStoring())
	{
		if(val == NULL)
			return;
		// Get the formatter for this object from the XML object factory
		pFactory->GetFTRFromObject((CObject*&)val, pFTR);
		ASSERT(pFTR != NULL);

		TCHAR type[128];
		pFTR->GetElementType(type);
		ar.Write(_T("Type"), type);
		ar.Write(NULL, pFTR);
	}
	else
	{
		// First read the type tag for this element from the XML archive. Then get the FTR corresponding to this 
		// type tag, from the XML object factory.
		// NOTE: Querying for the FTR using the tag will create an instance of the object for us
		// and passing this on to the IXMLArchive::Read() routine will initialize it from the XML archive.

		val = NULL;
		CString strTag;
		if(!ar.Read(_T("Type"), strTag))
		{
			val = NULL;
			return;	
		}
		pFactory->GetFTRFromTag(strTag, (CObject*&)val, pFTR);
		ASSERT(pFTR != NULL);
		ar.Read(NULL, pFTR);
	}
	if(pFTR)
		delete pFTR;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Router class used by the user-type array/list formatter classes

template<class _dataType>
class CObjectFTR_Router : public CXMLSerializeImp
{
public:
	CObjectFTR_Router(_dataType& ptrObj)
		: CXMLSerializeImp(_T("")), m_ptrObj(ptrObj) {}
	virtual ~CObjectFTR_Router() {}

	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SerializeObjData_T<_dataType>(ar, m_ptrObj);
	}
protected:
	_dataType& m_ptrObj;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatters for the MFC Array collection classes
template< typename _arrBase, typename _dataType >
class CArrayFTRBase : public CXMLSerializeImp
{
typedef void (*PFNSERIALIZEDATA)(SECXMLArchive&, _dataType&);

public:
	CArrayFTRBase(_arrBase*& ptrArray, PFNSERIALIZEDATA pfnSD = NULL, LPCTSTR strElementType = _T("Array"))
		: CXMLSerializeImp(strElementType), m_ptrObj(ptrArray)
	{
		m_pfnSD = pfnSD;
	}
	virtual ~CArrayFTRBase() {}


// Implementation of IXMLSerialize
	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		_arrBase*& m_ptrArray = m_ptrObj;
		if(ar.IsStoring())
		{
#ifdef _WIN64 //RW64
			INT_PTR nLength = m_ptrArray->GetSize();
			ar.Write(_T("Size"), static_cast<unsigned int>(nLength));
#else
			int nLength = m_ptrArray->GetSize();
			ar.Write(_T("Size"), nLength);
#endif //_WIN64
			for(int i=0; i<nLength; i++)
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i);
				_dataType val = (_dataType)m_ptrArray->GetAt(i);
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, val);						
				ar.CloseElement(strElement);
			}
		}
		else
		{
			int nLength;
			ar.Read(_T("Size"), nLength);
			// Clean the array of any existing elements and set this new size
			m_ptrArray->RemoveAll();
			m_ptrArray->SetSize(nLength);
			for(int i=0; i<nLength; i++)
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i);
				_dataType val;
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, val);
				ar.CloseElement(strElement);
				m_ptrArray->SetAt(i, val);
			}			
		}
	}

	SEC_XML_DYNCREATE_OBJECT(_arrBase)

protected:
	PFNSERIALIZEDATA m_pfnSD;
};


///////////////////////////////////////////////////////////////////////////
//@doc CDWordArrayFTR
//
//@mfunc | CDWordArrayFTR | CDWordArrayFTR | Constructor. 
//@parm CDWordArray*& | pDWArray | Reference to a CDWordArray pointer.
//@parm LPCTSTR | strElement = _T("DWordArray") | The XML tagname for the CDWordArray collection.
//
//@class CDWordArrayFTR | The CDWordArrayFTR class is the XML formatter for the MFC CDWordArray collection class. 
// In order to serialize the contents of a CDWordArray, your serialization code should first create an instance of the 
// CDWordArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CArrayFTRBase<lt>CDWordArray,DWORD<gt>
class CDWordArrayFTR : public CArrayFTRBase<CDWordArray, DWORD>
{
typedef CArrayFTRBase< CDWordArray, DWORD> _base;
public:
	static void SerializeData(SECXMLArchive& ar, DWORD& val)
	{
		if(ar.IsStoring())
			ar.Write(_T("DWORD"), val);
		else
			ar.Read(_T("DWORD"), val);
	}

	//@cmember
	/* Constructor.*/
	CDWordArrayFTR(CDWordArray*& pDWArray, LPCTSTR strElement = _T("DWordArray"))
		: _base(pDWArray, SerializeData, strElement) {}
	virtual ~CDWordArrayFTR()	{}

};


///////////////////////////////////////////////////////////////////////////
//@doc CUIntArrayFTR
//
//@mfunc | CUIntArrayFTR | CUIntArrayFTR | Constructor. 
//@parm CUIntArray*& | pUIntArray | Reference to a CUIntArray pointer.
//@parm LPCTSTR | strElement = _T("UIntArray") | The XML tagname for the CUIntArray collection.
//
//@class CUIntArrayFTR | The CUIntArrayFTR class is the XML formatter for the MFC CUIntArray collection class. 
// In order to serialize the contents of a CUIntArray, your serialization code should first create an instance of the 
// CUIntArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CArrayFTRBase<lt>CUIntArray,UINT<gt>
class CUIntArrayFTR : public CArrayFTRBase<CUIntArray, UINT>
{
	typedef CArrayFTRBase<CUIntArray, UINT> _base;
public:
	static void SerializeData(SECXMLArchive& ar, UINT& val)
	{
		if(ar.IsStoring())
			ar.Write(_T("UINT"), val);
		else
			ar.Read(_T("UINT"), val);
	}

	//@cmember
	/* Constructor.*/
	CUIntArrayFTR(CUIntArray*& pUIntArray, LPCTSTR /*strElement = _T("UIntArray")*/)
		: _base(pUIntArray, SerializeData) {}
	virtual ~CUIntArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CWordArrayFTR
//
//@mfunc | CWordArrayFTR | CWordArrayFTR | Constructor. 
//@parm CWordArray*& | pWArray | Reference to a CWordArray pointer.
//@parm LPCTSTR | strElement = _T("WordArray") | The XML tagname for the CWordArray collection.
//
//@class CWordArrayFTR | The CWordArrayFTR class is the XML formatter for the MFC CWordArray collection class. 
// In order to serialize the contents of a CWordArray, your serialization code should first create an instance of the 
// CWordArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CArrayFTRBase<lt>CWordArray,WORD<gt>
class CWordArrayFTR : public CArrayFTRBase<CWordArray, WORD>
{
	typedef CArrayFTRBase<CWordArray, WORD> _base;
public:
	static void SerializeData(SECXMLArchive& ar, WORD& val)
	{
		if(ar.IsStoring())
			ar.Write(_T("WORD"), val);
		else
			ar.Read(_T("WORD"), val);
	}

	//@cmember
	/* Constructor.*/
	CWordArrayFTR(CWordArray*& pWArray, LPCTSTR strElement = _T("WordArray"))
		: _base(pWArray, SerializeData, strElement) {}
	virtual ~CWordArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CStringArrayFTR
//
//@mfunc | CStringArrayFTR | CStringArrayFTR | Constructor. 
//@parm CStringArray*& | pStrArray | Reference to a CStringArray pointer.
//@parm LPCTSTR | strElement = _T("StringArray") | The XML tagname for the CStringArray collection.
//
//@class CStringArrayFTR | The CStringArrayFTR class is the XML formatter for the MFC CStringArray collection class. 
// In order to serialize the contents of a CStringArray, your serialization code should first create an instance of the 
// CStringArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CArrayFTRBase<lt>CStringArray,CString<gt>
class CStringArrayFTR : public CArrayFTRBase<CStringArray, CString>
{
	typedef CArrayFTRBase<CStringArray, CString> _base;
public:
	static void SerializeData(SECXMLArchive& ar, CString& val)
	{
		if(ar.IsStoring()) 
			ar.Write(_T("CString"), val);
		else
			ar.Read(_T("CString"), val);
	}

	//@cmember
	/* Constructor.*/
	CStringArrayFTR(CStringArray*& pStrArray, LPCTSTR strElement = _T("StringArray"))
		: _base(pStrArray, SerializeData, strElement) {}
	virtual ~CStringArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CByteArrayFTR
//
//@mfunc | CByteArrayFTR | CByteArrayFTR | Constructor. 
//@parm CByteArray*& | pBytArray | Reference to a CByteArray pointer.
//@parm LPCTSTR | strElement = _T("ByteArray") | The XML tagname for the CByteArray collection.
//
//@class CByteArrayFTR | The CByteArrayFTR class is the XML formatter for the MFC CByteArray collection class. 
// In order to serialize the contents of a CByteArray, your serialization code should first create an instance of the 
// CByteArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CArrayFTRBase<lt>CByteArray,BYTE<gt>
class CByteArrayFTR : public CArrayFTRBase<CByteArray, BYTE>
{
	typedef CArrayFTRBase<CByteArray, BYTE> _base;
public:
	static void SerializeData(SECXMLArchive& ar, BYTE& val)
	{
		if(ar.IsStoring())
			ar.Write(_T("BYTE"), val);
		else
			ar.Read(_T("BYTE"), val);
	}

	//@cmember
	/* Constructor.*/
	CByteArrayFTR(CByteArray*& pBytArray, LPCTSTR strElement = _T("ByteArray"))
		: _base(pBytArray, SerializeData, strElement) {}
	virtual ~CByteArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CObArrayFTR
//
//@mfunc | CObArrayFTR | CObArrayFTR | Constructor. 
//@parm CObArray*& | pObArray | Reference to a CObArray pointer.
//@parm LPCTSTR | strElement = _T("ObArray") | The XML tagname for the CObArray collection.
//
//@class CObArrayFTR | The CObArrayFTR class is the XML formatter for the MFC CObArray collection class. 
// In order to serialize the contents of a CObArray, your serialization code should first create an instance of the 
// CObArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@comm To enable runtime type discovery and creation, each CObject based class stored in the array must have an
// equivalent XML formatter class registered with the global XML Formatter Factory object.
//
//@base public | CArrayFTRBase<lt>CObArray,CObject*<gt>
class CObArrayFTR : public CArrayFTRBase<CObArray, CObject*>
{
	typedef CArrayFTRBase<CObArray, CObject*> _base;
public:
	//@cmember
	/* Constructor.*/
	CObArrayFTR(CObArray*& pObArray, LPCTSTR strElement = _T("ObArray"))
		: _base(pObArray, SerializeObjData_T<CObject*>, strElement) {}
	virtual ~CObArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CArrayFTR
//
//@mfunc | CArrayFTR | CArrayFTR | Constructor. 
//@parm _array*& | pArray | Reference to a CArray<lt>class TYPE, class ARG_TYPE<gt> pointer.
//@parm LPCTSTR | strElement = _T("Array") | The XML tagname for the CArray collection.
//
//@class CArrayFTR | The CArrayFTR class is the XML formatter for the MFC CArray collection template class. 
// In order to serialize the contents of a CArray, your serialization code should first create an instance of the 
// CArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _type | Template parameter specifying the type of objects stored in the array.
//@tcarg class | _argType | Argument type used to access objects stored in the array.
//@tcarg class | _dataFTR | XML formatter for the data type stored in the array.
//
//@base public | CArrayFTRBase<lt>CArray<lt>_type,_argType<gt>,_type<gt>
template<class _type, class _argType, class _dataFTR>
class CArrayFTR : public CArrayFTRBase< CArray<_type, _argType>, _type >
{
	typedef CArray<_type, _argType> _array;
	typedef CArrayFTRBase<_array, _type> _base;
public:
	static void SerializeData(SECXMLArchive& ar, _type& val)
	{
		_type* pType = &val;
		if(ar.IsStoring())
			ar.Write(NULL, _dataFTR(pType));
		else
			ar.Read(NULL, _dataFTR(pType));
	}

	//@cmember
	/* Constructor.*/
	CArrayFTR(_array*& pArray, LPCTSTR strElement = _T("Array"))
		:_base(pArray, SerializeData, strElement) {}
	virtual ~CArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CPtrArrayFTR
//
//@mfunc | CPtrArrayFTR | CPtrArrayFTR | Constructor. 
//@parm CPtrArray*& | pArray | Reference to a CPtrArray pointer.
//@parm LPCTSTR | strElement = _T("PtrArray") | The XML tagname for the CPtrArray collection.
//
//@class CPtrArrayFTR | The CPtrArrayFTR class is the XML formatter for the MFC CPtrArray collection class. 
// In order to serialize the contents of a CPtrArray, your serialization code should first create an instance of the 
// CPtrArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _dataType | Template parameter specifying the type of objects stored in the array.
//@tcarg class | _dataFTR | XML formatter for the data type stored in the array.
//
//@base public | CArrayFTRBase<lt>CPtrArray,_dataType*<gt>
template<class _dataType, class _dataFTR>
class CPtrArrayFTR : public CArrayFTRBase<CPtrArray, _dataType*>
{
	typedef CArrayFTRBase<CPtrArray, _dataType*> _base;
public:
	static void SerializeData(SECXMLArchive& ar, _dataType*& val)
	{
		if(ar.IsStoring())
		{
			if(val != NULL)
				ar.Write(NULL, _dataFTR(val));
		}
		else
		{
			val = NULL;
			ar.Read(NULL, _dataFTR(val));
		}
	}

	//@cmember
	/* Constructor.*/
	CPtrArrayFTR(CPtrArray*& pArray, LPCTSTR strElementType = _T("PtrArray"))
		:_base(pArray, SerializeData, strElementType) {}
	virtual ~CPtrArrayFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CTypedPtrArrayFTR
//
//@mfunc | CTypedPtrArrayFTR | CTypedPtrArrayFTR | Constructor. 
//@parm _array*& | pArray | Reference to a CTypedPtrArray<lt>class BASE_CLASS, class TYPE<gt> pointer.
//@parm LPCTSTR | strElement = _T("TypedPtrArray") | The XML tagname for the CTypedPtrArray collection.
//
//@class CTypedPtrArrayFTR | The CTypedPtrArrayFTR class is the XML formatter for the MFC CTypedPtrArray collection template 
// class. In order to serialize the contents of a CTypedPtrArray, your serialization code should first create an instance of the 
// CTypedPtrArrayFTR class, initialize it with the array object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _arrBase | Template parameter specifying the base class of the typed pointer array class.
//@tcarg class | _dataType | Template parameter specifying the type of objects stored in the array.
//@tcarg class | _dataFTR=CObjectFTR_Router<lt>_dataType<gt> | XML formatter for the data type stored in the array. 
//
//@comm The CObjectFTR_Router<lt>_dataType<gt> default option serves as a step-in when using the CTypedPtrArray with a CObArray and the XML 
// Formatter Factory.
//
//@base public | CArrayFTRBase<lt>CTypedPtrArray<lt>_arrBase,_dataType<gt>,_dataType<gt>
template<class _arrBase, class _dataType, class _dataFTR = CObjectFTR_Router<_dataType> >
class CTypedPtrArrayFTR : public CArrayFTRBase< CTypedPtrArray<_arrBase, _dataType>, _dataType >
{
	typedef CTypedPtrArray<_arrBase, _dataType> _array;
	typedef CArrayFTRBase<_array, _dataType> _base;
public:	
	static void SerializeData(SECXMLArchive& ar, _dataType& val)
	{
		if(ar.IsStoring())
		{
			if(val != NULL)
				ar.Write(NULL, _dataFTR(val));
		}
		else
		{
			val = NULL;
			ar.Read(NULL, _dataFTR(val));
		}
	}	

	//@cmember
	/* Constructor.*/
	CTypedPtrArrayFTR(_array*& pArray, LPCTSTR strElement = _T("TypedPtrArray"))
		:_base(pArray, SerializeData, strElement) {}
	virtual ~CTypedPtrArrayFTR() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatter for the MFC List collection classes

template< typename _listBase, typename _dataType >
class CListFTRBase : public CXMLSerializeImp
{
typedef void (*PFNSERIALIZEDATA)(SECXMLArchive&, _dataType&);

public:
	CListFTRBase(_listBase*& ptrList, PFNSERIALIZEDATA pfnSD = NULL, LPCTSTR strElement = _T("List"))
		: CXMLSerializeImp(strElement), m_ptrObj(ptrList)
	{
		m_pfnSD = pfnSD;
	}
	virtual ~CListFTRBase() {}


// Implementation of IXMLSerialize
	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		_listBase* m_ptrList = m_ptrObj;
		if(ar.IsStoring())
		{
#ifdef _WIN64 //RW64
			INT_PTR nLength = m_ptrList->GetCount();
			ar.Write(_T("Size"), static_cast<unsigned int>(nLength));
#else
			int nLength = m_ptrList->GetCount();
			ar.Write(_T("Size"), nLength);
#endif //_WIN64
			int i = 0;
			for(POSITION pos = m_ptrList->GetHeadPosition(); pos != NULL; )
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i++);
				_dataType val = (_dataType)m_ptrList->GetNext(pos);
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, val);
				ar.CloseElement(strElement);
			}			
		}
		else
		{
			int nLength;
			ar.Read(_T("Size"), nLength);
			// Clean the list of any existing elements
			m_ptrList->RemoveAll();
			for(int i=0; i<nLength; i++)
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i);
				_dataType val;
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, val);
				ar.CloseElement(strElement);
				m_ptrList->AddTail(val);
			}			
		}
	}

	SEC_XML_DYNCREATE_OBJECT(_listBase)

protected:
	PFNSERIALIZEDATA m_pfnSD;
};


///////////////////////////////////////////////////////////////////////////
//@doc CStringListFTR
//
//@mfunc | CStringListFTR | CStringListFTR | Constructor. 
//@parm CStringList*& | pList | Reference to a CStringList pointer.
//@parm LPCTSTR | strElement = _T("StringList") | The XML tagname for the CStringList collection.
//
//@class CStringListFTR | The CStringListFTR class is the XML formatter for the MFC CStringList collection class. 
// In order to serialize the contents of a CStringList, your serialization code should first create an instance of the 
// CStringListFTR class, initialize it with the list object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@base public | CListFTRBase<lt>CStringList,CString<gt>
class CStringListFTR : public CListFTRBase<CStringList, CString>
{
	typedef CListFTRBase<CStringList, CString> _base;
public:
	static void SerializeData(SECXMLArchive& ar, CString& val)
	{
		if(ar.IsStoring())
			ar.Write(_T("CString"), val);
		else
			ar.Read(_T("CString"), val);			
	}

	//@cmember
	/* Constructor.*/
	CStringListFTR(CStringList*& pList, LPCTSTR strElement = _T("StringList"))
		: _base(pList, SerializeData, strElement) {}
	virtual ~CStringListFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CObListFTR
//
//@mfunc | CObListFTR | CObListFTR | Constructor. 
//@parm CObList*& | pList | Reference to a CObList pointer.
//@parm LPCTSTR | strElement = _T("ObList") | The XML tagname for the CObList collection.
//
//@class CObListFTR | The CObListFTR class is the XML formatter for the MFC CObList collection class. 
// In order to serialize the contents of a CObList, your serialization code should first create an instance of the 
// CObListFTR class, initialize it with the list object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@comm To enable runtime type discovery and creation, each CObject based class stored in the list must have an
// equivalent XML formatter class registered with the global SFL XML Formatter Factory object.
//
//@base public | CListFTRBase<lt>CObList,CObject*<gt>
class CObListFTR : public CListFTRBase<CObList, CObject*>
{
	typedef CListFTRBase<CObList, CObject*> _base;
public:
	//@cmember
	/* Constructor.*/
	CObListFTR(CObList*& pList, LPCTSTR strElement = _T("ObList"))
		: _base(pList, SerializeObjData_T<CObject*>, strElement) {}	
	virtual ~CObListFTR() {}

	virtual void GetElementType(LPTSTR lpType)
	{
		ASSERT(lpType != NULL);
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(lpType, _T("CObList"));
	}
};


///////////////////////////////////////////////////////////////////////////
//@doc CPtrListFTR
//
//@mfunc | CPtrListFTR | CPtrListFTR | Constructor. 
//@parm CPtrList*& | pList | Reference to a CPtrList pointer.
//@parm LPCTSTR | strElement = _T("PtrList") | The XML tagname for the CPtrList collection.
//
//@class CPtrListFTR | The CPtrListFTR class is the XML formatter for the MFC CPtrList collection class. 
// In order to serialize the contents of a CPtrList, your serialization code should first create an instance of the 
// CPtrListFTR class, initialize it with the list object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _dataType | Template parameter specifying the type of objects stored in the list.
//@tcarg class | _dataFTR | XML formatter for the data type stored in the list.
//
//@base public | CListFTRBase<lt>CPtrList,_dataType*<gt>
template<class _dataType, class _dataFTR>
class CPtrListFTR : public CListFTRBase<CPtrList, _dataType*>
{
	typedef CListFTRBase<CPtrList, _dataType*> _base;
public:
	static void SerializeData(SECXMLArchive& ar, _dataType*& val)
	{
		if(ar.IsStoring())
		{
			if(val != NULL)
				ar.Write(NULL, _dataFTR(val));
		}
		else
		{
			val = NULL;
			ar.Read(NULL, _dataFTR(val));
		}
	}

	//@cmember
	/* Constructor.*/
	CPtrListFTR(CPtrList*& pList,  LPCTSTR strElement = _T("PtrList"))
		:_base(pList, SerializeData, strElement) {}
	virtual ~CPtrListFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CTypedPtrListFTR
//
//@mfunc | CTypedPtrListFTR | CTypedPtrListFTR | Constructor. 
//@parm _list*& | pList | Reference to a CTypedPtrList<lt>class BASE_CLASS, class TYPE<gt> pointer.
//@parm LPCTSTR | strElement = _T("TypedPtrList") | The XML tagname for the CTypedPtrList collection.
//
//@class CTypedPtrListFTR | The CTypedPtrListFTR class is the XML formatter for the MFC CTypedPtrList collection template 
// class. In order to serialize the contents of a CTypedPtrList, your serialization code should first create an instance of the 
// CTypedPtrListFTR class, initialize it with the list object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _listBase | Template parameter specifying the base class of the typed pointer list class.
//@tcarg class | _dataType | Template parameter specifying the type of objects stored in the list.
//@tcarg class | _dataFTR=CObjectFTR_Router<lt>_dataType<gt> | XML formatter for the data type stored in the list.
//
//@comm The CObjectFTR_Router<lt>_dataType<gt> default option serves as a step-in when using the CTypedPtrList with a CObList and the XML 
// Formatter Factory.
//
//@base public | CListFTRBase<lt>CTypedPtrList<lt>_listBase,_dataType<gt>,_dataType<gt>
template<class _listBase, class _dataType, class _dataFTR = CObjectFTR_Router<_dataType> >
class CTypedPtrListFTR : public CListFTRBase< CTypedPtrList<_listBase, _dataType>, _dataType >
{
	typedef CTypedPtrList<_listBase, _dataType> _list;
	typedef CListFTRBase<_list, _dataType> _base;
public:	
	static void SerializeData(SECXMLArchive& ar, _dataType& val)
	{
		if(ar.IsStoring())
		{
			if(val != NULL)
				ar.Write(NULL, _dataFTR(val));
		}
		else
		{
			val = NULL;
			ar.Read(NULL, _dataFTR(val));
		}
	}	

	//@cmember
	/* Constructor.*/
	CTypedPtrListFTR(_list*& pList,  LPCTSTR strElement = _T("TypedPtrList"))
		:_base(pList, SerializeData, strElement) {}
	virtual ~CTypedPtrListFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CListFTR
//
//@mfunc | CListFTR | CListFTR | Constructor. 
//@parm _list*& | pList | Reference to a CList pointer.
//@parm LPCTSTR | strElement = _T("List") | The XML tagname for the CList collection.
//
//@class CListFTR | The CListFTR class is the XML formatter for the MFC CList collection template class. 
// In order to serialize the contents of a CList, your serialization code should first create an instance of the 
// CListFTR class, initialize it with the list object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg class | _type | Template parameter specifying the type of objects stored in the list.
//@tcarg class | _argType | Argument type used to access objects stored in the list.
//@tcarg class | _dataFTR | XML formatter for the data type stored in the list.
//
//@base public | CListFTRBase<lt>CList<lt>_type,_argType<gt>,_type<gt>
template<class _type, class _argType, class _dataFTR>
class CListFTR : public CListFTRBase< CList<_type, _argType>, _type >
{
	typedef CList<_type, _argType> _list;
	typedef CListFTRBase<_list, _type> _base;
public:
	static void SerializeData(SECXMLArchive& ar, _type& val)
	{
		_type* pType = &val;
		if(ar.IsStoring())
			ar.Write(NULL, _dataFTR(pType));
		else
			ar.Read(NULL, _dataFTR(pType));
	}

	//@cmember
	/* Constructor.*/
	CListFTR(_list*& pList,  LPCTSTR strElement = _T("List"))
		:_base(pList, SerializeData, strElement) {}
	virtual ~CListFTR() {}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatter for the MFC Map collection classes

template< typename _mapBase, typename _key, typename _value>
class CMapFTRBase : public CXMLSerializeImp
{
typedef void (*PFNSERIALIZEDATA)(SECXMLArchive&, _key&, _value&);

public:
	CMapFTRBase(_mapBase*& ptrMap, PFNSERIALIZEDATA pfnSD = NULL, LPCTSTR strElementType = _T("Map"))
		: CXMLSerializeImp(strElementType), m_ptrObj(ptrMap)
	{
		m_pfnSD = pfnSD;
	}
	virtual ~CMapFTRBase() {}


// Implementation of IXMLSerialize
	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		_mapBase* m_ptrMap = m_ptrObj;
		if(ar.IsStoring())
		{
			ar.Write(_T("Size"), static_cast<unsigned int>(m_ptrMap->GetCount()));

			_key key;
			_value value;
			POSITION pos;
			int i = 0;
			for( pos = m_ptrMap->GetStartPosition(); pos != NULL; )
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i++);
				m_ptrMap->GetNextAssoc( pos, key, (void*&)value );
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, key, value);
				ar.CloseElement(strElement);
			}
		}
		else
		{
			int nLength;
			ar.Read(_T("Size"), nLength);
			// Clean the list of any existing elements
			m_ptrMap->RemoveAll();
			for(int i=0; i<nLength; i++)
			{
				CString strElement;
				strElement.Format(_T("Element%d"), i);
				_key key;
				_value value;
				ASSERT(m_pfnSD != NULL);
				ar.OpenElement(strElement);
				(*m_pfnSD)(ar, key, value);
				ar.CloseElement(strElement);
				m_ptrMap->SetAt(key, value);
			}			
		}
	}

	SEC_XML_DYNCREATE_OBJECT(_mapBase)

protected:
	PFNSERIALIZEDATA m_pfnSD;
};


///////////////////////////////////////////////////////////////////////////
//@doc CMapWordToPtrFTR
//
//@mfunc | CMapWordToPtrFTR | CMapWordToPtrFTR | Constructor. 
//@parm CMapWordToPtr*& | pMap | Reference to a CMapWordToPtr pointer.
//@parm LPCTSTR | strElement = _T("WordToRefMap") | The XML tagname for the CMapWordToPtr collection.
//
//@class CMapWordToPtrFTR | The CMapWordToPtrFTR class is the XML formatter for the MFC CMapWordToPtr collection class. 
// In order to serialize the contents of a CMapWordToPtr, your serialization code should first create an instance of the 
// CMapWordToPtrFTR class, initialize it with the map object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg typename | _ptrType | Template parameter specifying the type of pointer stored in the map.
//@tcarg typename | _ptrTypeFTR | XML formatter for the data type stored in the map.
//
//@base public | CMapFTRBase<lt>CMapWordToPtr,WORD,_ptrType*<gt>
template<typename _ptrType, typename _ptrTypeFTR> 
class CMapWordToPtrFTR : public CMapFTRBase<CMapWordToPtr, WORD, _ptrType*>
{
typedef CMapFTRBase<CMapWordToPtr, WORD, _ptrType*> _base;
public:
	static void SerializeData(SECXMLArchive& ar, WORD& key, _ptrType*& value)
	{
		if(ar.IsStoring())
		{
			ar.Write(_T("Key"), key);
			if(value != NULL)
				ar.Serialize(_T("Value"), _ptrTypeFTR(value));
		}
		else
		{
			value = NULL;
			ar.Read(_T("Key"), key);
			ar.Serialize(_T("Value"), _ptrTypeFTR(value));
		}
	}

	//@cmember
	/* Constructor.*/
	CMapWordToPtrFTR(CMapWordToPtr*& pMap, LPCTSTR strElementType = _T("WordToRefMap"))
		: _base(pMap, SerializeData, strElementType) {}
	virtual ~CMapWordToPtrFTR() {}
};


///////////////////////////////////////////////////////////////////////////
//@doc CMapStringToPtrFTR
//
//@mfunc | CMapStringToPtrFTR | CMapStringToPtrFTR | Constructor. 
//@parm CMapStringToPtr*& | pMap | Reference to a CMapStringToPtr pointer.
//@parm LPCTSTR | strElement = _T("StringToRefMap") | The XML tagname for the CMapStringToPtr collection.
//
//@class CMapStringToPtrFTR | The CMapStringToPtrFTR class is the XML formatter for the MFC CMapStringToPtr collection class. 
// In order to serialize the contents of a CMapStringToPtr, your serialization code should first create an instance of the 
// CMapStringToPtrFTR class, initialize it with the map object and then pass the formatter to the SECXMLArchive::Read/Write 
// method. 
//
//@tcarg typename | _ptrType | Template parameter specifying the type of pointer stored in the map.
//@tcarg typename | _ptrTypeFTR | XML formatter for the data type stored in the map.
//
//@base public | CMapFTRBase<lt>CMapStringToPtr,CString,_ptrType*<gt>
template<typename _ptrType, typename _ptrTypeFTR> 
class CMapStringToPtrFTR : public CMapFTRBase<CMapStringToPtr, CString, _ptrType*>
{
typedef CMapFTRBase<CMapStringToPtr, CString, _ptrType*> _base;
public:
	//@cmember
	/* Constructor.*/
	CMapStringToPtrFTR(CMapStringToPtr*& pMap, LPCTSTR strElementType = _T("StringToRefMap"))
		: _base(pMap, SerializeData, strElementType) {}
	virtual ~CMapStringToPtrFTR() {}

	static void SerializeData(SECXMLArchive& ar, CString& key, _ptrType*& value)
	{
		if(ar.IsStoring())
		{
			ar.Write(_T("Key"), key);
			if(value != NULL)
				ar.Serialize(_T("Value"), _ptrTypeFTR(value));
		}
		else
		{
			ar.Read(_T("Key"), key);
			value = NULL;
			ar.Serialize(_T("Value"), _ptrTypeFTR(value));			
		}
	}
};

}; // namespace stingray::foundation
}; // namespace stingray


#endif	//__SFL_XMLCOLLFTRS_H__