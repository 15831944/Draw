///////////////////////////////////////////////////////////////////////////////
// GxHtmlW.h : Interface for the CGXHtmlW class.
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

#ifndef _GXHTMLRW_H_
#define _GXHTMLRW_H_

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// // #include <StingrayExportDefs.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define gxHTML			_T("html")
#define gxHEAD			_T("head")
#define gxBODY			_T("body")
#define gxTITLE			_T("title")
#define gxMETA			_T("meta")
#define gxTABLE			_T("table")
#define gxTR			_T("tr")
#define gxTH			_T("th")
#define gxTD			_T("td")
#define gxFONT			_T("font")
#define gxFBOLD			_T("b")
#define gxFSTRIKE		_T("s")
#define gxFITALIC		_T("i")
#define gxFUNDERLINE	_T("u")
#define gxA				_T("a")

#define gxSPACE		_T("&nbsp;")

#define BEGIN_GX_TAG_MAP(xClass) \
	CGXTagHandlerEntry xClass::_gxTagHandlerEntries[] = {\

#define END_GX_TAG_MAP() \
	CGXTagHandlerEntry(NULL, _T("")), \
};

#define GX_TAG_MAP_ENTRY(strTag) \
	CGXTagHandlerEntry(new CGXTagDefaultHandler(strTag), strTag),

#define GX_TAG_MAP_ENTRY1(strTag, handler) \
	CGXTagHandlerEntry(new handler(strTag), strTag),


struct CellSpan
{
	int row;
	int col;
	inline CellSpan() 
	{
		row = col = 0;
	}
};

struct CGXTagInfo
{
	CString strAttrib;
	CString strContent;
	BOOL	bWrapByNewline;  // Need newline to wrap the content?
	BOOL	bEndingNewline; // Need newline at the end of the tag?
	inline CGXTagInfo(LPCTSTR lpszAttrib, LPCTSTR lpszContent, BOOL _bWrapByNewline = TRUE, BOOL _bEndingNewline = TRUE)
		: strAttrib(lpszAttrib), strContent(lpszContent)
	{
		bWrapByNewline = _bWrapByNewline;
		bEndingNewline = _bEndingNewline;
	}
};

class CGXTagHandler
{
protected:
	CString strTag;

public:
	inline CGXTagHandler(LPCTSTR lpszTag)
		: strTag(lpszTag)
	{
		strTag.TrimLeft();
		strTag.TrimRight();
	}
	inline virtual ~CGXTagHandler() {};

	virtual CString ComposeOutput(const CGXTagInfo& tagInfo) = 0;
};

class CGXTagDefaultHandler : public CGXTagHandler
{
public:
	inline CGXTagDefaultHandler(LPCTSTR lpszTag)
		: CGXTagHandler(lpszTag)
	{}
	inline virtual ~CGXTagDefaultHandler() {}
	GRID_API virtual CString ComposeOutput(const CGXTagInfo& tagInfo);
};

struct CGXTagHandlerEntry
{
	CGXTagHandler* pHandler;
	CString strTag;

	inline CGXTagHandlerEntry(CGXTagHandler* _pHandler, LPCTSTR lpszTag)
		: pHandler(_pHandler), strTag(lpszTag)
	{
	}
	inline virtual ~CGXTagHandlerEntry()
	{
		if( pHandler != NULL )
			delete pHandler;
		pHandler = NULL;
	}
};


/////////////////////////////
// AutoDuck tag block block for CGXHtmlW  
// adinsert AutoDuck insertion point for CGXHtmlW  
//@topic CGXHtmlW   Class Overview |
//TODO Add your class overview here...

//@doc CGXHtmlW  
//@class This class adds HTML output support for Objective Grid. Application can choose to
//write a rectangular portion of the grid into HTML table. If no selection range is passed
//in, the write proceedure output the whole grid into a HTML table. If you passed in a
//selection range in the grid, then only the selected portion of the grid will be output
//to the HTML table. When output the grid into
//HTML table, application can change the output format by writing custom tag handler. By default,
//all the HTML table related tags is handled by the CGXTagDefaultHandler class. To use custom tag
//handler, you just need to add proper tag entry into the tag map table specifying the name of the
//tag handler class.

class CGXHtmlW  
{
protected:
	CString		 m_strFileName;  // Cache the file name
	CGXGridCore* m_pGrid;
	CGXRange*	 m_pSelectRange;

	GRID_API static CGXTagHandlerEntry _gxTagHandlerEntries[];

public:
	//@cmember
	/* Get the pointer to the tag handler map */
	GRID_API static CGXTagHandlerEntry* GetHandlerEntries() { return _gxTagHandlerEntries; }
	//@cmember
	/* Get the tag handler map size */
	GRID_API static int	GetMapSize();

	//@cmember
	/* Composes the table cell attributes as a string */
	GRID_API virtual CString GetCellAttribString(const CGXStyle& style, BOOL bCovered, const CellSpan& cellSpan);
	//@cmember
	/* Composes the table cell string */
	GRID_API virtual CString GetTableCellString(int nRight, int nBottom, 
								 int nRow, int& nNextCol, 
								 CellSpan& cellSpan, BOOL bHeader = FALSE);
	//@cmember
	/* Composes the table cell font string */
	GRID_API virtual CString GetFontAttribString(const CGXStyle& style);
	//@cmember
	/* Composes the table cell contents string */
	GRID_API virtual CString GetCellContentString(int nRow, int nCol, const CGXStyle& style);
	//@cmember
	/* Composes the whole table attributes string */
	GRID_API virtual CString GetTableAttrib();
	//@cmember
	/* Composes the whole table contents as a single string */
	GRID_API virtual CString GetTableString();
	
	//@cmember
	/* Writes the portion of the grid as HTML into the given string */
	GRID_API void WriteToString(CString& s);
	//@cmember
	/* Writes the portion of the grid as HTML into the given file */
	GRID_API void WriteToFile(LPCTSTR lpszFileName);

	//@cmember
	/* Search the given tag from the tag handler map for its handler */
	GRID_API CGXTagHandler* LookupTag(LPCTSTR lpszTag);

	//@cmember
	/* Create CGXHtmlW object */
	GRID_API CGXHtmlW(CGXGridCore* pGrid, CGXRange* pSelectRange = NULL);
	GRID_API virtual ~CGXHtmlW();


	//@cmember
	/* Get the grid view this object is working with */
	inline CGXGridCore* Grid() { return m_pGrid; }
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _GXHTMLRW_H_
