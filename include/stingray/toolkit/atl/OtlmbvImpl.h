///////////////////////////////////////////////////////////////////////////////
// OtlmbvImpl.h
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

#ifndef __OTLMBVIMP_H__
#define __OTLMBVIMP_H__

#ifndef __OTLBASE_H__
	#error otlmbvimpl.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

#define OTL_SIZEOF_BSTR(bstrVal) (4+(static_cast<BSTR>(bstrVal) ? SysStringByteLen(bstrVal) : 0)+2)


/////////////////////////////////////////////////////////////////////////////
// OtlIMarshalByValueImpl - for Intel platforms ( no byte swapping )

template <class T>
class ATL_NO_VTABLE OtlIMarshalByValueImpl : public IMarshal
{
public:
    // IUnknown
    STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject) = 0;
    _ATL_DEBUG_ADDREF_RELEASE_IMPL(OtlIMarshalByValueImpl)

	// IMarshal
	inline STDMETHOD(GetUnmarshalClass)( REFIID riid, void * pv,
								  DWORD dwDestContext, void * pvDestContext, 
								  DWORD mshlflags, CLSID * pCid )
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::GetUnMarshalClass\n"));
        T* p = static_cast<T*>(this);
        *pCid = p->GetObjectCLSID();
        return S_OK;
	}

	inline STDMETHOD(GetMarshalSizeMax)( REFIID riid, void *pv, 
								  DWORD dwDestContext, void * pvDestContext, 
								  DWORD mshlflags, ULONG * pSize )
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::GetMarshalSizeMax\n"));
		ULARGE_INTEGER objSize;
		T* p = static_cast<T*>(this);
		HRESULT hr = p->GetSizeMax( &objSize );
		if (SUCCEEDED(hr))
			*pSize = objSize.LowPart;
		return hr;
	}

	inline STDMETHOD(MarshalInterface)(  IStream *pStm, REFIID riid,
								  void *pv, DWORD dwDestContext, 
								  void *pvDestContext, DWORD mshlflags)
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::MarshalInterface\n"));
        T* p = static_cast<T*>(this);
		HRESULT hr = p->Save( pStm, FALSE );
		return hr;
	}

	inline STDMETHOD(UnmarshalInterface)(IStream * pStm, REFIID riid, void ** ppv )
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::UnmarshalInterface\n"));
		T* p = static_cast<T*>(this);
        HRESULT hr = p->Load(pStm);
        if (FAILED(hr))
			return hr;
        hr = p->QueryInterface(riid,ppv);
		return hr;
	}

	inline STDMETHOD(ReleaseMarshalData)( IStream * pStm )
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::ReleaseMarshalData\n"));
		return S_OK;
	}

	inline STDMETHOD(DisconnectObject)(  DWORD dwReserved )
	{
		ATLTRACE(_T("OtlIMarshalByValueImpl::DisconnectObject\n"));
		return S_OK;
	}

};

};	// namespace StingrayOTL

#endif // __OTLMBVIMP_H__
