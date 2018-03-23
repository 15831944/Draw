///////////////////////////////////////////////////////////////////////////////
// SRGAxisManager.h
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
//@doc SRGAxisManager
//@module SRGAxisManager.h | SRGAxisManager header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGAxisManager.h: interface of the SRGAxisManager class
//
/////////////////////////////////////////////////////////////
#if !defined(_SRGAXISMANAGER_H_INCLUDED_)
#define _SRGAXISMANAGER_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block block for SRGAxisManager 

//@doc SRGAxisManager
//@mfunc void  | SRGAxisManager | SetNodeAdjust | Turns node adjustment on or off<nl>
//Node adjustments are made generally to label blocks that display groups or indices.<nl>
//A line graph that shows more than one index will have the first and 
//last indices shown on the left and right edges of the chart.<nl>
//A bar chart will have its first and last index markers at a 
//position equal to (DisplayWidth/GroupCount)/2 from either edge. 
//@parm BOOL  | b=TRUE | TRUE to turn node adjustment on (for use with line charts, etc.)

//@mfunc BOOL  | SRGAxisManager | GetNodeAdjust | Returns the node adjust flag<nl>
//For details see <mf SRGAxisManager::SetNodeAdjust>

//@mfunc void  | SRGAxisManager | SetStartPos | Sets the start position for the labels, 
//tick marks, and grid lines associated with this axis manager
//@parm CPoint  | ptStart | Logical coordinates of the start point


//@mfunc void  | SRGAxisManager | SetEndPos | Sets the end position for the labels, 
//tick marks, and grid lines associated with this axis manager
//@parm CPoint  | ptEnd | Logical coordinates of the end point


//@mfunc CPoint  | SRGAxisManager | GetStartPos | Returns the start position for all labels, 
//tick marks, and grid lines associated with this axis manager


//@mfunc CPoint  | SRGAxisManager | GetEndPos | Returns the end position for all labels, 
//tick marks, and grid lines associated with this axis manager

//@mdata BOOL  | SRGAxisManager | m_bNodeAdjust | TRUE if node adjustment should be made
//@see <mf SRGAxisManager::SetNodeAdjust>

//@mdata BOOL  | SRGAxisManager | m_bLabelsOK | TRUE if labels have been registered
//@see <mf SRGAxisManager::RegisterLabels>

//@mdata BOOL  | SRGAxisManager | m_bTicksOK | TRUE if tick marks have been registered
//@see <mf SRGAxisManager::RegisterTicks>

//@mdata BOOL  | SRGAxisManager | m_bGridsOK | TRUE if grid lines have been registered
//@see <mf SRGAxisManager::RegisterGrids>

//@mdata BOOL  | SRGAxisManager | m_bWatcherOK | TRUE if a data watcher has been registered
//@see <mf SRGAxisManager::RegisterWatcher>

//@mdata BOOL  | SRGAxisManager | m_bDisplayOK | TRUE if a display has been registered
//@see <mf SRGAxisManager::RegisterDisplay>

//@mdata BOOL  | SRGAxisManager | m_bTitleOK | TRUE when a title is registered

//@mdata CPoint  | SRGAxisManager | m_ptEnd | Defines the start position of the labels, 
//tick marks, and grid lines

//@mdata CPoint  | SRGAxisManager | m_ptStart | Defines the start position of the labels, 
//tick marks, and grid lines

// adinsert AutoDuck insertion point for SRGAxisManager 

//$head Compound components (sub components)
//$level 3

//@doc SRGAxisManager 
//@class The axis manager is a compound component used by <c SRGCompoundDisplay> to manage 
//one side of the chart axis area. The axis manager may hold up to six types of items. 
//These items are...<nl>
//	labels,<nl>
//	grid lines,<nl>
//	tick marks,<nl>
//	data watcher,<nl>
//	display,<nl>
//	title.<nl>
//These items are positioned and managed as subcomponents of the axis manager 
//which is, in turn, a subcomponent of the compound display.
//@base public | SRGCompoundComponent
class SRGAxisManager : public SRGCompoundComponent  
{
public:
	//@cmember
	/* Removes tick marks from the subcomponent list */
	CHART_API virtual SRGTickMarks * UnregisterTicks(BOOL bDelete=FALSE);
	//@cmember
	/* Removes grid lines from the subcomponent list*/
	CHART_API virtual SRGGridLines * UnregisterGrids(BOOL bDelete=FALSE);
	//@cmember
	/* Removes the data watcher from the subcomponent list*/
	CHART_API virtual SRGDataWatcher * UnregisterWatcher(BOOL bDelete=FALSE);
	//@cmember
	/* Removes labels from the subcomponent list*/
	CHART_API virtual SRGDecimalScale * UnregisterLabels(BOOL bDelete=FALSE);
	//@cmember
	/* Removes the display from the subcomponent list*/
	CHART_API virtual SRGDisplayBase * UnregisterDisplay(BOOL bDelete=FALSE);
	//@cmember
	/* Removes the axis title label from the subcomponent list*/
	CHART_API virtual SRGraphLabel * UnregisterTitle(BOOL bDelete=FALSE);
	//@cmember
	/* Serializes this object to the archive*/
	CHART_API virtual void Serialize(CArchive &ar);
	//@cmember
	/* Returns the address of the grid line subcomponent*/
	CHART_API virtual SRGGridLines * GetGrids();
	//@cmember
	/* Registers a grid line subcomponent*/
	CHART_API virtual void RegisterGrids(SRGGridLines *pG);
	//@cmember
	/* Turns node adjustment on or off*/
	inline virtual void SetNodeAdjust(BOOL b=TRUE){m_bNodeAdjust=b;}
	//@cmember
	/*  Returns node adjustment status*/
	CHART_API virtual BOOL GetNodeAdjust(){return m_bNodeAdjust;}
	//@cmember
	/* Specifies which side of the axis line the labels and tick marks are to be drawn -- TRUE=right/above, FALSE=left/below*/
	CHART_API virtual void SetLabelSide(BOOL b);
	//@cmember
	/* Sets the minimum numeric value used for the axis range*/
	CHART_API virtual void SetMinValue(double d);
	//@cmember
	/* Sets the maximum numeric value used for the axis range*/
	CHART_API virtual void SetMaxValue(double d);
	//@cmember
	/* Sets the scope of the axis manager and all the subcomponents*/
	CHART_API virtual void SetScope(SRGScope s);
	//@cmember
	/* Returns the address of the data watcher subcomponent*/
	CHART_API virtual SRGDataWatcher * GetWatcher();
	//@cmember
	/* Returns the address of the tick mark subcomponent*/
	CHART_API virtual SRGTickMarks * GetTicks();
	//@cmember
	/* Returns the address of the label subcomponent*/
	CHART_API virtual SRGDecimalScale * GetLabels();
	//@cmember
	/* Returns the address of the display subcomponent*/
	CHART_API virtual SRGDisplayBase * GetDisplay();
	//@cmember
	/* Returns the address of the axis title label subcomponent*/
	CHART_API virtual SRGraphLabel * GetTitle();
	//@cmember
	/* Returns the accumulated width of the subcomponents*/
	CHART_API virtual int GetWidth();
	//@cmember
	/* Returns the accumulated height of the subcomponents*/
	CHART_API virtual int GetHeight();
	//@cmember
	/* Registers a display subcomponent*/
	CHART_API virtual void RegisterDisplay(SRGDisplayBase *pD);
	//@cmember
	/* Sets the start position of the labels, tick marks, and grid lines*/
	inline virtual void SetStartPos(CPoint ptStart){m_ptStart=ptStart;}
	//@cmember
	/* Sets the end position of the labels, tick marks, and grid lines*/
	inline virtual void SetEndPos(CPoint ptEnd){m_ptEnd=ptEnd;}
	//@cmember
	/* Returns the start position of the labels, tick marks, and grid lines*/
	inline virtual CPoint GetStartPos(){return m_ptStart;}
	//@cmember
	/* Returns the end position of the labels, tick marks, and grid lines*/
	inline  virtual CPoint GetEndPos(){return m_ptEnd;}
	//@cmember
	/* Registers a tick mark subcomponent*/
	CHART_API virtual void RegisterTicks(SRGTickMarks *pT);
	//@cmember
	/* Registers a label subcomponent*/
	CHART_API virtual void RegisterLabels(SRGDecimalScale *pL);
	//@cmember
	/* Registers a data watcher subcomponent*/
	CHART_API virtual void RegisterWatcher(SRGDataWatcher *pDW);
	//@cmember
	/* Registers an axis title label subcomponent*/
	CHART_API virtual void RegisterTitle(SRGraphLabel *pL);
	//@cmember
	/* Constructor*/
	CHART_API SRGAxisManager();

	CHART_DECLARE_SERIAL(SRGAxisManager);

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGAxisManager();

protected:
	//@cmember
	/* Performs pre-draw or pre-size initialization of the subcomponents*/
	CHART_API virtual void PassTwoSetup();
	//@cmember
	/* Performs pre-draw initialization of the subcomponents*/
	CHART_API virtual void PassOneSetup();

	//@cmember
	/* Node adjustment flag*/
	BOOL m_bNodeAdjust;
	//@cmember
	/* TRUE if labels have been registered*/
	BOOL m_bLabelsOK;	// 0
	//@cmember
	/* TRUE if tick marks have been registered*/
	BOOL m_bTicksOK;	// 1
	//@cmember
	/* TRUE if grid lines have been registered*/
	BOOL m_bGridsOK;	// 2
	//@cmember
	/* TRUE if a data watcher has been registered*/
	BOOL m_bWatcherOK;	// 3
	//@cmember
	/* TRUE if a display has been registered*/
	BOOL m_bDisplayOK;	// 4
	//@cmember
	/* TRUE if a title label been registered*/
	BOOL m_bTitleOK;	// 5
	//@cmember
	/* Position of the end of the axis*/
	CPoint m_ptEnd;
	//@cmember
	/* Position of the start of the axis*/
	CPoint m_ptStart;

	// XML Formatter for SRGAxisManager
	friend class SRGAxisManagerFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_SRGAXISMANAGER_H_INCLUDED_)
