///////////////////////////////////////////////////////////////////////////////
// SRGraphRect.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc SRGraphRect
//@module SRGraphRect.h|  definition of the graph rectangle classes<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGraphRect.h: definition of the graph component rectangle classes
//
/////////////////////////////////////////////////////////////
#ifndef __SRGRAPHRECT__
#define __SRGRAPHRECT__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphRect

//@doc SRGraphRect

//@mfunc  | SRGraphRect | SRGraphRect | Constructor with device independent coordinates
//@parm double | left | Left side coordinate
//@parm double | topt | Top edge coordinate
//@parm double | right | Right side coordinate
//@parm double | bottom | Bottom edge coordinate

//@mfunc  | SRGraphRect | SRGraphRect | Default constructor

//@mfunc void | SRGraphRect | operator = | Assignment operator (overload #1)
//@parm SRGraphRect & | r | Reference to an existing SRGraphRect

//@mfunc void | SRGraphRect | operator = | Assignment operator (overload #2)
//@parm CRect & | r | Reference to a CRect object<nl>
//The edge coordinates are converted to doubles and stored in the equivalent variable in this SRGraphRect.

//@mfunc double | SRGraphRect | Width | Returns the width of the object
//@rdesc Right-Left
//@see <mf SRGraphRect::Height> 
 
//@mfunc double | SRGraphRect | Height | Returns the height of the object
//@rdesc Bottom-Top
//@see <mf SRGraphRect::Width>

//@mfunc void | SRGraphRect | Move | Shifts the rectangle by the x and y offsets provided
//@parm double | x | Value by which to move horizontally (may be negative)
//@parm double | y | Value by which to move vertically (may be negative)

//@mfunc void | SRGraphRect | GetLogRect | Returns the logical rectangle determined by CalcCRect during draw process<nl>
//If the logical coordinates have not been determined (the component has not been drawn), the value CRect(0,0,0,0) should be returned.
//@rdesc The rectangle in device dependent coordinates.

//@mdata double | SRGraphRect | left | Left side coordinate

//@mdata double | SRGraphRect | top |  Top edge coordinate

//@mdata double | SRGraphRect | right |	 Right side coordinate

//@mdata double | SRGraphRect | bottom |  Bottom edge coordinate

//@mdata int  | SRGraphRect | m_nType |	Type of measurement used<nl>
//Values may be one of...<nl>
//0 = PIXELS<nl>
//1 = MILLIMETERS<nl>
//2 = INCHES<nl>
//3 = PERCENTAGE of available area

//@mdata CRect | SRGraphRect | m_LogRect | Used in the calculation of logical rectangles from device independent rectangles (private)

//@mdata SRGraph *  | SRGraphRect | m_pGraph | Pointer to the SRGraph object that manages the chart

// adinsert for SRGraphRect
//$head Component rectangle manager
//$level 1
/////////////////////////////////////////////////////////

//@doc SRGraphRect
//@class Device independent rectangle class
//@base public | CObject
class SRGraphRect : public CObject
{
//@access public data members
public:
	//@cmember
	/* Device independent coordinate for the left of the rectangle*/
	double left;
	//@cmember
	/* Device independent coordinate for the top of the rectangle*/
	double top;
	//@cmember
	/* Device independent coordinate for the right of the rectangle*/
	double right;
	//@cmember
	/* Device independent coordinate for the bottom of the rectangle*/
	double bottom;

	enum _MeasurementTypes {
		pixel,
		millimeter,
		inch,
		percentage
	} ;


//@access protected data members
protected:
	//@cmember
	/* Pointer to the parent graph*/
	SRGraph * m_pGraph;
	//@cmember
	/* Type of measurement used: 0=pixels, 1=millimeters, 2=inches, 3=percentage*/
	int  m_nType;

	//@cmember
	/* CRect object for internal conversions and calculations*/
	CRect m_LogRect;


//@access public member functions
public:
	//@cmember
	/* Initializes the pointer to the owner graph*/
	CHART_API virtual void SetGraph(SRGraph *pGraph);
	//@cmember
	/* Returns m_nType data member*/
	CHART_API virtual int GetMeasurement();
	//@cmember
	/* Initializes m_nType data member*/
	CHART_API virtual void SetMeasurement(int m);
	//@cmember
	/* Initializes the rectangle from a CRect*/
	CHART_API virtual void SetRect(const CRect& r);
	//@cmember
	/* Initializes the rectangle with device independent coordinates*/
	CHART_API virtual void SetRect(double l,double t,double r, double b);
	//@cmember
	/* Construction*/
	inline SRGraphRect()
	{	left=top=right=bottom=(double)-1.0;
		m_nType=0; m_pGraph=NULL;
		m_LogRect=CRect(0,0,0,0);
	}
	//@cmember
	/* Construction*/
	inline SRGraphRect(double l,double t,double r,double b)
	{	left=l; top=t; right=r; bottom=b; 
		m_nType=0; 
		m_LogRect=CRect((int)l,(int)t,(int)r,(int)b);
	}
	//@cmember
	/* Construction*/
	CHART_API SRGraphRect(CRect& r);
	//@cmember
	/* Copy Constructor*/
	CHART_API SRGraphRect(SRGraphRect& r);


	//@cmember
	/* Calculates logical rectangle from device independent coordinates*/
	CHART_API virtual CRect CalcCRect(CDC *pDC,CWnd *pCWnd=NULL);

	//@cmember
	/* Returns the logical rectangle determined by CalcCRect during draw process*/
	CHART_API virtual CRect GetLogRect(){return m_LogRect;};


	CHART_DECLARE_SERIAL(SRGraphRect);
	//@cmember
	/* Stores or retrieves information via a CArchive*/
	CHART_API virtual void Serialize(CArchive& ar);


	//@cmember
	/* Assignment of data from an existing SRGraphRect object*/
	CHART_API void operator =(const SRGraphRect& r){top=r.top;
										  left=r.left;
										  bottom=r.bottom; 
										  right=r.right; 
										  m_nType=r.m_nType;
										  m_pGraph=r.m_pGraph;
										  m_LogRect=r.m_LogRect;}

	//@cmember
	/* Assignment of data from a CRect object*/
	CHART_API void operator =(const CRect& r){top=(double)r.top; 
									left=(double)r.left; 
									bottom=(double)r.bottom; 
									right=(double)r.right;
									m_LogRect.SetRect(0,0,0,0);}

	//@cmember
	/* Test for equality of one SRGRect to another.*/
	BOOL operator ==(const SRGraphRect& r)
	{
		return (left==r.left &&
				right==r.right &&
				top==r.top &&
				bottom==r.bottom &&
				m_nType==m_nType);
	}

	//@cmember
	/* Returns the width of the rectangle*/
	inline double Width(){return right-left;}
	//@cmember
	/* Returns the height of the rectangle*/
	inline double Height(){return bottom-top;}
	//@cmember
	/* Displaces the rectangle*/
	inline void Move(double x, double y){left+=x; right+=x; top+=y; bottom+=y;m_LogRect.SetRect(0,0,0,0);}
	//@cmember
	/* Expands the rectangle*/
	CHART_API  void Grow(double x, double y);
	//@cmember
	/* Calculates device independent measurements*/
	CHART_API void CRectToSRGRect(CRect& rect,CDC *pDC);

	//@cmember
	/* Calculates device independent measurements (special overload for percentage measuring system)*/
	CHART_API virtual void CRectToSRGRect(CRect& rect,CDC *pDC,CWnd *pCWnd);

	friend class SRGraphComponent;

	// XML formatter for SRGraphRect
	friend class SRGraphRectFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // __SRGRAPHRECT__
