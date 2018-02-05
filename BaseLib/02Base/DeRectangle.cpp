#include "stdafx.h"
#include "DeRectangle.h"


CDeRectangle::CDeRectangle(void)
{
}

CDeRectangle::CDeRectangle(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle)
	:CElement(start,color,aPenStyle),m_EndPoint(end)
{
	m_EnClosingRect = CRect(start,end);
	m_EnClosingRect.NormalizeRect();
	m_EnClosingRect.InflateRect(m_PenWidth,m_PenWidth);

}

CDeRectangle::~CDeRectangle(void)
{
}
void CDeRectangle::Draw(CDC *pDC,std::shared_ptr<CElement> pElement/* =nullptr */)
{
	CPen aPen;
	CreatePen(aPen,pElement);
	CPen* pOldPen = pDC->SelectObject(&aPen);
	pDC->Rectangle(CRect(m_StartPoint,m_EndPoint));
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);
	pDC->MoveTo(CPoint(m_StartPoint.x,m_EndPoint.y));
	pDC->LineTo(CPoint(m_EndPoint.x,m_StartPoint.y));
	
	pDC->SelectObject(pOldPen);
}