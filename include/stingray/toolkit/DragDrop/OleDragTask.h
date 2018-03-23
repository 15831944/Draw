///////////////////////////////////////////////////////////////////////////////
// OleDragTask.h
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
// Description:  Declaration of SECOleDragDropTask_T 
//

#ifndef __SEC_OLE_DRAG_DROP_TASK_H__
#define __SEC_OLE_DRAG_DROP_TASK_H__

#ifdef WIN32

// Header Includes
#include <afxole.h>
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
// SECOleDragDropTask_T

// Implementation of SECOleDragDropTask that provides drag/drop
// functionality by virtue of mouse capture and a local message loop.

// Templatized base class passed in should be SECWndListener derived!

template <class ListenerBaseClass>
class SECOleDragDropTask_T : public SECStartDragCore_T<ListenerBaseClass>, 
							               public SECDragDropTaskBase
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	inline SECOleDragDropTask_T() {}
	inline virtual ~SECOleDragDropTask_T() {}

protected:
	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//

	TOOLKIT_API virtual BOOL TestDragStartPoint(UINT nKeyFlags,const CPoint& ptScreenDragTest);
	TOOLKIT_API virtual BOOL OnStartDragDrop(UINT nKeyFlags,
								                           const CPoint& ptScreenLButtonDown,
								                           const CPoint& ptScreenMouseMove);
	TOOLKIT_API virtual BOOL OnDragDropToggleEvent(UINT nKeyFlags,const CPoint& ptScreenEvent);
};

typedef SECOleDragDropTask_T<stingray::foundation::SECWndListener> SECOleDragDropTask;

/////////////////////////////////////////////////////////////////////////////
// SECOleDragSource

class SECOleDropSource : public COleDropSource 
{
public:
	TOOLKIT_API SECOleDropSource(SECDragDropTaskBase* pDragTask);
	inline virtual ~SECOleDropSource() {}

	// overrides
	TOOLKIT_API virtual SCODE QueryContinueDrag( BOOL bEscapePressed, DWORD dwKeyState );

protected:
	SECDragDropTaskBase* m_pDragTask;
};

/////////////////////////////////////////////////////////////////////////////
// SECOleDropTarget

class SECOleDropTarget : public COleDropTarget
{
public:

	// Initialization/Destruction
	TOOLKIT_API SECOleDropTarget();
	TOOLKIT_API virtual ~SECOleDropTarget();

	// Get/Set the associated drag/drop feature for this adjunct to
	// SECOleDragDropTask_T (a SECDragDropTaskBase that uses a 
	// ISECDragDropFeature object).
	inline void SetDragDropFeature(ISECDragDropFeature* pFeature)	{ m_pDragDropFeature=pFeature; }
	inline ISECDragDropFeature* GetDragDropFeature() 				{ return m_pDragDropFeature; }

	// Overrides
	TOOLKIT_API virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, 
									                           DWORD dwKeyState, CPoint point );
protected:

	// Implementation Member Variables
	ISECDragDropFeature* m_pDragDropFeature;
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

#endif  //__SEC_OLE_DRAG_DROP_TASK_H__
