///////////////////////////////////////////////////////////////////////////////
// SRGZoom.h
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
//@doc SRGZoom
//@module SRGZoom.h | SRGZoom header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SRGZoom.h: interface for the SRGZoom class
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#if !defined(AFX_SRGZOOM_H_INCLUDED_)
#define AFX_SRGZOOM_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGZoom 
//@doc SRGZoom

//@mfunc void  | SRGZoom | SetMinY | Initializes the minimum Y value 
//@parm double  | v | New minimum Y value 

//@mfunc double  | SRGZoom | GetMinY | Retrieves the minimum Y value

//@mfunc void  | SRGZoom | SetMaxY | Initializes the maximum Y value 
//@parm double  | v | New maximum Y value

//@mfunc double  | SRGZoom | GetMaxY | Retrieves the maximum Y value 

//@mfunc void  | SRGZoom | SetMinX | Initializes the minimum X value 
//@parm double  | v | New minimum X value  

//@mfunc double  | SRGZoom | GetMinX | Retrieves the minimum X value 

//@mfunc void  | SRGZoom | SetMaxX | Initializes the maximum X value 
//@parm double  | v | New maximum X value 

//@mfunc double  | SRGZoom | GetMaxX | Retrieves the maximum X value 

//@mfunc void  | SRGZoom | SetMinZ | Initializes the minimum Z value 
//@parm double  | v | New minimum Z value 

//@mfunc double  | SRGZoom | GetMinZ | Retrieves the minimum Z value 

//@mfunc void  | SRGZoom | SetMaxZ | Initializes the maximum Z value 
//@parm double  | v | New maximum Z value 

//@mfunc double  | SRGZoom | GetMaxZ | Retrieves the maximum Z value 

//@mfunc void  | SRGZoom | SetYZoom | Sets the Y zoom semaphore 
//@parm BOOL  | v | TRUE if the Y zoom values are to be used, FALSE if they should be ignored

//@mfunc BOOL  | SRGZoom | GetYZoom | Retrieves the Y zoom semaphore 

//@mfunc void  | SRGZoom | SetXZoom | Sets the X zoom semaphore 
//@parm BOOL  | v | TRUE if the X zoom values are to be used, FALSE if they should be ignored

//@mfunc BOOL  | SRGZoom | GetXZoom | Retrieves the X zoom semaphore 

//@mfunc void  | SRGZoom | SetZZoom | Sets the Z zoom semaphore 
//@parm BOOL  | v | TRUE if the Z zoom values are to be used, FALSE if they should be ignored

//@mfunc BOOL  | SRGZoom | GetZZoom | Retrieves the Z zoom semaphore 

//@mfunc void  | SRGZoom | SetMinGroup | Initializes the minimum group in scope 
//@parm int  | v | New minimum group 

//@mfunc int  | SRGZoom | GetMinGroup | Retrieves the minimum group in scope 

//@mfunc void  | SRGZoom | SetMaxGroup | Initializes the maximum group in scope 
//@parm int  | v | New maximum group 

//@mfunc int  | SRGZoom | GetMaxGroup | Retrieves the maximum group in scope 

//@mfunc void  | SRGZoom | SetMinIndex | Initializes the minimum index in scope 
//@parm int  | v | New minimum index 

//@mfunc int  | SRGZoom | GetMinIndex | Retrieves the minimum index in scope 

//@mfunc void  | SRGZoom | SetMaxIndex | Initializes the maximum index in scope 
//@parm int  | v | New maximum index

//@mfunc int  | SRGZoom | GetMaxIndex | Retrieves the maximum index in scope 

//@mdata double  | SRGZoom | m_dMinY | Minimum Y value for the current zoom

//@mdata double  | SRGZoom | m_dMaxY | Maximum Y value for the current zoom

//@mdata double  | SRGZoom | m_dMinX | Minimum X value for the current zoom

//@mdata double  | SRGZoom | m_dMaxX | Maximum X value for the current zoom

//@mdata double  | SRGZoom | m_dMinZ | Minimum Z value for the current zoom 

//@mdata double  | SRGZoom | m_dMaxZ | Maximum Z value for the current zoom

//@mdata BOOL  | SRGZoom | m_bYZoom | TRUE if the Y values are to be used, FALSE if the Y values are ignored

//@doc SRGZoom
//@mdata BOOL  | SRGZoom | m_bXZoom | TRUE if the X values are to be used, FALSE if the X values are ignored

//@doc SRGZoom
//@mdata BOOL  | SRGZoom | m_bZZoom | TRUE if the Z values are to be used, FALSE if the Z values are ignored

//@doc SRGZoom
//@mdata int  | SRGZoom | m_nMinGroup | Minimum group number in scope

//@doc SRGZoom
//@mdata int  | SRGZoom | m_nMaxGroup | Maximum group number in scope

//@doc SRGZoom
//@mdata int  | SRGZoom | m_nMinIndex | Minimum index number in scope

//@doc SRGZoom
//@mdata int  | SRGZoom | m_nMaxIndex | Maximum index number in scope

//@doc SRGZoom
//@mfunc void  | SRGZoom | SetScaleZ | Set the Z scale
//@parm CScale  | v | The z-scale


//@doc SRGZoom
//@mfunc CScale  | SRGZoom | GetScaleZ | Return the Z scale CScale object.


//@doc SRGZoom
//@mfunc void  | SRGZoom | SetScaleY | Set the Y scale
//@parm CScale  | v | The y-scale


//@doc SRGZoom
//@mfunc CScale  | SRGZoom | GetScaleY | Return the Y scale CScale object


//@doc SRGZoom
//@mfunc void  | SRGZoom | SetScaleX | Set the X scale
//@parm CScale  | v | The x-scale


//@doc SRGZoom
//@mfunc CScale  | SRGZoom | GetScaleX | Return the X scale CScale object
 

//@doc SRGZoom
//@mfunc void  | SRGZoom | SetDisplayIndex | Set the integer index of the display used when displays overlap.
//@parm int  | v | the value


//@doc SRGZoom
//@mfunc int  | SRGZoom | GetDisplayIndex | Returns the index of the overlapping display that caused this zoom


//@doc SRGZoom
//@mfunc void  | SRGZoom | SetGraph | Sets a pointer to the SRGraph object that owns this zoom object
//@parm SRGraph *  | v | The pointer to the graph.

//@doc SRGZoom
//@mfunc SRGraph *  | SRGZoom | GetGraph | Retrieves the pointer to the SRGraph object that owns this zoom object.


//@doc SRGZoom
//@mdata CScale  | SRGZoom | m_ScaleZ | The Z scale

//@doc SRGZoom
//@mdata CScale  | SRGZoom | m_ScaleY | The Y scale

//@doc SRGZoom
//@mdata CScale  | SRGZoom | m_ScaleX | The X scale

//@doc SRGZoom
//@mdata int  | SRGZoom | m_nDisplayIndex | The index of the display that initiated this zoom.

//@doc SRGZoom
//@mdata SRGraph *  | SRGZoom | m_pGraph | The pointer to the parent graph.

// adinsert AutoDuck insertion point for SRGZoom 
//$head Utility classes
//$level 1

//@doc SRGZoom 
//@topic SRGZoom Class Overview |
//The SRGZoom class keeps zoom levels for the SRGraphView and SRGScrollView classes. 
//It is used to implement a full zoom-in and zoom-out system.

//@class The SRGZoom class keeps zoom levels for the SRGraphView and SRGScrollView classes. 
//It is used to implement a full zoom-in and zoom-out system.
//@base public | CObject
class SRGZoom : public CObject  
{
public:
	//@cmember
	/* Set the Z scale */
	inline  void SetScaleZ(CScale v){m_ScaleZ=v;}
	//@cmember
	/* Get the Z scale */
	inline CScale GetScaleZ(){return m_ScaleZ;}
	//@cmember
	/* Set the Y scale */
	inline void SetScaleY(CScale v){m_ScaleY=v;}
	//@cmember
	/* Get the Y scale */
	inline CScale GetScaleY(){return m_ScaleY;}
	//@cmember
	/* Set the X scale */
	inline void SetScaleX(CScale v){m_ScaleX=v;}
	//@cmember
	/* Get the X scale */
	inline CScale GetScaleX(){return m_ScaleX;}
	//@cmember
	/* Set the display index */
	inline void SetDisplayIndex(int v){m_nDisplayIndex=v;}
	//@cmember
	/* Get the display index */
	inline int GetDisplayIndex(){return m_nDisplayIndex;}
	//@cmember
	/* Set the parent graph */
	inline void SetGraph(SRGraph * v){m_pGraph=v;}
	//@cmember
	/* Get the parent graph */
	inline SRGraph * GetGraph(){return m_pGraph;}
	//@cmember
	/* Default constructor*/
	CHART_API SRGZoom();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGZoom();
	//@cmember
	/* Initializes the minimum Y value*/
	inline void SetMinY(double v){m_dMinY=v;}
	//@cmember
	/* Retrieves the minimum Y value*/
	inline double GetMinY(){return m_dMinY;}
	//@cmember
	/* Initializes the maximum Y value*/
	inline void SetMaxY(double v){m_dMaxY=v;}
	//@cmember
	/* Retrieves the maximum Y value*/
	inline double GetMaxY(){return m_dMaxY;}
	//@cmember
	/* Initializes the minimum X value*/
	inline void SetMinX(double v){m_dMinX=v;}
	//@cmember
	/* Retrieves the minimum X value*/
	inline double GetMinX(){return m_dMinX;}
	//@cmember
	/* Initializes the maximum X value*/
	inline void SetMaxX(double v){m_dMaxX=v;}
	//@cmember
	/* Retrieves the maximum X value*/
	inline double GetMaxX(){return m_dMaxX;}
	//@cmember
	/* Initializes the minimum Z value*/
	inline void SetMinZ(double v){m_dMinZ=v;}
	//@cmember
	/* Retrieves the minimum Z value*/
	inline double GetMinZ(){return m_dMinZ;}
	//@cmember
	/* Initializes the maximum Z value*/
	inline void SetMaxZ(double v){m_dMaxZ=v;}
	//@cmember
	/* Retrieves the maximum Z value*/
	inline double GetMaxZ(){return m_dMaxZ;}
	//@cmember
	/* Initializes the Y zoom level semaphore*/
	inline void SetYZoom(BOOL v){m_bYZoom=v;}
	//@cmember
	/* Retrieves the Y zoom level semaphore*/
	inline BOOL GetYZoom(){return m_bYZoom;}
	//@cmember
	/* Initializes the X zoom level semaphore*/
	inline void SetXZoom(BOOL v){m_bXZoom=v;}
	//@cmember
	/* Retrieves the X zoom level semaphore*/
	inline BOOL GetXZoom(){return m_bXZoom;}
	//@cmember
	/* Initializes the Z zoom level semaphore*/
	inline void SetZZoom(BOOL v){m_bZZoom=v;}
	//@cmember
	/* Retrieves the Z zoom level semaphore*/
	inline BOOL GetZZoom(){return m_bZZoom;}
	//@cmember
	/* Sets the minimum group in scope*/
	inline void SetMinGroup(int v){m_nMinGroup=v;}
	//@cmember
	/* Retrieves the minimum group in scope*/
	inline int GetMinGroup(){return m_nMinGroup;}
	//@cmember
	/* Sets the minimum group in scope*/
	inline void SetMaxGroup(int v){m_nMaxGroup=v;}
	//@cmember
	/* Retrieves the maximum group in scope*/
	inline int GetMaxGroup(){return m_nMaxGroup;}
	//@cmember
	/* Sets the minimum index in scope*/
	inline void SetMinIndex(int v){m_nMinIndex=v;}
	//@cmember
	/* Retrieves the minimum index in scope*/
	inline int GetMinIndex(){return m_nMinIndex;}
	//@cmember
	/* Sets the maximum index in scope*/
	inline void SetMaxIndex(int v){m_nMaxIndex=v;}
	//@cmember
	/* Retrieves the maximum index in scope*/
	inline int GetMaxIndex(){return m_nMaxIndex;}

protected:
	//@cmember
	/* The Z scale */
	CScale m_ScaleZ;
	//@cmember
	/* The Y scale */
	CScale m_ScaleY;
	//@cmember
	/* The X scale */
	CScale m_ScaleX;
	//@cmember
	/* The display index */
	int m_nDisplayIndex;
	//@cmember
	/* The pointer to the parent graph. */
	SRGraph * m_pGraph;
		//@cmember
		/* Minimum Y value*/
	double m_dMinY;
		//@cmember
		/* Maximum Y value*/
	double m_dMaxY;
		//@cmember
		/* Minimum X value*/
	double m_dMinX;
		//@cmember
		/* Maximum X value	*/
	double m_dMaxX;
		//@cmember
		/* Minimum Z value*/
	double m_dMinZ;
		//@cmember
		/* Maximum Z value*/
	double m_dMaxZ;
		//@cmember
		/* Y zoom level semaphore*/
	BOOL m_bYZoom;
		//@cmember
		/* X zoom level semaphore*/
	BOOL m_bXZoom;
		//@cmember
		/* Z zoom level semaphore*/
	BOOL m_bZZoom;
		//@cmember
		/* Minimum group in scope*/
	int m_nMinGroup;
		//@cmember
		/*  Maximum group in scope*/
	int m_nMaxGroup;
		//@cmember
		/*  Minimum index in scope*/
	int m_nMinIndex;
		//@cmember
		/*  Maximum index in scope*/
	int m_nMaxIndex;
};
#endif // !defined(AFX_SRGZOOM_H_INCLUDED_)

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

