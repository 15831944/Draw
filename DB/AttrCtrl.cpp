#include "stdafx.h"
#include "DBDoc.h"
#include "DataMemb.h"
#include "AttrCtrl.h"

CAttrCtrl::CAttrCtrl(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}


CAttrCtrl::~CAttrCtrl()
{
}

void CAttrCtrl::initialize()
{
	m_pDataMemb = m_pDoc->m_memb;
}

T_MATL_K CAttrCtrl::GetStartNumMatl()
{
	return m_pDataMemb->m_matl.m_nStartNum;
}

int CAttrCtrl::GetCountMatl()
{
	return m_pDataMemb->m_matl.GetCount();
}

POSITION CAttrCtrl::GetStartMatl()
{
	return m_pDataMemb->m_matl.GetStart();
}

void CAttrCtrl::GetNextMatl(POSITION& rNextPostion, T_MATL_K& Key, T_MATL_D& rData)
{
	m_pDataMemb->m_matl.GetNext(rNextPostion, Key, rData);
}

BOOL CAttrCtrl::GetMatl(T_MATL_K Key, T_MATL_D& rData)
{
	return m_pDataMemb->m_matl.Get(Key, rData);
}