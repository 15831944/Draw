///////////////////////////////////////////////////////////////////////////////
// Convert.h
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


#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <oaidl.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

class Convert
{
public:
	inline static BOOL LPtoLP(HDC hDstDC, const int nSrcMM, SIZE& size);
	inline static BSTR Variant2BSTR(VARIANT* pVar);
};


BOOL Convert::LPtoLP(HDC hDstDC, const int nSrcMM, SIZE& size)
{
	int nDstMM = ::GetMapMode(hDstDC);
	int dpi_x = ::GetDeviceCaps(hDstDC, LOGPIXELSX);
	int dpi_y = ::GetDeviceCaps(hDstDC, LOGPIXELSY);

	SIZE szWndExt;
	::GetWindowExtEx(hDstDC, &szWndExt);

	if (nDstMM == nSrcMM)
		return TRUE;

	// First, convert to twips. A twip is 1/1440 of an inch.
	switch (nSrcMM)
	{
	case MM_TWIPS:
		// That was easy
		break;

	case MM_HIMETRIC:
		size.cx = (size.cx * 1440) / 2540;
		size.cy = (size.cy * 1440) / 2540;
		break;

	case MM_LOMETRIC:
		size.cx = (size.cx * 1440) / 254;
		size.cy = (size.cy * 1440) / 254;
		break;

	case MM_HIENGLISH:
		size.cx = (size.cx * 1440) / 1000;
		size.cy = (size.cy * 1440) / 1000;
		break;

	case MM_LOENGLISH:
		size.cx = (size.cx * 1440) / 100;
		size.cy = (size.cy * 1440) / 100;
		break;

	case MM_TEXT:
		size.cx = (size.cx * 1440) / dpi_x;
		size.cy = (size.cy * 1440) / dpi_y;
		break;

	case MM_ISOTROPIC:
	case MM_ANISOTROPIC:
		return FALSE;
	}

	// Now, convert to target mode
	switch (nDstMM)
	{
	case MM_TWIPS:
		// That was easy
		break;

	case MM_HIMETRIC:
		size.cx = (size.cx * 2540) / 1440;
		size.cy = (size.cy * 2540) / 1440;
		break;

	case MM_LOMETRIC:
		size.cx = (size.cx * 254) / 1440;
		size.cy = (size.cy * 254) / 1440;
		break;

	case MM_HIENGLISH:
		size.cx = (size.cx * 1000) / 1440;
		size.cy = (size.cy * 1000) / 1440;
		break;

	case MM_LOENGLISH:
		size.cx = (size.cx * 100) / 1440;
		size.cy = (size.cy * 100) / 1440;
		break;

	case MM_TEXT:
		size.cx = (size.cx * dpi_x) / 1440;
		size.cy = (size.cy * dpi_y) / 1440;
		break;

	case MM_ISOTROPIC:
	case MM_ANISOTROPIC:
		// Convert from twips to device units
		size.cx = (size.cx * dpi_x) / 1440;
		size.cy = (size.cy * dpi_y) / 1440;
		// Convert from device units to logical units
		size.cx = size.cx * szWndExt.cx;
		if (szWndExt.cx != 0)
			size.cx = size.cx / szWndExt.cx;
		size.cy = size.cy * szWndExt.cy;
		if (szWndExt.cy != 0)
			size.cy = size.cy / szWndExt.cy;
		break;
	}

	return TRUE;
}


BSTR Convert::Variant2BSTR(VARIANT* pVar)
{
	BSTR bstrResult = NULL;

	VARIANT strVal;
	::VariantInit(&strVal);

	HRESULT hrConvert = ::VariantChangeType(&strVal, pVar, 0, VT_BSTR);
	if (SUCCEEDED(hrConvert))
	{
		bstrResult = ::SysAllocString(strVal.bstrVal);
		::VariantClear(&strVal);
	}

	return bstrResult;
}

};	// namespace stingray::foundation
};	// namespace stingray

#endif  // __CONVERT_H__
