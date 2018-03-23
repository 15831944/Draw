///////////////////////////////////////////////////////////////////////////////
// Traversable.h : SFL Polymorphic iterator 
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
// Author:       Dean Hallman
// Description:  SFL traversable implementation
//

#pragma once
#pragma warning(disable:4786)


#if !defined(_SFL)
#define _SFL
#endif

#include <unknwn.h>
#include <Foundation\RefCount.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

// Sub Iterator Handle type
struct FOUNDATION_API _sih  
{
};

template < class _Ty >
struct IConstForwardTraversableT
{
	// Iterator Implementation Members
	 virtual _sih* _const_iterator_create() const = 0; 
	 virtual _sih* _const_iterator_create_from(_sih*) const = 0; 
	 virtual void _const_iterator_destroy(_sih*) const = 0; 
	 virtual void _const_iterator_begin(_sih*) const = 0; 
	 virtual void _const_iterator_end(_sih*) const = 0; 
	 virtual bool _const_iterator_at_begin(_sih*) const = 0; 
	 virtual bool _const_iterator_at_end(_sih*) const = 0; 
	 virtual void _const_iterator_next(_sih*) const = 0; 
	 virtual void _const_iterator_prev(_sih*) const = 0; 
	 virtual bool _const_iterator_iseql(_sih*, _sih*) const = 0; 
	 virtual typename const _Ty& _const_iterator_get(_sih*) const = 0;
};

template < class _Ty >
struct IConstReverseTraversableT
{
	 virtual _sih* _const_reverse_iterator_create() const = 0; 
	 virtual _sih* _const_reverse_iterator_create_from(_sih*) const = 0; 
	 virtual void _const_reverse_iterator_destroy(_sih*) const = 0; 
	 virtual void _const_reverse_iterator_begin(_sih*) const = 0; 
	 virtual void _const_reverse_iterator_end(_sih*) const = 0; 
	 virtual bool _const_reverse_iterator_at_begin(_sih*) const = 0; 
	 virtual bool _const_reverse_iterator_at_end(_sih*) const = 0; 
	 virtual void _const_reverse_iterator_next(_sih*) const = 0; 
	 virtual void _const_reverse_iterator_prev(_sih*) const = 0; 
	 virtual bool _const_reverse_iterator_iseql(_sih*, _sih*) const = 0; 
	 virtual typename const _Ty& _const_reverse_iterator_get(_sih*) const = 0;
};
 
template < class _Ty >
struct IForwardTraversableT : public IConstForwardTraversableT< typename _Ty >
{
	 virtual _sih* _iterator_create() const = 0; 
	 virtual _sih* _iterator_create_from(_sih*) const = 0; 
	 virtual void _iterator_destroy(_sih*) const = 0; 
	 virtual void _iterator_begin(_sih*) = 0; 
	 virtual void _iterator_end(_sih*) = 0; 
	 virtual bool _iterator_at_begin(_sih*) = 0; 
	 virtual bool _iterator_at_end(_sih*) = 0; 
	 virtual void _iterator_next(_sih*) const = 0; 
	 virtual void _iterator_prev(_sih*) const = 0; 
	 virtual bool _iterator_iseql(_sih*, _sih*) const = 0; 
	 virtual typename const _Ty& _iterator_get(_sih*) const = 0;

	// Write functions
	 virtual typename _Ty& _iterator_wget(_sih*) const = 0;
	 virtual void _iterator_erase(_sih*) = 0;
	 virtual void _iterator_insert(_sih*, const _Ty&) = 0;

};

template < class _Ty >
struct IReverseTraversableT : public IConstReverseTraversableT< typename _Ty >
{
	 virtual _sih* _reverse_iterator_create() const = 0; 
	 virtual _sih* _reverse_iterator_create_from(_sih*) const = 0; 
	 virtual void _reverse_iterator_destroy(_sih*) const = 0; 
	 virtual void _reverse_iterator_begin(_sih*) = 0; 
	 virtual void _reverse_iterator_end(_sih*) = 0; 
	 virtual bool _reverse_iterator_at_begin(_sih*) = 0; 
	 virtual bool _reverse_iterator_at_end(_sih*) = 0; 
	 virtual void _reverse_iterator_next(_sih*) const = 0; 
	 virtual void _reverse_iterator_prev(_sih*) const = 0; 
	 virtual bool _reverse_iterator_iseql(_sih*, _sih*) const = 0; 
	 virtual typename const _Ty& _reverse_iterator_get(_sih*) const = 0;

	// Write functions
	 virtual typename _Ty& _reverse_iterator_wget(_sih*) const = 0;
};

/////////////////////////////
//
//@doc IConstTraversableT
//
//@class IConstTraversableT | The IConstTraversableT
//  templated interface is an abstract interface that
//  enables polymorphic iteration.  A polymorphic
//  iterator is one which performs traversal without
//  explicit knowledge of collection type.  Instead,
//  it uses the IConstTraversableT interface, which
//  permits access to elements without exposing collection
//  type.   The IConstTraversableT interface can be mixed
//  into any aggregate, thereby enabling polymorphic
//  iteration for that aggregate. Therefore, this interface
//  serves as a useful abstraction for an aggregate,
//  because it can be returned, passed between functions,
//  and used by polymorphic iterators without subjecting
//  client code to unnecessary implementation-oriented
//  dependencies.
//
//  The IConstTraversableT interface permits constant
//  access to the aggregate only.  If you need to
//  pass an aggregate to a function, you can prevent
//  that function from modifying collection content
//  by passing it an IConstTraversableT interface.
//  If the function requires read/write access to the
//  collection, you can use the <c ITraversableT> interface
//  instead.
//
//  Note: The IConstTraversableT interface has many
//  member functions but only four are documented.  The
//  remaining members are meant to be used by the
//  polymorphic iterators only.
//
//@tcarg class | _Ty | The type of element contained
//  in the aggregate that implements this interface.
//
// Member functions include:
//  <mf IConstTraversableT::AddRef>
//  <mf IConstTraversableT::Release>
//  <mf IConstTraversableT::empty>
//  <mf IConstTraversableT::size>
//
template < class _Ty >
struct IConstTraversableT 
	: public IConstForwardTraversableT < typename _Ty >,
	  public IConstReverseTraversableT < typename _Ty >
{
	//@cmember
	/* Increments the reference count on the aggregate. */
	 virtual ULONG STDMETHODCALLTYPE AddRef() const = 0;

	//@cmember
	/* Decrements the reference count on the aggregate. */
	 virtual ULONG STDMETHODCALLTYPE Release() const = 0;

	//@cmember
	/* Returns true if the traversable object is empty. */
	 virtual bool empty() const = 0;

	//@cmember
	/* Returns the number of elements contained. */
	 virtual SEC_INT size() const = 0;
};

/////////////////////////////
//
//@doc ITraversableT
//
//@class ITraversableT | The ITraversableT
//  templated interface is an abstract interface that
//  enables polymorphic iteration.  A polymorphic
//  iterator is one which performs traversal without
//  explicit knowledge of collection type.  Instead,
//  it uses the ITraversableT interface, which
//  permits access to elements without exposing collection
//  type.   The ITraversableT interface can be mixed
//  into any aggregate, thereby enabling polymorphic
//  iteration for that aggregate. Therefore, this interface
//  serves as a useful abstraction for an aggregate,
//  because it can be returned, passed between functions,
//  and used by polymorphic iterators without subjecting
//  client code to unnecessary implementation-oriented
//  dependencies.
//
//  The ITraversableT interface permits read/write
//  access to the aggregate.  Pass this interface to
//  functions that must modify the contents of the
//  underlying aggregate.  If you want to restrict
//  such functions from modifying, passing the
//  <c IConstTraversableT> interface instead.
//
//  Note: The ITraversableT interface has many
//  member functions but only one is documented.  The
//  remaining members are meant to be used by the
//  polymorphic iterators only.
//
//@tcarg class | _Ty | The type of element contained
//  in the aggregate that implements this interface.
//
// Member functions include:
//  <mf ITraversableT::clear>
//
template < class _Ty >
struct ITraversableT
	: public IConstTraversableT < typename _Ty >,
	  public IForwardTraversableT < typename _Ty >,
	  public IReverseTraversableT < typename _Ty >
{
	 virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	 virtual ULONG STDMETHODCALLTYPE Release() = 0;

	//@cmember
	/* Clears the contents of the underlying aggregate. */
	 virtual void clear() = 0;
};

/////////////////////////////
//
//@doc const_traversable
//
//@class const_traversable | The const_traversable
//  template is a helper that takes the grunt work
//  out of implementing the IConstTraversableT interface.
//  Use this template to automatically "decorate" an STL
//  or STL-compatible collection with const traversability.
//  To use the const_traversable template, simply wrap
//  an existing collection declaration as follows:
//
//     vector<int> v;
//
// becomes...
//
//     const_traversable< vector<int> > v;
// 
// With this simple modification, the vector "v" now
// implements the IConstTraversableT interface and
// therefore supports polymorphic iteration over its
// contents.  For example:
//
//      const_traversable< vector<int> > v;
//      const_iterator< int > i(&v);
//      for (i.begin(); !i.at_end(); i++) {
//         //do something
//       }
//      
//  The const_traversable template has many template
//  parameters.  However, only the first two are
//  likely to be used.  The first template parameter,
//  _coll, is the collection to decorate with const
//  traversability.  The const_traversable template
//  derives from the _coll parameter and mixes in
//  the IConstTraversableT interface.  Because the
//  template derives from _coll, the original interface
//  to the collection is preserved, allowing the
//  collection to be initialized and used as before.
//
//  The second parameter is the predicate used with
//  sets and maps.  If you are decorating a vector,
//  list, or deque, this parameter is irrelevant because
//  those structures don't use a predicate.  However,
//  sets and maps use them.  If you need to pass a
//  predicate to a set or map constructor, you'll have
//  to specify this parameter.  For example:
//
// 		const_traversable<
//          set<int, std::greater<int> >,
//          std::greater<int>
//          > s(std::greater<int>());
//
//  A note on lifetime management.  The IConstTraversableT
//  interface makes lifetime management feasible through
//  its AddRef and Release members.  However, because
//  const_traversable derives from the wrapped collection, it
//  is up to the underlying aggregate to actually manage its
//  own lifetime in accordance with the reference count.
//  STL collections do not manage their lifetime in this way.
//  Therefore, the AddRef and Release members are no-ops in
//  the const_traversable template.  Use the sister template
//  <c refcounted_const_traversable> to wrap an aggregate
//  that does support reference counting.
//
//@tcarg class | _coll | The collection type to derive
//  from and mix in IConstTraversable.
//@tcarg class | predicate_type | The predicate to use
//  with STL sets and maps.
//
template <
	class _coll,
	typename predicate_type = typename std::less<typename _coll::value_type>,
	typename const_iterator = typename _coll::const_iterator,
	typename const_reverse_iterator = typename _coll::const_reverse_iterator,
	typename value_type = typename _coll::value_type,
	typename allocator_type = typename _coll::allocator_type,
	typename size_type = typename _coll::size_type,
	typename collection_type = typename _coll::_Myt,
	typename constructor_iterator = typename _coll::const_iterator
	>
class const_traversable : public _coll, public IConstTraversableT<typename value_type>
{
protected:

	///////////////////////////////////////////////////////////////////////////
	//
	// Const Iterator Members
	//

	typedef typename struct const_iterator_hs : public _sih { typename const_iterator i; } const_iterator_hdl;
	
	inline _sih* _const_iterator_create() const { return new const_iterator_hdl; }
	
	inline _sih* _const_iterator_create_from(_sih* psih) const 
	{ 
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		typename const_iterator_hdl* pnsi = new const_iterator_hdl;
		if(pnsi)
		{
			pnsi->i = psi->i;
		}
		return pnsi; 
	}
	
	inline void _const_iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _const_iterator_begin(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		psi->i = begin(); 
	}
	
	inline void _const_iterator_end(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		psi->i = end(); 
	}
	
	inline bool _const_iterator_at_begin(_sih* psih) const 
	{ 
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		return psi->i == begin(); 
	}
	
	inline bool _const_iterator_at_end(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		return psi->i == end(); 
	}
	
	inline void _const_iterator_next(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		psi->i++; 
	}
	
	inline void _const_iterator_prev(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		psi->i--; 
	}
	
	inline bool _const_iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		typename const_iterator_hdl* psi1 = static_cast<typename const_iterator_hdl*>(psih1);
		typename const_iterator_hdl* psi2 = static_cast<typename const_iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline const value_type& _const_iterator_get(_sih* psih) const 
	{
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		return *(psi->i); 
	}


	///////////////////////////////////////////////////////////////////////////
	//
	// Const Reverse Iterator Members
	//
	typedef typename struct const_reverse_iterator_hs : public _sih { typename const_reverse_iterator i; } const_reverse_iterator_hdl;
	
	inline _sih* _const_reverse_iterator_create() const { return new const_reverse_iterator_hdl; }
	
	inline _sih* _const_reverse_iterator_create_from(_sih* psih) const 
	{		
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		typename const_reverse_iterator_hdl* pnsi = new const_reverse_iterator_hdl;
		if(pnsi)
		{
			pnsi->i = psi->i;
		}
		return pnsi; 
	}
	
	inline void _const_reverse_iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _const_reverse_iterator_begin(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i = rbegin(); 
	}
	
	inline void _const_reverse_iterator_end(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i = rend(); 
	}
	
	inline bool _const_reverse_iterator_at_begin(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return psi->i == rbegin(); 
	}
	
	inline bool _const_reverse_iterator_at_end(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return psi->i == rend(); 
	}
	
	inline void _const_reverse_iterator_next(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i++;
	}
	
	inline void _const_reverse_iterator_prev(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i--; 
	}
	
	inline bool _const_reverse_iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		typename const_reverse_iterator_hdl* psi1 = static_cast<typename const_reverse_iterator_hdl*>(psih1);
		typename const_reverse_iterator_hdl* psi2 = static_cast<typename const_reverse_iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline typename const value_type& _const_reverse_iterator_get(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return *(psi->i); 
	}

public:

	///////////////////////////////////////////////////////////////////////////
	//
	// Const Queries
	//

	inline bool empty() const {	return _coll::empty(); }

	inline SEC_INT size() const { return _coll::size(); }

	///////////////////////////////////////////////////////////////////////////
	//
	// Lifetime Management
	//

	// The underlying collection doesn't support reference counting.
	// (i.e. std::vector<>). So, just define the refcounting members so they resolve.
	inline ULONG STDMETHODCALLTYPE AddRef() const {	return 1; };
	inline ULONG STDMETHODCALLTYPE Release() const { return 1; };
	
	///////////////////////////////////////////////////////////////////////////
	//
	// Constructor Candidates
	//   - Note, these are constructor candidates because only the
	//     constructors you call in your code get instantiated.
	//     This is important because not all collection classes
	//     support all the constructor candidates.
	//  

protected:

	typedef typename constructor_iterator _It;

public:
	
	explicit const_traversable () : _coll() {}
	explicit const_traversable (typename const allocator_type& _Al)	: _coll(_Al) {}
	explicit const_traversable (size_type _N) : _coll(_N) {}
	explicit const_traversable (size_type _N, typename const value_type& _V): _coll(_N, _V) {}
	explicit const_traversable (size_type _N, typename const value_type& _V, typename const allocator_type& _Al) : _coll(_N, _V, _Al) {}
	const_traversable (typename const collection_type& _X) : _coll(_X) {}
	const_traversable (typename _It _F, typename _It _L) : _coll(_F, _L) {}
	const_traversable (typename _It _F, typename _It _L, typename const allocator_type& _Al) : _coll(_F, _L, _Al) {}
	explicit const_traversable (typename const predicate_type& _Pred) : _coll(_Pred) {}
	explicit const_traversable (typename const predicate_type& _Pred, typename const allocator_type& _Al) : _coll(_Pred, _Al) {}
	const_traversable (typename _It _F, typename _It _L, typename const predicate_type& _Pred) : _coll(_F, _L, _Pred) {}
	const_traversable (typename _It _F, typename _It _L, typename const predicate_type& _Pred, typename const allocator_type& _Al) : _coll(_F, _L, _Pred, _Al) {}

};



/////////////////////////////
//
//@doc traversable
//
//@class traversable | The traversable
//  template is a helper that takes the grunt work
//  out of implementing the ITraversableT interface.
//  Use this template to automatically "decorate" an STL
//  or STL-compatible collection with const traversability.
//  To use the traversable template, simply wrap
//  an existing collection declaration as follows:
//
//     vector<int> v;
//
// becomes...
//
//     traversable< vector<int> > v;
// 
// With this simple modification, the vector "v" now
// implements the ITraversableT interface and
// therefore supports polymorphic iteration over its
// contents.  For example:
//
//      traversable< vector<int> > v;
//      const_iterator< int > i(&v);
//      for (i.begin(); !i.at_end(); i++) {
//         //do something
//       }
//      
//  The traversable template has many template
//  parameters.  However, only the first two are
//  likely to be used.  The first template parameter,
//  _coll, is the collection to decorate with const
//  traversability.  The traversable template
//  derives from the _coll parameter and mixes in
//  the ITraversableT interface.  Because the
//  template derives from _coll, the original interface
//  to the collection is preserved, allowing the
//  collection to be initialized and used as before.
//
//  The second parameter is the predicate used with
//  sets and maps.  If you are decorating a vector,
//  list, or deque, this parameter is irrelevant because
//  those structures don't use a predicate.  However,
//  sets and maps use them.  If you need to pass a
//  predicate to a set or map constructor, you'll have
//  to specify this parameter.  For example:
//
// 		traversable<
//          set<int, std::greater<int> >,
//          std::greater<int>
//          > s(std::greater<int>());
//
//  A note on lifetime management.  The ITraversableT
//  interface makes lifetime management feasible through
//  its AddRef and Release members.  However, because
//  traversable derives from the wrapped collection, it is
//  up to the underlying aggregate to actually manage its
//  own lifetime in accordance with the reference count.
//  STL collections do not manage their lifetime in this way.
//  Therefore, the AddRef and Release members are no-ops in
//  the traversable template.  Use the sister template
//  <c refcounted_traversable> to wrap an aggregate
//  that does support reference counting.
//
//@tcarg class | _coll | The collection type to derive
//  from and mix in IConstTraversable.
//@tcarg class | predicate_type | The predicate to use
//  with STL sets and maps.
//
template <
	class _coll,
	typename predicate_type = typename std::less<typename _coll::value_type>,
	typename const_iterator = typename _coll::const_iterator,
	typename const_reverse_iterator = typename _coll::const_reverse_iterator,
	typename iterator = typename _coll::iterator,
	typename reverse_iterator = typename _coll::reverse_iterator,
	typename value_type = typename _coll::value_type,
	typename allocator_type = typename _coll::allocator_type,
	typename size_type = typename _coll::size_type,
	typename collection_type = typename _coll::_Myt,
	typename constructor_iterator = typename _coll::const_iterator
	>
class FOUNDATION_API traversable : public _coll, public ITraversableT<typename value_type>
{
protected:

	///////////////////////////////////////////////////////////////////////////
	//
	// Const Iterator Members
	//

	typedef struct const_iterator_hs : public _sih { typename const_iterator i; } const_iterator_hdl;
	
	inline _sih* _const_iterator_create() const { return new const_iterator_hdl; }
	
	inline _sih* _const_iterator_create_from(_sih* psih) const 
	{		
		typename const_iterator_hdl* psi = static_cast<typename const_iterator_hdl*>(psih);
		typename const_iterator_hdl* pnsi = new const_iterator_hdl;
		if(pnsi)
		{
			pnsi->i = psi->i;
		}
		return pnsi; 
	}
	
	inline void _const_iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _const_iterator_begin(_sih* psih) const 
	{ 
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		psi->i = begin(); 
	}
	
	inline void _const_iterator_end(_sih* psih) const 
	{
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		psi->i = end(); 
	}
	
	inline bool _const_iterator_at_begin(_sih* psih) const 
	{ 
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		return psi->i == begin(); 
	}
	
	inline bool _const_iterator_at_end(_sih* psih) const 
	{
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		return psi->i == end(); 
	}
	
	inline void _const_iterator_next(_sih* psih) const 
	{
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		psi->i++; 
	}
	
	inline void _const_iterator_prev(_sih* psih) const 
	{
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		psi->i--; 
	}
	
	inline bool _const_iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		const_iterator_hdl* psi1 = static_cast<const_iterator_hdl*>(psih1);
		const_iterator_hdl* psi2 = static_cast<const_iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline typename const value_type& _const_iterator_get(_sih* psih) const 
	{
		const_iterator_hdl* psi = static_cast<const_iterator_hdl*>(psih);
		return *(psi->i); 
	}


	///////////////////////////////////////////////////////////////////////////
	//
	// Const Reverse Iterator Members
	//
	typedef typename struct const_reverse_iterator_hs : public _sih { typename const_reverse_iterator i; } const_reverse_iterator_hdl;
	
	inline _sih* _const_reverse_iterator_create() const { return new const_reverse_iterator_hdl; }
	
	inline _sih* _const_reverse_iterator_create_from(_sih* psih) const 
	{ 
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		typename const_reverse_iterator_hdl* pnsi = new const_reverse_iterator_hdl;
		if(pnsi)
		{
			pnsi->i = psi->i;
		}
		return pnsi; 
	}
	
	inline void _const_reverse_iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _const_reverse_iterator_begin(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i = rbegin(); 
	}
	
	inline void _const_reverse_iterator_end(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i = rend(); 
	}
	
	inline bool _const_reverse_iterator_at_begin(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return psi->i == rbegin(); 
	}
	
	inline bool _const_reverse_iterator_at_end(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return psi->i == rend(); 
	}
	
	inline void _const_reverse_iterator_next(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i++; 
	}
	
	inline void _const_reverse_iterator_prev(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		psi->i--;
	}
	
	inline bool _const_reverse_iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		typename const_reverse_iterator_hdl* psi1 = static_cast<typename const_reverse_iterator_hdl*>(psih1);
		typename const_reverse_iterator_hdl* psi2 = static_cast<typename const_reverse_iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline typename const value_type& _const_reverse_iterator_get(_sih* psih) const 
	{
		typename const_reverse_iterator_hdl* psi = static_cast<typename const_reverse_iterator_hdl*>(psih);
		return *(psi->i); 
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Iterator Members
	//

	typedef typename struct iterator_hs : public _sih { typename iterator i; } iterator_hdl;
	
	inline _sih* _iterator_create() const { return new iterator_hdl; }
	
	inline _sih* _iterator_create_from(_sih* psih) const 
	{		
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		typename iterator_hdl* pnsi = new iterator_hdl;
		if(pnsi)
		{
			pnsi->i = psi->i;
		}
		return pnsi; 
	}
	
	inline void _iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _iterator_begin(_sih* psih) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		psi->i = begin(); 
	}
	
	inline void _iterator_end(_sih* psih) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		psi->i = end(); 
	}
	
	inline bool _iterator_at_begin(_sih* psih) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		return psi->i == begin(); 
	}
	
	inline bool _iterator_at_end(_sih* psih) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		return psi->i == end(); 
	}
	
	inline void _iterator_next(_sih* psih) const 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		psi->i++; 
	}
	
	inline void _iterator_prev(_sih* psih) const 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		psi->i--; 
	}
	
	inline bool _iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		typename iterator_hdl* psi1 = static_cast<typename iterator_hdl*>(psih1);
		typename iterator_hdl* psi2 = static_cast<typename iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline const value_type& _iterator_get(_sih* psih) const 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		return *(psi->i); 
	}

	inline value_type& _iterator_wget(_sih* psih) const 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		return *(psi->i); 
	}

	inline void _iterator_erase(_sih* psih) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		_coll::erase(psi->i); 
	}

	inline void _iterator_insert(_sih* psih, typename const value_type& _X) 
	{
		typename iterator_hdl* psi = static_cast<typename iterator_hdl*>(psih);
		_coll::insert(psi->i, _X); 
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Reverse Iterator Members
	//
	typedef typename struct reverse_iterator_hs : public _sih { typename reverse_iterator i; } reverse_iterator_hdl;
	
	inline _sih* _reverse_iterator_create() const { return new reverse_iterator_hdl; }
	
	inline _sih* _reverse_iterator_create_from(_sih* psih) const 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		typename reverse_iterator_hdl* pnsi = new reverse_iterator_hdl;
		pnsi->i = psi->i;
		return pnsi; 
	}
	
	inline void _reverse_iterator_destroy(_sih* psih) const { delete psih; }
	
	inline void _reverse_iterator_begin(_sih* psih) 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		psi->i = rbegin(); 
	}
	
	inline void _reverse_iterator_end(_sih* psih) 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		psi->i = rend(); 
	}
	
	inline bool _reverse_iterator_at_begin(_sih* psih) 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		return psi->i == rbegin(); 
	}
	
	inline bool _reverse_iterator_at_end(_sih* psih) 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		return psi->i == rend(); 
	}
	
	inline void _reverse_iterator_next(_sih* psih) const 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		psi->i++; 
	}
	
	inline void _reverse_iterator_prev(_sih* psih) const 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		psi->i--; 
	}
	
	inline bool _reverse_iterator_iseql(_sih* psih1, _sih* psih2) const 
	{
		typename reverse_iterator_hdl* psi1 = static_cast<typename reverse_iterator_hdl*>(psih1);
		typename reverse_iterator_hdl* psi2 = static_cast<typename reverse_iterator_hdl*>(psih2);
		return psi1->i == psi2->i; 
	}
	
	inline typename const value_type& _reverse_iterator_get(_sih* psih) const 
	{
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		return *(psi->i); 
	}

	inline typename value_type& _reverse_iterator_wget(_sih* psih) const 
	{		
		typename reverse_iterator_hdl* psi = static_cast<typename reverse_iterator_hdl*>(psih);
		return *(psi->i); 
	}

public:

	///////////////////////////////////////////////////////////////////////////
	//
	// Queries
	//

	inline bool empty() const { return _coll::empty(); }

	inline SEC_INT size() const { return _coll::size(); }

	inline void clear() { _coll::clear(); }

	///////////////////////////////////////////////////////////////////////////
	//
	// Lifetime Management
	//

	// The underlying collection doesn't support reference counting.
	// (i.e. std::vector<>). So, just define the refcounting members so they resolve.
	inline ULONG STDMETHODCALLTYPE AddRef() const { return 1; };
	inline ULONG STDMETHODCALLTYPE Release() const { return 1; };
	inline ULONG STDMETHODCALLTYPE AddRef() { return 1; };
	inline ULONG STDMETHODCALLTYPE Release() { return 1; };

	///////////////////////////////////////////////////////////////////////////
	//
	// Constructor Candidates
	//   - Note, these are constructor candidates because only the
	//     constructors you call in your code get instantiated.
	//     This is important because not all collection classes
	//     support all the constructor candidates.
	//

protected:

	typedef constructor_iterator _It;

public:

	explicit traversable () : _coll() {}
	explicit traversable (typename const allocator_type& _Al) : _coll(_Al) {}
	explicit traversable (size_type _N) : _coll(_N) {}
	explicit traversable (size_type _N, typename const value_type& _V) : _coll(_N, _V) {}
	explicit traversable (size_type _N, typename const value_type& _V, typename const allocator_type& _Al) : _coll(_N, _V, _Al) {}
	traversable (typename const collection_type& _X) : _coll(_X) {}
	traversable (typename _It _F, typename _It _L) : _coll(_F, _L) {}
	traversable (typename _It _F, typename _It _L, typename const allocator_type& _Al) : _coll(_F, _L, _Al) {}
	explicit traversable (typename const predicate_type& _Pred)	: _coll(_Pred) {}
	explicit traversable (typename const predicate_type& _Pred, typename const allocator_type& _Al) : _coll(_Pred, _Al) {}
	traversable (typename _It _F, typename _It _L, typename const predicate_type& _Pred) : _coll(_F, _L, _Pred) {}
	traversable (typename _It _F, typename _It _L, typename const predicate_type& _Pred, typename const allocator_type& _Al) : _coll(_F, _L, _Pred, _Al) {}

};

/////////////////////////////
//
//@doc refcounted_const_traversable
//
//@class refcounted_const_traversable | The
//  refcounted_const_traversable template is
//  identical to const_traversable, except it actually
//  implements the AddRef and Release members.  The
//  sister const_traversable template makes these
//  members no-ops.  This template implements
//  AddRef and Release such that all calls are
//  delegated to the underlying collection.
//
//@tcarg class | _coll | The collection type to derive
//  from and mix in IConstTraversable.
//@tcarg class | predicate_type | The predicate to use
//  with STL sets and maps.
//
template <
	class _coll,
	typename predicate_type = typename std::less<typename _coll::value_type>,
	typename const_iterator = typename _coll::const_iterator,
	typename const_reverse_iterator = typename _coll::const_reverse_iterator,
	typename value_type = typename _coll::value_type,
	typename allocator_type = typename _coll::allocator_type,
	typename size_type = typename _coll::size_type,
	typename collection_type = typename _coll::_Myt,
	typename constructor_iterator = typename _coll::const_iterator
	>
class FOUNDATION_API refcounted_const_traversable : public const_traversable< 
					typename _coll,
					typename predicate_type,
					typename const_iterator,
					typename const_reverse_iterator,
					typename value_type,
					typename allocator_type,
					typename size_type,
					typename collection_type,
					typename constructor_iterator
					>
{
public:

	///////////////////////////////////////////////////////////////////////////
	//
	// Lifetime Management
	//

	// The underlying collection does support reference counting.
	// So, just delegate to its AddRef/Release members.
	inline ULONG STDMETHODCALLTYPE AddRef() const { return (const_cast< typename refcounted_const_traversable < typename _coll >* >(this))->_coll::AddRef(); };
	inline ULONG STDMETHODCALLTYPE Release() const { return (const_cast< typename refcounted_const_traversable < typename _coll >* >(this))->_coll::Release(); };
		
};

/////////////////////////////
//
//@doc refcounted_traversable
//
//@class refcounted_traversable | The
//  refcounted_traversable template is
//  identical to traversable, except it actually
//  implements the AddRef and Release members.  The
//  sister traversable template makes these
//  members no-ops.  This template implements
//  AddRef and Release such that all calls are
//  delegated to the underlying collection.
//
//@tcarg class | _coll | The collection type to derive
//  from and mix in IConstTraversable.
//@tcarg class | predicate_type | The predicate to use
//  with STL sets and maps.
//
template <
	class _coll,
	typename predicate_type = typename std::less<typename _coll::value_type>,
	typename const_iterator = typename _coll::const_iterator,
	typename const_reverse_iterator = typename _coll::const_reverse_iterator,
	typename iterator = typename _coll::iterator,
	typename reverse_iterator = typename _coll::reverse_iterator,
	typename value_type = typename _coll::value_type,
	typename allocator_type = typename _coll::allocator_type,
	typename size_type = typename _coll::size_type,
	typename collection_type = typename _coll::_Myt,
	typename constructor_iterator = typename _coll::const_iterator
	>
class FOUNDATION_API refcounted_traversable
	: public traversable<
				typename _coll,
				typename predicate_type,
				typename const_iterator,
				typename const_reverse_iterator,
				typename iterator,
				typename reverse_iterator,
				typename value_type,
				typename allocator_type,
				typename size_type,
				typename collection_type,
				typename constructor_iterator
				>

{
public:

	///////////////////////////////////////////////////////////////////////////
	//
	// Lifetime Management
	//

	// The underlying collection does support reference counting.
	// So, just delegate to its AddRef/Release members.
	inline ULONG STDMETHODCALLTYPE AddRef() const { return (const_cast< typename refcounted_const_traversable < typename _coll >* >(this))->_coll::AddRef(); };
	inline ULONG STDMETHODCALLTYPE Release() const { return (const_cast< typename refcounted_const_traversable < typename _coll >* >(this))->_coll::AddRef(); };
	inline ULONG STDMETHODCALLTYPE AddRef() { return _coll::AddRef(); };
	inline ULONG STDMETHODCALLTYPE Release() { return _coll::Release(); };
		
};

};
};
