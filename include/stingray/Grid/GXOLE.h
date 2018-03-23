///////////////////////////////////////////////////////////////////////////////
// GXOLE.h
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//

#ifndef _GXOLE_H_
#define _GXOLE_H_

//#if ! ( defined(_GX_VER) && _GX_VER >= 0x01000)
//#pragma message( "Please make sure that you include Objective Grid 10.00 header files")
//#pragma message( "or a later version and not an older version header files!")
//Fatal error!
//#endif

// compile this file only if OLE is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

// include decls for base class

#ifndef _GXABSTR_H_
#include "gxabstr.h"
#endif

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

#ifndef _AFXOLE_H_
#include <afxole.h>
#endif

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file


// CGXGridDropTarget
//
// A CGXGridDropTarget object provides the communication mechanism between
// a grid (either CView or CWnd) and the OLE libraries. Creating an object
// of this class allows a window to accept data through the OLE drag-and-drop
// mechanism.
//

class CGXGridDropTarget : public COleDropTarget
{
// Constructors
public:
	GRID_API CGXGridDropTarget();

// Operations
	GRID_API BOOL Register(CGXGridCore* pGrid, DWORD dwFlags = GX_DNDEGDESCROLL|GX_DNDAUTOSCROLL|GX_DNDTEXT|GX_DNDSTYLES);

// Overridables
	GRID_API virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	GRID_API virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	GRID_API virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropEffect, CPoint point);
	GRID_API virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	GRID_API virtual void OnDragLeave(CWnd* pWnd);
	GRID_API virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState,
		CPoint point);

// Implementation
public:
	GRID_API virtual ~CGXGridDropTarget();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGXGridCore* m_pGrid;
};

// CGXOleDataObjectProxy
//
// CGXOleDataObjectProxy will be instantiated from the CGXGridDropTarget
// class and will forward calls to the embedded COleDataObject
//
// See gxcore.h for declararation of the abstract
// CGXNoOleDataObjectProxy base class.

class CGXOleDataObjectProxy: public CGXNoOleDataObjectProxy
{
public:
	GRID_API CGXOleDataObjectProxy(COleDataObject* pDataObject = NULL, BOOL bAutoDelete = FALSE);

	GRID_API virtual ~CGXOleDataObjectProxy();

	GRID_API virtual BOOL GetData(CLIPFORMAT cfFormat, LPSTGMEDIUM lpStgMedium,
		LPFORMATETC lpFormatEtc = NULL);

	GRID_API virtual BOOL IsDataAvailable(CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc = NULL);

	GRID_API COleDataObject* GetOleDataObject() const;

protected:
	COleDataObject* m_pDataObject;
	BOOL m_bAutoDelete;
};

class CGXGridDropTargetPlugin: public CGXPluginComponent, public CGXAbstractGridDropTargetImp
{
	GRID_DECLARE_DYNAMIC(CGXGridDropTargetPlugin);

public:
	GRID_API CGXGridDropTargetPlugin(CGXGridCore* pGrid);
	GRID_API virtual ~CGXGridDropTargetPlugin();
	GRID_API virtual BOOL PlugIn(CWnd* pParentWnd);

public:
	// GridCore overrides
	// overridables for drop target
	GRID_API virtual BOOL OnDndCalculateFocusRect(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt);
	GRID_API virtual BOOL OnDndQueryAcceptData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject);
	GRID_API virtual BOOL OnDndDropData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol);

	// support for drop target, functions called from CGXGridDropTarget
	GRID_API virtual DROPEFFECT OnGridDragEnter(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	GRID_API virtual DROPEFFECT OnGridDragOver(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	GRID_API virtual void OnGridDragLeave(CGXGridCore* pGrid);
	GRID_API virtual BOOL OnGridDrop(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	GRID_API virtual DROPEFFECT OnGridDropEx(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	GRID_API virtual DROPEFFECT OnGridDragScroll(CGXGridCore* pGrid, DWORD dwKeyState, CPoint point);

	// helpers for drop target
	GRID_API virtual void DndDrawMoveRect(CGXGridCore* pGrid, CPoint point, BOOL bEraseOld, BOOL bDrawNew);
	GRID_API virtual BOOL DoDragScroll(CGXGridCore* pGrid, CPoint point);
	GRID_API virtual BOOL IsOverAnotherApplication(CGXGridCore* pGrid, POINT point);

	// Attributes
	CGXGridCore* m_pGrid;
	CGXGridDropTarget* m_pobjDndDropTarget;

// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridDropTargetPlugin)
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnDestroy();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXOleDataSourceProxy
//

class CGXOleDataSourceProxy: public CGXNoOleDataSourceProxy
{
public:
	GRID_API CGXOleDataSourceProxy(COleDataSource* pDataSource = NULL, BOOL bAutoDelete = FALSE);

	GRID_API virtual ~CGXOleDataSourceProxy();

	// CacheData & DelayRenderData operations similar to ::SetClipboardData
	GRID_API virtual void CacheGlobalData(CLIPFORMAT cfFormat, HGLOBAL hGlobal,
		LPFORMATETC lpFormatEtc = NULL);    // for HGLOBAL based data

	// Clipboard and Drag/Drop access
	GRID_API virtual DROPEFFECT DoDragDrop(
		DWORD dwEffects = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK,
		LPCRECT lpRectStartDrag = NULL,
		COleDropSource* pDropSource = NULL);

	GRID_API virtual void Empty();   // empty cache (similar to ::EmptyClipboard)

	GRID_API COleDataSource* GetOleDataSource() const;

	// CGXGridCore Overridables
	GRID_API virtual BOOL DndStartDragDrop(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void DndStartDragDropMove(CGXGridCore* pGrid, 	CGXRangeList &selList);
	GRID_API virtual BOOL OnDndCacheGlobalData(CGXGridCore* pGrid, CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt);

protected:
	COleDataSource* m_pDataSource;
	BOOL m_bAutoDelete;
};

/////////////////////////////////////////////////////////////////////////////


//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA

#endif

//

#endif // _GXOLE_H_
