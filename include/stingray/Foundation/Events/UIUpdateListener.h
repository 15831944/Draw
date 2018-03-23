///////////////////////////////////////////////////////////////////////////////
// UIUpdateListener.h : Declares command listener interface and adapter class.
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
// Author:       Jeff Boenig and Bob Powell and George Shepherd
// Description:  Framework independent event model.
//

#pragma once

#ifndef __UIUPDATELISTENER_H__
#define __UIUPDATELISTENER_H__

#include <Foundation\SflGuids.h>
#include <Foundation\Events\EventListener.h>
#include <Foundation\Events\UIUpdateElement.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IUIUpdateListener
//
//@class IUIUpdateListener | Interface to handling UIUpdate events. UIUpdate
// event listeners map UIUpdate and UIUpdate query events onto virtual member
// functions.
//
//@base public | IEventListener
//
class __declspec(uuid("E3533293-D410-4502-9AB3-61C1CCA58572"))
				IUIUpdateListener : public IEventListener
{
public:
	//@cmember
	/* Called when a UIUpdate event is received by the UIUpdate listener. */
	virtual bool OnUIUpdate(IUIUpdateElement* pUIUpdateElement, UINT nCommandID) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CUIUpdateAdapter
//
//@class CUIUpdateAdapter | The UIUpdate adapter class supplies a default
// implementation of the <c IUIUpdateListener> interface. The
// <mf CUIUpdateAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the IUIUpdateListener
// interface that always return FALSE. UIUpdate listeners can be derived
// from this class that override and implement only the handlers they are
// interested in.
//
//@base public | CEventListenerBase
//
class CUIUpdateAdapter : public CEventListenerBase<IUIUpdateListener>
{
// Operations
public:
	//@cmember
	/* Called when a UIUpdate event is received by the UIUpdate listener. */
	inline virtual bool OnUIUpdate(IUIUpdateElement* pUIUpdateElement, UINT nCommandID);
};

///////////////////////////////////////////////////////////////////////////
//
// CUIUpdateAdapter
//

//@mfunc Called when a UIUpdate event is received by the UIUpdate listener.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nID | UIUpdate ID for UIUpdate event.
bool CUIUpdateAdapter::OnUIUpdate(IUIUpdateElement* pUIUpdateElement, UINT nCommandID)
{
	pUIUpdateElement;
	nCommandID;
	return false;
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __UIUPDATELISTENER_H__
