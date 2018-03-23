///////////////////////////////////////////////////////////////////////////////
// OtlComCollectionSTL.h
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


#ifndef __OTLCOMCOLLECTIONSTL_H__
#define __OTLCOMCOLLECTIONSTL_H__


#ifndef __OTLBASE_H__
	#error otlcomcollectionstl.h requires otlbase.h to be included first
#endif

#include <foundation\stwarn.h>
#include <map>
#include <foundation\stwarnp.h>
#include <comdef.h>


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// CComCollectionOnSTLAssoc

template<class TYPE, class ITEMMAP, class BASE>
class CComCollectionOnSTLAssoc : public BASE
{

public:
	inline CComCollectionOnSTLAssoc() {}
    virtual ~CComCollectionOnSTLAssoc() { RemoveAll(); }

	// standard Collection methods.
	STDMETHOD(Add)(TYPE *pIType, VARIANT index);
	STDMETHOD(get_Count)(long *pVal);
	STDMETHOD(Item)(VARIANT index, VARIANT *pvar);
	STDMETHOD(get__NewEnum)(LPUNKNOWN *pVal);
	STDMETHOD(Remove)(VARIANT index);

    typedef CComEnum<CComIEnum<VARIANT>, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > _CComCollEnum;

protected:
    long AddItem(TYPE *pIType, BSTR bstrKey);
	HRESULT RemoveItem(long lIndex);
	HRESULT RemoveItem(BSTR bstrKey);
    TYPE* Item(long lIndex);
    TYPE* Item(BSTR bstrKey);

protected:
	ITEMMAP m_coll;

	bool RemoveAll();

};

template<class TYPE, class ITEMMAP, class BASE>
STDMETHODIMP CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::Add(TYPE *pIType, VARIANT index)
{
    HRESULT hr = S_OK;

    if(pIType!=NULL)
    {
		// Validate the interface TYPE support.
		TYPE *pI=NULL;
		hr = pIType->QueryInterface(_uuidof(TYPE), (void **)&pI);

		if(SUCCEEDED(hr))
		{
			if(index.vt == VT_BSTR)
			{
				if(AddItem(pI, index.bstrVal)==NULL)
					hr = E_FAIL;
			}
			else if(index.vt == VT_EMPTY || index.vt == VT_ERROR)
			{
				if(AddItem(pI, NULL)==NULL)
					hr = E_FAIL;
			}
			else
				hr = E_INVALIDARG;
			pI->Release();
		}
		else
		{
			hr = E_NOINTERFACE;
		}
    }
    else
    {
        hr = E_POINTER;
    }
    return hr;
}

template<class TYPE, class ITEMMAP, class BASE>
STDMETHODIMP CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::get_Count(long *pVal)
{ 
    HRESULT hr = S_OK;
    if (pVal != NULL)
		*pVal = (int)m_coll.size();
    else
        hr = E_POINTER;

	return hr; 
}

template<class TYPE, class ITEMMAP, class BASE>
STDMETHODIMP CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::Item(VARIANT index, VARIANT *pvar)
{
    HRESULT hr = S_OK;
    if (pvar != NULL)
    {
        (*pvar).vt = VT_EMPTY;
        TYPE* pType=NULL;
		if(index.vt == VT_I4)
	        pType = Item(index.lVal);
		else if(index.vt == (VT_I4 | VT_BYREF))
			pType = Item(*(index.plVal));
		else if(index.vt == VT_I2)
            pType = Item((long)index.iVal);
		else if(index.vt == (VT_I2 | VT_BYREF))
			pType = Item((long)*index.piVal);
		else if(index.vt == VT_BSTR)
			pType = Item(index.bstrVal);
		else if(index.vt == (VT_BSTR | VT_BYREF))
			pType = Item(*(index.pbstrVal));

        if(pType == NULL)
        {
            hr = E_INVALIDARG;
        }
        else
        {
			IUnknown *pIUnk=NULL;
			IDispatch *pIDisp=NULL;
			
			// Attempt to get the dispatch pointer first.
			hr = pType->QueryInterface(IID_IDispatch, (void **)&pIDisp);
			if(SUCCEEDED(hr))
			{
	            (*pvar).vt = VT_DISPATCH;
		        (*pvar).pdispVal = pIDisp;
			}
			else
			{
				// The interface did not support IDispatch, simply try to get
				// the IUnknown pointer now.
				hr = pType->QueryInterface(IID_IUnknown, (void **)&pIUnk);
				if(SUCCEEDED(hr))
				{
					(*pvar).vt = VT_UNKNOWN;
					(*pvar).punkVal = pIUnk;
				}
			}
			pType->Release();
        }
    }
    else
    {
        hr = E_POINTER;
    }

	return hr; 
}

template<class TYPE, class ITEMMAP, class BASE>
STDMETHODIMP CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::get__NewEnum(LPUNKNOWN *ppVal)
{
    HRESULT hr = S_OK;

    if (ppVal == NULL)
	    return E_POINTER;
    *ppVal = NULL;

    _CComCollEnum *pEnum = NULL;
    ATLTRY(pEnum = new CComObject<_CComCollEnum>)
    if (pEnum == NULL)
	    return E_OUTOFMEMORY;

    // allocate an initialize a vector of VARIANT objects
	int nCount = (int)m_coll.size();
	unsigned int uiSize = sizeof(VARIANT) * nCount;
    VARIANT* pVar = (VARIANT*) new VARIANT[nCount];
	memset(pVar, '\0', uiSize);

	// Set the VARIANTs that will hold the TYPE Interface pointers.
    int i = 0;
	ITEMMAP::iterator it;
	for(it = m_coll.begin(); it != m_coll.end(); it++)
    {
		TYPE* pIP = NULL;
		pVar[i].vt = VT_DISPATCH;
		pIP = (*it).second;
		if(pIP != NULL)
		{
			hr = pIP->QueryInterface(IID_IUnknown, (void**)&pVar[i].pdispVal);
			pIP = NULL;
		}
		i++;
    }

    // copy the array of VARIANTs
	hr = pEnum->Init(&pVar[0],
					 &pVar[nCount],
					 reinterpret_cast<TYPE*>(this), AtlFlagCopy);
    if (FAILED(hr))
    {
	    delete pEnum;
    }
	else
	{
		hr = pEnum->QueryInterface(IID_IUnknown, (void**)ppVal);
		if (FAILED(hr))
			delete pEnum;
	}

	// Iterate through the VARIANT pointer array clearing each VARIANT
    i = 0;
    while ( i < nCount )
    {
		VariantClear(&pVar[i]);
		i++;
    }

	// Now free the memory for the array of VARIANT pointers.
	if(pVar)
	{
		delete [] pVar;
		pVar = NULL;
	}

	return hr; 
}

template<class TYPE, class ITEMMAP, class BASE>
STDMETHODIMP CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::Remove(VARIANT index)
{
    HRESULT hr = E_INVALIDARG;
    
	if(index.vt == VT_I4)
	    hr =  RemoveItem(index.lVal);
	else if(index.vt == VT_I2)
		hr =  RemoveItem((long)index.iVal);
    else if(index.vt == VT_BSTR)
		hr = RemoveItem(index.bstrVal);

	return hr; 
}

template<class TYPE, class ITEMMAP, class BASE>
long CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::AddItem(TYPE *pIType, BSTR bstrKey)
{
	OTLASSERT(pIType);
	ATLTRACE("Add item: %S:%0x\n", bstrKey, pIType);
	pIType->AddRef();
	m_coll.insert(ITEMMAP::value_type( bstrKey, pIType));
	return 1;
}

template<class TYPE, class ITEMMAP, class BASE>
TYPE* CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::Item(long lIndex)
{ 
    TYPE* pType=NULL;

	ITEMMAP::iterator it = m_coll.begin();
	lIndex--;
	while(it!=m_coll.end() && lIndex > 0)
	{
		lIndex--;
		it++;
	}

    if(it != m_coll.end())
	{
		pType = (*it).second;
		ATLTRACE("Item: %d:%0x\n", lIndex, pType);
        pType->AddRef();
    }

	return pType; 
}

template<class TYPE, class ITEMMAP, class BASE>
TYPE* CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::Item(BSTR bstrKey)
{ 
    TYPE* pType=NULL;
	ITEMMAP::iterator it = m_coll.find(bstrKey);
	if(it != m_coll.end())
	{
	    pType = (*it).second;
		ATLTRACE("Item: %S:%0x\n", bstrKey, pType);
		pType->AddRef();
	}

	return pType; 
}

template<class TYPE, class ITEMMAP, class BASE>
HRESULT CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::RemoveItem(long lIndex)
{
	if(	(lIndex < 1) || 
		(lIndex > (long)m_coll.size()) )
		return E_INVALIDARG;

	ITEMMAP::iterator it = m_coll.begin();
	lIndex--;
	while(it!=m_coll.end() && lIndex > 0)
	{
		lIndex--;
		it++;
	}

    if(it != m_coll.end())
	{
		TYPE* pType = (*it).second;
		ATLTRACE("Remove: %d:%0x\n", lIndex, pType);
		if(pType)
			pType->Release();
		m_coll.erase(it);
		return S_OK;
    }
	return E_INVALIDARG;

}


template<class TYPE, class ITEMMAP, class BASE>
HRESULT CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::RemoveItem(BSTR bstrKey)
{
	ITEMMAP::iterator it = m_coll.find(bstrKey);
	if( it != m_coll.end() )
	{
	    TYPE* pType = (*it).second;
		ATLTRACE("Remove: %S:%0x\n", bstrKey, pType);
		if(pType)
			pType->Release();
		m_coll.erase(it);
		return S_OK;
	}
	return E_INVALIDARG;
}

template<class TYPE, class ITEMMAP, class BASE>
bool CComCollectionOnSTLAssoc<TYPE,ITEMMAP,BASE>::RemoveAll()
{
	ITEMMAP::iterator it;
	TYPE* pType = NULL;
	for(it = m_coll.begin(); it!=m_coll.end(); it++)
	{
		pType = (*it).second;
		if(pType)
			pType->Release();
	}
	m_coll.erase(m_coll.begin(), m_coll.end());
	return true;
}



/////////////////////////////////////////////////////////////////////////////
// _OtlCopyVariantFromInterface - copy policies for CComCollectionOnSTL

template < class T >
class _OtlCopyVariantFromInterface
{
public:
	static HRESULT copy(VARIANT* pV, T** pIP)
	{
		HRESULT hr = (*pIP)->QueryInterface(IID_IDispatch, (void**)&pV->pdispVal);
		if(SUCCEEDED(hr) )
			pV->vt = VT_DISPATCH;
		else
		{
			(*pIP)->AddRef();
			pV->vt = VT_UNKNOWN;
			pV->punkVal = (*pIP);
		}
		return S_OK;
	}

	// _OtlCopyVariantFromInterface::copy overload
	// 2nd parameter MUST be CONST to prevent error C2664 for ATL_VER >= 8.0
    // Reference:
	//    c:\program files (x86)\microsoft visual studio 8\vc\atlmfc\include\atlcom.h(5126) : 
	//       error C2664: 'StingrayOTL::_OtlCopyVariantFromInterface<T>::copy' : 
	//       cannot convert parameter 2 from 'IDispatch *const *' to 'IDispatch **'

	static HRESULT copy(VARIANT* pV, T* const* pIP)
	{
		HRESULT hr = (*pIP)->QueryInterface(IID_IDispatch, (void**)&pV->pdispVal);
		if(SUCCEEDED(hr) )
			pV->vt = VT_DISPATCH;
		else
		{
			(*pIP)->AddRef();
			pV->vt = VT_UNKNOWN;
			pV->punkVal = (*pIP);
		}
		return S_OK;
	}

	static void init(VARIANT* p) { VariantInit(p); }
	static void destroy(VARIANT* p) { VariantClear(p); }
};

/////////////////////////////////////////////////////////////////////////////
// CComCollectionOnSTL

template<class TYPE, class COLLTYPE, class BASE, class COPY=_OtlCopyVariantFromInterface<TYPE> >
class CComCollectionOnSTL : public ICollectionOnSTLImpl<BASE, 
														COLLTYPE, 
														VARIANT, 
														COPY,
														CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, COPY, COLLTYPE > 
														>
{

};

/////////////////////////////////////////////////////////////////////////////
// CComCollectionOnSTLMap

template<class TYPE, class BASE>
class CComCollectionOnSTLMap : 
	public CComCollectionOnSTLAssoc<	TYPE,
										std::map<_bstr_t, TYPE*, std::less<_bstr_t> >,
										BASE 
										>
{
public:
	CComCollectionOnSTLMap() {}
    virtual ~CComCollectionOnSTLMap() {}
};


};	// namespace StingrayOTL

#endif // __OTLCOMCOLLECTIONSTL_H__
