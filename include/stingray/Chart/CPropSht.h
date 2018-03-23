///////////////////////////////////////////////////////////////////////////////
// CPropSht.h
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
//@module CPropSht.h | definition of the Chart Explorer property sheet class<nl>
//Written by Bob Powell (www.roguewave.com)

//$head The chart explorer
//$level 1

// cmember tags only used for this class

// SRGCPropertySheet.h : header file
//
// This class defines custom modal property sheet 
// SRGraphComponentProperties.

#ifndef __SRGCPROPERTYSHEET_H__
#define __SRGCPROPERTYSHEET_H__

#include "CPropPg.h"
//#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

/////////////////////////////////////////////////////////////////////////////
// SRGraphComponentProperties

/////////////////////////////
// AutoDuck tag block for SRGraphComponentProperties 

// adinsert AutoDuck insertion point for SRGraphComponentProperties 

//@topic SRGraphComponentProperties Class Overview |
//This is a property sheet in the chart explorer

//@doc SRGraphComponentProperties 
//@class SRGraphComponentProperties defines a custom modal property sheet.<nl>
//Part of Chart Explorer
//@base public | CPropertySheet
class SRGraphComponentProperties : public CPropertySheet
{
	CHART_DECLARE_DYNAMIC(SRGraphComponentProperties)

// Construction
public:
	//@cmember
	/* Constructor -- adds property pages appropriate or the type */
	//of item that the user selected, adds font style page if bFontSheet is TRUE 
	CHART_API SRGraphComponentProperties(CWnd* pParentWnd = NULL,BOOL bFontSheet=FALSE,int type=0);
// Attributes
public:
	//@cmember
	/* Property page for component rectangle position, measurement mode, and view angles*/
	SRGCTypeAndPos m_Page1;
	//@cmember
	/* Property page for component fill style*/
	SRGCFillStyle m_Page2;
	//@cmember
	/* Property page for component border style*/
	SRGCBorderStyle m_Page3;
	//@cmember
	/* Property page for component shadow style*/
	SRGCShadowStyle m_Page4;
	//@cmember
	/* Property page for component font style*/
	SRGCFontStyle m_Page5;
	//@cmember
	/* Property page for display component -- graph and axis type, scope, etc.*/
	SRGCDisplayStyle m_Page6;
	//@cmember
	/* Property page for legend component -- legend type, key style, scope*/
	SRGCLegendEdit m_Page7;
	//@cmember
	/* Property page for label component*/
	SRGCLabelStyle m_Page8;
	//@cmember
	/* Property page for annotations*/
	SRGCLabelStyle m_Page9;
	//@cmember
	/* Property page for data or data list objects*/
	SRGObjStyle m_Page10;
	//@cmember
	/* Property page for the interior of data or data list objects*/
	SRGInteriorEdit m_Page11;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGraphComponentProperties)
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphComponentProperties();

// Generated message map functions
protected:
	//{{AFX_MSG(SRGraphComponentProperties)
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// __SRGCPROPERTYSHEET_H__

