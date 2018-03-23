///////////////////////////////////////////////////////////////////////////////
// grpeddlg.h
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

/////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////
//@doc
//@module GrpEdDlg.h | Interface for the SRGraphEditDialog class<nl>
//Written by Bob Powell ( www.roguewave.com )
//
// using cmember tags only for these dialog classes
/////////////////////////////////////////////////////////////
//
// grpeddlg.h : header file
//
#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif
/////////////////////////////////////////////////////////////////////////////
// SRGraphEditDialog dialog
#ifndef __SRGRAPHEDITDIALOG_H__
#define __SRGRAPHEDITDIALOG_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGraphEditDialog

// adinsert AutoDuck insertion point for SRGraphEditDialog 

//$head The Chart explorer
//$level 1

//@topic SRGraphEditDialog Class Overview |
//The components and data lists in the current graph are displayed in an expandable tree diagram. 
//When the user double-clicks a component, data list, or individual data item; 
//a dialog (property sheet) is displayed that allows many properties of the selected item to be changed.<nl>
//When the user right-clicks on an item, a popup menu appears that is specific to the item type. 
//Components can be added or deleted, loaded or stored to disk, or reordered. Annotations can be added to data items.

//@doc SRGraphEditDialog
//@class Part of Chart Explorer<nl>
//The components and data lists in the current graph are displayed in an expandable tree diagram. 
//When the user double-clicks a component, data list, or individual data item; 
//a dialog (property sheet) is displayed that allows many properties of the selected item to be changed.<nl>
//When the user right-clicks on an item, a popup menu appears that is specific to the item type. 
//Components can be added or deleted, loaded or stored to disk, or reordered. Annotations can be added to data items.
//@base public | CDialog
class SRGraphEditDialog : public CDialog
{
// Construction
public:
	//@cmember
	/* Displays the SRGraphComponentProperties dialog with pages appropriate for the type of the selected item*/
	CHART_API virtual void OnEditDataItem();
	//@cmember
	/* Override this routine to add your own components*/
	CHART_API virtual void AddCustomComponent(int Selection);
	//@cmember
	/* Builds an expandable tree diagram showing the components and data in the current graph*/
	CHART_API virtual void BuildTree();
	//@cmember
	/* Constructor*/
	CHART_API SRGraphEditDialog(CWnd* pParent = NULL);   // standard constructor

	enum ImageValues {
	GRAPH_SEL,
	GRAPH_NSEL,
	COMLIST_SEL,
	COMLIST_NSEL,
	COMPONENT_SEL,
	COMPONENT_NSEL,
	ANNOTATION_SEL,
	ANNOTATION_NSEL,
	DATALIST_SEL,
	DATALIST_NSEL,
	DATAITEM_SEL,
	DATAITEM_NSEL,
	VALUE_SEL,
	VALUE_NSEL
	} ;

// Dialog Data
	//{{AFX_DATA(SRGraphEditDialog)
	enum { IDD = SRG_IDD_GRAPHEDIT };
	//@cmember
	/* Tree diagram control*/
	SRGTreeCtrl	m_GraphTree;
	//}}AFX_DATA

	//@cmember
	/* Pointer to the graph being edited*/
	SRGraph *m_pGraph; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGraphEditDialog)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//@cmember
	/* Data list item for tree diagram*/
	HTREEITEM m_DataListItem;
	//@cmember
	/* Component list item for tree diagram*/
	HTREEITEM m_ComponentListItem;
	//@cmember
	/* Root item for tree diagram*/
	HTREEITEM m_Root;
	//@cmember
	/* List of items in tree diagram*/
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(SRGraphEditDialog)
	//@cmember
	/* Initializes dialog -- builds tree diagram*/
	CHART_API virtual BOOL OnInitDialog();
	//@cmember
	/* Handles double-click on tree items -- displays editing dialog*/
	CHART_API afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//@cmember
	/* Handles right-click on tree items -- displays popup menu*/
	CHART_API afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//@cmember
	/* Displays file selection dialog and loads the graph from the file*/
	CHART_API afx_msg void OnLoadComponentList();
	//@cmember
	/* Saves a description of the graph in a disk file for reuse*/
	CHART_API afx_msg void OnSaveComponentList();
	//@cmember
	/* Deletes the selected component from the graph*/
	CHART_API afx_msg void OnDeleteComponent();
	//@cmember
	/* Displays property editing dialog for the selected component*/
	CHART_API afx_msg void OnEditComponentProperties();
	//@cmember
	/* Adds a new component to the graph*/
	CHART_API afx_msg void OnAddComponent();
	//@cmember
	/* Does nothing*/
	CHART_API afx_msg void OnAddLabel();
	//@cmember
	/* Adds an annotation to a data item, data list, or component*/
	CHART_API afx_msg void OnAddannotation();
	//@cmember
	/* Calls OnAddannotation*/
	CHART_API afx_msg void OnLabelAddannotation();
	//@cmember
	/* Moves the selected item back one step in the list order*/
	CHART_API afx_msg void OnIdBack1();
	//@cmember
	/* Moves the selected item forward one step in the list order*/
	CHART_API afx_msg void OnIdForward1();
	//@cmember
	/* Moves the selected item to the top of the list order*/
	CHART_API afx_msg void OnIdMovetotop();
	//@cmember
	/* Moves the selected item to the back of the list order*/
	CHART_API afx_msg void OnIdSendtoback();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

#endif

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

