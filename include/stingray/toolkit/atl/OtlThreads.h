///////////////////////////////////////////////////////////////////////////////
// OtlThreads.h
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

#ifndef __OTLTHREADS_H__
#define __OTLTHREADS_H__

#ifndef __OTLBASE_H__
	#error otlthreads.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otlfunctor.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (push)
#pragma warning (disable: 4239) // Non standard extension

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlThread
// encapsulates a thread procedure as a functor

void otlApartmentMain ( COtlFunctor fmain, DWORD dwCoInit)
{
    if (SUCCEEDED(::CoInitializeEx(0, dwCoInit)))
        try
        {
            fmain();
            ::CoUninitialize();
        }
        catch ( ... )
        {
            ::CoUninitialize();
            throw;
        }
}

COtlFunctor otlMakeAptMainFunctor ( COtlFunctor fmain, DWORD dwCoInit)
{
	// make a functor that calls otlApartmentMain( my_worker_functor, dwCoInit )
    return otlMakeFunctor(otlApartmentMain, fmain, dwCoInit);
}


class COtlThreadFunction
{
public:
	COtlThreadFunction(COtlFunctor fmain, DWORD dwCoInit = COINIT_APARTMENTTHREADED)
		: m_hthread(0), m_dwTID(0)
	{
		m_functor = otlMakeAptMainFunctor(fmain, dwCoInit);
		m_hthread = ::CreateThread(NULL, 0, ThreadEntry, &m_functor, CREATE_SUSPENDED, &m_dwTID);
	}

	virtual ~COtlThreadFunction()
	{
		WaitForFinish();
	}

	virtual void WaitForFinish(DWORD dwTimeout = INFINITE)
	{
		if(m_hthread)
		{
			::WaitForSingleObject(m_hthread, dwTimeout);
			::CloseHandle(m_hthread);
			m_hthread = 0;
		}
	}

	virtual BOOL Start()
	{
		OTLASSERT(m_hthread);
		if(0xFFFFFFFF == ::ResumeThread(m_hthread))
			return FALSE;
		return TRUE;

	}
	
	static DWORD WINAPI ThreadEntry(void *pv)
	{
		COtlFunctor* pFunctor = (COtlFunctor*)pv;
		(*pFunctor)();
		return 0;
	}


	COtlFunctor m_functor;
	HANDLE m_hthread;
	DWORD m_dwTID;

};


};	// namespace StingrayOTL

#pragma warning (pop) //4239

#endif // __OTLTHREADS_H__
