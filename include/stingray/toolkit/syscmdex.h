///////////////////////////////////////////////////////////////////////////////
// syscmdex.h
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
//  Author:       Bill Martschenko
//  Description:  Declarations for WM_SYSCOMMANDEX extension to WM_SYSCOMMAND
//  Created:      Sep 1997
//
/////////////////////////////////////////////////////////////////////////////
// Hierarchy of objects in this file.  Objects in () are defined elsewhere.
//
//   (CObject)
//   |-- (SECMsgFilter)
//       |-- (SECNcMsgFilter)
//           |-- (SECCaptionMsgFilter)
//               |-- (SECCaptionControlMsgFilter)
//                   |-- ScxButtonMsgFilter
//                       |-- ScxButtonMDIMaxChildMsgFilter
//                       |-- ScxButtonMDIChildMsgFilter
//               |-- ScxCaptionNCRDBLClkFilter
//          |-- ScxNCRDBLClkMDIMaxChildMsgFilter
//       |-- ScxMsgFilter
//		 |-- ScxContextMenuFilter
//
//   The classes beginning with Scx are in the namespace nsSysCommandEx.
/////////////////////////////////////////////////////////////////////////////
#ifdef WIN32

#ifndef __SYSCMDEX_H__
#define __SYSCMDEX_H__

// disable warning 4097:  typedef-name 'Super' used as synonym for class-name 'XXX'
#ifndef __SMSGFILT_H__
#include "toolkit\smsgfilt.h"
#endif // #ifndef __SMSGFILT_H__

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // #ifndef __AFXTEMPL_H__

#ifndef __SBARDOCK_H__
#include "toolkit\SBarDock.h"
#endif

//#include <StingrayExportDefs.h>

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

// WM_SYSCOMMANDEX
// ---------------
//   extended WM_SYSCOMMAND message.  See the SCX_ constants below for the valid values
//   for the wParam and lParam to this message as well as return values.
//
#define WM_SYSCOMMANDEX ::RegisterWindowMessage(_T("Stingray::WM_SYSCOMMANDEX"))

// ON_WM_SYSCOMMANDEX()
// --------------------
//   message map macros to use that defines a handler for WM_SYSCOMMANDEX.  Use the following
//   entry in the class declaration.
//
//        afx_msg LRESULT OnSysCommandEx ( WPARAM nID, LPARAM lParam );
//
//   In the message map, a global variable must be used because WM_SYSCOMMANDEX is a registered message.
//   Here is an example.
//
//        DEFINE_REGISTERED_MSGID_VAR(WM_SYSCOMMANDEX)
//        BEGIN_MESSAGE_MAP(...)
//             ON_WM_SYSCOMMANDEX()
//             ...
//        END_MESSAGE_MAP()
//
#define ON_WM_SYSCOMMANDEX() ON_REGISTERED_MESSAGE(REGISTERED_MSGID_VAR(WM_SYSCOMMANDEX), OnSysCommandEx)

// SCX_ constants for the WPARAM to WM_SYSCOMMANDEX
// ------------------------------------------------
//   Note:  Least significant 4 bits reserved for internal use
//          --> all hex values end in a zero
//          WM_SYSCOMMANDEX handlers must only use (wParam & 0xFFF0).
//          This is the same behavior as for WM_SYSCOMMAND.
//
//   Let pExInfo = reinterpret_cast<SECScxInfo*>(lParam).
//   pExInfo is referred to below with the description of each extended system command.
//
//   Note that the handler of WM_SYSCOMMANDEX does NOT delete pExInfo.
//   The caller owns the pExInfo pointer.  This is the convention followed in Win32 messages.
//   It is a little tricky for the caller because the recommendation is to use
//   PostMessage(WM_SYSCOMMANDEX, ...) when a new frame type command is sent.  See below.
//
//
//   SCX_NEWFRAME
//        indicates that a new frame type is needed.
//
//        pExInfo->m_hwnd = target for the frame type change
//        pExInfo->m_rc = rectangle in screen coordinates for the control (e.g., button in caption) 
//                        whose use (e.g., pressing the button) caused this message to be fired
//                        CRect(0,0,0,0) indicates no such control.
//        pExInfo->m_pt = point in screen coordinates with pExInfo->m_rc that the user clicked 
//                        with the mouse.  CPoint(-1,-1) indicates no such point.
//                        if pExInfo->m_rc is not all zeroes, this point can be any coordinate pair.
//                        special case:  see pExInfo->m_dwFlags
//        pExInfo->m_dw[0] = id (required) of the new frame where (DWORD)-1 means default 
//                           frame change for the current frame type of pExInfo->m_hwnd.
//                           The handler of the message defines the ids.  The expectation is
//                           the ids are an enumeration that is used to populate the
//                           NewFrame menu (see SCX_SELECTNEWFRAME below).  While not required,
//                           the builder of the menu is expected to be the same window that 
//                           handles the menu selection.
//        pExInfo->m_dwFlags:  bitwise-or of the following flags
//             SCXFLAG_INITIALPOS  -- means that pExInfo->m_pt contains the offset for the frame
//                                    currently only supported for a floating frame or mdi child frame.
//                                    m_pt will be used with SetWindowPos(); see that function for 
//                                    whether the point should be in screen coordinates.
//             SCXFLAG_INITIALSIZE -- means that pExInfo->m_sz contains the size for the frame
//                                    currently only supported for a floating frame or mdichild frame.
//
//        Other fields are unused and must be zero.
//
//        Recommendation to senders:  Use PostMessage() because the target of the message
//             (a frame window) will delete itself to make way for the new frame.
//             If SendMessage() is used, then upon return, caution is needed because the
//             the target of the SendMessage() no longer exists.
//
//        Return value:  1 on success and 0 on failure.  This message has no output parameters in pExInfo
//                       intentionally.  For example, the HWND of the new frame is NOT recorded in pExInfo->m_hwnd
//                       on output.  Reason:  To avoid hiding a subtle dependency, this message handler allows
//                       for the possibility that the pExInfo instance is deleted when the original frame is
//                       destroyed (e.g., pExInfo is a data member of the frame).
//
//   SCX_QUERYMENUFORNEWFRAME
//        indicates that a menu to select a new frame is needed.
//
//        pExInfo->m_hwnd = target for the frame type change
//        Other fields are unused and must be zero.
//
//        Return value:  1 on success and 0 on value.  If 1 is returned, then pExInfo->m_handle is the 
//                       handle to the menu.  Otherwise, pExInfo->m_handle is undefined on output.
//                       The caller of SCX_QUERYNEWFRAMEMENU is responsible for deleting the menu.
//
//   SCX_SELECTNEWFRAME
//        indicates that that the user should be queried to select a new frame.  Any GUI is permissible but
//        the expected behavior to popup a menu.  If no menu is provided, WM_SYSCOMMANDEX with 
//        wParam=SCX_QUERYMENUFORNEWFRAME is issued to get the menu.  If the user makes a selection,
//        then WM_SYSCOMMANDEX with wParam=SCX_NEWFRAME is sent with the user's selection.
//
//        pExInfo->m_hwnd = target for the frame type change
//        pExInfo->m_rc = same as for SCX_NEWFRAME
//        pExInfo->m_pt = recommended point in screen coordinates for displaying the GUI.
//                        The point will be passed directly to TrackPopupMenu()
//                        CPoint(-1,-1) means no such point recommended and any point can
//                        be used (e.g., center of pExInfo->m_hwnd)
//        pExInfo->m_handle = handle to the menu to use (or other GUI object if menus are not used for the GUI)
//                            or null if SCX_QUERYMENUFORNEWFRAME should be called to get the handle
//        pExInfo->m_dwFlags contains the flag SCX_NCPAINTAFTER if a WM_NCPAINT should be sent to pExInfo->m_hwnd
//                           after the selection.  This is useful, for example, when a button in the caption
//                           stays depressed during the menu selection.  That flag will do the proper refresh.
//
//        Other fields are unused and must be zero.
//
//        The handler must unconditionally delete the menu pExInfo->m_handle (if non-null).
//
//        Recommendation to senders:  Use PostMessage() (see SCX_NEWFRAME for more details).
//
//        Return value:  always zero.  All errors are to be dealt with in the SCX_SELECTNEWFRAME handler.
//                       Like SCX_NEWFRAME, this message has no output parameters in pExInfo because it is 
//                       a destructive message.  See SCX_NEWFRAME for details.
//
namespace nsSysCommandEx {
     class ScxInfo; // the LPARAM to any WM_SYSCOMMANDEX message
     enum { SCX_NCPAINTAFTER=0x1 }; // flags used in ScxInfo::m_dwFlags
}; // namespace nsSysCommandEx

namespace nsSysCommandEx {
     // reminder to implementors:  all SCX_ WPARAM values must have a 0 as the last hex digit
     enum { SCX_NEWFRAME            =0xc000,
            SCX_QUERYMENUFORNEWFRAME=0xc010,
            SCX_SELECTNEWFRAME      =0xc020 
          };
}; // namespace nsSysCommandEx



class nsSysCommandEx::ScxInfo
{    
// operations:  lifetime
public:
     ScxInfo ( HWND hwnd = 0 ) { Clear();  m_hwnd = hwnd; }
     ScxInfo ( const ScxInfo & rCopy ) // copy constructor
          : m_hwnd(rCopy.m_hwnd), m_dwFlags(rCopy.m_dwFlags), m_pt(rCopy.m_pt), m_sz(rCopy.m_sz),
            m_rc(rCopy.m_rc), m_handle(rCopy.m_handle)
          { memcpy(m_dw, rCopy.m_dw, sizeof m_dw); }

// properties
public:
     HWND   m_hwnd;			// handle to the target window
     DWORD  m_dwFlags;		// general purpose flags
     CPoint m_pt;			// general purpose point
     CSize  m_sz;			// general purpose size
     CRect  m_rc;			// general purpose rect
     HANDLE m_handle;	    // general purpose handle
     SEC_DWORD  m_dw[16];   // general purpose table of DWORDs

// typecast operators
public:
     inline operator HWND ( void ) const { return m_hwnd; }
     inline operator CWnd* ( void ) const { return CWnd::FromHandle(m_hwnd); }
     inline operator LPARAM ( void ) const { return reinterpret_cast<LPARAM>(this); } // allows passing an ScxInfo in the LPARAM slot of SendMessage or PostMessage()

// operations:
public:
     inline void Clear ( void ) { m_hwnd = 0;  m_dwFlags = 0;  m_pt = CPoint(0,0);  m_sz = CSize(0,0);
                           m_rc = CRect(0,0,0,0);  m_handle = 0;
                           memset(m_dw, '\0', sizeof m_dw); }
};

// message filter classes for handling WM_SYSCOMMANDEX and providing a caption button
//   to automatically send WM_SYSCOMMANDEX buttons for the user
namespace nsSysCommandEx {
     class  ScxButtonMsgFilter;            // implements new caption button for WM_SYSCOMMANDEX
     class  ScxButtonMDIMaxChildMsgFilter; // implements new caption button for WM_SYSCOMMANDEX
                                          // for a maximized mdi child.  The button appears in
                                          // the non-client area (the menu bar) of the mdi frame.
     class  ScxButtonMDIChildMsgFilter;    // implements new caption button for WM_SYSCOMMANDEX
                                          // in an mdi child window
     class  ScxMsgFilter;                  // implements WM_SYSCOMMANDEX handling
     class  ScxCaptionNCRDBLClkFilter;        // implements non-client right double click that
                                             // automatically sends WM_SYSCOMMANDEX
     class  ScxNCRDBLClkMDIMaxChildMsgFilter; // implements non-client right double click in the mdi 
                                             // frame that automatically sends WM_SYSCOMMANDEX to a 
                                             // maximized mdi child
     class  ScxContextMenuFilter;			// converts WM_NCRBUTTONUP into WM_SYSCOMMANDEX
											// with SCX_SELECTNEWFRAME


     enum { SCX_CAPTION_BUTTON_ID = SECCaptionControlMsgFilter::CUSTOM_CONTROL_ID_BASE + 0x400 };
          // SCX_CAPTION_BUTTON_ID is the id passed to SECCaptionControlMsgFilter constructor
          // by the ScxButtonMsgFilter constructor

     // constants used in the WM_SYSCOMMANDEX handler (see class ScxMsgFilter)
     //   these ids must positive
     enum { SCXID_NULL=0, 
            SCXID_MDICHILD=1, SCXID_MINMDICHILD, SCXID_MAXMDICHILD, SCXID_RESTOREDMDICHILD,
            SCXID_DOCKED, SCXID_DOCKLEFT, SCXID_DOCKTOP, SCXID_DOCKRIGHT, SCXID_DOCKBOTTOM,
            SCXID_FLOATING, 
            // id ranges:
            SCXID_MDICHILDFIRST=SCXID_MDICHILD, SCXID_MDICHILDLAST=SCXID_RESTOREDMDICHILD,
            SCXID_DOCKEDFIRST  =SCXID_DOCKED,   SCXID_DOCKEDLAST  =SCXID_DOCKBOTTOM,
            SCXID_FLOATINGFIRST=SCXID_FLOATING, SCXID_FLOATINGLAST=SCXID_FLOATING
     }; 

     // option flags (to be combined in a DWORD using bitwise-or operator)
     enum { SCXOPT_ENABLED=						0x1, 
	 		SCXOPT_NO_CAPTION_BUTTON=			0x02,
			SCXOPT_NO_HANDLE_RDBLCLK=			0x04,
			SCXOPT_NO_CONTEXTMENU=				0x08 };

     // flags for the ScxInfo m_dwFlags (to be combined in a DWORD using bitwise-or operator)
     enum { SCXFLAG_INITIALPOS = 0x1, SCXFLAG_INITIALSIZE = 0x2 };
}; // namespace nsSysCommandEx

// ScxButtonMsgFilter
// ------------------
//   is a subclass of SECCaptionControlMsgFilter that handles messages for the WM_SYSCOMMANDEX button.
//   This button appears in the captin.  The WM_SYSCOMMANDEX button is used to change the type of
//   the current frame.
///
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionControlListMsgFilter.
//
//   Required messages for this filter:
//        WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, 
//        WM_MOUSEMOVE, WM_NCRBUTTONDOWN
//

class nsSysCommandEx::ScxButtonMsgFilter
:    public SECCaptionControlMsgFilter
{ 
	TOOLKIT_DECLARE_DYNCREATE(ScxButtonMsgFilter);

// operations:  lifetime
public:
     typedef SECCaptionControlMsgFilter Super;
     TOOLKIT_API ScxButtonMsgFilter ( CWnd * pwnd = 0, UINT uiID = SCX_CAPTION_BUTTON_ID );
     TOOLKIT_API ScxButtonMsgFilter ( const ScxButtonMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxButtonMsgFilter(*this); }
     TOOLKIT_API virtual ~ScxButtonMsgFilter ( void );
    
// SECCaptionControlMsgFilter overrides
public:
     TOOLKIT_API virtual void OnPaint ( void );
     TOOLKIT_API virtual void OnPostSysCommand ( DWORD dwFlags, CPoint ptMouse /* screen coordinates */ );
     TOOLKIT_API virtual BOOL GetSysCommand ( DWORD dwFlags, CPoint ptMouse /* screen coordinates */, 
                                  HWND & rhwnd, UINT & ruiMessage, 
                                  WPARAM & rwParam, LPARAM & rlParam ); 
     TOOLKIT_API virtual BOOL IsVisible ( BOOL * pbGrayed = 0 );
     TOOLKIT_API unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// properties:
//   This classes sets the base class data member SECCaptionControlMsgFilter::m_lMouseHoldPeriod
//   to the default used by tooltips.  
};

// ScxButtonMDIMaxChildMsgFilter
// -----------------------------
//   is a subclass of ScxButtonMsgFilter that handles messages for the WM_SYSCOMMANDEX button
//   in a maximized mdi child.  The filter is actually used by the mdi frame.
///
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionControlListMsgFilter.
//
//   Required messages for this filter:
//        WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, 
//        WM_MOUSEMOVE, WM_NCRBUTTONDOWN
//
class nsSysCommandEx::ScxButtonMDIMaxChildMsgFilter
:    public ScxButtonMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(ScxButtonMDIMaxChildMsgFilter);

// operations:  lifetime
public:
     typedef ScxButtonMsgFilter Super;

     TOOLKIT_API ScxButtonMDIMaxChildMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxButtonMDIMaxChildMsgFilter ( const ScxButtonMDIMaxChildMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxButtonMDIMaxChildMsgFilter(*this); }
     TOOLKIT_API virtual ~ScxButtonMDIMaxChildMsgFilter ( void );
     
// SECMsgFilter override:  FilterStrict()
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// SECCaptionControlMsgFilter overrides
public:
     TOOLKIT_API virtual BOOL GetSysCommand ( DWORD dwFlags, CPoint ptMouse /* screen coordinates */, 
                                  HWND & rhwnd, UINT & ruiMessage, 
                                  WPARAM & rwParam, LPARAM & rlParam ); 
     TOOLKIT_API virtual BOOL IsVisible ( BOOL * pbGrayed = 0 );

// new overrides
public:
     TOOLKIT_API virtual CWnd * GetMaximizedMDIChild ( void ) const;
};

// ScxButtonMDIChildMsgFilter
// --------------------------
//   is a subclass of ScxButtonMsgFilter that handles messages for the WM_SYSCOMMANDEX button
//   in a non-maximized mdi child.  When an mdi child is maximized, the mdi frame handles it.
///
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionControlListMsgFilter.
//
//   Required messages for this filter:
//        WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, 
//        WM_MOUSEMOVE, WM_NCRBUTTONDOWN
//
class nsSysCommandEx::ScxButtonMDIChildMsgFilter
:    public ScxButtonMsgFilter
{ 
	TOOLKIT_DECLARE_DYNCREATE(ScxButtonMDIChildMsgFilter);

// operations:  lifetime
public:
     typedef ScxButtonMsgFilter Super;
     TOOLKIT_API ScxButtonMDIChildMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxButtonMDIChildMsgFilter ( const ScxButtonMDIChildMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxButtonMDIChildMsgFilter(*this); }
     TOOLKIT_API virtual ~ScxButtonMDIChildMsgFilter ( void );
    
// SECMsgFilter override:  FilterStrict()
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// SECCaptionControlMsgFilter overrides
public:
     TOOLKIT_API virtual BOOL IsVisible ( BOOL * pbGrayed = 0 );
};

// ScxCaptionNCRDBLClkFilter
// -------------------------
//   is a subclass of SECCaptionMsgFilter that handles the non-client right-double click mouse
//   event and issues a WM_SYSCOMMANDEX in response.
//
//   Required messages for this filter:
//        WM_NCRBUTTONDBLCLCK
//
class nsSysCommandEx::ScxCaptionNCRDBLClkFilter
:    public SECCaptionMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(ScxCaptionNCRDBLClkFilter);

// operations:  lifetime
public:
     typedef SECCaptionMsgFilter Super;
     TOOLKIT_API ScxCaptionNCRDBLClkFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxCaptionNCRDBLClkFilter ( const ScxCaptionNCRDBLClkFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxCaptionNCRDBLClkFilter(*this); }
     TOOLKIT_API virtual ~ScxCaptionNCRDBLClkFilter ( void );
     
// SECMsgFilter override:  FilterStrict()
//   filters WM_NCRBUTTONDBLCLCK
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );
};

// ScxNCRDBLClkMDIMaxChildMsgFilter
// --------------------------------
//   is a subclass of SECNcMsgFilter that handles the non-client right-double click mouse
//   event for a maximized mdi child and issues a WM_SYSCOMMANDEX in response.  The filter
//   is intended to be used by the main mdi frame.
//
//   Required messages for this filter:
//        WM_NCRBUTTONDBLCLCK
//
class nsSysCommandEx::ScxNCRDBLClkMDIMaxChildMsgFilter
:    public SECNcMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(ScxNCRDBLClkMDIMaxChildMsgFilter);

// operations:  lifetime
public:
     typedef SECNcMsgFilter Super;
     TOOLKIT_API ScxNCRDBLClkMDIMaxChildMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxNCRDBLClkMDIMaxChildMsgFilter ( const ScxNCRDBLClkMDIMaxChildMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxNCRDBLClkMDIMaxChildMsgFilter(*this); }
     TOOLKIT_API virtual ~ScxNCRDBLClkMDIMaxChildMsgFilter ( void ); 

// SECMsgFilter override:  FilterStrict()
//   filters WM_NCRBUTTONDBLCLCK
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );
};

// ScxContextMenuFilter
// --------------------------------
//   is a subclass of SECMsgFilter that handles WM_NCRBUTTONUP messages
//   and issues a WM_SYSCOMMANDEX in response. This is not derived from
//	 SECNcMsgFilter because there is really no reason this would have to be
//	 dependent on non-client messages. It could be issued for WM_CONTEXTMENU.
//
//   Required messages for this filter:
//        none
//
class nsSysCommandEx::ScxContextMenuFilter
:    public SECMsgFilter
{ 
	TOOLKIT_DECLARE_DYNCREATE(ScxContextMenuFilter);

// operations:  lifetime
public:
     typedef SECMsgFilter Super;
     TOOLKIT_API ScxContextMenuFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxContextMenuFilter ( const ScxContextMenuFilter& rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxContextMenuFilter(*this); }
     TOOLKIT_API virtual ~ScxContextMenuFilter ( void );

// SECMsgFilter override:  FilterStrict()
//   filters WM_CONTEXTMENU
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );
};

// ScxMsgFilter
// ------------
//   is a subclass of SECMsgFilter that provides the default handler for the OTPRO extended
//   message WM_SYSCOMMANDEX.
//
//   Any window that wants to handle this message can delegate to this filter to get the
//   "default" handler.  For exmaple, the virtual CWnd::DefWindowProc() can be overridden to
//   delegate to this filter for WM_SYSCommandExMsgFilter for WM_SYSCOMMANDEX and delegate to
//   the bsae class otherwise.  This change allows the user to just call Default() or
//   DefWindowProc().
//
//   Required messages for this filter:
//        WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, 
//        WM_MOUSEMOVE, WM_NCRBUTTONDOWN
//
class SECMultiDocTemplate;
class nsSysCommandEx::ScxMsgFilter
:    public SECMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(ScxMsgFilter);

// operations:  lifetime
public:
     typedef SECMsgFilter Super;
     TOOLKIT_API ScxMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API ScxMsgFilter ( const ScxMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new ScxMsgFilter(*this); }
     TOOLKIT_API virtual ~ScxMsgFilter ( void );
     
// SECMsgFilter override:  FilterStrict()
//        overridden to handle WM_SYSCOMMANDEX only
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// operations:  top-level handlers called by FilterStrict() for WM_SYSCOMMANDEX
//   These functions must define the return value and output parameter plResult for FilterStrict.
//   Caution:  plResult is an in/out parameter that must not be changed unless MSG_HANDLED is returned.
public:
     TOOLKIT_API virtual unsigned long OnScxSelectNewFrame       ( ScxInfo & rScxInfo, LRESULT * plResult );
     TOOLKIT_API virtual unsigned long OnScxQueryMenuForNewFrame ( ScxInfo & rScxInfo, LRESULT * plResult );
     TOOLKIT_API virtual unsigned long OnScxNewFrame             ( ScxInfo & rScxInfo, LRESULT * plResult ); 

// operations:  used by default implementation of OnScxSelectnewFrame()
//   GetNewFrameMenu()    -- retrieves HMENU from rScxInfo or sends a WM_SYSCOMMANDEX
//                           to get one if rScxInfo does not define one
//   SelectNewFrameType() -- uses the given menu to get a user selection; the expectation
//                           is that the menu was obtained from GetNewFrameMenu()
//   ChangeFrameType()    -- change to the given frame type; the ID must be a non-zero id 
//                           that is the command id from the menu obtained via GetNewFrameMenu()
public:
     TOOLKIT_API virtual HMENU GetNewFrameMenu   ( const ScxInfo & );
     TOOLKIT_API virtual UINT SelectNewFrameType ( HMENU, const ScxInfo & );
     TOOLKIT_API virtual BOOL ChangeFrameType    ( UINT uiFrameTypeID, const ScxInfo & );

// operations:  used by default implementation of OnScxQueryMenuForNewFrame()
//   BuildInspectMenu() -- construct the menu for selecting a new frame type.
//                         A second signature is a helper function that is called
//                         by BuildInspectMenu(const ScxInfo&).
public:
     TOOLKIT_API virtual HMENU BuildInspectMenu ( const ScxInfo & );
     TOOLKIT_API virtual HMENU BuildInspectMenu ( const CFrameWnd &, UINT uiTypeID, const ScxInfo & );

// operations:  used by default implementation of OnScxNewFrame()
//   ChangeToMDIChild()          -- change a frame type to an mdi child frame in a specific state 
//                                  (minimized, maximized, normal)
//   Dock()                      -- change a frame type to docked to a specific edge
//   Float()                     -- change a frame type to floating
//   ToggleMDIChildAndDockable() -- toggle between a dockable frame an mdi child frame
//   ToggleDockableAndFloating() -- toggle between a docked frame and a floating frame
//   DockMDIChild()              -- dock an mdi child at a specific location
public:
     TOOLKIT_API virtual CFrameWnd * ChangeToMDIChild   ( CFrameWnd &, UINT uiSourceID, UINT uiTargetID, SECMultiDocTemplate &, ScxInfo & );
     TOOLKIT_API virtual CFrameWnd * Dock               ( CFrameWnd &, UINT uiSourceID, UINT uiTargetID, SECMultiDocTemplate &, ScxInfo & );
     TOOLKIT_API virtual CFrameWnd * Float              ( CFrameWnd &, UINT uiSourceID, UINT uiTargetID, SECMultiDocTemplate &, ScxInfo & );
     TOOLKIT_API virtual CFrameWnd * ToggleMDIChildAndDockable ( CFrameWnd &, SECMultiDocTemplate &, ScxInfo & );
     TOOLKIT_API virtual void ToggleDockableAndFloating ( CFrameWnd &, SECMultiDocTemplate &, ScxInfo & );
     TOOLKIT_API virtual CFrameWnd* DockMDIChild 		( CFrameWnd &, UINT uiDockBarID, SECDockPos *, SECDockSize *, SECMultiDocTemplate &, ScxInfo & );

// operations:  general helper functions used in implementation of FilterStrict() handler of WM_SYSCOMMANDEX
//   Definition:  type id = command id from the menu presented to the user (build in GetNewFrameMenu())
//
//   NormalizeType()          -- maps type id to single normalized value for comparison purposes.
//                               Default implementation maps SCXID_MDICHILDFIRST..SCXID_MDICHILDLAST to SCXID_MDICHILD,
//                               SCXID_DOCKEDFIRST..SCXID_DOCKEDLAST to SCXID_DOCKED, and
//                               SCXID_FLOATINGFIRST..SCXID_FLOATINGLAST to SCXID_FLOATING.
//   GetDefaultNewFrameType() -- given the id of a frame type, return the id of another
//                               frame type to use as the default change
//   GetFrameType()           -- return the type of a frame window where the type is the command
//                               id used in the menu for selecting frame types
//   GetDocTemplate()         -- return doc template based on parameters to a WM_SYSCOMMANDEX message
//                               Optionally, a CRuntimeClass* can be passed to force the return value to
//                               be of a certain type.  Null is returned if a doc template is found
//                               but has the wrong type.
//   IsClonedFilterRequired() -- returns whether the parameters to WM_SYSCOMMANDEX require that a clone
//                               of this message filter actually handle the message.  The default implementation
//                               returns true iff the WPARAM to WM_SYSCOMMANDEX is SCX_NEWFRAME or SCX_SELECTNEWFRAME.
//                               Both of those WPARAM values cause the frame to be destroyed.  It is possible that the
//                               this message filter is a data membe of the frame to be destroyed.  Hence, a clone
//                               is made and then automatically deleted after completing the handling.
public:
     TOOLKIT_API virtual UINT NormalizeType  ( UINT uiFrameTypeID ) const; 
     TOOLKIT_API virtual UINT GetDefaultNewFrameType ( const CFrameWnd &, UINT uiFrameTypeID, const ScxInfo & ) const;
     TOOLKIT_API virtual UINT GetFrameType ( const CFrameWnd &, const SECMultiDocTemplate &, const ScxInfo & ) const;
     TOOLKIT_API virtual CDocTemplate * GetDocTemplate ( const ScxInfo &, const CRuntimeClass * = 0 ); // null means not found
     TOOLKIT_API virtual BOOL IsClonedFilterRequired ( WPARAM, const ScxInfo & );
protected:
          BOOL m_bCloneForDelegation; // flags that a filter is a clone for delegation purposes.
                                      // see FilterStrict() handler for usage.
};


//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SYSCMDEX_H__

#endif // WIN32
