///////////////////////////////////////////////////////////////////////////////
// MvcPersist.h : Persistence support for MVC architecture 
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

#pragma once

#ifndef __MVCPERSIST_H__
#define __MVCPERSIST_H__

#if defined(_SFL_ATL_SUPPORT)

#include <foundation\util\sflcom.h>
#include <foundation\MVC\MvcModel.h>
#include <foundation\persistence\XMLPropBag.h>


namespace stingray {
namespace foundation {

//////////////////////////////////////////
// CMvcPersistableModel

template <typename _Derived, typename _Model = CMvcModel>
class CMvcPersistableModel : 
	public _Model
{
public:

	virtual bool Load(LPCTSTR lpszFileName) = 0;
	virtual bool Save(LPCTSTR lpszFileName) = 0;
};



//////////////////////////////////////////
// CMvcPropertyBagPersistableModel

template <typename _Derived, typename _Model = CMvcModel>
class CMvcPropertyBagPersistableModel :
	public CMvcPersistableModel<_Derived, _Model>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPersistPropertyBag
{
	typedef CMvcPropertyBagPersistableModel<_Derived, _Model>	_thisClass;

public:

	BEGIN_COM_MAP(_thisClass)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY2(IPersist, IPersistPropertyBag)
	END_COM_MAP_NO_PURE()
	ATL_IUNKNOWN_IMPL_NODESTROY()

public:

	// IPersistPropertyBag implementation

	virtual HRESULT STDMETHODCALLTYPE GetClassID(CLSID* pClassID)
	{
		*pClassID = __uuidof(_Derived);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE InitNew()
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Load(IPropertyBag* pPropBag, IErrorLog* /*pErrorLog*/)
	{
		HRESULT hr = S_OK;
		try {
			if (!ReadFromPropertyBag(pPropBag)) {
				hr = E_FAIL;
			}
		}
		catch (...) {
			hr = E_FAIL;
		}
		return hr;
	}

	virtual HRESULT STDMETHODCALLTYPE Save(IPropertyBag* pPropBag, BOOL /*fClearDirty*/, BOOL /*fSaveAllProperties*/)
	{
		HRESULT hr = S_OK;
		try {
			if (!WriteToPropertyBag(pPropBag)) {
				hr = E_FAIL;
			}
		}
		catch (...) {
			hr = E_FAIL;
		}
		return hr;
	}


protected:
	// Overridables: implement custom persistence functionality
	// in your derived class

	virtual bool WriteToPropertyBag (
		IPropertyBag* pPropBag
	) = 0;

	virtual bool ReadFromPropertyBag (
		IPropertyBag* pPropBag
	) = 0;

public:

	// CMvcPersistableModel overrides

	virtual bool Load (
		LPCTSTR lpszFileName
	)
	{
		// Create the property bag
		CComObjectCached<foundation::CXMLPropertyBag> propBag;
		propBag.AddRef();

		// Initialize the property bag on the give file 
		HRESULT hr = propBag.Init(CComVariant(lpszFileName));

		// Get the IUnknown interface of this model, 
		// as the property bag will communicate with it
		// excusively through COM interfaces
		IUnknown* punkModel;
		hr = QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&punkModel));
		if (FAILED(hr)) return false;

		// Load the model, using the special IPropertyBag2 method
		// LoadObject to avoid having the property bag dealing
		// with creation issues
		LPOLESTR lpszPropertyName = _Derived::GetModelPropertyString();
		hr = propBag.LoadObject(lpszPropertyName, 0, punkModel, NULL);
		if (FAILED(hr)) return false;
		hr = propBag.Commit();
		if (FAILED(hr)) return false;
		punkModel->Release();

		// Data has changed, update all observers
		UpdateAllObservers();
		return true;
	}


	virtual bool Save (
		LPCTSTR lpszFileName
	)
	{
		// Create the property bag
		CComObjectCached<foundation::CXMLPropertyBag> propBag;
		propBag.AddRef();

		// Initialize the property bag on the give file 
		HRESULT hr = propBag.Init(CComVariant(lpszFileName));

		// Get the IUnknown interface of this model, 
		// as the property bag will communicate with it
		// excusively through COM interfaces
		IUnknown* punkModel;
		hr = QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&punkModel));
		if (FAILED(hr)) return false;

		// Save the model
		LPOLESTR lpszPropertyName = _Derived::GetModelPropertyString();
		hr = propBag.Save(lpszPropertyName, punkModel);
		if (FAILED(hr)) return false;
		hr = propBag.Commit();
		if (FAILED(hr)) return false;
		punkModel->Release();
		return true;
	}


public:

	// Override this static function in the derived class
	// to provide a custom property name for your model
	static LPOLESTR GetModelPropertyString()
	{
		static OLECHAR* lpszPropertyName = OLESTR("MVCModel");
		return lpszPropertyName;
	}
};

};	// namespace stingray::foundation
};	// namespace stingray

#endif  // #if defined(_SFL_ATL_SUPPORT)

#endif  // #ifndef __MVCPERSIST_H__
