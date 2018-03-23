///////////////////////////////////////////////////////////////////////////////
// OtlIPersistStreamImpl.h
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

#ifndef __OTLPERSISTSTREAM_H__
#define __OTLPERSISTSTREAM_H__

#ifndef __OTLBASE_H__
	#error otlipersiststreamimpl.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{
/////////////////////////////////////////////////////////////////////////////
// OtlIPeristStreamImpl<T>
//
// default implementations for shell extensions
template <class T>
class ATL_NO_VTABLE OtlIPersistStreamImpl : public IPersistStream
{
public:
	// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(OtlIPersistStreamImpl)

	// IPersist
	inline STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		*pClassID = T::GetObjectCLSID();
		return S_OK;
	}

	// IPersistStream
	inline STDMETHOD(IsDirty)()
	{
		return S_FALSE;
	}
	inline STDMETHOD(Load)(LPSTREAM /*pStm*/)
	{
		return S_OK;
	}
	inline STDMETHOD(Save)(LPSTREAM /*pStm*/, BOOL /*fClearDirty*/)
	{
		return S_OK;
	}
	inline STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR* /* pcbSize */)
	{
		return E_NOTIMPL;
	}
};

}; // namespace StingrayOTL 

#endif // __OTLPERSISTSTREAM_H__
