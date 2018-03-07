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

void CUndoCtrl::CloseEditDB()
{
	//m_pDoc->UpdateViews(D_UPDATE_BUFFER_BEFFORE);
	m_pDoc->UpdateViews(D_UPDATE_BUFFER_AFTER);
}

void CUndoCtrl::AddUndoMatl(int nCmd, T_MATL_K Key, T_MATL_D& rData)
{
	CDB_MATLU* pvMemb = &m_pDoc->m_vbuff->m_matl;
	T_MATL_UDRD_D data_ur;
	data_ur.Key = Key;
	data_ur.data = rData;
	pvMemb->Add(m_pDoc->m_vbuff->AddBuffer(UR_MATL_ADD), data_ur);
}