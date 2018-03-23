///////////////////////////////////////////////////////////////////////////////
// SECRichHyperlink.h
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

#ifndef __SECRICHHYPERLINK__
#define __SECRICHHYPERLINK__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ATL headers
#include <atlbase.h>
#include <atlwin.h>
// Includes for the rich edit control
#include <richedit.h>
#include <richole.h>
// STL string
#include <foundation\stwarn.h>
#include <string>
#include <foundation\stwarnp.h>
// required for ShellExecute()
#include "shellapi.h"
#include "Foundation\SflRes.h"

// Always use the ASCII version of CHARFORMAT
typedef _charformat SECCharFormat;

#ifdef _UNICODE
typedef std::wstring _string;
#else
typedef std::string _string;
#endif //_UNICODE


/////////////////////////////////////////////////////////////////////////////
// SECRichHyperlink 
// AutoDuck tag block block for SECRichHyperlink

//@doc SECRichHyperlink
//@mdata Attrib | std::string | m_strHyperlink | Protected member that holds the hyperlink.
//@doc SECRichHyperlink
//@mdata Attrib | std::string | m_strDisplayText | Protected member that holds the text to be displayed.
//@doc SECRichHyperlink
//@mdata Attrib | COLORREF | m_clrBkgnd | Protected member that holds the COLORREF value set for the background color.
//@doc SECRichHyperlink
//@mdata Attrib | COLORREF | m_clrDispTextNormal | Protected member that holds the COLORREF of the display text in it's normal state.
//@doc SECRichHyperlink
//@mdata Attrib | COLORREF | m_clrDispTextVisited | Protected member that holds the COLORREF of the display text after it has been clicked on.
//@doc SECRichHyperlink
//@mdata Attrib | BOOL | m_bExecuteLink | Protected member that determinsed if the hyperlink will be executed. 
//@doc SECRichHyperlink
//@mdata Attrib | BOOL | m_bVisited | Protected member that indicates if the link has been visited.
//@doc SECRichHyperlink
//@mdata Attrib | BOOL | m_bSizeToText | Protected member that controls if the window will be resized to fit the text.
//@doc SECRichHyperlink
//@mdata Attrib | HFONT|  m_hUserFont | Protected member which holds a pointer to a font that the user has created for the display text.
//@doc SECRichHyperlink
//@mdata Attrib | HCURSOR | m_hUserCursor | Protected member that which holds a handle to a user specified cursor to be displayed when the mouse is over the hyperlink.
//@doc SECRichHyperlink
//@mdata Attrib | std::string | m_strStartActiveDelim | Protected member that holds the delimiter for the start of the hot text area.
//@doc SECRichHyperlink
//@mdata Attrib | std::string |  m_strEndActiveDelim | Protected member that holds the delimiter for the end of the hot text area.

//@doc SECRichHyperlink
//@mfunc  | SECRichHyperlink | SECRichHyperlink | Constructor for the SECRichHyperlink class.
//@xref <c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc BOOL  | SECRichHyperlink | Create | Creates the child window for the hyperlink and attaches it to it's parent window.
//@rdesc BOOL TRUE if successful; otherwise FALSE.
//@parm HWND | hParentWnd | Handle to the window that is the hyperlink’s parent or owner.
//@parm  RECT& | rect | The size and position of the hyperlink, in client coordinates of pParentWnd.
//@parm  UINT | nID | The ID of the hyperlink.
//@parm  LPCTSTR | lpszWindowName | Points to a string that contains the hyperlink's name. This is usually NULL. This default is supplied.
//@parm DWORD | dwStyle | Specifies the hyperlink’s style attributes. A default argument of WS_CHILD + WS_VISIBLE is supplied.
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc BOOL  | SECRichHyperlink | AttachHyperlink | Attaches an SECRichHyperlink object to an edit control.
//@rdesc BOOL TRUE if successful; otherwise FALSE.
//@parm HWND | hParentWnd | The parent of the dialog control you want to replace.
//@parm UINT | uID | The ID of the dialog control you want to replace with the SECRichHyperlink control.
//@parm DWORD | dwStyle | The window style of the SECRichHyperlink control.
//@xref <c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetHyperlink | Sets the string for the hyperlink.
//@parm const TCHAR* | lpStrLink | String specifying the hyperlink.
//@xref<mf SECRichHyperlink::GetHyperlink>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc const TCHAR*  | SECRichHyperlink | GetHyperlink | Returns the hyperlink string.
//@xref<mf SECRichHyperlink::SetHyperlink>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetLinkVerb | Sets the string specifying the hyperlink verb; default is "open". For a list of verbs, please refer to the SDK ::ShellExecute() documentation.
//@parm const TCHAR* | lpStrVerb | String specifying the verb.
//@xref<mf SECRichHyperlink::GetLinkVerb>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc const TCHAR*  | SECRichHyperlink | GetLinkVerb | Returns the hyperlink verb.
//@xref<mf SECRichHyperlink::SetLinkVerb>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc const TCHAR*  | SECRichHyperlink | GetLinkParams | Returns the execution parameters.
//@xref<mf SECRichHyperlink::SetLinkParams>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetLinkParams | Sets the parameters for executing the link.
//@parm const TCHAR* | lpStrParams | String specifying the parameters.
//@xref<mf SECRichHyperlink::GetLinkParams>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc const TCHAR*  | SECRichHyperlink | GetLinkDefDir | Returns a string containing the default directory.
//@xref<mf SECRichHyperlink::SetLinkDefDir>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetLinkDefDir | Sets the default directory.
//@parm const TCHAR* | lpStrDefDir | String specifying the default directory.
//@xref<mf SECRichHyperlink::GetLinkDefDir>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc int  | SECRichHyperlink | GetLinkShowCmd | Returns the application display flags.
//@xref<mf SECRichHyperlink::SetLinkShowCmd>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetLinkShowCmd | Sets the flags specifying the initial display state for the application associated with the link. 
//@parm int | nShowCmd | Flags specifying the initial display state. For a list of flags, please refer to the SDK ::ShellExecute() documentation.
//@xref<mf SECRichHyperlink::GetLinkShowCmd>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc const TCHAR*  | SECRichHyperlink | GetDisplayText | Returns the display text string.
//@xref<mf SECRichHyperlink::SetDisplayText>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetDisplayText | Sets the string that will be shown to the end user.
//@parm const TCHAR* | lpStrDisplayText | String specifying the display text.
//@xref<mf SECRichHyperlink::GetDisplayText>
//@xref<c SECRichHyperlink>
	
//@doc SECRichHyperlink
//@mfunc COLORREF  | SECRichHyperlink | GetClrBkgnd | Returns the color set for the control's background.
//@xref<mf SECRichHyperlink::SetClrBkgnd>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetClrBkgnd | Sets the background color for the control. CLR_BTNFACE is the default background color.
//@parm COLORREF | clrBkgnd | A COLORREF value.
//@xref<mf SECRichHyperlink::GetClrBkgnd>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc COLORREF  | SECRichHyperlink | GetClrDispTextNormal | Returns the color set for an unaccessed link.
//@xref<mf SECRichHyperlink::SetClrDispTextNormal>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetClrDispTextNormal | Sets the color that will be used for an unaccessed link. 
//@parm COLORREF | clrNormal | A COLORREF value.
//@xref<mf SECRichHyperlink::GetClrDispTextNormal>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc COLORREF  | SECRichHyperlink | GetClrDispTextHotTrack | Returns the color for the string when the mouse is over it.
//@xref<mf SECRichHyperlink::SetClrDispTextHotTrack>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetClrDispTextHotTrack | Sets the color for the string when the mouse is over it. 
//@parm COLORREF | clrHotTrack | A COLORREF value.
//@xref<mf SECRichHyperlink::GetClrDispTextHotTrack>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetClrDispTextVisited | Sets the color for the string after it has been accessed. 
//@parm COLORREF | clrVisited | A COLORREF value.
//@xref<mf SECRichHyperlink::GetClrDispTextVisited>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc COLORREF  | SECRichHyperlink | GetClrDispTextVisited | Returns the color for the string after it has been accessed.
//@xref<mf SECRichHyperlink::SetClrDispTextVisited>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetVisited | Sets the link to it's visited state. 
//@parm BOOL | bVisited | BOOL value specifying the visited state.
//@xref<mf SECRichHyperlink::GetVisited>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc BOOL  | SECRichHyperlink | GetVisited | Returns TRUE if the link has been clicked on or set to the visited state.
//@xref<mf SECRichHyperlink::SetVisited>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetUserFont | Sets the display font to the one passed in. 
//@parm HFONT | hUserFont | The display font.
//@xref<mf SECRichHyperlink::GetUserFont>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc HFONT  | SECRichHyperlink | GetUserFont | Returns a handle to the specified font.
//@xref<mf SECRichHyperlink::SetUserFont>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetUserCursor | Sets the cursor to be shown when the mouse is over the hyperlink. 
//@parm HCURSOR | hUserCursor | The display cursor.
//@xref<mf SECRichHyperlink::GetUserCursor>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc HCURSOR  | SECRichHyperlink | GetUserCursor | Returns a handle to the cursor.
//@xref<mf SECRichHyperlink::SetUserCursor>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SetColdCursor | Sets the cursor to be shown when the mouse is over the cold portion of the hyperlink. 
//@parm HCURSOR | hColdCursor | The cold cursor.
//@xref<mf SECRichHyperlink::GetColdCursor>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc HCURSOR  | SECRichHyperlink | GetColdCursor | Returns a handle to the cold cursor.
//@xref<mf SECRichHyperlink::SetColdCursor>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | SizeToText | If TRUE, sizes the hyperlink window to the size of the display text. 
//@parm BOOL | bReSize | FALSE for non-resizing; Default is TRUE.
//@xref<mf SECRichHyperlink::GetSizeToText>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc BOOL  | SECRichHyperlink | GetSizeToText | Returns the resizing mode. If TRUE then resizing is enabled.
//@xref<mf SECRichHyperlink::SizeToText>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc void  | SECRichHyperlink | ExecuteLink | Allows the automatic execution of a hyperlink to be inhibited. Set to FALSE to inhibit execution. 
//@parm BOOL | bExecute | Default is TRUE.
//@xref<mf SECRichHyperlink::GetExecuteLink>
//@xref<c SECRichHyperlink>

//@doc SECRichHyperlink
//@mfunc BOOL  | SECRichHyperlink | GetExecuteLink | Returns the auto execute mode. If TRUE then execution is enabled.
//@xref<mf SECRichHyperlink::Execute>
//@xref<c SECRichHyperlink>

// adinsert AutoDuck insertion point for SECRichHyperlink
//@doc SECRichHyperlink
//@class SECRichHyperlink 
//@comm The SECRichHyperlink class is a browser independent class for providing
// a simple link to a registered internet resource. The most common sorts of
// resources are web resources (HTTP://xxxx.yyy.zzz), email resources 
// (mailto:someone@somewhere.com) and ftp resources. This differs from the 
// SECHyperlink class in that it superclasses a rich edit control and thereby makes use of 
// the rich edit's enhanced display/formatting capabilities for the text. SECRichHyperlink allows
// there to be a subset of the text that contains the link. This
// control supports one link in a given string. 
//
// Usage of this class can be done by either calling the create function or by
// attaching the SECRichHyperlink control to an existing control located on a dialog.
// Using the existing control simplifies layout by allowing the resource editor to
// be used to position the control.
//@base public | CWindowImpl
class SECRichHyperlink : public CWindowImpl<SECRichHyperlink>
{
typedef CWindowImpl<SECRichHyperlink> BASE;

public:
DECLARE_WND_SUPERCLASS( NULL, _T("RICHEDIT") )

// Construction
	//@cmember
	/* Constructor */
	inline SECRichHyperlink()
	{
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

		m_strStartActiveDelim = _T("<");
		m_strEndActiveDelim = _T(">");
		m_hColdCursor = NULL;
		m_clrBkgnd	= ::GetSysColor(COLOR_BTNFACE);
		m_clrDispTextNormal = RGB(0,0,255);
		m_clrDispTextVisited = RGB(0,0,128);
		m_clrDispTextHotTrack = RGB(255,0,0);
		m_hRichEditLib = NULL;
		// make sure the rich edit dll that we want is loaded.
		m_hRichEditLib = ::LoadLibrary(_T("RICHED32.DLL"));
		_ASSERTE(m_hRichEditLib != NULL);
	}

	virtual ~SECRichHyperlink()
	{
		// Free the dll we loaded.
		if(m_hRichEditLib)
			::FreeLibrary(m_hRichEditLib);
	}

// Utility functions that provide a convenient subset of the Rich Edit API
	inline BOOL SetDefaultCharFormat(SECCharFormat &cf) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		cf.cbSize = sizeof(SECCharFormat);
		return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}

	inline BOOL GetDefaultCharFormat(SECCharFormat &cf) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		cf.cbSize = sizeof(SECCharFormat);
		return (BOOL)::SendMessage(m_hWnd, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}

	inline void HideSelection(BOOL bHide, BOOL bPerm)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, EM_HIDESELECTION, bHide, bPerm);
	}

	inline void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, EM_SETSEL, nStartChar, nEndChar);
		if(!bNoScroll)
			::SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0L);
	}

	inline BOOL SetSelectionCharFormat(SECCharFormat &cf)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		cf.cbSize = sizeof(SECCharFormat);
		return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	inline BOOL GetSelectionCharFormat(SECCharFormat &cf)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		cf.cbSize = sizeof(SECCharFormat);
		return (BOOL)::SendMessage(m_hWnd, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	inline long GetSelText(LPTSTR lpBuf) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (long)::SendMessage(m_hWnd, EM_GETSELTEXT, 0, (LPARAM)lpBuf);
	}

	inline void GetSel(int& nStartChar, int& nEndChar) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&nStartChar, (LPARAM)&nEndChar);
	}

public:
// Overrides
	//@cmember 
	/*Creates the child window for the hyperlink and attaches it to it's parent window.*/
	inline BOOL Create(HWND hParentWnd, RECT& rect, UINT nID, LPCTSTR lpszWindowName = NULL, DWORD dwStyle = WS_CHILD|WS_VISIBLE)
	{
		m_bEmbeddedTag = TRUE;
		BOOL bRet;
		_ASSERTE(::IsWindow(hParentWnd));
		if(!::IsWindow(hParentWnd))
		{
			return FALSE;
		}

		HWND hWnd = BASE::Create(hParentWnd, rect, lpszWindowName, dwStyle|ES_MULTILINE, 0, nID);

		_ASSERTE(::IsWindow(hWnd));
		if (!::IsWindow(hWnd))
		{
			//DWORD dwError = GetLastError();
			bRet = FALSE;
		}
		else
		{
			bRet = TRUE;
		}
		if(bRet)
		{
			// Set the event mask so that the parent gets notified when the text
			// of the rich edit control changes. 
			SendMessage(EM_SETEVENTMASK,0,ENM_MOUSEEVENTS);
			// This is static text, so prevent the end user from changing
			// it.
			SendMessage(EM_SETREADONLY, TRUE, 0L);
			// Sets the background color for the rich edit control to 'm_clrBkgnd'
			SendMessage(EM_SETBKGNDCOLOR, 0, (LPARAM)m_clrBkgnd);

			// Are there delimiters that will change the way the text is to be
			// shown?
			m_nHotStart = (int)m_strDisplayText.find(m_strStartActiveDelim);
			m_nHotEnd = (int)m_strDisplayText.find(m_strEndActiveDelim);
			if(m_nHotStart < 0)
			{
				m_nHotStart = 0;
				m_nHotEnd = (int)m_strDisplayText.size();
				m_strScreenText = m_strDisplayText;
				m_bEmbeddedTag = FALSE;
			}
			if(m_nHotEnd < 0)
			{
				m_nHotEnd = (int)m_strDisplayText.size();
			}
			// If the delimiters are present, remove them from the text string.
			if(m_bEmbeddedTag)
			{
				m_strScreenText = m_strDisplayText.substr(0,m_nHotStart);
				m_strScreenText += m_strDisplayText.substr(m_nHotStart+1, (m_nHotEnd-1)-m_nHotStart);
				m_strScreenText += m_strDisplayText.substr(m_nHotEnd+1,	m_strDisplayText.size()-(m_nHotEnd+1));
				// Compensate for removing the delimiter.
				m_nHotEnd--;
			}
			// If a user-font has been assigned, then make this the default window font.
			if(m_hUserFont)
				SetFont(m_hUserFont, FALSE);
			// Now that we've determined what the text should look like
			// let's put it into the rich edit control.
			SetWindowText(m_strScreenText.data());			
			
			// Now it's time to color the text appropriately.
			SECCharFormat CharFormat;
			GetDefaultCharFormat(CharFormat);
			HideSelection(TRUE,TRUE);
			SetSel(m_nHotStart,m_nHotEnd);
			CharFormat.crTextColor = m_clrDispTextNormal;
			CharFormat.dwMask = CFM_COLOR;
			CharFormat.dwEffects = CFE_PROTECTED;
			SetSelectionCharFormat(CharFormat);
			if(m_bSizeToText)
			{
				HDC dc = GetDC();
				SIZE sizeNew;
				GetTextExtentPoint32(dc, m_strScreenText.data(), (int)_tcslen(m_strScreenText.data()), &sizeNew);
				SetWindowPos(GetParent(),0,0,sizeNew.cx,sizeNew.cy,SWP_NOMOVE|SWP_NOZORDER);
				ReleaseDC(dc); 
			}
		}
		return bRet;
	}
	
// Operations
public:
	//@cmember
	/*Attaches the hyperlink to an existing control specified in a dialog resource.*/
	inline BOOL AttachHyperlink( HWND hParentWnd, UINT nID, DWORD dwStyle = WS_CHILD|WS_VISIBLE)
	{
		//First the parent window must be valid.
		_ASSERTE( hParentWnd );
		if(!::IsWindow(hParentWnd))
			return FALSE;

		CWindow wndParent,wndCtrl;
		wndParent.Attach(hParentWnd);

		//Get the control to replace
		HWND hCtrlToReplace =  wndParent.GetDlgItem(nID);

		// Test to verify that we did get a valid dialog item window.
		_ASSERTE(::IsWindow(hCtrlToReplace));
		if(!::IsWindow(hCtrlToReplace))
		{
			wndParent.Detach();
			return FALSE;
		}
		wndCtrl.Attach(hCtrlToReplace);

		RECT rcOld;
		wndCtrl.GetWindowRect(&rcOld);
		wndParent.ScreenToClient(&rcOld);

		// Save help context identifier so that context help will
		// continue to work
		DWORD dwContextHelpId = wndCtrl.GetWindowContextHelpId();
		
		BOOL bRet = Create(hParentWnd, rcOld,nID,NULL,dwStyle);
		_ASSERTE( bRet );
		if(!bRet)
			return FALSE;

		// Position the new window 
		if(!m_bSizeToText)
			SetWindowPos(wndCtrl, rcOld.left, rcOld.top, rcOld.right-rcOld.left, rcOld.bottom-rcOld.top, SWP_NOREDRAW|SWP_NOACTIVATE);
		
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
	virtual void SetHyperlink(const TCHAR* lpStrLink)
	{
		m_strHyperlink.assign(lpStrLink);
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
	/*Sets the string that will be shown to the end user*/
	virtual void SetDisplayText(const TCHAR* lpStrDisplayText)
	{
		m_strDisplayText.assign(lpStrDisplayText);
	}
	//@cmember
	/*Returns the display text string*/
	virtual const TCHAR* GetDisplayText()
	{
		return m_strDisplayText.data();
	}
	//@cmember
	/*Sets the background color for the control*/
	virtual void SetClrBkgnd(COLORREF clrBkgnd)
	{
		m_clrBkgnd = clrBkgnd;
	}
	//@cmember
	/*Returns the background color*/
	virtual COLORREF GetClrBkgnd()
	{
		return m_clrBkgnd;
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
	/*Sets the color for the string when the mouse is over it*/
	virtual void SetClrDispTextHotTrack(COLORREF clrHotTrack)
	{
		m_clrDispTextHotTrack = clrHotTrack;
	}
	//@cmember
	/*Returns the color for the string when the mouse is over it*/
	virtual COLORREF GetClrDispTextHotTrack()
	{
		return m_clrDispTextHotTrack;
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
	/*Allows a different cursor to be shown when the mouse is over the cold portion of the hyperlink*/
	virtual void SetColdCursor(HCURSOR hColdCursor)
	{
		m_hColdCursor = hColdCursor;
	}
	//@cmember
	/*Returns a handle to the cursor being shown when the mouse is over the cold portion of the hyperlink*/
	virtual HCURSOR GetColdCursor()
	{
		return m_hColdCursor;
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
	BEGIN_MSG_MAP( SECRichHyperlink )
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP,OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDOWN,OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
	END_MSG_MAP()

// message map handlers
	inline LRESULT OnMouseMove(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		RECT rectFull;
		BOOL bHot = FALSE;

		// Note:GET_X_LPARAM(lParam) and GET_Y_LPARAM(lParam);
		// are not being used because they don't exist in a pure MFC
		// framework.
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 

		POINT point;
		point.x = xPos;
		point.y = yPos;
		GetClientRect(&rectFull);
		if(m_bEmbeddedTag)
		{
			HDC dc = this->GetDC();
			TCHAR szText[1024] = { '\0' };
			int nStart,nEnd;
			GetSel(nStart,nEnd);
			int nLnBegin = static_cast<int>(SendMessage( EM_LINEFROMCHAR, nStart, 0L ));
			int nLnEnd   = static_cast<int>(SendMessage( EM_LINEFROMCHAR, nEnd, 0L ));
			for( int i = nLnBegin; (i <= nLnEnd) && !bHot; i++ )
			{
				int nLnPos = static_cast<int>(SendMessage( EM_LINEINDEX, i, 0L ));
				int nLnLen = static_cast<int>(SendMessage( EM_LINELENGTH, nLnPos, 0L ));
				int nLocalStart = max( nLnPos, nStart );
				int nLocalEnd   = min( nLnPos + nLnLen, nEnd );
				m_strScreenText.copy(szText, nLocalEnd-nLocalStart, nLocalStart);
				SIZE sizeText;
				GetTextExtentPoint32(dc, szText, (int)_tcslen(szText), &sizeText);
				POINT ptStart;
				SendMessage(EM_POSFROMCHAR, (WPARAM)&ptStart, (LPARAM)nLocalStart);
				RECT rectHot;
				::SetRect(&rectHot, ptStart.x,ptStart.y,ptStart.x+sizeText.cx,ptStart.y+sizeText.cy);
				bHot = PtInRect( &rectHot, point );
			}
			ReleaseDC(dc);
		}
		else
		{
			GetClientRect(&rectFull);
			bHot = TRUE;
		}

		if(PtInRect(&rectFull, point))
		{
			if(m_hOldCursor == NULL)
				m_hOldCursor = GetCursor();
			if(GetCapture() != this->m_hWnd)
				::SetCapture(this->m_hWnd);
			if(bHot)
			{
				SECCharFormat CharFormat, CharFormatSel;
				CharFormat.cbSize = sizeof(SECCharFormat);
				GetDefaultCharFormat(CharFormat);
				HideSelection(TRUE,TRUE);
				SetSel(m_nHotStart,m_nHotEnd);
				CharFormatSel.cbSize = sizeof(SECCharFormat);
				CharFormatSel.dwMask = CFM_COLOR;
				GetSelectionCharFormat(CharFormatSel);
				if(CharFormatSel.crTextColor != m_clrDispTextHotTrack)
				{
					CharFormat.crTextColor = m_clrDispTextHotTrack;
					CharFormat.dwMask = CFM_COLOR;
					CharFormat.dwEffects = CFE_PROTECTED;
					SetSelectionCharFormat(CharFormat);
				}

				if(NULL != m_hUserCursor)
				{
					if(GetCursor() != m_hUserCursor)
						::SetCursor(m_hUserCursor);
				}
				else
				{	
					m_hUserCursor = ::LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_BARS_HAND));
					// If the following ASSERT fires then it is likely that you have not added the SFL resources to your project.
					// Please include the 'foundation\sflres.h' and 'foundation\sfl.rc' files as compile time resources. 
					_ASSERTE(m_hUserCursor != NULL);
					SetCursor(m_hUserCursor);
				}
			}
			else
			{
				SECCharFormat CharFormat;
				GetDefaultCharFormat(CharFormat);
				HideSelection(TRUE,TRUE);
				SetSel(m_nHotStart,m_nHotEnd);
				if(m_bVisited)
				{
					CharFormat.crTextColor = m_clrDispTextVisited;
				}
				else
				{
					CharFormat.crTextColor = m_clrDispTextNormal;
				}

				CharFormat.dwMask = CFM_COLOR;
				CharFormat.dwEffects = CFE_PROTECTED;			
				SetSelectionCharFormat(CharFormat);
				SetCursor(m_hOldCursor);
			}

		}
		else if(!PtInRect(&rectFull, point) && (::GetCapture()== this->m_hWnd))
		{
			SECCharFormat CharFormat;
			GetDefaultCharFormat(CharFormat);
			HideSelection(TRUE,TRUE);
			SetSel(m_nHotStart,m_nHotEnd);
			if(m_bVisited)
			{
				CharFormat.crTextColor = m_clrDispTextVisited;
			}
			else
			{
				CharFormat.crTextColor = m_clrDispTextNormal;
			}

			CharFormat.dwMask = CFM_COLOR;
			CharFormat.dwEffects = CFE_PROTECTED;			
			SetSelectionCharFormat(CharFormat);
			SetCursor(m_hOldCursor);
			::ReleaseCapture();
		}
		
		bHandled = TRUE;
		return 0l;
	}
		
	inline LRESULT OnLButtonUp(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		RECT rectFull;
		BOOL bHot = FALSE;

		// Note:GET_X_LPARAM(lParam) and GET_Y_LPARAM(lParam);
		// are not being used because they don't exist in a pure MFC
		// framework.
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 

		POINT point;
		point.x = xPos;
		point.y = yPos;
		GetClientRect(&rectFull);
		if(m_bEmbeddedTag)
		{
			HDC dc = this->GetDC();
			TCHAR szText[1024] = { '\0' };
			int nStart,nEnd;
			GetSel(nStart,nEnd);
			int nLnBegin = static_cast<int>(SendMessage( EM_LINEFROMCHAR, nStart, 0L ));
			int nLnEnd   = static_cast<int>(SendMessage( EM_LINEFROMCHAR, nEnd, 0L ));
			for( int i = nLnBegin; (i <= nLnEnd) && !bHot; i++ )
			{
				int nLnPos = static_cast<int>(SendMessage( EM_LINEINDEX, i, 0L ));
				int nLnLen = static_cast<int>(SendMessage( EM_LINELENGTH, nLnPos, 0L ));
				int nLocalStart = max( nLnPos, nStart );
				int nLocalEnd   = min( nLnPos + nLnLen, nEnd );
				m_strScreenText.copy(szText, nLocalEnd-nLocalStart, nLocalStart);
				SIZE sizeText;
				GetTextExtentPoint32(dc, szText, (int)_tcslen(szText), &sizeText);
				POINT ptStart;
				SendMessage(EM_POSFROMCHAR, (WPARAM)&ptStart, (LPARAM)nLocalStart);
				RECT rectHot;
				::SetRect(&rectHot, ptStart.x,ptStart.y,ptStart.x+sizeText.cx,ptStart.y+sizeText.cy);
				bHot = PtInRect( &rectHot, point );
			}
			ReleaseDC(dc);
		}
		else
		{
			GetClientRect(&rectFull);
			bHot = TRUE;
		}

		if(bHot)
		{
			if(m_bExecuteLink)
			{
				::ShellExecute( this->m_hWnd, GetLinkVerb(), GetHyperlink(), GetLinkParams(),
									GetLinkDefDir(), GetLinkShowCmd() );	

			}
			SetVisited(TRUE);
			SECCharFormat CharFormat;
			GetDefaultCharFormat(CharFormat);
			HideSelection(TRUE,TRUE);
			SetSel(m_nHotStart,m_nHotEnd);
			CharFormat.crTextColor = m_clrDispTextVisited;
			CharFormat.dwMask = CFM_COLOR;
			CharFormat.dwEffects = CFE_PROTECTED;
			SetSelectionCharFormat(CharFormat);			
			Invalidate();
		}

		return 0l;
	}

	inline LRESULT OnLButtonDown(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// We don't want to call the default LButtonDown handler because 
		// this invokes default editing behavior for the CRichEditControl.

		bHandled = TRUE;
		return 0l;
	}

	inline LRESULT OnLButtonDblClk(UINT /*nMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Treat double clicks as a singe click
		return OnLButtonDown(WM_LBUTTONDOWN, wParam, lParam, bHandled);
	}

	LRESULT OnSetCursor(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// if a cold cursor has not been set, then use the cursor associated with the parent window class
		if(m_hColdCursor == NULL)
#ifdef _WIN64
			SetCursor((HCURSOR)GetClassLongPtr(GetParent(), GCLP_HCURSOR));
#else	//WIN32
			SetCursor((HCURSOR)GetClassLong(GetParent(), GCL_HCURSOR));
#endif	//_WIN64
		else
			SetCursor(m_hColdCursor);

		bHandled = TRUE;
		return 0L;
	}

	inline LRESULT OnNotify(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		MSGFILTER* pMsg = (MSGFILTER*)lParam;
		if(WM_MOUSEMOVE == pMsg->msg)
		{
			OnMouseMove(pMsg->msg,pMsg->wParam,pMsg->lParam,bHandled);
		}
		if(WM_LBUTTONDOWN == pMsg->msg)
		{
			OnLButtonDown(pMsg->msg,pMsg->wParam,pMsg->lParam,bHandled);
		}
		if(WM_LBUTTONUP == pMsg->msg)
		{
			OnLButtonUp(pMsg->msg,pMsg->wParam,pMsg->lParam,bHandled);
		}
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
	_string m_strScreenText;
	COLORREF m_clrBkgnd;
	COLORREF m_clrDispTextNormal;
	COLORREF m_clrDispTextVisited;
	COLORREF m_clrDispTextHotTrack;
	BOOL m_bExecuteLink;
	BOOL m_bVisited;
	BOOL m_bSizeToText;
	HFONT m_hUserFont;
	HCURSOR m_hOldCursor;
	HCURSOR m_hUserCursor;
	HCURSOR m_hColdCursor;
	_string m_strStartActiveDelim;
	_string m_strEndActiveDelim;

	// These variables are NOT user-modifyable.
	// These variables control the state of the control.
	int m_nHotStart;
	int m_nHotEnd;
	BOOL m_bEmbeddedTag;
	HINSTANCE m_hRichEditLib;
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined __SECRICHHYPERLINK__
