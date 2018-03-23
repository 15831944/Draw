///////////////////////////////////////////////////////////////////////////////
// SRGTickMarks.h
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
//$head Component classes (Specialized sub components)
//level 2

/////////////////////////////////////////////////////////////
//@doc SRGTickMarks
//@module SRGTickMarks.h | SRGTickMarks header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SRGTickMarks.h: interface for the SRGTickMarks class.
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif


#if !defined(_SRGTICKMARKS_H_INCLUDED_)
#define _SRGTICKMARKS_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGTickMarks 

//@doc SRGTickMarks
//@mfunc void  | SRGTickMarks | SetMinorTickColor | Sets the color of the minor ticks
//@parm COLORREF  | c | RGB color value

//@mfunc COLORREF  | SRGTickMarks | GetMinorTickColor | Returns the minor tick color

//@mfunc void  | SRGTickMarks | SetMajorTickColor | Sets the color of the major ticks
//@parm COLORREF  | c | RGB color

//@mfunc COLORREF  | SRGTickMarks | GetMajorTickColor | Returns the major tick color

//@mfunc void  | SRGTickMarks | SetMajorTickWidth | Sets the width of the major ticks in pixels
//@parm int  | n | Positive integer specifying the width

//@mfunc void  | SRGTickMarks | SetMinorTickWidth | Sets the width of the minor ticks in pixels.
//@parm int  | n | Positive integer specifying the width

//@mfunc int  | SRGTickMarks | GetMinorTickWidth | Returns the minor tick width

//@mfunc int  | SRGTickMarks | GetMajorTickWidth |  Returns the major tick width

//@mfunc void  | SRGTickMarks | SetptrTickPositionList | Initializes the pointer to the tick position list
//@parm CPtrList  * | pList | Pointer to a CPtrList object that contains addresses of a list of CPoint objects that control the tick list

//@mfunc CPtrList * | SRGTickMarks | GetptrTickPositionList | Returns the tick position list pointer

//@mfunc void  | SRGTickMarks | SetTickSide | Sets the side of the line upon which ticks are displayed
//@parm BOOL  | bSide | TRUE = right

//@mfunc BOOL  | SRGTickMarks | GetTickSide | Returns the side of the line upon which ticks are displayed

//@mfunc void  | SRGTickMarks | SetMajorTickSize | Sets the size of the major tick marks in pixels
//@parm int  | nTickSize | Positive integer specifying the length of the tick marks in pixels

//@mfunc int  | SRGTickMarks | GetMajorTickSize | Returns the size of the major tick marks in pixels

//@mfunc void  | SRGTickMarks | SetMinorTickSize | Sets the size of the minor ticks
//@parm double  | d | Ratio of major tick to minor tick sizes (ie. 0.5 makes minor ticks half as long as the major ticks)

//@mfunc double  | SRGTickMarks | GetMinorTickSize | Returns the minor tick size

//@mfunc void  | SRGTickMarks | SetDisplayRect | Sets the display rect
//@parm CRect  | rect |  The final display rectangle which has the start and the end points of the X and Y axis

//@mfunc int  | SRGTickMarks | GetDisplayRect | Returns the final display rect

//@mdata int  | SRGTickMarks | m_nMinorTickWidth | Width in pixels of the minor tick marks

//@mdata int  | SRGTickMarks | m_nMajorTickWidth | Width in pixels of the major tick marks

//@mdata COLORREF  | SRGTickMarks | m_MinorTickColor | RGB color of the minor ticks

//@mdata COLORREF  | SRGTickMarks | m_MajorTickColor | RGB color of the major ticks

//@mdata BOOL  | SRGTickMarks | m_bTickSide | Side of the line upon which ticks are displayed

//@mdata int  | SRGTickMarks | m_nTickSize | Size of the major ticks

//@mdata double  | SRGTickMarks | m_dMinorTickSize | Ratio of minor tick length to major tick length

//@mdata CPtrList *  | SRGTickMarks | m_pTickPositionList | Pointer to the tick position list

//@mdata int  | SRGTickMarks | m_nMinorTickRatio | Number of minor ticks to each major tick

// adinsert AutoDuck insertion point for SRGTickMarks 
//$head Component classes (Specialized sub components)
//$level 2
//@doc SRGTickMarks 
//@class This class manages the major and minor tick marks that may optionally be displayed on the axis of a chart. 
//The positions of the major ticks are defined by a list of CPoint coordinates. 
//Normally this list of CPoint objects is generated by an SRGraphLabelBlock-based class and 
//then passed by pointer to the SRGTickMarks object.<nl>
//Minor tick marks are interspersed between major tick marks at a preset ratio (N:1).<nl>
//Major and minor color, length, and thickness styles are individually adjustable. 
//@base public | SRGraphComponent
class SRGTickMarks : public SRGraphComponent  
{
public:
	//@cmember
	/* Modifies a start and end position so that the label block won't overwrite the tick marks*/
	CHART_API virtual void GetStandoff(CPoint *ptStart, CPoint *ptEnd);
	//@cmember
	/* Offsets a single CPoint by the angle and size of the major tick*/
	CHART_API virtual CPoint OffsetPoint(CPoint ptPos, int nSize,double dAngle);
	//@cmember
	/* Draws this component*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pCWnd);
	//@cmember
	/* Serializes this component*/
	CHART_API virtual void Serialize(CArchive &ar);
	//@cmember
	/* Draws a single tick mark with a given style and position*/
	CHART_API virtual void DrawTick(CPoint ptPos, int nSize, double dAngle,int nStrength=1,COLORREF Color=CXCLR_BLACK);
	//@cmember
	/* Initializes the ratio of minor ticks to major ticks*/
	CHART_API virtual void SetMinorTickRatio(int n);
	//@cmember
	/* Returns the ratio of minor ticks to major ticks*/
	CHART_API virtual int GetMinorTickRatio();
	//@cmember
	/* Constructor*/
	CHART_API SRGTickMarks();

	CHART_DECLARE_SERIAL(SRGTickMarks);
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGTickMarks();
	//@cmember
	/* Sets the color of the minor ticks*/
	CHART_API virtual void SetMinorTickColor(COLORREF c);
	//@cmember
	/* Gets the color of the minor ticks*/
	CHART_API virtual COLORREF GetMinorTickColor();
	//@cmember
	/* Sets the color of the major ticks*/
	CHART_API virtual void SetMajorTickColor(COLORREF c);
	//@cmember
	/* Gets the color of the major ticks*/
	CHART_API virtual COLORREF GetMajorTickColor();
	//@cmember
	/* Sets the width in pixels of the major ticks*/
	CHART_API virtual void SetMajorTickWidth(int n);
	//@cmember
	/* Sets the width in pixels of the minor ticks*/
	CHART_API virtual void SetMinorTickWidth(int n);
	//@cmember
	/* Gets the width in pixels of the major ticks*/
	CHART_API virtual int GetMinorTickWidth();
	//@cmember
	/* Gets the width in pixels of the major tick*/
	CHART_API virtual int GetMajorTickWidth();
	//@cmember
	/* Sets the tick position pointer*/
	CHART_API virtual void SetptrTickPositionList(CPtrList *pList);
	//@cmember
	/* Returns the tick position list address*/
	CHART_API virtual CPtrList *GetptrTickPositionList();
	//@cmember
	/* Sets the side upon which ticks are displayed*/
	CHART_API virtual void SetTickSide(BOOL bSide);
	//@cmember
	/* Returns the side upon which ticks are displayed*/
	CHART_API virtual BOOL GetTickSide();
	//@cmember
	/* Sets the size (length) of the major ticks*/
	CHART_API virtual void SetMajorTickSize(int nTickSize);
	//@cmember
	/* Returns the size (length) of the major ticks*/
	CHART_API virtual int GetMajorTickSize();
	//@cmember
	/* Sets the size of the minor tick as a ratio of the length of the major tick*/
	CHART_API virtual void SetMinorTickSize(double d);
	//@cmember
	/* Returns the size of the minor tick expressed as a ratio to the length of the major tick*/
	CHART_API virtual double GetMinorTickSize();
	//@cmember
	/* Sets the display rect, which has the starting and the end points of the X and the Y axes. */
	CHART_API virtual void SetDisplayRect(CRect rect);
	//@cmember
	/* Returns the display rect */
	CHART_API virtual CRect GetDisplayRect();

protected:
	//@cmember
	/* Overridden to do nothing*/
	CHART_API virtual void DrawShadow();
	//@cmember
	/* Overridden to do nothing*/
	CHART_API virtual void DrawBorder();
	//@cmember
	/* Overridden to do nothing*/
	CHART_API virtual void DrawFill();
	//@cmember
	/* Width in pixels of the minor ticks*/
	int m_nMinorTickWidth;
	//@cmember
	/* Width in pixels of the major ticks*/
	int m_nMajorTickWidth;
	//@cmember
	/* RGB color of the minor ticks*/
	COLORREF m_MinorTickColor;
	//@cmember
	/* RGB color of the major ticks*/
	COLORREF m_MajorTickColor;
	//@cmember
	/* Side (left=0 right=1) upon which the ticks are drawn*/
	BOOL m_bTickSide;
	//@cmember
	/* Size (length) of the major ticks*/
	int m_nTickSize;
	//@cmember
	/* Ratio of the size of the minor ticks to the major ticks*/
	double m_dMinorTickSize;
	//@cmember
	/* Pointer to the CPtrList object that controls the tick list*/
	CPtrList * m_pTickPositionList;

	//@cmember
	/* The final display rect */
	CRect m_DisplayRect;

	//@cmember
	/* Draws the ticks*/
	CHART_API virtual void DrawForeground();
	//@cmember
	/* Number of minor ticks for each major tick (0 or positive integers only)*/
	int m_nMinorTickRatio;

	// XML Formatter for SRGTickMarks
	friend class SRGTickMarksFTR;
};

#endif // !defined(_SRGTICKMARKS_H_INCLUDED_)
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

