#include "stdafx.h"
#include "DBDoc.h"


IMPLEMENT_DYNCREATE(CDBDoc, CDocument)
CDBDoc* CDBDoc::m_pDBDoc = NULL;
CDBDoc::CDBDoc()
{
	m_pDBDoc = this;
	m_memb = new CDataMemb();//origin data buffer
		
	m_pAttrCtrl = new CAttrCtrl(this);
	m_pMatlDB = new CMatlDB(this);
	
	m_pAttrCtrl->initialize();

	m_pMatlDB->initialize();
}

CDBDoc * CDBDoc::GetDocPoint()
{
	return m_pDBDoc;
}

BEGIN_MESSAGE_MAP(CDBDoc, CDocument)
	
END_MESSAGE_MAP()