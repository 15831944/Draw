///////////////////////////////////////////////////////////////////////////////
// MvcModel.h : Declaration of MvcModel
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
// Description:  Declaration of MvcModel interface.
//

//@doc MvcModel

#ifndef __COMPAT_MVCMODEL_H__
#define __COMPAT_MVCMODEL_H__

// Includes
#ifndef __COMPAT_MVCIFCS_H__
#include <Foundation\Compatibility\MVC\MvcIfcs.h>
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

///////////////////////////////////////////////////////////////////////////
//
// MvcModel
//
//@class
// A model is a kind of subject that serves as a base class for your
// application-specific models.  There are generally two types
// of models: system-models and presentation-models.  This distinction is
// purely conceptual.  System-models are models that simulate or model some
// real world process or object.  The system-model, in this case, is somewhat
// like a proxy or stand-in for the real thing.  An presentation model is
// a model that represents application or presentation data and functionality.  
//
//@base public | IMvcModel
//

class FOUNDATION_API MvcModel : public IMvcModel
{
public:
	typedef CCArray_T<IMvcObserver*, IMvcObserver*> ObserverSet;

// Construction/Destruction
public:
	MvcModel();
	virtual ~MvcModel();

	// IMvcModel interface

	//@cmember
	/* Tests whether the model has been modified*/
	virtual BOOL IsModified() const;

	// ISubject interface

	//@cmember
	/* Adds a observer to the list of dependents on this object.  When a change in state occurs, all observers are notified.*/
	virtual void AddObserver(IMvcObserver* pObserver);

	//@cmember
	/* The dependent identified by the argument is removed from this objects list of dependents*/
	virtual void RemoveObserver(IMvcObserver* pObserver);

	//@cmember
	/* All objects dependent on this object are sent a notification indicating what aspect of this object has changed*/
	virtual void UpdateAllObservers(IMvcObserver* pObserver = NULL, IMvcMessage* pMsg = NULL);

	//@cmember
	/* Reset the state of the model to its initial state*/
	virtual void Reset();

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

// Attributes
protected:
	ObserverSet m_setObservers;
};

///////////////////////////////////////////////////////////////////////////

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // __COMPAT_MVCMODEL_H__

