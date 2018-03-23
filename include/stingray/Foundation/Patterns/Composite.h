///////////////////////////////////////////////////////////////////////////////
// Composite.h : SFL Composite design pattern
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
// Description:  SFL Composite design pattern templated implementation
//


#pragma once


#if !defined(_SFL)
#define _SFL
#endif

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4876)
	#pragma warning(disable:4284) // STL, not a UDT or reference to a UDT. Errors if infix notation used.
#endif

#include <foundation\stwarn.h>
#include <list>
#include <algorithm>
#include <foundation\stwarnp.h>
#include <foundation\GuidCast.h>
#include <foundation\Patterns\Iterator.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc 

//@class CComposite |
/*
	Implements the composite design pattern
*/
//@tcarg typename | _Component | Type of the elements in the composite structure
//@tcarg GUID | guid | GUID that identifies the Composite interface among all the interfaces implemented by an element
template <typename _Component, const GUID* _guid>
class  CComposite : public IQueryGuid
{
	typedef typename CComposite<typename _Component, _guid> _thisClass;
	typedef typename std::list<typename _Component* > Children;

	class CompIterator : public foundation::Iterator<typename Children>
	{
	public:
		friend class CComposite<typename _Component, _guid>;
		explicit CompIterator(Children& acoll) : foundation::Iterator<Children>(acoll) {}
	};


public:

	typedef typename foundation::IteratorBase<typename _Component*> Iterator;

	// Composite design pattern operations

	//@cmember
	// Returns the number of nodes directly contained in this node
	SEC_INT GetChildrenCount () const;
	//@cmember
	// Returns the total number of nodes contained by this node and its children
	SEC_INT GetAllDescendantsCount () const;


	//@cmember
	// Returns this node's parent
	typename _Component* GetParent() const;
	//@cmember
	// Sets the parent node
	void SetParent(typename _Component* pComp);
	//@cmember
	// Returns the root of the composite tree
	typename _Component* GetRoot();

	//@cmember
	// Adds a node as a child of this node
	SEC_INT AddChild(typename _Component* pComp);
	//@cmember
	// Removes a child node
	SEC_INT RemoveChild(typename _Component* pComp);

	//@cmember
	// Returns an iterator of this node's children
	typename Iterator* GetChildIterator();

protected:

	CComposite(): m_pParent(NULL) {}
	virtual ~CComposite() {}

protected:
	// Composite design pattern implementation
	typename Children m_Children;
	typename _Component* m_pParent;

};



//@mfunc SEC_INT | CComposite<lt<gt | GetChildrenCount | 
// Returns the number of nodes directly contained in this node
//@rdesc Count of child nodes
template <typename _Component, const GUID* _guid>
SEC_INT CComposite<_Component, _guid>::GetChildrenCount() const
{
	SEC_INT nCount = 0;
	nCount = (SEC_INT)m_Children.size();
	return nCount;
}


//@mfunc SEC_INT | CComposite<lt<gt | GetAllDescendantsCount | 
// Returns the total number of nodes contained by this node and its children
//@rdesc Count of child nodes
//@comm GetAllDescendantsCount recursively counts the number of nodes in this
// node and its children.
template <typename _Component, const GUID* _guid> 
SEC_INT CComposite<_Component, _guid>::GetAllDescendantsCount() const
{
	SEC_INT nCount = GetChildrenCount();
	typename Children::const_iterator i;
	for (i = m_Children.begin(); i != m_Children.end(); ++i) {
#if _MSC_VER > 1100
		const _thisClass* pComposite = guid_cast<const _thisClass*, _guid>(*i);
		nCount += pComposite->GetAllDescendantsCount();
#else
		const _thisClass* pComposite;
		if ((*i)->QueryGuid(*_guid, (void**) &pComposite))
		{
			nCount += pComposite->GetAllDescendantsCount();
		}
#endif
	}
	return nCount;
}


//@mfunc _Component* | CComposite<lt<gt | GetParent | 
// Returns this node's parent node
//@rdesc Pointer to parent node
template <typename _Component, const GUID* _guid>
typename _Component* CComposite<_Component, _guid>::GetParent() const
{ 
	return m_pParent; 
}


//@mfunc void | CComposite<lt<gt | SetParent | 
// Sets this node as child of the given node
//@parm _Component* | pComp | Parent node
template <typename _Component, const GUID* _guid>
void CComposite<_Component, _guid>::SetParent(typename _Component* pComp)
{ 
	m_pParent = pComp; 
}


//@mfunc _Component* | CComposite<lt<gt | GetRoot | 
// Returns the root of tree-like structure the composite defines
//@rdesc Root node of the composite
template <typename _Component, const GUID* _guid>
_Component* 
CComposite<_Component, _guid>::GetRoot (
) 
{
	typename _thisClass* pRoot = this;
	typename _Component* pParent = 0;
	do {
		pParent = pRoot->GetParent();
		if (pParent) {
#if _MSC_VER > 1100
			pRoot = guid_cast<_thisClass*, _guid>(pParent);
#else
			pParent->QueryGuid(*_guid, (void**) &pRoot);
#endif
		}
	} while (pParent);

	return guid_cast<_Component*>(pRoot);
}


//@mfunc SEC_INT | CComposite<lt<gt | AddChild | 
// Adds the given node to this node's list of children 
//@rdesc The number of children this node contains after inserting the new one
//@parm _Component* | pComp | New child node
template <typename _Component, const GUID* _guid>
SEC_INT CComposite<_Component, _guid>::AddChild( _Component* pComp ) 
{
	//const UUID& uuid = __uuidof(CComposite);
#if _MSC_VER > 1100
	_thisClass* pNode = guid_cast<_thisClass*, _guid>(pComp);
	_thisClass* pParent = guid_cast<_thisClass*, _guid>(pNode->GetParent());
#else
	_thisClass* pNode;
	_thisClass* pParent;
	pComp->QueryGuid(*_guid, (void**)&pNode);
	pNode->GetParent()->QueryGuid(*_guid, (void**)&pParent);
#endif
	if (pParent) {
		if (pParent == this) {
			return GetChildrenCount();	// already a child!
		}
		else {
			pParent->RemoveChild(pComp);
		}
	}

	// Add the child node
	try {
		m_Children.push_back(pComp);
		pNode->SetParent(guid_cast<_Component*>(this));
	}
	catch (std::exception& ) {
		return -1;
	}

	return GetChildrenCount();
}


//@mfunc SEC_INT | CComposite<lt<gt | RemoveChild | 
// Removes the given node from this node's list of children 
//@rdesc The number of children this node contains after removing the one requested
//@parm _Component* | pComp | Node to remove
template <typename _Component, const GUID* _guid>
SEC_INT CComposite<_Component, _guid>::RemoveChild( _Component* pComp )
{
	if (!pComp) {
		return -1;
	}

#if _MSC_VER > 1100
	_thisClass* pNode = guid_cast<_thisClass*, _guid>(pComp);
#else
	_thisClass* pNode;
	pComp->QueryGuid(*_guid, (void**)&pNode);
#endif

	// Remove the child
	try {
		typename Children::iterator pos = std::find(m_Children.begin(), m_Children.end(), pComp);
		if (pos != m_Children.end()) {
			m_Children.erase(pos);
			pNode->SetParent(NULL);
		}
	}
	catch (std::exception& ) {
		return -1;
	}

	return GetChildrenCount();
}


//@mfunc Iterator* | CComposite<lt<gt | GetChildIterator | 
// Returns an iterator that allows traversing this node's collection of child nodes
//@rdesc Iterator for collection of children
template <typename _Component, const GUID* _guid>
typename CComposite<_Component, _guid>::Iterator*
CComposite<_Component, _guid>::GetChildIterator()
{
	return new CompIterator(m_Children);
}



};	// namespace stingray::foundation
};	// namespace stingray

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning (pop)
	#endif
#endif
