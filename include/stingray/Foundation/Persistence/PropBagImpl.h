///////////////////////////////////////////////////////////////////////////////
// PropBagImpl.h : SFL Property bags
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
// Description:  Generic behavior of a PropertyBag implementation
//

#pragma once

#include <foundation\string\StringEx.h>
#include <comdef.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

// Classes introduced due to the fact that IPropertyBag and IPropertyBag2 have methods
// with the same names, so a class cannot inherit from both of them directly or indirectly if
// those methods remain abstract

class FOUNDATION_API IPropertyBag2_NoDupl: public IPropertyBag2
{
public:
	virtual HRESULT __stdcall Read(ULONG cProperties, PROPBAG2 * pPropBag, IErrorLog * pErrLog, VARIANT * pvarValue, HRESULT* phrError)
	{return PropBag2_Read(cProperties, pPropBag, pErrLog, pvarValue, phrError);}
	virtual HRESULT __stdcall Write(ULONG cProperties, PROPBAG2 * pPropBag, VARIANT * pvarValue)
	{return PropBag2_Write(cProperties, pPropBag, pvarValue);}

protected:
	virtual HRESULT __stdcall PropBag2_Read(ULONG cProperties, PROPBAG2 * pPropBag, IErrorLog * pErrLog, VARIANT * pvarValue, HRESULT* phrError) = 0;
	virtual HRESULT __stdcall PropBag2_Write(ULONG cProperties, PROPBAG2 * pPropBag, VARIANT * pvarValue) = 0;
};

class FOUNDATION_API IPropertyBag_NoDupl: public IPropertyBag
{
public:
	virtual HRESULT __stdcall Read(LPCOLESTR pszPropName, VARIANT* pVar, IErrorLog* pErrorLog)
	{return PropBag_Read(pszPropName, pVar, pErrorLog);}
	virtual HRESULT __stdcall Write(LPCOLESTR pszPropName, VARIANT* pVar)
	{return PropBag_Write(pszPropName, pVar);}

protected:
	virtual HRESULT __stdcall PropBag_Read(LPCOLESTR pszPropName, VARIANT* pVar, IErrorLog* pErrorLog) = 0;
	virtual HRESULT __stdcall PropBag_Write(LPCOLESTR pszPropName, VARIANT* pVar) = 0;
};


class FOUNDATION_API CPropertyBagImpl:
	public IPersistenceStrategy,
	public IPropertyBag2_NoDupl,
	public IPropertyBag_NoDupl
{
public:
	STDMETHOD(Save)(/*[in]*/BSTR bstrPropName, /*[in]*/ IUnknown* pPersistObject);
	STDMETHOD(Load)(/*[in]*/BSTR bstrPropName, /*[out]*/ IUnknown** pPersistObject);

	// IPropertyBag2
	STDMETHOD(LoadObject)(LPCOLESTR pstrName, DWORD dwHint, IUnknown * pUnkObject, IErrorLog * pErrLog);

protected:
	// IPropertyBag
	STDMETHOD(PropBag_Read)(LPCOLESTR pszPropName, VARIANT* pVar, IErrorLog* pErrorLog);
	STDMETHOD(PropBag_Write)(LPCOLESTR pszPropName, VARIANT* pVar);

	// IPropertyBag2
	STDMETHOD(PropBag2_Read)(ULONG cProperties, PROPBAG2 * pPropBag, IErrorLog * pErrLog, VARIANT * pvarValue, HRESULT* phrError);
	STDMETHOD(PropBag2_Write)(ULONG cProperties, PROPBAG2 * pPropBag, VARIANT * pvarValue);

protected:
	// Persistance implementation
	virtual bool ReadProperty(const foundation::string& sPropName, _variant_t& vaValue) = 0;
	virtual void WriteBasicType(const foundation::string& sPropName, const _variant_t& vaValue) = 0;
	virtual void WriteObject(const foundation::string& sPropName, IUnknownPtr spUnk) = 0;
	virtual void WriteSafeArray(const foundation::string& sPropName, _variant_t& vaArray) = 0;

	// Object serialization helpers
	virtual void LoadObject(const _bstr_t& bstrCLSID, IUnknownPtr& spUnk);
	virtual void LoadObject(IUnknownPtr& spUnk);
	virtual void SaveObject(const IUnknownPtr& spUnk, _bstr_t& bstrCLSID);
};


};	// namespace stingray::foundation
};	// namespace stingray


