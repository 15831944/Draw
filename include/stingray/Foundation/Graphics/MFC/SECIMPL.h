///////////////////////////////////////////////////////////////////////////////
// SECIMPL.h : Internal declarations for the SEC++ library
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

//	Author:		Don			05/15/96
//


#ifndef __SFL_SECIMPL_H__
#define __SFL_SECIMPL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

// Useful drawing functions ... these exist in the MFC from version 3 onwards.
#ifdef WIN32

#define FillSolidRect1(dc, rect, color) \
		(dc)->FillSolidRect(rect, color)
		
#define FillSolidRect2(dc, x, y, cx, cy, color) \
		(dc)->FillSolidRect(x, y, cx, cy, color)
		
#define Draw3dRect1(dc, rect, color1, color2) \
		(dc)->Draw3dRect(rect, color1, color2)
		
#define Draw3dRect2(dc, x, y, cx, cy, color1, color2) \
		(dc)->Draw3dRect(x, y, cx, cy, color1, color2)

#else // WIN32

extern void FillSolidRect1(CDC* pDC, LPCRECT lpRect, COLORREF color);
extern void FillSolidRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color);
extern void Draw3dRect1(CDC* pDC, LPCRECT lpRect, COLORREF color1, COLORREF color2);
extern void Draw3dRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color1,
						COLORREF color2);  
						
#endif // WIN32


#endif // __SFL_SECIMPL_H__
 
