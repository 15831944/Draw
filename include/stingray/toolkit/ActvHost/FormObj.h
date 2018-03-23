///////////////////////////////////////////////////////////////////////////////
// FormObj.h
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

#ifndef __SECSCRIPTHOSTDOC_H_
#define __SECSCRIPTHOSTDOC_H_

/////////////////////////////////////////////////////////////////////////////
// SECAFormObj : See FormObj.cpp for implementation.

#include <afxctl.h>
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

// Forward declaration
class SECScriptHostDoc;

//@doc SECAFormObj 
//@mfunc void | SECAFormObj | FireOnLoad | Fires the OnLoad form event for this form.
//@xref <c SECAFormObj>

//@doc SECAFormObj 
//@mfunc void | SECAFormObj | FireOnUnload | Fires the OnUnload form event for this form.
//@xref <c SECAFormObj>

//@doc SECAFormObj
//@mfunc void  | SECAFormObj | SetDocument | Set the document
//@parm SECScriptHostDoc*  | pDoc | A pointer to the document
//@xref <c SECScriptHostDoc>

//@doc SECAFormObj
//@mfunc SECScriptHostDoc*  | SECAFormObj | GetDocument | Get the document
//@xref <c SECScriptHostDoc>

//@doc SECAFormObj
//@mfunc BOOL | SECAFormObj | IsVisible | returns current visibility state of the form
//@xref <c SECScriptHostDoc>


//@doc SECAFormObj 
//@class Form object for Active Scripting. This class implements a scriptable form object to link your script to your app.
//@BASE public | COleControl
//@xref <c SECAAppObj>


class SECAFormObj : public COleControl
{
	TOOLKIT_DECLARE_DYNCREATE(SECAFormObj)

public:

	//@access Contruction/Initialization

	//@cmember
	/* Constructor, independent*/
	TOOLKIT_API SECAFormObj();

	//@cmember
	/* Constructor, link to SECScriptHostDoc*/
	TOOLKIT_API SECAFormObj(SECScriptHostDoc *pDoc);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAFormObj)
	public:
	TOOLKIT_API virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	TOOLKIT_API virtual void DoPropExchange(CPropExchange* pPX);
	TOOLKIT_API virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	TOOLKIT_API virtual ~SECAFormObj();

	DECLARE_OLECREATE_EX(SECAFormObj) // Class factory and guid
	DECLARE_OLETYPELIB(SECAFormObj)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(SECAFormObj)  // Property page IDs
	DECLARE_OLECTLTYPE(SECAFormObj)   // Type name and misc status

// Message maps
	//{{AFX_MSG(SECAFormObj)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(SECAFormObj)
	BOOL m_visible;
	
	TOOLKIT_API afx_msg void OnVisibleChanged();
	TOOLKIT_API afx_msg void Show();
	TOOLKIT_API afx_msg void Hide();
	TOOLKIT_API afx_msg void Close();
	TOOLKIT_API afx_msg void Enable(BOOL fEnable);
	TOOLKIT_API afx_msg void Minimize();
	TOOLKIT_API afx_msg void Maximize();
	TOOLKIT_API afx_msg void Restore();

	//@cmember
	/* Return a pointer to the SECAAppObj dispatch for frame creation/loading.*/
	TOOLKIT_API afx_msg LPDISPATCH GetApp();
	
	TOOLKIT_API afx_msg void ShowMenu();
	TOOLKIT_API afx_msg void HideMenu();
	TOOLKIT_API afx_msg void Caption(LPCTSTR strNewCaption);
	TOOLKIT_API afx_msg void DoEvents();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

public:
// Event maps
	//@access Operations

	//@cmember
	/* returns current visibility state of the form*/
	inline BOOL IsVisible() { return m_visible; }

	//@cmember
	/* Set the document*/
	inline void SetDocument(SECScriptHostDoc* pDoc){ m_pDoc = pDoc; }
	//@cmember
	/* Get the document*/
	inline SECScriptHostDoc* GetDocument(){ return m_pDoc; }

	//{{AFX_EVENT(SECAFormObj)

	//@cmember
	/* Fire the OnLoad form event*/
	inline void FireOnLoad() { FireEvent(eventidOnLoad,EVENT_PARAM(VTS_NONE)); }

	//@cmember
	/* Fire the OnUnload form event*/
	inline void FireOnUnload() { FireEvent(eventidOnUnload,EVENT_PARAM(VTS_NONE)); }
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(SECAFormObj)
	dispidVisible =   1L,
	dispidShow =      2L,
	dispidHide =      3L,
	dispidClose =     4L,
	dispidEnable =    5L,
	dispidMinimize =  6L,
	dispidMaximize =  7L,
	dispidRestore =   8L,
	dispidGetApp =    9L,
	dispidShowMenu = 10L,
	dispidHideMenu = 11L,
	dispidCaption =  12L,
	dispidDoEvents = 13L,
	eventidOnLoad =   1L,
	eventidOnUnload = 2L,
	//}}AFX_DISP_ID
	};

	SECScriptHostDoc *m_pDoc;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SECSCRIPTHOSTDOC_H_

