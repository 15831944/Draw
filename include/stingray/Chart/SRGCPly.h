///////////////////////////////////////////////////////////////////////////////
// SRGPly.h
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
//@doc SRGCompoundDisplay
//@module SRGCply.h | SRGCompiledPolygon class declaration file<nl>
//Includes SRGCoordinate class<nl>
//Written by Bob Powell (www.roguewave.com)

//$head Utility classes
//$level 1
#ifndef __SRGCOMPILEDPOLYGON__
#define __SRGCOMPILEDPOLYGON__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////
// Autoduck comment block for SRGCoordinate

//@mdata float | SRGCoordinate | x | Floating point X coordinate value

//@mdata float | SRGCoordinate | y | Floating point Y coordinate value

//@mfunc 	| SRGCoordinate |SRGCoordinate | Initializing constructor -- Sets X and Y to 0

//@mfunc 	| SRGCoordinate |~SRGCoordinate | Destructor

//@mfunc 	void | SRGCoordinate | SetX | Sets the floating point X coordinate

//@mfunc 	void | SRGCoordinate | SetX | Sets the floating point X coordinate from a double

//@mfunc 	void | SRGCoordinate | SetX | Sets the floating point X coordinate from an integer

//@mfunc 	float | SRGCoordinate | GetX | Returns the floating point X coordinate

//@mfunc 	void | SRGCoordinate | SetY | Sets the floating point Y coordinate

//@mfunc 	void | SRGCoordinate | SetY | Sets the floating point Y coordinate from a double

//@mfunc 	void | SRGCoordinate | SetY | Sets the floating point Y coordinate from an integer

//@mfunc 	float | SRGCoordinate | GetY | Returns the floating point Y coordinate

//@class SRGCoordinate | Manages a single floating point coordinate pair -- used for scaleable polygons
class SRGCoordinate
{
//@access public data members
public:

	//@cmember
	/* X coordinate*/
	float x;
	//@cmember
	/* Y coordinate*/
	float y;

//@access public member functions
public:
	//@cmember
	/* Initializing constructor -- sets X and Y to 0*/
	inline SRGCoordinate(){x=y=0.0f;}
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGCoordinate();
	//@cmember
	/* Sets the floating point X coordinate*/
	CHART_API virtual void SetX(float f);
	//@cmember
	/* Sets the floating point X coordinate*/
	CHART_API virtual void SetX(double f);
	//@cmember
	/* Sets the floating point X coordinate*/
	CHART_API virtual void SetX(int f);
	//@cmember
	/* Returns the floating point X coordinate*/
	CHART_API virtual float GetX();
	//@cmember
	/* Sets the floating point Y coordinate*/
	CHART_API virtual void SetY(float f);
	//@cmember
	/* Sets the floating point Y coordinate*/
	CHART_API virtual void SetY(double f);
	//@cmember
	/* Sets the floating point Y coordinate*/
	CHART_API virtual void SetY(int f);
	//@cmember
	/* Returns the floating point Y coordinate*/
	CHART_API virtual float GetY();
};


//////////////////////////////////////////////////////
//  Autoduck comment block for SRGCompiledPolygon
//
//@doc SRGCompiledPolygon

//@mdata CString | SRGCompiledPolygon | m_strName | Name of the polygon

//@mdata LPPOINT | SRGCompiledPolygon | m_pPoints | Pointer to the list of CPoints which is 
//generated by compiling the floating point coodinates

//@mdata int | SRGCompiledPolygon | m_nCount | Number of CPoint objects in the list pointed to by m_pPoints<nl>
//Note that this may be different from the number of points in the floating point coordinate list.

//@mdata CPtrList | SRGCompiledPolygon | m_Coords | Linked list of SRGCoordinate objects -- 
//one for each point in the polygon<nl>
//By storing the coordinates as floating point data, the scaling and positioning of graphic 
//shapes may be carried out with great accuracy.

//@mdata BOOL | SRGCompiledPolygon | m_bDirty | Indicates that the floating point list must be recompiled<nl>
//As floating point coordinates are added to the list, the integer CPoint list will become out of date. 

//@mfunc int | SRGCompiledPolygon | GetCount | Returns the number of points or SRGCoordinates used to describe this polygon

//@doc SRGCompiledPolygon
//@mdata double  | SRGCompiledPolygon | m_dScaleY | The Y scale of the polygon, normally 1.0

//@doc SRGCompiledPolygon
//@mdata double  | SRGCompiledPolygon | m_dScaleX | The X scale of the polygon. Normally 1.0

//@doc SRGCompiledPolygon
//@mdata BOOL  | SRGCompiledPolygon | m_bRotated | Set to TRUE if that polygon is to be rotated.

//@doc SRGCompiledPolygon
//@mdata double  | SRGCompiledPolygon | m_dRotation | The angle, in degrees, to which the polygon should be rotated.

//@doc SRGCompiledPolygon
//@mfunc virtual void  | SRGCompiledPolygon | SetScaleY | Sets the Y scale of the polygon 
//@parm double  | v | The relative scale: 1.0 for 1:1 scale, less than 1 for smaller, greater than 1 for bigger

//@doc SRGCompiledPolygon
//@mfunc virtual double  | SRGCompiledPolygon | GetScaleY | Returns the Y scale of the polygon. 

//@doc SRGCompiledPolygon
//@mfunc virtual void  | SRGCompiledPolygon | SetScaleX | Sets the X scale of the polygon 
//@parm double  | v | The relative scale: 1.0 for 1:1 scale, less than 1 for smaller, greater than 1 for bigger

//@doc SRGCompiledPolygon
//@mfunc virtual double  | SRGCompiledPolygon | GetScaleX | Returns the current polygon X scale. 

//@doc SRGCompiledPolygon
//@mfunc virtual void  | SRGCompiledPolygon | SetRotated | Sets the rotation semaphore 
//@parm BOOL  | v | TRUE to signify rotation. 

//@doc SRGCompiledPolygon
//@mfunc virtual BOOL  | SRGCompiledPolygon | GetRotated | Gets the rotation semaphore 

//@doc SRGCompiledPolygon
//@mfunc virtual void  | SRGCompiledPolygon | SetRotation | Sets the number of degrees of rotation 
//@parm double  | v | Rotation angle in degrees. 

//@doc SRGCompiledPolygon
//@mfunc virtual double  | SRGCompiledPolygon | GetRotation | Gets the number of degrees of rotation 

//adinsert

//@topic SRGCompiledPolygon Class Overview |
//This class manages a polygon which is stored as a list of floating point coordinates. When needed the floting point list is compiled into an integer list with scalingm rotation and offset already applied.

//@class Manages a single scaleable polygon object
//@devnote When repeated movement, scaling, or other operations are carried 
//out on polygons, the coordinates may become degraded through small computational 
//inaccuraccies and the polygon may become malformed. By keeping a pristine floating point 
//"master list" of points and generating a compiled CPoint-list polygon from the master every time 
//an operation takes place, the polygon will always be an accurate representation of the original.
class SRGCompiledPolygon : public CObject
{
//@access protected data members
protected:
	//@cmember
	/* The Y scaling factor*/
	double m_dScaleY;
	//@cmember
	/* The X scaling factor*/
	double m_dScaleX;
	//@cmember
	/* The rotation semaphore*/
	BOOL m_bRotated;
	//@cmember
	/* The angle of rotation.*/
	double m_dRotation;
	//@cmember
	/* Assigns or reassigns required memory*/
	CHART_API virtual void AssignPointBlock();
	//@cmember
	/* Name of the polygon or wiget*/
	CString m_strName;
	//@cmember
	/* List of CPoint points*/
	LPPOINT m_pPoints;
	//@cmember
	/* Number of points in the integer polygon*/
	int m_nCount;
	//@cmember
	/* List of the floating point coordinates*/
	CPtrList m_Coords;
	//@cmember
	/* Semaphore indicating that the polygon should be recompiled */
	BOOL m_bDirty;
	
//@access public member functions
public:
	//@cmember
	/* Initialises the Y scaling factor*/
	CHART_API virtual void SetScaleY(double v);
	//@cmember
	/* Gets the Y scaling factor*/
	CHART_API virtual double GetScaleY();
	//@cmember
	/* Initialises the X scaling factor*/
	CHART_API virtual void SetScaleX(double v);
	//@cmember
	/* Gets the X scaling factor*/
	CHART_API virtual double GetScaleX();
	//@cmember
	/* Sets the rotation semaphore*/
	CHART_API virtual void SetRotated(BOOL v);
	//@cmember
	/* Gets the rotation semaphore*/
	CHART_API virtual BOOL GetRotated();
	//@cmember
	/* Sets the rotation angle*/
	CHART_API virtual void SetRotation(double v);
	//@cmember
	/* Gets the rotation angle*/
	CHART_API virtual double GetRotation();
	//@cmember
	/* Gets the	number of CPoints in the list.*/
	CHART_API int GetIntegerPointCount();
	//@cmember
	/* Adds points to create a circle with (nPoints) nodes.*/
	CHART_API virtual void AddCirclePoints(int nPoints);
	//@cmember
	/* Constructs a polygon with a stock shape.*/
	CHART_API SRGCompiledPolygon(int nPrimitive);
	//@cmember
	/* Sets the rotation to the specified angle.*/
	CHART_API virtual void RotatePoints(double dDegrees,LPRECT pRect=NULL);
	//@cmember
	/* Converts the floating point list into a CPoint list which is scaled to fit neatly into the desired rectangle*/
	CHART_API virtual LPPOINT GetFittedPoints(CRect &r);
	//@cmember
	/* Generates a CPoint list to be an integer representation of the floating point list with X and Y offsets added*/
	CHART_API virtual void OffsetPolygon(float xo,float yo);
	//@cmember
	/* Returns the name of this polygon*/
	CHART_API virtual CString & GetName();
	//@cmember
	/* Initializes the name of this polygon*/
	CHART_API virtual void SetName(LPCTSTR name);
	//@cmember
	/* Constructor*/
	CHART_API SRGCompiledPolygon();
	//@cmember
	/* Virtual Destructor*/
	CHART_API virtual ~SRGCompiledPolygon();
	//@cmember
	/* Returns a pointer to the integer (compiled) point block*/
	CHART_API virtual LPPOINT GetPoints();
	//@cmember
	/* Adds a floating point coordinate pair to the list*/
	CHART_API virtual void AddCoord(SRGCoordinate *c);
	//@cmember
	/* Adds a coordinate pair using floats*/
	CHART_API virtual void AddCoord(float xc,float yc);
	//@cmember
	/* Adds a coordinate pair using integers*/
	CHART_API virtual void AddCoord(int nx,int ny);
	//@cmember
	/* Returns the number of points in the floating point list*/
	CHART_API virtual int GetCount();
};

// Reset DLL declaration context

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif
