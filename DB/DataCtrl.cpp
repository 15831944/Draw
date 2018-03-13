#include "stdafx.h"
#include "DBDoc.h"
#include "DataCtrl.h"
#include "EditData.h"
#include "UndoCtrl.h"
#include "AttrCtrl.h"
CDataCtrl::CDataCtrl(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CDataCtrl::~CDataCtrl() {}

void CDataCtrl::initialize()
{
	m_pEditData = m_pDoc->m_pEditData;
	m_pUndoCtrl = m_pDoc->m_pUndoCtrl;
	m_pAttrCtrl = m_pDoc->m_pAttrCtrl;
}
BOOL CDataCtrl::StartEdit(const CString& strCmd,int nCmdType)
{
	return m_pUndoCtrl->StartEditDB(strCmd,nCmdType);
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
	if(!StartEdit(_LS(IDS_DB_DATACTRL_Add_Material),CMDTYPE_REMOVE_ANALYSIS))return FALSE;
	for (int i = 0; i < nCount; i++)
	{
		if(m_pAttrCtrl->ExistMatl(rKey[i]))
		{
			AfxMessageBox(_LS(IDS_DB_MATL_EXIST));
			continue;
		}
		if (!m_pEditData->AddMatl(rKey[i], rData[i]))
			return FALSE;
	}
	return EndEdit();
}
BOOL CDataCtrl::DelMatl(T_MATL_K Key)
{
	CArray<T_MATL_K,T_MATL_K> rKey;
	rKey.Add(Key);
	return DelMatl(rKey);
}
BOOL CDataCtrl::DelMatl(CArray<T_MATL_K, T_MATL_K>& rKey)
{
	int nCount = static_cast<int>(rKey.GetCount());
	ASSERT(nCount != 0);
	if(!StartEdit(_LS(IDS_DB_DATACTRL_Delete_Material),CMDTYPE_REMOVE_ANALYSIS))return FALSE;
	for(int i=0;i<nCount;i++)
	{
		if(!m_pAttrCtrl->ExistMatl(rKey[i]))
		{
			AfxMessageBox(_LS(IDS_DB_MATL_NOEXIST));
			continue;
		}
		if(!m_pEditData->DelMatl(rKey[i]))
			return FALSE;
	}
	return EndEdit(TRUE);
}