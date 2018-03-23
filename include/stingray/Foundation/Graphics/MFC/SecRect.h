///////////////////////////////////////////////////////////////////////////////
// SecRect.h : Declaration of SECRect
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
// Author:       Mark Isham
// Description:  Declaration of SECRect
//


#ifndef __SFL_SEC_RECT_H__
#define __SFL_SEC_RECT_H__

// Header Includes
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

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
// SECRect

class FOUNDATION_API SECRect : public CRect {
public:
	// Construction/Initialization
	SECRect();
	SECRect(BOOL bHorz);
	SECRect(const RECT& srcRect,BOOL bHorz=TRUE);
	SECRect& operator=(const CRect& rhs);

	// Set the implicit orientation of this rectangle
	void SetHorzOrient(BOOL bHorz=TRUE);

	//
	// Orientation-neutral functions
	//

	// Set left/top or right/bottom based on set orientation.
	// If horz, primary LT is left, primary RB is right,
	// secondary TL is top, off BR is bottom. Reversed for vertical.
	void LT(int nLeftOrTop);			// primary left for horz, top vert
	void RB(int nRightOrBottom);		// primary right for horz, bottom vert
	void OffTL(int nLeftOrTop);		// off side: top for horz, left for vert
	void OffBR(int nRightOrBottom);	// off side: bottom for horz, right for vert

	// Get versions of above
	int GetLT();
	int GetRB();
	int GetOffTL();
	int GetOffBR();

	// orienation neutral size functions
	int PrimarySize();			// Width() for horz, Height() for vert
	int SecondarySize();		// Height() for horz, Width() for vert

protected:
	BOOL m_bHorz;
};

};  // namespace stingray::foundation
};  // namespace stingray

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SFL_SEC_RECT_H__
