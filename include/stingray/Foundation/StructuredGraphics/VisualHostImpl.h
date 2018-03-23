///////////////////////////////////////////////////////////////////////////////
// VisualHostImpl.h : SFL Model-View-Controller architecture 
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
// Description:  SFL MVC: Host architecture implementation
//

#pragma once

#ifndef __VISUALHOSTIMPL_H__
#define __VISUALHOSTIMPL_H__

#include <assert.h>
#include <Foundation\StructuredGraphics\VisualHost.h>
#include <Foundation\Graphics\GCCore.h>

namespace stingray {
namespace foundation {

template<typename T>
struct CVisualHostImpl : public IVisualHost
{
	typedef T _hostwin;

	BEGIN_GUID_MAP(CVisualHostImpl<T>)
		GUID_ENTRY(IVisualHost)
	END_GUID_MAP

	CVisualHostImpl():_m_hWnd((static_cast<_hostwin*>(this))->m_hWnd){
		// no implementation
	};

	virtual ~CVisualHostImpl() {
		// no implementation
	};

	//@cmember
	/* Invalidate the specified rectangle within this visual host. */
	virtual void InvalidateRect(const CRect& rect, BOOL bErase = TRUE, BOOL bRepairNow = FALSE)
	{
		bRepairNow;
		assert( ::IsWindow(_m_hWnd) );// error invalid window
		::InvalidateRect(_m_hWnd, rect, bErase);
	}

	//@cmember
	/* Validate the specified rectangle within this visual host. */
	virtual void ValidateRect(const CRect& rect)
	{
		assert( ::IsWindow(_m_hWnd) );// error invalid window
		::ValidateRect(_m_hWnd, rect);
	}

private:
	// Window handle
	HWND& _m_hWnd;
};


};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __VISUALHOSTIMPL_H__
