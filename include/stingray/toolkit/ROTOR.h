///////////////////////////////////////////////////////////////////////////////
// ROTOR.h
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
//  Description:	Declarations for CryptoRotor (SECCryptoRotor)
//  Created:		Apr 4, 1995
//
//  CHANGELOG:
//     PCB          12/1/95    SEC++ Accomodations
//
//

#ifndef __ROTOR_H__
#define __ROTOR_H__

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

#ifndef FALSE
#define FALSE 0
#endif /* FALSE */
#ifndef TRUE
#define TRUE (!FALSE)
#endif /* TRUE */

/////////////////////////////////////////////////////////////////////////////
// SECCryptoRotor

class SECCryptoRotor
{
// Construction
public:
		TOOLKIT_API SECCryptoRotor( char *array, long size );
		TOOLKIT_API SECCryptoRotor( );
		TOOLKIT_API ~SECCryptoRotor( );
		
// Operations
TOOLKIT_API BOOL 	Load( char *array, long size );
TOOLKIT_API void 	Set( long what );
TOOLKIT_API void	Reset( void );
TOOLKIT_API int	GetSize( void );
TOOLKIT_API char	GetChar( void );
TOOLKIT_API char	operator++( int );// int forces it to be postfix.

// Attributes
private:
		char *m_pBuffer;
		long  m_bufSz;
		long  m_ptr;
};
#endif // __ROTOR_H__
