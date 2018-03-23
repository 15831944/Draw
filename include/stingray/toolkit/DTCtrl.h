///////////////////////////////////////////////////////////////////////////////
// DTCtrl.h : Header file for SECDateTimeCtrl. A date and/or time editting
//            control.
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

#ifndef __SECDATET_H__
#define __SECDATET_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

#ifndef __DTGADGET_H__
#include "toolkit\DTGadget.h"
#endif

#ifndef __AFXDISP_H__
#include "afxdisp.h"
#endif

#ifndef __SEC_CALENDAR_H__
#include "toolkit\calendar.h"
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL


// SECDateTimeCtrl styles
#define SEC_DTS_CALENDAR		0x0001L
#define SEC_DTS_UPDOWN			0x0002L
#define SEC_DTS_Y2K_NOFIX		0x0010L		// overrides Y2K fix (backward compatibility)
#define SEC_DTS_Y2K_CONTEXT		0x0020L     // base Y2K fix on current date in control

// SECDateTimeCtrl notifications
//
//  Note we support the following edit control notifications:
//		EN_CHANGE, EN_KILLFOCUS, EN_SETFOCUS.
//  All others are unsupported.
//
#define SECDTN_CHANGED		EN_CHANGE
#define SECDTN_KILLFOCUS	EN_KILLFOCUS
#define SECDTN_SETFOCUS		EN_SETFOCUS

// SECDateTimeCtrl Gadget IDs (bit settings)
#define SECDTID_12HOUR		0x0001
#define SECDTID_24HOUR		0x0002
#define SECDTID_MINUTE		0x0004
#define SECDTID_SECOND		0x0008
#define SECDTID_AMPM		0x0010
#define SECDTID_DAYNO		0x0020
#define SECDTID_DAYNAME		0x0040
#define SECDTID_MONTHNO		0x0080
#define SECDTID_MONTHNAME	0x0100
#define SECDTID_YEAR2		0x0200
#define SECDTID_YEAR4		0x0400
#define SECDTID_CALDROPDOWN	0x4000
#define SECDTID_SPINNER		0x8000
#define SECDTID_ALL			0xffff

/////////////////////////////////////////////////////////////////////////////
// SECDateTimeCtrl window
//
/////////////////////////////
// AutoDuck tag block block for SECDateTimeCtrl 

//@doc SECDateTimeCtrl
//@mfunc void  | SECDateTimeCtrl | SetTabMode | Sets the tab behaviour.
//@comm Sets the tab behaviour, TRUE means tab will move between fields, FALSE
// means move to next control. The default is FALSE, unless fast entry is
// enabled when this is changed to TRUE.  
//@parm BOOL | bEnable | If TRUE, enables tab mode; else, disables tab mode.
//@xref <c SECDateTimeCtrl>

//@doc SECDateTimeCtrl
//@mfunc void  | SECDateTimeCtrl | DisableWMCtlColor | Disables sending of the 
// WM_CTLCOLOR messages.
//@parmopt BOOL | bDisable | TRUE |  If TRUE, disables sending of WM_CTLCOLOR messages.
//@xref <c SECDateTimeCtrl>

//@doc SECDateTimeCtrl
//@mfunc void  | SECDateTimeCtrl | SetBkColor | Sets the background color of the control.
//@parm COLORREF  | cNewColor | parm comment 
//@xref <c SECDateTimeCtrl>

//@doc SECDateTimeCtrl
//@mfunc TCHAR  | SECDateTimeCtrl | GetNullChar | Retrieves the current null mode character. 
//@xref <c SECDateTimeCtrl>

//@doc SECDateTimeCtrl
//@mfunc BOOL  | SECDateTimeCtrl | IsHourPM | Retrieves whether the current hour is PM. 
//@xref <c SECDateTimeCtrl>

// adinsert AutoDuck insertion point for SECDateTimeCtrl 
//@doc SECDateTimeCtrl 
//@class SECDateTimeCtrl is a date/time editing control.  This class works 
// in conjunction with SECDTGadget, an abstract base class for the gadget 
// components used by SECDateTimeCtrl.  The several subclasses that are 
// based on SECDTGadget include:
//
//SECDTStaticGadget		Implements a non-editable text gadget.<nl>
//SECDTNumericGadget	Implements an editable numeric gadget.<nl>
//SECDTListGadget		Implements a text gadget with a defined list of possible strings.<nl>
//SECDTButtonGadget		Implements a simple push button gadget.<nl>
//SECDTSpinGadget		Implements a spin button gadget.<nl>
//
//@comm Before creating/attaching the date/time control, the member 
// function SetFormat must be called.
//
// See the DATETIME sample in the \SAMPLES\TOOLKIT\STANDARD\CONTROLS\DATETIME directory for a 
// demonstration of this class.
//
//@base public | CWnd
class SECDateTimeCtrl : public CWnd
{
	TOOLKIT_DECLARE_DYNAMIC(SECDateTimeCtrl)

	//@access Creation/Initialization
public:
	//@cmember
	/* Constructs a SECDateTimeCtrl object.*/
	TOOLKIT_API SECDateTimeCtrl();

	//@cmember
	/* Creates the edit control and attaches it to the SECDateTimeCtrl object.*/
	TOOLKIT_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, 
				CCreateContext* pContext = NULL);

	//@cmember
	/* Creates the edit control with extended style attributes and attaches it */
	// to the SECDateTimeCtrl object.
	TOOLKIT_API BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, 
				  CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//@cmember
	/* Attaches an SECDateTimeCtrl object to an edit control.*/
	TOOLKIT_API BOOL AttachDateTimeCtrl( UINT uID, CWnd* pParent, DWORD dwDTStyles, 
		                     DWORD dwWinStyles = WS_CHILD|WS_TABSTOP, 
							 DWORD dwExStyle = WS_EX_CLIENTEDGE );
public:

	//@access Attributes

	// Control format type as used by Get/SetFormat.
	//@cmember,menum
	/* Format types */
	enum FormatType
	{
		Time,							//@@emem Locale time format
		ShortDate,						//@@emem Locale short date format 
		LongDate,						//@@emem Locale long date format
		Custom							//@@emem A user supplied date/time format string
	};									

	// The validation types as used by Get/SetMinMax
	//@cmember,menum
	/* Validation types*/
	enum ValidationMode
	{
		NoValidation,					//@@emem No validation is required
		TimeValidation,					//@@emem Validation of time fields only
		DateValidation,					//@@emem Validation of date fields only
		DateTimeValidation				//@@emem Validation of date & time fields
	};

	// Definitions of non-editable fields as used by Get/SetNoEdit
	//@cmember,menum
	/* Non-editable fields*/
	enum NoEdit
	{
		FixedYear   = 0x0001,			//@@emem The year is non-editable
		FixedMonth  = 0x0002,			//@@emem The month is non-editable
		FixedDay    = 0x0004,			//@@emem The day is non-editable
		FixedHour   = 0x0008,			//@@emem The hour is non-editable
		FixedMinute = 0x0010,			//@@emem The minute is non-editable
		FixedSecond = 0x0020,			//@@emem The second is non-editable
		FixedDate   = 0x0007,			//@@emem The date is non-editable
		FixedTime   = 0x0038			//@@emem The time is non-editable
	};

	// Set/Get the current validation mode and the ranges being validated to.
	//@cmember
	/* Sets the current validation mode and the ranges being validated.*/
	TOOLKIT_API BOOL SetMinMax(const COleDateTime& minDateTime, 
				   const COleDateTime& maxDateTime, 
				   ValidationMode mode = DateTimeValidation);

	//@cmember
	/* Gets the current validation mode and the ranges being validated.*/
	TOOLKIT_API ValidationMode GetMinMax(COleDateTime& minDateTime, 
							 COleDateTime& maxDateTime) const;

	// Set/Get the current date/time format
	//@cmember
	/* Sets the current date/time format.*/
	TOOLKIT_API void SetFormat(FormatType format);

	//@cmember
	/* Sets the current date/time format.*/
	TOOLKIT_API void SetFormat(LPCTSTR lpszFormat);

	//@cmember
	/* Gets the current date/time format.*/
	TOOLKIT_API void GetFormat(FormatType& format) const;

	//@cmember
	/* Gets the current date/time format.*/
	TOOLKIT_API void GetFormat(CString& format) const;

	//@cmember
	/* Sets the background color.*/
	TOOLKIT_API void SetBkColor(COLORREF cNewColor) { m_cBkColor=cNewColor; }

	//@cmember
	/* Enables fast input in numeric fields.*/
	TOOLKIT_API void EnableFastEntry(BOOL bEnable = TRUE);

	//@cmember
	/* Enables fast input in numeric fields.*/
	TOOLKIT_API void EnableFastEntry(BOOL bEnable, BOOL bTabEnable);

	//@cmember
	/* Determines whether fast input is enabled.*/
	TOOLKIT_API BOOL IsFastEntryEnabled() const;

	// With fast entry enabled, when a 
	// numeric field has received a valid input (it's maximum number of
	// digits), it advances input focus to the next field.

	//@cmember
	/* Sets the tab behaviour.*/
	TOOLKIT_API void SetTabMode(BOOL bEnable);

	// Sets the tab behaviour, TRUE means tab will move between fields, FALSE
	// means move to next control. The default is FALSE, unless fast entry is
	// enabled when this is changed to TRUE.
	// Set/Determine the current modified state.

	//@cmember
	/* Sets the current modified state.*/
	TOOLKIT_API void SetModified(BOOL bModified);

	//@cmember
	/* Sets the current modified state.*/
	TOOLKIT_API void SetModified(BOOL bDate, BOOL bTime);

	//@cmember
	/* Returns the current modified state.*/
	TOOLKIT_API BOOL IsModified() const;

	//@cmember
	/* Returns the current modified state.*/
	TOOLKIT_API void IsModified(BOOL& bDate, BOOL& bTime) const;

	// Returns TRUE if the user is currently in the middle of editting one
	// of the numeric fields
	//@cmember
	/* Determines if one of the fields is being edited.*/
	TOOLKIT_API BOOL IsEditing() const;

	// Set/Get the current date and time
	//@cmember
	/* Sets the current date and time in the control.*/
	TOOLKIT_API BOOL SetDateTime(const COleDateTime& datetime);

	//@cmember
	/* Sets the current date in the control.*/
	TOOLKIT_API BOOL SetDate(const COleDateTime& date);

	//@cmember
	/* Sets the current time in the control.*/
	TOOLKIT_API BOOL SetTime(const COleDateTime& time);

	//@cmember
	/* Gets the current date and time in the control.*/
	TOOLKIT_API const COleDateTime& GetDateTime() const;

	// Set/Get the edittable fields.
	//@cmember
	/* Gets the non-editable fields.*/
	TOOLKIT_API int  GetNoEdit() const;
	
	//@cmember
	/* Sets the non-editable fields.*/
	TOOLKIT_API void SetNoEdit(int nNoEdit);

	//@cmember
	/* Returns the current null mode character.*/
	inline TCHAR GetNullChar() const { return m_cNull; }

	// AM/PM indicator
	//@cmember
	/* Returns TRUE if current hour is PM.*/
	inline BOOL IsHourPM()		{ return m_bHourPM; }

public:

	//@access Operations

	//@cmember
	/* Forces the specified gadget to be redrawn.*/
	TOOLKIT_API void InvalidateGadget(SECDTGadget* pGadget, BOOL bImmediateRedraw = FALSE);
	
	//@cmember
	/* Forces the specified gadget to be redrawn.*/
	TOOLKIT_API void InvalidateGadget(int nIndex, BOOL bImmediateRedraw = FALSE);

	//@cmember
	/* Returns the index of the gadget at the given portion of the window.*/
	TOOLKIT_API int  GadgetFromPoint(CPoint point);

	//@cmember
	/* Brings the specified gadget into the displayable portion of the window.*/
	TOOLKIT_API void BringIntoView(SECDTGadget* pGadget);
	
	//@cmember
	/* Brings the specified gadget into the displayable portion of the window.*/
	TOOLKIT_API void BringIntoView(int nIndex);

	//@cmember
	/* Forces the control to re-size to fit its content exactly.*/
	TOOLKIT_API void SizeToContent();

	//@cmember
	/* Validates the given date/time to the current ranges.*/
	TOOLKIT_API BOOL Validate(const COleDateTime& datetime) const;

	//@cmember
	/* Sets control to null date entry mode.*/
	// Add one parameter to control the null state.
//	void SetNull(TCHAR cNull = _T('_'));
	TOOLKIT_API void SetNull(TCHAR cNull = _T('_'), BOOL bAlways = FALSE);
	
	//@cmember
	/* Disables sending of the WM_CTLCOLOR messages*/
	TOOLKIT_API void DisableWMCtlColor(BOOL bDisable = TRUE);

	//@access Overrides

	// Function called just before a commit of a new date/time is applied.
	// Return FALSE to abandon the commit.
	//@cmember
	/* Called just before a commit of a new date/time is applied.*/
	TOOLKIT_API virtual BOOL OnChanging(const COleDateTime& newDateTime);

	// Function called after the date/time has been modified. The default
	// implementation passes a SECDTN_CHANGED notification to the parent.
	//@cmember
	/* Called after the date/time has been modified.*/
	TOOLKIT_API virtual void OnChanged();

// Implementation
public:
	TOOLKIT_API virtual ~SECDateTimeCtrl();

protected:
	// Function responsible for parsing the date/time format string and 
	// building the m_gadgets component list.
	TOOLKIT_API virtual void ParseDateTimeFormat();

	// Functions used by ParseDateTimeFormat for parsing individual components
	// of the date/time string
	TOOLKIT_API void ParseHours(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseMinutes(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseSeconds(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseAmPm(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseDay(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseMonth(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseYear(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseEra(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API void ParseQuotedText(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	TOOLKIT_API BOOL CheckLeadZero(LPCTSTR& lpsz, TCHAR c) const;
	TOOLKIT_API void FlushStatic(LPCTSTR lpszStart, LPCTSTR lpszEnd);

	// Functions used for changing the value of a speicific field 
	TOOLKIT_API BOOL ChangeHour(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeMinute(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeSecond(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeAmPm(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeDay(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeMonth(UINT uNotifyCode, int nID, LPARAM lParam);
	TOOLKIT_API BOOL ChangeYear(UINT uNotifyCode, int nID, LPARAM lParam);

	// Function used for converting a two-digit year to four-digit year
	TOOLKIT_API virtual int GetCentury(int nTwoDigitYear);

	// Function used in GetCentury. Required because VC 5 does now have a replace member
	// in CString.
	TOOLKIT_API TCHAR* ot_str_replace(const TCHAR* pszInput, const TCHAR* pszOld, const TCHAR* pszNew);

	// Functions for moving forward/backwards a gadget
	TOOLKIT_API void AdvanceGadget();
	TOOLKIT_API void RetreatGadget();

	// Function used to layout the gadgets within the controls client
	TOOLKIT_API virtual void LayoutGadgets();

	// Function used for controlling the drawing of the gadgets.
	TOOLKIT_API virtual void Draw(CDC& dc);

	// Handler for spinner events
	TOOLKIT_API BOOL SpinnerEvent(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handler for creating the popup calendar
	TOOLKIT_API virtual BOOL PopupCalendar(UINT uNotifyCode, int nID, LPARAM lParam);

	// Override this to hook in a SECPopupCalendar derived object.
	inline virtual void OnCreatePopupCalendar() 	{ m_pPopupCalendar = new SECPopupCalendar; }

	// Functions for updating the specified gadgets with new values and
	// for forcing them to be redisplayed
	TOOLKIT_API void UpdateGadgets(const COleDateTime& datetime);
	TOOLKIT_API void UpdateGadgets(UINT nFlags = SECDTID_ALL);

	// Performs validation of a new date (and can correct certain
	// fields to make it valid)
	TOOLKIT_API virtual BOOL Validate(COleDateTime& datetime, int nPos) const;

	// Handles notify events from gadgets
	TOOLKIT_API virtual BOOL OnNotify(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handles requests from gadgets to capture the mouse.
	TOOLKIT_API void CaptureMouse(SECDTGadget* pGadget, BOOL bSet);

	// Functions for causing the gadget display to be re-built.
	TOOLKIT_API virtual void Tidy();
	TOOLKIT_API void TidyEx();
	TOOLKIT_API void ResetGadgets();
	TOOLKIT_API void ResetCurrentGadget( int nCurGadget );
	TOOLKIT_API BOOL CheckGadgetFocusAbility( int nGadget );
	TOOLKIT_API int  GetFirstFocusGadget();

	// Returns fields which are present (used for NULL dates)
	TOOLKIT_API WORD GetNullFields() const;

	// Checks whether we can leave a NULL edit state.
	TOOLKIT_API void CheckNull(BOOL bUpdate = TRUE);

	// modify day/month format, if desired
	inline  virtual void OnMonthNameInit(CString& strMonthName) { strMonthName; }
	inline  virtual void OnDayNameInit(CString& strDayName) { strDayName; }

	// Sends the notification to our parent.
	TOOLKIT_API void SendNotification(UINT nCode) const;

	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		LRESULT OnThemeChanged();
	#endif

protected:
// Implementation - data members
	enum								// Internal state flags
	{
		DateModified = 0x0001,			// The date has been modified
		TimeModified = 0x0002,			// The time has been modified
		Editing      = 0x0004			// A numeric field is currently being
	};									// editted.

	int               m_nState;			// Holds state information (see flags)
	int               m_nNoEdit;		// Holds non-editable fields (see NoEdit)
	BOOL			  m_bFastInput;		// TRUE if fast input enabled
	BOOL              m_bTabMode;		// TRUE if tab is to move between fields
	BOOL              m_bCtlColor;		// TRUE if the sending of WM_CTLCOLOR messages is enabled
	COleDateTime      m_datetime;		// Current date/time
	COleDateTime      m_datetimeMin;	// Minimum date/time
	COleDateTime      m_datetimeMax;	// Maximum date/time
	ValidationMode    m_validMode;		// Validation mode (see ValidationMode)
	FormatType        m_formatType;		// Date/Time format type (see FormatType)
	CString           m_strCustomFormat;// Holds custom date/time format string
	HFONT             m_hFont;			// Font used by control
	int               m_nCurGadget;		// Current gadget (gadget with focus)
	int               m_nXOrigin;		// Current offset (scrolled percentage)
										// of window.
	int               m_nRightOffset;	// Amount of space on right reserved for
										// fixed gadgets
	int               m_nFixed;			// No. of fixed gadgets.
	SECDTGadget*      m_pCapture;		// Ptr to gadget which has mouse capture
	SECPopupCalendar* m_pPopupCalendar;	// Handle of popup calendar 
										// (normally NULL)
	TCHAR             m_cNull;			// Char. used to display NULL gadgets.
	BOOL			  m_bHourPM;		// AM/PM toggle
	COLORREF          m_cBkColor;		// Current background color
	COLORREF          m_cTextColor;		// Current text color
	HTHEME			  m_hEditTheme;		// Theme Handle

public:
	int               m_nBkDisabled;	// System background color when disabled
	int               m_nFgDisabled;	// System foreground color when disabled
	UINT              m_nCalBmp;		// ID of bmp to display on cal. drop down
										// button.
	CRuntimeClass*    m_pListGadClass;	// RTTI info for creating SECDTListGadget
	CRuntimeClass*    m_pNumGadClass;	// RTTI info for creating SECDTNumericGadget
	CRuntimeClass*    m_pStaticGadClass;// RTTI info for creating SECDTStaticGadget
	CRuntimeClass*    m_pButtonGadClass;// RTTI info for creating SECDTButtonGadget
	CRuntimeClass*    m_pSpinGadClass;	// RTTI info for creating SECDTSpinGadget

protected:
	// SECDTGadgetArray would normally be implemented as a template 
	// (CTypedPtrArray). Since templates are not implemented by some Unix
	// compilers, we copy what the template would have done.
	class SECDTGadgetArray : public CObArray
	{
	public:
		// Accessing elements
		inline SECDTGadget* GetAt(int nIndex) const
			{ return (SECDTGadget*)CObArray::GetAt(nIndex); }
		inline SECDTGadget*& ElementAt(int nIndex)
			{ return (SECDTGadget*&)CObArray::ElementAt(nIndex); }
		inline void SetAt(int nIndex, SECDTGadget* ptr)
			{ CObArray::SetAt(nIndex, ptr); }

		// Potentially growing the array
		inline void SetAtGrow(int nIndex, SECDTGadget* newElement)
		   { CObArray::SetAtGrow(nIndex, newElement); }
		inline int Add(SECDTGadget* newElement)
		   { return (int)CObArray::Add(newElement); }
		inline int Append(const SECDTGadgetArray& src)
		   { return (int)CObArray::Append(src); }
		inline void Copy(const SECDTGadgetArray& src)
			{ CObArray::Copy(src); }

		// Operations that move elements around
		inline void InsertAt(int nIndex, SECDTGadget* newElement, int nCount = 1)
			{ CObArray::InsertAt(nIndex, newElement, nCount); }
		inline void InsertAt(int nStartIndex, SECDTGadgetArray* pNewArray)
		   { CObArray::InsertAt(nStartIndex, pNewArray); }

		// overloaded operator helpers
		inline SECDTGadget* operator[](int nIndex) const
			{ return (SECDTGadget*)CObArray::operator[](nIndex); }
		inline SECDTGadget*& operator[](int nIndex)
			{ return (SECDTGadget*&)CObArray::operator[](nIndex); }
	};

	// Object maintaining status for null dates.
	class SECNull
	{
	public:
		TOOLKIT_API SECNull();

		// Enables Null edit mode
		// Use one parameter to control the null state.
		TOOLKIT_API void Set(BOOL bAlways = FALSE);

		// Sets the currently displayed fields
		TOOLKIT_API void SetActualFields(WORD wActualFields);

		// Aborts null edit mode.
		TOOLKIT_API void Clear();
		
		// Returns the bit settings for fields yet to be completed
		inline WORD GetFields() const { return WORD(m_wNullFields & m_wActualFields); }

		// Returns TRUE if we are currently in NULL date mode
		inline BOOL IsSet() const     { return m_bSet; }

		// Functions for setting/getting the various date/time fields.
		// Note that the get functions return -1 if the fields has yet to be
		// entered.
		TOOLKIT_API int  GetHour() const;
		TOOLKIT_API void SetHour(int nHour);
		TOOLKIT_API int  GetMinute() const;
		TOOLKIT_API void SetMinute(int nMinute);
		TOOLKIT_API int  GetSecond() const;
		TOOLKIT_API void SetSecond(int nSecond);
		TOOLKIT_API int  GetYear() const;
		TOOLKIT_API void SetYear(int nYear);
		TOOLKIT_API int  GetMonth() const;
		TOOLKIT_API void SetMonth(int nMonth);
		TOOLKIT_API int  GetDay() const;
		TOOLKIT_API void SetDay(int nDay);
		TOOLKIT_API int  GetDayOfWeek() const;
		TOOLKIT_API void SetDayOfWeek(int nDayOfWeek);

		enum							// Bit settings for m_wNullFields
		{
			Hour      = 0x0001,			// Set if hour has yet to be entered
			Minute    = 0x0002,			// Set if minute has yet to be entered
			Second    = 0x0004,			// Set if second has yet to be entered
			Year      = 0x0008,			// Set if year has yet to be entered
			Month     = 0x0010,			// Set if month has yet to be entered
			Day       = 0x0020,			// Set if day has yet to be entered
			DayOfWeek = 0x0040			// Set if day of week has yet to be entered
		};

	protected:
		WORD m_wNullFields;				// Bit settings for incomplete fields
		WORD m_wActualFields;			// Bit settings for fields present
		BOOL m_bSet;					// TRUE if date is currently null
		// Add one data member to control the null state.
		BOOL m_bAlways;					// TRUE if date always remains at null state
		int  m_nHour;					// Holds hour while in null state
		int  m_nMinute;					// Holds minute while in null state
		int  m_nSecond;					// Holds second while in null state
		int  m_nYear;					// Holds year while in null state
		int  m_nMonth;					// Holds month while in null state
		int  m_nDay;					// Holds day while in null state
		int  m_nDayOfWeek;				// Holds day of week while in null state
	} m_null;

	// m_gadgets is an array of all the gadget components.
	SECDTGadgetArray m_gadgets;

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg UINT OnGetDlgCode();
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg void OnEnable(BOOL bEnable);
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnSysColorChange();
	TOOLKIT_API afx_msg void OnCancelMode();
	TOOLKIT_API afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg int OnMouseActivate( CWnd* pDesktopWnd, UINT nHitTest, UINT message );
#ifndef UNDER_CE
	TOOLKIT_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#endif //UNDER_CE (WindowsCE)
	TOOLKIT_API afx_msg void OnNcPaint();
	TOOLKIT_API afx_msg LRESULT OnCalendarOK(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnCalendarCancel(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);

	// A very dear friend of mine ...
	friend class SECDTGadget;
};


/////////////////////////////////////////////////////////////////////////////
// Function for converting a DATE (base type of COleDateTime) to a tm structure
extern TOOLKIT_API BOOL SECTmFromOleDate(COleDateTime CdtSrc, struct tm& tmDest);


/////////////////////////////////////////////////////////////////////////////
// Helper function for setting the date/time of a COleDateTime object
extern TOOLKIT_API BOOL SECSetOleDateTime(COleDateTime& dt, int nYear, int nMonth, 
							  int nDay, int nHour, int nMinute, int nSecond);

/////////////////////////////////////////////////////////////////////////////
// inline functions
inline int SECDateTimeCtrl::SECNull::GetHour() const
{ return ((m_wNullFields & m_wActualFields) & Hour)      ? -1 : m_nHour;      }

inline int  SECDateTimeCtrl::SECNull::GetMinute() const 
{ return ((m_wNullFields & m_wActualFields) & Minute)    ? -1 : m_nMinute;    }

inline int SECDateTimeCtrl::SECNull::GetSecond() const 
{ return ((m_wNullFields & m_wActualFields) & Second)    ? -1 : m_nSecond;    }

inline int SECDateTimeCtrl::SECNull::GetYear() const   
{ return ((m_wNullFields & m_wActualFields) & Year)      ? -1 : m_nYear;      }

inline int SECDateTimeCtrl::SECNull::GetMonth() const  
{ return ((m_wNullFields & m_wActualFields) & Month)     ? -1 : m_nMonth;     }

inline int SECDateTimeCtrl::SECNull::GetDay() const    
{ return ((m_wNullFields & m_wActualFields) & Day)	     ? -1 : m_nDay;       }

inline int SECDateTimeCtrl::SECNull::GetDayOfWeek() const
{ return ((m_wNullFields & m_wActualFields) & DayOfWeek) ? -1 : m_nDayOfWeek; }

inline void SECDateTimeCtrl::SetTabMode(BOOL bEnable)
{ m_bTabMode = bEnable; }

inline void SECDateTimeCtrl::DisableWMCtlColor(BOOL bDisable /* = TRUE */)
{ m_bCtlColor = !bDisable; }

inline void SECDateTimeCtrl::SendNotification(UINT nCode) const
{
// Not defined on CE platforms
#ifdef WS_EX_NOPARENTNOTIFY  
	if(GetExStyle() & WS_EX_NOPARENTNOTIFY)
		return;
#endif
	GetParent()->SendMessage(WM_COMMAND,
							 (WPARAM) MAKELONG(GetDlgCtrlID(), nCode),
							 (LPARAM) m_hWnd);
}

inline COLORREF SECDTGadget::GetBkColor() const
{ return m_pCtrl->m_cBkColor; }

inline COLORREF SECDTGadget::GetTextColor() const
{ return m_pCtrl->m_cTextColor; }

/////////////////////////////////////////////////////////////////////////////

#define ON_SECDTN_CHANGED(id, memberFxn) \
		ON_EN_CHANGE(id, memberFxn)

#define ON_SECDTN_SETFOCUS(id, memberFxn) \
		ON_EN_SETFOCUS(id, memberFxn)

#define ON_SECDTN_KILLFOCUS(id, memberFxn) \
		ON_EN_KILLFOCUS(id, memberFxn)

/////////////////////////////////////////////////////////////////////////////

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


