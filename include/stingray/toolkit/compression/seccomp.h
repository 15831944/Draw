///////////////////////////////////////////////////////////////////////////////
// seccomp.h
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
//  Author:		    AAB
//  Description:	Declarations for Compress-File (SECCompress)
//  Created:		Jan 15, 1996
//
//  CHANGELOG:
//     AAB	1/15/96		Original creation based on CCryptoFile architecture
//
//

#ifndef __SECCOMPRESS_FILE_H__
#define __SECCOMPRESS_FILE_H__

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

#ifndef OT_ZLIB095
	#error Add Zlib 0.9.5 support using OT Build Wizard before use SECCompressFile
#endif

#ifdef OT_ZLIB095
	//#include "..\..\..\src\toolkit\utility\compression\zlib095\compeng.h"
  #include "compeng.h"
#endif

#include <StingrayExportDefs.h>


/////////////////////////////////////////////////////////////////////////////
// SECCompressFile

/////////////////////////////
// AutoDuck tag block block for SECCompressFile 
//@doc SECCompressFile
//@mdata SECComp  | SECCompressFile | m_Comp | Compression engine object.
//@xref <c SECCompressFile>

//@doc SECCompressFile
//@mdata gzFile  | SECCompressFile | m_gzFile | 'zlib' compression object.
//@xref <c SECCompressFile>

//@doc SECCompressFile
//@mdata BOOL  | SECCompressFile | m_bReadHuge | Flag when reading huge 
// vals (WIN3.1 only)
//@xref <c SECCompressFile>

//@doc SECCompressFile
//@mdata BOOL  | SECCompressFile | m_bCompressMode | Indicates whether 
// compression is enabled or disabled.
//@xref <c SECCompressFile> <mf SECComp::SetCompressMode>

// adinsert AutoDuck insertion point for SECCompressFile 
//@doc SECCompressFile 
//@class SECCompressFile is derived from CFile, and provides compression 
// and decompression services for data written to and from the file.
//
//@comm An instance of SECCompressFile can be in compression mode, where a 
// limited number of CFile access functions are available; and regular 
// mode, where normal CFile behavior is exhibited.
//
// Since SECCompressFile compresses its data as a whole, it is not 
// possible to seek to the middle of a compressed data block to partially 
// decompress a block.
//
// However, by switching back and forth between compressed mode and normal 
// CFile mode, compressed data can be written to a file in different 
// locations, and a jump table might be placed at the beginning of the 
// file to store seek locations of the different compressed blocks.
//
// See the COMPDEMO sample in the \SAMPLES\TOOLKIT\STANDARD\UTILITY\CFILES directory for a 
// demonstration of this class.
//@base public | CFile
class SECCompressFile : public CFile 
{
public:

	//@access Creation/Initialization

	//@cmember
	/* Constructs a SECCompressFile object.*/
	TOOLKIT_API SECCompressFile();

	//@cmember
	/* Constructs a SECCompressFile object.*/
	TOOLKIT_API SECCompressFile(  LPCTSTR lpszFileName, UINT nOpenFlags );
	
	//@cmember
	/* Constructs a SECCompressFile object.*/
	TOOLKIT_API SECCompressFile( int hFile );

	virtual ~SECCompressFile() { if (m_bCompressMode) Close(); }
	
	//@access Operations
	
	//@cmember
	/* Opens an SECCompressFile with a given pathname.*/
	TOOLKIT_API virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError = NULL, int nCompLevel=-1);

	//@cmember
	/* Reads a number of bytes from the file and decompresses them. */
	TOOLKIT_API UINT Read( void FAR *pBuf, UINT nCount );
	
	//@cmember
	/* Reads a number of bytes from the file and decompresses them.  */
	// Semantically equivalent to Read, in Win32.
	TOOLKIT_API DWORD ReadHuge( void FAR *pBuf, DWORD nCount );
	
	//@cmember
	/* Compresses and then writes a number of characters to the file.*/
	TOOLKIT_API void Write( const void FAR *pBuf, UINT nCount );
	
	//@cmember
	/* Compresses and then writes a number of characters to the file.  */
	// Semantically equivalent to Write, in Win32.
	TOOLKIT_API void WriteHuge( void FAR *pBuf, DWORD nCount );
	
	//@cmember
	/* Seeks to the specified location.*/
	TOOLKIT_API long Seek( long lOff, UINT nFrom );
	
	//@cmember
	/* Seeks to the beginning of file.*/
	TOOLKIT_API void SeekToBegin( void );
	
	//@cmember
	/* Seeks to end of file.*/
	TOOLKIT_API void SeekToEnd( void );
	
	//@cmember
	/* Returns the compressed length of the file.*/
	TOOLKIT_API DWORD GetLength();
	
	//@cmember
	/* Closes the file.*/
	TOOLKIT_API void Close( void );
	
	//@cmember
	/* Turns the compression mode on or off.*/
	TOOLKIT_API void SetCompressMode(BOOL bState);
	
	//@cmember
	/* Retrieves whether compression is enabled or disabled.*/
	TOOLKIT_API BOOL GetCompressMode();

public: 

	//@access Public data members
	
	//@cmember
	/* Compression engine object.*/
	SECComp m_Comp;

	//@cmember
	/* 'zlib' compression object.*/
	gzFile	m_gzFile; 

#ifndef WIN32
	//@cmember
	/* Flag when reading huge vals (WIN3.1 only)*/
	BOOL	m_bReadHuge;
#endif

protected:
	
	//@access Protected data members

	//@cmember
	/* Indicates whether compression is enabled or disabled.*/
	BOOL m_bCompressMode;

};	

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECCOMPRESS_FILE_H__

