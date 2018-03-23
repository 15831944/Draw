///////////////////////////////////////////////////////////////////////////////
// SplitWnd.h  : Declaration of SECSplitterWnd
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
// Author:       Mark Isham
// Description:  Declaration of SECSplitterWnd
//

#ifndef __SECSPLITTERWND_H
#define __SECSPLITTERWND_H

// Header Includes
#ifndef __SECSPLITTERBASE_H
#include "toolkit\layout\splitter.h"
#endif

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
// SECSplitterWnd

// This class is provided as-is mostly as a proof of concept for the 
// SECSplitterBase base class implementation. The functionality offered by 
// this class does not directly hook into the layout manager framework (see 
// the supported class 'SECLayoutNodeSplitter' for this functionality), 
// but rather is offered as a "beta level" implementation of a generic 
// CWnd-centric splitter class (unlike CSplitterWnd, which is much more 
// CView-centric). We welcome any feedback, positive or negative, but 
// please understand this class is considered beta level and thus unsupported.

class SECSplitterWnd : public SECSplitterBase
{
	TOOLKIT_DECLARE_DYNAMIC(SECSplitterWnd);

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECSplitterWnd();
	TOOLKIT_API virtual ~SECSplitterWnd();

	// Operations
	TOOLKIT_API virtual BOOL AddPane(USHORT nRow,USHORT nCol,CWnd* pWnd);
	TOOLKIT_API virtual BOOL RemovePane(USHORT nRow,USHORT nCol);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	// Override this with your own pane display logic
	TOOLKIT_API virtual void OnSetPanePositions(SECSplitterPaneInfo* pPaneInfo);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	CTypedPtrArray<CPtrArray,CWnd*> m_wndPanes;

	// Implementation member Functions

	//---------------------------------------------------------------------//
	// 						Message Map Declarations					   //
	//---------------------------------------------------------------------//

	// Generated message map functions
	//{{AFX_MSG(SECSplitterWnd)
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __SECSPLITTERWND_H__
