///////////////////////////////////////////////////////////////////////////////
// DScale.h
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
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////
//@doc
//@module DScale.h | Class definition file for SRGDecimalScale, SRGLogScale, SRGDateScale, SRGIndexScale, SRGGroupScale classes<nl>
//These classes are derived from SRGraphLabelBlock and handle the creation and display of 
//scales along the sides of axes.<nl>
//Written by Bob Powell (www.roguewave.com)


#ifndef __SRGDECIMALSCALE__
#define __SRGDECIMALSCALE__

#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE != 201)
	#include <afxdisp.h>
#endif

#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif


///////////////////////////////////////////////////////////////////////
// Autoduck comment block for SRGDecimal Scale
//
//@doc SRGDecimalScale
//@mdata BOOL | SRGDecimalScale | m_bAscending | When TRUE numeric values count up from m_ptStart to m_ptEnd, 
//when FALSE they count down
//@see <mf SRGDecimalScale::SetAscending> <mf SRGDecimalScale::SetDescending>

//@mdata CPoint | SRGDecimalScale | m_ptStart | Defines the point in the device context 
//where the scale line should commence
//@rem For example, in the case of the classic axis, the line starts at the graph origin.
//@see <md SRGDecimalScale::m_ptEnd>	<mf SRGDecimalScale::SetStartPos>

//@mdata CPoint | SRGDecimalScale | m_ptEnd | Defines the point in the device context 
//where the scale line should end
//@see <md SRGDecimalScale::m_ptStart> <mf SRGDecimalScale::SetEndPos>

//@mdata double | SRGDecimalScale | m_dMinValue | Minimum numeric value of the scale
//@rem The numeric scale will show values from m_dMinValue to m_dMaxValue in steps of m_dResolution.
//@see <mf SRGDecimalScale::SetMinValue> <mf SRGDecimalScale::GetMinValue> <md SRGDecimalScale::m_dResolution> <md SRGDecimalScale::m_dMaxValue>

//@mdata double | SRGDecimalScale | m_dMaxValue | Maximum numeric value of the scale
//@rem The numeric scale will show values from m_dMinValue to m_dMaxValue in steps of m_dResolution.
//@see <mf SRGDecimalScale::SetMaxValue> <mf SRGDecimalScale::GetMaxValue> <md SRGDecimalScale::m_dResolution> <md SRGDecimalScale::m_dMinValue>

//@mdata double | SRGDecimalScale | m_dResolution | Numeric interval between labels -- 
//by default this value is 0.01, but it may be set to any desired value.
//@rem This value will be automatically changed to suit the length of the line and the size of the font. 
//The formula for these changes allows a sensible scale to be created 
//that works with most graph types. For example, if a decimal scale from 0 to 10 is required, 
//steps may be displayed as...<nl>
//0 1 2 3 4 5 6 7 8 9 10 or...<nl>
//0 2 4 6 8 10 or...<nl>
//0 0.5 1 1.5 2 2.5 3 3.5 etc.<nl>
//@see <mf SRGDecimalScale::SetResolution> <mf SRGDecimalScale::GetResolution>

//@mdata CString | SRGDecimalScale | m_strFormatString | Printf-style format string which 
//should contain only one floating point type format specifier and any other text that you want on your labels
//@rem You can use this to embellish your labels. For example, you might supply the format string " $%.2f " to display prices in dollars.
//@see <mf SRGDecimalScale::SetFormatString> 11GetFormatString>

//@mdata BOOL | SRGDecimalScale | m_bLabelSide | Side of the imaginary line upon which labels are placed -- default (FALSE) is the left/below, set TRUE to place on the right/above
//@ex |
//FALSE			TRUE
//
//10 |			| 10
// 8 |			| 8
// 6 |			| 6
// 4 |			| 4
// 2 |			| 2
// 0 |			| 0

//@mfunc void | SRGDecimalScale | SetStartPos | Defines the point at which the scale line starts
//@parm CPoint | prStart | Start position
//@rem An imaginary line is drawn between this point and the point defined in m_ptEnd. 
//The length of this line, its angle, and the size of the current font will all contribute to 
//the final scale and the angle at which the labels are displayed.
//@see <md SRGDecimalScale::m_ptrStart> <md SRGDecimalScale::m_ptEnd> <mf SRGDecimalScale::SetEndPos>

//@mfunc void | SRGDecimalScale | SetEndPos | Defines the point at which the scale line ends
//@parm CPoint | ptEnd | End position
//@see <md SRGDecimalScale::m_ptrStart> <md SRGDecimalScale::m_ptEnd> <mf SRGDecimalScale::SetStartPos>

//@mfunc void | SRGDecimalScale | SetResolution | Specifies the resolution of the steps in between labels
//@parm double | dResolution | Desired resolution
//@rem If your minimum and maximum values are 0 and 10 respectively and the resolution is set to 1.0, 
//the scale will be calculated as follows:<nl>
//If there is room for all the labels...		0 1 2 3 4 5 6 7 8 9 10<nl>
//If there is not enough room...				0 2 4 6 8 10<nl>
//If that won't fit...							0 5 10<nl>
//Whatever the range of values, the scale will be divided by 1, 5, 2, and 10 repeatedly until a fit is found.
//@see <mf SRGDecimalScale::GetResolution> <md SRGDecimalScale::m_dResolution>

//@mfunc void | SRGDecimalScale | SetMaxValue | Sets the maximum value which a scale may display
//@parm double | dMaxValue | Desired maximum value
//@ex An ideal percentage scale |
//	SetMaxValue(10);
//	SetMinValue(0);
//	SetResolution(0.1);
//@see <md SRGDecimalScale::m_dMaxValue> <mf SRGDecimalScale::GetMaxValue> <mf SRGDecimalScale::SetMinValue>

//@mfunc void | SRGDecimalScale | SetMinValue | Sets the minimum value which a scale may display
//@parm double | dMinValue | Desired minimum value
//@ex An ideal percentage scale |
//	SetMaxValue(10);
//	SetMinValue(0);
//	SetResolution(0.1);
//@see <md SRGDecimalScale::m_dMinValue> <mf SRGDecimalScale::GetMinValue> <mf SRGDecimalScale::SetMaxValue>


//@mfunc void | SRGDecimalScale | SetFormatString | Specifies a printf-style format string for the labels
//@parm LPCTSTR | strFormatString | Format string
//@see <md SRGDecimalScale::m_strFormatString> <mf SRGDecimalScale::GetFormatString>

//@mfunc void | SRGDecimalScale | SetLabelSide | Specifies on which side of the line between m_ptStart and m_ptEnd the labels are drawn
//@parm BOOL | b | TRUE to set labels on the right/above of the line, FALSE (default) to set them to the left/below
//@see <md SRGDecimalScale::m_bLabelSide> <mf SRGDecimalScale::GetLabelSide>

//@mfunc CPoint | SRGDecimalScale | GetStartPos | Interrogates the m_ptStart member
//@rdesc Start position of the scale line
//@see <md SRGDecimalScale::m_ptStart> <mf SRGDecimalScale::SetStartPos> 

//@mfunc CPoint | SRGDecimalScale | GetEndPos | Interrogates the m_ptEnd member
//@rdesc End position of the scale line
//@see <md SRGDecimalScale::m_ptEnd> <mf SRGDecimalScale::SetEndPos>

//@mfunc double | SRGDecimalScale | GetResolution | Interrogates the m_dResolution member
//@rdesc Difference in value of adjacent labels
//@see <md SRGDecimalScale::m_dResolution> <mf SRGDecimalScale::SetResolution>

//@mfunc void | SRGDecimalScale | SetAscending | Forces labels to be drawn in ascending order
//@see <mf SRGDecimalScale::SetDescending> <md SRGDecimalScale::m_bAscending>

//@mfunc void | SRGDecimalScale | SetDescending | Forces labels to be drawn in descending order
//@see <mf SRGDecimalScale::SetAscending> <md SRGDecimalScale::m_bAscending>

//@mfunc CString& | SRGDecimalScale |  GetFormatString | Interrogates the m_strFormatString member
//@rdesc Reference to a CString object containing the printf-style format string
//@see <md SRGDecimalScale::m_strFormatString> <mf SRGDecimalScale::SetFormatString>

//@mfunc BOOL | SRGDecimalScale | GetLabelSide | Interrogates the m_bLabelSide member
//@rdesc TRUE if labels are set to display on the right of or above the line, FALSE if they are on the left or below
//@see <md SRGDecimalScale::m_bLabelSide> <mf SRGDecimalScale::SetLabelSide>
	
//@mfunc double | SRGDecimalScale | GetMaxValue | Interrogates the m_dMaxValue member
//@rdesc Maximum value for the axis scale
//@see <md SRGDecimalScale::m_dMaxValue> <mf SRGDecimalScale::SetMaxValue> <mf SRGDecimalScale::GetMinValue>

//@mfunc double | SRGDecimalScale | GetMinValue |  Interrogates the m_dMinValue member.
//@rdesc Minimum value for the axis scale
//@see <md SRGDecimalScale::m_dMinValue> <mf SRGDecimalScale::SetMinValue> <mf SRGDecimalScale::GetMaxValue>
	
////////////////////////////////////////////////////////////////////////
//$head Component classes (Specialized sub components)
//$level 2

//@doc SRGDecimalScale
//@class Derived from SRGraphLabelBlock, this class manages a decimal numeric scale 
//placed between two screen point positions. The scale will automatically calculate the best possible 
//sequence of numbers depending upon the length of the line and the size of the font.<nl>
//This class will, by default, draw all the labels perpendicular to the imaginary line joining the two end points. 
//After the labels are created, they may be manipulated using the standard SRGraphLabelBlock methods.
class  SRGDecimalScale : public SRGraphLabelBlock
{
//@access Protected data members
protected:
	//@cmember
	/* Get the relative offset of the labels from the DC origin*/
	CHART_API virtual CPoint GetRelOffset();
	//@cmember
	/* Get the offset of the labels from the tick list*/
	CHART_API virtual CPoint GetOffset();
	//@cmember
	/* TRUE when the list of numerals generated is to go from low values toward high values*/
	BOOL m_bAscending;
	//@cmember
	/* Start position of the line of numerals*/
	CPoint m_ptStart;
	//@cmember
	/* End position of the line of numerals*/
	CPoint m_ptEnd;
	//@cmember
	/* Minimum value in the range of generated numbers*/
	double m_dMinValue;
	//@cmember
	/* Maximum value in the range of generated numbers*/
	double m_dMaxValue;
	//@cmember
	/* Preferred or initial resolution of steps in the number list*/
	double m_dResolution;
	//@cmember
	/* Format string used to generate the numeral strings (see sprintf)*/
	CString m_strFormatString;
	//@cmember
	/* Side of the imaginary line between m_ptStart and m_ptEnd on which labels are displayed -- FALSE=left/below, TRUE=right/above*/
	BOOL m_bLabelSide;

//@access public member functions 
public:
	//@cmember
	/* Writes or restores the scale to an archive for reuse*/
	CHART_API virtual void Serialize(CArchive &ar);

	//@cmember
	/* Constructor*/
	CHART_API SRGDecimalScale();

	CHART_DECLARE_SERIAL(SRGDecimalScale);
	
	//@cmember
	/* Constructor with initialization parameters*/
	CHART_API SRGDecimalScale(CPoint ptStart, CPoint ptEnd, double dMinValue, double dMaxValue, double dResolution,CString & strFormatString);
	
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGDecimalScale();

	//@cmember
	/* Specifies the start position of the scale line*/
	CHART_API virtual void SetStartPos(CPoint ptStart);

	//@cmember
	/* Specifies the end position of the scale line*/
	CHART_API virtual void SetEndPos(CPoint ptEnd);
	
	//@cmember
	/* Specifies the label step resolution (defaults to 0.1)*/
	CHART_API virtual void SetResolution(double dRes);
	
	//@cmember
	/*  Sets the maximum value for this scale*/
	CHART_API virtual void SetMaxValue(double dMaxValue);
	
	//@cmember
	/* 	Sets the minimum value for this scale*/
	CHART_API virtual void SetMinValue(double dMinValue);
	
	//@cmember
	/* Initializes a printf-style format string for the labels*/
	CHART_API virtual void SetFormatString(LPCTSTR strFormatString);
	
	//@cmember
	/* Sets the m_bLabelSide semaphore*/
	CHART_API virtual void SetLabelSide(BOOL bRight);
	
	//@cmember
	/*  Specifies ascending label order*/
	CHART_API virtual void SetAscending();
	
	//@cmember
	/* Specifies descending label order*/
	CHART_API virtual void SetDescending();
	
	//@cmember
	/* Interrogates the m_ptStart member*/
	CHART_API virtual CPoint GetStartPos();
	
	//@cmember
	/* Interrogates the m_ptEnd member*/
	CHART_API virtual CPoint GetEndPos();
	
	//@cmember
	/* Interrogates the m_dResolution member*/
	CHART_API virtual double GetResolution();
	
	//@cmember
	/* Interrogates the m_dMaxValue member*/
	CHART_API virtual double GetMaxValue();
	
	//@cmember
	/* Interrogates the m_dMinValue member*/
	CHART_API virtual double GetMinValue();
	
	//@cmember
	/* Interrogates the m_strFormatString member*/
	CHART_API virtual CString & GetFormatString();
	
	//@cmember
	/* Interrogates the m_bLabelSide member*/
	CHART_API virtual BOOL GetLabelSide();
	
	//@cmember
	/* Creates the label list from available information*/
	CHART_API virtual void CreateLabels();

	//@cmember
	/* Sets all labels perpendicular to the line between the start and end points*/
	CHART_API virtual void SetRTAngles();

	CHART_API virtual void TrimLabel(CString& strLabel);

	// XML Formatter for SRGDecimalScale
	friend class SRGDecimalScaleFTR;
};

//@doc SRGLogScale
//@mfunc  | SRGLogScale | SRGLogScale | Basic constructor

// adinsert

//@class SRGLogScale manages the logarithmic equivalent of the decimal scale
class  SRGLogScale : public SRGDecimalScale
{
public:
	//@cmember
	/* Constructor*/
	inline SRGLogScale(){m_bCheckOverlaps=TRUE;}

	CHART_DECLARE_SERIAL(SRGLogScale);

	//@cmember
	/* Constructor with parameters*/
	CHART_API SRGLogScale(CPoint ptStart, CPoint ptEnd, double dMinValue, double dMaxValue, double dResolution,CString & strFormatString);

	//@cmember
	/* The only significant change from the ancestor class*/
	CHART_API virtual void CreateLabels();

	// XML Formatter for SRGLogScale
	friend class SRGLogScaleFTR;
};

//@doc SRGDateScale

//adinsert

#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE != 201)
//@class SRGDateScale is derived from and similar in operation to the SRGDecimalScale. 
//This axis labeling scale provides date and time support via the COLEDateTime functions. 
//The maximum and minimum scales can be set to decimal values which 
//correspond to the new date and time standards, and sensible annotations will be derived from them.
class SRGDateScale : public SRGDecimalScale
{
public:
	CHART_API CString TimeFormat(LPCTSTR strFormatString,COleDateTime dt);

	//@cmember
	/* Constructor*/
	CHART_API SRGDateScale();
	
	CHART_DECLARE_SERIAL(SRGDateScale);
	
	//@cmember
	/* Builds the label list*/
	CHART_API virtual void CreateLabels();

//Implementation

	//@cmember
	/* Sets the maximum scale value as a COleDateTime object*/
	CHART_API virtual void SetMaxValue(COleDateTime t);
	//@cmember
	/* Sets the minimum scale value as a COleDateTime object*/
	CHART_API virtual void SetMinValue(COleDateTime t);

	//@cmember
	/* Sets the resolution value as a COleDateTimeSpan object*/
	CHART_API virtual void SetResolution(COleDateTimeSpan s);

	// XML Formatter for SRGDateScale
	friend class SRGDateScaleFTR;
};
#endif

//@doc SRGIndexScale

//@mfunc BOOL  | SRGIndexScale | GetNodeAdjust | Returns the node adjust flag 

//@mfunc void  | SRGIndexScale | SetNodeAdjust | Sets the node adjust flag
//@parm BOOL  | b | TRUE to set node adjustment on
//@rem If node adjustment is on, the start and end points of the label block should be placed 
//at the corners of the chart axis area -- as for line charts.<nl>
//If node adjustment is off, the nodes will be placed in the correct positions for bar charts.

//@mdata BOOL  | SRGIndexScale | m_bNodeAdjust | Node adjustment flag

//adinsert

//@doc SRGIndexScale
//@class Creates and displays a label-block style chart scale from the index annotations of an SRGraph object
class SRGIndexScale : public SRGDecimalScale
{
public:
	//@cmember
	/* Serialization*/
	CHART_API virtual void Serialize(CArchive &ar);
	//@cmember
	/* Destructor*/
	CHART_API virtual  ~SRGIndexScale();
	//@cmember
	/* Constructor*/
	CHART_API SRGIndexScale();

	//@cmember
	/* Creates the index labels*/
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Returns the node adjustment flag*/
	CHART_API virtual BOOL GetNodeAdjust();
	//@cmember
	/* Sets the node adjustment flag*/
	CHART_API virtual void SetNodeAdjust(BOOL b=TRUE);

	CHART_DECLARE_SERIAL(SRGIndexScale);

protected:
	//@cmember
	/* Node adjustment flag*/
	BOOL m_bNodeAdjust;

	// XML Formatter for SRGIndexScale
	friend class SRGIndexScaleFTR;
};



//@doc SRGGroupScale

//@class Creates and displays a label-block style chart scale from the group annotations of an SRGraph object
class SRGGroupScale : public SRGIndexScale
{
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual  ~SRGGroupScale();
	//@cmember
	/* Constructor*/
	CHART_API SRGGroupScale();

	CHART_DECLARE_SERIAL(SRGGroupScale);

	//@cmember
	/* Creates the group labels*/
	CHART_API virtual void CreateLabels();

	// XML Formatter for SRGGroupScale
	friend class SRGGroupScaleFTR;
};

#endif //__SRGDECIMALSCALE__

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

