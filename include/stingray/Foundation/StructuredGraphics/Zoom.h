///////////////////////////////////////////////////////////////////////////////
// Zoom.h : SFL Windowing package 
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
// Author:       Jeff Boenig
// Description:  Support for zooming windows
//

#pragma once

#ifndef __ZOOM_H__
#define __ZOOM_H__

#if !defined(_SFL)
#define _SFL
#endif

#include "Foundation\GuidCast.h"
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc IZoom
//
//@class IZoom | This interface defines functions for setting the
// magnification of an object that supports zooming. The <mf IZoom::ZoomExtents>
// function does the work of adjusting a device context to account for the
// zoom magnification.
//
//@base public | IQueryGuid

class __declspec(uuid("8407B2B4-4B5E-11d3-AF1B-006008AFE059")) IZoom : public IQueryGuid
{
public:

	//@cmember,mfunc
	// Set logical scaling as percent magnification.
	//@@rdesc Previous magnification setting
	//@@parm Zoom factor for X axis
	//@@parm Zoom factor for Y axis
	//@@end
	/* Set logical scaling as percent magnification*/
	virtual CSize SetMagnification(const int nPctX, const int nPctY) = 0;

	//@cmember,mfunc
	// Get logical scaling as percent magnification.
	//@@rdesc Zoom factor
	//@@end
	/* Get logical scaling as percent magnification*/
	virtual CSize GetMagnification() const = 0;

	//@cmember,mfunc
	// Increase logical scaling by a percentage.
	//@@rdesc Previous magnification setting
	//@@parm Increase in magnification for X axis
	//@@parm Increase in magnification for Y axis
	//@@end
	/* Increase logical scaling by a percentage*/
	virtual CSize IncreaseMagnification(const int nPctX, const int nPctY) = 0;

	//@cmember,mfunc
	// Decrease logical scaling by a percentage.
	//@@rdesc Previous magnification setting
	//@@parm Decrease in magnification for X axis
	//@@parm Decrease in magnification for Y axis
	//@@end
	/* Decrease logical scaling by a percentage*/
	virtual CSize DecreaseMagnification(const int nPctX, const int nPctY) = 0;

	//@cmember,mfunc
	// Adjust window and viewport extents for magnification.
	//@@rdesc void
	//@@parm In,out parameter to receive adjusted extent value
	//@@parm In,out parameter to receive adjusted extent value
	//@@end
	/* Adjust window and viewport extents for magnification*/
	virtual void ZoomExtents(CSize& szWndExt, CSize& szVpExt) const = 0;
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __ZOOM_H__
