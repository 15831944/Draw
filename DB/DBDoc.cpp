#include "stdafx.h"

#include "EditData.h"
#include "UndoCtrl.h"
#include "AttrCtrl.h"
#include "DataCtrl.h"
#include "DataMemb.h"
#include "MatlDB.h"
#include "DBDoc.h"
IMPLEMENT_DYNCREATE(CDBDoc, CDocument)
CDBDoc* CDBDoc::m_pDBDoc = NULL;
CDBDoc::CDBDoc()
{
	m_pDBDoc = this;
	m_memb = new CDataMemb();//origin data buffer
	m_pEditData = new CEditData(this);
	m_pUndoCtrl = new CUndoCtrl(this);
	m_pAttrCtrl = new CAttrCtrl(this);
	m_pDataCtrl = new CDataCtrl(this);
	m_pMatlDB = new CMatlDB(this);
	//
	m_pEditData->initialize();
	m_pUndoCtrl->initialize();
	m_pAttrCtrl->initialize();
	m_pDataCtrl->initialize();
	m_pMatlDB->initialize();
}

CDBDoc * CDBDoc::GetDocPoint()
{
	return m_pDBDoc;
}

BEGIN_MESSAGE_MAP(CDBDoc, CDocument)
	
END_MESSAGE_MAP()


void CDBDoc::UpdateViews(LPARAM lUpdateType)
{

}