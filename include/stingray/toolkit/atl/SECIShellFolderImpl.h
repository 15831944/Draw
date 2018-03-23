///////////////////////////////////////////////////////////////////////////////
// SECIShellFolderImpl.h
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

#if !defined(AFX_SECISHELLFOLDERIMPL_H__8C3CA215_408C_4D22_B4F9_72D1F7080CBE__INCLUDED_)
#define AFX_SECISHELLFOLDERIMPL_H__8C3CA215_408C_4D22_B4F9_72D1F7080CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
// AutoDuck tag block block for SECIShellFolderImpl 
//@doc SECIShellFolderImpl
//@mdata LPITEMIDLIST      | SECIShellFolderImpl | m_pPidl | A PIDL of the current folder

//@doc SECIShellFolderImpl
//@mdata TPidlMgr*       | SECIShellFolderImpl | m_pPidlMgr | A PILD manager that used to manage the PIDL.

//@doc SECIShellFolderImpl
//@mdata CComPtr lt; IMalloc gt;     | SECIShellFolderImpl | m_spMalloc | A smart IMalloc interface pointer used to 
//manage memory allocation.

//@doc SECIShellFolderImpl
//@mfunc | SECIShellFolderImpl | SECIShellFolderImpl | Constructor. It creates a valid PIDL manager of class TPidlMgr in the template argument and
//also obtains a valid IMalloc interface pointer from the shell. If for some reason, a valid PIDL 
//manager or IMalloc pointer cannot be created, this object will fail.
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc void | SECIShellFolderImpl | GetPidlName | This function get the string name from a given PIDL. The name will be place in the 
//passed in buffer. It is called from inside GetDisplayNameOf method. If you want more control
//to GetDisplayNameOf, you can override that function.
//@rdesc void 
//@parm LPCITEMIDLIST | pidl | The PIDL to the calling function is request for string name
//@parm  LPTSTR | lpszOut | Buffer to accept the name for the PIDL
//@parm  DWORD | nSize | The size of the passed in buffer.
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | EnumObjects | Create a new instance of IEnumIDList implementation class from the heap. If the creation is successfule,
//the method calls CreateEnumIDList method to create the enum ID list passing the current PIDL and the dwFlags into
//this function. If CreateEnumIDList succeeded, the method assigns the new instance to *ppEnumIDList arguments 
//and return S_OK, otherwise return E_OUTOFMEMORY or E_FAIL. You most probaly will not need to override this
//method.<nl>
//See IShellFolder::EnumObjects in Win32 SDK for details of the arguments.
//@rdesc HRESULT 
//@parm HWND | hwndOwner |
//@parm  DWORD | dwFlags |
//@parm  LPENUMIDLIST* | ppEnumIDList |
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | BindToObjects | This function deletes the existing PIDL and makes a copy of the passed in PIDL and save it
//as the current PIDL in m_pPidl member. It then calls QueryInterface of this object to find requested 
//interface. You most probably will not need to override this method.<nl>
//See IShellFolder::BindToObject in Win32 SDK for details about the arguments. 
//@rdesc HRESULT 
//@parm LPCITEMIDLIST | pidl |
//@parm  LPBC | pbcReserved |
//@parm  REFIID | riid |
//@parm  LPVOID* | ppvObj |
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | CreateViewObject | This method creates a new instance from the heap of your IShellView implementation class given in the template argument
//of this class. If the creation succeeded, it will call the new instance to QueryInterface for this method, otherwise return 
//E_OUTOFMEMORY. When the method create the new instance of your IShellView implementation class, it pass the "this" pointer 
//of this object and the current PIDL member m_pPidl to the constructor of your IShellView implementation class.
//You most probably will not need to override this method.<nl>
//See IShellView::CreateViewObject in Win32 SDK for details.
//@rdesc HRESULT Return S_OK if succeeded, otherwise return E_OUTOFMEMORY or other error code from the
//QueryInterface method of your IShellView implementation class.
//@parm HWND | hwndOwner | Not used in the default implementation.
//@parm  REFIID | riid | IID of the requested interface.
//@parm  LPVOID* | ppvObj | Addresss of the interface pointer requested.
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | GetAttributesOf | See IShellFolder::GetAttributesOf in Win32 SDK for details. The default implementation 
//just blindly assigns SFGAO_HASSUBFOLDER + SFGAO_FOLDER to *pdwAttribs argument. You almost always have 
//to override this function in your namespace extension.
//@rdesc HRESULT 
//@parm  UINT | uCount |
//@parm  LPCITEMIDLIST* | apidls |
//@parm  ULONG* | pdwAttribs |
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | GetUIObjectsOf | See IShellFolder::GetUIObject in Win32 SDK for details. No implementation is provided in this class.
//However, if your namespace extension want to support other optional interface, you will have to override this
//function. The code generated by wizard will always override this function.
//@rdesc HRESULT 
//@parm HWND | hwndOwner |
//@parm  UINT | uCount |
//@parm  LPCITEMIDLIST* | pPidl |
//@parm  REFIID | riid |
//@parm  LPUINT | puReserved |
//@parm  LPVOID* | ppvObj |
//@xref <c SECIShellFolderImpl>

//@doc SECIShellFolderImpl
//@mfunc HERSULT | SECIShellFolderImpl | GetDisplayNameOf | See IShellFolder::GetDisplayNameOf in Win32 SDK for details. The default implementation
//call GetPidlName to obtain a string name for the given PIDL. If you don't have any special 
//requirement, you may only need to override the GetPidlName virtual function.
//@rdesc HRESULT 
//@parm LPCITEMIDLIST | pidl |
//@parm  DWORD | dwFlags |
//@parm  LPSTRRET | lpName |
//@xref <c SECIShellFolderImpl>

// adinsert AutoDuck insertion point for SECIShellFolderImpl 
//@doc SECIShellFolderImpl 
//@class SECIShellFolderImpl
//@comm This class is a wrapper of IShellFolder interface. This 
//class is the central class in the our namespace extension framework. IShellFolder interface
//is the first interface Explorer will request from namespace extension. This class provides
//most common implementation for most of the methods in the IShellFolder. This class has to 
//derived before it can be used. At the bare minimal, the derived class should provide the
//implementation of IUnknown and also provide reference counting. Using CComObjectRootEx and
//CoComClass from ATL is the general way to accomplish both of these. Generally, you may only
//need to override the GetPidlName virtual function and CompareIDS, GetUIObject and GetAttributesOf methods
//of IShellFolder interface. You will rarely need to touch CreateViewObject and EnumObjects 
//methods. The BindToStorage method is not currently used by the shell. <nl>
// This template class requires four template arguments, the first should be the 
//derived class, the second one is the IShellView implementation class, the third is the IEnumIDList
//implementation class and the last one is the PIDL manager class that derived from SECPidlMgr template 
//class. <nl>
//Note that only one instance of our IShellFolder implementation class is created in the whole 
//namespace extension, so we can place some global setting inside the IShellFolder implementation 
//class and expose a extra interface to let other component to access and change settings. Here is
//a good example using this idea. As you know, that the view in the right pane of the Explorer is
//constantly created and destroyed. In order to store the sort settings of our list view, we cannot
//store the settings inside the IShellView implementation class. But we can store the settings in the IShellFoler
//implementation class, we then expose a custom interface from our IShellFolder implementation class.
//Since our view hold a pointer to our IShellView interface, you can query the custom interface to 
//get and change the settings. <nl>
//In the default implementation of the related interfaces, only SECIShellViewImpl class stored a pointer
//to IShellFolder interface, so if you need to access the value in IShellFolder implementation component
//from other interface implementation you need to store the IShellFolder interface in your derived class. <nl>
//<nl>
//For a complete documentation of IShellFolder, please refer to windows SDK or MSDN from Microsoft.
//@tcarg class | T | The dervied class
//@tcarg class | TIShellView | The IShellView implementation class
//@tcarg class | TIEnumIDList | The IEnumIDList implementation class
//@tcarg class | TPidlMgr | SECPidlMgr derived class
//@base public | IShellFolder
template<typename T, typename TIShellView, typename TIEnumIDList, typename TPidlMgr>
class SECIShellFolderImpl : public IShellFolder
{
public:
	//@cmember
	/* PIDL of this folder */
	LPITEMIDLIST					m_pPidl;
	//@cmember
	/* A pointer to PIDL manager */
	TPidlMgr*						m_pPidlMgr;
	//@cmember
	/* A smart pointer of IMalloc */
	CComPtr<IMalloc>				m_spMalloc;

public:
	//@cmember
	/* Constructor */
	inline SECIShellFolderImpl()
	{
		m_pPidl = NULL;
		m_pPidlMgr = new TPidlMgr;
		if( m_pPidlMgr == NULL )
		{
			delete this;
			return;
		}
		if( FAILED(SHGetMalloc(&m_spMalloc)))
		{
			delete this;
			return;
		}
	}
	virtual ~SECIShellFolderImpl()
	{
		if( m_pPidl != NULL )
			m_pPidlMgr->Delete(m_pPidl);
		if( m_pPidlMgr != NULL )
			delete m_pPidlMgr;
		//m_spMalloc will be released automatically
	}

	//@cmember
	/* Get string name of a give PIDL */
	virtual void GetPidlName(LPCITEMIDLIST pidl, LPTSTR lpszOut, DWORD nSize)
	{		
		//Here we just put the pidl as hex value.
		LPITEMIDLIST pTmp = m_pPidlMgr->GetLastItem(pidl);
		TCHAR szText[50] = {0};
		_stprintf(szText, _T("pidl=0x%x"), (DWORD)(pTmp->mkid.abID[0])); 
		_tcsncpy(lpszOut, szText, nSize);
	}

	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(SECIShellFolderImpl)

	//IShellFolder methods
	inline STDMETHOD (ParseDisplayName) (HWND /*hwndOwner*/, LPBC /*lpcReserved*/, LPOLESTR /*lpDisplayName*/, LPDWORD /*pdwEaten*/, LPITEMIDLIST* /*pPidlNew*/, LPDWORD /*pdwAttribs*/)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD (EnumObjects) (HWND /*hwndOwner*/, DWORD dwFlags, LPENUMIDLIST* ppEnumIDList)
	{
		*ppEnumIDList = NULL;

		TIEnumIDList* pEnum = new TIEnumIDList;
		if( pEnum == NULL )
			return E_OUTOFMEMORY;
		if( !pEnum->CreateEnumIDList(m_pPidl, dwFlags) )
		{
			delete pEnum;
			return E_FAIL;
		}
		*ppEnumIDList = pEnum;
		
		return S_OK;
	}
	inline STDMETHOD (BindToObject) (LPCITEMIDLIST pidl, LPBC /*pbcReserved*/, REFIID riid, LPVOID* ppvObj)
	{
		if(m_pPidl != NULL )
			m_pPidlMgr->Delete(m_pPidl);

		*ppvObj = NULL;

		m_pPidl = m_pPidlMgr->Copy(pidl);
		T* pT = static_cast<T*>(this);
		return pT->QueryInterface(riid, ppvObj);
	}
	inline STDMETHOD (BindToStorage) (LPCITEMIDLIST /*pidl*/, LPBC /*pbcReserved*/, REFIID /*riid*/, LPVOID* /*ppvObj*/)
	{
		return E_NOTIMPL;
	}

	inline STDMETHOD (CompareIDs) (LPARAM /*lParam*/, LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
	{
		if( pidl1 == NULL && pidl2 == NULL )
			return 0;
		if( pidl1 == NULL && pidl2 != NULL )
			return 1;
		if( pidl1 != NULL && pidl2 == NULL  )
			return -1;

		// Do the memory compare, since we can make sense of the data
		if( m_pPidlMgr->GetLastItem(pidl1)->mkid.cb 
			== m_pPidlMgr->GetLastItem(pidl2)->mkid.cb)
			return memcmp(m_pPidlMgr->GetLastItem(pidl1)->mkid.abID,
						m_pPidlMgr->GetLastItem(pidl2)->mkid.abID,
						m_pPidlMgr->GetLastItem(pidl1)->mkid.cb);
		if( m_pPidlMgr->GetLastItem(pidl1)->mkid.cb 
			< m_pPidlMgr->GetLastItem(pidl2)->mkid.cb)
			return 1;
		return -1;
	}

	inline STDMETHOD (CreateViewObject) (HWND /*hwndOwner*/, REFIID riid, LPVOID* ppvObj)
	{
		T* pT = static_cast<T*>(this);
		TIShellView* pView = new TIShellView(pT, m_pPidl);
		if( pView == NULL )
			return E_OUTOFMEMORY;

		HRESULT hr = pView->QueryInterface(riid, ppvObj); //Ref count increased again

		//We need to decrease the ref count to one
		pView->Release();

		return hr;
	}

	inline STDMETHOD (GetAttributesOf) (UINT /*uCount*/, LPCITEMIDLIST* /*apidls*/, ULONG* pdwAttribs)
	{
		// TODO : Return appropriate ShellFolder attributes in pdwAttribs
		// By default the following ORed value suffices.
		//
		*pdwAttribs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;
		return S_OK;
	}

	inline STDMETHOD (GetUIObjectOf) (HWND /*hwndOwner*/, UINT /*uCount*/, LPCITEMIDLIST* /*pPidl*/, REFIID /*riid*/, LPUINT /*puReserved*/, LPVOID* ppvObj)
	{
		*ppvObj = NULL;
		return E_NOTIMPL;
	}

	inline STDMETHOD (GetDisplayNameOf) (LPCITEMIDLIST pidl, DWORD /*dwFlags*/, LPSTRRET lpName)
	{
		T* pT = static_cast<T*>(this);

		TCHAR szText[MAX_PATH] = {0};

		pT->GetPidlName(pidl, szText, MAX_PATH);

		// Must convert string to Unicode, so allocate a wide character string
		int cchOleStr = (int)_tcslen(szText) + 1;
		lpName->pOleStr = reinterpret_cast<LPWSTR>(m_spMalloc->Alloc(cchOleStr * sizeof(WCHAR)));
		if(!lpName->pOleStr)
		  return E_OUTOFMEMORY;

		lpName->uType = STRRET_WSTR;

#ifdef _UNICODE
		_tcsncpy(lpName->pOleStr, szText, cchOleStr);
#else
		mbstowcs(lpName->pOleStr, szText, cchOleStr);
#endif
		return S_OK;
	}

	inline STDMETHOD (SetNameOf)(HWND /*hwndOwner*/, LPCITEMIDLIST /*pidl*/, LPCOLESTR /*lpName*/, DWORD /*dw*/, LPITEMIDLIST* /*pPidlOut*/)
	{
		return E_NOTIMPL;
	}
};

#endif // !defined(AFX_SECISHELLFOLDERIMPL_H__8C3CA215_408C_4D22_B4F9_72D1F7080CBE__INCLUDED_)
