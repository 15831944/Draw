///////////////////////////////////////////////////////////////////////////////
// MvcCommand.h : Declaration of CMvcCommand
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
// Description:  Declaration of MvcCommand class.
//

// @doc MvcCommand

#pragma once

#ifndef __MVCCOMMAND_H__
#define __MVCCOMMAND_H__

#include <Foundation\RefCount.h>
#include <Foundation\Patterns\SubjectObserver.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc CMvcCommand
//
//@class CMvcCommand |
// A CMvcCommand is an abstract base class that defines the interface for
// all command objects.  A command object is essentially a persistent form of
// a verb.  Graphical User Interfaces typically adhere to what is known
// as the "Object-Verb" paradigm, which simply means you select an object
// and then apply a verb to that object.  Fundamentally, each command
// object represents a verb and classes which you derive from MvcCommand
// define specific verbs as appropriate for your application.  Basically,
// you are expected to derive multiple command classes from this class and
// implement the Execute function such that it performs whatever function
// the derived command class encapsulates.  In MVC, the model defines
// a set of verbs, or command objects, that make sense within the triad.
// 
// The CMvcCommand class is central to the undo/redo architecture defined
// by MVC.  Typically, a controller will respond to user input by calling
// some operation defined by the model it observes.  That model operation
// should create a command object of the required type, log the command
// and execute it. Logging the commands prior to executing them creates
// a history buffer so that a record exist for undo/redo purposes.  This
// history buffer is maintained internal to the transaction model.
//
//@base public | IMessage

class FOUNDATION_API CMvcCommand : public CRefCountImpl<IMessage>
{
// Constructors/destructor
public:
	//@cmember,mfunc Construct an MVC command object
	//@@end
	/* Construct an MVC command object*/
	CMvcCommand()
	{
		m_bUndoable = TRUE;
	}

	//@cmember,mfunc Destroy an MVC command object
	//@@end
	/* Destroy an MVC command object*/
	virtual ~CMvcCommand()
	{}

// Attributes
protected:
	//@cmember
	/* Flag to indicate if command supports Unexecute*/
	BOOL m_bUndoable;

// Operations
public:

	//@cmember,mfunc Determines if this command can be undone
	//@@rdesc TRUE if command is undoable, otherwise FALSE
	//@@end
	/* Determines if this command can be undone*/
	virtual BOOL IsUndoable() const
	{
		return m_bUndoable;
	}

	//@cmember,mfunc BOOL  | CMvcCommand | SetUndoable | Sets if this command can be undone
	//@@parm BOOL | bUndoable | The state to be set.  TRUE indicates the command is undoable.
	//@@end
	/* Sets if this command can be undone*/
	virtual void SetUndoable(BOOL bUndoable)
	{
		m_bUndoable = bUndoable;
	}

	//@cmember,mfunc Execute this command
	//@@rdesc TRUE if successful, otherwise FALSE
	//@@comm
	// The action represented by this command object is executed.  You should
	// derive a class from MvcCommand and override this function, so the
	// command will actually do something. The default implentation simply returns
	// TRUE.
	//@@end
	/* Execute this command*/
	virtual BOOL Execute()
	{
		return TRUE;
	}

	//@cmember,mfunc Reverse the effects of this command
	//@@rdesc TRUE if successful, otherwise FALSE
	//@@comm
	// The action represented by this command object is reversed.
	//@@end
	/* Perform the opposite action of what the command represents*/
	virtual BOOL Unexecute()
	{
		return TRUE;
	}

	// GUID map implements QueryGuid method
	BEGIN_GUID_MAP(CMvcCommand)
		GUID_ENTRY(IMessage)
	END_GUID_MAP
};

//////////////////////////////////////////////////////////////////////////
// Message and command declaration macros
//

#ifndef MVC_NO_COMMAND_DECL_MACROS

#define MVC_DECLARE_COMMAND() \
	private: static const unsigned int m_nID; \
	public: virtual unsigned int GetTypeID() const { return m_nID; } \

#define MVC_IMPLEMENT_COMMAND(class_name, cmd_id) \
	const unsigned int class_name::m_nID = cmd_id; \

#define MVC_DECLARE_MESSAGE() \
	MVC_DECLARE_COMMAND() \

#define MVC_IMPLEMENT_MESSAGE(class_name, cmd_id) \
	MVC_IMPLEMENT_COMMAND(class_name, cmd_id) \

#endif //MVC_NO_COMMAND_DECL_MACROS

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MVCCOMMAND_H__
