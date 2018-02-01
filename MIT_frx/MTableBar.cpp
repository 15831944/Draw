#include "stdafx.h"
#include "MTableBar.h"
#include "MLayeredDockingControlBar.h"
#include "MTable.h"
#include "MTabbedChildFrm.h"
#include "MTableManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit::lib;
using namespace mit::frx;

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar

BEGIN_MESSAGE_MAP(MTableBar, MLayeredDockingControlBar)
	//{{AFX_MSG_MAP(MAutoDestroyBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()	
	ON_WM_PAINT()	
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar construction/destruction

IMPLEMENT_SERIAL(MTableBar, MLayeredDockingControlBar, VERSIONABLE_SCHEMA | 2)
MTableBar::MTableBar()
{
	m_pDoc = NULL;
	m_arTables.RemoveAll();
	m_arRTC.RemoveAll();
}

MTableBar::MTableBar(CDocument* pDoc)
{
	ASSERT(pDoc);

	m_pDoc = pDoc;
	m_arTables.RemoveAll();
	m_arRTC.RemoveAll();
}

MTableBar::MTableBar(CDocument* pDoc, CRuntimeClass* pRTC)
{
	ASSERT(pDoc);

	m_pDoc = pDoc;
	m_arTables.RemoveAll();
	m_arRTC.RemoveAll();
	AddTableClass(pRTC);
}

MTableBar::MTableBar(CDocument* pDoc, CArray<CRuntimeClass*>& arRTCs)
{
	ASSERT(pDoc);

	m_pDoc = pDoc;
	m_arTables.RemoveAll();
	m_arRTC.RemoveAll();
	SetTableClass(arRTCs);
}

MTableBar::~MTableBar()
{
	int iSize = (int)m_arTables.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		_SAFE_DELETE(m_arTables[i]);
	}
	
	m_arRTC.RemoveAll();
}

int MTableBar::SetTableClass(CArray<CRuntimeClass*>& arTable)
{
	m_arRTC.RemoveAll();

	m_arRTC.Copy(arTable);

	return (int)m_arRTC.GetSize();
}

void MTableBar::AddTableClass(CRuntimeClass* pRTC)
{
	if( !pRTC->IsDerivedFrom(RUNTIME_CLASS(MTable)) )
	{
		ASSERT(0);
	}

	m_arRTC.Add(pRTC);
}

const CRuntimeClass* MTableBar::GetTableClass(int idx)
{
	if( idx < 0 || idx >= (int)m_arRTC.GetSize() )
	{
		// 인덱스를 제대로 넣으라고!!!
		ASSERT(0);
		return NULL;
	}

	return m_arRTC[idx];
}

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar message handlers

int MTableBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MLayeredDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	int iSize = (int)m_arTables.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		_SAFE_DELETE(m_arTables[i]);
	}
	m_arTables.RemoveAll();
		
	iSize = (int)m_arRTC.GetSize();

	if( iSize == 1 )
	{
		MTable* pTable = (MTable*)m_arRTC[0]->CreateObject();
		pTable->GetTableDB()->SetDocument(m_pDoc);

		if (!pTable->Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/, CRect(0,0, 300, 500), this, WM_USER) )
		{
			TRACE0("Failed to create workspace view\n");
			return -1;      // fail to create
		}

		m_arTables.Add(pTable);

		pTable->AdjustLayout();
	}
	else if( iSize > 1 )
	{
		CRect rectDummy;
		rectDummy.SetRectEmpty ();

		// Create tabs window:
		if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, WM_USER))
		{
			TRACE0("Failed to create output tab window\n");
			return -1;      // fail to create
		}

		m_wndTabs.RemoveAllTabs();

		for( int i=0; i<iSize; ++i )
		{
			MTable* pTable = (MTable*)m_arRTC[i]->CreateObject();
			pTable->GetTableDB()->SetDocument(m_pDoc);

			if (!pTable->Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/, CRect(0,0, 300, 500), &m_wndTabs, WM_USER+(i+1) ) )
			{
				TRACE0("Failed to create workspace view\n");
				return -1;      // fail to create
			}

			m_arTables.Add(pTable);

			TCHAR buffer[10];
			_itot(i+1, buffer, 10);
			m_wndTabs.AddTab(pTable, pTable->GetTableTitle() + buffer, (UINT)-1);
		}

		m_wndTabs.RecalcLayout();
	}
	
	return 0;
}

void MTableBar::OnPressCloseButton ()
{
	CFrameWnd* pParentFrame = DYNAMIC_DOWNCAST (CFrameWnd, BCGPGetParentFrame (this));
	ASSERT_VALID (pParentFrame);

	if (pParentFrame != NULL)
	{
		if (pParentFrame->SendMessage (BCGM_ON_PRESS_CLOSE_BUTTON, NULL, (LPARAM) (LPVOID) this))
		{
			return;
		}
	}

	SendMessage(WM_CLOSE, NULL, NULL);

	pParentFrame->RecalcLayout();
}

BOOL MTableBar::CanBeTabbedDocument () const
{
	ASSERT_VALID (this);

	if (IsAutoHideMode ())
	{
		return FALSE;
	}

	return TRUE;
}

void MTableBar::OnSize(UINT nType, int cx, int cy) 
{
	MLayeredDockingControlBar::OnSize(nType, cx, cy);

	int iSize = (int)m_arTables.GetSize();
	
	if( iSize == 1 )
	{
		if( m_arTables[0] && m_arTables[0]->GetSafeHwnd() )
		{
			// Tab control should cover a whole client area:
			m_arTables[0]->SetWindowPos (NULL, 0, 0, cx, cy,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}
	else if( iSize > 1)
	{
		m_wndTabs.SetWindowPos (NULL, 0, 0, cx, cy,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void MTableBar::OnClose()
{
	if( m_wndTabs.GetSafeHwnd() )
	{
		m_wndTabs.RemoveAllTabs();
	}
	
	int iSize = (int)m_arTables.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		if( m_arTables[i]->GetSafeHwnd() )
		{
			m_arTables[i]->DestroyWindow();
		}

		_SAFE_DELETE(m_arTables[i]);
	}
	m_arTables.RemoveAll();

	MLayeredDockingControlBar::OnClose();
}

BOOL MTableBar::DestroyWindow()
{
	// Override 시 아래 내용을 반드시 처리해야 함. 
	BOOL bResult = MLayeredDockingControlBar::DestroyWindow();

	if( !MTableManager::GetInstance()->RemoveTableBar(GetRuntimeClass(), m_pDoc) )
	{
		ASSERT(0);
		return FALSE;
	}

	return bResult;
}

void MTableBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	MLayeredDockingControlBar::OnNcCalcSize(bCalcValidRects, lpncsp);
}

//***********************************************************************
void MTableBar::OnNcPaint() 
{
	MLayeredDockingControlBar::OnNcPaint();
}

void MTableBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect (rectClient);

	dc.FillRect (rectClient, &globalData.brBarFace);
}