#include "stdafx.h"
#include "EditData.h"
#include "DBDoc.h"
#include "DataMemb.h"

#include "UndoCtrl.h"

CEditData::CEditData(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CEditData::~CEditData() {}

void CEditData::initialize()
{
	m_pDataMemb = m_pDoc->m_memb;
	m_pUndoCtrl = m_pDoc->m_pUndoCtrl;
}

BOOL CEditData::AddMatl(T_MATL_K Key, T_MATL_D& rData)
{
	//T_MATD_D DataDesign;
	//DataDesign.Initialize();
	//T_MATL_D tempData;
	m_pUndoCtrl->AddUndoMatl(UR_MATL_DEL, Key, rData);
	m_pDataMemb->m_matl.Add(Key, rData);
		
	//if (!AddMatd(Key, DataDesign))return FALSE;
	return TRUE;
}
BOOL CEditData::AddMatd(T_MATL_K Key, T_MATD_D& rData)
{
	m_pDataMemb->m_matl.AddDesign(Key, rData);
	return FALSE;
}
BOOL CEditData::DelMatl(T_MATL_K Key)
{
	T_MATL_D data;
	m_pDataMemb->m_matl.Get(Key,data);
	m_pUndoCtrl->AddUndoMatl(UR_MATL_ADD,Key,data);
	m_pDataMemb->m_matl.Del(Key);
	return TRUE;
}
