///////////////////////////////////////////////////////////////////////////////
// gxexman.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_EXMAN_H__
#define _GX_EXMAN_H__

#if _MFC_VER >= 0x0400 

// helper class for managing captive objects
// CGXCaptiveManagerNoRef
template <class T>
class CGXCaptiveManagerNoRef
{
public:
	CGXCaptiveManagerNoRef();
	virtual ~CGXCaptiveManagerNoRef();

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
CGXCaptiveManagerNoRef<T>::CGXCaptiveManagerNoRef()
{
 //
}

template <class T>
CGXCaptiveManagerNoRef<T>::~CGXCaptiveManagerNoRef()
{
	CleanObjects();
}

template <class T>
T* CGXCaptiveManagerNoRef<T>::CreateObject()
{
	if(GetList()->IsEmpty())
	{
		T* p = new T;
		return p;
	}
	else
		return GetList()->RemoveTail();
}
	
template <class T>
void CGXCaptiveManagerNoRef<T>::RecycleObject(T* pObject)
{
	// check to see if the element is already in the list
	ASSERT(GetList()->Find(pObject) == NULL);	

	GetList()->AddTail(pObject);
}
	
// clean up
template <class T>
void CGXCaptiveManagerNoRef<T>::CleanObjects()
{
	// iterate through the list and call delete
	CList<T*, T*&>* pList = GetList();

	TRACE1("The number of objects in CGXCaptiveManager is: %i\n", pList->GetCount());

	ASSERT(pList!=NULL);

	POSITION pos = pList->GetHeadPosition();
	
	T* pObject = NULL;

	while (pos != NULL)
	{	
		pObject = pList->GetNext(pos);
	
		if(pObject != NULL)
			delete pObject;
	}	

	pList->RemoveAll();
}

#endif //_MFC_VER >= 0x0400 

#endif //_GX_EXMAN_H__
