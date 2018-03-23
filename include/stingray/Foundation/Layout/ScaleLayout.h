///////////////////////////////////////////////////////////////////////////////
// ScaleLayout.h : SFL Layout Manager
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
// Author:       Gilberto Araya
// Description:  SFL Layout Manager: Scale layout algorithm
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\Layout\LayoutNode.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc


//@class CScaleLayout |
/* Implementation of the Scale layout algorithm.<nl>
   The Scale layout maintains all children with a constant aspect ratio to the parent scale node. 
   In other words, the child node's top, left, right, and bottom coordinates are stored as percentages 
   of the parent node's size and are resolved to actual pixel values with each recalculation.
   This guarantees a constant aspect ratio regardless of the size of the parent node.
*/
//@base public | CLayoutNode<CScaleLayout, ILayoutNode>
//@supint ILayoutNode | Basic layout node interface.
class __declspec(uuid("8B1647C1-45E5-11d3-9D92-00C04F91E286")) CScaleLayout: public CLayoutNode<CScaleLayout, ILayoutNode>
{
public:
	// Initialization/Destruction
	CScaleLayout() {}
	virtual ~CScaleLayout() {}


protected:
	// ILayoutNode interface
	inline virtual CRect OnRecalcLayout(const CRect& rectDesired,
								 bool bChildNegotiate, bool bStrictRecalc);

protected:
	// Implementation

	inline virtual CRect CalcNewChildNodeRect(const CRect& rectNodeInitial,
								  	   const CRect& rectNodeNew,
								  	   const CRect& rectChildInitial);
};

/////////////////////////////////////////////////////////////////////
// foundation::CScaleLayout implementation
//

CRect 
CScaleLayout::OnRecalcLayout (
							  const CRect& rcDesired,
							  bool bChildNegotiate,
							  bool bStrictRecalc
							  )
{
	// Apply layout to all child nodes
	ILayoutNode* pNode;
	CRect rcChildDesired, rcChildInitial;
	CRect rcNodeNew;
	CRect rcNodeInitial;
	GetInitialRect(rcNodeInitial);
	CRect rcUsed;

	Children::iterator i;
	for (i = m_Children.begin(); i != m_Children.end(); ++i) {
		pNode = (*i);
		pNode->GetInitialRect(rcChildInitial);
		rcChildDesired = CalcNewChildNodeRect(rcNodeInitial, rcDesired, rcChildInitial);

		// We have the desired rect of the child node - attempt
		// to apply this rect. If child negotiation is enabled, child
		// node may suggest an alternate sizing.
		rcUsed = pNode->RecalcLayout(rcChildDesired, bChildNegotiate, bStrictRecalc);

		// if child suggested an alternate sizing, and we allow child negotiation,
		// process the requested size as desired. Do nothing if size is ok.
		if ((bChildNegotiate) && (rcUsed != rcChildDesired)) {

			// TODO: rect massaging here...

			// If rectUsed has been changed, apply again, with no child negotiation
			pNode->RecalcLayout(rcUsed, false, bStrictRecalc);
		}

	}

	SetCurrentRect(rcDesired);
	return rcDesired;
}


// Based on raw data passed in, calculate and return the new child
// node rectangle.
CRect 
CScaleLayout::CalcNewChildNodeRect (
									const CRect& rcNodeInitial,
									const CRect& rcNodeNew,
									const CRect& rcChildInitial
									)
{
	CRect rcChildNew;

	// Use initial rect's as baseline for size calculation to avoid cumulative rounding error.
	// However, in case the rect has been displaced, use the current rect for positioning

	// Width aspect: new relative to old
	float fAspectWidth = 1.0;
	if (rcNodeInitial.Width() > 0) {
		fAspectWidth = static_cast<float>(rcNodeNew.Width()) / static_cast<float>(rcNodeInitial.Width());
	}
	// Height aspect: new relative to old
	float fAspectHeight = 1.0;
	if (rcNodeInitial.Height() > 0) {
		fAspectHeight = static_cast<float>(rcNodeNew.Height()) / static_cast<float>(rcNodeInitial.Height());
	}

	int nHorizontalDisplacement = rcNodeNew.left - rcNodeInitial.left;
	int nVerticalDisplacement = rcNodeNew.top - rcNodeInitial.top;

	// now, recalc rectangle based on aspect change: (round to nearest int)
	rcChildNew.left	  = static_cast<int>(static_cast<float>(rcChildInitial.left * fAspectWidth + 0.5) + nHorizontalDisplacement);
	rcChildNew.right  = static_cast<int>(static_cast<float>(rcChildInitial.right * fAspectWidth + 0.5) + nHorizontalDisplacement);
	rcChildNew.top	  = static_cast<int>(static_cast<float>(rcChildInitial.top * fAspectHeight + 0.5) + nVerticalDisplacement);
	rcChildNew.bottom = static_cast<int>(static_cast<float>(rcChildInitial.bottom * fAspectHeight + 0.5) + nVerticalDisplacement);

	// Done!
	return rcChildNew;
}

}; // namespace foundation
}; // namespace stingray
