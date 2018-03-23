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

#ifndef __OTLGIT_H__
#define __OTLGIT_H__

#ifndef __OTLBASE_H__
	#error otlgit.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// class OtlGIT

// This is a general helper class to assist developers needing to marshal
//  pointers from one apartment to another. 

class OtlGIT 
{
	static bool m_sbIsInstantiated;

	IGlobalInterfaceTable* m_pGIT;

	// list of allocated marshaled object references stored in streams...
	std::vector<LPSTREAM> m_streams;

public:
	inline OtlGIT() 
	{
		// check to see if already registered...
		if(m_sbIsInstantiated)
			return;

		// constructor should get a pointer to the global interface table
		m_pGIT = NULL;
		HRESULT hr;
		hr = CoCreateInstance(CLSID_StdGlobalInterfaceTable,                            
							NULL,
                            CLSCTX_INPROC_SERVER,
                            IID_IGlobalInterfaceTable,
                            (void **)&m_pGIT);

		if(SUCCEEDED(hr)) 
		{

		}
		m_sbIsInstantiated = TRUE;

	}

	inline ~OtlGIT() 
	{
		std::vector<LPSTREAM>::iterator iter;
		for (iter = m_streams.begin(); iter < m_streams.end(); iter++) 
		{
			(*iter)->Release();
			m_streams.erase(iter);
		}

		// Destructor should release the pointer to the global interface table
		if(m_pGIT) 
		{
			m_pGIT->Release();
		} 

		m_sbIsInstantiated = FALSE;
	}

	inline HRESULT RegisterInterface(IUnknown *pUnk, REFIID  riid, SEC_DWORD *pdwCookie) 
	{
		if(m_pGIT)
		{
			return m_pGIT->RegisterInterfaceInGlobal(pUnk, riid, (DWORD*)pdwCookie); 
		} else // manage our own table...
		{
			LPSTREAM pStm = 0;

			HRESULT hr;
			hr = CoMarshalInterThreadInterfaceInStream(riid,
														pUnk,
														&pStm);
			if(SUCCEEDED(hr)) {
				m_streams.push_back(pStm);
				*pdwCookie = (SEC_DWORD)pStm;
			}
			return hr;
		}
	}
	
	inline HRESULT RevokeInterface(SEC_DWORD dwCookie)
	{
		if(m_pGIT)
		{
			return m_pGIT->RevokeInterfaceFromGlobal((DWORD)dwCookie);
		} 
		else
		{
			std::vector<LPSTREAM>::iterator iter;
			for (iter = m_streams.begin(); iter < m_streams.end(); iter++) 
			{
				if ((SEC_DWORD)*iter == (SEC_DWORD)dwCookie) 
				{
					(*iter)->Release();
					m_streams.erase(iter);
					break;
				}
			}

			return S_OK;
		}
	}
	
	inline HRESULT GetInterface(SEC_DWORD dwCookie, REFIID riid, void** ppv)
	{
		if(m_pGIT) 
		{
			return m_pGIT->GetInterfaceFromGlobal((DWORD)dwCookie, riid, ppv);
		} 
		else
		{
			LPSTREAM pStm = NULL;

			std::vector<LPSTREAM>::iterator iter;
			for (iter = m_streams.begin(); iter < m_streams.end(); iter++) 
			{
				if ((SEC_DWORD)*iter == (SEC_DWORD)dwCookie) 
				{
					pStm = (*iter);
					*iter = 0;
					break;
				}
			}

			HRESULT hr;
			hr = S_OK;

			if(pStm)
			{
				hr = CoGetInterfaceAndReleaseStream(pStm,
													riid,
													ppv);
			} else
			{
				hr = STG_E_INVALIDPOINTER;
			}

			return hr;
		}
	}

};

bool OtlGIT::m_sbIsInstantiated = FALSE;

};	// namespace StingrayOTL

#endif // __OTLGIT_H__
