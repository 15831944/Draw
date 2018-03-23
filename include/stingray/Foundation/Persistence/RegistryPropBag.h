///////////////////////////////////////////////////////////////////////////////
// REgistryPropBag.h : SFL Property bags
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
// Description:  Definition of the CRegistryPropertyBag class
//

#pragma once

#include "SflPropBagsRes.h"       // main symbols
#include "PropBagImpl.h"
#include "RegistryUtil.h"
#include <foundation\string\StringEx.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {


/////////////////////////////////////////////////////////////////////////////
// CRegistryPropertyBag

class FOUNDATION_API ATL_NO_VTABLE CRegistryPropertyBag : 
	public CComObjectRoot,
	public CComCoClass<CRegistryPropertyBag,&CLSID_RegistryPropertyBag>,
	public IDispatchImpl<CPropertyBagImpl, &IID_IPersistenceStrategy, &LIBID_SflPropBags, 2, 0>, 
	public ISupportErrorInfo
{
public:
	CRegistryPropertyBag(): m_preg(0) {}

DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRYPROPERTYBAG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRegistryPropertyBag)
	COM_INTERFACE_ENTRY2(IDispatch, IPersistenceStrategy)
	COM_INTERFACE_ENTRY(IPersistenceStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IPropertyBag2)
	COM_INTERFACE_ENTRY(IPropertyBag)
END_COM_MAP()

public:
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersistenceStrategy
	STDMETHOD(Init)(VARIANT varInitParam);
	STDMETHOD(Commit)();

// IPropertyBag2
	STDMETHOD(CountProperties)(ULONG * pcProperties);
	STDMETHOD(GetPropertyInfo)(ULONG iProperty, ULONG cProperties, PROPBAG2 * pPropBag, ULONG * pcProperties);

protected:
	// Instance data
	foundation::string m_sRootKey;
	foundation::CRegistry m_regBase;

	foundation::CRegistry* m_preg;

	// Overriden implementation operations
	virtual bool ReadProperty(const foundation::string& sPropName, _variant_t& vaValue);
	virtual void WriteBasicType(const foundation::string& sPropName, const _variant_t& vaValue);
	virtual void WriteObject(const foundation::string& sPropName, IUnknownPtr spUnk);
	virtual void WriteSafeArray(const foundation::string& sPropName, _variant_t& vaArray);

	// Implementation operations
	virtual bool ReadPropertyFromKey(const foundation::string& sPropName, _variant_t& vaValue, foundation::CRegistry& regKey);
	virtual void WriteObjectToKey(IUnknownPtr spUnk, foundation::CRegistry& regKey);
	virtual void WriteSafeArrayToKey(_variant_t& vaArray, foundation::CRegistry& regKey);
	virtual void WriteBasicTypeToKey(const foundation::string& sPropName, const _variant_t& vaValue, foundation::CRegistry& regKey);

	// Requirement: regKey must correspond to an object store.
	// No verification is done
	virtual void ReadObjectFromKey(foundation::CRegistry& regKey, IUnknownPtr& spNewObject);
	virtual void ReadSafeArrayFromKey(foundation::CRegistry& regKey, _variant_t& vaArray);
};

};	// namespace stingray::foundation
};	// namespace stingray
