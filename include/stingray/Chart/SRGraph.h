///////////////////////////////////////////////////////////////////////////////
// SRGraph.h
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
//@doc SRGraph
//@module SRGraph.h | SRGraph header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SRGraph.h: interface for the SRGraph class
//
/////////////////////////////////////////////////////////////////

#ifndef __SRGRAPH__
#define __SRGRAPH__

#include <afxtempl.h>	
#include "SRGDat.h"
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

//////////////////////////////////////////////////////
// Autoduck help file entries for SRGraph

//@doc SRGraph

//@mfunc BOOL | SRGraph | IsBackgroundDraw | Interrogates the m_bBackgroundDraw member
//@see <mf SRGraph::SetBackgroundDraw> <md SRGraph::m_bBackgroundDraw>

//@mfunc BOOL | SRGraph | IsFeedbackLogging | Interrogates the m_bFeedbackLogging member
//@see <mf SRGraph::SetFeedbackLogging>, <md SRGraph::m_bFeedbackLogging>

//@mfunc void | SRGraph | SetBackgroundDraw | Initializes the m_BackgroundDraw member
//@parm BOOL | bBDraw | TRUE to enable background drawing, FALSE to disable

//@mfunc void | SRGraph | SetFeedbackLogging | Initializes the m_bFeedbackLogging member
//@parm BOOL | bLogging | TRUE to enable feedback logging, FALSE to disable
//@rem When drawing a graph, a list of feedback items may be created. Each feedback item contains 
//information about a data item and its appearance on screen. When the mouse button is clicked or 
//moves over a "hot" area, the feedback list can determine the group and index of the data associated with the area.
//@see <c SRGraphFeedback>, <md SRGraph::m_FeedbackList>

//@mdata BOOL | SRGraph | m_bIsEmpty | TRUE if this graph holds no data, otherwise FALSE

//@mdata BOOL | SRGraph | m_bSignificantChange | TRUE after a <mf SRGraph::SetSignificantChanges> command
//@rem The signficant change system allows the graph to process data faster by only updating items 
//when they have changed. All of the components in the component list look at their own 
//significant change flag before the draw cycle commences. If the flag is TRUE, the component 
//completely redraws all of its elements and updates all of its labels.

//@mdata BOOL | SRGraph | m_bBackgroundDraw | TRUE if the <mf SRGraph::DrawComponentList> 
//function should draw data in a back buffer before copying to the screen<nl>
//Ignored if the owner window is printing
//@rem Background drawing is useful for drawing flicker-free graphs, but it may be slow 
//or memory hungry on slower or smaller systems.

//@mdata BOOL | SRGraph | m_bFeedbackLogging | TRUE if automatic construction of the feedback list is required, otherwise FALSE
//@see <c SRGraphFeedback>, <md SRGraph::m_FeedbackList>

//@mdata BOOL | SRGraph | m_bHintPending | TRUE if a redrawing hint has been flagged but not yet processed

//@mdata CObList | SRGraph | m_ComponentList | Holds a list of <c SRGraphComponent> objects 
//which define the appearance of this graph
//@rem This is the master list of all graphic components in this graph.
//@see <c SRGraphComponent>, <c SRGraphDisplay>, <c SRGraphLegend>, <c SRGraphTitle>, 
//<c SRGraphBackground>, <mf SRGraph::DrawComponentList>, <mf SRGraph::GetComponentList>

//@mdata int | SRGraph | m_nDefaultGroup | Group currently being used as the default data set

//@mdata CObList | SRGraph | m_FeedbackList | Holds a list of <c SRGraphFeedback> objects
//@see <md SRGraph::m_bFeedbackLogging>

//@mdata LPARAM | SRGraph | m_lHint | Hint value passed to this graph after a view update request

//@mdata CObject* | SRGraph | m_pHint | Pointer to a CObject-based hint item -- not currently 
//used in this implementation of Objective Chart (reserved)

//@mdata SRGraphStyle | SRGraph | m_Style | An <c SRGraphStyle> object which holds information about this graph

//@mdata SRGraphAnnotationList | SRGraph | m_strTitle |  Multi-lingual titles for this graph object
//@see <c SRGraphAnnotationList> <c SRGraphAnnotation>

//@mdata int | SRGraph | m_nCountryCode | Telephone dialing code of the country for which 
//annotation texts should be displayed
//@rem The default setting for the country code is 1 (USA). Providing that you have made the 
//correct entries in your annotation lists, setting this data member will make the graph 
//display the corresponding language text at the next redraw.
//@see <mf SRGraph::SetCountryCode>, <mf SRGraph::GetCountryCode>

//@mfunc void | SRGraph | SetCountryCode | Initializes the country code for this graph
//@parm int | nCode | Integer specifying the telephone dialing code of the desired language 
//(ie. 1 for USA, 49 for Germany, etc.)
//@see <mf SRGraph::GetCountryCode>, <md SRGraph::m_nCountryCode>

//@mfunc int | SRGraph | GetCountryCode | Interrogates the country code for this graph
//@rdesc Integer which specifies the telephone dialing code of the desired language (i.e, 1 for USA, 49 for Germany, etc.)
//@see <mf SRGraph::SetCountryCode> <md SRGraph::m_nCountryCode>

//@mfunc void | SRGraph | SetMaxArea | Sets the maximum area which a graph may use
//@parm CRect | r | Rectangle in which to display the graph
//@parm BOOL | UseMaxArea | If TRUE (default) then this area is used
//@rem The maximum area is primarily used to limit page sizes and image areas during printing, 
//but it could be used for window displays too.

//@mdata CRect | SRGraph | m_MaxArea | Maximum area which a chart may occupy
//@rem The maximum area is currently used only in print preview mode, 
//but it could be used in a screen mode too.

//@mdata DWORD | SRGraph | m_dwAlignInDC | Semaphores for centering behaviour
//@rem Alignment is currently used only in print preview mode, but it could be used in a screen mode too.

//@mdata BOOL | SRGraph | m_bUseMaxArea | Flag to use maximum area rectangle
//@rem When this flag is not set, the size is determined by the DC being drawn on.<nl>
//The maximum area is currently used only in print preview mode, but it could be used in a screen mode too.

//@mfunc BOOL | SRGraph | GetUseMaxArea | Returns TRUE if the maximum area described in m_MaxArea is to be used

//@mfunc BOOL | SRGraph | SetUseMaxArea | Initializes the m_MaxArea member variable
//@parm BOOL | b | TRUE if the area is to be used

//@mfunc CRect | SRGraph | GetMaxArea | Returns the m_MaxArea rectangle

//@mfunc void | SRGraph | SetAlignment | Sets up pagination of the graph
//@parm DWORD | dwAlign | Alignment code
//@rem The alignment code may be defined by mixing parameters with a binary OR operator.<nl>
//Vertical alignment codes are...<nl>
//		CX_ALIGN_NONE<nl>
//		CX_ALIGN_VTOP<nl>
//		CX_ALIGN_VCENTER<nl>
//		CX_ALIGN_VBOTTOM<nl>
//Horizontal alignment codes are...<nl>
//		CX_ALIGN_NONE<nl>
//		CX_ALIGN_HLEFT<nl>
//		CX_ALIGN_HCENTER<nl>
//		CX_ALIGN_HRIGHT<nl>


//@mdata POSITION  | SRGraph | m_CurrentComponentPos | POSITION in the list of the component currently being drawn

//@mdata BOOL  | SRGraph | m_bDrawing | Flag set while chart is being drawn

//@mdata CWnd *  | SRGraph | m_pCWnd | Pointer to the CWnd being drawn into

//@mdata CDC *  | SRGraph | m_pDC | Pointer to the CDC being drawn into

//@mdata CRect  | SRGraph | m_OldRect | Rectangle used to retain the old display rectangle

//@mdata CRect  | SRGraph | m_BGRect | Background rectangle

//@mdata CBitmap  | SRGraph | m_Shadow | Bitmap used as a back buffer for flicker free drawing

//@mdata SRGraphData  | SRGraph | dummydata | A dummy chart data object that is returned in case none exists

//@mfunc void  | SRGraph | SetBanding | Sets the banding flag.
//@parm BOOL  | v | Set TRUE before a print preview or print run to use the PrintComponentList routine

//@mfunc BOOL  | SRGraph | GetBanding | Returns the m_bBanding flag -- set during construction of a banded print bitmap

//@mdata CRect  | SRGraph | m_DisplayRect | Current display rectangle -- not saved at serialization

//@mdata CObStack  | SRGraph | m_ClipStack | Stack for storing clipping regions

//@mdata CRect  | SRGraph | m_PageRect | Drawing rectangle used in printing

//@mdata BOOL  | SRGraph | m_bBanding | Banding flag to enable use of banding system during printing

//@mfunc virtual void  | SRGraph | SetPaletteSupported | Initializes the palette support flag 
//@parm BOOL  | v | Set to TRUE to enable palette support 

//@mfunc virtual BOOL  | SRGraph | GetPaletteSupported | Returns the palette support flag.

//@mdata CPalette  | SRGraph | m_Palette | Palette used for this chart (normally preset to a 332 scheme)

//@mdata BOOL  | SRGraph | m_bPaletteSupported | Palette support flag<nl>
//When this flag is set TRUE, the chart is being drawn on a palettized GDI.

//@mfunc virtual CPalette * | SRGraph | GetPalette | Returns a pointer to the stored palette

//@mfunc DWORD  | SRGraph | GetAlignment | Returns the alignment style for this graph

//@doc SRGraph
//@mdata SRGraphStyle  | SRGraph | m_DefaultDataStyle | This <c SRGraphStyle> object is used to generate a default style
// that is copied automatically to new data items as they are created through the <mf SRGraph::SetValue> process.

//@doc SRGraph
//@mdata int  | SRGraph | m_nAutoColorRange | This is the range of colors recognised by the auto pen and auto brush features of OC. This defaults to 16 but
// may be set to generate any default data style configuration.

//@doc SRGraph
//@mfunc virtual void  | SRGraph | SetDefaultDataStyle | This allows initialisation of the default style used whenever a new data object is created. Preset this to
//  some visual style, for example set the default color to red or the default object type to CX_OBJECT_DOT, and this style will be used for all subsequent data creation operations. 
//@parm SRGraphStyle  | v | The pre-set style.

//@doc SRGraph
//@mfunc virtual SRGraphStyle  * | SRGraph |GetDefaultDataStyle | This function returns the default style as set by <mf SRGraph::SetDefaultDataStyle >

//@doc SRGraph
//@mfunc virtual void  | SRGraph | SetAutoColorRange | The normal range of pen colors defaults to 16. Using this function it is possible to use a default range of any number.
// The auto-pen and auto-bruh creation routines will return a color that is based upon this range or the standard colors if 16 is used.
//@parm int  | v | The range 

//@doc SRGraph
//@mfunc virtual int  | SRGraph | GetAutoColorRange | This returns the value set by <mf SRGraph::SetAutoColorRange>

//@doc SRGraph
//@mdata CObList  | SRGraph | m_PolygonList | This variable retains the list of compiled polygons used by all the components on the component list.

//@doc SRGraph
//@mdata CMapStringToPtr  | SRGraph | m_PenMap | This map collection stores pens which have been created by the chart 
//Pens are given a string identifier generated from thier color and style information. These pens can then be re-used 
//thereby eliminating the time consuming pen creation and destruction process.

//@doc SRGraph
//@mdata CString  | SRGraph | m_strEmptyString | Always contains an empty string. This eliminates some CString object creation and speeds up execution.

//@doc SRGraph
//@mdata BOOL  | SRGraph | m_bQuickBlit | 6.11 and CE. The quick blit function is provided for those instances where refreshing of the chart image is needed 
//when the image does not have to reflect the actual data. This feature has been added for time critical applications such as windows CE programs and large data volume
//apps. The current chart image is stored in a back-buffer and transferred to the screen when required. The component list is not re-drawn and so the image is a copy of the 
//previous one. This is used primarily for quick data dragging feedback in CE apps.

//@doc SRGraph
//@mfunc virtual void  | SRGraph | SetQuickBlit | Sets the quickblit flag 
//@parm BOOL  | v | TRUE to enable quickblitting
//@see <md SRGraph::m_bQuickBlit>

//@doc SRGraph
//@mfunc virtual BOOL  | SRGraph | GetQuickBlit | Returns the value of the quickblit flag. 
//@see <md SRGraph::m_bQuickBlit>

//@doc SRGraph
//@mdata BOOL  | SRGraph | m_bSerializeData | Indicating if the graph will serialize the data in the data manager

//@doc SRGraph
//@mdata SRGDataManager*  | SRGraph | m_pDataMgr | Data manager that stores and manages the graph data

//@doc SRGraph
//@mdata BOOL  | SRGraph | m_bAutoDelete | Indicating if the graph manages the memory of the data manager or not.

//@doc SRGraph
//@mfunc virtual CPtrList * | SRGraph | GetDataList | Returns a pointer to the m_data member

//@doc SRGraph
//@mfunc virtual SRGraphFeedback * | SRGraph | GetFeedback | Searches for a feedback point
//@parm int | x | The x coordinate
//@parm int | y | The y coordinate

//@doc SRGraph
//@mfunc virtual SRGraphDataList * | SRGraph | GetGroup | References the correct <c SRGraphDataList> in the array
//@parm int | group | The group number
//@parm BOOL | GrowList | "true" if the list is to grow, otherwise false (set to "true" by default)	

//@doc SRGraph
//@mfunc virtual void * | SRGraph | GetNextData | Gets the next item fron the m_data list
//@parm POSITION& | p | The position

//@doc SRGraph
//@mfunc virtual CPalette * | SRGraph | GetPalette | Returns the stored palette

//@doc SRGraph
//@mfunc BOOL | SRGraph | GetAutoDeleteDataManager | Returns the AutoDelete flag on the data manager

//@doc SRGraph
//@mfunc SRGDataManager* | SRGraph | GetDataManager | Return the existing data manager

//@doc SRGraph
//@mfunc inline CDC* | SRGraph | GetpDC | Return a pointer to the current device context

//@doc SRGraph
//@mfunc void | SRGraph | SetAutoDeleteDataManager | Sets the AutoDelete flag on the data manager
//@parm BOOL | bAutoDelete | true to set automatic delete for the data manager, false otherwise

//@doc SRGraph
//@mfunc inline void | SRGraph | SetpDC | Sets the pointer to a drawing device context -- not used
//@parm CDC* | pDC | pointer to the device context

//@doc SRGraph
//@mdata CMap\<CString , LPCTSTR ,HFONT,HFONT &\> | SRGraph | m_FontMap | This map collection stores fonts which have been created by the chart

//adinsert

/////////////////////////////////////////////////////////////////////////////////////////////

//$head The Graph object
//$level 1

//@doc SRGraph
//@class The graph data parent object -- the main placeholder for all Objective Chart functionality
//@base public | CObject
class SRGraph : public CObject
{
protected:
	CHART_API static BOOL	m_bUseNewModel;

	friend void OCSetUseNewModel(BOOL bUseNewModel);

	//@cmember
	/* Contains an empty string */
	CString m_strEmptyString;	// always empty

//@access Public data members
public:
	//@cmember
	/* Returns the m_bFeedbackLogging flag*/
	CHART_API virtual BOOL GetFeedbackLogging();

	//@cmember
	/* Set TRUE to inform the whole graph of a change in the data or component structures*/
	BOOL m_bSignificantChange;

	//@cmember
	/* Dialing code of the country for which this graph should be adjusted*/
	int m_nCountryCode;
	
	//@cmember
	/* Pointer to a hint object (not currently used)*/
	CObject * m_pHint;

	//@cmember
	/* Most recent hint code*/
	LPARAM m_lHint;

	//@cmember
	/* Semaphore signifying that a hint operation is outstanding*/
	BOOL m_bHintPending;

	//@cmember
	/* Semaphore enabling or disabling the use of a back buffer in draw operations*/
	BOOL m_bBackgroundDraw;

	//@cmember
	/* Style data for axes and graph types*/
	SRGraphStyle m_Style;
	
	//@cmember
	/* List of components which make up the graphical display elements for this graph*/
	CObList m_ComponentList;

	//@cmember
	/* Data manager */
	SRGDataManager*	m_pDataMgr;
	//@cmember
	/* Indicating if the graph manage the memory of data manager of not */
	BOOL	m_bAutoDelete;

	//@cmember
	/* Semaphore to enable or disable feedback logging*/
	BOOL m_bFeedbackLogging;
	
	//@cmember
	/* Linked list of SRGraphFeedback objects*/
	CObList m_FeedbackList;

//operations
//@access Private member functions
private:

	//@cmember
	/* Parses a substring from the text buffer*/
	int SubString(LPCTSTR text,CString &section,DWORD *index,double *number);

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Reports syntax errors in graph template text*/
	CHART_API virtual void TemplateSyntax(LPCTSTR line);//QA: 31877
#endif	//  _OC_DONT_SUPPORT_TEXT_TEMPLATE

//@access Public member functions
public:
	//@cmember
	/* Sets the AutoDelete flag on the data manager*/
	inline void SetAutoDeleteDataManager(BOOL bAutoDelete) { m_bAutoDelete = bAutoDelete; }
	//@cmember
	/* Returns the AutoDelete flag on the data manager*/
	inline BOOL GetAutoDeleteDataManager() { return m_bAutoDelete; }

	//@cmember
	/* Sets the pointer to a drawing device context -- not used */
	inline void SetpDC(CDC* pDC){m_pDC = pDC;}
	//@cmember
	/* Return a pointer to the current device context*/
	inline CDC* GetpDC(){return m_pDC;}
	//@cmember
	/* Prepares for the use of component drawing or sizing functions outside the normal drawing process*/
	CHART_API virtual void DrawingUsing(CDC *pDC,CWnd *pCWnd);
	//@cmember
	/* Resets the drawing parameters set by DrawingUsing()*/
	CHART_API virtual void NotDrawing();
	
	CHART_API virtual HFONT GetFont(LPCTSTR strFontName, int nSize, int nStyle,int nRotation, HDC hDC, LOGFONT *pLogFont=NULL);
	//@cmember
	/* Returns a pointer to the component in the main component list that is currently being drawn */
	CHART_API SRGraphComponent * GetCurrentComponent();
	//@cmember
	/* A one step version of add component to graph*/
	CHART_API virtual SRGraphComponent* AddComponent(UINT nType, int nMeasure = CX_PERCENT, 
		const CRect& rect = CRect(-1, -1, -1, -1), DWORD nBorder = CX_NO_BORDER, 
		DWORD nShadow = CX_NO_SHADOW, DWORD nFillStyle = CX_SOLID_FILL, 
		DWORD nGraphStyle = CX_GRAPH_VBAR, DWORD nAxisStyle = CX_AXIS_AUTOMATIC);
	//@cmember
	/* Returns a new pen or one stored in the cache */
	CHART_API virtual CPen * GetPen(int nPenStyle, int nPenWidth, COLORREF PenColor);
	//@cmember
	/* Loads a named polygon*/
	CHART_API virtual SRGCompiledPolygon * LoadPolygon(LPCTSTR strPolygonName, LPCTSTR strSectionName);
	//@cmember
	/* Initialises the default data style*/
	CHART_API virtual void SetDefaultDataStyle(SRGraphStyle v);
	//@cmember
	/* Retrieves the default data style*/
	CHART_API virtual SRGraphStyle * GetDefaultDataStyle();
	//@cmember
	/* Sets the range of colors used by auto pen and auto brush*/
	CHART_API virtual void SetAutoColorRange(int v);
	//@cmember
	/* Sets the range of colors used by auto pen and auto brush*/
	CHART_API virtual int GetAutoColorRange();
	//@cmember
	/* Deletes components designated as "temporary" from the component list.*/
	CHART_API virtual void DeleteTemporaryComponents(LPCTSTR strName);
	//@cmember
	/* Finds a component on the component list*/
	CHART_API virtual SRGraphComponent * FindComponentByName(LPCTSTR strName);
	//@cmember
	/* Finds or tries to create a compiled polygon by accessing the polgon cache*/
	CHART_API virtual BOOL GetCompiledPolygon(LPCTSTR strPolygonName, LPCTSTR strSectionName, SRGCompiledPolygon * * pPoly,double dAngle=0);

#ifndef _OCCE_
	//@cmember
	/* Creates a half tone palette*/
	CHART_API virtual void Create332Palette(CPalette *pPal);
#endif //_OCCE_

	//@cmember
	/* Saves or loads the component list via serialization*/
	CHART_API virtual void SerializeComponentList(CArchive &ar);
	
	//@cmember
	/* Adds a point to the feedback logging system*/
	CHART_API virtual void LogPoint(CPoint point,int group,int index,int nRadius);
	
	//@cmember
	/* Removes all data from the graph object while leaving the component list intact*/
	CHART_API virtual void KillData();

	//@cmember
	/* Marks the position of the last group accessed as invalid*/
	CHART_API virtual void InvalidateGroupPosition();
	
	//@cmember
	/* Sets the clipping region to a particular polygon*/
	CHART_API virtual void ClipPoly(CPoint *pPoint,int nPointCount,int nMode=RGN_COPY);

	//@cmember
	/* Sets the clipping region to a particular rectangle*/
	CHART_API virtual void ClipRect(CRect r,int nMode=RGN_COPY);
	
	//@cmember
	/* "Pops" a stored clipping region and restores it*/
	CHART_API virtual void PopClip();
	
	//@cmember
	/* "Pushes" the current clipping region on to a stack*/
	CHART_API virtual void PushClip();
	
	//@cmember
	/* Uses a print banding system to output the component list to the printer */
	CHART_API virtual void PrintComponentList(CDC *pCD, CWnd *pCWnd);
	
	//@cmember
	/* Returns the POSITION of the component currently being drawn*/
	CHART_API virtual POSITION GetCurrentComponentPos();
	
	//@cmember
	/* Creates a new SRGraphDataList-based object -- overridable to */
	//allow objects derived from SRGraphDataList to be returned
	CHART_API virtual SRGraphDataList * NewGroup();
	
	//@cmember
	/* Returns the 'safe' data item -- does not grow the list, does not assert*/
	CHART_API virtual SRGraphData * GetSafeData(int index,int group);
	
	//@cmember
	/* Returns the 'unsafe' data item -- can grow the list*/
	CHART_API virtual SRGraphData * GetData(int index,int group);
	
	//@cmember
	/* Returns the size of the display area*/
	CHART_API virtual CSize GetDisplaySize();
	
	//@cmember
	/* Default contructor */
	CHART_API SRGraph();
	//@cmember
	/* Constructor*/
	CHART_API SRGraph(SRGDataManager* pDataMgr, BOOL bAutoDelete);

	//@cmember
	/* Install a data manager*/
	CHART_API virtual void SetDataManager(SRGDataManager* pNewDataManager, BOOL bAutoDelete);
	//@cmember
	/* Return the existing data manager */
	inline SRGDataManager* GetDataManager() { return m_pDataMgr; }
	
	//@cmember
	/* Current display rectangle -- not saved at serialization*/
	CRect m_DisplayRect;
	
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraph();

	//@cmember
	/* Rolls a group in the specified direction*/
	CHART_API virtual void RollGroup(int nGroup, double dValue=0.0, BOOL bDirection=FALSE);

	//@cmember
	/* Places a feedbck rectangle on the feedback list*/
	CHART_API virtual void LogRectangle(CRect r,int group, int index);

	//@cmember
	/* Sets the maximum area which a graph may use*/
	inline void SetMaxArea(CRect r,BOOL bUseArea=TRUE){m_MaxArea=r;m_bUseMaxArea=bUseArea;}

	//@cmember
	/* Returns the rectangle defined as the maximum usable area*/
	inline CRect GetMaxArea(){return m_MaxArea;}

	//@cmember
	/* Returns TRUE if the sizes of the final display are to be controlled by the m_MaxArea rectangle*/
	inline BOOL GetUseMaxArea(){return m_bUseMaxArea;}

	//@cmember
	/* Enables or disables the use of the maximum size rectangle*/
	inline void SetUseMaxArea(BOOL b){m_bUseMaxArea=b;}

	//@cmember
	/* Sets the alignment style for this graph*/
	inline void SetAlignment(DWORD dwAlign){m_dwAlignInDC=dwAlign;}

	//@cmember
	/* Gets the alignment style for this graph*/
	inline DWORD GetAlignment(){return m_dwAlignInDC;}

	//@cmember
	/* Signals to all components on the main list that an important change has taken place*/
	CHART_API virtual void SetSignificantChanges();
	
	//@cmember
	/* Sets the style of all data items in a range to a reference style*/
	CHART_API virtual void SetGlobalStyle(int nStartGroup,int nEndGroup,int nStartIndex,int nEndIndex,SRGraphStyle *ptrStyle,BOOL bSetHeaders=TRUE);

	//@cmember
	/* Sets the minimum index for a given display on the component list*/
	CHART_API virtual void SetComponentMinIndex(int nComponent,int index,UINT Type=-1);
	
	//@cmember
	/* Sets the maximum index for a given display on the component list*/
	CHART_API virtual void SetComponentMaxIndex(int nComponent,int index,UINT Type=-1);
	
	//@cmember
	/* Sets the minimum group for a given display on the component list*/
	CHART_API virtual void SetComponentMinGroup(int nComponent,int group,UINT Type=-1);
	
	//@cmember
	/* Sets the maximum group for a given display on the component list*/
	CHART_API virtual void SetComponentMaxGroup(int nComponent,int group,UINT Type=-1);
	
	//@cmember
	/* Returns the average of all data items in this group*/
	CHART_API virtual double GetGroupAverage(int group);

	//@cmember
	/* Returns the total for a given index across all groups*/
	CHART_API virtual double GetIndexTotal(int index,int nMinGroup=0,int nMaxGroup=0);

	//@cmember
	/* Returns FALSE  -- this object is not a dynamic graph*/
	CHART_API virtual BOOL IsDynamic();

	//@cmember
	/* Wipes the component list without destroying the graph data*/
	CHART_API virtual void KillComponentList();

	//@cmember
	/* Changes title text in the m_strTitle annotation list*/
	CHART_API virtual void SetGraphTitle(LPCTSTR title,int code=1);

	//@cmember
	/* Updates hint information for the component drawing routines*/
	CHART_API virtual void SetComponentHint(CWnd * pCWnd,LPARAM lHint,CObject * pHint);

	//@cmember
	/* Interprets tab delimited text data into graph information*/
	CHART_API virtual void ParseText(LPCTSTR text);
	
	//@cmember
	/* Empties a graph of data*/
	CHART_API virtual void KillGraph(void);

	//@cmember
	/* Calculates the total of all data values in a given range of groups and indices -- used to calculate percentages*/
	CHART_API virtual double GetDataTotal(int mingroup, int  minindex, int maxgroup, int maxindex);

	//@cmember
	/* Calculates the total of all data storage values in this graph -- used to calculate percentages*/
	CHART_API virtual double GetDataTotal(int group=-1);

	//@cmember
	/* Get the number of data item in the given group */
	CHART_API virtual int GetDataCount(int nGroup, BOOL GrowList = TRUE);

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Parses a graph template either from a resource or filename*/
	CHART_API virtual void ReadTemplate(LPCTSTR TemplateName);

	//@cmember
	/* Override this function to interpret your own custom template commands*/
	CHART_API virtual BOOL UserParser(LPCTSTR line);
#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE

	//@cmember	Returns
	/* the header from the <c SRGraphDataList> list indexed by group*/
	CHART_API virtual CString GetHeader(int group=0,int code=1);

	//@cmember	Returns
	/* text held in the <c SRGraphData> object within group and referenced by index*/
	CHART_API virtual CString GetText(int group,int index,int code=1);

	//@cmember
	/* Returns the title of the graph*/
	CHART_API virtual CString GetGraphTitle(int code=1);

	//@cmember
	/* Returns the total number of data sets (groups) in the graph*/
	CHART_API virtual int GetGroupCount();

	//@cmember
	/* Returns the count of the longest group*/
	CHART_API virtual int GetMaxXDivisions();

	//@cmember
	/* Scans the graph data and returns the maximum and minimum value used in this graph*/
	CHART_API virtual CScale GetAutoScaleRange(BOOL HiLo=FALSE);

	//@cmember
	/* References the correct <c SRGraphDataList> in the array*/
	CHART_API virtual SRGraphDataList* GetGroup(int group,BOOL GrowList=TRUE);

	//@cmember	Adds
	/* a <c SRGraphComponent> or derived object to the list of graphic objects*/
	CHART_API virtual POSITION AddComponent(SRGraphComponent *gc);

	//@cmember 
	/* Scans the component list, drawing as it goes (order in the list is reverse Z order on screen)*/
	CHART_API virtual void DrawComponentList(CDC *pDC,CWnd *pCWnd);

	CHART_DECLARE_SERIAL(SRGraph);

	//@cmember
	/* Handles storage and retrieval of data*/
	CHART_API virtual void Serialize(CArchive &ar);

	//@cmember
	/* Sets a header for a group of data by annotating the <c SRGraphDataList> for that group*/
	CHART_API void SetHeader(int group,LPCTSTR text,int nCode=1);

	//@cmember
	/* Sets a numeric value in the data array*/
	CHART_API void SetValue(int index,int group,double number,BOOL bUseDefaultStyle=FALSE);

	//@cmember
	/* Sets text in the data array*/
	CHART_API void SetText(int index,int group,LPCTSTR text);

#ifdef _DEBUG
	//@cmember
	/* Dump diagnostics -- debug only*/
	CHART_API void Dump(CDumpContext &dc) const;
#endif //_DEBUG

	//@cmember
	/* Searches for a feedback point*/
	CHART_API virtual SRGraphFeedback* GetFeedback(int x,int y);
	
	//@cmember
	/* Adds a polygon to the feedback list*/
	CHART_API virtual void LogPoly(LPPOINT points,int PointCount,int group,int index);
	
	//@cmember
	/* Adds a point to the feedback list*/
	CHART_API virtual void LogPoint(CPoint point,int group,int index);
	
	//@cmember
	/* Retrieves an average value for a specific index across a range of groups*/
	CHART_API virtual double GetGroupAverage(int MinIndex,int MaxIndex,int Group);
	
	//@cmember
	/* Calculates the total of all graph values*/
	CHART_API virtual double GetGraphTotal();
	
	//@cmember
	/* Retrieves the m_bBackgroundDraw member*/
	CHART_API virtual BOOL IsBackgroundDraw();
	
	//@cmember
	/* Retrieves the m_bFeedbackLogging member*/
	CHART_API virtual BOOL IsFeedbackLogging();
	
	//@cmember
	/* Initializes the m_bFeedbackLogging member*/
	CHART_API virtual void SetFeedbackLogging(BOOL bLogging=TRUE);
	
	//@cmember
	/* Initializes the m_bBackgroundDraw member*/
	CHART_API virtual void SetBackgroundDraw(BOOL bBDraw=TRUE);
	
	//@cmember
	/* Returns a pointer to the m_strTitle member*/
	CHART_API virtual SRGraphAnnotationList * GetTitle();
	
	//@cmember
	/* Returns a pointer to the m_FeedbackList member*/
	CHART_API virtual CObList * GetFeedbackList();
	
	//@cmember
	/* Returns a pointer to the m_ComponentList member*/
	CHART_API virtual CObList * GetComponentList();
	
	//@cmember
	/* Returns a pointer to the m_ComponentList member*/
	CHART_API virtual SRGraphStyle * GetStyle();
	
	//@cmember
	/* Gets a numeric value from the data array*/
	CHART_API virtual double GetValue(int index,int group);
	
	//@cmember
	/* Returns a pointer to a specific component in the component list*/
	CHART_API virtual SRGraphComponent * GetComponent(int nComponent,UINT Type);
	
	//@cmember
	/* Searches the m_ComponentList for the next item after the supplied POSITION*/
	CHART_API virtual SRGraphComponent * GetNextComponent(POSITION& rPos,UINT Type=-1);
	
	//@cmember
	/* Gets the first POSITION in the component list*/
	CHART_API virtual POSITION GetFirstComponentPosition(UINT Type=-1);
	
	//@cmember
	/* Returns a pointer to the m_data member*/
	CHART_API virtual CPtrList* GetDataList();
	
	//@cmember
	/* Finds the first POSITION of the first item on the m_data list*/
	CHART_API virtual POSITION GetFirstDataPosition();
	
	//@cmember
	/* Gets the next item fron the m_data list*/
	CHART_API virtual void* GetNextData(POSITION& p);

	//@cmember
	/* Sets the dialing code for the annotations in this graph*/
	CHART_API virtual void SetCountryCode(int n);
	
	//@cmember
	/* Interrogates the dialing code for the annotations in this graph.*/
	CHART_API virtual int GetCountryCode();

	//@cmember
	/* Sets the banding variable -- call SetBanding before a print or preview to use the banding system*/
	CHART_API virtual void SetBanding(BOOL v);
	
	//@cmember
	/* Returns the banding flag*/
	CHART_API virtual BOOL GetBanding();

	//@cmember
	/* Initializes the palette support flag.*/
	CHART_API virtual void SetPaletteSupported(BOOL v);

	//@cmember
	/* Returns the palette support flag.*/
	CHART_API virtual BOOL GetPaletteSupported();

	//@cmember
	/* Sets the quickblit flag */
	CHART_API virtual void SetQuickBlit(BOOL v);
	//@cmember
	/* Gets the quickblit flag */
	CHART_API virtual BOOL GetQuickBlit();

#ifndef _OCCE_
	//@cmember
	/* Returns the stored palette*/
	inline virtual CPalette* GetPalette(){return &m_Palette;}
#endif //_OCCE_

protected:
	//@cmember
	/* Flag signifying a clean graph if TRUE*/
	BOOL m_bIsEmpty;
	//@cmember
	/* 6.11 and CE Quick blitting flag */
	BOOL m_bQuickBlit;
	//@cmember
	/* This map collection stores pens which have been created by the chart */
	CMapStringToPtr m_PenMap;

//#ifndef _OCCE_
	//@cmember
	/* This map collection stores fonts which have been created by the chart */
	CMap<CString , LPCTSTR ,HFONT,HFONT &> m_FontMap;
//#endif //_OCCE_

	//@cmember
	/* The polygon cache*/
	CObList m_PolygonList;

	//@cmember
	/* The color range used for choosing auto brushes.*/
	int m_nAutoColorRange;
	//@cmember
	/* TRUE if a palette is used on this chart*/
	BOOL m_bPaletteSupported;

#ifndef _OCCE_

	//@cmember
	/* Stored palette (set to a 332 palette)*/
	CPalette m_Palette;
#endif //_OCCE_

	//@cmember
	/* Stack for storing clipping regions*/
	CObStack m_ClipStack;

	//@cmember
	/* Drawing rectangle used in printing*/
	CRect m_PageRect;

	//@cmember
	/* Banding flag to enable use of banding system during printing*/
	BOOL m_bBanding;

	//@cmember
	/* Aligns a display area rectangle within a given window or page*/
	CHART_API virtual void AlignRect(CRect * r, CRect DCRect);

	//@cmember
	/* POSITION in the list of the component currently being drawn*/
	POSITION m_CurrentComponentPos;


	//@cmember
	/* Flag set when the chart is being drawn and the DC should be valid*/
	BOOL m_bDrawing;

	//@cmember
	/* Pointer to the CWnd being drawn into -- not valid unless m_bDrawing is true*/
	CWnd * m_pCWnd;

	//@cmember
	/* Pointer to the CDC being drawn into -- not valid unless m_bDrawing is true*/
	CDC * m_pDC;

	//@cmember
	/* Rectangle used to retain the old display rectangle*/
	CRect m_OldRect;

	//@cmember
	/* Background rectangle*/
	CRect m_BGRect;

	//@cmember
	/* Bitmap used as a back-buffer in flicker free drawing.*/
	CBitmap m_Shadow;

	//@cmember
	/* Maximum area which a chart may occupy*/
	CRect m_MaxArea;

	//@cmember
	/* Binary semaphores for centering behaviour*/
	DWORD m_dwAlignInDC;

	//@cmember
	/* Semaphore set when maximum area is used to define the image size*/
	BOOL m_bUseMaxArea;

	// XML formatter for SRGraph
	friend class SRGraphFTR;
};

CHART_API void SetUseNewModel(BOOL bUseNewModel);

#ifndef _OCHART_ACTIVEX_
//$head The Graph object (dynamic graph)
//$level 2

//@doc SRDynamicGraph

//@mfunc SRGDataManager* | SRDynamicGraph | GetDataManager | Return the existing data manager

//@class Graphs which handle dynamic data
//@devnote SRDynamicGraph is supplied for compatibility with older versions of OC.
// SRGraph handles all data models (Standard, Dynamic, and Structure), so the
// use of SRDynamicGraph is no longer required.
class SRDynamicGraph: public SRGraph
{

public:
	CHART_API SRDynamicGraph();
	CHART_API SRDynamicGraph(SRGDynamicDataManager* pDataMgr, BOOL bAutoDelete);
	CHART_DECLARE_SERIAL(SRDynamicGraph);
	
	//@cmember
	/* Install a data manager*/
	CHART_API virtual void SetDataManager(SRGDataManager* pNewDataManager, BOOL bAutoDelete);
	//@cmember
	/* Return the existing data manager */
	inline SRGDataManager* GetDataManager() { return m_pDataMgr; }

	//@cmember
	/* Stores or retrieves dynamic graphs*/
	virtual void Serialize(CArchive &ar);

	//@cmember
	/* Returns TRUE to indicate that the Dynamic Data Storage model is in use*/
	CHART_API virtual BOOL IsDynamic();

	//@cmember
	/* Sets text header for this data*/
	CHART_API virtual void SetText(int index,int group,LPCTSTR text);
	
	//@cmember
	/* Overloaded member function: places a double in the buffer*/
	CHART_API virtual void SetValue(int index,int group,double number);
	
	//@cmember
	/* Overloaded member function: places an integer in the buffer*/
	CHART_API virtual void SetValue(int index,int group,int number);
	
	//@cmember
	/* Overloaded member function: places a _TCHAR in the buffer*/
	CHART_API virtual void SetValue(int index,int group,_TCHAR number);
	
	//@cmember
	/* Returns the requested annotation from the SRGraphData referenced by index and group */
	CHART_API virtual CString GetText(int group, int index, int code=1);
	
	//@cmember
	/* Returns the maximum number of indices allowed*/
	CHART_API virtual int GetMaxXDivisions();
	
	//@cmember
	/* Returns the sum of all data stored in a specified group*/
	CHART_API virtual double GetDataTotal(int group=-1);
	
	//@cmember
	/* Returns the maximum and minimum values stored in this graph	*/
	CHART_API virtual CScale GetAutoScaleRange(BOOL HiLo=FALSE);

	// XML formatter for SRDynamicGraph
	friend class SRDynamicGraphFTR;
};

#endif //_OCHART_ACTIVEX_

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SRGRAPH__

