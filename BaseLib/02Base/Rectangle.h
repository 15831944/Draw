#pragma once
#include "HeaderPre.h"
#include "Element.h"

class __MY_EXT_CLASS__ CRectangle:public CElement
{
public:
	CRectangle(void);
	~CRectangle(void);
	CRectangle(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle);
protected:
	CPoint m_EndPoint;
	void Draw(CDC *pDC,std::shared_ptr<CElement> pElement);
};

#include "HeaderPost.h"