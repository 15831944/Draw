#pragma once
struct SCMPoint2D
{
	SCMPoint2D(){x = 0.;y = 0.;}
	SCMPoint2D(double dx,double dy){x = dx;y = dy;}
	double x,y;
};
struct SCMRect2D
{
	SCMRect2D(){}
	SCMRect2D(double minx,double miny,double maxx,double maxy)
	{
		min.x = minx;	miny = miny;	max.x = maxx;	max.y = maxy;
	}
	double Width(){return max.x - min.x;}
	double Height(){return max.y - min.y;}
	SCMPoint2D min,max;
};

class CCMGeom2D
{
public:
	CCMGeom2D(){}
	CCMGeom2D(COLORREF PenColor,COLORREF BrushColor);
	virtual ~CCMGeom2D(){}
	virtual void Draw(CDC* pDC,const CPoint& offset,double scale)=0;
	virtual SCMRect2D GetMBR()=0;
protected:
	int RoundUp(double dValue);//��������
	COLORREF PenColor,BrushColor;
	
};
class CCMLine:public CCMGeom2D
{
public:
	CCMLine(COLORREF PenColor,COLORREF BrushColor);
	//virtual void dddd(){};
};
class CCMPolygon:public CCMGeom2D
{
public:
	CCMPolygon();
	CCMPolygon(COLORREF PenColor,COLORREF BrushColor);
	~CCMPolygon(){}
	
	int Add(SCMPoint2D& pt){return (int)m_aVertex.Add(pt);}
private:
	virtual SCMRect2D GetMBR();
	virtual void Draw(CDC* pDC,const CPoint& offset,double scale);
private:
	CArray<SCMPoint2D,SCMPoint2D&> m_aVertex;
};
class CCMGeom2DArray
{
public:
	CCMGeom2DArray(void);
	~CCMGeom2DArray(void);
	void Draw(CDC* pDC,const CPoint& offset,double scale);
	void Add(CCMGeom2D* pGeom2D);
	SCMRect2D GetMBR(){return m_aGeom2D->GetMBR();}
	
private:
	CCMGeom2D* m_aGeom2D;
};
