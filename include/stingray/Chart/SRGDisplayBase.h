///////////////////////////////////////////////////////////////////////////////
// SRGDisplayBase.h
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
//@doc SRGDisplayBase
//@module SRGDisplayBase.h | Class definition file for the SRGDisplayBase class<nl>
//This class is an abstract base class used to facillitate the conversion of OC to a lighter format    
//Written by Bob Powell (www.roguewave.com)

#if !defined(_SRGDISPLAYBASE_H_INCLUDED_)
#define _SRGDISPLAYBASE_H_INCLUDED_

#include "SRGraphTitle.h"
#include "SRGDat.h"	// Added by ClassView
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

/////////////////////////////
// AutoDuck tag block for SRGDisplayBase 

//@doc SRGDisplayBase
//@mdata CScale  | SRGDisplayBase | m_oZoomStateY | The Y scale zoom state.

//@doc SRGDisplayBase
//@mdata CScale  | SRGDisplayBase | m_oZoomStateX | The X scale zoom state.

//@doc SRGDisplayBase
//@mfunc virtual void  | SRGDisplayBase | SetZoomStateY | Sets the Y scale zoom state. This keeps a record of the zoom level between draw cycles.
//@parm CScale  | v | The zoom level to retain.

//@doc SRGDisplayBase
//@mfunc virtual CScale  | SRGDisplayBase | GetZoomStateY | Returns the current Y scale zoom state.

//@doc SRGDisplayBase
//@mfunc virtual void  | SRGDisplayBase | SetZoomStateX | Sets the X scale zoom state. This keeps a record of the zoom level between draw cycles.
//@parm CScale  | v | The zoom level to retain.

//@doc SRGDisplayBase
//@mfunc virtual CScale  | SRGDisplayBase | GetZoomStateX | Returns the current X scale zoom state. 

//@mdata double | SRGDisplayBase | m_dMaxRangeY |  Maximum range which this display will show on its axes
//@rem If this range is exceeded by the data, there is no overflow procedure. It is the responsibility of
//the application to keep data within the correct range when these limits are used.
//@see <mf SRGDisplayBase::SetMaxRange>  <mf SRGDisplayBase::GetMaxRange>

//@mdata double | SRGDisplayBase | m_dMaxScaleY | Used internally to calculate the scaling factor for data<nl>
//This variable is usually set by taking the maximum range of data and multiplying by 1.1. 
//This ensures a maximum data scale which is always a little bit larger than the data in the graph. 
//Axes, labels and, scales are all re-calculated using this number to keep data from 
//overflowing the display area.

//@mdata CRect | SRGDisplayBase | m_LabelRectX | Rectangle used during the drawing of X labels

//@mdata CRect | SRGDisplayBase | m_LabelRectY | Rectangle used during the drawing of Y labels

//@mdata CRect | SRGDisplayBase | m_DisplayRect | Rectangle which contains the usable data display area 
//@rem The rectangle starts out each draw cycle with the whole component area. 
//As items are drawn, this rectangle is reduced in size so that subsequent items know how much 
//area is left to work with. For example, the component reduces the area to account 
//for its borders. The labels then reduce the area to account for their widths and heights 
//leaving the axis and data to be drawn in the area that is left.

//@mdata CRect | SRGDisplayBase | m_DrawnRect | Record of the previous final m_DisplayRect value
//@see <md SRGDisplayBase::m_DisplayRect>

//@mdata BOOL | SRGDisplayBase | m_bDisplayDrawn | Set to TRUE when the display has been drawn at least once

//@mdata CPtrList | SRGDisplayBase | m_XTickList | The X, Y and Z tick lists are optionally 
//built by the label system to allow accurate positioning of the tick marks and grid lines.
//@rem The tick list contains a simple CPoint list. Each point is derived directly from the 
//position of a label used on the graph's axes. These positions are normally only used to 
//position the ticks or grid lines vertically or horizontally.

//@mdata SRGraphLabelBlock * | SRGDisplayBase | m_ptrXLabels | The X, Y and Z label pointers 
//are placeholders for any one of the SRGraphLabelBlock (or derived) objects. 
//The axis drawing system will normally assign a semi-permanent label block 
//(<c SRGraphLabelBlock>) or decimal scale (<c SRGDecimalScale>) to one of these pointers 
//for the duration of its existence. Keeping the same label block and modifying it requires 
//far less time than constantly creating and destroying large, complex objects on the stack.

//@mdata SRGraphLabelBlock *  | SRGDisplayBase | m_ptrYLabels | Pointer to the Y label scale
//@see <md SRGDisplayBase::m_ptrXLabels>

//@mdata SRGraphLabelBlock *  | SRGDisplayBase | m_ptrZLabels | Pointer to the Z label scale
//@see <md SRGDisplayBase::m_ptrXLabels>

//@mdata BOOL  | SRGDisplayBase | m_bPrepared | TRUE if the display has been prepared for drawing

//@mdata BOOL  | SRGDisplayBase | m_bUnZoomY | TRUE if the Y axis has been zoomed (only used for scatter graphs)

//@mdata BOOL  | SRGDisplayBase | m_bUnZoomX | TRUE if the X axis has been zoomed (only used for scatter graphs)

//@mdata double  | SRGDisplayBase | m_dMaxRangeX | Maximum allowed X value 
//@mdata double  | SRGDisplayBase | m_dMinRangeX | Minimum allowed X value 

//@mdata double  | SRGDisplayBase | m_dMinRangeY | Minimum allowed Y value 

//@mdata double  | SRGDisplayBase | m_dMaxScaleX | Minimum usable X scale 

//@mdata CPtrList  | SRGDisplayBase | m_YTickList | Pointer to the list of CPoint objects that will be updated by the Y labels

//@mdata CPtrList  | SRGDisplayBase | m_ZTickList | Pointer to the list of CPoint objects that will be updated by the Z labels

//@mdata CScale  | SRGDisplayBase | m_ZoomScaleY | Scale used when zooming the Y axis for scatter charts

//@mdata CScale  | SRGDisplayBase | m_ZoomScaleX | Scale used when zooming the X axis for scatter charts

//@mfunc void  | SRGDisplayBase | SetptrXLabels | Initializes the X labels with an externally created label class 
//@parm SRGraphLabelBlock *  | v | Pointer to label block

//@mfunc SRGraphLabelBlock * | SRGDisplayBase | GetptrXLabels | Retrieves the X labels so that they may be modified 
//@rdesc Pointer to label block

//@mfunc void  | SRGDisplayBase | SetptrYLabels | Initializes the Y labels with an externally created label class
//@parm SRGraphLabelBlock *  | v | Pointer to label block

//@mfunc SRGraphLabelBlock * |SRGDisplayBase | GetptrYLabels | Retrieves the Y labels so that they may be modified  
//@rdesc Pointer to label block

//@mfunc void  | SRGDisplayBase | SetptrZLabels | Initializes the Z labels with an externally created label class
//@parm SRGraphLabelBlock *  | v | Pointer to label block 

//@mfunc SRGraphLabelBlock * | SRGDisplayBase | GetptrZLabels | Retrieves the Z labels so that they may be modified  
//@rdesc Pointer to label block

//@mfunc virtual void  | SRGDisplayBase | CleanZoomScaleX | Zeroes the X data zooming scale -- currently only used for scattergraphs

//@mfunc virtual void  | SRGDisplayBase | CleanZoomScaleY | Zeroes the Y data zooming scale -- currently only used for scattergraphs

//@mfunc virtual CRect  | SRGDisplayBase | GetDisplayRect | Returns the display rectangle

//@mfunc virtual double  | SRGDisplayBase | GetMaxScaleY | Returns the m_dMaxScaleY member

//@mfunc virtual double  | SRGDisplayBase | GetMaxScaleX | Returns the m_dMaxScaleX member

//@mfunc virtual CPtrList * | SRGDisplayBase | GetXTickList | Returns the X tick list

//@mfunc virtual CPtrList * | SRGDisplayBase | GetYTickList | Returns the Y tick list

//@mfunc virtual CPtrList * | SRGDisplayBase | GetZTickList | Returns the Z tick list

//@mfunc virtual CScale  | SRGDisplayBase | GetZoomScaleX | Returns the X data zooming scale -- currently only used for scattergraphs

//@mfunc virtual CScale  | SRGDisplayBase | GetZoomScaleY | Returns the Y data zooming scale -- currently only used for scattergraphs

//@mfunc virtual void  | SRGDisplayBase | SetZoomScaleX | Sets the X data zooming scale -- currently only used for scattergraphs
//@parm CScale  | scale | CScale object containing the desired limits

//@mfunc virtual void  | SRGDisplayBase | SetZoomScaleY | Sets the Y data zooming scale -- currently only used for scattergraphs
//@parm CScale  | scale | CScale object containing the desired limits

//@mfunc virtual void  | SRGDisplayBase | SetUnZoomY | Initializes the Y unzoom semaphore
//@parm BOOL  | v | TRUE if Y is zoomed 

//@mfunc virtual BOOL  | SRGDisplayBase | GetUnZoomY | Retrieves the Y unzoom semaphore

//@mfunc virtual void  | SRGDisplayBase | SetUnZoomX | Initializes the X unzoom semaphore
//@parm BOOL  | v | TRUE if X is zoomed

//@mfunc virtual BOOL  | SRGDisplayBase | GetUnZoomX | Retrieves the X unzoom semaphore

//@mdata double  | SRGDisplayBase | m_dXRes | Interval between axis labels (resolution) for horizontal axis
//@mdata double  | SRGDisplayBase | m_dYRes | Interval between axis labels (resolution) for vertical axis
//@mdata double  | SRGDisplayBase | m_dZRes | Interval between axis labels (resolution) for depth axis [not currently used]

//@mdata CString  | SRGDisplayBase | m_sXFormat | Format string for horizontal axis
//@mdata CString  | SRGDisplayBase | m_sYFormat | Format string for vertical axis
//@mdata CString  | SRGDisplayBase | m_sZFormat | Format string for depth axis  [not currently used]

//@mfunc void | SRGDisplayBase | SetResolutionX | Sets the interval between axis labels (resolution) for the horizontal axis <nl>
//Can be used to specify how axis labels are chosen if the automatic selection is not satisfactory. 
//@rdesc  void 
//@parm double | dRes | For axes with a decimal, date, or log scale -- the desired numeric difference between labeled values. <nl>
//For axes with an index or group scale -- the step between labels (e.g. 2 to use the annotations from every other data object).
//@rem Does not apply to compound displays.

//@mfunc void | SRGDisplayBase | SetResolutionY | Sets the interval between axis labels (resolution) for the vertical axis <nl>
//Can be used to specify how axis labels are chosen if the automatic selection is not satisfactory. 
//@rdesc  void 
//@parm double | dRes | For axes with a decimal, date, or log scale -- the desired numeric difference between labeled values. <nl>
//For axes with an index or group scale -- the step between labels (e.g. 2 to use the annotations from every other data object).
//@rem Does not apply to compound displays.

//@mfunc void | SRGDisplayBase | SetResolutionZ | Sets the interval between axis labels (resolution) for the depth axis <nl>
//Can be used to specify how axis labels are chosen if the automatic selection is not satisfactory. <nl>
//[not currently used]
//@rdesc  void 
//@parm double | dRes | (z axis is always an index scale) The step between labels (e.g. 2 to use the annotations from every other data object).
//@rem Does not apply to compound displays.

//@mfunc double | SRGDisplayBase | GetResolutionX | Retrieves the interval between axis labels (resolution) of the horizontal axis <nl>
//if it was previously set by SetResolutionX() -- otherwise 0
//@rdesc The numeric interval between labels or annotation step depending on the type of axis scale.

//@mfunc double | SRGDisplayBase | GetResolutionY | Retrieves the interval between axis labels (resolution) of the horizontal axis <nl>
//if it was previously set by SetResolutionX() -- otherwise 0 
//@rdesc The numeric interval between labels or annotation step depending on the type of axis scale.

//@mfunc double | SRGDisplayBase | GetResolutionZ | Retrieves the interval between axis labels (resolution) of the horizontal axis <nl>
//if it was previously set by SetResolutionX() -- otherwise 0 <nl>
//[not currently used]
//@rdesc Step used to select annotations from the data array.

//@mfunc void | SRGDisplayBase | SetFormatX | Sets the format string for the horizontal axis
//@rdesc  void 
//@parm LPCTSTR | sFormat | Format string that may be used with CString.Format() -- COleDateTime.Format() for date scales.
//@rem Applies only to numeric scales.  Does not apply to compound displays.

//@mfunc void | SRGDisplayBase | SetFormatY | Sets the format string for the vertical axis
//@rdesc  void 
//@parm LPCTSTR | sFormat | Format string that may be used with CString.Format() -- COleDateTime.Format() for date scales.
//@rem Applies only to numeric scales.  Does not apply to compound displays.

//@mfunc void | SRGDisplayBase | SetFormatZ | Sets the format string for the depth axis <nl>
//[not currently used]
//@rdesc  void 
//@parm LPCTSTR | sFormat | Format string that may be used with CString.Format() -- COleDateTime.Format() for date scales.
//@rem Applies only to numeric scales.  Does not apply to compound displays.

//@mfunc CString& | SRGDisplayBase | GetFormatX | Retrieves the format string for the horizontal axis <nl>
//if previously set by SetFormatX()
//@rdesc  CString&
//@rem Applies only to numeric scales.  Does not apply to compound displays.

//@mfunc CString& | SRGDisplayBase | GetFormatY | Retrieves the format string for the vertical axis <nl>
//if previously set by SetFormatY() <nl>
//[not currently used]//@rdesc  CString&
//@rem Applies only to numeric scales.  Does not apply to compound displays.

//@mfunc CString& | SRGDisplayBase | GetFormatZ | Retrieves the format string for the depth axis <nl>
//if previously set by SetFormatZ()
//@rdesc  CString&
//@rem Applies only to numeric scales.  Does not apply to compound displays.

// adinsert AutoDuck insertion point for SRGDisplayBase 
//$head Component classes
//$level 1

//@doc SRGDisplayBase 
//@class Abstract base class for graph display components including <c SRGraphDisplay> -- inherits font abilities from SRGraphTitle
//@base public | SRGraphTitle
class SRGDisplayBase : public SRGraphTitle  
{

	CHART_DECLARE_DYNAMIC(SRGDisplayBase);

public:
	//@cmember
	/* Constructor*/
	CHART_API SRGDisplayBase();

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGDisplayBase();

//@access Protected data members
protected:
	//@cmember
	/* Y scale to be used when data is zoomed up -- used only on XY Scatter graphs for the moment*/
	CScale m_ZoomScaleY;
	//@cmember
	/* X scale to be used when data is zoomed up -- used only on XY Scatter graphs for the moment*/
	CScale m_ZoomScaleX;
	//@cmember
	/* Minimum Y numeric value allowed for this graph*/
	double m_dMinRangeY;
	//@cmember
	/* Maximum Y numeric value allowed for this graph*/
	double m_dMaxRangeY;
	//@cmember
	/* Maximum Y scale of the values in this graph display*/
	double m_dMaxScaleY;
	//@cmember
	/* Minimum X numeric value allowed for this graph*/
	double m_dMinRangeX;
	//@cmember
	/* Maximum X numeric value allowed for this graph*/
	double m_dMaxRangeX;
	//@cmember
	/* Maximum X scale of the values in this graph display*/
	double m_dMaxScaleX;

	//@cmember
	/* Pointer to a block of labels used to annotate the X axis*/
	SRGraphLabelBlock * m_ptrXLabels;
	//@cmember
	/* Pointer to a block of labels used to annotate the Y axis*/
	SRGraphLabelBlock * m_ptrYLabels;
	//@cmember
	/* Pointer to a block of labels used to annotate the Z axis*/
	SRGraphLabelBlock * m_ptrZLabels;

	//@cmember
	/* List of points which have been provided by the X label block -- used to position tick marks and grid lines*/
	CPtrList m_YTickList;
	//@cmember
	/* List of points which have been provided by the Y label block -- used to position tick marks and grid lines*/
	CPtrList m_XTickList;
	//@cmember
	/* List of points which have been provided by the Z label block -- used to position tick marks and grid lines*/
	CPtrList m_ZTickList;

	//@cmember
	/* Rectangle enclosing the X labels*/
	CRect m_LabelRectX;
	//@cmember
	/* Rectangle enclosing the Y labels*/
	CRect m_LabelRectY;
	//@cmember
	/* Display rectangle -- initially the whole component display area, resized according to room taken up by labels, etc.*/
	CRect m_DisplayRect;
	//@cmember
	/* Previously drawn rectangle*/
	CRect m_DrawnRect;

	//@cmember
	/* Semaphore - TRUE if the display has been drawn*/
	BOOL m_bDisplayDrawn;

	//@cmember
	/* Flag signifying that the chart has been prepared for this draw cycle*/
	BOOL m_bPrepared;

	//@cmember
	/* Flag signifying that the X axis is zoomed*/
	BOOL m_bUnZoomY;

	//@cmember
	/* Flag signifying that the Y axis is zoomed*/
	BOOL m_bUnZoomX;

	//@cmember
	/* Interval between axis labels (resolution) for horizontal axis*/
	double m_dXRes;
	//@cmember
	/* Interval between axis labels (resolution) for vertical axis*/
	double m_dYRes;
	//@cmember
	/* Interval between axis labels (resolution) for depth axis*/
	double m_dZRes;

	//@cmember
	/* Format string for horizontal axis*/
	CString m_sXFormat;
	//@cmember
	/* Format string for vertical axis*/
	CString m_sYFormat;
	//@cmember
	/* Format string for depth axis*/
	CString m_sZFormat;

//@access Public member functions
public:

	//@cmember
	/* Initializes the Y unzoom semaphore*/
	CHART_API virtual void SetUnZoomY(BOOL v);
	//@cmember
	/* Retrieves the Y unzoom semaphore*/
	CHART_API virtual BOOL GetUnZoomY();
	//@cmember
	/* Initializes the X unzoom semaphore*/
	CHART_API virtual void SetUnZoomX(BOOL v);
	//@cmember
	/* Retrieves the X unzoom semaphore*/
	CHART_API virtual BOOL GetUnZoomX();

	//@cmember
	/* Calculates font sizes for the display class*/
	CHART_API virtual int CalcFontAutoSize();

	//@cmember
	/* Prepares the chart*/
	CHART_API virtual void Prepare();

	//@cmember
	/* Initializes the X labels with an externally created label class*/
	CHART_API virtual void SetptrXLabels(SRGraphLabelBlock * v);

	//@cmember
	/* Retrieves the X labels so that they may be modified*/
	CHART_API virtual SRGraphLabelBlock * GetptrXLabels();

	//@cmember
	/* Initializes the Y labels with an externally created label class*/
	CHART_API virtual void SetptrYLabels(SRGraphLabelBlock * v);

	//@cmember
	/* Retrieves the Y labels so that they may be modified*/
	CHART_API virtual SRGraphLabelBlock * GetptrYLabels();

	//@cmember
	/* Initializes the Z labels with an externally created label class*/
	CHART_API virtual void SetptrZLabels(SRGraphLabelBlock * v);

	//@cmember
	/* Retrieves the Z labels so that they may be modified*/
	CHART_API virtual SRGraphLabelBlock * GetptrZLabels();

	//@cmember
	/* Stores or retrieves this object*/
	CHART_API virtual void Serialize(CArchive& ar);

	//@cmember
	/* Returns the m_dMaxScaleY member*/
	CHART_API virtual double GetMaxScaleY();

	//@cmember
	/* Returns the m_dMaxScaleX member*/
	CHART_API virtual double GetMaxScaleX();

	//@cmember
	/* Refreshes the display after a change is made to the graph type after its first draw cycle*/
	CHART_API virtual void Refresh();

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Reads a single line from the graph template */
	CHART_API virtual int ReadTemplateLine(LPCTSTR line);

	//@cmember
	/* Writes the name of this component to a file*/
	CHART_API virtual void WriteName(CStdioFile* file);

	//@cmember
	/* Writes component parameters for Display components to a file*/
	CHART_API virtual void WriteSpecificParameters(CStdioFile* file);
#endif // _OC_DONT_SUPPORT_TEXT_TEMPLATE

	//@cmember
	/* Sets the X data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual void SetZoomScaleX(CScale scale);

	//@cmember
	/* Sets the Y data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual void SetZoomScaleY(CScale scale);

	//@cmember
	/* Gets the X data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual CScale GetZoomScaleX();

	//@cmember
	/* Gets the Y data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual CScale GetZoomScaleY();

	//@cmember
	/* Zeroes the X data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual void CleanZoomScaleX();

	//@cmember
	/* Zeroes the Y data zooming scale -- currently only used for scattergraphs*/
	CHART_API virtual void CleanZoomScaleY();

	//@cmember
	/* Returns the display rectangle*/
	CHART_API virtual CRect GetDisplayRect();

	//@cmember
	/* Returns the minimum numeric value allowed for this graph's Y axis*/
 	CHART_API virtual double GetMinRangeY();

	//@cmember
	/* Retrieves the maximum numeric value allowed for this graph*/
	CHART_API virtual double GetMaxRangeY();

	//@cmember
	/* Sets the minimum numeric value allowed for this graph*/
	CHART_API virtual void SetMinRangeY(double dValue);

	//@cmember
	/* Sets the maximum numeric value allowed for this graph*/
	CHART_API virtual void SetMaxRangeY(double dValue);

	//@cmember
	/* Retrieves the minimum numeric X value allowed for this graph*/
	CHART_API virtual double GetMinRangeX();

	//@cmember
	/* Retrieves the maximum numeric X value allowed for this graph*/
	CHART_API virtual double GetMaxRangeX();

	//@cmember
	/* Sets the minimum numeric Y value allowed for this graph*/
	CHART_API virtual void SetMinRangeX(double dValue);

	//@cmember
	/* Sets the maximum numeric Y value allowed for this graph*/
	CHART_API virtual void SetMaxRangeX(double dValue);

	//@cmember
	/* Allows initialization and locking of the display rectangle*/
	CHART_API virtual void SetDisplayRect(CRect r,BOOL lock=FALSE);

	//@cmember
	/* Initializes the Y scale zoom state */
	CHART_API virtual void SetZoomStateY(CScale v);
	//@cmember
	/* Returns the Y scale zoom state */
	CHART_API virtual CScale GetZoomStateY();
	//@cmember
	/* Initializes the X scale zoom state */
	CHART_API virtual void SetZoomStateX(CScale v);
	//@cmember
	/* Returns the X scale zoom state */
	CHART_API virtual CScale GetZoomStateX();

	//@cmember
	/* Sets the interval between axis labels (resolution) of the horizontal axis*/
	CHART_API void SetResolutionX(double dRes);
	//@cmember
	/* Sets the interval between axis labels (resolution) of the vertical axis*/
	CHART_API void SetResolutionY(double dRes);
	//@cmember
	/* Sets the interval between axis labels (resolution) of the depth axis*/
	CHART_API void SetResolutionZ(double dRes);
	//@cmember
	/* Retrieves the interval between axis labels (resolution) of the horizontal axis if previously set by SetResolutionX()*/
	CHART_API double GetResolutionX();
	//@cmember
	/* Retrieves the interval between axis labels (resolution) of the vertical axis if previously set by SetResolutionX()*/
	CHART_API double GetResolutionY();
	//@cmember
	/* Retrieves the interval between axis labels (resolution) of the depth axis if previously set by SetResolutionX()*/
	CHART_API double GetResolutionZ();

	//@cmember
	/* Sets the format string for the horizontal axis*/
	CHART_API void SetFormatX(LPCTSTR sFormat);
	//@cmember
	/* Sets the format string for the vertical axis*/
	CHART_API void SetFormatY(LPCTSTR sFormat);
	//@cmember
	/* Sets the format string for the depth axis*/
	CHART_API void SetFormatZ(LPCTSTR sFormat);
	//@cmember
	/* Retrieves the format string for the horizontal axis if previously set by SetFormatX()*/
	CHART_API CString& GetFormatX();
	//@cmember
	/* Retrieves the format string for the vertical axis if previously set by SetFormatY()*/
	CHART_API CString& GetFormatY();
	//@cmember
	/* Retrieves the format string for the depth axis if previously set by SetFormatZ()*/
	CHART_API CString& GetFormatZ();
	
//@access Protected member functions
protected:
	//@cmember
	/* The Y scale zoom state. */
	CScale m_oZoomStateY;
	//@cmember
	/* The Y scale zoom state. */
	CScale m_oZoomStateX;
	//@cmember
	/* Displays the data representation -- called from DrawForeground*/
	CHART_API virtual void DrawData();

	//@cmember
	/* Displays the axes -- called from DrawForeground*/
	CHART_API virtual void DrawAxis();

	//@cmember
	/* Displays the labels -- called from DrawForeground*/
	CHART_API virtual void DrawLabels();

	//@cmember
	/* Displays the graph data*/
	CHART_API virtual void DrawForeground();

	//@cmember
	/* Displays a warning sign for null graphs*/
	CHART_API virtual void DrawEmptyGraph();

	//@cmember
	/* Returns the X tick list*/
	CHART_API virtual CPtrList * GetXTickList();
	//@cmember
	/* Returns the Y tick list*/
	CHART_API virtual CPtrList * GetYTickList();
	//@cmember
	/* Returns the Z tick list*/
	CHART_API virtual CPtrList * GetZTickList();

	//@cmember
	/* Empties a tick list and deletes its contents*/
	CHART_API virtual void KillTickList(CPtrList * pTickList);
	
	//@cmember
	/* Returns 1.1 -- override to return your own custom Y scaling adjustment*/
	CHART_API virtual double GetYScaleAdjustment();
	//@cmember
	/* Returns 1.1 -- override to return your own custom X scaling adjustment*/
	CHART_API virtual double GetXScaleAdjustment();

	//@cmember
	/* Generates a list of numbers which are used to annotate the Y axis of graphs (no longer used, maintained for compatibility)*/
	CHART_API virtual void CreateNumberList(double multiplier,CStringList *list);

	//@cmember
	/* Returns the step required to generate numbers for a graph (superceded by SRGDecimalScale class)*/
	CHART_API virtual double GetIdealScale();
	//@cmember
	/* Allows custom adjustment of safety scaling*/
	CHART_API virtual void AdjustScale();

	//@cmember
	/* Adjusts data range so that labels display "nice" numbers*/
	CHART_API virtual void FindLimits(CScale* pScale, double dScaleAdjust);
	//@cmember
	/* Expands data range to give "nice" limits for log axis*/
	CHART_API virtual void FindLogLimits(CScale* pScale, BOOL bFullDecade=TRUE);
	//@cmember
	/* Adjusts the data range to find sensible limits for date scales */
	CHART_API virtual void FindDateLimits(CScale* pScale, double dScaleAdjust);


// Custom charts
	//@cmember
	/* (Empty) Override to set index and group steps for your custom graph type*/
	CHART_API virtual void SetCustomSteps();
	//@cmember
	/* (Empty) Virtual function to allow extension of the preparation process*/
	CHART_API virtual void PrepareCustom();
	//@cmember
	/* (Empty) Override to draw custom axes*/
	CHART_API virtual void DrawCustomAxis();
	//@cmember
	/* (Empty) Override to draw custom labels*/
	CHART_API virtual void DrawCustomLabels();
	//@cmember
	/* (Empty) Override to draw custom data*/
	CHART_API virtual void DrawCustomData();

	//@cmember,mfunc
	/* (Pure Virtual) Prepares the display component for drawing*/
	CHART_API virtual void PrepareDisplay() ;
	//@cmember,mfunc
	/* (Pure Virtual) Calculates scale ranges for most simple graph types*/
	CHART_API virtual void PrepareYScale() ;

// Classic axes
	//@cmember,mfunc
	/* (Pure Virtual) Called to draw standard X,Y labels*/
	CHART_API virtual void DrawClassicLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Called to draw standard X,Y axes*/
	CHART_API virtual void DrawClassicAxis() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws the pseudo 3D axis*/
	CHART_API virtual void DrawIsoClassicAxis() ;
	//@cmember,mfunc
	/* (Pure Virtual) Called to draw labels for the YX graphs*/
	CHART_API virtual void DrawYXLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws the YX axis for use with horizontal bar charts*/
	CHART_API virtual void DrawYXAxis() ;

// Stage axes
	//@cmember,mfunc
	/* (Pure Virtual) Calculates the size of a stage or platform axis*/
	CHART_API virtual int StageCalcSize(CRect *BackPlane);
	//@cmember,mfunc
	/* (Pure Virtual) Draws labels and annotations on the stage or platform graphs*/
	CHART_API virtual void DrawStageLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws the "stage" type axis*/
	CHART_API virtual void DrawStageAxis() ;

//Pie charts
	//@cmember,mfunc
	/* (Pure Virtual) Draws pie chart labels*/
	CHART_API virtual void DrawPieLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws pie chart data*/
	CHART_API virtual void DrawPieData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws the 3D pie chart*/
	CHART_API virtual void DrawIsoPieData() ;

// Bar charts
	//@cmember,mfunc
	/* (Pure Virtual) Draws vertical bar chart data*/
	CHART_API virtual void DrawVBarData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws horizontal bar data*/
	CHART_API virtual void DrawHBarData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws vertical stacked bars*/
	CHART_API virtual void DrawStackVBarData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws horizontal stacked bars*/
	CHART_API virtual void DrawStackHBarData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Prepares displays for the drawing of Manhattan type graphs*/
	CHART_API virtual void PrepareIsoBar() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws "Manhattan" bars*/
	CHART_API virtual void DrawIsoBarData() ;


// Polar charts
	//@cmember,mfunc
	/* (Pure Virtual) Prepares the display for drawing polar data*/
	CHART_API virtual void PreparePolar() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws polar chart labels*/
	CHART_API virtual void DrawPolarLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws polar chart axes*/
	CHART_API virtual void DrawPolarAxis() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws polar chart data*/
	CHART_API virtual void DrawPolarData() ;

// Strata charts
	//@cmember,mfunc
	/* (Pure Virtual) Pre-display preparation for strata graphs*/
	CHART_API virtual void PrepareStrata() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws strata graphs*/
	CHART_API virtual void DrawStrataData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw a strata hbar label with the group header as the label text of each bar*/
	CHART_API virtual void DrawStrataHBarGLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw a strata vbar label with the group header as the label text of each bar*/
	CHART_API virtual void DrawStrataVBarGLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw a strata hbar with each group on one bar*/
	CHART_API virtual void DrawStrataHBarGData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw a strata vbar with each group on one bar*/
	CHART_API virtual void DrawStrataVBarGData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Do some pre-initialization for the strata bar( one group/ per bar )*/
	CHART_API virtual void PrepareStrataBarG() ;
	//@cmember,mfunc
	/* (Pure Virtual) Do some pre-initialization for the strata bar( one index/per bar )*/
	CHART_API virtual void PrepareStrataBar() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw strata hbar(data with the same index of different group on the same bar)*/
	CHART_API virtual void DrawStrataHBarData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draw strata vbar(data with the same index of different group on the same bar)*/
	CHART_API virtual void DrawStrataVBarData() ;

// Gantt chart
	//@cmember,mfunc
	/* (Pure Virtual) Draws Gantt labels*/
	CHART_API virtual void DrawGanttLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws Gantt data*/
	CHART_API virtual void DrawGanttData() ;

// Web chart
	//@cmember,mfunc
	/* (Pure Virtual) Draws Web char data*/
	CHART_API virtual void DrawWebData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws Web chart labels*/
	CHART_API virtual void DrawWebLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws Web chart axes*/
	CHART_API virtual void DrawWebAxis() ;

// Scatter charts
	//@cmember,mfunc
	/* (Pure Virtual) Calculates X,Y, and marker size scale information for bubble graphs*/
	CHART_API virtual void PrepareBubble() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws bubble chart data*/
	CHART_API virtual void DrawBubbleData() ;

	//@cmember,mfunc
	/* (Pure Virtual) prepares scales for the display of vector charts */
	CHART_API virtual void PrepareVector() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws vector data */
	CHART_API virtual void DrawVectorData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Calculates X and Y scale information for scatter graphs*/
	CHART_API virtual void PrepareScatter() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws X,Y scatter data*/
	CHART_API virtual void DrawScatterData() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws X,Y scatter labels*/
	CHART_API virtual void DrawScatterLabels() ;
	//@cmember,mfunc
	/* (Pure Virtual) Draws X,Y scatter axes */
	CHART_API virtual void DrawScatterAxis() ;

// Various charts
	//@cmember,mfunc
	/* (Pure Virtual) Called to draw a line plot of the data*/
	CHART_API virtual void DrawLineData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Draws the data for the step charts*/
	CHART_API virtual void DrawStepData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Draws candle chart labels*/
	CHART_API virtual void DrawCandleData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Draws area charts*/
	CHART_API virtual void DrawAreaData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Draws the data components of FreeStyle graphs*/
	CHART_API virtual void DrawFreeStyleData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Called to draw stock quote hi-lo-close graphs*/
	CHART_API virtual void DrawStockData() ;

	//@cmember,mfunc
	/* (Pure Virtual) Draws "Rooftop" objects*/
	CHART_API virtual void DrawIsoAreaData() ;

	// XML formatter for SRGraphDisplayBase
	friend class SRGDisplayBaseFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // !defined(_SRGDISPLAYBASE_H_INCLUDED_)

