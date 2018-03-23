///////////////////////////////////////////////////////////////////////////////
// CommandListener.h : Declares command listener interface and adapter class.
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
// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//
// $Header: $
// $NoKeywords: $

#ifndef __COMPAT_COMMANDLISTENER_H__
#define __COMPAT_COMMANDLISTENER_H__

#include "Foundation\Compatibility\Common\CmnGuids.h"

#ifndef __COMPAT_EVENTLISTENER_H__
#include "Foundation\Compatibility\Common\Events\EventListener.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
//@doc ICommandListener
//
//@class ICommandListener | Interface to handling command events. Command
// event listeners map command and command query events onto virtual member
// functions.
//
//@base public | IEventListener
//
class __declspec(uuid("47E1CE3A-D500-11d2-8CAB-0010A4F36466"))
				ICommandListener : public IEventListener
{
public:
	//@cmember
	/* Called when a command query event is received by the command listener. */
	virtual BOOL OnCommandQuery(UINT nID) = 0;
	//@cmember
	/* Called when a command event is received by the command listener. */
	virtual BOOL OnCommand(UINT nID, int nNotifyCode) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CommandAdapter
//
//@class CommandAdapter | The command adapter class supplies a default
// implementation of the <c ICommandListener> interface. The
// <mf CommandAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the ICommandListener
// interface that always return FALSE. Command listeners can be derived
// from this class that override and implement only the handlers they are
// interested in.
//
//@base public | EventListener_T
//
class FOUNDATION_API CommandAdapter : public EventListener_T<ICommandListener, &IID_ICommandListener>
{
// Operations
public:
	//@cmember
	/* Called when a command query event is received by the command listener. */
	virtual BOOL OnCommandQuery(UINT nID);

	//@cmember
	/* Called when a command event is received by the command listener. */
	virtual BOOL OnCommand(UINT nID, int nNotifyCode);
};

};  // end namespace rw

#endif // __COMPAT_COMMANDLISTENER_H__
