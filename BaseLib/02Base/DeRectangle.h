#pragma once
#include "HeaderPre.h"
#include "Element.h"

class __MY_EXT_CLASS__ CDeRectangle:public CElement
{
public:
	CDeRectangle(void);
	~CDeRectangle(void);
	CDeRectangle(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle);
protected:
	CPoint m_EndPoint;
	void Draw(CDC *pDC,std::shared_ptr<CElement> pElement);
};

#include "HeaderPost.h"