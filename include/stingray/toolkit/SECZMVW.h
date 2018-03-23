///////////////////////////////////////////////////////////////////////////////
// SECZMVW.h
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
//  Description:	Declarations for SECZoomView
//  Created:		7/16/95
//
//  Got most logic from ScrollView, plus the tangram sample, which
//  shows how to use ANISTROPIC mode to do zooming.
//
//  Since we're aiming to be a drop-in replacement for scrollview,
//  we override some of the usual scrollview routines plus we
//  always start with zooming off and let the user set it up,
//  instead of zooming by default.
//

#ifndef __SECZMVW_H__
#define __SECZMVW_H__

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

/////////////////////////////
// AutoDuck tag block block for SECZoomView 

//@doc SECZoomView
//@mfunc UINT   | SECZoomView | GetZoomMode | Retrieves the current zoom mode, one of either SEC_ZOOMOFF, SEC_ZOOMNORMAL or SEC_ZOOMFIT.
//@rdesc Returns the current zoom mode. 
//@xref<mf SECZoomView::SetZoomMode>
//@xref<c SECZoomView>

//@doc SECZoomView
//@mfunc float  | SECZoomView | GetZoomLevel | Returns a float which represents the current zoom level. To convert to a percentage
// multiply by 100.
//@rdesc Returns the current zoom level.
//@xref<mf SECZoomView::SetZoomLevel>
//@xref<mf SECZoomView::ZoomIn>
//@xref<mf SECZoomview::ZoomPercent>
//@xref<mf SECZoomView::ZoomOut>
//@xref<c SECZoomView>

//@doc SECZoomView
//@mfunc virtual void  | SECZoomView | ZoomLevelChanged | Override this virtual member function and add a call to GetZoomLevel
// if you want to update any user-interface elements to reflect new zoom levels.
//@xref<mf SECZoomView::GetZoomLevel>
//@xref<c SECZoomView>

// adinsert AutoDuck insertion point for SECZoomView 
//@doc SECZoomView 
//@class SECZoomView is a CScrollView extension that adds automatic zooming to your application views.  
//@comm
// SECZoomView does this by overloading the CScrollView::OnPrepareDC method and performing zooming 
// through standard Windows GDI mapping modes.  MM_ANISOTROPIC is the only supported mapping mode.  
// If you must use a mapping mode other than MM_ANISOTROPIC, SECZoomView cannot be used.  If your 
// current CScrollView changes the mapping modes with an OnPrepareDC override, you will need to 
// turn off these changes as they will nullify the effects of SECZoomView.

//SECZoomView supports three zoom modes:
//@flag	SEC_ZOOMOFF | Zooming is disabled.
//@flag	SEC_ZOOMNORMAL | Zooming is performed based on a floating point zoom factor.  This can be specified as a zoom 
// percentage as well.
//@flag SEC_ZOOMFIT | The SECZoomView automatically changes the zoom level such that all portions of the view are visible 
// inside the view window.
//@normal The developer can specify a min/max zoom which is appropriate for the application and platform.  
// The default is infinite zooming, but this will cause ‘wrap’ as the values which track scrolling 
// overflow.  The ‘wrap’ factor depends on the operating system (Win16 has lower tolerences than 
// Win32, etc.) A SECZoomView can be zoomed by specifying a zoom percentage, a rectangle to be zoomed, 
// or a zoom factor.
//
// SECZoomView provides an overridable callback, <mf SECZoomView::ZoomLevelChanged>, that is called 
// whenever the zoom level changes so that any user interface elements can be updated. The simplicity 
// of this approach allows any number of interesting zoom user interfaces to be used.
//
// The CLOUD sample in the \SAMPLES\TOOLKIT\STANDARD\VIEWS\CLOUD directory shows the SECZoomView and SECPanView classes in action. 
//@xref<c SECPanView>
//@BASE public | CScrollView
class SECZoomView : public CScrollView
{
    TOOLKIT_DECLARE_DYNAMIC(SECZoomView);
    
public:
    enum {SEC_ZOOMOFF, SEC_ZOOMPANOVER, SEC_ZOOMNORMAL, SEC_ZOOMFIT};
// Construction    
protected:
	// protected constructor used by dynamic creation
	//@Access Protected Members
	//Constructors
	//@cmember
	/* Creates an SECZoomView object.*/
    TOOLKIT_API SECZoomView();   

// Override this to get zoom scale change notifications.
    //@Access Overridable
	//@cmember
	/* Override ZoomLevelChanged to receive notifications that the zoom level has been modified.  Good for */
	// automatically updating zoom user-interface elements.
   inline  virtual void ZoomLevelChanged(void) {};

	//@cmember
	/* Called when an attempt is made to zoom beyond allowed range.*/
    TOOLKIT_API virtual void ZoomOutOfRange(BOOL bUnderFlow, float fAttempt);

	//@cmember
	/* Sets the current zoom level.*/
    TOOLKIT_API virtual void SetZoomLevel(float);
  
// Operations
public:
    // Overridden CScrollView member functions
    // sizeDefault lives in scrollview?
    TOOLKIT_API void   SetScrollSizes(int nMapMode,
			  SIZE sizeTotal, const SIZE& sizePage = sizeDefault,
			  const SIZE& sizeLine = sizeDefault);
    TOOLKIT_API void   CenterOnLogicalPoint(CPoint ptCenter);
    TOOLKIT_API CPoint GetLogicalCenterPoint(void);
	TOOLKIT_API void   UpdateZoomBars();   // replacement for nonvirtual UpdateBars()
    	
	//@Access Public Members
    //Zooming Operations
	//@cmember
	/* Gets the current zoom mode setting.*/
    TOOLKIT_API UINT  GetZoomMode() {return m_zoomMode;};

	//@cmember
	/* Retrieves the floating point zoom factor.*/
    TOOLKIT_API float GetZoomLevel() {return m_fZoomScale;};

	//@cmember
	/* Restrict the zoom factor to a minimum and maximum zooming factor.*/
    TOOLKIT_API void  SetZoomMinMax(float fMin, float fMax);

	//@cmember
	/* Restrict the zoom factor to a minimum and maximum zoom percent.*/
    TOOLKIT_API void  SetZoomMinMaxPercent(int nMin, int nMax);

	//@cmember
	/* Sets the zoom mode to either SEC_ZOOMOFF, SEC_ZOOMNORMAL, or SEC_ZOOMFIT.*/
    TOOLKIT_API void  SetZoomMode(UINT zoomMode);
    
	//@cmember
	/* Increases the zoom level.*/
    TOOLKIT_API virtual void ZoomIn(CRect &rect);

	//@cmember
	/* Increases the zoom level.*/
    TOOLKIT_API virtual void ZoomIn(CPoint *point = NULL, float delta = 1.25);

	//@cmember
	/* Decreases the zoom level.*/
    TOOLKIT_API virtual void ZoomOut(CPoint *point = NULL, float delta = 1.25);

	//@cmember
	/* Sets the zoom level to 100%, or no zooming.*/
    TOOLKIT_API virtual void ZoomOriginal(CPoint *point = NULL);

	//@cmember
	/* todo Add a description*/
    TOOLKIT_API  virtual void ZoomFit();
    
    //Arguments slightly different, so people can just enter percent
    //and have point as default instead of having to specify null point.
	//@cmember
	/* Zooms in or out based on a percent.  For example, 200% will zoom in, where 5% will zoom out.*/
    TOOLKIT_API virtual void ZoomPercent(int nPercent = 25,CPoint *point = NULL);
    
    // Zooming utility functions
    TOOLKIT_API void      ViewDPtoLP (LPPOINT lpPoints, int nCount = 1);
    TOOLKIT_API void      ViewLPtoDP (LPPOINT lpPoints, int nCount = 1);
    TOOLKIT_API void      ClientToDevice(CPoint &point);


// Implementation
protected:
    TOOLKIT_API virtual ~SECZoomView();
#ifdef _DEBUG
    TOOLKIT_API virtual void Dump(CDumpContext&) const;
    TOOLKIT_API virtual void AssertValid() const;
#endif //_DEBUG
    TOOLKIT_API virtual void OnDraw(CDC* pDC) = 0; // Pass on Pure Virtual from CScrollView
    TOOLKIT_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    // Printing support
    TOOLKIT_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    
protected:
    TOOLKIT_API void      PersistRatio(const CSize &orig, CSize &dest, CPoint &remainder);
    TOOLKIT_API void      ReCalcBars(void);
    TOOLKIT_API virtual	void UpdateViewport(CPoint * ptNewCenter);
    
    // Private member variables
    UINT      m_zoomMode;      // The current zoom mode: normal/off/zoom to fit
    CSize     m_szOrigTotalDev;  // Origional total size in device units
    CSize     m_szOrigPageDev;   // Origional page scroll size in device units
    CSize     m_szOrigLineDev;   // Origional line scroll size in device units
    float     m_fZoomScale;      // Current ratio between device/logical units
    float     m_fZoomMin;
    float     m_fZoomMax;
    
public:
    // Generated message map functions
    //{{AFX_MSG(SECZoomView)
    TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
    TOOLKIT_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    TOOLKIT_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECZMVW_H__

