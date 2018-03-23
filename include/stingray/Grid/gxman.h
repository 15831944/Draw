///////////////////////////////////////////////////////////////////////////////
// gxman.h
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

// Author: Daniel Jebaraj
//

#ifndef _GX_MAN_H__
#define _GX_MAN_H__

#if _MFC_VER >= 0x0400 

#include <afxtempl.h>
#include <unknwn.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif


// helper class for managing captive objects
template <class T>
class CGXCaptiveManager
{
	inline class __captive : public T
	{
		friend class CGXCaptiveManager;
	 public:
		 __captive()
		 {};
		 virtual ~__captive()
		 {};

	};


public:
	CGXCaptiveManager();
	virtual ~CGXCaptiveManager();

	T* CreateObject();
	void RecycleObject(T* pObject);
	
	inline CList<T*, T*&>* GetList()
	{return &m_pLstT;};



//implementation
protected:
	CList<T*, T*&> m_pLstT;
	
// clean up
	void CleanObjects();
};


template <class T>
CGXCaptiveManager<T>::CGXCaptiveManager()
{
 //
}

template <class T>
CGXCaptiveManager<T>::~CGXCaptiveManager()
{
	CleanObjects();
}

template <class T>
T* CGXCaptiveManager<T>::CreateObject()
{
	if(GetList()->IsEmpty())
	{
		T* p = new __captive();
		return p;
	}
	else
		return GetList()->RemoveTail();
}
	
template <class T>
void CGXCaptiveManager<T>::RecycleObject(T* pObject)
{
	// check to see if the element is already in the list
	ASSERT(GetList()->Find(pObject) == NULL);	

	GetList()->AddTail(pObject);
}
	
// clean up
template <class T>
void CGXCaptiveManager<T>::CleanObjects()
{
	// iterate through the list and call delete
	CList<T*, T*&>* pList = GetList();

	TRACE1("The number of objects in CGXCaptiveManager is: %i\n", pList->GetCount());

	ASSERT(pList!=NULL);

	POSITION pos = pList->GetHeadPosition();
	
	__captive* pObject = NULL;

	while (pos != NULL)
	{	
		pObject = (__captive*)pList->GetNext(pos);
	
		if(pObject != NULL)
			delete pObject;
	}	

	pList->RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CGXNodeManager
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple creation and garbage collection support
// uses CRuntimeClass

template <class T>
class CGXNodeManager
{
	
	class __t : public T
	{
		friend class CGXNodeManager;
	 public:
		 inline __t(SEC_DWORD index)
		 {m_dwIndexUsed = index; };
		 
		 inline virtual ~__t()
		 {};

	 protected:
		 SEC_DWORD m_dwIndexUsed;
	};


public:
	CGXNodeManager(CRuntimeClass* pRuntimeClass);
	virtual ~CGXNodeManager();

	virtual T* CreateObject(SEC_DWORD dw);
	void RemoveObject(SEC_DWORD dw);
	
	inline CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* GetMap()
	{return &m_pMpT;};

//implementation
protected:
	CMap<SEC_DWORD, SEC_DWORD&, T*, T*&> m_pMpT;
	
// clean up
	void CleanObjects();
	CRuntimeClass* m_pRuntimeClass;
};


template <class T>
CGXNodeManager<T>::CGXNodeManager(CRuntimeClass* pRuntimeClass)
{
	m_pRuntimeClass = pRuntimeClass;
}

template <class T>
CGXNodeManager<T>::~CGXNodeManager()
{
	CleanObjects();
}

template <class T>
T* CGXNodeManager<T>::CreateObject(SEC_DWORD dw)
{
	T* pObject = NULL;
	if(GetMap()->Lookup(dw, pObject) == FALSE )
	{
		//T* p = new __t(dw);
		T* p = (T*) m_pRuntimeClass->CreateObject();

		ASSERT(p != NULL);
		
		GetMap()->SetAt(dw, p);
		return p;
	}
	else
	{
		return pObject;
	}	
}
	

// This will remove the object from the internal map and delete it
template <class T>
void CGXNodeManager<T>::RemoveObject(SEC_DWORD dw)
{
	SEC_DWORD dwKey = dw;
	T* pObject = NULL;
	
	ASSERT( GetMap()->Lookup(dwKey, pObject) != FALSE ); // Error: This object was already removed. 
	// Check if you are calling RemoveObject twice
	// on the same object

	GetMap()->RemoveKey(dwKey);

	if (pObject != NULL)
		delete pObject;
}

// clean up
template <class T>
void CGXNodeManager<T>::CleanObjects()
{
	// iterate through the list and call delete
	CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* pMap = GetMap();

	TRACE1("The number of objects in CGXNodeManager is: %i\n", pMap->GetCount());

	ASSERT( pMap != NULL ); // Error: Allocation map. This cannot be NULL --->END

	POSITION pos = pMap->GetStartPosition( );
	
	T* pObject = NULL;
	
	SEC_DWORD dw(0);

	while (pos != NULL)
	{	
		pMap->GetNextAssoc(pos, dw, pObject);
	
		if(pObject != NULL)
			delete pObject;
	}	

	pMap->RemoveAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// CGXNodeManagerNor
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple creation and garbage collection support
// Does not use CRuntimeClass* (No runtimeclass ---> Nor) 
///////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
struct CGXCreator
{
	virtual T* CreateObject() = 0;
};

template <class T>
class CGXNodeManagerNor
{
public:
	struct _iterOp
	{
		virtual void Execute(typename T* pObject) const = 0 ;
	};

	typedef typename void (T::*pFn) ();
	typedef _iterOp nodeIter;

	CGXNodeManagerNor(CGXCreator<T>* pCreator, pFn pfnCleanup);
	virtual ~CGXNodeManagerNor();

	virtual T* CreateObject(SEC_DWORD dw);
	void RemoveObject(SEC_DWORD dw);
	virtual T* GetObject(SEC_DWORD dw);

	void IterateObjects(const nodeIter* pIterObject) const;

	inline const CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* GetMap() const
	{return &m_pMpT;};

	inline CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* AccessMap()
	{return &m_pMpT;};

//implementation
protected:
	CMap<SEC_DWORD, SEC_DWORD&, T*, T*&> m_pMpT;
	
// clean up
	void CleanObjects();
	typename CGXCreator<typename T>* m_pCreator;
	typename pFn m_pfnCleanup;
};


template <class T>
CGXNodeManagerNor<T>::CGXNodeManagerNor(CGXCreator<T>* pCreator, typename CGXNodeManagerNor::pFn pfnCleanup)
{
	m_pCreator = pCreator;
	m_pfnCleanup = pfnCleanup;
	
	ASSERT(m_pfnCleanup != NULL); // Error no clean up function provided
}

template <class T>
CGXNodeManagerNor<T>::~CGXNodeManagerNor()
{
	if(m_pCreator != NULL)
		delete m_pCreator;

	CleanObjects();
}

template <class T>
T* CGXNodeManagerNor<T>::CreateObject(SEC_DWORD dw)
{
	ASSERT(m_pCreator != NULL); // Creator object must be valid at all times
	
	T* pObject = NULL;
	if(GetMap()->Lookup(dw, pObject) == FALSE )
	{
		T* p = m_pCreator->CreateObject();
		
		ASSERT(p != NULL);
		
		AccessMap()->SetAt(dw, p);
		return p;
	}
	else
	{
		return pObject;
	}	
}
	

template <class T>
T* CGXNodeManagerNor<T>::GetObject(SEC_DWORD dw)
{
	T* pObject = NULL;
	if(GetMap()->Lookup(dw, pObject) == FALSE )
		return NULL;
	else
		return pObject;
}

// This will remove the object from the internal map and delete it
template <class T>
void CGXNodeManagerNor<T>::RemoveObject(SEC_DWORD dw)
{
	SEC_DWORD dwKey = dw;
	T* pObject = NULL;
	
	ASSERT( GetMap()->Lookup(dwKey, pObject) != FALSE ); // Error: This object was already removed. 
	// Check if you are calling RemoveObject twice
	// on the same object

	AccessMap()->RemoveKey(dwKey);

	ASSERT(m_pfnCleanup != NULL); // Error no clean up function provided

	if(pObject != NULL && m_pfnCleanup != NULL)
			(pObject->*m_pfnCleanup)();
}

// clean up
template <class T>
void CGXNodeManagerNor<T>::CleanObjects()
{
	// iterate through the list and call delete
	CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* pMap = AccessMap();

	TRACE1("The number of objects in CGXNodeManager is: %i\n", pMap->GetCount());

	ASSERT( pMap != NULL ); // Error: Allocation map. This cannot be NULL --->END

	POSITION pos = pMap->GetStartPosition( );
	
	T* pObject = NULL;
	
	SEC_DWORD dw(0);

	while (pos != NULL)
	{	
		pMap->GetNextAssoc(pos, dw, pObject);
	
		ASSERT(m_pfnCleanup != NULL); // Error no clean up function provided

		if(pObject != NULL && m_pfnCleanup != NULL)
			(pObject->*m_pfnCleanup)();
	}	

	pMap->RemoveAll();
}

// special support for iteration. You can pass in an object that implements the callback
// Execute. This object can have state that can be used to make a context call to the
// object that is passed in. We use this approach for handling suplementary tabs in the tab
// window persistence mechanism 
template <class T>
void CGXNodeManagerNor<T>::IterateObjects(typename const CGXNodeManagerNor::nodeIter* pIterObject) const
{
	if(pIterObject == NULL)
		return;
	
	// iterate through the list and call delete
	const CMap<SEC_DWORD, SEC_DWORD&, T*, T*&>* pMap = GetMap();

	TRACE1("The number of objects in CGXNodeManager is: %i\n", pMap->GetCount());

	ASSERT( pMap != NULL ); // Error: Allocation map. This cannot be NULL --->END

	POSITION pos = pMap->GetStartPosition( );
	
	T* pObject = NULL;
	
	SEC_DWORD dw(0);

	while (pos != NULL)
	{	
		pMap->GetNextAssoc(pos, dw, pObject);
	
		if(pObject != NULL)
			pIterObject->Execute(pObject);
	}	

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CGXInterfaceManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple interface management. We use these as alternatives to smart pointers. When a interface is obtained
// it is registered with the interface manager. If an exception is thrown then the manager will call release.
// At class scope they can be used instead of having numerous interface variables...one for each interface.
// This map can only contain one instance of an interface type. There is no provision for multiple interfaces
// of the same type

template<class T>
struct CGXUnkWrapper
{	
	CGXUnkWrapper()
	{
		pUnk = NULL;
	};
	
	CGXUnkWrapper(T* p)
	{
		pUnk = p;
	};

	~CGXUnkWrapper()
	{};

	T* pUnk;
	
	inline operator T*()
	{return pUnk;};

	void Release()
	{
		if(pUnk)
			pUnk->Release();
	};
};

// This class will handle calling Release on all registered interface pointers
template <class T = IUnknown>
class CGXInterfaceManager
{
public:
	CGXInterfaceManager();
	virtual ~CGXInterfaceManager();

	T* GetInterface(const IID* iid);
	void SetInterface(T* p, const IID* pid);

	void RemoveInterface(const IID* iid, BOOL bRelease = FALSE);
	
	inline CMap<const IID*, const IID*&, T*, T*&>* GetMap()
	{return &m_pMpT;};

	// clean up
	void CleanObjects();

//implementation
protected:
	CMap<const IID*, const IID*&, T*, T*&> m_pMpT;
};

template <class T>
CGXInterfaceManager<T>::CGXInterfaceManager()
{
}

template <class T>
CGXInterfaceManager<T>::~CGXInterfaceManager()
{
	CleanObjects();
}

template <class T>
T* CGXInterfaceManager<T>::GetInterface(const IID* iid)
{
	const IID* refKey = iid;
	T* pInterface = NULL;
	
	// ASSERT( GetMap()->Lookup(refKey, pInterface) == TRUE ); // Error: This object was already removed. 
	// Check if you are calling RemoveObject twice
	// on the same object
	GetMap()->Lookup(refKey, pInterface);

	return pInterface;
}
	
template <class T>
void CGXInterfaceManager<T>::SetInterface(T* pInterface, const IID* pid)
{
	T* p = NULL;

	const IID* refKey =  pid;
	
	if(GetMap()->Lookup(refKey, p) == TRUE )
		pInterface->Release();
	
	GetMap()->SetAt(refKey, pInterface);
}


// This will remove the object from the internal map and delete it
template <class T>
void CGXInterfaceManager<T>::RemoveInterface(const IID* iid, BOOL bRelease /* = FALSE*/)
{
	const IID* refKey = iid;
	T* pObject = NULL;
	
	ASSERT( GetMap()->Lookup(refKey, pObject) == TRUE ); // Error: This object was already removed. 
	// Check if you are calling RemoveObject twice
	// on the same object
	
	GetMap()->Lookup(refKey, pObject);

	GetMap()->RemoveKey(refKey);

	if (bRelease && pObject != NULL)
		pObject->Release();
}

// clean up
template <class T>
void CGXInterfaceManager<T>::CleanObjects()
{
	// iterate through the list and call delete
	CMap<const IID*, const IID*&, T*, T*&>* pMap = GetMap();

	TRACE1("The number of objects in CGXNodeManager is: %i\n", pMap->GetCount());

	ASSERT( pMap != NULL ); // Error: Allocation map. This cannot be NULL --->END

	POSITION pos = pMap->GetStartPosition( );
	
	T* pObject = NULL;
	
	const IID* iid = NULL;

	while (pos != NULL)
	{	
		pMap->GetNextAssoc(pos, iid, pObject);
	
		if(pObject != NULL)
			pObject->Release();
	}	

	pMap->RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// CGXHandleManager ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple memory management of Global Memory handles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T = HGLOBAL>
class CGXHandleManager
{
public:
	CGXHandleManager();
	virtual ~CGXHandleManager();

	void SetHandle(T* ph);

	void RemoveHandle(T* ph, BOOL bFree = FALSE);
	
	inline CMap<const T*, const T*&, T, T&>* GetMap()
	{return &m_pMpT;};

	virtual void FreeObject(T h);

	// clean up
	void CleanObjects();

//implementation
protected:
	CMap<const T*, const T*&, T, T&> m_pMpT;
};


template <class T>
CGXHandleManager<T>::CGXHandleManager()
{
}

template <class T>
CGXHandleManager<T>::~CGXHandleManager()
{
	CleanObjects();
}

template <class T>
void CGXHandleManager<T>::FreeObject(T h)
{
	::GlobalFree(h);
}

template <class T>
void CGXHandleManager<T>::SetHandle(T* ph)
{
	ASSERT(ph != NULL);
	
	T hLocal = NULL;

	const T* refKey = ph ;
	
	// this handle is already in place
	ASSERT(GetMap()->Lookup(refKey, hLocal) == FALSE);
	
	GetMap()->SetAt(refKey, *ph);
}


// This will remove the object from the internal map and delete it
template <class T>
void CGXHandleManager<T>::RemoveHandle(T* ph, BOOL bFree /*= FALSE*/)
{
	const T* refKey = ph;
	T pObject = NULL;
	
	ASSERT( GetMap()->Lookup(refKey, pObject) == TRUE); // Error: This object was already removed. 
	// Check if you are calling RemoveHandle twice
	// on the same object

	GetMap()->Lookup(refKey, pObject);

	GetMap()->RemoveKey(refKey);

	if (bFree && pObject != NULL)
		FreeObject(pObject);
}

// clean up
template <class T>
void CGXHandleManager<T>::CleanObjects()
{
	// iterate through the list and call delete
	CMap<const T*, const T*&, T, T&>* pMap = GetMap();

	TRACE1("The number of objects in CGXHandleManager is: %i\n", pMap->GetCount());

	ASSERT( pMap != NULL ); // Error: Allocation map. This cannot be NULL --->END

	POSITION pos = pMap->GetStartPosition( );
	
	T pObject = NULL;
	
	const T* p = NULL;

	while (pos != NULL)
	{	
		pMap->GetNextAssoc(pos, p, pObject);
	
		if(pObject != NULL)
			FreeObject(pObject);
	}	

	pMap->RemoveAll();
}


// end class implementation

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_MFC_VER >= 0x0400 

#endif //_GX_MAN_H__
