///////////////////////////////////////////////////////////////////////////////
// SECIQueryInfoImpl.h
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

#if !defined(AFX_SECIQUERYINFOIMPL_H__948BA547_8E7F_4CAD_89B6_2B9961F7B1B8__INCLUDED_)
#define AFX_SECIQUERYINFOIMPL_H__948BA547_8E7F_4CAD_89B6_2B9961F7B1B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
// AutoDuck tag block block for SECIQueryInfoImpl 

//@doc SECIQueryInfoImpl
//@mdata HWND      | SECIQueryInfoImpl | m_hwndOwner | A window handle to the owner of this interface.

//@doc SECIQueryInfoImpl
//@mdata LPITEMIDLIST    | SECIQueryInfoImpl | m_pPidl | A copy of the PIDL the instance of this class is attached to.

//@doc SECIQueryInfoImpl
//@mdata TPidlMgr*     | SECIQueryInfoImpl | m_pPidlMgr | A PIDL manager to help manage the PIDL.

//@doc SECIQueryInfoImpl
//@mfunc | SECIQueryInfoImpl | SECIQueryInfoImpl | Constructor. It creates a valid instance of PIDL manager class indicated in our template arguments. 
//Application can always assume the PIDL manager is valid.
//It also sets reference count to one and increases the lock count of _Module by one. In addition, the contructor
//will make a copy of the given PIDL and store the given owner window handle for later use. If application need 
//to access the IShellFolder in the namespace development, then application should derive from this class.
//@parm HWND | hwndOwner | A handle to the owner window. Inside the implementation of this class, applicaion should use
//this handle to popup message box or dialog box.
//@parm  LPCITEMIDLIST | pidl | The PIDL the instance of this class is attached to.
//@xref <c SECIQueryInfoImpl>

// adinsert AutoDuck insertion point for SECIQueryInfoImpl 

//@doc SECIQueryInfoImpl 
//@class SECIQueryInfoImpl
//@comm This class is a thin wrapper class of IQueryInfo interface. It implemented the
//methods in the IUnknown interface and the reference counting logic. It can only be used in 
//an ATL base project. Since its reference counting makes use of the lock count in CComModule
//class of ATL, i.e. a global CComModule instanace _Module. The template argument should be an PIDL
//management class derived from SECPidlMgr lt; T gt; template class. This implementation is majorly 
//targeted for namespace or shell extension. To use this class, you can derive from it and 
//provide sensible implementation for all the methods of IQueryInfo other than that of 
//IUnknown interface. The constructor need two arguments, a window handle 
//and a PIDL. The window handle is usually the owner window of this interface. The constructor will 
//save the window handle and make a copy of the PIDL. Note though, Only GetInfoTip other than that of IUnknown is currently 
//been used. <nl>
//<nl>
//For a complete documentation of IQueryInterface, please refer to windows SDK or MSDN from Microsoft.
//@tcarg class | TPidlMgr | A SECPidlMgr derived class
//@base public | IQueryInfo
template<typename TPidlMgr>
class SECIQueryInfoImpl : public IQueryInfo  
{
protected:
	DWORD					m_nRefCount;
	//@cmember
	/* todo Add your Intellisense compatible description here */
	HWND					m_hwndOwner;
	//@cmember
	/* todo Add your Intellisense compatible description here */
	LPITEMIDLIST			m_pPidl;
	//@cmember
	/* todo Add your Intellisense compatible description here */
	TPidlMgr*				m_pPidlMgr;

public:
	//@cmember
	/* Constructor */
	inline SECIQueryInfoImpl(HWND hwndOwner, LPCITEMIDLIST pidl)
	{
		m_pPidlMgr = new TPidlMgr;
		if( m_pPidlMgr == NULL )
		{
			delete this;
			return;
		}
		m_pPidl = m_pPidlMgr->Copy(pidl);
		m_hwndOwner = hwndOwner;

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
	virtual ~SECIQueryInfoImpl()
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
	// IUnknown
	inline STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
	{
		*ppvObj = NULL;

		//IUnknown
		if(IsEqualIID(riid, IID_IUnknown))
			*ppvObj = this;
		else if(IsEqualIID(riid, IID_IQueryInfo))
			*ppvObj = (IQueryInfo*)this;

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

	inline STDMETHOD(GetInfoFlags)(DWORD *pdwFlags)
	{
		// Not used currently
		return E_NOTIMPL;
	}
	inline STDMETHOD(GetInfoTip)(DWORD dwFlags, WCHAR** ppszTip)
	{
		// This assumes that class T contain m_spMalloc member
		if( ppszTip == NULL )
			return E_INVALIDARG;

		CComPtr<IMalloc> spMalloc;
		if( FAILED(SHGetMalloc(&spMalloc)) )
			return E_OUTOFMEMORY;

		*ppszTip = (WCHAR*)spMalloc->Alloc(MAX_PATH * sizeof(WCHAR));
		if( *ppszTip == NULL )
			return E_OUTOFMEMORY;

		mbstowcs(*ppszTip, _T("Put your own infotip here"), MAX_PATH);

		//Calling function is responsible to free the memoy using Free method
		//in the IMalloc interface !!!
		return S_OK;
	}
};

#endif // !defined(AFX_SECIQUERYINFOIMPL_H__948BA547_8E7F_4CAD_89B6_2B9961F7B1B8__INCLUDED_)
