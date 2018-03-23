///////////////////////////////////////////////////////////////////////////////
// Factory.h : SFL Object factory design pattern
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
//
// Author:       Gilberto Araya
// Description:  SFL Object factory design pattern templated implementation
//


#pragma once

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4786)
#endif

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\stwarn.h>
#include <memory>
#include <foundation\stwarnp.h>
#include <foundation\GuidCast.h>

namespace stingray {
namespace foundation {

template <typename _Base>
class CObjectFactoryBase
{
public:
    virtual _Base* CreateObject() const = 0;
	virtual void DestroyObject(_Base* pObject) const = 0;
};


template <typename _Base, typename _Derived, typename _A = typename std::allocator<_Derived> >
class CObjectFactory: 
	public CObjectFactoryBase<typename _Base>
{
public:
    virtual typename _Base* CreateObject() const 
	{ 
		_A a; 
		_Derived* p = a.allocate(1, NULL); 
		a.construct(p, _Derived()); 
		return p;
	}

	virtual void DestroyObject(typename _Base* pObject) const
	{ 
		_A a; 
		_Derived* pD = guid_cast<_Derived*>(pObject);
		if (pD) {
			a.destroy(pD);
			a.deallocate(pD, 1);
		}
	}
};

};	// namespace stingray::foundation
};	// namespace stingray

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
#pragma warning(pop)
	#endif //1200 <= _MSC_VER
#endif //_SFL_NO_PRAGMA_WARNINGS
