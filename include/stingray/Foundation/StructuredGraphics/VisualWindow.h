///////////////////////////////////////////////////////////////////////////////
// VisualWindow.h : SFL Model-View-Controller architecture 
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
// Description:  SFL MVC: Visual window interface definition
//

#pragma once

#ifndef __VISUALWINDOW_H__
#define __VISUALWINDOW_H__

#include <foundation\guidcast.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc IVisualWindow
//
//@class IVisualWindow | This interface provides access to a window
// handle. It is used to abstract away the differences between windowed
// and windowless visual objects. A windowed visual object implements
// the <mf IVisualWindow::GetWindowHandle> function by returning its
// own window handle. A windowless visual object usually implements
// the <mf IVisualWindow::GetWindowHandle> function by returning the
// handle of its parent. This is used by MVC viewports.
//
//@base public | IQueryGuid

struct __declspec(uuid("722E1FCB-034F-4030-A600-3140A9D23DB4"))
	IVisualWindow : public IQueryGuid
{
	//@cmember,mfunc
	// Return the window handle for this object.
	//@@rdesc Window handle
	//@@end
	/* Return the window handle*/
	virtual HWND GetWindowHandle() = 0;
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __VISUALWINDOW_H__
