///////////////////////////////////////////////////////////////////////////////
// EventBar.h
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

#ifndef __SECEVENTBAR_H_
#define __SECEVENTBAR_H_

#include "toolkit\ActvHost\EventList.h"
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

class SECScriptHostDoc;
/////////////////////////////////////////////////////////////////////////////
// SECAEventBar 

class SECAEventBar : public CDialogBar
{
public:
	TOOLKIT_API SECAEventBar(SECScriptHostDoc *pDoc, CWnd *pParent, UINT nIDTemplate);
	//information fillup
	TOOLKIT_API void ReleaseAllObjects(BOOL fClearCombos=TRUE); //release previous series
    TOOLKIT_API void AddDesignedObject( const CString& strItem, IUnknown *pObj );
	TOOLKIT_API void InitItems(); //brute force initialization
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAEventBar)
	//}}AFX_VIRTUAL
public:
	TOOLKIT_API virtual ~SECAEventBar();
protected:
	//{{AFX_MSG(SECAEventBar)
	TOOLKIT_API afx_msg void OnSelchangeItems();
	TOOLKIT_API afx_msg void OnSelchangeEvents();
	TOOLKIT_API afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

	SECA_EventArray	 m_ItemEvents;      //a list of events for a picked item
	CString          m_strSelectedItem; //the name of a currently picked item
	
	TOOLKIT_API virtual void PopulateEventsCombo(); //uses m_ItemEvents to polulate combo	

	BOOL             m_fInitialized;
	SECScriptHostDoc *m_pDoc;
	CTypedPtrMap<CMapStringToPtr, CString, IUnknown *> m_DesignItems;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SECEVENTBAR_H_


/////////////////////////////////////////////////////////////////////////////
