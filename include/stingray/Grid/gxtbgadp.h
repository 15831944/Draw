///////////////////////////////////////////////////////////////////////////////
// gxtbgadp.h
//

#ifndef _GX_TB_GRD_ADAPT_H__
#define _GX_TB_GRD_ADAPT_H__

// #include <StingrayExportDefs.h>

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


// Begin CGXTabWndMgr implementation

class CGXGridTabWndAdapter : public CGXTabWndAdapter 
{
public:
	GRID_API CGXGridTabWndAdapter();

	GRID_API virtual ~CGXGridTabWndAdapter();

// interface that will be used by CGXTabWndMgr
	
// access
	// this will be called by CGXTabWndMgr to pass in the parent for the window
	// you can use this to create a window (as a child) or to simply render
	GRID_API virtual void SetParentWnd(CWnd* pParentWnd);
	
	// return the parent window passed in.
	GRID_API virtual CWnd* GetParentWnd() const;
	
	// return the correct tab count
	GRID_API virtual int GetTabCount() const;
	
	GRID_API virtual int GetCursel() const;

	inline CGXTabWnd* GetTabWnd() const {return m_pTabWnd;}

// view creation
	// view creation interface
	GRID_API virtual CWnd* CreateView(CRuntimeClass* pViewRuntimeClass, const TCHAR* pszLabel, CCreateContext* pContextDefault);

	//tab window creation interface
	GRID_API virtual BOOL Create(const TCHAR* pszLabel, CCreateContext* pCreateContext);
	
	// return a meaningful default label
	GRID_API virtual CString GenerateLabel(UINT nID = 0);
	
	GRID_API virtual BOOL InsertWorkSheet(int nInsertBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel = 0, UINT nID = 0);
	
	GRID_API virtual BOOL DeleteWorksheet(int nDeleteIndex);

	GRID_API virtual BOOL CanInsertWorkSheet() const;
	
	GRID_API virtual BOOL CanDeleteWorkSheet() const;
	
	
// maintenance	
	// perform clean up as appropriate. Do a 'delete this' if this object was allocated on the heap
	GRID_API virtual void Destroy();
	
protected:
	//data
	CGXTabWnd*	m_pTabWnd;
	CWnd*		m_pParentWnd;

// static members
	GRID_API static CWnd* SpecialTabWndCreate(CGXTabWnd* pTabWnd, CRuntimeClass* pViewClass,  BOOL& bSendInitialUpdate,  CCreateContext* pContext, LPCTSTR szLabel = NULL, UINT nID = 0);
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

#endif //_GX_TB_GRD_ADAPT_H__
