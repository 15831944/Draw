///////////////////////////////////////////////////////////////////////////////
// SECIcon.h : interface for the SECIcon class.
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
// Author:       Justin Rudd
// Description:  Declaration of SECIcon
//

#ifndef __SECICON_H__
#define __SECICON_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

#ifdef WIN32

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

// Forward Declarations

/////////////////////////////////////////////////////////////////////////////
// SECIcon

class SECIcon : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECIcon)

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//

public:
	TOOLKIT_API SECIcon();
	TOOLKIT_API virtual ~SECIcon();

	// Attributes ...Publicly accessible member variables...
	HICON m_hIcon;
	int   m_cxWidth;
	int   m_cyHeight;

	// Accessors ...Get and Set functions...
	TOOLKIT_API HICON GetIcon() const;
	TOOLKIT_API void  SetIcon( HICON hIcon );

	//Operations
	inline operator BOOL() const { return BOOL(m_hIcon != NULL); }
	//---------------------------------------------------------------------//
	// 							Public Overridables						   //
	//---------------------------------------------------------------------//
public:
	TOOLKIT_API virtual BOOL LoadIcon( LPCTSTR lpszIcon, int iDesiredWidth, int iDesiredHeight );
	
	inline virtual BOOL LoadIcon( UINT nIcon, int iDesiredWidth, int iDesiredHeight )
		{ 
			return LoadIcon(MAKEINTRESOURCE(nIcon), iDesiredWidth, iDesiredHeight);
		}

	TOOLKIT_API virtual void Draw( CDC& dc, int iLeft, int iTop, CBrush* pBrush = NULL );
	TOOLKIT_API virtual void Draw( CDC& dc, int iLeft, int iTop, int cxWidth, int cyHeight, CBrush* pBrush = NULL );
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // WIN32
#endif // __SECICON_H__


