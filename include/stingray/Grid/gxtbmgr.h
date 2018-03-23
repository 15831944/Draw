///////////////////////////////////////////////////////////////////////////////
// gxtbmgr.h

#ifndef _GX_TB_MGR_H__
#define _GX_TB_MGR_H__

#include "gxdoc.h"
#include "gxman.h"
#include "gxtbadpt.h"
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

// CRuntimeClass::Load slightly modified
class CGXRuntimeClassOp
{
public:
	GRID_API static CRuntimeClass* PASCAL Load(CArchive& ar);
	GRID_API static void Store(CRuntimeClass* pRClass, CArchive& ar);
};

enum gxContextGen
{
	gxGenFromDefault,
	gxGenFromIndex,
	gxGenUseIntact,
};

// this will be passed in to create the actual views as tab children
class CGXTabCreateInfo : public CObject
{
	GRID_DECLARE_SERIAL(CGXTabCreateInfo)

public:
// constructors / destructors
	GRID_API CGXTabCreateInfo();
	
	GRID_API CGXTabCreateInfo(CCreateContext* pContext, gxContextGen gen = gxGenFromDefault,
		CDocTemplate* pDocTemplate = NULL, const TCHAR* pszLabel = NULL, BOOL bUseContextIntact = FALSE);
	
	GRID_API CGXTabCreateInfo(CGXTabCreateInfo& info);
	
	GRID_API virtual ~CGXTabCreateInfo();
	
// operations
	GRID_API void Initialize(CCreateContext* pContext, gxContextGen gen = gxGenFromDefault,
		CDocTemplate* pDocTemplate = NULL, const TCHAR* pszLabel = NULL, BOOL bUseContextIntact = FALSE);

// overrides 
	GRID_API virtual void Serialize(CArchive& ar);
	
// access
	GRID_API CRuntimeClass* GetViewRuntimeClass() const;
	GRID_API void SetViewRuntimeClass(CRuntimeClass* pRuntimeClass);

	GRID_API CRuntimeClass* GetDocRuntimeClass() const;
	GRID_API void SetDocRuntimeClass(CRuntimeClass* pRuntimeClass);

	GRID_API CCreateContext* GetCreateContext();
	GRID_API void SetCreateContext(const CCreateContext* pContext);

	GRID_API BOOL GetUseContextIntact() const;
	GRID_API void SetUseContextIntact(BOOL bContext);

	GRID_API CString GetLabel() const;
	GRID_API void SetLabel(CString strLabel);

	GRID_API CDocTemplate* GetDocTemplate() const;
	GRID_API void SetDocTemplate(CDocTemplate* pDocTemplate);

	GRID_API CGXDocument* GetDocument() const;
	GRID_API void SetDocument(CGXDocument* pDocument);

	GRID_API gxContextGen GetContextGenMode() const;
	GRID_API void SetContextGenMode(gxContextGen gen);

	GRID_API int GetIndex();
	GRID_API void SetIndex(int index);
	
	GRID_API void SetInit(BOOL b);
	GRID_API BOOL IsInit();

//operators
	GRID_API virtual void operator=(CGXTabCreateInfo& pInfo);

// Diagnostic Support
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//data
	// the view runtime class
	CRuntimeClass* m_pViewRuntimeClass; 
	// the document runtime class
	CRuntimeClass* m_pDocRuntimeClass; 
	// the current creation context
	CCreateContext* m_pContext;
	
	// Whether the create context should be used intact.
	// a new document will not be created in this case.
	BOOL m_bUseContextIntact;
	// the label for the tab. Only minimum information for the tab appearance is
	// persisted in this variant
	CString m_strLabel;
	// the doc template to be used for document creation
	CDocTemplate* m_pDocTemplate;
	// pointer to the document used (set or created)
	CGXDocument* m_pDocument;

	// CCreateContext generation mode
	gxContextGen m_gxCGgen;

	// Init 
	BOOL m_bIsInit;
	
	int m_nIndex;
};



// two responsibilities
// 1) Create 
// 2) Serialize tabs and recreate
class CGXTabWndAdapter;

//typedef CArray<CGXTabCreateInfo*, CGXTabCreateInfo*> CGXTabCreateArray;
typedef std::vector<CGXTabCreateInfo*> CGXTabCreateArray;

class CGXTabWndMgr : public CObject
{
	GRID_DECLARE_SERIAL(CGXTabWndMgr)
public:
	
// constructors / destructors
	GRID_API CGXTabWndMgr();
	
	GRID_API CGXTabWndMgr(CWnd* pTabParent);
	
	GRID_API virtual ~CGXTabWndMgr();

// operations
	
	// create tabs initially
	GRID_API virtual BOOL CreateTabs(CGXTabCreateInfo* pTabCreateInfo, int nTabs = 0, TCHAR* pszFileName = NULL, CGXTabWndAdapter* pTabAdapter = NULL);
	
	//use to Create supplementary tabs
	GRID_API virtual BOOL CreateSupTabs(CGXTabCreateInfo* pTabCreateInfo, CMDIChildWnd* pChildWnd, int nTabs = 0, TCHAR* pszFileName = NULL );
	
	//use to remove supplementary tabs
	GRID_API virtual void RemoveSupTab(CMDIChildWnd* pChildWnd);

	GRID_API virtual CGXNodeManagerNor<CGXTabWndAdapter>* CreateSupTabHolder();

	GRID_API virtual BOOL InsertWorkSheet(int nInsertBefore, CGXTabCreateInfo* pTabCreateInfo, UINT nID = 0);

	GRID_API virtual BOOL DeleteWorkSheet(int nDeleteIndex);

	GRID_API virtual BOOL CanInsertWorkSheet() const;
	
	GRID_API virtual BOOL CanDeleteWorkSheet() const;

	GRID_API virtual BOOL GenerateCreateContext(CGXTabCreateInfo* pTabCreateInfo);

	GRID_API void UpdateTabCount();

	//access
	
	// sets the primary CCreateContext for all view creation
	GRID_API void SetPrimaryContext(CCreateContext* pContext);
	
	// intialize with a parent window
	GRID_API void SetParent(CWnd* pParentWnd);

	GRID_API void SetPrimaryTabCreateInfo(CGXTabCreateInfo* pTabCreateInfo, BOOL bDeleteTabInfo = FALSE);
	
	GRID_API CGXTabCreateInfo* GetPrimaryTabCreateInfo();

	GRID_API int GetPrimaryIndex();
	
	// GRID_API CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* GetTabCreateInfoArray();
	GRID_API std::vector<CGXTabCreateInfo*>* GetTabCreateInfoArray();

	GRID_API int GetTabCount();

	GRID_API int GetCursel() const;

	GRID_API CGXNodeManagerNor<CGXTabWndAdapter>& GetSupTabWndHolder();

// overrides / overrideables
	
	//serialization code
	GRID_API virtual void Serialize(CArchive& ar);
	
	GRID_API virtual void Cleanup();
	
	GRID_API virtual void OnInitialize();

	GRID_API virtual CGXTabWndAdapter* GetTabWndAdapter() const;
	
	GRID_API virtual void SetTabWndAdapter(CGXTabWndAdapter* pAdapter, BOOL bOwn = FALSE);

	GRID_API virtual BOOL IsModified();
	
	GRID_API virtual void SetModify(BOOL bModify);

	GRID_API virtual void SetPrimaryModified(BOOL b);

	// serialization helpers
	GRID_API virtual BOOL ReadDocumentsFromArchive(CArchive& ar, CGXDocument* pDocThis, int nIndex = 0);
	
	GRID_API virtual BOOL StoreDocumentsInArchive(CArchive& ar);

// implementation
protected:
	
	GRID_API BOOL IterateAndSaveDocuments(CArchive& ar) const;
	
	GRID_API BOOL IterateAndLoadDocuments(CArchive& ar, CGXDocument* pDocThis, int nIndex = 0);
	
protected:
	// whether we own the tab window adapter. Owned adapters will be deleted by us.
	BOOL m_bOwn;
	// array of CGXTabCreateInfo structures
	// CArray<CGXTabCreateInfo*, CGXTabCreateInfo*> m_ArrTabCreateInfo;
	std::vector<CGXTabCreateInfo*> m_ArrTabCreateInfo;

	// tab count
	int m_nTabCount;
	// Tab Window adapter
	CGXTabWndAdapter* m_pTabWndAdapter;
	// map to hold the supplementary tabs
	CGXNodeManagerNor<CGXTabWndAdapter>* m_pSupTabHolder;
	// pointer to the primary document
	CGXTabCreateInfo* m_pPrimaryTabCreateInfo;
	// Whether we should delete the stored tab info
	BOOL m_bDeleteTabInfo;

private:
	// the index of the primary tab
	int m_nPrimaryIndex;
	
	// Never call this unless you know exactly what changes will be needed
	GRID_API void SetPrimaryIndex(int nIndex);
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

#endif //_GX_TB_MGR_H__
