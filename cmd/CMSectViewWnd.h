#pragma once
#include "HeaderPre.h"
#include "CMGeometry.h"
class ICMPainter
{
public:
	ICMPainter();
	~ICMPainter();
	CRect m_DrawArea;	
	
public:
	void SetDrawingArea(const CRect& r);
	void DrawSection(CDC* pDC,CCMGeom2DArray& aGeom);
	void EraseBkgnd(CDC* pDC);
private:
	void DrawAxis(CDC* pDC,CPoint& org);
	void CalcScaleOrgOff(CCMGeom2DArray& aGeom,CRect& rect,CPoint& org,CPoint& offset,double& scale);
};
class ICMGeomMaker
{
public:
	ICMGeomMaker(){}
	~ICMGeomMaker(){}
	void MakePicture(T_SECT_D* pSect,CCMGeom2DArray& aGeom);
private:
	T_SECT_D* m_pDataSrc;
	void MakePictureHBeam(CCMGeom2DArray& aGeom);
	void GetRegularData(double& H,double& B1,double& tw,double& tf1,double& B2,double& tf2);
	void _MakeHBeam(double H,double B1,double tw,double tf1,double B2,double tf2,CCMPolygon* pPolygon);
};
class __MY_EXT_CLASS__ CCMSectViewWnd : public CWnd
{
public:
	CCMSectViewWnd(void);
	~CCMSectViewWnd(void);
	DECLARE_MESSAGE_MAP()
private:
	ICMPainter m_Painter;// Geometry Painting Interface
	ICMGeomMaker m_GeomMaker;
	T_SECT_D* m_pDataSrc;
public:
	BOOL Init(CWnd* pWnd);
	void SetDataSource(T_SECT_D* pData);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
#include "HeaderPost.h"