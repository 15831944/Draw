///////////////////////////////////////////////////////////////////////////////
// BLACKBOX.h
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
//  Author:		    PCB
//  Description:	Declarations for Crypto-BlackBox (SECCryptoBlackBox)
//  Created:		Apr 4, 1995
//
//  CHANGELOG:
//     PCB          12/1/95    SEC++ Accomodations
//
//

#ifndef __BLACKBOX_H__
#define __BLACKBOX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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

#include <StingrayExportDefs.h>

// forward class references
class SECCryptoRotor;


#define KEYSIZE 72
#define NROTORS 3

/////////////////////////////////////////////////////////////////////////////
// SECCryptoBlackBox

class SECCryptoBlackBox
{
public:
enum 	eDir { ENC, DEC };		// Direction: ENCrypt, DECrypt...
enum 	eMode { ECB, OFB }; 	// ECB == Electronic CodeBook 
								// OFB == Output FeedBack

// Construction
TOOLKIT_API SECCryptoBlackBox( TCHAR FAR *pswd = NULL, eDir dir=ENC, eMode mode = ECB );
TOOLKIT_API ~SECCryptoBlackBox( );
		
// Operations
TOOLKIT_API BOOL	SetPassword( const TCHAR FAR *buf );
TOOLKIT_API void 	SetPtr( long toWhere );
TOOLKIT_API void	SetDir( eDir dir );
TOOLKIT_API void 	SetMode( eMode mode );
TOOLKIT_API SECCryptoBlackBox::eMode	GetMode( void );
TOOLKIT_API void 	Reset( void );

TOOLKIT_API void 	TransformBuf( char FAR *buf, long nChars );

protected:
TOOLKIT_API void	Encrypt( char FAR &c );
TOOLKIT_API void	Decrypt( char FAR &c );

private:
const 	char &NextKey( void );
void 	HashString( char FAR *from, int fromSize, char FAR *to, int toSize );

// Attributes		
int 	m_nRotors;
SECCryptoRotor 
		*m_rotor;
eDir	m_opDir;
eMode 	m_opMode;
char	m_cFBD, m_cFBE;
 };


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _BLACKBOX_H_
		
