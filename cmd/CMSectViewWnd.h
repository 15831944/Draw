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
	void MakePictureAngle(CCMGeom2DArray& aGeom);
	void MakePictureChannel(CCMGeom2DArray& aGeom);
	void MakePictureHBeam(CCMGeom2DArray& aGeom);
	void MakePictureTee(CCMGeom2DArray& aGeom);
	void MakePictureBox(CCMGeom2DArray& aGeom);
	void MakePicturePipe(CCMGeom2DArray& aGeom);
	void MakePictureDblAngle(CCMGeom2DArray& aGeom);
	void MakePictureDblChannel(CCMGeom2DArray& aGeom);
	void MakePictureSolidRect(CCMGeom2DArray& aGeom);
	void MakePictureSolidCircle(CCMGeom2DArray& aGeom);
	void GetRegularData(double& H,double& B1,double& tw,double& tf1,double& B2,double& tf2);
	void _MakeRect(double minx,double miny,double maxx,double maxy,CCMPolygon* pPolygon);
	void _MakeLeftAngle(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeRightAngle(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeLeftChannel(double H,double B1,double tw,double tf1,double B2,double tf2,CCMPolygon* pPolygon);
	void _MakeRightChannel(double H,double B1,double tw,double tf1,double B2,double tf2,CCMPolygon* pPolygon);
	void _MakeHBeam(double H,double B1,double tw,double tf1,double B2,double tf2,CCMPolygon* pPolygon);
	void _MakeTee(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeBox(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeDblAngle(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeDblChannel(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeSolieRect(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
	void _MakeSolidCircle(double H,double B,double tw,double tf,CCMPolygon* pPolygon);
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