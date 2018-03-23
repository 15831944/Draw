///////////////////////////////////////////////////////////////////////////////
// OtlSimpleSafeArray.h
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

#ifndef __OTLSIMPLESAFEARRAY_H__
#define __OTLSIMPLESAFEARRAY_H__

#ifndef __OTLBASE_H__
	#error otlsimplesafearray.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <StingrayExportDefs.h>

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlSimpleSafeArray


template <class T>
class COtlSimpleSafeArray
{
public:

	inline COtlSimpleSafeArray(){ ClearState(); }

	// construct a new safearray using an [out] VARIANT* parameter.
	// will auto-assign pVariant on destruction
	inline COtlSimpleSafeArray(VARIANT* pVariant, VARTYPE vt, unsigned int cElements)
	{
			// ppsa must be an [out] parameter to a method.
			// we can not own this array
			ClearState();
			OTLASSERT(pVariant);
			VariantClear(pVariant);
			pVariant->vt = VT_ARRAY | vt;
			m_pVariant = pVariant;	// cache the out param pointer
			Create(vt, cElements);
		} 


	// construct a new safearray using an [out] SAFEARRAY** parameter.
	// will auto-assign ppsa on destruction
	inline COtlSimpleSafeArray(SAFEARRAY **ppsa, VARTYPE vt, unsigned int cElements)
	{
			// ppsa must be an [out] parameter to a method.
			// we can not own this array
			ClearState();
			OTLASSERT(ppsa);
			*ppsa = 0;				// clear the [out] param
			m_ppsafearray = ppsa;	// cache the out param pointer
			Create(vt, cElements);
		} 

	// construct a new safearray.
	// same as default constructor followed by Create()
	inline COtlSimpleSafeArray(VARTYPE vt, unsigned int cElements, bool bOwnArray=false)
	{
		ClearState();
		Create(vt, cElements, bOwnArray);
	} 

	// construct on an existing const VARIANT safearray
    inline COtlSimpleSafeArray ( const VARIANT & v) 
	{ 
		ClearState();
		Init(v.vt, v.parray, false); 
	}

	// construct on an existing VARIANT safearray
    inline COtlSimpleSafeArray ( VARIANT & v, bool bOwnArray = false )
	{
		ClearState();
		Init(v.vt, v.parray, bOwnArray); 
	}

	// construct on an existing SAFEARRAY.
	// Same result as default constructor followed by Attach
    inline COtlSimpleSafeArray ( SAFEARRAY * a, bool bOwnArray = false)
	{
		ClearState();
		Init(VT_ARRAY, a, bOwnArray);
	}

    inline ~COtlSimpleSafeArray(void) { OnFinalRelease(); }


    operator const T * ( void ) const { return m_pvalues; }
    operator       T * ( void )       { return m_pvalues; }

	inline void Create(VARTYPE vt, unsigned int cElements, bool bOwnArray=false, bool bVector=false)
	{
		SAFEARRAY* psa = 0;
		if(bVector)
		{
			psa = ::SafeArrayCreateVector(vt, 0, cElements);
		}else 
		{
			SAFEARRAYBOUND bounds = {cElements, 0};
			psa = ::SafeArrayCreate(vt, 1, &bounds);
		}
		OTLASSERT(psa);
		Init( vt | VT_ARRAY , psa, bOwnArray);
	}

	
	inline void Attach(SAFEARRAY *psa)
	{
		OTLASSERT(psa);
		ClearState();
		Init(VT_ARRAY, psa, false);
	}

	inline SAFEARRAY* Detach()
	{
		if (m_bAccessedData) 
		{
			::SafeArrayUnaccessData(m_psafearray);
			m_bAccessedData = false;
		}
		return m_psafearray;
	}

	inline long LBound()
	{
		OTLASSERT(m_psafearray);
		long nFirst = 0;
		try {
		  if (FAILED(::SafeArrayGetLBound(m_psafearray, 1, &nFirst))) throw 0;
		}
		catch ( ... ) {
			OTLASSERT(FALSE); 
		}
		return nFirst;
	}

	inline long UBound()
	{
		OTLASSERT(m_psafearray);
		long nLast = 0;
		try {
		  if (FAILED(::SafeArrayGetUBound(m_psafearray, 1, &nLast))) throw 0;
		}
		catch ( ... ) {
			OTLASSERT(FALSE); 
		}
		return nLast;
	}

	inline long GetSize() { return m_nSize; }
	
private:
    bool m_bOwnArray;         // whether to destroy the safearray
    bool m_bAccessedData;     // whether SafeArrayAccessData succeeded
    long m_nSize;             // number of entries in the array
    SAFEARRAY * m_psafearray; // SAFEARRAY that are wrapping

	SAFEARRAY ** m_ppsafearray;		// used when constructed with an [out] SAFEARRAY** parameter
	VARIANT * m_pVariant;			// used when constructed with an [out] VARIANT* parameter

    T * m_pvalues;            // array of values accessed from the safearray

	void ClearState()
	{
		m_pvalues       = 0;
		m_psafearray    = 0;
		m_bOwnArray     = false;
		m_bAccessedData = false;
		m_nSize         = 0;
		m_ppsafearray	= 0;
		m_pVariant = 0;
	}
    
	void OnFinalRelease ( void ) 
    {  
		try { 
            if (m_psafearray) {
                if (m_bAccessedData) ::SafeArrayUnaccessData(m_psafearray);
				// if used for building an [out] parameter, copy the pointer now
				if (m_ppsafearray)
					*m_ppsafearray = m_psafearray;
				else if (m_pVariant)
					m_pVariant->parray = m_psafearray;

                if (m_bOwnArray) ::SafeArrayDestroy(m_psafearray); 
            }
        }
        catch ( ... ) { 
            OTLASSERT(FALSE); 
        }
		ClearState();
    }


    void Init ( VARTYPE vt, SAFEARRAY * a, bool bOwnArray )
    {   
		try {
            m_psafearray    = a;
            m_bOwnArray     = bOwnArray;

            if (a && (vt & VT_ARRAY)) {
                if (FAILED(::SafeArrayAccessData(m_psafearray, (void **)&m_pvalues))) throw 0;
                m_bAccessedData = true; // flags that SafeArrayAccessData() succeeded
                m_nSize = UBound() - (LBound() - 1);
            }
		}
		catch ( ... ) {
			OTLASSERT(FALSE);
			OnFinalRelease();
		}
    }

};


};	// namespace StingrayOTL

#endif // __OTLSIMPLESAFEARRAY_H__
