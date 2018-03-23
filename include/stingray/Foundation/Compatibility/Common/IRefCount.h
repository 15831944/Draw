///////////////////////////////////////////////////////////////////////////////
// IRefCount.h
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
// Author:       Dean Hallman
// Description:  Declaration of IRefCount interface.
//

// @doc MISC

#ifndef __IREFCOUNT_H__
#define __IREFCOUNT_H__

//
// CMN Extension DLL
// Initialize declaration context
//
#ifdef _CMNDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    MVC_DATAEXT
#endif //_CMNDLL

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
//
// IRefCount
//
//@class 
// IRefCount is an interface that can be mixed into any derivation to allow
// the class instances to be referenced counted.  When the reference count
// reaches zero, the class automatically deletes itself.
// 

class FOUNDATION_API IRefCount
{
protected:
	int m_dwRefCount;

public:
	IRefCount() {
		m_dwRefCount = 0;
	};

	virtual ~IRefCount() {}

	virtual void AddRef() {
		m_dwRefCount++;
	};

	virtual void Release() {
		--m_dwRefCount;
		if (!m_dwRefCount)
			delete this;
	};
};

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // __IREFCOUNT_H__
