///////////////////////////////////////////////////////////////////////////////
// gxfctry.h : Interface of CGXControlFactory 
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
// Author: Stefan Hoenig
//

#ifndef _GXFCTRY_H_
#define _GXFCTRY_H_

#ifndef _GXABSTR_H_
#include "gxabstr.h"
#endif

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

/////////////////////////////////////////////////////////////////////////////
// Control Factory

// default implementation (knows all control classes and will
// therefore force your application to be linked with all control classes)

class CGXControlFactory: public CGXAbstractControlFactory
{
public:
	GRID_API virtual CGXControl* CreateControl(UINT nID, CGXGridCore* pGrid);
	GRID_API virtual void RegisterAllControls(CGXStylesMap* pStylesMap);
	GRID_API virtual void RegisterAllUserAttributes(CGXStylesMap* pStylesMap);
	GRID_API virtual void InitializeGridComponents(CGXGridCore* pGrid);
	GRID_API virtual void InitializeApplicationComponents();
	GRID_API virtual void RegisterWndClasses(HINSTANCE hResource);
	GRID_API virtual void UnregisterWndClasses(HINSTANCE hResource);
};


/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GXFCTRY_H_
