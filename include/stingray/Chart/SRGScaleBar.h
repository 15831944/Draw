///////////////////////////////////////////////////////////////////////////////
// SRGScaleBar.h
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


#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#if !defined(AFX_SRGSCALEBAR_H__8319F185_C754_11D2_B341_006008AF1D5D__INCLUDED_)
#define AFX_SRGSCALEBAR_H__8319F185_C754_11D2_B341_006008AF1D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block block for SRGScaleBar 

//$head Specialized scale classes
//$level 2

//@doc SRGScaleBar
//@mdata SRGDisplayBase*  | SRGScaleBar | m_pDisplay | The cached display pointer this component is working with

//@doc SRGScaleBar
//@mdata BOOL    | SRGScaleBar | m_bShowAxis | Flag whether the axis should draw an axis line

//@doc SRGScaleBar
//@mdata BOOL    | SRGScaleBar | m_bShowTick | Flag whether the axis should draw the tick marks

//@doc SRGScaleBar
//@mdata SRGScaleType  | SRGScaleBar | m_nScaleType | Store the scale type of this component

//@doc SRGScaleBar
//@mdata int     | SRGScaleBar | m_nAxisWidth | The axis line width

//@doc SRGScaleBar
//@mdata COLORREF   | SRGScaleBar | m_AxisColor | Color of the Axis line

//@doc SRGScaleBar
//@mdata int     | SRGScaleBar | m_nAxisPenStyle | The pen style of the axis line

//@doc SRGScaleBar
//@mdata double    | SRGScaleBar | m_dConvertRatio | If the conversion mode is RATIO_CONVERSION, this variable will specify the ratio

//@doc SRGScaleBar
//@mdata int     | SRGScaleBar | m_nConversionMode | Specify the conversion mode, default is NO_CONVERSION

//@doc SRGScaleBar
//@mfunc virtual double | SRGScaleBar | DoConversion | Used when the conversion mode is FUNC_CONVERSION
//@parm double | dValue | The value

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetTickColor | Sets the RGB colour of the tick msrks.
//@parm COLORREF  | clr | The colour

//@doc SRGScaleBar
//@mfunc COLORREF  | SRGScaleBar | GetTickColor | Returns the tick color  

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetAxisWidth | Sets the width (in pixels) of the axis line. 
//@parm int  | nWidth | The width of the axis line. 

//@doc SRGScaleBar
//@mfunc int  | SRGScaleBar | GetAxisWidth | Returns the width (in pixels) of the axis line.

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetAxisColor | Initialises the colour of the axis line
//@parm COLORREF  | clr | An RGB color definition. 

//@doc SRGScaleBar
//@mfunc COLORREF  | SRGScaleBar | GetAxisColor | Interrogates the axis line colour .

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetShowAxis | Call this to enable the display of the axis line.	
//@parm BOOL  | bShowAxis | TRUE to show the axis line.

//@doc SRGScaleBar
//@mfunc BOOL  | SRGScaleBar | GetShowAxis | Interrogates the axis line setting

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetShowTick | Initialises the axis tick setting. 
//@parm BOOL  | bShowTick | TRUE to enable the axis ticks.

//@doc SRGScaleBar
//@mfunc BOOL  | SRGScaleBar | GetShowTick | Returns the axis tick setting.

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetScaleType | Initialises the scale type setting.<nl>
//Valid scale types are..<nl>
//HORIZONTAL for scales that go across the top or bottom of a display.
//VERTICAL for scales that attach to the left or righ of a display.
//ANGLE for scales that may be set to any arbitrary angle.
//@parm SRGScaleType  | nType | The type, VERTICAL, HORIZONTAL or ANGLE.

//@doc SRGScaleBar
//@mfunc SRGScaleType  | SRGScaleBar  | GetScaleType | Returns the SRGScaleBar type. 

//@doc SRGScaleBar
//@mfunc int  | SRGScaleBar | GetConversionMode | Returns the conversion mode. See 

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetConversionRatio | Sets a numerical ratio (as a floating point double) by which values will be multiplied to ascertain the final scale values. This is good for linear conversions.<nl>
//For non-linear conversions you must use the FUNC_CONVERSION type and override the DoConversion function to suit your application.
//@parm double  | dRatio | The actiual conversion ratio.

//@doc SRGScaleBar
//@mfunc double  | SRGScaleBar | GetConversionRatio | Returns the conversion ratio.

//@doc SRGScaleBar
//@mfunc void  | SRGScaleBar | SetConversionMode | Initialises the conversion mode used to calculate relationships between scales.  There are three different settings for the conversion mode. They are...<nl>
//NO_CONVERSION	<tab> In this case no conversion is performed <nl>
//RATIO_CONVERSION <tab> When this option is set a strate ratiometric conversion is performed using the value set by SetConversionRatio<nl>
//FUNC_CONVERSION <tab> This option calls DoConversion with a double value as its parameter. You must derive from this class and override DoConversion to provide a suitable conversion routine.<nl>
//@parm int  | nMode | The conversion standard to use. 

// adinsert AutoDuck insertion point for SRGScaleBar 

//@topic SRGScaleBar Class Overview |
//Scale bars are a new component type that allow you to place a standard axis scale in the component list.<nl>
//These scales should be placed after an SRGraphDisplay component from which information about the placement of the display rectangle will be taken.<nl>
//

//@doc SRGScaleBar 
//@class NEW OC6.01 Scalebars are designed to allow you to place independant axis scales near your chart display. 
class SRGScaleBar : public SRGDecimalScale  
{
	CHART_DECLARE_SERIAL(SRGScaleBar)

protected:
	//@cmember
	/* A cached display pointer this component work with */
	SRGDisplayBase* m_pDisplay;
	//@cmember
	/* Flag for axis line drawing */
	BOOL			m_bShowAxis;
	//@cmember
	/* Flag for tick marks drawing of the axis */
	BOOL			m_bShowTick;

	//@cmember
	/* Scale type of this axis scale */
	SRGScaleType	m_nScaleType;

	//@cmember
	/* The axis line width */
	int				m_nAxisWidth;
	//@cmember
	/* The color of the axis line */
	COLORREF		m_AxisColor;
	//@cmember
	/* The line style of the axis line */
	int				m_nAxisPenStyle;

	//@cmember
	/* When using RATIO_CONVERSION, it stores the conversion ratio */
	double			m_dConvertRatio;
	//@cmember
	/* What kind of conversion this scale will use? */
	int				m_nConversionMode;

public:
	enum 
	{
		NO_CONVERSION = 0,
		RATIO_CONVERSION = 1,
		FUNC_CONVERSION = 2
	};
	//@cmember
	/*  */
	CHART_API virtual void Serialize(CArchive& ar);
	//@cmember
	/* Override this function to do custom drawing */
	CHART_API virtual void DrawForeground();
	//@cmember
	/* Draw the grid lines on top of the display component  */
	CHART_API virtual void DrawGrids();
	//@cmember
	/* Used when the conversion mode is FUNC_CONVERSION */
	inline virtual double DoConversion(double dValue)
	{
		return dValue;
	}
	//@cmember
	/* Create the axis labels and the tick marks position */
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Calculate the bounding rectangle of this component */
	CHART_API virtual void GetBoundingPolygon(CPoint * points,int nPointCount = 5);
	//@cmember
	/* Set the parent graph of this component */
	CHART_API virtual void SetParent(SRGraph* pParent);
	//@cmember
	/* Fill the background of this component */
	CHART_API virtual void DrawFill();
	//@cmember
	/* Draw shadow for this component */
	CHART_API virtual void DrawShadow();
	//@cmember
	/* Draw border for this component */
	CHART_API virtual void DrawBorder();
	//@cmember
	/* Do the final setting before drawing */
	CHART_API virtual void BeforeDraw();
	//@cmember
	/* The top most draw function of this component */
	CHART_API virtual void Draw(CDC* pDC, CWnd* pWnd);

	//@cmember
	/* Find the attach display component if not set by SetDisplay() */
	CHART_API virtual SRGDisplayBase* FindAttachDisplay();

	//@cmember
	/* Method to explicitly attach the specified display component */
	CHART_API virtual void SetDisplay(SRGDisplayBase* pDisplay);
	//@cmember
	/* Returns a pointer to the attached display component */
	CHART_API virtual SRGDisplayBase* GetDisplay();
	//@cmember
	/* Sets all labels perpendicular to the line between the start and end points*/
	CHART_API virtual void SetRTAngles();

	//@cmember
	/* Set the tick marks color */
	inline void SetTickColor(COLORREF clr) { m_Style.SetFrameColor(clr); }
	//@cmember
	/* Get Tick marks color */
	inline COLORREF GetTickColor() { return m_Style.GetFrameColor(); }
	//@cmember
	/* Set axis width, inlined */
	inline void SetAxisWidth(int nWidth) { if( nWidth > 0 ) m_nAxisWidth = nWidth; }
	//@cmember
	/* Get the axis width, inlined */
	int	GetAxisWidth() { return m_nAxisWidth; }
	//@cmember
	/* Set axis color, inlined */
	inline void SetAxisColor(COLORREF clr) { m_AxisColor = clr; }
	//@cmember
	/* Get axis color, inlined */
	inline COLORREF GetAxisColor() { return m_AxisColor; }
	//@cmember
	/* Set the flag of show axis, inlined */
	inline void SetShowAxis(BOOL bShowAxis) { m_bShowAxis = bShowAxis; }
	//@cmember
	/* Check if need to show axis, inlined */
	inline BOOL GetShowAxis() { return m_bShowAxis; }
	//@cmember
	/* Set flag for showing tick marks, inlined */
	inline void SetShowTick(BOOL bShowTick){m_bShowTick=bShowTick;}
	//@cmember
	/* Check if need to show tick marks, inlined */
	inline BOOL GetShowTick(){return m_bShowTick;}

	//@cmember
	/* Set the scale type, inlined */
	inline void SetScaleType(SRGScaleType nType ) { m_nScaleType = nType; }
	//@cmember
	/* Get the scale type, inlined */
	inline SRGScaleType GetScaleType () { return m_nScaleType; }
	
	//@cmember
	/* Set the conversion mode, inlined */
	inline void SetConversionMode(int nMode){if( nMode >= NO_CONVERSION && nMode <= FUNC_CONVERSION )	m_nConversionMode = nMode;	}

	//@cmember
	/* Get conversion mode, inlined */
	inline int GetConversionMode() { return m_nConversionMode; }

	//@cmember
	/* Set conversion ratio, used when conversion mode is RATIO_CONVERSION, inlined */
	inline void SetConversionRatio(double dRatio) { m_dConvertRatio = dRatio; }
	//@cmember
	/* Get conversion ratio, inlined */
	inline double GetConversionRatio() { return m_dConvertRatio; }

	CHART_API SRGScaleBar();
	CHART_API virtual ~SRGScaleBar();

	// XML Formatter for SRGScaleBar
	friend class SRGScaleBarFTR;
};


/////////////////////////////
// AutoDuck tag block block for SRGDateBar 

//@doc SRGDateBar
//@mfunc void  | SRGDateBar | SetMinValue | Sets the minimum scale bar value 
//@parm COleDateTime  | t | The value to set. 

//@doc SRGDateBar
//@mfunc void  | SRGDateBar | SetMaxValue | Sets the maximum scale bar value 
//@parm COleDateTime  | t | The value to set. 

//@doc SRGDateBar
//@mfunc void  | SRGDateBar | SetResolution | Sets the scale bar resolution.
//@parm COleDateTimeSpan  | s | A time and date value that is used to set the steps between the minimum and maximum values.

// adinsert AutoDuck insertion point for SRGDateBar 
//@topic SRGDateBar  Class Overview |
//The date bar class is based upon the <c SRGScaleBar> class and provides 
//an axis scale component that can be added to your chart component layout.<nl>
//The date-bar displays date and time information in the same format as is used in the 
//COleDateTime class. 

#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE != 201)
//@doc SRGDateBar 
//@class NEW OC 6.01. This class is one of the 
class SRGDateBar : public SRGScaleBar
{
	CHART_DECLARE_SERIAL(SRGDateBar)

public:
	//@cmember
	/* Formatting the time into date format */
	CHART_API CString TimeFormat(LPCTSTR strFormatString, COleDateTime dt);

	//@cmember
	/* Create axis labels and the tick marks position */
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Constructor */
	CHART_API SRGDateBar();
	//@cmember
	/* Destructor */
	CHART_API virtual ~SRGDateBar();

	//@cmember
	/* Set the minimum value for this scale-bar */
	inline void SetMinValue(COleDateTime t) { m_dMinValue = (double)t.m_dt; }
	//@cmember
	/* Set the maximum value for this scale-bar */
	inline void SetMaxValue(COleDateTime t) { m_dMaxValue = (double)t.m_dt; }
	//@cmember
	/* Set the scale bar resolution */
	inline void SetResolution(COleDateTimeSpan s) { m_dResolution=(double)s.m_span;}

	// XML Formatter for SRGDateBar
	friend class SRGDateBar;
};
#endif


/////////////////////////////
// AutoDuck tag block block for SRGLogBar 
// adinsert AutoDuck insertion point for SRGLogBar 
//@topic SRGLogBar  Class Overview |
//The SRGLogBar is a scale bar object that displays a logarithmic scale. See <c SRGScaleBar> for more details on the operation of these types of object.

//@doc SRGLogBar 
//@class A ScaleBar class that displays a logarithmic scale.
class SRGLogBar : public SRGScaleBar
{
	CHART_DECLARE_SERIAL(SRGLogBar)
public:
	//@cmember
	/* Create the axis labels and the tick marks position */
	CHART_API  virtual void CreateLabels();
	CHART_API SRGLogBar();
	CHART_API virtual ~SRGLogBar();

	// XML Formatter for SRGLogBar
	friend class SRGLogBar;
};

#endif // !defined(AFX_SRGSCALEBAR_H__8319F185_C754_11D2_B341_006008AF1D5D__INCLUDED_)

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

