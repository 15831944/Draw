///////////////////////////////////////////////////////////////////////////////
// SelTracker.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//


#ifndef _SEL_TRACKER_H
#define _SEL_TRACKER_H

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

class TOOLKIT_API SECASelTracker : public CRectTracker
{
public:
	SECASelTracker(SECASelection &sel, SECACtrlItem *pOrigItem, SECScriptHostView *pView) : m_selection(sel),  
																							m_pView(pView), 
																							m_fInitilized(FALSE), 
																							m_pOriginalItem(pOrigItem) {}

	enum SelectionTrackerStyleFlags
	{
		hatchInside1 = hatchInside,
		selectedItem = 64
	};

	inline void SetGridSnap(BOOL fSnap, int xStep, int yStep) 
	{ 
	  m_fSnap = fSnap;
	  m_xStep = xStep;
	  m_yStep = yStep; 
	}
									 
	CRect SnapRect(const LPRECT lpRect);

	virtual void DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo,
								 CDC* pDC, CWnd* pWnd);
	  
	virtual void AdjustRect(int nHandle, LPRECT lpRect);

	void Draw(CDC* pDC) const;

protected:
	int SnapX(int nValue);
	int SnapY(int nValue);

	SECASelection		&m_selection;
	SECScriptHostView	*m_pView;
	SECACtrlItem		*m_pOriginalItem;
	BOOL			 m_fInitilized;
	CRect			 m_startRect;
	int				 m_xStep; 
	int				 m_yStep;
	BOOL			 m_fSnap;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
