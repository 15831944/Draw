#include "stdafx.h"
#include "Element.h"


CElement::CElement(void)
{
}
CElement::CElement(const CPoint& start, COLORREF color, int aPenStyle,int penWidth /* = 1*/) :
	m_StartPoint(start), m_Color(color), m_PenWidth(penWidth),m_PenStyle(aPenStyle){}

CElement::~CElement(void)
{
}

void CElement::CreatePen(CPen &aPen,std::shared_ptr<CElement> pElement)
{
	//if(this == pElement.get())
	//	AfxMessageBox(_T("failed"),MB_OK);
	if (!aPen.CreatePen(m_PenStyle, m_PenWidth, this==pElement.get()?SELECT_COLOR:m_Color)){
		AfxMessageBox(_T("Pen Creation failed."), MB_OK);
	}
}