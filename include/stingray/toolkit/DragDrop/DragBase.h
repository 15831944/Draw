///////////////////////////////////////////////////////////////////////////////
// DragBase.h
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
// This source code is only intended as a supplement to
// the Objective Toolkit Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Toolkit product.
//
// Authors:      Mark Isham
// Description:  Declaration of SEC Drag-Drop Base framework
//

#ifndef __SEC_DRAG_DROP_BASE_H__
#define __SEC_DRAG_DROP_BASE_H__

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
// ISECDragDropFeature

// Drag-Drop feature interface.
// This interface serves as the base for specific drag drop utilizations.
// For example, a toolbar button drag drop feature could be one derived
// implementation. Docking windows could be another.

class ISECDragDropFeature 
{
public:
	virtual BOOL TestDragStartPoint(UINT nKeyFlags,const CPoint& ptScreenDragTest)=0;
	virtual BOOL InitiateDrag(UINT nKeyFlags,const CPoint& ptScreenDragStart)=0;
	virtual BOOL TrackDrag(UINT nKeyFlags,const CPoint& ptScreenMove)=0;
	virtual BOOL EndDrag(UINT nKeyFlags,const CPoint& ptScreenDragEnd,BOOL bDoDrop)=0;
	virtual BOOL DragDropToggleEvent(UINT nKeyFlags,const CPoint& ptScreenEvent)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECDragDropTaskBase

// Drag-Drop framework base.
// This class serves as the base for specific drag-drop implementations.
// Examples: one implementation for OLE based drag and drop. Local message
// loop based drag/drop could be another.
// This base does little more than delegate particular events (fired by
// the derived implementations) to the aggregated drag/drop feature
// (similar to the "Bridge" Design Pattern).
// This separation of the drag/drop implementation from the drag/drop
// utilization allows us to very the actual implementation of drag/drop
// (local msg loop, OLE, or other) completely independently of the
// utilization of this mechanism (toolbar button drag/drop, docking windows,
// splitter movement, etc.)

class SECDragDropTaskBase 
{
public:
	// Construnction/Initialization
	inline SECDragDropTaskBase() {}
	virtual ~SECDragDropTaskBase() {}

	// Get/Set. Avoid using Get if possible, as this implementation
	// is really intended to be used via the virtual functions!
	inline ISECDragDropFeature* GetDragDropFeature()				{ return m_pDragDropFeature; }
	inline void SetDragDropFeature(ISECDragDropFeature* pFeature)  { m_pDragDropFeature=pFeature; }

	// Drag/Drop events
	virtual BOOL TestDragStartPoint(UINT nKeyFlags,const CPoint& ptScreenDragTest) 
			{ ASSERT(m_pDragDropFeature); 
			  return m_pDragDropFeature->TestDragStartPoint(nKeyFlags,ptScreenDragTest); }
	virtual BOOL InitiateDrag(UINT nKeyFlags,const CPoint& ptScreenDragStart)
			{ ASSERT(m_pDragDropFeature); 
			  return m_pDragDropFeature->InitiateDrag(nKeyFlags,ptScreenDragStart); }
	virtual BOOL TrackDrag(UINT nKeyFlags,const CPoint& ptScreenNew) 
			{ ASSERT(m_pDragDropFeature); 
			  return m_pDragDropFeature->TrackDrag(nKeyFlags,ptScreenNew); }
	virtual BOOL EndDrag(UINT nKeyFlags,const CPoint& ptScreenDragEnd,BOOL bDoDrop) 
			{ ASSERT(m_pDragDropFeature); 
			  return m_pDragDropFeature->EndDrag(nKeyFlags,ptScreenDragEnd,bDoDrop); }
	virtual BOOL DragDropToggleEvent(UINT nKeyFlags,const CPoint& ptScreenEvent) 
			{ ASSERT(m_pDragDropFeature); 
			  return m_pDragDropFeature->DragDropToggleEvent(nKeyFlags,ptScreenEvent); }


private:
	// Derived classes should not directly access to the aggregate 
	// feature, use the virtual member functions instead.
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

#endif	//__SEC_DRAG_DROP_BASE_H__
