///////////////////////////////////////////////////////////////////////////////
// TBMPMGR.h
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
//  Authors:		Don
//  Description:	Declarations for SECBmpMgr
//  Created:		Jan 1998
//

#ifdef WIN32

#ifndef __TBMPMGR_H__
#define __TBMPMGR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

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

#include <StingrayExportDefs.h>

class SECBmpMgr : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECBmpMgr)

public:
// Construction
	TOOLKIT_API SECBmpMgr();

	// Functions for maintaining reference count. Note this object should
	// be Release'd and note deleted!
	TOOLKIT_API void AddRef();
	TOOLKIT_API void Release();

// Operations
public:
	// Note all resources loaded are assumed to be the same size
	// Defines a toolbar resource to add to the list of bitmaps managed
	TOOLKIT_API BOOL AddToolbarResource(LPCTSTR lpszSmall, LPCTSTR lpszLarge, BOOL bSysColor = TRUE);
	TOOLKIT_API BOOL AddToolbarResource(UINT nIDSmall, UINT nIDLarge, BOOL bSysColor = TRUE);

	// Defines a bitmap resource to add to the list of bitmaps managed
	TOOLKIT_API BOOL AddBitmapResource(LPCTSTR lpszSmall, LPCTSTR lpszLarge, const UINT* lpIDArray, 
						   UINT nIDCount, BOOL bSysColor = TRUE);
	TOOLKIT_API  BOOL AddBitmapResource(UINT nIDSmall, UINT nIDLarge, const UINT* lpIDArray, 
						   UINT nIDCount, BOOL bSysColor = TRUE);

	// Defines a bitmap handle to add to the list of bitmaps managed
	TOOLKIT_API  BOOL AddBitmap(HBITMAP hBmpSmall, HBITMAP hBmpLarge, 
				   const UINT* lpIDArray, UINT nIDCount);

	// Ensures all relevant bitmaps are loaded
	TOOLKIT_API BOOL LoadBitmaps(BOOL bAlwaysLoad = TRUE);

	// Returns the bitmap and handle for the given ID.
	TOOLKIT_API BOOL GetButton(UINT nID, HBITMAP& hBmp, UINT& nIndex, BOOL bAlwaysSmall = FALSE);

	// Changes between small and large bitmap mode
	TOOLKIT_API void ChangeMode(BOOL bSmall);

	// Set's keep small bitmap mode (the small bitmap will always be loaded, even when in
	// large bitmap mode)
	TOOLKIT_API void SetKeepSmall(BOOL bKeep);

	// Set's the bitmap sizes (should not be used with AddToolbarResource).
	TOOLKIT_API void SetSmallSize(int nWidth, int nHeight);
	TOOLKIT_API void SetLargeSize(int nWidth, int nHeight);

	// Methods for returning the various bitmaps sizes
	TOOLKIT_API int  GetSmallWidth() const;
	TOOLKIT_API int  GetSmallHeight() const;
	TOOLKIT_API int  GetLargeWidth() const;
	TOOLKIT_API int  GetLargeHeight() const;
	TOOLKIT_API int  GetImgWidth() const;
	TOOLKIT_API int  GetImgHeight() const;

	// Loads the image information from a toolbar resource
	TOOLKIT_API BOOL LoadToolbarInfo(LPCTSTR lpszResourceName, UINT*& pBmpItems, UINT& nBmpItems, 
						 int& nImgWidth, int& nImgHeight, BOOL bSeparators=FALSE);

// Implementation
public:
	TOOLKIT_API virtual ~SECBmpMgr();

	// Structure detailing a particular bitmap
	struct TOOLKIT_API BmpInfo
	{
		BmpInfo();
		~BmpInfo();

		LPCTSTR m_lpszSmallRsrc;			// The small resource name
		LPCTSTR m_lpszLargeRsrc;			// The large resource name
		HBITMAP m_hBmpSmall;				// The small bitmap handle
		HBITMAP m_hBmpLarge;				// The large bitmap handle
		UINT    m_nCount;					// The no. of images in the bitmap
		BOOL    m_bSysColor;				// TRUE if the bitmap should be modified for
											// the system color scheme when loaded.
		BOOL    m_bSmallHandleOnly;			// TRUE if we don't own the small bmp handle
		BOOL    m_bLargeHandleOnly;			// TRUE if we don't own the large bmp handle
	};

	// Structure detailing an individual image
	struct TOOLKIT_API BmpItem
	{
		UINT m_nIndBmpInfo;					// Index within m_arrInfo of the BmpInfo structure
		UINT m_nBmpOffset;					// Offset within bitmap of image
	};

	// Map of ID's to BmpItem structures
	CMap<UINT, UINT, BmpItem*, BmpItem*> m_mapItem;

	// Array of BmpInfo structures
	CTypedPtrArray<CPtrArray, BmpInfo*>  m_arrInfo;
		
	int m_nSmallWidth;						// Width of small bitmap
	int m_nSmallHeight;						// Height of small bitmap
	int m_nLargeWidth;						// Width of large bitmap
	int m_nLargeHeight;						// Height of large bitmap
	BOOL m_bSmall;							// TRUE if we are in small bitmap mode
	BOOL m_bKeepSmall;						// TRUE if the small bitmaps are to always be kept
	ULONG m_nRef;							// Our reference count

protected:

	// Loads the bitmap for an individual BmpInfo item.
	TOOLKIT_API virtual BOOL LoadBitmap(BmpInfo* pInfo, BOOL bAlwaysLoad = TRUE);

	// Loads the small/large bitmap for an individual BmpInfo item.
	TOOLKIT_API virtual BOOL LoadSmall(BmpInfo* pInfo);
	TOOLKIT_API virtual BOOL LoadLarge(BmpInfo* pInfo);

	// Generates BmpItem's for the given ID array
	TOOLKIT_API void AddBmpInfo(BmpInfo* pInfo, const UINT* lpIDArray, UINT nIDCount);
};

/////////////////////////////////////////////////////////////////////////////

inline BOOL SECBmpMgr::AddToolbarResource(UINT nIDSmall, UINT nIDLarge, 
										  BOOL bSysColor /* = TRUE */)
{
	return AddToolbarResource(MAKEINTRESOURCE(nIDSmall),
							  MAKEINTRESOURCE(nIDLarge),
							  bSysColor);
}

inline BOOL SECBmpMgr::AddBitmapResource(UINT nIDSmall, UINT nIDLarge, 
										 const UINT* lpIDArray, UINT nIDCount, 
										 BOOL bSysColor /* = TRUE */)
{
	return AddBitmapResource(MAKEINTRESOURCE(nIDSmall),
							 MAKEINTRESOURCE(nIDLarge),
							 lpIDArray,
							 nIDCount,
							 bSysColor);
}

inline int SECBmpMgr::GetSmallWidth() const
{
	return m_nSmallWidth;
}

inline int SECBmpMgr::GetSmallHeight() const
{
	return m_nSmallHeight;
}

inline int SECBmpMgr::GetLargeWidth() const
{
	return m_nLargeWidth;
}

inline int SECBmpMgr::GetLargeHeight() const
{
	return m_nLargeHeight;
}

inline int SECBmpMgr::GetImgWidth() const
{
	return m_bSmall ? GetSmallWidth() : GetLargeWidth();
}

inline int SECBmpMgr::GetImgHeight() const
{
	return m_bSmall ? GetSmallHeight() : GetLargeHeight();
}

/////////////////////////////////////////////////////////////////////////////

#endif	// __TBMPMGR_H__

#endif	// WIN32
