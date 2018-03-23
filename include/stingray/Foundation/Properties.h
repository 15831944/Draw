///////////////////////////////////////////////////////////////////////////////
// Properties.h : SFL properties package
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


#if !defined(_SFL)
#define _SFL
#endif

#include <Foundation\SflCommon.h>

#if defined(_ATL)
#include <Foundation\Properties\PropIface.h>
#include <Foundation\Properties\Property.h>
#include <Foundation\Properties\Enumeration.h>
#include <Foundation\Properties\PropAccessor.h>
#include <Foundation\Properties\PropContainer.h>
#include <Foundation\Properties\PropEditorBase.h>
#endif

#if defined(_SFL_ATL_SUPPORT)
#include <Foundation\Properties\AxProperty.h>
#include <Foundation\Properties\AxPropContainer.h>
#endif // #if defined(_SFL_ATL_SUPPORT)
