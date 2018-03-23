///////////////////////////////////////////////////////////////////////////////
// SRGDat.h
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

/////////////////////////////////////////////////////////////
//@doc SRGDat
//@module SRGDat.h | SRGraphData header file<nl>
//Includes SRGraphAnnotation, SRGraphAnnotationList, <nl>
//SRGraphData, SRGraphDataList, SRGraphDynamicData, <nl>
//SRGraphStyle, and CScale classes
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SRGDat.h: interface of the SRGraphData and related classes
//
/////////////////////////////////////////////////////////////////
#pragma once

//Dll declaration context

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//////////////////////////////////////////////////////////////////////////
// Various helper functions and classes
#ifndef __SCALE__
#define __SCALE__

/////////////////////////////////////////////////////////////
// AutoDuck supplementary help section for CScale

//@doc CScale

//@mfunc  | CScale | CScale | Constructs and zeroes a CScale object
//@see <mf CScale::Zero>

//@mdata double | CScale | m_dMax | Maximum cumulative value 

//@mdata double | CScale | m_dMin | Minimum cumulative value 

//@mdata BOOL | CScale | m_bClean | (Private) TRUE if this CScale object has not accumulated any data

//@mfunc void | CScale | Zero | Resets m_dMax and m_dMin to zero, sets the m_bClean semaphore

//@mfunc double | CScale | Min | Returns the m_dMin (minimum historic value) member
//@rdesc The lowest number ever passed to this object since construction or zeroing
//@see <mf CScale::Zero> <md CScale::m_dMin> <mf CScale::Max>
											
//@mfunc double | CScale | Max | Returns the m_dMax (maximum historic value) member
//@rdesc The highest number ever passed to this object since construction or zeroing
//@see <mf CScale::Zero> <md CScale::m_dMax> <md CScale::Min> 

//@mfunc BOOL | CScale | IsClean | Ascertains whether the object has been used since it was created or zeroed
//@rem A clean CScale holds no minimum or maximum information.

//@mfunc void operator | CScale | += | Addition operator<nl>
//Compares the given number to the current min and max values and 
//updates the limits to include the new value<nl>
//Overloaded to support for addition (+=) of... <nl>
//	 const double <nl>
//	 const float <nl>
//	 const int <nl>
//	 const unsigned int <nl>
//	 const char <nl>
//	 const unsigned char <nl>

//@mfunc void operator | CScale | = | Assignment operator<nl>
//Copies the min and max data from the source object

//adinsert

//$head Utility classes
//$level 1

//@class Collates and returns minimum and maximum values from a set
//@base public | CObject
class CScale : public CObject
{
//@access Public data members
public:
	//@cmember
	/* Returns TRUE if this object has never been used or has been zeroed*/
	CHART_API virtual BOOL IsClean();
	//@cmember
	/* Maximum accumulated value since creation or zeroing*/
	double m_dMax;
	//@cmember
	/* Minimum accumulated value since creation or zeroing*/
	double m_dMin;

//@access Private data members 
private:
	//@cmember
	/* Signifies that this object is empty and has no accumulated min-max values*/
	BOOL m_bClean;

//@access Private member functions
private:
	//@cmember
	/* Adds the value to the accumulated Min-Max values*/
	CHART_API void total(double n);
	
////////////////////////////
// Construction destruction

//@access Public member functions
public:
	//@cmember
	/* Returns the range of values for the logarithmic scaling system*/
	CHART_API virtual double LogRange();
	//@cmember
	/* Constructor -- zeroes the object*/
	inline CScale(){Zero();}
	//@cmember
	/* Assignment constructor*/
	CHART_API CScale(const CScale& s);

	///////////////////////////
// Operations

	//@cmember,mfunc
	/* Use the += operator to add a number to the Min-Max data<nl>*
	Overloaded to provide support for addition (+=) of... <nl>
	 const double <nl>
	 const float <nl>
	 const int <nl>
	 const unsigned int <nl>
	 const char <nl>
	 const unsigned char <nl>*/
	inline void operator +=(const double n){total(n);}
	inline void operator +=(const float n){total((double)n);}
	inline void operator +=(const int n){total((double)n);}
	inline void operator +=(const unsigned int n){total((double)n);}
#ifndef _UNICODE
	inline void operator +=(const char n){total((double)n);}
	inline void operator +=(const unsigned char n){total((double)n);}
#endif
	//@cmember
	/* Assignment operator*/
	inline void operator =(const CScale& s){m_dMax=s.m_dMax; m_dMin=s.m_dMin; m_bClean=s.m_bClean;}
	//@cmember
	/* Zeroes the accumulated Min-Max data*/
	inline void Zero(void){m_bClean=TRUE; m_dMax=m_dMin=0;}
	//@cmember
	/* Returns the Max value*/
	inline double Max(void){return m_dMax;}
	//@cmember
	/* Returns the Min value*/
	inline double Min(void){return m_dMin;}
	//@cmember
	/* Returns range of values*/
	CHART_API double Range();
	
	CHART_DECLARE_SERIAL(CScale);

	//@cmember
	/* Serialization.*/
	CHART_API virtual void Serialize(CArchive &ar);

	// XML formatter for CScale
	friend class CScaleFTR;
};

#endif //__SCALE__


#ifndef __SRGRAPHSTYLE__
#define __SRGRAPHSTYLE__

//$head The style class
//$level 1

/////////////////////////////////////////////////////////////////////////////
// Autoduck help section for SRGraphStyle

//@doc SRGraphStyle

//@mdata double | SRGraphStyle | m_dMaxHeight | Maximum height in pixels that an object may be drawn
//@see <mf SRGraphStyle::GetMaxObjectHeight> <mf SRGraphStyle::SetMaxObjectHeight> <md SRGraphStyle::m_dMaxDepth> <md SRGraphStyle::m_dMaxWidth>

//@mdata double | SRGraphStyle | m_dMaxDepth | Maximum depth in pixels that an object may be drawn<nl>
//Used to limit sizes of bars in Manhattan graphs, etc.
//@see <mf SRGraphStyle::GetMaxObjectDepth> <mf SRGraphStyle::SetMaxObjectDepth> <md SRGraphStyle::m_dMaxWidth> <md SRGraphStyle::m_dMaxHeight>

//@mdata double | SRGraphStyle | m_dMaxWidth | Maximum width in pixels that an object may be drawn<nl>
//Used to limit the width of bars, etc. 
//@see <mf SRGraphStyle::GetMaxObjectWidth> <mf SRGraphStyle::SetMaxObjectWidth> <md SRGraphStyle::m_dMaxDepth> <md SRGraphStyle::m_dMaxHeight>

//@mdata CString | SRGraphStyle | m_strObjectName | Used to identify a resource or file associated with this object<nl>
//Particularly used for the resource name which define polygon bars
//@see <mf SRGraphStyle::SetObjectName> <mf SRGraphStyle::GetObjectName>

//@mdata DWORD | SRGraphStyle | m_dwStyle | Various style semaphores and bit combinations<nl>
//You are strongly advised to use the correct initialization and interrogation routines for these styles.<nl>
//
//@head3 Frame styles | Define the type of frame drawn around bars, etc.<nl>
//Use <mf SRGraphStyle::GetFrameStyle> and <mf SRGraphStyle::SetFrameStyle>.<nl>
//See <l Frame styles> for a list of available tags.
//
//@head3 Interior styles | Define how an object is filled<nl>
//Use <mf SRGraphStyle::GetInteriorStyle> and <mf SRGraphStyle::SetInteriorStyle>.<nl>
//See <l Interior styles> for a list of available tags.
//
//@head3 Object styles | Define the type of object used for a particular data item<nl>
//Use <mf SRGraphStyle::SetObjectStyle> and <mf SRGraphStyle::GetObjectStyle>.<nl>
//See <l Frame styles> for a list of available tags.
//
//@head3 Graph styles | Define the type of graph display<nl>
//Use <mf SRGraphStyle::SetGraphStyle> and <mf SRGraphStyle::GetGraphStyle>.<nl>
//See <l Graph styles> for a list of available tags.
//
//@head3 Axis styles | Each graph data display needs an axis upon which data is projected. 
//Use <mf SRGraphStyle::SetAxisStyle> and <mf SRGraphStyle::GetAxisStyle>.<nl>
//See <l Axis styles> for a list of available tags.


//@mdata DWORD | SRGraphStyle | m_dwStyleA | Contains various single bit styles<nl>
//You are strongly advised to use the correct initialization and interrogation routines for these styles.<nl>
//
//@head3 Feature masks | Select various chart features <nl>
//Settings are all single bit semaphores.<nl>
//See <l Feature masks> for a bit definitions.

//@mdata DWORD | SRGraphStyle | m_dwStyleB | Style data<nl>
//
//@head3 Legend styles | Determine which data is displayed in the legend<nl>
//Use <mf SRGraphStyle::SetLegendStyle> and <mf SRGraphStyle::GetLegendStyle>.<nl>
//See <l Legend styles> for a list of available tags.
//
///@head3 Feature masks | Select various chart features <nl>
//Settings are all single bit semaphores.<nl>
//See <l Feature masks> for a bit definitions.
//
//@devnote Stingray reserves all other bits in the m_dwStyleB variable.<nl>

//@mdata DWORD | SRGraphStyle | m_dwComponentStyle | Styles for the basic component panel<nl>
//Use only the correct get and set routines to change these parameters.<nl>
//
//@head3 Component border styles | Determine the appearance of the border drawn around the component rectangle<nl>
//Use <mf SRGraphStyle::SetComponentBorderStyle> and <mf SRGraphStyle::GetComponentBorderStyle>.<nl>
//See <l Border styles> for a list of available tags.
//
//@head3 Shadow styles | Determine the shadow drawn around the component rectangle<nl>
//Use <mf SRGraphStyle::SetComponentShadowStyle> and <mf SRGraphStyle::GetComponentShadowStyle>.<nl>
//See <l Shadow styles> for a list of available tags.
//
//@head3 Background fill styles | Determine how the interior of the component retangle is filled<nl>
//Use <mf SRGraphStyle::GetComponentFillStyle> and <mf SRGraphStyle::SetComponentFillStyle>.<nl>
//See <l Background styles> for a list of available tags.<nl>

//@mdata DWORD | SRGraphStyle | m_dwStyleC | Contains type, label, and highlight settings
//
//@head3 Component types | Identify the type of object which owns the SRGraphStyle variable <nl>
//Use <mf SRGraphStyle::GetType> and <mf SRGraphStyle::SetType>.<nl>
//See <l Component types> for a list of available types.
//
//@head3 Legend key styles | Determine the appearance of legend keys<nl>
//Use <mf SRGraphStyle::SetLegendKeyStyle> and <mf SRGraphStyle::GetLegendKeyStyle>.<nl>
//See <l Legend key styles> for a list of available tags.
//
//@head3 Label styles | Particularly used on pie charts to show information normally shown on the axes of other graphs<nl>
//Use <mf SRGraphStyle::SetLabelStyle> and <mf SRGraphStyle::GetLabelStyle>.<nl>
//See <l Label styles> for a list of available tags.<nl>
//
//@head3 Highlight styles for pie wedge slices | A highlight setting will "explode" the wedge from the pie.<nl>
//Use <mf SRGraphStyle::SetHighlight> and  <mf SRGraphStyle::GetHighlight>.<nl>
//See <l Highlight styles for pie wedges> for a list of available tags.<nl>

//@mdata COLORREF | SRGraphStyle | m_RGBFrameColor | RGB color value associated with frames around objects, graph axes, etc.
//@see <mf SRGraphStyle::SetFrameColor> <mf SRGraphStyle::GetFrameColor>

//@mdata CString | SRGraphStyle | m_strFramePattern | Resource name of the pattern used to paint frames
//@see <mf SRGraphStyle::SetFramePattern> and <mf SRGraphStyle::GetFamePattern>

//@mdata int | SRGraphStyle | m_nFrameWidth | Pen width for drawing frames
//@see <mf SRGraphStyle::SetFrameWidth> and <mf SRGraphStyle::GetFrameWidth>

//@mdata COLORREF | SRGraphStyle | m_RGBColorA | RGB color value used to color objects and backgrounds -- also used as the first color value in vignette drawing
//@see <mf SRGraphStyle::SetColor> and <mf SRGraphStyle::GetColor>

//@mdata COLORREF | SRGraphStyle | m_RGBColorB | The final color used in vignette drawing
//@see <mf SRGraphStyle::SetColor> and <mf SRGraphStyle::GetColor>

//@mdata double | SRGraphStyle | m_dAngle | The angle (in degrees) used for drawing angled vignettes
//@see <mf SRGraphStyle::SetAngle> <mf SRGraphStyle::GetAngle>

//@mdata CString &| SRGraphStyle | m_strImage | The name of the resource used to paint or tile image fills
//@see <mf SRGraphStyle::SetResourceName> <mf SRGraphStyle::GetResourceName>

//@mfunc CString &| SRGraphStyle | GetFramePattern | Fetches the resource name for the bitmap used to generate pattern brushes for the frames of objects etc.
//@see <mf SRGraphStyle::SetFramePattern> <md SRGraphStyle::m_strFramePattern>

//@mfunc void | SRGraphStyle | SetFramePattern | Initialises the resource name for the bitmap used to generate pattern brushes for the frames of objects etc.
//@see <mf SRGraphStyle::GetFramePattern> <md SRGraphStyle::m_strFramePattern>

//@mfunc void | SRGraphStyle | SetFrameWidth | Sets the size of the pen used for the frames of objects etc.
//@parm int | nFrameWidth | Desired pen width in logical units
//@see <mf SRGraphStyle::GetFrameWidth> <md SRGraphStyle::m_nFrameWidth>

//@mfunc DWORD | SRGraphStyle | GetStyle | Retrieves a raw style
//@rdesc DWORD with all current styles from the m_dwStyle member
//@see <mf SRGraphStyle::SetStyle>
//@devnote If possible, you should not use this or the SetStyle members. 
//Use the provided Get and Set member functions instead. These routines ensure that no bit mask confusion can arise from direct access to the m_dwStyle?? members.

//@mfunc void | SRGraphStyle | SetStyle | Sets a raw style
//@parm DWORD | style | Bit combination with any or all style settings
//@see <mf SRGraphStyle::GetStyle>
//@devnote If possible, you should not use this or the GetStyle members. 
//Use the provided Get and Set member functions instead. These routines ensure that no bit mask confusion can arise from direct access to the m_dwStylex members.

//@mfunc void | SRGraphStyle | SetGridColor | Sets the RGB color used to draw grid lines (default is CXCLR_TEAL)
//@parm COLORREF | c | New color

//@mfunc void | SRGraphStyle | SetXAngle | Sets the X rotation for the object viewing angle (currently used only for pie charts -- tilts the pie to a specific angle)
//@parm double | dAngle | Desired angle (0-90) in degrees

//@mfunc void | SRGraphStyle | SetYAngle | Sets the Y rotation for the object viewing angle (currently unused)
//@parm double | dAngle | Desired angle (0-90) in degrees

//@mfunc void | SRGraphStyle | SetZAngle | Initializes the Z rotation for the object viewing angle (currently unused)
//@parm double | dAngle | Desired angle (0-90) in degrees

//@mdata COLORREF  | SRGraphStyle | m_RGBGridColor | RGB color reference for grid lines

//@mfunc virtual BOOL  | SRGraphStyle | DRIsLocked | Checks to see if the position of m_DisplayRect is locked

//@mdata BOOL  | SRGraphStyle | m_bStyleIsDifferent | Set TRUE by modifications to the style.

//@mfunc virtual void  | SRGraphStyle | SetStyleIsDifferent | Sets the StyleIsDifferent flag
//@parm BOOL  | v | TRUE to signify a change (this is the default)

//@mfunc virtual BOOL  | SRGraphStyle | GetStyleIsDifferent | Retrieves the StyleIsDifferent flag

//@mdata double  | SRGraphStyle | m_dXAngle | Number of degrees the display should be rotated about the X axis (currently used only in Pie charts)

//@mdata double  | SRGraphStyle | m_dYAngle | Number of degrees the display should be rotated about the Y axis (currently unused)

//@mdata double  | SRGraphStyle | m_dZAngle | Number of degrees the display should be rotated about the Y axis (currently unused)


//adinsert

/////////////////////////////////////////////////////////////////////////////

//@class Manages style data for graphic objects in the graph class kit
//@base public | CObject
class SRGraphStyle : public CObject
{

//@access Public data members
public:
	CHART_API SRGraphStyle(const SRGraphStyle &s);

//@access Protected data members
protected:
	//@cmember
	/* set TRUE by modifications to the style (Not serialized)*/
	BOOL m_bStyleIsDifferent;
	
	//@cmember
	/* Various style flags*/
	DWORD m_dwStyleC;
	
	//@cmember
	/* RGB color reference for grid lines*/
	COLORREF m_RGBGridColor;
	
	//@cmember
	/* Various style flags -- see bitmask definitions*/
	DWORD m_dwStyleB;

	//@cmember
	/* Holds the maximum object height*/
	double m_dMaxHeight;

	//@cmember
	/* Holds the maximum object depth*/
	double m_dMaxDepth;

	//@cmember
	/* Holds the maximum object width*/
	double m_dMaxWidth;

	//@cmember
	/* Holds a name used to retrieve resource or file data for this graph display item (ie. the polygon resource for custom bars)*/
	CString m_strObjectName;
  
	//@cmember
	/* Various style flags -- see bitmask definitions*/
	DWORD m_dwStyle;

	//@cmember
	/* Various style flags -- see bitmask definitions*/
	DWORD m_dwStyleA;

	//@cmember
	/* Style for this component*/
	DWORD m_dwComponentStyle;

	//@cmember
	/* Color variable for frame (RGB value)*/
	COLORREF m_RGBFrameColor;

	//@cmember
	/* Name of the pattern used to fill the frame*/
	CString m_strFramePattern;

	//@cmember
	/* Width of the frame in pixels*/
	int m_nFrameWidth;

	//@cmember
	/* Color variable for interior (RGB value)*/
	COLORREF m_RGBColorA;

	//@cmember
	/* Color variable for interior (RGB value)*/
	COLORREF m_RGBColorB;

	//@cmember
	/* Angle of vignet*/
	double m_dAngle;

	//@cmember
	/* Name of an image or resource*/
	CString m_strImage;

	//@cmember
	/* Number of degrees the display should be rotated about the X axis (currently used only in Pie charts)*/
	double m_dXAngle;
	
	//@cmember
	/* Number of degrees the display should be rotated about the Y axis (currently unused)*/
	double m_dYAngle;
	
	//@cmember
	/* Number of degrees the display should be rotated about the Z axis (currently unused)*/
	double m_dZAngle;

//@access public member functions
public:	
	//@cmember
	/* returns the semaphore that signifies that an image is loaded */
	inline BOOL GetImageLoaded();
	//@cmember
	/* Initializes the semaphore that signifies that an image is loaded */
	inline void SetImageLoaded(BOOL b);
	//@cmember
	/* Returns the semaphore that allows lines to be broken when a null item is found*/
	inline BOOL GetBreakLinesOnNull();
	//@cmember
	/* initializes the semaphore that allows lines to be broken when a null item is found*/
	inline void SetBreakLinesOnNull(BOOL b);
	//@cmember
	/* Returns flag to insert thousand separators (',') in labels created by SRGDecimalScale and its derivatives*/
	inline BOOL GetUseThousandSeparator();
	//@cmember
	/* Sets flag to insert thousand separators (',') in labels created by SRGDecimalScale and its derivatives*/
	inline void SetUseThousandSeparator(BOOL b);
	//@cmember
	/* Used in bubble or vector charts to ensure all items are drawn inside the display */
	inline void SetObjectInsideView(BOOL bInside);
	//@cmember
	/* Tells bubble or vector charts to ensure all items are drawn inside the display */
	inline BOOL GetObjectInsideView();
	//@cmember
	/* Sets a semaphore that makes tags draw a line from their final position to thier anchor point */
	inline void SetLinkTags(BOOL b);
	//@cmember
	/* Returns the semaphore that makes tags draw a line from their final position to thier anchor point */
	inline BOOL GetLinkTags();
	//@cmember
	/* Returns the tag color settings */
	inline COLORREF GetTagColor();
	//@cmember
	/* Initializes the tag color settings */
	inline void SetTagColor(COLORREF c);
	//@cmember
	/* Returns the current tag model */
	inline DWORD GetTagModel();
	//@cmember
	/* Initializes the tag model */
	inline void SetTagModel(DWORD dwStyle);
	//@cmember
	/* Returns the tag font size */
	inline DWORD GetTagFontSize();
	//@cmember
	/* Initializes the tag font size */
	inline void SetTagFontSize(DWORD dwStyle);
	//@cmember
	/* Returns the current tag orientation */
	inline DWORD GetTagOrientation();
	//@cmember
	/* Initializes tag orientation */
	inline void SetTagOrientation(DWORD dwStyle);
	//@cmember
	/* Returns the current tag position */
	inline DWORD GetTagPosition();
	//@cmember
	/* Initializes the tag position */
	inline void SetTagPosition(DWORD dwStyle);
	//@cmember
	/* Returns the current tag outline style */
	inline DWORD GetTagOutlineStyle();
	//@cmember
	/* Initializes the tag outline style */
	inline void SetTagOutlineStyle(DWORD dwStyle);
	//@cmember
	/* Returns the independent max-scale semaphore for Y axes (not currently used).*/
	 inline  BOOL GetUseMaxYScale();
	//@cmember
	/* Returns the independent max-scale semaphore for X axes (not currently used).*/
	 inline  BOOL GetUseMaxXScale();
	//@cmember
	/* Initialises the independent max-scale semaphore for Y axes (not currently used).*/
	 inline  void SetUseMaxYScale(BOOL b);
	//@cmember
	/* Initialises the independent max-scale semaphore for X axes (not currently used).*/
	 inline  void SetUseMaxXScale(BOOL b);
	//@cmember
	/* Returns the semaphore that specifies if scatter charts should use the same scaling factor for both x and y axes*/
	 inline  BOOL GetUseSameXYScaleFactor();
	//@cmember
	/* Sets the semaphore that specifies if scatter charts should use the same scaling factor for both x and y axes*/
	 inline  void SetUseSameXYScaleFactor(BOOL b);
	//@cmember
	/* Return the relative index semaphore*/
	 inline  BOOL GetRelIndex();
	//@cmember
	/* Initializes the relative index semaphore*/
	 inline  void SetRelIndex(BOOL b);
	//@cmember
	/* Sets the StyleIsDifferent flag*/
	  inline void SetStyleIsDifferent(BOOL v=TRUE){m_bStyleIsDifferent=v;}
	//@cmember
	/* Retrieves the StyleIsDifferent flag*/
	  inline BOOL GetStyleIsDifferent(){return m_bStyleIsDifferent;}
	//@cmember
	/* Returns the OC 1.01 label compatibility flag*/
	 inline  BOOL GetXLCompatibility();
	//@cmember
	/* Sets the OC 1.01 compatibility flag*/
	 inline  void SetXLCompatibility(BOOL b);
	//@cmember
	/* Returns the XY scale swap flag*/
	 inline  BOOL GetHgraph();
	//@cmember
	/* Sets XY scale swap flag (compound charts only)*/
	 inline  void SetHgraph(BOOL b);
	//@cmember
	/* Returns the point culling flag*/
	  inline BOOL GetCull();
	//@cmember
	/* Sets the point culling flag*/
	  inline void SetCull(BOOL b);
	//@cmember
	/* Returns the X scale log setting*/
	  inline BOOL GetLogX();
	//@cmember
	/* Sets the X scale log setting*/
	 inline  void SetLogX(BOOL b);
	//@cmember
	/* Returns the automatic orientation flag*/
	 inline  BOOL GetAutoOrientation();
	//@cmember
	/* Sets the automatic orientation flag*/
	 inline  void SetAutoOrientation(BOOL b);
	//@cmember
	/* Returns the deferred drawing flag*/
	 inline  BOOL GetDeferDraw();
	//@cmember
	/* Sets the deferred drawing flag*/
	 inline  void SetDeferDraw(BOOL b);
	//@cmember
	/* Returns the number of columns available for legend keys*/
	 inline  int GetLegendColumns();
	//@cmember
	/* Sets the number of columns in which to display legend keys*/
	 inline  void SetLegendColumns(int n);
	//@cmember
	/* Returns the number of rows available for legend keys*/
	 inline  int GetLegendRows();
	//@cmember
	/* Sets the number of rows in which to display legend keys*/
	 inline  void SetLegendRows(int n);
	//@cmember
	/* Returns the scale limiting flag */
	 inline  BOOL GetScaleLimit();
	//@cmember
	/* Turns scale limiting on or off */
	 inline  void SetScaleLimit(BOOL style);
	//@cmember
	/* Returns the key-first flag -- TRUE if keys appear to left of text*/
	inline  BOOL GetLegendKeyFirst();
	//@cmember
	/* Specifies if legend keys should appear before the text, or vica versa*/
	 inline  void SetLegendKeyFirst(BOOL style);
	//@cmember
	/* Returns the rectangle locking flag for legends*/
	 inline  BOOL GetLegendLockRC();
	//@cmember
	/* Sets rectangle locking for legends*/
	 inline  void SetLegendLockRC(BOOL style);
	//@cmember
	 /* NEW 6.01 Returns the Display Info Only semaphore */
	 inline BOOL GetDisplayInfoOnly();
	//@cmember
	 /* NEW 6.01 Sets the Display Info Only semaphore */
	 inline void SetDisplayInfoOnly(BOOL style);

	CHART_DECLARE_SERIAL(SRGraphStyle);
	
	//@cmember
	/* Initializes the legend key style*/
	inline   void SetLegendKeyStyle(DWORD dwStyle);

	//@cmember
	/* Fetches the legend key style*/
	 inline  DWORD GetLegendKeyStyle();
	
	//@cmember
	/* Initializes the flag that controls the "tiered" display of label blocks attached to the x-axis*/
	inline   void SetTierXLabels(BOOL style);

	//@cmember
	/* Initializes the flag that controls the "tiered" display of label blocks attached to the y-axis*/
	 inline  void SetTierYLabels(BOOL style);

	//@cmember
	/* Returns the flag that controls the "tiered" display of label blocks attached to the x-axis*/
	 inline  BOOL GetTierXLabels();

	//@cmember
	/* Returns the flag that controls the "tiered" display of label blocks attached to the y-axis*/
	inline   BOOL GetTierYLabels();
	
	//@cmember
	/* Initializes the color used to display grid lines*/
	 inline  void SetGridColor(COLORREF c){m_RGBGridColor=c;}
	
	//@cmember,mfunc
	/* Fetches the grid line color*/
	 inline  COLORREF GetGridColor(){return m_RGBGridColor;}
	
	//@cmember
	/* Sets the angle which the display should be rotated about the X axis (currently used only on Pie charts)*/
	 inline  void SetXAngle(double d){m_dXAngle=d;}
	
	//@cmember
	/* Sets the angle which the display should be rotated about the Y axis (currently unused)*/
	 inline  void SetYAngle(double d){m_dYAngle=d;}
	
	//@cmember
	/* Sets the angle which the display should be rotated about the Z axis (currently unused)*/
	inline   void SetZAngle(double d){m_dZAngle=d;}
	
	//@cmember,mfunc
	/* Returns the angle which the display should be rotated about the X axis (currently used only on Pie charts)*/
	 inline  double GetXAngle(){return m_dXAngle;}
	
	//@cmember,mfunc
	/* Returns the angle which the display should be rotated about the Y axis (implemented but unused)*/
 	 inline  double GetYAngle(){return m_dYAngle;}
	
	//@cmember,mfunc
	/* Returns the angle which the display should be rotated about the Z axis (implemented but unused)*/
 	inline   double GetZAngle(){return m_dZAngle;}
	
	//@cmember
	/* Assignment (copy) operator for Style objects*/
	 CHART_API void operator =(const SRGraphStyle &s);
	
	//@cmember
	/* Constructor*/
	CHART_API SRGraphStyle();

	//@cmember
	/* Sets axis styles*/
	 inline  void SetAxisStyle(DWORD style);

	//@cmember
	/* Interrogates the axis style*/
	inline   DWORD GetAxisStyle();

	//@cmember
	/* Interrogates the m_dwStyle member*/
	 inline  DWORD GetGraphStyle();
	 
	//@cmember
	/* Interrogates legend style*/
	inline   DWORD GetLegendStyle();

	//@cmember
	/* Initializes the legend style*/
	 inline  void SetLegendStyle(DWORD style);

	//@cmember
	/* Sets the m_dwStyle member with an absolute code*/
	 inline void SetStyle(DWORD style){m_dwStyle=style;}

	//@cmember
	/* Retrieves the m_dwStyle code without masking any bits*/
	 inline DWORD GetStyle(){return m_dwStyle;}

	//@cmember
	/* Sets the highlight flags*/
	 inline void SetHighlight(DWORD style);

	//@cmember
	/* Returns the highlight flags*/
	 inline  DWORD GetHighlight();

	//@cmember
	/* Sets the label flags*/
	 inline  void SetLabelStyle(DWORD style);

	//@cmember
	/* Returns the label flags*/
	inline   DWORD GetLabelStyle();

	//@cmember
	/* Returns the frame flags*/
	 inline  DWORD GetFrameStyle();

	//@cmember
	/* Returns the object flags*/
	 inline  DWORD GetObjectStyle();

	//@cmember
	/* Sets the object flags*/
	 inline  void SetObjectStyle(DWORD style);

	//@cmember
	/* Sets the name of the resource or image used in filling */
	 inline  void SetResourceName(LPCTSTR name);

	//@cmember
	/* Retrieves the name of the resource or image used in filling */
	 inline  CString & GetResourceName();

	//@cmember
	/* Returns the interior flags*/
	 inline  DWORD GetInteriorStyle();

	//@cmember
	/* Returns the type flags*/
	inline   DWORD GetType();

	//@cmember
	/* Sets the type flags*/
	inline   void SetType(DWORD type);

	//@cmember
	/* Returns the shadow flags*/
	inline   DWORD GetComponentShadowStyle();

	//@cmember
	/* Returns the shadow flags*/
	inline   DWORD GetComponentFillStyle();

	//@cmember
	/* Returns the shadow flags*/
	inline   DWORD GetComponentBorderStyle();

	//@cmember
	/* Alternative color setting routine*/
	inline   void SetColor(COLORREF color,BOOL bSetB=FALSE);

	//@cmember
	/* Sets the style flags*/
	 inline  void SetComponentStyle(DWORD style);

	//@cmember
	/* Returns the style flags*/
	inline   DWORD GetComponentStyle();

	//@cmember
	/* Sets the component flags*/
	inline   void SetColor(COLORREF a,COLORREF b);

	//@cmember
	/* Initializes graph styles*/
	inline   void SetGraphStyle(DWORD style);

	//@cmember
	/* Initializes the shading style for data objects*/
 	inline  void SetObjectShadeStyle(BOOL style);

	//@cmember
	/* Interrogates the shading style for data objects	*/
	 inline  BOOL GetObjectShadeStyle();

	//@cmember
	/* Sets the pen color used to outline objects*/
	inline   void SetFrameColor(COLORREF color);

	//@cmember
	/* Sets the maximum height of a data object*/
	inline   void SetMaxObjectHeight(double size);

	//@cmember
	/* Sets the maximum depth of a data object*/
	inline   void SetMaxObjectDepth(double size);

	//@cmember
	/* Sets the maximum width of a data object*/
	inline   void SetMaxObjectWidth(double size);

	//@cmember
	/* Sets the axis filling function*/
	 inline  void SetAxisFillStyle(BOOL style);

	//@cmember
	/* Interrogates the axis filling semaphore*/
	inline   BOOL GetAxisFillStyle();

	//@cmember
	/* Interrogates the m_FrameColor member*/
	 inline  COLORREF GetFrameColor();

	//@cmember
	/* Interrogates the m_colorA or m_colorB members */
	inline   COLORREF GetColor(BOOL GetColorB=FALSE);

	//@cmember
	/* Determines whether the maximum data object size is to be used*/
	inline   BOOL GetUseMaxSize();

	//@cmember
	/* Sets or resets the maximum data object size semaphore*/
	inline   void SetUseMaxSize(BOOL flag);

	//@cmember
	/* Interrogates the m_dMaxHeight member*/
	 inline  double GetMaxObjectHeight();

	//@cmember
	/* Interrogates the m_dMaxWidth member*/
	 inline  double GetMaxObjectWidth();

	//@cmember
	/* Interrogates the m_dMaxDepth member*/
	 inline  double GetMaxObjectDepth();

	//@cmember
	/* Sets the shadow style for component display panels*/
	 inline  void SetComponentShadowStyle(DWORD style);

	//@cmember
	/* Sets the border style for component display panels*/
	 inline  void SetComponentBorderStyle(DWORD style);

	//@cmember
	/* Sets the interior fill style for component display panels*/
	inline  void SetComponentFillStyle(DWORD style);

	//@cmember
	/* Sets the style used for framing graphic data objects*/
	inline   void SetFrameStyle(DWORD style);

	//@cmember
	/* Sets the style used to fill the interior areas of graphic data objects*/
	inline   void SetInteriorStyle(DWORD style);

	//@cmember
	/* Interrogates the image stretching semaphore*/
	inline   BOOL GetStretchMode();

	//@cmember
	/* Sets or resets the image stretching semaphore*/
	 inline  void SetStretchMode(BOOL m);

	//@cmember
	/* Returns the name of the graphic data object*/
	 inline  CString& GetObjectName();

	//@cmember
	/* Sets the name of the graphic data object*/
	 inline  void SetObjectName(LPCTSTR name);

	//@cmember
	/* Assigns the angle for angled shaded fills*/
	inline   void SetAngle(double angle);

	//@cmember
	/* Retrieves the angle for angled shaded fills*/
	inline   double GetAngle();

	//@cmember
	/* Retrieves the pen width of lines used to draw frames*/
	inline   int GetFrameWidth();

	//@cmember
	/* Determines if the legend is a line or fill type*/
	inline   BOOL GetLegendLine();

	//@cmember
	/* Initializes legend style to line or fill type*/
	inline  void SetLegendLine(BOOL style);

	//@cmember
	/* Determines whether indices should be drawn on axes*/
	 inline  BOOL GetShowIndices();

	//@cmember
	/* Determines whether groups should be drawn on axes*/
	 inline  BOOL GetShowGroups();

	//@cmember
	/* Determines whether values should be drawn on axes*/
	 inline  BOOL GetShowNumerals();

	//@cmember
	/* Defines whether groups should be drawn on axes*/
	 inline  void SetShowGroups(BOOL style);

	//@cmember
	/* Defines whether indices should be drawn on axes*/
	 inline  void SetShowIndices(BOOL style);

	//@cmember
	/* Defines whether values should be drawn on axes*/
	 inline  void SetShowNumerals(BOOL style);

	//@cmember
	/* Determines whether the "empty" graph symbol should be shown*/
	inline   BOOL GetUseEmptyGraph();

	//@cmember
	/* Defines whether the "empty" graph symbol should be shown*/
	 inline  void SetUseEmptyGraph(BOOL style);

	//@cmember
	/* Determines whether the maximum scale values should be used*/
	 inline  BOOL GetUseMaxScale();

	//@cmember
	/* Defines whether the maximum scale values should be used*/
	 inline  void SetUseMaxScale(BOOL style);

	//@cmember
	/* Initializes the frame pattern resource name*/
	 inline  void SetFramePattern(CString& framepattern){m_strFramePattern=framepattern;}

	//@cmember
	/* Retrieves the frame pattern resource name*/
	 inline  CString& GetFramePattern(){return m_strFramePattern;}

	//@cmember
	/* Initializes the pen width for frames around objects*/
	 inline  void SetFrameWidth(int FrameWidth){m_nFrameWidth=FrameWidth;}

	//@cmember
	/* Gets the Log scaling flag */
	 inline  BOOL GetLog();

    //@cmember
    /* Sets or resets the logarithmic scaling function*/
	  inline void SetLog(BOOL logFlag=TRUE);

	//@cmember
	/* Interrogates the semaphore which enables or disables the display of X grid lines on the axis*/
	 inline  BOOL GetShowXGrid();
	//@cmember
	/* Interrogates the semaphore which enables or disables the display of Y grid lines on the axis*/
	  inline BOOL GetShowYGrid();
	//@cmember
	/* Interrogates the semaphore which enables or disables the display of Z grid lines on the axis*/
	 inline  BOOL GetShowZGrid();
	//@cmember
	/* Initializes the semaphore which enables or disables the display of X grid lines on the axis*/
	inline   void SetShowXGrid(BOOL style);
	//@cmember
	/* Initializes the semaphore which enables or disables the display of Y grid lines on the axis*/
	 inline  void SetShowYGrid(BOOL style);
	//@cmember
	/* Initializes the semaphore which enables or disables the display of Z grid lines on the axis*/
	 inline  void SetShowZGrid(BOOL style);
	//@cmember
	/* Interrogates the semaphore which enables or disables the display of X tick marks*/
	inline   BOOL GetShowXTicks();
	//@cmember
	/* Interrogates the semaphore which enables or disables the display of Y tick marks*/
	inline   BOOL GetShowYTicks();
	//@cmember
	/* Interrogates the semaphore which enables or disables the display of Z tick marks*/
	 inline  BOOL GetShowZTicks();
	//@cmember
	/* Initializes the semaphore which enables or disables the display of X tick marks*/
	inline   void SetShowXTicks(BOOL style);
	//@cmember
	/* Initializes the semaphore which enables or disables the display of Y tick marks*/
	 inline  void SetShowYTicks(BOOL style);
	//@cmember
	/* Initializes the semaphore which enables or disables the display of Z tick marks*/
	 inline  void SetShowZTicks(BOOL style);
	//@cmember
	/* Initializes the AutoSort flag -- if TRUE auto sorting takes place on Manhattan and Rooftop charts.*/
	 inline  void SetSort(BOOL style);
	//@cmember
	/* Interrogates the AutoSort flag in <md SRGraphStyle::m_dwStyleC>*/
	 inline  BOOL GetSort();
	//@cmember
	/* Sets the order in which grid and data overlay one another*/
	 inline  void SetGridOrder(BOOL style);
	//@cmember
	/* Gets the order in which grid and data overlay one another*/
	 inline  BOOL GetGridOrder();
	//@cmember
	/* Enables or disables the locking of the position of m_DisplayRect*/
	  inline void DRLock(BOOL style);
	//@cmember
	/* Checks to see if the position of m_DisplayRect is locked*/
	 inline  BOOL DRIsLocked(){return m_dwStyleA & CX_DISPLAYLOCK_MASK;}
	//@cmember
	/* Interrogates the "Always Show Zero" flag*/
	 inline  BOOL GetAlwaysShowZero();
	//@cmember
	/* Initializes the "Always Show Zero" flag -- if TRUE the graph will allways extend to or cover the zero value*/
	inline   void SetAlwaysShowZero(BOOL style);

	//@cmember
	/* Serialization*/
	 CHART_API void Serialize(CArchive &ar);
#ifdef _DEBUG
	//@cmember
	/* Debug dumping*/
	 CHART_API void Dump(CDumpContext &dc) const;
#endif

	// XML formatter for SRGraphStyle
	friend class SRGraphStyleFTR;
};



//@doc SRGraphStyle
//@mfunc Interrogates the graph style
//@rdesc Bit-masked value representing the graph style settings
//@see <l Graph styles>, <mf SRGraphStyle::SetGraphStyle>, <md SRGraphStyle::m_dwStyle>
inline DWORD SRGraphStyle::GetGraphStyle()
{
	return m_dwStyle & CX_GRAPH_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Safely sets the graph style bits<nl>
//When used on <c SRGraphDisplay> objects, this function sets the type used for 
//the chart or graph. By having more than one display component -- each programmed 
//to a different graph style, you may show graphs with multiple, overlaying displays or multiple axes.
//@parm New style value for the graph type
//@see <l Graph styles>, <mf SRGraphStyle::GetGraphStyle>, <md SRGraphStyle::m_dwStyle>
inline void SRGraphStyle::SetGraphStyle(DWORD style)
{
	SetStyleIsDifferent();
	m_dwStyle &= ~CX_GRAPH_STYLE_MASK;
	style &= CX_GRAPH_STYLE_MASK;
	m_dwStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Interrogates the axis style
//@rdesc Bit-masked value representing the axis style
//@see <l Axis styles>, <mf SRGraphStyle::SetAxisStyle>, <md SRGraphStyle::m_dwStyle>
inline DWORD SRGraphStyle::GetAxisStyle()
{
	return m_dwStyle & CX_AXIS_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Safely sets the axis style bits
//@parm New style value for the axis type
//@see <l Axis styles>, <mf SRGraphStyle::GetAxisStyle>, <md SRGraphStyle::m_dwStyle>
inline void SRGraphStyle::SetAxisStyle(DWORD style)
{
	SetStyleIsDifferent();
	m_dwStyle &= ~CX_AXIS_STYLE_MASK;
	style &= CX_AXIS_STYLE_MASK;
	m_dwStyle |= style;
}


//@doc SRGraphStyle
//@mfunc Interrogates the legend style bits
//@rdesc Masked legend style
//@see <l Legend styles>, <mf SRGraphStyle::SetLegendStyle>, <md SRGraphStyle::m_dwStyleB>
inline DWORD SRGraphStyle::GetLegendStyle()
{
	return m_dwStyleB & CX_LEGEND_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Safely sets the legend style bits -- only applies to legend components <nl>
//Selects the format of data key display.
//@parm New style value for the legend type
//@see <l Legend styles>, <mf SRGraphStyle::GetLegendStyle>, <md SRGraphStyle::m_dwStyleB>
inline void SRGraphStyle::SetLegendStyle(DWORD style)
{
	m_dwStyleB &= ~CX_LEGEND_STYLE_MASK;
	style &= CX_LEGEND_STYLE_MASK;
	m_dwStyleB |= style;
}

//@doc SRGraphStyle
//@mfunc Interrogates the m_RGBColorA or m_RGBColorB members
//@parm FALSE to retrieve the m_RGBColorA data, TRUE to retrieve the m_RGBColorB information
//@rdesc COLORREF taken from the requested data member
//@see <mf SRGraphStyle::SetColor>, <md SRGraphStyle::m_RGBColorA>, <md SRGraphStyle::m_RGBColorB>
inline COLORREF SRGraphStyle::GetColor(BOOL GetColorB)
{
	return GetColorB ? m_RGBColorB : m_RGBColorA;
}

//@doc SRGraphStyle
//@mfunc Initializes the colors used in filling objects
//@parm RGB value for color A
//@parm RGB value for color B (default = BLACK)
//@see <mf SRGraphStyle::GetColor>, <md SRGraphStyle::m_RGBColorA>, <md SRGraphStyle::m_RGBColorB>
inline void SRGraphStyle::SetColor(COLORREF a,COLORREF b)
{
	m_RGBColorA=a; m_RGBColorB=b;
}

//@doc SRGraphStyle
//@mfunc Alternative method of setting the color members
//@parm Color to set
//@parm FALSE (default) to set m_RGBColorA, TRUE to set m_RGBColorB
//@see <mf SRGraphStyle::GetColor>, <md SRGraphStyle::m_RGBColorA>, <md SRGraphStyle::m_RGBColorB>
inline void SRGraphStyle::SetColor(COLORREF color,BOOL bSetB)
{
	if(bSetB)
		m_RGBColorB=color;
	else
		m_RGBColorA=color;
}


//@doc SRGraphStyle
//@mfunc Retrieves component style data
//@rdesc Component style (unadulterated)
//@rem This routine simply returns the contents of the <md SRGraphStyle::m_dwComponentStyle> member variable. 
//If a specific style (ie. Shadow style or Border style) is required, use the specialized routines.
//@see <mf SRGraphStyle::GetComponentShadowStyle>, <mf SRGraphStyle::GetComponentBorderStyle>, 
//<mf SRGraphStyle::GetComponentFillStyle>
//@devnote The use of this routine is not recommended. Use the specific Get and Set routines provided.
inline DWORD SRGraphStyle::GetComponentStyle()
{
	return m_dwComponentStyle;
}

//@doc SRGraphStyle
//@mfunc Initializes the component style with an absolute value
//@parm Combined component style
//@rem This flag setting routine is not safe in that it affects all flags in the m_dwStyle variable. 
//For safe initialization of only the required flags, use the specific routines.
//@see <mf SRGraphStyle::SetComponentShadowStyle>, <mf SRGraphStyle::SetComponentBorderStyle>, 
//<mf SRGraphStyle::SetComponentFillStyle>
//@devnote The use of this routine is not recommended. Use the specific Get and Set routines provided.
inline void SRGraphStyle::SetComponentStyle(DWORD style)
{
	m_dwComponentStyle=style;
}

//@doc SRGraphStyle
//@mfunc Retrieves component shadow flag data
//@rdesc Bit-masked flags which deal with the shadow styles for component panels
//@see <l Shadow styles>, <mf SRGraphStyle::SetComponentShadowStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline DWORD SRGraphStyle::GetComponentShadowStyle()
{
	return m_dwComponentStyle & CX_SHADOW_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves component fill flag data
//@rdesc Bit-masked flags which deal with the styles associated with the filling of component panels
//@see <l Background styles>, <mf SRGraphStyle::SetComponentFillStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline DWORD SRGraphStyle::GetComponentFillStyle()
{
	return m_dwComponentStyle & CX_FILL_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves component border information
//@rdesc Bit-masked flags which deal with the styles defining the borders around component panels
//@see <l Border styles>, <mf SRGraphStyle::SetComponentBorderStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline DWORD SRGraphStyle::GetComponentBorderStyle()
{
	return m_dwComponentStyle & CX_BORDER_MASK;
}


//@doc SRGraphStyle
//@mfunc Safe initialization of the type flags<nl>
//Types are used to differentiate between components which are used to draw panels etc. 
//and objects which represent single data items.
//@parm New type
//@see <l Component types>, <mf SRGraphStyle::GetType>, <md SRGraphStyle::m_dwStyleC>
inline void SRGraphStyle::SetType(DWORD type)
{
	m_dwStyleC &= ~CX_TYPE_MASK;
	type &= CX_TYPE_MASK;
	m_dwStyleC |= type;
}


//@doc SRGraphStyle
//@mfunc Retrieves type flag data
//@rdesc Bit-masked flags which deal with the type styles
//@see <l Component types>, <mf SRGraphStyle::SetType>, <md SRGraphStyle::m_dwStyleC>
inline DWORD SRGraphStyle::GetType()
{
	return m_dwStyleC & CX_TYPE_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves interior flag data
//@rdesc Bit-masked flags which deal with the styles used to fill interiors of objects
//@see <l Interior styles>, <mf SRGraphStyle::SetInteriorStyle>, <md SRGraphStyle::m_dwStyle>
inline DWORD SRGraphStyle::GetInteriorStyle()
{
	return m_dwStyle & CX_INTERIOR_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves the resource or image name used to fill graphic objects
//@rdesc Reference to the CString object containing the name
//@see <mf SRGraphStyle::SetResourceName>, <md SRGraphStyle::m_strImage>
inline CString & SRGraphStyle::GetResourceName()
{
	return m_strImage;
}

//@doc SRGraphStyle
//@mfunc Initializes the resource or image name used to fill graphic objects
//@parm Text string containing the name
//@see <mf SRGraphStyle::GetResourceName>, <md SRGraphStyle::m_strImage>
inline void SRGraphStyle::SetResourceName(LPCTSTR name)
{
	if( m_strImage != name )
		SetImageLoaded(FALSE);
	m_strImage=name;
}

//@doc SRGraphStyle
//@mfunc Sets the object style<nl>
//This can be used in the style member of an SRGraphData item to define the type of data object 
//seen on the graph. 
//For example, use OBJECT_POINT to display simple points on line graphs or OBJECT_EXPOINT to show a wiget on the point. 
//By default, the object style is set to OBJECT_AUTOMATIC, and the graph routines choose an object style in context with the graph style. 
//@parm New style
//@see <l Object styles>, <mf SRGraphStyle::GetObjectStyle>, <md SRGraphStyle::m_dwStyle>
inline void SRGraphStyle::SetObjectStyle(DWORD style)
{
	m_dwStyle &= ~CX_OBJECT_STYLE_MASK;
	style &= CX_OBJECT_STYLE_MASK;
	m_dwStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Retrieves object flag data
//@rdesc Bit-masked flags which deal with the object styles
//@see <l Object styles>, <mf SRGraphStyle::SetObjectStyle>, <md SRGraphStyle::m_dwStyle>
inline DWORD SRGraphStyle::GetObjectStyle()
{
	return m_dwStyle & CX_OBJECT_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves frame flag data
//@rdesc Bit-masked flags which deal with the frame styles
//@see <l Frame styles>, <mf SRGraphStyle::SetFrameStyle>, <md SRGraphStyle::m_dwStyle>
inline DWORD SRGraphStyle::GetFrameStyle()
{
	return m_dwStyle & CX_FRAME_STYLE_MASK;

}

//@doc SRGraphStyle
//@mfunc Retrieves label flag data
//@rdesc Bit-masked flags which deal with the label styles
//@see <l Label styles>, <mf SRGraphStyle::SetLabelStyle>, <md SRGraphStyle::m_dwStyleC>
inline DWORD SRGraphStyle::GetLabelStyle()
{
	return m_dwStyleC & CX_LABEL_MASK;
}

//@doc SRGraphStyle
//@mfunc Safe initialization of the label flags<nl>
//Label styles apply particularly to pie chart displays. 
//You can choose to display data about a pie wedge as any combination of data value, percentage, and annotation.
//@parm Flags to update
//@see <l Label styles>, <mf SRGraphStyle::GetLabelStyle>, <md SRGraphStyle::m_dwStyleC>
inline void SRGraphStyle::SetLabelStyle(DWORD style)
{
	m_dwStyleC &= ~CX_LABEL_MASK;
	style &= CX_LABEL_MASK;
	m_dwStyleC |= style;
}

//@doc SRGraphStyle
//@mfunc Retrieves highlight flag data
//@rdesc Bit-masked flags which deal with the highlight styles
//@see <l Highlight styles for pie wedges>, <mf SRGraphStyle::SetHighlight>, <md SRGraphStyle::m_dwStyleC>
inline DWORD SRGraphStyle::GetHighlight()
{
	return m_dwStyleC & CX_HIGHLIGHT_MASK;
}

//@doc SRGraphStyle
//@mfunc Safe initialization of the highlight style
//@parm Style to be used to highlight pie wedges by exploding them from the pie
//@see <l Highlight styles for pie wedges>, <mf SRGraphStyle::GetHighlight>, <md SRGraphStyle::m_dwStyleC>
inline void SRGraphStyle::SetHighlight(DWORD style)
{
	m_dwStyleC &= ~CX_HIGHLIGHT_MASK;
	style &= CX_HIGHLIGHT_MASK;
	m_dwStyleC |= style;
}

//@doc SRGraphStyle
//@mfunc Stores a name string to be associated with this object<nl>  
//This name can be used to identify resources or files needed in the display of this data item. 
//For example, it is used to identify the polygonal shape used to outline custom shaped bars.
//@parm Pointer to a string containing the text to use
//@see <mf SRGraphStyle::GetObjectName>, <md SRGraphStyle::m_strObjectName>
inline void SRGraphStyle::SetObjectName(LPCTSTR name)
{
	m_strObjectName=name;
}

//@doc SRGraphStyle
//@mfunc Returns the name associated with this graphic object -- see <mf SRGraphStyle::SetObjectName> for details
//@rdesc Reference to the m_strObjectName member
//@see <mf SRGraphStyle::SetObjectName>, <md SRGraphStyle::m_strObjectName>
inline CString& SRGraphStyle::GetObjectName()
{
	return m_strObjectName;
}

//@doc SRGraphStyle
//@mfunc Sets or resets the stretch mode semaphore<nl> 
//If this semaphore is TRUE, then images used to fill the component area will be stretched 
//rather than tiled to cover the required space.
//@parm TRUE for stretch mode, FALSE for tile mode
//@see <mf SRGraphStyle::GetStretchMode>, <md SRGraphStyle::m_dwComponentStyle>
inline void SRGraphStyle::SetStretchMode(BOOL m)
{
	m_dwComponentStyle &= ~CX_STRETCH_MASK;
	m_dwComponentStyle |=	(m ? CX_STRETCH_MASK : 0);
}

//@doc SRGraphStyle
//@mfunc Returns the value of the stretch mode semaphore <nl>
//When TRUE, images used to cover the filled backgrounds are stretched to fill the space rather than tiled.
//@rdesc Current stretch mode setting
//@see <mf SRGraphStyle::SetStretchMode>, <md SRGraphStyle::m_dwComponentStyle> 
inline BOOL SRGraphStyle::GetStretchMode()
{
	return m_dwComponentStyle & CX_STRETCH_MASK;
}


//@doc SRGraphStyle
//@mfunc Sets the style of the data items interior fill
//@parm Fill style to set
//@see <l Interior styles>, <mf SRGraphStyle::GetInteriorStyle>, <md SRGraphStyle::m_dwStyle>
inline void SRGraphStyle::SetInteriorStyle(DWORD style)
{
	m_dwStyle &= ~CX_INTERIOR_STYLE_MASK;
	style &= CX_INTERIOR_STYLE_MASK;
	m_dwStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Sets the frame style for the data item
//@parm Style to set
//@see <l Frame styles>, <mf SRGraphStyle::GetFrameStyle>, <md SRGraphStyle::m_dwStyle>
inline void SRGraphStyle::SetFrameStyle(DWORD style)
{
	m_dwStyle &= ~CX_FRAME_STYLE_MASK;
	style &= CX_FRAME_STYLE_MASK;
	m_dwStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Sets the style used to fill the interior of component panels
//@parm Style to set 	
//@see <l Background styles>, <mf SRGraphStyle::GetComponentFillStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline void SRGraphStyle::SetComponentFillStyle(DWORD style)
{
	m_dwComponentStyle &= ~CX_FILL_MASK;
	style &= CX_FILL_MASK;
	m_dwComponentStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Sets the style used to draw the borders of component panels
//@parm Style to set
//@see <l Border styles>, <mf SRGraphStyle::GetComponentBorderStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline void SRGraphStyle::SetComponentBorderStyle(DWORD style)
{
	m_dwComponentStyle &= ~CX_BORDER_MASK;
	style &= CX_BORDER_MASK;
	m_dwComponentStyle |= style;
}

//@doc SRGraphStyle
//@mfunc Sets the style used to draw the shadows of component panels
//@parm Style to set
//@see <l Shadow styles>, <mf SRGraphStyle::GetComponentShadowStyle>, <md SRGraphStyle::m_dwComponentStyle>
inline void SRGraphStyle::SetComponentShadowStyle(DWORD style)
{
	m_dwComponentStyle &= ~CX_SHADOW_MASK;
	style &= CX_SHADOW_MASK;
	m_dwComponentStyle |= style;
}


//@doc SRGraphStyle
//@mfunc Gets the maximum depth of data items -- used to limit the stretching of bars etc.
//@rdesc Contents of the m_dMaxDepth member
//@see <mf SRGraphStyle::SetMaxObjectDepth>, <md SRGraphStyle::m_dMaxDepth>
inline double SRGraphStyle::GetMaxObjectDepth()
{
	return m_dMaxDepth;
}

//@doc SRGraphStyle
//@mfunc Gets the maximum width of data items -- used to limit the stretching of bars etc.
//@rdesc Contents of the m_dMaxWidth member
//@see <mf SRGraphStyle::SetMaxObjectWidth>, <md SRGraphStyle::m_dMaxWidth>
inline double SRGraphStyle::GetMaxObjectWidth()
{
	return m_dMaxWidth;
}

//@doc SRGraphStyle
//@mfunc Gets the maximum height of data items -- used to limit the stretching of bars etc.
//@rdesc Contents of the m_dMaxHeight member
//@see <mf SRGraphStyle::SetMaxObjectHeight>, <md SRGraphStyle::m_dMaxHeight>
inline double SRGraphStyle::GetMaxObjectHeight()
{
	return m_dMaxHeight;
}

//@doc SRGraphStyle
//@mfunc Sets the "use max size" semaphore in m_dwStyleA <nl>
//If this is TRUE, then the size that bars and other data items 
//can stretch to will be limited by the m_dMaxHeight, m_dMaxDepth and m_dMaxWidth members.
//@parm TRUE to activate size limits, FALSE to disable limits
//@see <l Feature masks>, <mf SRGraphStyle::GetUseMaxSize>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetUseMaxSize(BOOL flag)
{
	m_dwStyleA &= ~CX_SIZE_MASK;
	m_dwStyleA |= flag ? CX_SIZE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Interrogates the "use max size" semaphore which prevents bars and other objects 
//from growing larger than a pre-set maximum
//@rdesc TRUE if the size is to be limited, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetUseMaxSize>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetUseMaxSize()
{
	return m_dwStyleA & CX_SIZE_MASK ? TRUE : FALSE;
}


//@doc SRGraphStyle
//@mfunc Interrogates the m_RGBFrameColor member -- used to draw the frames of bars etc.
//@rdesc COLORREF containing the current frame color
//@see <mf SRGraphStyle::SetFrameColor>, <md SRGraphStyle::m_RGBFrameColor>
inline COLORREF SRGraphStyle::GetFrameColor()
{
	return m_RGBFrameColor;
}

//@doc SRGraphStyle
//@mfunc Returns the axis fill style
//@rdesc TRUE if axes are to be filled with the m_RGBColorA value
//@see <l Feature masks>, <mf SRGraphStyle::SetAxisFillStyle>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetAxisFillStyle()
{
	return (m_dwStyleA & CX_FILL_AXIS_MASK) ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore in m_dwStyleA which decides whether areas covered by axes are filled
//or simply framed. If the style is TRUE, then axes will be painted with the color stored in the m_RGBColorA member. 
//If FALSE, then the axes will only be framed with the color set in the m_RGBFrameColor member.
//@parm TRUE to fill the area covered by the axis, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::GetAxisFillStyle>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetAxisFillStyle(BOOL style)
{
	m_dwStyleA &= ~CX_FILL_AXIS_MASK;
	m_dwStyleA |= style ? CX_FILL_AXIS_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Sets the object stretching limit for bars etc.
//@parm Maximum attainable size
//@see <mf SRGraphStyle::GetMaxObjectWidth>, <mf SRGraphStyle::SetMaxObjectDepth>, <mf SRGraphStyle::SetMaxObjectHeight> <md SRGraphStyle::m_dMaxWidth>
inline void SRGraphStyle::SetMaxObjectWidth(double size)
{
	m_dMaxWidth=size;
}

//@doc SRGraphStyle
//@mfunc Sets the object stretching limit for bars etc.<nl>
//For example, the Manhattan graph uses this value to prevent the graph from being 
//stretched to the whole width of the window if such stretching would make the bars wider than this setting.
//@parm Maximum attainable size
//@see <mf SRGraphStyle::GetMaxObjectDepth>, <mf SRGraphStyle::SetMaxObjectWidth>, <mf SRGraphStyle::SetMaxObjectHeight> <md SRGraphStyle::m_dMaxDepth>
inline void SRGraphStyle::SetMaxObjectDepth(double size)
{
	m_dMaxDepth=size;
}

//@doc SRGraphStyle
//@mfunc Sets the object stretching limit for bars etc.
//@parm Maximum attainable size
//@see <mf SRGraphStyle::GetMaxObjectHeight>, <mf SRGraphStyle::SetMaxObjectWidth>, <mf SRGraphStyle::SetMaxObjectDepth> <md SRGraphStyle::m_dMaxHeight>
inline void SRGraphStyle::SetMaxObjectHeight(double size)
{
	m_dMaxHeight=size;

}

//@doc SRGraphStyle
//@mfunc Sets the color used to draw frames around graphic data items
//@parm COLORREF containing the desired RGB color
//@see <mf SRGraphStyle::GetFrameColor>, <md SRGraphStyle::m_RGBFrameColor>
inline void SRGraphStyle::SetFrameColor(COLORREF color)
{
	m_RGBFrameColor=color;
}

//@doc SRGraphStyle
//@mfunc Interrogates the shade style semaphore in m_dwStyleA<nl>
//If TRUE, objects such as 3D isographic bars 
//used in the "Manhattan" graphs (etc) will be shaded to provide a more pleasing 3D effect. 
//One side panel will be shaded and the top panels will have reflective glare added.<nl>
//@rdesc TRUE if objects require shading, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetObjectShadeStyle>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetObjectShadeStyle()
{
	return m_dwStyleA & CX_SHADE_OBJECT_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the shade style semaphore in m_dwStyleA
//@parm TRUE to turn shading on, FALSE to turn it off
//@see <l Feature masks>, <mf SRGraphStyle::GetObjectShadeStyle>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetObjectShadeStyle(BOOL style)
{
	m_dwStyleA &= ~CX_SHADE_OBJECT_MASK;
	m_dwStyleA |= style ? CX_SHADE_OBJECT_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Sets or resets the logarithmic scaling semaphore defined in m_dwStyleA
//@parm TRUE to turn on log scaling (default), FALSE to turn off log scaling
//@see <l Feature masks>, <mf SRGraphStyle::GetLog>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetLog(BOOL logFlag)
{
	BOOL oldFlag = GetLog();
	if(oldFlag != logFlag) SetStyleIsDifferent();
	m_dwStyleA &= ~CX_LOG_SCALE_MASK;
	m_dwStyleA |= logFlag ? CX_LOG_SCALE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Interrogates the log scaling semaphore defined in m_dwStyleA
//@rdesc TRUE if log scaling flag is set, FALSE if flag is reset
//@see <l Feature masks>, <mf SRGraphStyle::SetLog>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetLog()
{
	return m_dwStyleA & CX_LOG_SCALE_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Initializes the semaphore for use of maximum scale values
//@parm TRUE to use maximum scales
//@rem When set, the display object which owns this style object will use 
//the maximum and minimum scales stored in the m_dMaxRangeY and m_dMinRangeY members.<nl> 
//For display components, the effect depends on the ScaleLimit flag.<nl>  
//If SetScaleLimit(FALSE) and SetUseMaxScale(FALSE), axes are scaled to fit the data values (full autoscaling).<nl> 
//If SetScaleLimit(FALSE) and SetUseMaxScale(TRUE), the axis limits are fixed (no autoscaling).<nl> 
//If SetScaleLimit(TRUE) and SetUseMaxScale(FALSE), axes are autoscaled but the specified range is not exceeded (autoscaling with maximum limits).<nl> 
//If SetScaleLimit(TRUE) and SetUseMaxScale(TRUE), the data range is expanded, if necessary, to the specified limits  (autoscaling with minimum limits).<nl> 
//Autoscaling with minimum limits can be used to avoid the problematic situation which occurs when all the data values have the same value.
//@rdesc void 
//@parm BOOL | style | TRUE to turn the scale limiting on
//@see <l Feature masks>, <mf SRGraphStyle::GetScaleLimit>, <mf SRGraphStyle::SetUseMaxScale>, <md SRGraphStyle::m_dwStyleA>
//@see <l Feature masks>, <mf SRGraphDisplay::GetMaxRangeY>, <mf SRGraphDisplay::GetMinRangeY>, <md SRGraphStyle::m_dwStyleA>
//@devnote For Pie graphs, SetUseMaxScale(TRUE) and SetMinRangeX(dMin) can be used to prevent small wedges (smaller than dMin) from being labeled.
//If dMin is a negative number between 0 and -100, -dMin sets the limit as a percentage of the total pie.
inline void SRGraphStyle::SetUseMaxScale(BOOL style)
{
	m_dwStyleA &= ~CX_MAX_SCALE_MASK;
	m_dwStyleA |= style ? CX_MAX_SCALE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Gets the semaphore which forces SRGraphDisplay objects to lock their scales to a specific range
//@rdesc TRUE if scales are to be locked, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetUseMaxScale>, <md SRGraphDisplay::m_dMaxRangeY>, <md SRGraphStyle::m_dwStyleA>
//@devnote For Pie graphs, SetUseMaxScale(TRUE) and SetMinRangeX(dMin) can be used to prevent small wedges (smaller than dMin) from being labeled.
//If dMin is a negative number between 0 and -100, -dMin sets the limit as a percentage of the total pie.
inline BOOL SRGraphStyle::GetUseMaxScale()
{
	return m_dwStyleA & CX_MAX_SCALE_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore which enables the display of the "empty graph" sign
//@parm TRUE to enable, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::GetUseEmptyGraph>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetUseEmptyGraph(BOOL style)
{
	m_dwStyleA &= ~CX_EMPTY_GRAPH_MASK;
	m_dwStyleA |= style ? CX_EMPTY_GRAPH_MASK : 0;
}


//@doc SRGraphStyle
//@mfunc Gets the semaphore which enables the display of the "empty graph" sign
//@rdesc TRUE if enabled, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetUseEmptyGraph>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetUseEmptyGraph()
{
	return m_dwStyleA & CX_EMPTY_GRAPH_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore which enables the display of numbers on an axis
//@parm TRUE to enable display of numbers, FALSE to disable
//@see <l Feature masks>, <mf SRGraphStyle::SetShowGroups>, <mf SRGraphStyle::SetShowIndices>, <mf SRGraphStyle::GetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowNumerals(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_NUMERALS_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_NUMERALS_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore which enables the display of indices on an axis
//@parm TRUE to enable display of indices, FALSE to disable
//@see <l Feature masks>, <mf SRGraphStyle::SetShowGroups>, <mf SRGraphStyle::GetShowIndices>, <mf SRGraphStyle::SetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowIndices(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_INDICES_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_INDICES_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns the X-axis grid lines on or off
//@rdesc void 
//@parm TRUE to show grid lines, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowXGrid>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowXGrid(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_XGRID_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_XGRID_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns Y-axis grid lines on or off
//@rdesc void 
//@parm TRUE to show grid lines, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowYGrid>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowYGrid(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_YGRID_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_YGRID_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns Z-axis grid lines on or off
//@rdesc void 
//@parm TRUE to show grid lines, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowZGrid>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowZGrid(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_ZGRID_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_ZGRID_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns X-axis tick marks on or off
//@rdesc void 
//@parm TRUE to show tick marks, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowXTicks>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowXTicks(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_XTICKS_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_XTICKS_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns Y-axis tick marks on or off
//@rdesc void 
//@parm TRUE to show tick marks, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowYTicks>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowYTicks(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_YTICKS_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_YTICKS_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns Z-axis tick marks on or off
//@rdesc void 
//@parm TRUE to show tick marks, FALSE to hide
//@see <l Feature masks>, <mf SRGraphStyle::GetShowZTicks>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetShowZTicks(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_ZTICKS_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_ZTICKS_MASK;
}

//@doc SRGraphStyle
//@mfunc Turns value sorting for charts on or off -- allows Manhattan charts (etc) 
//to sort their group order so that groups with a higher average value are displayed toward the back of the chart
//@rdesc void 
//@parm TRUE to sort, FALSE to leave in set order
//@see <l Feature masks>, <mf SRGraphStyle::GetSort>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetSort(BOOL style)
{
	m_dwStyleA &= ~CX_SORT_VALUES_MASK;
	m_dwStyleA |= style ? 0 : CX_SORT_VALUES_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets the order in which grids and data are shown 
//@rdesc void 
//@parm FALSE to show grids on top of data
//@see <l Feature masks>, <mf SRGraphStyle::GetGridOrder>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetGridOrder(BOOL style)
{
	m_dwStyleA &= ~CX_OVERLAY_GRID_MASK;
	m_dwStyleA |= style ? 0 : CX_OVERLAY_GRID_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets or resets the "Always show zero" flag
//@rdesc void 
//@parm When TRUE, axes will always show the zero point
//@see <l Feature masks>, <mf SRGraphStyle::GetAlwaysShowZero>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetAlwaysShowZero(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_ZERO_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_ZERO_MASK;
}

//@doc SRGraphStyle
//@mfunc Locks or unlocks the position of the m_DisplayRect member
//@parm TRUE to lock
//@rem Use this function to override the normal automatic sizing and positioning 
//behavior of the SRGraphDisplay object which owns this style. 
//Using this method, you may exactly define the size and position of the data display 
//portion of the graph and its axes. Note however that labels (etc.) will be drawn outside 
//of this area in the normal fashion. This implies that you are responsible for ensuring 
//that sufficient room is allowed for the external text (etc.). Otherwise cropping of the 
//graphics may occur.
//@see <l Feature masks>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::DRLock(BOOL style)
{
	m_dwStyleA &= ~CX_DISPLAYLOCK_MASK;
	m_dwStyleA |= style ? CX_DISPLAYLOCK_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore which enables the display of groups on an axis
//@parm TRUE to enable display of groups, FALSE to disable.
//@see <l Feature masks>, <mf SRGraphStyle::GetShowGroups>, <mf SRGraphStyle::SetShowIndices>, <mf SRGraphStyle::SetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
//@devnote When this function is used on the style of an <c SRGraphDataList> object the binary flag will signify whether the group is to be seen on the chart or not.<nl>
//Call <mf SRGraphDataList::GetStyle()>->SetShowGroups(FALSE) to turn the group off.
inline void SRGraphStyle::SetShowGroups(BOOL style)
{
	m_dwStyleA &= ~CX_HIDE_GROUPS_MASK;
	m_dwStyleA |= style ? 0 : CX_HIDE_GROUPS_MASK;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore which enables or disables the display of the numeric scale (for example, the Y axis of a classic XY graph) on graph axes
//@rdesc Current setting -- TRUE to display the numeric scale, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::GetShowGroups>, <mf SRGraphStyle::GetShowIndices>, <mf SRGraphStyle::SetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowNumerals()
{
	return m_dwStyleA & CX_HIDE_NUMERALS_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore which enables or disables the display of the groups on graph axes
//@rdesc Current setting -- TRUE to display the groups, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetShowGroups>, <mf SRGraphStyle::GetShowIndices>, <mf SRGraphStyle::GetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
//@devnote When this function is used in te context of a GetGroup() call the binary flag will signify whether the group is to be seen on the chart or not.<nl>
//Call SRGraphDataList::GetStyle()->SetShowGroups(FALSE) to turn the group off.
inline BOOL SRGraphStyle::GetShowGroups()
{
	return m_dwStyleA & CX_HIDE_GROUPS_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore which enables or disables the display of the indices on graph axes
//@rdesc Current setting -- TRUE to display the indices, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::GetShowGroups>, <mf SRGraphStyle::SetShowIndices>, <mf SRGraphStyle::GetShowNumerals>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowIndices()
{
	return m_dwStyleA & CX_HIDE_INDICES_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the X-grid display flag
//@rdesc TRUE if grids are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowXGrid>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowXGrid()
{
	return m_dwStyleA & CX_HIDE_XGRID_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the Y-grid display flag
//@rdesc TRUE if grids are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowYGrid>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowYGrid()
{
	return m_dwStyleA & CX_HIDE_YGRID_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the Z-grid display flag
//@rdesc TRUE if grids are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowZGrid>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowZGrid()
{
	return m_dwStyleA & CX_HIDE_ZGRID_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the "Always show zero" flag
//@rdesc TRUE if the zero should be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetAlwaysShowZero>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetAlwaysShowZero()
{
	return m_dwStyleA & CX_HIDE_ZERO_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the X-axis tick mark display flag
//@rdesc TRUE if ticks are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowXTicks>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowXTicks()
{
	return m_dwStyleA & CX_HIDE_XTICKS_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the Y-axis tick mark display flag
//@rdesc TRUE if ticks are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowYTicks>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowYTicks()
{
	return m_dwStyleA & CX_HIDE_YTICKS_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the Z-axis tick mark display flag
//@rdesc TRUE if ticks are to be shown
//@see <l Feature masks>, <mf SRGraphStyle::SetShowZTicks>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetShowZTicks()
{
	return m_dwStyleA & CX_HIDE_ZTICKS_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the "Sort" flag
//@rdesc TRUE if groups are to be sorted into descending average order
//@see <l Feature masks>, <mf SRGraphStyle::SetSort>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetSort()
{
	return m_dwStyleA & CX_SORT_VALUES_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Returns the grid order flag
//@rdesc FALSE if grids are to overlay data
//@see <l Feature masks>, <mf SRGraphStyle::SetGridOrder>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetGridOrder()
{
	return m_dwStyleA & CX_OVERLAY_GRID_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore which switches legends to either line key display or filled box keys
//@parm TRUE to use a line type legend key, FALSE to use a filled box key
//@see <l Feature masks>, <mf SRGraphStyle::GetLegendLine>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetLegendLine(BOOL style)
{
	m_dwStyleA &= ~CX_LEGEND_LINE_MASK;
	m_dwStyleA |= style ? 0 : CX_LEGEND_LINE_MASK;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore which signifies whether legends are line types or fill types
//@rdesc TRUE for line type, FALSE for filled box type
//@see <l Feature masks>, <mf SRGraphStyle::SetLegendLine>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetLegendLine()
{
	return m_dwStyleA & CX_LEGEND_LINE_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Gets the pen width used for framing objects
//@rdesc Contents of the m_nFrameWidth member
//@see <mf SRGraphStyle::SetFrameWidth> <md SRGraphStyle::m_nFrameWidth>
inline int SRGraphStyle::GetFrameWidth()
{
	return m_nFrameWidth;
}

//@doc SRGraphStyle
//@mfunc Gets the angle used for filling angled vignettes
//@rdesc Contents of the m_dAngle member variable
//@see <mf SRGraphStyle::SetAngle>, <md SRGraphStyle::m_dAngle>
inline double SRGraphStyle::GetAngle()
{
	return m_dAngle;
}

//@doc SRGraphStyle
//@mfunc This function has two contexts. When used in the context of a data item and attached 
//to an SRGraphData or derived object, this function sets the angle for angled vignettes 
//used to fill the interiors of those objects.<nl>
//When used in the context of an SRGraphDisplay or derived object, it may define the angle 
//of tilt of a pie chart etc.
//@parm Angle to set (in degrees)
//@see <mf SRGraphStyle::GetAngle>, <md SRGraphStyle::m_dAngle>
inline void SRGraphStyle::SetAngle(double angle)
{
	m_dAngle=angle;
}

//@doc SRGraphStyle
//@mfunc  Sets or resets the flag that allows overlapping x-labels to be either hidden 
//or moved into a staggered or "tiered" formation
//@parm TRUE to set the x-labels to tiered format
//@see <l Feature masks>, <mf SRGraphStyle::GetTierXLabels>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetTierXLabels(BOOL style)
{
	m_dwStyleA &= ~CX_TIER_XLABELS_MASK;
	m_dwStyleA |= style ? CX_TIER_XLABELS_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Sets or resets the flag that allows overlapping y-labels to be either hidden 
//or moved into a staggered or "tiered" formation
//@parm TRUE to set the y-labels to tiered format
//@see <l Feature masks>, <mf SRGraphStyle::GetTierYLabels>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetTierYLabels(BOOL style)
{
	m_dwStyleA &= ~CX_TIER_YLABELS_MASK;
	m_dwStyleA |= style ? CX_TIER_YLABELS_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Retrieves the flag that defines whether overlapping x-labels should be hidden or moved 
//into a "tiered" format
//@rdesc TRUE if the labels should be moved, otherwise FALSE
//@see <l Feature masks>, <mf SRGraphStyle::SetTierXLabels>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetTierXLabels()
{
	return m_dwStyleA & CX_TIER_XLABELS_MASK;// ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Retrieves the flag that defines whether overlapping y-labels should be hidden or moved 
//into a "tiered" format
//@rdesc TRUE if the labels should be moved, otherwise FALSE.
//@see <l Feature masks>, <mf SRGraphStyle::SetTierYLabels>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetTierYLabels()
{
	return m_dwStyleA & CX_TIER_YLABELS_MASK;// ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Initializes the legend key style
//@parm Legend key style to set
//Note that you have the option of setting a custom style.
//@see <l Legend key styles>, <c SRGraphLegend> <mf SRGraphStyle::GetLegendKeyStyle>, <md SRGraphStyle::m_dwStyleC>
inline void SRGraphStyle::SetLegendKeyStyle(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_KEY_STYLE_MASK;
	m_dwStyleC |= dwStyle & CX_KEY_STYLE_MASK;
}

//@doc SRGraphStyle
//@mfunc Retrieves the legend key style
//@rdesc Current legend key style
//@see <l Legend key styles>, <c SRGraphLegend>, <mf SRGraphStyle::SetLegendKeyStyle>, <md SRGraphStyle::m_dwStyleC>
inline DWORD SRGraphStyle::GetLegendKeyStyle()
{
	 return m_dwStyleC & CX_KEY_STYLE_MASK;
}



//@doc SRGraphStyle
//@mfunc Turns scale limiting on or off 
//@rem When scale limiting is on, the range for autoscaled axes are restricted.<nl>  
//The limits are specified by calling SetMinRangeX(), SetMaxRangeX(), or SetMinRangeY(), SetMaxRangeY().<nl> 
//For display components, the effect depends on the UseMaxScale flag.<nl>  
//If SetScaleLimit(FALSE) and SetUseMaxScale(FALSE), axes are scaled to fit the data values (full autoscaling).<nl> 
//If SetScaleLimit(FALSE) and SetUseMaxScale(TRUE), the axis limits are fixed (no autoscaling).<nl> 
//If SetScaleLimit(TRUE) and SetUseMaxScale(FALSE), axes are autoscaled but the specified limits are not exceeded (autoscaling with maximum limits).<nl> 
//If SetScaleLimit(TRUE) and SetUseMaxScale(TRUE), the data range is expanded, if necessary, to the specified limits  (autoscaling with minimum limits).<nl> 
//Autoscaling with minimum limits can be used to avoid the problematic situation which occurs when all the data values have the same value.
//@rdesc void 
//@parm BOOL | style | TRUE to turn the scale limiting on
//@see <l Feature masks>, <mf SRGraphStyle::GetScaleLimit>, <mf SRGraphStyle::SetUseMaxScale>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetScaleLimit(BOOL style)
{
	m_dwStyleA &= ~CX_SCALE_LIMIT_MASK;
	m_dwStyleA |= style ? CX_SCALE_LIMIT_MASK : 0;
}


//@doc SRGraphStyle
//@mfunc Returns the scale limiting flag 
//@rdesc TRUE signifies that scale limiting is enabled
//@see <l Feature masks>, <mf SRGraphStyle::SetScaleLimit>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetScaleLimit()
{
	return( m_dwStyleA & CX_SCALE_LIMIT_MASK );
}


//@doc SRGraphStyle
//@mfunc Sets the placement of legend keys in front of the legend key text
//@rdesc void 
//@parm BOOL | style | TRUE sets the key in front of the text
//@see <l Feature masks>, <mf SRGraphStyle::GetLegendKeyFirst>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetLegendKeyFirst(BOOL style)
{
	m_dwStyleA &= ~CX_LEGEND_KEYFIRST_MASK;
	m_dwStyleA |= style ? CX_LEGEND_KEYFIRST_MASK : 0;
}



//@doc SRGraphStyle
//@mfunc Returns the legend key position flag
//@rdesc TRUE if legend keys are to be placed before the legend text
//@see <l Feature masks>, <mf SRGraphStyle::SetLegendKeyFirst>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetLegendKeyFirst()
{
	return( m_dwStyleA & CX_LEGEND_KEYFIRST_MASK ) ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the rectangle locking flag for legends
//@rdesc void 
//@parm TRUE to lock the legend rectangle
//@see <l Feature masks>, <mf SRGraphStyle::GetLegendLockRC>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetLegendLockRC(BOOL style)
{
	m_dwStyleA &= ~CX_LEGEND_LOCK_RC_MASK;
	m_dwStyleA |= style ? CX_LEGEND_LOCK_RC_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the legend rectangle locking flag
//@rdesc TRUE if legend rectangles are locked
//@see <l Feature masks>, <mf SRGraphStyle::SetLegendLockRC>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetLegendLockRC()
{
	return( m_dwStyleA & CX_LEGEND_LOCK_RC_MASK );
}

//@doc SRGraphStyle
//@mfunc Sets the number of rows that the legends may use
//@rdesc void 
//@parm int | n | Maximum number of rows
inline void SRGraphStyle::SetLegendRows(int n)
{
	m_dMaxHeight=(double)n;
}

//@doc SRGraphStyle
//@mfunc Returns the DisplayInfoOnly semaphore. For complete details of this semaphore see <mf SRGraphStyle::GetDisplayInfoOnly>
//@rdesc void 
//@parm BOOL style TRUE to turn off label and axis drawing for this display regardless of axis and label style.
inline void SRGraphStyle::SetDisplayInfoOnly(BOOL style)
{
	SetLegendLockRC(style);
}

//@doc SRGraphStyle
//@mfunc NEW 6.01 Returns the Display Info Only semaphore.<nl>
//When a display is set-up to use the new ScaleBar components it may be neccesary to set an axis and label style in a display without actually drawing them.<nl>
//The DisplayInfoOnly semaphore is designed to allow a label and axis style to be set but ignored by the display drawing routines thereby allowing the scale-bar components to do the actual label drawing. 
//Scale bars also control the grid-lines and tick-marks of the display.
//@devnote Be aware that when scale bars are used to draw the grid-lines the data will always be below the lines even if the grid-order is set to show data on top of the lines. This is due to the fact that
// scale bars must be placed on the component list after the display and so the display's draw cycle is already complete by the time the scale-bars are drawn.<nl>
//Note also that this style is context sensitive and shares the semaphore for LegendLockRC which may apply to legends. Generally it would be nonsense to set the DisplayInfoOnly semaphore in a legend or the LegendLockRC semaphore in a display.
//@rdesc inline BOOL 
inline BOOL SRGraphStyle::GetDisplayInfoOnly()
{
	return GetLegendLockRC();
}

//@doc SRGraphStyle
//@mfunc Returns the maximum of rows that legends may use
//@rdesc Maximum number of rows 
inline int SRGraphStyle::GetLegendRows()
{
	return (int)m_dMaxHeight;
}

//@doc SRGraphStyle
//@mfunc Sets the maximum number of legend columns
//@rdesc void 
//@parm int | n | Maximum number of columns that legends may use
inline void SRGraphStyle::SetLegendColumns(int n)
{
	m_dMaxWidth=(double)n;
}

//@doc SRGraphStyle
//@mfunc Returns the maximum number of legend columns
//@rdesc Maximum number of columns 
inline int SRGraphStyle::GetLegendColumns()
{
	return (int)m_dMaxWidth;
}

//@doc SRGraphStyle
//@mfunc Safely sets the deferred drawing flag -- only applies to components of a compound component
//@rdesc void
//@parm BOOL | b | TRUE to defer drawing
inline void SRGraphStyle::SetDeferDraw(BOOL b)
{
	m_dwStyleA &= ~CX_DEFER_DRAW_MASK;
	m_dwStyleA |= b ? CX_DEFER_DRAW_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the deferred drawing flag
//@rdesc TRUE if drawing is to be deferred
inline BOOL SRGraphStyle::GetDeferDraw()
{
	return (m_dwStyleA & CX_DEFER_DRAW_MASK) ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets or resets the automatic orientation flag
//@rem If the automatic orientation flag is FALSE, scales based on SRGDecimalScale will use 
//the explicit orientation and location point rather than 
//calculating orientations that are at 90 degrees to the scale line.
//@rdesc void
//@parm BOOL | b | TRUE to use automatic orientation (default)
//@see <l Feature masks>, <mf SRGraphStyle::GetAutoOrientation>, <md SRGraphStyle::m_dwStyleA>
inline void SRGraphStyle::SetAutoOrientation(BOOL b)
{
	m_dwStyleA &= ~CX_AUTO_ORIENTATION_MASK;
	m_dwStyleA |= b ? 0 : CX_AUTO_ORIENTATION_MASK;
}

//@doc SRGraphStyle
//@mfunc Returns the automatic orientation flag
//@rdesc TRUE if automatic orientation is on (default), otherwise FALSE 
//@see <l Feature masks>, <mf SRGraphStyle::SetAutoOrientation>, <md SRGraphStyle::m_dwStyleA>
inline BOOL SRGraphStyle::GetAutoOrientation()
{
	return (m_dwStyleA & CX_AUTO_ORIENTATION_MASK) ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Sets that flag that signifies whether the X scale is logarithmic or linear
//@rdesc void 
//@parm BOOL  | b | TRUE for a logarithmic X scale
//@see <l Feature masks>, <mf SRGraphStyle::GetLogX>, <md SRGraphStyle::m_dwStyleB>
inline void SRGraphStyle::SetLogX(BOOL b)
{
	BOOL oldFlag = GetLogX();
	if(oldFlag != b) SetStyleIsDifferent();
	m_dwStyleB &= ~CX_LOG_SCALE_X_MASK;
	m_dwStyleB |= b ? CX_LOG_SCALE_X_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore that signifies that logarithmic scale should be used on the X axis.
//@rdesc TRUE if log scale should be used
//@see <l Feature masks>, <mf SRGraphStyle::SetLogX>, <md SRGraphStyle::m_dwStyleB>
inline BOOL SRGraphStyle::GetLogX()
{
	return m_dwStyleB & CX_LOG_SCALE_X_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that signifies that X scales for older SRGraphDisplay types should use 1.01 compatibility mode -- 
//X labels will be shown "top up"
//@parm TRUE if OC 1.01 compatibility mode is to be used
//@rem This is the default mode for Objective Chart 1.1 onward.
//@see <l Feature masks>, <mf SRGraphStyle::GetXLCompatibility>, <md SRGraphStyle::m_dwStyleB>
inline void SRGraphStyle::SetXLCompatibility(BOOL b)
{
	m_dwStyleB &= ~CX_XLCOMP_MASK;
	m_dwStyleB |= b ?  0 : CX_XLCOMP_MASK;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore that signifies that OC 1.01 compatibility mode is in use
//@rdesc TRUE if compatibility mode is being used
//@see <l Feature masks>, <mf SRGraphStyle::SetXLCompatibility>, <md SRGraphStyle::m_dwStyleB>
inline BOOL SRGraphStyle::GetXLCompatibility()
{
	return m_dwStyleB & CX_XLCOMP_MASK ? FALSE : TRUE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that signifies that X and Y scales should be swapped in compound displays
//@parm TRUE if the chart is a "YX" type
//@see <l Feature masks>, <mf SRGraphStyle::GetHgraph>, <md SRGraphStyle::m_dwStyleB>
inline void SRGraphStyle::SetHgraph(BOOL b)
{
	m_dwStyleB &= ~CX_HGRAPH_MASK;
	m_dwStyleB |= b ? CX_HGRAPH_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore that signifies to compound displays that X and Y scales should be swapped
//@rdesc TRUE if scales are to be swapped
//@see <l Feature masks>, <mf SRGraphStyle::SetHgraph>, <md SRGraphStyle::m_dwStyleB>
inline BOOL SRGraphStyle::GetHgraph()
{
	return m_dwStyleB & CX_HGRAPH_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that signifies that points may be skipped to speed up drawing
//@parm TRUE if the points may be culled
//@see <l Feature masks>, <mf SRGraphStyle::GetCull>, <md SRGraphStyle::m_dwStyleB>
inline void SRGraphStyle::SetCull(BOOL b)
{
	m_dwStyleB &= ~CX_CULLPOINTS_MASK;
	m_dwStyleB |= b ? CX_CULLPOINTS_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore that signifies that points will be removed to speed drawing
//@rdesc TRUE if points are to be culled
//@see <l Feature masks>, <mf SRGraphStyle::SetCull>, <md SRGraphStyle::m_dwStyleB>
inline BOOL SRGraphStyle::GetCull()
{
	return m_dwStyleB & CX_CULLPOINTS_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Initializes the semaphore that allows a component with a defined scope to display index labels
// relative to the minimum group for that scope. The default behaviour ensures that this new feature is not
// used unless explicitly requested.
//@rdesc void 
//@parm BOOL b TRUE to allow the use of index annotation from groups other than 0. 
inline void SRGraphStyle::SetRelIndex(BOOL b)
{
	m_dwStyleB &= ~CX_RELINDEX_MASK;
	m_dwStyleB |= b ? CX_RELINDEX_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Returns the semaphore that allows a component with a defined scope to display index labels
// relative to the minimum group for that scope.
//@rdesc BOOL TRUE if the index anotations may be taken from the minimum group.
inline BOOL SRGraphStyle::GetRelIndex()
{
	return m_dwStyleB & CX_RELINDEX_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Set the link tag
//@rdesc inline void 
//@parm BOOL b 
inline void SRGraphStyle::SetLinkTags(BOOL b)
{
	m_dwStyleB &= ~CX_LINKTAGS_MASK;
	m_dwStyleB |= b ? CX_LINKTAGS_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Get the link 
//@rdesc inline BOOL 
inline BOOL SRGraphStyle::GetLinkTags()
{
	return m_dwStyleB & CX_LINKTAGS_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that specifies if scatter charts should use the same scaling factor [x-y units/logical inch] for both x and y axes
//@rdesc void 
//@parm BOOL TRUE to use same scaling factor for both axes
inline void SRGraphStyle::SetUseSameXYScaleFactor(BOOL b)
{
	m_dwStyleA &= ~CX_USE_SAME_XYSCALE_MASK;
	m_dwStyleA |= b ? CX_USE_SAME_XYSCALE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Gets the semaphore that specifies if scatter charts should use the same scaling factor [x-y units/logical inch] for both x and y axes
//@rdesc BOOL TRUE when the same scaling factor is to be used for both axes
inline BOOL SRGraphStyle::GetUseSameXYScaleFactor()
{
	return m_dwStyleA & CX_USE_SAME_XYSCALE_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that signifies that the X scale on scatter charts should be calculated independently of the Y scales. 
//(Not currently used).
//@rdesc void 
//@parm BOOL b TRUE when the axis scaling needs to be calculated independently.
inline void SRGraphStyle::SetUseMaxXScale(BOOL b)
{
	m_dwStyleA &= ~CX_USE_MAX_XSCALE_MASK;
	m_dwStyleA |= b ? CX_USE_MAX_XSCALE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Sets the semaphore that signifies that the X scale on scatter charts should be calculated independently of the Y scales. 
//(Not currently used).
//@rdesc void 
//@parm BOOL b TRUE when the axis scaling needs to be calculated independently.
inline void SRGraphStyle::SetUseMaxYScale(BOOL b)
{
	m_dwStyleA &= ~CX_USE_MAX_YSCALE_MASK;
	m_dwStyleA |= b ? CX_USE_MAX_YSCALE_MASK : 0;
}

//@doc SRGraphStyle
//@mfunc Gets the semaphore that signifies that the X scale on scatter charts should be calculated independently of the Y scales. 
//(Not currently used).
//@rdesc BOOL TRUE if the X scale will be calculated separately.
inline BOOL SRGraphStyle::GetUseMaxXScale()
{
	return m_dwStyleA & CX_USE_MAX_XSCALE_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Gets the semaphore that signifies that the X scale on scatter charts should be calculated independently of the Y scales. 
//(Not currently used).
//@rdesc BOOL TRUE if the Y scale will be calculated separately.
inline BOOL SRGraphStyle::GetUseMaxYScale()
{
	return m_dwStyleA & CX_USE_MAX_YSCALE_MASK ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Initilalizes the tag outline style. Choose from the following;<nl>
//CX_TAG_OUTLINE_NONE      Just the label<nl>  
//CX_TAG_OUTLINE_AUTOMATIC An automatic label (normally a box)<nl>
//CX_TAG_OUTLINE_BOX       A box<nl>
//CX_TAG_OUTLINE_ELLIPSE   An ellipse<nl>
//CX_TAG_OUTLINE_FLASH     A flashy sign like a "sale" notice<nl>
//CX_TAG_OUTLINE_POLYGON   Uses the polygon named by the <mf SRGraphStyle::SetObjectName> function<nl>
//CX_TAG_OUTLINE_CUSTOM    Defines a custom tag style<nl>
//@rdesc inline void 
//@parm DWORD dwStyle
inline void SRGraphStyle::SetTagOutlineStyle(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_TAG_OUTLINE_MASK;
	dwStyle &= CX_TAG_OUTLINE_MASK;
	m_dwStyleC |= dwStyle;
}

//@doc SRGraphStyle
//@mfunc Returns the current tag outline style.
//@rdesc DWORD the style.
inline DWORD SRGraphStyle::GetTagOutlineStyle()
{
	return m_dwStyleC & CX_TAG_OUTLINE_MASK;
}

//@doc SRGraphStyle
//@mfunc Intializes the tag position in relation to the data item being tagged.
//@parm DWORD dwStyle the new style
inline void SRGraphStyle::SetTagPosition(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_TAG_POSITION_MASK;
	dwStyle &= CX_TAG_POSITION_MASK;
	m_dwStyleC |= dwStyle;
}

//@doc SRGraphStyle
//@mfunc Returns the current tag settings.
//@rdesc DWORD the setting
inline DWORD SRGraphStyle::GetTagPosition()
{
	return m_dwStyleC & CX_TAG_POSITION_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets the tag orientation. Note that tags, unlike ordinary labels, may not be set to an arbitrary angle.
//The choices are as follows.<nl>
//CX_TAG_ORIENTATION_ZERO<nl>
//CX_TAG_ORIENTATION_45<nl>
//CX_TAG_ORIENTATION_90<nl>
//CX_TAG_ORIENTATION_135<nl>
//CX_TAG_ORIENTATION_180<nl>
//CX_TAG_ORIENTATION_225<nl>
//CX_TAG_ORIENTATION_270<nl>
//CX_TAG_ORIENTATION_315<nl>
//@parm DWORD dwStyle
inline void SRGraphStyle::SetTagOrientation(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_TAG_ORIENTATION_MASK;
	dwStyle &= CX_TAG_ORIENTATION_MASK;
	m_dwStyleC |= dwStyle;
}

//@doc SRGraphStyle
//@mfunc Returns the current tag orientation.
//@rdesc DWORD one of the tag orientation styles.
inline DWORD SRGraphStyle::GetTagOrientation()
{
	return m_dwStyleC & CX_TAG_ORIENTATION_MASK;
}

//@doc SRGraphStyle
//@mfunc Initializes the tag model used for the chart.
//@parm DWORD One of the following settings.<nl>
//CX_TAG_MODEL_AUTOMATIC  Normally no tag at all
//CX_TAG_MODEL_LOCAL      Tags are handled by a single label object and may not be seriallized.
//CX_TAG_MODEL_PERSISTENT Tags are placed on the component list and may be serialized.
//CX_TAG_MODEL_BLOCKED    Tags are placed in a label block and subjected to anti collision calculations. The label block is also placed on the component list and may be serialized.
inline void SRGraphStyle::SetTagModel(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_TAG_MODEL_MASK;
	dwStyle &= CX_TAG_MODEL_MASK;
	m_dwStyleC |= dwStyle;
}


//@doc SRGraphStyle
//@mfunc Returns the current tag model settings.
//@rdesc DWORD 
inline DWORD SRGraphStyle::GetTagModel()
{
	return m_dwStyleC & CX_TAG_MODEL_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets the tag font to one of these settings.
//CX_TAG_FONT_NORMAL  normally 10 point
//CX_TAG_FONT_SMALL   8 point
//CX_TAG_FONT_LARGE   12 point
//CX_TAG_FONT_CUSTOM  A custom setting.
//@parm DWORD The style
inline void SRGraphStyle::SetTagFontSize(DWORD dwStyle)
{
	m_dwStyleC &= ~CX_TAG_FONT_MASK;
	dwStyle &= CX_TAG_FONT_MASK;
	m_dwStyleC |= dwStyle;
}


//@doc SRGraphStyle
//@mfunc Returns the tag font setting.
//@rdesc DWORD one of the CX_TAG_FONT_xxx settings.
inline DWORD SRGraphStyle::GetTagFontSize()
{
	return m_dwStyleC & CX_TAG_FONT_MASK;
}

//@doc SRGraphStyle
//@mfunc Sets the tag color to the provided value.
//@parm COLORREF c
inline void SRGraphStyle::SetTagColor(COLORREF c)
{
	m_RGBGridColor=c;
}

//@doc SRGraphStyle
//@mfunc Returns the current color setting.
//@rdesc inline COLORREF 
inline COLORREF SRGraphStyle::GetTagColor()
{
   return m_RGBGridColor;
}

//@doc SRGraphStyle
//@mfunc Get the flag of whether the whole bodies of the Bubbles and Vectors should all be drawn inside the view area.
//@rdesc BOOL TRUE if the bubbles and vectors should be drawn inside the view, othersize FALSE.
// The flag only has effect when the maximum object size is NOT set by calling SetUseMaxSize(FALSE).
//@devnote For Pie graphs, GetObjectInsideView() == TRUE to display the labels within the pie.
inline BOOL SRGraphStyle::GetObjectInsideView()
{
	return ((m_dwStyleB & CX_OBJECT_INSIDE_MASK)? TRUE : FALSE);
}

//@doc SRGraphStyle
//@mfunc Set the flag of whether the bubbles and vectors should all be drawn inside the view area
//@rdesc void 
//@parm BOOL bInside TRUE if the whole body is drawn inside the view area, otherwise FALSE. This function
// only has effect when NOT using max object size.
//@devnote For Pie graphs, use SetObjectInsideView(TRUE) to display the labels within the pie.
inline void SRGraphStyle::SetObjectInsideView(BOOL bInside)
{
	m_dwStyleB &= ~CX_OBJECT_INSIDE_MASK;
	m_dwStyleB |= (bInside? CX_OBJECT_INSIDE_MASK : 0);
}  


//@doc SRGraphStyle
//@mfunc Set flag if the line should break when encounter a null value or connect to
// the next available non-null value.
//@rdesc inline void 
//@parm BOOL b TRUE if break on null value, otherwise FALSE
inline void SRGraphStyle::SetBreakLinesOnNull(BOOL b)
{
	m_dwStyleA &= ~CX_BREAK_LINES_ON_NULL;
	m_dwStyleA |= b ? CX_BREAK_LINES_ON_NULL : 0;
}

//@doc SRGraphStyle
//@mfunc Get the flag if the line should break when encounter a null value or to
// connect to the next available non-null value.
//@rdesc inline BOOL TRUE if break on null value, otherwse FALSE
inline BOOL SRGraphStyle::GetBreakLinesOnNull()
{
	return m_dwStyleA & CX_BREAK_LINES_ON_NULL ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Set flag to insert thousand separators (',') in labels created by SRGDecimalScale and its derivatives.
//@rdesc inline void 
//@parm BOOL b TRUE if commas are to be inserted, otherwise FALSE
inline void SRGraphStyle::SetUseThousandSeparator(BOOL b)
{
	m_dwStyleA &= ~CX_BREAK_LINES_ON_NULL;
	m_dwStyleA |= b ? CX_BREAK_LINES_ON_NULL : 0;
}

//@doc SRGraphStyle
//@mfunc Get the flag to insert thousand separators (',') in labels created by SRGDecimalScale and its derivatives.
//@rdesc inline BOOL TRUE if commas are to be inserted, otherwse FALSE
inline BOOL SRGraphStyle::GetUseThousandSeparator()
{
	return m_dwStyleA & CX_BREAK_LINES_ON_NULL ? TRUE : FALSE;
}

//@doc SRGraphStyle
//@mfunc Get the flag to see if the image has already loaded. Used in case of external image filling.
//@rdesc inline BOOL Return TRUE if image has already loaded, otherwise return FALSE
inline BOOL SRGraphStyle::GetImageLoaded()
{
	return (m_dwStyleB & CX_IMAGE_LOADED_MASK)? TRUE:FALSE;
}

//@doc SRGraphStyle
//@mfunc Set the flag to avoid the repeatedly load image when use external image to fill a region
//@rdesc inline void 
//@parm TRUE if the image has already loaded, otherwise FALSE
inline void SRGraphStyle::SetImageLoaded(BOOL b)
{
	m_dwStyleB &= ~CX_IMAGE_LOADED_MASK;
	m_dwStyleB |= (b? CX_IMAGE_LOADED_MASK:0);
}

#endif //__SRGRAPHSTYLE__

#ifndef __SRGRAPHANNOTATION__
#define __SRGRAPHANNOTATION__
/////////////////////////////////////////////////////////////////////////////
// Autoduck help section for SRGraphAnnotation
//@doc SRGraphAnnotation

//@mdata int | SRGraphAnnotation | m_nCode | Country code of the annotation

//@mdata CString | SRGraphAnnotation | m_strAnnotation | Text string of the annotation

//@mfunc  | SRGraphAnnotation | SRGraphAnnotation | Constructor
//@rem Sets the m_nCode variable to the default (01 USA)
//@see <md SRGraphAnnotation::m_nCode>

//adinsert

//$head Annotation management
//$level 1

//@doc SRGraphAnnotation
//@class SRGraphAnnotation |
//This class is the basic storage medium for multi-language annotations for graphs.<nl>
//The m_nCode data member holds an integer which corresponds to the country code of the annotation.<nl>
//The m_strAnnotation data member is a CString object which holds the text in the specific language of the country.<nl>
//For example: <nl>
//m_nCode=01(USA) m_strAnnotation="Annual peanut production world-wide"<nl>
//m_nCode=33(France) m_strAnnotation="Production annuel des cachuettes (mondial)"
//@base public | CObject
class SRGraphAnnotation : public CObject
{
//@access Data members
protected:
	
	// @cmember
	/* Country code corresponding to the international telephone dialing code*/
	int m_nCode; 

	// @cmember
	/* Text associated with this annotation*/
	CString m_strAnnotation;

//@access Member functions
public:
	//@cmember
	/* Default constructor -- initializes the country code to 01 (USA).*/
	inline SRGraphAnnotation(){m_nCode=01;}

	//@cmember
	/* Constructor with code and text initializers*/
	CHART_API SRGraphAnnotation(int code, LPCTSTR text);

	
	CHART_DECLARE_SERIAL(SRGraphAnnotation)
	
	// @cmember
	/* Handles storage and retrieval of the data*/
	CHART_API virtual void Serialize(CArchive& ar);
	
	//@cmember
	/* Queries the country code data member*/
	CHART_API int GetCode();

	//@cmember
	/* Sets the country code data member*/
	CHART_API void SetCode(int code); 
	
	//@cmember
	/* Retrieves the text for this annotation*/
	CString& GetText();  
	
	//@cmember
	/* Stores text in this annotation*/
	CHART_API void SetText(CString s); 

#ifdef _DEBUG
	
	//@cmember
	/* DEBUG ONLY dumps the contents of this object*/
	CHART_API void Dump(CDumpContext& dc) const;
#endif

	// XML formatter for SRGraphAnnotation
	friend class SRGraphAnnotationFTR;
};

#endif //__SRGraphAnnotation__

#ifndef __SRGRAPHANNOTATIONLIST__
#define __SRGRAPHANNOTATIONLIST__

/////////////////////////////////////////////////////////////////////////////
// Autoduck help section for SRGraphAnnotationList
//@doc SRGraphAnnotationList

//@mdata CString  | SRGraphAnnotationList | m_strEmptyString | An empty string

//@mfunc void | SRGraphAnnotationList | SetAnnotation | Sets the default annotation using the text supplied
//@parm LPCTSTR | text | Pointer to the annotation text

//@mfunc  | SRGraphAnnotationList | SRGraphAnnotationList | Constructor

// adinsert AutoDuck insertion point for SRGraphAnnotationList 

//@class The annotation list class manages the multi-lingual annotations for Objective Chart. 
//It handles lists of <c SRGraphAnnotation> objects. <nl>
//Annotation lists allow you to have a single graph with multiple annotations in each element. 
//The graph will note the locale of the computer on which it is being displayed 
//and will use the corresponding entry. The default locale is 01 (USA).
//@base public | CObList
class SRGraphAnnotationList : public CObList
{
//@access Protected data member
protected:
	//@cmember
	/* Always contains a empty string ("")*/
	CString m_strEmptyString; // Always empty

//@access Member functions
public:

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE

	//@cmember
	/* Writes the list of annotations to the template file*/
	CHART_API virtual void WriteList(CStdioFile *file);

#endif

	//@cmember
	/* Retrieves an annotation for a specific code*/
	CHART_API virtual CString& GetAnnotation(int code=1);

	//@cmember
	/* Default constructor*/
	inline SRGraphAnnotationList(){}

	//@cmember
	/* Destructor -- handles cleanup of stored <c SRGraphAnnotation> objects*/
	CHART_API virtual ~SRGraphAnnotationList();

	CHART_DECLARE_SERIAL(SRGraphAnnotationList)

	//@cmember
	/* Serialization */
	CHART_API virtual void Serialize(CArchive &ar);

#ifdef _DEBUG
	//@cmember
	/* Dump this object to a CDumpContext*/
	CHART_API void Dump(CDumpContext &dc) const;
#endif

	//@cmember
	/* Adds an annotation or replaces one with the corresponding country code*/
	CHART_API void SetAnnotation(int code, LPCTSTR text);

	//@cmember
	/* Sets annotation in default locale*/
	CHART_API void SetAnnotation(LPCTSTR text){SetAnnotation(1,text);}

	//@cmember
	/* Deletes all data in a list*/
	CHART_API void KillList(void);
};

#endif //__SRGraphAnnotationList__

//$head Standard data system
//$level 1


#ifndef __SRGRAPHDATA__
#define __SRGRAPHDATA__

/////////////////////////////////////////////////////////////////////////////
// Autoduck help section for SRGraphData
//@doc SRGraphData

//@mdata BOOL | SRGraphData | m_bNULL | Semaphore which signifies that the data in this object 
//is to be considered null or invalid
//@rem When this member is TRUE, the data value should be ignored and treated as being unreliable.

//@mdata CScale | SRGraphData | m_HiLoValue | CScale object which keeps a record of the highest 
//and lowest values ever sent to this data item

//@mdata double | SRGraphData | m_dValue | Current value stored in this data item

//@mdata SRGraphAnnotationList | SRGraphData | m_strAnnotationList | List of multi-language 
//text strings associated with this data item -- may be used to annotate individual items of data

//@mdata SRGraphStyle | SRGraphData | m_Style | Style associated with this data item -- may be 
//used to define the look of the graphic object used to represent the data item

//@mfunc BOOL | SRGraphData | GetNull | Returns the <md SRGraphData::m_bNULL> member

//@mfunc virtual SRGraphAnnotationList * | SRGraphData | GetAnnotationList | Returns a pointer to the annotation list associated with this object

//@mfunc virtual SRGraphAnnotationList * | SRGraphDataList | GetAnnotationList | Returns a pointer to the annotation list

//@mfunc virtual BOOL  | SRGraphData | IsDynamic | Returns FALSE indicating that non-dynamic data storage is being used

//@mfunc virtual CScale * | SRGraphData | GetHiLoValue | Returns a pointer to the CScale member of this data object 

//@mfunc virtual void  | SRGraphData | SetNull | Flags this data object as NULL so that it will be ignored 
//@parm BOOL  | b | TRUE if NULL should be set 

//adinsert

//$head Standard data storage

//@class SRGraphData | Manages one item of data within a graph<nl><nl>
//SRGraphData can be considered as the controller for one node in a chart, one bar on a graph, 
//one slice of a pie chart, etc.<nl>
//Each node has a value member (held in m_Value) and an annotation list (held in m_strAnnotationList).<nl>
//The <c SRGraphAnnotationList> enables a single node to hold many text annotations which are recognized 
//according to a locale-specific code. 
//These annotations may then be used to reproduce graphs for different languages without 
//needing to alter the data itself.
//@devnote The data items now contain a null flag (m_bNull) which may be set to exclude a data item from the display.
//@base public | CObject
class SRGraphData : public CObject
{
//@access Data members
public:
	//@cmember
	/* Accumulated high and low values*/
	CScale m_HiLoValue;

	//@cmember
	/* Floating-point current value of the graph data item*/
	double m_dValue;		

	//@cmember
	/* Manages the multi-lingual annotation list*/
	SRGraphAnnotationList m_strAnnotationList; 

	//@cmember
	/* Style settings for this data object*/
	SRGraphStyle m_Style; 
protected:
	//@cmember
	/* Semaphore -- when TRUE the data held in this item is NULL and should not be used*/
	BOOL m_bNULL;

//@access Member functions
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphData();

	//@cmember
	/* Returns the style of the data item*/
	CHART_API virtual SRGraphStyle * GetStyle();

	//@cmember
	/* Sets the m_bNull member*/
	CHART_API virtual void SetNull(BOOL b);

	//@cmember
	/* Interrogates the m_bNull member*/
	CHART_API virtual BOOL GetNull();
	
	//@cmember
	/* Returns the true logarithmic value for m_value*/
	CHART_API virtual double GetLogValue();
	
	//@cmember
	/* Returns all data to zero and cleans the hi-lo data*/
	CHART_API virtual void Zero();
	
	//@cmember
	/* Returns the hi-lo data value*/
	CHART_API virtual CScale GetHiLoData();

	//@cmember
	/* Returns FALSE because this is not a dynamic data storage object*/
	CHART_API virtual BOOL IsDynamic();

	//@cmember
	/* Retrieves the annotation for this object that is associated with the given country code*/
	CHART_API virtual CString& GetAnnotation(int code=1);

	//@cmember
	/* Retrieves the current value for this data object*/
	CHART_API virtual double GetValue(BOOL bLogData=FALSE);

	//@cmember
	/* Initializes the value for this object*/
	CHART_API virtual void SetValue(double number);

	//@cmember
	/* Constructor with default initialization of the data members*/
	CHART_API SRGraphData();

	//@cmember
	/* Constructor with explicit initialization of data members*/
	CHART_API SRGraphData(double value, CString text, int style=0);

	CHART_DECLARE_SERIAL(SRGraphData)

	//@cmember
	/* Handles storage and retrieval*/
	CHART_API virtual void Serialize(CArchive& ar);
	
	//@cmember
	/* Overload 1. Sets text in an annotation for given country code*/
	CHART_API virtual void SetAnnotation(int code, LPCTSTR text);
	
	//@cmember
	/* Overload 2. Sets text in an annotation -- flexible*/
	CHART_API virtual void SetAnnotation(LPCTSTR text, BOOL clear=FALSE, int code=1);

	//@cmember
	/* Returns a pointer to the annotation list associated with this object*/
	CHART_API virtual SRGraphAnnotationList* GetAnnotationList();

	//@cmember
	/* Returns a pointer to the CScale item (hi-lo history) associated with this object*/
	CHART_API virtual CScale* GetHiLoValue();

#ifdef _DEBUG
	//@cmember
	/* Dumps this object to a CDumpContext*/
	CHART_API void Dump(CDumpContext &dc) const;
#endif

	// XML formatter for SRGraphData
	friend class SRGraphDataFTR;
};

#endif //__SRGraphData__

#ifndef __SRGRAPHDATALIST__
#define __SRGRAPHDATALIST__   

/////////////////////////////////////////////////////////////////////////////
// Autoduck help section for SRGraphDataList
//@doc SRGraphDataList

//@mdata UINT  | SRGraphDataList | m_LastIndex | Last used index in this data list

//@mdata POSITION  | SRGraphDataList | m_LastPos | Last used position in this data list

//@mdata SRGraphStyle  | SRGraphDataList | m_Style | Style information which may globally affect the styles of all data items in the list

//@mdata SRGraphAnnotationList  | SRGraphDataList | m_strAnnotationList | Annotations for this data list, group header

//@mdata BOOL  | SRGraphDataList | m_bDynamic | Set TRUE when this list holds a single dynamic data object (SRGraphDynamic Data) instead of a list of individual non-dynamic objects (SRGraphData)

//@mfunc virtual BOOL  | SRGraphDataList | IsDynamic | Interrogates the m_bDynamic member

//@mfunc virtual SRGraphData * | SRGraphDataList | GetIndex | Returns the requested SRGraphData object, possibly making the list grow if it is too short
//@parm int | index | the index
//@parm BOOL | GrowList | "true" if the list to grow, otherwise false (set to "true" by default)
	
//adinsert

//$head Standard data storage
//$level 1

//@class SRGraphDataList | Holds a linked list of <c SRGraphData> objects<nl>
//This class is the top level data store for the <c SRGraph> class. The m_strAnnotation member of this class 
//effectively names the graph.
//@ex For example: |
//		SRGraphDataList <nl>
//			m_strAnnotation (01),("January 1996") <nl>
//		SRGraphData <nl>
//			m_Value 50,000 <nl>
//			m_Annotation (01),("Capital expenditure") <nl>
//		SRGraphData <nl>
//			m_Value 17,000 <nl>
//			m_Annotation (01),("Wages") <nl>
//		SRGraphData <nl>
//			m_Value 77,000 <nl>
//			m_Annotation (01),("Gross Income") <nl>
//		SRGraphData <nl>
//			m_Value 10,000 <nl>
//			m_Annotation (01),("Profit") <nl>
//
//
//@base public | CObList
class SRGraphDataList : public CObList
{
	//@access Public data members
public:
	//@cmember
	/* Style information which may globally affect the styles of the whole list*/
	SRGraphStyle m_Style;

	//@cmember
	/* Annotations for this data list*/
	SRGraphAnnotationList m_strAnnotationList;

	//@access Member functions
public:
	//@cmember
	/* Returns the data item count*/
	CHART_API virtual int GetDataCount();

	//@cmember
	/* Creates a new data object and adds it to the list*/
	CHART_API virtual SRGraphData * NewIndex();

	//@cmember
	/* Places a (already created) SRGraphData or derived object into the list*/
	CHART_API virtual POSITION SetIndex(SRGraphData *pData,int nIndex=-1);

	//@cmember
	/* Rolls a data set forwards or backwards*/
	CHART_API virtual void Roll(double dValue,BOOL bDirection=FALSE);

	//@cmember
	/* Returns a pointer to the annotation list*/
	CHART_API virtual SRGraphAnnotationList * GetAnnotationList();

	//@cmember
	/* Returns a pointer to this object's style member*/
	CHART_API virtual SRGraphStyle * GetStyle();

	//@cmember
	/* Sets or resets the dynamic chart flag*/
	CHART_API virtual void SetDynamic(BOOL b=TRUE);

	//@cmember
	/* Default constructor*/
	CHART_API SRGraphDataList();

	//@cmember
	/* Constructor with annotation initialization*/
	SRGraphDataList(LPCTSTR text,int code=01);

	//@cmember
	/* Destructor -- cleans up stored objects*/
	CHART_API virtual ~SRGraphDataList();

	//@cmember
	/* Retrieves annotations for this list -- used to fetch group headers*/
	CHART_API virtual CString& GetAnnotation(int code=1);

	CHART_DECLARE_SERIAL(SRGraphDataList)

	//@cmember
	/* Handles storage and retrieval of the data*/
	CHART_API virtual void Serialize(CArchive &ar);

	//@cmember
	/* Overload 1. Sets text in an annotation*/
	CHART_API void SetAnnotation(int code, LPCTSTR text);
	
	//@cmember
	/* Overload 2. Sets text in an annotation*/
	CHART_API void SetAnnotation(LPCTSTR text, BOOL clear=FALSE, int code=1);

	//@cmember
	/* Returns the requested SRGraphData object, possibly making the list grow if it is too short*/
	CHART_API virtual SRGraphData * GetIndex(int index,BOOL GrowList=TRUE);

	//@cmember
	/* Marks the position of the last index accessed as invalid*/
	CHART_API virtual void InvalidateIndexPosition();

	//@cmember
	/* Interrogates the m_bDynamic member*/
	inline virtual BOOL IsDynamic(){return m_bDynamic;}

#ifdef _DEBUG
	//@cmember
	/* Dumps the contents of this object to a CDumpContext*/
	CHART_API void Dump(CDumpContext &) const;
#endif

//@access Protected data members
protected:
	//@cmember
	/* Last index for the speed-up code*/
	UINT m_LastIndex;
	//@cmember
	/* Last position for the speed-up code*/
	POSITION m_LastPos;
	//@cmember
	/* Set TRUE when this list holds a single dynamic data object instead of a list of individual non-dynamic objects*/
	BOOL m_bDynamic;

	// XML formatter for SRGraphDataList
	friend class SRGraphDataListFTR;
};

#endif //__SRGraphDataList__

#ifndef __SRGRAPHDYNAMICDATA__
#define __SRGRAPHDYNAMICDATA__
//@doc SRGraphDynamicData

//@type SRGDataBuffer | This union contains the various values which may be contained in 
//dynamic data objects.
typedef union _TAG_SRGDATABUFFER {
	_TCHAR c;	//@field A character
	int n;		//@field An integer
	double d;	//@field A double precision floating point value
} SRGDataBuffer;

//@enum SRGD_TYPES | The type of data being used in a dynamic data object
enum SRGD_TYPES {
	SRGD_NONE,	//@emem No data has been entered.
	SRGD_DOUBLE,//@emem The first data used was a double.
	SRGD_INT,	//@emem The first data used was an int.
	SRGD_CHAR	//@emem The first data used was a char.
};

/////////////////////////////////////////
// Autoduck comment block for SRGraphDynamicData
//@doc SRGraphDynamicData

//@mdata CScale* | SRGraphDynamicData | m_HiLoBuffer | Points to a buffer containing CScale objects -- one for every data item<nl>
//This buffer is only initialized if the m_bHiLo semaphore is set.

//@mdata BOOL | SRGraphDynamicData | m_bHiLo | When TRUE this semaphore signifies that hi-lo history gathering is required<nl>
//A buffer for the CScale objects will be allocated automatically.
//@see <md SRGraphDynamicData::m_HiLoBuffer> <mf SRGraphDynamicData::SetHiLoFunction>

//@mdata int | SRGraphDynamicData | m_nDataType | Data type currently being used<nl>
//So that raw information can be quickly stored without conversion to a double, 
//the object keeps a record of the first data type used. If data of a different type is used, 
//an exception will be thrown.
//@see <c SRGraphException> 

//@mdata UINT | SRGraphDynamicData | m_nGrowSize | Size (in SRGDataBuffers) by which the buffer should grow in case of an overflow
//@see <mf SRGraphDynamicData::SetGrowSize> <mf SRGraphDynamicData::SetValue>

//@mdata BOOL | SRGraphDynamicData | m_bCyclic | When TRUE any potential overflow of the input or output indices resets the relevant index to zero. 
//This allows repeated filling of the fixed length buffer.
//@see <mf SRGraphDynamicData::SetCyclic>

//@mdata BOOL | SRGraphDynamicData | m_bReady |	Set to TRUE by the object after a successful 
//initialization -- also tells the object to delete the buffers on destruction. 
//Reset it at your peril.

//@mdata UINT | SRGraphDynamicData | m_nBufferSize | Size (in SRGDataBuffers) of the buffer

//@mdata UINT | SRGraphDynamicData | m_nOutIndex | Index within the buffer from which data and hi-lo information is taken<nl>
//When a data item is accessed, this index is automatically incremented to the next position 
//in the buffer. Overflow behavior depends on the settings of <md SRGraphDynamicData::m_nGrowSize> 
//and <md SRGraphDynamicData::m_bCyclic>.

//@mdata UINT | SRGraphDynamicData | m_nInIndex | Index into which data is placed within the 
//data buffer.  When the data item is accessed, this index is automatically incremented to 
//the next position in the buffer. Overflow behavior depends on the settings of 
//<md SRGraphDynamicData::m_nGrowSize> and <md SRGraphDynamicData::m_bCyclic>.

//@mdata SRGDataBuffer* | SRGraphDynamicData | m_pBuffer | Pointer to a block of SRGraphDatabuffer structures which contain the data

//@mfunc virtual BOOL  | SRGraphDynamicData | IsDynamic |  Returns TRUE because this is a dynamic data storage object 

//@mdata UINT | SRGraphDynamicData | m_nMaxValid | Number of initialized data items = highest initialized index+1
	
//@mdata CString | SRGraphDynamicData | m_str | A handy string

//adinsert

//$head Dynamic data storage

////////////////////////////////////////////////////////////////

//@doc SRGraphDynamicData
//@class Manages the storage and manipulation of dynamic information in various formats<nl>
//The dynamic data buffer is an array of SRGDataBuffer unions.
class SRGraphDynamicData : public SRGraphData
{
//@access Public member functions
public:
	CHART_API virtual BOOL GetNull();
	//@cmember
	/* Rolls dynamic data by shifting the memory blocks by one space*/
	CHART_API virtual void Roll(double dValue=0.0,BOOL bDirection=FALSE);
	//@cmember
	/* Enables cycling of the buffer indices*/
	CHART_API virtual void SetCyclic(BOOL b=TRUE);
	//@cmember
	/* Interrogates the CScale object attached to a particular value*/
	CHART_API virtual CScale GetHiLoData();
	//@cmember
	/* Positions the input pointer within the buffer*/
	CHART_API virtual BOOL SetInputPointer(UINT index);
	//@cmember
	/* Sets the input pointer to zero*/
	CHART_API virtual void ResetInputPointer();
	//@cmember
	/* Check validity of input pointer and grow the buffer if necessary and allowed*/
	CHART_API virtual BOOL CheckInPointer();
	//@cmember
	/* Returns the current input pointer*/
	CHART_API virtual UINT GetInputPointer();
	//@cmember
	/* Positions the output pointer within the buffer*/
	CHART_API virtual BOOL SetOutputPointer(UINT index);
	//@cmember
	/* Resets the output pointer to zero*/
	CHART_API virtual void ResetOutputPointer();
	//@cmember
	/* Returns the current output pointer*/
	CHART_API virtual UINT GetOutputPointer();
	//@cmember
	/* Determines whether the hi-lo gathering is enabled*/
	CHART_API virtual BOOL GetHiLoFunction();
	//@cmember
	/* Enables or disables the hi-lo gathering feature*/
	CHART_API virtual void SetHiLoFunction(BOOL b=TRUE);
	//@cmember
	/* Returns a value from the buffer -- the logarithmic value is available on request*/
	CHART_API virtual double GetValue(BOOL bLogData=FALSE);
	//@cmember
	/* Return the annotation for the buffer -- commonly overridden to supply text dependent on current index*/
	CHART_API virtual CString& GetAnnotation(int code);
	//@cmember
	/* Interrogates the BufferSize member*/
	CHART_API virtual UINT GetBufferSize();
	//@cmember
	/* Interrogates the GrowSize member*/
	CHART_API virtual UINT GetGrowSize();
	//@cmember
	/* Initializes the GrowSize member*/
	CHART_API virtual void SetGrowSize(UINT size);
	//@cmember
	/* Constructor*/
	CHART_API SRGraphDynamicData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphDynamicData();
	//@cmember
	/* Returns TRUE because this is a dynamic data storage object*/
	CHART_API virtual BOOL IsDynamic();
	//@cmember
	/* Allocates or re-allocates a data buffer*/
	CHART_API virtual void SetBufferSize(UINT nSize);
	//@cmember
	/* Places a char value into the buffer*/
	CHART_API virtual void SetValue(_TCHAR value);
	//@cmember
	/* Places an integer value into the buffer*/
	CHART_API virtual void SetValue(int value);
	//@cmember
	/* Places a double precision floating point value into the buffer*/
	CHART_API virtual void SetValue(double value);
	//@cmember
	/* Returns the number of data items that have been initialized with SetValue()*/
	CHART_API virtual UINT GetHighestValidIndex();


	CHART_DECLARE_SERIAL(SRGraphDynamicData);

	//@cmember
	/* Manages storage and retrieval of this object*/
	CHART_API virtual void Serialize(CArchive &ar);

//@access Protected data members
protected:
	//@cmember
	/* Pointer to a block of CScale objects*/
	CScale* m_HiLoBuffer;
	//@cmember
	/* Flag that signifies if hi-lo history gathering is required*/
	BOOL m_bHiLo;
	//@cmember
	/* Type of data (int,char or double) that this object stores*/
	int m_nDataType;
	//@cmember
	/* Size by which the buffer grows in case of overflow*/
	UINT m_nGrowSize;
	//@cmember
	/* TRUE if the buffer remains a fixed size and pointers recycle to the beginning*/
	BOOL m_bCyclic;
	//@cmember
	/* TRUE if this object has been properly initialized with a data buffer*/
	BOOL m_bReady;
	//@cmember
	/* Number of SRGDataBuffers in storage*/
	UINT m_nBufferSize;
	//@cmember
	/* Index of the output pointer*/
	UINT m_nOutIndex;
	//@cmember
	/* Index of the input pointer*/
	UINT m_nInIndex;
	//@cmember
	/* Number of initialized data items = highest initialized index+1*/
	UINT m_nMaxValid;
	//@cmember
	/* A handy string*/
	CString m_str;
	//@cmember
	/* Pointer to the stored data*/
	SRGDataBuffer* m_pBuffer;	

	// XML formatter for SRGraphDynamicData
	friend class SRGraphDynamicDataFTR;
};

#endif //__SRGRAPHDYNAMICDATA__

// Reset DLL declaration context

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

