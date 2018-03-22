#include "stdafx.h"
#include "CMSectViewWnd.h"
#include "../DB/SectUtil.h"

#pragma region Color
const COLORREF CCM_WHITE		= COLORREF(RGB(255, 255, 255));
const COLORREF CCM_BLACK		= COLORREF(RGB(0, 0, 0));
const COLORREF CCM_REDGREEN = COLORREF(RGB(128, 128, 0));
const COLORREF CCM_GRAY     = COLORREF(RGB(128, 128, 128));
const COLORREF CCM_BLUE     = COLORREF(RGB(0, 0, 255));
const COLORREF CCM_DARKBLUE = COLORREF(RGB(0, 0, 128));
const COLORREF CCM_YELLOW   = COLORREF(RGB(255, 255, 0));
const COLORREF CCM_CYAN     = COLORREF(RGB(0, 255, 255));
const COLORREF CCM_RED      = COLORREF(RGB(255, 0, 0));

const COLORREF CCM_BORDER		=	CCM_WHITE;
const COLORREF CCM_FILL			= CCM_REDGREEN;
const COLORREF CCM_HOLE			=	CCM_BLACK;
#pragma endregion Color


#pragma region ICMPainter
ICMPainter::ICMPainter(){}
ICMPainter::~ICMPainter(){}
void ICMPainter::SetDrawingArea(const CRect& r)
{
	m_DrawArea = r;
}
void ICMPainter::DrawSection(CDC* pDC,CCMGeom2DArray& aGeom)
{
	if(m_DrawArea.left >= m_DrawArea.right)return;
	if(m_DrawArea.top >= m_DrawArea.bottom)return;
	CPoint org,offset;
	CRect rect;
	rect = m_DrawArea;
	double scale;
	CalcScaleOrgOff(aGeom,rect,org,offset,scale);
	aGeom.Draw(pDC,offset,scale);
	DrawAxis(pDC,org);
}
void ICMPainter::DrawAxis(CDC* pDC,CPoint& org)
{
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	//int nSaveDC = pDC->SaveDC();
	pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,255));

	pDC->Ellipse(org.x-1,org.y-1,org.x+3,org.y+2);
	pDC->MoveTo(org.x,org.y);
	pDC->LineTo(org.x,org.y-15);
	pDC->MoveTo(org.x,org.y-20);
	pDC->LineTo(org.x-2,org.y-15);
	pDC->MoveTo(org.x-2,org.y-15);
	pDC->LineTo(org.x+2,org.y-15);
	pDC->MoveTo(org.x+2,org.y-15);
	pDC->LineTo(org.x,org.y-20);
	pDC->TextOut(org.x-4,org.y-36,_T("z"),1);

	pDC->MoveTo(org.x,org.y);
	pDC->LineTo(org.x+15,org.y);
	pDC->MoveTo(org.x+20,org.y);
	pDC->LineTo(org.x+15,org.y-2);
	pDC->MoveTo(org.x+20,org.y);
	pDC->LineTo(org.x+15,org.y+2);
	pDC->MoveTo(org.x+15,org.y-2);
	pDC->LineTo(org.x+15,org.y+2);
	pDC->TextOut(org.x+25,org.y-8,_T("y"),1);
	//pDC->RestoreDC(nSaveDC);
}
void ICMPainter::CalcScaleOrgOff(CCMGeom2DArray& aGeom,CRect& rect,CPoint& org,CPoint& offset,double& scale)
{
	SCMRect2D mbr = aGeom.GetMBR();
	double xRadio,yRadio;
	if(mbr.Width() < cZero)xRadio = 0.0;
	else xRadio = rect.Width()/mbr.Width()*0.7;
	if(mbr.Height() < cZero) yRadio = 0.0;
	else yRadio = rect.Height()/mbr.Height()*0.7;
	scale = min(xRadio,yRadio);
	if(scale < cZero) scale = max(xRadio,yRadio);
	offset.x = (rect.Width() - (int)(mbr.Width()*scale))/2;
	offset.y = (rect.Height() - (int)(mbr.Height()*scale))/2;
	org.x = rect.Width()/2;
	org.y = rect.Height()/2;
}
void ICMPainter::EraseBkgnd(CDC* pDC)
{
	//int nSaveDC = pDC->SaveDC();
	if(m_DrawArea.left >= m_DrawArea.right)return;
	if(m_DrawArea.top >= m_DrawArea.bottom)return;
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CBrush backBrush(RGB(0,0,0));
	pDC->SelectObject(&pen);
	pDC->SelectObject(&backBrush);
	CRect rect;
	rect = m_DrawArea;
	pDC->PatBlt(rect.left,rect.top,rect.Width(),rect.Height(),PATCOPY);
	//pDC->RestoreDC(nSaveDC);
}
#pragma endregion ICMPainter


#pragma region ICMGeomMaker
void ICMGeomMaker::MakePicture(T_SECT_D* pSect,CCMGeom2DArray& aGeom)
{
	m_pDataSrc = pSect;
	switch(pSect->nStype)
	{
	case D_SECT_TYPE_REGULAR:
		{
			CString csShape = pSect->SectI.Shape;
			int nShape = CSectUtil::GetShapeIndexFromNameReg(csShape);
			switch (nShape)
			{
			case D_SECT_SHAPE_REG_H:
				MakePictureHBeam(aGeom);	break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
void ICMGeomMaker::MakePictureHBeam(CCMGeom2DArray& aGeom)
{
	double H,B1,tw,tf1,B2,tf2;
	GetRegularData(H,B1,tw,tf1,B2,tf2);
	CCMPolygon* pGeom2D = new CCMPolygon(CCM_BORDER,CCM_FILL);
	_MakeHBeam(H,B1,tw,tf1,B2,tf2,pGeom2D);
	aGeom.Add(pGeom2D);
}
void ICMGeomMaker::GetRegularData(double& H,double& B1,double& tw,double& tf1,double& B2,double& tf2)
{
	H = m_pDataSrc->SectI.dSize[0];
	B1 = m_pDataSrc->SectI.dSize[1];
	tw = m_pDataSrc->SectI.dSize[2];
	tf1 = m_pDataSrc->SectI.dSize[3];
	B2 = m_pDataSrc->SectI.dSize[4];
	tf2 = m_pDataSrc->SectI.dSize[5];
}
void ICMGeomMaker::_MakeHBeam(double H,double B1,double tw,double tf1,double B2,double tf2,CCMPolygon* pPolygon)
{
	if(fabs(B2) < cZero)B2 = B1;
	if(fabs(tf2) < cZero) tf2 = tf1;
	pPolygon->Add(SCMPoint2D(0.0,0.0));
	pPolygon->Add(SCMPoint2D(0.0,tf1));
	pPolygon->Add(SCMPoint2D((B1-tw)/2.0,tf1));
	pPolygon->Add(SCMPoint2D((B1-tw)/2.0,H-tf2));
	pPolygon->Add(SCMPoint2D((B1-B2)/2.,H-tf2));
	pPolygon->Add(SCMPoint2D((B1-B2)/2.,H));
	pPolygon->Add(SCMPoint2D((B1+B2)/2.,H));
	pPolygon->Add(SCMPoint2D((B1+B2)/2.,H-tf2));
	pPolygon->Add(SCMPoint2D((B1+tw)/2.0,H-tf2));
	pPolygon->Add(SCMPoint2D((B1+tw)/2.0,tf1));
	pPolygon->Add(SCMPoint2D(B1,tf1));
	pPolygon->Add(SCMPoint2D(B1,0));

}
#pragma endregion ICMGeomMaker


#pragma region CCMSectViewWnd
CCMSectViewWnd::CCMSectViewWnd(void)
{
}
CCMSectViewWnd::~CCMSectViewWnd(void)
{
}
BEGIN_MESSAGE_MAP(CCMSectViewWnd,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
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
	pWnd->GetClientRect(r);
	m_Painter.SetDrawingArea(r);
	return TRUE;
}
void CCMSectViewWnd::SetDataSource(T_SECT_D* pData)
{
	m_pDataSrc = pData;
}
void CCMSectViewWnd::OnPaint()
{
	CPaintDC dc(this);
	if(m_pDataSrc)
	{
		if(m_pDataSrc->nStype == 0)return;
		CSectUtil::CalcSectData(*m_pDataSrc);
		CCMGeom2DArray aGeom;
		m_GeomMaker.MakePicture(m_pDataSrc,aGeom);
		m_Painter.DrawSection(&dc,aGeom);
	}
}
BOOL CCMSectViewWnd::OnEraseBkgnd(CDC* pDC)
{
	m_Painter.EraseBkgnd(pDC);
	return CWnd::OnEraseBkgnd(pDC);
}
#pragma endregion CCMSectViewWnd