///////////////////////////////////////////////////////////////////////////////
// gxdoc.h
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

#ifndef _GX_DOC_H__
#define _GX_DOC_H__

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


// All documents that are used by workbook classes should be derived from CGXDocument. The actual serialization code should be 
// copied over to WorkBookSerialize. Change the existing Serialize handler to simply call the base class (or remove the handler
// itself) 
class CGXTabWndMgr;
class CGXDocument :public CDocument
{
	GRID_DECLARE_SERIAL(CGXDocument)

// constructors / destructor
	GRID_API CGXDocument();
	GRID_API virtual ~CGXDocument();

//overrides
	GRID_API virtual void WorkBookSerialize(CArchive& ar);
	
	GRID_API virtual void Serialize(CArchive& ar);
	
	GRID_API virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);

	GRID_API virtual BOOL SaveModified(); // return TRUE if ok to continue
	
//access
	GRID_API void SetPrimaryDocument(CGXDocument* pDoc) ;
	GRID_API CGXDocument* GetPrimaryDocument() const;
	GRID_API CGXTabWndMgr* GetTabManager();

protected:

	//data
	CGXDocument* m_pDocument;
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
#endif //_GX_DOC_H__
