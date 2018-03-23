///////////////////////////////////////////////////////////////////////////////
// slstvw.h
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
//  Authors:		Dean Hallman and Justin Rudd

#ifdef WIN32

#ifndef __SLSTVW_H__
#define __SLSTVW_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SEC_LISTBASEV_H__
#include "toolkit\slstbaseV.h"
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

/////////////////////////////
// AutoDuck tag block block for SECListView 
// adinsert AutoDuck insertion point for SECListView 
//@doc SECListView 
//@class SECListView | This is an internal base class for Stingray list and tree classes.
//@base public | SEC_LISTCLASS
//@xref <c SEC_LISTCLASS>

class SECListView : public SECListBaseV  
{
	TOOLKIT_DECLARE_DYNCREATE( SECListView )

public:
	//@access Construction/Initialization
	//@cmember
	/* Construction*/
	TOOLKIT_API SECListView();
	TOOLKIT_API virtual ~SECListView();

	TOOLKIT_API SECListView& GetListCtrl() const;

	// printing
	TOOLKIT_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	TOOLKIT_API virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );

protected:
	// CView overrides
	TOOLKIT_API virtual void OnDraw( CDC* );
	TOOLKIT_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	TOOLKIT_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	TOOLKIT_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	// misc
	TOOLKIT_API virtual BOOL NextPage( CDC* pDC );
	TOOLKIT_API virtual void InternalPrepareDC( CDC* pDC );
	TOOLKIT_API virtual BOOL GoToPage( UINT nPage, CDC* pDC );

	// fonts
	TOOLKIT_API virtual BOOL InitPrinterFonts( CDC* pDC );
	TOOLKIT_API virtual BOOL ReleasePrinterFonts( );

	// core overrides
	TOOLKIT_API virtual void SECGetClientRect(LPRECT lpRect) const;
	TOOLKIT_API virtual CDC* GetActiveDC( BOOL& bDelete );

	CFont*	m_pOldLabelFont;	// saved screen font for drawing label text
	CFont*	m_pOldHeaderFont;	// saved screen font for drawing header text
	CFont	m_printLabelFont;	// font used when printing label text
	CFont	m_printHeaderFont;	// font used when printing the header control
	RECT	m_rectPage;			// we need this in our override of SECGetClientRect
	BOOL	m_bIsPrinting;		// we need this in our override of SECGetClientRect
	int		m_nScreenTopIndex;	// the top item number before printing
	UINT	m_nCurPage;
	CDC*	m_pPrinterDC;

protected:
	TOOLKIT_API afx_msg void OnPaint();
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

#endif // __SLSTVW_H__

#endif // WIN32

