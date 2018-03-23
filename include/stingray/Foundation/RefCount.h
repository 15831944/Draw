///////////////////////////////////////////////////////////////////////////////
// RefCount.h
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

#ifndef __REFCOUNT_H__
#define __REFCOUNT_H__

#include <objbase.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc IRefCount
//
//@class IRefCount | This class provides methods for reference counting
// objects. It is used in order to do interface based programming in C++.
// The AddRef and Release methods it defines have the same signature as
// IUnknown.

class __declspec(uuid("8407B2B0-4B5E-11d3-AF1B-006008AFE059")) IRefCount
{
public:
	//@cmember,mfunc
	// Add a reference to this object.
	//@@rdesc New reference count value.
	//@@end
	/* Add a reference to this object*/
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	//@cmember,mfunc
	// Release a reference to this object.
	//@@rdesc New reference count value.
	//@@end
	/* Release a reference to this object*/
	virtual ULONG STDMETHODCALLTYPE Release() = 0;
};

/////////////////////////////////////////////////////////////////////////////
//@doc CRefCountImpl
//
//@mfunc | CRefCountImpl | CRefCountImpl | Default constructor sets reference
// count to zero.

//@doc CRefCountImpl
//@mfunc ULONG | CRefCountImpl | AddRef | Add a reference to this object.
//@rdesc New reference count value.

//@doc CRefCountImpl
//@mfunc ULONG | CRefCountImpl | Release | Release a reference to this object.
//@rdesc New reference count value.

//@class Template to implement reference counting for an interface. This class
// derives itself from the template parameter passed in and overrides AddRef
// and Release.

template<class base_t>
class CRefCountImpl : public base_t
{
public:

	//@cmember
	/* Constructor to set reference count to zero. */
	CRefCountImpl()
	{
		m_ulRefCount = 0;
	}

	//@cmember
	/* Empty virtual destructor */
	virtual ~CRefCountImpl()
	{
	}

	//@cmember
	/* Constructor to set reference count to zero. */
	ULONG STDMETHODCALLTYPE AddRef()
	{
		return ++m_ulRefCount;
	}

	//@cmember
	/* Constructor to set reference count to zero. */
	ULONG STDMETHODCALLTYPE Release()
	{
		ULONG ulRefCount = --m_ulRefCount;
		if (m_ulRefCount == 0)
			delete this;
		return ulRefCount;
	}

protected:
	//@cmember
	/* Stores reference count for object. */
	ULONG m_ulRefCount;
};

#define IRefCountImpl_T CRefCountImpl

template<class base_t>
class CNoRefCountImpl : public base_t
{
public:
	//@cmember
	/* Constructor to set reference count to zero. */
	ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1L;
	}

	//@cmember
	/* Constructor to set reference count to zero. */
	ULONG STDMETHODCALLTYPE Release()
	{
		return 1L;
	}
};

};  // namespace stingray::foundation
};  // namespace stingray

#endif   // __REFCOUNT_H__
