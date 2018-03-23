///////////////////////////////////////////////////////////////////////////////
// XMLValueTypes.h : MFC Simple Types Formatters
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
// Description:  XML Formatter classes for the MFC simple value types
//

#ifndef __SFL_XMLVALTYPEFTRS_H__
#define __SFL_XMLVALTYPEFTRS_H__

#include <foundation\XMLSerCore\XMLArch.h>
#include <StingrayExportDefs.h>

namespace stingray {
	namespace foundation {

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the MFC CRect class

#ifndef __CRECTFTR__
#define __CRECTFTR__

///////////////////////////////////////////////////////////////////////////
//@doc CRectFTR
//
//@mfunc | CRectFTR | CRectFTR | Constructor. 
//@parm CRect*& | ptrObj | Reference to a CRect pointer.
//@parm LPCTSTR | strTag = _T("CRect") | XML tagname for the CRect class.
//
//@class CRectFTR | CRectFTR is the XML formatter for the MFC CRect class. Implementations of XMLSerialize() that
// attempt to serialize a CRect, should create an instance of the CRectFTR class, initialize it with the CRect
// object and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//
class CRectFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CRectFTR(CRect*& ptrObj, LPCTSTR strTag=_T("CRect"))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)	{ }

	virtual ~CRectFTR()
	{
	}

	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar.Write(_T("Left"), m_ptrObj->left);
			ar.Write(_T("Top"), m_ptrObj->top);
			ar.Write(_T("Right"), m_ptrObj->right);
			ar.Write(_T("Bottom"), m_ptrObj->bottom);					
		}
		else
		{
			ar.Read(_T("Left"), m_ptrObj->left);
			ar.Read(_T("Top"), m_ptrObj->top);
			ar.Read(_T("Right"), m_ptrObj->right);			
			ar.Read(_T("Bottom"), m_ptrObj->bottom);
		}
	}

protected:
	CRect*& m_ptrObj;
};

#endif // __CRECTFTR__

//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the MFC CPoint class

#ifndef __CPOINTFTR__
#define __CPOINTFTR__

///////////////////////////////////////////////////////////////////////////
//@doc CPointFTR
//
//@mfunc | CPointFTR | CPointFTR | Constructor. 
//@parm CPoint*& | ptrObj | Reference to a CPoint pointer.
//@parm LPCTSTR | strTag = _T("CPoint") | XML tagname for the CPoint class.
//
//@class CPointFTR | CPointFTR is the XML formatter for the MFC CPoint class. Implementations of XMLSerialize() that
// attempt to serialize a CPoint, should create an instance of the CPointFTR class, initialize it with the CPoint
// object and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//

class CPointFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CPointFTR(CPoint*& ptrObj, LPCTSTR strTag=_T("CPoint"))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)	{ }

	virtual ~CPointFTR()
	{
	}

	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar.Write(_T("XVal"), m_ptrObj->x);
			ar.Write(_T("YVal"), m_ptrObj->y);
		}
		else
		{
			ar.Read(_T("XVal"), m_ptrObj->x);
			ar.Read(_T("YVal"), m_ptrObj->y);
		}
	}

protected:
	CPoint*& m_ptrObj;
};


#endif // __CPOINTFTR__

//
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// XML Formatter for the MFC CSize class

#ifndef __CSIZEFTR__
#define __CSIZEFTR__

///////////////////////////////////////////////////////////////////////////
//@doc CSizeFTR
//
//@mfunc | CSizeFTR | CSizeFTR | Constructor. 
//@parm CSize*& | ptrObj | Reference to a CSize pointer.
//@parm LPCTSTR | strTag = _T("CSize") | XML tagname for the CSize class.
//
//@class CSizeFTR | CSizeFTR is the XML formatter for the MFC CSize class. Implementations of XMLSerialize() that
// attempt to serialize a CSize, should create an instance of the CSizeFTR class, initialize it with the CSize
// object and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//

class CSizeFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CSizeFTR(CSize*& ptrObj, LPCTSTR strTag=_T("CSize"))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)	{ }

	virtual ~CSizeFTR()
	{
	}

	virtual void XMLSerialize(SECXMLArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar.Write(_T("XExt"), m_ptrObj->cx);
			ar.Write(_T("YExt"), m_ptrObj->cy);
		}
		else
		{
			ar.Read(_T("XExt"), m_ptrObj->cx);
			ar.Read(_T("YExt"), m_ptrObj->cy);
		}
	}

protected:
	CSize*& m_ptrObj;
};

#endif // __CSIZEFTR__

//
///////////////////////////////////////////////////////////////////////////

}; // namespace stingray::foundation
}; // namespace stingray


#endif	//__SFL_XMLVALTYPEFTRS_H__