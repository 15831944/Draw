///////////////////////////////////////////////////////////////////////////////
// OtlUtil.h
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

#ifndef __OTLUTIL_H__
#define __OTLUTIL_H__

#ifndef __OTLBASE_H__
	#error otlutil.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// Message box functions

	inline int OtlMessageBox(CComBSTR bstr, LPCTSTR lpCaption, UINT uType=MB_OK|MB_ICONEXCLAMATION )
	{
		USES_CONVERSION;
		return ::MessageBox(NULL, 
							OLE2T(bstr), 
							lpCaption ? lpCaption : _T(""), 
							uType);
	}
 
	inline int OtlMessageBox(CComBSTR bstr, UINT nIDCaption=0, UINT uType=MB_OK|MB_ICONEXCLAMATION )
	{
		TCHAR szCaption[_MAX_PATH];
		LPCTSTR pszCaption = NULL;
		if(nIDCaption)
		{
#if (_ATL_VER < 0x0700)
			int nLoaded = ::LoadString(_Module.GetResourceInstance(), nIDCaption, szCaption, _MAX_PATH);
#else
			int nLoaded = ::LoadString(_AtlBaseModule.GetResourceInstance(), nIDCaption, szCaption, _MAX_PATH);
#endif
			OTLASSERT(nLoaded);
			pszCaption = szCaption;
		}
		return OtlMessageBox(bstr, pszCaption, uType);
	}

	inline int OtlMessageBox(UINT nID, UINT nIDCaption=0, UINT uType=MB_OK|MB_ICONEXCLAMATION)
	{

#if _ATL_VER >= 0x0300
		CComBSTR bstr;
		if( bstr.LoadString(nID) )
			return OtlMessageBox(bstr, nIDCaption, uType);
#else
		if(nID)
		{
			TCHAR szText[_MAX_PATH];
#if (_ATL_VER < 0x0700)
			int nLoaded = ::LoadString(_Module.GetResourceInstance(), nID, szText, _MAX_PATH);
#else
			int nLoaded = ::LoadString(_AtlBaseModule.GetResourceInstance(), nID, szText, _MAX_PATH);
#endif
			OTLASSERT(nLoaded);
			CComBSTR bstr(szText);
			return OtlMessageBox(bstr, nIDCaption, uType);
		}
#endif
		return 0;
	}


};	// namespace StingrayOTL

#endif // __OTLUTIL_H__
