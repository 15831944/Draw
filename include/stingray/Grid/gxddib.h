///////////////////////////////////////////////////////////////////////////////
// gxddib.h
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

#ifndef _GXDDIB_H_
#define _GXDDIB_H_

#if _MFC_VER >= 0x0400 

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif


class CGXDataDib : public CGXDIB 
{
public:
// constructor 
	GRID_API CGXDataDib();
	GRID_API virtual ~CGXDataDib();
	
	GRID_API static HANDLE AFXAPI Draw(CDC* pDC, const COleVariant& var, LPRECT lpRect, int nStretchFlags = none, 
		UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL, HANDLE hBitmap = NULL, BOOL bFree = FALSE);
	
	// locate the actual bitmap data in a buffer
	GRID_API static HANDLE AFXAPI LocateBitmap(const COleVariant& var, BOOL bIncludeFileHeader = FALSE);
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_MFC_VER >= 0x0400 

#endif //_GXDDIB_H_
