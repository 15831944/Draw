///////////////////////////////////////////////////////////////////////////////
// Event.h : Interface to event classes.
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

// Authors:      Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#ifndef __EVENT_H__
#define __EVENT_H__

#pragma once

#include <foundation\CppIface.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IEvent
//
//@class IEvent | Base interface for event objects.
//
//@base public | IRefCount
//@base public | IQueryGuid
//
class __declspec(uuid("83C0B4B9-BFBD-466b-8082-B9B086E00756"))
					IEvent : public IRefCount, public IQueryGuid
{
public:
	//@cmember,mfunc
	// Dispatches the event to the given event listener.
	//@@rdesc Returns true if event dispatched successfully, otherwise false.
	//@@parm Pointer to listener object to receive the event.
	//@@end
	/* Dispatches the event to the given event listener*/
	virtual bool Dispatch(IQueryGuid* pIListener) = 0;
};


};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __EVENT_H__
