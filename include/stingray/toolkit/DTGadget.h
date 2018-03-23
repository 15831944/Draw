///////////////////////////////////////////////////////////////////////////////
// DTGadget.h : Header file for SECDTGadget and associated classes. These
//              are used as display components by SECDateTimeCtrl
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
//		Author:		Don			20/01/97
//


#ifndef __DTGADGET_H__
#define __DTGADGET_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

#ifdef WIN32

// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Gadget notifications
#define SECGN_INCREMENT		0x0001
#define SECGN_DECREMENT		0x0002
#define SECGN_SPINUP		0x0003
#define SECGN_SPINDOWN		0x0004
#define SECGN_DROPDOWN		0x0005
#define SECGN_VALIDATE		0x0006
#define SECGN_MODIFY		0x0007
#define SECGN_MINIMUM		0x0008
#define SECGN_MAXIMUM		0x0009
#define SECGN_EDIT			0x000a
#define SECGN_NUMERIC_DONE	0x000b	// Input into numeric gadget is complete

// Forward references
class SECDateTimeCtrl;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTGadget 
//  
//  Abstract base class for the gadget components used by SECDateTimeCtrl
//
class SECDTGadget : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECDTGadget)

// Construction
public:
	TOOLKIT_API SECDTGadget();

	// Initialises the gadget.
	TOOLKIT_API BOOL Initialise(SECDateTimeCtrl* pCtrl, int nID = -1);

// Attributes
public:
	enum	// Style flags (for m_style and GetStyle/SetStyle)
	{
		WantFocus = 0x0001,		// Gadget accepts focus (i.e. can be enabled)
		WantMouse = 0x0002,		// Gadget wants mouse clicks
		IsFixed   = 0x0004,		// Gadget is not moveable (fixed to right edge
								// of control)
		IsNull    = 0x0008
	};

// Operations
public:
	// Set/Get the style flags for this gadget.
	TOOLKIT_API int  GetStyle() const;
	TOOLKIT_API void SetStyle(int style);

	// Set/Get the current value of the gadget
	TOOLKIT_API void SetValue(int nNewValue);
	TOOLKIT_API int  GetValue() const;

	// Get's a textual representation of this control
	TOOLKIT_API virtual void GetText(LPTSTR lpszBuf);

	// Returns the gadget's ID;
	TOOLKIT_API int GetID() const;

	// Set/Get the gadget's rectangle (relative to SECDateTimeCtrl's client)
	TOOLKIT_API const CRect& GetRect() const;
	TOOLKIT_API void SetRect(const RECT& rect);

// Overrideables
public:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc) = 0;

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc) = 0;

	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	TOOLKIT_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN/WM_CHAR messages while gadget is enabled
	inline virtual void OnKeyDown(UINT /* nChar */) {}
	inline virtual void OnChar(UINT /* nChar */) {}

	// Handler for mouse messages while gadget is enabled (only if
	// style has WantMouse flag).
	inline virtual void OnLButtonDown(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnLButtonUp(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnMouseMove(UINT /* nFlags */, CPoint /* point */) {}
	inline virtual void OnCancelMode() {}

	// Handles timer events requested by this gadget
	inline virtual void OnTimer() {}

	// Handler for the WM_SYSCOLORCHANGE message (each gadget receives it)
	inline virtual void OnSysColorChange() {}

// Implementation
public:
	TOOLKIT_API virtual ~SECDTGadget();

protected:
	// Passes notify events to parent
	TOOLKIT_API BOOL Notify(UINT uNotifyCode, int nID, LPARAM lParam = 0L);

	// Invalidates this gadget.
	TOOLKIT_API void Invalidate(BOOL bImmediateRedraw = FALSE);

	// Returns the background and text color to use
	TOOLKIT_API COLORREF GetBkColor() const;
	TOOLKIT_API COLORREF GetTextColor() const;

	// Set capture to this gadget
	TOOLKIT_API void CaptureMouse(BOOL bSet);

	// Functions for manipulating timer events
	TOOLKIT_API void StartTimer(UINT uElapse /* ms */);
	TOOLKIT_API void StopTimer();

	// Callback function used for timer events.
	TOOLKIT_API static void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);

// Implementation - data members
protected:
	CRect               m_rect;			// Gadget window rect (relative to
										// SECDateTimeCtrl's client)
	BOOL                m_bEnabled;		// TRUE if we are enabled (have focus)
	int                 m_style;		// Holds style flags
	int                 m_nID;			// This gadgets ID
	int                 m_nValue;		// This gadgets current value
	SECDateTimeCtrl*    m_pCtrl;		// Parent SECDateTimeCtrl
	TOOLKIT_API static CMapWordToOb m_timers;		// Maps current timers onto gadgets
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTStaticGadget
//  
//  Class implementing a non-editable text gadget for SECDateTimeCtrl
//

// Exported through base class. 
class SECDTStaticGadget : public SECDTGadget
{
	TOOLKIT_DECLARE_DYNCREATE(SECDTStaticGadget)

// Construction
public:
	TOOLKIT_API SECDTStaticGadget();

	// Initialises the static gadget (and define the caption)
	TOOLKIT_API BOOL Initialise(SECDateTimeCtrl* pCtrl, LPCTSTR lpszCaption, 
					int nID = -1);
// Operations
public:
	// Function to return the caption
	TOOLKIT_API CString GetCaption() const;

	// Get's a textual representation of this control
	TOOLKIT_API virtual void GetText(LPTSTR lpszBuf);

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc);

// Implementation
public:
	TOOLKIT_API virtual ~SECDTStaticGadget();

// Implementation - data members
protected:
	CString m_strCaption;				// Text of caption
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTNumericGadget
//  
//  Class implementing an editable numeric gadte for SECDateTimeCtrl
//

// Exported through base class. 
class SECDTNumericGadget : public SECDTGadget
{
	TOOLKIT_DECLARE_DYNCREATE(SECDTNumericGadget)

// Construction
public:
	TOOLKIT_API SECDTNumericGadget();

	// Initialise the numeric gadget.
	TOOLKIT_API BOOL Initialise(SECDateTimeCtrl* pCtrl, int nMin, int nMax, int nValue, 
					BOOL bLeadZero, int nID = -1);

// Operations
public:
	// Get's a textual representation of this control
	TOOLKIT_API virtual void GetText(LPTSTR lpszBuf);

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	TOOLKIT_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	TOOLKIT_API virtual void OnKeyDown(UINT nChar);
	TOOLKIT_API virtual void OnChar(UINT nChar);

	// Handler for WM_CANCELMODE
	TOOLKIT_API virtual void OnCancelMode();

// Implementation
public:
	TOOLKIT_API virtual ~SECDTNumericGadget();

protected:
	// Validate's keyboard entry of new date
	TOOLKIT_API BOOL Validate();

// Implementation - data members
protected:
	int  m_nMin;				// Minimum value
	int  m_nMax;				// Maximum value
	int  m_nWidth;				// Maximum no. of chars. allowed
	int  m_nNewValue;			// New value (used during keyboard entry)
	int  m_nCurDigit;			// Current digit being editted
	BOOL m_bLeadZero;			// TRUE if value is to be displayed with
								// leading zero
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTListGadget
//  
//  Class implementing a text gadget with a defined list of possible strings
//

// Exported through base class. 
class SECDTListGadget : public SECDTGadget
{
	TOOLKIT_DECLARE_DYNCREATE(SECDTListGadget)

// Construction
public:
	TOOLKIT_API SECDTListGadget();

	// Initialise the list gadget
	TOOLKIT_API BOOL Initialise(SECDateTimeCtrl* pCtrl, const CStringArray& list, 
					            int nValue, int nID = -1);

// Operations
public:
	// Get's a textual representation of this control
	TOOLKIT_API virtual void GetText(LPTSTR lpszBuf);

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	TOOLKIT_API virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	TOOLKIT_API virtual void OnKeyDown(UINT nChar);
	TOOLKIT_API virtual void OnChar(UINT nChar);

	// Handler for timer events
	TOOLKIT_API virtual void OnTimer();

// Implementation
public:
	TOOLKIT_API virtual ~SECDTListGadget();

protected:
	TOOLKIT_API int FindMatch(LPCTSTR lpszPat, int nCurPos);

// Implementation - data members
protected:
	CStringArray m_list;				// List of possible string
	TCHAR        m_cBuf[3];				// Used during entry of Multi-Byte
										// character
	CString      m_strPat;				// Holds string entered so far 
										// (during partial match)
	BOOL         m_bTimerRunning;		// TRUE when we have a timer enabled
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTButtonGadget
//  
//  Class implementing a simple push button gadget for SECDateTimeCtrl
//

// Exported through base class. 
class SECDTButtonGadget : public SECDTGadget
{
	TOOLKIT_DECLARE_DYNCREATE(SECDTButtonGadget)

// Construction
public:
	TOOLKIT_API SECDTButtonGadget();

	TOOLKIT_API BOOL Initialise(SECDateTimeCtrl* pCtrl, LPCTSTR lpszBmpName, 
					int nID = -1);

// Attributes
public:
	enum				// State flags (see m_nState)
	{
		Capture = 0x0001,			// We currently have capture (tracking
									// button press)
		Down    = 0x0002,			// The button is currently pressed
		Hot     = 0x0004			// Item is hot - under mouse
	};

// Operations
public:

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	TOOLKIT_API virtual void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnCancelMode();

	// Handler for WM_SYSCOLORCHANGE
	TOOLKIT_API virtual void OnSysColorChange();

// Implementation
public:
	TOOLKIT_API virtual ~SECDTButtonGadget();

// Implementation - data members
protected:
	int     m_nState;				// State information
	CBitmap m_bmp;					// Bitmap displayed on button
	LPCTSTR m_lpszBmpName;			// Resource ID of bitmap
	HTHEME  m_hButtonTheme;
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class SECDTSpinGadget
//  
//  Class implementing a spin button gadget for use with SECDateTimeCtrl
//

// Exported through base class. 
class SECDTSpinGadget : public SECDTGadget
{
	TOOLKIT_DECLARE_DYNCREATE(SECDTSpinGadget)

// Construction
public:
	TOOLKIT_API SECDTSpinGadget();

// Attributes
public:
	enum							// State flags (see m_nState)
	{	
		SpinUp       = 0x0001,		// The spin up button is currently pressed
		SpinDown     = 0x0002,		// The spin down button is currently pressed
		CaptureUp    = 0x0004,		// We are tracking press of spin up btn
		CaptureDown  = 0x0008,		// We are tracking press of spin down btn
		TimerRunning = 0x0010,		// We have a timer running
		InitialTimer = 0x0020,		// The timer has been initialised (first
									// tick = 500ms, subsequent ticks = 100ms).
		HotUp        = 0x0040,		// Item is hot - under mouse
		HotDown      = 0x0080		// Item is hot - under mouse
	};								

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	TOOLKIT_API virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	TOOLKIT_API virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	TOOLKIT_API virtual void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API virtual void OnCancelMode();

	// Handler for timer events
	TOOLKIT_API virtual void OnTimer();

// Implementation
public:
	TOOLKIT_API virtual ~SECDTSpinGadget();

protected:
	// Draws either up or down spin button
	TOOLKIT_API void DrawPart(CDC& dc, CRect& r, BOOL bInvert, BOOL bDown);

	// Returns 0 if point is on spin up button, 1 if on spin down, else -1
	TOOLKIT_API int  CheckHit(CPoint point) const;

// Implementation - data members
protected:
	int m_nState;					// Holds state information
	int m_nTimer;					// Timer tick count
	HTHEME m_hSpinTheme;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif 	// WIN32

#endif
