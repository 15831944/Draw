///////////////////////////////////////////////////////////////////////////////
// gxexbse.h
//


#ifndef _GX_EX_EX_BASE_H__
#define _GX_EX_EX_BASE_H__

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _UNICODE 

class CGXExcelGrid
{

public:
	// Construction
	GRID_API CGXExcelGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);
	GRID_API virtual ~CGXExcelGrid();

	// operations
	GRID_API virtual BOOL OnPasteFromClipboardImpl(const CGXRange& rg);
	GRID_API virtual BOOL OnCheckClipboardFormatImpl();
	GRID_API virtual BOOL CopyRangeImpl(const CGXRangeList& selList);
	
	GRID_API virtual BOOL IsFormulaMode();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// implemented with typecasting
	GRID_API virtual CGXGridCore* GetCorePtr();

};

#endif 

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

//

#endif //_GX_EX_EX_BASE_H__
