///////////////////////////////////////////////////////////////////////////////
// gxhgfr.h : Implementation for Find/Replace in a Hierarchy Grid.
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

#ifndef GX_HGFRIMP_H
#define GX_HGFRIMP_H

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

#include <StingrayExportDefs.h>

class CGXGridFindReplaceImp: public CGXAbstractGridFindReplaceImp
{
	CGXGridCore* m_pGrid;
public:
	GRID_API virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly);
	GRID_API virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	GRID_API virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell);
	GRID_API virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	GRID_API virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	GRID_API virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog);
	GRID_API virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
	GRID_API virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
	GRID_API virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
};

class CGXHierarchyGridFindReplaceImp : public CGXGridFindReplaceImp
{
public:
	//GRID_API virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly);
	//GRID_API virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	GRID_API virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell);
	GRID_API virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	GRID_API virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	GRID_API virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog);
	GRID_API virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
	//GRID_API virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
	//GRID_API virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	GRID_API virtual BOOL FindTextInChild(CGXGridCore* pGrid, ROWCOL nChildRow, BOOL bSetCell, BOOL bSetParent);
	GRID_API virtual void ReplaceAllInChild(CGXGridCore* pGrid, ROWCOL nChildRow, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // GX_HGFRIMP_H
