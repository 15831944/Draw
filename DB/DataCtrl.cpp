#include "stdafx.h"
#include "DBDoc.h"
#include "DataCtrl.h"
#include "EditData.h"
#include "UndoCtrl.h"

CDataCtrl::CDataCtrl(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CDataCtrl::~CDataCtrl() {}

void CDataCtrl::initialize()
{
	m_pEditData = m_pDoc->m_pEditData;
	m_pUndoCtrl = m_pDoc->m_pUndoCtrl;
}

BOOL CDataCtrl::EndEdit(BOOL bEnd /* = TRUE */)
{
	if (bEnd)
		m_pUndoCtrl->CloseEditDB();
	return TRUE;
}

BOOL CDataCtrl::AddMatl(T_MATL_K Key, const T_MATL_D& rData)
{ 
	CArray<T_MATL_K, T_MATL_K> aKey;
	CArray<T_MATL_D, const T_MATL_D&> aData;
	aKey.Add(Key);
	aData.Add(rData);
	return AddMatl(aKey, aData);
}

BOOL CDataCtrl::AddMatl(CArray<T_MATL_K, T_MATL_K>& rKey, CArray<T_MATL_D, const T_MATL_D &>& rData)
{
	int nCount = (int)rKey.GetSize();
	if (nCount == 0)return FALSE;
	ASSERT(nCount == rData.GetSize());
	for (int i = 0; i < nCount; i++)
	{
		if (!m_pEditData->AddMatl(rKey[i], rData[i]))
			return FALSE;
	}
	return EndEdit();
}

