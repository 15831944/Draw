///////////////////////////////////////////////////////////////////////////////
// PropList.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//


#ifndef __PROPLIST_H_
#define __PROPLIST_H_

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

#ifndef SECA_OBJTYPE_DEF
#define SECA_OBJTYPE_DEF
typedef enum {
    TYPE_FUNCTION = 0,
    TYPE_PROPERTY = 1,
    TYPE_CONSTANT = 2,
    TYPE_PARAMETER = 3
} SECA_OBJTYPE;
#endif

struct SECA_EnumType
{
	CString		strItemName;
	long		lValue;
};

#define SECA_ENUMARRAY CArray < SECA_EnumType, SECA_EnumType& > 

class TOOLKIT_API SECABrowseProp
{
public:

	SECABrowseProp() {}
	SECABrowseProp & operator= (const SECABrowseProp &src);
	SECABrowseProp(const SECABrowseProp &copy);

	CString strName;

	VARTYPE vartype; //paramater's type

	SECA_OBJTYPE	objType; //either property or method

	MEMBERID memid;

	//for user defined values
	CString		strUserDefined;
	SECA_ENUMARRAY	enumArray; //array of possible values
};

#define PROPARRAY CArray < SECABrowseProp, SECABrowseProp& > 

struct  ISCollection;

TOOLKIT_API HRESULT EnumProperties( LPDISPATCH pItemDisp, 
					                ISCollection *pCollection,   
					                PROPARRAY &props);

TOOLKIT_API HRESULT EnumMethods( LPDISPATCH pItemDisp, 
					             ISCollection *pCollection,   
					             PROPARRAY &props);

TOOLKIT_API HRESULT BuildPropertyList( LPDISPATCH pDisp,  
						               PROPARRAY &props,
						               ITypeInfo	*pObjTypeInfo = NULL);

TOOLKIT_API HRESULT LoadConstants( LPDISPATCH pDisp,  
					               const CString &strUserConstName,
					               SECA_ENUMARRAY &enumArray );

// eliminate dupes
TOOLKIT_API BOOL NotIn( const PROPARRAY &props, const SECABrowseProp &bp );

//supported types

enum { 	st_NotSupported,		//not displayed in the browser
		st_Supported, 
		st_StockProperty, 
		st_StockPropertySimple, //can be handled the same way as st_Supported
		st_NoSts };

TOOLKIT_API int IsSupportedPropertyType( const CString &strName, VARTYPE vartype );

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// __PROPLIST_H_
