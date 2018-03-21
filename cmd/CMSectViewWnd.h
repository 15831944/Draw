#pragma once
#include "HeaderPre.h"
class ICMPainter
{
public:
	ICMPainter();
	~ICMPainter();
	CRect m_DrawArea;	
	
public:
	void SetDrawingArea(const CRect& r);
};
class __MY_EXT_CLASS__ CCMSectViewWnd : public CWnd
{
public:
	CCMSectViewWnd(void);
	~CCMSectViewWnd(void);
	DECLARE_MESSAGE_MAP()
private:
	ICMPainter m_Painter;// Geometry Painting Interface
	T_SECT_D* m_pDataSrc;
public:
	BOOL Init(CWnd* pWnd);
	void SetDataSource(T_SECT_D* pData);
	afx_msg void OnPaint();
};
#include "HeaderPost.h"