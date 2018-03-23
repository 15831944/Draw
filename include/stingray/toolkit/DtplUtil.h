///////////////////////////////////////////////////////////////////////////////
// DtplUtil.h : Declaration of SECDocTemplateUtils
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
// Author:       Mark Isham
// Description:  Declaration of SECDocTemplateUtils
//
// Utility class providing useful functions for examining and manipulating
// data associated with CDocTemplate and its derived classes.

#ifndef __DOCTEMPLATE_UTILS_H__
#define __DOCTEMPLATE_UTILS_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

// Header Includes
#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Constants

// Macros

// Types

typedef CTypedPtrList<CPtrList,CDocTemplate*> SECDocTemplatePtrList;

// Forward Declarations

/////////////////////////////////////////////////////////////////////////////
// SECDocTemplateUtils

class SECDocTemplateUtils
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	inline SECDocTemplateUtils() 
	{
		m_bUseDocTypeID = TRUE;
	}
	inline virtual ~SECDocTemplateUtils() {}

	// Operations
	TOOLKIT_API virtual int GetDocTemplateIndex(CDocTemplate* pDocTemplate,
										const CString& strDocType);
	TOOLKIT_API virtual CDocTemplate* GetDocTemplateAtIndex(const CString& strDocType,
										int nDocTemplateIndex);
	TOOLKIT_API virtual CDocTemplate* FindDocTemplateBestGuess(CDocument* pDoc,
								CView* pView,CFrameWnd* pFrame);
	TOOLKIT_API virtual UINT GetFrameResourceId(CFrameWnd* pFrame);

	inline BOOL IsUseDocTypeID()
	{
		return m_bUseDocTypeID;
	}

	inline void SetUseDocTypeID(BOOL bUseDocTypeID )
	{
		m_bUseDocTypeID = bUseDocTypeID;
	}

protected:


	// Implementation Member Variables

	// Internal classes to provide needed access to MFC protected data.
	class SECDocTemplateProtectedAccess : public CDocTemplate {
	public:
		TOOLKIT_API SECDocTemplateProtectedAccess();
		friend class SECDocTemplateUtils; 
	};
	class SECFrameWndProtectedAccess : public CFrameWnd {
		friend class SECDocTemplateUtils; 
	};

	// Implementation Member Functions
	TOOLKIT_API virtual BOOL BuildDocTemplateList(SECDocTemplatePtrList& listMatches);
	TOOLKIT_API virtual BOOL SearchDTByViewFrame(SECDocTemplatePtrList& listMatches,
								CView* pView,CFrameWnd* pFrame);
	TOOLKIT_API virtual BOOL SearchDTByResource(SECDocTemplatePtrList& listMatches,
								CFrameWnd* pFrame);
	TOOLKIT_API virtual BOOL SearchDTByDocument(SECDocTemplatePtrList& listMatches,
								CDocument* pDoc);
	TOOLKIT_API virtual BOOL DoReturnFromFindDTBestGuess(const SECDocTemplatePtrList& listMatches,
								CDocTemplate*& pDocTemplateMatch);

	// OT-Pro aware functions. 
	TOOLKIT_API virtual BOOL IsProDockFrame(CRuntimeClass* pFrameClass);
	TOOLKIT_API virtual CRuntimeClass* GetAppropFrameClass(const CDocTemplate* pDTTest,
								BOOL bIsDockableFrame);

private:
	BOOL	m_bUseDocTypeID;
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// WIN32

#endif	//__DOCTEMPLATE_UTILS_H__
