///////////////////////////////////////////////////////////////////////////////
// CollectMfc.h : Declaration of base collection classes
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
// Description:  Declaration of base collection classes.
//

#ifndef __SFL_COLLECTMFC_H__
#define __SFL_COLLECTMFC_H__

// Includes

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#include <StingrayExportDefs.h>

#pragma warning(disable: 4244)

//
// CMN Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXApp_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

namespace stingray {
namespace foundation {

//@doc CCArray_T
//@class A Collection Classes array that supports the ICollection_T interface
// a therefore iteration with Iterator_T.  This class doesn't define a new
// interface, other than that inherited from MFC's CArray class.  The interface
// you should use is the Iterator_T class to access the elements stored in
// a CCArray_T.
//@tcarg class | element_t | The class of the element to store.
//@tcarg class | arg_t | The class of the arguments to certain CArray functions.
template < class element_t,	class arg_t	> class  CCArray_T : 
	public CArray<element_t, arg_t>, public ICollection_T<element_t>
{
public:
	virtual element_t iGet(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		if (!iEOC(pbp))
			return GetAt(pp->m_value);
		else
			return NULL;
	};

	virtual element_t* iGetPtr(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		if (!iEOC(pbp))
			return &(m_pData[pp->m_value]);
		else
			return NULL;
	};

	virtual element_t& iGetRef(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		if (!iEOC(pbp))
			return m_pData[pp->m_value];
		else
			return *m_pData;
	};

	virtual BOOL iEOC(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		if (pp->m_value >= 0 && pp->m_value < GetSize())
			return FALSE;
		else
			return TRUE;
	};

	virtual void iFirst(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		pp->m_value = 0;
	};

	virtual void iNext(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		pp->m_value++;
	};

	virtual void iPrev(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		pp->m_value--;
	};

	virtual void iLast(CCIterPos* pbp) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		pp->m_value = GetUpperBound();
	};

	virtual SEC_INT GetSize() const {
		return CArray<element_t, arg_t>::GetSize();
	};

	virtual void iSet(CCIterPos* pbp, element_t elem) {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		SetAt(pp->m_value, elem);
	};

	virtual void iRemoveAt(CCIterPos* pbp) {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		RemoveAt(pp->m_value);
	};

	virtual void Remove(element_t elem) {
		SEC_INT i;
		for (i = GetUpperBound(); i >= 0; i--) {
			if (elem == GetAt(i))
				RemoveAt(i);
		}
	};

// WNL: Fix for CArray::Append() for VC++ 4.2
#if _MFC_VER == 0x0420
	virtual SEC_INT Append(const CCArray_T<element_t,arg_t>& src) {
		SEC_INT nAppendIndex = GetSize();
		for(SEC_INT i=0; i<src.GetSize(); i++)
			Add(src[i]);
		return nAppendIndex;
	};
#endif

	virtual element_t iInsert(CCIterPos* pbp, element_t elem) {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		InsertAt(pp->m_value, elem);
		return elem;
	};

	virtual BOOL iFindNext(CCIterPos* pbp, element_t elem) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		return FindNext(pp->m_value, elem);
	};

	virtual BOOL iFindPrev(CCIterPos* pbp, element_t elem) const {
		CCIterPos_T<SEC_INT>* pp = (CCIterPos_T<SEC_INT>*)pbp;
		return FindPrev(pp->m_value, elem);
	};

	virtual BOOL FindNext(SEC_INT& pos, element_t elem) const {
		BOOL bFound = FALSE;
		SEC_INT seek = pos;
		while (!bFound && ++seek < GetSize()) {
			if (elem == GetAt(seek))
				bFound = TRUE;
		}
		seek = -1;
		while (!bFound && ++seek < GetSize()) {
			if (elem == GetAt(seek))
				bFound = TRUE;
		}
		if (bFound)
			pos = seek;
		return bFound;
	};

	virtual BOOL FindPrev(SEC_INT& pos, element_t elem) const {
		BOOL bFound = FALSE;
		SEC_INT seek = pos;
		while (!bFound && --seek >= 0) {
			if (elem == GetAt(seek))
				bFound = TRUE;
		}
		seek = GetSize();
		while (!bFound && --seek >= 0) {
			if (elem == GetAt(seek))
				bFound = TRUE;
		}
		if (bFound)
			pos = seek;
		return bFound;
	};

	virtual void RemoveAll() {
		CArray<element_t, arg_t>::RemoveAll();
	};

	virtual SEC_INT FindIndex(element_t elem) const {
		SEC_INT nIdx = -1;
		for (SEC_INT nCurIdx = 0; nCurIdx < GetSize() && nIdx == -1; nCurIdx++)
		{
			if (elem == GetAt(nCurIdx))
				nIdx = nCurIdx;
		}
		return nIdx;
	};

	virtual CCIterPos* iCreateIteratorPosition() const {
		return new CCIterPos_T<SEC_INT>;
	};
};

//@doc CCStack_T
//@mfunc void | CCStack_T | CCStack_T | This constructor creates a CCStack_T object initialized with the specified maximum depth
//@parm SEC_INT | nMaxSize | The maximum depth of the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@mfunc void | CCStack_T | SetMaxSize | Sets the maximum depth of the stack.  Once this depth is reached, the stack "rolls"
//@parm SEC_INT | nMaxSize | The maximum depth of the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@mfunc void | CCStack_T | Push | Pushes a new element onto the stack
//@parm element_t | elem | The element to push onto the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@mfunc void | CCStack_T | Pop | Retrieves and deletes to newest element off the top of the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@mfunc void | CCStack_T | Peek | Retrieves but does not delete the newest element off the top of the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@mfunc SEC_INT | CCStack_T | GetElementCount | Returns the number of elements that currently exist in the stack
//@xref <c CCStack_T>

//@doc CCStack_T
//@class A Collection Classes Stack that implements the First-In, First-Out
// method of storage.  In addition, this stack can function as a circular
// buffer.  Basically, when the stack reaches its maximum depth, the oldest
// element at the bottom of the stack is expired to make room for a new
// element.  Use the SetMaxSize to setup the maximum depth.
//@tcarg class | element_t | The class of the element to store in the stack.
//@tcarg class | arg_t | The class of the arguments to certain CArray functions.
template <class element_t, class arg_t> class  CCStack_T : 
	private CArray<element_t, arg_t>, public IStack_T<element_t>
{
protected:
	SEC_INT m_nIndex;
	SEC_INT m_nMaxSize;
	SEC_INT m_cElems;

public:
	CCStack_T<element_t, arg_t>() {
		m_nIndex = -1;
		m_cElems = 0;
		m_nMaxSize = -1;
	}

	//@cmember
	/* This constructor creates a CCStack_T object initialized with the specified maximum depth*/
	CCStack_T<element_t, arg_t>(SEC_INT nMaxSize) {
		m_nIndex = -1;
		m_cElems = 0;
		SetMaxSize(nMaxSize);
	}

	//@cmember
	/* Sets the maximum depth of the stack.  Once this depth is reached, the stack "rolls"*/
	void SetMaxSize(SEC_INT nMaxSize) {
		m_nMaxSize = nMaxSize;
		SetSize(m_nMaxSize);
	}

	//@cmember
	/* Returns the number of elements that currently exist in the stack*/
	SEC_INT GetElementCount() const {
		return m_cElems;
	}

	//@cmember
	/* Pushes a new element onto the stack*/
	element_t Push(element_t elem) {
		element_t oldElem;
		m_nIndex = ( (m_nIndex+1) % m_nMaxSize );
		oldElem = GetAt(m_nIndex);
		SetAt(m_nIndex, elem);
		m_cElems++;
		m_cElems = mvcmin(m_cElems, m_nMaxSize);
		return oldElem;
	}

	//@cmember
	/* Retrieves but does not delete the newest element off the top of the stack*/
	element_t Peek() const {
		return (m_nIndex >= 0 && m_nIndex < m_nMaxSize) ? GetAt(m_nIndex) : NULL;
	}

	//@cmember
	/* Retrieves and deletes to newest element off the top of the stack*/
	element_t Pop() {
		element_t elem;
		if (m_cElems > 0) {
			elem = GetAt(m_nIndex);
			SetAt(m_nIndex, NULL);
			m_nIndex = ( (m_nIndex-1) % m_nMaxSize );
			if (m_nIndex < 0)
				m_nIndex = m_nMaxSize-1;
			m_cElems--;
			m_cElems = mvcmax(m_cElems, 0);
		}
		else
			elem = NULL;
		return elem;
	}

	//@cmember
	/* Accessing elements */
	element_t GetElementAt(SEC_INT m_nIndex) const { return GetAt(m_nIndex); }

};

};  // namespace stingray::foundation
};  // namespace stingray

//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SFL_SECCOLLECT_H__

