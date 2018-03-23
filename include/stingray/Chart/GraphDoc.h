///////////////////////////////////////////////////////////////////////////////
// GraphDoc.h
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

/////////////////////////////////////////////////////////////
//@doc
//@module GraphDoc.h| interface of the CGraphDoc class<nl>
//Written by Bob Powell (www.roguewave.com)
/////////////////////////////////////////////////////////////
//
// GraphDoc.h : interface of the CGraphDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __GRAPHDOC_H__
#define __GRAPHDOC_H__

#include <StingrayExportDefs.h>

// Document subcodes for processing data via the SECComDoc linking system
#define OGRIDDOC_CMND_NOOP			0x00000000	// No-Ops are always zero
#define OGRIDDOC_CMND_CELLVALUE		0x00000100	// Grid commands are kept away from graph commands

/////////////////////////////
// AutoDuck tag block for CGraphDoc

// adinsert AutoDuck insertion point for CGraphDoc 

//@doc CGraphDoc
//$head Document classes
//$level 1
//@mdata SRGraph | CGraphDoc | m_Graph | The chart object

//@class Manages linked document operations for the SRGraphView class
//@rem This file is optional and it is not required for the normal operation 
//of the Objective Graph kit.
//@base public | SECComDoc
class CGraphDoc : public SECComDoc
{
protected: // create from serialization only
	//@cmember
	/* Constructor*/
	CHART_API CGraphDoc();
	CHART_DECLARE_DYNCREATE(CGraphDoc)

// Attributes
public:
	//@cmember
	/* Initializes a document with data stored in global memory*/
	CHART_API virtual BOOL GmemInit(SEC_UINT code,HANDLE hMem);

	//@cmember
	/* The graph object*/
	SRGraph m_Graph;	 

// Operations
public:

	//@cmember
	/* Update the document*/
	// [VC7] - The return type was missing and was assumed to be 'int'
	CHART_API BOOL SecDocUpdate(SEC_UINT nSubCode,SEC_DWORD dwData);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphDoc)
public:
	//@cmember
	/* New document handler*/
	CHART_API virtual BOOL OnNewDocument();
	//@cmember
	/* Serialization*/
	CHART_API virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~CGraphDoc();

#ifdef _DEBUG
	//@cmember,mfunc
	/* Debug*/
	CHART_API virtual void AssertValid() const;
	//@cmember,mfunc
	/* Debug*/
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

#endif // __GRAPHDOC_H__

/////////////////////////////////////////////////////////////////////////////
// Reset DLL declaration context

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

