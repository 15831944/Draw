///////////////////////////////////////////////////////////////////////////////
// FloatingDocTemplate.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SECFLOATINGDOCTEMPLATE_H_
#define __SECFLOATINGDOCTEMPLATE_H_

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

//@doc SECAFloatDocTemplate 
//@class Document template for use with scriptable, dynamically created forms.
//@BASE public | CMultiDocTemplate
//@comm
// Use this class in conjunction with SECScriptHostDoc, SECScriptHostView, and
// SECADlgFrame to provide proper support for scriptable frame creation. The
// following code demonstrates typical usage (place in your CWinApp's InitInstance)
//
//	SECAFloatDocTemplate* pFloatDocTempl=
//		new SECAFloatDocTemplate(IDR_TOPLEVEL,		// use these resources for loaded/new frames
//								RUNTIME_CLASS(SECScriptHostDoc),
//								RUNTIME_CLASS(SECADlgFrame),      
//								RUNTIME_CLASS(SECScriptHostView));
//	AddDocTemplate(pFloatDocTempl);
//
// In addition, you can also exploit the SECScriptHostDoc::SetFormClass static method
// to provide a new form class (see SECAFormObj) to receive scriptable dispatch events.
// For example,
//
//	...
//	AddDocTemplate(pFloatDocTempl);
//  SECScriptHostDoc::SetFormClass(RUNTIME_CLASS(CMyCustomFormClass));
//
//@xref <c SECScriptHostDoc> <c SECADlgFrame> <c SECScriptHostView>
class SECAFloatDocTemplate : public CMultiDocTemplate
{
	TOOLKIT_DECLARE_DYNAMIC(SECAFloatDocTemplate);

public:
	//@cmember
	/* Construction*/
	TOOLKIT_API SECAFloatDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
public:
	TOOLKIT_API virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);
	TOOLKIT_API virtual Confidence MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch);

	//@cmember
	/* Fetch the form dispatch matching the particular name.*/
	TOOLKIT_API virtual LPDISPATCH GetFormByName(const CString &strFormName); 
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif 		// __SECFLOATINGDOCTEMPLATE_H_

