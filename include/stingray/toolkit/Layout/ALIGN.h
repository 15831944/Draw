///////////////////////////////////////////////////////////////////////////////
// Align.h
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
// Description:  Declaration of SECLNAlign class
//
// SECLNAlign
// This SECLayoutNode derived class implements basic node alignment
// (left, right, top, bottom, or center)
// 

#ifndef __SECLAYOUT_ALIGN_H__
#define __SECLAYOUT_ALIGN_H__

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

// Constants

// Alignment styles
// only 1 of the following:
#define SECLAYOUT_ALIGN_LEFT		0x0001
#define SECLAYOUT_ALIGN_RIGHT		0x0002
#define SECLAYOUT_ALIGN_CENTER_HORZ	0x0004
// and/or only 1 of the following:
#define SECLAYOUT_ALIGN_TOP			0x0010
#define SECLAYOUT_ALIGN_BOTTOM		0x0020
#define SECLAYOUT_ALIGN_CENTER_VERT	0x0040

#define SECLAYOUT_ALIGN_DEFAULT		SECLAYOUT_ALIGN_CENTER_HORZ | 		\
									SECLAYOUT_ALIGN_CENTER_VERT
//@doc SECLNAlign
//@mfunc DWORD  | SECLNAlign | GetAlignment | Retrieves the current alignment configuration.
//@xref <c SECLNAlign>

//@doc SECLNAlign
//@mfunc CRect  | SECLNAlign | GetBoundingRect | Return the bounding rectangle for this layout node.
//@xref <c SECLNAlign>

/////////////////////////////////////////////////////////////////////////////
// SECLayout

//@doc SECLNAlign 
//@class Implements the alignment layout algorithm
//@BASE public | SECLayoutNode
class SECLNAlign : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	//@access Construction/Initialization

	//@cmember
	/* Constructor*/
	TOOLKIT_API SECLNAlign(DWORD dwAlignment=SECLAYOUT_ALIGN_DEFAULT);
	TOOLKIT_API virtual ~SECLNAlign();

	//@access Attributes

	//@cmember
	/* Set alignment style*/
	TOOLKIT_API void SetAlignment(DWORD dwAlignment);

	//@cmember
	/* Get alignment style*/
	inline DWORD GetAlignment() { return m_dwAlignment; }

	//@cmember
	/* Get current bounding rectangle*/
	inline CRect GetBoundingRect() { return m_rectBounding; }

	//@cmember
	/* Set alignment margins*/
	TOOLKIT_API void SetMargins(int nLeft,int nRight,int nTop,int nBottom);
	//@cmember
	/* Set alignment margins*/
	TOOLKIT_API void SetMargins(int nHorzMargin,int nVertMargin);
	//@cmember
	/* Set alignment margins*/
	TOOLKIT_API void SetMargins(int nMargin);
	//@cmember
	/* Get alignment margins*/
	TOOLKIT_API void GetMargins(int& nLeft,int& nRight,int& nTop,int& nBottom);

	// Operations
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,
								 BOOL bChildNegotiate,BOOL bStrictRecalc);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	CRect	m_rectBounding;
	BOOL	m_bInitBoundingRect;
	DWORD	m_dwAlignment;
	int		m_nLeftMargin,m_nRightMargin,m_nTopMargin,m_nBottomMargin;

	// Implementation Member Functions
	TOOLKIT_API virtual void RecalcBoundingRect();
	TOOLKIT_API virtual void AdjustBoundingRectForNewNode(const CRect& rectNodeAdded);
	TOOLKIT_API virtual void CalcMoveForAlignment(const CRect& rectNew,int& deltaX,int& deltaY);
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


#endif //__SECLAYOUT_ALIGN_H__

