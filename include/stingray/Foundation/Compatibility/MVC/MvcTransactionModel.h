///////////////////////////////////////////////////////////////////////////////
// MvcTransactionModel.h : Declaration of MvcTransactionModel
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
// Description:  Declaration of MvcTransactionModel class.
//

//@doc MvcTransactionModel

#ifndef __COMPAT_MVCTRANSACTIONMODEL_H__
#define __COMPAT_MVCTRANSACTIONMODEL_H__

// Includes

#ifndef __COMPAT_MVCCOMMAND_H__
#include "Foundation\Compatibility\MVC\MvcCommand.h"
#endif

#ifndef __COMPAT_MVCMODEL_H__
#include "Foundation\Compatibility\MVC\MvcModel.h"
#endif

#include <StingrayExportDefs.h>

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _MVCDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    MVC_DATAEXT
#endif //_MVCDLL

#ifndef MVC_HISTORY_DEPTH
#define MVC_HISTORY_DEPTH	256
#endif

/////////////////////////////////////////////////////////////////////////////////
//
// MvcTransactionModel
//

//@doc MvcTransactionModel
//@mdata CCStack_T | MvcTransactionModel | m_undoStack | 	Stack of command actions that can be undone.
//@xref <c MvcTransactionModel>

//@doc MvcTransactionModel
//@mdata CCStack_T | MvcTransactionModel | m_redoStack | Stack of command actions that can be redone.
//@xref <c MvcTransactionModel>


//@class
// A transaction model records all commands that have occured
// within an application and is central to the undo/redo, record/playback
// and event logging functionality.  To record a command, the controller
// simply has to call the Log member passing a pointer to the
// MvcCommand object.  Later, the transaction model can undo the logged
// commands.
//
//@base public | MvcModel

class FOUNDATION_API MvcTransactionModel : public MvcModel
{
public:
	//@cmember
	/* Constructor*/
	MvcTransactionModel();

	//@cmember
	/* Destructor*/
	virtual ~MvcTransactionModel();

public:

	//@cmember
	/* Reset the state of the transaction model to its initial state*/
	virtual void Reset();

	//@cmember
	/* Tests whether the transaction model has stored new commands since last save*/
	virtual BOOL IsModified() const;

	//@cmember
	/* Records the specified command for later undo or event logging*/
	virtual BOOL Log(MvcCommand* pCmd);

	//@cmember
	/* Execute and log a command*/
	virtual BOOL Do(MvcCommand* pCmd);

	//@cmember
	/* Undo a command*/
	virtual MvcCommand* Undo();

	//@cmember
	/* Redo a command*/
	virtual MvcCommand* Redo();

	//@cmember
	/* Get the command that will be reversed next time Undo is called*/
	MvcCommand* PeekUndo();

	//@cmember
	/* Get the Undo command with index */
	MvcCommand* PeekUndo(int);

	//@cmember
	/* Get the command that will be execute next time Redo is called*/
	MvcCommand* PeekRedo();

	//@cmember
	/* Get the Redo command with index */
	MvcCommand* PeekRedo(int);

	//@cmember
	/* Set the number of commands that can be stored by the transaction model*/
	void SetHistorySize(int m_nHistorySize);

	//@cmember
	/* Get the Undo commands count */
	//int GetUndoCommandsCount() const;
	SEC_INT GetUndoCommandsCount() const;

	//@cmember
	/* Get the redo commands count */
	//int GetRedoCommandsCount() const;
	SEC_INT GetRedoCommandsCount() const;

protected:

	//@cmember
	/* Stack of command actions that can be undone.*/
	CCStack_T<MvcCommand*, MvcCommand*> m_undoStack;

	//@cmember
	/* Stack of command actions that can be redone.*/
	CCStack_T<MvcCommand*, MvcCommand*> m_redoStack;
};

//@doc MvcTransactionModel
//@mfunc Get the command that will be reversed next time Undo is called
//@rdesc Pointer to previous command in buffer
inline MvcCommand* MvcTransactionModel::PeekUndo()
{
	return m_undoStack.Peek();
}

//@doc MvcTransactionModel
//@mfunc Get the command that will be execute next time Redo is called
//@rdesc Pointer to next command in undo buffer
inline MvcCommand* MvcTransactionModel::PeekRedo()
{
	return m_redoStack.Peek();
}

//@doc MvcTransactionModel
//@mfunc Get the Undo command with specified index
//@rdesc Pointer to previous command in buffer
inline MvcCommand* MvcTransactionModel::PeekUndo(int nIndex)
{
	return (nIndex >= 0 && nIndex < m_undoStack.GetElementCount()) ? m_undoStack.GetElementAt(nIndex) : NULL;
}

//@doc MvcTransactionModel
//@mfunc Get the Redo command with specified index
//@rdesc Pointer to next command in undo buffer
inline MvcCommand* MvcTransactionModel::PeekRedo(int nIndex)
{
	return (nIndex >= 0 && nIndex < m_redoStack.GetElementCount()) ? m_redoStack.GetElementAt(nIndex) : NULL;
}

//@doc MvcTransactionModel
//@mfunc Get the Undo commands count
//@rdesc Commands count in Undo stack
//inline int MvcTransactionModel::GetUndoCommandsCount() const
inline SEC_INT MvcTransactionModel::GetUndoCommandsCount() const
{
	return m_undoStack.GetElementCount();
}

//@doc MvcTransactionModel
//@mfunc Get the Redo commands count
//@rdesc Commands count in Redo stack
//inline int MvcTransactionModel::GetRedoCommandsCount() const
inline SEC_INT MvcTransactionModel::GetRedoCommandsCount() const
{
	return m_redoStack.GetElementCount();
}

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif __COMPAT_MVCTRANSACTIONMODEL_H__

