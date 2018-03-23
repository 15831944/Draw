///////////////////////////////////////////////////////////////////////////////
// OtlGIT.h
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

#ifndef __OTLMQI_H__
#define __OTLMQI_H__

#ifndef __OTLBASE_H__
	#error otlmqi.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <foundation\stwarn.h>
#include <map>
#include <foundation\stwarnp.h>

namespace StingrayOTL
{

class COtlMultiQI {
	MULTI_QI* m_pMultiQI;
	ULONG m_nItfs;
	bool* m_pbNeedsAddRef;

public:
	inline COtlMultiQI() 
	{
		m_pMultiQI = 0;
		m_nItfs = 0;
		m_pbNeedsAddRef = 0;
	}

	inline ~COtlMultiQI() 
	{
		Reset();
	}

	inline void Reset() 
	{
		// clients are supposed to release the pointers...
		if(m_pMultiQI)
		{
			delete [] m_pMultiQI;
			m_pMultiQI = NULL;
		}
		if(m_pbNeedsAddRef)
		{
			delete [] m_pbNeedsAddRef;
			m_pbNeedsAddRef = NULL;
		}

		m_nItfs = 0;
	}

	inline void ClearItfPointers()
	{
		// This is done before calling CoCreateInstanceEx...

		for(ULONG i = 0; i < m_nItfs; i++)
		{
			m_pMultiQI[i].pItf = NULL;
			m_pbNeedsAddRef[i] = false;
		}
	}

	inline ULONG SetIID(REFIID riid)
	{
		// Create a new array of size m_nItfs + 1
		m_nItfs++;
		MULTI_QI* pMultiQI = new MULTI_QI[m_nItfs];
		bool* pbNeedsAddRef = new bool[m_nItfs];

		// zero it out
		memset(pMultiQI, 0, (m_nItfs * sizeof(MULTI_QI)));
		memset(pbNeedsAddRef, 0, (m_nItfs * sizeof(bool)));

		// copy old array to new
		memcpy(pMultiQI, m_pMultiQI, (sizeof(MULTI_QI) * (m_nItfs - 1)));
		memcpy(pbNeedsAddRef, m_pbNeedsAddRef, (sizeof(bool) * (m_nItfs - 1)));

		// delete old array
		delete [] m_pMultiQI;
		delete [] m_pbNeedsAddRef;

		// reset the pointer
		m_pMultiQI = pMultiQI;
		m_pbNeedsAddRef = pbNeedsAddRef;

		// Set the IID
		(m_pMultiQI[m_nItfs - 1]).pIID = &riid;

		return 0;
	}


	inline HRESULT GetInterface(REFIID riid, void** pObj)
	{
		for(ULONG i = 0; i < m_nItfs; i++)
		{
			if(*(m_pMultiQI[i].pIID) == riid) 
			{
				if(m_pbNeedsAddRef[i])
				{
					if(m_pMultiQI[i].pItf)
					{
						m_pMultiQI[i].pItf->AddRef();
					}
				}
				(m_pbNeedsAddRef[i]) = true;
				*pObj = m_pMultiQI[i].pItf;
				return m_pMultiQI[i].hr;
			}
		}

		*pObj = NULL;
		return E_NOINTERFACE;
	}

	template <class T> HRESULT GetInterface(T** ppt) 
	{
		return GetInterface(__uuidof(*ppt), (void**)ppt);
	}

    operator MULTI_QI* (void)
	{
		return m_pMultiQI;
	}

	inline HRESULT CoCreateInstanceEx(REFCLSID rclsid, IUnknown *punkOuter,
							   DWORD dwClsCtx, COSERVERINFO *pServerInfo)
	{
		HRESULT hr;

		ClearItfPointers();
		
		hr = ::CoCreateInstanceEx(rclsid, 
                                  punkOuter,
                                  dwClsCtx,
                                  pServerInfo,
                                  this->m_nItfs,
                                  this->m_pMultiQI);
		return hr;
	}

	inline HRESULT CoGetInstanceFromIStorage(COSERVERINFO * pServerInfo,
	                           	      CLSID * pclsid,
		                              IUnknown * punkOuter,
                                      DWORD dwClsCtx,
                                      IStorage * pstg)
	{
		HRESULT hr;

		ClearItfPointers();

		hr = ::CoGetInstanceFromIStorage(pServerInfo,
	                          	       pclsid,
		                               punkOuter,
                                       dwClsCtx,
                                       pstg,
                                       this->m_nItfs,
									   this->m_pMultiQI);
		return hr;
	}
};

#define DECLARE_OTLMQI COtlMultiQI otlMQI;
#define OTLMQI_GETINTERFACE(Type) Type* p##Type; \
                                  otlMQI.GetInterface(IID_##Type, reinterpret_cast<void**>( static_cast<Type**>(&p##Type) ) );

} // namespace StingrayOTL

#endif // __OTLMQI_H__
