///////////////////////////////////////////////////////////////////////////////
// otlsafearray.h
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


#ifndef _OTLSAFEARRAY_H
#define _OTLSAFEARRAY_H

#ifndef __OTLBASE_H__
	#error otlsafearray.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <assert.h>
#include <StingrayExportDefs.h>

namespace StingrayOTL
{
/////////////////////////////////////////////////////////////
//Stingray Safe array wrapper


template <class T, VARTYPE vtTemplateParam>
class COtlSafeArray : public VARIANT 
{
	inline void Init() 
	{
		memset(this, 0, sizeof(COtlSafeArray));
		VariantInit(this);
	}


//Constructors
public:
	inline COtlSafeArray()
	{
		Init();
	}

	inline COtlSafeArray(UINT nDims)
	{
		Init();

	    SAFEARRAY* psa = NULL;
		SAFEARRAYBOUND* psab = NULL;

		long* prgnBounds;

		prgnBounds = new long[nDims];

		if(prgnBounds)
		{
			for(UINT x = 0; x < nDims; x++) {
				prgnBounds[x] = 10;
			}

			psab = new SAFEARRAYBOUND[nDims];

			if(psab)
			{
				for(UINT i = 0; i < nDims; i++) {	
					psab[i].lLbound = 0;
					psab[i].cElements = prgnBounds[i];
				}

				psa = SafeArrayCreate(vtTemplateParam, nDims, psab);

				delete psab;
			}
			delete prgnBounds;
		}
	}

	inline COtlSafeArray(const SAFEARRAY& rsaSrc)
	{
		Init();
		HRESULT hr;
		
		hr = ::SafeArrayCopy((LPSAFEARRAY)&rsaSrc, &parray);
		if(SUCCEEDED(hr)) 
		{
			vt = vtTemplateParam | VT_ARRAY;
		} else 
		{
			throw hr;
		}
	}

	inline COtlSafeArray(SAFEARRAY* psaSrc)
	{
		Init();
		HRESULT hr = SafeArrayCopy(psaSrc, &parray);
		if(SUCCEEDED(hr)) 
		{
			vt = vtTemplateParam | VT_ARRAY;
		} else
		{
			if(FAILED(hr)) 
				throw hr;
		}
	}

	inline COtlSafeArray(LPCSAFEARRAY pcsaSrc)
	{
		Init();
		HRESULT hr = ::SafeArrayCopy((LPSAFEARRAY)pcsaSrc, &parray);

		if(SUCCEEDED(hr))
		{
			vt = vtTemplateParam |VT_ARRAY;
		} else
		{
			if(FAILED(hr))
				throw hr;
		}
	}

	inline COtlSafeArray(COtlSafeArray& rosaSrc)
	{
		Init();
		*this = rosaSrc;
	}

	inline COtlSafeArray(const VARIANT& rvarSrc)
	{
		Init();
		*this = rvarSrc;
	}

// Operations
public:
	// this clears out the safe array 
	inline HRESULT Clear()
	{
		HRESULT hr;

		hr = VariantClear(this);

		if(parray && SUCCEEDED(hr)) {
			// Sometimes the array is set, but the VT flag isn't
			SafeArrayDestroyData(parray);
		    parray = 0;

			memset(this, 0, sizeof(COtlSafeArray));
		}

		return hr;
	}

	// Assignment operator 
	inline COtlSafeArray& operator=(COtlSafeArray* pOtlSASrc)
	{ 
		HRESULT hr = S_OK;

		Clear();

		if(pOtlSASrc) 
		{
			SAFEARRAY* psa;
			psa = pOtlSASrc->GetSafeArray();

			hr = ::SafeArrayCopy(psa, &parray);
			if(SUCCEEDED(hr)) 
			{
				vt = pOtlSASrc->vt;
			} else
			{
				if(FAILED(hr)) 
					throw hr;
			}
		}
		return *this;
	}

	inline COtlSafeArray& operator=(const COtlSafeArray* pcOtlSASrc)
	{ 
		HRESULT hr = S_OK;

		Clear();

		if(psaSrc) 
		{
			SAFEARRAY* psa;
			psa = pcOtlSASrc->GetSafeArray();

			hr = ::SafeArrayCopy(psa, &parray);
			if(SUCCEEDED(hr)) 
			{
				vt = pcOtlSASrc->vt;
			} else
			{
				throw hr;
			}
		}
		return *this;
	}

	inline COtlSafeArray& operator=(COtlSafeArray& rOtlSASrc)
	{
		HRESULT hr = S_OK;

		Clear();

		SAFEARRAY* psa;

		psa = rOtlSASrc.GetSafeArray();
		
		hr = SafeArrayCopy(psa, &parray);;

		if(SUCCEEDED(hr)) 
		{
			this->vt = rOtlSASrc.vt;
		} else
		{
			throw hr;
		}

		return *this;
	}

	inline COtlSafeArray& operator=(const VARIANT& varSrc)
	{
		HRESULT hr = S_OK;

		hr = VariantClear(this);

		SAFEARRAY* psa = NULL;

		hr = SafeArrayCopy(varSrc.parray, &psa);
		if(SUCCEEDED(hr))
		{
			this->vt = varSrc.vt;
			this->parray = psa;
		} else
		{
			throw(hr);
		}

		return *this;
	}

	inline COtlSafeArray& operator=(const VARIANT* pcvarSrc)
	{
		HRESULT hr = S_OK;

		hr = VariantClear(this);

		SAFEARRAY* psa = NULL;

		hr = SafeArrayCopy(pcvarSrc->parray, &psa);
		if(SUCCEEDED(hr))
		{
			this->vt = pcvarSrc->vt;
			this->parray = psa;
		} else
		{
			throw(hr);
		}

		return *this;
	}

	// function to return the array part of the structore
	inline SAFEARRAY* GetSafeArray() 
	{
		return parray;
	}

	// One dim array helpers
	inline long GetSingleDimSize()
	{
		if(GetDim() != 1)
			return 0;

		long nUBound, nLBound;

		GetUBound(1, &nUBound);
		GetLBound(1, &nLBound);

		return nUBound + 1 - nLBound;
	}

	inline long GetDimSize(DWORD dwDim)
	{
		if(dwDim > SafeArrayGetDim(parray))
			return 0;

		long nUBound, nLBound;

		GetUBound(dwDim, &nUBound);
		GetLBound(dwDim, &nLBound);

		return nUBound + 1 - nLBound;
	}

	inline HRESULT GetLBound(DWORD dwDim, long* pLBound)
	{
		return SafeArrayGetLBound(parray, dwDim, pLBound);
	}

	inline long GetLBound(DWORD dwDim)
	{
		long lLBound = 0;
		HRESULT hr = SafeArrayGetLBound(parray, dwDim, &lLBound);

		if(FAILED(hr))
			throw hr;

		return lLBound;
	}

	inline HRESULT GetUBound(DWORD dwDim, long* pUBound)
	{
		return SafeArrayGetUBound(parray, dwDim, pUBound);
	}

	inline long GetUBound(DWORD dwDim)
	{
		long lUBound = 0;
		HRESULT hr = SafeArrayGetUBound(parray, dwDim, &lUBound);

		if(FAILED(hr))
			throw hr;

		return lUBound;
	}

	inline HRESULT GetElement(long* rgIndices, void* pvData)
	{
		HRESULT hr = E_UNEXPECTED;

		if(parray) 
		{
			hr = SafeArrayGetElement(parray, rgIndices, pvData);
		} else
		{
			pvData = NULL;
		}

		return hr;
	}

	inline HRESULT GetElement(long* rgIndices, T* pt) 
	{
		HRESULT hr = E_UNEXPECTED;

		if(parray) 
		{
			hr = SafeArrayGetElement(parray, rgIndices, pt);
		}  else
		{
			pt = NULL;
		}

		return hr;
	}

	inline HRESULT GetElement(long l, void* pvData) 
	{
		HRESULT hr = E_UNEXPECTED;

		if(parray) 
		{
			hr = SafeArrayGetElement(parray, &l, pvData);
		} else
		{
			pvData = NULL;
		}
		return hr;
	}

	inline void GetSingleDimElement(long l, T* pt) 
	{
		long m = l;

		if(parray) 
		{
			HRESULT hr = SafeArrayGetElement(parray, &m, pt);
		} else
		{
			pvData = NULL;
		}
	}

	T operator[](long nIndex) const
	{
		static T t;
		GetElement(nIndex, &t);

		return t;
	}

	T& operator[](long nIndex)
	{
		static T t;
		GetElement(nIndex, &t);

		return t;
	}

	inline void PtrOfIndex(long* rgIndices, void** ppvData) 
	{
		if(parray) 
		{
			::SafeArrayPtrOfIndex(parray, rgIndices, ppvData);
		}
	}

	inline void PutElement(long* rgIndices, void* pvData) 
	{
		HRESULT hr;
		if(parray) 
		{
			hr = ::SafeArrayPutElement(parray, rgIndices, pvData);
			if(FAILED(hr)) 
				throw hr;
		}
	}

	// Put a typed element in the array 
	inline void PutElement(long* rgIndices, T* pt) 
	{
		HRESULT hr;
		if(parray) 
		{
			hr = ::SafeArrayPutElement(parray, rgIndices, pt);
			if(FAILED(hr)) 
				throw hr;
		}
	}

	// Put a typed element in the array 
	inline void SetAt(long* rgIndices, void* pvData) 
	{
		PutElement(rgIndices, pvData);
	}

	// Put a raw element in the array 
	inline void SetAt(long lNdx, void* pvData) 
	{
		PutElement(&lNdx, pvData);
	}

	// Put a typed element in the array 
	inline void SetAt(long* rgIndices, T* pt) 
	{
		PutElement(rgIndices, pt);
	}

	// Put a typed element in the array 
	inline void SetAt(long lNdx, T* pt) 
	{
		PutElement(&lNdx, pt);
	}

	// Redimension the array based on a safearray bound passed in by the client
	inline void Redim(SAFEARRAYBOUND* psaboundNew)
	{
		HRESULT hr = S_FALSE;
		if(parray) 
		{
			hr = ::SafeArrayRedim(parray, psaboundNew);
		} 
		if (FAILED(hr))
		{
			throw hr;
		}

	}

	// Lock down the array... 
	inline void Lock()
	{
		if(parray) 
		{
			::SafeArrayLock(parray);
		}
	}

	inline void Unlock()
	{
		if(parray) 
		{
			::SafeArrayUnlock(parray);
		}
	}

	inline DWORD GetDim()
	{
		if(parray) 
		{
			return ::SafeArrayGetDim(parray);
		} else
		{
			return 0;
		}
	}

	inline DWORD GetElemSize()
	{
		if(parray) 
		{
			return ::SafeArrayGetElemsize(parray);
		} else 
		{
			return 0;
		}
	}

//Implementation
public:
	inline ~COtlSafeArray()
	{
		Clear(); 
	}
};

// Some useful typedefs
typedef COtlSafeArray<BSTR, VT_BSTR> OtlSABSTR;
typedef COtlSafeArray<short, VT_I2> OtlSAShort;
typedef COtlSafeArray<long, VT_I4> OtlSALong;
typedef COtlSafeArray<float, VT_R4> OtlSAFloat;
typedef COtlSafeArray<double, VT_R8> OtlSADouble;
typedef COtlSafeArray<CURRENCY, VT_CY> OtlSACurrency;
typedef COtlSafeArray<DATE, VT_DATE> OtlSADate;

};	// namespace StingrayOTL

#endif // _OTLSAFEARRAY_H
