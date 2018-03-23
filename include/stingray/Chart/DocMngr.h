///////////////////////////////////////////////////////////////////////////////
// DocMngr.h
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

/////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////
//@doc
//@module DocMngr.h | implementation file for the SECDocManager class<nl>
//Adds functionality to the default OnFileNew behavior
//Written by Bob Powell (www.roguewave.com)

//@mfunc virtual CDocument * | SECDocManager | OnFileNew | File creation function with parameters to allow a document to begin some process immediately and without user intervention
//@parm LPCTSTR | DocIdent | Pointer to a constant string identifying the document
//@parm SEC_UINT | nIpCode | The OpCode (default set to 0)
//@parm SEC_UINT | nSubCode | The SubCode (default set to 0)
//@parm SEC_DWORD | dwData | The data (default set to NULL)
//@parm SECComDoc * | parent | A pointer to the parent (default set to NULL)

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SECDOCMANAGER__
#define __SECDOCMANAGER__

#include <StingrayExportDefs.h>

//$head The "ComDoc" system
//$level 1
//@class Stingray Document Manager class -- inherits behaviors from the standard CDocManager class 
//and adds the ability to open and link <c SECComDoc> documents
class SECDocManager : public CDocManager
{
public:
	//@cmember
	/* File creation function with parameters to allow a document to begin some process immediately and without user intervention*/
	CHART_API virtual CDocument* OnFileNew(LPCTSTR DocIdent, SEC_UINT nOpCode,SEC_UINT nSubCode=0, SEC_DWORD dwData=NULL,SECComDoc *parent=NULL);
	
	//@cmember
	/* Constructor*/
	CHART_API SECDocManager();

	//@cmember
	/* File creation function with a choice of document type and parameter passing to empty documents*/
	CHART_API void OnFileNew(LPCTSTR DocIdent,LPCTSTR Params=NULL,SECComDoc *parent=NULL);

	//@cmember
	/* Standard behavior*/
	CHART_API void OnFileNew();
};

#endif
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

