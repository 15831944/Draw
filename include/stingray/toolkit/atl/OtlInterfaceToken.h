///////////////////////////////////////////////////////////////////////////////
// OtlInterfaceToken.h
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

#ifndef __OTLINTERFACETOKEN_H__
#define __OTLINTERFACETOKEN_H__

#ifndef __OTLBASE_H__
	#error otlinterfacetoken.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlInterfaceToken
// encapsulates interthread marshaling of an interface to another apartment


template <class I>
class COtlInterfaceToken
{
public:

	inline COtlInterfaceToken( I* p ) : m_pstream(0), m_p(0)
	{ 
		OTLASSERT(p);
		MarshalInterface(p);
	}

	inline COtlInterfaceToken( COtlInterfaceToken<I>& a) : m_pstream(a.m_pstream), m_p(a.m_p)
	{
		// take ownership of the stream from the source. The source is no longer valid.
		a.m_pstream = 0;
	}

	inline ~COtlInterfaceToken()
	{
		if(m_pstream)
		{	// was never unmarshaled
			AtlFreeMarshalStream(m_pstream);
			m_pstream = 0;
		}
	}


	inline I* GetInterface()
	{
		if(m_pstream == 0)		// already unmarshaled
			return m_p;

		void * p = 0;
		if(SUCCEEDED(::CoGetInterfaceAndReleaseStream( m_pstream, __uuidof(I), &p)))
			m_p = (I*)p;
		else
			m_p = 0;
	
		m_pstream = 0;
		return m_p;
	}

	inline I* operator->()	{ return GetInterface(); }

	inline void MarshalInterface(I* p)
	{
		OTLASSERT(m_pstream == 0 );
		OTLASSERT(p);
		m_p = 0;
		HRESULT hr = ::CoMarshalInterThreadInterfaceInStream( __uuidof(I), p, &m_pstream);
		if (FAILED(hr)) m_pstream = 0;
	}

public:
   CComPtr<I> m_p;
   IStream* m_pstream;
};



};	// namespace StingrayOTL

#endif // __OTLINTERFACETOKEN_H__
