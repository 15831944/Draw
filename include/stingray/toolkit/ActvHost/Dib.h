///////////////////////////////////////////////////////////////////////////////
// Dib.h
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
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See dib.cpp

#ifndef __SEC_DIB_H_
#define __SEC_DIB_H_

#ifndef _INC_VFW
#pragma message ("NOTE: You can speed compilation by including <vfw.h> in stdafx.h")
#pragma warning(disable:4201)
#include <vfw.h>		// to speed up compilation
#pragma warning(default:4201)
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

// global functions for ordinary CBitmap too
//
extern CSize GetBitmapSize(CBitmap* pBitmap);
extern BOOL  DrawBitmap(CDC& dc, CBitmap* pBitmap,
	const CRect* rcDst, const CRect* rcSrc);

////////////////
// SECADib implements Device Independent Bitmaps as a form of CBitmap. 
//
class SECADib : public CBitmap 
{
protected:
	TOOLKIT_DECLARE_DYNAMIC(SECADib)
	BITMAP	 m_bm;		// stored for speed
	CPalette m_pal;	// palette
	HDRAWDIB m_hdd;	// for DrawDib

public:
	TOOLKIT_API SECADib();
	TOOLKIT_API ~SECADib();

	CSize	GetSize() { return CSize(m_bm.bmWidth, m_bm.bmHeight); }
	TOOLKIT_API BOOL Attach(HGDIOBJ hbm);
	TOOLKIT_API BOOL Load(LPCTSTR szPathName);
	TOOLKIT_API BOOL Load(HINSTANCE hInst, LPCTSTR lpResourceName);
	inline BOOL Load(HINSTANCE hInst, UINT uID)
		{ return Load(hInst, MAKEINTRESOURCE(uID)); }

	// Universal Draw function can use DrawDib or not.
	TOOLKIT_API BOOL Draw(CDC& dc, const CRect* rcDst=NULL, const CRect* rcSrc=NULL,
		BOOL bUseDrawDib=TRUE, CPalette* pPal=NULL, BOOL bForeground=FALSE);

	TOOLKIT_API BOOL DeleteObject();
	TOOLKIT_API BOOL CreatePalette(CPalette& pal);
	inline CPalette* GetPalette()  { return &m_pal; }

	TOOLKIT_API UINT GetColorTable(RGBQUAD* colorTab, UINT nColors);
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SEC_DIB_H_
