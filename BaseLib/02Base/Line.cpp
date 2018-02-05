#include "stdafx.h"
#include "Line.h"


CLine::CLine(void)
{
}

CLine::CLine(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle)
	:CElement(start,color,aPenStyle),m_EndPoint(end)
{
	m_EnClosingRect = CRect(start,end);
	m_EnClosingRect.NormalizeRect();
	m_EnClosingRect.InflateRect(m_PenWidth,m_PenWidth);
}

CLine::~CLine(void)
{
}

void CLine::Draw(CDC *pDC,std::shared_ptr<CElement> pElement/* =nullptr */)
{
	CPen aPen;
	CreatePen(aPen,pElement);
	auto pOldPen = pDC->SelectObject(&aPen);
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);
	pDC->SelectObject(pOldPen);
}