#pragma once
#include <memory>

static const COLORREF SELECT_COLOR(RGB(180, 0, 0));//默认画笔颜色
class CElement : public CObject
{
protected:
	CElement(void);
	CElement(const CPoint &start, COLORREF color, int aPenStyle = PS_SOLID, int penWidth = 1);
	void CreatePen(CPen &aPen,std::shared_ptr<CElement> pElement);
public:
	virtual void Draw(CDC *pDC,std::shared_ptr<CElement> pElement=nullptr)=0;
	virtual ~CElement(void);
	//需要使占用区域失效时，使用此函数
	const CRect& GetEnclosingRect() const{ return m_EnClosingRect; }
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	int m_PenStyle;
	std::shared_ptr<CElement> m_PTempElement;
	CRect m_EnClosingRect;
};
typedef std::shared_ptr<CElement> CPElement;
