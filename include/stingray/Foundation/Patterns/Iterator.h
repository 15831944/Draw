///////////////////////////////////////////////////////////////////////////////
// Iterator.h : SFL Polymorphic iterator 
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
// Description:  SFL polymorphic iterator implementation
//


#pragma once

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4786)
	#pragma warning( disable : 4251 4512) // See Microsoft KB article Q168958
#endif

#include <StingrayExportDefs.h>

#if !defined(_SFL)
#define _SFL
#endif

namespace stingray {
namespace foundation {

template <typename _Elem>
class IteratorBase 
{
public:

	typedef typename _Elem Element;
	virtual ~IteratorBase() {}

public:
	virtual typename Element Next() = 0;
	virtual typename Element Prev() = 0;
	virtual typename Element Current() = 0;
	virtual bool Finished() = 0;
	virtual void Start() = 0;
};


#if _MSC_VER <= 1300
template <typename _Aggr, typename _Iter = _Aggr::iterator, typename _Elem = _Aggr::value_type>
#else
template <typename _Aggr, typename _Iter = typename _Aggr::iterator, typename _Elem = typename _Aggr::value_type>
#endif
class Iterator : public IteratorBase<_Elem>
{
public:
	explicit Iterator(typename _Aggr& acollection): _coll(acollection) {Start();}

public:

	// Polymorphic iteration methods
	virtual typename Element Next();
	virtual typename Element Prev();
	virtual typename Element Current();
	virtual bool Finished();
	virtual void Start();

private:
	typename _Aggr& _coll;
	typename _Iter _it;
};


template <typename _Aggr, typename _Iter, typename _Elem>
typename Iterator<_Aggr, _Iter, _Elem>::Element 
Iterator<_Aggr, _Iter, _Elem>::Next()
{
	++_it;
	return Current();
}

template <typename _Aggr, typename _Iter, typename _Elem>
typename Iterator<_Aggr, _Iter, _Elem>::Element 
Iterator<_Aggr, _Iter, _Elem>::Prev()
{
	--_it;
	return Current();
}

template <typename _Aggr, typename _Iter, typename _Elem>
typename Iterator<_Aggr, _Iter, _Elem>::Element 
Iterator<_Aggr, _Iter, _Elem>::Current()
{
	return *_it;
}

template <typename _Aggr, typename _Iter, typename _Elem>
bool 
Iterator<_Aggr, _Iter, _Elem>::Finished()
{
	return _it == _coll.end();
}

template <typename _Aggr, typename _Iter, typename _Elem>
void 
Iterator<_Aggr, _Iter, _Elem>::Start()
{
	_it = _coll.begin();
}


};
};

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(pop)
	#endif //1200 <= _MSC_VER
#endif //_SFL_NO_PRAGMA_WARNINGS

#endif // #ifndef __ITERATOR_H__
