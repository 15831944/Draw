///////////////////////////////////////////////////////////////////////////////
// ScrollListener.h  Declares mouse listener interface and adapter class.
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
// Description:  Framework independent event model.
//

#pragma once

#ifndef __SCROLLLISTENER_H__
#define __SCROLLLISTENER_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\EventListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IScrollListener
//
//@class IScrollListener | Interface to handling scroll events. Scroll event
// listeners map various scroll events onto the virtual member functions for
// handling.
//
//@mfunc bool | IScrollListener | OnHScroll | Handle horizontal scroll events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm int | nScrollCode | Indicates the type of movement (line, page, thumb)
//@parm short | nScrollPos | The position the scrollbar has been moved to.
//@parm HWND | hScrollWnd | Window handle of scrollbar that caused the event.
//
//@mfunc bool | IScrollListener | OnVScroll | Handle vertical scroll events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm int | nScrollCode | Indicates the type of movement (line, page, thumb)
//@parm short | nScrollPos | The position the scrollbar has been moved to.
//@parm HWND | hScrollBar | Window handle of scrollbar that caused the event.
//
//@base public | IEventListener
//
class __declspec(uuid("DF46F837-8A05-4d88-9E4B-263BACD8B5C5"))
				IScrollListener : public IEventListener
{
public:
	//@cmember
	/* Handle horizontal scroll events. */
	virtual bool OnHScroll(int nScrollCode, short nScrollPos, HWND hScrollBar) = 0;
	//@cmember
	/* Handle vertical scroll events. */
	virtual bool OnVScroll(int nScrollCode, short nScrollPos, HWND hScrollBar) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CScrollAdapter
//
//@class CScrollAdapter | 
//
//@base public | CEventListenerBase
//
class CScrollAdapter : public CEventListenerBase<IScrollListener>
{
// Operations
public:
	//@cmember
	/* Handle horizontal scroll events. */
	virtual bool OnHScroll(int nScrollCode, short nScrollPos, HWND hScrollBar)
	{
		nScrollCode;
		nScrollPos;
		hScrollBar;
		return false;
	}

	//@cmember
	/* Handle vertical scroll events. */
	virtual bool OnVScroll(int nScrollCode, short nScrollPos, HWND hScrollBar)
	{
		nScrollCode;
		nScrollPos;
		hScrollBar;
		return false;
	}
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __SCROLLLISTENER_H__
