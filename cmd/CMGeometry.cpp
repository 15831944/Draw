#include "stdafx.h"
#include "CMGeometry.h"


CCMGeom2DArray::CCMGeom2DArray(void)
{
	m_aGeom2D = 0;
}
CCMGeom2DArray::~CCMGeom2DArray(void)
{
}
void CCMGeom2DArray::Draw(CDC* pDC,const CPoint& offset,double scale)
{
	if(m_aGeom2D)
		m_aGeom2D->Draw(pDC,offset,scale);
}
void CCMGeom2DArray::Add(CCMGeom2D* pGeom2D)
{
	if(m_aGeom2D)
	{
		delete m_aGeom2D;
		m_aGeom2D = 0;
	}
	m_aGeom2D = pGeom2D;
}


CCMGeom2D::CCMGeom2D(COLORREF PenColor,COLORREF BrushColor)
{
	CCMGeom2D::PenColor = PenColor;
	CCMGeom2D::BrushColor = BrushColor;
}
int CCMGeom2D::RoundUp(double dValue)
{
	if(dValue>0)
		return (int)floor(dValue+0.5);
	else
		return (int)ceil(dValue-0.5);
}


CCMLine::CCMLine(COLORREF PenColor,COLORREF BrushColor)
	:CCMGeom2D(PenColor,BrushColor)
{

}


CCMPolygon::CCMPolygon()
{

}
CCMPolygon::CCMPolygon(COLORREF PenColor,COLORREF BrushColor)
	:CCMGeom2D(PenColor,BrushColor)
{

}
void CCMPolygon::Draw(CDC* pDC,const CPoint& offset,double scale)
{
	int nCount = static_cast<int>(m_aVertex.GetSize());
	CPoint* pt = new CPoint[nCount];
	SCMPoint2D v;
	for(int i = 0;i<nCount;i++)
	{
		v = m_aVertex.GetAt(i);
		pt[i].x = RoundUp(v.x*scale+offset.x);
		pt[i].y = RoundUp(v.y*scale+offset.y);
	}
	CPen pen(PS_SOLID,1,PenColor);
	CBrush brush(BrushColor);
	pDC->SelectObject(&pen);
	pDC->SelectObject(&brush);
	pDC->Polygon(pt,nCount);
	delete[] pt;
}
SCMRect2D CCMPolygon::GetMBR()
{
	SCMRect2D mbr;
	if(m_aVertex.GetSize()<1)return mbr;
	for(int i = 0;i<m_aVertex.GetSize();i++)
	{
		if(m_aVertex[i].x > mbr.max.x)mbr.max.x = m_aVertex[i].x;
		if(m_aVertex[i].y > mbr.max.y)mbr.max.y = m_aVertex[i].y;
	}
	return mbr;
}