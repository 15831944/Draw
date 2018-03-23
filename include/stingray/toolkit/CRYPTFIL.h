///////////////////////////////////////////////////////////////////////////////
// CRYPTFIL.h
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
//  Description:	Declarations for Crypto-File (SECCryptoFile)
//  Created:		Apr 4, 1995
//
//  CHANGELOG:
//     PCB          12/1/95    SEC++ Accomodations
//
//


#ifndef __CRYPTOFIL_H__
#define __CRYPTOFIL_H__

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


#ifndef __BLACKBOX_H__
#include "toolkit\blackbox.h"
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
// SECCryptoFile

/////////////////////////////
// AutoDuck tag block block for SECCryptoFile 


//@doc SECCryptoFile
//@mdata SECCryptoBlackBox  | SECCryptoFile | m_bb | En/decryption engine object.
//@xref <c SECCryptoFile>

// adinsert AutoDuck insertion point for SECCryptoFile 
//@doc SECCryptoFile 
//@class SECCryptoFile is derived from CFile, and provides encryption and 
// decryption services for data written to and from the file.
//
//@comm Two modes are provided, Electronic Codebook (ECB) and Output Feedback (OFB).
//
// ECB is moderately secure, and allows random access reads and writes.  
// However, application of sophisticated cryptographic methods allows much 
// easier recovery of the contents of each of two or more files encrypted 
// with the same password.  Encourage your users to change their passwords 
// frequently, or implement another layer of key management.
// 
// OFB is much more secure, but file access is unidirectional and sequential 
// only.  Therefore, an SECCryptoFile opened in OFB may be CFile::modeRead 
// or CFile::modeWrite, but not both.  The seek functions are also not 
// available.
//
// See the TEST32 sample in the \SAMPLES\TOOLKIT\STANDARD\UTILITY\CRYPT directory for a 
// demonstration of this class.
//@base public | CFile
class SECCryptoFile : public CFile 
{
public:
	
	//@cmember,menum
	/* Encryption directions*/
	enum eDir { 
		ENC,	//@@emem Encode
		DEC		//@@emem Decode
	} ;

	//@cmember,menum
	/* Encryption methods*/
	enum eMode { 
		ECB,	//@@emem Electronic Codebook encoding
		OFB		//@@emem Output Feedback encoding
	} ;

	//@access Creation/Initialization

	//@cmember
	/* Constructs a SECCryptoFile object.*/
	TOOLKIT_API SECCryptoFile( const TCHAR 	*pszFileName, 
					const TCHAR 	*pszPassword, 
					UINT 		nOpenFlags,
					eMode		CipherMode );
	
	//@cmember
	/* Constructs a SECCryptoFile object.*/
	TOOLKIT_API SECCryptoFile( int hFile, const TCHAR *pszPassword, eMode CipherMode );
	
	//@cmember
	/* Constructs a SECCryptoFile object.*/
	TOOLKIT_API SECCryptoFile();
	
	//@access Operations

	//@cmember
	/* Opens an SECCryptoFile with a path, password, direction and */
	//en/decryption mode.
	TOOLKIT_API BOOL Open( 	const TCHAR *pszFileName,
				const TCHAR *pszPassword, 
				UINT nOpenFlags,
	 			eMode CipherMode,
				CFileException *p = NULL );
	
	//@cmember
	/* Reads a number of bytes from the file and decrypts them. */
	TOOLKIT_API UINT Read( void FAR *pBuf, UINT nCount );

	//@cmember
	/* Reads a number of bytes from the file and decrypts them.  */
	TOOLKIT_API UINT ReadHuge( void FAR *pBuf, DWORD nCount );

	//@cmember
	/* Encrypts and then writes a number of characters to the file.*/
	TOOLKIT_API void Write( const void FAR *pBuf, UINT nCount );

	//@cmember
	/* Encrypts and then writes a number of characters to the file.  */
	TOOLKIT_API void WriteHuge( void FAR *pBuf, DWORD nCount );
	
	//@cmember
	/* Moves to a specified location in the file.  */
	TOOLKIT_API long Seek( long lOff, UINT nFrom );

	//@cmember
	/* Moves to the beginning of the file.*/
	TOOLKIT_API void SeekToBegin( void );

	//@cmember
	/* Moves to the end of the file.  Only usable in ECB mode.*/
	TOOLKIT_API void SeekToEnd( void );

protected:

	//@access Protected data members

	//@cmember
	/* En/decryption engine object.*/
	SECCryptoBlackBox m_bb;
};	


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __CRYPTOFIL_H__

