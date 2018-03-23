///////////////////////////////////////////////////////////////////////////////
// gxgmouse.h
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

#ifndef _GXGMOUSE_H_
#define _GXGMOUSE_H_

#ifndef _GXIMOUSE_H_
#include "gximouse.h"
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
// CGXGridMouseWheelPlugin window

class CGXGridMouseWheelPlugin : public CGXMouseWheelPlugin
{
// Construction
public:
	GRID_API CGXGridMouseWheelPlugin(CGXGridCore* pGrid);

// Attributes
public:
	CGXGridCore* m_pGrid;

// Operations
public:

// Overrides
	GRID_API virtual int OnIMouseGetZoom();
	GRID_API virtual void OnIMouseSetZoom(int nZoom);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXGridMouseWheelPlugin)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXGridMouseWheelPlugin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridMouseWheelPlugin)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXGridIntelliMousePlugin window

class CGXGridIntelliMousePlugin : public CGXIntelliMousePlugin
{
// Construction
public:
	GRID_API CGXGridIntelliMousePlugin(CGXGridCore* pGrid);

// Attributes
public:
	CGXGridCore* m_pGrid;

// Operations
public:

// Overrides
	GRID_API virtual int OnIMouseGetZoom();
	GRID_API virtual void OnIMouseSetZoom(int nZoom);
	GRID_API virtual void OnIMouseVScroll(UINT nSBCode, UINT nScroll);
	GRID_API virtual void OnIMouseHScroll(UINT nSBCode, UINT nScroll);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXGridIntelliMousePlugin)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXGridIntelliMousePlugin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridIntelliMousePlugin)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
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


#endif //_GXGMOUSE_H_

