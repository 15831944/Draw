///////////////////////////////////////////////////////////////////////////////
// ZoomImpl.h : SFL Windowing package 
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

#ifndef __ZOOMIMPL_H__
#define __ZOOMIMPL_H__

#if !defined(_SFL)
#define _SFL
#endif

#include "Foundation\GuidCast.h"
#include "Foundation\StructuredGraphics\Zoom.h"
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc IZoomImpl
//
//@class IZoomImpl | This class provides a default implementation of the
// <c IZoom> interface.
//
//@base public | IZoom

class FOUNDATION_API IZoomImpl : public IZoom
{
// Constructors/destructor
public:
	//@cmember,mfunc
	// Default constructor for IZoomImpl
	//@@end
	/* Default constructor for IZoomImpl*/
	IZoomImpl() :
		m_nZoomPctX(100),
		m_nZoomPctY(100)
	{
	}

// Attributes
protected:
	//@cmember
	/* Magnification value for X axis*/
	int m_nZoomPctX;
	//@cmember
	/* Magnification value for Y axis*/
	int m_nZoomPctY;

// Operations
public:

	// GUID map implements the QueryGuid() function
	BEGIN_GUID_MAP(IZoomImpl)
		GUID_ENTRY(IQueryGuid)
		GUID_ENTRY(IZoom)
	END_GUID_MAP

	//@cmember,mfunc
	// Set logical scaling as percent magnification.
	//@@rdesc Previous magnification setting
	//@@parm Zoom factor for X axis
	//@@parm Zoom factor for Y axis
	//@@end
	/* Set logical scaling as percent magnification*/
	virtual CSize SetMagnification(const int nPctX, const int nPctY)
	{
		CSize szPrevMag(m_nZoomPctX, m_nZoomPctY);
		m_nZoomPctX = nPctX;
		m_nZoomPctY = nPctY;
		return szPrevMag;
	}

	//@cmember,mfunc
	// Get logical scaling as percent magnification.
	//@@rdesc Zoom factor
	//@@end
	/* Get logical scaling as percent magnification*/
	virtual CSize GetMagnification() const
	{
		return CSize(m_nZoomPctX, m_nZoomPctY);
	}

	//@cmember,mfunc
	// Increase logical scaling by a percentage.
	//@@rdesc Previous magnification setting
	//@@parm Increase in magnification for X axis
	//@@parm Increase in magnification for Y axis
	//@@end
	/* Increase logical scaling by a percentage*/
	virtual CSize IncreaseMagnification(const int nPctX, const int nPctY)
	{
		CSize szMag(GetMagnification());
		szMag.cx += nPctX;
		szMag.cy += nPctY;
		return SetMagnification(szMag.cx, szMag.cy);
	}

	//@cmember,mfunc
	// Decrease logical scaling by a percentage.
	//@@rdesc Previous magnification setting
	//@@parm Decrease in magnification for X axis
	//@@parm Decrease in magnification for Y axis
	//@@end
	/* Decrease logical scaling by a percentage*/
	virtual CSize DecreaseMagnification(const int nPctX, const int nPctY)
	{
		CSize szMag(GetMagnification());
		szMag.cx -= nPctX;
		szMag.cy -= nPctY;
		return SetMagnification(szMag.cx, szMag.cy);
	}

	//@cmember,mfunc
	// Adjust window and viewport extents for magnification.
	//@@rdesc void
	//@@parm In,out parameter to receive adjusted extent value
	//@@parm In,out parameter to receive adjusted extent value
	//@@end
	/* Adjust window and viewport extents for magnification*/
	virtual void ZoomExtents(CSize& szWndExt, CSize& szVpExt) const
	{
		// routine breaks down if you scale beyond 1000%. 
		// need data normalization.
		// should really check zoom percentage to avoid invalid floating point numbers

		float fScaleWidth = 100.0f / m_nZoomPctX;
		float fScaleHeight = 100.0f / m_nZoomPctY;

		szWndExt.cx = static_cast<long>(szWndExt.cx * fScaleWidth * 1000);
		szWndExt.cx = (szWndExt.cx < 1) ? (1) : szWndExt.cx;
		szWndExt.cy = static_cast<long>(szWndExt.cy * fScaleHeight * 1000);
		szWndExt.cy = (szWndExt.cy < 1) ? (1) : szWndExt.cy;

		szVpExt.cx *= 1000;
		szVpExt.cy *= 1000;
	}
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __ZOOMIMPL_H__
