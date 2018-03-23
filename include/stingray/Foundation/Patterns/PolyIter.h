///////////////////////////////////////////////////////////////////////////////
// PolyIter.h : SFL Polymorphic Iterator 
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
// Description:  SFL polymorphic iterator implementation
//

#pragma once
#pragma warning(disable:4786)


#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\stwarn.h>
#include <stack>
#include <foundation\stwarnp.h>
#include <Foundation\Patterns\Traversable.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

template <typename _Ty>
class  iterator_base
{
protected:
 
	// Types
	typedef typename _Ty *pointer;
	typedef typename const _Ty *const_pointer;
	typedef typename _Ty& reference;
	typedef typename const _Ty & const_reference;

public:

	typedef typename _Ty value_type;
	typedef typename const _Ty const_value_type;

	virtual void prev() = 0;      
	virtual void next() = 0;
	virtual typename const_reference getref() const = 0;
	virtual typename const_pointer getptr() const = 0;
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual bool at_begin() const = 0;
	virtual bool at_end() const = 0;
	virtual bool iseql(_sih* ) const = 0;
};

/////////////////////////////
//
//@doc const_iterator
//
//@class const_iterator | The const_iterator
//  templated class is an STL-like iterator that can be
//  instantiated and attached to any collection that
//  implements the <c IConstTraversableT> templated interface.
//  Unlike STL's iterators, const_iterator is polymorphic,
//  meaning it can traverse a collection without explicit
//  knowledge of the collection's type. const_iterator is
//  a bidirectional type iterator that is interface
//  compatible with its STL counterpart.  Therefore, it
//  can be used with any STL algorithm which takes a
//  bidirectional iterator. Note, const_iterator does
//  not support random iteration.
//
//@tcarg class | _Ty | The type of element in the collection
//  the iterator is traversing.
//
// Member functions include:
//  <mf const_iterator::const_iterator>
//  <mf const_iterator::begin>
//  <mf const_iterator::end>
//  <mf const_iterator::at_begin>
//  <mf const_iterator::at_end>
//  <mf const_iterator::operator*>
//  <mf const_iterator::operator->>
//  <mf const_iterator::operator++ >
//  <mf const_iterator::operator++>
//  <mf const_iterator::operator-->
//  <mf const_iterator::operator-->
//  <mf const_iterator::operator==>
//  <mf const_iterator::operator!=>
//  <mf const_iterator::operator=>
//
template < class _Ty > class
const_iterator : public iterator_base<typename _Ty>
{
public:

	// Types
	typedef typename const value_type qualified_value_type;
	typedef typename IConstTraversableT<_Ty> traversable_type;
	typedef typename const traversable_type qualified_traversable_type;

protected:

	typename _sih* m_psih;
	typename qualified_traversable_type * m_pct;

public:

	////////////////////////////////////////////////////////
	// Construction

	protected:

	void const_attach(typename qualified_traversable_type* pct) {
		m_pct = pct;
		m_pct->AddRef(); }

	void const_detach() {
		m_pct->Release();
		m_pct = NULL; }

	const_iterator(typename qualified_traversable_type* pct, typename _sih* psih) {
		const_attach(pct);
		m_psih = psih; }

	public:

	const_iterator()
		: m_pct(NULL), m_psih(NULL) {
		}

	//@cmember
	/* Constructs a const_iterator and attaches it to the specified traversable */
	/* of type <c IConstTraversableT>. Notice, you must call <const_iterator::begin> */
	/* or <const_iterator::end> before the iterator is usable. */
	const_iterator(typename qualified_traversable_type* pct) {
		const_attach(pct);
		m_psih = m_pct->_const_iterator_create(); }

	//@cmember
	/* Copy constructor for const_iterator */
	const_iterator( typename const const_iterator<typename _Ty>& iter )  {
		const_attach(iter.m_pct);
		m_psih = m_pct->_const_iterator_create_from(iter.m_psih); }

	virtual ~const_iterator() {
		if (m_psih) {
			m_pct->_const_iterator_destroy(m_psih);
			m_psih = NULL;
			const_detach(); }}

	////////////////////////////////////////////////////////
	// Iterator Base Interface 

	//@cmember
	/* Move the iterator to the previous element in the collection */
	void prev() {
		m_pct->_const_iterator_prev(m_psih); }
   
	//@cmember
	/* Move the iterator to the next element in the collection */
	void next() {
		m_pct->_const_iterator_next(m_psih); }
   
	//@cmember
	/* Return a const reference to the element at the iterator's current position */
	typename const_reference getref() const {
		return m_pct->_const_iterator_get(m_psih); }

	//@cmember
	/* Return a const pointer to the element at the iterator's current position */
	typename const_pointer getptr() const {
		return (&**this); }

	//@cmember
	/* Positions the iterator at the start of the collection */
	void begin() {
		m_pct->_const_iterator_begin(m_psih); }

	//@cmember
	/* Positions the iterator at the end of the collection.  Note, the end
	   is one position passed the last element. */
	void end() {
		m_pct->_const_iterator_end(m_psih); }

	//@cmember
	/* Returns true if currently positioned at start of collection */
	bool at_begin() const {
		return m_pct->_const_iterator_at_begin(m_psih); }

	//@cmember
	/* Returns true if currently positioned at end of collection */
	bool at_end() const {
		return m_pct->_const_iterator_at_end(m_psih); } 

	bool iseql(_sih* other) const {
		return (m_pct->_const_iterator_iseql(m_psih, other)); }
	
 
	///////////////////////////////////////////////////////
	// Operators

	//@cmember
	/* Returns a constant reference to the element at the current iterator position */
	typename const_reference operator*() const {
		return getref(); }

	//@cmember
	/* Returns a constant pointer to the element at the current iterator position */
	typename const_pointer operator->() const {
		return getptr(); }

	//@cmember
	/* The preincrement operator advances the iterator by one position and returns *this */
	typename const_iterator& operator++() {
		next(); return (*this); }

	//@cmember
	/* The postincrement operator advances the iterator by one position and returns an unmoved *this */
	typename const_iterator operator++(int){
		typename const_iterator _Tmp = *this;
		++*this;
		return (_Tmp); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns *this */
	typename const_iterator& operator--() {
		prev(); return (*this); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns an unmoved *this */
	typename const_iterator operator--(int) {
		typename const_iterator _Tmp = *this;
		--*this;
		return (_Tmp); }

	//@cmember
	/* Returns true if the given iterator is equal to this one */
	bool operator==(typename const const_iterator& _X) const {
		return (m_pct == _X.m_pct && iseql(_X.m_psih)); }

	//@cmember
	/* Returns true if the given iterator is not equal to this one */
	bool operator!=(typename const const_iterator& _X) const {
		return (!(*this == _X)); }

	//@cmember
	/* This iterator is set equal to the given one */
    typename const_iterator& operator=( typename const const_iterator& iter) {  // Right side is the argument.
		const_attach(iter.m_pct);
		m_psih = m_pct->_const_iterator_create_from(iter.m_psih);
		return *this; }
};

/////////////////////////////
//
//@doc const_reverse_iterator
//
//@class const_reverse_iterator | The const_reverse_iterator
//  templated class is an STL-like iterator that can be
//  instantiated and attached to any collection that
//  implements the <c IConstTraversableT> templated interface.
//  Unlike STL's iterators, const_reverse_iterator is polymorphic,
//  meaning it can traverse a collection without explicit
//  knowledge of the collection's type. const_reverse_iterator is
//  a bidirectional type iterator that is interface
//  compatible with its STL counterpart.  Therefore, it
//  can be used with any STL algorithm which takes a
//  bidirectional iterator. Note, const_reverse_iterator does
//  not support random iteration.
//
//@tcarg class | _Ty | The type of element in the collection
//  the iterator is traversing.
//
// Member functions include:
//  <mf const_reverse_iterator::const_reverse_iterator>
//  <mf const_reverse_iterator::begin>
//  <mf const_reverse_iterator::end>
//  <mf const_reverse_iterator::at_begin>
//  <mf const_reverse_iterator::at_end>
//  <mf const_reverse_iterator::operator*>
//  <mf const_reverse_iterator::operator->>
//  <mf const_reverse_iterator::operator++ >
//  <mf const_reverse_iterator::operator++>
//  <mf const_reverse_iterator::operator-->
//  <mf const_reverse_iterator::operator-->
//  <mf const_reverse_iterator::operator==>
//  <mf const_reverse_iterator::operator!=>
//  <mf const_reverse_iterator::operator=>
//
template < class _Ty > class
const_reverse_iterator : public iterator_base<typename _Ty>
{
public:

	// Types
	typedef typename const value_type qualified_value_type;
	typedef typename IConstTraversableT<typename _Ty> traversable_type;
	typedef typename const traversable_type qualified_traversable_type;

protected:

	typename _sih* m_psih;
	typename qualified_traversable_type* m_pct;
 
	////////////////////////////////////////////////////////
	// Construction

	protected:

	void const_attach(typename qualified_traversable_type* pct) {
		m_pct = pct;
		m_pct->AddRef(); }

	void const_detach() {
		m_pct->Release();
		m_pct = NULL; }

	const_reverse_iterator(typename qualified_traversable_type* pct, typename _sih* psih) {
		const_attach(pct);
		m_psih = psih; }

	public:

	const_reverse_iterator()
		: m_pct(NULL), m_psih(NULL) {
		}

	//@cmember
	/* Constructs a const_reverse_iterator and attaches it to the specified traversable */
	/* of type <c IConstTraversableT>. Notice, you must call <const_reverse_iterator::begin> */
	/* or <const_reverse_iterator::end> before the iterator is usable. */
	const_reverse_iterator(typename qualified_traversable_type* pct) {
		const_attach(pct);
		m_psih = m_pct->_const_reverse_iterator_create();
		}

	//@cmember
	/* Copy constructor for const_iterator */
	const_reverse_iterator( typename const const_reverse_iterator<_Ty>& iter ) {
		const_attach(iter.m_pct);
		m_psih = m_pct->_const_reverse_iterator_create_from(iter.m_psih);
		}

	virtual ~const_reverse_iterator() {
		if (m_psih) {
			m_pct->_const_reverse_iterator_destroy(m_psih);
			m_psih = NULL;
			const_detach(); }}

	////////////////////////////////////////////////////////
	// Iterator Base Interface 

	//@cmember
	/* Move the iterator to the previous element in the collection */
	void prev() {
		m_pct->_const_reverse_iterator_prev(m_psih); }
   
	//@cmember
	/* Move the iterator to the next element in the collection */
	void next() {
		m_pct->_const_reverse_iterator_next(m_psih); }
   
	//@cmember
	/* Return a const reference to the element at the iterator's current position */
	typename const_reference getref() const {
		return m_pct->_const_reverse_iterator_get(m_psih); }

	//@cmember
	/* Return a const pointer to the element at the iterator's current position */
	typename const_pointer getptr() const {
		return (&**this); }

	//@cmember
	/* Positions the iterator at the start of the collection, which for a reverse 
	   is actually at the physical last element. */
	void begin() {
		m_pct->_const_reverse_iterator_begin(m_psih); }

	//@cmember
	/* Positions the iterator at the end of the collection.  Note, the end
	   is one passed the last element. */
	void end() {
		m_pct->_const_reverse_iterator_end(m_psih); }

	//@cmember
	/* Returns true if currently positioned at start of the collection */
	bool at_begin() const {
		return m_pct->_const_reverse_iterator_at_begin(m_psih); }

	//@cmember
	/* Returns true if currently positioned at end of collection */
	bool at_end() const {
		return m_pct->_const_reverse_iterator_at_end(m_psih); } 

	bool iseql(typename _sih* other) const {
		return (m_pct->_const_reverse_iterator_iseql(m_psih, other)); }
	
 
	///////////////////////////////////////////////////////
	// Operators

	//@cmember
	/* Returns a constant reference to the element at the current iterator position */
	const_reference operator*() const {
		return getref(); }

	//@cmember
	/* Returns a constant pointer to the element at the current iterator position */
	typename const_pointer operator->() const {
		return getptr(); }

	//@cmember
	/* The preincrement operator advances the iterator by one position and returns *this */
	typename const_reverse_iterator& operator++() {
		next(); return (*this); }

	//@cmember
	/* The postincrement operator advances the iterator by one position and returns an unmoved *this */
	typename const_reverse_iterator operator++(int){
		typename const_reverse_iterator _Tmp = *this;
		++*this;
		return (_Tmp); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns *this */
	typename const_reverse_iterator& operator--() {
		prev(); return (*this); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns an unmoved *this */
	typename const_reverse_iterator operator--(int) {
		typename const_reverse_iterator _Tmp = *this;
		--*this;
		return (_Tmp); }

	//@cmember
	/* Returns true if the given iterator is equal to this one */
	bool operator==(typename const const_reverse_iterator& _X) const {
		return (m_pct == _X.m_pct && iseql(_X.m_psih)); }

	//@cmember
	/* Returns true if the given iterator is not equal to this one */
	bool operator!=(typename const const_reverse_iterator& _X) const {
		return (!(*this == _X)); }

	//@cmember
	/* This iterator is set equal to the given one */
    typename const_reverse_iterator& operator=( typename const const_reverse_iterator& iter) {  // Right side is the argument.
		const_attach(iter.m_pct);
		m_psih = m_pct->_const_reverse_iterator_create_from(iter.m_psih);
		return *this; }

	inline void rbegin() {
		begin(); }

	inline void rend() {
		end(); }

	inline void at_rbegin() const {
		at_begin(); }

	inline void at_rend() const {
		at_end(); }
};



/////////////////////////////
//
//@doc iterator
//
//@class iterator | The iterator
//  templated class is an STL-like iterator that can be
//  instantiated and attached to any collection that
//  implements the <c ITraversableT> templated interface.
//  Unlike STL's iterators, this iterator class is polymorphic,
//  meaning it can traverse a collection without explicit
//  knowledge of the collection's type. The iterator class is
//  a bidirectional type iterator that is interface
//  compatible with its STL counterpart.  Therefore, it
//  can be used with any STL algorithm which takes a
//  bidirectional iterator. Note, this iterator does
//  not support random iteration.
//
//@tcarg class | _Ty | The type of element in the collection
//  the iterator is traversing.
//
// Member functions include:
//  <mf iterator::iterator>
//  <mf iterator::begin>
//  <mf iterator::end>
//  <mf iterator::at_begin>
//  <mf iterator::at_end>
//  <mf iterator::operator*>
//  <mf iterator::operator->>
//  <mf iterator::operator++ >
//  <mf iterator::operator++>
//  <mf iterator::operator-->
//  <mf iterator::operator-->
//  <mf iterator::operator==>
//  <mf iterator::operator!=>
//  <mf iterator::operator=>
//
//@base public | const_iterator
//
template < class _Ty > class
iterator : public const_iterator < typename _Ty >
{
public:

	// Types
	typedef typename value_type qualified_value_type;
	typedef typename ITraversableT<typename _Ty> traversable_type;
	typedef typename traversable_type qualified_traversable_type;

protected:

	typename qualified_traversable_type* m_pt;

	////////////////////////////////////////////////////////
	// Construction

	protected:

	void attach(typename qualified_traversable_type* pt) {
		m_pt = pt;
		m_pt->AddRef(); }

	void detach() {
		m_pt->Release();
		m_pt = NULL; }

	public:

	iterator()
		: const_iterator<typename _Ty>(), m_pt(NULL) {
		}

	//@cmember
	/* Constructs an iterator and attaches it to the specified traversable */
	/* of type <c ITraversableT>. Notice, you must call <iterator::begin> */
	/* or <iterator::end> before the iterator is usable. */
	iterator(typename qualified_traversable_type* pt)
		: const_iterator<typename _Ty>(pt, pt->_iterator_create()) {
		attach(pt);
		}

	//@cmember
	/* Copy constructor for const_iterator */
	iterator(typename const iterator<_Ty>& iter )
		: const_iterator<typename _Ty>(iter.m_pt, iter.m_pt->_iterator_create_from(iter.m_psih)) {
		attach(iter.m_pt);
		}

	virtual ~iterator() {
		if (m_psih) {
			m_pt->_iterator_destroy(m_psih);
			m_psih = NULL; // so base class doesn't attempt to destroy too
			detach(); }}

	////////////////////////////////////////////////////////
	// Iterator Base Interface 

	//@cmember
	/* Move the iterator to the previous element in the collection */
	void prev() {
		m_pt->_iterator_prev(m_psih); }
   
	//@cmember
	/* Move the iterator to the next element in the collection */
	void next() {
		m_pt->_iterator_next(m_psih); }
   
	//@cmember
	/* Return a const reference to the element at the iterator's current position */
	typename const_reference getref() const {
		return m_pt->_iterator_get(m_psih); }

	//@cmember
	/* Return a const pointer to the element at the iterator's current position */
	typename const_pointer getptr() const {
		return (&**this); }

	//@cmember
	/* Positions the iterator at the start of the collection */
	void begin() {
		m_pt->_iterator_begin(m_psih); }

	//@cmember
	/* Positions the iterator at the end of the collection.  Note, the end
	   is one position passed the last element. */
	void end() {
		m_pt->_iterator_end(m_psih); }

	//@cmember
	/* Returns true if currently positioned at start of collection */
	bool at_begin() const {
		return m_pt->_iterator_at_begin(m_psih); }

	//@cmember
	/* Returns true if currently positioned at end of collection */
	bool at_end() const {
		return m_pt->_iterator_at_end(m_psih); } 

	bool iseql(_sih* other) const {
		return (m_pt->_iterator_iseql(m_psih, other)); }

	///////////////////////////////////////////////////////
	// Non-Const Operators
    
	//@cmember
	/* Returns a reference to the element at the current iterator position */
	typename reference operator*() const {
		return m_pt->_iterator_wget(m_psih); }

	//@cmember
	/* Returns a pointer to the element at the current iterator position */
	typename pointer operator->() const {
		return (&**this); }

	//@cmember
	/* The preincrement operator advances the iterator by one position and returns *this */
	typename iterator& operator++() {
		next();
		return (*this); }

	//@cmember
	/* The postincrement operator advances the iterator by one position and returns an unmoved *this */
	typename iterator operator++(int) {
		iterator _Tmp = *this;
		++*this;
		return (_Tmp); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns *this */
	typename iterator& operator--() {
		prev();
		return (*this); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns an unmoved *this */
	typename iterator operator--(int) {
		iterator _Tmp = *this;
		--*this;
		return (_Tmp); }

	//@cmember
	/* This iterator is set equal to the given one */
    typename iterator& operator=( typename const iterator& iter) {  // Right side is the argument.
		const_attach(iter.m_pct);
		attach(iter.m_pt);
		m_psih = m_pt->_iterator_create_from(iter.m_psih);
		return *this; }

	///////////////////////////////////////////////////////
	// Writing Members
    
	//@cmember
	/* Erases the element at the current iterator position */
	void erase() {
		m_pt->_iterator_erase(m_psih); }

	//@cmember
	/* Insert the given element at the current iterator position */
	void insert(typename const _Ty& _X) {
		m_pt->_iterator_insert(m_psih, _X); }
};

/////////////////////////////
//
//@doc reverse_iterator
//
//@class reverse_iterator | The reverse_iterator
//  templated class is an STL-like iterator that can be
//  instantiated and attached to any collection that
//  implements the <c ITraversableT> templated interface.
//  Unlike STL's iterators, reverse_iterator is polymorphic,
//  meaning it can traverse a collection without explicit
//  knowledge of the collection's type. reverse_iterator is
//  a bidirectional type iterator that is interface
//  compatible with its STL counterpart.  Therefore, it
//  can be used with any STL algorithm which takes a
//  bidirectional iterator. Note, reverse_iterator does
//  not support random iteration.
//
//@tcarg class | _Ty | The type of element in the collection
//  the iterator is traversing.
//
// Member functions include:
//  <mf reverse_iterator::reverse_iterator>
//  <mf reverse_iterator::begin>
//  <mf reverse_iterator::end>
//  <mf reverse_iterator::at_begin>
//  <mf reverse_iterator::at_end>
//  <mf reverse_iterator::operator*>
//  <mf reverse_iterator::operator->>
//  <mf reverse_iterator::operator++ >
//  <mf reverse_iterator::operator++>
//  <mf reverse_iterator::operator-->
//  <mf reverse_iterator::operator-->
//  <mf reverse_iterator::operator==>
//  <mf reverse_iterator::operator!=>
//  <mf reverse_iterator::operator=>
//
//@base public | const_reverse_iterator
//
template < class _Ty > class
reverse_iterator : public const_reverse_iterator < typename _Ty >
{
public:

	// Types
	typedef typename value_type qualified_value_type;
	typedef typename ITraversableT<typename _Ty> traversable_type;
	typedef typename traversable_type qualified_traversable_type;

protected:

	typename qualified_traversable_type * m_pt;

	////////////////////////////////////////////////////////
	// Construction

	protected:

	void attach(typename ITraversableT<typename _Ty>* pt) {
		m_pt = pt;
		m_pt->AddRef(); }

	void detach() {
		m_pt->Release();
		m_pt = NULL; }

	public:

	reverse_iterator()
		: const_reverse_iterator<typename _Ty>(), m_pt(NULL) {
		}

	//@cmember
	/* Constructs a reverse_iterator and attaches it to the specified traversable */
	/* of type <c ITraversableT>. Notice, you must call <reverse_iterator::begin> */
	/* or <reverse_iterator::end> before the iterator is usable. */
	reverse_iterator(typename qualified_traversable_type* pt)
		: const_reverse_iterator<typename _Ty>(pt, pt->_reverse_iterator_create()) {
		attach(pt);
		}

	//@cmember
	/* Copy constructor for const_iterator */
	reverse_iterator(typename const reverse_iterator<typename _Ty>& iter )
		: const_reverse_iterator<typename _Ty>(iter.m_pt, iter.m_pt->_reverse_iterator_create_from(iter.m_psih)) {
		attach(iter.m_pt);
		}

	virtual ~reverse_iterator() {
		if (m_psih) {
			m_pt->_reverse_iterator_destroy(m_psih);
			m_psih = NULL; // so base class doesn't attempt to destroy too
			detach(); }}

	////////////////////////////////////////////////////////
	// Iterator Base Interface 

	//@cmember
	/* Move the iterator to the previous element in the collection */
	void prev() {
		m_pt->_reverse_iterator_prev(m_psih); }
   
	//@cmember
	/* Move the iterator to the next element in the collection */
	void next() {
		m_pt->_reverse_iterator_next(m_psih); }
   
	//@cmember
	/* Return a const reference to the element at the iterator's current position */
	typename const_reference getref() const {
		return m_pt->_reverse_iterator_get(m_psih); }

	//@cmember
	/* Return a const pointer to the element at the iterator's current position */
	typename const_pointer getptr() const {
		return (&**this); }

	//@cmember
	/* Positions the iterator at the start of the collection, which for a reverse 
	   is actually at the physical last element. */
	void begin() {
		m_pt->_reverse_iterator_begin(m_psih); }

	//@cmember
	/* Positions the iterator at the end of the collection.  Note, the end
	   is one passed the last element. */
	void end() {
		m_pt->_reverse_iterator_end(m_psih); }

	//@cmember
	/* Returns true if currently positioned at start of the collection */
	bool at_begin() const {
		return m_pt->_reverse_iterator_at_begin(m_psih); }

	//@cmember
	/* Returns true if currently positioned at end of collection */
	bool at_end() const {
		return m_pt->_reverse_iterator_at_end(m_psih); } 

	bool iseql(typename _sih* other) const {
		return (m_pt->_reverse_iterator_iseql(m_psih, other)); }

	///////////////////////////////////////////////////////
	// Non-Const Operators
    
	//@cmember
	/* Returns a reference to the element at the current iterator position */
	typename reference operator*() const {
		return m_pt->_reverse_iterator_wget(m_psih); }

	//@cmember
	/* Returns a pointer to the element at the current iterator position */
	typename pointer operator->() const {
		return (&**this); }

	//@cmember
	/* The preincrement operator advances the iterator by one position and returns *this */
	typename reverse_iterator& operator++() {
		next();
		return (*this); }

	//@cmember
	/* The postincrement operator advances the iterator by one position and returns an unmoved *this */
	typename reverse_iterator operator++(int) {
		typename reverse_iterator _Tmp = *this;
		++*this;
		return (_Tmp); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns *this */
	typename reverse_iterator& operator--() {
		prev();
		return (*this); }

	//@cmember
	/* The predecrement operator retreats the iterator by one position and returns an unmoved *this */
	typename reverse_iterator operator--(int) {
		typename reverse_iterator _Tmp = *this;
		--*this;
		return (_Tmp); }

	//@cmember
	/* This iterator is set equal to the given one */
    typename reverse_iterator& operator=( typename const reverse_iterator& iter) {  // Right side is the argument.
		const_attach(iter.m_pct);
		attach(iter.m_pt);
		m_psih = m_pt->_reverse_iterator_create_from(iter.m_psih);
		return *this; }
};


template<class _Ty>
struct iteration_filter {
	virtual bool operator()(typename _Ty& _X) const = 0;
	};

/////////////////////////////
//
//@doc filtered_iterator
//
//@class filtered_iterator | The filtered_iterator
//  templated class is an iterator that skips
//  elements that don't match your selection criteria.
//  The template parameter to the filtered_iterator
//  is the iterator to filter.  The filtered_iterator
//  derives from the iterator type passed in,
//  and overrides the <mf const_iterator::next> and
//  <mf const_iterator::prev> members to skip
//  non-matching elements.  Note, you can even
//  have multiple levels of filtering by wrapping a
//  filtered_iterator by another filtered_iterator.
//
//  To use the filtered_iterator, you must specify
//  a selection criteria.  There are two methods you
//  can choose from.  First, you can override the
//  virtual select function, <c filtered_iterator::select>, 
//  and test the current element when called upon.  If
//  the element matches, the select function should
//  return true.  Otherwise, return false and the
//  element will be skipped during iteration.
//
//  The second method is two declare a filter object
//  and pass it into the constructor. To declare a
//  filter object, derive a a class from the nested type
//  <c filtered_iterator::filter_type>.  filter_type
//  is a base class for a functor that implements
//  operator(), and receives the current element as
//  a parameter.  The operator is expected to return
//  true if the element is selected, or false if it
//  should be skipped. To use the filtered_iterator,
//  define a filter object and pass it into the
//  filtered_iterator constructor.
//
//  Note, a filtered_iterator can also serve to
//  implement a find feature.  This method is
//  preferable over a function because multiple
//  finds are more easily dealt with.
//
//@tcarg class | _It | The type of iterator to wrap
//  and filter.
//
// Member functions include:
//  <mf filtered_iterator::filtered_iterator>
//
template < class _It >
class filtered_iterator : public _It
{
public:
	//@type filtered_iterator::filter_type | The base type for a functor which
	//  tests a given node for whether it matches a selection criteria.  If
	//  it matches, the functor returns true and the node is included in
	//  iteration.  If not, the functor returns false and the node is skipped.
	typedef typename iteration_filter< typename _It::const_value_type > filter_type;

protected:

	typename const filter_type & m_ft;

	//@cmember
	/* Returns true of the current element matches the selection criteria. */
	virtual bool select() const
		{ return m_ft( operator*() ); }

public:
	
	//@cmember
	/* Construct a filtered_iterator that attaches to the specified
	   traversable, and applies the specified filter. */
	filtered_iterator( typename _It::qualified_traversable_type * pt,
		typename const filter_type& ft )
		: _It(pt), m_ft(ft) { }

	filtered_iterator( typename const _It& iter,
		typename const filter_type& ft )
		: _It(iter), m_ft(ft) { }

	void prev() {
		do {
			 _It::prev();
		} while ( !select() && !_It::at_begin() ); }
   
	void next() {
		do {
			_It::next();
		} while ( !_It::at_end() && !select() ); }

	void begin() {
		_It::begin();
		if (!_It::at_end() && !select())
			next(); }

	void end() {
		_It::end();
		if (!_It::at_begin() && !select())
			prev(); }
};

template<class _Ty, class _Tv>
struct children_accessor {
	virtual typename _Tv* operator()(typename _Ty& _i) const = 0;
};

template<class _Ty, class _Tv>
struct _default_children_accessor : public children_accessor< typename _Ty, typename _Tv > {
	virtual typename _Tv* operator()(typename _Ty& _i) const {
		return _i.GetChildren();
	}
};

/////////////////////////////
//
//@doc hierarchy_iterator
//
//@class hierarchy_iterator | The hierarchy_iterator
//  templated class is an iterator that traverses a
//  hierarchy in depth first order.  When traversing
//  a hierarchy, the iterator visits the parent first,
//  then the first child, second child etc.  When the
//  last child is reached, the parent's next sibling
//  is visited.  In effect, the hierarchy is visited in
//  the same order that nodes in a tree control are shown
//  reading from top to bottom.  This permits every
//  node in a hierarchy to be visited with one simple
//  for loop
//
//  The hierarchy_iterator class defines a query,
//  <mf hierarchy_iterator::depth> which tells you
//  the iterator's current depth within the hierarchy.
//  Aside from this additional member, the
//  hierarchy_iterator is the same as the iterator
//  you pass in as its template parameter.
//
//  To use the hierarchy_iterator, you must first tell
//  it how to access the children of a given node. 
//  There are three ways to do so.  First, you can
//  simply add a GetChildren method to the node type.
//  By default, the hierarchy iterator will assume
//  this member exists and call it to access children.
//  The GetChildren method should return a traversable
//  to its children or NULL if it has no children.
//
//  Second, you can derive a specialized hierarchy_iterator
//  and override its <mf hierarchy_iterator::get_children>
//  virtual function.  This function is expected to
//  test the current node when called upon.  If it has
//  children, a traversable interface must be returned
//  which permits access to those child.  If not, a
//  NULL traversable indicates no children.
//
//  The second method is two declare an accessor object
//  and pass it into the constructor. To declare a
//  accessor object, derive a a class from the nested type
//  <c hierarchy_iterator::accessor_type>.  accessor_type
//  is a base class for a functor that implements
//  operator(), and receives the current element as
//  a parameter.  The operator is expected to return
//  a traversable interface if the element has children
//  or NULL if it doesn't. To use the hierarchy_iterator,
//  define an accessor object and pass it into the
//  hierarchy_iterator constructor.
//
//@tcarg class | _It | The type of iterator to wrap
//  and traverse hierarchically.
//
// Member functions include:
//  <mf hierarhcy_iterator::hierarchy_iterator>
//  <mf hierarhcy_iterator::depth>
//
template < class _It >
class hierarchy_iterator : public _It
{
public:
	//@type hierarchy_iterator::accessor_type | The base type for a functor which
	//  accesses the children of a given node
	typedef typename children_accessor< typename _It::qualified_value_type, typename _It::qualified_traversable_type > accessor_type;
	typedef typename _default_children_accessor< typename _It::qualified_value_type, typename _It::qualified_traversable_type > default_accessor;
	typedef typename hierarchy_iterator< typename _It > self_type;

protected:

	typename const accessor_type & m_ca;
	std::stack<typename _It> m_stack;

	////////////////////////////////////////////////////////
	// Utility functions

	void push(typename const _It& iChildren) {
		m_stack.push( *this );
		_It::operator=(iChildren); }

	void pop() {
		_It::operator=(m_stack.top());
		m_stack.pop(); }

	virtual typename _It::qualified_traversable_type* get_children() const {
		return m_ca( operator*() ); }

public:

	////////////////////////////////////////////////////////
	// Construction

	//@cmember
	/* Constructs a hierarchy iterator, attaching to the specified
	   traversable */
	hierarchy_iterator( typename _It::qualified_traversable_type * pt,
		typename const accessor_type & ca = default_accessor())
		: _It(pt), m_ca(ca) { }

	hierarchy_iterator( typename const _It& iter,
		typename const accessor_type & ca = default_accessor())
		: _It(iter), m_ca(ca) { }

	hierarchy_iterator( typename const self_type & iter) {
		m_ca = iter.m_ca;
		m_stack = iter.m_stack; }

	////////////////////////////////////////////////////////
	// Iterator Base Interface 

	void prev() {
		if (_It::at_begin()) {
			if (m_stack.size())
				pop(); }
		else {
			_It::prev();
			typename _It::qualified_traversable_type* pChildren;
			pChildren = get_children();
			while ( pChildren ) {
				push( _It(pChildren) );
				_It::end();
				_It::prev();
				pChildren = get_children(); } } }
			  
	void next() {
		typename _It::qualified_traversable_type* pChildren = get_children();
		if (pChildren) {
			push( _It(pChildren) );
			_It::begin(); }
		else {
			_It::next();
			if (_It::at_end() && m_stack.size()) {
				pop();
				_It::next(); } } }

	void begin() {
		while (m_stack.size() > 0) pop();
		_It::begin(); }

	void end() {
		while (m_stack.size() > 0) pop();
		_It::end(); }

	bool at_begin() const {
		return (m_stack.size() == 0) && _It::at_begin(); }

	bool at_end() const {
		return (m_stack.size() == 0) && _It::at_end(); }

	////////////////////////////////////////////////////////
	// Queries

	//@cmember
	/* Returns the iterator's current depth within the hierarchy */
	SEC_INT depth() const {
		return m_stack.size(); }
};

};};
