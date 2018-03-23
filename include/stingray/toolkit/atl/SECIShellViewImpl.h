///////////////////////////////////////////////////////////////////////////////
// SECIShellViewImpl.h
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

#if !defined(AFX_SECISHELLVIEWIMPL_H__1F27E3AC_C860_42B9_B3ED_CD35F06753AF__INCLUDED_)
#define AFX_SECISHELLVIEWIMPL_H__1F27E3AC_C860_42B9_B3ED_CD35F06753AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////
//SECIShellViewImpl<class T, class TPidlMgr>
// AutoDuck tag block block for SECIShellViewImpl 

//@doc SECIShellViewImpl
//@mdata LPITEMIDLIST    | SECIShellViewImpl | m_pPidl | A copy of the PIDL the instance of this class is attached to.

//@doc SECIShellViewImpl
//@mdata TPidlMgr*     | SECIShellViewImpl | m_pPidlMgr | A PIDL manager to help manage the PIDL.

//@doc SECIShellViewImpl
//@mdata CComPtr lt; IShellFolder gt;  | SECIShellViewImpl | m_spShellFolder | A smart IShellFolder interface pointer that points to
//the owner folder object.

//@doc SECIShellViewImpl
//@mdata CComPtr lt; IShellBrowser gt;  | SECIShellViewImpl | m_spShellBrowser | A smart IShellBrowser interface pointer that points to
//Explorer. It is saved out from the CreateViewWindow method.

//@doc SECIShellViewImpl
//@mdata HWND      | SECIShellViewImpl | m_hParentWnd | Windows handle to the parent window of the namespace extension.

//@doc SECIShellViewImpl
//@mdata HMENU      | SECIShellViewImpl | m_hMenu | A menu handle to store the menu of this namespace extension.

//@doc SECIShellViewImpl
//@mdata FOLDERSETTINGS    | SECIShellViewImpl | m_FolderSettings | Folder settings of the attached PIDL. It is saved from CreateViewWindow method.

//@doc SECIShellViewImpl
//@mdata UINT      | SECIShellViewImpl | m_uState | UI activation status. It is saved from UIActivate method call.

//@doc SECIShellViewImpl
//@mfunc  | SECIShellViewImpl | SECIShellViewImpl | Constructor. It creates a valid instance of PIDL manager class indicated in our template arguments. 
//Application can always assume the PIDL manager is valid.
//It also sets reference count to one and increases the lock count of _Module by one. In addition, the contructor
//will make a copy of the given PIDL and store the give IShellFolder pointer into a COM smart Interface pointer 
//object for later use. 
//@parm IShellFolder* | pShellFolder | The IShellFolder object that created this object.
//@parm  LPCITEMIDLIST | pidl | The PIDL this object will attach to.
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc virtual | SECIShellViewImpl |  ~SECShellViewImpl | Destructor. It will delete the PIDL and the PIDL manager and clean up the memory used by SECContextMenuItems
//in the command vector. It also decreases the lock count of _Module by one.
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | QueryInterface | This is the implementation one of IUnknown interface method. It returns valid interface only 
//if the IID is IUnknown, IOleWindow or IShellView. If you need expose other interface, you need to override this method.
//@rdesc HRESULT If succeeded return S_OK, otherwise E_NOINTERFACE.
//@parm REFIID | riid | Reference to IID of the interface requested.
//@parm  void** | ppvObj | Address of the interface pointer to accept the requested interface.
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | UIActivate | See IShellView::UIActivate in Win32 SDK for details. Default implementation in this class
//first check if the uState is the same as the old status. If they are the same, it does nothing and
//return S_OK, otherwise, it will save the new uState into m_uState variable. Generally, you should 
//override this method to add proper UI and remove the UI depending on the passing UI status before 
//saving the new UI state.
//and return S_OK.
//@rdesc HRESULT 
//@parm UINT | uState | Activation state
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | CreateViewWindow | See IShellView::CreateViewWindow in Win32 SDK for details. Default implementation in this class
//first saves the given IShellBrowser pointer and the folder settings, then obtains the m_hParentWnd from
//the IShellBrowser pointer. After that, it creates our view window object by calling Create method
//passing m_hParentWnd and the prcView rect to the create method. If everything goes well, this method
//will assign the valid window handle m_hWnd to *phWnd and return S_OK, otherwise, it will return E_FAIL.
//@rdesc HRESULT 
//@parm LPSHELLVIEW | pPrevView |
//@parm  LPCFOLDERSETTINGS | lpfs | 
//@parm  LPSHELLBROWSER | psb |
//@parm  LPRECT | prcView | 
//@parm  HWND* | phWnd |
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | DestroyViewWindow | See IShellView::DestroyViewWindow in Win32 SDK for details. Default implementation here first
//calls UIActivate with SVUIA_DEACTIVATE argument and then destory the menu and this window object and 
//finally release the IShellBrowser interface. 
//@rdesc HRESULT Return S_OK.
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | GetCurrentInfo | See IShellView::GetCurrentInfo in Win32 SDK for details. Default implementation return the value
//saved in the internal m_FolderSettings.
//@rdesc HRESULT Return S_OK
//@parm LPFOLDERSETTINGS | lpfs | A pointer to FOLDERSETTINGS struct to receive the folder settings.
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | OnSetFocus | Default Windows message WM_SETFOCUS handler. See Win32 SDK for details for the arguments.
//The default implementation call OnViewWindowActive of IShellBrowser if m_spShellBrowser is valid passing
//this object as IShellView interface it. Then the implementation call UIActivate with SVUIA_ACTIVATE_FOCUS
//argument and return 0.
//@rdesc HRESULT 
//@parm UINT | uMsg |
//@parm  WPARAM | wParam |
//@parm  LPARAM | lParam |
//@parm  BOOL& | bHandled |
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | OnKillFocus | Default Windows message WM_KILLFOCUS handler. See Win32 SDK for details for the arguments.
//The default implementation calls UIActivate with SVUIA_ACTIVATE_NOFOCUS argument and return 0.
//@rdesc HRESULT 
//@parm UINT | uMsg |
//@parm  WPARAM | wParam |
//@parm  LPARAM | lParam |
//@parm  BOOL& | bHandled |
//@xref<c SECIShellViewImpl>

//@doc SECIShellViewImpl
//@mfunc HRESULT | SECIShellViewImpl | OnActivate | Default Windows message WM_ACTIVATE handler. See Win32 SDK for details of the arguments. 
//The default implementation calls UIActivate with SVUIA_ACTIVATE_FOCUS argument and return 0.
//@rdesc HRESULT 
//@parm UINT | uMsg |
//@parm  WPARAM | wParam |
//@parm  LPARAM | lParam |
//@parm  BOOL& | bHandled |
//@xref<c SECIShellViewImpl>

// adinsert AutoDuck insertion point for SECIShellViewImpl 
//@doc SECIShellViewImpl 
//@class SECIShellViewImpl
//@comm This class is a wrapper of IShellView interface. It derived from both IShellView interface
//and CWindowImpl class. This class provides implementation for the method in IUnknown 
//and also provides reference counting for this object. It also provided most common used
//implementation for the view class used in the namespace extension. 
//For a complete documentation of IShellView, please refer to windows SDK or MSDN from Microsoft.
//@tcarg class | T | The derived class
//@tcarg class | TPidlMgr | The SECPidlMgr derived class
//@base public | CWindowImpl
//@base public | IShellView
template<typename T, typename TPidlMgr>
class SECIShellViewImpl : 
		public CWindowImpl<SECIShellViewImpl<T,TPidlMgr>,CWindow,CControlWinTraits>,
		public IShellView 
{
protected:
	DWORD					m_nRefCount;
	//@cmember
	/* Store PIDL of the current view item */
	LPITEMIDLIST			m_pPidl;
	//@cmember
	/* Pointer to a Pidl mamanger */
	TPidlMgr*				m_pPidlMgr;
	//@cmember
	/* A pointer to the folder object */
	CComPtr<IShellFolder>	m_spShellFolder;

	//@cmember
	/* A pointer to shell browser object */
	CComPtr<IShellBrowser>	m_spShellBrowser;
	//@cmember
	/* Parent window handle */
	HWND					m_hParentWnd;
	//@cmember
	/* Menu handle */
	HMENU					m_hMenu;
	//@cmember
	/* Folder setting structure */
	FOLDERSETTINGS			m_FolderSettings;
	//@cmember
	/* State of current item */
	UINT					m_uState;

BEGIN_MSG_MAP(SECIShellViewImpl)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
END_MSG_MAP()

public:

	//IUnknown
	inline STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
	{
		*ppvObj = NULL;

		//IUnknown
		if(IsEqualIID(riid, IID_IUnknown))
			*ppvObj = this;
		//IOleWindow
		else if(IsEqualIID(riid, IID_IOleWindow))
			*ppvObj = (IOleWindow*)this;

		//IShellView
		else if(IsEqualIID(riid, IID_IShellView))
			*ppvObj = (IShellView*)this;

		if(*ppvObj)
		{
		   (*(LPUNKNOWN*)ppvObj)->AddRef();
		   return S_OK;
		}
		return E_NOINTERFACE;
	}

	inline STDMETHOD_ (DWORD, AddRef)()
	{
	   m_nRefCount++;
	   return m_nRefCount;
	}
	inline STDMETHOD_ (DWORD, Release)()
	{
	   m_nRefCount--;
	   if( 0 == m_nRefCount )
	   {
		   delete this;
		   return 0;
	   }
	   return m_nRefCount;
	}

public:
	//@cmember
	/* Constructor */
	inline SECIShellViewImpl(IShellFolder* pShellFolder, LPCITEMIDLIST pidl)
	{
		m_pPidl = NULL;
		m_pPidlMgr = new TPidlMgr;
		
		// We always need a good PIDL manager. If we can not get one, we fail here!
		if( m_pPidlMgr == NULL )
		{
			delete this; 
			return;
		}
		if( pidl != NULL )
			m_pPidl = m_pPidlMgr->Copy(pidl);

		m_spShellFolder = pShellFolder; //Will automatically add ref count

		m_hParentWnd = NULL;
		m_hMenu = NULL;
		memset(&m_FolderSettings, 0, sizeof(FOLDERSETTINGS));
		m_uState = SVUIA_DEACTIVATE;

		m_nRefCount = 1;

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt++;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt++;
		_pAtlModule->Unlock();
#endif

	}
	virtual ~SECIShellViewImpl()
	{
		if( m_pPidl != NULL )
			m_pPidlMgr->Delete(m_pPidl);

		if( m_pPidlMgr != NULL )
			delete m_pPidlMgr;

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt--;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt--;
		_pAtlModule->Unlock();
#endif
	}

public:
	//IOleWindow
   inline STDMETHOD (GetWindow) (HWND* phWnd)
   {
	   *phWnd = m_hWnd;
	   return S_OK;
   }
   inline STDMETHOD (ContextSensitiveHelp) (BOOL /*bEnterMode*/)
   {
	   return E_NOTIMPL;
   }

	//IShellView methods
	inline STDMETHOD (TranslateAccelerator) (LPMSG /*pMsg*/)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD (EnableModeless) (BOOL /*bEnable*/)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD (UIActivate) (UINT uState)
	{
		if( m_uState == uState )
			return S_OK;
		
		//If deactivate, clear the UI
		if( uState == SVUIA_DEACTIVATE )
		{
			if( m_hMenu != NULL )
			{
				m_spShellBrowser->SetMenuSB(NULL, NULL, NULL);
				m_spShellBrowser->RemoveMenusSB(m_hMenu);
				::DestroyMenu(m_hMenu);
				m_hMenu = NULL;
			}
		}
		else
		{
			// If we are active, add some menu here
		}

		//Save the state
		m_uState = uState;

		return S_OK;
	}
	inline STDMETHOD (Refresh) ()
	{
		// To do: Add code to redraw the view window
		return S_OK;
	}
	inline STDMETHOD (CreateViewWindow) (LPSHELLVIEW /*pPrevView*/, LPCFOLDERSETTINGS lpfs, LPSHELLBROWSER psb, LPRECT prcView, HWND* phWnd)
	{
		m_spShellBrowser = psb;
		m_FolderSettings = *lpfs;
		if( m_spShellBrowser )
			m_spShellBrowser->GetWindow(&m_hParentWnd);

		*phWnd = NULL;
		m_hWnd = NULL;

		if( m_hParentWnd != NULL)
			Create(m_hParentWnd, *prcView);

		if( m_hWnd == NULL )
			return E_FAIL;

		*phWnd = m_hWnd;

		return S_OK;
	}
	inline STDMETHOD (DestroyViewWindow)()
	{
		//Make absolutely sure all our UI is cleaned up.
		UIActivate(SVUIA_DEACTIVATE);

		if(m_hMenu)
			::DestroyMenu(m_hMenu);

		if( m_hWnd != NULL )
			DestroyWindow();

		//release the shell browser object
		m_spShellBrowser.Release();

		return S_OK;
	}
	inline STDMETHOD (GetCurrentInfo) (LPFOLDERSETTINGS lpfs)
	{
		*lpfs = m_FolderSettings;
		return S_OK;
	}
	inline STDMETHOD (AddPropertySheetPages) (DWORD /*dwReserved*/, LPFNADDPROPSHEETPAGE /*lpfn*/, LPARAM /*lParam*/)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD (SaveViewState)()
	{
		return S_OK;
	}
	inline STDMETHOD (SelectItem) (LPCITEMIDLIST /*pidlItem*/, UINT /*uFlags*/)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD (GetItemObject) (UINT /*uItem*/, REFIID /*riid*/, LPVOID* ppvObj)
	{
		*ppvObj = NULL;
		return E_NOTIMPL;
	}
public:
	//Message Handler
	//@cmember
	/* WM_SETFOCUS message handler */
	inline LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if( m_spShellBrowser )
			m_spShellBrowser->OnViewWindowActive((IShellView *)this);

		UIActivate(SVUIA_ACTIVATE_FOCUS);

		return 0;
	}
	//@cmember
	/* WM_KILLFOCUS message handler */
	inline LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		UIActivate(SVUIA_ACTIVATE_NOFOCUS);
		return 0;
	}
	//@cmember
	/* WM_ACTIVATE message handler */
	inline LRESULT OnActivate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		UIActivate(SVUIA_ACTIVATE_FOCUS);
		return 0;
	}
};

#endif // !defined(AFX_SECISHELLVIEWIMPL_H__1F27E3AC_C860_42B9_B3ED_CD35F06753AF__INCLUDED_)
