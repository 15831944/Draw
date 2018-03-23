///////////////////////////////////////////////////////////////////////////////
// Notify.h : Declaration of AgentNotifySink
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
// Description:  Declaration of AgentNotifySink
//

#ifndef _AgentNotifySink_h_
#define _AgentNotifySink_h_

#ifndef _OT_AGENTID
#include "toolkit\ot_agentid.h"
#endif

#include <StingrayExportDefs.h>

using namespace AgentServerObjects;

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

class AgentNotifySink : public IAgentNotifySinkEx {
public:
	inline AgentNotifySink() : m_cRefs(0) {}
    inline virtual ~AgentNotifySink() {}

    TOOLKIT_API STDMETHODIMP QueryInterface(REFIID, LPVOID FAR *);
    TOOLKIT_API STDMETHODIMP_(ULONG) AddRef();
    TOOLKIT_API STDMETHODIMP_(ULONG) Release();

	TOOLKIT_API STDMETHODIMP GetTypeInfoCount(UINT *);
	TOOLKIT_API STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
	TOOLKIT_API STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR **, UINT, LCID, DISPID *);
	TOOLKIT_API STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

    TOOLKIT_API STDMETHODIMP raw_Command(long dwCommandID, IUnknown * punkUserInput);
    TOOLKIT_API STDMETHODIMP raw_ActivateInputState(long dwCharID, long bActivated);
    TOOLKIT_API STDMETHODIMP raw_Restart();
    TOOLKIT_API STDMETHODIMP raw_Shutdown();
    TOOLKIT_API STDMETHODIMP raw_VisibleState(long dwCharID, long bVisible, long lCause);
	TOOLKIT_API STDMETHODIMP raw_Click(long dwCharID, short fwKeys, long X, long Y);
	TOOLKIT_API STDMETHODIMP raw_DblClick(long dwCharID, short fwKeys, long X, long Y);
	TOOLKIT_API STDMETHODIMP raw_DragStart(long dwCharID, short fwKeys, long X, long Y);
	TOOLKIT_API STDMETHODIMP raw_DragComplete(long dwCharID, short fwKeys, long X, long Y);
	TOOLKIT_API STDMETHODIMP raw_RequestStart(long dwRequestID);
	TOOLKIT_API STDMETHODIMP raw_RequestComplete(long dwRequestID, long hrStatus);
	TOOLKIT_API STDMETHODIMP raw_BookMark(long dwBookMarkID);
    TOOLKIT_API STDMETHODIMP raw_Idle(long dwCharID, long bStart);
	TOOLKIT_API STDMETHODIMP raw_Move(long dwCharID, long X, long Y, long lCause);
	TOOLKIT_API STDMETHODIMP raw_Size(long dwCharID, long lWidth, long lHeight);
	TOOLKIT_API STDMETHODIMP raw_BalloonVisibleState(long dwCharID, long bVisible);

	TOOLKIT_API STDMETHODIMP raw_HelpComplete(long dwCharID, long dwCommandID, long dwCause);
	TOOLKIT_API STDMETHODIMP raw_ListeningState(long dwCharacterID, long bListenState, long dwCause);
	TOOLKIT_API STDMETHODIMP raw_DefaultCharacterChange(BSTR bszGUID);
	TOOLKIT_API STDMETHODIMP raw_AgentPropertyChange();
	TOOLKIT_API STDMETHODIMP raw_ActiveClientChange(long dwCharID, long lStatus);


private:
	ULONG	m_cRefs;
};

// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
