///////////////////////////////////////////////////////////////////////////////
// SubjectObserver.h : Subject/observer interfaces.
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
// Author:       Jeff Boenig and Dean Hallman
// Description:  
//

#ifndef __COMPAT_SUBJECTOBSERVER_H__
#define __COMPAT_SUBJECTOBSERVER_H__

#include <unknwn.h>
#include "Foundation\Compatibility\Common\CmnGuids.h"

#ifndef __COMPAT_SECCOLLECT_H__
#include "Foundation\Compatibility\Common\Patterns\Collect.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

class __declspec(uuid("F0526983-E944-11d2-B412-006008AFE059"))
				IObserver;

//@doc IMessage 
//@mfunc void  | IMessage | GetTypeID  | The type ID of the message.  Used for safe typecasting
//@xref <c IMessage>

//@doc IMessage 
//@mfunc void  | IMessage | Sprint | Print a description of the message for logging purposes
//@parm CString& | strCmd | A string to receive the message text
//@xref <c IMessage>

//@doc IMessage
//@class Message interface.  Classes which implement this interface can be sent from subject
// to observer as a notification of change.
class __declspec(uuid("F0526982-E944-11d2-B412-006008AFE059"))
				IMessage : public IUnknown
{
public:
	//@cmember
	/* The type ID of the message.  Used for safe typecasting*/
	virtual unsigned int GetTypeID() const = 0;

	//@cmember
	/* Print a description of the message for logging purposes*/
	virtual void Sprint(CString& strCmd) = 0;
};

//@doc ISubject
//@mfunc void  | ISubject | AddObserver | Adds a observer to the list of dependents on this object.  When a change in state occurs, all observers are notified.
//@parm IObserver* | pObserver | The observer to add
//@xref <c ISubject>

//@doc ISubject
//@mfunc void  | ISubject | RemoveObserver | The dependent identified by the argument is removed from this objects list of dependents
//@parm IObserver* | pObserver | The observer to remove
//@xref <c ISubject>

//@doc ISubject
//@mfunc void  | ISubject | UpdateAllObservers | All objects dependent on this object are sent a notification indicating what aspect of this object has changed
//@parm IObserver* | pObserver | The observer that triggered the update
//@parm IMessage* | pMsg | The message to send to all observers
//@xref <c ISubject>

//@doc ISubject
//@class ISubject is an interface that can be mixed into any object through
// multiple inheritance.  An object that incorporates this interface can
// be observed by any object that incorporates the IObserver interface.
// All observers of a subject are notified of changes to the subject
// state via a change notification protocol.  This notification can be
// any object whose class mixes in the IMessage interface.
//
// NOTE: the ISubject interface implements the subject part of the
// Observer design pattern.  See the book "Design Patterns: Elements of
// reusable Object-oriented software."
class __declspec(uuid("F0526981-E944-11d2-B412-006008AFE059"))
				ISubject : public IUnknown
{
public:
	//@cmember
	/* Adds a observer to the list of dependents on this object.  When a change in state occurs, all observers are notified.*/
	virtual void AddObserver(IObserver* pObserver) = 0;

	//@cmember
	/* The dependent identified by the argument is removed from this objects list of dependents*/
	virtual void RemoveObserver(IObserver* pObserver) = 0;

	//@cmember
	/* All objects dependent on this object are sent a notification indicating what aspect of this object has changed*/
	virtual void UpdateAllObservers(IObserver* pObserver, IMessage* pMsg) = 0;
};


//@doc IObserver
//@mfunc void  | IObserver | OnUpdate | The function reacts to notifications of change on the subject it is observing
//@parm ISubject* | pSubject | The subject sending the update
//@parm IMessage* | pMsg | The message indicating what change has occurred
//@xref <c IObserver>

//@doc IObserver
//@class IObserver is an interface that can be mixed into any object through
// multiple inheritance.  An object that incorporates this interface can
// observe any object that incorporates the ISubject interface.
// All observers of a subject are notified of changes to the subject
// state via a change notification protocol.
//
// NOTE: the ISubject interface implements the subject part of the
// Observer design pattern.  See the book "Design Patterns: Elements of
// reusable Object-oriented software."
class FOUNDATION_API IObserver : public IUnknown
{
public:
	//@cmember
	/* The function reacts to notifications of change on the subject it is observing*/
	virtual void OnUpdate(ISubject* pSubject, IMessage* pMsg) = 0;
};

//
// Collections
//

typedef CCArray_T<IObserver*, IObserver*> ObserverArray;
typedef Iterator_T<IObserver*> ObserverIterator;

};  // end namespace rw

///////////////////////////////////////////////////////////////////////////

#endif  // __COMPAT_SUBJECTOBSERVER_H__
