///////////////////////////////////////////////////////////////////////////////
// CodeView.h
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
// UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//


#ifndef _SECCODEVIEW_H_
#define _SECCODEVIEW_H_

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

#include <StingrayExportDefs.h>

// CodeView.h : header file

// Forward declarations
class SECAColorEditor;
class CDoc;
class SECAEventBar;

/////////////////////////////////////////////////////////////////////////////
// SECACodeView view
//
class SECACodeView : public CView
{
public: // for now
	TOOLKIT_API SECACodeView();           // protected constructor used by dynamic creation
protected:
	TOOLKIT_DECLARE_DYNCREATE(SECACodeView)

public:
	TOOLKIT_API virtual BOOL IsModified() const;
	TOOLKIT_API virtual void SetModified(BOOL bModified = TRUE);


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECACodeView)
public:
	TOOLKIT_API virtual void OnFinalRelease();
	TOOLKIT_API virtual void OnInitialUpdate();
protected:
	TOOLKIT_API virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	TOOLKIT_API virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	TOOLKIT_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
	TOOLKIT_API virtual ~SECACodeView();
	TOOLKIT_API virtual CDocument* GetDocument() const;
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif
protected:

	//{{AFX_MSG(SECACodeView)
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnEditPaste();
	TOOLKIT_API afx_msg void OnEditCopy();
	TOOLKIT_API afx_msg void OnEditCut();
	TOOLKIT_API afx_msg void OnEditUndo();
	TOOLKIT_API afx_msg void OnViewEventBar();
	TOOLKIT_API afx_msg void OnUpdateViewEventBar(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnDestroy();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(SECACodeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	TOOLKIT_DECLARE_DISPATCH_MAP()
	TOOLKIT_DECLARE_INTERFACE_MAP()

public:
	SEC_TOOLBAR*	 m_pToolEdit;

protected:
	SECAColorEditor *m_pColorEditor;
	SECAEventBar	 *m_pEventBar;
	inline BOOL	  IsEventBarVisible() { return (m_pEventBar != NULL); }
	TOOLKIT_API virtual void CreateEditToolbar();
	TOOLKIT_API         void ShowEventBar();
	TOOLKIT_API         void HideEventBar(BOOL fReLayout = TRUE);
	
	BOOL			m_bCreatingContext;

public: //temp...
	TOOLKIT_API void CreateContext(CWnd *pWnd);
	
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// _SECCODEVIEW_H_


/////////////////////////////////////////////////////////////////////////////
