#pragma once
#include "HeaderPre.h"
#include "Element.h"

class __MY_EXT_CLASS__ CLine:public CElement
{
private:
	CLine(void);
public:
	
	~CLine(void);
	CLine(const CPoint& start,const CPoint& end,COLORREF color,int aPenStyle);
private:
	CPoint m_EndPoint;
	void Draw(CDC *pDC,std::shared_ptr<CElement> pElement=nullptr);
};

#include "HeaderPost.h"