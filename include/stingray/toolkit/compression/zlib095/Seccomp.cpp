///////////////////////////////////////////////////////////////////////////////
// seccomp.cpp
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
//  Author:		AAB
//  Description:	Implementation of SECComp
//  Created:		Fri Dec 29 23:47:10 1995
//


// stdafx.h for SEC includes secall.h
#define _OT_EXPORT_IMPL

#include "stdafx.h"

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __SECCOMP_H__
#include "compeng.h"
#endif

#ifndef _INC_WINDOWSX
#include <windowsx.h> 
#endif

#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif


#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL


IMPLEMENT_SERIAL(SECComp, CObject,1)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW


SECComp::SECComp()
{
	// initializer taken originally from crc32.cpp
	crc_table_empty = 1;
	fixed_lock = 0;
	fixed_built = 0;
	fixed_left = FIXEDH;

}

SECComp::~SECComp()
{
    // nothing for now
}

void SECComp::Serialize(CArchive& ar)
{
    ASSERT_VALID(this);
	//AAB TODO Flesh out
	ar;
}

#ifdef _DEBUG
void SECComp::AssertValid() const
{
    CObject::AssertValid();
}
#endif /* _DEBUG */

