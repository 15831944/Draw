///////////////////////////////////////////////////////////////////////////////
// gxdcadpt.h
//

#ifndef _GX_DCADPT_H__
#define _GX_DCADPT_H__

#ifndef _GX_EX_OLE_H__
#include "gxexole.h"
#endif

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


// forward decl
class CGXExcelReader;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXNodeManagerAr
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple creation and garbage collection support
// uses CRuntimeClass

template <class T>
class CGXNodeManagerAr
{
	
	class __t : public T
	{
		friend class CGXNodeManagerAr;
	 public:
		 inline __t(DWORD index)
		 {m_dwIndexUsed = index; };
		 
		 inline virtual ~__t()
		 {};

	 protected:
		 DWORD m_dwIndexUsed;
	};


public:
	CGXNodeManagerAr(CRuntimeClass* pRuntimeClass);
	virtual ~CGXNodeManagerAr();

	virtual T* CreateObject(int dw);
	virtual T* CreateAndInsertObject(int dw);

	void RemoveObject(int dw);
	
	CArray<T*, T*&>& GetMap()
	{return m_pMpT;};

//implementation
protected:
	CArray<T*, T*&> m_pMpT;
	
// clean up
	void CleanObjects();
	CRuntimeClass* m_pRuntimeClass;
};


template <class T>
CGXNodeManagerAr<T>::CGXNodeManagerAr(CRuntimeClass* pRuntimeClass)
{
	m_pRuntimeClass = pRuntimeClass;
}

template <class T>
CGXNodeManagerAr<T>::~CGXNodeManagerAr()
{
	CleanObjects();
}

template <class T>
T* CGXNodeManagerAr<T>::CreateObject(int dw)
{
	//T* pObject = NULL;
	if(GetMap().GetUpperBound() < dw || GetMap()[dw] == NULL)
	{
		T* p = (T*) m_pRuntimeClass->CreateObject();

		ASSERT(p != NULL);
		
		GetMap().SetAtGrow(dw, p);
		return p;
	}
	else
	{
		return (GetMap())[dw];
	}	
}
	
template <class T>
T* CGXNodeManagerAr<T>::CreateAndInsertObject(int dw)
{
	if(GetMap()[dw] == NULL)
		return CreateObject(dw);
	
	T* p = NULL;
	GetMap().InsertAt(dw, p);
		
	return CreateObject(dw);
}

// This will remove the object from the internal map and delete it
template <class T>
void CGXNodeManagerAr<T>::RemoveObject(int dw)
{
	//DWORD dwKey = dw;
	T* pObject = NULL;
	
	ASSERT( dw <= GetMap().GetUpperBound());
	
	pObject = GetMap()[dw];

	GetMap().RemoveAt(dw);

	if (pObject != NULL)
		delete pObject;
}

// clean up
template <class T>
void CGXNodeManagerAr<T>::CleanObjects()
{
	// iterate through the list and call delete
	CArray<T*, T*&>& arr = GetMap();

	TRACE1("The number of objects in CGXNodeManagerAr is: %i\n", arr.GetSize());

	int nBound = (int)arr.GetUpperBound();
	
	T* pObject = NULL;

	for (int index(0); index <= nBound; index++)
	{	
		pObject = arr[index];
	
		if(pObject != NULL)
			delete pObject;
	}	

	arr.RemoveAll();
}

typedef CGXNodeManagerAr<CGXGridParam> CGXParamManager;

#ifndef _UNICODE

/////////////////////////////////////////////////////////
// CGXExcelDocAdapter ///////////////////////////////////
/////////////////////////////////////////////////////////

class CGXExcelDocAdapter
{
public:
	// construction
	GRID_API CGXExcelDocAdapter();
	GRID_API virtual ~CGXExcelDocAdapter();

	// Operations
	GRID_API void ImplementExcelReadWrite();
	
	GRID_API virtual void InitializeParam(UINT index, UINT nIndexPrim);
	
	GRID_API virtual void ReadExcelData();

	GRID_API virtual void UpdateTabCount();

	//serialization helpers
	GRID_API virtual void ExcelSerializeImpl(CArchive& ar, BOOL bReadAll = FALSE);
	GRID_API virtual void ExcelWorkBookSerializeImpl(CArchive& ar);

	//access
	// will return a CGXGridParam based on the index value passed in
	GRID_API virtual CGXGridParam* GetParam(UINT index);
	// will return a CGXGridCore pointer based on the index passed in
	GRID_API virtual CGXGridCore* GetGrid(UINT index);
	// Will return the index based on the CObject pointer that is passed in
	GRID_API virtual int GetIndex(const CObject* pObject);
	
	// will return the parent document that is derived from this document adapter
	GRID_API virtual CGXDocument* GetParentDoc();
	// will retun the associated CGXTabWnd
	GRID_API virtual CGXTabWnd* GetTabWnd();
	// will return the document adapter that corresponds to the primary 
	GRID_API virtual CGXExcelDocAdapter* GetParentDocAdapter();

	// whether the write mode is set to Excel output
	GRID_API BOOL GetWriteAsExcel() const;
	// set the write mode
	GRID_API void SetWriteAsExcel(BOOL b);

	// when reading the file this checks to see if this is an Excel file
	// This uses a rather simplistic check. You can override and handle for other checks
	// You have to override and handle if you use a different extension than xls
	GRID_API virtual BOOL IsExcelFile(const TCHAR* lpszFileName) const;

	// returns a pointer to the Excel Reader
	GRID_API virtual CGXExcelReader* GetExcelReader() const;
	GRID_API virtual CGXExcelReader* GetExcelReaderA();
	
	// return the param manager. This object manages parameter objects based on the index
	// of the tab
	GRID_API virtual CGXParamManager* GetParamManager();
	
	// return the number of tabs hosted
	GRID_API UINT GetTabCount() const;
	
	// will be called from OnInitialUpdate to check whether it is possible to perform
	// initialization or wait.
	GRID_API void SetWaitMode(BOOL bWaitMode);
	GRID_API BOOL GetWaitMode();

	// the path of the underlying file
	GRID_API void SetFilePath(LPCTSTR pszFilePath);
	GRID_API const CString& GetFilePath() const;

protected:
	// data
	// actual reader
	CGXExcelReader* m_pExcelReader;	
	
	// Write as Excel or as grid data?
	BOOL m_bWriteAsExcel;

	// wait mode is used for proper initialization
	BOOL m_bWaitMode;
	
	// the number of tabs
	UINT m_nTabCount;

	// file path
	CString m_strFilePath;

	// document read mode
	BOOL m_bDocReadMode;

	// shared data
	CGXProperties* m_pProperties;
	CGXStylesMap* m_pStylesMap;
	CGXPrintDevice* m_pPrintDevice;

	// non shared data
	// some node manager for CGXGridParam data. This will depend on the number of worksheets
	CGXParamManager*  m_pParamManager;
	
	// impl
	GRID_API virtual void AllocSharedComponents();
	GRID_API virtual void SetSharedComponents(UINT index, UINT nIndexPrim);
};

/////////////////////////////////////////////////////////////////////////
// class GRID_API CGXExcelWndDocAdapter //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Used for single tab read/write

class CGXExcelWndDocAdapter : public CGXExcelDocAdapter
{
public:
	// construction
	GRID_API CGXExcelWndDocAdapter();
	GRID_API virtual ~CGXExcelWndDocAdapter();

	// Operations
	GRID_API virtual void InitializeParam(UINT index);
	
	GRID_API void ReadExcelFile(const CString& strFileName, UINT index = 0);
	GRID_API void SaveExcelFile(const CString& strFileName);

	//serialization helpers
	GRID_API virtual void ExcelSerializeImpl(CArchive& ar, BOOL bReadAll = FALSE);
	GRID_API virtual void ExcelWorkBookSerializeImpl(CArchive& ar);

	//access
	// will return a CGXGridParam based on the index value passed in
	GRID_API virtual CGXGridParam* GetParam(UINT index);
	GRID_API virtual CGXGridCore* GetGrid(UINT index);
	GRID_API virtual int GetIndex(const CObject* pObject);

	GRID_API virtual CGXDocument* GetParentDoc();
	GRID_API virtual CGXTabWnd* GetTabWnd();
	GRID_API virtual CGXExcelDocAdapter* GetParentDocAdapter();

	GRID_API void SetGrid(CGXGridCore* pCore);
	
protected:
	// data
	CGXGridCore* m_pCore;
};

////////////////////////////////////////////////////////////////////
// class GRID_API CGXExcelClipHandler ///////////////////////////////////////
////////////////////////////////////////////////////////////////////
// Used for BIFF clipboard handling
class CGXExcelClipHandler
{
public:
	GRID_API CGXExcelClipHandler(BOOL bFormula = FALSE);
	GRID_API ~CGXExcelClipHandler();

	GRID_API virtual BOOL Copy(CGXGridCore* pCore, const CGXRange& rg);
	GRID_API virtual BOOL Paste(CGXGridCore* pCore, const CGXRange& rg);
	
	GRID_API virtual BOOL CanCopy(CGXGridCore* pCore);
	GRID_API virtual BOOL CanPaste(CGXGridCore* pCore);
	
	GRID_API virtual CGXGridWnd* GetGridWnd();
	GRID_API void DestroyGridWnd();
	GRID_API void ResetGridWnd();
	
protected:
	UINT m_uiData;
	// used internally for easier clipboard access
	CGXGridWnd  m_gridWnd;
	
	// When used with formula grids
	BOOL m_bFormula;
};


#endif // _UNICODE

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

#endif //_GX_DCADPT_H__
