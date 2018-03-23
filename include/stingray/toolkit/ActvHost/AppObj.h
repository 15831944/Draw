////////////////////////////////////////////////////////////////////////////////
// AppObj.h
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
//     Update Log:
//
//        06.19.06  exported classes with TOOLKIT_API macro by csd
//

#ifndef __SEC_APP_OBJ_H
#define __SEC_APP_OBJ_H

#include "toolkit\ActvHost\FloatingDocTemplate.h"
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

/////////////////////////////////////////////////////////////////////////////
// SECAAppObj command target

//@doc SECAAppObj 
//@class Application object loadable from an ActiveScript script.
//@BASE public | CCmdTarget
//@xref <c SECAFormObj>
class SECAAppObj : public CCmdTarget
{
	TOOLKIT_DECLARE_DYNCREATE(SECAAppObj)

	TOOLKIT_API SECAAppObj();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAAppObj)
	public:
	TOOLKIT_API virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
	TOOLKIT_API void NotifyFrameClosed(CFrameWnd *pFrame);
protected:
	TOOLKIT_API virtual ~SECAAppObj();

	// Generated message map functions
	//{{AFX_MSG(SECAAppObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(SECAAppObj)

	//@cmember
	/* Load a form */
	TOOLKIT_API afx_msg short OpenForm(LPCTSTR strFormPathName, BOOL fUseExisting, BOOL fOpenInEditMode);

	//@cmember
	/* Create a new form*/
	TOOLKIT_API afx_msg short NewForm();

	//@cmember
	/* Get the dispatch of an existing form matching a specific name.*/
	TOOLKIT_API afx_msg LPDISPATCH FormByName(LPCTSTR strFormName);

	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	// Scriptable window information
	TOOLKIT_API SECAFloatDocTemplate* GetFloatingDocTemplate();

	//running window state...
	CTypedPtrArray<CObArray, CFrameWnd *> m_arrScriptFrames;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SEC_APP_OBJ_H


/////////////////////////////////////////////////////////////////////////////

