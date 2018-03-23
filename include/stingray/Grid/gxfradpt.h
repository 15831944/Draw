///////////////////////////////////////////////////////////////////////////////
// gxfradpt.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_FRAME_ADPT_H__
#define _GX_FRAME_ADPT_H__

#include "gxapatr.h"
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

class CGXTabCreateInfo;

class CGXFrameAdapter
{
public:
// constructor/destructor
	GRID_API CGXFrameAdapter();
	GRID_API virtual ~CGXFrameAdapter();

// Attributes	
	CRuntimeClass* m_pDefViewClass;
	CRuntimeClass* m_pDefDocClass;
// Operations
public:

// overrideables
	GRID_API virtual LRESULT InitNewHandler(WPARAM ui = 0, LPARAM l = 0);
	GRID_API virtual LRESULT InitFromFileHandler(WPARAM ui = 0, LPARAM l = 0);
	
	GRID_API virtual void InsertWorkSheetHandler();
	GRID_API virtual void DeleteWorkSheetHandler();
	
	GRID_API virtual BOOL CanDeleteWorkSheetHandler();
	GRID_API virtual BOOL CanInsertWorkSheetHandler();

	// will make a copy of the create context
	GRID_API virtual BOOL HandleOnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// override this function to supply actual insert information
	GRID_API virtual void OnChangeInsertInfo(int& nInsertBefore, CGXTabCreateInfo*& pTabCreateInfo, UINT& nID);

	// override this function if you want to make any changes to the generated tab create information
	GRID_API virtual void OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pTabCreateInfo);

//access
	GRID_API void SetDocRuntimeClass(CRuntimeClass* pRClass);
	
	GRID_API void SetViewRuntimeClass(CRuntimeClass* pRClass);
	
	GRID_API void SetNumberOfTabs(int nTabs);
	
	GRID_API int GetNumberOfTabs() const;
	
	GRID_API CGXAppAdapter* GetApplicationAdapter() const;	

	GRID_API virtual CGXTabCreateInfo* GetTabCreateInfo();
	
	GRID_API virtual void CanFreeTabCreateInfo();

	GRID_API virtual void GetInsertInfo(int nInsertBefore, CGXTabCreateInfo* pTabCreateInfo, UINT& nID);

	GRID_API virtual CGXTabWndMgr* GetTabManager() const;

	GRID_API void SetWindow(CWnd* pWnd);

	GRID_API CWnd* GetWindow() const;

protected:
//data members
	CGXTabCreateInfo*	m_pTabCreateInfo;
	CCreateContext*		m_pContext;
	int					m_nSize;
	CWnd*				m_pWndPointer;
};

class CGXMDIFrameAdapter : public CGXFrameAdapter
{
public:
	GRID_API CGXMDIFrameAdapter();
	GRID_API virtual ~CGXMDIFrameAdapter();

//overrideables
	GRID_API virtual void HandleOnNewWindow();
	GRID_API virtual void HandleDestroy();
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

#endif //_GX_FRAME_ADPT_H__
