///////////////////////////////////////////////////////////////////////////////
// gxxmlser.h
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

#ifndef _GX_XMLSER_
#define _GX_XMLSER_

// Common Library includes
// If Grid is a DLL, then CMN must be a DLL
#ifdef _GXDLL
	#ifndef _SFLDLL
		#define _SFLDLL
	#endif
#endif // _GXDLL

// version info
#define _SFLNOMSG
#include "Foundation\SflCommon.h"

#ifdef WIN32
#include "foundation\SflDef.h"
#endif

#include <foundation\XMLSerialize.h>

using namespace stingray::foundation;

#include "grid\gxoleusr.h"

#include <StingrayExportDefs.h>

//using namespace stingray::foundation;

class CGXDataFTR : public CXMLSerializeImp
{
public:
	inline CGXDataFTR(CGXData*& data, LPCTSTR strElementType = _T("GridData"))
		: CXMLSerializeImp(strElementType), m_ptrObj(data){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXData)
};

class CGXPrintDeviceFTR : public CXMLSerializeImp
{
public:
	inline CGXPrintDeviceFTR(CGXPrintDevice*& dev, LPCTSTR strElementType = _T("PrintDeviceInfo"))
		: CXMLSerializeImp(strElementType), m_ptrObj(dev){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXPrintDevice)

};

class CGXPropertiesFTR : public CXMLSerializeImp
{
public:
	inline CGXPropertiesFTR(CGXProperties*& prop, LPCTSTR strElementType = _T("GridProperties"))
		: CXMLSerializeImp(strElementType), m_ptrObj(prop){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXProperties)
};

class CGXRangeFTR : public CXMLSerializeImp
{
public:
	inline CGXRangeFTR(CGXRange*& pRange, LPCTSTR strElementType = _T("GridRange"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pRange)
        {};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXRange)

};

class CGXStyleFTR : public CXMLSerializeImp
{
public:
	inline CGXStyleFTR(CGXStyle*& style, LPCTSTR strElementType = _T("GridStyle"))
		: CXMLSerializeImp(strElementType), m_ptrObj(style){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXStyle)
};

class CGXStylesMapFTR : public CXMLSerializeImp
{
public:
	inline CGXStylesMapFTR(CGXStylesMap*& stylesMap, LPCTSTR strElementType = _T("GridStylesMap"))
		: CXMLSerializeImp(strElementType), m_ptrObj(stylesMap){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXStylesMap)
};

class CGXGridParamFTR : public CXMLSerializeImp
{
public:
	inline CGXGridParamFTR(CGXGridParam*& gridParam, LPCTSTR strElementType = _T("GridParam"))
		: CXMLSerializeImp(strElementType), m_ptrObj(gridParam){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXGridParam)

};

class CGXBrushFTR : public CXMLSerializeImp
{
public:
	inline CGXBrushFTR(CGXBrush& lb, LPCTSTR strElementType = _T("GXBRUSH"))
		: CXMLSerializeImp(strElementType), m_lb(lb){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	CGXBrush& m_lb;
};

class CGXFontFTR : public CXMLSerializeImp
{
public:
	inline CGXFontFTR(CGXFont*& pFont, LPCTSTR strElementType = _T("GXFONT"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pFont){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXFont)
};

class CGXCollMapDWordToLongFTR : public CXMLSerializeImp
{
public:
	inline CGXCollMapDWordToLongFTR(CGXCollMapDWordToLong*& pMap, LPCTSTR strElementType = _T("HASH_TABLE"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pMap){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXCollMapDWordToLong)
};

class CGXUserPropertyInfoFTR : public CXMLSerializeImp
{
public:
	inline CGXUserPropertyInfoFTR(CGXProperties::UserPropertyInfo*& pInfo, LPCTSTR strElementType = _T("UserPropertyInfo"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pInfo){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CGXProperties::UserPropertyInfo)
};

class CGXAbstractUserAttributeFTR : public CXMLSerializeImp
{
public:
	inline CGXAbstractUserAttributeFTR(CGXAbstractUserAttribute*& pUA, LPCTSTR strElementType = _T("AbstractUserAttribute"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pUA){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	BEGIN_SEC_XMLFORMATTERMAP(CGXAbstractUserAttributeFTR)
		XMLFORMATTERMAP_ADDENTRY(CGXAbstractUserAttribute, CGXAbstractUserAttributeFTR)
	END_SEC_XMLFORMATTERMAP()

	SEC_XML_DYNCREATE_OBJECT(CGXAbstractUserAttribute)
};

class CGXUserAttributeFTR : public CGXAbstractUserAttributeFTR
{
public:
	inline CGXUserAttributeFTR(CGXUserAttribute*& pUA, LPCTSTR strElementType = _T("UserAttribute"))
		: CGXAbstractUserAttributeFTR((CGXAbstractUserAttribute*&)pUA, strElementType), m_ptrObj(pUA){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	BEGIN_SEC_XMLFORMATTERMAP(CGXUserAttributeFTR)
		XMLFORMATTERMAP_ADDENTRY(CGXUserAttribute, CGXUserAttributeFTR)
	END_SEC_XMLFORMATTERMAP()

	SEC_XML_DYNCREATE_OBJECT(CGXUserAttribute)
};

class CGXEllipseUserAttributeFTR : public CGXAbstractUserAttributeFTR
{
public:
	inline CGXEllipseUserAttributeFTR(CGXEllipseUserAttribute*& pUA, LPCTSTR strElementType = _T("EllipseUserAttribute"))
		: CGXAbstractUserAttributeFTR((CGXAbstractUserAttribute*&)pUA, strElementType), m_ptrObj(pUA){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	BEGIN_SEC_XMLFORMATTERMAP(CGXEllipseUserAttributeFTR)
		XMLFORMATTERMAP_ADDENTRY(CGXEllipseUserAttribute, CGXEllipseUserAttributeFTR)
	END_SEC_XMLFORMATTERMAP()

	SEC_XML_DYNCREATE_OBJECT(CGXEllipseUserAttribute)
};

class CGXOleVarUserAttributeFTR : public CGXAbstractUserAttributeFTR
{
public:
	inline CGXOleVarUserAttributeFTR(CGXOleVarUserAttribute*& pUA, LPCTSTR strElementType = _T("OleVarUserAttribute"))
		: CGXAbstractUserAttributeFTR((CGXAbstractUserAttribute*&)pUA, strElementType), m_ptrObj(pUA){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	BEGIN_SEC_XMLFORMATTERMAP(CGXOleVarUserAttributeFTR)
		XMLFORMATTERMAP_ADDENTRY(CGXOleVarUserAttribute, CGXOleVarUserAttributeFTR)
	END_SEC_XMLFORMATTERMAP()

	SEC_XML_DYNCREATE_OBJECT(CGXOleVarUserAttribute)
};

class CGXDelayedRangeFTR : public CXMLSerializeImp
{
public:
	inline CGXDelayedRangeFTR(CGXDelayedRange*& pDelRang, LPCTSTR strElementType = _T("DelayedRange"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pDelRang){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	BEGIN_SEC_XMLFORMATTERMAP(CGXDelayedRangeFTR)
		XMLFORMATTERMAP_ADDENTRY(CGXDelayedRange, CGXDelayedRangeFTR)
	END_SEC_XMLFORMATTERMAP()

	SEC_XML_DYNCREATE_OBJECT(CGXDelayedRange)
};

// replace escape sequences with XML compatible chars
class CStringXMLCompatibleFTR : public CXMLSerializeImp
{
public:
	inline CStringXMLCompatibleFTR(CString*& pString, LPCTSTR lpszOrig = _T("\r\n\t"), LPCTSTR lpszWrite = _T("RNT"), LPCTSTR strElementType = _T("XMLCompatibleString"))
		: CXMLSerializeImp(strElementType), m_ptrObj(pString), m_strOrig(lpszOrig), m_strWrite(lpszWrite){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	SEC_XML_DYNCREATE_OBJECT(CString)

	CString m_strOrig;
	CString m_strWrite;
};

// Exported through base class.
class CInt64FTR : public CXMLSerializeImp
{
public:
	inline CInt64FTR(__int64& iVal, LPCTSTR strElementType = _T("Int64"))
		: CXMLSerializeImp(strElementType), m_iVal(iVal){};

	GRID_API virtual void XMLSerialize(SECXMLArchive& ar);

	__int64& m_iVal;
};

#endif //_GX_XMLSER_