///////////////////////////////////////////////////////////////////////////////
// otlmsmq.h
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


#ifndef __OTLMSMQ_H__
#define __OTLMSMQ_H__

#ifndef __OTLBASE_H__
	#error otlmsmq.h requires otlbase.h to be included first
#endif

#include <mqoai.h>
#include <comdef.h>
#include <atlcom.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlMSMQ

class COtlMSMQ
{
public:
	IMSMQQueueInfo* m_pqinfo;
	IMSMQQueue*		m_pq;
public:
	inline COtlMSMQ() : m_pqinfo(NULL), m_pq(NULL){}
	inline ~COtlMSMQ()
	{ 
		Close();
		ResetInfo(); 
	}
public:
// transaction helpers
	static void InitVarTrans(VARIANT& varTrans, IMSMQTransaction* pTrans)
	{
		// pTrans can be 0
		switch((SEC_LONG)pTrans)
		{			// a const
		case MQ_NO_TRANSACTION:
		case MQ_MTS_TRANSACTION:
		case MQ_XA_TRANSACTION:
		case MQ_SINGLE_MESSAGE:
			{
#ifdef _WIN64
				varTrans.vt = VT_I8;
				varTrans.llVal = (LONGLONG)pTrans;
#else	//WIN32
				varTrans.vt = VT_I4;
				varTrans.lVal = (long)pTrans;
#endif	//_WIN64
				break;
			}
		default:	// an IMSMQTransaction pointer
			{
				IDispatch* pDisp=NULL;
				HRESULT hr = pTrans->QueryInterface(IID_IDispatch,(void**)&pDisp);
				if(SUCCEEDED(hr))
				{
					varTrans.vt = VT_DISPATCH;
					varTrans.pdispVal = pDisp;
				}
				else
				{
					varTrans.vt = VT_UNKNOWN;
					pTrans->AddRef();
					varTrans.punkVal = static_cast<IUnknown*>(pTrans);
				}
				break;
			}
		}
	}

	static HRESULT BeginTransactionDTC( IMSMQTransaction** ppTrans)
	{
		OTLASSERT(ppTrans);
		*ppTrans = NULL;
		CComPtr<IMSMQCoordinatedTransactionDispenser> pTD;
		HRESULT hr = ::CoCreateInstance(CLSID_MSMQCoordinatedTransactionDispenser,
											NULL,
											CLSCTX_ALL,
											IID_IMSMQCoordinatedTransactionDispenser,
											(void**)&pTD);
		if(SUCCEEDED(hr))
			hr = pTD->BeginTransaction(ppTrans);
		return hr;
	}

	static HRESULT BeginTransactionInternal( IMSMQTransaction** ppTrans)
	{
		OTLASSERT(ppTrans);
		*ppTrans = NULL;
		CComPtr<IMSMQTransactionDispenser> pTD;
		HRESULT hr = ::CoCreateInstance(CLSID_MSMQTransactionDispenser,
											NULL,
											CLSCTX_ALL,
											IID_IMSMQTransactionDispenser,
											(void**)&pTD);
		if(SUCCEEDED(hr))
			hr = pTD->BeginTransaction(ppTrans);
		return hr;
	}

// lookup queue
	static HRESULT FindQueue (IMSMQQueueInfos** ppqinfos,
								VARIANT * QueueGuid = &vtMissing,
								VARIANT * ServiceTypeGuid = &vtMissing,
								VARIANT * Label = &vtMissing,
								VARIANT * CreateTime = &vtMissing,
								VARIANT * ModifyTime = &vtMissing,
								VARIANT * RelServiceType = &vtMissing,
								VARIANT * RelLabel = &vtMissing,
								VARIANT * RelCreateTime = &vtMissing,
								VARIANT * RelModifyTime = &vtMissing )
	{
		OTLASSERT(ppqinfos);
		*ppqinfos = NULL;
		CComPtr<IMSMQQuery> pquery;
		HRESULT hr = ::CoCreateInstance(
                   CLSID_MSMQQuery,
                   NULL,      // punkOuter
                   CLSCTX_SERVER,
                   IID_IMSMQQuery,
                   (void**)&pquery);

		if(SUCCEEDED(hr))
		{
			hr = pquery->LookupQueue(QueueGuid,
								ServiceTypeGuid,
								Label,
								CreateTime,
								ModifyTime,
								RelServiceType,
								RelLabel,
								RelCreateTime,
								RelModifyTime,
								ppqinfos);
		}
		return hr;
	}

// message object creation
	static HRESULT CreateMessage(	IMSMQMessage** ppMsg, 
									const _variant_t& varBody, 
									const _bstr_t& bstrLabel=(BSTR)NULL)
	{
		OTLASSERT(ppMsg);
		*ppMsg=NULL;
		HRESULT hr = ::CoCreateInstance( CLSID_MSMQMessage,
										 NULL,      // punkOuter
										 CLSCTX_SERVER,
										 IID_IMSMQMessage,
										 (void**)ppMsg);
		if(SUCCEEDED(hr))
			hr = (*ppMsg)->put_Body(varBody); // this will fail with E_NOINTERFACE if your object does not support IPersistStream

		if(SUCCEEDED(hr))
		{
			if(!bstrLabel)
			{
				// no label
			}
			else
				hr = (*ppMsg)->put_Label(bstrLabel);
		}
		return hr;
	}

public:
// send functions
	inline HRESULT SendObject(	IUnknown* pUnk, 
						const _bstr_t& bstrLabel=(BSTR)NULL, 
						IMSMQTransaction* pTrans=(IMSMQTransaction*)MQ_NO_TRANSACTION)
	{
		OTLASSERT(pUnk);
		IMSMQMessage* pMsg = NULL;
		_variant_t varBody(pUnk, true);	// AddRef
		HRESULT hr = COtlMSMQ::CreateMessage(&pMsg, varBody, bstrLabel);
		if(SUCCEEDED(hr))
		{
			hr = SendMessage(pMsg, pTrans);
			pMsg->Release();
		}
		return hr;
	}

	inline HRESULT SendMessage(IMSMQMessage* pMsg, 
						IMSMQTransaction* pTrans=(IMSMQTransaction*)MQ_NO_TRANSACTION)
	{
		OTLASSERT(pMsg);
		// Queue has not been opened
		OTLASSERT(m_pq);
		_variant_t varTrans;
		InitVarTrans(varTrans, pTrans);
		return pMsg->Send(m_pq, &varTrans);
	}

	inline HRESULT SendMessage(const _bstr_t& bstrBody, 
						const _bstr_t& bstrLabel=(BSTR)NULL, 
						IMSMQTransaction* pTrans=(IMSMQTransaction*)MQ_NO_TRANSACTION)
	{
		IMSMQMessage* pMsg = NULL;
		HRESULT hr = COtlMSMQ::CreateMessage(&pMsg, bstrBody, bstrLabel);
		if(SUCCEEDED(hr))
		{
			hr = SendMessage(pMsg, pTrans);
			pMsg->Release();
		}
		return hr;
	}

//receive functions
	inline HRESULT ReceiveObject(	REFIID iid, 
							void** ppvObject, 
							IMSMQTransaction* pTrans=(IMSMQTransaction*)MQ_NO_TRANSACTION,
							long lTimeout=INFINITE)
	{
		OTLASSERT(ppvObject);
		_variant_t varBody;
		CComPtr<IMSMQMessage> pMsg;
		HRESULT hr = ReceiveMessage(&pMsg, pTrans, lTimeout);
		if(SUCCEEDED(hr))
			hr = pMsg->get_Body(&varBody);

		if(SUCCEEDED(hr))
		{
			switch(varBody.vt)
			{
			case VT_UNKNOWN:
				hr = (varBody.punkVal)->QueryInterface(iid, ppvObject);
				break;
			case VT_DISPATCH:
				hr = (varBody.pdispVal)->QueryInterface(iid, ppvObject);
				break;
			default:
				hr = E_NOINTERFACE;
			}
		}
		return hr;
	}

	inline HRESULT ReceiveMessage(IMSMQMessage** ppMessage, 
							IMSMQTransaction* pTrans=(IMSMQTransaction*)MQ_NO_TRANSACTION,
							long lTimeout=INFINITE, 
							BOOL bWantDestQ=FALSE, 
							BOOL bWantBody=TRUE)
	{
		OTLASSERT(m_pq);
		OTLASSERT(ppMessage);
		*ppMessage = NULL;
		long lAccess;
		HRESULT hr = m_pq->get_Access(&lAccess);
		if(FAILED(hr))
			return hr;
		if(lAccess != MQ_RECEIVE_ACCESS)
			return E_FAIL;

		_variant_t varWantDestQueue;
		_variant_t varWantBody;
		_variant_t varReceiveTimeout;
		_variant_t varTrans;
		varWantDestQueue.vt = VT_BOOL;
		varWantDestQueue.boolVal = static_cast<VARIANT_BOOL>(bWantDestQ);
		varWantBody.vt = VT_BOOL;
		varWantBody.boolVal = static_cast<VARIANT_BOOL>(bWantBody);
		varReceiveTimeout.vt = VT_I4;
		varReceiveTimeout.lVal = lTimeout;

		InitVarTrans(varTrans, pTrans);
		IMSMQMessage* pM = NULL;
		hr = m_pq->Receive(	&varTrans,
							&varWantDestQueue,
							&varWantBody,
							&varReceiveTimeout,
							&pM);

		if(SUCCEEDED(hr))
			*ppMessage = pM;

		return hr;
	}

// functions to open a queue
	inline HRESULT OpenForSend()
	{
		// must have queue info first
		OTLASSERT(m_pqinfo);
		Close();
		IMSMQQueue*	pq = NULL;
		HRESULT hr = m_pqinfo->Open( MQ_SEND_ACCESS, MQ_DENY_NONE, &pq);
		if(SUCCEEDED(hr))
			m_pq = pq;
		else
		{
			ATLTRACE("COtlMSMQ::OpenForOutput failed %0x\n", hr);
			OTLASSERT(0);
		}
		return hr;
	}

	inline HRESULT OpenForReceive(BOOL bDenyShare=FALSE)
	{
		// must have queue info first
		OTLASSERT(m_pqinfo);
		Close();
		IMSMQQueue*	pq = NULL;
		HRESULT hr = m_pqinfo->Open(	MQ_RECEIVE_ACCESS, 
										bDenyShare ? MQ_DENY_RECEIVE_SHARE : MQ_DENY_NONE,
										&pq );
		if(SUCCEEDED(hr))
			m_pq = pq;
		else
		{
			ATLTRACE("COtlMSMQ::OpenForInput failed %0x\n", hr);
			OTLASSERT(0);
		}
		return hr;
	}

	inline HRESULT OpenForPeek()
	{
		// must have queue info first
		OTLASSERT(m_pqinfo);
		Close();
		IMSMQQueue*	pq = NULL;
		HRESULT hr = m_pqinfo->Open(MQ_PEEK_ACCESS, MQ_DENY_NONE, &pq );
		if(SUCCEEDED(hr))
			m_pq = pq;
		else
		{
			ATLTRACE("COtlMSMQ::OpenForPeek failed %0x\n", hr);
			OTLASSERT(0);
		}

		return hr;
	}

// delete a Queue
	inline HRESULT Delete()
	{
		HRESULT hr = E_FAIL;
		if(m_pqinfo)
			hr = m_pqinfo->Delete();
		return hr;
	}

// close the Queue and release the IMSMQQueue interface
	inline HRESULT Close()
	{
		HRESULT hr = S_OK;
		if(m_pq)
		{
			hr = m_pq->Close();
			m_pq->Release();
			m_pq = NULL;
		}
		return hr;
	}

// create a Queue
	inline HRESULT Create(	BOOL bTrans=FALSE,
					BOOL bWorldReadable=FALSE)
	{
		// must set QueueInfo first using CreateInfo or SetInfo
		OTLASSERT(m_pqinfo);

		_variant_t varTrans;
	    varTrans.vt = VT_BOOL;
		varTrans.boolVal = static_cast<VARIANT_BOOL>(bTrans ? MQ_TRANSACTIONAL : MQ_TRANSACTIONAL_NONE);

		_variant_t varIsWorldReadable;
		varIsWorldReadable.vt = VT_BOOL;
		varIsWorldReadable.boolVal = static_cast<VARIANT_BOOL>(bWorldReadable);

	    HRESULT hr = m_pqinfo->Create(&varTrans, &varIsWorldReadable);
		if (FAILED(hr))
		{
			if (hr == MQ_ERROR_QUEUE_EXISTS) 
				ATLTRACE("COtlMSMQ::Create - Queue already exists\n");
		}
		return hr;
	}

// create a QueueInfo with a few minimal parameters
	inline HRESULT CreateInfo(	const _bstr_t& bstrPath, 
						const _bstr_t& bstrLabel=(BSTR)NULL, 
						const _bstr_t& bstrServiceTypeGuid=(BSTR)NULL )
	{
		ResetInfo();
		IMSMQQueueInfo*	pqinfo=NULL;
		HRESULT hr = ::CoCreateInstance(CLSID_MSMQQueueInfo,
								NULL,      // punkOuter
								CLSCTX_SERVER,
								IID_IMSMQQueueInfo,
								(void**)&pqinfo);

		if (SUCCEEDED(hr))
		{
			m_pqinfo = pqinfo;
			hr = m_pqinfo->put_PathName(bstrPath);
		}

		if(SUCCEEDED(hr))
		{
			if(!bstrLabel)
			{
				// don't set label
			}
			else 
			{
				if(FAILED(hr = m_pqinfo->put_Label(bstrLabel)))
					return hr;
			}
		}

		if(SUCCEEDED(hr))
		{
			if(!bstrServiceTypeGuid)
			{
				// don't set service type
			}
			else 
			{
				hr = m_pqinfo->put_ServiceTypeGuid(bstrServiceTypeGuid); 
			}
		}
		return hr;
	}

// take ownership of your QueueInfo object after releasing the current QueueInfo
	inline void SetInfo(IMSMQQueueInfo* pqinfo)
	{
		OTLASSERT(pqinfo);
		ResetInfo();
		pqinfo->AddRef();
		m_pqinfo = pqinfo;
	}

// release the current QueueInfo
	inline void ResetInfo()
	{
		if(m_pqinfo)
		{
			m_pqinfo->Release();
			m_pqinfo = NULL;
		}
	}


};

};	// namespace StingrayOTL

#endif // __OTLMSMQ_H__
