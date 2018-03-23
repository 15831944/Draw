#include "stdafx.h"
#include "CMGeometry.h"


CCMGeom2DArray::CCMGeom2DArray(void)
{
}
CCMGeom2DArray::~CCMGeom2DArray(void)
{
	for(int i = 0;i<m_aGeom2D.GetSize();i++)
		delete m_aGeom2D[i];
}
void CCMGeom2DArray::Draw(CDC* pDC,const CPoint& offset,double scale)
{
	for(int i = 0;i<m_aGeom2D.GetSize();i++)
		m_aGeom2D[i]->Draw(pDC,offset,scale);
}
void CCMGeom2DArray::Add(CCMGeom2D* pGeom2D)
{
	m_aGeom2D.Add(pGeom2D);
}
SCMRect2D CCMGeom2DArray::GetMBR()
{
	SCMRect2D mbr;
	SCMRect2D tmp;
	for(int i = 0;i<m_aGeom2D.GetSize();i++)
	{
		tmp = m_aGeom2D[i]->GetMBR();
		if(mbr.max.x < tmp.max.x)mbr.max.x = tmp.max.x;
		if(mbr.max.y < tmp.max.y)mbr.max.y = tmp.max.y;
	}
	return mbr;
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
CCMPolygon::~CCMPolygon()
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
void CCMPolygon::Transfer(SCMPoint2D offset)
{
	for(int i=0;i<m_aVertex.GetSize();i++)
	{
		m_aVertex[i].x += offset.x;
		m_aVertex[i].y +=offset.y;
	}
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


CCMEllipse::CCMEllipse()
{

}
CCMEllipse::CCMEllipse(COLORREF PenColor,COLORREF BrushColor)
	:CCMGeom2D(PenColor,BrushColor)
{
}
CCMEllipse::~CCMEllipse()
{

}
void CCMEllipse::Draw(CDC* pDC,const CPoint& offset,double scale)
{
	/*int nCount = static_cast<int>(m_aVertex.GetSize());
	CPoint* pt = new CPoint[nCount];
	SCMPoint2D v;
	for(int i = 0;i<nCount;i++)
	{
	v = m_aVertex.GetAt(i);
	pt[i].x = RoundUp(v.x*scale+offset.x);
	pt[i].y = RoundUp(v.y*scale+offset.y);
	}*/
	SCMPoint2D v;
	CRect ellipse;
	v = m_Rect.min;
	ellipse.left = RoundUp(v.x*scale+offset.x);
	ellipse.top = RoundUp(v.y*scale+offset.y);
	v = m_Rect.max;
	ellipse.right = RoundUp(v.x*scale+offset.x);
	ellipse.bottom = RoundUp(v.y*scale+offset.y);

	CPen pen(PS_SOLID,1,PenColor);
	CBrush brush(BrushColor);
	pDC->SelectObject(&pen);
	pDC->SelectObject(&brush);
	pDC->Ellipse(ellipse);
}
