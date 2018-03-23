///////////////////////////////////////////////////////////////////////////////
// EventList.h
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

#ifndef _EventList_H
#define _EventList_H

#include <afxtempl.h>
#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

struct SECA_EventParam
{
	CString		strParamName;
	VARTYPE		vartype; //paramater's type
	long		idlFlags;
};

#define SECA_EventParamArray CArray < SECA_EventParam, SECA_EventParam& > 

class SECABrowsedEvent
{
public:

	inline SECABrowsedEvent() {}
	TOOLKIT_API SECABrowsedEvent &operator= (const SECABrowsedEvent &src);
	TOOLKIT_API SECABrowsedEvent( const SECABrowsedEvent &copy);

	CString			          strEventName;
	SECA_EventParamArray	eventParams;
};

#define SECA_EventArray CArray < SECABrowsedEvent, SECABrowsedEvent& > 

struct  ISCollection;

TOOLKIT_API HRESULT EnumEvents( ISCollection *pCollection, SECA_EventArray /*out */ &events );
TOOLKIT_API HRESULT LoadParams( LPDISPATCH pdispElements, SECA_EventParamArray /*out*/ &ep);
TOOLKIT_API HRESULT BuildEventList( ITypeInfo  /*int*/  *pObjTypeInfo, SECA_EventArray /*out */ &events);

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
