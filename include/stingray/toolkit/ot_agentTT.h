///////////////////////////////////////////////////////////////////////////////
// ot_agentTT.h
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
// Author:       Praveen Ramesh
// Description:  Declaration SECAgentTooltipListener class. 
//


#ifndef _OT_AGENT_TOOLTIP
#define _OT_AGENT_TOOLTIP

#ifndef __SFL_PLUGIN_H__
#include "Foundation\patterns\mfc\plugin.h"
#endif

#ifndef __SFL_SECWndListener_H__
#include "Foundation\patterns\mfc\Listen.h"
#endif

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

//@doc SECAgentTooltipListener 
//@class The SECAgentTooltipListener provides you tooltips via agents for the specified windows.
class SECAgentTooltipListener : public stingray::foundation::SECWndListener
{
	// SECWndListener exports this in the ClassRuntime calls in ..\Include\Foundation\Pattern\MFC\Listen.h
	TOOLKIT_DECLARE_DYNAMIC(SECAgentTooltipListener)

public:
	TOOLKIT_API SECAgentTooltipListener();
	TOOLKIT_API virtual ~SECAgentTooltipListener();

	TOOLKIT_API BOOL AddTool(CWnd* pWnd, UINT nDelay, LPCTSTR pStr);
	
	UINT					m_nDelay;
	CString					m_strText;
	BOOL					m_bWaitingForTimer;
	SECAgentCharacterExPtr*	m_pptrChar;

	// Generated message map functions
protected:
	//{{AFX_MSG(SECAgentTooltipListener)
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()

	long m_lTTActID;
};

// Macros to specify a Agent Tooltip for a window

// To be used inside the View/Dialog's .h
#define DECLARE_AGENT_TOOLTIPS() \
	TOOLKIT_API void InitAgentTooltips(SECAgentCharacterExPtr* pptrChar); \

#define TOOLTIP_LISTENER(listenerId) \
	SECAgentTooltipListener m_##listenerId;\

// To be used in the View/Dialog's .cpp
#define BEGIN_AGENT_TOOLTIPS(theClass) \
	void theClass::InitAgentTooltips(SECAgentCharacterExPtr* pptrChar){ \
	
#define TOOLTIP_ENABLE(listenerId, theWnd, theDelay, theText) \
	m_##listenerId.AddTool(theWnd, theDelay, theText); \
	m_##listenerId.m_pptrChar = pptrChar; \

#define END_AGENT_TOOLTIPS() \
	} \

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_OT_AGENT_TOOLTIP
