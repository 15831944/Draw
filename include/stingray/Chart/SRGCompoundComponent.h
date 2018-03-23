///////////////////////////////////////////////////////////////////////////////
// SRGCompoundComponent.h
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
//@doc SRGCompoundComponent
//@module SRGCompoundComponent.h | SRGCompoundComponent header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGCompoundComponent.h: Interface for the SRGCompoundComponent class.
//
/////////////////////////////////////////////////////////////
#if !defined(_SRGCOMPOUNDCOMPONENT_H_INCLUDED_)
#define _SRGCOMPOUNDCOMPONENT_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGCompoundComponent 
//
//@doc SRGCompoundComponent 

//@mfunc CObList * | SRGCompoundComponent  | GetComponentList | Returns a pointer to the 
//component list owned by this compound component

//@mfunc BOOL  | SRGCompoundComponent  | GetDrawLocalForeground | Returns TRUE if the local 
//foreground is to be drawn
//@devnote Aside from the drawing actions performed by the various subcomponents of this object, 
//drawing local to this object may be performed. 
//Such drawing may be placed behind or in front of the graphics produced by the subcomponents 
//by altering the state of the foreground order flag.
//@see <mf SRGCompoundComponent::GetForegroundOrder> <mf SRGCompoundComponent::GetForegroundOrder>

//@mfunc BOOL  | SRGCompoundComponent  | GetForegroundOrder | Returns the foreground order flag -- used 
//to determine if the local foreground is to be drawn before or after the subcomponent list 

//@mfunc void  | SRGCompoundComponent  | SetDrawLocalForeground | Sets that flag that signifies that 
//the local foreground should be drawn
//@parm BOOL  | b | TRUE to draw the local foreground

//@mfunc void  | SRGCompoundComponent  | SetForegroundOrder | Sets the order of the foreground drawing
//@parm BOOL  | b | FALSE to draw the foreground before the subcomponent list, TRUE to draw the foreground after

//@mfunc void  | SRGCompoundComponent  | SetDrawPanel | Sets the flag signifying that the 
//panel is to be drawn for this compound object
//@parm BOOL  | b | TRUE (default) to draw the panel, FALSE to ignore

//@mfunc BOOL  | SRGCompoundComponent  | GetDrawPanel | Returns the draw panel flag

//@mfunc BOOL  | SRGCompoundComponent  | GetAutoPanel | Returns the auto panel sizing flag

//@mfunc void  | SRGCompoundComponent  | SetTwoPass | Sets the two-pass flag
//@parm BOOL  | b | TRUE (default) to do a two pass draw with pre-display sizing

//@mfunc BOOL  | SRGCompoundComponent  | GetTwoPass | Returns the two-pass flag

//@mfunc void  | SRGCompoundComponent | SetTopLevel | Sets the top-level flag
//@parm BOOL  | v | If TRUE this component is considered to be a top-level or master component

//@mfunc BOOL  | SRGCompoundComponent | GetTopLevel | Returns the top-level flag

//@mdata BOOL  | SRGCompoundComponent | m_bTwoPass | TRUE if this component performs pre-draw sizing functions

//@mdata BOOL  | SRGCompoundComponent | m_bDrawLocalForeground | Draw local foreground flag

//@doc SRGCompoundComponent
//@mdata BOOL  | SRGCompoundComponent | m_bForegroundOrder | Foreground drawing order flag<nl>
//If FALSE, the foreground is drawn before the subcomponent list.<nl>
//If TRUE, the foreground is drawn after.

//@mdata BOOL  | SRGCompoundComponent | m_bAutoPanel | TRUE if automatic panel sizing from the sizes of subcomponents is available

//@mdata BOOL  | SRGCompoundComponent | m_bDrawPanel | TRUE if the panel is filled, and borders and shadows are drawn as normal

//@mdata CRect  | SRGCompoundComponent | m_DisplayRect | Data display rectangle

//@mdata BOOL  | SRGCompoundComponent | m_bTopLevel | True if this is a top level component 
//(ie. if it can be displayed directly from the graph's component list)

//@mdata CObList  | SRGCompoundComponent | m_ComponentList | The local subcomponent list

// adinsert
//$head Compound components
//$level 1

//@doc SRGCompoundComponent 
//@class This class allows a component to manage its own local subcomponent list. 
//This means that a list of subcomponents may now be considered as a single entity.<nl>
//The compound component manages its own subcomponents in much the same way as an 
//SRGraph user application would manage the component list in the SRGraph class.<nl>
//It is responsible for the placement, sizing, and other housekeeping tasks. 
//A two pass system is implemented that handles pre-draw sizing and final drawing processes. 
//These tasks are performed by the <mf SRGCompoundComponent::PassOneSetup>, <mf SRGCompoundComponent::PassOneCleanup>, 
//<mf SRGCompoundComponent::PassTwoSetup> and <mf SRGCompoundComponent::PassTwoCleanup> functions 
//that are called to allow this housekeeping to be carried out by a derived class.
//@base public | SRGraphComponent
class SRGCompoundComponent : public SRGraphComponent  
{
public:
	CHART_API virtual BOOL IsCompound();
	CHART_API virtual void SetSignificantChange();
	//@cmember
	/* Serializes this component*/
	CHART_API virtual void Serialize(CArchive& ar);
	//@cmember
	/* Sets the top-level flag*/
	inline virtual void SetTopLevel(BOOL v){m_bTopLevel=v;}
	//@cmember
	/* Returns the top-level flag*/
	inline virtual BOOL GetTopLevel(){return m_bTopLevel;}
	//@cmember
	/* Returns a nested component*/
	CHART_API virtual SRGraphComponent * GetComponent(int nComponent,UINT Type,int *pCurrentComponent=0);
	//@cmember
	/* Returns a pointer to the local subcomponent list*/
	inline virtual CObList * GetComponentList(){return &m_ComponentList;}
	//@cmember
	/* Sets the parent of this and all subcomponent objects*/
	CHART_API virtual void SetParent(SRGraph *pG);
	//@cmember
	/* Adds a component to the local list*/
	CHART_API virtual POSITION AddComponent(SRGraphComponent * pC);
	//@cmember
	/* Returns the draw local foreground flag*/
	inline virtual BOOL GetDrawLocalForeground(){return m_bDrawLocalForeground;}
	//@cmember
	/* Returns the foreground drawing order flag*/
	inline virtual BOOL GetForegroundOrder(){return m_bForegroundOrder;}
	//@cmember
	/* Sets the draw local foreground flag*/
	inline virtual void SetDrawLocalForeground(BOOL b){m_bDrawLocalForeground=b;}
	//@cmember
	/* Sets the foreground drawing order flag*/
	inline virtual void SetForegroundOrder(BOOL b){m_bForegroundOrder=b;}
	//@cmember
	/* Draws this compound component*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pCWnd);
	//@cmember
	/* Sets the draw panel flag*/
	inline virtual void SetDrawPanel(BOOL b=TRUE){m_bDrawPanel=b;}
	//@cmember
	/* Returns the draw panel flag*/
	inline virtual BOOL GetDrawPanel(){return m_bDrawPanel;}
	//@cmember
	/* Returns the automatic panel sizing flag*/
	inline virtual BOOL GetAutoPanel(){return m_bAutoPanel;}
	//@cmember
	/* Sets the two pass processing flag*/
	inline virtual void SetTwoPass(BOOL b=TRUE){m_bTwoPass=b;}
	//@cmember
	/* Returns the two pass processing flag*/
	inline virtual BOOL GetTwoPass(){return m_bTwoPass;}

	//@cmember
	/* Constructor*/
	CHART_API SRGCompoundComponent();

	CHART_DECLARE_SERIAL(SRGCompoundComponent);

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGCompoundComponent();

protected:
	//@cmember
	/* Draws subcomponents that have been deferred*/
	CHART_API virtual void DrawDeferred();
	//@cmember
	/* Pass one setup -- override to perform sensible tasks*/
	CHART_API virtual void PassOneSetup();
	//@cmember
	/* Pass one setup -- override to perform sensible tasks*/
	CHART_API virtual void PassTwoSetup();
	//@cmember
	/* Pass one cleanup -- override to perform sensible tasks*/
	CHART_API virtual void PassOneCleanup();
	//@cmember
	/* Pass two cleanup -- override to perform sensible tasks*/
	CHART_API virtual void PassTwoCleanup();
	//@cmember
	/* Custom panel sizing -- override to perform sensible tasks*/
	CHART_API virtual void CalcAutoPanel();
	//@cmember
	/* Draw local foreground graphics -- override to perform sensible tasks */
	CHART_API virtual void DrawLocalForeground();
	//@cmember
	/* Draws all items in the subcomponent list*/
	CHART_API virtual void DrawForeground();

	//@cmember
	/* The subcomponent list*/
	CObList m_ComponentList;
	//@cmember
	/* Top level or master component flag*/
	BOOL m_bTopLevel;
	//@cmember
	/* Two pass processing flag*/
	BOOL m_bTwoPass;
	//@cmember
	/* Draw local foreground flag*/
	BOOL m_bDrawLocalForeground;
	//@cmember
	/* Foreground drawing order flag*/
	BOOL m_bForegroundOrder;
	//@cmember
	/* Automatic panel resizing flag*/
	BOOL m_bAutoPanel;
	//@cmember
	/* Panel drawing flag*/
	BOOL m_bDrawPanel;
	//@cmember
	/* Data display rectangle*/
	CRect m_DisplayRect;

	// XML Formatter for SRGCompoundComponent
	friend class SRGCompoundComponentFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_SRGCOMPOUNDCOMPONENT_H_INCLUDED_)
