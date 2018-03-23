///////////////////////////////////////////////////////////////////////////////
// SmartPtr.h
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
// @doc SmartPtr
// @module SmartPtr.h | Pointer class that does automatic reference counting.
// 
// 
// Author: Jeff Boenig
// <nl>Created: 01/98
// 
/////////////////////////////////////////////////////////////////////////////

#ifndef __SMARTPTR_H__
#define __SMARTPTR_H__

// MVC Extension DLL
// Initialize declaration context
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA SFL_DATAEXT
#endif //_SFLDLL

#include <foundation\sflcommon.h>

/////////////////////////////////////////////////////////////////////
// SmartPtr
//
//@class
// SmartPtr | A SmartPtr encapsulates pointers to objects that support
// the IRefCount interface and automatically performs reference
// counting on the object.
//
//@tcarg class | element_t |
//  The class of objects that the smart pointer can reference. This
//  class must support the IRefCount interface.

template <class T> class SmartPtr
{
	T *m_pObj;
public:
	SmartPtr()
	{
		m_pObj = 0;
	}

	SmartPtr( T *pObj )
	{
		if( ( m_pObj = pObj ) != 0 )
		{
			m_pObj->AddRef();
		}
	}

	SmartPtr( const SmartPtr &src )
	{
		m_pObj = 0;
		*this = src.m_pObj;
	}

	~SmartPtr(void)
	{
		if( m_pObj != 0 )
		{
			m_pObj->Release();
		}
	}

	operator T*(void) const { return m_pObj; }

	operator SEC_LONG(void) const { return (SEC_LONG)m_pObj; }

	T& operator*(void) { return *m_pObj; }

	T* operator->(void) const { return m_pObj; }

	SmartPtr& operator=( T* pObj )
	{
		if( pObj != 0 )
		{
			pObj->AddRef();
		}

		if( m_pObj != 0 )
		{
			m_pObj->Release();
		}

		m_pObj = pObj;

		return *this;
	}

	SmartPtr& operator=( const SmartPtr &src )
	{
		return( *this = src.m_pObj );
	}

	BOOL operator==( const SmartPtr &src )
	{
		return ( m_pObj == src.m_pObj );
	}

	BOOL operator==( T *pObj )
	{
		return ( m_pObj == pObj );
	}

	BOOL operator!=( const SmartPtr &src )
	{
		return ( m_pObj != src.m_pObj );
	}

	BOOL operator!=( T *pObj )
	{
		return ( m_pObj != pObj );
	}
};

/////////////////////////////////////////////////////////////////////////////

// MVC Extension DLL
// Reset declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SMARTPTR_H__

/////////////////////////////////////////////////////////////////////////////
