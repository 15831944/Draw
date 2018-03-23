///////////////////////////////////////////////////////////////////////////////
// Otltab.h
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

#ifndef __OTLTAB_H__
#define __OTLTAB_H__

#ifndef __OTLBASE_H__
	#error otltab.h requires otlbase.h to be included first
#endif

#include <commctrl.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{
/////////////////////////////////////////////////////////////////////////////
// COtlAppBarTabs

class COtlAppBarTabs : public CWindowImpl<COtlAppBarTabs>
{
public:
DECLARE_WND_SUPERCLASS(NULL, _T("SysTabControl32"))

BEGIN_MSG_MAP(COtlAppBarTabs)
	MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

	inline COtlAppBarTabs()
	{
		m_cxTabMax = 150;		// max button width
		m_cxBorder = 10;	// depends on style, this works for flat tracked button. Can be 3 for non tracked.
		m_cyBorder = 3;		// spacing betwen rows. appears to be constant for button styles.
		m_cxIndent = 4;		// spacing between icon and text in owner draw button
	}

	virtual ~COtlAppBarTabs()
	{
	}

	inline BOOL Create( HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,  
					DWORD dwStyle=WS_VISIBLE|WS_CHILD,
					DWORD dwCtrlStyle=TCS_BUTTONS|TCS_FLATBUTTONS|TCS_FIXEDWIDTH|TCS_FOCUSONBUTTONDOWN|
					TCS_FORCELABELLEFT|TCS_HOTTRACK|TCS_TOOLTIPS|TCS_OWNERDRAWFIXED|TCS_MULTILINE,
					DWORD dwExStyle=0,
					UINT nID=0)
	{
		if(!CWindowImpl<COtlAppBarTabs>::Create(hWndParent, rcPos, szWindowName, dwStyle|dwCtrlStyle, dwExStyle, nID))
			return FALSE;

		AlwaysTip();	// we want tooltips even if not active
		return TRUE;
	}
	
	inline HWND GetToolTipCtrl() { return (HWND)TabCtrl_GetToolTips(m_hWnd); }

	inline void AlwaysTip(BOOL bTip=TRUE)
	{
		OTLASSERT(m_hWnd);
		if(GetStyle() & TCS_TOOLTIPS)
		{
			HWND hTips = TabCtrl_GetToolTips(m_hWnd);
			if( hTips)
			{
				CWindow wndTip(hTips);
				wndTip.ModifyStyle(bTip ? 0 : TTS_ALWAYSTIP, bTip ? TTS_ALWAYSTIP : 0);
				wndTip.Detach();
			}
		}

	}

	inline int AddTab(UINT uIndex, LPTSTR strLabel, int iImage = -1, BOOL bRefreshTips=TRUE)
	{
		OTLASSERT(m_hWnd);
		TCITEM tci;
		::ZeroMemory(&tci, sizeof(tci));
		tci.mask = TCIF_TEXT | TCIF_IMAGE;
		tci.pszText = strLabel;
		tci.iImage = iImage;
		int nIndex = TabCtrl_InsertItem(m_hWnd, uIndex, &tci);
		if(bRefreshTips)
			RefreshToolTips();
		return nIndex;
	}

	inline BOOL RemoveTab(UINT uIndex, BOOL bRefreshTips=TRUE)
	{
		BOOL bRet = TabCtrl_DeleteItem(m_hWnd, uIndex);
		if(bRefreshTips)
			RefreshToolTips();
		return bRet;
	}

	inline BOOL SetImageList(HIMAGELIST hImg)
	{
		OTLASSERT(hImg);
		return (BOOL)(SEC_INT)TabCtrl_SetImageList(m_hWnd, hImg);
	}

	inline BOOL GetItemRect( int iItem, RECT& rc)
	{
		return TabCtrl_GetItemRect(m_hWnd, iItem, &rc);
	}

	inline int GetCYBorder() { return m_cyBorder; }

	inline void RefreshToolTips()
	{
		OTLASSERT(m_hWnd);
		RemoveAllToolTips();
		HWND hwndTip = TabCtrl_GetToolTips(m_hWnd);
		static TCHAR strTip[80];
		if(hwndTip)
		{
			TOOLINFO ti;
			TCITEM tci;
			for (int index = 0; index < TabCtrl_GetItemCount(m_hWnd); index++)
			{
				::ZeroMemory(&tci, sizeof(TCITEM));
				tci.mask = TCIF_TEXT;
				tci.pszText = strTip;
				tci.cchTextMax = 80;
				TabCtrl_GetItem(m_hWnd, index, &tci);

				::ZeroMemory(&ti, sizeof(TOOLINFO));
				ti.cbSize = sizeof(TOOLINFO);
				ti.hwnd = m_hWnd;
				ti.uId = 100 + index;
				_tcscpy(strTip, tci.pszText);
				ti.lpszText = strTip;
				TabCtrl_GetItemRect(m_hWnd, index, &ti.rect);

				::SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&ti );
			}
		}
	}

	inline void RemoveAllToolTips()
	{
		OTLASSERT(m_hWnd);
		HWND hwndTip = TabCtrl_GetToolTips(m_hWnd);
		if(hwndTip)
		{
			UINT nCount = (UINT)::SendMessage(hwndTip, TTM_GETTOOLCOUNT, 0, 0);
			for(UINT iTool=0; iTool < nCount; iTool++)
			{
				TOOLINFO ti;
				::ZeroMemory(&ti, sizeof(TOOLINFO));
				ti.cbSize = sizeof(TOOLINFO);
				if(::SendMessage(hwndTip, TTM_ENUMTOOLS, (WPARAM)iTool, (LPARAM)&ti ))
				DeleteToolTip(ti.uId);
			}
		}
	}

	inline void DeleteToolTip(SEC_UINT uId)
	{
		OTLASSERT(m_hWnd);
		HWND hwndTip = TabCtrl_GetToolTips(m_hWnd);
		if(hwndTip)
		{
			TOOLINFO ti;
			::ZeroMemory(&ti, sizeof(TOOLINFO));
			ti.cbSize = sizeof(TOOLINFO);
			ti.hwnd = m_hWnd;
			ti.uId = uId;
			::SendMessage(hwndTip, TTM_DELTOOL, 0, (LPARAM)&ti );
		}
	}

	inline int GetFocusItem() { return TabCtrl_GetCurFocus(m_hWnd);}

	virtual void DrawItem(DRAWITEMSTRUCT* pItem)
	{
		RECT rcText;
		::CopyRect(&rcText, &pItem->rcItem);
		HDC hdc = pItem->hDC;
		::FillRect(hdc, &rcText, (HBRUSH)(COLOR_3DFACE+1));
		// retrieve the item from the tab control
		TCITEM tci;
		static TCHAR strItem[256];
		tci.mask = TCIF_TEXT | TCIF_IMAGE;
		tci.pszText = strItem;
		tci.cchTextMax = 256;
		HIMAGELIST hImageList = TabCtrl_GetImageList(m_hWnd);
		if(TabCtrl_GetItem(m_hWnd, pItem->itemID, &tci))
		{
			if(tci.iImage != -1 && hImageList)
			{
				int cx;
				int cy;
				ImageList_GetIconSize(hImageList, &cx, &cy);
				int topOffset = (rcText.bottom - rcText.top - cy)/2;
				ImageList_Draw( hImageList, 
								 tci.iImage,
								 hdc, 
								 pItem->rcItem.left,
								 pItem->rcItem.top + topOffset,
								 ILD_NORMAL);
					rcText.left += cx;
			}

			rcText.left += m_cxIndent;
			// determine if the text is too long for the rect
			RECT rcCopy;
			::CopyRect(&rcCopy, &rcText);
			::DrawText(hdc, tci.pszText, -1, &rcCopy,
				DT_LEFT | DT_VCENTER | DT_CALCRECT | DT_SINGLELINE);
			// save flag as lparam so we can check it for tooltip
			tci.mask = TCIF_PARAM;
			if(rcCopy.right > rcText.right)	// too long, need tooltip
				tci.lParam = 1;
			else							// text fits, no tooltip
				tci.lParam = 0;
			TabCtrl_SetItem(m_hWnd, pItem->itemID, &tci);
			// draw the text
			::DrawText(hdc, tci.pszText, -1, &rcText,
				DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS | DT_SINGLELINE);
		}

	}

	inline LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled;
		uMsg;
		wParam;
		DRAWITEMSTRUCT* pItem = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
		OTLASSERT(pItem);
		DrawItem(pItem);
		return 0;
	}

	inline void RecalcTabLayout(BOOL bVertical=FALSE)
	{
		OTLASSERT(m_hWnd);
		if(TabCtrl_GetItemCount(m_hWnd) == 0)
			return;
		RECT rc;
		GetClientRect(&rc);
		int iWidth;
		if(bVertical)
		{
			// use the entire width
			iWidth = rc.right - rc.left;
		}
		else	// horizontal
		{
			// make it fit in the number of rows we have
			RECT rcTab;
			iWidth = m_cxTabMax;
			if(TabCtrl_GetItemRect(m_hWnd, 0, &rcTab))	// measure item 0
			{
				int nItems = TabCtrl_GetItemCount(m_hWnd);
				int cyTab = rcTab.bottom - rcTab.top;
				if( cyTab <= 0 ) cyTab = 22;
				int nRows = (rc.bottom - rc.top) / cyTab;
				int nItemsPerRow = nRows > 0 ? nItems/nRows : 0;
				if(nItemsPerRow * nRows < nItems)
					nItemsPerRow++;
				// account for the space between items
				int nOverhead = ((nItemsPerRow-1) * m_cxBorder);
				// calc width of 1 item
				iWidth = (rc.right-rc.left- nOverhead)/nItemsPerRow;
				if(iWidth > m_cxTabMax )	// max
					iWidth = m_cxTabMax;
			}
		}

		TabCtrl_SetItemSize(m_hWnd, iWidth, 0);
		UpdateTipRects();
	}

	inline void UpdateTipRects()
	{
		HWND hwndTip = TabCtrl_GetToolTips(m_hWnd);
		if(hwndTip)
		{
			TOOLINFO ti;
			for(int index = 0; index < TabCtrl_GetItemCount(m_hWnd); index++)
			{
				::ZeroMemory(&ti, sizeof(TOOLINFO));
				ti.cbSize = sizeof(TOOLINFO);
				ti.hwnd = m_hWnd;
				ti.uId = 100 + index;
				// first, see if a tooltip is necessary
				TCITEM tci;
				tci.mask = TCIF_PARAM;
				TabCtrl_GetItem(m_hWnd, index, &tci);
				if(tci.lParam)	// need tooltip
					TabCtrl_GetItemRect(m_hWnd, index, &ti.rect);
				else
					::SetRect(&ti.rect, -100, -100, -100, -100);
				::SendMessage(hwndTip, TTM_NEWTOOLRECT, 0, (LPARAM)&ti );
			}
		}
	}

	inline void SetMaxWidth(int nMax) { m_cxTabMax = nMax; }
	inline void DeselectAll(BOOL bExcludeFocus=FALSE){ TabCtrl_DeselectAll(m_hWnd, bExcludeFocus);}


public:
	int m_cxTabMax;
	int m_cyBorder;
	int m_cxBorder;
	int m_cxIndent;

};

};	// namespace StingrayOTL 

#endif __OTLTAB_H__
