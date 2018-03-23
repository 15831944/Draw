///////////////////////////////////////////////////////////////////////////////
// SRGbck.h
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
//@doc SRGraphFeedback
//@module SRGFbck.h | SRGraphFeedback header file<nl>
//Written by Bob Powell (www.roguewave.com)

////////////////////////////////////////////////////////////////
//
// SRGFbck.h: Declaration of the SRGraphFeedback class
//
////////////////////////////////////////////////////////////////
#ifndef __FEEDBACK__
#define __FEEDBACK__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//@doc SRGraphFeedback

//@mdata CRgn * | SRGraphFeedback | m_polygonRegion | Polygonal region which outlines the data

//@mdata CRect | SRGraphFeedback | m_BoundingRect | Bounding rectangle for the polygonal region (not currently used)

//@mdata int | SRGraphFeedback | m_nGroup | Group to which the data defined by the region belongs

//@mdata int | SRGraphFeedback | m_nIndex | Index in which the data defined by the region is stored

//@mdata SRGraph * | SRGraphFeedback | m_pParentGraph | Pointer to the SRGraph object that owns this feedback object

//@mfunc virtual CRgn * | SRGraphFeedback | GetPolygonRegion | Returns a pointer the feedback region

//@doc SRGraphFeedback
//@mdata int  | SRGraphFeedback | m_nRadius | NEW for 6.0. Feedback may now use a point and radius combination to define the hot spot. This variable defines the radius from the point stored in m_FeedbackPoint which specfies the hot area.

//@doc SRGraphFeedback
//@mdata CPoint  | SRGraphFeedback | m_FeedbackPoint | NEW 6.0 Feedback may now use a point / radius combination to define the hot spot for feedback. This variable stores the point upon which the hot spot is centered.

//@doc SRGraphFeedback
//@mdata CRect  | SRGraphFeedback | m_rFeedbackRect | NEW 6.0 Feedback may now use a rectangular area defined in this variable to create the hot spot for feedback as an alternative to the older region based system.

//@doc SRGraphFeedback
//@mdata int  | SRGraphFeedback | m_nFeedbackType | NEW 6.0 The type of feedback used. This may be one of Point, Rectangle or Region.<nl>

#ifndef _OCCE_
//@doc SRGraphFeedback
//@mfunc virtual CRgn * | SRGraphFeedback | GetPolygonRegion | Returns a pointer to the CRgn defining the feedback area
#endif //_OCCE_

// adinsert

//$head Chart feedback
//$level 1

//@doc SRGraphFeedback
//@class A list of SRGraphFeedback objects stores "hot" areas which can be used to 
//associate a screen area with the data displayed in it.<nl>
//When a graphic object like a bar or graph data point is drawn, the outline of that 
//object is stored in an SRGraphFeedback object as a CRgn (GDI region object), CRect, or CPoint with radius along
//with the group and index of the associated data item.<nl>
//An hit-test routine can then use this list to determine which data item, if any, is 
//associated with the screen location of the mouse cursor.
//@base public | CObject
class SRGraphFeedback : public CObject
{
public:
	//@cmember
	/* Returns the index of the data item attached to this feedback object*/
	CHART_API int GetnIndex();
	//@cmember
	/* Returns the group of the data item attached to this feedback object*/
	CHART_API virtual int GetnGroup();
	//@cmember
	/* Constructor*/
	CHART_API SRGraphFeedback();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphFeedback();

#ifndef _OCCE_
		//@cmember
	/* Constructor with initialization*/
	CHART_API SRGraphFeedback(LPPOINT points,int PointCount,int group,int index,SRGraph *Parent);

#endif //_OCCE_

	//@cmember
	/* Performs hit testing for the coordinates supplied in X and Y*/
	CHART_API BOOL ptInFeedback(int x,int y);

// Attributes
public:
	//@cmember
	/* Creates a feedback item that uses a point and radius combination instead of the normal region */
	CHART_API SRGraphFeedback(CPoint p,int nRadius, int group, int index, SRGraph *pParent);
	//@cmember
	/* Creates a feedback item that uses a rectangle instead of the normal region */
	CHART_API SRGraphFeedback(CRect r,int group,int index, SRGraph *pParent);

	//@cmember
	/* Index associated with this hot area*/
	int m_nIndex;
	//@cmember
	/* Group associated with this hot area*/
	int m_nGroup;
	//@cmember
	/* Pointer to the SRGraph object which owns this object*/
	SRGraph * m_pParentGraph;


	// public accessors of protected data members
#ifndef _OCCE_
	//@cmember
	/* Returns a pointer the feedback region */
	inline virtual CRgn* GetPolygonRegion(){return m_polygonRegion;}
#endif //_OCCE_
	
	//@cmember
	/* Returns the feedback point */
	CHART_API virtual CPoint GetFeedbackPoint();

	//@cmember
	/* Returns the radius of the circle around the feedback point */
	CHART_API virtual int GetRadius();

	//@cmember
	/* Returns a pointer the feedback rectangle */
	CHART_API virtual CRect GetFeedbackRect();

	//@cmember
	/* Returns a flag indicating the type of feedback area used -- point(2), rectangle(1), or region(0) */
	CHART_API virtual int GetFeedbackType();

protected:

#ifndef _OCCE_
	//@cmember
	/* Region which defines the on-screen feedback area*/
	CRgn* m_polygonRegion;
#endif //_OCCE_

	//@cmember
	/* NEW 6.0 Feedback radius from a point */
	int m_nRadius;

	//@cmember
	/* NEW 6.0 feedback may use points as well as regions */
	CPoint m_FeedbackPoint;

	//@cmember
	/* NEW 6.0 Feedback may use rectangles as well as regions */
	CRect m_rFeedbackRect;

	//@cmember
	/* The type of feedback used -- point(2), rectangle(1), or region(0) */
	int m_nFeedbackType;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__FEEDBACK__
