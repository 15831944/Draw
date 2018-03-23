///////////////////////////////////////////////////////////////////////////////
// gxtbadpt.h
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


#ifndef _GX_TAB_ADAPT_H__
#define _GX_TAB_ADAPT_H__

// #include <StingrayExportDefs.h>

// Adapter class for CGXTabWnd. If you have a different tab window you can derive from the abstract
// CGXTabWndAdapter class and implement your own adapter

class CGXTabWndAdapter
{
public:
	inline CGXTabWndAdapter() {};
	inline virtual ~CGXTabWndAdapter(){};
	
// interface that will be used by CGXTabWndMgr
	
// access
	// this will be called by CGXTabWndMgr to pass in the parent for the window
	// you can use this to create a window (as a child) or to simply render
	virtual void SetParentWnd(CWnd* pParentWnd) = 0;
	
	// return the parent window passed in.
	virtual CWnd* GetParentWnd() const = 0;

	// return the correct tab count
	virtual int GetTabCount() const = 0;

	// return the current selection
	virtual int GetCursel() const = 0;

// view creation
	// view creation interface
	virtual CWnd* CreateView(CRuntimeClass* pViewRuntimeClass,const TCHAR* pszLabel, CCreateContext* pContextDefault) = 0;
	
	//tab window creation interface
	virtual BOOL Create(const TCHAR* pszLabel, CCreateContext* pCreateContext) = 0;
	
// Worksheet
	virtual BOOL InsertWorkSheet(int nInsertBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel = 0, UINT nID = 0) = 0;
	virtual BOOL DeleteWorksheet(int nDeleteIndex) = 0;
	virtual BOOL CanInsertWorkSheet() const = 0;
	virtual BOOL CanDeleteWorkSheet() const = 0;
	
// maintenance	
	// perform clean up as appropriate. Do a 'delete this' if this object was allocated on the heap
	virtual void Destroy() = 0;
};


#endif //_GX_TAB_ADAPT_H__
