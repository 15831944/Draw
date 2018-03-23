
#pragma once

#ifndef _GXCORE_H_
#define _GXCORE_H_

#ifndef _GXTCHAR_H_
#include "gxtchar.h" 
#endif

#ifndef _GXABSTR_H_
#include "gxabstr.h"
#endif

#ifndef _GXPLUGIN_H_
#include "gxplugin.h"
#endif

#ifndef _GXSTYLES_H_
#include "gxstyles.h"   // CGXStyle
#endif

#ifndef _GXCOLL_H_
#include "gxcoll.h"     // Collections
#endif

#ifndef _GXIME_H_
#include "gxime.h"
#endif

#include <afxtempl.h>
// // #include <StingrayExportDefs.h>


// constants

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// classes declared in this header file

class CGXRange;
class CGXRangeList;
class CGXProperties;
class CGXGridCore;
class CGXGridParam;
class CGXSortInfoArray;
struct CGXSortInfo;

// OLE Drag&Drop support
class CGXNoOleDataObjectProxy;
class CGXNoOleDataSourceProxy;

// Tooltip support
class CGXNoToolTipCtrlProxy;

// forward declarations;

class CGXPrintDevice;
class CGXControl;
class CGXData;
class CGXSpanCellPool;
class CGXCoveredCellPool;
class CGXDelayedRangePool;

class COleDataObject;
class COleDropSource;
class COleDropSource;

class CGXCommand;
class CGXGridHint;

// header file

// #define TICKCOUNT       // used to test performance
// #define _CCHIT           // used to test LookupStyleRowCol hits

// update technique and SetEditCell flags
// used by all command and update methods

const UINT   GX_NOREDRAW            = 0x0000;
const UINT   GX_INVALIDATE          = 0x0001;
const UINT   GX_UPDATENOW           = 0x0002;
const UINT   GX_SMART               = 0x0004;

// SetCurrentCell - extra flags
const UINT   GX_SCROLLINVIEW        = 0x0008;
const UINT   GX_DISPLAYEDITWND      = 0x0010;
const UINT   GX_NOSETFOCUS          = 0x0020;
const UINT   GX_NOSYNCCURRENTCELL   = 0x0040;
const UINT   GX_NOSELECTRANGE       = 0x0080;

// Resize rows and cols to fit size - extra flags
const UINT   GX_NOSHRINKSIZE        = 0x0008;

 
// flags for drawing lines used by
// CGXGridCore::DrawGridLine

const UINT   GX_TRACKLINE           = 0x0001;
const UINT   GX_SELDRAGLINE         = 0x0002;
const UINT   GX_ACTIVECELL          = 0x0004;
const UINT   GX_INVERT              = 0x0008;

// Predefined Color Properties
const int    GX_COLOR_GRIDLINES     = 0;
const int    GX_COLOR_FIXEDLINES    = 1;
const int    GX_COLOR_TRACKINGLINE  = 2;
const int    GX_COLOR_DRAGGINGLINE  = 3;
const int    GX_COLOR_BACKGROUND    = 4;

// Flags for Hitting, used in

// CGXGridCore::DoLButtonDown
// CGXGridCore::DoLButtonUp
// CGXGridCore::DoMouseMove
// CGXGridCore::OnLButtonHitRowCol

// CGXGridCore::m_nHitState contains following flags

const WORD GX_HIT            = 0x0001;
const WORD GX_SELECT         = 0x0002;
const WORD GX_HITSTART       = 0x0004;
const WORD GX_HITMOVE        = 0x0008;
const WORD GX_HITEND         = 0x0010;
const WORD GX_HITLEAVE       = 0x0020;
const WORD GX_HITINCELL      = 0x0040;
const WORD GX_CTRLPRESSED    = 0x0080;
const WORD GX_HITCURRENTCELL = 0x0100;
const WORD GX_FILLDRAG		 = 0x0200; // For excel like auto fill support

// used in GetStyleRowCol and StoreStyleRowCol
// indicating that a range and not only one cell is meant to be retrieved
// (either nRow or nCol is 0, see the class-reference)
const int GXRANGETYPE = -1;

// Enums

// GXDirectionType is used for specifying directions
// Some methods using its values are:
// CGXGridCore::DoScroll
// CGXGridCore::OnAutoScroll
// CGXGridCore::OnMoveEdit
// and many more

enum GXDirectionType
{
	GX_UP               = 1,
	GX_LEFT             = 2,
	GX_DOWN             = 3,
	GX_RIGHT            = 4,
	GX_PGDOWN           = 5,
	GX_PGUP             = 6,
	GX_TOP              = 7,
	GX_BOTTOM           = 8,
	GX_MOSTLEFT         = 9,
	GX_MOSTRIGHT        = 10,
	GX_TOPLEFT          = 11,
	GX_BOTTOMRIGHT      = 12
};

// GXHitTestType is used by
// CGXGridCore::HitTest

enum GXHitTestType
{
	GX_NOHIT            = 0,
	GX_VERTLINE         = 1,
	GX_HORZLINE         = 2,
	GX_CELLHIT          = 3,
	GX_HEADERHIT        = 4,
	GX_SELEDGEHIT       = 5,
	GX_FILLHANDLEHIT	= 6,
	GX_HDNCOL_VERTLINE	= 7,
	GX_HDNROW_HORZLINE	= 8,
};

// GXTrackingType specifies, if the user is tracking a vertical or horizontal line
// used by:
// CGXGridCore::OnStartTracking
// CGXGridCore::OnEndTracking
// CGXGridCore::OnMoveTracking

enum GXTrackingType
{
	GX_TRACKHEIGHT      = 1,
	GX_TRACKWIDTH       = 2
};

// GXDragModeType specifies, if the user is dragging rows or columns
enum GXDragModeType
{
	GX_SELDRAG_COL      = 1,
	GX_SELDRAG_ROW      = 2
};

// GXScrollbarSettings is used in SetScrollBar to specify the scrollbar-behaviour
enum GXScrollbarSettings
{
	gxnDisabled  = 0,
	gxnEnabled   = 1,
	gxnAutomatic = 2,
	gxnShared    = 4,
	gxnEnhanced  = 8
};

// Drawing technique
enum GXDrawingTechnique
{
	gxDrawDirectToDC = 0,   // All output is directly drawn to dc
	gxDrawUsingMemDC = 1    // All output is drawn using a CMemDC (less flickering but slower)
};

// How to handle record count while printing (usefull for ODBC or DAO grids)
enum PrintHandleRecordCount
{
	gxCountNever = 0,	// Let record count grow while printing
	gxCountAlways = 1,	// Count records for both printing and print preview before printing
	gxCountPrint = 2	// Count records only for printing but not for print preview (default)
};


enum DirectionValue
{
	GX_HORZ             = 1,
	GX_VERT             = 2,
	GX_BOTH             = 3
};

// drawing (used in OnDrawTopLeftBottomRight)
const int gxnFlagSel = 0x10;
const int gxnFlagColor = 0x20;
const int gxnFlagSpanned = 0x40;
const int gxnFlagCovered = 0x80;
const int gxnFlagSpannedCont = 0x100;
const int gxnFlagHorzLine = 0x200;
const int gxnFlagVertLine = 0x400;
const int gxnFlagFixedVertLine = 0x800;
const int gxnFlagFixedHorzLine = 0x1000;

// floating cells
const WORD gxnFloatDisable       = 0x00;
const WORD gxnFloatDelayEval     = 0x01;
const WORD gxnFloatEvalOnDisplay = 0x02;

// merge cells
const WORD gxnMergeDisable       = 0x00;
const WORD gxnMergeDelayEval     = 0x01;
const WORD gxnMergeEvalOnDisplay = 0x02;
const WORD gxnMergeHorzOnly      = 0x04;
const WORD gxnMergeVertOnly      = 0x08;
const WORD gxnMergeOverHidden    = 0x10;

// CGXStyle - SetMergeCell attribute
const unsigned GX_MERGE_HORIZONTAL   = 0x01;
const unsigned GX_MERGE_VERTICAL     = 0x02;
const unsigned GX_MERGE_COMPVALUE    = 0x04;
const unsigned GX_MERGE_COMPSTYLE    = 0x00;
const unsigned GX_MERGE_DISABLED     = 0x00;

// Flags for allowing selection used by
// CGXGridParam::EnableSelection
// CGXGridParam::IsEnableSelection

const WORD GX_SELFULL        = 0xff;
const WORD GX_SELNONE        = 0x00;
const WORD GX_SELROW         = 0x01;
const WORD GX_SELCOL         = 0x02;
const WORD GX_SELTABLE       = 0x04;
const WORD GX_SELCELL        = 0x08;
const WORD GX_SELMULTIPLE    = 0x10;
const WORD GX_SELSHIFT       = 0x20;
const WORD GX_SELKEYBOARD    = 0x40;

// Flags for changig row and col width used by
// CGXGridParam::EnableTrackRowHeight
// CGXGridParam::EnableTrackColWidth
// CGXGridParam::IsEnableTrackRowHeight
// CGXGridParam::IsEnableTrackColWidth

const WORD GX_TRACK_DISABLE     = 0x00;
const WORD GX_TRACK_ALL         = 0x01;
const WORD GX_TRACK_INDIVIDUAL  = 0x02;
const WORD GX_TRACK_EXTHITTEST  = 0x04;
const WORD GX_TRACK_NOTHEADER   = 0x08;

const WORD GX_TRACK_NOPRESSEDHEADER   = 0x10;   // don't show headers pressed
const WORD GX_TRACK_NOMARKTRACKLINE   = 0x20;   // don't mark line of tracked row/column
const WORD GX_TRACK_NOINVERTLINE      = 0x40;   // don't invert line for new row/column size
const WORD GX_TRACK_SMOOTHHEADER      = 0x80;   // show header contents while dragging
const WORD GX_TRACK_SMOOTHCELLS       = 0x100;  // show all cell contents while dragging

const WORD GX_TRACK_DEFAULT     = GX_TRACK_INDIVIDUAL
		| GX_TRACK_SMOOTHHEADER | GX_TRACK_NOPRESSEDHEADER | GX_TRACK_NOMARKTRACKLINE;

// Flags for Special Modes, used by
// CGXGridParam::SetSpecialMode
// CGXGridParam::IsSpecialMode

const WORD GX_MODELISTBOX     = 0x03;   // both
const WORD GX_MODELBOX_SS     = 0x01;   // Singe selection listbox emulation
const WORD GX_MODELBOX_MS     = 0x02;   // Multi selection listbox emulation

// Undo information needed when removing rows/columns
const WORD GX_RMUNDO_BASESTYLES = 0x01; // row and column styles
const WORD GX_RMUNDO_CELLSTYLES = 0x02; // cell contents

// Cell activation (set focus to cell) see m_wActivateCell
const WORD GX_CAFOCUS_CLICKINTEXT   = 0x01;     // (default)
const WORD GX_CAFOCUS_CLICKONCELL   = 0x02;
const WORD GX_CAFOCUS_SETCURRENT    = 0x04;
const WORD GX_CAFOCUS_DBLCLICKONCELL = 0x08;

// for compatibility with 1.0 and 1.1
#define GX_HIDE_ALWAYS GX_HIDE_ALLWAYS

// Hide current cell
const WORD GX_HIDE_NEVER            = 0x00;
const WORD GX_HIDE_ALWAYS           = 0x01;
const WORD GX_HIDE_INACTIVEFRAME    = 0x02;

// Draw?g order
const WORD GX_DRAWORDER_ROWS = 0x00;        // (default)
const WORD GX_DRAWORDER_COLS = 0x01;

// Drag and Drop options
const DWORD GX_DNDDISABLED   = 0x00;        // disable drop target
const DWORD GX_DNDCOLHEADER  = 0x01;        // also copy/move column header cells
const DWORD GX_DNDROWHEADER  = 0x02;        // also copy/move row header cells
const DWORD GX_DNDMULTI      = 0x04;        // allow dragging multiple selections
const DWORD GX_DNDTEXT       = 0x08;        // force dragging of CF_TEXT clipboard format
const DWORD GX_DNDSTYLES     = 0x10;        // force dragging of internal styles format
const DWORD GX_DNDCOMPOSE    = 0x20;        // when copying internal styles, compose the full style of the cell
											// and do not copy only the cell specific attributes
const DWORD GX_DNDAUTOSCROLL = 0x40;        // enable autoscroll when user drags out of windows
const DWORD GX_DNDEGDESCROLL = 0x80;        // enable edgescroll when user drags to the corner of the window
const DWORD GX_DNDDIFFRANGEDLG = 0x100;     // Paste only: Display "Selected Range is Different"-Dialog
const DWORD GX_DNDNOAPPENDROWS = 0x200;     // If the user pastes (or drops) more rows than
											// currently available, don't append as many rows as needed
const DWORD GX_DNDNOAPPENDCOLS = 0x400;     // If the user pastes (or drops) more columns than
											// currently available, don't append as many columns as needed
const DWORD GX_DNDEXPRESSION = 0x800;       // Copy Expression instead of value	(when GX_DNDSTYLES is set)
											// this setting has no effect for direct copy/paste in sheet
											// and for CF_TEXT clipboard format
const DWORD GX_DNDMULTILINETEXT = 0x1000;	// preserves \t \r \n in the cell's value

// some nType values that can be passed to SetStyleRange, GetStyleRowCol etc.
const int GX_VALUE_BASESTYLE  = -1;		// used for row, column and table style
const int GX_VALUE_TEXT       = 0;		// used to store/retrieve plain style information in cell
const int GX_VALUE_EXPRESSION = 1;		// use this when calling SetValueRage, StoreStyleRowCol etc.
										// and the value should be parsed (date, time, number, formula etc.)

const WORD GX_EXPR_DISPLAYNEVER  = 0;	// never display formula expression in cell
const WORD GX_EXPR_DISPLAYACTIVE = 1;	// display formula expression in cell when cell is active
const WORD GX_EXPR_DISPLAYALWAYS = 2;	// always display formula expression 

// GX_NXYFACTOR specifies the granularity of logical values.
// It is used in Width_LPtoDP, Width_DPtoLP, Height_LPtoDP and Height_DPtoLP
// to convert between logical and vertical values.
const int   GX_NXYFACTOR = 1000;

const int   GX_NXAVGWIDTH = 1000;       // logical char width (average)
const int   GX_NYHEIGHT = 1000;         // logical char height

const ROWCOL GX_INVALID      = 0xFFFFFFFF;
const ROWCOL GX_MAXROWCOL    = 0xFFFFFFFE;


// Excel like auto fill flags
const DWORD GX_XLFILLDISABLED = 0x00;		// Disable excel like drag&fill...
const DWORD GX_XLFILLTEXT = 0x01;			// During excel fill only value is copied over...
const DWORD GX_XLFILLSTYLE = 0x02;			// During excel fill the whole style is copied over...


// for the cell tips
const DWORD GX_CELLTIP_ID_NOTDEFINED			=	LONG_MAX;
const DWORD GX_CELLTIP_ID_TEXT					=	0x00000001;
const DWORD GX_CELLTIP_ID_BITMAP				=	0x00000002;

const DWORD GX_CELLTIP_CLIPPING_BYCELL_HORZ		=	0x0001;
const DWORD GX_CELLTIP_CLIPPING_BYCELL_VERT		=	0x0002;
const DWORD GX_CELLTIP_CLIPPING_BYGRID_HORZ		=	0x0004;
const DWORD GX_CELLTIP_CLIPPING_BYGRID_VERT		=	0x0008;
const DWORD GX_CELLTIP_CLIPPING_BYSCREEN_HORZ	=	0x0010;
const DWORD GX_CELLTIP_CLIPPING_BYSCREEN_VERT	=	0x0020;


// Alignment conversion
UINT    AFXAPI AlignTAToDT(UINT ntAlign);
UINT    AFXAPI AlignDTToTA(UINT ntAlign);
LONG    AFXAPI AlignTAToES(UINT ntAlign);
UINT    AFXAPI AlignESToTA(LONG ltAlign);

// packing row and column in a DWORD

DWORD AFXAPI GXRowColToDWord(ROWCOL nRow, ROWCOL nCol);
WORD AFXAPI GXDWordToRow(DWORD dwValue);
WORD AFXAPI GXDWordToCol(DWORD dwValue);

// Performance testing

#ifdef TICKCOUNT
extern DWORD tickIndFont, tickStdFont, tickDrawItem, tickDraw, tickLookup;
extern DWORD tickLookupFont, tickLoadFont, tickCompStd, tickComposeStyle;
extern DWORD tick1, tick2, tick3, tick4, tick5, tick6, tick7, tick8, tick9, tick10;
#endif

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXRange

class CGXRange
{
public:
	// Type
	enum RangeType { rtCells = 0, rtRows = 1, rtCols = 2, rtTable = 3 };

public:
	// operations
	//@cmember
	// CGXRange constructor.
	GRID_API CGXRange();
	//@cmember
	// CGXRange constructor.
	GRID_API CGXRange(const CGXRange& r);
	//@cmember
	// CGXRange constructor.
	GRID_API CGXRange(const CGXRange* r);
	//@cmember
	// CGXRange constructor.
	GRID_API CGXRange(ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight);
	//@cmember
	// CGXRange constructor.
	GRID_API CGXRange(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// CGXRange copy constructor.
	GRID_API const CGXRange& operator=(const CGXRange& r);
	//@cmember
	// CGXRange equal operator.
	GRID_API int operator ==(const CGXRange &r) const;
	//@cmember
	// CGXRange not equal operator.
	GRID_API int operator !=(const CGXRange &r) const;
	//@cmember
	// Set cells.
	GRID_API CGXRange& SetCells(ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight);
	//@cmember
	// Set cells.
	GRID_API CGXRange& SetCells(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Set rows.
	GRID_API CGXRange& SetRows(ROWCOL nFrom, ROWCOL nTo);
	//@cmember
	// Set rows.
	GRID_API CGXRange& SetRows(ROWCOL nRow);
	//@cmember
	// Set columns.
	GRID_API CGXRange& SetCols(ROWCOL nFrom, ROWCOL nTo);
	//@cmember
	// Set columns.
	GRID_API CGXRange& SetCols(ROWCOL nCol);
	//@cmember
	// Set table.
	GRID_API CGXRange& SetTable();
	//@cmember
	// Expand range.
	GRID_API CGXRange& ExpandRange(ROWCOL nFirstRow, ROWCOL nFirstCol, ROWCOL nRowCount, ROWCOL nColCount);
	//@cmember
	// Intersect range.
	GRID_API BOOL IntersectRange(const CGXRange& r1, const CGXRange& r2);
	//@cmember
	// Union range.
	GRID_API BOOL UnionRange(const CGXRange& r1, const CGXRange& r2);
	//@cmember
	// Is cell in range?
	GRID_API BOOL IsCellInRange(ROWCOL nRow, ROWCOL nCol) const;
	//@cmember
	// Is rows?
	GRID_API BOOL IsRows() const;
	//@cmember
	// Is columns?
	GRID_API BOOL IsCols() const;
	//@cmember
	// Is cells?
	GRID_API BOOL IsCells() const;
	//@cmember
	// Is table?
	GRID_API BOOL IsTable() const;
	//@cmember
	// Is valid?
	GRID_API BOOL IsValid() const;
	//@cmember
	// Get ROWCOL width.
	GRID_API ROWCOL GetWidth() const;
	//@cmember
	// Get ROWCOL height.
	GRID_API ROWCOL GetHeight() const;

	// Iterate through range
	//@cmember
	// Get first cell row/col.
	GRID_API BOOL GetFirstCell(ROWCOL &nRow, ROWCOL &nCol) const;
	//@cmember
	// Get next cell row/col.
	GRID_API BOOL GetNextCell(ROWCOL &nRow, ROWCOL &nCol, BOOL bSortByRow = TRUE) const;

public:
	// data
	RangeType   rtType;

	ROWCOL      top,
				left,
				bottom,
				right;

	BOOL        m_bValid;
};

GRID_API CArchive& AFXAPI operator<<(CArchive& ar, const CGXRange& range);
GRID_API CArchive& AFXAPI operator>>(CArchive& ar, CGXRange& range);

typedef CGXRange* LPRANGE;

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXRangeList

class CGXRangeList: public CPtrList
{
	GRID_DECLARE_SERIAL(CGXRangeList)
public:
	//@cmember
	// Is cell in CGXRangeList?
	GRID_API BOOL        IsCellInList(ROWCOL nRow, ROWCOL nCol, POSITION posWithOut = NULL/*, BOOL bEdit = TRUE*/) const;
	//@cmember
	// Find range row/col.
	GRID_API POSITION    FindRange(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Is any cell from col?
	GRID_API BOOL        IsAnyCellFromCol(ROWCOL nCol);
	//@cmember
	// Is any cell from row?
	GRID_API BOOL        IsAnyCellFromRow(ROWCOL nRow);
	//@cmember
	// Get column array.
	GRID_API BOOL        GetColArray(ROWCOL nColCount, CRowColArray& awLeft, CRowColArray& awRight, BOOL bFixed = FALSE) const;
	//@cmember
	// Get row array.
	GRID_API BOOL        GetRowArray(ROWCOL nRowCount, CRowColArray& awTop, CRowColArray& awBottom, BOOL bFixed = FALSE) const;
	//@cmember
	// Delete garbage.
	GRID_API void        DeleteGarbage();
	//@cmember
	// Insert rows.
	GRID_API void        InsertRows(ROWCOL nRow, ROWCOL nCount);
	//@cmember
	// Insert columns.
	GRID_API void        InsertCols(ROWCOL nRow, ROWCOL nCount);
	//@cmember
	// Remove rows.
	GRID_API void        RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nRowCount = GX_MAXROWCOL);
	//@cmember
	// Remove columns.
	GRID_API void        RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nColCount = GX_MAXROWCOL);
	//@cmember
	// Move rows.
	GRID_API void        MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, ROWCOL nRowCount = GX_MAXROWCOL);
	//@cmember
	// Move columns.
	GRID_API void        MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, ROWCOL nColCount = GX_MAXROWCOL);

#ifdef _DEBUG
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

	// Implementation
public:
	//@cmember
	// Find fixed rows.
	GRID_API BOOL        FindFixedRows(POSITION& pos, ROWCOL nCount, ROWCOL& nStart, ROWCOL& nEnd);
	//@cmember
	// Find fixed columns.
	GRID_API BOOL        FindFixedCols(POSITION& pos, ROWCOL nCount, ROWCOL& nStart, ROWCOL& nEnd);
	//@cmember
	// CGXRangeList destructor.
	GRID_API virtual ~CGXRangeList();
	//@cmember
	// Serialize.
	GRID_API virtual void Serialize(CArchive& ar);   // overridden for document i/o
	//@cmember
	// CGXRangeList copy constructor.
	GRID_API virtual CGXRangeList& operator=(const CGXRangeList& l);

// type safe return values from CPtrList

// Attributes (head and tail)
	// peek at head or tail
	//@cmember
	// Get head.
	GRID_API CGXRange*& GetHead();
	//@cmember
	// Get head.
	GRID_API CGXRange* GetHead() const;
	//@cmember
	// Get tail.
	GRID_API CGXRange*& GetTail();
	//@cmember
	// Get tail.
	GRID_API CGXRange* GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	//@cmember
	// Remove head.
	GRID_API CGXRange* RemoveHead();
	//@cmember
	// Remove tail.
	GRID_API CGXRange* RemoveTail();

	// add before head or after tail
	//@cmember
	// Add head.
	GRID_API POSITION AddHead(CGXRange* newElement);
	//@cmember
	// Add tail.
	GRID_API POSITION AddTail(CGXRange* newElement);

	// add another list of elements before head or after tail
	//@cmember
	// Add head.
	GRID_API void AddHead(CGXRangeList* pNewList);
	//@cmember
	// Add tail.
	GRID_API void AddTail(CGXRangeList* pNewList);

	// iteration
	//@cmember
	// Get next position in range.
	GRID_API CGXRange*& GetNext(POSITION& rPosition); // return *Position++
	//@cmember
	// Get next position in range.
	GRID_API CGXRange* GetNext(POSITION& rPosition) const; // return *Position++
	//@cmember
	// Get previous position in range.
	GRID_API CGXRange*& GetPrev(POSITION& rPosition); // return *Position--
	//@cmember
	// Get previous position in range.
	GRID_API CGXRange* GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	//@cmember
	// Get at position.
	GRID_API CGXRange*& GetAt(POSITION position);
	//@cmember
	// Get at position.
	GRID_API CGXRange* GetAt(POSITION position) const;
	//@cmember
	// Set at position.
	GRID_API void SetAt(POSITION pos, CGXRange* newElement);

	// inserting before or after a given position
	//@cmember
	// Insert element before position.
	GRID_API POSITION InsertBefore(POSITION position, CGXRange* newElement);
	//@cmember
	// Insert element after position.
	GRID_API POSITION InsertAfter(POSITION position, CGXRange* newElement);
	//@cmember
	// helper functions (note: O(n) speed)
	// Find value.
	GRID_API POSITION Find(CGXRange* searchValue, POSITION startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found

	// Added members
	//@cmember
	// Delete all.
	GRID_API void        DeleteAll();
	//@cmember
	// Delete tail.
	GRID_API void        DeleteTail();
	//@cmember
	// Delete at position.
	GRID_API void        DeleteAt(POSITION position);
};

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXProperties

// colors
const int gxnPropGridLines        = 0;
const int gxnPropFixedLines       = 1;
const int gxnPropTrackingLines    = 2;
const int gxnPropDraggingLines    = 3;
const int gxnPropBackground       = 4;

// Defines

#define INCHtoDP(f) ((int) (f*((double) GXGetFontState()->m_nLogPixelsX)+0.51))
#define CMtoDP(f)   ((int) (f*((double) GXGetFontState()->m_nLogPixelsX)/2.54))
#define DPtoINCH(f) ((float) f/((double) GXGetFontState()->m_nLogPixelsX))
#define DPtoCM(f)   ((float) f*2.54/((double) GXGetFontState()->m_nLogPixelsX))

#define NROWS   10      // No of Rows for Footer/Header

// Predefined Tokens

const int GTK_DOCUMENT      = 0;
const int GTK_APP           = 1;
const int GTK_PAGE          = 2;
const int GTK_NOOFPAGE      = 3;
const int GTK_DATE          = 4;
const int GTK_REGISTER      = 5;


class CGXProperties: public CObject
{
	GRID_DECLARE_SERIAL(CGXProperties)

	// structures
	struct GRID_API UserPropertyInfo
	{
		UserPropertyInfo();
		UserPropertyInfo(const UserPropertyInfo& srcInfo);
		~UserPropertyInfo ();

		WORD    nID;
		CString sName;
		CGXStyle* pStyle;
	};

public:
	// constants
	CGXAppData* m_pAppData;

	// profile entries
	GRID_API static LPCTSTR szMarkRowHeader;
	GRID_API static LPCTSTR szMarkColHeader;
	GRID_API static LPCTSTR szDisplayRowHeader;
	GRID_API static LPCTSTR szDisplayColHeader;
	GRID_API static LPCTSTR szDisplay3DButtons;
	GRID_API static LPCTSTR szDisplayVertLines;
	GRID_API static LPCTSTR szDisplayHorzLines;

	GRID_API static LPCTSTR szDefaultSection;

	// printing
	GRID_API static LPCTSTR szPrintVertLines;
	GRID_API static LPCTSTR szPrintHorzLines;
	GRID_API static LPCTSTR szBlackWhite;
	GRID_API static LPCTSTR szRowHeaders;
	GRID_API static LPCTSTR szColHeaders;
	GRID_API static LPCTSTR szCenterVertical;
	GRID_API static LPCTSTR szCenterHorizontal;
	GRID_API static LPCTSTR szPageOrder;
	GRID_API static LPCTSTR szPrintFrame;
	GRID_API static LPCTSTR szMargins;
	GRID_API static LPCTSTR szFirstPage;
	GRID_API static LPCTSTR szDistances;

	// current cell
	CString sInvertNormal;
	CString sInvertThick;
	CString sInvertDrawBorder;
	CString sInvertThickBorder;
	CString sInvertNoBorder;

public:
	// operations
	//@cmember
	// CGXProperties constructor.
	GRID_API CGXProperties();
	//@cmember
	// CGXProperties constructor.
	GRID_API CGXProperties(const CGXProperties& p);
	//@cmember
	// CGXProperties destructor.
	GRID_API virtual ~CGXProperties();
	//@cmember
	// CGXProperties copy constructor.
	GRID_API const CGXProperties& operator=(const CGXProperties& p);
	//@cmember
	// Add default user properties.
	GRID_API virtual void AddDefaultUserProperties();
	CGXStyle m_styleEmpty;
	//@cmember
	// Serialize.
	GRID_API void Serialize(CArchive& ar);

#ifdef _DEBUG
	GRID_API void AssertValid() const;
	GRID_API void Dump(CDumpContext& dc) const;
#endif

	// Profile
	//@cmember
	// Write profile.
	GRID_API virtual void WriteProfile() const;
	//@cmember
	// Read profile.
	GRID_API virtual BOOL ReadProfile();
	//@cmember
	// Set section.
	GRID_API void SetSection(LPCTSTR pszSection);
	//@cmember
	// Get section.
	GRID_API const CString& GetSection() const;

	// Colors
	//@cmember
	// Add color property.
	GRID_API int AddColorProperty(LPCTSTR pszName, COLORREF color = RGB(192,192,192));
	//@cmember
	// Add color property.
	GRID_API int AddColorProperty(UINT nID, COLORREF color = RGB(192,192,192));
	//@cmember
	// Get color at index.
	GRID_API COLORREF GetColor(int nIndex) const;
	//@cmember
	// Set color at index.
	GRID_API void SetColor(int nIndex, COLORREF rgbColor);

	// Printing
	//@cmember
	// Enable printing.
	GRID_API void SetPrinting(BOOL b);
	//@cmember
	// Get printing.
	GRID_API BOOL GetPrinting() const;
	//@cmember
	// OnPrintHeaderAndFooter handler.
	GRID_API void                OnPrintHeaderAndFooter(CDC* pDC, CPrintInfo* pInfo, CDocument* pDoc = NULL, CGXGridParam* pParam = NULL);
	//@cmember
	// Calculate height for printing.
	GRID_API int                 CalculateHeight(CDC* pDC, CGXData &data, CGXStylesMap* pStylesMap);
	//@cmember
	// Print header and footer.
	GRID_API void                PrintHeaderFooter(CDC* pDC, CPrintInfo* pInfo, CRect& rect, CGXData& data, CGXStylesMap* pStylesMap);
	//@cmember
	// Parse text.
	GRID_API virtual CString     ParseText(LPCTSTR sz);
	
	//@cmember
	// Add token.
	GRID_API int                 AddToken(LPCTSTR sz);
	//@cmember
	// Token in substring.
	GRID_API virtual CString     SubstTokenText(int nToken, CString& sRest);
	//@cmember
	// Get token arguments.
	GRID_API CString             GetTokenArgs(CString& sRest);

	// Header&Footer
	//@cmember
	// Get distances top and bottom.
	GRID_API void GetDistances(int& top, int& bottom);
	//@cmember
	// Set distances top and bottom.
	GRID_API void SetDistances(int top, int bottom);
	//@cmember
	// Set first starting page.
	GRID_API void SetFirstPage(int nStart);
	//@cmember
	// Get first starting page.
	GRID_API int GetFirstPage();

	CStringArray        m_sTokenArray;
	CStringArray        m_sSubstTokenArray;

	// User attributes
	//@cmember
	// Add user property.
	GRID_API void AddUserProperty(WORD nID, const CGXStyle& style);
	//@cmember
	// Set user property.
	GRID_API void SetUserProperty(WORD nID, const CGXStyle& style);
	//@cmember
	// Get user property.
	GRID_API const CGXStyle& GetUserProperty(WORD nID);
	//@cmember
	// Get user property info map.
	GRID_API const CMapWordToPtr& GetUserPropertyInfoMap() const;

	//@cmember
	// Get parent grid.
	GRID_API CGXGridCore* Grid() const;

protected:
	//@cmember
	// Free.
	GRID_API void Free();

public:
	// user attributes
	CMapWordToPtr      m_UserPropertyInfoMap;

	// attributes
	BOOL
			m_b3dButtons,           // 3d look alike Headers
			m_bDisplayVertLines,    // vertical gridlines
			m_bDisplayHorzLines,    // horinzontal gridlines
			m_bMarkRowHeader,       // mark row headers
			m_bMarkColHeader;       // mark column headers

	BOOL    m_bPrinting;

	CString m_sSection;

	// colors
	CStringArray        m_ColorNameArray;
	CDWordArray         m_ColorArray;
	// zoom
	int                 m_nZoom;
	// print settings
	LONG    m_nBottomMargin;
	LONG    m_nLeftMargin;
	LONG    m_nTopMargin;
	LONG    m_nRightMargin;
	GBOOL   m_bCenterHorizontal;
	GBOOL   m_bCenterVertical;
	GBOOL   m_bColHeaders;
	GBOOL   m_bPrintHorzLines;
	GBOOL   m_bRowHeaders;
	GBOOL   m_bPrintVertLines;
	LONG    m_nPageOrder;
	GBOOL   m_bBlackWhite;
	GBOOL   m_bPrintFrame;

	// Header&Footer
	LONG    m_nDistTop;
	LONG    m_nDistBottom;
	LONG    m_nFirstPage;
	CGXData    m_mapDataFooter;
	CGXData    m_mapDataHeader;
	WORD m_gxnPropTextHeadline;
	WORD m_gxnPropTextFootnote;

	// custom page breaks
	CDWordArray m_awColBreaks;
	CDWordArray m_awRowBreaks;

public:
	// access member functions
	//@cmember
	// Set mark row header.
	GRID_API void SetMarkRowHeader(BOOL b);
	//@cmember
	// Get mark row header.
	GRID_API BOOL GetMarkRowHeader() const;
	//@cmember
	// Set mark column header.
	GRID_API void SetMarkColHeader(BOOL b);
	//@cmember
	// Get mark column header.
	GRID_API BOOL GetMarkColHeader() const;
	//@cmember
	// Set display horizontal lines.
	GRID_API void SetDisplayHorzLines(BOOL b);
	//@cmember
	// Is display horizontal lines?
	GRID_API BOOL GetDisplayHorzLines() const;
	//@cmember
	// Set display vertical lines.
	GRID_API void SetDisplayVertLines(BOOL b);
	//@cmember
	// Is display vertical lines?
	GRID_API BOOL GetDisplayVertLines() const;
	//@cmember
	// Set display 3D buttons.
	GRID_API void SetDisplay3dButtons(BOOL b);
	//@cmember
	// Is display 3D buttons?
	GRID_API BOOL GetDisplay3dButtons() const;
	//@cmember
	// Set last zoom.
	GRID_API void SetLastZoom(int nZoom);
	//@cmember
	// Get last zoom.
	GRID_API int GetLastZoom() const;

	// Printing support
	//@cmember
	// Is black/wite printing?
	GRID_API BOOL GetBlackWhite() const;
	//@cmember
	// Is display column headers?
	GRID_API BOOL GetDisplayColHeaders() const;
	//@cmember
	// Is display row headers?
	GRID_API BOOL GetDisplayRowHeaders() const;
	//@cmember
	// Is center horizontal?
	GRID_API BOOL    GetCenterHorizontal();
	//@cmember
	// Is center vertical?
	GRID_API BOOL    GetCenterVertical();
	//@cmember
	// Is print row headers?
	GRID_API BOOL    GetPrintRowHeaders();
	//@cmember
	// Is print column headers?
	GRID_API BOOL    GetPrintColHeaders();
	//@cmember
	// Is print frame?
	GRID_API BOOL    GetPrintFrame();
	//@cmember
	// Is print horizontal lines?
	GRID_API BOOL    GetPrintHorzLines();
	//@cmember
	// Is print vertical lines?
	GRID_API BOOL    GetPrintVertLines();
	//@cmember
	// Is print black/white?
	GRID_API BOOL    GetPrintBlackWhite();
	//@cmember
	// Get page order.
	GRID_API int     GetPageOrder();
	//@cmember
	// Set print horizontal lines.
	GRID_API void    SetPrintHorzLines(BOOL b);
	//@cmember
	// Set print vertical lines.
	GRID_API void    SetPrintVertLines(BOOL b);
	//@cmember
	// Set center horizontal.
	GRID_API void    SetCenterHorizontal(BOOL b);
	//@cmember
	// Set center vertical.
	GRID_API void    SetCenterVertical(BOOL b);
	//@cmember
	// Set black/white printing.
	GRID_API void    SetBlackWhite(BOOL b);
	//@cmember
	// Set print row headers.
	GRID_API void    SetPrintRowHeaders(BOOL b);
	//@cmember
	// Set print column headers.
	GRID_API void    SetPrintColHeaders(BOOL b);
	//@cmember
	// Set page order.
	GRID_API void    SetPageOrder(int n);
	//@cmember
	// Set print frame.
	GRID_API void    SetPrintFrame(BOOL b);

	//@cmember
	// Get margins.
	GRID_API void    GetMargins(int& top, int& left, int& bottom, int& right);
	//@cmember
	// Set margins.
	GRID_API void    SetMargins(int top, int left, int bottom, int right);

	//@cmember
	// Get data header.
	GRID_API CGXData& GetDataHeader();
	//@cmember
	// Get data footer.
	GRID_API CGXData& GetDataFooter();

	//@cmember
	// Get column break array.
	GRID_API CDWordArray& GetColBreakArray();
	//@cmember
	// Get row break array.
	GRID_API CDWordArray& GetRowBreakArray();

	friend class CGXGridParamCopyOperatorImp;
};

/////////////////////////////////////////////////////////////////////////////
// class CGXGridParam

CObject* AFXAPI GXCreateObjectFromFile(CFile& file, CRuntimeClass* pRuntimeClass);
CObject* AFXAPI GXCreateObjectFromFile(LPCTSTR lpszFileName, CRuntimeClass* pRuntimeClass);
CObject* AFXAPI GXCreateObjectFromResource(LPCTSTR lpszResourceName, LPCTSTR lpszType, CRuntimeClass* pRuntimeClass);

class CGXCoveredCellPool;
class CGXGridDropTarget;

// This local version of CByteArray is required to workaround a bug in 
// the CByteArray::Serialize() implementation found in the IA64 SDK
// and MFC 7.0
#if defined(_WIN64) || _MFC_VER >= 0x0700

class CByteArray64 :  public CByteArray
{
public:
	//@cmember
	// CByteArray64 constructor.
	GRID_API CByteArray64();
	//@cmember
	// CByteArray64 destructor.
	GRID_API virtual ~CByteArray64();

	//@cmember
	// This will hide the base class Serialize() function
	GRID_API void Serialize(CArchive &ar);
};
#else //defined(_WIN64) || _MFC_VER >= 0x0700
#define CByteArray64 CByteArray
#endif	

class CGXGridParam : public CObject
{
	GRID_DECLARE_SERIAL(CGXGridParam)

// Constructor
public:
	//@cmember
	// CGXGridParam constructor.
	GRID_API CGXGridParam();

	// Support for loading/storing layout
	//@cmember
	// Create from file.
	GRID_API static CGXGridParam* AFXAPI CreateFromFile(LPCTSTR lpszFileName);
	//@cmember
	// Create from resource name.
	GRID_API static CGXGridParam* AFXAPI CreateFromResource(LPCTSTR lpszResourceName);
	//@cmember
	// Create from resource id.
	GRID_API static CGXGridParam* AFXAPI CreateFromResource(UINT nId);
	//@cmember
	// Write to file.
	GRID_API void WriteToFile(LPCTSTR lpszFileName) const;

	//@cmember
	// Implement serialize.
	GRID_API static void AFXAPI ImplementSerialize();
	//@cmember
	// Implement copy operator.
	GRID_API static void AFXAPI ImplementCopyOperator();

	CGXAppData* m_pAppData;

// Objects
public:
	//@cmember
	// Get properties.
	GRID_API CGXProperties* GetProperties();
	//@cmember
	// Set properties.
	GRID_API void    SetProperties(CGXProperties* pProperties, BOOL bMustDelete = TRUE);

	//@cmember
	// Get CGXData.
	GRID_API CGXData* GetData();
	//@cmember
	// Set CGXData.
	GRID_API void    SetData(CGXData* p, BOOL bMustDelete = TRUE);

	//@cmember
	// Get styles map.
	GRID_API CGXStylesMap* GetStylesMap();
	//@cmember
	// Set styles map.
	GRID_API void    SetStylesMap(CGXStylesMap* p, BOOL bMustDelete = TRUE);

	//@cmember
	// Get print device.
	GRID_API CGXPrintDevice* GetPrintDevice();
	//@cmember
	// Set print device.
	GRID_API void    SetPrintDevice(CGXPrintDevice* pPD, BOOL bMustDelete = TRUE);

	//@cmember
	// Get range list.
	GRID_API CGXRangeList* GetRangeList();
	//@cmember
	// Get covered cells list.
	GRID_API CGXRangeList* GetCoveredCellsList();
	//@cmember
	// Update covered cells list.
	GRID_API void UpdateCoveredCellsList();

	//@cmember
	// Get undo list.
	GRID_API CObList& GetUndoList();
	//@cmember
	// Get redo list.
	GRID_API CObList& GetRedoList();
	//@cmember
	// Empty undo list.
	GRID_API void     EmptyUndoList();
	//@cmember
	// Empty redo list.
	GRID_API void     EmptyRedoList();

	//@cmember
	// Init covered cells.
	GRID_API void     InitCoveredCells();

// Attributes
public:
// Enable/Disable specific features
	//@cmember
	// Enable thumb track.
	GRID_API void EnableThumbTrack(BOOL b);
	//@cmember
	// Enable selection.
	GRID_API void EnableSelection(UINT wFlags = GX_SELFULL);
	//@cmember
	// Enable move columns.
	GRID_API void EnableMoveCols(BOOL b = TRUE);
	//@cmember
	// Enable move rows.
	GRID_API void EnableMoveRows(BOOL b = TRUE);
	//@cmember
	// Enable track row height.
	GRID_API void EnableTrackRowHeight(UINT wFlags = GX_TRACK_DEFAULT);
	//@cmember
	// Enable track column width.
	GRID_API void EnableTrackColWidth(UINT wFlags = GX_TRACK_DEFAULT);
	//@cmember
	// Enable all features.
	GRID_API void EnableAllFeatures(BOOL b = TRUE);
	//@cmember
	// Set special mode.
	GRID_API void SetSpecialMode(WORD wFlags);

	//@cmember
	// Is enable thumb track?
	GRID_API BOOL IsEnableThumbTrack();
	//@cmember
	// Is enabled selection?
	GRID_API BOOL IsEnableSelection(WORD wFlags);
	//@cmember
	// Is enable move columns?
	GRID_API BOOL IsEnableMoveCols();
	//@cmember
	// Is enable move rows?
	GRID_API BOOL IsEnableMoveRows();
	//@cmember
	// Is enable track row height?
	GRID_API BOOL IsEnableTrackRowHeight(WORD wFlags = GX_TRACK_INDIVIDUAL | GX_TRACK_ALL);
	//@cmember
	// Is enable track column width?
	GRID_API BOOL IsEnableTrackColWidth(WORD wFlags = GX_TRACK_INDIVIDUAL | GX_TRACK_ALL);
	//@cmember
	// Is special mode?
	GRID_API BOOL IsSpecialMode(WORD wFlags);

	//@cmember
	// Enable undo.
	GRID_API void EnableUndo(BOOL bEnable = TRUE);
	//@cmember
	// Is enabled undo?
	GRID_API BOOL IsEnableUndo();

	//@cmember
	// Enable change tab.
	GRID_API void EnableChangeTab(BOOL b);
	//@cmember
	// Is enable change tab.
	GRID_API BOOL IsEnableChangeTab();

	//@cmember
	// Set numbered row headers.
	GRID_API void SetNumberedRowHeaders(BOOL b);
	//@cmember
	// Set numbered column headers.
	GRID_API void SetNumberedColHeaders(BOOL b);
	//@cmember
	// Is numbered row headers?
	GRID_API BOOL IsNumberedRowHeaders();
	//@cmember
	// Is numbered column headers?
	GRID_API BOOL IsNumberedColHeaders();

	//@cmember
	// Set default combobox height.
	GRID_API void SetDefaultComboBoxHeight(int nHeight);
	//@cmember
	// Get default combobox height.
	GRID_API int GetDefaultComboBoxHeight();

	//@cmember
	// Set eat first mouse click.
	GRID_API void SetEatFirstMouseClick(BOOL b);
	//@cmember
	// Is eat first mouse click?
	GRID_API BOOL IsEatFirstMouseClick();

	//@cmember
	// Set transparent background.
	GRID_API void SetTransparentBackground(BOOL b);
	//@cmember
	// Is transparent background?
	GRID_API BOOL IsTransparentBackground();

	//@cmember
	// Set remove row flags.
	GRID_API void SetRemoveRowsFlags(WORD wFlags);
	//@cmember
	// Set remove column flags.
	GRID_API void SetRemoveColsFlags(WORD wFlags);
	//@cmember
	// Get remove row flags.
	GRID_API WORD GetRemoveRowsFlags();
	//@cmember
	// Get remove column flags.
	GRID_API WORD GetRemoveColsFlags();

	//@cmember
	// Set min track row height.
	GRID_API void SetMinTrackRowHeight(int nHeight);
	//@cmember
	// Set min track column width.
	GRID_API void SetMinTrackColWidth(int nWidth);
	//@cmember
	// Get min track row height.
	GRID_API int GetMinTrackRowHeight();
	//@cmember
	// Get min track column width.
	GRID_API int GetMinTrackColWidth();

	//@cmember
	// Set active cell flags.
	GRID_API void SetActivateCellFlags(WORD wFlags);
	//@cmember
	// Get active cell flags.
	GRID_API WORD GetActivateCellFlags();

	//@cmember
	// Set smart resize.
	GRID_API void SetSmartResize(BOOL b);
	//@cmember
	// Is smart resize?
	GRID_API BOOL IsSmartResize();

	//@cmember
	// Set lock read only.
	GRID_API void SetLockReadOnly(BOOL b);
	//@cmember
	// Is lock read only?
	GRID_API BOOL IsLockReadOnly();

	//@cmember
	// Set draw order.
	GRID_API void SetDrawOrder(WORD w);
	//@cmember
	// Get draw order.
	GRID_API WORD GetDrawOrder();

	//@cmember
	// Set hide current cell.
	GRID_API void SetHideCurrentCell(WORD nSetting);
	//@cmember
	// Get hide current cell.
	GRID_API WORD GetHideCurrentCell();

	//@cmember
	// Get sheet name.
	GRID_API const CString& GetSheetName();
	//@cmember
	// Set sheet name.
	GRID_API void SetSheetName(LPCTSTR szName);

	//@cmember
	// Set scroll like excel.
	GRID_API void SetScrollLikeExcel(BOOL b);
	//@cmember
	// Is scroll like excel.
	GRID_API BOOL IsScrollLikeExcel();

	//@cmember
	// Set sync current cell.
	GRID_API void SetSyncCurrentCell(BOOL b);
	//@cmember
	// Is sync current cell.
	GRID_API BOOL IsSyncCurrentCell();

	//@cmember
	// Set draw WYSIWYG.
	GRID_API void SetDrawWYSIWYG(BOOL b);
	//@cmember
	// Is draw WYSIWYG?
	GRID_API BOOL IsDrawWYSIWYG();

	//@cmember
	// Set enter key action.
	GRID_API void SetEnterKeyAction(WORD nAction); // 0 for simply storing current cells value
	//@cmember
	// Get enter key action.
	GRID_API WORD GetEnterKeyAction();

	//@cmember
	// Set undo limit.
	GRID_API void SetUndoLimit(DWORD nMaxUndoOp);
	//@cmember
	// Get undo limit.
	GRID_API DWORD GetUndoLimit();

	//@cmember
	// Set grid line style.
	GRID_API void SetGridLineStyle(UINT nStyle);
	//@cmember
	// Get grid line style.
	GRID_API UINT GetGridLineStyle() const;

	//@cmember
	// Set new grid line mode.
	GRID_API void SetNewGridLineMode(BOOL b);
	//@cmember
	// Get new grid line mode.
	GRID_API BOOL GetNewGridLineMode();

	//@cmember
	// Set excel like current cell.
	GRID_API void SetExcelLikeCurrentCell(BOOL b);
	//@cmember
	// Is excel like current cell?
	GRID_API BOOL GetExcelLikeCurrentCell();

	//@cmember
	// Set excel like headers.
	GRID_API void SetExcelLikeHeaders(BOOL b);
	//@cmember
	// Is excel like headers?
	GRID_API BOOL GetExcelLikeHeaders();

	//@cmember
	// Set excel like selection frame.
	GRID_API void SetExcelLikeSelectionFrame(BOOL b);
	//@cmember
	// Is excel like selection frame?
	GRID_API BOOL GetExcelLikeSelectionFrame();

	//@cmember
	// Set excel like fill flags.
	GRID_API void SetExcelLikeFillFlags(DWORD dw);
	//@cmember
	// Get excel like fill flags.
	GRID_API DWORD GetExcelLikeFillFlags() const;

	//@cmember
	// Set sort columns on double click.
	GRID_API void SetSortColsOnDblClk(BOOL b);
	//@cmember
	// Is sort columns on double click?
	GRID_API BOOL GetSortColsOnDblClk();

	//@cmember
	// Set sort rows on double click.
	GRID_API void SetSortRowsOnDblClk(BOOL b);
	//@cmember
	// Is sort rows on double click?
	GRID_API BOOL GetSortRowsOnDblClk();

	//@cmember
	// Is init?
	GRID_API BOOL IsInit() const;

	//@cmember
	// Get parent grid.
	GRID_API CGXGridCore* Grid() const;

// Attributes
public:
	// If you do not have row or column headers in the form 1, 2, 3, ... or A, B, C, ...
	// set the following parameters FALSE. This avoids refreshing all headers when
	// you do insert, move or remove rows or columns.
	BOOL                m_bNumberedRowHeaders;
	BOOL                m_bNumberedColHeaders;
	int                 m_nDefaultComboBoxHeight;
	BOOL                m_bEatFirstMouseClick;
	BOOL                m_bTransparentBackground;
	WORD                m_nRemoveRowsFlags,
						m_nRemoveColsFlags;
	int                 m_nMinTrackRowHeight,
						m_nMinTrackColWidth;
	WORD                m_wActivateCell;
	WORD                m_wAllowSelection;           // Selection of cells
	BOOL                m_bAllowSelDragCols,         // dragging columns
						m_bAllowSelDragRows;         // dragging rows
	WORD                m_wAllowTrackRowHeight,      // tracking row heights
						m_wAllowTrackColWidth;       // tracking column withs
	WORD                m_nSpecialMode;              // use as listbox
	BOOL                m_bThumbTrack;
	BOOL                m_bLockReadOnly;
			// if FALSE, the grid will not take care on read-only state
			// if TRUE, read-only cells are protected.
	BOOL                m_bSmartResize;
	WORD                m_wFloatCellsMode;
	WORD                m_wMergeCellsMode;
	BOOL                m_bDrawWYSIWYG;             // draw WYSIWIG
	WORD                m_nHideCurrentCell;
	WORD                m_nDrawRowOrder;
	ROWCOL              m_nHeaderRows,
						m_nHeaderCols;
	BOOL                m_bScrollLikeExcel;
	CString             m_sSheetName;           // Sheet name (when used in CGXTabWnd)
	ROWCOL              m_nFrozenRows,          // Frozen Rows
						m_nFrozenCols;          // Frozen Cols
	ROWCOL              m_nUndoFreezeFromCol,   // additional information
						m_nUndoFreezeToCol,     // for "Unfreeze" columns
						m_nUndoFreezeDestCol;
	ROWCOL              m_nUndoFreezeFromRow,   // additional information
						m_nUndoFreezeToRow,     // for "Unfreeze" rows
						m_nUndoFreezeDestRow;
	BOOL                m_bSyncCurrentCell;     // Synchronize current cell
	ROWCOL              m_nLastSyncEditRow,     // among several views
						m_nLastSyncEditCol;
	DWORD               m_dwUndoLimit;
	WORD                m_nEnterKeyAction;
	// Marked Cells
	CGXRangeList        m_SelRects;
	// Covered Cells
	CGXRangeList        m_CoveredCellsList;
	CGXCoveredCellPool*	m_pCoveredCells;
	// Floated Cells
	CGXSpanCellPool*    m_pDispFloatCells;
	CGXDelayedRangePool* m_pDelayedDispFloatCells;
	CGXSpanCellPool*    m_pPrintFloatCells;       // backup state while printing
	CGXDelayedRangePool* m_pDelayedPrintFloatCells;   // backup state while printing
	// Merged Cells
	CGXSpanCellPool*    m_pHorzMergeCells;
	CGXSpanCellPool*    m_pVertMergeCells;
	CGXDelayedRangePool* m_pDelayedMergeCells;
	// Property-Object
	BOOL                m_bOwnProperties;
	CGXProperties*      m_pProperties;
	// Styles Map
	BOOL                m_bOwnStylesMap;
	CGXStylesMap*       m_pStylesMap;
	// pointer to an optional Data-Object
	BOOL                m_bOwnData;
	CGXData*            m_pData;
	// Pointer to an optional PrintDevice-Object
	BOOL                m_bOwnPD;
	CGXPrintDevice*     m_pPD;
	BOOL                m_bReadOnly;
	BOOL                m_bNeedChangeTab;            // Enable or disable changing the worksheet-name
	// Undo, Redo, Transactions
	CObList             m_UndoList;
	CObList             m_RedoList;
	int                 m_nTrans;
	BOOL                m_bUndoEnabled;
	// Row Heights, Column Widths
	CByteArray64        m_abRowHidden,
						m_abColHidden;
	CGXMapDWordToLong   m_RowHeights,
						m_ColWidths;
	LONG                m_nDefaultHeight,
						m_nDefaultWidth;
	BOOL                m_bUpdateLocked; // see CGXGridCore::LockUpdate
	BOOL                m_bNewGridLineMode;
	WORD                m_nGridLineStyle; // dotted or regular grid lines
	BOOL                m_bExcelLikeCurrentCell,
						m_bExcelLikeSelectionFrame;
	BOOL                m_bExcelLikeHeaders;
	DWORD				m_nExcelLikeFillFlags;	// Excel like fill flags...
	BOOL                m_bSortColsOnDblClk,
						m_bSortRowsOnDblClk;
	ROWCOL				m_nLastSortedRow,	// remember last sorted row
						m_nLastSortedCol;
	BOOL				m_bSortAscending;	// remember if last sort was ascending or descending
	BOOL                m_bIsInit;      // TRUE when one-time initialization is done

public:
	// Temporary attributes for drag&drop
	BOOL    m_bDndSource;
	ROWCOL  m_nDndStartRow,
			m_nDndStartCol;
	CGXRangeList* m_pDndSelList;
	ROWCOL  m_nDndForceDropCol,
			m_nDndForceDropRow;
	ROWCOL  m_nDndRowOffset,
			m_nDndColOffset;
	BOOL   m_bDndCurrentCellText;       // TRUE if selected text from current cell is dragged
	CGXControl* m_pDndCurrentCellControl;
	// Copy,Cut/Paste
	BOOL	m_bDirectCopyPaste;
	BOOL	m_bDirectCutPaste;
	BOOL	m_bDirectDragDrop;
	BOOL	m_bCut;
	CGXRangeList m_CopyRangeList;
	// Display expressions in active/inactive cells
	WORD	m_nDisplayExpression;	// GX_EXPR_DISPLAYACTIVE, GX_EXPR_DISPLAYALWAYS
	// Cell depencies - updated cells:
	CGXRangeList m_UpdatedRangeList;
	// Tabbed comboboxes (old-fashioned way)
	CPtrArray m_ArrayOfMapValueToChoice;
	CPtrArray m_ArrayOfMapTextToChoice;
	LONG m_nSerial;
	// map with more objects that can be linked into parameter object
	CMapPtrToPtr m_mapParamLocalData;

// Implementation
public:
	//@cmember
	// CGXGridParam destructor.
	GRID_API virtual ~CGXGridParam();
	//@cmember
	// Serialize.
	GRID_API virtual void Serialize(CArchive& ar);
	//@cmember
	// CGXGridParam copy constructor.
	GRID_API virtual CGXGridParam& operator=(const CGXGridParam& p);

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif
};

// Parameter object local data

#define GX_PARAM_LOCAL(class_name, ident_name) \
	class_name* ident_name(CGXGridParam* pParam) { \
			void* voidptr; \
			class_name* pData; \
			if (!pParam->m_mapParamLocalData.Lookup(this, pData)) \
				pParam->m_mapParamLocalData.SetAt(this, pData = new class_name); \
			return pData; \
		} \

#define GX_EXTERN_PARAM_LOCAL(class_name, ident_name) \
	extern class_name* ident_name;

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXGridCore

class CGXTabWnd;
class CGXRecordInfoWnd;
class CGXDragLineWnd;
class CGXFormulaSheet;
class CGXLongOperation;
class CGXPlugInComponent;

class CGXGridCore
{
public:
	//@cmember
	// Construction, Destruction
	GRID_API CGXGridCore(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);
	GRID_API virtual ~CGXGridCore();

public:
	// Components that are implemented in concrete classes 
	// derived from abstract base classes. The concrete implementation
	// is only necessary to be linked into an .exe if its functionality
	// is needed.

	void* begin_component_ptr;

	//@cmember
	// Implement printing.
	GRID_API void ImplementPrinting();
	CGXAbstractGridPrintImp* m_pPrintImp;
	friend class CGXGridPrintImp;
	
	//@cmember
	// Implement grid sort.
	GRID_API void ImplementGridSort();
	CGXAbstractGridSortImp* m_pSortImp;
	friend class CGXGridSortImp;
	
	//@cmember
	// Implement old drawing.
	GRID_API void ImplementOldDrawing();
	CGXAbstractGridOldDrawingImp* m_pOldDrawingImp;
	friend class CGXGridOldDrawingImp;
	
	//@cmember
	// Implement covered cells.
	GRID_API void ImplementCoveredCells();
	CGXAbstractGridCoveredCellsImp* m_pCoveredCellsImp;
	friend class CGXGridCoveredCellsImp;
	
	//@cmember
	// Implement draw spanned cells.
	GRID_API void ImplementDrawSpannedCells();
	CGXAbstractDrawSpannedCellsImp* m_pDrawSpannedCellsImp;
	friend class CGXDrawSpannedCellsImp;
	
	//@cmember
	// Implement float cells.
	GRID_API void ImplementFloatCells();
	CGXAbstractGridFloatCellsImp* m_pFloatCellsImp;
	friend class CGXGridFloatCellsImp;
	
	//@cmember
	// Imeplement merge cells.
	GRID_API void ImplementMergeCells();
	CGXAbstractGridMergeCellsImp* m_pMergeCellsImp;
	friend class CGXGridMergeCellsImp;
	
	//@cmember
	// Implement undo/redo.
	GRID_API void ImplementUndoRedo();
	CGXAbstractCommandFactory* m_pUndoImp;
	friend class CGXCommandFactory;
	
	//@cmember
	// Implement calc size.
	GRID_API void ImplementCalcSize();
	CGXAbstractCalcSizeImp* m_pAbstractCalcSizeImp;
	friend class CGXCalcSizeImp;

	//@cmember
	// Implement update hint.
	GRID_API void ImplementUpdateHint();
	CGXAbstractGridUpdateHintImp* m_pUpdateHintImp;
	friend class CGXGridUpdateHintImp;

	//@cmember
	// Implement resize to fit.
	GRID_API void ImplementResizeToFit();
	CGXAbstractGridResizeToFitImp* m_pResizeToFitImp;
	friend class CGXGridResizeToFitImp;
	
	//@cmember
	// Implement hide cells.
	GRID_API void ImplementHideCells();
	CGXAbstractGridHideCellsImp* m_pHideCellsImp;
	friend class CGXGridHideCellsImp;
	
	//@cmember
	// Implement find/replace.
	GRID_API void ImplementFindReplace();
	CGXAbstractGridFindReplaceImp* m_pFindReplaceImp;
	friend class CGXGridFindReplaceImp;
	
	//@cmember
	// Implement user select range.
	GRID_API void ImplementUserSelectRange();
	CGXAbstractGridUserSelectRangeImp* m_pUserSelectRangeImp;
	friend class CGXGridUserSelectRangeImp;
	
	//@cmember
	// Implement excel like frame.
	GRID_API void ImplementExcelLikeFrame();
	CGXAbstractGridExcelLikeFrameImp* m_pExcelLikeFrameImp;
	friend class CGXGridExcelLikeFrameImp;
	
	//@cmember
	// Implement excel like fill.
	GRID_API void ImplementExcelLikeFill();
	GRID_API void SetExcelLikeFillImp(CGXAbstractGridExcelLikeFillImp* pGridExcelLikeFillImp, BOOL bDelete = TRUE);
	CGXAbstractGridExcelLikeFillImp* m_pExcelLikeFillImp;
	friend class CGXGridExcelLikeFillImp;
	
	//@cmember
	// Implement user drag select range.
	GRID_API void ImplementUserDragSelectRange();
	CGXAbstractGridUserDragSelectRangeImp* m_pUserDragSelectRangeImp;
	friend class CGXGridUserDragSelectRangeImp;
	
	//@cmember
	// Implement move rows/columns.
	GRID_API void ImplementMoveRowsCols();
	friend class CGXGridMoveRowsColsImp;
	CGXAbstractGridMoveRowsColsImp* m_pMoveRowsColsImp;
	
	//@cmember
	// Implement user resize cells.
	GRID_API void ImplementUserResizeCells();
	friend class CGXGridUserResizeCellsImp;
	CGXAbstractGridUserResizeCellsImp* m_pUserResizeCellsImp;
	
	//@cmember
	// Implement optimize update.
	GRID_API void ImplementOptimizedUpdate();
	CGXAbstractGridOptimizedUpdateImp* m_pOptimizedUpdateImp;
	friend class CGXGridOptimizedUpdateImp;
	
	//@cmember
	// Implement mark edit header.
	GRID_API void ImplementMarkEditHeader();
	CGXAbstractGridMarkEditHeaderImp* m_pMarkEditHeaderImp;
	friend class CGXGridMarkEditHeaderImp;
	
	//@cmember
	// Implement freez menu helper.
	GRID_API void ImplementFreezeMenuHelper();
	CGXAbstractGridFreezeMenuHelperImp* m_pFreezeMenuImp;
	friend class CGXGridFreezeMenuHelperImp;
	
	//@cmember
	// Implement direct copy move cells.
	GRID_API void ImplementDirectCopyMoveCells();
	CGXAbstractGridDirectCopyMoveCellsImp* m_pDirectCopyMoveCellsImp;
	friend class CGXGridDirectCopyMoveCellsImp;
	
	//@cmember
	// Implement text data exchange.
	GRID_API void ImplementTextDataExchange();
	CGXAbstractGridTextDataExchangeImp* m_pTextDataExchangeImp;
	friend class CGXGridTextDataExchangeImp;
	
	//@cmember
	// Implement style data exchange.
	GRID_API void ImplementStyleDataExchange();
	CGXAbstractGridStyleDataExchangeImp* m_pStyleDataExchangeImp;
	friend class CGXGridStyleDataExchangeImp;
	
	//@cmember
	// Implement cut/paste.
	GRID_API void ImplementCutPaste();
	CGXAbstractGridCutPasteImp* m_pCutPasteImp;
	friend class CGXGridCutPasteImp;
	
	//@cmember
	// Implement clear cells.
	GRID_API void ImplementClearCells();
	CGXAbstractGridClearCellsImp* m_pClearCellsImp;
	friend class CGXGridClearCellsImp;
	
	//@cmember
	// Implement range name.
	GRID_API void ImplementRangeName();
	CGXAbstractGridRangeNameImp* m_pRangeNameImp;
	friend class CGXGridRangeNameImp;
	
	CGXAbstractGridDropTargetImp* m_pOleDropTargetImp;
	friend class CGXGridDropTargetPlugin;

	CGXNoOleDataSourceProxy* m_pOleDataSourceProxy;
	friend class CGXOleDataSourceProxy;

	//@cmember
	// Enable locale numbers
	GRID_API void EnableLocaleNumbers();
	//@cmember
	// Enable cell tips
	GRID_API void EnableCellTips(CRuntimeClass* pCellTipWndFactory = NULL, BOOL bShowHeaders = FALSE, 
						BOOL bShowActive = FALSE, UINT nDelay = 500);
	CGXPluginComponent* m_pCellTipPlugin;
	
	// Plugins
	//@cmember
	// Enable mouse wheel.
	GRID_API void EnableMouseWheel();    // Support for WM_MOUSEWHEEL message
	//@cmember
	// Enable intellimouse.
	GRID_API void EnableIntelliMouse();  // Advanced Intelli-mouse support with Internet Explorer-like 
								// panning and scrolling

	CGXPluginComponent* m_pImousePlugin;		// Make sure only one of the two above gets called.
	//@cmember
	// Enable scroll tips.
	GRID_API void EnableScrollTips();
	CGXPluginComponent* m_pScrollTipPlugin;		
	//@cmember
	// Implement auto scroll.
	GRID_API void ImplementAutoScroll();
	friend class CGXAutoScrollPlugin;
	CGXPluginComponent* m_pAutoScrollPlugin;		

	void* end_component_ptr;
	//@cmember
	// Tooltips, Formula Engine, Ole Dnd see below
	GRID_API void ImplementToolTips();
	
	//@cmember
	// Auto delete pointer.
	GRID_API void AutoDeletePtr(void* p);
	CPtrList m_autodeleteptrlist;

	CGXAppData* m_pAppData;

// Initialization, Client Area and Parameter Object
public:
	// Client Area
	//@cmember
	// Get grid rect.
	GRID_API CRect GetGridRect();
	//@cmember
	// Set grid rect.
	GRID_API void  SetGridRect(BOOL bSet, LPRECT rect = NULL);

	// Parameter object
	//@cmember
	// Get param.
	GRID_API CGXGridParam* GetParam();
	//@cmember
	// Set param.
	GRID_API void SetParam(CGXGridParam* pParam, BOOL bMustDelete = TRUE);

	// Printing mode
	//@cmember
	// Is printing?
	GRID_API BOOL IsPrinting();
	//@cmember
	// Set printing.
	GRID_API virtual void SetPrinting(BOOL b, BOOL bClientToRect = FALSE);

// Update, Hints, Initialization
public:
	//@cmember
	// Enable hints.
	GRID_API void EnableHints(BOOL b = TRUE);
	//@cmember
	// Set modified flag.
	GRID_API virtual void SetModifiedFlag(BOOL bModified = TRUE);
	//@cmember
	// Get grid doc.
	CDocument* GetGridDoc();

	//@cmember
	// Set view id.
	GRID_API void SetViewID(int nID);
	//@cmember
	// Get view id.
	GRID_API int GetViewID();

	//@cmember
	// Set grid wnd.
	GRID_API void SetGridWnd(CWnd* pGridWnd, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);
	//@cmember
	// Get grid wnd.
	GRID_API CWnd* GridWnd();

public:
	//@cmember
	// OnGridPrepareDC handler.
	GRID_API virtual void OnGridPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	//@cmember
	// UpdateAllViews handler.
	GRID_API virtual void UpdateAllViews(CWnd* pSender, LPARAM lHint, CObject* pHint);

protected:
	//@cmember
	// OnGridInitialUpdate handler.
	GRID_API virtual void OnGridInitialUpdate();
	//@cmember
	// OnActivateGrid handler.
	GRID_API virtual BOOL OnActivateGrid( BOOL bActivate ); // called by OnActivateView
	//@cmember
	// OnGridUpdate handler.
	GRID_API virtual void OnGridUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

public:
// data members
	CWnd*   m_pGridWnd;     // this a main anchor for multiple inheritance
							// m_pGridWnd points to CGXGridView or CGridControl

	CDocument* m_pGridDoc; // pointer to the document (or NULL)

	BOOL    m_bIsViewContext;   // TRUE if the grid is used in a CView

protected:
	BOOL    m_bHintsEnabled;
	int     m_nViewID;
	int     m_nPrintHandleRecordCount;

// Cell Formatting
public:
	//@cmember
	// Set style range.
	GRID_API virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Set style range.
	GRID_API BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	//@cmember
	// Get style row/col.
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	//@cmember
	// Set value range.
	GRID_API BOOL SetValueRange(const CGXRange& range, const CString& s, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	//@cmember
	// Set value range.
	GRID_API BOOL SetValueRange(const CGXRange& range, LPCTSTR lpsz, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
#ifdef _UNICODE
	//@cmember
	// Set value range.
	GRID_API BOOL SetValueRange(const CGXRange& range, const char* lpsz, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
#endif
	//@cmember
	// Set value range.
	GRID_API BOOL SetValueRange(const CGXRange& range, DWORD dw, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	GRID_API BOOL SetValueRange(const CGXRange& range, WORD w, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	GRID_API BOOL SetValueRange(const CGXRange& range, short s, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	GRID_API BOOL SetValueRange(const CGXRange& range, LONG l, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	GRID_API BOOL SetValueRange(const CGXRange& range, float f, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	GRID_API BOOL SetValueRange(const CGXRange& range, double d, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);

	//@cmember
	// SetExpressionRowCol allows you to specify expression (number, value, date, formula) for a cell
	// The value will be parsed and correct cell format, formula stored (Formula Engine support must be enabled).
	GRID_API BOOL SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, const CString& s, UINT flags = GX_UPDATENOW);
	//@cmember
	// Get expression row/col.
	GRID_API const CString& GetExpressionRowCol(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Get style array.
	GRID_API virtual CObArray* GetStyleArray(const CGXRange& range, int nType, CGXLongOperation* pTheOp);
	//@cmember
	// Get value row/col.
	GRID_API const CString& GetValueRowCol(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Get column style.
	GRID_API BOOL GetColStyle(ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy);
	//@cmember
	// Get row style.
	GRID_API BOOL GetRowStyle(ROWCOL nRow, CGXStyle& style, GXModifyType mt = gxCopy);
	//@cmember
	// Get table style.
	GRID_API BOOL GetTableStyle(CGXStyle& style, GXModifyType mt = gxCopy);

	// Note: LookupStyle returns reference to temporary style-object. See class-reference.
	//@cmember
	// Lookup style row/col.
	GRID_API virtual const CGXStyle& LookupStyleRowCol(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Compose style row/col.
	GRID_API virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);
	//@cmember
	// Store style row/col.
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	//@cmember
	// Update style range.
	GRID_API virtual void UpdateStyleRange(const CGXRange &range, const CGXStyle* pStyle = NULL, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_INVALIDATE, BOOL bCreateHint = TRUE);
	//@cmember
	// Create style.
	GRID_API virtual CGXStyle* CreateStyle();
	//@cmember
	// Recycle style.
	GRID_API virtual void RecycleStyle(CGXStyle* pStyle);

	// Changing the styles map (with undo/redo support)
	//@cmember
	// Change style map.
	GRID_API virtual BOOL ChangeStylesMap(const CGXStylesMap& stylesMap, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Update style map.
	GRID_API virtual void UpdateStylesMap(UINT flags, BOOL bCreateHint = TRUE);

	// Changing the proprties (with undo/redo support)
	//@cmember
	// Change properties. 
	GRID_API virtual BOOL ChangeProperties(const CGXProperties& properties, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Update properties. 
	GRID_API virtual void UpdateProperties(UINT flags, BOOL bCreateHint = TRUE);

	// Changing the base style setting (with undo/redo support)
	//@cmember
	// Change standard style. 
	GRID_API BOOL ChangeStandardStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Change row header style. 
	GRID_API BOOL ChangeRowHeaderStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Change column header style. 
	GRID_API BOOL ChangeColHeaderStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	// all above call ChangeBaseStyle

	//@cmember
	// Change base style.
	GRID_API virtual BOOL ChangeBaseStyle(WORD wStyleID, const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Update base style. 
	GRID_API virtual void UpdateBaseStyle(WORD wStyleId, UINT flags, BOOL bCreateHint = TRUE);

	// Some useful shortcuts for the standard-styles 
	// (but better use ChangeBaseStyle to change base styles)
	//@cmember
	// Get standard style.
	GRID_API CGXStyle& StandardStyle();
	//@cmember
	// Get row header style.
	GRID_API CGXStyle& RowHeaderStyle();
	//@cmember
	// Get column header style.
	GRID_API CGXStyle& ColHeaderStyle();
	//@cmember
	// Get base style.
	GRID_API CGXStyle& BaseStyle(WORD wStyleID);

	//@cmember
	// Update font metrics.
	GRID_API void UpdateFontMetrics();
		// call this method to update internal font metrics
		// after changing the font for the StandardStyle .

protected:
	CPtrList		m_StyleBuffer;
	CGXStyle*		m_pStyleValue;
	CGXStyle*		m_pStyleGetValue;
	CRuntimeClass*	m_pStyleClass;
	const CGXStyle*	m_pOldStyle;
	CGXPen			m_tempPen;

public:
	BOOL m_bOnlyValueNeeded;
	BOOL m_bNoValueNeeded;

// Cell coordinates
public:
	// Number of Rows and Colums

	//@cmember
	// be careful: SetRowCount calls InsertRows and RemoveRows
	GRID_API virtual BOOL SetRowCount(ROWCOL nRows, UINT flags = GX_UPDATENOW);
	//@cmember
	// be careful: SetColCount calls InsertCols and RemoveCols
	GRID_API virtual BOOL SetColCount(ROWCOL nCols, UINT flags = GX_UPDATENOW);
	//@cmember
	// Get row count.
	GRID_API virtual ROWCOL GetRowCount();
	//@cmember
	// Get column count.
	GRID_API virtual ROWCOL GetColCount();

protected:
	//@cmember
	// Store row count.
	GRID_API virtual BOOL StoreRowCount(ROWCOL nRows);
	//@cmember
	// Store column count.
	GRID_API virtual BOOL StoreColCount(ROWCOL nCols);
	//@cmember
	// Update changed row count.
	GRID_API virtual void UpdateChangedRowCount(ROWCOL nOldRows, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update changed column count.
	GRID_API virtual void UpdateChangedColCount(ROWCOL nOldCols, UINT flags, BOOL bCreateHint = FALSE);

	// Insert, Remove and Move Cells
public:
	//@cmember
	// Remove rows.
	GRID_API virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Remove columns.
	GRID_API virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Move rows. 
	GRID_API virtual BOOL MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Move columns. 
	GRID_API virtual BOOL MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Insert rows. 
	GRID_API virtual BOOL InsertRows(ROWCOL nRow, ROWCOL nCount, int* anHeightArray = NULL, CObArray* pCellsArray = NULL, CObArray* pRowsArray = NULL, ROWCOL nColCount = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Insert columns. 
	GRID_API virtual BOOL InsertCols(ROWCOL nCol, ROWCOL nCount, int* anWidthArray = NULL, CObArray* pCellsArray = NULL, CObArray* pColsArray = NULL, ROWCOL nRowCount = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

protected:
	//@cmember
	// Store insert rows.
	GRID_API virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	//@cmember
	// Store insert columns.
	GRID_API virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	//@cmember
	// Store remove rows. 
	GRID_API virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);
	//@cmember
	// Store remove columns. 
	GRID_API virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);
	//@cmember
	// Store move rows. 
	GRID_API virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	//@cmember
	// Store move columns.
	GRID_API virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);

	//@cmember
	// Update insert rows. 
	GRID_API virtual void UpdateInsertRows(ROWCOL nRow, ROWCOL nCount, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update insert columns.
	GRID_API virtual void UpdateInsertCols(ROWCOL nCol, ROWCOL nCount, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update remove rows.
	GRID_API virtual void UpdateRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update remove columns. 
	GRID_API virtual void UpdateRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update move rows.
	GRID_API virtual void UpdateMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update move columns.
	GRID_API virtual void UpdateMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, BOOL bCreateHint = FALSE);

	// Frozen Rows and Columns
public:
	//@cmember
	// Set frozen rows.
	GRID_API virtual BOOL SetFrozenRows(ROWCOL nFrozenRows, ROWCOL nHeaderRows = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Set frozen columns.
	GRID_API virtual BOOL SetFrozenCols(ROWCOL nFrozenCols, ROWCOL nHeaderCols = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Get frozen rows.
	GRID_API virtual ROWCOL GetFrozenRows();
	//@cmember
	// Get frozen columns.
	GRID_API virtual ROWCOL GetFrozenCols();
	//@cmember
	// Get header rows.
	GRID_API virtual ROWCOL GetHeaderRows();
	//@cmember
	// Get header columns.
	GRID_API virtual ROWCOL GetHeaderCols();
	//@cmember
	// Is frozen row?
	GRID_API BOOL IsFrozenRow(ROWCOL nRow);
	//@cmember
	// Is frozen column?
	GRID_API BOOL IsFrozenCol(ROWCOL nCol);

protected:
	//@cmember
	// Store frozen rows. 
	GRID_API virtual BOOL StoreFrozenRows(ROWCOL nFrozenRows, ROWCOL nHeaderRows);
	//@cmember
	// Store frozen columns.
	GRID_API virtual BOOL StoreFrozenCols(ROWCOL nFrozenCols, ROWCOL nHeaderCols);
	//@cmember
	// Update frozen rows.
	GRID_API virtual void UpdateFrozenRows(ROWCOL nOldFrozenRows, ROWCOL nOldHeaderRows, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update frozen columns.
	GRID_API virtual void UpdateFrozenCols(ROWCOL nOldFrozenCols, ROWCOL nOldHeaderCols, UINT flags, BOOL bCreateHint = FALSE);

	// Sorting the grid
public:
	// Rows
	//@cmember
	// Sort rows.
	GRID_API virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	//@cmember
	// Move data rows.
	GRID_API virtual BOOL MoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Store move data rows.
	GRID_API virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	//@cmember
	// Update move data rows.
	GRID_API virtual void UpdateMoveDataRows(const CGXRange& sortRange, UINT flags = GX_UPDATENOW, BOOL bCreateHint =TRUE);
	//@cmember
	// OnGetSortRowsKey handler.
	GRID_API virtual void OnGetSortRowsKey(ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// Columns
	//@cmember
	// Sort columns.
	GRID_API virtual void SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	//@cmember
	// Move data columns.
	GRID_API virtual BOOL MoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Store move data columns.
	GRID_API virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);
	//@cmember
	// Update move data columns.
	GRID_API virtual void UpdateMoveDataCols(const CGXRange& sortRange, UINT flags = GX_UPDATENOW, BOOL bCreateHint =TRUE);
	//@cmember
	// OnGetSortColsKey handler.
	GRID_API virtual void OnGetSortColsKey(ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// General
	//@cmember
	// Sort Keys
	GRID_API virtual void SortKeys(const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray);
	//@cmember
	// Get sort keys.
	GRID_API virtual void GetSortKey(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// Used within a cell control to control whether grid can scroll
public: 
	//@cmember
	// Set scroll locked from cell.
	GRID_API virtual BOOL SetScrollLockedFromCell(BOOL b = TRUE);
	//@cmember
	// Is scroll locked from cell?
	GRID_API virtual BOOL IsScrollLockedFromCell();
protected:
	BOOL m_bScrollLockedFromCell;

	// Current view
public:
	//@cmember
	// Set top row.
	GRID_API virtual void SetTopRow(ROWCOL nRow, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Set left column.
	GRID_API virtual void SetLeftCol(ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Set top left row/col.
	GRID_API void SetTopLeftRowCol(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);

	//@cmember
	// Get top row.
	GRID_API ROWCOL GetTopRow();
	//@cmember
	// Get left column.
	GRID_API ROWCOL GetLeftCol();
	//@cmember
	// Get top left row/col.
	GRID_API void GetTopLeftRowCol(ROWCOL* nRow, ROWCOL* nCol);

	//@cmember
	// Get client row.
	GRID_API ROWCOL GetClientRow(ROWCOL nRow);
	//@cmember
	// Get client column.
	GRID_API ROWCOL GetClientCol(ROWCOL nCol);
	//@cmember
	// Get row.
	GRID_API ROWCOL GetRow(ROWCOL nClientRow);
	//@cmember
	// Get column.
	GRID_API ROWCOL GetCol(ROWCOL nClientCol);

	//@cmember
	// Is drag selection?
	GRID_API BOOL IsDragSelection(int* pnSelDragMode = NULL);

protected:
	// User is dragging rows or columns
	//@cmember
	// OnSelDragStart handler.
	GRID_API virtual BOOL OnSelDragStart(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnSelDragMove handler.
	GRID_API virtual BOOL OnSelDragMove(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nDragRow, ROWCOL nDragCol);
	//@cmember
	// OnSelDragDrop handler.
	GRID_API virtual BOOL OnSelDragDrop(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nDragRow, ROWCOL nDragCol);
	//@cmember
	// OnSelDragCancel handler.
	GRID_API virtual void OnSelDragCancel();

	//@cmember
	// OnSelDragRowsStart handler.
	GRID_API virtual BOOL OnSelDragRowsStart(ROWCOL nFirstRow, ROWCOL nLastRow);
	//@cmember
	// OnSelDragColsStart handler.
	GRID_API virtual BOOL OnSelDragColsStart(ROWCOL nFirstCol, ROWCOL nLastCol);
	//@cmember
	// OnSelDragRowsMove handler.
	GRID_API virtual BOOL OnSelDragRowsMove(ROWCOL nFirstRow, ROWCOL nLastRow, ROWCOL nDestRow);
	//@cmember
	// OnSelDragColsMove handler.
	GRID_API virtual BOOL OnSelDragColsMove(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);
	//@cmember
	// OnSelDragRowsDrop handler.
	GRID_API virtual BOOL OnSelDragRowsDrop(ROWCOL nFirstRow, ROWCOL nLastRow, ROWCOL nDestRow);
	//@cmember
	// OnSelDragColsDrop handler.
	GRID_API virtual BOOL OnSelDragColsDrop(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);

// Cell Size and Position
// Cell size
public:
	//@cmember
	// Set row height.
	GRID_API virtual BOOL SetRowHeight(ROWCOL nFromRow, ROWCOL nToRow, int nHeight, int* anHeightArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Set column width.
	GRID_API virtual BOOL SetColWidth(ROWCOL nFromCol, ROWCOL nToCol, int nWidth, int* anWidthArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Set default row height.
	GRID_API virtual BOOL SetDefaultRowHeight(int nHeight, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Set default column width.
	GRID_API virtual BOOL SetDefaultColWidth(int nWidth, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	//@cmember
	// Get row height.
	GRID_API virtual int  GetRowHeight(ROWCOL nRow);
	//@cmember
	// Get column width.
	GRID_API virtual int  GetColWidth(ROWCOL nCol);
	//@cmember
	// Get Default row height.
	GRID_API virtual int  GetDefaultRowHeight();
	//@cmember
	// Get default column width.
	GRID_API virtual int  GetDefaultColWidth();

	//@cmember
	// Hide rows.
	GRID_API virtual BOOL HideRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bHide = TRUE, BOOL* abHideArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Hide columns.
	GRID_API virtual BOOL HideCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bHide = TRUE, BOOL* abHideArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	//@cmember
	// Is row hidden?
	GRID_API virtual BOOL IsRowHidden(ROWCOL nRow);
	//@cmember
	// Is column hidden?
	GRID_API virtual BOOL IsColHidden(ROWCOL nCol);

	//@cmember
	// Resize row heights to fit.
	GRID_API virtual BOOL ResizeRowHeightsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW);
	//@cmember
	// Resize column widths to fit.
	GRID_API virtual BOOL ResizeColWidthsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW);

	// limit cell size so that it is not larger than the grid area
	BOOL    m_bLimitRowHeight,  // checked in GetRowHeight
			m_bLimitColWidth;   // checked in GetColWidth

protected:
	//@cmember
	// Store hide row.
	GRID_API virtual BOOL StoreHideRow(ROWCOL nRow, BOOL bHide);
	//@cmember
	// Store hide column.
	GRID_API virtual BOOL StoreHideCol(ROWCOL nCol, BOOL bHide);

	//@cmember
	// Store default row height.
	GRID_API virtual BOOL StoreDefaultRowHeight(int nHeight);
	//@cmember
	// Store default column width.
	GRID_API virtual BOOL StoreDefaultColWidth(int nWidth);
	//@cmember
	// Store column width.
	GRID_API virtual BOOL StoreColWidth(ROWCOL nCol, int nWidth = 0);
	//@cmember
	// Store row height.
	GRID_API virtual BOOL StoreRowHeight(ROWCOL nRow, int nHeight = 0);

	//@cmember
	// Update changed column widths.
	GRID_API virtual void UpdateChangedColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update chagned row heights.
	GRID_API virtual void UpdateChangedRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags, BOOL bCreateHint = FALSE);

public:
	// convert Height and Width pixel values to logical values and vice versa
	//@cmember
	// Height Device Points to Logical Points.
	GRID_API LONG Height_DPtoLP(int nHeight);
	//@cmember
	// Width Device Points to Logical Points.
	GRID_API LONG Width_DPtoLP(int nWidth);
	//@cmember
	// Height Logical Points to Device Points.
	GRID_API int Height_LPtoDP(LONG nHeight);
	//@cmember
	// Width Logical Points to Device Points.
	GRID_API int Width_LPtoDP(LONG nWidth);
	//@cmember
	// Get font height.
	GRID_API virtual int GetFontHeight();
	//@cmember
	// Get font width.
	GRID_API virtual int GetFontWidth();

	// Get Row, Col under point
	//@cmember
	// Hit test.
	GRID_API virtual int HitTest(CPoint& pt, ROWCOL* Row = NULL, ROWCOL* Col = NULL, CRect* rectHit = NULL);
	//@cmember
	// OnExtHitText handler.
	GRID_API virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);

	// Return row heights and column widths
	//@cmember
	// Get array with column widths.
	GRID_API void GetArrayWithColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* pArray);
	//@cmember
	// Get array with row heights.
	GRID_API void GetArrayWithRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int* pArray);

	// Calculations
	//@cmember
	// Calculate sum of row heights.
	GRID_API int CalcSumOfRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int nAbortAt = 0);
	//@cmember
	// Calculate sum of column widths.
	GRID_API int CalcSumOfColWidths(ROWCOL nFromCol, ROWCOL nToCol, int nAbortAt = 0);
	//@cmember
	// Calculate sum of client row heights.
	GRID_API int CalcSumOfClientRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int nAbortAt = 0);
	//@cmember
	// Calculate sum of client column widths.
	GRID_API int CalcSumOfClientColWidths(ROWCOL nFromCol, ROWCOL nToCol, int nAbortAt = 0);

	GRID_API CRect CalcRectFromRowColExEx(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol);
	GRID_API CRect CalcRectFromRowColEx(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol);
	GRID_API CRect CalcRectFromRowColExEx(ROWCOL nRow, ROWCOL nCol);
	GRID_API CRect CalcRectFromRowColEx(ROWCOL nRow, ROWCOL nCol);
	GRID_API CRect CalcRectFromRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, BOOL bOutsideClientArea = FALSE);
	GRID_API CRect CalcRectFromRowCol(ROWCOL nRow, ROWCOL nCol);

	// Get rows and cols from Points
	// Note: Result can be GX_INVALID
	//@cmember
	// Calculate client row from point.
	GRID_API ROWCOL CalcClientRowFromPt(CPoint& pt, int* yUp = NULL);
	//@cmember
	// Calculate client column from point.
	GRID_API ROWCOL CalcClientColFromPt(CPoint& pt, int* xLeft = NULL);

	// calculate last visible row or column from GridRect()
	//@cmember
	// Calculate right column from rect.
	GRID_API ROWCOL CalcRightColFromRect(const CRect& rect);
	//@cmember
	// Calculate bottom row from rect.
	GRID_API ROWCOL CalcBottomRowFromRect(const CRect& rect);
	//@cmember
	// Calculate right column from rect.
	GRID_API ROWCOL CalcRightColFromRect(const CRect& rect, BOOL& bLastColVisible);
	//@cmember
	// Calculate bottom row from rect.
	GRID_API ROWCOL CalcBottomRowFromRect(const CRect& rect, BOOL& bLastRowVisible);
	//@cmember
	// Calculate bottom right row column from rect.
	GRID_API void CalcBottomRightRowColFromRect(const CRect& rect, ROWCOL *nRow, ROWCOL *nCol);
	//@cmember
	// Calculate grid line rect.
	GRID_API CRect CalcGridLineRect(int type, ROWCOL nClientRC);

	//@cmember
	// Get  last visible row.
	GRID_API ROWCOL GetLastVisibleRow(BOOL* pbLastRowVisible = NULL);
	//@cmember
	// Get last visible column.
	GRID_API ROWCOL GetLastVisibleCol(BOOL* pbLastColVisible = NULL);

	//@cmember
	// Is tracking?
	GRID_API BOOL IsTracking(int* pnTrackingMode = NULL, ROWCOL* pnTracking = NULL);

protected:
	// Attributes for HitTest
	BOOL   m_bHitTestSelEdge;
	int    m_nHitTestFrame;

	// Tracking
	//@cmember
	// OnStartTracking handler.
	GRID_API virtual BOOL OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode);
	//@cmember
	// OnMoveTracking handler.
	GRID_API virtual void OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	//@cmember
	// OnEndTracking handler.
	GRID_API virtual void OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	//@cmember
	// OnCancelTracking handler.
	GRID_API virtual void OnCancelTracking();

	//@cmember
	// OnTrackColWidth handler.
	GRID_API virtual BOOL OnTrackColWidth(ROWCOL nCol);  // return FALSE to prevent the display of the column-width cursor
	//@cmember
	// OnTrackColWidthStart handler.
	GRID_API virtual BOOL OnTrackColWidthStart(ROWCOL nCol);
	//@cmember
	// OnTrackColWidthMove handler.
	GRID_API virtual BOOL OnTrackColWidthMove(ROWCOL nCol, int nWidth);
	//@cmember
	// OnTrackColWidthEnd handler.
	GRID_API virtual BOOL OnTrackColWidthEnd(ROWCOL nCol, int nWidth);

	//@cmember
	// OnTrackRowHeight handler.
	GRID_API virtual BOOL OnTrackRowHeight(ROWCOL nRow); // return FALSE to prevent the display of the row-height cursor
	//@cmember
	// OnTrackRowHeightStart handler.
	GRID_API virtual BOOL OnTrackRowHeightStart(ROWCOL nRow);
	//@cmember
	// OnTrackRowHeightMove handler.
	GRID_API virtual BOOL OnTrackRowHeightMove(ROWCOL nRow, int nHeight);
	//@cmember
	// OnTrackRowHeightEnd handler.
	GRID_API virtual BOOL OnTrackRowHeightEnd(ROWCOL nRow, int nHeight);

// Zoom, ReadOnly
public:
	//@cmember
	// Set zoom.
	GRID_API virtual void SetZoom(int nZoom, UINT flags = GX_UPDATENOW);
	//@cmember
	// Set read only.
	GRID_API virtual void SetReadOnly(BOOL bReadOnly = TRUE);
	//@cmember
	// Get zoom.
	GRID_API virtual int  GetZoom();
	//@cmember
	// Is read only?
	GRID_API virtual BOOL IsReadOnly();

protected:
	//@cmember
	// Store zoom.
	GRID_API virtual BOOL StoreZoom(int nZoom, BOOL bCreateHint = TRUE);
	//@cmember
	// Store read only.
	GRID_API virtual BOOL StoreReadOnly(BOOL bReadOnly);
	//@cmember
	// Update zoom.
	GRID_API virtual void UpdateZoom(int nOldZoom, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Update read only.
	GRID_API virtual void UpdateReadOnly(BOOL bOldReadOnly, BOOL bCreateHint = FALSE);

	// support for CGXTabWnd, CGXRecordInfoWnd
public:
	//@cmember
	// Get tab wnd.
	GRID_API CGXTabWnd* GetTabWnd() const;
	//@cmember
	// Get shared scrollbar parent wnd.
	GRID_API CWnd* GetSharedScrollbarParentWnd() const;
	//@cmember
	// OnInfoWndMoveRecord handler.
	GRID_API virtual void OnInfoWndMoveRecord(int nDirection, long nRecord);
	//@cmember
	// Can activate grid?
	GRID_API virtual BOOL CanActivateGrid(BOOL bActivate);
	//@cmember
	// Can change tab?
	GRID_API virtual BOOL CanChangeTab();
	//@cmember
	// Get record info wnd.
	GRID_API CGXRecordInfoWnd* GetRecordInfoWnd() const;
	//@cmember
	// OnTabChanged handler.
	GRID_API virtual void OnTabChanged(int nTab);
	//@cmember
	// Get tab name.
	GRID_API CString GetTabName();
	//@cmember
	// Set tab name.
	GRID_API void SetTabName(CString s);
	//@cmember
	// Update record info wnd.
	GRID_API virtual void UpdateRecordInfoWnd();

// Selections and Covered Cells
	// Selected Cells (see also CGXRangeList)
public:
	//@cmember
	// Get selected columns.
	GRID_API BOOL GetSelectedCols(CRowColArray& awLeft, CRowColArray& awRight, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);
	//@cmember
	// Get selected rows.
	GRID_API virtual BOOL GetSelectedRows(CRowColArray& awTop, CRowColArray& awBottom, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);
	//@cmember
	// Get selected columns.
	GRID_API ROWCOL GetSelectedCols(CRowColArray& awCols, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);
	//@cmember
	// Get selected rows.
	GRID_API virtual ROWCOL GetSelectedRows(CRowColArray& awRows, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);

	//@cmember
	// Set selection.
	GRID_API virtual void SetSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0);

	//@cmember
	// Copy range list.
	GRID_API virtual BOOL CopyRangeList(CGXRangeList& list, BOOL bEdit);

	//@cmember
	// Is selecting cells?
	GRID_API BOOL IsSelectingCells();
	//@cmember
	// Get hit state.
	GRID_API WORD GetHitState();

	//@cmember
	// Get invert state row/col.
	GRID_API virtual BOOL GetInvertStateRowCol(ROWCOL nRow, ROWCOL nCol, const CGXRangeList* pSelList);
	//@cmember
	// Select range.
	GRID_API virtual void SelectRange(const CGXRange& range, BOOL bSelect = TRUE, BOOL bUpdate = TRUE);

	CGXRange m_rgLastSelectionFrame;
	int m_nLastSelectionFrameMarker;

	//@cmember
	// Draw selection frame.
	GRID_API virtual void DrawSelectionFrame(CDC* pDC, BOOL bDrawOld = TRUE, const CGXRange* pNewRange = NULL);
	//@cmember
	// Lock selection frame.
	GRID_API BOOL LockSelectionFrame(BOOL bLock, BOOL bCreateHint = TRUE);
	//@cmember
	// Tobble selection frame marker.
	GRID_API virtual void ToggleSelectionFrameMarker();

protected:
	//@cmember
	// Draw selection range frame.
	GRID_API virtual void DrawSelectionRangeFrame(CDC* pDC, const CGXRange& rg, int nMarker = 0, BOOL bOnlyMarker = FALSE);
	//@cmember
	// Draw invert frame.
	GRID_API virtual void DrawInvertFrame(CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker = FALSE);

	//@cmember
	// Store select range.
	GRID_API virtual BOOL StoreSelectRange(const CGXRange& range, BOOL bSelect);
	//@cmember
	// Update select range.
	GRID_API virtual void UpdateSelectRange(const CGXRange& range, const CGXRangeList* pOldRangeList, BOOL bCreateHint);

	// invert cells
	//@cmember
	// Prepare change selection.
	GRID_API virtual void PrepareChangeSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0, BOOL bCreateHint = FALSE);
	//@cmember
	// Prepare clear selection.
	GRID_API virtual void PrepareClearSelection(BOOL bCreateHint = FALSE);

	// Events
	//@cmember
	// Can change selection?
	GRID_API virtual BOOL CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey);
	//@cmember
	// OnChangeSelection handler.
	GRID_API virtual void OnChangedSelection(const CGXRange* changedRect, BOOL bIsDragging, BOOL bKey);
	//@cmember
	// OnStartSelection handler.
	GRID_API virtual BOOL OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point);

// just for compatibility with OG 1.0. It is recommended that
// you override CanChangeSelection instead.
	//@cmember
	// Prepare change selection.
	GRID_API virtual void PreChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey);

	// Attributes
	BOOL m_bLockDrawSelectionFrame;

// Auto Fill
protected:
	//@cmember
	// OnStartAutoFillSelection handler.
	GRID_API virtual BOOL OnStartAutoFillSelection(CGXRange& rgStart, UINT& flags, CPoint& point);
	//@cmember
	// Can change auto fill selection?
	GRID_API virtual BOOL CanChangeAutoFillSelection(CGXRange& rgNew, const CGXRange& rgStart);
	//@cmember
	// Do auto fill.
	GRID_API virtual void DoAutoFill(CGXRange& rgFinal, CGXRange& rgStart);
	//@cmember
	// OnAutoFillDone handler.
	GRID_API virtual void OnAutoFillDone(CGXRange& rgFinal);

// Covered Cells
public:
	//@cmember
	// Set covered cells row/col.
	GRID_API virtual BOOL SetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Get covered cells row/col.
	GRID_API virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);

protected:
	//@cmember
	// Store covered cells row/col.
	GRID_API virtual BOOL StoreCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);
	//@cmember
	// Update covered cells row/col.
	GRID_API virtual void UpdateCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Merge covered cells.
	GRID_API virtual void MergeCoveredCells(CGXRange& range);

// Floating Cells
public:
	//@cmember
	// Set float cells mode.
	GRID_API void SetFloatCellsMode(WORD nMode, BOOL bRedraw = TRUE);
	//@cmember
	// Get float cells mode.
	GRID_API WORD GetFloatCellsMode() const;

	//@cmember
	// Delay float cells.
	GRID_API void DelayFloatCells(const CGXRange& range, ROWCOL nMaxCols = GX_INVALID);
	//@cmember
	// Eval float cells?
	GRID_API BOOL EvalFloatCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

	//@cmember
	// Can float cell?
	GRID_API virtual BOOL CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	//@cmember
	// Get floated cells row/col.
	GRID_API CGXRange* GetFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);

protected:
	//@cmember
	// Set floated cells row/col.
	GRID_API BOOL SetFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW);
	//@cmember
	// Merge floated cells.
	GRID_API void MergeFloatedCells(CGXRange& range);
	//@cmember
	// Update floated cells row/col.
	GRID_API void UpdateFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Get float cells pool.
	GRID_API CGXSpanCellPool* GetFloatCellsPool();

	// Implementation - Float Cell Data
	BOOL m_bLockEvalFloatCells;

	struct GRID_API FloatCellsData
	{
		ROWCOL nColOffset;
		CObArray apStylesArray;         // cached style objects for latest row
		CWordArray awSizeArray;         // cached CalcSize return values for latest row
		ROWCOL nLastRow;                // latest row id

		void InitColOffset(ROWCOL nCol);
		int GetIndex(ROWCOL nCol);
		void Reset(CGXGridCore* pGrid);
	} m_FloatCellData;

// Merge Cells
public:
	//@cmember
	// Set merge cells mode.
	GRID_API void SetMergeCellsMode(WORD nMode, BOOL bRedraw = TRUE);
	//@cmember
	// Get merge cells mode.
	GRID_API WORD GetMergeCellsMode() const;
	//@cmember
	// Delay merge cells.
	GRID_API void DelayMergeCells(const CGXRange& range, ROWCOL nMaxRows = GX_INVALID, ROWCOL nMaxCols = GX_INVALID);
	//@cmember
	// Eval merge cells.
	GRID_API BOOL EvalMergeCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	//@cmember
	// Get merged cells row/col.
	GRID_API CGXRange* GetMergedCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType = -1);
	//@cmember
	// Can merge cell?
	GRID_API virtual BOOL CanMergeCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType);
	//@cmember
	// Can merge cells?
	GRID_API virtual BOOL CanMergeCells(const CGXStyle& style1, const CGXStyle& style2);

protected:
	//@cmember
	// Set merged cells row/col.
	GRID_API BOOL SetMergedCellsRowCol(int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW);
	//@cmember
	// Update merged cells row/col.
	GRID_API void UpdateMergedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);
	//@cmember
	// Merge merged cells.
	GRID_API void MergeMergedCells(CGXRange& range);

	BOOL m_bLockEvalMergeCells;

	enum MergeCellType
	{
		mtHorz = 0,
		mtVert = 1
	};

	struct GRID_API MergeCellsData
	{
		ROWCOL nColOffset;
		CObArray apStylesArray;         // cached style objects for latest row
		CWordArray awSizeArray;         // cached CalcSize return values for latest row
		ROWCOL nLastRow;                // latest row id

		void InitColOffset(ROWCOL nCol);
		int GetIndex(ROWCOL nCol);
		void Reset(CGXGridCore* pGrid);
	} m_MergeCellData;

	CGXRange m_rgMerged;

// Covered, Float and Merge Cells
public:
	//@cmember
	// Get cell range row/col.
	GRID_API virtual CGXRange* GetCellRangeRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	//@cmember
	// Eval visible float merge cells.
	GRID_API BOOL EvalVisibleFloatMergeCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	//@cmember
	// Eval visible float merge cells.
	GRID_API virtual BOOL EvalVisibleFloatMergeCells(const CGXRange& range, ROWCOL nfr, ROWCOL nfc, ROWCOL nTopRow, ROWCOL nLefCol, ROWCOL nLastRow, ROWCOL nLastCol, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

// Find&Replace
public:
	//@cmember
	// Find text.
	GRID_API BOOL FindText(BOOL bSetCell = TRUE);
	//@cmember
	// Find text.
	GRID_API BOOL FindText(ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
	//@cmember
	// Get selected text.
	GRID_API void GetSelectedText(CString& strResult);

	// Find&Replace - Overridables
	//@cmember
	// OnFindNext handler.
	GRID_API virtual void OnFindNext(LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	//@cmember
	// OnReplaceSel handler.
	GRID_API virtual void OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	//@cmember
	// OnReplaceAll handler.
	GRID_API virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	//@cmember
	// OnTextNotFound handler.
	GRID_API virtual void OnTextNotFound(LPCTSTR lpszFind);
	//@cmember
	// OnShowFindReplaceDialog handler.
	GRID_API virtual void OnShowFindReplaceDialog(BOOL bFindOnly);

protected:
	// Find&Replace - Implementation
	//@cmember
	// OnFindReplace handler.
	GRID_API virtual void OnFindReplace(CFindReplaceDialog* pDialog);

// Attributes
	BOOL    m_bCanceled;
	ROWCOL  m_nFirstRow;

// Undo, Redo
public:
	//@cmember
	// Undo command.
	GRID_API virtual BOOL Undo();
	//@cmember
	// Redo command.
	GRID_API virtual BOOL Redo();
	//@cmember
	// Can Undo?
	GRID_API virtual BOOL CanUndo(CCmdUI* pCmdUI);
	//@cmember
	// Can Redo?
	GRID_API virtual BOOL CanRedo(CCmdUI* pCmdUI);

	//@cmember
	// Begin transaction.
	GRID_API virtual void BeginTrans(LPCTSTR pszDescription);
	//@cmember
	// Commit transaction.
	GRID_API virtual void CommitTrans();
	//@cmember
	// Rollback transaction.
	GRID_API virtual void Rollback();

	//@cmember
	// Add command.
	GRID_API virtual void AddCommand(CGXCommand* pCmd, GXCmdType ctCmd);
	//@cmember
	// Remove command.
	GRID_API virtual void RemoveCommand(GXCmdType ctCmd);
	//@cmember
	// OnCellUndone handler.
	GRID_API virtual void OnCellUndone(ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit = FALSE);
	//@cmember
	// Set advanced undo.
	GRID_API virtual BOOL SetAdvancedUndo(BOOL bAdvUndo);
	//@cmember
	// Get advanced undo info.
	GRID_API virtual CObject* GetAdvancedUndoInfo();
	//@cmember
	// Undo advanced.
	GRID_API virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	//@cmember
	// Clean advanced undo.
	GRID_API virtual void CleanAdvancedUndo();
	//@cmember
	// Execute command.
	GRID_API virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType);

protected:
	// Attributes
	BOOL	m_bBlockCmd;
	BOOL	m_bLastSetEdit;
	BOOL	m_bCellUndone;
	ROWCOL	m_nLastRow;
	ROWCOL	m_nLastCol;
	CString m_sTransText;

	// text for undo/redo menu item
	CString m_sEditRedo;
	CString m_sEditUndo;

// Scrolling
public:
	//@cmember
	// Scroll cell in view.
	GRID_API virtual BOOL ScrollCellInView(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bFloatCell = FALSE);
	//@cmember
	// Do scroll.
	GRID_API virtual BOOL DoScroll(int direction, ROWCOL nCell);
	//@cmember
	// Update scroll bars.
	GRID_API virtual void UpdateScrollbars(BOOL bRedraw = TRUE, BOOL bOnlyIfDimensionChanged = FALSE);
	//@cmember
	// Set scroll bar mode.
	GRID_API virtual void SetScrollBarMode(int nBar, int nSetting, BOOL bRedraw = TRUE);
	//@cmember
	// Get scroll bar mode.
	GRID_API int GetScrollBarMode(int nBar);
	//@cmember
	// Lock scroll bars.
	GRID_API BOOL LockScrollbars(BOOL bLock);
	//@cmember
	// OnAutoScroll handler.
	GRID_API virtual BOOL OnAutoScroll(int direction, ROWCOL nCell);

protected:
	//@cmember
	// OnLefColChange handler.
	GRID_API virtual BOOL OnLeftColChange(ROWCOL nNewLeftCol);
	//@cmember
	// OnTopRowChange handler.
	GRID_API virtual BOOL OnTopRowChange(ROWCOL nNewTopRow);
	//@cmember
	// OnLeftColChanged handler.
	GRID_API virtual void OnLeftColChanged();
	//@cmember
	// OnTopRowChanged handler.
	GRID_API virtual void OnTopRowChanged();

	// Scrollbars
	// I have here my own functions to support 16-Bit Grids with more than 32767 lines or cols
	// even with the 16-Bit version. See description of CWnd->
	//@cmember
	// Set scroll position.
	GRID_API virtual ROWCOL SetScrollPos(int nBar, ROWCOL nPos, BOOL bRedraw = TRUE);
	//@cmember
	// Set scroll range.
	GRID_API virtual void SetScrollRange(int nBar, ROWCOL nMinPos, ROWCOL nMaxPos, BOOL bRedraw = TRUE);
	//@cmember
	// Get scroll position.
	GRID_API virtual ROWCOL GetScrollPos(int nBar) const;
	//@cmember
	// Get scroll range.
	GRID_API virtual void GetScrollRange(int nBar, ROWCOL* lpMinPos, ROWCOL* lpMaxPos) const;
	//@cmember
	// Scroll window.
	GRID_API void ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect = NULL, LPCRECT lpClipRect = NULL);

public:	
	//@cmember
	// Auto scroll.
	GRID_API void AutoScroll(BOOL bSetCapture = FALSE, BOOL bVertical = TRUE, BOOL bHorizontal = TRUE);

	// Prevent or enable use of autoscroll-mode
	//@cmember
	// Set auto scroll.
	void SetAutoScroll(BOOL bAutoScroll);
	//@cmember
	// Set accell arrow key.
	void SetAccelArrowKey(BOOL bEnable);
	//@cmember
	// Set accell scroll bars.
	void SetAccelScrollbars(BOOL bEnable);

protected:
	int		m_nVScrollSetting;
	int		m_nHScrollSetting;
	BOOL	m_bLockedScrollbars;		// prevents flickering of scrolbars
	BOOL	m_bScrollbarsChanged;		// SetScrollRange wil set this to be TRUE

	ROWCOL  m_nLastSBRowCount,			// UpdateScrollbars stores GetRowCount, GetColCount to these
			m_nLastSBColCount;			// attributes.

// The Current Cell
public:
	//@cmember
	// Set current cell.
	GRID_API virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	//@cmember
	// Transfer current cell.
	GRID_API virtual BOOL TransferCurrentCell(BOOL bSaveAndValidate = TRUE, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Get current cell.
	GRID_API BOOL GetCurrentCell(ROWCOL* pnRow, ROWCOL* pnCol, BOOL bIgnorePrint = FALSE);
	//@cmember
	// Get current cell.
	GRID_API BOOL GetCurrentCell(ROWCOL& nRow, ROWCOL& nCol, BOOL bIgnorePrint = FALSE);
	//@cmember
	// Is current cell?
	GRID_API BOOL IsCurrentCell(ROWCOL nRow = GX_INVALID, ROWCOL nCol = GX_INVALID, BOOL bIgnorePrint = FALSE);
	//@cmember
	// Is active current cell?
	GRID_API BOOL IsActiveCurrentCell();
	//@cmember
	// Find next cell.
	GRID_API virtual BOOL FindNextCell(int direction, ROWCOL& nSetRow, ROWCOL& nSetCol);
	//@cmember
	// Process keys.
	GRID_API virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	//@cmember
	// Move current cell.
	GRID_API virtual BOOL MoveCurrentCell(int direction, UINT nCell = 1, BOOL bCanSelectRange = TRUE);
	//@cmember
	// Reset current cell.
	GRID_API virtual void ResetCurrentCell(BOOL bStoreIfModified = TRUE);
	//@cmember
	// Hide current cell.
	GRID_API virtual void HideCurrentCell();

	// delayed message box when invalid cell
	//@cmember
	// Set warning text.
	GRID_API virtual void SetWarningText(LPCTSTR s);
	//@cmember
	// Display warning text.
	GRID_API virtual void DisplayWarningText();

	CString m_sWarningText;
	BOOL    m_bLockActivateGrid;
	BOOL	m_bLockCurrentCell;  // Don't reset current cell when grid is deactivate
	BOOL    m_bRefreshControl;
	BOOL    m_bWarningTextDisplayed;
	BOOL	m_bKillFocusCalled;

protected:
	//@cmember
	// Store current cell.
	GRID_API virtual void StoreCurrentCell(BOOL bActive, ROWCOL nRow = 0, ROWCOL nCol = 0);
	//@cmember
	// Move current cell ex.
	GRID_API virtual BOOL MoveCurrentCellEx(int direction, UINT nCell = 1);

	// events
	//@cmember
	// OnValidateCell handler.
	GRID_API virtual BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnStartEditing handler.
	GRID_API virtual BOOL OnStartEditing(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnModifyCell handler.
	GRID_API virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnCancelEditing handler.
	GRID_API virtual BOOL OnCancelEditing(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnCanceledEditing handler.
	GRID_API virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnEndEditing handler.
	GRID_API virtual BOOL OnEndEditing(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnLeftCell handler.
	GRID_API virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	//@cmember
	// OnDeleteCell handler.
	GRID_API virtual BOOL OnDeleteCell(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnInitCurrentCell handler.
	GRID_API virtual void OnInitCurrentCell(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// OnMovedCurrentCell handler.
	GRID_API virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Can select current cell?
	GRID_API virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	//@cmember
	// OnScrollBecauseOfEdit handler.
	GRID_API virtual BOOL OnScrollBecauseOfEdit(int direction, ROWCOL nCell);
	//@cmember
	// OnLButtonClickedRowCol handler.
	GRID_API virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnMButtonClickedRowCol handler.
	GRID_API virtual BOOL OnMButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnRButtonClickedRowCol handler.
	GRID_API virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnLButtonDblClkRowCol handler.
	GRID_API virtual BOOL OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnMButtonDblClkRowCol handler.
	GRID_API virtual BOOL OnMButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnRButtonDblClkRowCol handler.
	GRID_API virtual BOOL OnRButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	//@cmember
	// OnMouseMoveOver handler.
	GRID_API virtual BOOL OnMouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Buttons and Combobox
	//@cmember
	// OnClickedButtonRowCol handler.
	GRID_API virtual void OnClickedButtonRowCol(ROWCOL nHitRow, ROWCOL nHitCol);
	//@cmember
	// OnLButtonHitRowCol handler.
	GRID_API virtual BOOL OnLButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);
	//@cmember
	// OnMButtonHitRowCol handler.
	GRID_API virtual BOOL OnMButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);
	//@cmember
	// OnRButtonHitRowCol handler.
	GRID_API virtual BOOL OnRButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);

public:
	BOOL m_bDisableMouseMoveOver;

public:
	//@cmember
	// Get current cell control.
	GRID_API CGXControl* GetCurrentCellControl();
	//@cmember
	// Get control.
	GRID_API virtual CGXControl* GetControl(ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Register control.
	GRID_API void RegisterControl(WORD nID, CGXControl* pControl, BOOL bDefault = FALSE, BOOL bShowInStyleSheet = TRUE);
	//@cmember
	// Get registered control.
	GRID_API virtual CGXControl* GetRegisteredControl(WORD nID);

protected:
	CGXControl*		m_pDefaultControl;
	CGXControl*		m_pLastControlHit;
	UINT			m_nLastControlHit;
	CMapPtrToPtr	m_ControlMap;

	BOOL m_bValidatingCell;
	BOOL m_bCacheCurrentCell;   // set this FALSE if you want to outline the current cell with special formattings

	BOOL m_bRefreshOnSetCurrentCell;
					// If your cells appearence is depending on whether
					// it is a current cell or not, you should set
					// m_bRefreshOnSetCurrentCell = TRUE. Otherwise
					// a smarter redrawing of the cell will be used.

	ROWCOL m_nLastInitRow,  // used in OnInitCurrentCell()
		   m_nLastInitCol;

// Splitter support
public:
	CSplitterWnd*   m_pSplitterWnd;
	int             m_nSplitRow,
					m_nSplitCol;

	//@cmember
	// Get other split row child pane.
	CGXGridCore*    GetOtherSplitRowChildPane(int nSplitRow, int nSplitCol);
	//@cmember
	// Get other split column child pane.
	CGXGridCore*    GetOtherSplitColumnChildPane(int nSplitRow, int nSplitCol);

// Range names
public:
	//@cmember
	// Set range name.
	GRID_API virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	//@cmember
	// Get range name.
	GRID_API virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	//@cmember
	// Delete range name.
	GRID_API virtual BOOL DeleteRangeName(LPCTSTR name, CObject* pUndoInfo = NULL, GXCmdType ctCmd = gxDo);

// Clipboard - Cut, Copy and Paste helper
public:
	// copy to clibpoard helpers
	//@cmember
	// Copy range.
	GRID_API virtual BOOL CopyRange(const CGXRange& range);
	//@cmember
	// Copy text to file.
	GRID_API BOOL CopyTextToFile(CFile& destFile, const CGXRange& range);
	//@cmember
	// Copy cells to archive.
	GRID_API BOOL CopyCellsToArchive(CArchive& ar, const CGXRange& range, BOOL bLoadBaseStyles = FALSE);
	//@cmember
	// Copy range.
	GRID_API virtual BOOL CopyRange(const CGXRangeList& selList);
	//@cmember
	// Copy text to file.
	GRID_API virtual BOOL CopyTextToFile(CFile& destFile, const CGXRangeList& selList);
	//@cmember
	// Copy cells to archive.
	GRID_API virtual BOOL CopyCellsToArchive(CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles = FALSE);
	//@cmember
	// Get clipboard style row/col.
	GRID_API virtual BOOL GetClipboardStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles);
	//@cmember
	// Get copy text row/col.
	GRID_API virtual CString GetCopyTextRowCol(ROWCOL nRow, ROWCOL nCol);

	// cut cells - helpers
	//@cmember
	// Cut range.
	GRID_API BOOL CutRange(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	//@cmember
	// Cut range.
	GRID_API virtual BOOL CutRange(const CGXRangeList& selList, BOOL bStyleOrValue = TRUE);

	//@cmember
	// Clear cells.
	GRID_API BOOL ClearCells(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	//@cmember
	// Clear cells.
	GRID_API virtual BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue = TRUE);
	//@cmember
	// Clear cells alternate.
	GRID_API virtual BOOL ClearCellsAlternate(const CGXRange& range, BOOL bStyleOrValue = TRUE);

	// paste cells - helpers
	//@cmember
	// Paste cells from archive.
	GRID_API virtual BOOL PasteCellsFromArchive(CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange = FALSE);
	//@cmember
	// Paste text from buffer.
	GRID_API virtual BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);
	//@cmember
	// Calc buffer dimension.
	GRID_API virtual BOOL CalcBufferDimension(LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols);
	//@cmember
	// Set control text row col.
	GRID_API virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);
	//@cmember
	// Paste text row col.
	GRID_API virtual BOOL PasteTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);

	// paste cells - overridables
	// override this methods if you want to support additional clipboard formats
	//@cmember
	// OnPasteDirect handler.
	GRID_API virtual BOOL OnPasteDirect(const CGXRange& range);
	//@cmember
	// OnPasteFromClipboard handler.
	GRID_API virtual BOOL OnPasteFromClipboard(const CGXRange& range);
	//@cmember
	// OnCheckClipboardFormat handler.
	GRID_API virtual BOOL OnCheckClipboardFormat();

	// copy/move ranges in one step
	//@cmember
	// Store copy cells.
	GRID_API virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	//@cmember
	// Store move cells.
	GRID_API virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, GXCmdType ctCmd);
	//@cmember
	// Copy cells.
	GRID_API virtual BOOL CopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);
	//@cmember
	// Move cells. 
	GRID_API virtual BOOL MoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	//@cmember
	// Displays message box when range is different
	GRID_API virtual BOOL OnPasteDiffRange();

	// Implementation
	//@cmember
	// Copy text to clipboard.
	GRID_API BOOL CopyTextToClipboard(const CGXRangeList& selList);
	//@cmember
	// Copy cells to clipboard.
	GRID_API BOOL CopyCellsToClipboard(const CGXRangeList& selList, BOOL bLoadBaseStyles = FALSE);

	CString m_sImportTabDelim;  // default is '\t', used for separating columns when importing text file
	CString m_sExportTabDelim;  // default is '\t', used for separating columns when exporting text file
	DWORD m_nClipboardFlags;

	// Attributes
protected:
	ROWCOL  m_nRowsCopied,  // No of rows/cols copied by CopyTextToFile or
			m_nColsCopied;  // CopyCellsToArchive operation

public:
	// OLE drag/drop support

	//@cmember
	// Start drag&drop operation
	GRID_API virtual BOOL DndStartDragDrop(ROWCOL nRow, ROWCOL nCol);

	// Attributes - Options
	DWORD   m_nDndFlags;                // Data source options (Copy headers, Clipboard formats)
	DWORD   m_dwDndDropTargetFlags;     // Drop target options (AutoScroll, Drop on header)

#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)
public:
	//@cmember
	// Enable support for data source
	GRID_API BOOL EnableOleDataSource(DWORD dwFlags = GX_DNDTEXT|GX_DNDSTYLES|GX_DNDCOMPOSE|GX_DNDDIFFRANGEDLG);
	GRID_API void EnableOleDropTarget(DWORD dwFlags = GX_DNDEGDESCROLL|GX_DNDAUTOSCROLL|GX_DNDTEXT|GX_DNDSTYLES);

	// overridables for OLE dnd
	// overridable for data source
	//@cmember
	// OnDndCacheGlobalData handler.
	GRID_API virtual BOOL OnDndCacheGlobalData(CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt);

	// overridables for drop target
	//@cmember
	// OnDndCalculateFocusRect handler.
	GRID_API virtual BOOL OnDndCalculateFocusRect(CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt);
	//@cmember
	// OnDndQueryAcceptData handler.
	GRID_API virtual BOOL OnDndQueryAcceptData(CGXNoOleDataObjectProxy* pDataObject);
	//@cmember
	// OnDndDropData handler.
	GRID_API virtual BOOL OnDndDropData(CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol);

	// support for drop target, functions called from CGXGridDropTarget
	//@cmember
	// OnGridDragEnter handler.
	GRID_API virtual DROPEFFECT OnGridDragEnter(CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	//@cmember
	// OnGridDragOver handler.
	GRID_API virtual DROPEFFECT OnGridDragOver(CGXNoOleDataObjectProxy* pDataObject,	DWORD dwKeyState, CPoint point);
	//@cmember
	// OnGridDragLeave handler.
	GRID_API virtual void OnGridDragLeave();
	//@cmember
	// OnGridDrop handler.
	GRID_API virtual BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	//@cmember
	// OnGriDropEx handler.
	GRID_API virtual DROPEFFECT OnGridDropEx(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	//@cmember
	// OnGridDragScroll handler.
	GRID_API virtual DROPEFFECT OnGridDragScroll(DWORD dwKeyState, CPoint point);

	// helpers for drop target
	//@cmember
	// Dnd draw move rect.
	GRID_API virtual void DndDrawMoveRect(CPoint point, BOOL bEraseOld, BOOL bDrawNew);
	//@cmember
	// Do drag scroll.
	GRID_API BOOL DoDragScroll(CPoint point);
	//@cmember
	// Is over another application?
	GRID_API BOOL IsOverAnotherApplication(POINT point);

	// Attributes - Data Source Proxy

	// Attributes - Focus Rectangle
	ROWCOL m_nDndLastRow,
		   m_nDndLastCol;
	BOOL   m_bDndDrawn;
	CRect  m_DndLastRect;
	ROWCOL m_nDndRowExt,
		   m_nDndColExt;                // No of rows/cols to be dropped

	// Attributes - Auto scrolling
	int  m_nDndScrollInset;             // margin for inset scrolling regions
	UINT m_nDndScrollDelay;             // delay for starting inset scrolling
	UINT m_nDndScrollInterval;          // interval for auto scrolling
	UINT m_nDndOutOfWndDelay;           // delay for starting out of window scrolling
	UINT m_nDndOufOfWndHorzScrollBy,    // factor for no of rows/cols to scroll
		 m_nDndOufOfWndVertScrollBy;

	BOOL m_bDndGlobalTimer;             // TRUE for out of window scrolling

	UINT  m_nDndLastScrollCode;
	BOOL  m_bDndLastScrollCode2;
	DWORD m_dwDndLastTick;
	UINT  m_nDndNextTicks;
	CGXGridDropTarget* m_pRegDropTarget;

	DROPEFFECT m_nDndDropeffect;        // last drop effect

	// static attributes for general information
	GRID_API static BOOL     m_bDndGridSource;   // TRUE if CGXGridCore is a data source
	GRID_API static ROWCOL   m_nDndRowsCopied;   // No of rows copied in OnDndCacheGlobalData
	GRID_API static ROWCOL	 m_nDndColsCopied;   // No of cols copied in OnDndCacheGlobalData
#endif

	
#if _MFC_VER >= 0x0400
public:
	//@cmember
	// Support for tooltips on cells
	GRID_API BOOL EnableGridToolTips(BOOL b = TRUE);
#if _MFC_VER >= 0x0600
	//@cmember
	// Tooltip set delay time.
	GRID_API void ToolTipSetDelayTime(UINT nDelay);
	//@cmember
	// Tooltip set delay time.
	GRID_API void ToolTipSetDelayTime(DWORD dwDuration, int iTime);
	//@cmember
	// Support of multiline tooltips can be turned on by calling this method
	GRID_API void ToolTipSetMaxTipWidth(int iWidth);
#endif//_MFC_VER >= 0x0600
	
protected:
	CGXNoToolTipCtrlProxy* m_pTooltipProxy;
	friend class CGXToolTipCtrlProxy;
	BOOL m_bTtnIsEnabled;               // TRUE if tooltips are enabled


#endif

	// Support for IntelliMouse 
public:
	CObList m_pluginList;
	//@cmember
	// Add plugin. 
	GRID_API void AddPlugin(CGXPluginComponent* pPlugin);

	// Call EnableFormulaEngine before CGXGridCore::OnGridInitialUpdate
	// to enable formula support
protected:
	CRuntimeClass* m_pDefaultDataClass;  // default: CGXData

public:
	//@cmember
	// Enable formula engine.
	GRID_API void EnableFormulaEngine();  // assign CGXFormulaSheet to m_pDefaultDataClass
	//@cmember
	// Get sheet context.
	GRID_API CGXFormulaSheet* GetSheetContext();  // shortcut to get a pointer to CGXFormulaSheet

public:
	//@cmember
	// Get update flag.
	GRID_API virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);  // is update flag set
	//@cmember
	// Set update flag.
	GRID_API virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);  // set update flag (TRUE if cell shall be updated later)
	//@cmember
	// Add recalc range.
	GRID_API virtual void AddRecalcRange(const CGXRange& range);
	//@cmember
	// Refresh views. 
	GRID_API virtual BOOL RefreshViews(BOOL bRecalc = TRUE, CString* pErrorStr = NULL, BOOL bCreateHint = TRUE); // loop through visible cells and redraw cells with update flag
	//@cmember
	// Recalculate.
	GRID_API virtual void Recalc(BOOL bForceRecalc = FALSE);
	//@cmember
	// Reset error.
	GRID_API virtual void ResetError();
	//@cmember
	// Get error.
	GRID_API virtual BOOL GetError(CString& strError);

	// void CGXGridCore::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	// --- add m_nHintRefreshViews

protected:
	BOOL m_bRefreshOnlyUpdatedCells;  // RefreshViews will set this TRUE if only marked cells should be redrawn
	BOOL m_bLockAddRecalcRange;
	int m_nExpressionValueType;

// Menu commands
public:
	//@cmember
	// Copy.
	GRID_API virtual BOOL Copy();
	//@cmember
	// Paste.
	GRID_API virtual BOOL Paste();
	//@cmember
	// Cut.
	GRID_API virtual BOOL Cut();
	//@cmember
	// Clear.
	GRID_API virtual BOOL Clear(BOOL bStyleOrValue = TRUE);

	//@cmember
	// Can copy?
	GRID_API virtual BOOL CanCopy();
	//@cmember
	// Can cut?
	GRID_API virtual BOOL CanCut();
	//@cmember
	// Can paste?
	GRID_API virtual BOOL CanPaste();
	//@cmember
	// Can clear?
	GRID_API virtual BOOL CanClear();

	//@cmember
	// Freeze columns.
	GRID_API virtual void FreezeCols();
	//@cmember
	// Can Freeze columns.
	GRID_API virtual BOOL CanFreezeCols();
	//@cmember
	// Unfreeze columns.
	GRID_API virtual void UnfreezeCols();
	//@cmember
	// Can unfreeze columns?
	GRID_API virtual BOOL CanUnfreezeCols();
	//@cmember
	// Freeze rows.
	GRID_API virtual void FreezeRows();
	//@cmember
	// Can freeze rows?
	GRID_API virtual BOOL CanFreezeRows();
	//@cmember
	// Unfreeze rows.
	GRID_API virtual void UnfreezeRows();
	//@cmember
	// Can unfreeze rows?
	GRID_API virtual BOOL CanUnfreezeRows();

// Drawing of cells
public:
	//@cmember
	// Redraw row/col.
	GRID_API virtual void RedrawRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Redraw.
	GRID_API virtual void Redraw(UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Redraw row/col.
	GRID_API void RedrawRowCol(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	//@cmember
	// Redraw row/col.
	GRID_API void RedrawRowCol(const CGXRange& range, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);

	//@cmember
	// Subtract borders.
	GRID_API virtual CRect SubtractBorders(const CRect& rect, const CGXStyle& style, BOOL bSubtrLines = TRUE);
	//@cmember
	// Add borders.
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);

	//@cmember
	// Lock update.
	GRID_API BOOL LockUpdate(BOOL b = TRUE);
	//@cmember
	// Is lock update?
	GRID_API BOOL IsLockUpdate();

	// CGXGridCore Printing support
	//@cmember
	// OnAdjustPrintRectangle handler.
	GRID_API virtual void OnAdjustPrintRectangle(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	// OnPrintHeaderAndFooter handler.
	GRID_API virtual void OnPrintHeaderAndFooter(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	// OnGridBeginPrinting handler.
	GRID_API virtual void OnGridBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	// OnGridEndPrinting handler.
	GRID_API virtual void OnGridEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	// OnGridPrint handler.
	GRID_API virtual void OnGridPrint(CDC* pDC, CPrintInfo* pInfo);

	// Grid Dimension
	//@cmember
	// OnTestGridDimension handler.
	GRID_API virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);

protected:
	//@cmember
	// OnGridDraw handler.
	GRID_API virtual void OnGridDraw(CDC* pDC);  // called by OnPaint
	//@cmember
	// Prepare device context attributes.
	GRID_API virtual void PrepareDCAttribs(CDC* pDC); // gets called on all CDCs before the grid draws into it.
	//@cmember
	// OnDrawItem handler.
	GRID_API virtual void OnDrawItem(CDC *pDC, ROWCOL nRow, ROWCOL nCol, const CRect& rectDraw, const CGXStyle& style);
	//@cmember
	// Mark edit.
	GRID_API virtual void MarkEdit(ROWCOL nEditRow, ROWCOL nEditCol, UINT direction = 0, UINT flags = GX_UPDATENOW);
	//@cmember
	// OnDrawTopLeftBottomRight handler.
	GRID_API virtual void OnDrawTopLeftBottomRight(ROWCOL topRow, ROWCOL leftCol, ROWCOL bottomRow, ROWCOL rightCol, CDC* pDC);

	// implementation specific->
protected:
	int m_nNestedDraw;

	struct GRID_API DrawStruct
	{
		DrawStruct();
		~DrawStruct();

		unsigned    nRows,
					nCols;

		ROWCOL      gridTopRow,
					gridLeftCol,
					gridFrozenCols,
					gridFrozenRows,
					gridHeaderCols,
					gridHeaderRows;

		CRect       rectEdit,
					rectItem;

		int         nxMin,
					nyMin;
		int         nxMax,
					nyMax;

		int*        anHeights;
		int*        anWidths;
		int*        anYOffset;
		int*        anXOffset;
		ROWCOL*     anRows;
		ROWCOL*     anCols;
		LPCSTYLE*   apStyles;
		WORD*       abBits;

		CGXControl* pCurrentControl;

		BOOL        bAnyCellCovered;
		BOOL        bAnyCellSelected;
		BOOL        bColor;
		COLORREF    rgbStandard;

		ROWCOL      topRow,
					leftCol,
					bottomRow,
					rightCol;

		CDC*        pDC;

		CRect       rectClip;
		CGXBrush    brTemp1, brTemp2;
	};

	// Stack for nested redraw
	class GRID_API CDrawStack : public CTypedPtrList<CPtrList, DrawStruct*>
	{
	public:
		//@cmember
		// Add element to top of stack
		void Push(DrawStruct* newDraw)
			{AddHead(newDraw);}
		//@cmember
		// Peek at top element of stack
		DrawStruct* Peek()
			{return IsEmpty() ? NULL : GetHead();}
		//@cmember
		// Pop top element off stack
		DrawStruct* Pop()
			{return RemoveHead();}
	};

	DrawStruct* m_pDrawStruct;
	CDrawStack m_StackOldDraw;
	CGXBrush m_tempBrush;
	BOOL m_bInvertRect;
	BOOL m_bForceOldDrawing;

	//@cmember
	// Evaluate float merge cell.
	GRID_API void OnDrawTLBR_EvalFloatMergeCell(DrawStruct& ds);
	//@cmember
	// Load cell.
	GRID_API void OnDrawTLBR_LoadCell(DrawStruct& ds, unsigned nRow, unsigned nCol);
	//@cmember
	// Draw background.
	GRID_API void OnDrawTLBR_DrawBackground(DrawStruct &ds, unsigned nRow);
	//@cmember
	// Draw background.
	GRID_API void OnDrawTLBR_DrawBackground(DrawStruct &ds);
	//@cmember
	// Draw cell.
	GRID_API void OnDrawTLBR_DrawCell(DrawStruct& ds, unsigned nRow, unsigned nCol);
	//@cmember
	// Draw vertical borders.
	GRID_API void OnDrawTLBR_DrawVertBorders(DrawStruct& ds, unsigned nCol);
	//@cmember
	// Draw horizontal borders.
	GRID_API void OnDrawTLBR_DrawHorzBorders(DrawStruct& ds, unsigned nRow);
	//@cmember
	// Invert cells.
	GRID_API void OnDrawTLBR_InvertCells(DrawStruct& ds);
	//@cmember
	// Invert cells.
	GRID_API void OnDrawTLBR_InvertCells(DrawStruct& ds, unsigned nRow);

	//@cmember
	// Draw invert cell.
	GRID_API virtual void DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem);
	//@cmember
	// Draw grid line.
	GRID_API virtual void DrawGridLine(CDC* pDC,int x,int y,int dx,int dy, int type, ROWCOL nClientRC, UINT flags = 0);
	//@cmember
	// Draw grid line.
	GRID_API void DrawGridLine(CDC* pDC, int type, ROWCOL nClientRC, UINT flags = 0);
	//@cmember
	// OnDrawBorders handler.
	GRID_API void OnDrawBorders(CDC *pDC, CRect rectItem, const CGXStyle& style);

public:
	//@cmember
	// Draw border.
	GRID_API void DrawBorder(const CGXPen& pen, const CRect& rect, GXBorderType bt, CDC* pDC, const CGXBrush* pbrInterior = NULL);
	//@cmember
	// Draw brush rect.
	GRID_API void DrawBrushRect(CDC* pDC, const CRect& rect, const CGXBrush& brush);

public:
	//@cmember
	// Set drawing technique.
	GRID_API GXDrawingTechnique SetDrawingTechnique(GXDrawingTechnique t);
	GRID_API GXDrawingTechnique GetDrawingTechnique(); // QA: 28154

protected:
	GXDrawingTechnique m_nDrawingTechnique;

	//@cmember
	// Draw using memDC.
	GRID_API void DrawUsingMemDC(CDC* pDC);
	//@cmember
	// Draw direct to DC.
	GRID_API void DrawDirectToDC(CDC* pDC);

	BOOL m_bDrawCoveredCell; // flag for CGXControl::DrawBackground
	BOOL m_bForceDrawBackground; // flag for CGXControl::DrawBackground

// GDI-Objects, Cache operations
public:
	//@cmember
	// Lookup or create font.
	GRID_API CFont*  LookupOrCreateFont(const CGXFont& font);
	//@cmember
	// Lookup or create brush.
	GRID_API CBrush* LookupOrCreateBrush(const CGXBrush& brush);
	//@cmember
	// Lookup or create pen.
	GRID_API CPen*   LookupOrCreatePen(const CGXPen& pen);
	//@cmember
	// Get grid DC.
	GRID_API CDC*    GetGridDC();
	//@cmember
	// Release grid DC.
	GRID_API void    ReleaseGridDC(); // QA: 31753, Added GRID_API
	//@cmember
	// Load font.
	GRID_API CFont*  LoadFont(CDC* pDC, const CGXFont& font);
	//@cmember
	// Load font.
	GRID_API virtual CFont*  LoadFont(CDC* pDC, const CGXStyle& style, const CGXStyle* pStandardStyle = NULL);

protected:
	//@cmember
	// Free object cache.
	GRID_API virtual void FreeObjectCache();
	//@cmember
	// Get font metrics.
	GRID_API virtual void GetFontMetrics(CDC* pDC, int& dxWidth, int& dyHeight);

protected:
	//@cmember
	// Get default font size.
	GRID_API void GetDefaultFontSize(int &dxWidth, int &dyHeight);

	// Object cache for drawing
	CGXMapByte8ToPtr	m_mapFontHandles;
	CGXMapByte8ToPtr	m_mapBrushHandles;
	CGXMapByte8ToPtr    m_mapPenHandles;
	CGXMapCellToOb      m_mapStyles;

	CMapWordToOb        m_mapAltStyles;
	void**              m_papAltStyles;
	ROWCOL              m_nAltStylesTopRow,
						m_nAltStylesLeftCol;
	CPtrList            m_listAltStyles;
	unsigned            m_nAltStylesRows,
						m_nAltStylesCols,
						m_nAltStylesColOffs,
						m_nAltStylesRowOffs,
						m_nAltStylesCount;
	CDC*                m_pGridDC;
	HFONT               m_hOldFont;

#ifdef _CCHIT
	CGXCollMapDWordToLong     m_mapCellHit;
#endif

	CGXStyle*           m_pStyleColHeader;
	CGXStyle*           m_pStyleRowHeader;
	CGXStyle*           m_pStyleStandard;

	CGXStyle*           m_pStyleEdit;

	CFont               m_fontEdit;
	CBrush              m_brushEdit;
	CPen                m_penEdit;
	CFont               m_fontCombo;

	int                 m_nZoom;

	BOOL                m_bLockGDIObjects;    // avoid emptying GDI-objects-cache
	BOOL                m_bLockStyleEdit;     // don't reload edit cell
	ROWCOL              m_nLockRow;
	ROWCOL              m_nLockCol;
	ROWCOL              m_nLockRow2;
	ROWCOL              m_nLockCol2;

	// Excluded clipping regions for BitmapDC drawing
	CPtrList            m_listExcludeClipRect;
	BOOL				m_bLastFocus;

/////////////////////////////////////////////////////////////////////////////
// Implementation

public:
	//@cmember
	// Is active frame?
	GRID_API BOOL IsActiveFrame();
	//@cmember
	// Lock resize.
	GRID_API void LockResize(BOOL bState);

// Calculations
	// Mouse Actions
	//@cmember
	// Show context cursor.
	GRID_API virtual void ShowContextCursor(CPoint& point);
	//@cmember
	// Show context cursor.
	GRID_API virtual void ShowContextCursor(UINT idcPrimary, LPCTSTR idcSecondary);
	//@cmember
	// Set grid cursor.
	GRID_API virtual void SetGridCursor(UINT idcCursor);

protected:
	//@cmember
	// Reset grid.
	GRID_API void ResetGrid();

	//@cmember
	// Get rows and cols from Points
	// CalcClientRowColFromPt checks if nRow, nCol != GX_INVALID
	GRID_API BOOL   CalcClientRowColFromPt(CPoint& pt, ROWCOL* nRow, ROWCOL* nCol, CRect* rect = NULL );
	//@cmember
	// CalcValidClientRowColFromPt: if pt is Invalid --> nRow = GetRowCount, nCol = GetColCount
	GRID_API void   CalcValidClientRowColFromPt(CPoint& pt, ROWCOL* nRow, ROWCOL* nCol);

	//@cmember
	// Get coordinates rectangle from row, col
	GRID_API int CalcLeftFromClientCol(ROWCOL nCol);
	GRID_API int CalcTopFromClientRow(ROWCOL nRow);

	//@cmember
	// Get rectangle from row, col
	GRID_API CRect CalcRectFromClientRowCol(ROWCOL nClientRow, ROWCOL nClientCol);
	GRID_API CRect CalcNextRectFromClientRowCol(ROWCOL nClientRow, ROWCOL nClientCol);
	GRID_API CRect CalcClientRectRightFromCol(ROWCOL nCol);
	GRID_API CRect CalcClientRectBottomFromRow(ROWCOL nRow);

public:
	// Current view
	ROWCOL  m_nEditRow,                  // row id for current cell
			m_nEditCol,                  // column id for current cell
			m_nTopRow,                   // top row
			m_nLeftCol,                  // left column
			m_nVScrollFactor,            // scrolling factor (if more than 32768 rows, it is > 1)
			m_nHScrollFactor;            // scrolling factor (if more than 32768 columns, it is > 1)

	CGXControl* m_pCurrentCellControl;

	BOOL    m_bVertScrollBar,
			m_bHorzScrollBar;

	BOOL    m_bActiveFrame,              // FrameWnd is activ
			m_bActiveEditCell;           // current cell is activ

	BOOL	m_bDoScrollNoUpdateWindow;	// Set this TRUE if DoScroll should not call UpdateWindow

public:
	BOOL    m_bDropDownCell;
	BOOL    m_bIgnoreFocus;              // ignore incoming KillFocus/SetFocus messages

	void    SetIgnoreFocus(BOOL b);
	void    SetDropDownCell(BOOL b);

protected:
	// Font
	int     m_dyHeight,                  // Font - height
			m_dxWidth;                   // Font - avg. width

	int     m_psSelDragLine;             // pen for "dragging columns/rows"
	CGXDragLineWnd* m_pWndDrag;

	UINT    m_idcCursor;                 // default Cursor

	// Parameter
	CGXGridParam*
			m_pParam;
	BOOL    m_bOwnParam;                 // is parameter-object life-time bound?

	// internal status
	BOOL    m_bInitDone,                 // TRUE if OnInitialUpdate has been called
			m_bAutoScroll,               // Autoscroll
			m_bDisplayHeaderRow,         // display row headers
			m_bDisplayHeaderCol;         // display column headers

	BOOL	m_bAutoScrollStart,			 // will be checked by autoscroll plugin component
			m_bAutoScrollVert,
			m_bAutoScrollHorz,
			m_bAutoScrollStop,
			m_bSpeedKey,
			m_bAccelArrowKey,
			m_bAccelScrollbars;
	
	int		m_nAutoScrollDirection;

	SEC_UINT	m_nAutoScrollTimer;

	UINT	m_nSpeedKeyChar,
			m_nSpeedKeyFlags;

	// Print / Print Preview
	BOOL    m_bPrintInProgress;          // Semaphor is TRUE when grid is printing
	CRect   m_rectPrint;                 // Return value for GetGridRect() when printing
	BOOL	m_bPrintCurSelOnly;			 // TRUE if "Selected Range" is set in prinf dialog
	ROWCOL  m_nPrintTopRow,              // Return value for GetTopRow() when printing
			m_nPrintLeftCol;             // Return value for GetLeftCol() when printing
	int    m_dyPrintHeight,             // Return value for GetFontHeight() when printing
			m_dxPrintWidth;              // Return value for GetFontWidth() when printing
	BOOL	m_bPrintPaintMsg;
	CRowColArray
			m_awPageFirstRow,            // Page breaks (rows)
			m_awPageFirstCol;            // Page breaks (columns)
	int     m_nCurrentPageRowIndex,      // Currently printed page (index for m_awPageFirstRow)
			m_nCurrentPageColIndex;      // Currently printed page (index for m_awPageFirstCol)

	BOOL    m_bUpdateScrollbar;          // Semaphor to avoid recursive call of UpdateScrollbars()

protected:

	// Dragging rows/columnns
	ROWCOL
			m_nSelDragRow,               // currently selected col/row which shall be dragged
			m_nSelDragCol;               //

	POSITION
			m_SelRectId;

	CGXRange
			m_rangeCurSel;

	ROWCOL  m_dwLastMoveRow,
			m_dwLastMoveCol,             // holds the last row/col of the cell where the mouse was dragged
			m_dwButtonDownRow,
			m_dwButtonDownCol;           // holds the row/col where the mouse was clicked

	// Grid Rectangle (see SetGridRect())
	CRect   m_rectDisplay;
	BOOL    m_bRectDisplay;

	// system settings
	int     m_dxFrame,                   // SM_CXFRAME
			m_dyFrame,                   // SM_CYFRAME
			m_dxBorder,                  // SM_CXBORDER
			m_dyBorder;                  // SM_CYBORDER

	HCURSOR m_hcurArrow;                 // handle for arrow cursor

	// This are only temporary Rectangles, (No scrolling!!!)
	CRect   m_rectTrack,                 // tracking
			m_rectBoundTrack,
			m_rectInvertBar,
			m_rectRC;

	CPoint  m_ptAutoPos;

	ROWCOL  m_RCnRowClient,
			m_RCnColClient;

	ROWCOL  m_nLastVisibleCol,           // Last Visible Row and Column:
			m_nLastVisibleRow;
	BOOL    m_bLastColVisible,
			m_bLastRowVisible;
	ROWCOL  m_nLastVisibleLeftCol,       // if values differ from m_nRopRow/m_nLeftRow
			m_nLastVisibleTopRow;        // m_nLastVisibleCol must be recalculated

	// Mouse actions
	BOOL
			m_bTracking,                 // TRUE if user is tracking row height/column width
			m_bCellHit,                  // TRUE if user is selecting cells
			m_bSelDrag;                  // TRUE if user is dragging rows/cols


	BOOL    m_bTrackMove,
			m_bTrackSmoothHeader,
			m_bTrackSmoothCells,
			m_bTrackMarkLine,
			m_bTrackInvertLine,
			m_bTrackPressedHeader;

	CSize   m_sizeTrackStart;

	WORD    m_nHitState;
	UINT    m_nMouseFlags;
	ROWCOL  m_nHitRow,
			m_nHitCol;
	int     m_nHitChar;
	BOOL    m_bHitCellScope,
			m_bHitMoved,
			m_bEditBtnHit;

	int     m_nTrackingMode,             // either GX_TRACKHEIGHT or GX_TRACKWIDTH
			m_nSelDragMode;              // either GX_SELDRAG_COL or GX_SELDRAG_ROW

	ROWCOL  m_nRowTracking,              // row index for tracking row height
			m_nColTracking;              // column index for tracking column width

	// smarter resizing: old window coordinates (see DoSize and DoShowWindow)
	int     m_cxOld,
			m_cyOld;
	CRect   m_rectWnd;
	BOOL    m_bLockResize;               // Needed for smart resizing
	BOOL    m_bZoomed;

	// support for eat first mouse click
	CWnd*   m_pWndLastFocus;

	// support for IME/DBCS
	BOOL    m_bDoubleByteChar;
	TCHAR   m_nDoubleByteLeadChar;

	// map with more objects that can be linked into grid object
	CMapPtrToPtr m_mapGridLocalData;

/////////////////////////////////////////////////////////////////////////////
// typically CView member functions
public:

protected:
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Translated message map functions
protected:
	//@cmember
	// Do set cursor.
	GRID_API virtual BOOL DoSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//@cmember
	// Do vertical scroll.
	GRID_API virtual BOOL DoVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//@cmember
	// Do horizontal scroll.
	GRID_API virtual BOOL DoHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//@cmember
	// Do size.
	GRID_API virtual BOOL DoSize(UINT nType, int cx, int cy);
	//@cmember
	// Do mouse move.
	GRID_API virtual BOOL DoMouseMove(UINT flags, CPoint point);
	//@cmember
	// Do show window.
	GRID_API virtual BOOL DoShowWindow(BOOL bShow, UINT nStatus);
	//@cmember
	// Do left button double click.
	GRID_API virtual BOOL DoLButtonDblClk(UINT flags, CPoint point);
	//@cmember
	// Do left button down.
	GRID_API virtual BOOL DoLButtonDown(UINT flags, CPoint point);
	//@cmember
	// Do left button up.
	GRID_API virtual BOOL DoLButtonUp(UINT flags, CPoint point);
	//@cmember
	// Do middle button double click.
	GRID_API virtual BOOL DoMButtonDblClk(UINT flags, CPoint point);
	//@cmember
	// Do middle button down.
	GRID_API virtual BOOL DoMButtonDown(UINT flags, CPoint point);
	//@cmember
	// Do middle button up.
	GRID_API virtual BOOL DoMButtonUp(UINT flags, CPoint point);
	//@cmember
	// Do right button double click.
	GRID_API virtual BOOL DoRButtonDblClk(UINT flags, CPoint point);
	//@cmember
	// Do right button down.
	GRID_API virtual BOOL DoRButtonDown(UINT flags, CPoint point);
	//@cmember
	// Do right button up.
	GRID_API virtual BOOL DoRButtonUp(UINT flags, CPoint point);
	//@cmember
	// Do control color.
	GRID_API virtual HBRUSH DoCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//@cmember
	// Do notify destroy.
	GRID_API virtual BOOL DoNotifyDestroy();
	//@cmember
	// Do cancel mode.
	GRID_API virtual BOOL DoCancelMode();
	//@cmember
	// Do mouse activate.
	GRID_API virtual BOOL DoMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);
	//@cmember
	// Do command.
	GRID_API virtual BOOL DoCommand(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnGriWinIniChange handler.
	GRID_API virtual void OnGridWinIniChange(LPCTSTR lpszSection);
	//@cmember
	// OnGridSysColorChange handler.
	GRID_API virtual void OnGridSysColorChange();
	//@cmember
	// Do get dialog code.
	GRID_API virtual UINT DoGetDlgCode(UINT uiDefaultVal);
	//@cmember
	// Do get scroll bar control.
	GRID_API virtual CScrollBar* DoGetScrollBarCtrl(int nBar) const;

	// Focus
	//@cmember
	// OnGridKillFocus handler.
	GRID_API virtual void OnGridKillFocus(CWnd* pNewWnd);
	//@cmember
	// OnGridSetFocus handler.
	GRID_API virtual void OnGridSetFocus(CWnd* pOldWnd);
	//@cmember
	// PreTranslateMessage handler.
	GRID_API virtual BOOL OnGridPreTranslateMessage(MSG* pMsg);
	//@cmember
	// WindowProc handler.
	GRID_API virtual BOOL OnGridWindowProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& result);
	//@cmember
	// Timer handler.
	GRID_API virtual void OnGridTimer(SEC_UINT nIDEvent);

	//@cmember
	// Keyboard events for both child windows and grid window before
	// they are processed. This virtuals are called from PreTranslateMessage.
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

// CWnd functions used in CGXGridCore
protected:
	//@cmember
	// Invalidate rect.
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	//@cmember
	// Invalidate.
	GRID_API void Invalidate(BOOL bErase = TRUE);
	//@cmember
	// Update window.
	GRID_API void UpdateWindow();
	//@cmember
	// Scroll window ex.
	GRID_API int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	//@cmember
	// Get device context.
	GRID_API CDC* GetDC();
	//@cmember
	// Release device context.
	GRID_API int ReleaseDC(CDC* pDC);
	//@cmember
	// Get client rect.
	GRID_API void GetClientRect(LPRECT lpRect);
	//@cmember
	// Show scroll bar.
	GRID_API virtual void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	//@cmember
	// Set capture.
	GRID_API CWnd* SetCapture();
	//@cmember
	// Get capture.
	GRID_API CWnd* GetCapture();
	//@cmember
	// Screen to client.
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	//@cmember
	// Screen to client.
	GRID_API void ScreenToClient(LPRECT lpRect);
	//@cmember
	// OnMouseMove handler.
	GRID_API void OnMouseMove(UINT flags, CPoint pt);
	//@cmember
	// Open clipboard.
	GRID_API BOOL OpenClipboard();

	friend class CGXControl;
	friend class CGXBlockCmd;
	friend class CGXODBCGrid;
	friend class CGXGridHandleView;
	friend class CGXGridHandleWnd;
	friend class CGXGridDropTarget;
	friend class CGXDragLineWnd;
	friend class CGXAutoScrollPlugin;
	friend class CGXPageBreakPlugin; 
	friend static BOOL AFXAPI _doButtonDown1(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	friend static BOOL AFXAPI _doButtonDown(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags);
	friend static BOOL AFXAPI _doButtonUp(CGXGridCore* pGrid, UINT flags, CPoint point, int& ht, ROWCOL& nRow, ROWCOL& nCol, WORD& w);
};


// Grid local data

#define GX_GRID_LOCAL(class_name, ident_name) \
	class_name* ident_name(CGXGridCore* pGrid) { \
			void* voidptr; \
			class_name* pData; \
			if (!pGrid->m_mapGridLocalData.Lookup(this, pData)) \
				pGrid->m_mapGridLocalData.SetAt(this, pData = new class_name); \
			return pData; \
		} \

#define GX_EXTERN_GRID_LOCAL(class_name, ident_name) \
	extern class_name* ident_name;

/////////////////////////////////////////////////////////////////////////////
// CGXGridHint

// identifier

typedef enum
{
	gxFirstHint,
	gxHintRedraw,
	gxHintRedrawRowCol,
	gxHintUpdateChangedRowCount,
	gxHintUpdateChangedColCount,
	gxHintUpdateChangedRowHeights,
	gxHintUpdateChangedColWidths,
	gxHintUpdateInsertCols,
	gxHintUpdateInsertRows,
	gxHintUpdateRemoveCols,
	gxHintUpdateRemoveRows,
	gxHintUpdateMoveCols,
	gxHintUpdateMoveRows,
	gxHintPrepareChangeSelection,
	gxHintPrepareClearSelection,
	gxHintUpdateFrozenRows,
	gxHintUpdateFrozenCols,
	gxHintUpdateStyleRange,
	gxHintUpdateCoveredCellsRowCol,
	gxHintUpdateZoom,
	gxHintStoreZoom,
	gxHintUpdateReadOnly,
	gxHintChangedTab,
	gxHintUpdateSelectRange,
	gxHintTransferCurrentCell,
	gxHintSetTopRow,
	gxHintSetLeftCol,
	gxHintSyncCurrentCell,
	gxHintUpdateFloatedCellsRowCol,
	gxHintUpdateMergedCellsRowCol,
	gxHintLockSelectionFrame,
	gxHintMoveDataRows,
	gxHintMoveDataCols,
	gxHintUpdateProperties,
	gxHintUpdateStylesMap,
	gxHintUpdateBaseStyle,
	gxHintRefreshViews,
	gxLastHint
} GXHINTID;

// CGXGridHint class

class CGXGridHint : public CObject
{
	GRID_DECLARE_DYNAMIC(CGXGridHint)
public:
	//@cmember
	// CGXGridHint constructor.
	GRID_API CGXGridHint(UINT id, int viewID = -1);

// Attributes
public:
	UINT    m_id;

	CGXRange range;
	const CGXStyle* pStyle;
	GXModifyType mt;
	ROWCOL      nRow1, nRow2, nRow3;
	ROWCOL      nCol1, nCol2, nCol3;
	LONG    lParam;
	DWORD   dwParam;
	void*   vptr;
	UINT    flags;
	int     nViewID;

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

};

// Excel-like selction frame

class CGXLockSelectionFrame
{
public:
	//@cmember
	// CGXLockSelectionFrame constructor.
	GRID_API CGXLockSelectionFrame(CGXGridCore* pGrid);
	//@cmember
	// CGXLockSelectionFrame destructor.
	GRID_API ~CGXLockSelectionFrame();

	BOOL m_bLock;
	CGXGridCore* m_pGrid;
};

// Unlock read-only cells

class CGXGridUnlockReadOnly
{
public:
	BOOL m_bLock;
	CGXGridParam* m_pParam;
	//@cmember
	// CGXGridUnlockReadOnly constructor.
	CGXGridUnlockReadOnly(CGXGridParam* pParam) { m_pParam = pParam; m_bLock = pParam->IsLockReadOnly(); pParam->SetLockReadOnly(FALSE); }
	//@cmember
	// CGXGridUnlockReadOnly destructor.
	GRID_API ~CGXGridUnlockReadOnly() { m_pParam->SetLockReadOnly(m_bLock); }
	//@cmember
	// Lock read only.
	GRID_API void LockReadOnly(BOOL bLock = TRUE) { m_pParam->SetLockReadOnly(bLock); }
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxcore.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXCORE_H_

