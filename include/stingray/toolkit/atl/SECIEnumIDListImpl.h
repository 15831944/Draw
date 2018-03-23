///////////////////////////////////////////////////////////////////////////////
// SECIEnumIDListImpl.h
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

#if !defined(AFX_SECIENUMIDLISTIMPL_H__8CF98155_7E75_4C09_AB71_5CC517A3A10A__INCLUDED_)
#define AFX_SECIENUMIDLISTIMPL_H__8CF98155_7E75_4C09_AB71_5CC517A3A10A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <foundation\stwarn.h>
#include <list>
#include <foundation\stwarnp.h>
using namespace std;

/////////////////////////////
// AutoDuck tag block block for SECIEnumIDListImpl 

//@doc SECIEnumIDListImpl
//@mdata TPidlMgr*       | SECIEnumIDListImpl | m_pPidlMgr | data member comment

//@doc SECIEnumIDListImpl
//@mdata list lt; LPITEMIDLIST gt;     | SECIEnumIDListImpl | m_idlList | data member comment

//@doc SECIEnumIDListImpl
//@mdata list lt; LPITEMIDLIST gt;::iterator  | SECIEnumIDListImpl | m_iterCurrent | data member comment

//@doc SECIEnumIDListImpl
//@mfunc BOOL | SECIEnumIDListImpl | CreateEnumIDList | Call this function to create the enumerate PIDL list. It is called
//inside the IShellFolder::EnumObjects method implementation.
//@rdesc BOOL If successful, return TRUE, otherwise return FALSE
//@parm LPCITEMIDLIST | pidl | The top PIDL of this folder
//@parm DWORD | dwFlags | Flag passed in the IShellFolder::EnumObjects method.
//@xref <c SECIEnumIDListImpl>

//@doc SECIEnumIDListImpl
//@mfunc void | SECIEnumIDListImpl | DeleteList | Delete all the PIDLs in the list.
//@rdesc void
//@xref <c SECIEnumIDListImpl>

//@doc SECIEnumIDListImpl
//@mfunc void | SECIEnumIDListImpl | AddToEnumList | Add a new pidl to the internal list of PIDL.
//@rdesc void
//@parm LPITEMIDLIST | pidl | The pidl to be added to the internal list of pidl
//@xref <c SECIEnumIDListImpl>

// adinsert AutoDuck insertion point for SECIEnumIDListImpl 
//@doc SECIEnumIDListImpl 
//@class SECIEnumIDListImpl 
//@comm This class is a wrapper of IEnumIDList interface. It also implemented
//the IUnknown interface and the reference counting logic. User of the
//class only need to override CreateEnumIDList function to create the
//PIDL list for a given PIDL. The template argument should be an PIDL
//management class derived from SECPidlMgr lt; T gt; template class. This 
//implementation is majorly targeted for namespace or shell extension. 
//To use this class, user should use AddToEnumList method to add a PIDL
//to the internal PIDL list. After a PIDL is added to the list, 
//this class becomes the owner of the PIDL. To clean the internal PIDL
//list, application should use DeleteList method. It will free all the
//memory used by the PIDLs in the list and then clear the list and reset
//the current iterator. <nl>
//<nl>
//In your overriding function CreateEnumIDList, you must initialize the
//m_iterCurrent to the begining of the enum ID list after you add element
//to the enum ID list, otherwise you will get an runtime error. <nl>
//<nl>
//For a complete documentation of IEnumIDList, please refer to windows SDK or MSDN from Microsoft.
//@tcarg class | TPidlMgr | A SECPidlMgr derived class
//@base public | IEnumIDList
template<typename TPidlMgr>
class SECIEnumIDListImpl : public IEnumIDList
{
protected:
	DWORD							m_nRefCount;

	//@cmember
	/* A pointer to PIDL manager */
	TPidlMgr*						m_pPidlMgr;
	//@cmember
	/* A list of PIDL */
	list<LPITEMIDLIST>				m_idlList;
	//@cmember
	/* A pointer to the current PIDL */
	list<LPITEMIDLIST>::iterator	m_iterCurrent;

public:
	inline SECIEnumIDListImpl() 
	{
		m_pPidlMgr = new TPidlMgr;
		if( m_pPidlMgr == NULL )
		{
			delete this;
			return;
		}
		m_nRefCount = 1;

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt++;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt++;
		_pAtlModule->Unlock();
#endif

		m_iterCurrent = m_idlList.begin();
	}
	virtual ~SECIEnumIDListImpl()
	{
		DeleteList();

		if( m_pPidlMgr != NULL )
			delete m_pPidlMgr;

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt--;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt--;
		_pAtlModule->Unlock();
#endif
	}

	//@cmember
	/* Override this function to create PIDL list */
	virtual BOOL CreateEnumIDList(LPCITEMIDLIST /*pidl*/, DWORD /*dwFlags*/)
	{
		return TRUE;
	}

public:
	//@cmember
	/* Delete the PIDL in the list */
	inline void DeleteList()
	{
		for(list<LPITEMIDLIST>::iterator it = m_idlList.begin(); it != m_idlList.end(); it++)
		{
			m_pPidlMgr->Delete(*it);
		}
		m_idlList.clear();
		m_iterCurrent = m_idlList.begin();
	}

	//@cmember
	/* Add a new PIDL to the PIDL list */
	inline void AddToEnumList(LPITEMIDLIST pidl)
	{
		if( pidl != NULL )
		{
			// Make sure this item is not already on the list
			for(list<LPITEMIDLIST>::iterator it = m_idlList.begin(); it != m_idlList.end(); it++)
			{
				if( *it == pidl ) // Already on the list;
					break;
			}
			m_idlList.push_back(pidl);
		}
	}

public:
	inline STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
	{
		*ppvObj = NULL;

		//IUnknown
		if(IsEqualIID(riid, IID_IUnknown))
			*ppvObj = this;
		//IEnumIDList
		else if(IsEqualIID(riid, IID_IEnumIDList))
			*ppvObj = (IEnumIDList*)this;

		if(*ppvObj)
		{
		   (*(LPUNKNOWN*)ppvObj)->AddRef();
		   return S_OK;
		}
		return E_NOINTERFACE;
	}
	inline STDMETHOD_ (DWORD, AddRef)()
	{
	   m_nRefCount++;
	   return m_nRefCount;
	}
	inline STDMETHOD_ (DWORD, Release)()
	{
	   m_nRefCount--;
	   if( 0 == m_nRefCount )
	   {
		   delete this;
		   return 0;
	   }
	   return m_nRefCount;
	}

	//IEnumIDList
	inline STDMETHOD (Next) (ULONG dwElements, LPITEMIDLIST* apidl, ULONG* pdwFetched)
	{
		if( dwElements > 1 && pdwFetched == NULL )
			return E_INVALIDARG;
		DWORD dwIndex;
		for(dwIndex = 0; dwIndex < dwElements; dwIndex++)
		{
			if( m_iterCurrent == m_idlList.end() )
				return S_FALSE;
			apidl[dwIndex] = m_pPidlMgr->Copy(*m_iterCurrent);
			m_iterCurrent++;
		}
		if( pdwFetched != NULL )
			*pdwFetched = dwIndex;
		return S_OK;
	}
	inline STDMETHOD (Skip) (ULONG dwSkips)
	{
		for(DWORD dwIndex = 0; dwIndex < dwSkips; dwIndex++)
		{
			if( m_iterCurrent == m_idlList.end() )
				return S_FALSE;
			m_iterCurrent++;
		}
		return S_OK;
	}
	inline STDMETHOD (Reset) ()
	{
		m_iterCurrent = m_idlList.begin();
		return S_OK;
	}
	inline STDMETHOD (Clone) (LPENUMIDLIST* /*ppEnum*/)
	{
		return E_NOTIMPL;
	}
};

#endif // !defined(AFX_SECIENUMIDLISTIMPL_H__8CF98155_7E75_4C09_AB71_5CC517A3A10A__INCLUDED_)
