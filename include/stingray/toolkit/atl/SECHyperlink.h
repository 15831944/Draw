///////////////////////////////////////////////////////////////////////////////
// SECHyperlink.h
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
//		Author:		Sam Robinson	9/15/99
//

#ifndef __SECHYPERLINK__
#define __SECHYPERLINK__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ATL headers
#include <atlbase.h>
#include <atlwin.h>
// Required for ShellExecute()
#include "shellapi.h"
// STL string header
#include <foundation\stwarn.h>
#include <string>
#include <foundation\stwarnp.h>

// SFL Resources
#include "Foundation\SflRes.h"

#ifdef _UNICODE
typedef std::wstring _string;
#else
typedef std::string _string;
#endif //_UNICODE

/////////////////////////////////////////////////////////////////////////////
// SECHyperlink 
// AutoDuck tag block block for SECHyperlink

//@doc SECHyperlink
//@mdata Attrib | std::string | m_strHyperlink | Protected member that holds the hyperlink.
//@doc SECHyperlink
//@mdata Attrib | std::string | m_strDisplayText | Protected member that holds the text to be displayed.
//@doc SECHyperlink
//@mdata Attrib | COLORREF | m_clrDispTextNormal | Protected member that holds the COLORREF of the display text in it's normal state.
//@doc SECHyperlink
//@mdata Attrib | COLORREF | m_clrDispTextVisited | Protected member that holds the COLORREF of the display text after it has been clicked on.
//@doc SECHyperlink
//@mdata Attrib | BOOL | m_bExecuteLink | Protected member that determinsed if the hyperlink will be executed. 
//@doc SECHyperlink
//@mdata Attrib | BOOL | m_bVisited | Protected member that indicates if the link has been visited.
//@doc SECHyperlink
//@mdata Attrib | BOOL | m_bSizeToText | Protected member that controls if the window will be resized to fit the text.
//@doc SECHyperlink
//@mdata Attrib | HFONT|  m_hUserFont | Protected member which holds a handle to a font that the user has created for the display text.
//@doc SECHyperlink
//@mdata Attrib | HCURSOR | m_hUserCursor | Protected member that which holds a handle to a user specified cursor to be displayed when the mouse is over the hyperlink.

//@doc SECHyperlink
//@mfunc  | SECHyperlink | SECHyperlink | Constructor for the SECHyperlink class.
//@xref <c SECHyperlink>

//@doc SECHyperlink
//@mfunc BOOL  | SECHyperlink | Create | Creates the child window for the hyperlink and attaches it to it's parent window.
//@rdesc BOOL TRUE if successful; otherwise FALSE.
//@parm HWND | hParentWnd | Handle to the window that is the hyperlink’s parent or owner.
//@parm  RECT& | rect | The size and position of the hyperlink, in client coordinates of pParentWnd.
//@parm  UINT | nID | The ID of the hyperlink.
//@parm  LPCTSTR | lpszWindowName | Points to a string that contains the hyperlink's name. This is usually NULL. This default is supplied.
//@parm DWORD | dwStyle | Specifies the hyperlink’s style attributes. A default argument of WS_CHILD + WS_VISIBLE is supplied.
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc BOOL  | SECHyperlink | AttachHyperlink | Attaches an SECHyperlink object to an edit control.
//@rdesc BOOL TRUE if successful; otherwise FALSE.
//@parm HWND | hParentWnd | The parent of the dialog control you want to replace.
//@parm UINT | uID | The ID of the dialog control you want to replace with the SECHyperlink control.
//@parm DWORD | dwStyle | The window style of the SECHyperlink control.
//@xref <c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetHyperlink | Sets the string for the hyperlink.
//@parm const TCHAR* | pStrLink | String specifying the hyperlink.
//@xref<mf SECHyperlink::GetHyperlink>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc const TCHAR*  | SECHyperlink | GetHyperlink | Returns the hyperlink string.
//@xref<mf SECHyperlink::SetHyperlink>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetLinkVerb | Sets the string specifying the hyperlink verb; default is "open". For a list of verbs, please refer to the SDK ::ShellExecute() documentation.
//@parm const TCHAR* | lpStrVerb | String specifying the verb.
//@xref<mf SECHyperlink::GetLinkVerb>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc const TCHAR*  | SECHyperlink | GetLinkVerb | Returns the hyperlink verb.
//@xref<mf SECHyperlink::SetLinkVerb>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc const TCHAR*  | SECHyperlink | GetLinkParams | Returns the execution parameters.
//@xref<mf SECHyperlink::SetLinkParams>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetLinkParams | Sets the parameters for executing the link.
//@parm const TCHAR* | lpStrParams | String specifying the parameters.
//@xref<mf SECHyperlink::GetLinkParams>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc const TCHAR*  | SECHyperlink | GetLinkDefDir | Returns a string containing the default directory.
//@xref<mf SECHyperlink::SetLinkDefDir>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetLinkDefDir | Sets the default directory.
//@parm const TCHAR* | lpStrDefDir | String specifying the default directory.
//@xref<mf SECHyperlink::GetLinkDefDir>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc int  | SECHyperlink | GetLinkShowCmd | Returns the application display flags.
//@xref<mf SECHyperlink::SetLinkShowCmd>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetLinkShowCmd | Sets the flags specifying the initial display state for the application associated with the link. 
//@parm int | nShowCmd | Flags specifying the initial display state. For a list of flags, please refer to the SDK ::ShellExecute() documentation.
//@xref<mf SECHyperlink::GetLinkShowCmd>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc const TCHAR*  | SECHyperlink | GetDisplayText | Returns the display text string.
//@xref<mf SECHyperlink::SetDisplayText>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetDisplayText | Sets the string that will be shown to the end user.
//@parm const TCHAR* | pStrDisplayText | String specifying the display text.
//@xref<mf SECHyperlink::GetDisplayText>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc COLORREF  | SECHyperlink | GetClrDispTextNormal | Returns the color set for an unaccessed link.
//@xref<mf SECHyperlink::SetClrDispTextNormal>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetClrDispTextNormal | Sets the color that will be used for an unaccessed link. 
//@parm COLORREF | clrNormal | A COLORREF value.
//@xref<mf SECHyperlink::GetClrDispTextNormal>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetClrDispTextVisited | Sets the color for the string after it has been accessed. 
//@parm COLORREF | clrVisited | A COLORREF value.
//@xref<mf SECHyperlink::GetClrDispTextVisited>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc COLORREF  | SECHyperlink | GetClrDispTextVisited | Returns the color for the string after it has been accessed.
//@xref<mf SECHyperlink::SetClrDispTextVisited>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetVisited | Sets the link to it's visited state. 
//@parm BOOL | bVisited | BOOL value specifying the visited state.
//@xref<mf SECHyperlink::GetVisited>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc BOOL  | SECHyperlink | GetVisited | Returns TRUE if the link has been clicked on or set to the visited state.
//@xref<mf SECHyperlink::SetVisited>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetUserFont | Sets the display font to the one passed in. 
//@parm HFONT | hUserFont | The display font.
//@xref<mf SECHyperlink::GetUserFont>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc HFONT  | SECHyperlink | GetUserFont | Returns a handle to the specified font.
//@xref<mf SECHyperlink::SetUserFont>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SetUserCursor | Sets the cursor to be shown when the mouse is over the hyperlink. 
//@parm HCURSOR | hUserCursor | The display cursor.
//@xref<mf SECHyperlink::GetUserCursor>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc HCURSOR  | SECHyperlink | GetUserCursor | Returns a handle to the cursor.
//@xref<mf SECHyperlink::SetUserCursor>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | SizeToText | If TRUE, sizes the hyperlink window to the size of the display text. 
//@parm BOOL | bReSize | FALSE for non-resizing; Default is TRUE.
//@xref<mf SECHyperlink::GetSizeToText>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc BOOL  | SECHyperlink | GetSizeToText | Returns the resizing mode. If TRUE then resizing is enabled.
//@xref<mf SECHyperlink::SizeToText>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc void  | SECHyperlink | ExecuteLink | Allows the automatic execution of a hyperlink to be inhibited. Set to FALSE to inhibit execution. 
//@parm BOOL | bExecute | Default is TRUE.
//@xref<mf SECHyperlink::GetExecuteLink>
//@xref<c SECHyperlink>

//@doc SECHyperlink
//@mfunc BOOL  | SECHyperlink | GetExecuteLink | Returns the auto execute mode. If TRUE then execution is enabled.
//@xref<mf SECHyperlink::Execute>
//@xref<c SECHyperlink>

// adinsert AutoDuck insertion point for SECHyperlink
//@doc SECHyperlink
//@class SECHyperlink 
//@comm The SECHyperlink class is a browser independent class for providing
// a simple link to a registered internet resource. The most common sorts of
// resources are web resources (HTTP://xxxx.yyy.zzz), email resources 
// (mailto:someone@somewhere.com) and ftp resources. 
//
// Usage of this class can be done by either calling the create function or by
// attachin the SECHyperlink control to an existing control located on a dialog.
// Using the existing control simplifies layout by allowing the resource editor to
// be used to position the control.
//@base public | CWindowImpl
class SECHyperlink : public CWindowImpl<SECHyperlink>
{
// Construction
public:
	//@cmember
	/*Constructor*/
	inline SECHyperlink()
	{
		// Set default behavior
		m_strVerb = _T("open");
		m_strHyperlink = _T("");
		m_strParams = _T("");
		m_strDefDir = _T("");
		m_nLinkShowCmd = SW_SHOWNORMAL;
		m_strDisplayText = _T("");
		m_bVisited = FALSE;
		m_bExecuteLink = TRUE;
		m_bSizeToText = FALSE;

		m_hUserFont = NULL;
		m_hUserCursor = NULL;
		m_hOldCursor = NULL;

		m_clrDispTextNormal = RGB(0,0,255);
		m_clrDispTextVisited = RGB(0,0,128);
		m_bExecuteLink = TRUE;
	}

	virtual ~SECHyperlink()	{}

// Overrides	
public:
	//@cmember
	/*Creates the child window for the hyperlink and attaches it to it's parent window.*/
	virtual BOOL Create(HWND hParentWnd, RECT& rect,UINT nID, LPCTSTR lpszWindowName = NULL, DWORD dwStyle = WS_CHILD | WS_VISIBLE)
	{
		_ASSERTE(::IsWindow(hParentWnd));
		if(!::IsWindow(hParentWnd))
		{
			return FALSE;
		}
		HWND hWnd = CWindowImpl<SECHyperlink>::Create(hParentWnd, rect, lpszWindowName, dwStyle,NULL, nID);

		// verify that we created our window.
		_ASSERTE(::IsWindow(hWnd));
		if(::IsWindow(hWnd))
			return TRUE;

		return FALSE;
	}


// Operations
public:
	//@cmember
	/*Attaches the hyperlink to an existing control specified in a dialog resource*/
	inline BOOL AttachHyperlink(HWND hParentWnd, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE)
	{
		//First the parent window must be valid.
		_ASSERTE( hParentWnd );
		if(!::IsWindow(hParentWnd))
			return FALSE;
		
		RECT rc;
		SetRect(&rc,0,0,0,0);
		BOOL bRet = this->Create(hParentWnd,rc,nID,NULL,dwStyle);
		_ASSERTE( bRet );
		if(!bRet)
			return FALSE;

		//Get the control to replace
		CWindow wndParent,wndCtrl;
		wndParent.Attach(hParentWnd);
		HWND hCtrlToReplace =  wndParent.GetDlgItem(nID);

		// Test to verify that we did get a valid dialog item window.
		_ASSERTE(::IsWindow(hCtrlToReplace));
		if(!::IsWindow(hCtrlToReplace))
		{
			wndParent.Detach();
			return FALSE;
		}
		
		wndCtrl.Attach(hCtrlToReplace);

		// Save help context identifier so that context help will
		// continue to work
		DWORD dwContextHelpId = wndCtrl.GetWindowContextHelpId();

		RECT rcOld;
		wndCtrl.GetWindowRect(&rcOld);
		wndParent.ScreenToClient(&rcOld);
		
		// Position the new window 
		SetWindowPos(wndCtrl, rcOld.left, rcOld.top, rcOld.right-rcOld.left, rcOld.bottom-rcOld.top,
							SWP_SHOWWINDOW|SWP_NOREDRAW|SWP_NOACTIVATE);
		
		// Set the help context identifier
		SetWindowContextHelpId(dwContextHelpId);

		//Destroy the old control...we don't need it anymore
		wndCtrl.DestroyWindow();
		wndCtrl.Detach();
		wndParent.Detach();

		return bRet;
	}
	
	//@cmember
	/*Sets the string that will control the action to be taken*/
	virtual void SetHyperlink(const TCHAR* pStrLink)
	{
		m_strHyperlink.assign(pStrLink);
	}
	//@cmember
	/*Returns the hyperlink string*/
	virtual const TCHAR* GetHyperlink()
	{
		return m_strHyperlink.data();
	}
	//@cmember
	/*Sets a verb that specifies the action to be taken*/
	virtual void SetLinkVerb(const TCHAR* lpStrVerb)
	{
		m_strVerb.assign(lpStrVerb);
	}
	//@cmember
	/*Returns the verb specifying an action for the link*/
	virtual const TCHAR* GetLinkVerb()
	{
		return m_strVerb.data();
	}	
	//@cmember
	/*Sets the shell execution parameters*/
	virtual void SetLinkParams(const TCHAR* lpStrParams)
	{
		m_strParams.assign(lpStrParams);
	}
	//@cmember
	/*Returns the shell execution parameters*/
	virtual const TCHAR* GetLinkParams()
	{
		return m_strParams.data();
	}	
	//@cmember
	/*Sets the default directory for executing the link*/
	virtual void SetLinkDefDir(const TCHAR* lpStrDefDir)
	{
		m_strDefDir.assign(lpStrDefDir);
	}
	//@cmember
	/*Returns the default directory for the link execution*/
	virtual const TCHAR* GetLinkDefDir()
	{
		return m_strDefDir.data();
	}	
	//@cmember
	/*Sets the flags specifying the initial display state for the application*/
	virtual void SetLinkShowCmd(int nShowCmd)
	{
		m_nLinkShowCmd = nShowCmd;
	}
	//@cmember
	/*Returns the application display flags*/
	virtual int GetLinkShowCmd()
	{
		return m_nLinkShowCmd;
	}
	//@cmember
	/*Returns the display text string*/
	virtual const TCHAR* GetDisplayText()
	{
		return m_strDisplayText.data();
	}
	//@cmember
	/*Sets the string that will be shown to the end user*/
	virtual void SetDisplayText(const TCHAR* pStrDisplayText)
	{
		m_strDisplayText.assign(pStrDisplayText);
	}
	//@cmember
	/*Sets the color that will be used for the link when it has not been accessed*/
	virtual void SetClrDispTextNormal(COLORREF clrNormal)
	{
		m_clrDispTextNormal = clrNormal;
	}
	//@cmember
	/*Returns the color for the string when it has not been accessed*/
	virtual COLORREF GetClrDispTextNormal()
	{
		return m_clrDispTextNormal;
	}
	//@cmember
	/*Sets the color for the string after it has been accessed*/
	virtual void SetClrDispTextVisited(COLORREF clrVisited)
	{
		m_clrDispTextVisited = clrVisited;
	}
	//@cmember
	/*Returns the color for the string after it has been accessed*/
	virtual COLORREF GetClrDispTextVisited()
	{
		return m_clrDispTextVisited;
	}
	//@cmember
	/*Sets the link to it's visited state*/
	virtual void SetVisited(BOOL bVisited)
	{
		m_bVisited = bVisited;
	}
	//@cmember
	/*Returns TRUE if the link has been clicked on or set to the visited state*/
	virtual BOOL GetVisited()
	{
		return m_bVisited;
	}
	//@cmember
	/*Changes the display font to the one pointed to*/
	virtual void SetUserFont(HFONT hUserFont)
	{
		m_hUserFont = hUserFont;
	}
	//@cmember
	/*Returns a handle to the specified font. NULL if no font has been specified.*/
	virtual HFONT GetUserFont()
	{
		return m_hUserFont;
	}
	//@cmember
	/*Allows a different cursor to be shown when the mouse is over the hyperlink*/
	virtual void SetUserCursor(HCURSOR hUserCursor)
	{
		m_hUserCursor = hUserCursor;
	}
	//@cmember
	/*Returns a handle to the cursor being shown when the mouse is over the hyperlink*/
	virtual HCURSOR GetUserCursor()
	{
		return m_hUserCursor;
	}
	//@cmember
	/*Sets the size of the hyperlink window to exactly the size of the display text if TRUE.*/
	virtual void SizeToText(BOOL bReSize = TRUE)
	{
		m_bSizeToText = bReSize;
	}
	//@cmember
	/*Returns TRUE if the hyperlink window will be resized to fit the display text*/
	virtual BOOL GetSizeToText()
	{
		return m_bSizeToText;
	}
	//@cmember
	/*Allows the automatic execution of a hyperlind to be inhibited. Set to FALSE to inhibit execution.*/
	virtual void ExecuteLink(BOOL bExecute = TRUE)
	{
		m_bExecuteLink = bExecute;
	}
	//@cmember
	/*Returns a BOOL indicating if the link will automaticly execute*/
	virtual BOOL GetExecuteLink()
	{
		return m_bExecuteLink;
	}

public:
	BEGIN_MSG_MAP( SECHyperlink )
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP,OnLButtonUp)
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

	// Handlers
	inline LRESULT OnMouseMove(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		RECT rect;
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 
		POINT point;
		point.x = xPos;
		point.y = yPos;
		::GetClientRect(this->m_hWnd, &rect);

		if(::PtInRect(&rect, point))
		{
			SetCapture();
			if(NULL != m_hUserCursor )
			{
				m_hOldCursor = ::SetCursor(m_hUserCursor);
			}
			else
			{
#if (_ATL_VER < 0x0700)
				m_hOldCursor = SetCursor(::LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_BARS_HAND)));
#else
				m_hOldCursor = SetCursor(::LoadCursor(_AtlBaseModule.GetModuleInstance(), MAKEINTRESOURCE(IDC_BARS_HAND)));
#endif
			}
		}
		else 
		{
			SetCursor(m_hOldCursor);
			ReleaseCapture();
		}
		bHandled = TRUE;
		return 0l;
	}

	inline LRESULT OnLButtonUp(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		RECT rect;
		// Note:GET_X_LPARAM(lParam) and GET_Y_LPARAM(lParam);
		// are not being used because they don't exist in a pure MFC
		// framework. 
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 
		POINT point;
		point.x = xPos;
		point.y = yPos;
		::GetClientRect(this->m_hWnd, &rect);

		if(::PtInRect(&rect, point))
		{
			::ShellExecute( this->m_hWnd, GetLinkVerb(), GetHyperlink(), GetLinkParams(),
								GetLinkDefDir(), GetLinkShowCmd() );
			SetVisited(TRUE);
			Invalidate();
		}
		return 0l;
	}

	inline LRESULT OnPaint(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		HFONT hOldFont = NULL;
		COLORREF clrOld;
		PAINTSTRUCT ps;
		HDC hdc;	// device context for painting
		hdc = BeginPaint(&ps);

		int nDCRestore = ::SaveDC(hdc);
		
		// Check for a defined user font for the hyperlink.
		if(m_hUserFont != NULL)
		{
			hOldFont = (HFONT)::SelectObject(hdc, m_hUserFont);
		}

		// Has the link been hit in this session? If you wish, you can persist
		// this value. Set it in the control initialization to persist across
		// sessions.
		if(m_bVisited)
		{
			clrOld = ::SetTextColor(hdc, m_clrDispTextVisited);
		}
		else
		{
			clrOld = ::SetTextColor(hdc, m_clrDispTextNormal);
		}

		// Do we want to fit the display area to the text? 
		if(m_bSizeToText)
		{
			SIZE sizeNew;
			::GetTextExtentPoint32(hdc, GetDisplayText(), (int)_tcslen(GetDisplayText()), &sizeNew);
			SetWindowPos(GetParent(),0,0,sizeNew.cx,sizeNew.cy,SWP_NOMOVE|SWP_NOZORDER);
		}

		// Time to draw the text.
		int nOldMode = ::SetBkMode(hdc, TRANSPARENT);
		::TextOut(hdc, 0,0,GetDisplayText(), (int)_tcslen(GetDisplayText()));

		// Remove our changes to the DC.
		if(m_hUserFont)
			::SelectObject(hdc, hOldFont);
		::SetTextColor(hdc, clrOld);
		::SetBkMode(hdc, nOldMode);
		::RestoreDC(hdc, nDCRestore);
		::DeleteDC(hdc);
		this->EndPaint(&ps);
		
		bHandled = TRUE;

		return 0l;
	}

	inline LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// Don't call the default handler.
		return 0;
	}

// Attributes
protected:
	// These variables are modifyable via access functons.
	_string m_strVerb;
	_string m_strHyperlink;
	_string m_strParams;
	_string m_strDefDir;
	int m_nLinkShowCmd;
	_string m_strDisplayText;
	COLORREF m_clrDispTextNormal;
	COLORREF m_clrDispTextVisited;
	BOOL m_bExecuteLink;
	BOOL m_bVisited;
	BOOL m_bSizeToText;
	HFONT	m_hUserFont;
	HCURSOR m_hOldCursor;
	HCURSOR m_hUserCursor;
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined __SECHYPERLINK__
