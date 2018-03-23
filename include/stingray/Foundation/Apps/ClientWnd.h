///////////////////////////////////////////////////////////////////////////////
// ClientWnd.h : SFL Client window
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

#pragma once

#include <foundation\SflCommon.h>


namespace stingray {
namespace foundation {


typedef CWinTraits<WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE, WS_EX_STATICEDGE> CClientWindowTraits;


///////////////////////////////////////////////////////////////////////////
//@doc CClientWindowImpl
//
//@class CClientWindowImpl | Base class for client windows
//
//@tcarg typename | typename _Derived | The ultimately-derived class
//@tcarg typename | _Traits = CClientWindowTraits | Window creation flags
//@tcarg typename | _Base = ATL::CWindowImpl<_Derived, CWindow, _Traits | Base class
//
//@base public | _Base (default is CComModule)
//
//@comm Sometimes your application architecture calls for non-frame windows. 
// For example, many applications require the rendering and drawing code to be 
// separate from the frame. SFL supports this requirement through its client 
// windows. SFL defines its client windows through CClientWindowImpl. 
// Client windows are usually children of frame windows. SFL's client window class 
// is usually mixed in with other classes. 
//
// The main benefit of the CClientWindowImpl is that it defines a window
//  class with client window creation flags. The flags used by CClientWindowTraits
//  include WS_CLIPCHILDREN. WS_CLIPSIBLINGS, WS_CHILD, WS_VISIBLE, WS_EX_STATICEDGE. 
//
template <typename _Derived, typename _Traits = CClientWindowTraits, typename _Base = ATL::CWindowImpl<_Derived, CWindow, _Traits> >
class CClientWindowImpl: 
	public _Base
{
public:
	typedef CClientWindowImpl<_Derived, _Base, _Traits > _thisClass;
	typedef _Base _windowBase;

	BEGIN_MSG_MAP(_thisClass)

	END_MSG_MAP()
};


};	// namespace stingray::foundation
};	// namespace stingray
