#include "stdafx.h"
#include "UndoCtrl.h"
#include "DBDoc.h"
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
	m_pDoc->UpdateViews(D_UPDATE_BUFFER_BEFFORE);
	m_pDoc->UpdateViews(D_UPDATE_BUFFER_AFTER);
}