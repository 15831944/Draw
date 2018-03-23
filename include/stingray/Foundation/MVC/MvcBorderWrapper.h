///////////////////////////////////////////////////////////////////////////////
// MvcBorderWrapper.h : Declaration of MvcBorderWrapper_T
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
// Description:  Declaration of MvcBorderWrapper_T interface.
//

//@doc MvcBorderWrapper_T
//
// MvcBorderWrapper_T class

#pragma once

#ifndef __MVCBORDERWRAPPER_H__
#define __MVCBORDERWRAPPER_H__

// Header Includes
#include <Foundation\MVC\MvcWrapper.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//
// MvcBorderWrapper_T
//
//@class MvcBorderWrapper_T |
// The MvcBorderWrapper_T class draws a border around the contained class.
// A border decorator is a wrapper class that contains a component, insets it
// by some margin and draws a border around the perimeter of the contained
// component.  A border decorator currently supports only ThinBorder style.
//
//@tcarg class | base_t | The class of the visual part to derive from
//@tcarg COLORREF | crBorder_t | Border color
//@tcarg int | nWidth_t | Border width
//
//@base public | MvcWrapper_T
//

template <class base_t, COLORREF crBorder_t, int nWidth_t>
class MvcBorderWrapper_T : public MvcWrapper_T<base_t>
{
// Construction/destruction
public:

	MvcBorderWrapper_T() 
	{
		SetMargins(CRect(nWidth_t, nWidth_t, nWidth_t, nWidth_t));
	}

// Operations
public:
	//@cmember
	/* Draw the border on a device context*/
	virtual void Draw(CDC* pDC);
};

template<class base_t, COLORREF crBorder_t, int nWidth_t>
//@doc MvcBorderWrapper_T
//@mfunc Draw the border on a device context
//@rdesc void 
//@parm CDC* | pDC | The device context to draw on
void MvcBorderWrapper_T<base_t, crBorder_t, nWidth_t>::Draw(CDC* pDC)
{
	// Draw the wrapped component
	MvcWrapper_T<base_t>::Draw(pDC);

	MvcViewport::DC dcWnd(this, FALSE);

	CRect rcBounds(GetBounds());

	CRect rcBorder(rcBounds.left + (m_rcMargins.left/2),
	               rcBounds.top + (m_rcMargins.top/2),
	               rcBounds.right - (m_rcMargins.right/2),
	               rcBounds.bottom - (m_rcMargins.bottom/2));

	CPen pen(PS_SOLID, nWidth_t, crBorder_t);
	CPen *pOldPen = dcWnd.SelectObject(&pen);

	// Draw a border
	dcWnd.MoveTo(rcBorder.TopLeft());
	dcWnd.LineTo(rcBorder.right, rcBorder.top);
	dcWnd.LineTo(rcBorder.BottomRight());
	dcWnd.LineTo(rcBorder.left, rcBorder.bottom);
	dcWnd.LineTo(rcBorder.TopLeft());

	dcWnd.SelectObject(pOldPen);
}

///////////////////////////////////////////////////////////////////////////

};  // namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MVCBORDERWRAPPER_H__
