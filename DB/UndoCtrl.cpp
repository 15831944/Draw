#include "stdafx.h"
#include "UndoCtrl.h"
#include "DBDoc.h"
#include "UndoRedo.h"
#include "DataMemb.h"
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
	m_pDoc->m_vbuff->ClearBuffer();
	m_pDoc->m_vbuff->StartCmd(strCmd,nCommandType);
	m_pDoc->m_redo->ClearBuffer();
	m_pDoc->m_undo->StartCmd(strCmd,nCommandType);
	return TRUE;
}
void CUndoCtrl::CloseEditDB()
{
	//m_pDoc->UpdateViews(D_UPDATE_BUFFER_BEFFORE);
	//m_pDoc->DoUndoOnly();
	m_pDoc->UpdateViews(D_UPDATE_BUFFER_BEFFORE);
}
int CUndoCtrl::CmdRever(int nCmd)
{
	switch (nCmd)
	{
	case UR_MATL_ADD:return UR_MATL_DEL;
	case UR_MATL_DEL:return UR_MATL_ADD;

	default:
		break;
	}
	return 0;
}
#pragma region Matl
void CUndoCtrl::AddUndoMatl(int nCmd, T_MATL_K Key, T_MATL_D& rData)
{
	CDB_MATLU* pvMemb = &m_pDoc->m_vbuff->m_matl;
	CDB_MATLU* puMemb = &m_pDoc->m_undo->m_matl;
	T_MATL_UDRD_D data_ur;
	data_ur.Key = Key;
	data_ur.data = rData;
	pvMemb->Add(m_pDoc->m_vbuff->AddBuffer(CmdRever(nCmd)), data_ur);//view
	puMemb->Add(m_pDoc->m_undo->AddBuffer(nCmd),data_ur);//undo
}
void CUndoCtrl::UndoRedo(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbf,CDataMemb* pMemb,BOOL bCancel,int nUndoCount)
{
	if(pViewbf!=NULL)pViewbf->ClearBuffer();

	int nCount = static_cast<int>(pUndo->m_uridx.GetCount());
	if(nUndoCount > nCount) nUndoCount = nCount;
	T_UDRD_INDEX idex_ur;
	T_UDRD_BUFFER buffer_ur;
	for(int i=0;i<nUndoCount;i++)
	{
		idex_ur = pUndo->m_uridx.GetTail();
		pRedo->StartCmd(idex_ur.strCmd,idex_ur.nCommandType);
		while(!pUndo->m_urbuf.IsEmpty())
		{
			buffer_ur = pUndo->m_urbuf.GetTail();
			if(buffer_ur.Index != idex_ur.Index)break;
			UndoRedoCase(pUndo,pRedo,pViewbf,pMemb,buffer_ur.nCmd,buffer_ur.nKey);
			pUndo->m_urbuf.RemoveTail();
		}
		pUndo->m_uridx.RemoveTail();
	}
	
}
void CUndoCtrl::UndoRedoCase(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbuf,CDataMemb* pDataMemb,int nCmd,int nKey)
{
	switch (nCmd)
	{
	case UR_MATL_ADD:
	case UR_MATL_DEL:
		DoUndoMatl(pUndo,pRedo,pViewbuf,pDataMemb,nCmd,nKey);
		break;
	default:
		break;
	}
}
void CUndoCtrl::DoUndoMatl(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbuf,CDataMemb* pMemb,int nCmd,int nKey)
{
	ASSERT(nCmd == UR_MATL_DEL || nCmd == UR_MATL_ADD);
	CDB_MATL* pMMemb = &pMemb->m_matl;
	CDB_MATLU* pUMemb = &pUndo->m_matl;
	CDB_MATLU* pRMemb = &pRedo->m_matl;
	CDB_MATLU* pVMemb = NULL;
	if(pViewbuf != NULL)pVMemb = &pViewbuf->m_matl;
	T_MATL_UDRD_D data_ur;
	pUMemb->Get(nKey,data_ur);
	pUMemb->Del(nKey);
	pUndo->DecreaseBuffer();
	pRMemb->Add(pRedo->AddBuffer(CmdRever(nCmd)),data_ur);
	if(pVMemb != NULL)pVMemb->Add(pViewbuf->AddBuffer(nCmd),data_ur);
	if(nCmd == UR_MATL_ADD)pMMemb->Add(data_ur.Key,data_ur.data);
	else if(nCmd == UR_MATL_DEL)pMMemb->Del(data_ur.Key);
}
#pragma endregion Matl