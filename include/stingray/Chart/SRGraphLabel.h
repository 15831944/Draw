///////////////////////////////////////////////////////////////////////////////
// SRGraphLabel.h
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
//@doc SRGraphLabel
//@module SRGraphLabel.h|  definition of the graph label class<nl>
//Written by Bob Powell (www.roguewave.com)

#ifndef __SRGRAPHLABEL__
#define __SRGRAPHLABEL__

#include <math.h>
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphLabel
//
//@doc SRGraphLabel

//@mdata int | SRGraphLabel | m_nLocationPoint | Point at which a label will be anchored<nl>
//This is not the same as the text position. A label may be fixed to its screen position 
//by any one of nine points. See the overview for this class for details.

//@mdata SRGraphAnnotationList | SRGraphLabel | m_Labels | Multi-language annotation list which holds the text for this label
//@rem As with other SRGraphComponent-based objects, the SRGraphLabel may display different 
//text according to the user-defined locale parameter (country code).

//@mdata BOOL  | SRGraphLabel | m_bBlockMember | Designates this label as part of a label block when TRUE

//@mdata SRGraphLabelBlock *  | SRGraphLabel | m_pLabelBlock | Pointer to the parent label block -- only valid if m_bBlockMember is TRUE

//@mdata CPoint  | SRGraphLabel | m_TextPosition | Screen coordinate of the location point

//@mdata double  | SRGraphLabel | m_dPosY | Device independent Y coordinate

//@mdata double  | SRGraphLabel | m_dPosX | Device independent X coordinate

//@mdata BOOL  | SRGraphLabel | m_bVectorStandard | Semaphore signifying that the vector is 0, 90, 180 or 270 degrees

//@mdata BOOL  | SRGraphLabel | m_bLabelStandard | Semaphore signifying that the label is oriented to 0, 90, 180 or 270 degrees

//@mdata BOOL  | SRGraphLabel | m_bMoveable | Determines the motility of this label -- may move when TRUE (unimplemented)

//@mdata double  | SRGraphLabel | m_dVectorX | Direction (-1 to 1) in which the X-axis label can move

//@mdata double  | SRGraphLabel | m_dVectorY | Direction (-1 to 1) in which the Y-axis label can move

//@mdata BOOL  | SRGraphLabel | m_bUseLocalFont | Designates use of the font description local to this label when TRUE

//@mfunc void | SRGraphLabel | SetTextPosition | Sets the text position (in pixels) of the label
//@parm int | x | X position in pixels
//@parm int | y | Y position in pixels

//@mfunc void | SRGraphLabel | SetTextPosition | Sets the text position of the label
//@parm CPoint | point | containing the position in pixels

//@mfunc double | SRGraphLabel | GetTextPosX |Retrieves the device independent X position of this label
//@rdesc Floating point X coordinate

//@mfunc double | SRGraphLabel | GetTextPosY |Retrieves the device independent Y position of this label
//@rdesc Floating point Y coordinate

//@doc SRGraphLabel
//@mfunc inline void  | SRGraphLabel | SetPointCount | Initializes the number of points in the boundary polygon 
//@parm int  | v | The number of points (normally 5 or more) 

//@doc SRGraphLabel
//@mfunc inline int  | SRGraphLabel | GetPointCount | Returns the number of points in the label boundary polygon.

//@doc SRGraphLabel
//@mfunc inline void  | SRGraphLabel | SetOutline | Initializes the outline to be used to frame this label.
//@parm CPoint *  | v | A pointer to a list of CPoint objects which describe the polygon.

//@doc SRGraphLabel
//@mfunc inline CPoint * | SRGraphLabel | GetOutline | Returns the pointe to the CPoints which describe the outline of this label. 

//@doc SRGraphLabel
//@mdata BOOL  | SRGraphLabel | m_bPolyValid | TRUE if the currently stored polygon is valid.

//@doc SRGraphLabel
//@mdata CPoint *  | SRGraphLabel | m_pOutline | Points to the list of CPoint objects that describe the outline drawn around the label.

//@doc SRGraphLabel
//@mdata int  | SRGraphLabel | m_nPointCount | The number of points in the polygon that describes the outline of the label.

//adinsert

//$head Component classes
//$level 1

//@doc SRGraphLabel
//@class Displays labels on graphs and charts in various orientations and without overlapping 
//other labels
//@base public | SRGraphTitle
class SRGraphLabel : public SRGraphTitle
{
//@access protected data members
protected:
	//@cmember
	/* TRUE if the polygon describing the outline of the label is valid */
	BOOL m_bPolyValid;
	//@cmember
	/* The pointer to the list of CPoint objects that describe the outline of the label */
	CPoint * m_pOutline;
	//@cmember
	/* The number of points in the polygon that describes the outline of the label */
	int m_nPointCount;
	//@cmember
	/* Draws the text of the label*/
	//@cmember
	/* Device independent Y coordinate*/
	double m_dPosY;
	//@cmember
	/* Device independent X coordinate*/
	double m_dPosX;
	//@cmember
	/* Semaphore signifying that the vector is 0, 90, 180 or 270 degrees*/
	BOOL m_bVectorStandard;
	//@cmember
	/* Semaphore signifying that the label is oriented to 0, 90, 180 or 270 degrees*/
	BOOL m_bLabelStandard;
	//@cmember
	/* Determines the motility of this label -- may move when TRUE (unimplemented)*/
	BOOL m_bMoveable;
	//@cmember
	/* Direction (-1 to 1) in which the X-axis label can move*/
	double m_dVectorX;
	//@cmember
	/* Direction (-1 to 1) in which the Y-axis label can move*/
	double m_dVectorY;
	//@cmember
	/* Location point code*/
	int m_nLocationPoint;
	//@cmember
	/* Pointer to the parent label block -- only valid if m_bBlockMember is TRUE*/
	SRGraphLabelBlock* m_pLabelBlock;
	//@cmember
	/* Designates this label as part of a label block when TRUE*/
	BOOL m_bBlockMember;
	//@cmember
	/* Designates use of the font description local to this label when TRUE*/
	BOOL m_bUseLocalFont;
	//@cmember
	/* Screen coordinate of the location point*/
	CPoint m_TextPosition;
	//@cmember
	/* Annotation list containing the coded labels*/
	SRGraphAnnotationList m_Labels;

//@access public data members
public:

	// Note: LocationPoints are arranged so that you may access this list
	// by dividing the number of degrees by 45 to give a relevant outer edge point.

	//@cmember,menum
	/* Label location and rotation points (VertHoriz)*/
	enum LocationPoints {
		MidLeft,		//@@emem MidLeft=0
		TopLeft,		//@@emem TopLeft=1
		TopCenter,		//@@emem TopCenter=2
		TopRight,		//@@emem TopRight=3
		MidRight,		//@@emem MidRight=4
		BottomRight,	//@@emem BottomRight=5
		BottomCenter,	//@@emem BottomCenter=6
		BottomLeft,		//@@emem BottomLeft=7
		MidCenter		//@@emem MidCenter=8
	} ;


	//@cmember,menum
	/* Standard vectors by which a label may move<nl>*/
	//These are converted to their sine and cosine equivalents before being stored.
	enum LabelVectors {
		VectorUp,	 //@@emem Label moves up (x=0, y=-1)
		VectorLeft,	 //@@emem Label moves left (x=-1, y=0)
		VectorRight, //@@emem Label moves right (x=1, y=0)
		VectorDown,	 //@@emem Label moves down (x=0, y=1)
		VectorCustom //@@emem Label moves in some other durection
	} ;

	//@cmember,menum
	/* Standard label orientations (measurements in degrees)*/
	enum LabelStandards {
		Normal,		//@@emem Normal = 0	
		Upward,		//@@emem Upward = 90
		Inverted,	//@@emem Inverted = 180
		Downward,	//@@emem Downward = 270
		Angled		//@@emem Some value other than the four above
	} ;


//@access Public member functions
public:

	//@cmember
	/* Custom override to determine font size used on tags */
	CHART_API virtual int GetCustomTagFontSize();
	//@cmember
	/* Sets the number of points used on the label's bounding polygon */
	inline void SetPointCount(int v){m_nPointCount=v;}
	//@cmember
	/* Returns the number of points used on the label's bounding polygon */
	inline int GetPointCount(){return m_nPointCount;}
	//@cmember
	/* Initialaizes the list of CPoint objects used to describe the labels bounding polygon */
	inline void SetOutline(CPoint * v){m_pOutline=v;}
	//@cmember
	/* Returns the list of CPoint objects used to describe the labels bounding polygon */
	inline CPoint * GetOutline(){return m_pOutline;}
	//@cmember
	/* Removes all points from the labels bounding polygon */
	CHART_API virtual void CleanBoundingPolygon();
	//@cmember
	/* Copies and converts tag styles from label styles where needed */
	CHART_API virtual void ConvertDataStyle(SRGraphStyle *pStyle);
	//@cmember
	/* Returns the size of tick marks*/
	CHART_API virtual double GetTickSize();
	//@cmember
	/* Returns the size of the X-margin. Used by axis scales for label offset*/
	CHART_API virtual double GetXMargin();
	//@cmember
	/* Returns the size of the Y-margin -- not used for labels*/
	CHART_API virtual double GetYMargin();

	//@cmember
	/* Returns the text size*/
	CHART_API virtual int GetFontSize();
	//@cmember
	/* Sets the text size for this label*/
	CHART_API virtual void SetFontSize(double dSize);
	//@cmember
	/* Calculates the text size in pixels*/
	CHART_API virtual int CalcFontAutoSize();

	//@cmember
	/* Returns the logical (device dependent) rectangle enclosing this label -- CRect(0,0,0,0) if not available*/
	CHART_API virtual CRect GetLogRect();

	//attributes
	//@cmember
	/* Constructor*/
	CHART_API SRGraphLabel();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphLabel();

	CHART_DECLARE_SERIAL(SRGraphLabel);

//operations
	//@cmember
	/* Sets text X position*/
	CHART_API virtual void SetTextPosX(double dPosX);
	//@cmember
	/* Sets text Y position*/
	CHART_API virtual void SetTextPosY(double dPosY);
	//@cmember
	/* Returns text Y position*/
	inline double GetTextPosY(){	return m_dPosY;}

	//@cmember
	/* Returns text Y position*/
	inline double GetTextPosX(){	return m_dPosX;}

	//@cmember
	/* Sets the device independent position for the text*/
	CHART_API virtual void SetTextPosition(double dXPos,double dYPos);

	//@cmember,mfunc
	/* Retrieves the annotation list for external access*/
	inline SRGraphAnnotationList* GetAnnotationList(){return &m_Labels;}

	//@cmember
	/* Calculates the pixel position from the device independent position*/
	CHART_API void CalcPos();

	//@cmember,mfunc
	/* Returns the text associated with this label*/
	CHART_API virtual CString& GetAnnotation(int code=1);

	//@cmember,mfunc
	/* Returns a pointer to this object's parent block*/
	inline SRGraphLabelBlock* GetLabelBlock(){return m_pLabelBlock;}

	//@cmember
	/* Returns a pointer to the graph that owns this object*/
	CHART_API virtual SRGraph * GetParent();

	//@cmember
	/* Returns the width and height of the label in pixels*/
	CHART_API virtual CSize GetLabelSize();

	//@cmember
	/* Returns the text color*/
	CHART_API virtual COLORREF GetTextColor();

	//@cmember,mfunc
	/* Returns the m_bLabelStandard semaphore*/
	inline BOOL GetLabelStandard(){return m_bLabelStandard;}

	//@cmember
	/* Saves or restores this object via the archive*/
	CHART_API virtual void Serialize(CArchive &ar);

	//@cmember,mfunc
	/* Initializes the pointer to the parent block.*/
	inline void SetLabelBlock(SRGraphLabelBlock *block){m_pLabelBlock=block;}

	//@cmember
	/* Returns the m_bDrawing semaphore -- TRUE if drawing is possible*/
	CHART_API virtual BOOL IsDrawing();

	//@cmember
	/* Returns the pointer to the CWnd being used to draw the object*/
	CHART_API virtual CWnd * GetpCWnd();

	// @ cmember
	/* Returns the pointer to the CDC being used to draw the object*/
//	CDC* GetpDC();

	//@cmember
	/* Initializes the vector along which the label will move to avoid other labels*/
	CHART_API void SetVector(double dAngle);
	//@cmember,mfunc
	/* Initializes the vector along which the label will move to avoid other labels*/
	inline void SetVector(double x,double y){m_dVectorX=x; m_dVectorY=y; m_bVectorStandard=FALSE;}
	//@cmember,mfunc
	/* Returns the X anti-collision vector*/
	inline double GetVectorX(){return m_dVectorX;}
	//@cmember,mfunc
	/* Returns the Y anti-collision vector*/
	inline double GetVectorY(){return m_dVectorY;}

        //@cmember,mfunc
	/* Initializes the angle at which the label is displayed*/	
	CHART_API void SetOrientation(double o);
	//@cmember,mfunc
	/* Returns the angle at which the label is displayed*/
	inline double GetOrientation(){return GetStyle()->GetZAngle();}

	//@cmember,mfunc
	/* Initializes the point at which the text is to be anchored*/
	inline void SetLocationPoint(int p){m_nLocationPoint=p;}
	//@cmember,mfunc
	/* Returns the point to which the text is to be anchored*/
	inline int GetLocationPoint(){return m_nLocationPoint;}

	//@cmember
	/* Returns a CRgn object which covers the area that the text occupies*/
	CHART_API virtual CRgn* GetBoundingRegion();
 	//@cmember
 	/* Returns an array of points describing the area outline that the text occupies*/
	CHART_API virtual void GetBoundingPolygon(CPoint *points=NULL,int nPointCount=5);

	//@cmember
	/* Determines the point at which text must be output to place it in the desired position*/
	CHART_API virtual CPoint GetTextOrigin();

	//@cmember,mfunc
	/* Returns the coordinates of the label's location point*/
	CHART_API virtual CPoint GetTextPosition();

	//@cmember
	/* Sets the position of the label's location point*/
	inline void SetTextPosition(CPoint p)
	{
		m_dPosX=(double)p.x;
		m_dPosY=(double)p.y;
		m_TextPosition=p;
	}

	//@cmember
	/* Sets the position of the label's location point*/
	inline void SetTextPosition(int x,int y)
	{
		SetTextPosition(CPoint(x,y));
	}

	//@cmember
	/* Orients a label according to a standard code*/
	CHART_API virtual void SetLabelStandard(int nLabelStandard);
	//@cmember
	/* Sets the label vector to a standard direction using a predefined code*/
	CHART_API virtual void SetVector(int nVectorCode);

	//@cmember
	/* Returns the font used to display this label*/
	CHART_API virtual CFont* GetFont();

	//@cmember
	/* Returns a pointer to the style object*/
	CHART_API virtual SRGraphStyle* GetStyle();

	//@cmember
	/* Sets the text of the label*/
	CHART_API virtual void SetAnnotation(int code,LPCTSTR strText);
	//@cmember
	/* Sets the text of the label*/
	CHART_API virtual void SetAnnotation(LPCTSTR strText);

	//@cmember,mfunc
	/* Designates whether this label is a member of a block of labels*/
	inline void SetBlockMember(BOOL b){m_bBlockMember=b;}
	//@cmember,mfunc
	/* Determines if this label is a member of a block of labels*/
	inline BOOL GetBlockMember(){return m_bBlockMember;}

	//@cmember,mfunc
	/* Designates whether this label manages its own font*/
	inline void SetUseLocalFont(BOOL b){m_bUseLocalFont=b;}
	//@cmember,mfunc
	/* Determines if this label manages its own font*/
	inline BOOL GetUseLocalFont(){return m_bUseLocalFont;}

	//@cmember
	/* Initializes the font using the supplied LOGFONT structure*/
	CHART_API virtual void SetLogFont(LOGFONT * v);

	//@cmember
	/* Refreshes font information before drawing*/
	CHART_API virtual BOOL UpdateFont();

	//@cmember,mfunc
	/* Overridden to prevent the labels from performing the base class behavior - does nothing*/
	CHART_API virtual void GetParentContent();

	//@cmember
	/* User extension function to allow you to define your own fill routine for this label*/
	CHART_API virtual void DrawCustomLabelFill();
	//@cmember
	/* User extension function to allow you to define your own border drawing routine for this label*/
	CHART_API virtual void DrawCustomLabelBorder();
	//@cmember
	/* User extension function to allow you to define your own shadow drawing routine for this label*/
	CHART_API virtual void DrawCustomLabelShadow();

	//@cmember
	/* Main drawing function for this label*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pWnd);

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Reads a template line for chart labels*/
	CHART_API virtual int ReadTemplateLine(LPCTSTR line);

	//@cmember
	/* Writes label details to the template*/
	CHART_API virtual void WriteSpecificParameters(CStdioFile * file);

	//@cmember
	/* Writes the object name to the template*/
	CHART_API virtual void WriteName(CStdioFile * file);
#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE


protected:
	CHART_API virtual void DrawForeground();		// Overridden to draw foreground text
	//@cmember
	/* Fills the background of this label*/
	CHART_API virtual void DrawFill();			// overrides from the basic component
	//@cmember
	/* Draws the border around the label*/
	CHART_API virtual void DrawBorder();
	//@cmember
	/* Draws the shadow under the label*/
	CHART_API virtual void DrawShadow();

	// XML Formatter for SRGraphLabel
	friend class SRGraphLabelFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SRGRAPHLABEL__

