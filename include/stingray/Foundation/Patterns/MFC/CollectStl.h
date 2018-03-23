///////////////////////////////////////////////////////////////////////////////
// CollectStl.h : STL version of collection classes.
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
// Author:       Jeff Boenig
// Description:  STL version of collection classes.
//

#ifndef __SFL_COLLECTSTL_H__
#define __SFL_COLLECTSTL_H__

#pragma warning (disable : 4018)
#pragma warning (disable : 4100)
#pragma warning (disable : 4238)
#pragma warning (disable : 4663)
#pragma warning (disable : 4244)

#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>

using std::vector;

namespace stingray {
namespace foundation {

#define _GET_ITERPOS_VAL(pbp)  (((CCIterPos_T<size_type>*) pbp)->m_value)

template <class element_t,	class arg_t>
class CCArray_T : public vector<element_t>, public ICollection_T<element_t>
{
public:

	typedef vector<element_t> ElementVector;
	typedef vector<element_t>::iterator ElementIterator;
	typedef CCIterPos_T<size_type> ElementIteratorPos;

	virtual element_t iGet(CCIterPos* pbp) const
	{
		CCArray_T<element_t,arg_t>* pThis = const_cast<CCArray_T<element_t,arg_t>*>(this);

		try
		{
			size_type pos = _GET_ITERPOS_VAL(pbp);
			if (pos < size())
				return pThis->at(pos);
		}
		catch (out_of_range)
		{
			return NULL;
		}

		return NULL;
	}

	virtual element_t* iGetPtr(CCIterPos* pbp)
	{
		try
		{
			return &(at(_GET_ITERPOS_VAL(pbp)));
		}
		catch (out_of_range)
		{
			return NULL;
		}
	}

	virtual BOOL iEOC(CCIterPos* pbp) const
	{
		if (_GET_ITERPOS_VAL(pbp) >= 0 && _GET_ITERPOS_VAL(pbp) < size())
			return FALSE;
		else
			return TRUE;
	}

	virtual void iFirst(CCIterPos* pbp) const
	{
		_GET_ITERPOS_VAL(pbp) = 0;
	}

	virtual void iNext(CCIterPos* pbp) const
	{
		_GET_ITERPOS_VAL(pbp)++;
	}

	virtual void iPrev(CCIterPos* pbp) const
	{
		_GET_ITERPOS_VAL(pbp)--;
	}

	virtual void iLast(CCIterPos* pbp) const
	{
		_GET_ITERPOS_VAL(pbp) = (size() - 1);
	}

	virtual SEC_INT GetSize() const
	{
		return size();
	}

	virtual void iSet(CCIterPos* pbp, element_t elem)
	{
		at(_GET_ITERPOS_VAL(pbp)) = elem;
	}

	virtual void iRemoveAt(CCIterPos* pbp)
	{
		ElementIterator iElem;
		iElem = begin() + _GET_ITERPOS_VAL(pbp);
		erase(iElem);
	}

	virtual void Remove(element_t elem)
	{
		ElementIterator iElem;

		for (iElem = begin(); iElem != end(); iElem++)
		{
			if (*iElem == elem)
			{
				erase(iElem);
				return;
			}
		}
	}

	virtual element_t iInsert(CCIterPos* pbp, element_t elem)
	{
		ElementIterator iElem;
		iElem = begin() + _GET_ITERPOS_VAL(pbp);
		insert(iElem, elem);
		return elem;
	}

	virtual BOOL iFindNext(CCIterPos* pbp, element_t elem) const
	{
		return FindNext(_GET_ITERPOS_VAL(pbp), elem);
	}

	virtual BOOL iFindPrev(CCIterPos* pbp, element_t elem) const
	{
		return FindPrev(_GET_ITERPOS_VAL(pbp), elem);
	}

	virtual BOOL FindNext(size_type& pos, element_t elem) const
	{
		BOOL bFound = FALSE;
		size_type posSeek = pos;

		while (!bFound && (++posSeek) < size())
		{
			if (elem == at(posSeek))
				bFound = TRUE;
		}

		posSeek = 0;

		while (!bFound && (++posSeek) < size())
		{
			if (elem == at(posSeek))
				bFound = TRUE;
		}

		if (bFound)
			pos = posSeek;

		return bFound;
	}

	virtual BOOL FindPrev(size_type& pos, element_t elem) const
	{
		BOOL bFound = FALSE;
		SEC_INT posSeek = pos;

		while (!bFound && (--posSeek) >= 0)
		{
			if (elem == at((size_type)posSeek))
				bFound = TRUE;
		}

		posSeek = (SEC_INT) (size() - 1);

		while (!bFound && (--posSeek) >= 0)
		{
			if (elem == at((size_type)posSeek))
				bFound = TRUE;
		}

		if (bFound)
			pos = (size_type)posSeek;

		return bFound;
	}

	virtual void RemoveAll()
	{
		clear();
	}

	virtual SEC_INT FindIndex(element_t elem) const
	{
		CCArray_T<element_t,arg_t>* pThis = const_cast<CCArray_T<element_t,arg_t>*>(this);
		ElementIterator iElem;
		SEC_INT nIdx = -1;
		SEC_INT nCurIdx = 0;

		for (iElem = pThis->begin(); nIdx == -1 && iElem != pThis->end(); iElem++)
		{
			if (elem == *iElem)
				nIdx = nCurIdx;
			else
				nCurIdx++;
		}

		return nIdx;
	}

	virtual CCIterPos* iCreateIteratorPosition() const
	{
		return new ElementIteratorPos;
	}

	element_t GetAt(SEC_INT nIndex) const
	{
		try
		{
			return at(nIndex);
		}
		catch (out_of_range)
		{
			return NULL;
		}
	}

	element_t& ElementAt(SEC_INT nIndex)
	{
		return at(nIndex);
	}

	SEC_INT Add(element_t newElement)
	{
		push_back(newElement);
		return (size() - 1);
	}

	SEC_INT Append(const CCArray_T<element_t,arg_t>& src)
	{
		SEC_INT nCount = 0;
		ElementIterator iElem;
		CCArray_T<element_t,arg_t>* pSrc = const_cast<CCArray_T<element_t,arg_t>*>(&src);

		for (iElem = pSrc->begin(); iElem != pSrc->end(); iElem++)
		{
			push_back(*iElem);
			nCount++;
		}

		return nCount;
	}

	void RemoveAt(SEC_INT nIndex, SEC_INT nCount = 1)
	{
		if (nIndex < size())
		{
			ElementIterator iFirst = begin() + nIndex;

			if (nCount == 1)
			{
				erase(iFirst);
			}
			else
			{
				ElementIterator iLast = iFirst + (nCount - 1);
				erase(iFirst, iLast);
			}
		}
	}

	SEC_INT GetUpperBound() const
	{
		return (size()-1);
	}

	void SetSize(SEC_INT nNewSize, SEC_INT nGrowBy = -1)
	{
		if (nGrowBy != -1)
		{
			reserve(size() + nGrowBy);
		}

		resize(nNewSize);
	}

	void SetAt(SEC_INT nIndex, arg_t newElement)
	{
		at(nIndex) = newElement;
	}

	void SetAtGrow(SEC_INT nIndex, arg_t newElement)
	{
		if (nIndex >= size())
		{
			resize(nIndex + 1);
		}

		at(nIndex) = newElement;
	}

	void InsertAt(SEC_INT nIndex, arg_t newElement, SEC_INT nCount = 1)
	{
		ElementIterator iElem;
		iElem = begin() + nIndex;
		insert(iElem, nCount, newElement);
	}
};

};  // namespace stingray::foundation
};  // namespace stingray

#endif // __SFL_COLLECTSTL_H__

