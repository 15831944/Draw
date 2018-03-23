///////////////////////////////////////////////////////////////////////////////
// XMLPropBag.h : SFL Property bags
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
// Author:       Gilberto Araya
// Description:  Definition of the CXMLPropertyBag class
//

#pragma once

#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif
#if _WIN32_IE < 0x0500
#error "The XML Property Bag implementation requires Internet Explorer 5.0"
#endif


#include "SflPropBags.h"
#include "SflPropBagsRes.h"       // main symbols
#include "PropBagImpl.h"
#include <foundation\string\StringEx.h>
#include "foundation\msxmlimport.h"
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {


/////////////////////////////////////////////////////////////////////////////
// CXMLPropertyBag

class ATL_NO_VTABLE CXMLPropertyBag : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXMLPropertyBag, &CLSID_XMLPropertyBag>,
	public IDispatchImpl<CPropertyBagImpl, &IID_IPersistenceStrategy, &LIBID_SflPropBags, 2, 0>,
	public ISupportErrorInfo
{
public:
	FOUNDATION_API CXMLPropertyBag();

DECLARE_REGISTRY_RESOURCEID(IDR_FILEPROPERTYBAG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLPropertyBag)
	COM_INTERFACE_ENTRY2(IDispatch, IPersistenceStrategy)
	COM_INTERFACE_ENTRY(IPersistenceStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IPropertyBag2)
	COM_INTERFACE_ENTRY(IPropertyBag)
END_COM_MAP()

public:
// COM interfaces

// ISupportsErrorInfo
	FOUNDATION_API STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersistanceStrategy
	FOUNDATION_API STDMETHOD(Init)(VARIANT varInitParam);
	FOUNDATION_API STDMETHOD(Commit)();

// IPropertyBag2
	FOUNDATION_API STDMETHOD(CountProperties)(ULONG * pcProperties);
	FOUNDATION_API STDMETHOD(GetPropertyInfo)(ULONG iProperty, ULONG cProperties, PROPBAG2 * pPropBag, ULONG * pcProperties);

protected:
	// Instance data
	foundation::string m_sFileName;
	IStreamPtr m_spStream;
	LARGE_INTEGER m_nStreamPos;

	xml::IXMLDOMDocumentPtr m_spXMLDocument;
	xml::IXMLDOMElementPtr m_spXMLElement;

protected:
	// Overriden implementation operations
	FOUNDATION_API virtual bool ReadProperty(const foundation::string& sPropName, _variant_t& vaValue);
	FOUNDATION_API virtual void WriteBasicType(const foundation::string& sPropName, const _variant_t& vaValue);
	FOUNDATION_API virtual void WriteObject(const foundation::string& sPropName, IUnknownPtr spUnk);
	FOUNDATION_API virtual void WriteSafeArray(const foundation::string& sPropName, _variant_t& vaArray);

	// Internal implementation
	xml::IXMLDOMElementPtr GetBasicTypeElement(const foundation::string& sPropName, const _variant_t& vaValue);
	xml::IXMLDOMElementPtr GetObjectElement(const foundation::string& sPropName, IUnknownPtr spUnk);
	xml::IXMLDOMElementPtr GetSafeArrayElement(const foundation::string& sPropName, _variant_t& vaArray);

	FOUNDATION_API bool ReadPropertyFromElement(xml::IXMLDOMElementPtr spPropertyElement, _variant_t& vaValue);
	FOUNDATION_API void ReadBasicTypeFromElement(xml::IXMLDOMElementPtr spPropertyElement, _variant_t& vaValue);
	FOUNDATION_API void ReadObjectFromElement(xml::IXMLDOMElementPtr spPropertyElement, _variant_t& vaValue);
	FOUNDATION_API void ReadSafeArrayFromElement(xml::IXMLDOMElementPtr spPropertyElement, _variant_t& vaArray);

	FOUNDATION_API static xml::IXMLDOMElementPtr GetPropertyElement(xml::IXMLDOMElementPtr spParent, const foundation::string& sPropName);
	FOUNDATION_API static void ClearSubelement(xml::IXMLDOMElementPtr spParent, const foundation::string& sPropName);

	FOUNDATION_API static foundation::cstring BinaryToString(SAFEARRAY* psaArray);
	FOUNDATION_API static SAFEARRAY* StringToBinary(foundation::cstring& sBinary);

private:

	static LPCTSTR lpszRootTag;
};

};	// namespace stingray::foundation
};	// namespace stingray

