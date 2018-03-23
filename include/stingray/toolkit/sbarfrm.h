///////////////////////////////////////////////////////////////////////////////
// sbarfrm.h
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

#ifdef WIN32

#ifndef __SBARFRM_H__
#define __SBARFRM_H__

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
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


/////////////////////////////////////////////////////////////////////////////
// SECFrameBar frame

class SECFrameBar : public SECControlBar
{
	TOOLKIT_DECLARE_DYNCREATE(SECFrameBar)

protected:
	TOOLKIT_API SECFrameBar();           // protected constructor used by dynamic creation

// Operations
public:

	TOOLKIT_API CFrameWnd* GetDockedFrame() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECFrameBar)
	TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );
	//}}AFX_VIRTUAL

// Implementation
protected:
	TOOLKIT_API virtual ~SECFrameBar();

	// Generated message map functions
	//{{AFX_MSG(SECFrameBar)
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	TOOLKIT_API afx_msg int OnMouseActivate( CWnd* pDesktopWnd, UINT nHitTest, UINT message );
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////

#endif __SBARFRM_H__

#endif WIN32