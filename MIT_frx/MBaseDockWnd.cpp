#include "StdAfx.h"
#include "MBaseDockWnd.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNCREATE(MBaseDockWnd, CWnd)

MBaseDockWnd::MBaseDockWnd(void)
{
}

MBaseDockWnd::~MBaseDockWnd(void)
{
}

BEGIN_MESSAGE_MAP(MBaseDockWnd, CWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL MBaseDockWnd::Create(CWnd *pParent, UINT nID, CDocument* pDocument, DWORD dwStyle, CRect rect)
{
	CString wndClass = ::AfxRegisterWndClass(CS_DBLCLKS|CS_CLASSDC,	0, ::GetSysColorBrush(COLOR_WINDOW));
	m_pDocument = pDocument;

	return CWnd::Create( wndClass, _T(""), dwStyle, rect, pParent, nID );
}

BOOL MBaseDockWnd::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}