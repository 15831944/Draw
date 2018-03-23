///////////////////////////////////////////////////////////////////////////////
// xmlgdiser.h  MFC GDI Formatters
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
// Description:  XML Formatters for the MFC GDI classes
//

#ifndef __SFL_XMLGDIFTRS_H__
#define __SFL_XMLGDIFTRS_H__

#include <foundation\XMLSerCore\xmlarch.h>
#include <StingrayExportDefs.h>

namespace stingray {
	namespace foundation {


///////////////////////////////////////////////////////////////////////////
//@doc CBrushFTR
//
//@mfunc | CBrushFTR | CBrushFTR | Constructor. 
//@parm LOGBRUSH& | lb | Reference to a LOGBRUSH.
//@parm LPCTSTR | strTag = _T("Brush") | XML tagname for the CBrush.
//
//@class CBrushFTR | CBrushFTR is the XML formatter for the MFC CBrush class. Implementations of XMLSerialize() that
// attempt to serialize a CBrush, should create an instance of the CBrushFTR class, initialize it with the LOGBRUSH object
// attached to the CBrush and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//
//@comm Getting a LOGBRUSH instead of a CBrush, since while storing the CBrush contents could contain application
// specifics (like lbHatch pointing to a packed DIB) that are not meant to be persisted, and while reading
// there might be insufficient information to create a CBrush out of the persisted information.
//
class FOUNDATION_API CBrushFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CBrushFTR(LOGBRUSH& lb, LPCTSTR strElementType = _T("Brush")) : CXMLSerializeImp(strElementType), m_lb(lb)	{ };

	virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	LOGBRUSH& m_lb;
};



///////////////////////////////////////////////////////////////////////////
//@doc CPenFTR
//
//@mfunc | CPenFTR | CPenFTR | Constructor. 
//@parm LOGPEN& | lopn | Reference to a LOGPEN.
//@parm LPCTSTR | strTag = _T("Pen") | XML tagname for the CPen.
//
//@class CPenFTR | CPenFTR is the XML formatter for the MFC CPen class. Implementations of XMLSerialize() that
// attempt to serialize a CPen, should create an instance of the CPenFTR class, initialize it with the LOGPEN object
// attached to the CPen and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//
//@comm The formatter references a LOGPEN instead of a CPen, since while storing the CPen contents could contain application
// specifics that are not meant to be persisted, and while reading there might be insufficient information to
// create a CPen out of the persisted information.
//
class FOUNDATION_API CPenFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CPenFTR(LOGPEN& lopn, LPCTSTR strElementType = _T("Pen")) : CXMLSerializeImp(strElementType), m_lopn(lopn)	{ };

	virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	LOGPEN& m_lopn;
};


///////////////////////////////////////////////////////////////////////////
//@doc CFontFTR
//
//@mfunc | CFontFTR | CFontFTR | Constructor. 
//@parm LOGFONT& | lf | Reference to a LOGFONT.
//@parm LPCTSTR | strTag = _T("Font") | XML tagname for the CFont.
//
//@class CFontFTR | CFontFTR is the XML formatter for the MFC CFont class. Implementations of XMLSerialize() that
// attempt to serialize a CFont, should create an instance of the CFontFTR class, initialize it with the LOGFONT object
// attached to the CFont and then pass the formatter to the SECXMLArchive::Read/Write method. 
//
// See Also <c SECXMLArchive> and <c CXMLSerializeImp>
//
//@base public | CXMLSerializeImp
//
//@comm The formatter references a LOGFONT instead of a CFont, since while storing the CFont contents could contain application
// specifics that are not meant to be persisted, and while reading there might be insufficient information to
// create a CFont out of the persisted information.
//
class FOUNDATION_API CFontFTR : public CXMLSerializeImp
{
public:
	//@cmember
	/* Constructor.*/
	CFontFTR(LOGFONT& lf, LPCTSTR strElementType = _T("Font")) : CXMLSerializeImp(strElementType), m_lf(lf)	{ };

	virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	LOGFONT& m_lf;
};

}; // namespace stingray::foundation
}; // namespace stingray

#endif //__SFL_XMLGDIFTRS_H__