///////////////////////////////////////////////////////////////////////////////
// OtlIDeskBandImpl.h
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

#ifndef __OTLDESKBAND_H__
#define __OTLDESKBAND_H__

#ifndef __OTLBASE_H__
	#error otlideskbandimpl.h requires otlbase.h to be included first
#endif

#include <shlobj.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{
/////////////////////////////////////////////////////////////////////////////
// OtlIDeskBandImpl<T>
//
// requires T base class members:
// HWND m_hWnd
//
// or can be CWindowImpl derivative

template <class T>
class ATL_NO_VTABLE OtlIDeskBandImpl : public IDeskBand
{
public:
	inline OtlIDeskBandImpl() : m_dwBandID(0), m_dwViewMode(0)
	{
		::ZeroMemory(&m_bandInfo, sizeof(DESKBANDINFO));
		// note ptMinSize.x must be 0 for Autohide to work in
		// IE Theater mode ( full screen )
		m_bandInfo.ptMinSize.x = 0;	
		m_bandInfo.ptMinSize.y = 0;
		m_bandInfo.ptMaxSize.x = -1;
		m_bandInfo.ptMaxSize.y = -1;
		m_bandInfo.ptIntegral.x = 1;
		m_bandInfo.ptIntegral.y = 1;
		lstrcpyW(m_bandInfo.wszTitle, L"Stingray OTL Band Object");
		m_bandInfo.dwModeFlags = DBIMF_NORMAL | DBIMF_VARIABLEHEIGHT;
	}

public:
	DWORD	m_dwBandID;
	DWORD	m_dwViewMode;
	DESKBANDINFO m_bandInfo;

public:
// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(OtlIDeskBandImpl)


// IOleWindow
    inline STDMETHOD(GetWindow)(HWND* phwnd)
	{
		T* pBase = static_cast<T*>(this);
		*phwnd = pBase->m_hWnd;
		return S_OK;
	}
   inline  STDMETHOD(ContextSensitiveHelp)(BOOL bEnterMode)
	{
		return E_NOTIMPL;
	}
// IDockingWindow
    inline STDMETHOD(ShowDW)(BOOL fShow)
	{
		T* pBase = static_cast<T*>(this);
	    if(pBase->m_hWnd)
			::ShowWindow(pBase->m_hWnd, fShow ? SW_SHOW : SW_HIDE);
	    return S_OK; 
	}
    inline STDMETHOD(CloseDW)(DWORD dwReserved)
	{
		T* pBase = static_cast<T*>(this);
		ShowDW(FALSE);
		if(::IsWindow(pBase->m_hWnd))
		   DestroyWindow(pBase->m_hWnd);
		pBase->m_hWnd = NULL;
		return S_OK;
	}
    inline STDMETHOD(ResizeBorderDW)(LPCRECT prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
	{
		// This method is never called for Band Objects.
		return E_NOTIMPL;
	}
//IDeskBand
    inline STDMETHOD(GetBandInfo)(DWORD dwbandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
	{
		if(pdbi)
		{
		   m_dwBandID = dwbandID;
		   m_dwViewMode = dwViewMode;

		   if(pdbi->dwMask & DBIM_MINSIZE)
			  {
			  pdbi->ptMinSize.x = m_bandInfo.ptMinSize.x;
			  pdbi->ptMinSize.y = m_bandInfo.ptMinSize.y;

			  }

		   if(pdbi->dwMask & DBIM_MAXSIZE)
			  {
			  pdbi->ptMaxSize.x = m_bandInfo.ptMaxSize.x;
			  pdbi->ptMaxSize.y = m_bandInfo.ptMaxSize.y;
			  }

		   if(pdbi->dwMask & DBIM_INTEGRAL)
			  {
			  pdbi->ptIntegral.x = m_bandInfo.ptIntegral.x;
			  pdbi->ptIntegral.y = m_bandInfo.ptIntegral.y;
			  }

		   if(pdbi->dwMask & DBIM_ACTUAL)
			  {
			  pdbi->ptActual.x = m_bandInfo.ptActual.x;
			  pdbi->ptActual.y = m_bandInfo.ptActual.y;
			  }

		   if(pdbi->dwMask & DBIM_TITLE)
			  {
			  OTLASSERT(m_bandInfo.wszTitle);
			  lstrcpyW(pdbi->wszTitle, m_bandInfo.wszTitle);
			  }

		   if(pdbi->dwMask & DBIM_MODEFLAGS)
			  {
			  pdbi->dwModeFlags = m_bandInfo.dwModeFlags;
			  }
   
		   if(pdbi->dwMask & DBIM_BKCOLOR)
			  {
			  pdbi->crBkgnd = m_bandInfo.crBkgnd;
			  }
		}
		return S_OK;
	}

};

}; // namespace StingrayOTL 

#endif // __OTLDESKBAND_H__
