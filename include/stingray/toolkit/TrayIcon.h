///////////////////////////////////////////////////////////////////////////////
// TrayIcon.h : Declaration of SECTrayIcon
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

#ifndef __SEC_TRAYICON_H
#define __SEC_TRAYICON_H

#include <StingrayExportDefs.h>

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

// Default Tray Icon notification message
#define WM_SEC_TRAYICON_NOTIFY	WM_USER+1025


//@doc SECTrayIcon
//@mfunc UINT | SECTrayIcon | GetNotifyID | Returns the current notification ID for this object.
//@rdesc The notification ID.
//@xref<c SECTrayIcon>


//@doc SECTrayIcon
//@mfunc BOOL | SECTrayIcon | IsPlaying | Call this function to query if animation is in progress. 
//@rdesc Returns TRUE if animation is in progress; FALSE otherwise.
//@xref<c SECTrayIcon>

	

//@doc SECTrayIcon 
//@class Windows 95-style System Tray icon functionality. The SECTrayIcon class provides your application with an easy to use mechanism
// to add your own custom icons to the system tray, providing neat UI feedback such as tooltip text, context menu support,
// and animated icons.
//@comm The TRAYICON sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\TRAYICON directory demonstrates the SECTrayIcon class.
//@BASE public|CObject
class SECTrayIcon : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC( SECTrayIcon )

public:
    // construction/destruction
    TOOLKIT_API SECTrayIcon();
    TOOLKIT_API virtual ~SECTrayIcon();

	//@access Creation/Destruction

	//@cmember
	/* Create the tray icon.*/
    TOOLKIT_API virtual void Create(CWnd* pwnd, UINT nNotifyID,
						UINT nMsg=WM_SEC_TRAYICON_NOTIFY, 
						HINSTANCE hinst = ::AfxGetResourceHandle());

	//@cmember
	/* Create the tray icon.*/
    TOOLKIT_API virtual void Create(CWnd* pwnd, 
						UINT nMsg=WM_SEC_TRAYICON_NOTIFY, 
						HINSTANCE hinst = ::AfxGetResourceHandle());

	//@cmember
	/* Destroy the tray icon.*/
    TOOLKIT_API virtual void Destroy();

	//@access Attributes

	//@cmember
	/* Set the tooltip text.*/
    TOOLKIT_API virtual void SetTip(const CString& sTip);

	//@cmember
	/* Set the associated tray icon.*/
    TOOLKIT_API virtual void SetIcon(UINT nIconID);

	//@cmember
	/* Set the associated tray icon.*/
    TOOLKIT_API virtual void SetIcon(LPCTSTR szIconID);

	//@cmember
	/* Set the associated tray icon.*/
    TOOLKIT_API virtual void SetIcon(HICON hIcon);

	//@cmember
	/* Set the current tray icon state.*/
    TOOLKIT_API virtual void  SetState(SEC_DWORD nState);

	//@cmember
	/* Get the current tray icon state.*/
    TOOLKIT_API virtual SEC_DWORD GetState();

    //@cmember
    /* Add a tray icon state.*/
    TOOLKIT_API virtual void AddState(SEC_DWORD nState, UINT nIconID, const CString& sTip, UINT nJiffy = 15);

    //@cmember
    /* Add a tray icon state.*/
    TOOLKIT_API virtual void AddState(SEC_DWORD nState, LPCTSTR szIconID, const CString& sTip, UINT nJiffy = 15);

    //@cmember
    /* Add a tray icon state.*/
    TOOLKIT_API virtual void AddState(SEC_DWORD nState, HICON hIcon, const CString& sTip, UINT nJiffy = 15);

    //@cmember
    /* Remove a tray icon state.*/
    TOOLKIT_API virtual void RemoveState(SEC_DWORD nState);

	//@access Operations

	//@cmember
	/* Show/hide the tray icon.*/
    TOOLKIT_API virtual void Show(BOOL bShow = TRUE);

    //@cmember
    /* Play an icon animation.*/
    TOOLKIT_API virtual void Play(SEC_DWORD nBaseState, UINT nStates);

	//@cmember
	/* Stop an icon animation.*/
    TOOLKIT_API virtual void Stop();

	//@cmember
	/* Queries whether animation is in progress.*/
	inline BOOL IsPlaying() { return (BOOL)m_nTimerID; }

    //@cmember
    /* Show tray icon context menu.*/
    TOOLKIT_API static void ShowContextMenu(CWnd* pwnd, UINT nMenuID, UINT nSubMenu = 0);

    //@cmember
    /* Show tray icon context menu.*/
    TOOLKIT_API static void ShowContextMenu(CWnd* pwnd, LPCTSTR szMenuID, UINT nSubMenu = 0);

	// Default notification id recall

	//@cmember
	/* Get next available id for tray icon notification.*/
	TOOLKIT_API static UINT GetNextNotifyID();

	//@cmember
	/* Get the latest allocated nofitication id.*/
	TOOLKIT_API static UINT GetLatestNotifyID();

	
	//@cmember
	/* Get the objects' current notification ID.*/
	inline UINT GetNotifyID() { return m_nNotifyID; }

protected:
    TOOLKIT_API static BOOL s_bAnimWndClassRegistered;
	TOOLKIT_API static UINT s_nNextNotifyID;

    UINT        m_nNotifyID;
    HWND        m_hwnd;
    UINT        m_nMsg;
    SEC_DWORD   m_nCurrentState;
    BOOL        m_bShowing;
    HINSTANCE   m_hinst;
    SEC_UINT    m_nTimerID;
    HWND        m_hwndTimer;
    SEC_DWORD   m_nAnimBaseState;
    UINT        m_nAnimStates;
    UINT        m_nAnimOffset;
	CMapPtrToPtr    m_mapStateData;

    struct TOOLKIT_API STATEDATA
    {
        HICON   hicon;
        CString sTip;
        UINT    nJiffy;

        STATEDATA(HICON hicon, const CString& sTip, UINT nJiffy)
            : hicon(hicon), sTip(sTip), nJiffy(nJiffy) {}
    };
 
    TOOLKIT_API BOOL    GetStateData(SEC_DWORD nState, HICON* phicon, CString* psTip, UINT* pnJiffy);
    TOOLKIT_API void    SetStateData(SEC_DWORD nState, HICON hicon, const CString& sTip, UINT nJiffy);
    TOOLKIT_API void    OnTimer();
    // Shell_NotifyIcon() wrapper
    TOOLKIT_API BOOL    ShellNotifyIcon(DWORD nMsg);

    TOOLKIT_API friend LRESULT CALLBACK AnimWndProc(HWND, UINT, WPARAM, LPARAM);
};


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// WIN32

#endif  // __SEC_TRAYICON_H

