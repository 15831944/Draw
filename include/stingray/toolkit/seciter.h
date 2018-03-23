///////////////////////////////////////////////////////////////////////////////
// seciter.h : interface for the iterator classes.
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
// Author:       Justin Rudd
// Description:  Declaration of iterator classes
//

#ifdef WIN32

#ifndef __SECITER_H__
#define __SECITER_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Constants

// Macros

// Types

// Forward Declarations

template<class TYPE>
class SECIterator
{
protected:
	inline SECIterator(){}
public:
	virtual ~SECIterator(){}
	virtual void First() = 0;
	virtual void Last() = 0;
	virtual void Next() = 0;
	virtual void Prev() = 0;
	virtual TYPE Item() = 0;
	virtual BOOL IsDone() const = 0;
};

template<class TYPE>
class SECIteratorPtr
{
public:
	//construction/destruction
	inline SECIteratorPtr()
		{ m_pIterator = NULL; }
	inline SECIteratorPtr( SECIterator<TYPE>* pIterator )
		{ m_pIterator = pIterator; }
	inline SECIteratorPtr( const SECIterator<TYPE>& source )
		{ *this = source; }
	inline ~SECIteratorPtr()
		{ delete m_pIterator; } //safe to delete NULL pointer

	//normal operators...
	inline void operator=( SECIterator<TYPE>* pIterator )
		{
			delete m_pIterator;
			m_pIterator = pIterator;
		}
	inline const SECIteratorPtr& operator=( const SECIteratorPtr<TYPE>& source )
		{
			if( this != &source )
			{
				delete m_pIterator;
				m_pIterator = source.m_pIterator;
			}
			return *this;
		}
	inline SECIterator<TYPE>* operator->()
		{
			ASSERT(m_pIterator);
			return m_pIterator;
		}
	inline SECIterator<TYPE>& operator*()
		{
			ASSERT(m_pIterator);
			return *m_pIterator;
		}

	//type-cast operators...
	inline operator SECIterator<TYPE>*()
		{
			ASSERT(m_pIterator);
			return m_pIterator;
		}
	inline operator SECIterator<TYPE>&()
		{
			ASSERT(m_pIterator);
			return *m_pIterator;
		}

protected:
	SECIterator<TYPE>* m_pIterator;
};

namespace SECArrayIteratorTypes
{
	class IArrayInterface
	{
	protected:
		int m_iItem;
		
		inline IArrayInterface()
			{
				m_iItem = -1;
			}
		inline void FirstImp()
			{
				m_iItem = 0;
			}
		inline void LastImp( int iItem )
			{
				m_iItem = iItem;
			}
		inline void NextImp()
			{
				m_iItem++;
			}
		inline void PrevImp()
			{
				m_iItem--;
			}
	};

	template<class TYPE,class ARG_TYPE>
	class SECCArrayIterator : public SECIterator<TYPE>, private IArrayInterface
	{
	protected:
		CArray<TYPE,ARG_TYPE>& m_ar;
				
	public:
		inline SECCArrayIterator( CArray<TYPE,ARG_TYPE>& ar ) : m_ar(ar) 
			{

			}
		inline virtual ~SECCArrayIterator()
			{ 
		
			}

		inline virtual void First()
			{ 
				FirstImp();
			}
		inline virtual void Last()
			{ 
				LastImp( (int)m_ar.GetSize() - 1 );
			}
		inline virtual void Next()
			{ 
				NextImp();
			}
		inline virtual void Prev()
			{ 
				PrevImp();
			}
		inline virtual BOOL IsDone() const
			{
				return BOOL( (m_iItem == m_ar.GetSize()) || (m_iItem < 0) );
			}

		inline virtual TYPE Item()
			{
				ASSERT(!IsDone());
				return m_ar[m_iItem];
			}
	};

	template<class BASE_CLASS,class TYPE>
	class SECCTypedPtrArrayIterator : public SECIterator<TYPE>, private IArrayInterface
	{
	protected:
		CTypedPtrArray<BASE_CLASS,TYPE>& m_ar;

	public:
		inline SECCTypedPtrArrayIterator( CTypedPtrArray<BASE_CLASS,TYPE>& ar) : m_ar(ar)
			{

			}
		inline virtual ~SECCTypedPtrArrayIterator()
			{	

			}

		inline virtual void First()
			{
				FirstImp();
			}
		inline virtual void Last()
			{
				LastImp(m_ar.GetSize()-1);
			}
		inline virtual void Next()
			{
				NextImp();
			}
		inline virtual void Prev()
			{
				PrevImp();
			}
		inline virtual BOOL IsDone() const
			{
				return BOOL( (m_iItem == m_ar.GetSize()) || (m_iItem < 0) );
			}
		inline virtual TYPE Item()
			{
				ASSERT(!IsDone());
				return m_ar[m_iItem];
			}
	};
}

namespace SECIteratorFactory
{
	template<class TYPE,class ARG_TYPE>
	inline SECIterator<TYPE>* CreateIterator( CArray<TYPE,ARG_TYPE>& ar )
		{
			return new SECArrayIteratorTypes::SECCArrayIterator<TYPE,ARG_TYPE>(ar);
		}

	template<class BASE_CLASS,class TYPE>
	inline SECIterator<TYPE>* CreateIterator( CTypedPtrArray<BASE_CLASS,TYPE>& ar )
		{
			return new SECArrayIteratorTypes::SECCTypedPtrArrayIterator<BASE_CLASS,TYPE>(ar);
		}
}

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECITER_H__

#endif //WIN32
