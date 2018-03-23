///////////////////////////////////////////////////////////////////////////////
// OtlComCollection.h
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

#ifndef __OTLCOMCOLLECTION_H__
#define __OTLCOMCOLLECTION_H__

#ifndef __OTLBASE_H__
	#error otlcomcollection.h requires otlbase.h to be included first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// CComCollection


template<class TYPE, class BASE>
class CComCollection : public BASE
{
protected:
	struct CMinNode
	{
		CMinNode* pNext;
		CMinNode* pPrev;
		TYPE* pData;
		CComBSTR bstrKey;
	};
	struct TNode
	{
		WCHAR	wc;
		TNode	*pLo,*pHi,*pEq;
		void    *pMatch;
	};
	typedef TNode *TNodePtr;

public:
// Construction
	inline CComCollection() 
    {	
		m_bCaseSensitive = true;
        m_nCount = 0;
        m_pNodeHead = m_pNodeTail = NULL;
		m_pTRoot = (TNodePtr)NULL;
    };

    virtual ~CComCollection()
    {
	    RemoveAll();
		OTLASSERT(m_pNodeHead==NULL);
		OTLASSERT(m_pNodeTail==NULL);
		OTLASSERT(m_pTRoot==NULL);
    };

	// standard Collection methods.
	STDMETHOD(Add)(TYPE *pIType, VARIANT index);
	STDMETHOD(get_Count)(long *pVal);
	STDMETHOD(Item)(VARIANT index, VARIANT *pvar);
	STDMETHOD(get__NewEnum)(LPUNKNOWN *pVal);
	STDMETHOD(Remove)(VARIANT index);

    typedef CComEnum<CComIEnum<VARIANT>, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > _CComCollEnum;

// Implementation
protected:
	CMinNode* m_pNodeHead;
	CMinNode* m_pNodeTail;
	int m_nCount;
	TNodePtr m_pTRoot;
	bool m_bCaseSensitive;

	// remove all elements
	bool RemoveAll();

    // array type iteration
    TYPE* Item(long lIndex);
    TYPE* Item(BSTR bstrKey);
    CMinNode* GetNode(long lIndex);
    CMinNode* GetNode(BSTR bstrKey);

    long AddTail(TYPE *pIType, BSTR bstrKey);
    CMinNode* NewMinNode(CMinNode*, CMinNode*);
	void FreeMinNode(CMinNode*);

	// key iteration/retrieval
	void * TNodeSearch(WCHAR *pwstr, TNodePtr pRoot);
	TNodePtr TNodeAdd(WCHAR *pwstr, TNodePtr *ppRoot);
	void * TNodeRemove(WCHAR *pwstr, TNodePtr *ppRoot);


};

template<class TYPE, class BASE>
STDMETHODIMP CComCollection<TYPE,BASE>::Add(TYPE *pIType, VARIANT index)
{
    HRESULT hr = S_OK;

    if(pIType!=NULL)
    {
		// Validate the interface TYPE support.
		TYPE *pI=NULL;
		hr = pIType->QueryInterface(_uuidof(TYPE), (void **)&pI);
		if(SUCCEEDED(hr))
		{
			if(index.vt == VT_BSTR)
			{
				if(!m_bCaseSensitive)
				{
					CComBSTR bstrIndex = index.bstrVal;
					bstrIndex.ToLower();
					if(AddTail(pI, bstrIndex)==NULL)
						hr = E_FAIL;
				}
				else if(AddTail(pI, index.bstrVal)==NULL)
					hr = E_FAIL;
			}
			else if(index.vt == VT_EMPTY || index.vt == VT_ERROR)
			{
				if(AddTail(pI, NULL)==NULL)
				{
					hr = E_FAIL;
				}
			}
			else
			{
				hr = E_INVALIDARG;
			}
			pI->Release();
		}
		else
		{
			hr = E_NOINTERFACE;
		}
    }
    else
    {
        hr = E_POINTER;
    }
    return hr;
}

template<class TYPE, class BASE>
STDMETHODIMP CComCollection<TYPE,BASE>::get_Count(long *pVal)
{ 
    HRESULT hr = S_OK;
    if (pVal != NULL)
    {
		*pVal = m_nCount;
    }
    else
    {
        hr = E_POINTER;
    }

	return hr; 
}

template<class TYPE, class BASE>
STDMETHODIMP CComCollection<TYPE,BASE>::Item(VARIANT index, VARIANT *pvar)
{
    HRESULT hr = S_OK;
    if (pvar != NULL)
    {
        (*pvar).vt = VT_EMPTY;
        TYPE* pType=NULL;

		if(index.vt == VT_I4)
	        pType = Item(index.lVal);
		else if(index.vt == (VT_I4 | VT_BYREF))
			pType = Item(*(index.plVal));
		else if(index.vt == VT_I2)
            pType = Item((long)index.iVal);
		else if(index.vt == (VT_I2 | VT_BYREF))
			pType = Item((long)*index.piVal);
		else if(index.vt == VT_BSTR)
		{
			if(!m_bCaseSensitive)
			{
				CComBSTR bstrIndex = index.bstrVal;
				bstrIndex.ToLower();
				pType = Item(bstrIndex);
			}
			else
				pType = Item(index.bstrVal);
		}
		else if(index.vt == (VT_BSTR | VT_BYREF))
		{
			if(!m_bCaseSensitive)
			{
				CComBSTR bstrIndex = *(index.pbstrVal);
				bstrIndex.ToLower();
				pType = Item(bstrIndex);
			}
			else
				pType = Item(*(index.pbstrVal));
		}

        if(pType == NULL)
        {
            hr = E_INVALIDARG;
        }
        else
        {
			IUnknown *pIUnk=NULL;
			IDispatch *pIDisp=NULL;
			
			// Attempt to get the dispatch pointer first.
			hr = pType->QueryInterface(IID_IDispatch, (void **)&pIDisp);
			if(SUCCEEDED(hr))
			{
	            (*pvar).vt = VT_DISPATCH;
		        (*pvar).pdispVal = pIDisp;
			}
			else
			{
				// The interface did not support IDispatch, simply try to get
				// the IUnknown pointer now.
				hr = pType->QueryInterface(IID_IUnknown, (void **)&pIUnk);
				if(SUCCEEDED(hr))
				{
					(*pvar).vt = VT_UNKNOWN;
					(*pvar).punkVal = pIUnk;
				}
			}
			pType->Release();
        }
    }
    else
    {
        hr = E_POINTER;
    }

	return hr; 
}

template<class TYPE, class BASE>
STDMETHODIMP CComCollection<TYPE,BASE>::get__NewEnum(LPUNKNOWN *ppVal)
{
    HRESULT hr = S_OK;

    if (ppVal == NULL)
	    return E_POINTER;
    *ppVal = NULL;

    _CComCollEnum *pEnum = NULL;
    ATLTRY(pEnum = new CComObject<_CComCollEnum>)
    if (pEnum == NULL)
	    return E_OUTOFMEMORY;

    // allocate an initialize a vector of VARIANT objects
	unsigned int uiSize = sizeof(VARIANT) * m_nCount;
    VARIANT* pVar = (VARIANT*) new VARIANT[m_nCount];
	memset(pVar, '\0', uiSize);

	// Set the VARIANTs that will hold the TYPE Interface pointers.
    int i = 0;
    while ( i < m_nCount )
    {
		TYPE* pIP = NULL;
		pVar[i].vt = VT_DISPATCH;
		pIP = Item((long)i+1);
		if(pIP != NULL)
		{
			hr = pIP->QueryInterface(IID_IUnknown, (void**)&pVar[i].pdispVal);
			pIP->Release();
			pIP = NULL;
		}
		i++;
    }

    // copy the array of VARIANTs
	hr = pEnum->Init(&pVar[0],
					 &pVar[m_nCount],
					 reinterpret_cast<TYPE*>(this), AtlFlagCopy);
    if (FAILED(hr))
    {
	    delete pEnum;
    }
	else
	{
		hr = pEnum->QueryInterface(IID_IUnknown, (void**)ppVal);
		if (FAILED(hr))
			delete pEnum;
	}

	// Iterate through the VARIANT pointer array clearing each VARIANT
    i = 0;
    while ( i < m_nCount )
    {
		VariantClear(&pVar[i]);
		i++;
    }

	// Now free the memory for the array of VARIANT pointers.
	if(pVar)
	{
		delete [] pVar;
		pVar = NULL;
	}

	return hr; 
}

template<class TYPE, class BASE>
STDMETHODIMP CComCollection<TYPE,BASE>::Remove(VARIANT index)
{
    HRESULT hr = S_OK;
    CMinNode* pOldNode = NULL;

    if(index.vt == VT_I4)
    {
        pOldNode = GetNode(index.lVal);
		TNodeRemove(pOldNode->bstrKey,&m_pTRoot);
    }
    else if(index.vt == VT_I2)
    {
        pOldNode = GetNode((long)index.iVal);
		TNodeRemove(pOldNode->bstrKey,&m_pTRoot);
    }
    else if(index.vt == VT_BSTR)
    {
		if(!m_bCaseSensitive)
		{
			CComBSTR bstrIndex = index.bstrVal;
			bstrIndex.ToLower();
			pOldNode = (CMinNode*)TNodeRemove(bstrIndex,&m_pTRoot);
		}
		else
			pOldNode = (CMinNode*)TNodeRemove(index.bstrVal,&m_pTRoot);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    if(pOldNode!=NULL)
    {
	    // if this is the head remove pOldNode from list
	    if (pOldNode == m_pNodeHead)
	    {
		    m_pNodeHead = pOldNode->pNext;
	    }
	    else
	    {
		    if(pOldNode->pPrev != NULL)
            {
                // Adjust the Next pointer of the previous Node.
    		    pOldNode->pPrev->pNext = pOldNode->pNext;
            }
	    }

        // if this is the tail remove it from the list.
        if (pOldNode == m_pNodeTail)
	    {
		    m_pNodeTail = pOldNode->pPrev;
	    }
	    else
	    {
		    if(pOldNode->pNext != NULL)
            {
                // Adjust the Prev pointer of the next Node.
		        pOldNode->pNext->pPrev = pOldNode->pPrev;
            }
	    }
    
        // Now free the dangling node.
        FreeMinNode(pOldNode);
    }
    else
    {
        hr = E_INVALIDARG;
    }

	return hr; 
}

template<class TYPE, class BASE>
TYPE* CComCollection<TYPE,BASE>::Item(long lIndex)
{ 
    TYPE* pType=NULL;
    CMinNode* pNode = GetNode(lIndex);

    if(pNode != NULL)
    {
        pType = pNode->pData;
        if(pType!=NULL)
            pType->AddRef();
    }

	return pType; 
}

template<class TYPE, class BASE>
TYPE* CComCollection<TYPE,BASE>::Item(BSTR bstrKey)
{ 
    TYPE* pType=NULL;
    CMinNode* pNode = GetNode(bstrKey);

    if(pNode != NULL)
    {
        pType = pNode->pData;
        if(pType!=NULL)
            pType->AddRef();
    }

	return pType; 
}

template<class TYPE, class BASE>
typename CComCollection<TYPE,BASE>::CMinNode* CComCollection<TYPE,BASE>::GetNode(long lIndex)
{ 
    CMinNode* pNode=NULL;
    long lCounter=1;
	
	if(lIndex > m_nCount || lIndex < 1)
		return NULL;

	if(lIndex < m_nCount/2)
	{
	    pNode = m_pNodeHead;
		while (pNode != NULL && lCounter < lIndex)
		{
			pNode = pNode->pNext;
			lCounter++;
		}
	}
	else
	{
	    pNode = m_pNodeTail;
		lCounter = m_nCount;
		while (pNode != NULL && lCounter > lIndex)
		{
			pNode = pNode->pPrev;
			lCounter--;
		}
	}

	return pNode; 
}

template<class TYPE, class BASE>
typename CComCollection<TYPE,BASE>::CMinNode* CComCollection<TYPE,BASE>::GetNode(BSTR bstrKey)
{ 
	CMinNode *pNode=NULL;
	pNode = (CMinNode*)TNodeSearch(bstrKey,m_pTRoot);

	return pNode; 
}

template<class TYPE, class BASE>
long CComCollection<TYPE,BASE>::AddTail(TYPE *pIType, BSTR bstrKey)
{
	CMinNode* pNewNode = NewMinNode(m_pNodeTail, NULL);
	TNodePtr pT=NULL;

    if(bstrKey != NULL)
	{
        pNewNode->bstrKey = bstrKey;
		pT = TNodeAdd(bstrKey, &m_pTRoot);

		if(pT==NULL)
		{
			if(pNewNode) 
				delete pNewNode;
			return NULL;
		}
	}

	pNewNode->pData = pIType;
    pIType->AddRef();

	if(pT!=(TNodePtr)NULL)
		pT->pMatch = (void*)pNewNode;

	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;

    m_pNodeTail = pNewNode;
    m_nCount++;

    return (long)(SEC_LONG)pNewNode;
}

template<class TYPE, class BASE>
bool CComCollection<TYPE,BASE>::RemoveAll()
{
	// destroy elements
    bool fRet = true;
    VARIANT var;
    var.vt = VT_I4;
    var.lVal = 1;

    while (m_nCount != 0 && fRet)
    {
        if(Remove(var)!=S_OK)
            fRet = false;
    }

    return fRet;
}

template<class TYPE, class BASE>
typename CComCollection<TYPE,BASE>::CMinNode* CComCollection<TYPE,BASE>::NewMinNode(
                                        typename CComCollection<TYPE,BASE>::CMinNode* pPrev,
                                        typename CComCollection<TYPE,BASE>::CMinNode* pNext)
{
    typename CComCollection<TYPE,BASE>::CMinNode* pNode = new CComCollection<TYPE,BASE>::CMinNode;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
    pNode->pData = NULL;
    pNode->bstrKey = _T("");
    return pNode;
}

template<class TYPE, class BASE>
void CComCollection<TYPE,BASE>::FreeMinNode(typename CComCollection<TYPE,BASE>::CMinNode* pNode)
{
    // First, release the object
    pNode->pData->Release();

    // Now delete the memory used by the CMinNode.
    delete pNode;

	m_nCount--;
}


template<class TYPE, class BASE>
void * CComCollection<TYPE,BASE>::TNodeSearch(WCHAR *pwstr, typename CComCollection<TYPE,BASE>::TNodePtr pRoot)
{
	int n;
	while(pRoot!=NULL)
	{
		n = *pwstr - pRoot->wc;
		if(n == 0)
		{
			if(*(++pwstr)==NULL)
				return pRoot->pMatch;
			pRoot = pRoot->pEq;
		}
		else if(n < 0)
			pRoot = pRoot->pLo;
		else
			pRoot = pRoot->pHi;
	}
	return (void *)NULL;
}

#pragma warning (push)
#pragma warning (disable: 4706) // Intentional Assignment

template<class TYPE, class BASE>
typename CComCollection<TYPE,BASE>::TNodePtr CComCollection<TYPE,BASE>::TNodeAdd(WCHAR *pwstr, TNodePtr *ppRoot)
{
	int n;
	TNodePtr pT;
	TNodePtr *ppT;
	ppT=ppRoot;
	// Intentional Assignment. 
	while(pT=*ppT)
	{
		n = *pwstr-pT->wc;
		if(n==0)
		{
			if(*(++pwstr)==NULL)
			{
				if(pT->pMatch==NULL)
					return pT;
				else
					return (TNodePtr)NULL;
			}
			ppT=&(pT->pEq);
		}
		else if(n<0)
			ppT=&(pT->pLo);
		else
			ppT=&(pT->pHi);
	}
	for(;;)
	{
		*ppT=(TNodePtr) new TNode;
		pT=*ppT;
		pT->wc = *pwstr;
		pT->pLo=pT->pHi=pT->pEq=(TNodePtr)NULL; 
		pT->pMatch=(void*)NULL;
		if(*(++pwstr)==NULL)
			return pT;
		ppT=&(pT->pEq);
	}
}

#pragma warning (pop) //4706

template<class TYPE, class BASE>
void * CComCollection<TYPE,BASE>::TNodeRemove(WCHAR *pwstr, typename CComCollection<TYPE,BASE>::TNodePtr *ppRoot)
{
	void* pRet=NULL;
	int n;
	if(*ppRoot==NULL)
		return false;
	n = *pwstr-(*ppRoot)->wc;
	if(n<0)
		pRet = TNodeRemove(pwstr, &((*ppRoot)->pLo));
	else if(n>0)
		pRet = TNodeRemove(pwstr, &((*ppRoot)->pHi));
	else if(*(++pwstr)!=NULL)
		pRet = TNodeRemove(pwstr, &((*ppRoot)->pEq));
	else
	{
		pRet = (*ppRoot)->pMatch;
		(*ppRoot)->pMatch=NULL;
	}
	
	if((*ppRoot)->pLo==(TNodePtr)NULL &&
		(*ppRoot)->pHi==(TNodePtr)NULL &&
		(*ppRoot)->pEq==(TNodePtr)NULL &&
		(*ppRoot)->pMatch==(void*)NULL)
	{
		delete (*ppRoot);
		*ppRoot=NULL;
	}
	return pRet;
}

/////////////////////////////////////////////////////////////////////////////
// CComCollectionPersist

template<class TYPE, class BASE1, class BASE2>
class CComCollectionPersist : public CComCollection<TYPE,BASE1>, public BASE2
{
public:
   STDMETHOD(Load) (IStorage *pStorage);
   STDMETHOD(Save) (IStorage *pStorage, BOOL fSameAsLoad);

};

template<class TYPE, class BASE1, class BASE2>
STDMETHODIMP CComCollectionPersist<TYPE,BASE1,BASE2>::Load(IStorage *pStorage)
{
    HRESULT hr = S_OK;
    ATLTRACE(_T("CComCollectionPersist::Load\n"));

	// Call Load on the base class.
    if (SUCCEEDED(hr))
        hr = BASE2::Load(pStorage);

    if (SUCCEEDED(hr))
    {
        // Get the Name of the Storage to create the name of the
		// Storage used for the collection objects.
        STATSTG statstg;
        hr = pStorage->Stat(&statstg, STATFLAG_DEFAULT);

		CComBSTR cbstrStgName(statstg.pwcsName);
		cbstrStgName.Append(OLESTR(" Collection"));

        DWORD dwFlags = STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE;
        CComPtr<IStorage> spIStg;
        hr = pStorage->OpenStorage(cbstrStgName, NULL, dwFlags, NULL,
                                   NULL, &spIStg);
        if (SUCCEEDED(hr))
        {
			// Open the stream used for the text keys for the entries
			// in the collection.
			CComPtr<IStream> spKeyStream;
			hr = spIStg->OpenStream(OLESTR("Keys"), NULL,
				STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 0, &spKeyStream);

            if (SUCCEEDED(hr))
            {
				// First, read the count of keys.
				CComVariant cvar;
				hr = cvar.ReadFromStream(spKeyStream);
			}

			int nIndex = 1;
			hr = S_OK;
			bool fContinue = true;
			while(fContinue)
			{
				CComBSTR cbstrName(cbstrStgName);
				CComVariant cvar(nIndex++);
				cvar.ChangeType(VT_BSTR);
				cbstrName.Append(cvar.bstrVal);

                CComPtr<IStorage> spIObjStore;
                hr = spIStg->OpenStorage(cbstrName, NULL,
                                    dwFlags, NULL, NULL, &spIObjStore);
				if(FAILED(hr))
				{
					// End condition
					hr = S_OK;
					fContinue = false;
					break;
				}

				// Attempt to instantiate the object and QI for the
                // IPersistStorage Interface.
				STATSTG statstg;
				hr = spIObjStore->Stat(&statstg, STATFLAG_DEFAULT);

                CComPtr<IPersistStorage> spIPerStore;
                hr = CoCreateInstance(statstg.clsid, NULL, CLSCTX_ALL,
                                      IID_IPersistStorage,
                                      (void **) &spIPerStore);
                if (SUCCEEDED(hr))
                {
                    // Load the Persisted Storage.
                    hr = spIPerStore->Load(spIObjStore);

                    if (SUCCEEDED(hr))
                    {
						CComPtr<TYPE> spIType;
                        hr = spIPerStore->QueryInterface(IID_IUnknown,
                                                         (void **) &spIType);

                        // Add this object to the collection.
						CComVariant cvar;
						if(spKeyStream)
						{
							//CComBSTR cbstrEmpty("");
							hr = cvar.ReadFromStream(spKeyStream);
							if (cvar.vt != VT_BSTR || FAILED(hr) ||
								(cvar.vt == VT_BSTR && (::SysStringLen(cvar.bstrVal) < 1)))
								cvar.Clear();
						}
		                hr = Add(spIType,cvar);
                    }
                }
			}
        }
    }

    return hr;
}

template<class TYPE, class BASE1, class BASE2>
STDMETHODIMP CComCollectionPersist<TYPE,BASE1,BASE2>::Save(IStorage *pStorage, BOOL fSameAsLoad)
{
    HRESULT hr = S_OK;
    ATLTRACE(_T("CComCollectionPersist::Save\n"));

	// Call the base class to save.
    if (SUCCEEDED(hr))
        hr = BASE2::Save(pStorage, fSameAsLoad);

    if (SUCCEEDED(hr))
	{
        // Get the Name of the Storage to create the name of the
		// Storage used for the collection objects.
        STATSTG statstg;
        hr = pStorage->Stat(&statstg, STATFLAG_DEFAULT);
		CComBSTR cbstrStgName(statstg.pwcsName);
		cbstrStgName.Append(OLESTR(" Collection"));

        // Now create a new storage to be used for this
		// collection objects.
        DWORD dwFlags = STGM_DIRECT | STGM_READWRITE |
            STGM_SHARE_EXCLUSIVE | STGM_CREATE;
        CComPtr<IStorage> spIStorage;
        hr = pStorage->CreateStorage(cbstrStgName, dwFlags,
                                      NULL, NULL, &spIStorage);
		if(SUCCEEDED(hr))
		{
			// Create the stream used for the text keys for the entries
			// in the collection.
			CComPtr<IStream> spKeysStream;
			hr = spIStorage->CreateStream(OLESTR("Keys"),
				STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
				0, 0, &spKeysStream);
			if(SUCCEEDED(hr))
			{
				// First write out the count.
				CComVariant cvar;
				cvar = m_nCount;
				cvar.WriteToStream(spKeysStream);
			}

			CMinNode* pNode=NULL;
			long lCounter=1;

			// Iterate through the entries.
			pNode = m_pNodeHead;
			while (pNode != NULL && lCounter <= m_nCount)
			{
				CComPtr<IPersistStorage> pIPerStore;
				hr = pNode->pData->QueryInterface(IID_IPersistStorage,
								 				  (void **) &pIPerStore);
				if (SUCCEEDED(hr))
				{
					// Create the name of the new storage.
					CComVariant varIndex;
					varIndex = lCounter;
					varIndex.ChangeType(VT_BSTR);
					CComBSTR cbstrStoreName(cbstrStgName);
					cbstrStoreName.Append(varIndex.bstrVal);

					// Create a new storage to be used for this interface object.
					CComPtr<IStorage> spIStorageEntry;
					hr = spIStorage->CreateStorage(cbstrStoreName, dwFlags,
												  NULL, NULL, &spIStorageEntry);

					// Call Save on the PersistStorage interface.
					if (SUCCEEDED(hr))
						hr = pIPerStore->Save(spIStorageEntry, fSameAsLoad);

					// Write out the key to the key stream.
					CComVariant cvarKey;
					if(!pNode->bstrKey)
						cvarKey = (long)0;
					else
						cvarKey = (LPCTSTR)pNode->bstrKey;

					cvarKey.WriteToStream(spKeysStream);

				}

				pNode = pNode->pNext;
				lCounter++;
			}
        }
	}
    return hr;
}


};	// namespace StingrayOTL

#endif	// __OTLCOMCOLLECTION_H__

