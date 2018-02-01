#include "stdafx.h"
#include "MChartBar.h"
#include "MLayeredDockingControlBar.h"
#include "MChartCtrl.h"
#include "MTabbedChildFrm.h"
#include "MChartManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit::lib;
using namespace mit::frx;

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar

BEGIN_MESSAGE_MAP(MChartBar, MLayeredDockingControlBar)
	//{{AFX_MSG_MAP(MAutoDestroyBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar construction/destruction

IMPLEMENT_SERIAL(MChartBar, MLayeredDockingControlBar, VERSIONABLE_SCHEMA | 2)
MChartBar::MChartBar()
{
	m_pDoc = NULL;
// 	m_arTables.RemoveAll();
 	m_arRTC.RemoveAll();
}

MChartBar::MChartBar(CDocument* pDoc)
{
	ASSERT(pDoc);

	m_pDoc = pDoc;
 	m_arChart.RemoveAll();
 	m_arRTC.RemoveAll();
}

MChartBar::MChartBar(CDocument* pDoc, CRuntimeClass* pRTC)
{
	ASSERT(pDoc);

	m_pDoc = pDoc;
 	m_arChart.RemoveAll();
 	m_arRTC.RemoveAll();
	AddChartClass(pRTC);
}

MChartBar::~MChartBar()
{
	int iSize = (int)m_arChart.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		_SAFE_DELETE(m_arChart[i]);
	}

	m_arRTC.RemoveAll();
}

int MChartBar::SetChartClass(CArray<CRuntimeClass*>& arTable)
{
	m_arRTC.RemoveAll();

	m_arRTC.Copy(arTable);

	return (int)m_arRTC.GetSize();
}

void MChartBar::AddChartClass(CRuntimeClass* pRTC)
{
	if( !pRTC->IsDerivedFrom(RUNTIME_CLASS(MChartCtrl)) )
	{
		ASSERT(0);
	}

	m_arRTC.Add(pRTC);
}

const CRuntimeClass* MChartBar::GetChartClass(int idx)
{
	if( idx < 0 || idx >= (int)m_arRTC.GetSize() )
	{
		// 인덱스를 제대로 넣으라고!!!
		ASSERT(0);
		return NULL;
	}

	return m_arRTC[idx];
}

const MChartCtrl* MChartBar::GetChart(int idx)
{
	if( idx < 0 || idx >= (int)m_arChart.GetSize() )
	{
		// 인덱스를 제대로 넣으라고!!!
		ASSERT(0);
		return NULL;
	}

	return m_arChart[idx];
}

int MChartBar::GetChartCount()
{
	return (int)m_arChart.GetSize();
}

/////////////////////////////////////////////////////////////////////////////
// MAutoDestroyBar message handlers

int MChartBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MLayeredDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	int iSize = (int)m_arChart.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		_SAFE_DELETE(m_arChart[i]);
	}
	m_arChart.RemoveAll();

	iSize = (int)m_arRTC.GetSize();

	if( iSize == 1 )
	{
		MChartCtrl* pChart = (MChartCtrl*)m_arRTC[0]->CreateObject();

		if (!pChart->Create (CRect(0,0, 500, 500), this, (UINT)-1, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER))
		{
			TRACE0("Failed to create workspace view\n");
			return -1;      // fail to create
		}
		pChart = m_pDrawedChart;
		//pChart->Redraw();
		m_arChart.Add(pChart);

		//pChart->AdjustLayout();
	}
	else if( iSize > 1 )
	{
		CRect rectDummy;
		rectDummy.SetRectEmpty ();

		// Create tabs window:
		if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
		{
			TRACE0("Failed to create output tab window\n");
			return -1;      // fail to create
		}

		m_wndTabs.RemoveAllTabs();

		for( int i=0; i<iSize; ++i )
		{
			MChartCtrl* pChart = (MChartCtrl*)m_arRTC[i]->CreateObject();

			if (!pChart->Create (CRect(0,0, 300, 500), &m_wndTabs, WM_USER + i, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER) )
			{
				TRACE0("Failed to create workspace view\n");
				return -1;      // fail to create
			}

			m_arChart.Add(pChart);

			TCHAR buffer[10];
			_itot(i+1, buffer, 10);
			m_wndTabs.AddTab(pChart, pChart->GetTitle() + buffer, (UINT)-1);
		}

		m_wndTabs.RecalcLayout();
	}

	return 0;
}

void MChartBar::OnPressCloseButton ()
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

BOOL MChartBar::CanBeTabbedDocument () const
{
	ASSERT_VALID (this);

	if (IsAutoHideMode ())
	{
		return FALSE;
	}

	return TRUE;
}

void MChartBar::OnSize(UINT nType, int cx, int cy) 
{
	MLayeredDockingControlBar::OnSize(nType, cx, cy);

	int iSize = (int)m_arChart.GetSize();

	if( iSize == 1 )
	{
		if( m_arChart[0] && m_arChart[0]->GetSafeHwnd() )
		{
			// Tab control should cover a whole client area:
			m_arChart[0]->SetWindowPos (NULL, -1, -1, cx, cy,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}
	else if( iSize > 1)
	{
		m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void MChartBar::OnClose()
{
	if( m_wndTabs.GetSafeHwnd() )
	{
		m_wndTabs.RemoveAllTabs();
	}

	int iSize = (int)m_arChart.GetSize();
	for( int i=0; i<iSize; ++i )
	{
		if( m_arChart[i]->GetSafeHwnd() )
		{
			m_arChart[i]->DestroyWindow();
		}

		_SAFE_DELETE(m_arChart[i]);
	}
	m_arChart.RemoveAll();

	MLayeredDockingControlBar::OnClose();
}

BOOL MChartBar::DestroyWindow()
{
	// Override 시 아래 내용을 반드시 처리해야 함. 
	BOOL bResult = MLayeredDockingControlBar::DestroyWindow();

	if( !MChartManager::GetInstance()->RemoveChartBar(GetRuntimeClass(), m_pDoc) )
	{
		ASSERT(0);
		return FALSE;
	}

	return bResult;
}