///////////////////////////////////////////////////////////////////////////////
// gxapatr.h
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

#ifndef _GX_AP_ATR_H__
#define _GX_AP_ATR_H__

#include <afxtempl.h>
#include "gxman.h"

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

// #include <StingrayExportDefs.h>

// forward decl for CGXTabWndMgr

class CGXTabWndMgr;

// Your application class will inherit from this class or a class derived from this class. This class
// establishes the following essential links

// 1) The link between the frame that is used and the tab manager that is to be used. The relationship
// betwen the two can be established by overidding GetTabManager. This will return (by default) an instance
// of CGXTabWndMgr

// 2) The link betwen view, doc classes and the document template that is to be used for managing them. This relationship
// is established by the GetDoctemplate override. This function always needs to be overriden either in your application
// class or in your derived CGXAppAdapter class

//@doc
//@class
//@rem
//The CGXAppAdapter class is used as the base class by the global application 
//object in any project that implements tab persistence.<nl>
//<nl>
//Your application class will inherit from this class or a class derived from this class. 
//This class establishes the following essential links<nl>
//<nl>
//1) The link between the frame that is used and the tab manager that is to be used. 
//The relationship betwen the two can be established by overidding GetTabManager. 
//This will return (by default) an instance of CGXTabWndMgr<nl>
//2) The link betwen view, doc classes and the document template that is to be used for 
//managing them. This relationship is established by the GetDoctemplate override. 
//This function always needs to be overriden either in your application class or in your 
//derived CGXAppAdapter class<nl>
class CGXAppAdapter
{
public:

// constructors / destructor
	//@access Construction
	//@cmember 
	//Constructs an instance of the CGXAppAdapter class.
	GRID_API CGXAppAdapter();
	GRID_API virtual ~CGXAppAdapter();

// access
	//@access Operations
	//@cmember
	//Returns a tab manager that is appropriate for the frame and document instance passed in
	GRID_API virtual CGXTabWndMgr* GetTabManager(CRuntimeClass* pRClass, CDocument* pDocument);
	//@cmember
	//Removes the tab manager that is associated with the frame and document instance.
	GRID_API virtual void RemoveTabManager(CRuntimeClass* pRClass, CDocument* pDocument);
	//@cmember
	//Returns an appropriate document template based on the view and document runtime class.
	GRID_API virtual CDocTemplate* GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass) = 0;
	//@cmember
	//Returns an appropriate document template based on the view and document runtime class.
	GRID_API virtual CDocTemplate* GetDocTemplate(CCreateContext* pContext);
	//@cmember
	//This function will be called to create an instance of the Tab Window holder.
	//The node manager class performs 
	//simply duties such as object instantiation and garbage collection.
	GRID_API virtual CGXNodeManager<CGXTabWndMgr>* CreateTabWndHolder();

// implementation
protected:
	CGXNodeManager<CGXTabWndMgr>* m_pTabWndHolder;
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
#endif 
