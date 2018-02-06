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