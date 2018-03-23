///////////////////////////////////////////////////////////////////////////////
// OtlMallocSpyImpl.h
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


#ifndef __OtlMallocSpyImpl_H__
#define __OtlMallocSpyImpl_H__

#ifndef __OTLBASE_H__
	#error OtlMallocSpyImpl.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>
#include <objidl.h>

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlMallocSpyImpl class for spying on memory allocation

class OtlMallocSpyImpl : public IMallocSpy 
{
protected:
	// list of allocated pointers...
	std::vector<void*> m_ptrs;

public:
	inline OtlMallocSpyImpl() 
	{
		HRESULT otlHRESULT = CoRegisterMallocSpy(this);
		if(!SUCCEEDED(otlHRESULT)) 
		{
			OutputDebugString(_T("There's already a task allocator spy registered\n"));
		}
	}

	inline ~OtlMallocSpyImpl() 
	{
		// CAVEAT: This must happen BEFORE CoInitialize
		// dump any unreleased memory 
		Dump(NULL);

        m_ptrs.erase( m_ptrs.begin(), m_ptrs.end());

		HRESULT otlHRESULT = CoRevokeMallocSpy();
		if(!SUCCEEDED(otlHRESULT)) {
			if(otlHRESULT == E_ACCESSDENIED) 
			{
				OutputDebugString(_T("OTL's task allocator spy has outstanding allocations\n"));
			} else 
			{
				OutputDebugString(_T("Problem revoking IMallocSpy\n"));
			}
		} else {
			OutputDebugString(_T("Revoked IMallocSpy\n"));
		}
	}

	inline STDMETHODIMP QueryInterface(REFIID riid, void** ppv) 
	{
		// Gotta have that QI!
		if(IID_IUnknown == riid ||
			IID_IMallocSpy == riid) 
		{
			*ppv = static_cast<IMallocSpy*>(this);
			return NOERROR;
		} else 
		{
			*ppv = 0;
			return E_NOINTERFACE;
		}
	}

	inline STDMETHODIMP_(ULONG) AddRef() 
	{
		// this is a heap-based object
		return 2;
	}

	inline STDMETHODIMP_(ULONG) Release() 
	{
		// this is a heap-based object
		return 1;
	}

  inline STDMETHOD_(SIZE_T, PreAlloc)(SIZE_T cbRequest) 
	{	
		// This is called before allocating any memory from the
		//  task allocator...

		// Indicate how much is requested...
		TCHAR sz[128];

		CONTEXT context;

		GetThreadContext(GetCurrentThread(), &context);

//		context.

		_stprintf(sz, _T("Pre-allocing %ld bytes.\n"), cbRequest);
		
		OutputDebugString(sz);
		return cbRequest;
	}

  inline STDMETHOD_(void*, PostAlloc)(void *pActual)
	{
		// This is called after allocating any memory from the
		//  task allocator...

		// Show the pointer value on the screen. Then add it to the 
		//  list of pointers held by the malloc spy...
		TCHAR sz[128];

		_stprintf(sz, _T("Post-allocing some bytes starting at %p\n"), pActual);
		OutputDebugString(sz);

		m_ptrs.push_back(pActual);

		return pActual;
	}

  inline STDMETHOD_(void*, PreFree)(void *pRequest, BOOL /*fSpyed*/)
	{
		// This is called before freeing any memory from the
		//  task allocator...

		// Indicate which bytes are about to be freed. 
		TCHAR sz[128];

		_stprintf(sz, _T("Pre-freeing bytes at %p\n"), pRequest);
		OutputDebugString(sz);

		// remove the pointer from the list if it is being freed. 
		std::vector<void*>::iterator iter;

		bool bFoundPointer = false;

		for (iter = m_ptrs.begin(); iter < m_ptrs.end(); ) 
		{
			if (*iter==pRequest) 
			{
				bFoundPointer = true;

				m_ptrs.erase(iter);
				_stprintf(sz, _T("\nRemoving pointer from list: %p\n\n"), pRequest);

				OutputDebugString(sz);
				break;
			}

			iter++;
		}

		if(!bFoundPointer)
		{
			_stprintf(sz, _T("Weird pointer value: %p not in list.\n"), pRequest);

			OutputDebugString(sz);
		}

		return pRequest;
	}

  inline STDMETHOD_(void, PostFree)(BOOL /*fSpyed*/)
	{
		// This is called after freeing any memory from the
		//  task allocator...

		OutputDebugString(_T("Post-freeing\n"));
		return;
	}

  inline STDMETHOD_(SIZE_T, PreRealloc)(void *pRequest, SIZE_T cbRequest,
                                        void** ppNewRequest, BOOL /*fSpyed*/)
	{
		// This is called before reallocating any memory from the
		//  task allocator...

		TCHAR sz[128];

		*ppNewRequest = pRequest;

		_stprintf(sz, _T("Pre-reallocing %ld bytes at %p. The new memory is going to appear hereL %p \n"), 
			cbRequest, pRequest, ppNewRequest);
		OutputDebugString(sz);
		return cbRequest;
	}

  inline STDMETHOD_(void*, PostRealloc)(void *pActual, BOOL /*fSpyed*/)
	{
		TCHAR sz[128];

		_stprintf(sz,_T("Post-reallocing at: %p\n"), pActual);
		OutputDebugString(sz);
		return pActual;
	}

  inline STDMETHOD_(void*, PreGetSize)(void *pRequest, BOOL /*fSpyed*/)
	{
		TCHAR sz[128];

		_stprintf(sz, _T("Pre-GetSize bytes at %p\n"), pRequest);
		OutputDebugString(sz);

		return pRequest;
	}

  inline STDMETHOD_(SIZE_T, PostGetSize)(SIZE_T cbActual, BOOL /*fSpyed*/)
	{
		TCHAR sz[128];

		_stprintf(sz, _T("Post-GetSize %ld bytes\n"), cbActual);
		OutputDebugString(sz);

		return cbActual;
	}

  inline STDMETHOD_(void*, PreDidAlloc)(void *pRequest, BOOL /*fSpyed*/)
	{
		// This is called before reporting whether a pointer ws
		//  actually allocated from the task allocator...
		TCHAR sz[128];

		_stprintf(sz, _T("Pre-didalloc this block: %p\n"), pRequest);
		OutputDebugString(sz);
		return pRequest;
	}

  inline STDMETHOD_(int, PostDidAlloc)( void *pRequest, BOOL /*fSpyed*/, int fActual)
	{
		// This is called after reporting whether a pointer ws
		//  actually allocated from the task allocator...
		TCHAR sz[128];

		_stprintf(sz, _T("Post-DidAlloc %ld bytes at %p\n"), fActual, pRequest);
		OutputDebugString(sz);
		return fActual;
	}

  inline STDMETHOD_(void, PreHeapMinimize)(void)
	{
		// This is called before the task allocator heap is minimized 
		OutputDebugString(_T("Pre-HeapMinimize\n"));
		return;
	}

  inline STDMETHOD_(void, PostHeapMinimize)(void)
	{
		// This is called after the task allocator heap is minimized 
		OutputDebugString(_T("Post-HeapMinimize\n"));
		return;
	}

	inline STDMETHODIMP Dump(HWND hWnd) 
	{
		if(!hWnd) {
			return E_INVALIDARG;
		}

		// In this case, we expect the Window 
		//  handle to be a handle to a list box...
		HWND temphWnd = NULL;
		TCHAR szClassName[256];

		GetClassName(hWnd, szClassName, 255);

		int nStrCmp = _tcsicmp(szClassName, _T("ListBox")); //stricmp(szClassName, "ListBox"); 
		if(nStrCmp == 0) 
		{
			temphWnd = hWnd;
		} else
		{
			return E_INVALIDARG;
		}

		if(temphWnd) 
		{
			SendMessage(temphWnd, LB_RESETCONTENT, NULL, (LPARAM)0);
		}

		TCHAR sz[128];

		_stprintf(sz, _T("Checking for unreleased memory"));

		if(temphWnd) 
		{
			SendMessage(temphWnd, LB_ADDSTRING, NULL, (LPARAM)sz);
		} else 
		{
			OutputDebugString(sz);
			OutputDebugString(_T("\n"));
		}

		std::vector<void*>::iterator iter;
		for (iter = m_ptrs.begin(); iter < m_ptrs.end(); iter++) 
		{
			_stprintf(sz, _T("Un-freed pointer at %p"), *iter);
			if(temphWnd) 
			{
				SendMessage(temphWnd, LB_ADDSTRING, NULL, (LPARAM)sz);
			} else 
			{
				OutputDebugString(sz);
				OutputDebugString(_T("\n"));
			}

		}

		_stprintf(sz, _T("Done checking for unreleased memory"));

		if(temphWnd) 
		{
			SendMessage(temphWnd, LB_ADDSTRING, NULL, (LPARAM)sz);
		} else 
		{
			OutputDebugString(sz);
			OutputDebugString(_T("\n"));
		}

		return NOERROR;
	}

};

#define OTL_DECLARE_MALLOCSPY OtlMallocSpyImpl OtlMallocSpyImpl;
#define OTL_DUMP_MALLOCSPY OtlMallocSpyImpl.Dump(NULL);

};	// namespace StingrayOTL

#endif // __OtlMallocSpyImpl_H__
