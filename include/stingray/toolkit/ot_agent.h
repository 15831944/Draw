///////////////////////////////////////////////////////////////////////////////
// ot_agent.h
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
// Author:       Praveen Ramesh
// Description:  Declaration SECAgentCharacterExPtr, IAgentApp and associated
//				 classes. 
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef _OT_AGENT
#define _OT_AGENT

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifndef _OT_AGENTID
#include "toolkit\ot_agentid.h"
#endif

#ifndef _AgentNotifySink_h_
#include "toolkit\notify.h"
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


//   enum of type and status values for a SECAgentCharAct object.
//   This enum is not nested within the namespace of any class, since it is used by multiple classes.
//@enum Agent Character Act's type and status.
enum ActTypeAndStatus
{
	NonCritical = 0x0001,
	Critical = 0x0002,
	InProgress = 0x0004,
	TipOfTheDay = 0x0008,
};

// Forward declarations
class SECAgentCharacterExPtr;
class IAgentApp;

/////////////////////////////////////////////////////////////////////////////
// SECAgentCharAct window
//
/////////////////////////////

//@doc SECAgentCharAct
//@mfunc BOOL  | SECAgentCharAct | Execute | Contains code requesting the corresponding
// Animation for the Act on the character object.
//@xref <c SECAgentCharAct>

//@doc SECAgendCharAct
//@mfunc UINT | SECAgentCharAct | GetActTypeAndStatus | Gets the Act's TypeAndStatus
//@rdesc Return the Act's type and status
//@xref <c SECAgentCharAct>
//@doc SECAgentCharAct
//@mfunc void | SECAgentCharAct | SetActTypeAndStatus | Sets the Act's TypeAndStatus
//@parm UINT | nTypeAndStatus | The Act's type and status
//@xref <c SECAgentCharAct>

//@doc SECAgentCharAct 
//@mdata long | SECAgentCharAct | m_lOldLeft	| X co-ordinate of the origianl position
//@mdata long | SECAgentCharAct | m_lOldTop	| Y co-ordinate of the origianl position
//@mdata long | SECAgentCharAct | m_lFinalID	| ID of the final request made to the character 
// within the Execute function.
//@mdata long | SECAgentCharAct | m_lReturnAnimBeginID | ID of the request that plays the return
// animation for the Act, like moving the agent back to the original position.
//@mdata long | SECAgentCharAct | m_lActID	| The Act ID of the Act.
//@class The SECAgentCharAct is an abstract base class from which all the other Act objects are derived.
// This class provides the basic implementation for the Act object.
//
// Executing a sequence of animation on a Character (let us call it an Act) within a SECAgentCharAct 
// object will allow the Act to be represented by an ActID and also to be categorized as Critical or NonCritical.
// Using the ActID the corresponding Act can be interrupted any time at a later stage. Also, the underlying framework
// provides high priority to the Critical Acts by interrupting any current/pending NonCritical Acts.
//
// Such classification of Acts into Critical/NonCritical and the ability to Interrupt the current Acts 
// provide a powerful way of handling the agent character for demonstration and instruction purposes.
//
// For example, if the character is in the middle of providing a tooltip hint, and the user triggers Dynamic Data Validation
// which causes a Message Prompt via the agent, then the agent should immediately abandon the tooltip task 
// and move on to the DDV Prompt message task. This is possible only if the Acts are finely demarcated 
// and prioritized, such as in this framework.
// 
// You can create custom Acts by deriving from this base class.
//@BASE public | CObject
class SECAgentCharAct : public CObject
{
public:
	//@access Creation/Initialization
	TOOLKIT_API SECAgentCharAct(SECAgentCharacterExPtr* pptrChar);

	// Public Member Variables
	long m_lOldLeft, m_lOldTop;
	long m_lFinalID, m_lReturnAnimBeginID;
	long m_lActID;
	UINT m_nActTypeAndStatus;

	//@access  Accessors
	//@cmember
	/* Gets the Act's TypeAndStatus */
	inline virtual UINT GetActTypeAndStatus() { return m_nActTypeAndStatus; }
	//@cmember
	/* Sets the Act's TypeAndStatus */
	inline virtual void SetActTypeAndStatus(UINT nTypeAndStatus){ m_nActTypeAndStatus = nTypeAndStatus; }

	//@access Operations
	//@cmember
	/* Execute the Act */
	virtual BOOL Execute() = 0;
	//@cmember
	/* Interrupt the Act */
	TOOLKIT_API virtual void Interrupt();

	//@access virtual notifications
	//@cmember
	/* Notification to indicate beginning of the act. */
	TOOLKIT_API virtual BOOL OnBeginAct();
	//@cmember
	/* Notification to indicate the end of the act. */
	TOOLKIT_API virtual void OnEndAct();
	//@cmember
	/* Notification to indicate the completion of a bookmark. */
	TOOLKIT_API STDMETHODIMP OnBookMark(long dwBookMarkID);

protected:
	// Implementation Member Variables
	SECAgentCharacterExPtr* m_pptrChar;

	// Implementation Member Functions
	inline SECAgentCharacterExPtr& GetAgentCharRef(){ASSERT(m_pptrChar); return (*m_pptrChar);}
};

typedef CTypedPtrList<CObList, SECAgentCharAct*>  CActList;

//@doc SECAgentPromptAtWndAct 
//@class The SECAgentPromptAtWndAct moves the character beside the specified Window, GesturesAt the window
// and speaks out the supplied text.
//@BASE public | SECAgentCharAct
class SECAgentPromptAtWndAct : public SECAgentCharAct
{
public:
	// Construction and Destruction
	//@access Construction
	inline SECAgentPromptAtWndAct(SECAgentCharacterExPtr* pptrChar, HWND hWnd, BSTR bstr) : SECAgentCharAct(pptrChar), m_hWnd(hWnd)
		{m_bstrText = ::SysAllocString(bstr);}
	inline virtual ~SECAgentPromptAtWndAct()	{SysFreeString(m_bstrText);}

	// Operations	
	TOOLKIT_API virtual BOOL Execute();

protected:
	// Implementation Member Variables
	HWND m_hWnd;
	BSTR m_bstrText;
};

//@doc SECAgentPromptAtRectAct 
//@class The SECAgentPromptAtRectAct moves the character beside the specified rectangle, GesturesAt the rect
// and speaks out the supplied text.
//@BASE public | SECAgentCharAct
class SECAgentPromptAtRectAct : public SECAgentCharAct
{
public:
	// Construction and Destruction
	//@access Construction
	inline SECAgentPromptAtRectAct(SECAgentCharacterExPtr* pptrChar, CRect rect, BSTR bstr) : SECAgentCharAct(pptrChar), m_rect(rect)
		{m_pptrChar = pptrChar; m_bstrText = ::SysAllocString(bstr);}
	inline virtual ~SECAgentPromptAtRectAct()	{SysFreeString(m_bstrText);}

	// Operations	
	TOOLKIT_API virtual BOOL Execute();

protected:
	// Implementation Member Variables
	CRect m_rect;
	BSTR m_bstrText;
};

//@doc SECAgentSpeakAct 
//@class The SECAgentSpeakAct just speaks out the supplied text.
// Wrapping the Speak call within this Act object helps to interrupt this Act when a more Critical Act occurs.
//@BASE public | SECAgentCharAct
class SECAgentSpeakAct : public SECAgentCharAct
{
public:
	// Construction and Destruction
	//@access Construction
	inline SECAgentSpeakAct(SECAgentCharacterExPtr* pptrChar, BSTR bstr) : SECAgentCharAct(pptrChar)
		{ m_bstrText = ::SysAllocString(bstr);}
	inline virtual ~SECAgentSpeakAct()	{SysFreeString(m_bstrText);}

	// Operations	
	TOOLKIT_API virtual BOOL Execute();

	BSTR m_bstrText;
};

//@doc SECAgentNotifySink 
//@class SECAgentNotifySink is the default sink for the SECAgentCharacterExPtr object.
// This class listens for RequestComplete, RequestStart and Command notifications.
// You can derive from this class and listen for more notifications or modify the default behavior
// by just overriding the corresponding virtuals.
//@BASE public | AgentNotifySink
class SECAgentNotifySink : public AgentNotifySink
{
public:
	// Construction
	inline SECAgentNotifySink(SECAgentCharacterExPtr* pptrChar) : AgentNotifySink(), m_pptrChar(pptrChar)
		{AddRef();};

	// Implementation Overrides
	//@access Notification  Handlers
	TOOLKIT_API STDMETHOD(raw_RequestComplete)(long dwRequestID, long hrStatus);
	TOOLKIT_API STDMETHOD(raw_RequestStart)(long dwRequestID);
    TOOLKIT_API STDMETHOD(raw_Command)(long dwCommandID, IUnknown * punkUserInput);
	TOOLKIT_API STDMETHOD(raw_BookMark)(long dwBookMarkID);

protected:
	// Implementation Member Variables
	SECAgentCharacterExPtr* m_pptrChar;
};

// CWinApp::DoMessageBox is overriden in SECAgentApp to hook in agents based on the following
// interrupt types specified via IAgentApp::SetMessageBoxInterruptType. The type can be one or more of the following.
// These types are also used in SECAgentCharacterExPtr::MessageBox calls.
enum MBoxInterruptType
{
	None = 0x0000,
	NoMessageBox	= 0x0001,		// Will prevent displaying the default message box (by not calling AfxMessageBox).
	CharReadOut = 0x0002,			// Currently loaded Agent will read out the text.
	StoreMessage = 0x0004			// The text will be cached in a IAgentApp string member var. Cannot be used with SECAgentCharacterExPtr::MessageBox calls.
};

//@doc SECAgentCharacterExPtr 
//@class SECAgentCharacterExPtr is a subclass of the IAgentCharacterExPtr smart pointer that in-turn 
// encapsulates the IAgentCharacterEx interface.
// This class creates and registers a default notification sink for the underlying character.
// You can enable a pre-created command "Change Default Character" using which users can change the 
// character at any time.
// It provides APIs that instructs the underlying character to prompt at a Window or Rectangle.
// Using the MessageBox API, you can display a message box accompanied by the Agent 
// reading out the text from it.
// It also provides an elaborate framework to enclose character actions within Act objects. 
// Take a look at SECAgentCharAct for more information.
//@BASE public | IAgentCharacterExPtr
class SECAgentCharacterExPtr : public IAgentCharacterExPtr
{
public:
	// Construction, Initialization and Uninitialization
	//@access Construction
	TOOLKIT_API SECAgentCharacterExPtr();
	TOOLKIT_API virtual ~SECAgentCharacterExPtr();
	
	//@cmember
	/* Unloads the underlying character object */
	TOOLKIT_API void UnloadChar(IAgentExPtr& ptrAgent);

	//@cmember
	/* Creates a notification sink for the underlying character object */
	TOOLKIT_API virtual BOOL CreateNotifySink(IAgentExPtr& ptrAgent);
	//@cmember
	/* Release the notification sink for the underlying character object */
	TOOLKIT_API virtual void ReleaseNotifySink(IAgentExPtr& ptrAgent);

	//@access Attributes
	//@cmember
	/* This state tells you whether the character is busy playing a type of Act. */
	TOOLKIT_API BOOL IsBusy(UINT nActType);	
	//@cmember
	/* Enable/Disable the "Change Default Character" Command */
	TOOLKIT_API void EnableCharChangeCommand(BOOL bEnable = TRUE);
	//@cmember
	/* Get Act object for the corresponding ID. */
	TOOLKIT_API SECAgentCharAct* GetAct(long lActID);

	//@access Operations
	//@cmember
	/* Prompt at the window */
	TOOLKIT_API void PromptAt(CWnd* pWnd, const CString& strText, UINT nType = NonCritical, long* lActID = NULL);
	//@cmember
	/* Prompt at the window */
	TOOLKIT_API void PromptAt(HWND hWnd, const CString& strText, UINT nType = NonCritical, long* lActID = NULL);
	//@cmember
	/* Prompt at the window */
	TOOLKIT_API virtual void PromptAt(HWND hWnd, BSTR bstrText, UINT nType = NonCritical, long* lActID = NULL);
	//@cmember
	/* Get the optimal position for the character to move to beside the window */
	TOOLKIT_API CPoint* GetOptimalPosAdjacentTo(HWND hWnd, CPoint& pt);

	//@cmember
	/* Prompt at the rect */
	TOOLKIT_API void PromptAt(CRect& rect, const CString& strText, UINT nType = NonCritical, long* lActID = NULL);
	//@cmember
	/* Prompt at the rect */
	TOOLKIT_API virtual void PromptAt(CRect& rect, BSTR bstrText, UINT nType = NonCritical, long* lActID = NULL);

	//@cmember
	/* Speak out the text */
	TOOLKIT_API virtual void Speak(BSTR bstrText, UINT nType = NonCritical, long* lActID = NULL);

	//@cmember
	/* Interrupt a particular or all Acts */
	TOOLKIT_API virtual void InterruptAct(long nActID);

	//@cmember
	/* Display an Agent enabled message box. */
	TOOLKIT_API virtual int MessageBox( LPCTSTR lpszPrompt, UINT nType = MB_OK, UINT nIDHelp = 0, UINT nInterruptType = CharReadOut);

	//@cmember
	/* Add this act to the Acts list */
	TOOLKIT_API void AddAct(SECAgentCharAct* pAct);
	//@cmember
	/* Run pending acts in the Act list.*/
	TOOLKIT_API void RunActs();

	//@access virtual notifications
	//@cmember
	/* Command notification from the sink.*/
	TOOLKIT_API virtual HRESULT OnCommand(long dwCommandID, IUnknown * punkUserInput);
	//@cmember
	/* The default interrupt action. */
	TOOLKIT_API virtual void DefaultInterruptAction();
	//@cmember
	/* Notification to indicate beginning of the act. */
	TOOLKIT_API virtual BOOL OnBeginAct(SECAgentCharAct* pAct);
	//@cmember
	/* Notification to indicate the end of the act. */
	TOOLKIT_API virtual void OnEndAct(SECAgentCharAct* pAct);

	// Public Member Variables
	SECAgentNotifySink* m_pNotifySink;
	long m_lNotifySinkID;
	friend class SECAgentNotifySink;

	CActList m_listActs;
	long m_lUsedUpActIds;
	long m_lSelfID;
	long m_lChangeCharCmdID;
	IAgentExPtr m_ptrAgent;
	IAgentApp* m_pAgentCore;
};

//@doc IAgentApp
//@mfunc void | IAgentApp | SetMessageBoxInterruptType | Sets the current message box interrupt type.
//@rdesc void
//@parm UINT | nType | Message box interrupt type.
//@xref <c IAgentApp>

//@doc IAgentApp
//@mfunc UINT | IAgentApp | GetMessageBoxInterruptType | Gets the current message box interrupt type.
//@rdesc Return message box interrupt type.
//@xref <c IAgentApp>

//@doc IAgentApp
//@mfunc UINT | IAgentApp | GetTipOfTheDayCount |  Gets the current no. of tips. 
//@rdesc Return the current no. of tips. 
//@xref <c IAgentApp>

//@doc IAgentApp 
//@class Deriving your CWinApp object from IAgentApp instantly hooks in a lot of default
// agent functionality into your application. Take a look at the SECAgentApp template for more info.
// It exposes simple APIs to initiaize the AgentServer, create and maintain a default
// agent character (a SECAgentCharacterExPtr object), provides Agent support in Dynamic Data Validation (DDV)
// of forms and dialogs in the app, support for tip of the day and more.
// You need not necessarily derive your CWinApp class from IAgentApp. You could create
// an instance of IAgentApp anywhere in your application. But, part of the DDV support
// implemented in the SECAgentApp template  will have to be reproduced for proper agent 
// enabled DDV functionality. Also, you can not have an IAgentApp interface in your application
// and still work with just SECAgentCharacterExPtr.
class IAgentApp
{
public:
	// Construction and destruction
	//@access Construction
	TOOLKIT_API IAgentApp();
	TOOLKIT_API virtual ~IAgentApp();
	
	//@access More initialization
	//@cmember
	/* Loads the Agent Server and optionally a character */
	TOOLKIT_API virtual void LoadAgent(LPWSTR pwzAgentChar); 
	//@cmember
	/* UnLoads the Agent Server and the underlying character */
	TOOLKIT_API virtual void UnLoadAgent(); 
	//@cmember
	/* Loads and stores a reference to the character */
	TOOLKIT_API BOOL AttachChar(LPWSTR pwzAgent);
	//@cmember
	/* Unloads the underlying character. */
	TOOLKIT_API void DetachChar();

	//@access Utility function
	//@cmember
	/* Creates and returns a reference to SECAgentCharacterExPtr. */
	TOOLKIT_API static SECAgentCharacterExPtr* AFXAPI CreateChar(IAgentExPtr& ptrAgent, LPWSTR pwzAgent, SECAgentCharacterExPtr* pptrInChar = NULL);

	//@access Accessors

	inline SECAgentCharacterExPtr& GetAgentCharRef(){ASSERT(m_pptrChar); return (*m_pptrChar);}
	
	//@cmember
	/* Sets the current message box interrupt type.*/
	inline void SetMessageBoxInterruptType(UINT nType)	{m_uiMessageBoxInterruptType = nType;}
	//@cmember
	/* Gets the current message box interrupt type.*/
	inline UINT GetMessageBoxInterruptType()	{return m_uiMessageBoxInterruptType;}

	//@cmember
	/* Gets the current no. of tips. */
	inline UINT GetTipOfTheDayCount()	{return m_uiTipOfTheDayCount;}

	// public member variables
	
	SECAgentCharacterExPtr*  m_pptrChar; 

	CString m_strMBText;
	long m_lTipOfDayCmdID;
	
	UINT m_uiTipOfTheDayCount, m_uiLatestTip;

	//@access Operations
	//@cmember
	/* Enable or Disable Tip of the Day. */
	TOOLKIT_API void EnableTipOfTheDay(UINT nTipCount);
	//@cmember
	/* Show the tip of the day command in the commands list */
	TOOLKIT_API void ShowTipOfTheDay(UINT nTipID  = 0);
	
	//@access virtual notifications
	//@cmember
	/* Called when a new character is attached. */
	TOOLKIT_API virtual void OnInitChar();
	//@cmember
	/* Handler for the Command notification of the underlying character. */
	TOOLKIT_API virtual HRESULT OnCharCommand(long dwCommandID, IUnknown * punkUserInput);

protected:
	//@access Implementation methods
	//@cmember
	/* Function that supplies the tooltip Act. */
	TOOLKIT_API virtual SECAgentCharAct* GetTipOfTheDayAct(UINT nTip);
	
	// Implementation members
	IAgentExPtr m_ptrAgent; 
	UINT m_uiMessageBoxInterruptType;	// Interrupt normal message box handling
};

//@doc IAgentApp 
// 
// Derive your App class from SECAgentApp passing in CWinApp as the template variable.
// This will provide you agent enabled Dynamic Data Validation in your forms and dialogs, 
// besides providing the other features implemented in IAgentApp. 
template <class T>
class SECAgentApp : public T, public IAgentApp
{
	virtual int DoMessageBox( LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt );
};

//int AFXAPI SECAgentMessageBox( LPCTSTR lpszText, UINT nType = MB_OK, UINT nIDHelp = 0 );

// Agent enabled DDV support in dialogs and forms.
// Always use the following BEGIN_ and END_ macros as a pair.

// Include this macro at the beginning of your DoDataExchange override.
// You should supply a pointer to an IAgentApp interface as the argument.
#define BEGIN_AGENT_DDV(pAgentApp) \
	TRY{ \
	pAgentApp->SetMessageBoxInterruptType(NoMessageBox | StoreMessage); \

// Include this macro at the end of your DoDataExchange override.

#if(_MFC_VER < 0x0700)

#define END_AGENT_DDV() \
	} \
	CATCH(CUserException, e) \
	{ \
		pAgentApp->SetMessageBoxInterruptType(None); \
		CString strPrompt = pAgentApp->m_strMBText; \
		if(!strPrompt.IsEmpty()) \
		{ \
			pAgentApp->m_pptrChar->InterruptAct(-1); \
			pAgentApp->m_pptrChar->PromptAt(pDX->m_hWndLastControl, strPrompt, Critical); \
			pAgentApp->m_strMBText.Empty(); \
		} \
		AfxThrowUserException(); \
	} \
	END_CATCH \
	pAgentApp->SetMessageBoxInterruptType(None); \

#else

#define END_AGENT_DDV() \
	} \
	CATCH(CUserException, e) \
	{ \
		pAgentApp->SetMessageBoxInterruptType(None); \
		CString strPrompt = pAgentApp->m_strMBText; \
		if(!strPrompt.IsEmpty()) \
		{ \
			pAgentApp->m_pptrChar->InterruptAct(-1); \
			HWND hWndLastControl = NULL; \
			hWndLastControl = GetDlgItem( pDX->m_idLastControl )->GetSafeHwnd(); \
			pAgentApp->m_pptrChar->PromptAt(hWndLastControl, strPrompt, Critical); \
			pAgentApp->m_strMBText.Empty(); \
		} \
		AfxThrowUserException(); \
	} \
	END_CATCH \
	pAgentApp->SetMessageBoxInterruptType(None); \

#endif

// Overriding CWinApp::DoMessageBox allows you to hook-in agents with normal 
// message box display. 
template <class T>
int SECAgentApp<T>::DoMessageBox( LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt )
{
	if(m_pptrChar && (*m_pptrChar).GetInterfacePtr() == NULL)
		T::DoMessageBox(lpszPrompt, nType, nIDPrompt);

	// Empty cached message box text.
	m_strMBText.Empty();

	ASSERT(m_uiMessageBoxInterruptType != NoMessageBox);
		// Cannot be just a NoMessageBox, combine this with other flags.
	
	// NoMessageBox is entertained only if nType is not any of the following:
	if(m_uiMessageBoxInterruptType & NoMessageBox 
		&& (nType & (MB_ABORTRETRYIGNORE | MB_OKCANCEL | MB_RETRYCANCEL | MB_YESNO | MB_YESNOCANCEL)))
		m_uiMessageBoxInterruptType &= ~NoMessageBox;

	// If StoreMessage then cache the message in a member var.
	if(m_uiMessageBoxInterruptType & StoreMessage)
		m_strMBText = lpszPrompt;

	// Call base class if no NoMessageBox
	if(!(m_uiMessageBoxInterruptType & NoMessageBox))
	{
		long lActID = -1;
		// If CharReadOut, then prompt at the message box.
		if(m_uiMessageBoxInterruptType & CharReadOut)
		{
			m_uiMessageBoxInterruptType &= ~CharReadOut;

			// Figure out the center of the main wnd and where the msg box might get displayed
			CRect rectDesktop, rectMainWnd;
			HWND hWndDesk = ::GetDesktopWindow();
			::GetWindowRect(hWndDesk, &rectDesktop);
			CPoint pt(rectDesktop.CenterPoint().x, rectDesktop.CenterPoint().y);

			CWnd* pMainWnd = AfxGetMainWnd();
			if(pMainWnd)
			{
				pMainWnd->GetWindowRect(&rectMainWnd);
				rectMainWnd.IntersectRect(&rectMainWnd, &rectDesktop);
				pt.x = rectMainWnd.CenterPoint().x;
				pt.y = rectMainWnd.CenterPoint().y;
			}
			// Interrupt all Acts.
			m_pptrChar->InterruptAct(-1);
			GetAgentCharRef()->SetPosition(pt.x + 10, pt.y - 20);
			m_pptrChar->Speak(_bstr_t(lpszPrompt), Critical, &lActID);
		}

		int nRet = T::DoMessageBox(lpszPrompt, nType, nIDPrompt);
		if(lActID != -1)
			m_pptrChar->InterruptAct(lActID);
		return nRet;
	}

	// If CharReadOut, just Speak
	if(m_uiMessageBoxInterruptType & CharReadOut)
	{
		long lRequestID;
		GetAgentCharRef()->Speak(_bstr_t(lpszPrompt), _bstr_t(), &lRequestID);
	}

	return IDOK;
}

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // _OT_AGENT
