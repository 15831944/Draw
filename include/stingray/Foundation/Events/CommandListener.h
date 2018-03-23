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

// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#pragma once

#ifndef __COMMANDLISTENER_H__
#define __COMMANDLISTENER_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\EventListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc ICommandListener
//
//@class ICommandListener | Interface to handling command events. Command
// event listeners map command and command query events onto virtual member
// functions.
//
//@base public | IEventListener
//
class __declspec(uuid("81CEDD2C-B2F0-4702-AA2F-D911897F5F33"))
				ICommandListener : public IEventListener
{
public:
	//@cmember
	/* Called when a command query event is received by the command listener. */
	virtual bool OnCommandQuery(UINT nID) = 0;
	//@cmember
	/* Called when a command event is received by the command listener. */
	virtual bool OnCommand(UINT nID, int nNotifyCode) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CCommandAdapter
//
//@class CCommandAdapter | The command adapter class supplies a default
// implementation of the <c ICommandListener> interface. The
// <mf CCommandAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the ICommandListener
// interface that always return FALSE. Command listeners can be derived
// from this class that override and implement only the handlers they are
// interested in.
//
//@base public | CEventListenerBase
//
class CCommandAdapter : public CEventListenerBase<ICommandListener>
{
// Operations
public:
	//@cmember
	/* Called when a command query event is received by the command listener. */
	inline virtual bool OnCommandQuery(UINT nID);

	//@cmember
	/* Called when a command event is received by the command listener. */
	inline virtual bool OnCommand(UINT nID, int nNotifyCode);
};

///////////////////////////////////////////////////////////////////
// COMMAND map macros for implementing the OnCommand() function

#define BEGIN_COMMAND_MAP(CLASSNAME)  \
	virtual bool OnCommand(UINT nID, int nNotifyCode) { bool bHandled = false; \

#define COMMAND_ENTRY(CMDID,CMDHANDLER)  \
	if (nID == CMDID) { bHandled = CMDHANDLER(nID, nNotifyCode); } \

#define COMMAND_CHAIN_ENTRY(T)  \
	bHandled = T::OnCommand(nID, nNotifyCode); \

#define END_COMMAND_MAP  return bHandled; }


///////////////////////////////////////////////////////////////////////////
//
// CCommandAdapter
//

//@mfunc Called when a command query event is received by the command listener.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nID | Command ID for command query event.
bool CCommandAdapter::OnCommandQuery(UINT nID)
{
	nID;
	return false;
}

//@mfunc Called when a command event is received by the command listener.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nID | Command ID for command event.
bool CCommandAdapter::OnCommand(UINT nID, int nNotifyCode)
{
	nID;
	nNotifyCode;
	return false;
}



};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __COMMANDLISTENER_H__
