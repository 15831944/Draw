///////////////////////////////////////////////////////////////////////////////
// Enumeration.h
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
// Authors:      Jeff Boenig
// Description:  
//

#pragma once

#ifndef __ENUMERATION_H__
#define __ENUMERATION_H__

#include <comdef.h>
#include <atlbase.h>
#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>
#include <Foundation\SflGuids.h>
#include <Foundation\Properties\PropIface.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc CEnumeration
//
//@class CEnumeration | Provides a default implementation of the
// <c IEnumeration> interface.
//
//@base public | IEnumeration
//@xref <c IEnumeration>
//

class FOUNDATION_API CEnumeration : public IEnumeration
{
// Embedded types
public:
	typedef std::vector<_variant_t> Values;
	typedef Values::iterator ValueIterator;

	typedef std::vector<_bstr_t> Descriptions;
	typedef Descriptions::iterator DescIterator;

// Constructors/destructor
public:
	//@cmember
	/* Construct an enumeration. */
	CEnumeration()
	{
		m_ulRefCount = 0L;
	}

	//@cmember
	/* Destroy an enumeration. */
	virtual ~CEnumeration()
	{
	}

// Attributes
protected:
	//@cmember
	/* Item values in the enumeration. */
	Values m_values;
	//@cmember
	/* Item descriptions in the enumeration. */
	Descriptions m_descriptions;
	//@cmember
	/* Reference count. */
	ULONG m_ulRefCount;

// Operations
public:
	//@cmember,mfunc
	// Return the number of items in the enumeration.
	//@@rdesc Number of items in the enumeration.
	//@@end
	/* Return the number of items in the enumeration*/
	virtual int GetItemCount() const
	{
		return (int)m_values.size();
	}

	//@cmember,mfunc
	// Get the value of the given item in the enumeration.
	//@@rdesc void
	//@@parm Index of item to retrieve value of
	//@@parm VARIANT to receive the returned value
	//@@end
	/* Get the value of the given item in the enumeration*/
	virtual void GetItemValue(const int nItemIdx, VARIANT& val) const
	{
		if(nItemIdx >= static_cast<int>(m_values.size()))
			return;
		_variant_t var = m_values[nItemIdx];
		::VariantCopy(&val, &var);
	}

	//@cmember,mfunc
	// Set the value of the given item in the enumeration.
	//@@rdesc void
	//@@parm Index of item in enumeration.
	//@@parm Input value.
	//@@end
	/* Set the value of the given item in the enumeration*/
	virtual void SetItemValue(const int nItemIdx, const VARIANT& val)
	{
		if(nItemIdx >= static_cast<int>(m_values.size()))
			return;
		m_values[nItemIdx] = val;
	}

	//@cmember,mfunc
	// Get the description of the given item in the enumeration.
	//@@rdesc void
	//@@parm Index of item in enumeration.
	//@@parm Pointer to buffer in which to return description.
	//@@end
	/* Get the description of the given item in the enumeration*/
	virtual void GetItemDescription(const int nItemIdx, BSTR* bDesc) const
	{
		_ASSERTE(bDesc);
		if(nItemIdx >= static_cast<int>(m_descriptions.size()))
			return;
		*bDesc = m_descriptions[nItemIdx].copy();
	}

	//@cmember,mfunc
	// Set the description of the given item in the enumeration.
	//@@rdesc void
	//@@parm Index of item in enumeration.
	//@@parm Pointer to new description for the item.
	//@@end
	/* Set the description of the given item in the enumeration*/
	virtual void SetItemDescription(const int nItemIdx, const OLECHAR* pszDesc)
	{
		if(nItemIdx >= static_cast<int>(m_descriptions.size()))
			return;
		m_descriptions[nItemIdx] = pszDesc;
	}

	//@cmember,mfunc
	// Add an item to the enumeration.
	//@@rdesc void
	//@@parm Value of item to add.
	//@@parm Description of item to add.
	//@@comm
	// This function appends an item to the enumeration. It is added
	// at the end of the list of items.
	//@@end
	/* Add an item to the enumeration. */
	virtual void AddItem(const VARIANT& val, const OLECHAR* pszDesc)
	{
		_ASSERTE(pszDesc);
		m_values.push_back(val);
		m_descriptions.push_back(pszDesc);
	}

	// The GUID map implements the QueryGuid function
	BEGIN_GUID_MAP(CEnumeration)
		GUID_ENTRY(IEnumeration)
		GUID_ENTRY(IQueryGuid)
		GUID_ENTRY(IRefCount)
	END_GUID_MAP

	STDMETHOD_(ULONG, AddRef)()
	{
		return ++m_ulRefCount;
	}

	STDMETHOD_(ULONG, Release)()
	{
		ULONG ulRefCount = --m_ulRefCount;
		if (m_ulRefCount == 0)
			delete this;
		return ulRefCount;
	}
};

/////////////////////////////////////////////////////////////////////////////
//@doc CBoolEnumeration
//
//@class CBoolEnumeration | This class extends <c CEnumeration> and provides
// a built-in enumeration for boolean values. This class loads the enumeration
// with two values in its constructor - True and False.
//
//@base public | CEnumeration

class FOUNDATION_API CBoolEnumeration : public CEnumeration
{
public:
	CBoolEnumeration()
	{
		_variant_t val(true);
		AddItem(val, L"True");
		val = false;
		AddItem(val, L"False");
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAxUserEnumeration

class FOUNDATION_API CAxUserEnumeration : public CEnumeration
{
public:
	CAxUserEnumeration(ITypeInfo* pEnumTypeInfo)
	{
		_ASSERTE(pEnumTypeInfo);
		TYPEATTR *pta=NULL;
		pEnumTypeInfo->GetTypeAttr(&pta);
		TCHAR buf[256];
		if (pta && pta->typekind == TKIND_ENUM)
		{
			VARDESC* pvd=NULL;
			for (int i=0; i < pta->cVars; i++)
			{
				if(SUCCEEDED(pEnumTypeInfo->GetVarDesc(i, &pvd)))
				{
					DISPID idMember = pvd->memid;
					CComBSTR bstrName;
					pEnumTypeInfo->GetDocumentation(idMember, &bstrName, NULL, NULL, NULL);
					// format string description
					{
							USES_CONVERSION;
							wsprintf(buf, _T("%d - %s"), pvd->lpvarValue->lVal, OLE2T(bstrName));
							bstrName = T2BSTR(buf);
					}

					// add an entry
					AddItem(*(pvd->lpvarValue), bstrName);
					::SysFreeString(bstrName);
					pEnumTypeInfo->ReleaseVarDesc(pvd);
				}
			}
		}
		if (pta)
		{
			pEnumTypeInfo->ReleaseTypeAttr(pta);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAxPPBEnumeration

class FOUNDATION_API CAxPPBEnumeration : public CEnumeration
{
public:
	CAxPPBEnumeration(IPerPropertyBrowsing* pBrowse, DISPID id)
	{
		_ASSERTE(pBrowse);
		CALPOLESTR     castr;
		CADWORD        cadw; 
		HRESULT hr = GetBrowseArrays(pBrowse, id, &castr, &cadw);
		if(SUCCEEDED(hr))
		{
			// populate the list of items
			for(ULONG i=0; i < castr.cElems; i++)
			{
				BSTR bstrName = ::SysAllocString(castr.pElems[i]);
				DWORD dwCookie = cadw.pElems[i];
				CComVariant var;
				hr = pBrowse->GetPredefinedValue(id, dwCookie, &var);
				if(SUCCEEDED(hr))
					AddItem(var, bstrName);
				::SysFreeString(bstrName);
			}

			ReleaseBrowseArrays(&castr, &cadw);
		}
	}

	static void ReleaseBrowseArrays(CALPOLESTR* pcastr, CADWORD* pcadw)
	{
		_ASSERTE(pcastr);
		_ASSERTE(pcadw);

		CoTaskMemFree((void *)pcadw->pElems);
		for (ULONG i=0; i < pcastr->cElems; i++)     
				CoTaskMemFree((void *)pcastr->pElems[i]);  
		CoTaskMemFree((void *)pcastr->pElems); 
	}

	static HRESULT GetBrowseArrays(IPerPropertyBrowsing* pBrowse, DISPID id, CALPOLESTR* pcastr, CADWORD* pcadw)
	{
		_ASSERTE(pBrowse);
		_ASSERTE(pcastr);
		_ASSERTE(pcadw);
		HRESULT hr = pBrowse->GetPredefinedStrings(id, pcastr, pcadw);  
		return hr;
	}
};

}; // namespace stingray::foundation
}; // namespace stingray

#endif  // #ifndef __ENUMERATION_H__
