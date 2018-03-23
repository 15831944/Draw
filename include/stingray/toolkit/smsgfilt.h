///////////////////////////////////////////////////////////////////////////////
// smsgfilt.h
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
//  Description:  Declarations for message filter classes
//  Created:      Sep 1997
//
/////////////////////////////////////////////////////////////////////////////
// Hierarchy of objects in this file
//
//   CObject
//   |-- SECMsgFilter
//       |-- SECNcMsgFilter 
//           |-- SECCaptionMsgFilter
//               |-- SECCaptionControlMsgFilter
//               |-- SECCaptionControlListMsgFilter
//                   |-- SECCapConLstMDIMaxChildMsgFilter
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

#ifndef __SMSGFILT_H__
#define __SMSGFILT_H__

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // #ifndef __AFXTEMPL_H__

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

// filter ids for standard filters
enum { SEC_MSGFID_CAPTION_BUTTON_LIST  =0x100,
       SEC_MSGFID_SCX                  =0x101,
       SEC_MSGFID_SCX_BUTTON           =0x102,
       SEC_MSGFID_SCX_NCRBUTTONDBLCLK  =0x103,
       SEC_MSGFID_SCX_MAXMDICHILDBUTTON=0x104,
       SEC_MSGFID_SCX_MAXMDICHILDNCRDBL=0x105,
       SEC_MSGFID_SCX_CONTEXTMENU	   =0x106
};


// SECMsgFilter
// ------------
//   is a class that defines a message filter for an CWnd.
//
//   To use the filter, the CWnd must delegate one or more of its messages to the Filter() member function.
//   In addition, the CWnd must adhere to the return value of Filter() which instructs when to omit calls
//   to the system handler (see the doc for Filter() below).
//
//   Subclasses of SECMsgFilter() must document which messages they require to be passed and which are optional.
//   
//   Message filters can be composite.  See the functions Filter() and Delegate() below.
//
//   It is a design choice that message filters not subclass the CWnd to be filtered.  The reason is that it
//   is application specific how to weave filters into existing message handlers.  By subclassing the CWnd,
//   an assumption must be made in which order to do a) the filter and b) the original work.  Doing (a) first
//   is a pre-filter, doing (b) first is a post-filter.  In addition, it might be necessary to mix calls to
//   various filters into steps taken in a message handler.  Knowledge of how to do this is application specific.
//
class SECMsgFilter
:    public CObject
{
	TOOLKIT_DECLARE_DYNCREATE(SECMsgFilter);
// operations:  lifetime
public:
     typedef CObject Super;
     TOOLKIT_API SECMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API SECMsgFilter ( const SECMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new SECMsgFilter(*this); }
     TOOLKIT_API virtual ~SECMsgFilter ( void );
     
     
// properties
public:
     UINT m_uiID;            // id to distinguish between children; (UINT)-1 reserved to means "no id"
     BOOL m_bEnabled;        // whether this handler is enabled
     BOOL m_bOwnChildren;    // whether to auto-delete contents of m_pChildren in destructor (default is true)
     inline virtual CWnd * GetWindow ( void ) const { return m_pwnd; }
     TOOLKIT_API virtual void SetWindow ( CWnd * pwnd, BOOL bUpdateDescendants = TRUE );
     CArray<SECMsgFilter*,SECMsgFilter*> m_pChildren;  // table of sub-filters
protected:
     CWnd * m_pwnd;            // the CWnd whose messages are to be filtered

// operations:  message filter for m_pwnd
//   Filter() -- purpose is a) to do any special case handling and and b) delegate to sub-filters.
//        There is no order imposed (a) can be before (b), (b) can be before (a) or they can be intertwined.
//        Filter() must call Delegate() to do (b).  If no delegation is required or partial delegation is required,
//        then Delegate() should be overridden accordingly so that Filter() can call Delegate(). 
//        The default implementation of Filter() simply calls Delegate().
//
//   Delegate() -- purpose is to delegate the message to sub-filters in m_pChildren.
//        This function is called by Filter() but can be called whenever the sub-filters must be delegated to.
//        The default delegation interates over the contents of m_pChildren in order.  For each filter f that is
//        enabled, f->Filter() is called.  If the return value of f->Filter() signals that no more delegation should
//        be done, then Delegate() stops the iteration and returns immediately.
//
//   return value of Filter() and Delegate() is a set of bit flags in a single unsigned long
//        MSG_HANDLED = bit flag that the given message was handled
//                  Note that the message might have been handled multiple times.  This is ok and the Delegate()
//                  implementation must decide when to multiply-handle a message.
//        MUTEX_SYSHANDLER = bit flag indicating that the caller should not subsequently call the system handler (::DefWindowProc(),
//                  CWnd::Default(), etc.).  If MUTEX_SYSHANDLER_DONE is also set, then action has already been taken that must
//                  be mutually exclusive with the action taken by the system handler.  For example, the system handler might
//                  have already been called.  If MUTEX_SYSHANDLER_DONE is not set, then MUTEX_SYSHANDLER means that the
//                  system handler's behavior must be skipped.  In both cases, MUTEX_SYSHANDLER means don't call the system handler.
//                  MUTEX_SYSHANDLER_DONE should never be present without MUTEX_SYSHANDLER.
//                  Note that the MSG_HANDLD and MUTEX_SYSHANDLER flags are set independently.  MUTEX_SYSHANDLER can be set
//                  without actually handling the message.  In this case, MSG_HANDLED can also set in the return value due
//                  to handling by another sub-filter.
//        MUTEX_DELEGATE = bit flag indicating that subsequent delegation should cease.  That is, while iterating over the
//                  sub-filters, Delegate() will stop the iteration if MUTEX_DELEGATE is returned from a sub-filter.
//                  Upon receiving MUTEX_DELEGATE from a handler, Delegate() has 3 choices.  First, ignore the flag
//                  and continue.  Second, stop iteration and return but do not return the MUTEX_DELEGATE flag.  Third,
//                  stop iteration and return the MUTEX_DELEGATE flag to the caller.  Note that the caller could be part
//                  of an "outer delegation".  That is, the caller is either Delegate() or a function ultimately called by
//                  another Delegate().  The third case for returning the MUTEX_DELEGATE flag means to stop the outer
//                  delegation as well.
//
//        The caller is not strictly required to honor the MUTEX_SYSHANDLER and MUTEX_DELEGATE flags.  However, ignoring
//        these recommendations is done at complete responsibility of the caller.  Caller must have intimiate knowledge that
//        permits the flags to be ignored.
//
//   Output parameter plResult can be null to indicate no assignment of the message LRESULT will be output.
//   If non-null, then plResult is considered an in/out parameter.  Its value will be be assigned iff MSG_HANDLED is returned.
public:
     enum ReturnFlags { MSG_HANDLED=0x1ul, MUTEX_SYSHANDLER=0x2ul, MUTEX_SYSHANDLER_DONE=0x4ul, MUTEX_DELEGATE=0x8ul, FIRST_USER_FLAG=0x10000ul };
     TOOLKIT_API virtual unsigned long Filter ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 ); // calls FilterStrict() unless m_bEnabled is false
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );
     TOOLKIT_API virtual unsigned long Delegate ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );
     inline unsigned long Filter ( const MSG * pMsg = 0, LRESULT * plResult = 0 ) // non-virtual so base classes only have to override one signature for Filter()
          {    if (! pMsg) pMsg = & AfxGetThreadState()->m_lastSentMsg;
               return Filter(pMsg->message, pMsg->wParam, pMsg->lParam, plResult); 
          }

// operations:  accessing and enabling children
public:
     TOOLKIT_API virtual SECMsgFilter * GetChild ( UINT uiID, 
                                       CRuntimeClass * pClassForAutoCreate = 0, /* creates child if non-null and not found */
                                       int iNumSearchLevels = -1                /* 0=search child list, n>0 means also search n levels of descendants, 
                                                                                ** negative means search all levels */ );
     enum DescriptorFlags { NODISABLE=0x1 };
     struct Descriptor {
          UINT          m_uiID;
          UINT          m_uiParentID; // or (UINT)-1 if is a top-level child
          CRuntimeClass * m_pClass;   // used to auto-create or null if can't auto-create
          DWORD         m_dwFlags;  
          inline Descriptor ( UINT uiID = (UINT)-1, UINT uiParentID = (UINT)-1, CRuntimeClass * pClass = 0, DWORD dwFlags = 0 )
               : m_uiID(uiID), m_uiParentID(uiParentID), m_pClass(pClass), m_dwFlags(dwFlags) { }
          inline Descriptor ( const Descriptor & rCopy ) // copy constructor
               : m_uiID(rCopy.m_uiID), m_uiParentID(rCopy.m_uiParentID), m_pClass(rCopy.m_pClass), m_dwFlags(rCopy.m_dwFlags) { }
          inline virtual Descriptor * Clone ( void ) const { return new Descriptor(*this); }
     };
     struct DescriptorTable : public CArray<Descriptor*,Descriptor*>
     { 
          inline virtual ~DescriptorTable ( void ) 
          {    for ( int i = 0;  i < GetSize();  ++i )
                    delete operator[](i); // delete ith descriptor
          }
     };
     TOOLKIT_API virtual void EnableChild    ( const Descriptor & rDescriptor, BOOL bEnabled );       // enable/disable one descendant
     TOOLKIT_API virtual void EnableChildren ( const DescriptorTable & rDescriptors, BOOL bEnabled ); // enable/disable one or more descendants
     TOOLKIT_API virtual void EnableChildren ( const DescriptorTable & rDescriptors, const BOOL bEnabled[] ); // enable/disable one or more descendants
                                                                                                  // with separate enable flag for each
};


// SECNcMsgFilter
// --------------
//   is a subclass of SECMsgFilter that handles non-client messages.  
//
//   SECNcMsgFilter is a composite message handler.  For example, it can have an
//   instance of a caption filter, an mdi child menu filter, a frame sizing filter, etc.
//
//   Required messages for this filter:  
//        No messages are required explicitly for this composite filter.
//        However, this filter requires all messages required by sub-filters.
//        See the documentation for any sub-filters added at runtime.
//
class SECNcMsgFilter 
:    public SECMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(SECNcMsgFilter);

// operations:  lifetime
public:
     typedef SECMsgFilter Super;
     TOOLKIT_API SECNcMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API SECNcMsgFilter ( const SECNcMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new SECNcMsgFilter(*this); }
     TOOLKIT_API virtual ~SECNcMsgFilter ( void );
};

// SECCaptionMsgFilter
// -------------------
//   is a subclass of SECWndMsgFilter that handles messages for the caption.
//
//   SECCaptionMsgFilter is a composite message handler.  For example, it can have an
//   instance of a caption text painting filter, a list of filters for painting
//   caption buttons, and a filter for handling mouse double clicks in the caption.
//
//   Required messages for this filter:  
//        No messages are required explicitly for this composite filter.
//        However, this filter requires all messages required by sub-filters.
//        See the documentation for any sub-filters added at runtime.
//
class SECCaptionMsgFilter
:    public SECNcMsgFilter 
{
	TOOLKIT_DECLARE_DYNCREATE(SECCaptionMsgFilter);
// operations:  lifetime
public:
     typedef SECNcMsgFilter Super;
     TOOLKIT_API SECCaptionMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API SECCaptionMsgFilter ( const SECCaptionMsgFilter & rCopy ); // copy constructor
     inline  virtual SECMsgFilter * Clone ( void ) const { return new SECCaptionMsgFilter(*this); }
     TOOLKIT_API  ~SECCaptionMsgFilter ( void );
     

// properties:  rect, size, and position of caption and caption buttons
//   GetCaptionRect()           -- returns CRect in window coordinates for this window's caption, if any
//   GetStandardButtonSize()    -- calculate standard caption button size for the window.  Default implementation
//                                 calculates the indexes for ::GetSystemMetrics() and calls GetStandardButtonSize(x,y).
//   GetStandardButtonSize(x,y) -- calculate caption button size based on given system metrics indexes
//   GetRightmostButtonOffset() -- calculate offset of rightmost button in the caption
public:
     TOOLKIT_API virtual CRect  GetCaptionRect ( void ) const;
     TOOLKIT_API virtual CSize  GetStandardButtonSize ( void ) const;
     TOOLKIT_API virtual CSize  GetStandardButtonSize ( int iSysMetricCxIndex, int iSysMetricCyIndex ) const;
     TOOLKIT_API virtual CPoint GetRightmostButtonOffset ( CRect rcCaption, CSize szButton ) const;
};

// SECCaptionControlListMsgFilter
// ------------------------------
//   is a subclass of SECCaptionMsgFilter that handles messages for a list of caption controls.
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionMsgFilter.
//
//   SECCaptionMsgFilter is a composite message handler for a list of SECCaptionControlMsgFilter
//   instances. 
//
//   The purpose of this class is to provide a single filter to be placed in an instance of
//   SECCaptionMsgFilter.  The single filter organizes all of the caption controls.
//
//   Required messages for this filter:  
//        No messages are required explicitly for this composite filter.
//        However, this filter requires all messages required by SECCaptionControlMsgFilter.
//
class SECCaptionControlListMsgFilter
:    public SECCaptionMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(SECCaptionControlListMsgFilter);
// operations:  lifetime
public:
     typedef SECCaptionMsgFilter Super;
     TOOLKIT_API SECCaptionControlListMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API SECCaptionControlListMsgFilter ( const SECCaptionControlListMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new SECCaptionControlListMsgFilter(*this); }
     TOOLKIT_API virtual ~SECCaptionControlListMsgFilter ( void );
     

// SECMsgFilter override:  FilterStrict()
//   calls virtual EnumControls() before calling base class (which delegates to sub-filters)
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// operations:  
//   EnumControls() enumerates and updates all sub-filters (e.g., sets m_rcControl field) in preparation for using them
public:
     TOOLKIT_API virtual void EnumControls ( void );

// properties:
//   m_pSysButtonDescriptors -- table of descriptors for the system buttons (close box, maximize box, etc.)
//                              m_pSysButtonDescriptors[i] is the Descriptor* instance for the ith system button.
//                              example usage:  EnableChildren(m_pSysButtonDescriptors, FALSE) to disable all system button filters.
public:
     DescriptorTable m_pSysButtonDescriptors;
};

// SECCapConLstMDIMaxChildMsgFilter
// --------------------------------
//   is a subclass of SECCaptionControlListMsgFilter that handles messages for a list of caption controls
//   in the maximized mdi child area of an MDI frame window.  Recall that an MDI frame can have two lists
//   of caption controls:  one in the caption and one in the menu bar for the maximized child (if any).
//
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionMsgFilter.
//
//   SECCaptionMsgFilter is a composite message handler for a list of SECCaptionControlMsgFilter
//   instances.  
//
//   Required messages for this filter:  
//        No messages are required explicitly for this composite filter.
//        However, this filter requires all messages required by SECCaptionControlMsgFilter.
//
class SECCapConLstMDIMaxChildMsgFilter
:    public SECCaptionControlListMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(SECCapConLstMDIMaxChildMsgFilter);
// operations:  lifetime
public:
     typedef SECCaptionControlListMsgFilter Super;
     TOOLKIT_API SECCapConLstMDIMaxChildMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */ );
     TOOLKIT_API SECCapConLstMDIMaxChildMsgFilter ( const SECCapConLstMDIMaxChildMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new SECCapConLstMDIMaxChildMsgFilter(*this); }
     TOOLKIT_API virtual ~SECCapConLstMDIMaxChildMsgFilter ( void );
     

// SECCaptionMsgFilter overrides
public:
     TOOLKIT_API virtual CSize  GetStandardButtonSize ( void ) const;
     TOOLKIT_API virtual CPoint GetRightmostButtonOffset ( CRect rcCaption, CSize szButton ) const;
};

// SECCaptionControlMsgFilter
// --------------------------
//   is a subclass of SECCaptionMsgFilter that handles messages for a caption control.
//   An instance of this class is expected to appear at runtime in an instance of
//   SECCaptionControlListMsgFilter.
//
//   The purpose of this class parallels that of the Win32 API ::DrawFrameControl().  Any
//   control that can be drawn using ::DrawFrameControl() can be embodied in an instance
//   of this class to handle its drawing, hit testing, etc.
//
//   Required messages for this filter:
//        WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, 
//        WM_MOUSEMOVE, WM_NCRBUTTONDOWN
//
class SECCaptionControlMsgFilter
:    public SECCaptionMsgFilter
{
	TOOLKIT_DECLARE_DYNCREATE(SECCaptionControlMsgFilter);

// operations:  lifetime
public:
     typedef SECCaptionMsgFilter Super;
     enum { CUSTOM_CONTROL_ID_BASE=0x1000 }; // add this constant to a non-negative value to ensure that do not
                                             // have an id that conflicts with the system ids DFCS_CAPTIONCLOSE,
                                             // DFCS_CAPTIONMIN, DFCS_CAPTIONMAX, DFCS_CAPTIONHELP, DFCS_CAPTIONRESTORE 
     TOOLKIT_API SECCaptionControlMsgFilter ( CWnd * pwnd = 0, UINT uiID = (UINT)-1 /* no id */, UINT uiControlState = 0, 
                                  UINT uiControlType = DFC_CAPTION );
          // for uiControlType = DFC_CAPTION, uiID is a system ID if it has one of the buttons enum values
          // DFCS_CAPTIONCLOSE, DFCS_CAPTIONMIN, DFCS_CAPTIONMAX, DFCS_CAPTIONHELP, DFCS_CAPTIONRESTORE.
          // These values are defined by ::DrawFrameControl().
     TOOLKIT_API SECCaptionControlMsgFilter ( const SECCaptionControlMsgFilter & rCopy ); // copy constructor
     inline virtual SECMsgFilter * Clone ( void ) const { return new SECCaptionControlMsgFilter (*this); }
     TOOLKIT_API virtual ~SECCaptionControlMsgFilter ( void );
     

// properties: defining the control and its tracking state
public:
     CRect m_rcControl;         // as documented for ::DrawFrameControl() (logical coordinates).
                                // a value of CRect(0,0,0,0) means not visible.
     UINT  m_uiControlType;     // for a system-defined control, is a parameter for ::DrawFrameControl()
                                // for a custom control, is programmer defined.
     UINT  m_uiControlState;    // for a system-defined control, is a parameter for ::DrawFrameControl()
                                // for a custom control, is programmer defined
     inline UINT SystemID ( void ) const
          { return ((m_uiID != (UINT)-1) && (m_uiID < CUSTOM_CONTROL_ID_BASE))
                         ? m_uiID
                         : (UINT)-1; }
     inline BOOL IsSystemDefined ( void ) const { return SystemID() != (UINT)-1; }
     BOOL m_bTracking;          // currently tracking this control with the mouse

// SECMsgFilter override:  FilterStrict()
//   filters WM_SETTEXT, WM_NCACTIVATE, WM_NCPAINT, WM_NCLBUTTONDOWN, WM_LBUTTONUP, WM_MOUSEMOVE, WM_NCRBUTTONDOWN
public:
     TOOLKIT_API virtual unsigned long FilterStrict ( UINT uiMsg, WPARAM wParam, LPARAM lParam, LRESULT * plResult = 0 );

// operations:  virtuals used by FilterStrict() for filtering the caption control
public:
     // note that all CPoint arguments below are in screen coordinates
     TOOLKIT_API virtual void OnPaint ( void );             // paint the control according to m_uiControlType and m_uiControlState
     TOOLKIT_API virtual BOOL HitTest ( CPoint ptTest );    // test whether a point is within the control
     TOOLKIT_API virtual void OnPress ( CPoint ptTest );    // called when user first presses button (but does not release yet)
     TOOLKIT_API virtual void OnRelease ( CPoint ptMouse ); // called when user releases button
     TOOLKIT_API virtual void OnMouseHeldDown ( CPoint ptMouse ); // called in place of OnRelease() when the mouse button is held down
                                                      // for m_lMouseHoldPeriod milliseonds
     TOOLKIT_API virtual void OnRefresh ( CPoint ptTest );  // called when user moves mouse after pressing the button but before releasing it
     enum SysCommandFlags { SC_INSPECT=0x1, SC_MOUSEHELD=0x2 };
     TOOLKIT_API virtual void OnPostSysCommand ( DWORD dwFlags, CPoint ptMouse ); 
               // called by OnRelease(), OnMouseHeldDown(), and handler for WM_NCRBUTTONDOWN.
               // OnRelease() passes dwFlags=0, OnMouseHeldDown() passes dwFlags=SC_MOUSEHELD, WM_NCRBUTTONDOWN passes dwFlags=SC_INSPECT.
               // This function posts the appropriate WM_SYSCOMMAND (or other message) signal the event.
     TOOLKIT_API virtual BOOL GetSysCommand ( DWORD dwFlags, CPoint ptMouse, /* 1st 2 args are same as in OnPostSysCommand() */
                                  HWND & rhwnd /* normally m_pwnd->m_hwnd */,
                                  UINT & ruiMessage /* normally WM_SYSCOMMAND */,
                                  WPARAM & rwParam, LPARAM & rlParam ); // called by OnPostSysCommand() to get, if any, the sys command msg
     TOOLKIT_API virtual void BeginTracking ( BOOL bSetPressedState, BOOL bRepaint ); // called by OnPress() to begin the tracking state for this control
                                                                          // responsible for releasing mouse capture
     TOOLKIT_API virtual void EndTracking ( BOOL bClearPressedState, BOOL bRepaint ); // called by OnRelease() to end the tracking state for this control
                                                                          // responsible for releasing mouse capture
     TOOLKIT_API virtual void ResetMouseHoldTimer ( void );
     TOOLKIT_API virtual void SetMouseHoldTimer ( CPoint ptRef );

// properties
//   m_lMouseHoldPeriod -- number of milliseconds user must hold down mouse
//                           to get the "Held Mouse Down" event (defaults to same default for tooltips)
//                           A value of zero means immediate.
//                           A negative value means no menu.
//                           m_lMouseHoldPeriod = -1 by default.
public:
     long m_lMouseHoldPeriod;
protected:
     CWnd * m_pwndMouseHoldTimer;

// operations:  visibility test
//   IsVisible(g) -- returns whether the control is visiible.  If g is non-null, then *g is set to whether the control
//                   is visible but grayed
public:
     TOOLKIT_API virtual BOOL IsVisible ( BOOL * pbGrayed = 0 );
};


//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // #ifdef __SMSGFILT_H__

#endif // #ifdef WIN32
