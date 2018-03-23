///////////////////////////////////////////////////////////////////////////////
// TabBarModel.h : interfaces for the SECTabBarSysModel, SECTabBarPresModel classes.
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
// Author:      Prakash Surendra and Jay Gopalakrishnan
// Description:  ShortcutBar - MVCModel implementation
//

#ifndef __TABBAR_MODEL_H__
#define __TABBAR_MODEL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Foundation\Mvc\MvcModel.h"
#include "Foundation\Mvc\MvcController.h"
#include "Foundation\Mvc\MvcVisualComponent.h"
#include <string.h>
#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>
#include <StingrayExportDefs.h>

namespace stingray {

using namespace foundation;

class SECTabBarBase : public IQueryGuid
{
public:
	// IQueryGuid implementation
	inline virtual bool QueryGuid(REFGUID /*guid*/, void ** /*ppvObj*/)	{ return false;	}

	inline SECTabBarBase(LPCTSTR lpszLabel) {
		m_pszLabel = NULL;
		m_hIcon = NULL;
		m_bVisualComp = FALSE;
		SetLabel(lpszLabel);
	}

	inline virtual ~SECTabBarBase() {
		if(m_pszLabel)
			delete m_pszLabel;
		if(m_hIcon)
			::DestroyIcon(m_hIcon);
	}

	inline TCHAR* GetLabel() {	return m_pszLabel; }
	
	inline void SetLabel(LPCTSTR lpszLabel) {
		assert(lpszLabel);
		if(m_pszLabel)
			delete m_pszLabel;
		m_pszLabel = new TCHAR[_tcslen(lpszLabel)+1];
		_tcscpy(m_pszLabel, lpszLabel);
//		memcpy(m_pszLabel, lpszLabel, _tcslen(lpszLabel)+1);
	}
	
	inline HICON GetIcon() { return m_hIcon; }
	inline void SetIcon(HICON hIcon) {	m_hIcon = hIcon; }
	inline BOOL IsVisualComp() {	return m_bVisualComp;	}

protected:
// Attributes
	TCHAR*	m_pszLabel;
	HICON	m_hIcon;
	BOOL	m_bVisualComp;

	friend class SECTabBarSysModel;
};

template<class T>
class SECTabBar : public SECTabBarBase
{
	typedef T _client;

public:
	// IQueryGuid implementation
	inline virtual bool QueryGuid(REFGUID guid, void **ppvObj)	{ return false; }	

	inline SECTabBar()	{}
	inline SECTabBar(_client& client, LPCTSTR lpszLabel) : SECTabBarBase(lpszLabel), m_Client(client)	{}
	inline virtual ~SECTabBar()	{}

	inline _client& GetClient()	{ return m_Client; }	
	
protected:
	_client& m_Client;

friend class SECTabBarSysModel;
};

typedef SECTabBar<HWND> CTabBarWnd;

// The SECTabBarMvc class serves as an adapter for the common API between the MVC visual component and viewport types
template<class T>
class SECTabBarMvc : public SECTabBar<T>, public IVisual, public IBounds2D
{
public:
	inline SECTabBarMvc()	{}
	inline SECTabBarMvc(T& client) : SECTabBar<T>(client, _T(" ")) {}
	inline SECTabBarMvc(T& client, LPCTSTR lpszLabel) : SECTabBar<T>(client, lpszLabel) {}
	inline virtual ~SECTabBarMvc()	{}

	// IQueryGuid implementation
	inline virtual bool QueryGuid(REFGUID guid, void **ppvObj) { return m_Client.QueryGuid(guid, ppvObj); }

	// IRefCount implementation
	inline virtual ULONG STDMETHODCALLTYPE AddRef() { return m_Client.AddRef(); }
	inline virtual ULONG STDMETHODCALLTYPE Release() { return m_Client.Release(); }

	// IVisual implementation
	inline virtual void Draw(CDC* pCDC)	{ m_Client.Draw(pCDC); }
	inline virtual void OnPrepareDC(CDC* pCDC)	{ m_Client.OnPrepareDC(pCDC); }
	inline virtual void OnCleanupDC(CDC* pCDC)	{ m_Client.OnCleanupDC(pCDC); }

	// IBounds2D implementation
	inline virtual CSize GetSize() const { return m_Client.GetSize(); }
	inline virtual CSize SetSize(int cx, int cy) { return m_Client.SetSize(cx, cy); }
	inline virtual CRect GetBounds() const { return m_Client.GetBounds(); }
	inline virtual CPoint GetOrigin() const { return m_Client.GetOrigin();	}
	inline virtual CPoint SetOrigin(int x, int y) { return m_Client.SetOrigin(x,y); }
	inline virtual CPoint MoveOrigin(int xOff,int yOff) { return m_Client.MoveOrigin(xOff, yOff); }
};


// SECTabBarMessage - Updates observers with info related to changes in the tab bar model
class SECTabBarMessage : public CRefCountImpl<IMessage>
{
// IRefCount implementation
//	IMPLEMENTS_REFCOUNTING();

public:
// IQueryGuid implementation
	inline virtual bool QueryGuid(REFGUID guid, void **ppvObj)	{
		if(guid == __uuidof(IMessage))
		{
			*ppvObj=static_cast<IMessage*>(this);
			AddRef();
			return true;
		}
		*ppvObj=NULL;
		return false;
	};

	// IMessage implementation
	// No other message type is currently being used. 
	inline virtual unsigned int GetTypeID() const		{ return 0; };	
	inline virtual void Sprint(CString& /*strCmd*/)	{};

public:
	inline SECTabBarMessage(UINT nTabBarVerb, SECTabBarBase* pTabBar, DWORD dwExtra = 0)	{
		m_nTabBarVerb = nTabBarVerb;
		m_pTabBar = pTabBar;
		m_dwExData = dwExtra;
		m_ulRefCount=0;
	}	
	inline virtual ~SECTabBarMessage()	{};

	enum { TABBAR_ACTIVATE = 0, TABBAR_ADD, TABBAR_INSERT, TABBAR_REMOVE, TABBAR_UPDATE };

	UINT m_nTabBarVerb;
	SECTabBarBase* m_pTabBar;
	DWORD m_dwExData;
};

// SECTabBarSysModel - System model for the ShortcutBar/TabWindow components
class SECTabBarSysModel  : public CMvcModel
{
typedef std::vector<SECTabBarBase*>	TabBarVector;
typedef CMvcController<CMvcModel, Visual2D> CMvcControllerInst;

public:
	inline SECTabBarSysModel()
	{
		m_nActiveIndex = -1;
	}

	inline virtual ~SECTabBarSysModel()
	{
		// Iterate collection and destroy all tabbar objects
		TabBarVector::iterator iter = m_vectTabBar.begin();
		while(iter != m_vectTabBar.end())
		{
			delete *iter;
			iter++;
		}
	}

	inline int GetTabBarCount()	{ return (int)m_vectTabBar.size(); }

	inline SECTabBarBase* GetTabBarAt(int nIndex)
	{
		assert(nIndex >= 0 && nIndex < GetTabBarCount());
		return m_vectTabBar.at(nIndex);
	}

	inline int GetTabBarIndex(SECTabBarBase* pTabBar)
	{
		assert(pTabBar);
		int nSz = GetTabBarCount();
		for(int i=0; i<nSz; i++)
		{
			if(m_vectTabBar.at(i) == pTabBar)
				return i;
		}
		return -1;
	}

	inline int GetActiveIndex()	{ return m_nActiveIndex; };

	template<class TVisual>
	inline int AddTabBarVisual(TVisual* pClient, LPCTSTR lpszLabel)
	{
		assert(pClient != NULL);
		SECTabBarBase* pTabBar = new SECTabBarMvc<TVisual> (*pClient, lpszLabel);
		assert(pTabBar);
		pTabBar->m_bVisualComp = TRUE;
		m_vectTabBar.push_back(pTabBar);
		if(m_nActiveIndex == -1)
			m_nActiveIndex = 0;
		return GetTabBarCount();
	}

	inline int AddTabBarWnd(HWND& hWndClient, LPCTSTR lpszLabel)
	{
		assert(::IsWindow(hWndClient));
		SECTabBarBase* pTabBar = new SECTabBar<HWND> (hWndClient, lpszLabel);
		assert(pTabBar);
		m_vectTabBar.push_back(pTabBar);
		if(m_nActiveIndex == -1)
			m_nActiveIndex = 0;
		return GetTabBarCount();
	}

	template<class TVisual>
	inline int InsertTabBarVisual(int nIndex, TVisual* pClient, LPCTSTR lpszLabel)
	{
		assert(pClient != NULL);
		SECTabBarBase* pTabBar = new SECTabBarMvc<TVisual>(*pClient, lpszLabel);
		assert(pTabBar);
		pTabBar->m_bVisualComp = TRUE;
		if (nIndex < GetTabBarCount()) 
		{
			// QA: 32095 - Replacing m_vectTabBar[nIndex]
			m_vectTabBar.insert(m_vectTabBar.begin() + nIndex, pTabBar);
		}else
		{
			m_vectTabBar.push_back(pTabBar);
			nIndex = GetTabBarCount();
		}
		if(nIndex <= m_nActiveIndex)
			m_nActiveIndex++;
		return 0;
	}

	inline int InsertTabBarWnd(int nIndex, HWND& hWndClient, LPCTSTR lpszLabel)
	{
		assert(::IsWindow(hWndClient));
		SECTabBarBase* pTabBar = new CTabBarWnd(hWndClient, lpszLabel);
		assert(pTabBar);

		if (nIndex < GetTabBarCount()) 
		{
			// QA: 32095 - Replacing m_vectTabBar[nIndex]
			m_vectTabBar.insert(m_vectTabBar.begin() + nIndex, pTabBar);
		}else
		{
			m_vectTabBar.push_back(pTabBar);
			nIndex = GetTabBarCount();
		}

		if(nIndex <= m_nActiveIndex)
			m_nActiveIndex++;

		return nIndex;
	}

	inline void RemoveTabBar(int nIndex)
	{
		assert(nIndex >= 0 && nIndex < GetTabBarCount());

		// If nIndex is the currently active tabbar, then activate the previous/next tabbar
		if(nIndex == m_nActiveIndex)
		{
			if(nIndex-1 >= 0)
				m_nActiveIndex = nIndex-1;
			else if(nIndex+1 < GetTabBarCount())
					m_nActiveIndex = nIndex+1;
			else m_nActiveIndex = -1;

			NotifyObservers(SECTabBarMessage::TABBAR_REMOVE, GetTabBarAt(nIndex), m_nActiveIndex);	
		}
		
		// Remove the tab from the collection
		SECTabBarBase* pTabBar = GetTabBarAt(nIndex);
		// QA: 32095 - Replacing m_vectTabBar[nIndex]
		m_vectTabBar.erase(m_vectTabBar.begin() + nIndex);
		delete pTabBar;

		if(nIndex <= m_nActiveIndex)
			m_nActiveIndex--;
	}

	inline void ActivateTabBar(int nActivate, BOOL bUpdate = FALSE)
	{
		assert(nActivate >= 0 && nActivate < GetTabBarCount());
		int nPrev = m_nActiveIndex;
		m_nActiveIndex = nActivate;
		
		NotifyObservers(SECTabBarMessage::TABBAR_ACTIVATE, GetTabBarAt(nActivate), nPrev);
		if(bUpdate)
			NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);	
	}

protected:
	inline void NotifyObservers(UINT nMsg, SECTabBarBase* pTabBar, DWORD dwExtra = 0)
	{
		SECTabBarMessage* pMsg = new SECTabBarMessage(nMsg, pTabBar, dwExtra);
		pMsg->AddRef();
	 	UpdateAllObservers(NULL, pMsg);
		pMsg->Release();
	}

protected:
	TabBarVector m_vectTabBar;
	int m_nActiveIndex;
};


class SECTabBarVisual
{
public:
	inline SECTabBarVisual()	{ m_hBrush = NULL; }
	inline virtual ~SECTabBarVisual()	{};

protected:
	HFONT		m_hFont;			// Font used for the tabbar label
	HBRUSH		m_hBrush;			// Brush used for painting the tabbar background
	COLORREF	m_clrText;			// Text color of the tabbar
	COLORREF	m_clrBkgnd;			// Background color of the tabbar
	BOOL		m_bDisabled;		// Disabled if true

friend class SECTabBarPresModel;
};


// Label Alignment constants
#define SEC_TABBAR_LBLALIGNLEFT			0
#define SEC_TABBAR_LBLALIGNCENTER		1
#define SEC_TABBAR_LBLALIGNRIGHT		2

// TabBar styles
#define SEC_TABBAR_VERT				0x00000001		// Default alignment
#define SEC_TABBAR_HORZ				0x00000002		// To be implemented
#define SEC_TABBAR_BARCURSOR		0x00000004
#define SEC_TABBAR_NOANIMATE		0x00000080
#define SEC_TABBAR_NOHILIGHT		0x00000200
#define SEC_TABBAR_CNTXTMENU		0x00000400

#define SEC_TABBAR_STYLES			(SEC_TABBAR_VERT		|\
									 SEC_TABBAR_HORZ		|\
									 SEC_TABBAR_BARCURSOR   |\
									 SEC_TABBAR_NOHILIGHT   |\
									 SEC_TABBAR_NOANIMATE   |\
									 SEC_TABBAR_CNTXTMENU) 	
								

// SECTabBarPresModel - Presentation model for the ShortcutBar/TabWindow components. The presentation model
// observes the system model.
class SECTabBarPresModel  : public CMvcModel, public IObserver
{
typedef std::vector<SECTabBarVisual*>	VectTabBarVisual;

public:
	inline SECTabBarPresModel()
	{
		// Create the system model and add this instance as an observer
		m_pSysModel = new SECTabBarSysModel;
		m_pSysModel->AddObserver(this);
		
		m_nLblAlgn = SEC_TABBAR_LBLALIGNCENTER;
		
		ConstructGDIObjects();
	}

	inline virtual ~SECTabBarPresModel()
	{
		DestroyGDIObjects();

		// Iterate collection and destroy all SECTabBarVisual objects
		VectTabBarVisual::iterator iter = m_vectVisual.begin();
		while(iter != m_vectVisual.end())
		{
			delete *iter;
			iter++;
		}

		if(m_pSysModel)
			delete m_pSysModel;
	}

	// IQueryGuid, IRefCount 
	inline bool QueryGuid(REFGUID guid, void **ppvObj)	{ return CMvcModel::QueryGuid(guid, ppvObj); }
	inline ULONG STDMETHODCALLTYPE AddRef()	{ return CMvcModel::AddRef(); }
	inline ULONG STDMETHODCALLTYPE Release()	{ return CMvcModel::Release();	}

	inline virtual void OnUpdate(ISubject* pSubject, IMessage* pMsg)
	{
		// Pass on the notification to all observers of this subject
		pMsg->AddRef();
		UpdateAllObservers(NULL, pMsg);
		pMsg->Release();
	}

	template<class TVisual>
	inline int AddTabBarVisual(TVisual* pClient, LPCTSTR lpszLabel, BOOL bUpdate)
	{
		int nTab = m_pSysModel->AddTabBarVisual(pClient, lpszLabel);		
		m_vectVisual.push_back(CreateTabBarVisual());
		NotifyObservers(SECTabBarMessage::TABBAR_ADD, GetTabBarAt(nTab-1));
		if(bUpdate)
			NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);
		return nTab;
	}

	inline virtual int AddTabBarWnd(HWND& hWndClient, LPCTSTR lpszLabel, BOOL bUpdate)
	{
		int nTab = m_pSysModel->AddTabBarWnd(hWndClient, lpszLabel);	
		m_vectVisual.push_back(CreateTabBarVisual());

		NotifyObservers(SECTabBarMessage::TABBAR_ADD, GetTabBarAt(nTab-1));
		if(bUpdate)
			NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);

		return nTab;
	}

	template<class TVisual>
	inline int InsertTabBarVisual(int nIndex, TVisual* pClient, LPCTSTR lpszLabel)
	{
		m_pSysModel->InsertTabBarVisual(nIndex, pClient, lpszLabel);
		if (nIndex < m_vectVisual.size()) 
		{
			// QA: 32095 - Replacing m_vectVisual[nIndex]
			m_vectVisual.insert(m_vectVisual.begin() + nIndex, CreateTabBarVisual());
		}else
		{
			m_vectVisual.push_back(CreateTabBarVisual());
		}
		NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);
		return nIndex;
	}
	inline virtual int InsertTabBarWnd(int nIndex, HWND& hWndClient, LPCTSTR lpszLabel)
	{
		m_pSysModel->InsertTabBarWnd(nIndex, hWndClient, lpszLabel);	
		if (nIndex < m_vectVisual.size())
		{
			//QA: 32095 - Replacing m_vectVisual[nIndex]
			m_vectVisual.insert(m_vectVisual.begin() + nIndex, CreateTabBarVisual());
		}else
		{
			m_vectVisual.push_back(CreateTabBarVisual());
		}

		NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);

		return nIndex;
	}

	inline virtual void RemoveTabBar(int nIndex)
	{
		m_pSysModel->RemoveTabBar(nIndex);

		// Remove the SECTabBarVisual associated with this tabbar from the visual vector and delete it.	
		SECTabBarVisual* pVisual = GetTabBarVisualAt(nIndex);
		// QA: 32095 - Replacing m_vectVisual[nIndex]
		m_vectVisual.erase(m_vectVisual.begin() + nIndex);
		delete pVisual;

		NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);	
	}

	inline virtual void ActivateTabBar(int nActivate, BOOL bUpdate = FALSE)	{ m_pSysModel->ActivateTabBar(nActivate, bUpdate); }

	inline void SetNotifyWnd(HWND hWnd)
	{
		assert(::IsWindow(hWnd));
		m_hWndNotify = hWnd;
	}

	inline HWND GetNotifyWnd()	{ return m_hWndNotify; }

	inline DWORD SetTabBarStyle(DWORD dwStyle)
	{
		DWORD dwOld = m_dwStyle;
		m_dwStyle = dwStyle;
		return dwOld;
	}

	inline DWORD GetTabBarStyle()	{ return m_dwStyle; }

	inline void SetTabBarIcon(int nIndex, HICON hIcon)
	{
		SECTabBarBase* pTabBar = GetTabBarAt(nIndex);
		pTabBar->SetIcon( ::CopyIcon(hIcon) );
	}

	inline void SetTabBarIcon(int nIndex, UINT nIDIcon)
	{
		HICON hIcon = (HICON)::LoadImage(hResInstance, MAKEINTRESOURCE(nIDIcon), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		SECTabBarBase* pTabBar = GetTabBarAt(nIndex);
		pTabBar->SetIcon(hIcon);
	}

	inline HICON GetTabBarIcon(int nIndex)
	{
		SECTabBarBase* pTabBar = GetTabBarAt(nIndex);
		return pTabBar->GetIcon();
	}

	inline void SetTabBarLabel(int nIndex, LPCTSTR lpszLabel)
	{
		SECTabBarBase* pTabBar = GetTabBarAt(nIndex);
		pTabBar->SetLabel(lpszLabel);
	}

	inline LPCTSTR GetTabBarLabel(int nIndex)	{ return GetTabBarAt(nIndex)->GetLabel(); }

	inline void SetTabBarFont(HFONT hFont, int nBarIndex)
	{
		// if nBarIndex = -1, then all tabbars have the same font
		if(nBarIndex == -1)
			SetAttribHelper(hFont, offsetof(SECTabBarVisual, m_hFont));		
		else
			GetTabBarVisualAt(nBarIndex)->m_hFont = hFont;
	}

	inline HFONT GetTabBarFont(int nBarIndex)
	{
		SECTabBarVisual* pTabBarVisual = GetTabBarVisualAt(nBarIndex);
		return pTabBarVisual->m_hFont;
	}

	inline void SetTabBarBrush(HBRUSH hBrush, int nBarIndex)
	{
		if(nBarIndex == -1)
			SetAttribHelper(hBrush, offsetof(SECTabBarVisual, m_hBrush));
		else
			GetTabBarVisualAt(nBarIndex)->m_hBrush = hBrush;	
	}

	inline HBRUSH GetTabBarBrush(int nBarIndex)
	{
		SECTabBarVisual* pTabBarVisual = GetTabBarVisualAt(nBarIndex);
		return pTabBarVisual->m_hBrush;
	}

	inline void SetTabBarBkColor(COLORREF clrBk, int nBarIndex)
	{
		if(nBarIndex == -1)
			SetAttribHelper(clrBk, offsetof(SECTabBarVisual, m_clrBkgnd));
		else
			GetTabBarVisualAt(nBarIndex)->m_clrBkgnd = clrBk;
	}

	inline COLORREF GetTabBarBkColor(int nBarIndex)
	{
		SECTabBarVisual* pTabBarVisual = GetTabBarVisualAt(nBarIndex);
		return pTabBarVisual->m_clrBkgnd;
	}

	inline void SetTabBarTextColor(COLORREF clrText, int nBarIndex)
	{
		if(nBarIndex == -1)
			SetAttribHelper(clrText, offsetof(SECTabBarVisual, m_clrText));
		else
			GetTabBarVisualAt(nBarIndex)->m_clrText = clrText;
	}

	inline COLORREF GetTabBarTextColor(int nBarIndex)
	{
		SECTabBarVisual* pVisual = GetTabBarVisualAt(nBarIndex);
		return pVisual->m_clrText;
	}

	inline HCURSOR SetTabBarCursor(HCURSOR hCursor)
	{
		HCURSOR hCurOld = m_hBarCursor;
		m_hBarCursor = hCursor;
		return hCurOld;
	}

	inline HCURSOR GetTabBarCursor()	{ return m_hBarCursor; }

	inline void SetLabelAlignment(UINT nAlign)
	{
		if(m_nLblAlgn != nAlign)
		{
			m_nLblAlgn = nAlign;
			NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);
		}
	}

	inline UINT GetLabelAlignment()	{ return m_nLblAlgn; }

	inline void DisableTabBar(int nIndex, BOOL bDisable)
	{
		SECTabBarVisual* pVisual = GetTabBarVisualAt(nIndex);
		if(pVisual->m_bDisabled != bDisable)
		{
			pVisual->m_bDisabled = bDisable;
			NotifyObservers(SECTabBarMessage::TABBAR_UPDATE, NULL);
		}
	}

	inline BOOL IsTabBarEnabled(int nIndex)	{ return !GetTabBarVisualAt(nIndex)->m_bDisabled; }

	inline int GetTabBarCount()	{ return m_pSysModel->GetTabBarCount(); }

	inline SECTabBarBase* GetTabBarAt(int nIndex)	{ return m_pSysModel->GetTabBarAt(nIndex); }
	
	inline int GetTabBarIndex(SECTabBarBase* pTabBar)	{ return m_pSysModel->GetTabBarIndex(pTabBar); }

	inline int GetActiveIndex()	{ return m_pSysModel->GetActiveIndex(); }	

protected:
	inline SECTabBarVisual* CreateTabBarVisual()
	{
		SECTabBarVisual* pVisual = new SECTabBarVisual;
		assert(pVisual);
		pVisual->m_hFont = HFONT(m_defFont);
		pVisual->m_clrBkgnd = ::GetSysColor(COLOR_BTNFACE);
		pVisual->m_clrText = ::GetSysColor(COLOR_BTNTEXT);
		pVisual->m_bDisabled = FALSE;
		
		return pVisual;
	}

	inline SECTabBarVisual* GetTabBarVisualAt(int nIndex)
	{
		assert(nIndex >= 0 && nIndex < m_vectVisual.size());
		return m_vectVisual.at(nIndex);
	}

	inline void ConstructGDIObjects()
	{
		// Construct the default font object
		LOGFONT lf;
		lf.lfHeight = 15;
		lf.lfWidth = 0;
		lf.lfEscapement = 0;	
		lf.lfOrientation = 0;
		lf.lfWeight = FW_NORMAL;
		lf.lfItalic = FALSE;
		lf.lfUnderline = FALSE;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = ANSI_CHARSET;
		lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lf.lfQuality = DEFAULT_QUALITY;
		lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
		_tcsncpy(lf.lfFaceName, _T("Arial"), LF_FACESIZE);
		m_defFont.CreateFontIndirect( &lf );

		// Load the 'hand' cursor from the SFL resources.
		m_hBarCursor = ::LoadCursor(hResInstance, MAKEINTRESOURCE(IDC_BARS_HAND));
		assert(m_hBarCursor);
	}

	inline void DestroyGDIObjects()
	{
		if(HFONT(m_defFont) != NULL)
			m_defFont.DeleteObject();

		::DestroyCursor(m_hBarCursor);
	}

	inline void NotifyObservers(UINT nMsg, SECTabBarBase* pTabBar, DWORD dwExtra = 0)
	{
		SECTabBarMessage* pMsg = new SECTabBarMessage(nMsg, pTabBar, dwExtra);
		pMsg->AddRef();
 		UpdateAllObservers(NULL, pMsg);
		pMsg->Release();
	}

	// SetAttribHelper iterates the tabbar collection and sets the value for the SECTabBarVisual 
	// attribute existing at the BYTE offset specified by the 'nOffset' parameter.
	template<class TAttribType>
	inline void SetAttribHelper(TAttribType attribVal, size_t nOffset)
	{
		int nSz = (int)m_vectVisual.size();
		for(int i=0; i<nSz; i++)
			*(TAttribType*)((BYTE*)GetTabBarVisualAt(i) + nOffset) = attribVal;
	}

protected:
	SECTabBarSysModel* m_pSysModel;
	// Vector of SECTabBarVisual objects
	VectTabBarVisual m_vectVisual;

	CGDIFont	m_defFont;		// Default font for the tabbars.
	HCURSOR     m_hBarCursor;	// Default 'Hand' cursor for the tabbars
	UINT		m_nLblAlgn;
	DWORD		m_dwStyle;
	HWND        m_hWndNotify;
};

}; // namespace stingray


#endif // __TABBAR_MODEL_H__
