///////////////////////////////////////////////////////////////////////////////
// GXBROWSE.h
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
//
// Author: Stefan Hoenig
//

#ifndef _GXBROWSE_H_
#define _GXBROWSE_H_

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

// GRID_DECLARE_REGISTER

#ifndef _GXEXT_H_
#include "gxext.h"
#endif

// CGXControl

#ifndef _GXCTRL_H_
#include "gxctrl.h"
#endif

// CGXView

#ifndef _GXVIEW_H_
#include "gxview.h"
#endif

// Verify that include path is correct

//#if ! ( defined(_GX_VER) && _GX_VER >= 0x01000 )
//#pragma message( "Please make sure that you include Objective Grid 10.00 header files")
//#pragma message( "and not old header files!")
//Fatal error!
//#endif

// // #include <StingrayExportDefs.h>

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

// header file

class CGXBrowserGrid;

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseGridArrowRowHeader control

class CGXBrowseGridArrowRowHeader : public CGXControl
{
public:
	GRID_API CGXBrowseGridArrowRowHeader(CGXBrowserGrid* pODBCGrid);

	// event handler
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

// Attributes
public:
	CBitmap m_bmPencil;
	CBitmap m_bmStar;
	CBitmap m_bmArrow;
	CGXBrowserGrid* m_pBrowserGrid;
	BOOL m_bWin95Look;
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecSetInfo 

class CGXRecSetInfo : public CObject
{
	GRID_DECLARE_SERIAL(CGXRecSetInfo)

public:
	GRID_API CGXRecSetInfo();

	//serialization
	GRID_API virtual void Serialize(CArchive& ar);

// Attributes
	CString m_strSource;          // query string
	CString m_strSqlQuery;        // query string
	CString m_strConnectString;   // connect string
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseDirtyFieldStruct
//
// holds changed values for the current record


class CGXAbstractBlob;

struct CGXBrowseDirtyFieldStruct
{
	// changed fields
	BOOL bDirty;
	CString sValue;

	CGXAbstractBlob* pAttribute;

	GRID_API CGXBrowseDirtyFieldStruct();
	GRID_API ~CGXBrowseDirtyFieldStruct();
};


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXOleViewer
///////////////////////////////////////////////////////////////////////////////////////////////
// Viewer for ole objects
class CGXOleViewer
{
public:
	GRID_API CGXOleViewer();
	GRID_API virtual ~CGXOleViewer();

// overrides:
	// This can spawn an external viewer etc
	virtual void Render(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl,  BOOL bShow = TRUE) = 0;

	// Activate an existing viewer
	virtual void ActivateExisting() = 0;

	// No rendering....simple access and return
	virtual HGLOBAL AccessData(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;

	// This should close any external viewer etc
	GRID_API virtual void Close();
	
	GRID_API virtual void OnModify();

	virtual void Clear() = 0;
	
	virtual void SaveFromStorage() = 0;
	
	virtual COleVariant& GetData() = 0;
	
	virtual LPSTORAGE GetStorage() = 0;

	virtual LPOLEOBJECT GetOleObject() = 0;

	virtual IOleClientSite* GetClientSite() = 0;

// clipboard support
	
	virtual BOOL CanPaste() = 0;

	virtual COleVariant* Paste() = 0;

	virtual BOOL CanCopy() = 0;
	
	virtual IDataObject* Copy(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;
	
	virtual BOOL CanCut() = 0;
	
	virtual IDataObject* Cut(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;


//access 
	GRID_API CGXControl* GetActiveControl();
	GRID_API void SetActiveControl(CGXControl* pControl);

//data
	CGXControl* m_pControl;
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseParam
//
// holds all CGXBrowserGrid-specific data. This data can be
// shared among several CGXBrowserGrid-derived views so
// that the document/view architecture can be supported.
//

class CGXBrowseParam: public CGXGridParam
{
	GRID_DECLARE_SERIAL(CGXBrowseParam)

public:
	// Attributes
	BOOL m_bAllowPasteMultiCells;
		// Set this TRUE if you want to allow the user to paste
		// multiple lines of text into the grid. 
		// If FALSE OG will only paste into the current cell (default)

	BOOL m_bCanStoreGridCellInCGXData;
		// TRUE if any cell data can be directly stored in CGXData
		// FALSE if only headers can stored in CGXData
		// CGXDaoGrid and CGXODBCGrid initialize m_bCanStoreGridCellInCGXData = FALSE
		// The default value is TRUE.

	int  m_nMaxColWidth;            // holds the maximum col width in characters

	BOOL m_bCanAppend;              // Set this member FALSE if you want to disable appending rows

	BOOL m_bUpdateOnStore;          // TRUE when Update shall be called
	BOOL m_bDoReplaceAll;           // TRUE when OnReplaceAll is called

	BOOL m_bIsBrowseInit;           // TRUE when one-time initialization is done

	// moving columns / sorting rows
	CRowColArray
		m_awRowIndex,
		m_awColIndex;

	// Current record - internal buffer with changed values
	CGXBrowseDirtyFieldStruct* m_paDirtyFieldStruct;

	short m_nFields;                // number of fields in the bound data source (recordset)

	UINT m_nEditMode;               // current mode

	ROWCOL m_nCurrentRow;           // currently edited row

	CGXStyle* m_pTmpStyle;          // temporary style object


	// Record count
	BOOL m_bEOFSeen;                // set this member FALSE if you don't
									// know the exact record count.

	long m_nRecordLastSeen;         // Last seen record will be used to
		// determine the record count when OnGetRecordCount()
		// returns LONG_MAX

// Record count, currently only CGXDaoGrid and CGXODBCGrid use this members
	long
		m_nRecordCount,             // can be used by derived classes
		// m_nRecordCount has no meaning for this base class
		m_nRecordCountInc;          // can be used by derived classes
		// m_nRecordCount has no meaning for this base class

// Caching, currently only CGXDaoGrid takes advantage of this
	long m_nCacheSize;      // specify -1 for no caching
	ROWCOL m_nRowCacheStart;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	long
		m_lMoveRecordWaitCursor;

// Implementation
public:
	GRID_API CGXBrowseParam();
	GRID_API virtual ~CGXBrowseParam();
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXBrowseParam& operator=(const CGXBrowseParam& p);

//added for record information 
public:
	//operation
	CObject* m_pRecSetInfo;
	GRID_API CGXRecSetInfo* GetRecSetInfo();
	GRID_API void CreateRecSetInfo(CRuntimeClass* pClass = NULL);
};

/////////////////////////////////////////////////////////////////////////////
// CGXAbstractBlob
/////////////////////////////////////////////////////////////////////////////

// Has no data. Just implements a generic interface for cleanup. Data will be added
// to derived members as required

// to control the destruction of this object.


//@doc CGXAbstractBlob 
//@class GRID_API CGXAbstractBlob
// Abstract base class. 
// This class is used to identify and operate on Blob Data that needs to be stored in the Browser
// grid. The only common interface that the grid needs with such data 
// (apart from the dissimilar content specific members) is the ability 
class CGXAbstractBlob 
{
public:
	//@cmember 
	// Constructor
	GRID_API CGXAbstractBlob();
	GRID_API virtual ~CGXAbstractBlob();
	//@access overridable
	//@cmember
	// Pure virtual function. If bDestruct is TRUE, 
	// the object should destruct. If bDestruct is FALSE, 
        // the object should remain but reset data to the default values.
	virtual void Cleanup(BOOL bDestruct = FALSE) = 0;
};

//@doc CGXAbstractBlob
//@mfunc void | CGXAbstractBlob | CGXAbstractBlob |
//@rem Abstract base class. This class is used to identify 
// and operate on Blob Data that needs to be 
// stored in the Browser grid. The only common interface 
// that the grid needs with such data 
// (apart from the dissimilar content specific members) is the ability to control 
// the destruction of this object.
// @xref <c CGXAbstractBlob>
// @xref <mf CGXAbstractBlob::Cleanup>

//@doc CGXAbstractBlob
//@mfunc void  | CGXAbstractBlob | Cleanup  | 
// @parm BOOL | bDestruct | Specifies whether the object should destroy itself.
// @rem
// Pure virtual function. If bDestruct is TRUE, 
// the object should destruct. If bDestruct is FALSE, 
// the object should remain but reset data to the default values.
// @xref <c CGXAbstractBlob>
// @xref <mf CGXAbstractBlob::CGXAbstractBlob>

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid
//
// base class for browsing external data sources
//@doc
//@class
//The <c CGXBrowserGrid> encapsulates the browsing functionality used by the <c CGXDaoGrid>
//and the <c CGXODBCGrid> classes. By encapsulating all the functionality necessary for 
//browsing external data sources, you as programmer can benefit from the Objective Grid 
//browsing capabilities and derive your own class from <c CGXBrowserGrid>. This makes it 
//possible for you to create MS-Query-like browsers for self-written databases or other 
//database toolkits.<nl> 
//<nl>
//The <c CGXBrowserGrid> class maintains one current record with the current cell.  
//When the user edits data in the current record, all changes are stored in an internal buffer.
//When the user moves the current cell to another record, changes for the current record 
//are written to the data source before the current cell is positioned to a new record.  
//When the user clicks on the last row, 
//a new record will be added to the data source (if it supports appending records).<nl>
//<nl>
//The DbfBrows sample provides a sample for deriving a view from <c CGXBrowserGrid>
//and lets the user browse Dbase files.<nl>
//<nl>
//The main features of CGXBrowserGrid are: <nl>
//<nl>
//<ul>
//<li>Row headers show the state of the current record:
//an arrow marks the current record as unmodified; a pencil indicates 
//that the current record has been modified.<eli>
//<li>Provides support for adding rows to the data source. 
//When the user enters data in the last row 
//(marked with an asterisk in the row header), a new record will be appended.<eli>
//<li>The user can undo changes or cancel all pending changes in the current record.<eli>
//<li>Provides improved abstraction for loading cell data from data
//source and storing all changed cells data into the data source when the user has 
//moved to a new record.<eli>
//<li>Lets the programmer validate user input at record level. 
//This means that the user can input data into the record, and when he wants to move 
//to a new record, all changes for the previous record will be validated.<eli>
//<li>When the user opens several views on the same data, current cell changes and movements 
//will be synchronized among the views.<eli>
//<li>Provides support for rearranging columns and rows. This lets you add support for 
//dragging columns and sorting rows.<eli>
//<li>Provides support for maintaining a high-water mark for the last seen record. 
//CGXDaoGrid and CGXODBCGrid use this high-water mark so that the record count can 
//be determined while the user loops through the records.<eli>
//<eul>
//<nl>
//<c CGXBrowserGrid> is not derived from <c CWnd>. The <c CGXBrowserView> class represents the <c GXBrowserGrid>
//as view. The <c CGXBrowserWnd> class represents the <c GXBrowserGrid> as control.<nl>
//<nl>
//<c CGXBrowseParam> holds specific data for the <c CGXBrowserGrid>. It can be shared among 
//several views (works the same way as <c CGXGridParam>). You can embed it in a document if 
//you want to support several browse views on the same data, as for example in a dynamic 
//splitter window. The DbfBrows sample shows you how to embed the <c CGXBrowseParam> into 
//the document and how to add support for serializing the scheme information of the grid.<nl>
//<nl>
//Take a look at <c CGXBrowseParam>. It describes some internal attributes that let you adapt 
//the <c CGXBrowserGrid> to your specific needs. Also, cut and paste behavior can be customized 
//through <c CGXBrowseParam> attributes.
//@base public | CGXGridCore |
//@xref <c CGXBrowserGrid> <c CGXBrowseParam> <c CGXBrowserView> 
//<c CGXBrowserWnd> <c CGXDaoGrid> <c CGXODBCGrid> 
class CGXBrowserGrid: public CGXGridCore
{
public:
// Construction
	//@cmember 
	//Constructs a browser grid object.
	GRID_API CGXBrowserGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	//@cmember
	//Returns a pointer to the associated CGXBrowseParam object.
	GRID_API CGXBrowseParam* GetBrowseParam();

	enum EditMode { noMode, edit, addnew };

	// maximum col width
	//@cmember 
	//Specify the maximum column width in number of characters 
	//for text fields to be displayed in the cells. 
	//The method loops through all columns and resizes them if necessary.
	GRID_API void SetMaxColWidth(int nChar);
	//@cmember
        //Returns the maximum column width in number of characters for text fields.
	GRID_API int GetMaxColWidth();

	// records
	//@cmember
	//Returns the row number for the first record.
	GRID_API ROWCOL GetFirstRow();
	//@cmember
	//Specify if you want the user to be able to append rows to the recordset.
	GRID_API void SetCanAppend(BOOL b);

	//@cmember
	//Returns nonzero if the current record is the last row 
	//(when CanUpdate returns TRUE, the last row is the append row).
	GRID_API BOOL IsOnLastRecord();
	//@cmember
	//Returns nonzero if the current record is the first record.
	GRID_API BOOL IsOnFirstRecord();

	// Record state
	//@cmember
	// Returns nonzero if the current record has been changed, but 
	//changes are not yet written to data source. 
	GRID_API BOOL IsRecordDirty();
	//@cmember
	//Returns the zero-based row index associated with a row. Headers will return a negative value.
	GRID_API long GetRecordFromRow(ROWCOL nRow);

	// Fields
	//@cmember
	//Returns the zero-based field index associated with a column. Headers will return a negative value.
	GRID_API short GetFieldFromCol(ROWCOL nCol);

public:
	// Overridables - State members
	//@cmember
	//Called to determine if the user should be able to change data in the data source.
	GRID_API virtual BOOL CanUpdate();
	//@cmember
	// Called to determine if the user should be able to append rows to the data source. 
	GRID_API virtual BOOL CanAppend();
	//@cmember
	//This method is called to determine the number of records if the 
	//last record has been accessed. 
	//If the record count is unknown, the method should return <bold>LONG_MAX<ebold>.
	GRID_API virtual long OnGetRecordCount();

	//@cmember
	//Returns the row number for the append row.<bold>GX_INVALID<ebold> if undetermined.
	GRID_API virtual ROWCOL GetAppendRow();
	//@cmember
	//Returns the row number for the last record. 
	//If the grid allows appending records it will return the row number for the append row.
	GRID_API virtual ROWCOL GetLastRow();

	// Overridables - Operations
	//@cmember
	//Called to delete selected records. The user can select records 
	//either by clicking on the 
	//row header or programmatically by choosing the <mf SelectRange> command.
	GRID_API virtual void DeleteRecords();
	//@cmember
	//Called to delete rows from the grid. You need not select a range of rows before 
	//calling this method, because you can directly specify the range of rows to be deleted.
	GRID_API virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess = NULL);
	//@cmember
	//Called to requery the data source. The default implementation 
	//resets the high-water mark for the last seen record. 
	GRID_API virtual void Requery();
	//@cmember
	//Called to position the recordset to the given row. You should return <bold>FALSE<ebold>
	// if the positioning failed.
	GRID_API virtual BOOL MoveTo(ROWCOL nRow);

	// Wrapper methods for DeleteRows (not overridable)
	GRID_API void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API void DeleteRows(const CGXRange& range);

	// Overridables - Changing records
	//@cmember
	// Prepares for changes to the current record. Call <mf Update> to complete the edit. 
	GRID_API virtual void Edit(ROWCOL nRow);
	//@cmember 
	//Prepares the grid for adding a new record. 
	//The grid appends a new line in the grid. Call <mf Update> to complete 
	//the addition.
	GRID_API virtual ROWCOL AddNew();
	//@cmember
	//Completes an <mf AddNew> or <mf Edit> operation by saving the changed values to the data source.
	GRID_API virtual BOOL Update(CString* ps = NULL);
	//@cmember
	//Cancels all changes for the current record (by calling <mf CancelRecord>) and empties the undo and redo list.
	GRID_API virtual void UndoRecord();
	//@cmember
	//Cancels any pending changes in the current record and resets the 
	//edit- or append-mode. 
	//If an <mf AddNew> was pending, the last row is removed from the grid.
	GRID_API virtual void CancelRecord();

	// Overridables - Row/Column dereferencing
	//@cmember
	//<bold>GetRowIndex<ebold> returns the original row id for a given row. This original 
	//row id can be different from the given row when the row 
	//has been moved or the grid has been sorted. The return value is one-based.
	GRID_API virtual ROWCOL GetRowIndex(ROWCOL nRow);
	//@cmember
	//<bold>GetColIndex<ebold> returns the original column id for a given column. 
	//This original column id can be different from the given columnn 
	//when the column has been moved or the grid has been sorted. 
	//The return value is one-based.
	GRID_API virtual ROWCOL GetColIndex(ROWCOL nCol);

	// binary data support
	GRID_API virtual void GetOleViewerRowCol(ROWCOL nRow, ROWCOL nCol, DWORD dwId, CGXOleViewer*& pViewer ) const;
protected:
	// Overridables - Events
	//@cmember
	//Called from <mf Update> when a new record has been added to the data source.
	GRID_API virtual void OnAddedNewRecord();

	GRID_API virtual void OnFillCache();
	
	//@cmember
	//Overridable which initializes the default grid appearance. 
	//You should call this method from your OnInitialUpdate method.
	GRID_API virtual void InitBrowserSettings();

	// Overridables - Load cell styles and flush values
	//@cmember
	//Called to load the value from the data source or apply 
	//additional formatting at runtime. This method provides a better 
	//abstraction for loading data from data sources at record level. 
	//<bold>OnLoadCellStyle<ebold> is called from <mf GetStyleRowCol> when needed.
	GRID_API virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	//@cmember
	//<bold>OnFlushCellValue<ebold> is called from within 
	//<bold>CGXBrowserGrid::OnFlushRecord<ebold> for all values changed in the 
	//current record buffer. You should override this method to store changed 
	//values in your data source. If you cannot write the passed value to the data 
	//source, you may throw 
	//an exception and specify the text to be displayed in the grid with <mf SetWarningText>.
	GRID_API virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);
	
	//@cmember
	GRID_API virtual void OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute);
	
	//@cmember
	//This method writes dirty fields back to the data 
	//source and prepares the data source at 
	//record level before changes are written to it with <mf OnFlushCellValue>.
	GRID_API virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL);
	//@cmember
	GRID_API virtual BOOL SetBinaryFlags(const CGXStyle* pStyle, int nField);

		// NOTE: You should override the previous members instead
		// of GetStyleRowCol/StoreStyleRowCol. They provide a better
		// abstraction for loading/storing cell values in a CGXBrowserGrid

		// The methods will be called appropriately from within CGXBrowserGrid::Update(),
		// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
		// CGXBrowserGrid::SetStyleRange

	// Overridables - Sorting 
public:
	GRID_API virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	GRID_API virtual void SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

protected:
	GRID_API virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	GRID_API virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);

public:
	// called when text is pasted into cell
	GRID_API virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);

// Implementation - Menu handlers
protected:
	GRID_API BOOL OnMove(UINT nIDMoveCommand);
	GRID_API void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API void OnUpdateRecordLast(CCmdUI* pCmdUI);
	GRID_API void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	GRID_API void OnEditUndorecord();
	GRID_API void OnRecordDelete();
	GRID_API void OnUpdateRecordDelete(CCmdUI* pCmdUI);

// Implementation - CGXGridCore Overridables
public:
	GRID_API virtual void OnGridInitialUpdate();
	GRID_API virtual void OnGridDraw(CDC* pDC);
	GRID_API virtual ROWCOL GetRowCount();
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	GRID_API virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	GRID_API virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	GRID_API virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	GRID_API virtual BOOL CanChangeSelection(CGXRange* range, BOOL bIsDragging, BOOL bKey);
	GRID_API virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	GRID_API virtual BOOL Undo();
	GRID_API virtual BOOL Paste();
	GRID_API virtual BOOL Cut();
	GRID_API virtual BOOL CanCut();
	GRID_API virtual BOOL CanPaste();

	GRID_API virtual void OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	GRID_API virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);

	#if _MFC_VER >= 0x0400
	GRID_API BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	#endif

	GRID_API BOOL ClearCells(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	GRID_API virtual BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue);
	GRID_API virtual BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);

// Implementation - Rearrange the column indexes when one of the following events happen
	GRID_API virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);
	GRID_API virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	GRID_API virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);

	// Rearrange the row indexes when one of the following events happen
	GRID_API virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	GRID_API virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	GRID_API virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);

	// These special RemoveRows / RemoveCols implementations do not support undo!
	GRID_API virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	GRID_API virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	GRID_API BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);

// Implementation
protected:
	BOOL m_bUpdateDone;

	GRID_API void EmptyEditBuffer();

protected:
	GRID_API virtual ~CGXBrowserGrid();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserView view

class CGXBrowserView : public CGXView, public CGXBrowserGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXBrowserView();
	GRID_DECLARE_DYNCREATE(CGXBrowserView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXBrowserView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBrowserView)
public:
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	GRID_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	GRID_API virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	GRID_API virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	GRID_API virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	GRID_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
#ifdef _WINDU_SOURCE
 public:
#endif
	GRID_API afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndorecord();
	GRID_API afx_msg void OnRecordDelete();
	GRID_API afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	GRID_API afx_msg BOOL OnMove(UINT nIDMoveCommand);
	GRID_API afx_msg void OnView100();
	GRID_API afx_msg void OnViewZoomin();
	GRID_API afx_msg void OnViewZoomout();
	GRID_API afx_msg void OnFormatFreezecols();
	GRID_API afx_msg void OnFormatUnfreezecols();
	GRID_API afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
#ifdef _WINDU_SOURCE
 protected:
#endif
	GRID_API afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnMouseMove(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT flags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCopy();
	GRID_API afx_msg void OnEditPaste();
	GRID_API afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCut();
	GRID_API afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndo();
	GRID_API afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditRedo();
	GRID_API afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditFind();
	GRID_API afx_msg void OnEditReplace();
	GRID_API afx_msg void OnEditRepeat();
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//{{AFX_MSG(CGXBrowserView)
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXBrowserGrid
public:
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void Invalidate(BOOL bErase = TRUE);
	GRID_API void UpdateWindow();
	GRID_API int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC* GetDC();
	GRID_API int ReleaseDC(CDC* pDC);
	GRID_API void GetClientRect(LPRECT lpRect);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	GRID_API void ScreenToClient(LPRECT lpRect);
	GRID_API BOOL OpenClipboard();

// remove ambiguity between CGXBrowserGrid and CGXView
	GRID_API CString GetTabName();
	GRID_API void SetTabName(CString s);
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd window

class CGXBrowserWnd : public CWnd, public CGXBrowserGrid
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXBrowserWnd)

// Construction
public:
	GRID_API CGXBrowserWnd();
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	GRID_API void Initialize();

	// Support for tabwnds
public:
	GRID_API static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);
	GRID_API CScrollBar* GetScrollBarCtrl(int nBar) const;

// Operations
public:
	// CView Printing support
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Implementation
public:
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CGXBrowserWnd)
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API  void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	GRID_API afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndorecord();
	GRID_API afx_msg void OnRecordDelete();
	GRID_API afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	GRID_API afx_msg BOOL OnMove(UINT nIDMoveCommand);
	GRID_API afx_msg void OnView100();
	GRID_API afx_msg void OnViewZoomin();
	GRID_API afx_msg void OnViewZoomout();
	GRID_API afx_msg void OnFormatFreezecols();
	GRID_API afx_msg void OnFormatUnfreezecols();
	GRID_API afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXBrowserGrid
public:
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void Invalidate(BOOL bErase = TRUE);
	GRID_API void UpdateWindow();
	GRID_API int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC* GetDC();
	GRID_API int ReleaseDC(CDC* pDC);
	GRID_API void GetClientRect(LPRECT lpRect);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	GRID_API void ScreenToClient(LPRECT lpRect);
	GRID_API BOOL OpenClipboard();
};


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxbrowse.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXBROWSE_H_
