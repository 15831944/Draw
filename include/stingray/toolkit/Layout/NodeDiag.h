///////////////////////////////////////////////////////////////////////////////
// NodeDiag.h : Layout Node Debug Diagnostic Routines
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
// Description:  Layout Node Debug Diagnostic Routines
//

#ifndef __SEC_LAYOUT_NODE_DIAGNOSTIC_ROUTINES__
#define __SEC_LAYOUT_NODE_DIAGNOSTIC_ROUTINES__

// Utility Macro for node dump
#ifdef SECLAYOUTNODE_EXTENDED_DIAGNOSTICS
#define SEC_NODE_DUMP(PNODE) { SECLNDiagnostics diag; diag.DumpNodeTree(PNODE); } 
#else
#define SEC_NODE_DUMP(PNODE)
#endif

// All debug routines in this file should be considered "Private"
// and are subject to change in future versions of Objective Toolkit.

#ifdef _DEBUG
#ifdef SECLAYOUTNODE_EXTENDED_DIAGNOSTICS

// Header Includes
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
// SECLNDiagnostics

class SECLNDiagnostics 
{
public:
	inline SECLNDiagnostics() {}
	virtual ~SECLNDiagnostics() {}

	TOOLKIT_API virtual BOOL DumpNodeTree(SECLayoutNode* pRootNode);

protected:
	TOOLKIT_API virtual void DumpNodeTreeHelper(SECLayoutNode* pParent,CString strPreface);
	TOOLKIT_API virtual void DumpNodeInfo(SECLayoutNode* pNode,SECLayoutNode* pParent);
	TOOLKIT_API virtual void DumpDynGridNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual void DumpPreorderTraversal(SECLayoutNode* pRootNode);
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

#endif // SECLAYOUTNODE_EXTENDED_DIAGNOSTICS
#endif // _DEBUG

#endif //__SEC_LAYOUT_NODE_DIAGNOSTIC_ROUTINES__
