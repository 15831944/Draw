///////////////////////////////////////////////////////////////////////////////
// SRGraphTitle.h
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
//@doc SRGraphTitle
//@module SRGraphTitle.h|  definition of the graph title class<nl>
//Written by Bob Powell (www.roguewave.com)
#ifndef __SRGRAPHTITLE__
#define __SRGRAPHTITLE__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//////////////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphTitle

//@doc SRGraphTitle

//@mdata int  | SRGraphTitle | m_nJustification | Text justification<nl>
//0=Left justified<nl>
//1=Right justified<nl>
//2=Centered in component
//@see <mf SRGraphTitle::SetText> <mf SRGraphTitle::GetJustification> <mf SRGraphTitle::SetJustification>

//@mdata CString  | SRGraphTitle | m_strTitle | Text to be displayed
//@rem Note that setting this text outside the draw loop will never be seen because 
//the component updates the text using <mf SRGraphTitle::GetParentContent> every draw cycle.

//@mdata CFont  | SRGraphTitle | m_Font | CFont object which defines the text style to be used
//@see <mf SRGraphTitle::GetFont> <mf SRGraphTitle::SetFont>

//@mdata COLORREF  | SRGraphTitle | m_RGBTextColor | Sets the RGB color used to display text
//@see <mf SRGraphTitle::SetTextColor> <mf SRGraphTitle::GetTextColor>

//@mdata BOOL  | SRGraphTitle | MakeFont | Internal font update semaphore<nl>
//When TRUE the component updates the font information and creates a new font.<nl>
//Use this variable to ensure correct updating of fonts after changes to a font style.

//@mdata int  | SRGraphTitle | m_nSize | Font size -- positive numbers specify the font size 
//in points, negative numbers specify the size in screen pixels
//
//@ex For example: | <nl>
//	SetFontSize(10);	
//	SetMakeFont();	// Sets a font of 10 points
//
//	SetFontSize(-10);
//	SetMakeFont();	//Sets a font of 10 pixels
//@see <mf SRGraphTitle::SetFontSize> <mf SRGraphTitle::GetFontSize> <md SRGraphTitle::MakeFont> <mf SRGraphTitle::SetMakeFont>

//@mdata int | SRGraphTitle | m_nStyle | Bitwise flag which defines the font settings for bold, italic and other styles<nl>
//bit 0 = CX_FONT_BOLD<nl>
//bit 1 = CX_FONT_ITALIC<nl>
//bit 2 = CX_FONT_UNDERLINE<nl>
//bit 3 = CX_FONT_STRIKEOUT<nl>
//bit 4 = CX_FONT_AUTOSIZE<nl>
//bit 5 = CX_FONT_EMBOSS<nl>
//bit 6 = CX_FONT_RELIEF<nl>
//bit 7 = CX_FONT_NOWRAP<nl> 
//<nl>
//The AUTOSIZE bit may be set to allow the font to be sized by the object using the font. The CalcFontAutoSize() function returns 
//a value used to define the font height. This value may be modified to suit your application. For example. SRGraphDisplay returns the 
//font as 1/25th of the available display height and SRGraphLegend returns it as 1/10th. Your own derived classes may return values based 
//upon other calculations.<nl><nl>
//Objective Chart 6.01 added the ability to display fonts with an embossed style. When the EMBOSS bit is set fonts will be shown with a
//light and dark border which gives the impression of the font being "chiselled" from the surrounding color. The RELIEF bit may be set 
//to show the fonts "raised" out of the background or reset to show them chiselled into the background.<nl>
//This font style is very effective when a dark grey color is used (CXCLR_GRAY70) as the text color.<nl><nl> 
//Objective Chart 6.03 added the capability to wrap text to fit the available space for titles and text panels. 
//You can turn off word wrapping for titles and the text panels by including CX_FONT_NOWRAP in the font style.
//
//@see <mf SRGraphTitle::SetFontStyle> <mf SRGraphTitle::GetFontStyle>

//@mdata CString | SRGraphTitle | m_strFaceName | Name of the current typeface (eg. "Times New Roman")
//@see <mf SRGraphTitle::SetFaceName> <mf SRGraphTitle::GetFaceName> <mf SRGraphTitle::SetFont>

//@mfunc  void | SRGraphTitle |  SetFontSize | Set the font size
//@parm int | Size | Desired font size
//@rem Positive numbers make point size fonts. The absolute values of negative numbers make pixel sized fonts.
//@see <mf SRGraphTitle::GetFontSize> <md SRGraphTitle::m_nFontSize>

//@mfunc  void | SRGraphTitle |  SetFontStyle | Sets the bitwise flags which define the font style
//@parm int | style | Logical OR combination of the required flags
//@see For bit combinations... <md SRGraphTitle::m_nStyle> <mf SRGraphTitle::GetFontStyle>

//@mfunc  void | SRGraphTitle |  SetJustification | Sets the justification style
//@parm int | Justification | Type of justification desired
//@see For justification types... <md SRGraphTitle::m_nJustification> <mf SRGraphTitle::GetJustification>

//@mfunc  int | SRGraphTitle | GetFontSize | Fetches the current font size
//@rdesc Contents of the m_nSize member
//@see <mf SRGraphTitle::SetSize> <md SRGraphTitle::m_nSize>

//@mfunc  int | SRGraphTitle |  GetFontStyle | Fetches the current font style
//@rdesc Contents of the m_nStyle member
//@see <mf SRGraphTitle::SetFontStyle> <md SRGraphTitle::m_nStyle>

//@mfunc  int | SRGraphTitle |  GetJustification | Fetches the current font justification
//@rdesc Contents of the m_nJustification member
//@see <mf SRGraphTitle::SetJustification> <md SRGraphTitle::m_nJustification>

//@mfunc  COLORREF | SRGraphTitle | GetTextColor | Fetches the color currently used for text
//@rdesc Contents of the m_RGBTextColor member
//@see <mf SRGraphTitle::SetTextColor> <md SRGraphTitle::m_RGBTextColor>

//@mfunc  CString& | SRGraphTitle | GetText | Fetches the current text for this title
//@rdesc Contents of the m_strTitle member
//@see <mf SRGraphTitle::SetText> <md SRGraphTitle::m_strTitle>

//@mfunc  CFont* | SRGraphTitle | GetFont | Returns a pointer to the m_Font member
//@rdesc Pointer to the m_Font member
//@see <md SRGraphTitle::m_Font> <mf SRGraphTitle::SetFont>

//@mfunc void | SRGraphTitle | SetMakeFont | Sets or resets the MakeFont variable<nl>//You should set the MakeFont variable after changing font styles<nl>
//The font is updated at draw time and it is only changed if the MakeFont semaphore is set.
//@parm BOOL | make | TRUE (default) to set the semaphore, FALSE to reset
//@rem This method is used because the UpdateFont routine needs to get information directly 
//from the CDC used to draw the font. Therefore the request to change font style is deferred 
//until the m_pDC pointer is known to be valid.
//@see <md SRGraphTitle::MakeFont> <mf SRGraphTitle::UpdateFont> <mf SRGraphTitle::SetFontStyle> <mf SRGraphTitle::SetFontSize>

//@mfunc void | SRGraphTitle | SetTextColor | Initializes the text color used in this object
//@parm COLORREF | c | Desired color

//@doc SRGraphTitle
//@mdata LOGFONT *  | SRGraphTitle | m_pLogFont | Normally NULLthis pointer may be set to point to a valid LOGFONT structure.<nl>
//This structure will then override the font creation process and the fonts will be defined by the values in the LOGFONT structure supplied.<nl>
//@devnote The object will not delete this structure if it is left in place during the destruction of the title component. It is up to the programmer to
// ensure that correct memory management is carried out.

//@doc SRGraphTitle
//@mfunc LOGFONT  *  | SRGraphTitle |GetLogFont | Returns a pointer to the LOGFONT stored in this object 

//@doc SRGraphTitle
//@mfunc void  | SRGraphTitle | SetUseOwnText | Sets the m_bUseOwnText flag 
//@parm BOOL | b | TRUE to display own text -- SetText(),<nl> FALSE to display parent's text -- SRGraph::SetGraphTitle()

//@doc SRGraphTitle
//@mfunc BOOL  | SRGraphTitle | GetUseOwnText | Retrieves the m_bUseOwnText flag

//@doc SRGraphTitle
//@mdata BOOL  | SRGraphTitle | m_bUseOwnText | If TRUE, the title displays the internally stored string provided by SetText().<nl>
//If FALSE (default), the title obtains its text from its parent SRGraph object.<nl>
//This text specified by calling SRGraph::SetGraphTitle().

// adinsert for SRGraphTitle
//$head Component classes
//$level 1
//////////////////////////////////////////////////////////////////
//@doc SRGraphTitle
//@class Title manager derived from <c SRGraphComponent>
//@base public | SRGraphComponent
class SRGraphTitle : public SRGraphComponent
{
//@access protected data members
protected:
	//@cmember
	/* Type of text justification to use*/
	int m_nJustification;
	//@cmember
	/* Title text*/
	CString m_strTitle;
	//@cmember
	/* Font in which to display text*/
	CFont m_Font;
	//@cmember
	/* Color of the text*/
	COLORREF m_RGBTextColor;
	//@cmember
	/* Semaphore which signifies that a font has been set or that an existing font needs updating*/
	BOOL MakeFont;
	//@cmember
	/* Font size -- negative numbers set sizes in pixels, positive numbers set sizes in points*/
	int m_nSize;
	//@cmember
	/* Style of font*/
	int m_nStyle;
	//@cmember
	/* Font typeface*/
	CString m_strFaceName;

	//@cmember
	/* Flags display of internal text (SetText) or parent's text (GetParentText) */
	BOOL	m_bUseOwnText;

//@access Protected member functions
protected:
	//@cmember
	/* A pointer to an optional LOGFONT that will define the font*/
	LOGFONT * m_pLogFont;

	//@cmember
	/* Draws the text*/
	CHART_API virtual void DrawForeground();

	//@cmember
	/* Keeps font data current*/
	CHART_API virtual BOOL UpdateFont();

	//@cmember
	/* Retrieves pertinent data from the parent*/
	CHART_API virtual void GetParentContent();

//@access public member functions
public:
	//@cmember
	/* Get the number of lines of the text string separated by '\n' */
	CHART_API virtual int GetLineCount(LPCTSTR lpszText);

	//@cmember
	/* Searches the text for new line characters ('\r' or "\r\n") and computes where lines should be broken (word wrap) to fit the text in the specified rectangle*/
	CHART_API virtual int ComputeLineBreaks( LPCTSTR text, int nCount, LPRECT rc,
				BOOL bWrapText, int* LineBreaks, int* LineLengths, 	int nMaxBreaks);

	//@cmember
	/* Draw multiple lines of text vertically centered at the rectangle area */
	CHART_API virtual void DrawText(LPCTSTR lpText, LPRECT lpRect);
	//@cmember
	/* Draw multiple lines of text vertically centered at the rectangle area */
	CHART_API virtual void DrawText(const CString& str, const CRect& rc);
	//@cmember
	/* Draw multiple lines of text vertically centered at the rectangle area optionally wrapping text*/
	CHART_API virtual void DrawText(const CString &str, const CRect &rc, BOOL bWrapText);

	//@cmember
	/* Flag to decide if this component use parent's title text or its own */
	inline void SetUseOwnText(BOOL b) { m_bUseOwnText = b; }
	//@cmember
	/* Get the flag about whether to use its own text or from the parent graph */
	inline BOOL GetUseOwnText() { return m_bUseOwnText; }

	//@cmember
	/* Initializes the font using the supplied LOGFONT */
	CHART_API virtual void SetLogFont(LOGFONT * v);
	//@cmember
	/* Returns a pointer to the LOGFONT stored in this object */
	inline LOGFONT * GetLogFont(){return m_pLogFont;}
	//@cmember
	/* Calculates the font size based on 90% of the title panel height*/
	CHART_API virtual int CalcFontAutoSize();
	//@cmember
	/* Sets or resets the MakeFont semaphore*/
	CHART_API virtual void SetMakeFont(BOOL make=TRUE);
	//@cmember
	/* Returns logical size of text*/
	CHART_API virtual CSize GetTextDimension(LPCTSTR text);
	//@cmember
	/* Returns logical size of text with optional wordwrap*/
 	CHART_API virtual CSize GetTextDimension(LPCTSTR text, BOOL bWrapText, int nWrapWidth=0);
	//@cmember
	/* Constructor*/
	CHART_API SRGraphTitle();
	//@cmember
	/* Sets the point or pixel size of the current font*/
	inline void SetFontSize(int Size){m_nSize=Size;}
    CHART_API virtual void SetFontSize(double dblSize);
	//@cmember
	/* Sets the style of the font (ie. bold, underline, etc.)*/
	inline void SetFontStyle(int style){m_nStyle=style;}
	//@cmember
	/* Sets the font justification to left (0), right (1) or centered (2)*/
	inline void SetJustification(int Justification){m_nJustification=Justification;}
	//@cmember
	/* Fetches the font size data*/
	CHART_API int GetFontSize();
	//@cmember
	/* Fetches the font style data*/
	inline int GetFontStyle(){return m_nStyle;}
	//@cmember
	/* Fetches the font justification*/
	inline int GetJustification(){return m_nJustification;}
	//@cmember
	/* Fetches the RGB color used to display text*/
	CHART_API virtual COLORREF GetTextColor();
	//@cmember
	/* Returns the title text itself*/
	inline CString& GetText(){return m_strTitle;}
	//@cmember
	/* Fetches a pointer to the m_Font (CFont) object from this component*/
	inline CFont* GetFont(){return &m_Font;}
	//@cmember
	/* Sets the typeface name (ie. "Times New Roman")*/
	CHART_API virtual void SetFaceName(CString& FaceName);
	CHART_API virtual void SetFaceName(LPCTSTR FaceName);
	//@cmember
	/* Fetches the type face name currently in use*/
	CHART_API virtual CString& GetFaceName();

#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Reads and parses a chart template line*/
	CHART_API virtual int ReadTemplateLine(LPCTSTR line);
	//@cmember
	/* Writes the name "title" to the template file*/
	CHART_API virtual void WriteName(CStdioFile* file);
	//@cmember
	/* Outputs the current font details to the template file*/
	CHART_API virtual void WriteFontParameters(CStdioFile* file);
#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE


#ifdef _DEBUG

	CHART_API void Dump(CDumpContext& dc) const;

#endif


	CHART_DECLARE_SERIAL(SRGraphTitle);
	//@cmember
	/* Stores or retrieves information about the title via a CArchive*/
	CHART_API virtual void Serialize(CArchive &ar);

	//@cmember
	/* Destructor -- ensures that no GDI objects remain*/
	CHART_API virtual ~SRGraphTitle();

	//@cmember
	/* Sets font size, style, and typeface*/
	CHART_API virtual BOOL SetFont(int nSize,int nStyle,CString FaceName);

	//@cmember
	/* Modifies the contents of the text*/
	CHART_API virtual void SetText(LPCTSTR text,int justification=0);

	//@cmember
	/* Sets the color of text displayed to an RGB value*/
	CHART_API virtual void SetTextColor(COLORREF color);

	// XML formatter for SRGraphTitle
	friend class SRGraphTitleFTR;
};


/////////////////////////////
// AutoDuck tag block for SRGraphTitleResizeable 
//@doc SRGraphTitleResizeable 
//@mdata BOOL | SRGraphTitleResizeable | m_bResize | Semaphore to resize the component rectangle to fit the title text (default=TRUE)
//@xref <mf SRGraphTitleResizeable::SetResize> <mf SRGraphTitleResizeable::GetResize>

//@mfunc void  | SRGraphTitleResizeable | SetResize | Sets the auto-resize flag
//@parm BOOL  | b | Set TRUE to automatically resize the component rectangle to fit the title text. 
//@xref <md SRGraphTitleResizeable::m_bResize>  <mf SRGraphTitleResizeable::GetResize>

//@mfunc BOOL  | SRGraphTitleResizeable | GetResize | Returns the resize flag
//@xref <md SRGraphTitleResizeable::m_bResize>  <mf SRGraphTitleResizeable::SetResize>

//@mdata BOOL | SRGraphTitleResizeable | m_bSizeForeground | Internal semaphore signifying a demand to recalculate the component size
//@xref <mf SRGraphTitleResizeable::DrawForeground>

//@mdata SRGraphRect  | SRGraphTitleResizeable | m_FinalRect | The final, resized component rectangle in device independent coordinates
//@comm m_FinalRect contains the resized rectangle determined by the last call to Draw() or CalcFinalRect()
//@xref <mf SRGraphTitleResizeable::GetFinalRect>

//@mfunc SRGraphRect  | SRGraphTitleResizeable | GetFinalRect | Returns actual, resized component rectangle determined by previous call to Draw() or CalcFinalRect()
//@xref <md SRGraphTitleResizeable::m_FinalRect>

// adinsert AutoDuck insertion point for SRGraphTitleResizeable 
//@doc SRGraphTitleResizeable 
//@class A derivative of SRGraphTitle <c SRGraphTitle> that can resize its component rectangle to fit its text
//@base public | SRGraphTitle
class SRGraphTitleResizeable : public SRGraphTitle
{
//@access Protected data members
protected:
	//@cmember
	/* The final, resized component rectangle in device independent coordinates*/
	SRGraphRect m_FinalRect;
	//@cmember
	/* Semaphore to resize the component rectangle to fit the title text (default=TRUE)*/
	BOOL m_bResize;
	//@cmember
	/* Internal semaphore signifying a demand to recalculate the component size -- see <mf SRGraphTitleResizeable::DrawForeground>*/
	BOOL m_bSizeForeground;

//@access public member functions
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGraphTitleResizeable();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphTitleResizeable();
	//@cmember
	/* Set TRUE if the legend component rectangle is to be resized to fit the legend data*/
	inline virtual void SetResize(BOOL b=TRUE)	{m_bResize=b;}
	//@cmember
	/* Returns TRUE if the legend component rectangle is resizable*/
	inline virtual BOOL GetResize()	{return m_bResize;}
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
	/* To store or retrieve information via a CArchive*/
	CHART_API virtual void Serialize(CArchive& ar); 
	//@cmember
	/* NEW 6.01 SP1 The legend has a new file setting. */
	CHART_API virtual CScale SetComponentFileVersion();
	
//@access Protected member functions
protected:
	//@cmember 
	/* Draws text or recalculates the size of the component */
	CHART_API virtual void DrawForeground();

	CHART_DECLARE_SERIAL(SRGraphTitleResizeable);

	// XML formatter for SRGraphTitleResizeable
	friend class SRGraphTitleResizeableFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGRAPHTITLE__
