///////////////////////////////////////////////////////////////////////////////
// KeyboardListener.h : Declares keyboard listener interface and adapter class.
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
// Author:       Steve Danielson
// Description:  Framework independent event model.
//

#pragma once

#ifndef __KEYBOARDLISTENER_H__
#define __KEYBOARDLISTENER_H__

#include <foundation\SflGuids.h>
#include <foundation\Events/EventListener.h>
#include <Foundation\Events/KeyboardListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

class __declspec(uuid("C7E4D0B6-4F42-4a42-8E63-C2CC1C529424"))
				IKeyboardListener : public IEventListener
{
public:
	virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual bool OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
};

class CKeyboardAdapter : public CEventListenerBase<IKeyboardListener>
{
// Operations
public:
	inline virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline virtual bool OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

///////////////////////////////////////////////////////////////////////////
//
// CKeyboardAdapter
//

bool CKeyboardAdapter::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

bool CKeyboardAdapter::OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nChar;
	nRepCnt;
	nFlags;

	return false;
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __KEYBOARDLISTENER_H__
