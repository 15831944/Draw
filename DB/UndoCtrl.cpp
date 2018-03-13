#include "stdafx.h"
#include "UndoCtrl.h"
#include "DBDoc.h"
#include "UndoRedo.h"

CUndoCtrl::CUndoCtrl(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CUndoCtrl::~CUndoCtrl()
{
}

void CUndoCtrl::initialize()
{
	
}
BOOL CUndoCtrl::StartEditDB(const CString& strCmd,int nCommandType)
{
	m_pDoc->m_undo->StartCmd(strCmd,nCommandType);
	return TRUE;
}
void CUndoCtrl::CloseEditDB()
{
	//m_pDoc->UpdateViews(D_UPDATE_BUFFER_BEFFORE);
	m_pDoc->UpdateViews(D_UPDATE_BUFFER_AFTER);
	m_pDoc->DoUndoOnly();

}

void CUndoCtrl::AddUndoMatl(int nCmd, T_MATL_K Key, T_MATL_D& rData)
{
	CDB_MATLU* pvMemb = &m_pDoc->m_vbuff->m_matl;
	T_MATL_UDRD_D data_ur;
	data_ur.Key = Key;
	data_ur.data = rData;
	pvMemb->Add(m_pDoc->m_vbuff->AddBuffer(nCmd), data_ur);//view
	m_pDoc->m_undo->AddBuffer(nCmd);//undo
}
void CUndoCtrl::UndoRedo(CUndoRedo* pUndo,CUndoRedo* pViewbf)
{
	if(pViewbf!=NULL)pViewbf->ClearBuffer();

}