///////////////////////////////////////////////////////////////////////////////
// GraphicContext.h : Advanced graphics package
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
// Author:       Bob Powell
// Description:  GDI Device context wrapper
//

#pragma once

#include <foundation\APIStructs\GCUtil.h>
#include <foundation\Graphics\GDIObjects.h>
#include <tchar.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////
// CGraphicsContext class


//@doc CGraphicsContext 
//@class Encapsulates a Windows device context
//@comm
// The CGraphicsContext class is a very thin wrapper around the
// Device Context concept in Windows GDI, and its API.<nl>
// Most of this class methods are just inline invocations of
// the corresponding API functions. The working details of each of
// those functions are not covered here. Please refer to your
// Windows Platform SDK documentation for more information.
class CGraphicsContext
{

public:
	//@cmember
	// Attach constructor. Attaches the given DC handle to this instance.
	inline CGraphicsContext(HDC h = NULL);

	//@cmember
	// Copy constructor. Copies the contents of the given CGraphicsContext instance.
	inline CGraphicsContext(const CGraphicsContext& rhs);

	//@cmember,mfunc
	// CGraphicsContext destructor.
	/*@@comm
		Destructor: The CGraphicsContext destructor does not perform any
		release operation over the contained device context handle. 
		The correct way to destroy a device context depends on how it was 
		created in the first place, and since a CGraphicsContext object
		never creates a device context, it never destroys it either.
	*/
	virtual ~CGraphicsContext()
	{
		// Never destroy the handle upon destruction of the handle in this class. 
		// No ownership associated with instances of this class.
	}

	//@cmember
	// Assignment operator
	CGraphicsContext& operator=(const CGraphicsContext& rhs)
	{
		m_hDC = rhs.m_hDC;
		m_hAttribDC = rhs.m_hAttribDC;
		m_CurrentPosition = rhs.m_CurrentPosition;
		m_StartPoint = rhs.m_StartPoint;
		m_EndPoint = rhs.m_EndPoint;
		return *this;
	}

	//@cmember HDC | operator HDC | () |
	// Casting operator.
	operator HDC() const
	{
		return m_hDC;
	}


public:
	// Creation/destruction virtuals

	//@cmember
	/* 
		Attaches an existing device context handle to this instance
		of CGraphicsContext.
	*/
	inline virtual void Attach(HDC h);

	//@cmember
	/* 
		Terminates the relationship between this instance of CGraphicsContext
		and the contained DC handle, without releasing it.
	*/
	inline virtual HDC Detach();

	//@cmember
	/* 
		Causes the release of the contained DC handle. The actual release process
		is executed in ReleaseHandle, which must be implemented by all derived
		classes. CGraphicsContext instances do not release the DC handle, since 
		they don't create it.
	*/
	inline virtual bool Delete();

	//@cmember
	/* 
		Override in derived classes to release the DC handle according to 
		the process followed to create it. 
		ReleaseHandle() is a noop in CGraphicsContext, since there is no
		creation mehanism associated.
	*/
	inline virtual bool ReleaseHandle();


public:

	// GDI Object selection

	//@cmember
	/* 
		Selects one of Windows stock pens, brushes, fonts or palettes in the 
		device context. Returns a generic CGDIObject containing the correspon-
		ding object that has been unselected as a result.
	*/
	inline CGDIObject<HGDIOBJ> SelectStockObject(int nIndex);

	//@cmember,mfunc _GDIWrapper | SelectObject | _GDIWrapper& aGDIObject |
	// Select a GDI Object in the device context
	//@@tfarg typename | _GDIWrapper | Placeholder for any of the GDI wrapper objects, such as
	// CGDIPen, CGDIBrush, etc
	//@@rdesc Object that has been unselected from the device context. 
	// The returned instance does not have ownership of the contained handle
	//@@parm _GDIWrapper& | aGDIObject | Object to select in the DC
	template <typename _GDIWrapper>
	_GDIWrapper SelectObject(_GDIWrapper& aGDIObject)
	{
		ASSERT(m_hDC);
		HGDIOBJ hOld = NULL;
		if (m_hDC != m_hAttribDC) {
			hOld = ::SelectObject(m_hDC, static_cast<HGDIOBJ>(aGDIObject));
		}
		if (m_hAttribDC != NULL) {
			hOld = ::SelectObject(m_hAttribDC, static_cast<HGDIOBJ>(aGDIObject));
		}
		_GDIWrapper objRetVal(reinterpret_cast<_GDIWrapper::HANDLE>(hOld), false);
		return objRetVal;
	}

	//@cmember,mfunc _GDIWrapper | SelectObject | _GDIWrapper* pGDIObject |
	// Override needed to match the MFC Parameter types for SelectObject
	// The different return type is OK and necessary
	//@@tfarg typename | _GDIWrapper | Placeholder for any of the GDI wrapper objects, such as
	// CGDIPen, CGDIBrush, etc
	//@@rdesc Object that has been unselected from the device context. 
	// The returned instance does not have ownership of the contained handle
	//@@parm _GDIWrapper* | pGDIObject | Object to select in the DC
	template <typename _GDIWrapper>
	_GDIWrapper SelectObject(_GDIWrapper* pGDIObject)
	{
		ASSERT(pGDIObject);
		return SelectObject(*pGDIObject);
	}

	// Specialization for CGDIRgn
	template <typename _GDIWrapper>
	int SelectObject(CGDIRgn& aRgn)
	{
		ASSERT(m_hDC);
		int nRetVal = GDI_ERROR;

		if (m_hDC != m_hAttribDC) {
			nRetVal = ::SelectClipRgn(m_hDC, aRgn);
		}
		if (m_hAttribDC != NULL) {
			nRetVal = ::SelectClipRgn(m_hAttribDC, aRgn);
		}
		return nRetVal;
	}

	template <typename _GDIWrapper>
	int SelectObject(CGDIRgn* pRgn)
	{
		return SelectObject(*pRgn);
	}

	//@cmember
	// Set the value of the Attribute DC
	inline void SetAttribDC(HDC hDC);  // Set the Attribute DC

	//@cmember
	//Change the value of the Output DC
	inline void SetOutputDC(HDC hDC);  // Set the Output DC

	//@cmember
	// Release the Attribute DC
	inline void ReleaseAttribDC();

	//@cmember
	// Release the Output DC
	inline void ReleaseOutputDC();


	//@cmember
	// true if being used for printing
	inline bool IsPrinting() const;

#if !defined(UNDER_CE) && (WINVER >= 0x0500)
	//@cmember
	// Get layout
	inline DWORD GetLayout() const;

	//@cmember
	// Set layout
	inline DWORD SetLayout(DWORD dwLayout);
#endif


public:	
// Device-Context Functions

	//@cmember
	/* Creates a Graphics Context based for the device driver specified */
	inline bool CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName,LPCTSTR lpszOutput, const void* lpInitData);

	//@cmember
	/* Creates an Information Context for print/preview purposes */
	inline bool CreateIC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData);

	//@cmember
	// Creates a DC compatible with the one passed in.
	inline bool CreateCompatibleDC(const CGraphicsContext* aDC);

	//@cmember
	// Releases the DC.
	inline bool DeleteDC();


	//@cmember Please refer to the Win32 PlatformSDK
	inline int SaveDC();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool RestoreDC(int nSavedDC);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetDeviceCaps(int nIndex) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags);

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ResetDC(const DEVMODE* lpDevMode);


// Drawing-Tool Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint GetBrushOrg() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetBrushOrg(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetBrushOrg(POINT point);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int EnumObjects(int nObjectType,int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

public:

	//@cmember Please refer to the Win32 PlatformSDK
	HDC GetSafeHdc()
	{
		return m_hDC;
	}

	//@cmember Please refer to the Win32 PlatformSDK
	inline void StrokeScanPoints();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void EndScanPoints();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void FillScanPoints();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void BeginScanPoints();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void AddScanPoint(CPoint pt);

	CPoint m_LastPoint;


// Color and Color Palette Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF GetNearestColor(COLORREF crColor) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CGDIPalette SelectPalette(CGDIPalette& aPalette, bool bForceBackground);

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT RealizePalette();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void UpdateColors();

// Drawing-Attribute Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF GetBkColor() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetBkMode() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetPolyFillMode() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetROP2() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetStretchBltMode() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF GetTextColor() const;


	//@cmember Please refer to the Win32 PlatformSDK
	// todo Add your Intellisense compatible description here
	inline COLORREF SetBkColor(COLORREF crColor);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetBkMode(int nBkMode);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetPolyFillMode(int nPolyFillMode);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetROP2(int nDrawMode);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetStretchBltMode(int nStretchMode);

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF SetTextColor(COLORREF crColor);


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

// Mapping Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetMapMode() const;


	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint GetViewportOrg();


	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetMapMode(int nMapMode);

	// Viewport Origin

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetViewportOrg(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetViewportOrg(POINT point);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint OffsetViewportOrg(int nWidth, int nHeight);

	// Viewport Extent

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetViewportExt();

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize SetViewportExt(int cx, int cy);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize SetViewportExt(SIZE size);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);

	// Window Origin

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint GetWindowOrg();

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetWindowOrg(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint SetWindowOrg(POINT point);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint OffsetWindowOrg(int nWidth, int nHeight);

	// Window extent

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetWindowExt();

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize SetWindowExt(int cx, int cy);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize SetWindowExt(SIZE size);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

// Coordinate Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DPtoLP(LPPOINT lpPoints, int nCount = 1) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DPtoLP(LPRECT lpRect) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DPtoLP(LPSIZE lpSize) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void LPtoDP(LPPOINT lpPoints, int nCount = 1) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void LPtoDP(LPRECT lpRect) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void LPtoDP(LPSIZE lpSize) const;

// Special Coordinate Functions (useful for dealing with metafiles and OLE)

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DPtoHIMETRIC(LPSIZE lpSize) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void LPtoHIMETRIC(LPSIZE lpSize) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void HIMETRICtoDP(LPSIZE lpSize) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline void HIMETRICtoLP(LPSIZE lpSize) const;

// Region Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool FillRgn(CGDIRgn& aRgn, CGDIBrush& aBrush);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool FrameRgn(CGDIRgn& aRgn, CGDIBrush& aBrush, int nWidth, int nHeight);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool InvertRgn(CGDIRgn& aRgn);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PaintRgn(CGDIRgn& aRgn);

// Clipping Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetClipBox(LPRECT lpRect) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PtVisible(int x, int y) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PtVisible(POINT point) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool RectVisible(LPCRECT lpRect) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SelectClipRgn(CGDIRgn& aRgn);
	inline int SelectClipRgn(CGDIRgn* pRgn);
	inline int SelectClipRgn(CGDIRgn& aRgn, int nMode);
	inline int SelectClipRgn(CGDIRgn* pRgn, int nMode);
	inline int ClearClipRgn();

	//@cmember Please refer to the Win32 PlatformSDK
	inline int ExcludeClipRect(int x1, int y1, int x2, int y2);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int ExcludeClipRect(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int ExcludeUpdateRgn(HWND hWnd); // MODIFIED from CDC

	//@cmember Please refer to the Win32 PlatformSDK
	inline int IntersectClipRect(int x1, int y1, int x2, int y2);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int IntersectClipRect(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int OffsetClipRgn(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int OffsetClipRgn(SIZE size);


// Line-Output Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint GetCurrentPosition() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint MoveTo(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CPoint MoveTo(POINT point);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool LineTo(int x, int y);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool LineTo(POINT point);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Polyline(LPPOINT lpPoints, int nCount);


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetArcDirection() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetArcDirection(int nArcDirection);


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolylineTo(const POINT* lpPoints, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount);


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolyBezier(const POINT* lpPoints, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolyBezierTo(const POINT* lpPoints, int nCount);

// Simple Drawing Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline void FillRect(LPCRECT lpRect, CGDIBrush* pBrush);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void FrameRect(LPCRECT lpRect, CGDIBrush* pBrush);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void InvertRect(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawIcon(int x, int y, HICON hIcon);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawIcon(POINT point, HICON hIcon);
#ifndef UNDER_CE
	#if (WINVER >= 0x400)

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawState(CPoint pt, CSize size, HBITMAP hBitmap, UINT nFlags,HBRUSH hBrush = NULL);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawState(CPoint pt, CSize size, HICON hIcon, UINT nFlags,HBRUSH hBrush = NULL);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawState(CPoint pt, CSize size, LPCTSTR lpszText, UINT nFlags,bool bPrefixText = TRUE, int nTextLen = 0, HBRUSH hBrush = NULL);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawState(CPoint pt, CSize size, DRAWSTATEPROC lpDrawProc,LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
#endif
#endif //UNDER_CE

// Ellipse and Polygon Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DrawFocusRect(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Ellipse(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Ellipse(int x1, int y1, int x2, int y2);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Polygon(LPPOINT lpPoints, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PolyPolygon(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Rectangle(int x1, int y1, int x2, int y2);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool Rectangle(LPCRECT lpRect);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool RoundRect(int x1, int y1, int x2, int y2, int x3, int y3);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool RoundRect(LPCRECT lpRect, POINT point);

// Bitmap Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop);
	inline bool PatBlt(CRect rc, DWORD dwRop);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool BitBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, DWORD dwRop);
	inline bool BitBlt(CRect rcDst, CGraphicsContext& aSrcGC, CPoint ptSrc, DWORD dwRop);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool StretchBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);
	inline bool StretchBlt(CRect rcDst, CGraphicsContext& aSrcGC, CRect rcSrc, DWORD dwRop);

#if(WINVER >= 0x0500)
	//@cmember Please refer to the Win32 PlatformSDK
	inline bool TransparentBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest, CGraphicsContext& aSrcGC, 
		                int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);
	//@cmember Please refer to the Win32 PlatformSDK
	inline bool TransparentBlt(CRect rcDst, CGraphicsContext& aSrcGC, CRect rcSrc, UINT crTransparent);
#endif

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool MaskBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, CGDIBitmap& aBmpMask, int xMask, int yMask, DWORD dwRop);
	//@cmember Please refer to the Win32 PlatformSDK
	inline bool MaskBlt(CRect rcDst, CGraphicsContext& aSrcGC, CPoint ptSrc, CGDIBitmap& aBmpMask, CPoint ptMaskOffset, DWORD dwRop);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PlgBlt(LPPOINT lpPoint, CGraphicsContext& aSrcGC, int xSrc, int ySrc, int nWidth, int nHeight, CGDIBitmap& aBmpMask, int xMask, int yMask);

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF GetPixel(int x, int y) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF GetPixel(POINT point) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF SetPixel(int x, int y, COLORREF crColor);

	//@cmember Please refer to the Win32 PlatformSDK
	inline COLORREF SetPixel(POINT point, COLORREF crColor);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool FloodFill(int x, int y, COLORREF crColor);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool SetPixelV(int x, int y, COLORREF crColor);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool SetPixelV(POINT point, COLORREF crColor);

// Text Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool TextOut(int x, int y, LPCTSTR lpszString, int nCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int DrawText(LPCTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat = 0);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat = 0, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetTextExtent(LPCTSTR lpszString, int nCount) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetOutputTextExtent(LPCTSTR lpszString, int nCount) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetTabbedTextExtent(LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetOutputTabbedTextExtent(LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GrayString(CGDIBrush& aBrush, BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData,int nCount, int x, int y, int nWidth, int nHeight);

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT GetTextAlign() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT SetTextAlign(UINT nFlags);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetTextFace(int nCount, LPTSTR lpszFacename) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetTextMetrics(LPTEXTMETRIC lpMetrics) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetTextJustification(int nBreakExtra, int nBreakCount);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetTextCharacterExtra() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetTextCharacterExtra(int nCharExtra);

	// Advanced Drawing
#if (WINVER >= 0x400)

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);
#endif

// Scrolling Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, CGDIRgn& aRgnUpdate, LPRECT lpRectUpdate);

// Font Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline DWORD SetMapperFlags(DWORD dwFlag);

	//@cmember Please refer to the Win32 PlatformSDK
	inline CSize GetAspectRatioFilter() const;


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;


	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const;

// Printer/Device Escape Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline int Escape(int nEscape, int nCount,LPCSTR lpszInData, LPVOID lpOutData);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int Escape(int nEscape, int nInputSize, LPCSTR lpszInputData,int nOutputSize, LPSTR lpszOutputData);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int DrawEscape(int nEscape, int nInputSize, LPCSTR lpszInputData);

	// Escape helpers

	//@cmember Please refer to the Win32 PlatformSDK
	inline int StartDoc(LPCTSTR lpszDocName);  // old Win3.0 version

	//@cmember Please refer to the Win32 PlatformSDK
	inline int StartDoc(LPDOCINFO lpDocInfo);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int StartPage();

	//@cmember Please refer to the Win32 PlatformSDK
	inline int EndPage();

	//@cmember Please refer to the Win32 PlatformSDK
	inline int SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, int));

	//@cmember Please refer to the Win32 PlatformSDK
	inline int AbortDoc();

	//@cmember Please refer to the Win32 PlatformSDK
	inline int EndDoc();

// MetaFile Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PlayMetaFile(HMETAFILE hMF);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
		// can be used for enhanced metafiles only

// Path Functions

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool AbortPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool BeginPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool CloseFigure();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool EndPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool FillPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool FlattenPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool StrokeAndFillPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool StrokePath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool WidenPath();

	//@cmember Please refer to the Win32 PlatformSDK
	inline float GetMiterLimit() const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool SetMiterLimit(float fMiterLimit);

	//@cmember Please refer to the Win32 PlatformSDK
	inline int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const;

	//@cmember Please refer to the Win32 PlatformSDK
	inline bool SelectClipPath(int nMode);

// Misc Helper Functions

	inline static CGDIBrush GetHalftoneBrush();

	//@cmember Please refer to the Win32 PlatformSDK
	inline void DrawDragRect(LPCRECT pRect, SIZE size, LPCRECT pRectLast, SIZE sizeLast, const CGDIBrush& aBrush = CGDIBrush(), const CGDIBrush& aBrushLast = CGDIBrush());

	//@cmember Please refer to the Win32 PlatformSDK
	inline void FillSolidRect(LPCRECT lpRect, COLORREF clr);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);

	//@cmember Please refer to the Win32 PlatformSDK
	inline void Draw3dRect(int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight);

#ifdef NONSTANDARD_GDI


	//@cmember Please refer to the Win32 PlatformSDK
	inline virtual void AdjustViewport();

#endif //NONSTANDARD_GDI


/////////////////////////////////////////////////////////////////////////////////
//
//	IGraphicsUtility implementations
//
/////////////////////////////////////////////////////////////////////////////////


	inline double GetLineAngle(CPoint ptStart, CPoint ptEnd, bool bAdjust = false) ;
	inline double GetAngleDifference(double a1, double a2) ;
	inline double GetLineLength(CPoint ptStart, CPoint ptEnd);


/////////////////////////////////////////////////////////////////////////////////
//
//	IAdvancedGraphics implementations
//
/////////////////////////////////////////////////////////////////////////////////


	inline void AttachEx(HDC hdc);

	inline void SetEndPoint(CPoint v) {m_EndPoint = v;}

	inline CPoint GetEndPoint() {return m_EndPoint;}

	inline void SetStartPoint(CPoint v) {m_StartPoint = v;}

	inline CPoint GetStartPoint() {return m_StartPoint;}

protected:

	// DC handles
	HDC m_hDC;
	HDC m_hAttribDC;

	// Cache of the DC current position
	CPoint m_CurrentPosition;

	// Advanced graphics
	CPoint m_StartPoint;
	CPoint m_EndPoint;

};


///////////////////////////////////////////////////////////
// Inline functions implementation

// Constructors

inline
// @mfunc
// Attach constructor: Initializes the object, optionally attaching it
// to a device context handle 
// @parm HDC | h | Device context handle to attach.
CGraphicsContext::CGraphicsContext (
	HDC h
): m_hDC(h), m_hAttribDC(h)
{}


inline
//@mfunc
// Copy constructor: Initializes the object, copying its state
// from an existing instance. Upon return, both instances refer to the same
// device context handle.
//@parm const CGraphicsContext&  | rhs | Graphics context instance to copy
CGraphicsContext::CGraphicsContext (
	const CGraphicsContext& rhs
): m_hDC(rhs.m_hDC), m_hAttribDC(rhs.m_hDC)
{}


// Creation/destruction

inline
//@mfunc
/* 
	Attaches an existing device context handle to this instance
	of CGraphicsContext.
*/
//@parm HDC | h | Device context handle
void CGraphicsContext::Attach(HDC h)
{
	if (m_hDC != NULL) {
		Detach();
	}
	m_hDC = m_hAttribDC = h;
}

inline
//@mfunc
/* 
	Terminates the relationship between this instance of CGraphicsContext
	and the contained DC handle, without releasing it.
*/
//@rdesc DC handle previously associated with this instance
HDC CGraphicsContext::Detach() 
{
	HDC h = m_hDC;
	m_hDC = m_hAttribDC = NULL;
	return h;
}

inline
//@mfunc
/* 
	Causes the release of the contained DC handle. The actual release process
	is executed in ReleaseHandle, which must be implemented by all derived
	classes. CGraphicsContext instances do not release the DC handle, since 
	they don't create it.
*/
//@rdesc true if successful, false to indicate the occurrence of an error
bool CGraphicsContext::Delete()
{
	bool bRes = true;
	if (m_hDC) {
		bRes = ReleaseHandle();
		m_hDC = NULL;
		m_hAttribDC = NULL;
	}
	return bRes;
}

inline
//@mfunc
/* 
	Override in derived classes to release the DC handle according to 
	the process followed to create it. 
	ReleaseHandle() is a noop in CGraphicsContext, since there is no
	creation mehanism associated.
*/
//@rdesc true if successful, false to indicate the occurrence of an error
bool CGraphicsContext::ReleaseHandle()
{
	// Noop in this class
	return true;
}




// Accessors

inline
CGDIObject<HGDIOBJ> CGraphicsContext::SelectStockObject(int nIndex)
{
	ASSERT(m_hDC);
	HGDIOBJ hObj = ::GetStockObject(nIndex);
	HGDIOBJ hOldObj = NULL;
	if (hObj) {
		if (m_hDC != m_hAttribDC) {
			hOldObj = ::SelectObject(m_hDC, hObj);
		}
		if (m_hAttribDC != NULL) {
			hOldObj = ::SelectObject(m_hAttribDC, hObj);
		}
	}

	CGDIObject<HGDIOBJ> aRetObject(hOldObj);
	return aRetObject;
}


inline
void CGraphicsContext::SetAttribDC(HDC hDC)
{
	m_hAttribDC = hDC;
}

inline
void CGraphicsContext::SetOutputDC(HDC hDC)
{
	m_hDC = hDC;
}

inline
void CGraphicsContext::ReleaseAttribDC()
{
	// Equivalent to detach, no destruction performed...
	m_hAttribDC = m_hDC;
}

inline
void CGraphicsContext::ReleaseOutputDC()
{
	// Equivalent to detach, no destruction performed...
	m_hDC = NULL;
}

inline
bool CGraphicsContext::IsPrinting() const
{
	return (m_hAttribDC != m_hDC)? true : false;
}


// Device-context functions

inline
bool CGraphicsContext::CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData)
{
#ifndef UNDER_CE
	HDC hDC=::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, reinterpret_cast<const DEVMODE *>(lpInitData));
#else // if UNDER_CE
	HDC hDC=::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const _devicemodeW *)lpInitData);
#endif //UNDER_CE
	if (hDC) {
		Attach(hDC);
	}

	return hDC != NULL;
}

inline
bool CGraphicsContext::CreateIC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName,LPCTSTR lpszOutput, const void* lpInitData)
{
#ifndef UNDER_CE
	HDC hDC = ::CreateIC(lpszDriverName,lpszDeviceName,lpszOutput, reinterpret_cast<const DEVMODE*>(lpInitData));
	if (hDC) {
		Attach(hDC);
	}
#else
	HDC hDC = NULL;
#endif //UNDER_CE

	return hDC != NULL;
}

inline
bool CGraphicsContext::CreateCompatibleDC(const CGraphicsContext* aDC)
{
	HDC hDC = NULL;
	if (aDC != NULL) {
		hDC = *aDC;
	}
	HDC hDCNew;
	ASSERT(hDC);
	hDCNew = ::CreateCompatibleDC(hDC);

	if (hDCNew) {
		Attach(hDCNew);
	}
	
	return hDCNew != NULL;
}

inline
bool CGraphicsContext::DeleteDC()
{
	if (m_hDC != NULL) {
		::DeleteDC(m_hDC);
	}
	m_hDC = NULL;
	return true;
}


inline
int CGraphicsContext::SaveDC()
{
	ASSERT(m_hDC);
	int nRetVal = 0;
	if (m_hAttribDC) {
		nRetVal = ::SaveDC(m_hAttribDC);
	}
	if (m_hDC != m_hAttribDC && ::SaveDC(m_hDC) != 0) {
		nRetVal = -1;
	}
	return nRetVal;
}

inline
bool CGraphicsContext::RestoreDC(int nSavedDC)
{
	ASSERT(m_hDC);
	// if two distinct DCs, nSavedDC can only be -1
	ASSERT(m_hDC == m_hAttribDC || nSavedDC == -1);

	bool bRetVal = true;
	if (m_hDC != m_hAttribDC) {
		bRetVal = ::RestoreDC(m_hDC, nSavedDC)? true : false;
	}
	if (m_hAttribDC != NULL) {
		bRetVal = (bRetVal && ::RestoreDC(m_hAttribDC, nSavedDC));
	}
	return bRetVal;
}

inline
int CGraphicsContext::GetDeviceCaps(int nIndex) const
{
	ASSERT(m_hDC);
	return ::GetDeviceCaps(m_hAttribDC, nIndex);
}

inline
UINT CGraphicsContext::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::SetBoundsRect(m_hDC,lpRectBounds,flags);
#else
	return 0;
#endif
}

inline
UINT CGraphicsContext::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetBoundsRect(m_hAttribDC, lpRectBounds, flags);
#else
	return 0;
#endif
}

inline
bool CGraphicsContext::ResetDC(const DEVMODE* lpDevMode)
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::ResetDC(m_hAttribDC, lpDevMode) != NULL ? true : false;
#else
	return false; // CE devices dont handle this
#endif
}

inline
int CGraphicsContext::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::EnumObjects(m_hAttribDC, nObjectType, lpfn, lpData);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI

}

// Drawing-Tool Functions

inline
CPoint CGraphicsContext::GetBrushOrg() const
{
	ASSERT(m_hDC != NULL);
	POINT point;
#ifndef NONSTANDARD_GDI
	::GetBrushOrgEx(m_hDC, &point);
#else
	point = CPoint(0,0);
#endif
	return point;
}

inline
CPoint CGraphicsContext::SetBrushOrg(int x, int y)
{
	ASSERT(m_hDC);
	POINT point;
	::SetBrushOrgEx(m_hDC, x, y, &point);
	return point;
}

inline
CPoint CGraphicsContext::SetBrushOrg(POINT point)
{
	ASSERT(m_hDC);
	POINT p;
	::SetBrushOrgEx(m_hDC, point.x, point.y, &p);
	return p;
}



// Color and Color Palette Functions

inline
COLORREF CGraphicsContext::GetNearestColor(COLORREF crColor) const
{
	ASSERT(m_hDC);
	return ::GetNearestColor(m_hAttribDC, crColor);
}

inline
CGDIPalette CGraphicsContext::SelectPalette(CGDIPalette& aPalette, bool bForceBackground)
{
	ASSERT(m_hDC);
	HPALETTE hPal = static_cast<HPALETTE>(aPalette);
	ASSERT(hPal);

	hPal = ::SelectPalette(m_hDC, hPal, bForceBackground);
	CGDIPalette aRetObject(hPal);
	return aRetObject;
}

inline
UINT CGraphicsContext::RealizePalette()
{
	ASSERT(m_hDC);
	return ::RealizePalette(m_hDC);
}

inline
void CGraphicsContext::UpdateColors()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	::UpdateColors(m_hDC);
#endif
}



// Drawing-Attribute Functions

inline
COLORREF CGraphicsContext::GetBkColor() const
{
	ASSERT(m_hDC);
	return ::GetBkColor(m_hAttribDC);
}

inline
int CGraphicsContext::GetBkMode() const
{
	ASSERT(m_hDC);
	return ::GetBkMode(m_hAttribDC);
}

inline
int CGraphicsContext::GetPolyFillMode() const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetPolyFillMode(m_hAttribDC);
#else
	return 0;
#endif
}

inline
int CGraphicsContext::GetROP2() const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetROP2(m_hAttribDC);
#else
	return 0;
#endif
}

inline
int CGraphicsContext::GetStretchBltMode() const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetStretchBltMode(m_hAttribDC);
#else
	return 0;
#endif
}

inline
COLORREF CGraphicsContext::GetTextColor() const
{
	ASSERT(m_hDC);
	return ::GetTextColor(m_hAttribDC);
}

inline
COLORREF CGraphicsContext::SetBkColor(COLORREF crColor)
{
	ASSERT(m_hDC);
	COLORREF crRetVal = CLR_INVALID;

	if (m_hDC != m_hAttribDC) {
		crRetVal = ::SetBkColor(m_hDC, crColor);
	}
	if (m_hAttribDC != NULL) {
		crRetVal = ::SetBkColor(m_hAttribDC, crColor);
	}
	return crRetVal;
}

inline
int CGraphicsContext::SetBkMode(int nBkMode)
{
	ASSERT(m_hDC);
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetBkMode(m_hDC, nBkMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetBkMode(m_hAttribDC, nBkMode);
	}
	return nRetVal;
}

inline
int CGraphicsContext::SetPolyFillMode(int nPolyFillMode)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetPolyFillMode(m_hDC, nPolyFillMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetPolyFillMode(m_hAttribDC, nPolyFillMode);
	}
	return nRetVal;
#else
	return 0;
#endif
}

inline
int CGraphicsContext::SetROP2(int nDrawMode)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetROP2(m_hDC, nDrawMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetROP2(m_hAttribDC, nDrawMode);
	}
	return nRetVal;
#else
	return 0;
#endif
	
}

inline
int CGraphicsContext::SetStretchBltMode(int nStretchMode)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetStretchBltMode(m_hDC, nStretchMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetStretchBltMode(m_hAttribDC, nStretchMode);
	}
	return nRetVal;
#else
	return 0;
#endif
}

inline
COLORREF CGraphicsContext::SetTextColor(COLORREF crColor)
{
	ASSERT(m_hDC);
	COLORREF crRetVal = CLR_INVALID;

	if (m_hDC != m_hAttribDC) {
		crRetVal = ::SetTextColor(m_hDC, crColor);
	}
	if (m_hAttribDC != NULL) {
		crRetVal = ::SetTextColor(m_hAttribDC, crColor);
	}
	return crRetVal;
}

inline
bool CGraphicsContext::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetColorAdjustment(m_hAttribDC, lpColorAdjust)? true : false;
#else
	return false;
#endif
}

inline
bool CGraphicsContext::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	bool bResult = false;
	if (m_hDC != m_hAttribDC) {
		bResult = ::SetColorAdjustment(m_hDC, lpColorAdjust)? true : false;
	}
	if (m_hAttribDC != NULL) {
		bResult = ::SetColorAdjustment(m_hAttribDC, lpColorAdjust)? true : false;
	}
	return bResult;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}


// Mapping Mode Functions

#if !defined(UNDER_CE) && (WINVER >= 0x0500)

inline
DWORD CGraphicsContext::GetLayout() const
{
	return ::GetLayout(m_hDC);
}

inline
DWORD CGraphicsContext::SetLayout(DWORD dwLayout)
{
	return ::SetLayout(m_hDC, dwLayout);
}

#endif


inline
int CGraphicsContext::GetMapMode() const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetMapMode(m_hAttribDC);
#else
	return m_nMapMode;
#endif
}

inline
CPoint CGraphicsContext::GetViewportOrg()
{
	ASSERT(m_hAttribDC);
	CPoint p;
#ifndef NONSTANDARD_GDI
	::GetViewportOrgEx(m_hAttribDC, &p);
	return p;
#else
	return m_ViewportOrg;	
#endif
}

#ifndef NONSTANDARD_GDI
inline
int CGraphicsContext::SetMapMode(int nMapMode)
{
	ASSERT(m_hDC);
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetMapMode(m_hDC, nMapMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetMapMode(m_hAttribDC, nMapMode);
	}
	return nRetVal;
}


inline
CPoint CGraphicsContext::SetViewportOrg(int x, int y)
{
	ASSERT(m_hDC);
	CPoint p;

	if (m_hDC != m_hAttribDC) {
		::SetViewportOrgEx(m_hDC, x, y, &p);
	}
	if (m_hAttribDC != NULL) {
		::SetViewportOrgEx(m_hAttribDC, x, y, &p);
	}
	return p;
}

#endif // NONSTANDARD_GDI


inline
CPoint CGraphicsContext::SetViewportOrg(POINT point)
{
	ASSERT(m_hDC);
	return SetViewportOrg(point.x,point.y);
}

#ifndef NONSTANDARD_GDI
inline
CPoint CGraphicsContext::OffsetViewportOrg(int nWidth, int nHeight)
{
	ASSERT(m_hDC);
	CPoint p;
	if (m_hDC != m_hAttribDC) {
		::OffsetViewportOrgEx(m_hDC, nWidth, nHeight, &p);
	}
	if (m_hAttribDC != NULL) {
		::OffsetViewportOrgEx(m_hAttribDC, nWidth, nHeight, &p);
	}
	return p;
}
#endif // NONSTANDARD_GDI

inline
CSize CGraphicsContext::GetViewportExt()
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	CSize s;
	::GetViewportExtEx(m_hAttribDC, &s);
	return s;
#else 
	return m_ViewportExt;
#endif
}

inline
CSize CGraphicsContext::SetViewportExt(SIZE size)
{
	ASSERT(m_hDC);
	return SetViewportExt(size.cx, size.cy);
}

#ifndef NONSTANDARD_GDI
inline
CSize CGraphicsContext::SetViewportExt(int cx, int cy)
{
	ASSERT(m_hDC);
	CSize s;
	if (m_hDC != m_hAttribDC) {
		::SetViewportExtEx(m_hDC, cx, cy, &s);
	}
	if (m_hAttribDC != NULL) {
		::SetViewportExtEx(m_hAttribDC, cx, cy, &s);
	}
	return s;
}

inline
CSize CGraphicsContext::ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom)
{
	ASSERT(m_hDC);
	CSize s;
	if (m_hDC != m_hAttribDC) {
		::ScaleViewportExtEx(m_hDC, xNum, xDenom, yNum, yDenom, &s);
	}
	if (m_hAttribDC != NULL) {
		::ScaleViewportExtEx(m_hAttribDC, xNum, xDenom, yNum, yDenom, &s);
	}
	return s;
}
#endif

inline
CPoint CGraphicsContext::GetWindowOrg()
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	CPoint p;
	::GetWindowOrgEx(m_hAttribDC, &p);
	return p;
#else // if NONSTANDARD_GDI
	return m_WindowOrg;
#endif //NONSTANDARD_GDI
}

inline
CPoint CGraphicsContext::SetWindowOrg(POINT point)
{
	ASSERT(m_hDC);
	return SetWindowOrg(point.x, point.y);
}

#ifndef NONSTANDARD_GDI

inline
CPoint CGraphicsContext::SetWindowOrg(int x, int y)
{
	ASSERT(m_hDC);
	CPoint p;
	if (m_hDC != m_hAttribDC) {
		::SetWindowOrgEx(m_hDC, x, y, &p);
	}
	if (m_hAttribDC != NULL) {
		::SetWindowOrgEx(m_hAttribDC, x, y, &p);
	}
	return p;
}

inline
CPoint CGraphicsContext::OffsetWindowOrg(int nWidth, int nHeight)
{
	ASSERT(m_hDC);
	CPoint p;
	if (m_hDC != m_hAttribDC) {
		::OffsetWindowOrgEx(m_hDC, nWidth, nHeight, &p);
	}
	if (m_hAttribDC != NULL) {
		::OffsetWindowOrgEx(m_hAttribDC, nWidth, nHeight, &p);
	}
	return p;
}

#endif //NONSTANDARD_GDI

inline
CSize CGraphicsContext::GetWindowExt()
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	CSize s;
	::GetWindowExtEx(m_hAttribDC, &s);
	return s;
#else
	return m_WindowExt;
#endif
}

inline
CSize CGraphicsContext::SetWindowExt(SIZE size)
{
	ASSERT(m_hDC);
	return SetWindowExt(size.cx, size.cy);
}

#ifndef NONSTANDARD_GDI

inline
CSize CGraphicsContext::SetWindowExt(int cx, int cy)
{
	ASSERT(m_hDC);
	CSize s;
	if (m_hDC != m_hAttribDC) {
		::SetWindowExtEx(m_hDC, cx, cy, &s);
	}
	if (m_hAttribDC != NULL) {
		::SetWindowExtEx(m_hAttribDC, cx, cy, &s);
	}
	return s;
}

inline
CSize CGraphicsContext::ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom)
{
	ASSERT(m_hDC);
	CSize s;
	if (m_hDC != m_hAttribDC) {
		::ScaleWindowExtEx(m_hDC, xNum, xDenom, yNum, yDenom, &s);
	}
	if (m_hAttribDC != NULL) {
		::ScaleWindowExtEx(m_hAttribDC, xNum, xDenom, yNum, yDenom, &s);
	}
	return s;
}

#endif //NONSTANDARD_GDI



// Coordinate Space Functions

const int HIMETRIC_INCH = 2540;    // HIMETRIC units per inch

#ifndef NONSTANDARD_GDI
inline
void CGraphicsContext::DPtoLP(LPPOINT lpPoints, int nCount) const
{
	ASSERT(m_hAttribDC);
	::DPtoLP(m_hAttribDC, lpPoints, nCount);
}
#endif //NONSTANDARD_GDI

inline
void CGraphicsContext::DPtoLP(LPRECT lpRect) const
{
	DPtoLP((LPPOINT)lpRect,2);
}

inline
void CGraphicsContext::DPtoLP(LPSIZE lpSize) const
{
	CSize sizeWinExt = const_cast<CGraphicsContext*>(this)->GetWindowExt();
	CSize sizeVpExt = const_cast<CGraphicsContext*>(this)->GetViewportExt();
	lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
	lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
}

#ifndef NONSTANDARD_GDI
inline
void CGraphicsContext::LPtoDP(LPPOINT lpPoints, int nCount) const
{
	ASSERT(m_hAttribDC);
	::LPtoDP(m_hAttribDC, lpPoints, nCount);
}
#endif //NONSTANDARD_GDI

inline
void CGraphicsContext::LPtoDP(LPRECT lpRect) const
{
	LPtoDP(reinterpret_cast<LPPOINT>(lpRect), 2);
}

inline
void CGraphicsContext::LPtoDP(LPSIZE lpSize) const
{
	CSize sizeWinExt = const_cast<CGraphicsContext*>(this)->GetWindowExt();
	CSize sizeVpExt = const_cast<CGraphicsContext*>(this)->GetViewportExt();
	lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
	lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
}


inline
void CGraphicsContext::DPtoHIMETRIC(LPSIZE lpSize) const
{
	ASSERT(m_hDC);

	int nMapMode = GetMapMode();
	if (nMapMode < MM_ISOTROPIC && nMapMode != MM_TEXT) {
		// when using a constrained map mode, map against physical inch
		::SetMapMode(m_hDC, MM_HIMETRIC);
		DPtoLP(lpSize);
		::SetMapMode(m_hDC, nMapMode);
	}
	else {
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps(LOGPIXELSX);
		cyPerInch = GetDeviceCaps(LOGPIXELSY);
		ASSERT(cxPerInch != 0 && cyPerInch != 0);
		lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
		lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
	}
}

inline
void CGraphicsContext::LPtoHIMETRIC(LPSIZE lpSize) const
{
	LPtoDP(lpSize);
	DPtoHIMETRIC(lpSize);
}


inline
void CGraphicsContext::HIMETRICtoDP(LPSIZE lpSize) const
{
#ifndef NONSTANDARD_GDI
	ASSERT(m_hDC);

	int nMapMode = GetMapMode();
	if (nMapMode < MM_ISOTROPIC && nMapMode != MM_TEXT)	{
		// when using a constrained map mode, map against physical inch
		::SetMapMode(m_hDC, MM_HIMETRIC);
		LPtoDP(lpSize);
		::SetMapMode(m_hDC, nMapMode);
	}
	else {
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps(LOGPIXELSX);
		cyPerInch = GetDeviceCaps(LOGPIXELSY);
		ASSERT(cxPerInch != 0 && cyPerInch != 0);
		lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
		lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
	}
#else // if NONSTANDARD_GDI
#endif //NONSTANDARD_GDI
}

inline
void CGraphicsContext::HIMETRICtoLP(LPSIZE lpSize) const
{
	HIMETRICtoDP(lpSize);
	DPtoLP(lpSize);
}



// Region Functions


inline
bool CGraphicsContext::FillRgn(CGDIRgn& aRgn, CGDIBrush& aBrush)
{
	ASSERT(m_hDC);
	return ::FillRgn(m_hDC, aRgn, aBrush)? true : false;
}

inline
bool CGraphicsContext::FrameRgn(CGDIRgn& aRgn, CGDIBrush& aBrush, int nWidth, int nHeight)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::FrameRgn(m_hDC, aRgn, aBrush, nWidth, nHeight)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::InvertRgn(CGDIRgn& aRgn)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::InvertRgn(m_hDC, aRgn)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PaintRgn(CGDIRgn& aRgn)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PaintRgn(m_hDC, aRgn)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}



// Clipping Functions

inline
int CGraphicsContext::GetClipBox(LPRECT lpRect) const
{
	ASSERT(m_hDC);
	return ::GetClipBox(m_hDC, lpRect);
}

inline
bool CGraphicsContext::PtVisible(int x, int y) const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PtVisible(m_hDC, x, y)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PtVisible(POINT point) const
{
	return PtVisible(point.x, point.y);
}

inline
bool CGraphicsContext::RectVisible(LPCRECT lpRect) const
{
	ASSERT(m_hDC);
	return ::RectVisible(m_hDC, lpRect)? true : false;
}

inline
int CGraphicsContext::SelectClipRgn(CGDIRgn& aRgn)
{
	ASSERT(m_hDC);
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SelectClipRgn(m_hDC, aRgn);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SelectClipRgn(m_hAttribDC, aRgn);
	}
	return nRetVal;
}

inline
int CGraphicsContext::SelectClipRgn(CGDIRgn* pRgn)
{
	return SelectClipRgn(*pRgn);
}

inline
int CGraphicsContext::SelectClipRgn(CGDIRgn& aRgn, int nMode)
{
	ASSERT(m_hDC);
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::ExtSelectClipRgn(m_hDC, aRgn, nMode);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::ExtSelectClipRgn(m_hAttribDC, aRgn, nMode);
	}
	return nRetVal;
}

inline
int CGraphicsContext::SelectClipRgn(CGDIRgn* pRgn, int nMode)
{
	return SelectClipRgn(*pRgn, nMode);
}

inline
int CGraphicsContext::ClearClipRgn()
{
	ASSERT(m_hDC);
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SelectClipRgn(m_hDC, NULL);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SelectClipRgn(m_hAttribDC, NULL);
	}
	return nRetVal;
}

inline
int CGraphicsContext::ExcludeClipRect(int x1, int y1, int x2, int y2)
{
	ASSERT(m_hDC);
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::ExcludeClipRect(m_hDC, x1, y1, x2, y2);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::ExcludeClipRect(m_hAttribDC, x1, y1, x2, y2);
	}
	return nRetVal;
}

inline
int CGraphicsContext::ExcludeClipRect(LPCRECT lpRect)
{
	ASSERT(lpRect);
	return ExcludeClipRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
}

inline
int CGraphicsContext::ExcludeUpdateRgn(HWND hWnd)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::ExcludeUpdateRgn(m_hDC, hWnd);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::IntersectClipRect(int x1, int y1, int x2, int y2)
{
	ASSERT(m_hDC);
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::IntersectClipRect(m_hDC, x1, y1, x2, y2);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::IntersectClipRect(m_hAttribDC, x1, y1, x2, y2);
	}
	return nRetVal;
}

inline
int CGraphicsContext::IntersectClipRect(LPCRECT lpRect)
{
	ASSERT(lpRect);
	return IntersectClipRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
}

inline
int CGraphicsContext::OffsetClipRgn(int x, int y)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::OffsetClipRgn(m_hDC, x, y);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::OffsetClipRgn(m_hAttribDC, x, y);
	}
	return nRetVal;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::OffsetClipRgn(SIZE size)
{
	return OffsetClipRgn(size.cx, size.cy);
}



// Line-Output Functions


inline
CPoint CGraphicsContext::GetCurrentPosition() const
{
	return m_CurrentPosition;
}

inline
CPoint CGraphicsContext::MoveTo(int x, int y)
{
	ASSERT(m_hDC);
	CPoint p;

	m_CurrentPosition = CPoint(x, y);
#ifndef NONSTANDARD_GDI
	if (m_hDC != m_hAttribDC) {
		::MoveToEx(m_hDC, x, y, &p);
	}
	if (m_hAttribDC != NULL) {
		::MoveToEx(m_hAttribDC, x, y, &p);
	}
#else // if NONSTANDARD_GDI
	p = m_CurrentPosition;
#endif //NONSTANDARD_GDI
	return p;
}

inline
CPoint CGraphicsContext::MoveTo(POINT point)
{
	return MoveTo(point.x, point.y);
}


#ifndef NONSTANDARD_GDI

inline
bool CGraphicsContext::LineTo(int x, int y)
{
	ASSERT(m_hDC);
	m_CurrentPosition = CPoint(x, y);
	if (m_hAttribDC != NULL && m_hDC != m_hAttribDC) {
		::MoveToEx(m_hAttribDC, x, y, NULL);
	}
	return ::LineTo(m_hDC, x, y)? true : false;
}

inline
bool CGraphicsContext::LineTo(POINT point)
{
	return LineTo(point.x,point.y);
}

inline
bool CGraphicsContext::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	ASSERT(m_hDC);
	return ::Arc(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4)? true : false;
}

inline
bool CGraphicsContext::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	ASSERT(m_hDC);
	bool bResult = ::ArcTo(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4)? true : false;
	if (m_hDC != m_hAttribDC) {
		CPoint pt;
		::GetCurrentPositionEx(m_hDC, &pt);
		::MoveToEx(m_hAttribDC, pt.x, pt.y, NULL);
	}
	return bResult;
}

inline
bool CGraphicsContext::AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
{
	ASSERT(m_hDC);
	return ::AngleArc(m_hDC, x, y, nRadius, fStartAngle, fSweepAngle)? true : false;
}

#endif	// NONSTANDARD_GDI

inline
bool CGraphicsContext::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
{
	return Arc(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline
bool CGraphicsContext::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
{
	return ArcTo(lpRect->left,lpRect->top,lpRect->right,lpRect->bottom,ptStart.x,ptStart.y,ptEnd.x,ptEnd.y);
}

inline
bool CGraphicsContext::Polyline(LPPOINT lpPoints, int nCount)
{
	ASSERT(m_hDC);
	LPPOINT pPoints;
#ifdef UNDER_CE
	pPoints = new CPoint[nCount];
	memcpy(pPoints, lpPoints, nCount*sizeof(CPoint));
	LPtoDP(pPoints, nCount);
#else
	pPoints = lpPoints;
#endif

	bool rv = ::Polyline(m_hDC, pPoints, nCount)? true : false;

#ifdef UNDER_CE
	delete [] pPoints;
#endif

	return rv;
}

inline
int CGraphicsContext::GetArcDirection() const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetArcDirection(m_hAttribDC);
#else // if NONSTANDARD_GDI
	return m_bArcDirection ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::SetArcDirection(int nArcDirection)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nResult = 0;
	if (m_hDC != m_hAttribDC) {
		nResult = ::SetArcDirection(m_hDC, nArcDirection);
	}
	if (m_hAttribDC != NULL) {
		nResult = ::SetArcDirection(m_hAttribDC, nArcDirection);
	}
	return nResult;
#else // if NONSTANDARD_GDI
	bool bt = m_bArcDirection;
	m_bArcDirection = nArcDirection == AD_CLOCKWISE;
	return bt ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	bool bResult = ::PolyDraw(m_hDC, lpPoints, lpTypes, nCount)? true : false;
	if (m_hDC != m_hAttribDC) {
		CPoint pt;
		::GetCurrentPositionEx(m_hDC, &pt);
		::MoveToEx(m_hAttribDC, pt.x, pt.y, NULL);
	}
	return bResult;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PolylineTo(const POINT* lpPoints, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	bool bResult = ::PolylineTo(m_hDC, lpPoints, nCount)? true : false;
	if (m_hDC != m_hAttribDC) {
		CPoint pt;
		::GetCurrentPositionEx(m_hDC, &pt);
		::MoveToEx(m_hAttribDC, pt.x, pt.y, NULL);
	}
	return bResult;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PolyPolyline(m_hDC, lpPoints , lpPolyPoints , nCount)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PolyBezier(const POINT* lpPoints, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PolyBezier(m_hDC,lpPoints,nCount)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PolyBezierTo(const POINT* lpPoints, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	bool bResult = ::PolyBezierTo(m_hDC, lpPoints, nCount)? true : false;
	if (m_hDC != m_hAttribDC) {
		CPoint pt;
		::GetCurrentPositionEx(m_hDC, &pt);
		::MoveToEx(m_hAttribDC, pt.x, pt.y, NULL);
	}
	return bResult;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}



// Simple Drawing Functions


inline
void CGraphicsContext::FillRect(LPCRECT lpRect, CGDIBrush* pBrush)
{
	ASSERT(m_hDC);
	ASSERT(static_cast<HBRUSH>(*pBrush));
	::FillRect(m_hDC, lpRect, *pBrush);
}

inline
void CGraphicsContext::FrameRect(LPCRECT lpRect, CGDIBrush* pBrush)
{
	ASSERT(m_hDC);
	ASSERT(static_cast<HBRUSH>(*pBrush));
#ifndef NONSTANDARD_GDI
	::FrameRect(m_hDC, lpRect, *pBrush);
#endif
}

inline
void CGraphicsContext::InvertRect(LPCRECT lpRect)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	::InvertRect(m_hDC, lpRect);
#else // if NONSTANDARD_GDI
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::DrawIcon(int x, int y, HICON hIcon)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawIcon(m_hDC,x, y, hIcon)? true : false;
#else
	return false;
#endif
}

inline
bool CGraphicsContext::DrawIcon(POINT point, HICON hIcon)
{
	return DrawIcon(point.x, point.y, hIcon);
}


#ifndef UNDER_CE

inline
bool CGraphicsContext::DrawState(CPoint pt, CSize size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawState(m_hDC, hBrush,NULL, reinterpret_cast<LPARAM>(hBitmap), 0, 
		pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::DrawState(CPoint pt, CSize size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawState(m_hDC, hBrush, NULL, reinterpret_cast<LPARAM>(hIcon), 0, 
		pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::DrawState(CPoint pt, CSize size, LPCTSTR lpszText, UINT nFlags,bool bPrefixText, int nTextLen, HBRUSH hBrush)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawState(m_hDC, hBrush, NULL, reinterpret_cast<LPARAM>(lpszText), (WPARAM)nTextLen, 
		pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT))? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::DrawState(CPoint pt, CSize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawState(m_hDC, hBrush, lpDrawProc, lData, 0, 
		pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

#endif //UNDER_CE



// Ellipse and Polygon Functions

#ifndef NONSTANDARD_GDI

inline
bool CGraphicsContext::Chord(int x1, int y1, int x2, int y2, int x3, int y3,int x4, int y4)
{
	ASSERT(m_hDC);
	return ::Chord(m_hDC,x1, y1, x2, y2, x3, y3,x4, y4)? true : false;
}

#endif //NONSTANDARD_GDI


inline
bool CGraphicsContext::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
{
	return Chord(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline
void CGraphicsContext::DrawFocusRect(LPCRECT lpRect)
{
	ASSERT(m_hDC);
	::DrawFocusRect(m_hDC, lpRect);
}

inline
bool CGraphicsContext::Ellipse(int x1, int y1, int x2, int y2)
{
	ASSERT(m_hDC);
	return ::Ellipse(m_hDC, x1, y1, x2, y2)? true : false;
}

inline
bool CGraphicsContext::Ellipse(LPCRECT lpRect)
{
	return Ellipse(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
}

inline
bool CGraphicsContext::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::Pie(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
{
	return Pie(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline
bool CGraphicsContext::Polygon(LPPOINT lpPoints, int nCount)
{
	ASSERT(m_hDC);
	return ::Polygon(m_hDC, lpPoints, nCount)? true : false;
}

inline
bool CGraphicsContext::PolyPolygon(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PolyPolygon(m_hDC, lpPoints, lpPolyCounts, nCount)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::Rectangle(int x1, int y1, int x2, int y2)
{
	ASSERT(m_hDC);
#ifndef UNDER_CE
	return ::Rectangle(m_hDC,x1, y1, x2, y2)? true : false;
#else
	CPoint p[2];
	p[0].x=x1;
	p[0].y=y1;
	p[1].x=x2;
	p[1].y=y2;
	LPtoDP(p,2);
	return ::Rectangle(m_hDC, p[0].x, p[0].y, p[1].x, p[1].y)? true : false;
#endif
}

inline
bool CGraphicsContext::Rectangle(LPCRECT lpRect)
{
	return Rectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
}

inline
bool CGraphicsContext::RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
{
	ASSERT(m_hDC);
	return ::RoundRect(m_hDC, x1, y1, x2, y2, x3, y3)? true : false;
}

inline
bool CGraphicsContext::RoundRect(LPCRECT lpRect, POINT point)
{
	return RoundRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom,point.x, point.y);
}



// Bitmap Functions


inline
bool CGraphicsContext::PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::PatBlt(m_hDC, x, y, nWidth, nHeight, dwRop)? true : false;
}

inline
bool CGraphicsContext::PatBlt(CRect rc, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::PatBlt(m_hDC, rc.left, rc.top, rc.Width(), rc.Height(), dwRop)? true : false;
}

inline
bool CGraphicsContext::BitBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::BitBlt(m_hDC, x, y, nWidth, nHeight, aSrcGC, xSrc, ySrc, dwRop)? true : false;
}

inline
bool CGraphicsContext::BitBlt(CRect rcDst, CGraphicsContext& aSrcGC, CPoint ptSrc, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::BitBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), aSrcGC, ptSrc.x, ptSrc.y, dwRop)? true : false;
}

inline
bool CGraphicsContext::StretchBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::StretchBlt(m_hDC, x, y, nWidth, nHeight, aSrcGC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop)? true : false;
}

inline
bool CGraphicsContext::StretchBlt(CRect rcDst, CGraphicsContext& aSrcGC, CRect rcSrc, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::StretchBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), aSrcGC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), dwRop)? true : false;
}

#if(WINVER >= 0x0500)
inline
bool CGraphicsContext::TransparentBlt(int nXOriginDst, int nYOriginDst, int nWidthDst, int hHeightDst, CGraphicsContext& aSrcGC, 
		int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	ASSERT(m_hDC);
	return ::TransparentBlt(m_hDC, nXOriginDst, nYOriginDst, nWidthDst, hHeightDst, aSrcGC, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent)? true : false;
}

inline
bool CGraphicsContext::TransparentBlt(CRect rcDst, CGraphicsContext& aSrcGC, CRect rcSrc, UINT crTransparent)
{
	ASSERT(m_hDC);
	return ::TransparentBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), aSrcGC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), crTransparent)? true : false;
}
#endif // WINVER >= 0x0500

inline
bool CGraphicsContext::MaskBlt(int x, int y, int nWidth, int nHeight, CGraphicsContext& aSrcGC, int xSrc, int ySrc, CGDIBitmap& aBmpMask, int xMask, int yMask, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::MaskBlt(m_hDC, x, y, nWidth, nHeight, aSrcGC, xSrc,  ySrc, aBmpMask, xMask, yMask, dwRop)? true : false;
}

inline
bool CGraphicsContext::MaskBlt(CRect rcDst, CGraphicsContext& aSrcGC, CPoint ptSrc, CGDIBitmap& aBmpMask, CPoint ptMaskOffset, DWORD dwRop)
{
	ASSERT(m_hDC);
	return ::MaskBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), aSrcGC, ptSrc.x, ptSrc.y, aBmpMask, ptMaskOffset.x, ptMaskOffset.y, dwRop)? true : false;
}

inline
bool CGraphicsContext::PlgBlt(LPPOINT lpPoint, CGraphicsContext& aSrcGC, int xSrc, int ySrc, int nWidth, int nHeight, CGDIBitmap& aBmpMask, int xMask, int yMask)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PlgBlt(m_hDC, lpPoint, aSrcGC, xSrc, ySrc, nWidth, nHeight, aBmpMask, xMask, yMask)? true : false;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
COLORREF CGraphicsContext::GetPixel(int x, int y) const
{
	ASSERT(m_hDC);
	return ::GetPixel(m_hDC, x, y);
}

inline
COLORREF CGraphicsContext::GetPixel(POINT point) const
{
	return GetPixel(point.x, point.y);
}

inline
COLORREF CGraphicsContext::SetPixel(int x, int y, COLORREF crColor)
{
	ASSERT(m_hDC);
	return ::SetPixel(m_hDC, x, y, crColor);
}

inline
COLORREF CGraphicsContext::SetPixel(POINT point, COLORREF crColor)
{
	return SetPixel(point.x, point.y, crColor);
}

inline
bool CGraphicsContext::FloodFill(int x, int y, COLORREF crColor)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::FloodFill(m_hDC,x, y, crColor)? true : false;
#else // if NONSTANDARD_GDI
	CPoint p(x, y);
	LPtoDP(&p);
	return ExtFloodFill(p.x, p.y, crColor, FLOODFILLBORDER);
#endif //NONSTANDARD_GDI
}

#ifndef NONSTANDARD_GDI

inline
bool CGraphicsContext::ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
{
	ASSERT(m_hDC);
	return ::ExtFloodFill(m_hDC, x, y, crColor, nFillType)? true : false;
}

#endif

inline
bool CGraphicsContext::SetPixelV(int x, int y, COLORREF crColor)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::SetPixelV(m_hDC, x, y, crColor)? true : false;
#else // if NONSTANDARD_GDI
	return ::SetPixel(m_hDC, x, y, crColor)? true : false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::SetPixelV(POINT point, COLORREF crColor)
{
	ASSERT(m_hDC);
	return SetPixel(point.x, point.y, crColor)? true : false;
}



// Text Functions


inline
bool CGraphicsContext::TextOut(int x, int y, LPCTSTR lpszString, int nCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::TextOut(m_hDC, x, y, lpszString, nCount)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths)
{
	ASSERT(m_hDC);
	return ::ExtTextOut(m_hDC,x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths)? true : false;
}

inline
CSize CGraphicsContext::TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::TabbedTextOut(m_hDC, x, y, lpszString, nCount,nTabPositions, lpnTabStopPositions, nTabOrigin);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::DrawText(LPCTSTR lpszString, int nCount, LPRECT lpRect,UINT nFormat)
{
	ASSERT(m_hDC);
	return ::DrawText(m_hDC,lpszString, nCount, lpRect, nFormat);
}

inline
int CGraphicsContext::DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
{
	ASSERT(m_hDC);
	return ::DrawTextEx(m_hDC, lpszString, nCount, lpRect, nFormat, lpDTParams);
}

inline
CSize CGraphicsContext::GetTextExtent(LPCTSTR lpszString, int nCount) const
{
	ASSERT(m_hAttribDC);
	CSize s;
	::GetTextExtentPoint32(m_hAttribDC, lpszString, nCount, &s);
	return s;
}

inline
CSize CGraphicsContext::GetOutputTextExtent(LPCTSTR lpszString, int nCount) const
{
	ASSERT(m_hDC);
	CSize s;
	::GetTextExtentPoint32(m_hDC, lpszString, nCount, &s);
	return s;
}

inline
CSize CGraphicsContext::GetTabbedTextExtent(LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetTabbedTextExtent(m_hAttribDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
CSize CGraphicsContext::GetOutputTabbedTextExtent(LPCTSTR lpszString, int nCount,int nTabPositions, LPINT lpnTabStopPositions) const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetTabbedTextExtent(m_hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::GrayString(CGDIBrush& aBrush, BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData,int nCount, int x, int y, int nWidth, int nHeight)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GrayString(m_hDC, aBrush, lpfnOutput, lpData, nCount, x, y, nWidth, nHeight)? true : false;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
UINT CGraphicsContext::GetTextAlign() const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetTextAlign(m_hAttribDC);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
UINT CGraphicsContext::SetTextAlign(UINT nFlags)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	UINT nRetVal = GDI_ERROR;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetTextAlign(m_hDC, nFlags);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetTextAlign(m_hAttribDC, nFlags);
	}
	return nRetVal;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::GetTextFace(int nCount, LPTSTR lpszFacename) const
{
	ASSERT(m_hAttribDC);
	return ::GetTextFace(m_hAttribDC, nCount, lpszFacename);
}

inline
bool CGraphicsContext::GetTextMetrics(LPTEXTMETRIC lpMetrics) const
{
	ASSERT(m_hAttribDC);
	return ::GetTextMetrics(m_hAttribDC, lpMetrics)? true : false;
}

inline
bool CGraphicsContext::GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const
{
	ASSERT(m_hDC);
	return ::GetTextMetrics(m_hDC, lpMetrics)? true : false;
}

inline
int CGraphicsContext::SetTextJustification(int nBreakExtra, int nBreakCount)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = 0;

	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetTextJustification(m_hDC, nBreakExtra, nBreakCount);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetTextJustification(m_hAttribDC, nBreakExtra, nBreakCount);
	}
	return nRetVal;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::GetTextCharacterExtra() const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetTextCharacterExtra(m_hAttribDC);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::SetTextCharacterExtra(int nCharExtra)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	int nRetVal = 0x8000000;
	if (m_hDC != m_hAttribDC) {
		nRetVal = ::SetTextCharacterExtra(m_hDC, nCharExtra);
	}
	if (m_hAttribDC != NULL) {
		nRetVal = ::SetTextCharacterExtra(m_hAttribDC, nCharExtra);
	}
	return nRetVal;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}



// Advanced Drawing

inline
bool CGraphicsContext::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
{
	ASSERT(m_hDC);
	return ::DrawEdge(m_hDC, lpRect, nEdge, nFlags)? true : false;
}

inline
bool CGraphicsContext::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
{
	ASSERT(m_hDC);
	return ::DrawFrameControl(m_hDC, lpRect, nType, nState)? true : false;
}



// Scrolling Functions


inline
bool CGraphicsContext::ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, CGDIRgn& aRgnUpdate, LPRECT lpRectUpdate)
{
	ASSERT(m_hDC);
	return ::ScrollDC(m_hDC, dx, dy, lpRectScroll, lpRectClip, aRgnUpdate, lpRectUpdate)? true : false;
}



// Font Functions


inline
bool CGraphicsContext::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetCharWidth(m_hAttribDC, nFirstChar, nLastChar, lpBuffer)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetCharWidth(m_hDC, nFirstChar, nLastChar, lpBuffer)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
DWORD CGraphicsContext::SetMapperFlags(DWORD dwFlag)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	DWORD dwRetVal = GDI_ERROR;
	if (m_hDC != m_hAttribDC) {
		dwRetVal = ::SetMapperFlags(m_hDC, dwFlag);
	}
	if (m_hAttribDC != NULL) {
		dwRetVal = ::SetMapperFlags(m_hAttribDC, dwFlag);
	}
	return dwRetVal;
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
CSize CGraphicsContext::GetAspectRatioFilter() const
{
	ASSERT(m_hAttribDC);
	CSize s;
#ifndef NONSTANDARD_GDI
	::GetAspectRatioFilterEx(m_hAttribDC, &s);
#endif //NONSTANDARD_GDI
	return s;
}

inline
bool CGraphicsContext::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetCharABCWidths(m_hAttribDC, nFirstChar, nLastChar, lpabc)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
DWORD CGraphicsContext::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetFontData(m_hAttribDC, dwTable, dwOffset, lpData, cbData);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetKerningPairs(m_hAttribDC, nPairs, lpkrnpair);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
UINT CGraphicsContext::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetOutlineTextMetrics(m_hAttribDC, cbData, lpotm);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
DWORD CGraphicsContext::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetGlyphOutline(m_hAttribDC, nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::GetCharABCWidths(UINT nFirstChar, UINT nLastChar,LPABCFLOAT lpABCF) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetCharABCWidthsFloat(m_hAttribDC, nFirstChar, nLastChar, lpABCF)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::GetCharWidth(UINT nFirstChar, UINT nLastChar,float* lpFloatBuffer) const
{
	ASSERT(m_hAttribDC);
#ifndef NONSTANDARD_GDI
	return ::GetCharWidthFloat(m_hAttribDC, nFirstChar, nLastChar, lpFloatBuffer)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}



// Printer/Device Escape Functions


inline
int CGraphicsContext::Escape(int nEscape, int nCount, LPCSTR lpszInData, LPVOID lpOutData)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::Escape(m_hDC, nEscape, nCount, lpszInData, lpOutData);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::Escape(int nEscape, int nInputSize, LPCSTR lpszInputData,int nOutputSize, LPSTR lpszOutputData)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::ExtEscape(m_hDC, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::DrawEscape(int nEscape, int nInputSize, LPCSTR lpszInputData)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::DrawEscape(m_hDC, nEscape, nInputSize, lpszInputData);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::StartDoc(LPCTSTR lpszDocName)
{
	DOCINFO di;
	memset(&di, 0, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = lpszDocName;
	return StartDoc(&di);
}

inline
int CGraphicsContext::StartDoc(LPDOCINFO lpDocInfo)
{
	ASSERT(m_hDC);
	return ::StartDoc(m_hDC, lpDocInfo);
}

inline
int CGraphicsContext::StartPage()
{
	ASSERT(m_hDC);
	return ::StartPage(m_hDC);
}

inline
int CGraphicsContext::EndPage()
{
	ASSERT(m_hDC);
	return ::EndPage(m_hDC);
}

inline
int CGraphicsContext::SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, int))
{
	ASSERT(m_hDC);
#ifndef UNDER_CE
	return ::SetAbortProc(m_hDC, lpfn);
#else // if UNDER_CE
	return 0; 
#endif //UNDER_CE
}

inline
int CGraphicsContext::AbortDoc()
{
	ASSERT(m_hDC);
#ifndef UNDER_CE
	return ::AbortDoc(m_hDC);
#else // if UNDER_CE
	return 0;
#endif //UNDER_CE
}

inline
int CGraphicsContext::EndDoc()
{
	ASSERT(m_hDC);
	return ::EndDoc(m_hDC);
}



// MetaFile Functions


inline
bool CGraphicsContext::PlayMetaFile(HMETAFILE hMF)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PlayMetaFile(m_hDC, hMF)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::PlayEnhMetaFile(m_hDC, hEnhMetaFile, lpBounds)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GdiComment(m_hDC, nDataSize, pCommentData)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}



// Path Functions


inline
bool CGraphicsContext::AbortPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::AbortPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::BeginPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::BeginPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	m_bInPath = true;
	m_Path.clear();
	return true;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::CloseFigure()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::CloseFigure(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	m_Path.push_back(*m_Path.begin());
	return true;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::EndPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::EndPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	m_bInPath = false;
	return true;
#endif //NONSTANDARD_GDI
}

#ifndef NONSTANDARD_GDI
inline
bool CGraphicsContext::FillPath()
{
	ASSERT(m_hDC);
	return ::FillPath(m_hDC)? true : false;
}
#endif

inline
bool CGraphicsContext::FlattenPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::FlattenPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::StrokeAndFillPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::StrokeAndFillPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::StrokePath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::StrokePath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::WidenPath()
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::WidenPath(m_hDC)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
float CGraphicsContext::GetMiterLimit() const
{
	ASSERT(m_hDC);
	float f;
#ifndef NONSTANDARD_GDI
	::GetMiterLimit(m_hDC, &f);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
	return f;
}

inline
bool CGraphicsContext::SetMiterLimit(float fMiterLimit)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	float f;
	return ::SetMiterLimit(m_hDC, fMiterLimit, &f)? true : false;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}

inline
int CGraphicsContext::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	return ::GetPath(m_hDC,lpPoints, lpTypes, nCount);
#else // if NONSTANDARD_GDI
	return 0;
#endif //NONSTANDARD_GDI
}

inline
bool CGraphicsContext::SelectClipPath(int nMode)
{
	ASSERT(m_hDC);
#ifndef NONSTANDARD_GDI
	// output DC always holds the current path
	if (!::SelectClipPath(m_hDC, nMode)) return false;

	// transfer clipping region into the attribute DC
	bool bResult = true;
	if (m_hDC != m_hAttribDC) {
		HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
		if (::GetClipRgn(m_hDC, hRgn) < 0 || !::SelectClipRgn(m_hAttribDC, hRgn)) {
			bResult = false;
		}
		::DeleteObject(hRgn);
	}
	return bResult;
#else // if NONSTANDARD_GDI
	return false;
#endif //NONSTANDARD_GDI
}



/////////////////////////////////////////////////////////////////////
// CGraphicsContext derived classes: creation-destruction mechanisms


//@class CPaintGraphicsContext |
//  Device context for a window's invalid region. 
//@base public | CGraphicsContext
//@comm
// The CPaintGraphicsContext class uses the function pair BeginPaint()/EndPaint()
// to allocate a device context which is only valid during the processing of the
// WM_PAINT message.<nl>
// The DC is automatically initialized to have its clipping region equal to the
// invalid region of the window.
class CPaintGraphicsContext : public CGraphicsContext
{
public:

	//@cmember,mfunc | CPaintGraphicsContext | ([HDC h]) |
	// Attach constructor. Attaches the given DC handle to this instance.
	//@@parm HDC | h | Device context.
	//@@comm
	//  The device context passed in must have been created using the BeginPaint()
	//  API function; otherwise the deallocation process will have undefined 
	//  results as it will try to invoke EndPaint() on a DC handle that wasn't
	//  created appropiately for such function.
	CPaintGraphicsContext(HDC h = NULL): CGraphicsContext(h), m_hWnd(NULL)
	{}

	//@cmember,mfunc | CPaintGraphicsContext | (HWND hWnd) |
	// Creates a new paint DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	CPaintGraphicsContext(HWND hWnd)
	{
		Create(hWnd);
	}

	~CPaintGraphicsContext()
	{
		Delete();
	}

public:

	//@cmember,mfunc void | Create | (HWND hWnd) |
	// Creates a new paint DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	void Create(HWND hWnd)
	{
		Attach(::BeginPaint((m_hWnd = hWnd), &m_ps));
	}

	virtual bool ReleaseHandle()
	{
		::EndPaint(m_hWnd, &m_ps);
		m_hWnd = NULL;
		return true;
	}

protected:
	HWND m_hWnd;
	PAINTSTRUCT m_ps;
};


class CWindowGraphicsContextBase : public CGraphicsContext
{
public:
	CWindowGraphicsContextBase(HDC h = NULL): CGraphicsContext(h), m_hWnd(NULL)
	{}

	~CWindowGraphicsContextBase()
	{
		Delete();
	}

public:

	virtual bool ReleaseHandle()
	{
		int nRes = ::ReleaseDC(m_hWnd, m_hDC);
		m_hWnd = NULL;
		return nRes != 0;
	}

protected:
	HWND m_hWnd;
};


//@class CWindowGraphicsContext |
// Device context for the entire window.
//@base public | CWindowGraphicsContextBase
//@comm
// The API functions GetWindowDC()/ReleaseDC() are used to allocate
// a DC for the entire window area, including the non-client area.
class CWindowGraphicsContext : public CWindowGraphicsContextBase
{
public:
	//@cmember,mfunc | CWindowGraphicsContext | ([HDC h]) |
	// Attach constructor. Attaches the given DC handle to this instance.
	//@@parm HDC | h | Device context.
	//@@comm
	//  The device context passed in must have been created using the GetWindowDC
	//  API function; otherwise the deallocation process will have undefined 
	//  results as it will try to invoke ReleaseDC() on a DC handle that wasn't
	//  created appropiately for such function.
	CWindowGraphicsContext(HDC h = NULL): CWindowGraphicsContextBase(h)
	{}

	//@cmember,mfunc | CWindowGraphicsContext | (HWND hWnd) |
	// Creates a new window DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	CWindowGraphicsContext(HWND hWnd)
	{
		Create(hWnd);
	}

public:

	//@cmember,mfunc void | Create | (HWND hWnd) |
	// Creates a new window DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	void Create(HWND hWnd)
	{
		Attach(::GetWindowDC(m_hWnd = hWnd));
	}
};


//@class CWindowGraphicsContext |
// Device context for the window client area.
//@base public | CWindowGraphicsContextBase
//@comm
// The API functions GetDC()/ReleaseDC() are used to allocate
// a DC for the client area of the window.
class CClientGraphicsContext : public CWindowGraphicsContextBase
{
public:
	//@cmember,mfunc | CClientGraphicsContext | ([HDC h]) |
	// Attach constructor. Attaches the given DC handle to this instance.
	//@@parm HDC | h | Device context.
	//@@comm
	//  The device context passed in must have been created using the GetDC
	//  API function; otherwise the deallocation process will have undefined 
	//  results as it will try to invoke ReleaseDC() on a DC handle that wasn't
	//  created appropiately for such function.
	CClientGraphicsContext(HDC h = NULL): CWindowGraphicsContextBase(h)
	{}

	//@cmember,mfunc | CClientGraphicsContext | (HWND hWnd) |
	// Creates a new client DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	CClientGraphicsContext(HWND hWnd)
	{
		Create(hWnd);
	}

public:

	//@cmember,mfunc void | Create | (HWND hWnd) |
	// Creates a new client DC on the given window and attaches it to this instance.
	//@@parm HWND | hWnd | Target window for the DC.
	void Create(HWND hWnd)
	{
		Attach(::GetDC(m_hWnd = hWnd));
	}

};


//@class CDeviceGraphicsContext |
// Device context for a specific device.
//@base public | CGraphicsContext
//@comm
// A DC associated to the device and the device driver specified
// is created using the CreateDC() API function.
class CDeviceGraphicsContext: public CGraphicsContext
{
public:
	//@cmember,mfunc | CDeviceGraphicsContext | (HDC h) |
	// Attach constructor. Attaches the given DC handle to this instance.
	//@@parm HDC | h | Device context.
	//@@comm
	//  The device context passed in must have been created using the CreateDC
	//  API function; otherwise the deallocation process will have undefined 
	//  results as it will try to invoke DeleteDC() on a DC handle that wasn't
	//  created appropiately for such function.
	CDeviceGraphicsContext(HDC h): CGraphicsContext(h)
	{}

	//@cmember,mfunc | CDeviceGraphicsContext | (LPCTSTR lpszDriver = NULL, LPCTSTR lpszDevice = NULL, LPCTSTR lpszOutput = NULL, const DEVMODE* lpInitData = NULL) |
	// Creation constructor. Creates a new DC on the device given, and attaches it to this instance.
	CDeviceGraphicsContext(LPCTSTR lpszDriver = NULL, LPCTSTR lpszDevice = NULL, LPCTSTR lpszOutput = NULL, const DEVMODE* lpInitData = NULL)
	{
		Create(lpszDriver, lpszDevice, lpszOutput, lpInitData);
	}

	~CDeviceGraphicsContext()
	{
		Delete();
	}

public:

	//@cmember,mfunc void | Create | (LPCTSTR lpszDriver = NULL, LPCTSTR lpszDevice = NULL, LPCTSTR lpszOutput = NULL, const DEVMODE* lpInitData = NULL) |
	// Creates a new DC on the device given, and attaches it to this instance.
	void Create(LPCTSTR lpszDriver = NULL, LPCTSTR lpszDevice = NULL, LPCTSTR lpszOutput = NULL, const DEVMODE* lpInitData = NULL)
	{
		Attach(::CreateDC(lpszDriver, lpszDevice, lpszOutput, lpInitData));
	}

	virtual bool ReleaseHandle()
	{
		return ::DeleteDC(m_hDC) != 0;
	}
	
};


//@class CMemoryGraphicsContext |
// Device context on memory.
//@base public | CGraphicsContext
//@comm
// The output for a CMemoryGraphicsContext is not displayed on 
// any physical device but rather goes to a bitmap in memory.<nl>
// Use one of the Blt API functions to transfer the contents of 
// that memory bitmap to an actual output device.
class CMemoryGraphicsContext: public CGraphicsContext
{
public:

	//@cmember,mfunc | CMemoryGraphicsContext | (HDC h) |
	// Creates and initializes a compatible DC on memory.
	//@@parm HDC | h | Handle to a Device Context to be compatible with.
	//@@comm
	// Unlike the other constructors with HDC parameter, this one
	// does not attach this instance to the passed handle, 
	// but rather creates a compatible DC and associates it with
	// this object
	CMemoryGraphicsContext(HDC h)
	{
		Create(h);
	}

	~CMemoryGraphicsContext()
	{
		Delete();
	}

public:

	//@cmember,mfunc void | Create | (HDC hDCComp) |
	// Creates a DC on memory compatible with the one passed in, and 
	// attaches it to this instance.
	//@@parm HDC | h | Handle to a Device Context to be compatible with.
	void Create(HDC hDCComp)
	{
		Attach(::CreateCompatibleDC(hDCComp));
	}

	virtual bool ReleaseHandle()
	{
		return ::DeleteDC(m_hDC) != 0;
	}
};


//@class CMetafileGraphicsContext |
// device context that generates output to a metafile.
//@base public | CraphicsContext
//@comm
// Both Windows metafiles and enhanced metafiles are supported.
// The output metafile can be a real file on disk or a temporary
// metafile residing in memory.
class CMetafileGraphicsContext : public CGraphicsContext
{
public:
	//@cmember,mfunc | CMetafileGraphicsContext | () |
	// Initializes the graphics context as empty
	CMetafileGraphicsContext(): CGraphicsContext(NULL), m_bEnhanced(false) {}

public: 
	// Metafile operations

	//@cmember,mfunc bool | Create | (LPCTSTR lpszFileName = NULL) |
	// Creates a standard metafile.
	//@@rdesc true if succesfully created, otherwise false.
	bool Create (LPCTSTR lpszFileName = NULL)
	{
		Attach(::CreateMetaFile(lpszFileName));
		m_bEnhanced = false;
		return m_hDC != NULL;
	}

	//@cmember,mfunc bool | CreateEnhanced | (HDC hdcRef, LPCTSTR lpszFileName, LPCRECT prcBounds, LPCTSTR lpszDescription ) |
	// Create an enhanced metafile.
	//@@rdesc true if succesfully created, otherwise false.
	bool CreateEnhanced (HDC hdcRef, LPCTSTR lpszFileName, LPCRECT prcBounds, LPCTSTR lpszDescription )
	{
		Attach(::CreateEnhMetaFile(hdcRef, lpszFileName, prcBounds, lpszDescription)); 
		m_bEnhanced = true;
		return m_hDC != NULL;
	}

	//@cmember,mfunc bool | IsEnhanced | () | 
	// Returns whether or not the encapsulated metafile is an enhanced metafile or not.
	//@@rdesc true if the metatile is an enhanced metafile, false if it is not.
	bool IsEnhanced() const
	{
		return m_bEnhanced;
	}

	//@cmember,mfunc HMETAFILE | Close | () |
	// Close the device context associated with the contained metafile
	//@@rdesc Handle to the metafile.
	//@@comm
	//  Use only if the contained metafile is a standard Windows metafile,
	// as opposed to an enhanced metafile.
	HMETAFILE Close()
	{ 
		return ::CloseMetaFile(Detach()); 
	}

	//@cmember,mfunc HMETAFILE | CloseEnhanced | () |
	// Close the device context associated with the contained metafile
	//@@rdesc Handle to the enhanced metafile.
	//@@comm
	//  Use only if the contained metafile is an enhanced metafile,
	// as opposed to a standard Windows metafile.
	HENHMETAFILE CloseEnhanced()
	{ 
		return ::CloseEnhMetaFile(Detach()); 
	}

	virtual bool ReleaseHandle()
	{
		BOOL bResult;
		if (m_bEnhanced) {
			HENHMETAFILE hmf = ::CloseEnhMetaFile(m_hDC);
			bResult = ::DeleteEnhMetaFile(hmf);
		}
		else {
			HMETAFILE hmf = ::CloseMetaFile(m_hDC);
			bResult = ::DeleteMetaFile(hmf);
		}
		return bResult? true : false;
	}

protected:
	bool m_bEnhanced;
};

//////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Definitions for the Graphics package
////////////////////////////////////////////////////

#ifdef NONSTANDARD_GDI
#include <foundation\APIStructs\MissingStructs.h>

#define AFXAPI _cdecl 
#define AFX_CDECL AFXAPI 

#endif //NONSTANDARD_GDI

#define __STL_USE_NAMESPACES

#pragma warning(disable : 4250) 
#pragma warning(disable : 4006) 


#ifndef PI
#define PI  (double)3.14159265359
#endif

#ifndef TWO_PI
#define TWO_PI (2*PI)
#endif

#ifndef RADIANS

#define RADIANS(f) \
	((f * PI ) / 180)

#endif // RADIANS

#ifndef DEGREES

#define DEGREES(f) \
	((f * 180 )/ PI)

#endif // DEGREES

#define BRUSHSTYLE_SOLID 0

/////////////////////////////////////////////////////////////////////////////
// CGraphicsContext functions implementation

/*
This file includes mainly implementations of some common DC functions that 
do not have a corresponding in some non-Win32 platforms, particularly WinCE.
*/

#ifdef NONSTANDARD_GDI


int CGraphicsContext::SetMapMode(int nMapMode)
{
	int m = m_nMapMode;
	m_nMapMode = nMapMode;

	int nOutX = ::GetDeviceCaps(m_hDC,HORZRES);
	int nOutY = ::GetDeviceCaps(m_hDC,VERTRES);
	int nResX = ::GetDeviceCaps(m_hDC,LOGPIXELSX);
	int nResY = ::GetDeviceCaps(m_hDC,LOGPIXELSY);
#ifndef NONSTANDARD_GDI
	int nAspectX = ::GetDeviceCaps(m_hDC,XASPECT);
	int nAspectY = ::GetDeviceCaps(m_hDC,YASPECT);
#else // if NONSTANDARD_GDI
	int nAspectX = 1;
	int nAspectY = 1;
#endif //NONSTANDARD_GDI
	int nSizeOutX = ::GetDeviceCaps(m_hDC,HORZSIZE);
	int nSizeOutY = ::GetDeviceCaps(m_hDC,VERTSIZE);

	switch (m_nMapMode) {
case MM_TEXT:
case MM_ANISOTROPIC:
	m_ViewportExt = CSize(1,1);
	m_WindowExt = CSize(1,1);
	break;
case MM_HIENGLISH:
	m_WindowExt = CSize((nSizeOutX * 10000) / 254,(nSizeOutY * 10000) / 254);
	goto setviewport;
case MM_HIMETRIC:
	m_WindowExt = CSize((nSizeOutX * 100),(nSizeOutY * 100));
	goto setviewport;
case MM_ISOTROPIC:
	m_WindowExt = CSize(nSizeOutX * 10, nSizeOutY * 10);
	goto setviewport;
case MM_LOENGLISH:
	m_WindowExt = CSize((nSizeOutX * 1000) / 254,(nSizeOutY * 1000) / 254);
	goto setviewport;
case MM_LOMETRIC:
	m_WindowExt = CSize((nSizeOutX * 10),(nSizeOutY * 10));
	goto setviewport;
case MM_TWIPS:
	m_WindowExt = CSize((((nSizeOutX * 10000) / 254) * 144 ) / 100 , (((nSizeOutY * 10000) / 254) * 144 ) / 100);
setviewport:
	m_ViewportExt=CSize(nOutX,-nOutY);
	break;
	}
	return m;
}


CPoint CGraphicsContext::SetViewportOrg(int x, int y)
{
	ASSERT(m_hDC);
	CPoint p;
	p=m_ViewportOrg;
	m_ViewportOrg=CPoint(x,y);
	return p;
}


CPoint CGraphicsContext::OffsetViewportOrg(int nWidth, int nHeight)
{
	ASSERT(m_hDC);
	CPoint p;
	p = m_ViewportOrg;
	m_ViewportOrg += CPoint(nWidth, nHeight);
	return p;
}


CSize CGraphicsContext::SetViewportExt(int cx, int cy)
{
	ASSERT(m_hDC);
	CSize s;
	s=m_ViewportExt;
	if (m_nMapMode == MM_ANISOTROPIC || m_nMapMode == MM_ISOTROPIC) {
		m_ViewportExt = CSize(cx ? cx : 1,cy ? cy : 1); // dont allow zeros!
	}
	AdjustViewport();
	return s;
}


CSize CGraphicsContext::ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom)
{
	ASSERT(m_hDC);
	CSize s;
	s = m_ViewportExt;
	if (m_nMapMode == MM_ANISOTROPIC || m_nMapMode == MM_ISOTROPIC)	{
		m_ViewportExt.cx = (m_ViewportExt.cx * xNum) / xDenom;
		m_ViewportExt.cy = (m_ViewportExt.cy * yNum) / yDenom;
	}
	AdjustViewport();
	return s;
}


CPoint CGraphicsContext::SetWindowOrg(int x, int y)
{
	ASSERT(m_hDC);
	CPoint p;
	p = m_WindowOrg;
	m_WindowOrg = CPoint(x, y);
	return p;
}


CPoint CGraphicsContext::OffsetWindowOrg(int nWidth, int nHeight)
{
	ASSERT(m_hDC);
	CPoint p;
	p = m_WindowOrg;
	m_WindowOrg += CPoint(nWidth, nHeight);
	return p;
}


CSize CGraphicsContext::SetWindowExt(int cx, int cy)
{
	ASSERT(m_hDC);
	CSize s;
	s = m_WindowExt;
	if (m_nMapMode == MM_ANISOTROPIC || m_nMapMode == MM_ISOTROPIC) {
		m_WindowExt.cx = cx ? cx : 1;
		m_WindowExt.cy = cy ? cy : 1; // never allow a zero..
	}
	AdjustViewport();
	return s;
}


CSize CGraphicsContext::ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom)
{
	ASSERT(m_hDC);
	CSize s;
	s = m_WindowExt;
	if (m_nMapMode == MM_ANISOTROPIC || m_nMapMode == MM_ISOTROPIC) {
		m_WindowExt.cx = ((m_WindowExt.cx * xNum) / xDenom);
		m_WindowExt.cy = ((m_WindowExt.cy * yNum) / yDenom);
	}
	AdjustViewport();
	return s;
}



// Coordinate Space Functions


void CGraphicsContext::DPtoLP(LPPOINT lpPoints, int nCount) const
{
	ASSERT(m_hDC);
	if (m_nMapMode == MM_TEXT) return;

	for (int c=0; c < nCount; c++) {
		lpPoints[c].x = ((lpPoints[c].x = m_ViewportOrg.x) * m_WindowExt.cx / m_ViewportExt.cx ) + m_WindowOrg.x;
		lpPoints[c].y = ((lpPoints[c].y = m_ViewportOrg.y) * m_WindowExt.cy / m_ViewportExt.cy ) + m_WindowOrg.y;
	}
}


void CGraphicsContext::LPtoDP(LPPOINT lpPoints, int nCount) const
{
	ASSERT(m_hDC);
	//Dx = ((Lx - WOx) * VEx / WEx) + VOx
	for (int c = 0; c < nCount; c++) {
		lpPoints[c].x = ((lpPoints[c].x - m_WindowOrg.x) * m_ViewportExt.cx / m_WindowExt.cx ) + m_ViewportOrg.x;
		lpPoints[c].y = ((lpPoints[c].y - m_WindowOrg.y) * m_ViewportExt.cy / m_WindowExt.cy ) + m_ViewportOrg.y;
	}
}


// Drawing


inline
bool CGraphicsContext::LineTo(POINT point)
{
	ASSERT(m_hDC);
	CPoint p[2];
	p[0] = m_CurrentPosition;
	p[1] = point;
	LPtoDP(p, 2);

	if (m_bInScanPoints) {
		// Whoah Now we need a pixel for pixel line draw routine!!
		// it just stores the points really.
		int nXd = p[1].x - p[0].x;
		int nYd = p[1].y-p[0].y;
		int nXDir = nXd<0 ? -1 : 1;
		int nYDir = nYd<0 ? -1 : 1;
		nXd = abs(nXd);
		nYd = abs(nYd);
		bool bYStep = nXd>=nYd;
		int nCount =_SFLMAX(nXd,nYd);
		int nXVal, nXAcc = 0, nYVal, nYAcc = 0;

		if (bYStep) {
			nYVal = (nYd << 16) / (nXd ? nXd : 1);
			nXVal = 1 << 16;
		}
		else {
			nXVal = (nXd << 16) / (nYd ? nYd : 1);
			nYVal = 1 << 16;
		}

		for (int c = 0; c < nCount; c++) {
			nXAcc += nXVal;
			p[0].x += (nXAcc & 0x010000) ? nXDir : 0;
			nXAcc &= 0x0ffff;
			nYAcc += nYVal;
			p[0].y += (nYAcc & 0x010000) ? nYDir : 0;
			nYAcc &= 0x0ffff;
			AddScanPoint(CPoint(p[0].x + (((nXAcc & 0x0ffff)>0x08000) ? nXDir : 0), p[0].y + (((nYAcc & 0x0ffff)>0x08000) ? nYDir : 0)));
		}

		if (p[0]!=p[1]) {
			AddScanPoint(p[1]);
		}

	}
	else {
		::Polyline(m_hDC,p,2);
	}
	m_CurrentPosition = point;
	return true;
}


bool CGraphicsContext::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	ASSERT(m_hDC);
	CRect r(x1, y1, x2, y2);
	double rRatio = r.Aspect();
	CPoint ptCenter = r.CenterPoint();
	CPoint ptR1(x3 - ptCenter.x, static_cast<int>((y3-ptCenter.y)*rRatio));
	CPoint ptR2(x4 - ptCenter.x, staatic_cast<int>((y4-ptCenter.y)*rRatio));

	double a1, a2;

	a1 = GetLineAngle(CPoint(0,0), ptR1, true);
	a2 = GetLineAngle(CPoint(0,0), ptR2, true);

	CPoint lp = m_CurrentPosition;
	bool bFirst = true;

	int nR1 = r.Width() / 2;
	int nR2 = r.Height() / 2;

	if (!nR1 || !nR2) {
		return false; // error bounding box not big enough...
	}

	int nArcDirection = m_bArcDirection ? -1 : 1;

	double fStep = (double)(3 * 360 / (_SFLMAX(r.Width(),r.Height()) * PI));
	double fSRads = RADIANS(fStep) * nArcDirection;
	double fDegrees = GetAngleDifference(a1, a2);
	if (m_bArcDirection || fDegrees == 0) {
		fDegrees = 360 - fDegrees;
	}

	double dAngle = RADIANS(a1);
	for (double f = 0; f < fDegrees ; f += fStep) {
		CPoint p = ptCenter + CPoint(static_cast<int>((nR1*cos(dAngle)) + 0.5), -static_cast<int>(((nR2*sin(dAngle))+0.5)));
		if(bFirst) {
			bFirst = false;
			MoveTo(p);
		}
		else {
			LineTo(p);
		}

		dAngle += fSRads;

		if (dAngle > TWO_PI) {
			dAngle -= TWO_PI;
		}
		else if(dAngle < 0) {
			dAngle += TWO_PI;
		}

	}

	m_CurrentPosition = lp;
	return true;
}


inline
bool CGraphicsContext::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	ASSERT(m_hDC);
	CRect r(x1, y1, x2,y2);
	double rRatio = r.Aspect();
	CPoint ptCenter = r.CenterPoint();
	CPoint ptR1(x3 - ptCenter.x, static_cast<int>((y3 - ptCenter.y) * rRatio));
	CPoint ptR2(x4 - ptCenter.x, static_cast<int>((y4 - ptCenter.y) * rRatio));

	double a1, a2;

	a1 = GetLineAngle(CPoint(0,0), ptR1, true);
	a2 = GetLineAngle(CPoint(0,0), ptR2, true);

	bool bFirst = true;

	int nR1 = r.Width()/2;
	int nR2 = r.Height()/2;

	if (!nR1 || !nR2) return false; // error bounding box not big enough...

	int nArcDirection = m_bArcDirection ? -1 : 1;

	double fStep = (double)(3 * 360 / (_SFLMAX(r.Width(),r.Height()) * PI));
	double fSRads = RADIANS(fStep) * nArcDirection;
	double fDegrees = GetAngleDifference(a1,a2);
	if (m_bArcDirection || fDegrees == 0) {
		fDegrees = 360 - fDegrees;
	}

	double dAngle = RADIANS(a1);

	for (double f = 0; f < fDegrees ; f += fStep) {
		CPoint p = ptCenter + CPoint(static_cast<int>((nR1 * cos(dAngle)) + 0.5), -static_cast<int>(((nR2 * sin(dAngle)) + 0.5)));
		LineTo(p);
		dAngle += fSRads;

		if (dAngle > TWO_PI) {
			dAngle -= TWO_PI;
		}
		else if (dAngle < 0) {
			dAngle += TWO_PI;
		}

	}

	return true;
}


bool CGraphicsContext::AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
{
	ASSERT(m_hDC);
	float s = static_cast<float>(360 / (nRadius * 2 * PI));
	for (float f = fStartAngle; f < fStartAngle + fSweepAngle; f += s) {
		LineTo(CPoint(static_cast<int>(x + (nRadius * cos(RADIANS(f)))), static_cast<int>(y - (nRadius * sin(RADIANS(f))))));
	}
	return true;
}


bool CGraphicsContext::Chord(int x1, int y1, int x2, int y2, int x3, int y3,int x4, int y4)
{
	ASSERT(m_hDC);
	BeginScanPoints();

	CRect r(x1, y1, x2, y2);
	double rRatio = r.Aspect();
	CPoint ptCenter = r.CenterPoint();
	CPoint ptR1(x3 - ptCenter.x, static_cast<int>((y3 - ptCenter.y) * rRatio));
	CPoint ptR2(x4 - ptCenter.x, static_cast<int>((y4 - ptCenter.y) * rRatio));

	double a1, a2;

	a1 = GetLineAngle(CPoint(0,0),ptR1,TRUE);
	a2 = GetLineAngle(CPoint(0,0),ptR2,TRUE);

	CPoint lp = m_CurrentPosition,fp;
	bool bFirst = true;

	int nR1 = r.Width() / 2;
	int nR2 = r.Height() / 2;

	if (!nR1 || !nR2) return false; // error bounding box not big enough...

	int nArcDirection = m_bArcDirection ? -1 : 1;

	double fStep = static_cast<double>(3 * 360 / (_SFLMAX(r.Width(), r.Height()) * PI));
	double fSRads = RADIANS(fStep) * nArcDirection;
	double fDegrees = GetAngleDifference(a1, a2);
	if (m_bArcDirection || fDegrees == 0) {
		fDegrees = 360 - fDegrees;
	}

	double dAngle = RADIANS(a1);

	for (double f = 0; f < fDegrees; f += fStep) {
		CPoint p = ptCenter + CPoint(static_cast<int>((nR1 * cos(dAngle)) + 0.5), -static_cast<int>(((nR2 * sin(dAngle)) + 0.5)));
		if (bFirst) {
			bFirst = false;
			fp = p;
			MoveTo(p);
		}
		else {
			LineTo(p);
		}

		dAngle += fSRads;

		if (dAngle > TWO_PI) {
			dAngle -= TWO_PI;
		}
		else if (dAngle < 0) {
			dAngle += TWO_PI;
		}
	}
	LineTo(fp);
	m_CurrentPosition = lp;

	EndScanPoints();

	StrokeScanPoints();
	FillScanPoints();

	return true;
}



inline
bool CGraphicsContext::ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
{
	ASSERT(m_hDC);
	//What fun!! I never imagined having to write one of these again!!!

	// phew.. The recursive one works on emulation but not ont he real machine.
	// have to do a quick redesign.

	/*CPoint p(x,y);
	COLORREF cr,ccr=CLR_INVALID;
	bool bDone;
	CRect r(x,y,x,y+1);

	IGDIBrush *pB=GetCurrentBrush();
	if(pB!=NULL)
	ccr=pB->GetColor();

	bDone=false;
	do
	{
	cr=GetPixel(x-1,y);
	if(cr != CLR_INVALID && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor))))
	x--;
	else
	bDone=true;
	}
	while(!bDone);
	bDone=false;
	r.left=x;
	do
	{
	cr=GetPixel(x+1,y);
	if(cr != CLR_INVALID && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor))))
	x++;
	else
	bDone=true;
	}
	while(!bDone);
	r.right=x;

	#if defined(NONSTANDARD_GDI) && defined(UNDER_CE)

	HGDIOBJ obj= ::GetStockObject(NULL_PEN);
	HPEN op=(HPEN)::SelectObject(m_hDC,obj);
	::Rectangle(m_hDC,r.left,r.top,r.right+2,r.bottom+1);
	::SelectObject(m_hDC,op);

	#endif //NONSTANDARD_GDI


	for(int c=r.left; c<=r.right;c++)
	{
	cr=GetPixel(c,y-1);
	if((cr != ccr) && (cr != CLR_INVALID) && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor))))
	ExtFloodFill(c,y-1,crColor,nFillType);
	cr=GetPixel(c,y+1);
	if((cr != ccr) && (cr != CLR_INVALID) && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor))))
	ExtFloodFill(c,y+1,crColor,nFillType);
	}

	return true;

	#endif //NONSTANDARD_GDI
	*/

	// This ones better and it seems to be faster..

	list<CRect> rectList;

	CPoint p(x,y);
	COLORREF ccr = CLR_INVALID;
	COLORREF cr;
	bool bDone;

	IGDIBrush* pB = GetCurrentBrush();
	if (pB != NULL) {
		ccr=GetNearestColor(pB->GetColor());
	}

	CGDIPen pen(PS_SOLID, 1, ccr), op;

	op = SelectObject(pen);

	int c;
	CRect r;

fillLoop:

	r = CRect(p.x,p.y,p.x,p.y+1);

	bDone = false;
	do {
		cr = GetPixel(p.x-1,p.y);
		if (cr != CLR_INVALID && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor)))) {
			p.x--;
		}
		else {
			bDone = true;
		}
	} while (!bDone);

	bDone = false;
	r.left = p.x;
	do {
		cr = GetPixel(p.x+1, p.y);
		if (cr != CLR_INVALID && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor)))) {
			p.x++;
		}
		else {
			bDone = true;
		}
	} while (!bDone);

	r.right=p.x;
	// here r contains the rectangle that will fill the scan line
	// so the line gets filled...

	CPoint px[2];
	px[0].x = r.left;
	px[0].y = px[1].y = r.top;
	px[1].x = r.right + 1;
	Polyline(px, 2);

	c = r.left;

	do {
		do {
			// checking above...
			cr = GetPixel(c,p.y-1);
			if ((cr != ccr) && (cr != CLR_INVALID) && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor)))) {
				rectList.push_front(r);
				p.x=c;
				p.y--;
				goto fillLoop;
			}
			// and below
			cr = GetPixel(c,p.y+1);
			if ((cr != ccr) && (cr != CLR_INVALID) && (((nFillType == FLOODFILLBORDER) && (cr != crColor)) || ((nFillType == FLOODFILLSURFACE) && (cr == crColor)))) {
				rectList.push_front(r);
				p.x = c;
				p.y++;
				goto fillLoop;
			}

		} while (++c<=r.right);

		if (rectList.size()) {
			r = *rectList.begin();
			rectList.pop_front();
			c = r.left;
			p.x = c;
			p.y = r.top;
		}
	} while (c <= r.right);

	SelectObject(op);
	pen.DeleteObject();
	return true;
}


// Path functions


bool CGraphicsContext::FillPath()
{
	ASSERT(m_hDC);
	if (m_Path.empty()) return false;

	m_Path.sort();

#if UNDER_CE

	HGDIOBJ obj = GetStockObject(NULL_PEN);
	HPEN op = (HPEN)::SelectObject(m_hDC,obj);

	int x = 0;

	for (list<CPoint>::iterator t = m_Path.begin(); x < m_Path.size();) {
		CPoint p1 = *t++, p2 = *t++;
		x += 2;
		while (p2.x == p1.x+1 || p2.x == p1.x) {
			p2 = *t++;
			x++;
		}
		Rectangle(p1.x, p1.y, p2.x+1, p2.y+1);
	}

	::SelectObject(m_hDC,op);

#else // UNDER_CE
#endif // UNDER_CE

	return true;

}

#endif	//NONSTANDARD_GDI



// Special DC Primitives


CGDIBrush CGraphicsContext::GetHalftoneBrush()
{
	CGDIBrush brush;
	WORD grayPattern[8];
	for (int i = 0; i < 8; i++) {
		grayPattern[i] = (WORD)(0x5555 << (i & 1));
	}
	CGDIBitmap bmpGray(8, 8, 1, 1, &grayPattern);
	brush.CreatePatternBrush(bmpGray);
	return brush;
}


/*
Implementation and functionality equivalent to CDC::DrawDragRect in MFC
*/
void CGraphicsContext::DrawDragRect(LPCRECT pRect, SIZE size, LPCRECT pRectLast, SIZE sizeLast, const CGDIBrush& aBrush, const CGDIBrush& aBrushLast)
{
	ASSERT(pRect != NULL);

	// Rectangles given in logical units, convert to device units
	CRect rcCurrentTracker(*pRect);
	CSize szCurrentTracker(size);
	CRect rcLastTracker;
	if (pRectLast) {
		rcLastTracker = *pRectLast;
	}
	CSize szLastTracker(sizeLast);

	LPtoDP(&rcCurrentTracker);
	LPtoDP(&szCurrentTracker);
	if (pRectLast != NULL) {
		LPtoDP(&rcLastTracker);
		LPtoDP(&szLastTracker);
	}

	// Determine the update region and select it
	CGDIRgn rgnNew;
	CGDIRgn rgnOutside, rgnInside;
	{
		rgnOutside.CreateRectRgnIndirect(rcCurrentTracker);

		CRect rcInside = rcCurrentTracker;
		rcInside.InflateRect(-szCurrentTracker.cx, -szCurrentTracker.cy);
		rcInside.IntersectRect(rcInside, rcCurrentTracker);
		rgnInside.CreateRectRgnIndirect(rcInside);

		rgnNew.CreateRectRgn(0, 0, 0, 0);
		rgnNew.CombineRgn(rgnOutside, rgnInside, RGN_XOR);
	}

	// Prepare brushes to paint with
	CGDIBrush brushPaint(aBrush, false);
	CGDIBrush brushLastTone(aBrushLast, false);
	if (!aBrush) {
		brushPaint = GetHalftoneBrush();
	}
	if (!brushLastTone) {
		brushLastTone.Attach(brushPaint, false);
	}

	CGDIRgn rgnLast, rgnUpdate;
	if (!rcLastTracker.IsRectNull()) {
		// find difference between new region and old region
		rgnLast.CreateRectRgn(0, 0, 0, 0);
		rgnOutside.SetRectRgn(rcLastTracker);
		CRect rcLast = rcLastTracker;
		rcLast.InflateRect(-szLastTracker.cx, -szLastTracker.cy);
		rcLast.IntersectRect(rcLast, rcLastTracker);
		rgnInside.SetRectRgn(rcLast);
		rgnLast.CombineRgn(rgnOutside, rgnInside, RGN_XOR);

		bool bSameBrush = static_cast<HBRUSH>(brushPaint) != static_cast<HBRUSH>(brushLastTone);
		if (bSameBrush) {
			// Combine the regions
			rgnUpdate.CreateRectRgn(0, 0, 0, 0);
			rgnUpdate.CombineRgn(rgnLast, rgnNew, RGN_XOR);
		}
		else {
			// brushes are different -- erase old region first
			SelectClipRgn(rgnLast);
			CRect rcClip;
			GetClipBox(&rcClip);
			CGDIBrush brushOld = SelectObject(brushLastTone);
			PatBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), PATINVERT);
			SelectObject(brushOld);
		}
	}

	// draw into the update/new region
	{
		SelectClipRgn(rgnUpdate != NULL? rgnUpdate : rgnNew);
		CRect rcClip;
		GetClipBox(&rcClip);
		CGDIBrush brushOld = SelectObject(brushPaint);
		PatBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), PATINVERT);
		SelectObject(brushOld);
	}

	ClearClipRgn();
}


void CGraphicsContext::FillSolidRect(LPCRECT lpRect, COLORREF clr)
{
	COLORREF bC=SetBkColor(clr);
	ExtTextOut(lpRect->left, lpRect->top, ETO_OPAQUE, lpRect,_T(""), 0, NULL);
	SetBkColor(bC);
}


void CGraphicsContext::FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
{
	CRect r(x, y, x+cx, y+cy);
	FillSolidRect(&r, clr);
}


void CGraphicsContext::Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	CRect r(*lpRect);
	Draw3dRect(r.left, r.top, r.Width(), r.Height(), clrTopLeft, clrBottomRight);
}


void CGraphicsContext::Draw3dRect(int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	CGDIPen tl(PS_SOLID, 1, clrTopLeft), br(PS_SOLID, 1, clrBottomRight);
	CPoint p[3];
	p[0].x = p[1].x = x;
	p[0].y = y + cy;
	p[1].y = p[2].y = y;
	p[2].x = x + cx;
	CGDIPen op = SelectObject(tl);
	Polyline(p, 3);
	SelectObject(op);
	p[0].x = p[1].x = x + cx;
	p[0].y = y;
	p[1].y = p[2].y = y + cy;
	p[2].x = x;
	op = SelectObject(br);
	Polyline(p, 3);
	SelectObject(op);
	tl.DeleteObject();
	br.DeleteObject();
}


}; // foundation
}; // stingray
