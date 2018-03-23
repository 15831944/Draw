///////////////////////////////////////////////////////////////////////////////
// SRGCompoundDisplay.h
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
//@module SRGCompoundDisplay.h | SRGCompoundDisplay header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGCompoundDisplay.h: interface for the SRGCompoundDisplay class
//
//////////////////////////////////////////////////////////////
#if !defined(_SRGCOMPOUNDDISPLAY_H_INCLUDED_)
#define _SRGCOMPOUNDDISPLAY_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

/////////////////////////////
// AutoDuck tag block for SRGCompoundDisplay 
//@doc SRGCompoundDisplay 

//@mfunc void | SRGCompoundDisplay | SetXRelationship | Initializes the X relationship flag<nl>
//When set TRUE, the slave X axis is automatically recalculated by ratio or by specific 
//calculation to stay in relation to the master X axis
//@parm BOOL  | b | Ratio locking flag -- TRUE locks the ratio of master to slave

//@mfunc void | SRGCompoundDisplay | SetYRelationship | Locks the Y relationship<nl>
//See <mf SRGCompoundDisplay::SetXrelationship> for details
//@parm BOOL  | b | Ratio locking flag -- TRUE locks the ratio of master to slave

//@mfunc void | SRGCompoundDisplay | SetXLinkDirection | Sets the master and slave relationship of the X axes
//@parm BOOL  | b | Pass TRUE to make the X-A axis the master and the X-B the slave, FALSE for the reverse

//@mfunc void | SRGCompoundDisplay | SetYLinkDirection | Sets the master and slave relationship of the Y axes
//@parm BOOL  | b | Pass TRUE to make the Y-A axis the master and the Y-B the slave, FALSE for the reverse

//@mfunc void  | SRGCompoundDisplay | SetXRatio | Sets the numerical ratio of slave to master X axes (slave = master*ratio)
//@parm double | d | Ratio to use for scale conversion or zero
//@rem To invoke the special <mf SRGCompoundDisplay::CalcXRelationship> routine, pass a value of 0.0.

//@mfunc void  | SRGCompoundDisplay | SetYRatio | Sets the numerical ratio of slave to master Y axes (slave = master*ratio) 
//@parm double  | d | Ratio to use for scale conversion or zero
//@rem To invoke the special <mf SRGCompoundDisplay::CalcXRelationship> routine, pass a value of 0.0.

//@mfunc BOOL  | SRGCompoundDisplay | GetXRelationship | Returns the X relationship flag

//@mfunc BOOL  | SRGCompoundDisplay | GetYRelationship | Returns the Y relationship flag

//@mfunc BOOL  | SRGCompoundDisplay | GetXLinkDirection | Returns the X-link direction flag 
//@see <mf SRGCompoundDisplay::SetXLinkDirection>

//@mfunc BOOL  | SRGCompoundDisplay | GetYLinkDirection | Returns the Y-link direction flag
//@see <mf SRGCompoundDisplay::SetYLinkDirection>

//@mfunc double  | SRGCompoundDisplay | GetXRatio | Returns the X axis master / slave ratio

//@mfunc double  | SRGCompoundDisplay | GetYRatio | Returns the Y axis master / slave ratio


//@mdata BOOL  | SRGCompoundDisplay | m_bLinkDirectionY | Signifies that the Y-A axis is the master and the Y-B is the slave when TRUE

//@mdata BOOL  | SRGCompoundDisplay | m_bLinkDirectionX | Signifies that the X-A axis is the master and the X-B is the slave when TRUE

//@mdata BOOL  | SRGCompoundDisplay | m_bXAforYA | Indicates type of linkage between X and Y axes<nl>
//When TRUE, the Y-A axis and X-A axis are linked. When FALSE, the Y-A axis and X-B axis are linked.<nl>
//The oppposite Y axis, Y-B, becomes associated with the X axis that remains.

//@mdata CPtrList  | SRGCompoundDisplay | m_xTickListA | Tick list for the bottom axis

//@mdata CPtrList  | SRGCompoundDisplay | m_xTickListB | Tick list for the top axis

//@mdata CPtrList  | SRGCompoundDisplay | m_yTickListA | Tick list for the left axis

//@mdata CPtrList  | SRGCompoundDisplay | m_yTickListB | Tick list for the right axis

//@mdata BOOL  | SRGCompoundDisplay | m_bXRelationship | Indicates linkage between the two X axes<nl>
//When TRUE, the slave X axis has its maximum and minimum scaling calculated according to 
//either the ratio set by the <mf SRGCompoundDisplay::SetXRatio> routine or by the calculation 
//performed by the <mf SRGCompoundDisplay::CalcXRelationship> function.

//@mdata BOOL  | SRGCompoundDisplay | m_bYRelationship | Indicates linkage between the two Y axes<nl>
//When TRUE, the slave Y axis has its maximum and minimum scaling calculated according to 
//either the ratio set by the <mf SRGCompoundDisplay::SetYRatio> routine or by the calculation 
//performed by the <mf SRGCompoundDisplay::CalcYRelationship> function.

//@mdata double  | SRGCompoundDisplay | m_dXRatio | Ratio used to calculate the slave X axis 
//values from the master X axis (slave = master*m_dXRatio) -- set to 0.0 to invoke the 
//<mf SRGCompoundDisplay::CalcXRelationship> function

//@mdata double  | SRGCompoundDisplay | m_dYRatio | Ratio used to calculate the slave Y axis 
//values from the master Y axis (slave = master*m_dYRatio) -- set to 0.0 to invoke the 
//<mf SRGCompoundDisplay::CalcYRelationship> function

//@mfunc void  | SRGCompoundDisplay | SetXAforYA | Sets the flag that associates tha XA axis with the YA axis
//@parm BOOL  | v | Set TRUE to signify that the XA and YA axes are connected (default), set FALSE to tie the XB axis to the YA axis

//@mfunc BOOL  | SRGCompoundDisplay | GetXAforYA | Gets the flag that associates tha XA axis with the YA axis

// adinsert AutoDuck insertion point for SRGCompoundDisplay 
//$head Compound components (compound display)
//$level 2

//@doc SRGCompoundDisplay 
//@class The compound display class holds four subcomponents based on the SRGAxisManager class.<nl>
//These axis managers in turn may optionally hold a set of tick marks, a label block, a set of 
//grid lines, a data watcher, and a display.<nl>
//The four axis managers correspond to the four sides of a chart rectangle. Therefore by adding 
//subcomponents to the various axis managers, it is possible to define 
//a custom chart design without writing a chart extension.<nl>
//In addition, it is possible to define a relationship between the axes on opposing sides of the chart. 
//Then if the scale on one side changes, the scale on the other side is automatically 
//recalculated according to the preset ratio or some other calculation.<nl>
//Furthermore, the chart axis components may be dynamically added or removed without removing the display 
//from the main component list. This allows a highly flexible method of creating custom charts.
//@base public | SRGCompoundComponent
class SRGCompoundDisplay : public SRGCompoundComponent  
{
public:
	//@cmember
	/* Sets and optionally locks the display rectangle*/
	CHART_API virtual void SetDisplayRect(CRect r,BOOL bDRLock=TRUE);
	//@cmember
	/* Serializes this object*/
	CHART_API virtual void Serialize(CArchive& ar);
	//@cmember
	/* Performs X axis range conversions*/
	CHART_API virtual double CalcYRelationship(double d);
	//@cmember
	/* Peforms Y axis range conversions*/
	CHART_API virtual double CalcXRelationship(double d);
	//@cmember
	/* Initializes the X relationship flag*/
	inline virtual void SetXRelationship(BOOL b){m_bXRelationship=b;}
	//@cmember
	/* Initializes the Y relationship flag*/
	inline virtual void SetYRelationship(BOOL b){m_bYRelationship=b;}
	//@cmember
	/* Selects the X master axis*/
	inline virtual void SetXLinkDirection(BOOL b){m_bLinkDirectionX=b;}
	//@cmember
	/* Selects the Y master axis*/
	inline virtual void SetYLinkDirection(BOOL b){m_bLinkDirectionY=b;}
	//@cmember
	/* Sets the ratio between master and slave X axes*/
	inline virtual void SetXRatio(double d){m_dXRatio=d;}
	//@cmember
	/* Sets the ratio between master and slave Y axes*/
	inline virtual void SetYRatio(double d){m_dYRatio=d;}
	//@cmember
	/* Returns the X axis relationship flag*/
	inline virtual BOOL GetXRelationship(){return m_bXRelationship;}
	//@cmember
	/* Returns the Y axis relationship flag*/
	inline virtual BOOL GetYRelationship(){return m_bYRelationship;}
	//@cmember
	/* Returns the X axis link direction flag*/
	inline virtual BOOL GetXLinkDirection(){return m_bLinkDirectionX;}
	//@cmember
	/* Returns the Y axis link direction flag*/
	inline virtual BOOL GetYLinkDirection(){return m_bLinkDirectionY;}
	//@cmember
	/* Returns the X axis master / slave ratio*/
	inline virtual double GetXRatio(){return m_dXRatio;}
	//@cmember
	/* Returns the Y axis master / slave ratio*/
	inline virtual double GetYRatio(){return m_dYRatio;}
	//@cmember
	/* Sets the tick position list for the chosen axis manager*/
	CHART_API virtual void SetptrTickPositionList(SRGAxisManager *pAM,CPtrList *pL);
	//@cmember
	/* Sets the tick position list for the X-A axis manager*/
	CHART_API virtual void SetptrXTickPositionListA(CPtrList *pL);
	//@cmember
	/* Sets the tick position list for the X-B axis manager*/
	CHART_API virtual void SetptrXTickPositionListB(CPtrList *pL);
	//@cmember
	/* Sets the tick position list for the Y-A axis manager*/
	CHART_API virtual void SetptrYTickPositionListA(CPtrList *pL);
	//@cmember
	/* Sets the tick position list for the Y-B axis manager*/
	CHART_API virtual void SetptrYTickPositionListB(CPtrList *pL);
	//@cmember
	/* Returns a pointer to the bottom axis manager*/
	CHART_API virtual SRGAxisManager* GetXAxisA();
	//@cmember
	/* Returns a pointer to the top axis manager*/
	CHART_API virtual SRGAxisManager* GetXAxisB();
	//@cmember
	/* Returns a pointer to the left axis manager*/
	CHART_API virtual SRGAxisManager* GetYAxisA();
	//@cmember
	/* Returns a pointer to the right axis manager*/
	CHART_API virtual SRGAxisManager* GetYAxisB();
	//@cmember
	/* Constructor*/
	CHART_API SRGCompoundDisplay();

	CHART_DECLARE_SERIAL(SRGCompoundDisplay);

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGCompoundDisplay();
	//@cmember
	/* Registers a label block with the bottom axis manager*/
	CHART_API virtual void SetXLabelA(SRGDecimalScale *pL);
	//@cmember
	/* Registers a label block with the top axis manager*/
	CHART_API virtual void SetXLabelB(SRGDecimalScale *pL);
	//@cmember
	/* Registers a label block with the left axis manager*/
	CHART_API virtual void SetYLabelA(SRGDecimalScale *pL);
	//@cmember
	/* Registers a label block with the right axis manager*/
	CHART_API virtual void SetYLabelB(SRGDecimalScale *pL);
	//@cmember
	/* Registers a grid line component with the left axis manager*/
	CHART_API  void SetYGridLinesA(SRGGridLines *pG);
	//@cmember
	/* Registers a grid line component with the right axis manager*/
	CHART_API virtual void SetYGridLinesB(SRGGridLines *pG);
	//@cmember
	/* Registers a grid line component with the bottom axis manager*/
	CHART_API virtual void SetXGridLinesA(SRGGridLines *pG);
	//@cmember
	/* Registers a grid line component with the top axis manager*/
	CHART_API virtual void SetXGridLinesB(SRGGridLines *pG);
	//@cmember
	/* Registers a tick mark component with the bottom axis manager*/
	CHART_API virtual void SetXTickMarksA(SRGTickMarks *pT);
	//@cmember
	/* Registers a tick mark component with the top axis manager*/
	CHART_API virtual void SetXTickMarksB(SRGTickMarks *pT);
	//@cmember
	/* Registers a tick mark component with the left axis manager*/
	CHART_API virtual void SetYTickMarksA(SRGTickMarks *pT);
	//@cmember
	/* Registers a tick mark component with the right axis manager*/
	CHART_API virtual void SetYTickMarksB(SRGTickMarks *pT);
	//@cmember
	/* Registers a display with the bottom axis manager*/
	CHART_API virtual void SetXGraphDisplayA(SRGDisplayBase *pD);
	//@cmember
	/* Registers a display with the top axis manager*/
	CHART_API virtual void SetXGraphDisplayB(SRGDisplayBase *pD);
	//@cmember
	/* Registers a display with the left axis manager*/
	CHART_API virtual void SetYGraphDisplayA(SRGDisplayBase *pD);
	//@cmember
	/* Registers a display with the right axis manager*/
	CHART_API virtual void SetYGraphDisplayB(SRGDisplayBase *pD);
	//@cmember
	/* Registers a data watcher with the bottom axis manager*/
	CHART_API virtual void SetXDataWatcherA(SRGDataWatcher *pDW);
	//@cmember
	/* Registers a data watcher with the top axis manager*/
	CHART_API virtual void SetXDataWatcherB(SRGDataWatcher *pDW);
	//@cmember
	/* Registers a data watcher with the left axis manager*/
	CHART_API virtual void SetYDataWatcherA(SRGDataWatcher *pDW);
	//@cmember
	/* Registers a data watcher with the right axis manager*/
	CHART_API virtual void SetYDataWatcherB(SRGDataWatcher *pDW);
	//@cmember
	/* Sets the flag that associates the XA axis with the YA axis*/
	CHART_API virtual void SetXAforYA(BOOL v){m_bXAforYA=v;}
	//@cmember
	/* Returns the flag that associates the XA axis with the YA axis*/
	CHART_API virtual BOOL GetXAforYA(){return m_bXAforYA;}
	//@cmember
	/* Draws this compound component*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pCWnd);

protected:
	//@cmember
	/* Performs clean up operations after pass two of the draw cycle*/
	CHART_API virtual void PassTwoCleanup();
	//@cmember
	/* Performs setup before pass two of the draw cycle*/
	CHART_API virtual void PassTwoSetup();
	//@cmember
	/* Performs clean up after pass one of the draw cycle*/
	CHART_API virtual void PassOneCleanup();
	//@cmember
	/* Performs setup before pass one of the draw cycle*/
	CHART_API virtual void PassOneSetup();

	//@cmember
	/* When TRUE the Y-A axis is the master*/
	BOOL m_bLinkDirectionY;
	//@cmember
	/* When TRUE the X-A axis is the master*/
	BOOL m_bLinkDirectionX;
	//@cmember
	/* When TRUE the X-A axis is associated with the Y-A axis*/
	BOOL m_bXAforYA;
	//@cmember
	/* Tick position list associated with the bottom axis*/
	CPtrList m_xTickListA;
	//@cmember
	/* Tick position list associated with the top axis*/
	CPtrList m_xTickListB;
	//@cmember
	/* Tick position list associated with the left axis*/
	CPtrList m_yTickListA;
	//@cmember
	/* Tick position list associated with the right axis*/
	CPtrList m_yTickListB;
	//@cmember
	/* When TRUE the two X axes are related (locked)*/
	BOOL m_bXRelationship;
	//@cmember
	/* When TRUE the two Y axes are related (locked)*/
	BOOL m_bYRelationship;
	//@cmember
	/* Defines the ratio between locked X axes*/
	double m_dXRatio;
	//@cmember
	/* Defines the ratio between locked Y axes*/
	double m_dYRatio;

	// XML Formatter for SRGCompoundDisplay
	friend class SRGCompoundDisplayFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_SRGCOMPOUNDDISPLAY_H_INCLUDED_)
