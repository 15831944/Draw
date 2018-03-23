///////////////////////////////////////////////////////////////////////////////
// UndoNode.h : Declaration of basic Layout Mgr Undo functionality.
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
// Authors:      Mark Isham
// Description:  Declaration of basic Layout Mgr Undo functionality.
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//
// Provides very simply undo/redo functionality of basic layout mgr
// operations. Not intended to be the end all, be all undo architecture,
// but rather an isolated solution to a basic problem (esp. useful for
// the docking extensions of the layout mgr, but can still be used
// in a generic fashion).

#ifndef __SEC_LAYOUT_MGR_UNDO_FUNCTION_H__
#define __SEC_LAYOUT_MGR_UNDO_FUNCTION_H__

#ifdef WIN32

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
// ISECUndoableNode

// Interface for limited layout node undo/redo function.

class TOOLKIT_API ISECUndoableNode 
{
public:
	virtual ~ISECUndoableNode() {}
	virtual ISECUndoableNode* QueryOptimalUndoNode()=0;
	virtual int UndoableRemoveLayoutNode(SECLayoutNode* pNodeToRemove)=0;
	virtual int RestoreLastRemoveLayoutNode()=0;
	virtual int RestoreRemoveLayoutNode(SECLayoutNode* pNode)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECDefUndoableNode

// Default implementation of ISECUndoableNode. Must be used as a mixin
// class to a SECLayoutNode derived object.

class SECDefUndoableNode : public ISECUndoableNode 
{
public:
	TOOLKIT_API SECDefUndoableNode();
	virtual ~SECDefUndoableNode() {}
	virtual ISECUndoableNode* QueryOptimalUndoNode() { return this; }
	TOOLKIT_API virtual int UndoableRemoveLayoutNode(SECLayoutNode* pNodeToRemove);
	TOOLKIT_API virtual int RestoreLastRemoveLayoutNode();
	TOOLKIT_API virtual int RestoreRemoveLayoutNode(SECLayoutNode* pNode);

protected:
	SECLayoutNode* m_pNodeRemoved,*m_pNodeRestoreRemoveInsertAfter;
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

#endif	// WIN32

#endif	//__SEC_LAYOUT_MGR_UNDO_FUNCTION_H__
