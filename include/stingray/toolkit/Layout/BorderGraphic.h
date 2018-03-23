///////////////////////////////////////////////////////////////////////////////
// BorderGraphic.h : Declaration of node border drawing classes
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
// Description:  Declaration of node border drawing classes
//

#ifndef __SECLAYOUTNODE_BORDER_GRAPHIC_H___
#define __SECLAYOUTNODE_BORDER_GRAPHIC_H___

// Header Includes
#include "toolkit\Layout\Border.h"
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

/////////////////////////////////////////////////////////////////////////////
// ISECBorderWrapper

//
// Interface providing rudimentary wrapper manipulation
//

class ISECBorderWrapper 
{
public:
	inline virtual ~ISECBorderWrapper() {}

	virtual void ShowWrapper(BOOL bShow=TRUE,BOOL bRealizeChange=TRUE)=0;
	virtual BOOL GetWrapperVisible()=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECLayoutNodeBorderSpace

//
//	SECLayoutNode
//		|
//		SECLayoutNodeDCBase
//			|
//			SECLNBorder_T<SECLayoutNodeDCBase>  ISECBorderWrapper
//						|					  |
//						SECLayoutNodeBorderSpace
//

//
// Core logic to draw empty borderspace around a child node.
//

class SECLayoutNodeBorderSpace : public SECLNBorder_T<SECLayoutNodeDCBase>,
								 public ISECBorderWrapper
{
public:
	TOOLKIT_API SECLayoutNodeBorderSpace();
	TOOLKIT_API virtual ~SECLayoutNodeBorderSpace();

	// Current border node orientation. More useful for the derived class.
	enum BorderOrientation { top, bottom, left, right, none };

	TOOLKIT_API void SetDefBorderSize(UINT nLeft,UINT nTop,UINT nRight,UINT nBottom);
	TOOLKIT_API void GetDefBorderSize(UINT& nLeft,UINT& nTop,UINT& nRight,UINT& nBottom);

	// Implementation of ISECBorderWrapper
	TOOLKIT_API virtual void ShowWrapper(BOOL bShow=TRUE,BOOL bRealizeChange=TRUE);
	inline virtual BOOL GetWrapperVisible() { return m_bShowWrapper; }

	//---------------------------------------------------------------------//
	// 							 Overrides								   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);
	TOOLKIT_API virtual void OnDrawNode(HDC hDC,const CRect& rectDraw);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//

	TOOLKIT_API virtual void UpdateBorderSizes(UINT nLeft,UINT nTop,UINT nRight,UINT nBottom);
	TOOLKIT_API virtual void OnDrawBorderRegion(HDC hDC,const CRect& rectDraw,CRect& rectOld,
									BorderOrientation orientation);
	TOOLKIT_API virtual void OnInvalidateOldBorderRect(const CRect& rectNew,CRect& rectOld);
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rcErase);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:
	// Member Functions
	TOOLKIT_API void UpdateBorderSizes();
	TOOLKIT_API virtual void CalcBorderRects(const CRect& rectNode,BOOL bHorzOrientation,
									CRect& rectLeft,CRect& rectRight,
									CRect& rectTop,CRect& rectBottom);
	TOOLKIT_API BOOL RectContained(const CRect& rcParent,const CRect& rcChild);

	// Member Variables
	BOOL m_bHorizontal,m_bShowWrapper;
	UINT m_nDefBorderThickLeft,m_nDefBorderThickTop,
		 m_nDefBorderThickRight,m_nDefBorderThickBottom;
	CRect m_rectDrawLeft,m_rectDrawTop,m_rectDrawBottom,m_rectDrawRight;
	CRect m_rectDrawLeftOld,m_rectDrawRightOld,m_rectDrawTopOld,m_rectDrawBottomOld;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNBorderClientEdge

// Specialization of SECLayoutNodeBorderSpace designed to draw a small 3d
// border client edge around a particular contained node

class SECLNBorderClientEdge : public SECLayoutNodeBorderSpace,
							  public SECParentOfNegotiableChildNode 
{
public:
	TOOLKIT_API SECLNBorderClientEdge();
	TOOLKIT_API virtual ~SECLNBorderClientEdge();
	TOOLKIT_API void SetBorderEdgesToDraw(BOOL bDrawLeft,BOOL bDrawTop,BOOL bDrawRight,BOOL bDrawBottom);
	TOOLKIT_API void SetBorderEdgesToDraw(BOOL bDrawLeftRight,BOOL bDrawTopBottom);
	TOOLKIT_API void GetBorderEdgesToDraw(BOOL& bDrawLeft,BOOL& bDrawTop,BOOL& bDrawRight,BOOL& bDrawBottom);
	
protected:
	// SECLayoutNodeBorderSpace Overrides
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);
	TOOLKIT_API virtual void UpdateBorderSizes(UINT nLeft,UINT nTop,UINT nRight,UINT nBottom);
	TOOLKIT_API virtual void OnDrawBorderRegion(HDC hDC,const CRect& rectDraw,CRect& rectOld,
									BorderOrientation orientation);
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rcErase);

	// New Overridables
	TOOLKIT_API virtual void OnDrawExteriorPadding(HDC hDC,const CRect& rectDraw,
									BOOL bHorz,BorderOrientation orientation);
	TOOLKIT_API virtual void OnDrawClientEdge(HDC hDC,const CRect& rectDraw,
									BOOL bHorz,BorderOrientation orientation,
									CPen* pPenOutside,CPen* pPenInside);
	TOOLKIT_API virtual void OnDrawInteriorPadding(HDC hDC,const CRect& rectDraw,
									BOOL bHorz,BorderOrientation orientation);

	// Implementation variables
	BOOL m_bDrawLeft,m_bDrawTop,m_bDrawRight,m_bDrawBottom;
	UINT m_nExteriorPad,m_nEdgeSize,m_nInteriorPad;
	CPen m_penHilite,m_penShadow;

	// Implementation Member Functions
	TOOLKIT_API virtual BOOL IsValidOrientation(BorderOrientation orientation,BOOL& bHorz);
	TOOLKIT_API virtual CRect CalcDrawingRect(const CRect& rectBorderTotal,
									UINT nStartPad,UINT nStopPad,
									BorderOrientation orientation);
};

/////////////////////////////////////////////////////////////////////////////
// SECLayoutNodeGripper
//
//	SECLayoutNode
//		|
//		SECLayoutNodeDCBase
//			|
//			SECLNBorder_T<SECLayoutNodeDCBase>
//				|		
//				SECLayoutNodeBorderSpace
//					|
//					SECLayoutNodeGripper
//
//
// SECLayoutNodeGripper class (see also SECLayoutNode base class)
// This derivation of SECLayoutNode provides the implementation
// for DC drawing in the layout node tree.
//
// 
// Extension of SECLayoutNodeBorderSpace that also draws 
// a 3 dimensional dragging gripper.
//

//@doc SECLayoutNodeGripper 
//@class Internal Class. Refer only to the exported static functions below.
class SECLayoutNodeGripper : public SECLayoutNodeBorderSpace					 
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLayoutNodeGripper();
	TOOLKIT_API virtual ~SECLayoutNodeGripper();

	// Accessors
	//	...Get and Set functions...	
	TOOLKIT_API void SetGripperOrientation(BorderOrientation orientation);
	inline BorderOrientation GetGripperOrientation() { return m_GripperOrientation; }
	TOOLKIT_API void SetGripperThickness(UINT nThickness);
	inline UINT GetGripperThickness() { return m_nGripperThickness; }

	// Default single gripper setting

	//@cmember
	/* Enable "Rebar-Style" single gripper look */
	TOOLKIT_API static void SetSingleGripperDefault(BOOL bEnable=TRUE);

	//@cmember
	/* Get current "Rebar-Style" single gripper setting */
	TOOLKIT_API static BOOL GetSingleGripperDefault();

	// Single gripper override for a specific object (otherwise default)
	inline void SetSingleGripper(BOOL bEnable=TRUE) { m_bSingleGripper=bEnable; }
	inline BOOL GetSingleGripper() { return m_bSingleGripper; }
	
	// Cached gripper subcomponent positional awareness
	class SECGripperComponents 
	{
	public:
		inline SECGripperComponents() 
			{	m_rectGripperOutside=m_rectGripperInside=CRect(0,0,0,0); }

		CRect m_rectGripperOutside,m_rectGripperInside;
	};

	// Internal settings for gripper component calcs
	class SECGripperInternalZones 
	{
	public:
		inline SECGripperInternalZones() 
			{m_nZone1=m_nZone2=m_nZone3=m_nZone4=m_nZoneA=m_nZoneB=0; }

		UINT m_nZone1,m_nZone2,m_nZone3,m_nZone4;
		UINT m_nZoneA,m_nZoneB;
	};	
	
	// Overrides
	TOOLKIT_API virtual void SetNodeHorizontal(BOOL bHorz=TRUE,BOOL bRecurse=FALSE);

	//---------------------------------------------------------------------//
	// 							 Overrides								   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rcErase);
	TOOLKIT_API virtual void UpdateBorderSizes(UINT nLeft,UINT nTop,UINT nRight,UINT nBottom);

protected:
	// Overridables
	inline virtual SECGripperInternalZones* CreateGripperZoneInfo() { return new SECGripperInternalZones; }
	inline virtual SECGripperComponents* CreateGripperComponents() { return new SECGripperComponents; }
	TOOLKIT_API virtual void OnDrawBorderRegion(HDC hDC,const CRect& rectDraw,CRect& rectOld,
									BorderOrientation orientation);
	TOOLKIT_API virtual void OnDrawBorderRegionGripper(HDC hDC,const CRect& rectDraw,
									BorderOrientation orientation,
									SECGripperComponents* pComponents);
	
	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	BorderOrientation m_GripperOrientation;
	UINT m_nGripperThickness;
	SECGripperComponents* m_pGripperSubComponents;
	BOOL m_bSingleGripper;
	TOOLKIT_API static BOOL m_bSingleGripperDefault;
	
	// Implementation Member Functions
	TOOLKIT_API virtual void RecalcGripperComponents(const CRect& rectGripper,
									BorderOrientation orient,
									SECGripperComponents* pComponents);
	TOOLKIT_API virtual void CalcInternalGripperZones(SECGripperInternalZones* pZoneInfo,
									UINT nThicknessPrimary,UINT nThicknessSecondary,
									BorderOrientation orient);
	TOOLKIT_API virtual void CalcInternalGripperZonesSingle(SECGripperInternalZones* pZoneInfo,
									UINT nThicknessPrimary,UINT nThicknessSecondary,
									BorderOrientation orient);
	TOOLKIT_API virtual void CalcGripperComponentsHorz(const CRect& rectGripper,
									SECGripperInternalZones* pZoneInfo,
									SECGripperComponents* pComponents);
	TOOLKIT_API virtual void CalcGripperComponentsVert(const CRect& rectGripper,
									SECGripperInternalZones* pZoneInfo,
									SECGripperComponents* pComponents);
};

/////////////////////////////////////////////////////////////////////////////
// SECLayoutNodeGripperEx

// Extension of SECLayoutNodeGripper that supports close/expand buttons

// CWnd
//	|
//	SECWndPlugIn					... (see above)
//		|							|
//		SECWndListener		SECLayoutNodeGripper
//			|					|
//			SECLayoutNodeGripperEx

//
// Extension of SECLayoutNodeGripper that also draws a "close" and
// "expand" owner-draw pushbutton for additional state manipulation.
//
// Note: Window listener class mixed in to provess mouse events to
// these ownerdraw buttons

class SECLayoutNodeGripperEx :	public stingray::foundation::SECWndListener,
								public SECLayoutNodeGripper
{
public:
	TOOLKIT_API SECLayoutNodeGripperEx();

	// Override to plugin to the window as well.
	TOOLKIT_API virtual void SetNodeOwnerHWND(HWND hWndOwner);

	inline void SetExpandVisible(BOOL bEnable=TRUE) { m_bExpandButtonVisible=bEnable; }
	inline BOOL GetExpandVisible() 	{ return m_bExpandButtonVisible; }
	inline void SetCloseVisible(BOOL bEnable=TRUE) 	{ m_bCloseButtonVisible=bEnable; }
	inline BOOL GetCloseVisible()		{ return m_bCloseButtonVisible; }	
	inline void SetExpandExpandable(BOOL bEnable=TRUE) { m_bExpandButtonDoExpand=bEnable; }
	inline BOOL GetExpandExpandable()	{ return m_bExpandButtonDoExpand; }
	inline void SetExpandEnabled(BOOL bEnable=TRUE) 	{ m_bExpandButtonEnabled=bEnable; }
	inline BOOL GetExpandEnabled() 	{ return m_bExpandButtonEnabled; }
	inline void SetCloseEnabled(BOOL bEnable=TRUE) 	{ m_bCloseButtonEnabled=bEnable; }
	inline BOOL GetCloseEnabled() 		{ return m_bCloseButtonEnabled; }

	// Cached gripper subcomponent positional awareness
	class SECGripperComponentsEx : public SECLayoutNodeGripper::SECGripperComponents 
	{
	public:
		inline SECGripperComponentsEx() : SECGripperComponents()
			{	m_rectCloseButton=m_rectExpandButton=CRect(0,0,0,0); }
		CRect m_rectCloseButton;
		CRect m_rectExpandButton;
	};

	// Internal settings for gripper component calcs
	class SECGripperInternalZonesEx : public SECLayoutNodeGripper::SECGripperInternalZones 
	{	
	public:
		inline SECGripperInternalZonesEx() : SECGripperInternalZones() 
			{ 	m_nZoneEx1=m_nZoneEx2=m_nZoneEx3=m_nZoneExA=m_nZoneExB=
				m_nZoneExC=m_nZoneExD=m_nZoneExE=0; }
		UINT m_nZoneEx1,m_nZoneEx2,m_nZoneEx3;
		UINT m_nZoneExA,m_nZoneExB,m_nZoneExC,m_nZoneExD,m_nZoneExE;
	};	

	// Overridables
	TOOLKIT_API virtual void OnCloseButtonPushed();
	TOOLKIT_API virtual void OnExpandButtonPushed();

// Generated message map functions
protected:
	//{{AFX_MSG(SECLayoutNodeGripperEx)
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
	// Overrides to insert Ex types
	inline virtual SECGripperInternalZones* CreateGripperZoneInfo() { return new SECGripperInternalZonesEx; }
	inline virtual SECGripperComponents* CreateGripperComponents() { return new SECGripperComponentsEx; }

	TOOLKIT_API virtual void OnDrawBorderRegionGripper(HDC hDC,const CRect& rectDraw,
									BorderOrientation orientation,
									SECGripperComponents* pComponents);
	TOOLKIT_API virtual void CalcInternalGripperZones(SECGripperInternalZones* pZoneInfo,
									UINT nThicknessPrimary,UINT nThicknessSecondary,
									BorderOrientation orient);
	TOOLKIT_API virtual void CalcGripperComponentsHorz(const CRect& rectGripper,
									SECGripperInternalZones* pZoneInfo,
									SECGripperComponents* pComponents);
	TOOLKIT_API virtual void CalcGripperComponentsVert(const CRect& rectGripper,
									SECGripperInternalZones* pZoneInfo,
									SECGripperComponents* pComponents);
	TOOLKIT_API virtual UINT GetGripperExpandState(BorderOrientation orientation);
	TOOLKIT_API virtual UINT GetGripperCloseState(BorderOrientation orientation);
	TOOLKIT_API virtual BOOL GetGripperCloseRect(CRect& rect);
	TOOLKIT_API virtual BOOL GetGripperExpandRect(CRect& rect);

protected:
	BOOL m_bCloseButtonVisible,		m_bExpandButtonVisible;
	BOOL m_bCloseButtonEnabled;
	BOOL m_bExpandButtonDoExpand,	m_bExpandButtonEnabled;
	BOOL m_bCloseButtonPushGraphic,	m_bExpandButtonPushGraphic;
	BOOL m_bPushCloseInProgress,	m_bPushExpandInProgress;
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

#endif //__SECLAYOUTNODE_BORDER_GRAPHIC_H___
