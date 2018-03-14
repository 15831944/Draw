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
	m_bIsUndoRedoVisible = FALSE;
	m_pUndoRedoDlg = 0;

	m_pDBDoc = this;
	m_redo  = new CUndoRedo();
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

void CDBDoc::CloseUDRDVisible()
{
	m_bIsUndoRedoVisible = FALSE;
}
void CDBDoc::UpdateViews(LPARAM lUpdataType)
{
	UpdateAllViews(NULL, lUpdataType);

}

void CDBDoc::UpdateAllViews(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pDlgCtrl->UpdateAllDlgs(NULL, lHint, NULL);
	CDocBase::UpdateAllViews(pSender, lHint, pHint);
}

void CDBDoc::DoUndoOnly()
{
	m_pUndoCtrl->UndoRedo(m_undo,m_redo,NULL,m_memb);
}

void CDBDoc::DoRedo()
{
	m_pUndoCtrl->UndoRedo(m_redo,m_undo,m_vbuff,m_memb,TRUE);
	UpdateViews(D_UPDATE_BUFFER_AFTER);
}

void CDBDoc::DoUndo()
{
	m_pUndoCtrl->UndoRedo(m_undo,m_redo,m_vbuff,m_memb,TRUE);
	UpdateViews(D_UPDATE_BUFFER_AFTER);
}