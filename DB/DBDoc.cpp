#include "stdafx.h"
#include "EditData.h"
#include "UndoCtrl.h"
#include "AttrCtrl.h"
#include "DataCtrl.h"
#include "DataMemb.h"
#include "MatlDB.h"
#include "ViewBuff.h"
#include "UndoRedo.h"
#include "DBDoc.h"

#include "../BaseLib/ModelessDlgCtrl.h"
IMPLEMENT_DYNCREATE(CDBDoc, CDocBase)
CDBDoc* CDBDoc::m_pDBDoc = NULL;
CDBDoc::CDBDoc()
{
	m_pDBDoc = this;
	m_undo = new CUndoRedo();
	m_vbuff = new CUndoRedo();

	m_memb = new CDataMemb();//origin data buffer
	m_pEditData = new CEditData(this);
	m_pUndoCtrl = new CUndoCtrl(this);
	m_pAttrCtrl = new CAttrCtrl(this);
	m_pDataCtrl = new CDataCtrl(this);
	m_pMatlDB = new CMatlDB(this);
	m_pViewBuff = new CViewBuff(this);
	//
	m_pEditData->initialize();
	m_pUndoCtrl->initialize();
	m_pAttrCtrl->initialize();
	m_pDataCtrl->initialize();
	m_pMatlDB->initialize();
	m_pViewBuff->initialize();
}

CDBDoc * CDBDoc::GetDocPoint()
{
	return m_pDBDoc;
}

BEGIN_MESSAGE_MAP(CDBDoc, CDocBase)

END_MESSAGE_MAP()


void CDBDoc::UpdateViews(LPARAM lUpdataType)
{
	UpdateAllViews(NULL, lUpdataType);
}

void CDBDoc::UpdateAllViews(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pDlgCtrl->UpdateAllDlgs(NULL, lHint, NULL);
	CDocBase::UpdateAllViews(pSender, lHint, pHint);
}