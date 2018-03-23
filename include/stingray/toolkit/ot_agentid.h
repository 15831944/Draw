///////////////////////////////////////////////////////////////////////////////
// ot_agentid.h
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
// Description:  Basic includes and constants for MSAgent
//


#ifndef _OT_AGENTID
#define _OT_AGENTID

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

// Import the Agent Server Interface from the type library in agentsvr.exe
// Need implementation only when building the library.
// NOTE: The Agent SDK is already installed On Windows XP and Windows Server 2003.
//       WinXP path:                         C:\WINDOWS\msagent   (x86)
//       WinXP 64-bit Edition path:          C:\WINDOWS\msagent   (x64)
//       Win Server 2K3 path:                C:\WINDOWS\msagent   (x86)
//       Win Server 2K3 64-bit Edition path: C:\WINDOWS\msagent64 (x64)
// User needs to add one of the above paths to compiler's IDE Executable directory.

#pragma message ("###########\r\nInformation:\r\n\tThis file will not compile unless you have the Agent SDK installed in your system\r\n\tand the path for agentsvr.exe included in your system environment variables or Visual Studio environment variables.\r\n\tYou can download the Agent SDK from www.microsoft.com\\msagent.\r\n\tOn Windows XP, Windows XP 64-bit Edition, Windows Server 2003 or Windows Server 2003 64-bit Edition, simply add the path C:\\WINDOWS\\msagent (or msagent64) to your system environment variables or Visual Studio's Executable directory.\r\n##########")
#ifndef SEC_AGENT_IMPLEMENTATION
#import "agentsvr.exe" no_implementation
#else
#import "agentsvr.exe"
#endif

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

// Use the namespace defined in agtsvr.tlh
using namespace AgentServerObjects;

// Constants copied over from the Microsoft supplied agtsvr.h.

#define	NeverMoved	( 0 )

#define	UserMoved	( 1 )

#define	ProgramMoved	( 2 )

#define	OtherProgramMoved	( 3 )

#define	SystemMoved	( 4 )

#define	NeverShown	( 0 )

#define	UserHid	( 1 )

#define	UserShowed	( 2 )

#define	ProgramHid	( 3 )

#define	ProgramShowed	( 4 )

#define	OtherProgramHid	( 5 )

#define	OtherProgramShowed	( 6 )

#define	UserHidViaCharacterMenu	( 7 )

#define	UserHidViaTaskbarIcon	( UserHid )

#define	CSHELPCAUSE_COMMAND	( 1 )

#define	CSHELPCAUSE_OTHERPROGRAM	( 2 )

#define	CSHELPCAUSE_OPENCOMMANDSWINDOW	( 3 )

#define	CSHELPCAUSE_CLOSECOMMANDSWINDOW	( 4 )

#define	CSHELPCAUSE_SHOWCHARACTER	( 5 )

#define	CSHELPCAUSE_HIDECHARACTER	( 6 )

#define	CSHELPCAUSE_CHARACTER	( 7 )

#define	ACTIVATE_NOTTOPMOST	( 0 )

#define	ACTIVATE_TOPMOST	( 1 )

#define	ACTIVATE_NOTACTIVE	( 0 )

#define	ACTIVATE_ACTIVE	( 1 )

#define	ACTIVATE_INPUTACTIVE	( 2 )

#define	PREPARE_ANIMATION	( 0 )

#define	PREPARE_STATE	( 1 )

#define	PREPARE_WAVE	( 2 )

#define	STOP_TYPE_PLAY	( 0x1 )

#define	STOP_TYPE_MOVE	( 0x2 )

#define	STOP_TYPE_SPEAK	( 0x4 )

#define	STOP_TYPE_PREPARE	( 0x8 )

#define	STOP_TYPE_NONQUEUEDPREPARE	( 0x10 )

#define	STOP_TYPE_VISIBLE	( 0x20 )

#define	STOP_TYPE_ALL	( 0xffffffff )

#define	BALLOON_STYLE_BALLOON_ON	( 0x1 )

#define	BALLOON_STYLE_SIZETOTEXT	( 0x2 )

#define	BALLOON_STYLE_AUTOHIDE	( 0x4 )

#define	BALLOON_STYLE_AUTOPACE	( 0x8 )

#define	AUDIO_STATUS_AVAILABLE	( 0 )

#define	AUDIO_STATUS_NOAUDIO	( 1 )

#define	AUDIO_STATUS_CANTOPENAUDIO	( 2 )

#define	AUDIO_STATUS_USERSPEAKING	( 3 )

#define	AUDIO_STATUS_CHARACTERSPEAKING	( 4 )

#define	AUDIO_STATUS_SROVERRIDEABLE	( 5 )

#define	AUDIO_STATUS_ERROR	( 6 )

#define	LISTEN_STATUS_CANLISTEN	( 0 )

#define	LISTEN_STATUS_NOAUDIO	( 1 )

#define	LISTEN_STATUS_NOTACTIVE	( 2 )

#define	LISTEN_STATUS_CANTOPENAUDIO	( 3 )

#define	LISTEN_STATUS_COULDNTINITIALIZESPEECH	( 4 )

#define	LISTEN_STATUS_SPEECHDISABLED	( 5 )

#define	LISTEN_STATUS_ERROR	( 6 )

#define	MK_ICON	( 0x1000 )

#define	LSCOMPLETE_CAUSE_PROGRAMDISABLED	( 1 )

#define	LSCOMPLETE_CAUSE_PROGRAMTIMEDOUT	( 2 )

#define	LSCOMPLETE_CAUSE_USERTIMEDOUT	( 3 )

#define	LSCOMPLETE_CAUSE_USERRELEASEDKEY	( 4 )

#define	LSCOMPLETE_CAUSE_USERUTTERANCEENDED	( 5 )

#define	LSCOMPLETE_CAUSE_CLIENTDEACTIVATED	( 6 )

#define	LSCOMPLETE_CAUSE_DEFAULTCHARCHANGE	( 7 )

#define	LSCOMPLETE_CAUSE_USERDISABLED	( 8 )

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif
