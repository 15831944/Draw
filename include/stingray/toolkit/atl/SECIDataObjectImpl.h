///////////////////////////////////////////////////////////////////////////////
// SECIDataObjectImpl.h
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

#if !defined(AFX_SECIDATAOBJECTIMPL_H__5CDCBD42_B18F_459B_AF38_9EDC6252CCA0__INCLUDED_)
#define AFX_SECIDATAOBJECTIMPL_H__5CDCBD42_B18F_459B_AF38_9EDC6252CCA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
// AutoDuck tag block block for SECIDataObjectImpl 

//@doc SECIDataObjectImpl
//@mdata HWND      | SECIDataObjectImpl | m_hwndOwner | A window handle to the owner of this interface.

//@doc SECIDataObjectImpl
//@mdata LPITEMIDLIST    | SECIDataObjectImpl | m_pPidl |  A copy of the PIDL the instance of this class is attached to.

//@doc SECIDataObjectImpl
//@mdata TPidlMgr*     | SECIDataObjectImpl | m_pPidlMgr | A PIDL manager to help manage the PIDL.

//@doc SECIDataObjectImpl
//@mdata CComPtr lt; IShellFolder gt;  | SECIDataObjectImpl | m_spShellFolder | data member comment

//@doc SECIDataObjectImpl
//@mfunc | SECIDataObjectImpl | SECIDataObjectImpl | Constructor. It creates a valid instance of PIDL manager class indicated in our template arguments. 
//Application can always assume the PIDL manager is valid.
//It also sets reference count to one and increases the lock count of _Module by one. In addition, the contructor
//will make a copy of the given PIDL and store the given owner window handle for later use. If application need 
//to access the IShellFolder in the namespace development, then application should derive from this class.
//@parm HWND | hwndOwner | A handle to the owner window. Inside the implementation of this class, applicaion should use
//this handle to popup message box or dialog box.
//@parm  LPCITEMIDLIST | pidl | The PIDL the instance of this class is attached to.
//@xref <c SECIDataObjectImpl>

// adinsert AutoDuck insertion point for SECIDataObjectImpl 
//@doc SECIDataObjectImpl 
//@class SECIDataObjectImpl
//@comm This class is a thin wrapper class of IDataObject interface. It only implemented the
//methods in the IUnknown interface and the reference counting logic. It can only be used in 
//an ATL base project. Since its reference counting makes use of the lock count in CComModule
//class of ATL, i.e. a global CComModule instanace _Module. The template argument is an PIDL
//management class derived from SECPidlMgr lt; T gt; template class. This implementation is majorly 
//targeted for namespace or shell extension. To use this class, you can derive from it and 
//provide sensible implementation for all the methods of IDataObject other than that of 
//IUnknown interface. The constructor need two arguments, a window handle 
//and a PIDL. The window handle is usually the owner window of this interface. The constructor will 
//save the window handle and make a copy of the PIDL. <nl>
//<nl>
//For a complete documentation of IDataObject, please refer to windows SDK or MSDN from Microsoft.
//@tcarg class | TPidlMgr | A SECPidlMgr derived class
//@base public | IDataObject
template<typename TPidlMgr>
class SECIDataObjectImpl : public IDataObject
{
protected:
	DWORD					m_nRefCount;
	//@cmember
	/* Window handle of the owner of this interface */
	HWND					m_hwndOwner;
	//@cmember
	/* PIDL of the item this inteface attached to */
	LPITEMIDLIST			m_pPidl;
	//@cmember
	/* A pointer to PIDL manager */
	TPidlMgr*				m_pPidlMgr;

public:
	//@cmember
	/* Constructor */
	inline SECIDataObjectImpl(HWND hwndOwner, LPCITEMIDLIST pidl)
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
	virtual ~SECIDataObjectImpl()
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

	inline STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
	{
		*ppvObj = NULL;

		//IUnknown
		if(IsEqualIID(riid, IID_IUnknown))
			*ppvObj = this;
		else if(IsEqualIID(riid, IID_IDataObject))
			*ppvObj = (IDataObject*)this;

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

	inline STDMETHOD(GetData)(FORMATETC *pformatetcIn, STGMEDIUM *pmedium)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(GetDataHere)(FORMATETC* pformatetc , STGMEDIUM*  pmedium)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(QueryGetData)(FORMATETC*  pformatetc)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(GetCanonicalFormatEtc)(FORMATETC* pformatectIn,FORMATETC* pformatetcOut)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(SetData)(FORMATETC* pformatetc, STGMEDIUM* pmedium , BOOL fRelease)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(EnumFormatEtc)(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(DAdvise)(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
		DWORD *pdwConnection)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(DUnadvise)(DWORD dwConnection)
	{
		return E_NOTIMPL;
	}
	inline STDMETHOD(EnumDAdvise)(IEnumSTATDATA **ppenumAdvise)
	{
		return E_NOTIMPL;
	}
};

#endif // !defined(AFX_SECIDATAOBJECTIMPL_H__5CDCBD42_B18F_459B_AF38_9EDC6252CCA0__INCLUDED_)
