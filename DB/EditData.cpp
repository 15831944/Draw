#include "stdafx.h"
#include "EditData.h"
#include "DBDoc.h"
#include "DataMemb.h"





CEditData::CEditData(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CEditData::~CEditData() {}

void CEditData::initialize()
{
	m_pDataMemb = m_pDoc->m_memb;
}

BOOL CEditData::AddMatl(T_MATL_K Key, T_MATL_D& rData)
{
	T_MATD_D DataDesign;
	DataDesign.Initialize();
	if (!AddMatd(Key, DataDesign))return FALSE;
	return TRUE;
}

BOOL CEditData::AddMatd(T_MATL_K Key, T_MATD_D& rData)
{
	m_pDataMemb->m_matl.AddDesign(Key, rData);
	return FALSE;
}