///////////////////////////////////////////////////////////////////////////////
// sbarautohide.h
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
// Description:	Declarations for SECAutoHideBar
// Created:		August 2005
//
// Description:
// This class will behave more like a toolbar. It is used to display tab 
// looking icons on the side of a dockbar region. 

#ifndef __SECAUTOHIDEBAR__H__
#define __SECAUTOHIDEBAR__H__

// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#undef AFX_DATA
#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Includes
//#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
//#endif

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
#endif

#ifndef __SECICON_H__
#include "toolkit\secicon.h"
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

// Forwards
class SECFrameWnd;
class SECIcon;
class SECAutoHideBar;

class SECAutoHideBarBtn : public CWnd
{
public:
    TOOLKIT_API SECAutoHideBarBtn();
    TOOLKIT_API virtual ~SECAutoHideBarBtn();

public:
    BOOL	m_bMouseOver;
    BOOL    m_bDrawText;
    BOOL    m_bForcedDrawText;
    //HICON	m_hIcon;

    //-----------------------------------------------//
    // Protected Member Data                         //
    //-----------------------------------------------//
protected:
    CString m_Caption;
    UINT	m_nDockBarAlign;
    HWND	m_hWnd;
    CSize   m_szBtn;
    CFont   m_fontHorzMenu;
    CFont   m_fontVertMenu;
    int     m_cyHorzFont;
    int     m_cyMenuOnBar;
    int     m_cyTextMargin;
    SECAutoHideBar* m_pAutoHideBar;
    SECIcon m_Icon;
	HTHEME m_hButtonTheme;
    // Attributes

public:
    //-------------------------------------------//
    // Public Member Functions                   //
    //-------------------------------------------//

    inline HWND  GethWnd() { return m_hWnd; }
    TOOLKIT_API SECControlBar* GetBar(HWND hWnd);
    TOOLKIT_API SECControlBar* IsControlVisible(SECControlBar*);
    TOOLKIT_API void DrawTextHorz(CDC* pDC, CRect rect);
    TOOLKIT_API void DrawTextVert(CDC* pDC, CRect rect);
    inline CString GetString(){ return m_Caption;}
    inline UINT GetAlign() { return m_nDockBarAlign; }
    TOOLKIT_API void SetIconBtn(HICON hIcon); 

    inline CSize GetSizeIconBtn() 
	{
        if(m_Icon.m_hIcon != NULL)
        {
            return m_szBtn;
        }
        return CSize(0,0);
    } 

    inline BOOL HasIcon() { return (m_Icon.m_hIcon ? TRUE : FALSE); }
    inline void SetAutoHideBar(SECAutoHideBar* _pAutoHideBar) { m_pAutoHideBar = _pAutoHideBar; }

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECAutoHideBarBtn)
    TOOLKIT_API virtual BOOL Create(LPCTSTR lpszWindowName,DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, HWND hWnd);
    //}}AFX_VIRTUAL


    // Generated message map functions
protected:
    //{{AFX_MSG(SECAutoHideBarBtn)
    TOOLKIT_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnKillFocus(CWnd* pNewWnd);
#ifdef _WIN64 //RW64
    TOOLKIT_API afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	TOOLKIT_API afx_msg void OnTimer(UINT nIDEvent);
#endif //_WIN64
    TOOLKIT_API afx_msg void OnDestroy();
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP()
};



// Note we are deriving from standard CControlbar because we do not need
// all the associated functionality of the SECControlBar.
class SECAutoHideBar : public SECControlBar
{
public:

	//----------------------------------------------//
	// Constructors                                 //
	//----------------------------------------------//
	TOOLKIT_API SECAutoHideBar();
    TOOLKIT_API virtual ~SECAutoHideBar();

	//----------------------------------------------//
	// Member Functions                             //
	//----------------------------------------------//
public:
    inline int                  GetNumControlBars() { return m_nNumCtrlBars; }
    inline void                 SetNumControlBars(int _iNumCtrlBars) { m_nNumCtrlBars = _iNumCtrlBars; }
    TOOLKIT_API virtual void    OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    TOOLKIT_API virtual CSize   CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    TOOLKIT_API void            AddControlBars(SECControlBar* m_ctrlBars);
    TOOLKIT_API void            DeleteAllControlBars();
    TOOLKIT_API void            DeleteControlBars(SECControlBar* m_ctrlBars);
    TOOLKIT_API void            UpdateBars();
    TOOLKIT_API void            CalcButton();
    inline virtual int          GetCount(){ return m_nNumCtrlBars; }
    TOOLKIT_API SECControlBar*  GetBar(int );

    TOOLKIT_API void            SetActiveButton(SECAutoHideBarBtn* _pBtn);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECAutoHideBar)
    TOOLKIT_API virtual BOOL	Create(CWnd* pParentWnd, DWORD dwAlign);
    TOOLKIT_API virtual CSize	CalcDynamicLayout(int nLength, DWORD dwMode);
    TOOLKIT_API virtual void    EnableDocking(DWORD dwDockStyle);
    //}}AFX_VIRTUAL

public:
	//{{AFX_MSG(SECAutoHideBar)
	TOOLKIT_API afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#ifdef _WIN64 //RW64
    TOOLKIT_API afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	TOOLKIT_API afx_msg void OnTimer(UINT nIDEvent);
#endif //_WIN64
    TOOLKIT_API afx_msg void OnDestroy();
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
    TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()

	//----------------------------------------------//
	// Member Data                                  //
	//----------------------------------------------//
public:
    CPtrArray	m_ArrayButton;
    CFont       m_fontHorzMenu;
    CFont       m_fontVertMenu;

protected:
    int         m_cyHorzFont;
    int         m_cyMenuOnBar;
    int         m_cyTextMargin;
    int         m_nNumCtrlBars;
    int         m_nSize;
    COLORREF    m_clrface;
    HTHEME		m_hReBarTheme;
};

#endif // __SECAUTOHIDEBAR__H__