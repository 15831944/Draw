#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(void)
{
}

CRectangle::CRectangle(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle)
	:CElement(start,color,aPenStyle)
{

}

CRectangle::~CRectangle(void)
{
}

void CRectangle::Draw(CDC *pDC,std::shared_ptr<CElement> pElement/* =nullptr */)
{
	
}