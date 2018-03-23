///////////////////////////////////////////////////////////////////////////////
// SRGRectTracker.h
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

#ifndef __SRGRECTTRACKER_H__
#define __SRGRECTTRACKER_H__

#include <afxext.h>
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

/////////////////////////////
// AutoDuck tag block block for SRGRectTracker 

//$head The Chart Wizard
//$level 1

// adinsert AutoDuck insertion point for SRGRectTracker 
//@doc SRGRectTracker 
//@class Extention class of CRectTracker, this class added a new CWnd member
// whenever the rect changed size it send out a WM_TRACKINGRECTCHANGED message
// to the CWnd member, when it adjust its rect it also send out a WM_ADJUSTTRACKINGRECT
// message to CWnd member so that the CWnd member get a chance to do something
// if it choose to.
class SRGRectTracker : public CRectTracker  
{
public:
	//@cmember
	/* Send a WM_ADJUSTTRACKINGRECT message to its parent before call*/
	// the base class AdjustRect function
	CHART_API virtual void AdjustRect( int nHandle, LPRECT lpRect );
	//@cmember
	/* Send a WM_TRACKINGRECTCHANGED message to its parent before call*/
	// the base class OnChangedRect function
	CHART_API virtual void OnChangedRect(const CRect & rectOld);
	CHART_API SRGRectTracker(CWnd* pParent = NULL);
	CHART_API virtual ~SRGRectTracker();

	CWnd* m_pParent;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SRGRECTTRACKER_H__

