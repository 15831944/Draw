///////////////////////////////////////////////////////////////////////////////
// MvcDefSbjObs.h : Declaration of MvcDefSubject, MvcDefObserver
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
// Description:  Declaration of MvcDefSubject, MvcDefObserver
//

//@doc MvcDefSbjObs

#pragma once

#ifndef __MFC_MVCDEFSBJOBS_H__
#define __MFC_MVCDEFSBJOBS_H__

// Includes

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

//
// Note, to use the diagnostics below, define SEC_MVC_SUBJECT_OBSERVER_DIAG 
// in the OT stdafx.h, then rebuild the library
//

#ifdef SEC_MVC_SUBJECT_OBSERVER_DIAG
class MvcSubjectObserverDiagnostic;
#endif

#include <Foundation\MVC\MFC\MvcIfcs.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//
// MvcDefSubject
//
//@class 
// Default implementation of IMvcSubject interface
//@base public | IMvcSubject
//


class MvcDefSubject : public IMvcSubject
{
public:
	typedef CCArray_T<IMvcObserver*, IMvcObserver*> ObserverSet;

// Construction/Destruction
public:
	FOUNDATION_API MvcDefSubject();
	FOUNDATION_API virtual ~MvcDefSubject();

// Operations

	//@cmember
	/* Adds a observer to the list of dependents on this object.  When a change in state occurs, all observers are notified.*/
	FOUNDATION_API virtual void AddObserver(IMvcObserver* pObserver);

	//@cmember
	/* The dependent identified by the argument is removed from this objects list of dependents*/
	FOUNDATION_API virtual void RemoveObserver(IMvcObserver* pObserver);

	//@cmember
	/* All objects dependent on this object are sent a notification indicating what aspect of this object has changed*/
	FOUNDATION_API virtual void UpdateAllObservers(IMvcObserver* pObserver = NULL, IMvcMessage* pMsg = NULL);

	//@cmember
	/* Determine if the observer passed in is currently configured for this subject */
	FOUNDATION_API virtual BOOL HasObserver(IMvcObserver* pObserver);

	/////////
	// IUnknown interface

	//@cmember
	/* Retrieve a pointer to an interface supported by this object. */
	FOUNDATION_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

	//@cmember
	/* Add a reference to this object. */
	FOUNDATION_API virtual ULONG STDMETHODCALLTYPE AddRef();

	//@cmember
	/* Release a reference to this object. */
	FOUNDATION_API virtual ULONG STDMETHODCALLTYPE Release();

// Attributes
protected:
	ObserverSet m_setObservers;
	ObserverSet m_setPendingAddObservers;
	ObserverSet m_setPendingRemoveObservers;
	BOOL m_bUpdateInProgress;

// Subject-observer diagnostics
#ifdef SEC_MVC_SUBJECT_OBSERVER_DIAG
public:
	static MvcSubjectObserverDiagnostic* GetSbjObsDiag();
	static void SetReportUpdateViolations(bool bReport);
	static int GetObserverCount(ObserverSet& setObservers,IMvcObserver* pObserver);
protected:
	static MvcSubjectObserverDiagnostic* m_pSbjObsDiag;
	static int m_nSbjObsDiagRefCount;
	static bool sm_bReportUpdateViolations;
#endif

};

///////////////////////////////////////////////////////////////////////////
//
// MvcDefObserver

//@doc MvcDefObserver
//@mfunc  void | MvcDefObserver | OnUpdate | The function reacts to
// notifications of change on the subject it is observing.
//@rdesc void
//@parm IMvcSubject* | pSubject | Pointer to subject that was updated.
//@parm IMvcMessage* | pMsg | Pointer to message that describes the update.

//@class 
// Default implementation of IMvcObserver interface
//@base public | IMvcObserver
//

 
class FOUNDATION_API MvcDefObserver : public IMvcObserver
{
public:
	MvcDefObserver();
	virtual ~MvcDefObserver();

	//@cmember
	/* The function reacts to notifications of change on the subject it is observing*/
	virtual void OnUpdate(IMvcSubject* pSubject, IMvcMessage* pMsg)=0;
	
	/////////
	// IUnknown interface

	//@cmember
	/* Retrieve a pointer to an interface supported by this object. */
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

	//@cmember
	/* Add a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE AddRef();

	//@cmember
	/* Release a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE Release();
};

///////////////////////////////////////////////////////////////////////////
//
// MvcDefMsg
//

 
class FOUNDATION_API MvcDefMsg : public IMvcMessage
{
public:
	MvcDefMsg();
	virtual ~MvcDefMsg();

	virtual unsigned int GetTypeID() const = 0;
	virtual void Sprint(CString& strCmd) = 0;
	
	/////////
	// IUnknown interface

	//@cmember
	/* Retrieve a pointer to an interface supported by this object. */
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

	//@cmember
	/* Add a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE AddRef();

	//@cmember
	/* Release a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE Release();
};

///////////////////////////////////////////////////////////////////////////
//
// MvcSubjectObserverDiagnostic
//

#ifdef SEC_MVC_SUBJECT_OBSERVER_DIAG	// diagnostics only!

// Diagnostic aid in sniffing out dangling subject-observer linkages,
// for use with MvcDefSubject, MvcDefObserver
class MvcSubjectObserverDiagnostic {
public:
	FOUNDATION_API MvcSubjectObserverDiagnostic();
	FOUNDATION_API virtual ~MvcSubjectObserverDiagnostic();

	// Error-Reporting options, defaults to "trace"
	enum ErrorLevel { err_trace, err_assert, err_msgbox };
	static void SetErrorLevel(ErrorLevel level);

	// Call these functions whenever a new subject is constructed/destructed
	FOUNDATION_API virtual BOOL RegisterNewSubject(MvcDefSubject* pSubject);
	FOUNDATION_API virtual BOOL DeregisterSubject(MvcDefSubject* pSubject);
	
	// Call this function to verify a particular observer is no longer
	// referenced by any of the registered subjects. Useful for sniffing
	// out bogus dangling observer references.
	FOUNDATION_API virtual BOOL VerifyDetachedObserver(IMvcObserver* pObserver);

	// Log an error message for our subject-observer diagnostics
	FOUNDATION_API virtual void ReportError(LPCTSTR lpszErr);

protected:
	CTypedPtrList<CPtrList,MvcDefSubject*> m_listSubjects;
	static ErrorLevel m_errLevel;
};

#endif // SEC_MVC_SUBJECT_OBSERVER_DIAG
///////////////////////////////////////////////////////////////////////////
};  // namespace stingray::foundation
};  // namespace stingray

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // #ifndef __MFC_MVCDEFSBJOBS_H__
