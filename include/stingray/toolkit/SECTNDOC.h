///////////////////////////////////////////////////////////////////////////////
// SECTNDOC.h
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
//  Author:		Scot Wingo
//  Description:	Declaration of SECTNDocument - The ThumbNail document class
//  Created:		Wed Jul 26 13:15:44 1995
//

#ifndef __SECTNDOC_H__
#define __SECTNDOC_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

// Forward declarations
class SECTNView;

/////////////////////////////
// AutoDuck tag block block for SECTNDocument 


// adinsert AutoDuck insertion point for SECTNDocument 
//@doc SECTNDocument 
//@class SECTNDocument is a CDocument replacement that adds automatic thumbnailing to your 
// document’s Serialize routine.
//@comm
// First, SECTNDocument calls <mf SECTNDocument::GetThumbNailView> to obtain the view to thumbnail.  
// By default this is the first view in the document’s list of views.
//
// After obtaining a pointer to the view to thumbnail, SECTNDocument calls the view’s 
// GetThumbNailBitmap routine which eventually calls the OnDraw routine causing the view to draw 
// itself into a thumbnail bitmap.  This bitmap is prepended to the application-specific serialized 
// data by SECTNDocument during the Serialize calls. Therefore, if you override 
// SECTNDocument::<mf SECTNDocument::Serialize>, it is very important to be sure to place a 
// call to the base class’s Serialize member function before serializing your application-specific 
// data.
//
// When de-serializing, or reading, SECTNDocument::<mf SECTNDocument::Serialize> knows to skip over 
// the thumbnail image and just read in the application-specific data.
//
// The THUMBNL sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\THUMBNL directory demonstrates how to use 
// SECTNDocument and the other thumbnailing support classes.
//@xref<c SECTNBitmap> @xref<c SECTNDC> @xref<c SECTNFileDialog> @xref<c SECTNView> @xref<c SECTNWinApp>
//@BASE public|CDocument
class SECTNDocument : public CDocument
{
protected:
	TOOLKIT_API SECTNDocument();           // protected constructor used by dynamic creation
	TOOLKIT_DECLARE_DYNCREATE(SECTNDocument)

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECTNDocument)
protected:
	TOOLKIT_API virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL
    //Override to specify a certain view for thumbnailing
    //@access Protected Members
	//@cmember
	/* Gets a pointer to the SECTNView that will create the thumbnail image.*/
    TOOLKIT_API virtual SECTNView * GetThumbNailView();

// Implementation
public:
	TOOLKIT_API virtual ~SECTNDocument();
//@access Public Members
	//@cmember
	/* Prepends the application-specific serialization data with a thumbnail image when writing.*/
	// When reading, skips over the thumbnail image to the point where application-data begins.
	TOOLKIT_API virtual void Serialize(CArchive& ar);  
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(SECTNDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECTNDOC_H__

