///////////////////////////////////////////////////////////////////////////////
// SRGraphLabelBlock.h
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
//@doc SRGraphLabelBlock
//@module SRGraphLabelBlock.h|  definition of the graph label block class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGLabelBlock.h: definition of the graph label block component class
//
/////////////////////////////////////////////////////////////
#ifndef __SRGRAPHLABELBLOCK__
#define __SRGRAPHLABELBLOCK__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphLabelBlock
//
//@doc SRGraphLabelBlock

//@mdata POSITION  | SRGraphLabelBlock | m_LastPos | Last POSITION accessed in indexing the labels -- used in the list access speed-up code
//@doc SRGraphLabelBlock
//@mdata int  | SRGraphLabelBlock | m_nLastIndex | Last index accessed while indexing the labels -- used in the list access speed-up code

//@mdata int  | SRGraphLabelBlock | m_nBlockTitle | Set TRUE if this block should be titled (reserved for future expansion)

//@mdata BOOL  | SRGraphLabelBlock | m_bCheckOverlaps | When set, the labels within this block will be checked for overlaps

//@mdata CRect  | SRGraphLabelBlock | m_BlockRect | Rectangle of screen covered by the label block after pass 0 or pass 1 processing

//@mdata BOOL  | SRGraphLabelBlock | m_bLogTickPositions | Semaphore which enables the logging of label locations in a tick list

//@mdata BOOL  | SRGraphLabelBlock | m_bUseMyOwnTickList | Set by the label block when a tick logging request is made but no tick list is provided

//@mdata CObList  | SRGraphLabelBlock | m_LabelList | List of SRGraphLabel objects to be displayed in this block

//@mdata CPtrList *  | SRGraphLabelBlock | m_pTickPositionList | Pointer to the tick position list that this label block maintains

//@mdata CSize  | SRGraphLabelBlock | m_TotalBlockSize | Accumulated unrotated size of the label block

//@mfunc void  | SRGraphLabelBlock | DrawBorder | Overridden to prevent the drawing of a component panel 

//@mfunc void  | SRGraphLabelBlock | DrawFill | Overridden to prevent the drawing of a component panel

//@mfunc void  | SRGraphLabelBlock | DrawShadow | Overridden to prevent the drawing of a component panel

//@mfunc virtual BOOL  | SRGraphLabelBlock | GetCheckOverlaps | Returns the anti-collision test semaphore

//@mfunc virtual CRect  | SRGraphLabelBlock | GetBlockRect | Returns a rectangle calculated to fully cover the drawn block

//@mfunc virtual void  | SRGraphLabelBlock | SetPass | Initializes the pass semaphore to allow pre-draw sizing of the labels or actual drawing
//@parm BOOL  | b | FALSE to indicate preparation pass, TRUE to indicate drawing pass (no longer used) 

//@mfunc virtual BOOL  | SRGraphLabelBlock | GetPass | Returns the pass semaphore that allows pre-draw sizing of the labels or actual drawing (no longer used)

//@mfunc virtual void  | SRGraphLabelBlock | SetptrTickPositionList | Initializes the pointer to the block's tick list
//@parm CPtrList * | ptr | Pointer to the predefined position list

//@mdata BOOL  | SRGraphLabelBlock | m_bPass1 |  When reset - label placement and sizing takes place but no text is output, 
//When set - the text is generated (no longer used)

//@mfunc virtual void  | SRGraphLabelBlock | SetCheckOverlaps | Enables or disables the block's anti-collision feature
//@parm BOOL  | b | TRUE to check for overlaps

//@mfunc virtual void  | SRGraphLabelBlock | SetLogTickPositions | Enables or disables the tick position logging feature
//@parm BOOL  | b | TRUE to enable logging

//@mfunc virtual CPtrList * | SRGraphLabelBlock | GetptrTickPositionList | Retrieves the pointer to the tick position list associated with this label block

#ifdef _OCCE_
//@doc SRGraphLabelBlock
//@mdata CPtrList  | SRGraphLabelBlock | m_LabelRects | Windows CE only. This member maintains a list of CRect objects used to provide label anti-collision 
//features when there are no irregular regions available.
#endif //_OCCE_

//@doc SRGraphLabelBlock
//@mdata CRgn*  | SRGraphLabelBlock | m_pNoDrawRgn | This is a special reserved region into which text may not be placed. Currently used by the Pie chart code that draws the pie labels.

//adinsert
//$head Component classes
//$level 1

//@class Manages blocks of SRGraphLabel objects
//@base public | SRGraphLabel
//@rem Label blocks may perform anti-collision calculations on labels which they control. 
//If this facility is enabled, then any label found to be overlapping another may optionally 
//be removed or moved in a specific direction.<nl>
//Label blocks are also capable of maintaining a list of points, effectively the points at 
//which each label was displayed, for the positioning of tick marks or grid lines.
class SRGraphLabelBlock : public SRGraphLabel
{
//@access protected data members
protected:
	//@cmember
	/* When reset - label placement and sizing takes place but no text is output, */
	//when set - the text is generated (no longer used)
	BOOL m_bPass1; // Note: no longer used but left in to preserve class data
	//@cmember
	/* Set by the label block when a tick logging request is made but no tick list is provided*/
	BOOL m_bUseMyOwnTickList;
	//@cmember
	/* When TRUE, the label block checks all labels for overlaps and performs anti-collision vectoring*/
	BOOL m_bCheckOverlaps;
	//@cmember
	/* Rectangle of the screen covered by the label block -- determined during pass 0 or pass 1 processing*/
	CRect m_BlockRect;
	//@cmember
	/* Accumulated unrotated size of the label block*/
	CSize m_TotalBlockSize;
	//@cmember
	/* List of SRGraphLabel objects that this block holds*/
	CObList m_LabelList;
	//@cmember
	/* Enables the logging of label locations in a tick list*/
	BOOL m_bLogTickPositions;
	CPtrList * m_pTickPositionList;


//@access public member functions
public:
	//@cmember
	/* Pointer to a region that will be reserved for other use*/
	CRgn* m_pNoDrawRgn;
	//@cmember
	/* Calculate the font size */
	CHART_API int CalcFontAutoSize();
	//@cmember
	/* Sets the font style and reset the autofontsize flag */
	CHART_API void SetFontStyle(int nFontStyle);

	CHART_API virtual void SetParent(SRGraph * pParent);
	//@cmember
	/* Updates the tick list without an offset*/
	CHART_API virtual void UpdateTickList();
	//@cmember
	/* Creates the labels*/
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Returns the number of labels in this block*/
	CHART_API virtual int GetLabelCount();
	//@cmember
	/* Removes and deletes the "tail" label from the label list*/
	CHART_API virtual void RemoveLastLabel();
	//@cmember
	/* Removes and deletes all labels in the list*/
	CHART_API virtual void KillLabels();
	//@cmember
	/* Initializes the pass semaphore to allow pre-draw sizing of the labels or actual drawing*/
	CHART_API virtual void SetPass(BOOL b);
	//@cmember
	/* Interrogates the m_bPass member*/
	CHART_API virtual BOOL GetPass();
	//@cmember
	/* Adds a label or updates a label in an indexed position*/
	CHART_API virtual void AddLabelIndex(LPCTSTR LabelText,int nIndex,int nCode=1);
	//@cmember
	/* Transfers all label locations to a list for use when drawing grid lines and tick marks*/
	CHART_API virtual void UpdateTickList(int nOffsetX,int nOffsetY);
	//@cmember
	/* Retrieves a label from the list referenced by index*/
	CHART_API virtual SRGraphLabel * GetLabelIndex(int nIndex);
	//@cmember
	/* Adds a label to the tail of the label list*/
	CHART_API virtual void AddLabel(SRGraphLabel *label,BOOL bUseLocalFont=FALSE);
	//@cmember
	/* Globally sets the location points for all labels in the block*/
	CHART_API virtual void SetBlockLocationPoints(int nLocationPoint);
	//@cmember
	/* Globally sets the orientation angles for all labels in the block*/
	CHART_API virtual void SetBlockOrientations(double dAngle);
	//@cmember
	/* "Pegs" all labels in a block along a line between the two points supplied*/
	CHART_API virtual void SetBlockPositions(CPoint StartPoint, CPoint EndPoint);
	//@cmember
	/* Globally sets the anti-collision vectors for all labels in the block*/
	CHART_API virtual void SetBlockVectors(double dVectorX,double dVectorY);
	//@cmember
	/* Adds a label to the list (overload)*/
	CHART_API virtual void AddLabel(LPCTSTR strLabelText);
	//@cmember
	/* Returns a rectangle (in device dependent coordinates) calculated to fully cover the drawn block*/
	CHART_API virtual CRect GetBlockRect();
	//@cmember
	/* Same as GetBlockRect() -- for compatiblity with other components*/
	CHART_API virtual CRect GetLogRect();
	//@cmember
	/* Initializes the pointer to the block's tick list*/
	CHART_API virtual void SetptrTickPositionList(CPtrList *ptr);
	//@cmember
	/* Enables or disables the tick position logging feature*/
	CHART_API virtual void SetLogTickPositions(BOOL b);
	//@cmember,mfunc
	/* Retrieves the pointer to the tick position list associated with this label block*/
	CHART_API virtual CPtrList* GetptrTickPositionList();
	//@cmember
	/* Enables or disables the block's anti-collision feature*/
	CHART_API virtual void SetCheckOverlaps(BOOL b);
	//@cmember
	/* Returns the anti-collision test semaphore*/
	CHART_API virtual BOOL GetCheckOverlaps();
	//@cmember
	/* Constructor	*/
	CHART_API SRGraphLabelBlock();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphLabelBlock();

	CHART_DECLARE_SERIAL(SRGraphLabelBlock);
	//@cmember
	/* Allows storage or retrieval via the archive*/
	CHART_API virtual void Serialize(CArchive &ar);

//@cmember,menum
/* Block title positions*/
enum BlockTitle {
	None,
	Above,
	Right,
	Below,
	Left
	} ;



//@cmember,menum
/* May be used instead of a positive integer index to return the first or last label on the list*/
enum LabelPositions {
	LabelFirst=-1,	//@@emem Get the first on the list -1
	LabelLast=-2	//@@emem Get the last -2
	} ;


//@access protected member functions
protected:
	//@cmember
	/* Overridden to prevent the drawing of a component panel*/
	inline void DrawBorder(){};
	//@cmember
	/* Overridden to prevent the drawing of a component panel*/
	inline void DrawFill(){};
	//@cmember
	/* Overridden to prevent the drawing of a component panel*/
	inline void DrawShadow(){};
	//@cmember
	/* Sizes or draws the text with anti-collision if enabled*/
	CHART_API void DrawForeground();

//@access Protected data members
protected:
#ifdef _OCCE_
	//@cmember
	/* Windows CE only. This maintains a list of CRects for anti collision detection without regions.*/
	CPtrList m_LabelRects;
#endif //_OCCE_
	//@cmember
	/* List class position storage for speed-up code*/
	POSITION m_LastPos;
	//@cmember
	/* List class index number for speed-up code*/
	int m_nLastIndex;
	//@cmember
	/* Reserved*/
	int m_nBlockTitle;

	// XML Formatter for SRGGraphLabelBlock
	friend class SRGraphLabelBlockFTR;
};

#endif //__SRGRAPHLABELBLOCK__

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

