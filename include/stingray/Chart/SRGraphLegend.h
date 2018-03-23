///////////////////////////////////////////////////////////////////////////////
// SRGraphLegend.h
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
//@doc SRGraphLegend
//@module SRGComp.h|  definition of the graph legend class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGraphLegend.h: definition of the graph legend class
//
/////////////////////////////////////////////////////////////
#ifndef __SRGRAPHLEGEND__
#define __SRGRAPHLEGEND__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphLegend
//
// cmember tags only used for some data members

//@doc SRGraphLegend

//@mdata SRGDisplayBase * | SRGraphLegend | m_pDisplay | Pointer to a graph display component
//@rem When a legend finds itself immediately after a display in the component list, 
//it locks itself to it and displays legend information tailiored to that display type. 
//The locked legend will examine the scope of the graph display to find out 
//what range of data needs keys, etc.

//@mdata CRect | SRGraphLegend | m_LegendRect | Rectangle used to keep track of the automatically resized legend's extents

//@mdata int  | SRGraphLegend | m_nKeyHeight | Stores the height of the key items between passes

//@mfunc double  | SRGraphLegend | GetKeySize | Retrieves the size of the graphic keys

//@mdata BOOL | SRGraphLegend | m_bKeepTop | Semaphore used when m_bAutoSizeY == TRUE to specify to which side (top if TRUE, bottom if FALSE) of the component rectangle the legend data is to be grouped.
//@xref <md SRGraphLegend::m_bAutoSizeY> <mf SRGraphLegend::SetAutoSize>
//@mdata BOOL | SRGraphLegend | m_bKeepLeft | Semaphore used when m_bAutoSizeX == TRUE to specify to which side (left if TRUE, right if FALSE) of the component rectangle the legend data is to be grouped.
//@xref <md SRGraphLegend::m_bAutoSizeX> <mf SRGraphLegend::SetAutoSize>

//@mdata BOOL | SRGraphLegend | m_bAutoSizeX | Semaphore determining how legend data are positioned. If FALSE, the legend keys are spaced uniformly across 
//the width of the component rectangle. If TRUE, the keys are bunched to the left or right of the component rectangle depending on the value of m_bKeepLeft.
//@xref <md SRGraphLegend::m_bKeepLeft> <mf SRGraphLegend::SetAutoSize>
//@mdata BOOL | SRGraphLegend | m_bAutoSizeY | Semaphore determining how legend data are positioned. If FALSE, the legend keys are spaced uniformly down 
//the height of the component rectangle. If TRUE, the keys are bunched to the top or bottom of the component rectangle depending on the value of m_bKeepTop.
//@xref <md SRGraphLegend::m_bKeepTop> <mf SRGraphLegend::SetAutoSize>

//@mdata BOOL | SRGraphLegend | m_bResize | Semaphore to resize the component rectangle to fit the legend data
//@rem This flag is ineffective unless m_bAutoSizeX and/or m_bAutoSizeY are also set.
//@xref <md SRGraphLegend::m_bAutoSizeX> <md SRGraphLegend::m_bAutoSizeY> <mf SRGraphLegend::SetAutoSize> <mf SRGraphLegend::SetResize>

//@mfunc void  | SRGraphLegend | SetResize | Sets the auto-resize flag
//@parm BOOL  | b=TRUE | Set TRUE to automatically resize the component rectangle to fit the legend data. 
//@rem This flag is ineffective unless m_bAutoSizeX and/or m_bAutoSizeY are also set.
//@xref <md SRGraphLegend::m_bResize> <md SRGraphLegend::m_bAutoSizeX> <md SRGraphLegend::m_bAutoSizeY> <mf SRGraphLegend::SetAutoSize>

//@mfunc BOOL  | SRGraphLegend | GetResize | Returns the resize flag

//@mdata SRGraphRect  | SRGraphLegend | m_FinalRect | The final, resized component rectangle in device independent coordinates
//@comm m_FinalRect contains the resized rectangle determined by the last call to Draw() or CalcFinalRect()
//@xref <mf SRGraphLegend::GetFinalRect>

//@mfunc SRGraphRect  | SRGraphLegend | GetFinalRect | Returns actual, resized component rectangle determined by previous call to Draw() or CalcFinalRect()
//@xref <md SRGraphLegend::m_FinalRect>

//@mdata BOOL | SRGraphLegend | m_bSizeForeground | Internal semaphore signifying a demand to recalculate the component size
//@xref <mf SRGraphLegend::DrawForeground>

//@mdata double | SRGraphLegend | m_dKeySize | Width of key data
//@devnote A key is the pattern or color filled box which accompanies the text in the legend panel. 
//Heights for keys are calculated according to the height of text used. Widths are decided by you or 
//the user via a template or explicit initialization of the m_dKeySize member.

//@mdata BOOL | SRGraphLegend | m_nKeyCount | Count of the number of keys currently in this legend.

//@mdata SRGraphLabelBlock  | SRGraphLegend | m_LegendLabels | List of text items used to annotate the legend keys


//@doc SRGraphLegend
//@mfunc void  | SRGraphLegend | SetKeyAnnotationLineCount | This option allows the setting of the maximum number of lines in a legend key.
//@parm int  | nLineCount | The maximum number of lines allowed

//@doc SRGraphLegend
//@mfunc int   | SRGraphLegend | GetKeyAnnotationLineCount | Returns the setting of the legend line count.

//@doc SRGraphLegend
//@mdata int   | SRGraphLegend | m_nMaxLine | data member comment

//@doc SRGraphLegend
//@mdata int   | SRGraphLegend | m_nMaxChar | data member comment

//@doc SRGraphLegend
//@mfunc void | SRGraphLegend | SetKeyAnnotationCharCount | Sets the number of char that will displayed in the key annotation
//@parm int | nChar | the maximum number of characters allowed

//@doc SRGraphLegend
//@mfunc int | SRGraphLegend | GetKeyAnnotationCharCount | Get the number of char that will displayed in the key annotation

//adinsert
//$head Component classes
//$level 1


//@doc SRGraphLegend
//@class Handles painting of the legend panel and inherits font management from the SRGraphTitle class
//@base public | SRGraphTitle
class SRGraphLegend : public SRGraphTitle
{
//@access Protected data members
protected:
	//@cmember
	/* Stores the height of the key items between passes.*/
	int m_nKeyHeight;
	//cmember List of text items used to annotate the legend keys
	SRGraphLabelBlock m_LegendLabels;
	//@cmember
	/* Pointer to the SRGDisplayBase to which this legend has locked itself (do not alter)*/
	SRGDisplayBase * m_pDisplay;
	//@cmember
	/* Basic rectangle of the legend panel*/
	CRect m_LegendRect;
	//@cmember
	/* Semaphore to prevent moving the horizontal origin of the rectangle during auto resizing*/
	BOOL m_bKeepTop;
	//@cmember
	/* Semaphore to prevent moving the vertical origin of the rectangle during auto resizing*/
	BOOL m_bKeepLeft;
	//@cmember
	/* Semaphore to prevent changing the height of the rectangle during auto resizing*/
	BOOL m_bAutoSizeX;
	//@cmember
	/* TRUE if the legend is to automatically extend its bottom boundary to contain the list*/
	BOOL m_bAutoSizeY;
	//@cmember
	/* Semaphore to resize the component rectangle to fit the legend data*/
	BOOL m_bResize;
	//@cmember
	/* The final, resized component rectangle in device independent coordinates*/
	SRGraphRect m_FinalRect;
	//@cmember
	/* Semaphore signifying a demand to recalculate the component size -- see <mf SRGraphLegend::DrawForeground>*/
	BOOL m_bSizeForeground;
	//@cmember
	/* Width of key data*/
	double m_dKeySize;
	//@cmember
	/* Count of the number of keys currently in this legend.*/
	int m_nKeyCount;

	//@cmember
	/* Count of max number of character that will display in the annotation text*/
	int	m_nMaxChar;
	//@cmember
	/* Count of the maximum number of lines the legend will display */
	int	m_nMaxLine;
	
//@access Protected member functions
protected:
	//@cmember 
	/* Draws text or recalculates the size of the component */
	CHART_API virtual void DrawForeground();
	//@cmember
	/* Draws legend keys onto the component*/
	CHART_API virtual void DrawKey(CPoint topleft,CPoint bottomright, int index, int group, int CurrentKey);
	//@cmember
	/* Calculates size of graphic keys*/
	CHART_API virtual int CalcKeySize();
	//@cmember
	/* Customization system for legend keys*/
	CHART_API virtual void DrawCustomKey(CPoint topleft,CPoint bottomright,int group,int index,SRGraphStyle *ptrStyle);
	//@cmember
	/* Sets the group and index stepping interval for legends*/
	CHART_API virtual void SetCustomLegendSteps();
	//@cmember 
	/* Retrieves the legend style replacing CX_LEGEND_AUTOMATIC with an appropriate style*/
	CHART_API DWORD GetLegendStyle();
	//@cmember
	/* Return the size of a typical character in font pFont*/
	CHART_API virtual CSize CalcCharSize(CFont* pFont);

//@access public member functions
public:
	//@cmember
	/* Sets the number of char that will displayed in the key annotation*/
	inline void SetKeyAnnotationCharCount(int nChar) { m_nMaxChar = nChar; }
	//@cmember
	/* Get the number of char that will displayed in the key annotation*/
	inline int	 GetKeyAnnotationCharCount(){ return m_nMaxChar;}

	//@cmember
	/* Sets the maximum number of lines in the legend keys. */
	inline void SetKeyAnnotationLineCount(int nLineCount) { m_nMaxLine = nLineCount; }
	//@cmember
	/* Returns the maximum number of lines in the legend keys. */
	inline int  GetKeyAnnotationLineCount() { return m_nMaxLine; }

	//@cmember
	/* Sets default key size according to measurement mode*/
	CHART_API virtual void SetSizeDefaults();
	//@cmember
	/* Calculates font size for the legend class*/
	CHART_API virtual int CalcFontAutoSize();
	//@cmember
	/* NEW 6.01 SP1 The legend has a new file setting. */
	CHART_API virtual CScale SetComponentFileVersion();

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Writes special legend parameters to a template file*/
	CHART_API virtual void WriteSpecificParameters(CStdioFile *f);
	//@cmember
	/* Reads a legend line from a template file*/
	CHART_API virtual int ReadTemplateLine(LPCTSTR line);
	//@cmember
	/* Writes the object's name to a template file*/
	CHART_API virtual void WriteName(CStdioFile *file);
#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphLegend();
	//@cmember
	/* Initializes the size of graphic keys*/
	CHART_API void SetKeySize(double keysize);
	//@cmember
	/* Retrieves the size of the graphic keys*/
	inline double GetKeySize(){return m_dKeySize;}
	//@cmember,menum
	/* Bit flags used by SetAutoSize()*/
	enum AutoSize_Flags {
	AUTO_SIZE_X = 1, //@@emem Set to bunch legend data to the right or left
	AUTO_SIZE_Y = 2, //@@emem Set to bunch legend data to the top or bottom
	KEEP_LEFT   = 4, //@@emem Set this bit along with AUTO_SIZE_X to bunch to the left
	KEEP_TOP    = 8  //@@emem Set this bit along with AUTO_SIZE_Y to bunch to the top
	};
	//@cmember
	/* Initializes the auto-sizing flags*/
	CHART_API virtual void SetAutoSize(int sizebits);
	//@cmember
	/* Set TRUE if the legend component rectangle is to be resized to fit the legend data*/
	inline virtual void SetResize(BOOL b=TRUE){m_bResize=b;}
	//@cmember
	/* Returns TRUE if the legend component rectangle is resizable*/
	inline virtual BOOL GetResize(){return m_bResize;}
	//@cmember
	/* Returns actual, resized component rectangle -- can be called outside of draw cycle*/
	CHART_API virtual SRGraphRect CalcFinalRect(CDC *pDC,CWnd *pCWnd);
	//@cmember
	/* Returns actual, resized component rectangle determined by previous call to Draw() or CalcFinalRect()*/
	inline SRGraphRect GetFinalRect()  { return m_FinalRect; }

	//@cmember
	/* Overrides <mf SRGraphComponent::Draw> to enable automatic resizing*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pCWnd);
	//@cmember
	/* Retrieves pertinent data from the parent <c SRGraph>*/
	CHART_API virtual void GetParentContent();
	//@cmember
	/* Constructor*/
	CHART_API SRGraphLegend();

	CHART_DECLARE_SERIAL(SRGraphLegend);
	//@cmember
	/* To store or retrieve information via a CArchive*/
	CHART_API virtual void Serialize(CArchive& ar); 

	// XML Formatter for SRGraphLegend
	friend class SRGraphLegendFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGRAPHLEGEND__
