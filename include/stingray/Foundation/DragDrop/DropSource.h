///////////////////////////////////////////////////////////////////////////////
// DropSource.h
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

#pragma once

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
// class IDropSourceImpl
/////////////////////////////
// AutoDuck tag block for IDropSourceImpl
//
//@doc IDropSourceImpl
//
//@mfunc int | IDropSourceImpl| IDropSourceImpl | Constructor
//@comm Constructor performs initialization
//
//@mfunc ULONG | IDropSourceImpl| AddRef | Place a reference count on the object
//@rdesc Returns the current reference count, but you're not supposed to care.
//@comm AddRef is a member of IUnknown 
//
//@mfunc ULONG | IDropSourceImpl| Release | Remove a reference count on the object
//@rdesc Returns the current reference count, but you're not supposed to care.
//@comm Release is a member of IUnknown 
//
//@mfunc HRESULT | IDropSourceImpl| QueryInterface | Get a new interface from the object
//@rdesc Returns S_OK if succeeded, otherwise, returns E_NOINTERFACE
//@parm REFIID | riid | Interface ID to use 
//@parm void** | ppv | place to put the pointer
//@comm QueryInterface is the standard means by which client code acquires
// new interfaces to a COM object. IDropSourceImpl supports IUnknown and IDropSource.
//
//@mfunc HRESULT | IDropSourceImpl| QueryContinueDrag | Answers the question of whether the dragging should continue
//@rdesc Returns S_OK if dragging should continue. Returns DRAGDROP_S_CANCELif the dragging should
// stop. Returns DRAGDROP_S_DROP if it's time to drop the data. 
//@parm BOOL | bEscapePressed | Flag indicating whether or not escape is pressed. 
//@parm DWORD | dwKeyState | State of the keyboard (i.e. control key, alt key, escape key, etc.)
//@comm QueryContinueDrag default to stopping dragging and dropping when bEscapePressed
//  parameter is TRUE. Also defaults to the left mouse button indicating a drop.
//
//@mfunc HRESULT | IDropSourceImpl| GiveFeedback | Indicates which cursors Windows should load. 
//@rdesc Returns DRAGDROP_S_USEDEFAULTCURSORS
//@parm DWORD | dwEffect | Not used
//@comm Initiate Which cursors to use
//
//
//@class IDropSourceImpl | This class is provided as a standard way 
//
// Member functions include:
//  <mf IDropSourceImpl::IDropSourceImpl>, 
//  <mf IDropSourceImpl::AddRef>, 
//  <mf IDropSourceImpl::Release>, 
//  <mf IDropSourceImpl::QueryInterface>, 
//  <mf IDropSourceImpl::QueryContinueDrag>, and 
//  <mf IDropSourceImpl::GiveFeedback>, 
//
//@base public | IDropSource
//
class FOUNDATION_API IDropSourceImpl : public IDropSource 
{
	LONG m_cRef;
	DWORD m_dwButtonCancel;
	DWORD m_dwButtonDrop;
	bool m_bDragStarted;

public:
	//@cmember
	/* Init initializes the drag source object */
	void Init()
	{
		m_cRef = 0;
		m_dwButtonCancel = 0;
		m_dwButtonDrop = 0;
		m_bDragStarted = 0;
	}

	//@cmember
	/* Constructor initializes the drag source object by calling Init */
	IDropSourceImpl()
	{
		Init();
	}

	~IDropSourceImpl()
	{}

	// IDropTarget members:

	//@cmember
	/* AddRef increments the reference count */
	STDMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&m_cRef);
	}

	//@cmember
	/* Release decrements the reference count */
	STDMETHODIMP_(ULONG) Release()
	{
		if(InterlockedDecrement(&m_cRef) == 0) {
			return 0;
		} 
		else {
			return m_cRef;
		}
	}

	//@cmember
	/* Get New interfaces. This object supports IUnknown and IDropSource */
	STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
	{
		*ppv = NULL;
		if(riid == IID_IUnknown || riid == IID_IDropSource) {
			*ppv = static_cast<IDropSource*>(this);
		}

		if (*ppv) {
			((IUnknown*)(*ppv))->AddRef();
			return S_OK;
		} 
		else {
			return E_NOINTERFACE;
		}
	}

	//@cmember
	/* Answers the question of whether the system should continue the drag drop operation */
	STDMETHODIMP QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState)
	{
		if(bEscapePressed) {
			return DRAGDROP_S_CANCEL;
		} 
		else if (!(dwKeyState & MK_LBUTTON)) {
			return DRAGDROP_S_DROP;
		}

		return S_OK;		
	}

	//@cmember
	/* Tells system which cursors to used */
	STDMETHODIMP GiveFeedback(DWORD)
	{
		return DRAGDROP_S_USEDEFAULTCURSORS;
	}


}; // IDropSourceImpl


};	// namespace stingray::foundation
};	// namespace stingray

