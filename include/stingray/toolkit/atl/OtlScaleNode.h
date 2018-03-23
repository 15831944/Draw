///////////////////////////////////////////////////////////////////////////////
// OtlScaleNode.h
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

#ifndef __OTLSCALENODE_H__
#define __OTLSCALENODE_H__

#ifndef __OTLBASE_H__
	#error otlscalenode.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otllayoutnode.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlScaleNode

class COtlScaleNode : public COtlLayoutNode
{

	inline void OnRecalcLayout(LPRECT lpRect,
						const RECT& rectDesired,
						BOOL bChildNegotiate,
						BOOL bStrictRecalc)
	{
		// Apply layout to all child nodes
		COtlLayoutNode* pNode = 0;
		RECT rectChildDesired;
		RECT rectChildInitial;
		RECT rectNodeInitial;
		GetInitialRect(&rectNodeInitial);
		RECT rectUsed;

		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			OTLASSERT(*ppNode);
			pNode = *ppNode;
			pNode->GetInitialRect(&rectChildInitial);
			CalcNewChildNodeRect(&rectChildDesired, rectNodeInitial, rectDesired, rectChildInitial);

			// We have the desired rect of the child node - attempt
			// to apply this rect. If child negotiation is enabled, child
			// node may suggest an alternate sizing.
			pNode->RecalcLayout(&rectUsed, rectChildDesired,bChildNegotiate,bStrictRecalc);

			// if child suggested an alternate sizing, and we allow child negotiation,
			// process the requested size as desired. Do nothing if size is ok.
			if( bChildNegotiate && !::EqualRect(&rectUsed, &rectChildDesired) ) 
			{

				// TODO: rect massaging here...

				// If rectUsed has been changed, apply again, with no child negotiation
				RECT r;
				pNode->RecalcLayout(&r, rectUsed,FALSE,bStrictRecalc);
			}

		} // END FOR

		SetCurrentRect(rectDesired);
		if( lpRect )
		{
			::CopyRect(lpRect, &rectDesired);
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Protected Implementation
	//

	// Based on raw data passed in, calculate and return the new child
	// node rectangle.
	inline void CalcNewChildNodeRect(	LPRECT lpRect,
								const RECT& rectNodeInitial,
								const RECT& rectNodeNew,
								const RECT& rectChildInitial)
	{
		OTLASSERT(lpRect);
		RECT rectChildNew;

		// Use initial rect's as baseline for size calculation to avoid
		// cumulative rounding error.

		// Width aspect: new relative to old
		float fAspectWidth=1.0f;
		if(OtlRectWidth(rectNodeInitial)>0)
			 fAspectWidth=(float)OtlRectWidth(rectNodeNew)/(float)OtlRectWidth(rectNodeInitial);

		// Height aspect: new relative to old
		float fAspectHeight=1.0f;
		if(OtlRectHeight(rectNodeInitial)>0)
			 fAspectHeight=(float)OtlRectHeight(rectNodeNew)/(float)OtlRectHeight(rectNodeInitial);

		// now, recalc rectangle based on aspect change: (round to nearest int)
		rectChildNew.left=(int)((float)rectChildInitial.left*fAspectWidth+0.5);
		rectChildNew.right=(int)((float)rectChildInitial.right*fAspectWidth+0.5);
		rectChildNew.top=(int)((float)rectChildInitial.top*fAspectHeight+0.5);
		rectChildNew.bottom=(int)((float)rectChildInitial.bottom*fAspectHeight+0.5);

		// Done!
		::CopyRect(lpRect, &rectChildNew);
	}
};


};	// namespace StingrayOTL

#endif // __OTLXXX_H__
