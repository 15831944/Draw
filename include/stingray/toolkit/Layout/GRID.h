///////////////////////////////////////////////////////////////////////////////
// Grid.h : Declaration of SECLNGrid
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
// Author:       Mark Isham
// Description:  Declaration of SECLNGrid class
//
// SECLNGrid
// SECLayoutNode derived class implementing a grid layout scheme
// 

#ifndef __SECLAYOUT_GRID_H__
#define __SECLAYOUT_GRID_H__

// Header Includes

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
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
// SECLayout

//@doc SECLNGrid 
//@class Implements the grid layout algorithm
//@BASE public | SECLayoutNode
//@comm Similar to the Java Grid layout algorithm, Grid allows you to logically arrange child nodes in a one or two dimensional matrix of arbitrary size.
class TOOLKIT_API SECLNGrid : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							                         //
	//---------------------------------------------------------------------//
public:

	//@access Construction/Initialization

	//@cmember
	/* Construction*/
	SECLNGrid();

	//@cmember
	/* Construction*/
	SECLNGrid(UINT nRows,UINT nCols=0,UINT nHorzGap=0,UINT nVertGap=0,
                     	  BOOL bIterateColsFirst=TRUE);
	virtual ~SECLNGrid();

	//@access Attributes

	//@cmember
	/* Format the grid dimensions*/
	virtual void SetGridDimensions(UINT nRows,UINT nCols=0,UINT nHorzGap=0,
							                               UINT nVertGap=0,BOOL bIterateColsFirst=TRUE);

	// Operations
	virtual int AddLayoutNode(SECLayoutNode* pNode);

	//---------------------------------------------------------------------//
	// 							 Overridables							                             //
	//---------------------------------------------------------------------//
protected:
	virtual CRect OnRecalcLayout(const CRect& rectDesired,
								                           BOOL bChildNegotiate,BOOL bStrictRecalc);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					                       //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	UINT m_nRows,m_nCols;
	UINT m_nHorzGap,m_nVertGap;
	UINT m_nMinCellWidth,m_nMinCellHeight;
	BOOL m_bIterateColsFirst;

	// Implementation Member Functions
	virtual UINT GetColumnWidth(UINT nNodes,CRect rectAvail);
	virtual UINT GetRowHeight(UINT nNodes,CRect rectAvail);
	virtual void GetNextGridCell(UINT& xPos,UINT& yPos,UINT nColWidth,
							                             UINT nRowHeight,const CRect& rectGrid);
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECLAYOUT_GRID_H__

