#include "stdafx.h"
#include "CMSectViewWnd.h"
#pragma region ICMPainter
ICMPainter::ICMPainter(){}
ICMPainter::~ICMPainter(){}
void ICMPainter::SetDrawingArea(const CRect& r)
{
	m_DrawArea = r;
}
#pragma endregion ICMPainter

CCMSectViewWnd::CCMSectViewWnd(void)
{
}
CCMSectViewWnd::~CCMSectViewWnd(void)
{
}
BEGIN_MESSAGE_MAP(CCMSectViewWnd,CWnd)
END_MESSAGE_MAP()
BOOL CCMSectViewWnd::Init(CWnd* pWnd)
{
	if(!SubclassWindow(pWnd->m_hWnd))
	{
		TRACE(_LS(IDS_CMD0417__Fail_To_Subclassing_n));
		return FALSE;
	}
	LONG dwStyle;
	dwStyle = GetWindowLong(m_hWnd,GWL_STYLE);
	dwStyle |= WS_CLIPCHILDREN;
	SetWindowLong(m_hWnd,GWL_STYLE,dwStyle);
	CRect r;
	pWnd->GetWindowRect(r);
	m_Painter.SetDrawingArea(r);
	return TRUE;
}
void CCMSectViewWnd::SetDataSource(T_SECT_D* pData)
{
	m_pDataSrc = pData;
}