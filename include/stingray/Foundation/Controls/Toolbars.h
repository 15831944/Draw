///////////////////////////////////////////////////////////////////////////////
// Toolbars.h : SFL Toolbar support
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
// Author:       George Shepherd
// Description:  Toolbars Support.
//


#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <Foundation\sflres.h>
#include <Foundation\Controls\AtlControls.h>

namespace stingray {
namespace foundation {


const int nToolbarID = 100;

template <typename _Base = CToolBarCtrl, typename _Traits = CToolBarWinTraits>
class CToolBarImpl: public CWindowImpl<CToolBarImpl<_Base, _Traits>, _Base, _Traits>
{
	typedef CToolBarImpl<_Base, _Traits > thisClass;
	typedef CWindowImpl<CToolBarImpl<_Base, _Traits>, _Base, _Traits> baseClass;
    
public:

	CToolBarImpl(bool bInitialSeparator = true): m_bInitialSeparator(bInitialSeparator)
	{}

	virtual ~CToolBarImpl()
	{}

	DECLARE_WND_SUPERCLASS(_T("OTLToolBarClass"), _Base::GetWndClassName());

    BEGIN_MSG_MAP(thisClass)
	END_MSG_MAP()


protected:

	bool m_bInitialSeparator;

protected:

	struct ToolBarResourceFormat
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;
		//WORD aItems[wItemCount]

		WORD* items()
			{ return reinterpret_cast<WORD*>(this+1); }
	};


public:

	// Create toolbar from resource

	HWND Create (
		HWND hWndParent, 
		RECT& rcPos, 
		UINT nResourceID, 
		UINT nID = nToolbarID, 
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		LPCTSTR szWindowName = NULL,
		LPVOID lpCreateParam = NULL
	)
	{
#if (_ATL_VER < 0x0700)
		HINSTANCE hResourceInst = _Module.GetResourceInstance();
#else
		HINSTANCE hResourceInst = _AtlBaseModule.GetResourceInstance();
#endif
		HRSRC hResource = ::FindResource(hResourceInst, MAKEINTRESOURCE(nResourceID), RT_TOOLBAR);
		if (hResource == NULL) return NULL;

		HGLOBAL hGlobal = ::LoadResource(hResourceInst, hResource);
		if (hGlobal == NULL) return NULL;

		ToolBarResourceFormat* pToolBarLayout = reinterpret_cast<ToolBarResourceFormat*>(::LockResource(hGlobal));
		if (pToolBarLayout == NULL) return NULL;
		ATLASSERT(pToolBarLayout->wVersion == 1);

		WORD* pItems = pToolBarLayout->items();
		int nItems = pToolBarLayout->wItemCount + (m_bInitialSeparator ? 1 : 0);
		TBBUTTON* pTBBtn = reinterpret_cast<TBBUTTON*>(_alloca(nItems * sizeof(TBBUTTON)));

		// set initial separator (half width)
		if (m_bInitialSeparator) {
			pTBBtn[0].iBitmap = 4;
			pTBBtn[0].idCommand = 0;
			pTBBtn[0].fsState = 0;
			pTBBtn[0].fsStyle = TBSTYLE_SEP;
			pTBBtn[0].dwData = 0;
			pTBBtn[0].iString = 0;
		}

		int nBmp = 0;
		for (int i = 0, j = m_bInitialSeparator ? 1 : 0; i < pToolBarLayout->wItemCount; i++, j++) {
			if(pItems[i] != 0) {
				pTBBtn[j].iBitmap = nBmp++;
				pTBBtn[j].idCommand = pItems[i];
				pTBBtn[j].fsState = TBSTATE_ENABLED;
				pTBBtn[j].fsStyle = TBSTYLE_BUTTON;
				pTBBtn[j].dwData = 0;
				pTBBtn[j].iString = 0;
			}
			else {
				pTBBtn[j].iBitmap = 8;
				pTBBtn[j].idCommand = 0;
				pTBBtn[j].fsState = 0;
				pTBBtn[j].fsStyle = TBSTYLE_SEP;
				pTBBtn[j].dwData = 0;
				pTBBtn[j].iString = 0;
			}
		}

		HWND hWnd = Create(hWndParent, rcPos, pTBBtn, nItems, nResourceID, nID, dwStyle, dwExStyle, szWindowName, lpCreateParam);

		return hWnd;
	}


	// Create() which allows one to set the Toolbar bitmap and buttons too

	HWND Create (
		HWND hWndParent, 
		RECT& rcPos, 
		LPTBBUTTON lpTBButtons,
		UINT nButtons,
		UINT nBmpID, 
		UINT nID = nToolbarID, 
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		LPCTSTR szWindowName = NULL,
		LPVOID lpCreateParam = NULL
	)
	{
		HWND hWnd = baseClass::Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
		ATLASSERT(::IsWindow(hWnd));
		SetButtonStructSize(sizeof(TBBUTTON));

		//Set the bitmap and buttons
		AddBitmap(nButtons, nBmpID);
		AddButtons(nButtons, lpTBButtons);
		AutoSize();
		return hWnd;
	}
};

typedef CWinTraits<	WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | 
					TBSTYLE_TOOLTIPS | CCS_TOP, 0> CToolBarWinTraits;

typedef CWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | 
					TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | CCS_TOP> CFlatToolBarTraits;

typedef CWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | 
					CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN | 
					TBSTYLE_TOOLTIPS | TBSTYLE_FLAT> CToolBarPaneTraits;

typedef CToolBarImpl<ATLControls::CToolBarCtrl, CToolBarWinTraits> CToolBar;
typedef CToolBarImpl<ATLControls::CToolBarCtrl, CFlatToolBarTraits> CFlatToolBar;


};	// namespace stingray::foundation
};	// namespace stingray

