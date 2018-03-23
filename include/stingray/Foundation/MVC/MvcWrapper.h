///////////////////////////////////////////////////////////////////////////////
// MvcWrapper.h : Declaration of MvcWrapper_T
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
// Description:  Declaration of MvcWrapper_T template class.
//

#ifndef __MVCWRAPPER_H__
#define __MVCWRAPPER_H__

#pragma once

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc MvcWrapper_T
//@mfunc void  | MvcWrapper_T |  GetMargins | Retrieves the margins around the perimeter of the component
//@parm CRect& | rcMargins | Receives the current margin rectangle
//@xref <c MvcWrapper_T>

//@doc MvcWrapper_T
//@class MvcWrapper_T | A wrapper in MVC is way of nesting visual parts.  The wrapper
// class is equivalent to the Decorator design pattern.
//@tcarg class | base_t | The class of the visual part to derive from
template <class base_t>
class MvcWrapper_T : public base_t
{
// Constructor(s) & destructor
public:
	MvcWrapper_T() 
	{
		m_rcMargins.SetRectEmpty();
	}

// Attributes
protected:
	CRect m_rcMargins;		// margin offsets

// Operations
public:
	//@cmember
	/* Retrieves the margins around the perimeter of the component*/
	virtual void GetMargins(CRect& rcMargins);

	//@cmember
	/* Sets the margins around the perimeter of the component*/
	virtual void SetMargins(const CRect& rcMargins);

// Overrides
public:

	// Device Origin
	virtual CPoint SetOrigin(int x, int y);

	// Device Size
	virtual CSize SetSize(int cx, int cy);

	inline CSize SetSize(const CSize& sz)
	{
		return SetSize(sz.cx, sz.cy);
	}
};

template<class base_t>
//@doc MvcWrapper_T
//@mfunc Retrieves the margins around the perimeter of the component
//@rdesc void 
//@parm CRect& | rcMargins | Output parameter to receive margins
void MvcWrapper_T<base_t>::GetMargins(CRect& rcMargins)
{
	base_t::GetMargins(rcMargins);
	rcMargins.left += m_rcMargins.left;
	rcMargins.top += m_rcMargins.top;
	rcMargins.right += m_rcMargins.right;
	rcMargins.bottom += m_rcMargins.bottom;
}

template<class base_t>
//@doc MvcWrapper_T
//@mfunc Sets the margins around the perimeter of the component
//@rdesc void 
//@parm const CRect& | rcMargins | The new margin rectangle
void MvcWrapper_T<base_t>::SetMargins(const CRect& rcMargins)
{
	CRect rcBaseMargins;
	base_t::GetMargins(rcBaseMargins);
	CRect rc(GetBounds());
	rc.InflateRect(&rcBaseMargins);

	CRect delta;

	// Compute delta between old margin and new
	delta.left = rcMargins.left - m_rcMargins.left;
	delta.top = rcMargins.top - m_rcMargins.top;
	delta.right = rcMargins.right - m_rcMargins.right;
	delta.bottom = rcMargins.bottom - m_rcMargins.bottom;

	// Update the bounds to account for these new margins
	base_t::SetOrigin(rc.left + delta.left, rc.top + delta.top);
	base_t::SetSize(rc.Width() - (delta.left + delta.right),
					rc.Height() - (delta.top + delta.bottom));

	m_rcMargins = rcMargins;
}

template<class base_t>
CPoint MvcWrapper_T<base_t>::SetOrigin(int x, int y)
{
	// set the viewport rect accounting for margins
	return base_t::SetOrigin(x+m_rcMargins.left,y+m_rcMargins.top);
}

template<class base_t>
CSize MvcWrapper_T<base_t>::SetSize(int cx, int cy)
{
	return base_t::SetSize(cx - m_rcMargins.left - m_rcMargins.right,
						   cy - m_rcMargins.top - m_rcMargins.bottom);
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif // #ifndef __MVCWRAPPER_H__
