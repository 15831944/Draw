///////////////////////////////////////////////////////////////////////////////
// MvcGuids.h
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
// Author: Jeff Boenig
// <nl>Created: 3/99
// 
/////////////////////////////////////////////////////////////////////////////
//@doc
//@module MvcGuids.h | This module contains GUID declarations for
// the Stingray MVC library. If initguid.h is included before
// this file, the GUIDs are defined.

#pragma once

#include <objbase.h>
#include <Foundation\Compatibility\Common\CmnGuids.h>

const GUID IID_IMvcSubject = IID_ISubject;
const GUID IID_IMvcObserver = IID_IObserver;
const GUID IID_IMvcMessage = IID_IMessage;


// {F0526984-E944-11d2-B412-006008AFE059}
DEFINE_GUID(IID_IMvcModel, 
0xf0526984, 0xe944, 0x11d2, 0xb4, 0x12, 0x0, 0x60, 0x8, 0xaf, 0xe0, 0x59);
