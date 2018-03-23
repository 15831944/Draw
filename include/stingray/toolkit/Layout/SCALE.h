///////////////////////////////////////////////////////////////////////////////
// Scale.h : Declaration of SECLNScale
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
//
// This source code is only intended as a supplement to
// the Objective Toolkit Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Toolkit product.
//
// Author:       Mark Isham
// Description:  Declaration of SECLNScale class
//
// SECLNScale
// This SECLayoutNode derived class implements a basic "scaling" layout
// in which members are scaled on sizing to always occupy the same
// percentage of available width/height.
// 

#ifndef __SECLAYOUT_SCALE_H__
#define __SECLAYOUT_SCALE_H__

// Header Includes
#include <StingrayExportDefs.h>

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
#endif

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

//@doc SECLNScale 
//@class Implements the scale layout algorithm
//@BASE public | SECLayoutNode
//@comm The scale layout is used to maintain a constant aspect ratio throughout window resizing. 
class SECLNScale : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNScale();
	TOOLKIT_API virtual ~SECLNScale();

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

	// Implementation Member Functions
	TOOLKIT_API virtual CRect CalcNewChildNodeRect(const CRect& rectNodeInitial,
								  	   const CRect& rectNodeNew,
								  	   const CRect& rectChildInitial);
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


#endif //__SECLAYOUT__SCALE_H__
