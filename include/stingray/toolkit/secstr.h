///////////////////////////////////////////////////////////////////////////////
// secstr.h
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


#ifndef __SECSTR_H__
#define __SECSTR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#define SEC_BEDIT1	_T("(nofiles)|NOFILES.$$$||")
#define SEC_BEDIT2	"All files (*.*)|*.*||"

#define SEC_CALEN1	_T("September, 2000")
#define SEC_CALEN2  _T("Sep, 2000")

#define SEC_DTPAR1	_T('h')
#define SEC_DTPAR2	_T('H')
#define SEC_DTPAR3	_T('m')
#define SEC_DTPAR4	_T('s')
#define SEC_DTPAR5	_T('t')
#define SEC_DTPAR6	_T('d')
#define SEC_DTPAR7	_T('M')
#define SEC_DTPAR8	_T('y')
#define SEC_DTPAR9	_T('g')


#define SEC_STOD1	"WARNING: Could not find: \"%s\"..."

#define MAIN_FRAME_LABEL  _T("MainFrame")
#define SEC_WSMGR1	_T("Window %d")

#define SEC_TBPG1	_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
#define SEC_TBPG2	_T('&')

#define SEC_SCUT1	_T('\t')
#define SEC_SCUT2	_T('\0')
#define SEC_SCUT3	_T("\t")

#endif // __SECSTR_H__