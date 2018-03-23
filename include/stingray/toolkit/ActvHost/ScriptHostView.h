///////////////////////////////////////////////////////////////////////////////
// ScriptHostView.h
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
// Update Log:
//
//        06.19.06  exported classes with TOOLKIT_API macro by csd
//


#ifndef __SECSCRIPTHOSTVIEW_H_
#define __SECSCRIPTHOSTVIEW_H_

// ScriptHostView.h
/////////////////////////////////////////////////////////////////////////////
#include "toolkit\ActvHost\ToolBox.h"	// thing that floats in design mode
#include "toolkit\ActvHost\CtrlItem.h"
#include "toolkit\ActvHost\Selection.h"
#include "toolkit\ActvHost\ahostres.h"
#include "toolkit\ActvHost\ScriptHostDoc.h"
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

class SECAPropBrowser;

//@doc SECScriptHostView 
//@class ActiveScript view class
//@BASE public | CFormView
//@comm This class is intended to be plugged directly into your frame window's document template. In general, you will not need to utilize any of these member functions unless deriving a class and customizing functionality.
class SECScriptHostView : public CFormView
{
protected:
	TOOLKIT_DECLARE_DYNCREATE(SECScriptHostView)
	
	// Construction
	TOOLKIT_API SECScriptHostView();
	
public:
	//{{AFX_DATA(SECScriptHostView)
	enum{ IDD = SECAH_IDD_FORMS_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
public:
	//item(s) selection
	inline SECASelection &GetSelectedItems() { return m_selection; }
	TOOLKIT_API void SetSelection(SECACtrlItem* pNewSel, BOOL bSafeSelect=FALSE, BOOL fToggle=FALSE);

	//item - tracker interaction and invalidation
	TOOLKIT_API void SetupTracker(CRectTracker* pTracker, SECACtrlItem* pItem, CRect* pTrueRect=NULL);
	TOOLKIT_API SECACtrlItem*	GetHitItem(CPoint point);
	TOOLKIT_API void UpdateActiveItem();
	TOOLKIT_API void InvalidateItem(SECACtrlItem* pItem);

	//coordinates conversions
	TOOLKIT_API void ClientToDoc(CRect  &rc);
	TOOLKIT_API void DocToClient(CRect  &rc);
	TOOLKIT_API void ClientToDoc(CPoint &pt);
	TOOLKIT_API void DocToClient(CPoint &pt);
	TOOLKIT_API void ClientToDoc(CSize  &sz);
	TOOLKIT_API void DocToClient(CSize  &sz);
	TOOLKIT_API BOOL CanBeNormalized(CRect &SelectedRect);

	//scrolling and toolbars

	//@access Operations

	//@cmember
	/* Create the toolbars associated with the runtime form editor*/
	TOOLKIT_API virtual void CreateToolBars(CWnd *pParent);

	//@cmember
	/* Display the toolbars associated with the runtime form editor*/
	TOOLKIT_API virtual void DisplayToolBars();

	TOOLKIT_API virtual void SetViewSize();

	// show/hide the toolbox based on edit mode reference count
	TOOLKIT_API virtual void ShowToolBoxConditional(BOOL bShow);

	//container properties (window style, scrolling, color, ...)
	TOOLKIT_API virtual void ApplyContainerProperties();  // applies the settings

	//grid and grid snapping on/off
	TOOLKIT_API void SetGridDisplay(BOOL fOn); //does not repaint

	// toolbar access 

	//@cmember
	/* Set the top-level frame toolbar to activate Edit Mode.*/
	//
	// IMPORTANT! SEC_TOOLBAR maps at compile time to SECToolBar if SECFrameWnd or SECMDIFrameWnd is used as a parent frame, otherwise CToolBar.
	TOOLKIT_API virtual void SetToolBarEnterEdit(SEC_TOOLBAR* pToolEnterEdit);

	//@cmember
	/* Get the top-level frame toolbar to activate Edit Mode. See previous comments on SEC_TOOLBAR.*/
	TOOLKIT_API virtual SEC_TOOLBAR* GetToolBarEnterEdit();

	//@cmember
	/* Set the edit mode toolbox toolbar. See previous comments on SEC_TOOLBAR.*/
	TOOLKIT_API virtual void SetToolBox(SECAToolBox* pToolBox);

	//@cmember
	/* Get the edit mode toolbox toolbar. See previous comments on SEC_TOOLBAR.*/
	TOOLKIT_API virtual SECAToolBox* GetToolBox();	

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECScriptHostView)
	public:
	TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	TOOLKIT_API virtual void OnInitialUpdate();
	TOOLKIT_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	
	protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	TOOLKIT_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	TOOLKIT_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	TOOLKIT_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	TOOLKIT_API virtual void OnPrint(CDC* pDC, CPrintInfo*);
	TOOLKIT_API virtual void OnDraw(CDC* pDC);
	TOOLKIT_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	TOOLKIT_API virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL

protected:
	// overridables

	// override this to disable/modify custom accelerators
	TOOLKIT_API virtual BOOL OnPreTranslateChar(UINT nChar,LONG lKeyData);

protected:
	// 1 per all views in MDI: (if SDI, there is a new toolbar per each view)
	TOOLKIT_API static SECAToolBox* m_pToolBox;		
	TOOLKIT_API static SEC_TOOLBAR* m_pToolEnterEdit; 

	// 1 edit toolbar per view, regardless
	SEC_TOOLBAR* m_pToolEdit;	

	// If SDI, 1 toolbar per view (since we can have multiple top level SDIs).
	SECAToolBox* m_pSDIToolBox;
	SEC_TOOLBAR* m_pSDIToolEnterEdit;
         
	// Is this view inside an MDI child frame?
	BOOL m_bInsideMDIFrame;

	//copy/paste
	TOOLKIT_API void DoPasteNative(COleDataObject* pDataObject, CPoint* pPoint, SECACtrlItem* pItem);
	TOOLKIT_API SECACtrlItem* DoPasteItem(BOOL bLink, COleDataObject* pDataObject, CPoint* pPoint, CLIPFORMAT cfFormat = 0);

	//layout helpers
	TOOLKIT_API void InvalidateSelectedItems();
	TOOLKIT_API void MakesamesizeHeight();
	TOOLKIT_API void MakesamesizeWidth();


	//safe item creation and validation
	TOOLKIT_API BOOL CreateAndAddItem( REFCLSID CLSID, const CString &strNameInScript, const CRect *initialRect=NULL);
	TOOLKIT_API int GetNextItemID();

	SEC_TOOLBAR	   m_Layout;	      // These bars are owned by the view because they can fire
						                      // actions that are only handled by this view
	BOOL		     m_fSelecting;    // ---for doing selections
	CPoint		     m_lastPt;	      //
	CPoint		     m_downPt;		    //
	CRect		     m_SelectedRect;  //
	SECASelection	 m_selection;	    // current selection of SECACtrlItems (does multiple selection as well, multiple item copy/paste)

	// override these to customize created toolbars
	TOOLKIT_API virtual SEC_TOOLBAR* CreateEditToolBar(CFrameWnd* pParent);
	TOOLKIT_API virtual SEC_TOOLBAR* CreateEnterEditToolBar(CFrameWnd* pParent);
	TOOLKIT_API virtual SECAToolBox* CreateToolBox(CFrameWnd* pParent);

	//grid, background and form's color
	int		   m_xStep;
	int		   m_yStep;
	BOOL	   m_fGrid;
	COLORREF m_GridColor;
	TOOLKIT_API void DrawGrid(CDC* pDC);

	// edit mode reference counting
	ScriptMode m_modeLast;
	TOOLKIT_API static int m_nMDIEditRefCount;	// number of view objects in "edit mode" at any 1 time (MDI)
	TOOLKIT_API static int m_nMDIViewRefCount;	// total number of MDI view objects of this type
	TOOLKIT_API virtual void OnDecrementIfEditModeRefCount();
	TOOLKIT_API virtual void OnUpdateModeRefCount();

protected:
	//{{AFX_MSG(SECScriptHostView)
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnEditInsertControl();
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnEditCut();
	TOOLKIT_API afx_msg void OnLayoutEdit();
	TOOLKIT_API afx_msg void OnUpdateLayoutEdit(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnProperties();
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg void OnViewToolbox();
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnEditCopy();
	TOOLKIT_API afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnEditPaste();
	TOOLKIT_API afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnEditDelete();
	TOOLKIT_API afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignLeft();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignLeft(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignRight();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignRight(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignTop();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignTop(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignBottom();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignBottom(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignVertcenter();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignVertcenter(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutAlignHorcenter();
	TOOLKIT_API afx_msg void OnUpdateLayoutAlignHorcenter(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutSpaceEvenlyAcross();
	TOOLKIT_API afx_msg void OnUpdateLayoutSpaceEvenlyAcross(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutSpaceEvenlyDown();
	TOOLKIT_API afx_msg void OnUpdateLayoutSpaceEvenlyDown(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutCnterInViewHoriz();
	TOOLKIT_API afx_msg void OnUpdateLayoutCnterInViewHoriz(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutCnterInViewVert();
	TOOLKIT_API afx_msg void OnUpdateLayoutCnterInViewVert(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutMakesamesizeBoth();
	TOOLKIT_API afx_msg void OnUpdateLayoutMakesamesizeBoth(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutMakesamesizeHeight();
	TOOLKIT_API afx_msg void OnUpdateLayoutMakesamesizeHeight(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutMakesamesizeWidth();
	TOOLKIT_API afx_msg void OnUpdateLayoutMakesamesizeWidth(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutSendToBack();
	TOOLKIT_API afx_msg void OnUpdateLayoutSendToBack(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnLayoutBringToFront();
	TOOLKIT_API afx_msg void OnUpdateLayoutBringToFront(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnViewLayoutBar();
	TOOLKIT_API afx_msg void OnUpdateViewLayoutBar(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateEditInsertControl(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnViewPropertiesControl();
	//}}AFX_MSG
	TOOLKIT_API afx_msg void OnContainerProperties();
	TOOLKIT_API afx_msg void OnToggleGrid();
	TOOLKIT_API afx_msg void OnUpdateToggleGrid(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnPickedTool( UINT nToolCommandID );
	TOOLKIT_API afx_msg void OnPickedToolUpdate(CCmdUI* pCmdUI);
	TOOLKIT_DECLARE_MESSAGE_MAP()
public:
	TOOLKIT_API virtual ~SECScriptHostView();
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
	TOOLKIT_API SECScriptHostDoc* GetDocument();
#endif
#ifndef _DEBUG 
	inline SECScriptHostDoc* GetDocument(){ return (SECScriptHostDoc*)m_pDocument; }
#endif
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SECSCRIPTHOSTVIEW_H_


/////////////////////////////////////////////////////////////////////////////

