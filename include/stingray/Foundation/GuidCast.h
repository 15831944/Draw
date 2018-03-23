///////////////////////////////////////////////////////////////////////////////
// GuidCast.h
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

#ifndef __GUIDCAST_H__
#define __GUIDCAST_H__

#include <wtypes.h>
#include <StingrayExportDefs.h>


namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////
//@doc IQueryGuid
//
//@class IQueryGuid | This interface provides a method very similar
// to QueryInterface. The <mf IQueryGuid::QueryGuid> function is
// more generic and can be used to query an object for any type of
// pointer based given a GUID. QueryInterface can be thought of as
// a subset of QueryGuid.  QueryGuid is simply a replacement for
// compiler RTTI.

class __declspec(uuid("8407B2B1-4B5E-11d3-AF1B-006008AFE059")) IQueryGuid
{
public:
	//@cmember,mfunc Cast object to a pointer type given a GUID.
	//@@rdesc true if object is successfully cast to the new data type, otherwise false.
	//@@parm REFGUID | guid | Input GUID that determines the data type to cast to.
	//@@parm void ** | ppvObj | Output parameter to receive the result of the cast.
	//@@comm
	// This function is very similar to IUnknown's QueryInterface, but it is more
	// generic. It can be used to cast to any C++ data type using a GUID. It provides
	// a more flexible and efficient way to dynamically cast objects and doesn't
	// incur the overhead of C++ RTTI.
	//@@end
	/* Cast object to a pointer type given a GUID*/
	virtual bool QueryGuid(REFGUID guid, void **ppvObj) = 0;
};


};	// namespace stingray::foundation
};	// namespace stingray


///////////////////////////////////////////////////////////////////
// guid_cast is a function template that calls QueryGuid on the
// object passed in.

template<class to_t, class from_t>
to_t guid_cast(from_t* pFrom)
{
	to_t pTo = NULL;
	if (pFrom) {
		pFrom->QueryGuid(__uuidof(to_t), (void**) &pTo);
	}
	return pTo;
}


template<class to_t, const GUID* guid, class from_t>
to_t guid_cast(from_t* pFrom)
{
	to_t pTo = NULL;
	if (pFrom) {
		pFrom->QueryGuid(*guid, (void**) &pTo);
	}
	return pTo;
}
///////////////////////////////////////////////////////////////////
// GUID map macros for implementing the QueryGuid() function.

#define BEGIN_GUID_MAP(CLASSNAME)  \
	virtual bool QueryGuid(REFGUID guid, void **ppvObj) {  *ppvObj = NULL; \

#define GUID_ENTRY(T)  \
	if (guid == __uuidof(T)) { *ppvObj=static_cast<T*>(this); return true; } \

#define GUID_ENTRY2(T,X)  \
	if (guid == __uuidof(T)) { *ppvObj=static_cast<X*>(this); return true; } \

#define GUID_ENTRY_IID(iid, T)  \
	if (guid == iid) { *ppvObj=static_cast<T*>(this); return true; } \

#define GUID_CHAIN_ENTRY(T)  \
	if (T::QueryGuid(guid, ppvObj)) return true; \

#define END_GUID_MAP  return false; }

#endif  // __GUIDCAST_H__
